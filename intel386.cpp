//
// i386 processor.
//
// Copyright (c) 2026 Serge Vakulenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "intel386.h"

#include <capstone.h>

#include <iomanip>
#include <iostream>

#include "machine.h"

//
// 386 size codes (B=byte, W=word, D=dword).
//
enum {
    B = 0,
    W = 1,
    D = 2,
};
static const unsigned SIGN[3] = { 0x80u, 0x8000u, 0x80000000u };
static const unsigned MASK[3] = { 0xffu, 0xffffu, 0xffffffffu };

static const uint8_t PARITY[256] = {
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1
};

struct SegmentFault {};
struct InstructionFault {}; // e.g. #UD for invalid LOCK; exit REP without updating ECX

//
// Initialize the processor.
//
Intel386::Intel386(Machine &mach) : machine(mach)
{
    reset();
}

//
// Reset routine: all registers and opcode to initial 386 state.
//
void Intel386::reset()
{
    core     = {};
    core.eip = 0x00000000;
    core.cs  = 0xffff;
    core.ds  = 0x0000;
    core.ss  = 0x0000;
    core.es  = 0x0000;
    core.fs  = 0x0000;
    core.gs  = 0x0000;
    set_eflags(0);
    opcode           = {};
    plen             = 0;
    rep              = 0;
    segment_override = false;
    os               = core.ds;
    ea               = -1;

    // Show initial state.
    machine.trace_exception("Reset");
}

//
// Print instruction address and opcode.
//
void Intel386::print_instruction()
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();
    auto pc         = (core.cs << 4) + core.eip;
    static csh disasm;

    // Initialize Capstone for i86 16-bit mode.
    if (!disasm && cs_open(CS_ARCH_X86, CS_MODE_16, &disasm) != CS_ERR_OK) {
        throw std::runtime_error("Failed to initialize Capstone");
    }

    out << std::hex << std::setfill('0') << std::setw(5) << pc << " :";

    // Disassemble one instruction.
    cs_insn *insn;
    size_t count = cs_disasm(disasm, opcode.data(), opcode.size(), 0x0, 1, &insn);
    if (count > 0) {
        size_t i;
        for (i = 0; i < insn->size; ++i) {
            out << ' ' << std::setw(2) << std::setfill('0') << (unsigned)insn->bytes[i];
        }
        for (; i < 6; ++i) {
            out << "   ";
        }
        out << "  " << insn[0].mnemonic << ' ' << insn[0].op_str;
        cs_free(insn, count);
    } else {
        // Cannot disassembler, just print bytes.
        for (size_t i = 0; i < opcode.size(); ++i) {
            out << ' ' << std::setw(2) << std::setfill('0') << (unsigned)opcode[i];
        }
    }
    out << std::endl;

    out.flags(save_flags);
}

//
// Print changed CPU registers (core vs prev), then update prev.
//
void Intel386::print_registers()
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    if (core.eax != prev.eax)
        out << "\tEAX = " << std::hex << std::setfill('0') << std::setw(8) << core.eax << std::endl;
    if (core.ebx != prev.ebx)
        out << "\tEBX = " << std::hex << std::setfill('0') << std::setw(8) << core.ebx << std::endl;
    if (core.ecx != prev.ecx)
        out << "\tECX = " << std::hex << std::setfill('0') << std::setw(8) << core.ecx << std::endl;
    if (core.edx != prev.edx)
        out << "\tEDX = " << std::hex << std::setfill('0') << std::setw(8) << core.edx << std::endl;
    if (core.esp != prev.esp)
        out << "\tESP = " << std::hex << std::setfill('0') << std::setw(8) << core.esp << std::endl;
    if (core.ebp != prev.ebp)
        out << "\tEBP = " << std::hex << std::setfill('0') << std::setw(8) << core.ebp << std::endl;
    if (core.esi != prev.esi)
        out << "\tESI = " << std::hex << std::setfill('0') << std::setw(8) << core.esi << std::endl;
    if (core.edi != prev.edi)
        out << "\tEDI = " << std::hex << std::setfill('0') << std::setw(8) << core.edi << std::endl;
    if (core.cs != prev.cs)
        out << "\tCS = " << std::hex << std::setfill('0') << std::setw(4) << core.cs << std::endl;
    if (core.ds != prev.ds)
        out << "\tDS = " << std::hex << std::setfill('0') << std::setw(4) << core.ds << std::endl;
    if (core.ss != prev.ss)
        out << "\tSS = " << std::hex << std::setfill('0') << std::setw(4) << core.ss << std::endl;
    if (core.es != prev.es)
        out << "\tES = " << std::hex << std::setfill('0') << std::setw(4) << core.es << std::endl;
    if (core.fs != prev.fs)
        out << "\tFS = " << std::hex << std::setfill('0') << std::setw(4) << core.fs << std::endl;
    if (core.gs != prev.gs)
        out << "\tGS = " << std::hex << std::setfill('0') << std::setw(4) << core.gs << std::endl;
    if (core.flags.w != prev.flags.w) {
        out << "\tEFlags = " << std::hex << std::setfill('0') << std::setw(8) << core.flags.w;
        if (core.flags.w & 0x800)
            out << " OF";
        if (core.flags.w & 0x400)
            out << " DF";
        if (core.flags.w & 0x200)
            out << " IF";
        if (core.flags.w & 0x100)
            out << " TF";
        if (core.flags.w & 0x80)
            out << " SF";
        if (core.flags.w & 0x40)
            out << " ZF";
        if (core.flags.w & 0x10)
            out << " AF";
        if (core.flags.w & 0x4)
            out << " PF";
        if (core.flags.w & 0x1)
            out << " CF";
        out << std::endl;
    }

    prev = core;
    out.flags(save_flags);
}

//
// Set FLAGS/EFLAGS register.
//
void Intel386::set_flags(Word val)
{
    set_eflags((core.flags.w & 0xFFFF0000u) | (val & 0xFFFFu));
}

void Intel386::set_eflags(Dword val)
{
    static const Dword RESERVED_OFF_MASK = 0x00008028; // Bits 3,5,15 always off
    static const Dword RESERVED_ON_MASK  = 0xFFFC0002; // Bits 1,18-31 always on

    core.flags.w = (val & ~RESERVED_OFF_MASK) | RESERVED_ON_MASK;
}

void Intel386::update_flags_zsp(int width, int res)
{
    // Zero flag.
    core.flags.f.zf = res == 0;

    // Sign flag.
    if (width == B) {
        core.flags.f.sf = (int8_t)res < 0;
    } else if (width == W) {
        core.flags.f.sf = (int16_t)res < 0;
    } else {
        core.flags.f.sf = (int32_t)res < 0;
    }

    // Parity flag.
    core.flags.f.pf = PARITY[(Byte)res];
}

//
// Get effective address, caching result so getRM+setRM only advance EIP once.
//
unsigned Intel386::getEA_cached(unsigned mod_val, unsigned rm_val)
{
    if (ea >= 0)
        return static_cast<unsigned>(ea);
    unsigned addr = getEA(mod_val, rm_val);
    ea            = static_cast<int>(addr);
    return addr;
}

//
// Effective address from ModR/M and displacement. Handles both 16-bit and 32-bit
// addressing modes (address_32 for SIB, disp32, etc.).
//
unsigned Intel386::getEA(unsigned mod_val, unsigned rm_val)
{
    if (address_32) {
        int disp = 0;
        int off  = 2;      // bytes after ModR/M
        if (rm_val == 4) { // SIB
            Byte sib  = opcode[plen + off];
            int scale = 1 << (sib >> 6);
            int index = (sib >> 3) & 7;
            int base  = sib & 7;
            off++;
            // base=4 (ESP) with mod=00: [ESP+index*scale], no disp. base=5 (EBP) with mod=00: no
            // base, disp32.
            Dword base_val = (base == 5 && mod_val == 0) ? 0 : static_cast<Dword>(getReg(D, base));
            if (base == 5 && mod_val == 0) {
                disp = static_cast<int32_t>(static_cast<Dword>(
                    opcode[plen + off] | (opcode[plen + off + 1] << 8) |
                    (opcode[plen + off + 2] << 16) | (opcode[plen + off + 3] << 24)));
            } else if (mod_val == 1) {
                disp = (int8_t)opcode[plen + off];
            } else if (mod_val == 2) {
                disp = static_cast<int32_t>(static_cast<Dword>(
                    opcode[plen + off] | (opcode[plen + off + 1] << 8) |
                    (opcode[plen + off + 2] << 16) | (opcode[plen + off + 3] << 24)));
            }
            // 386 quirk: when index=4 (none) and base is not ESP/EBP (or EBP with mod!=0), use
            // [base*scale+disp] (real 386 encodes [ESI*8+disp] as SIB 0xE6) 386 quirk: when index=4
            // (none) and base=4 (ESP), scale applies to base: [ESP*scale+disp]
            Dword index_val;
            if (index == 4 && base != 4 && (base != 5 || mod_val != 0)) {
                index_val = static_cast<Dword>(getReg(D, base));
                base_val  = 0;
            } else {
                index_val = (index == 4) ? 0 : static_cast<Dword>(getReg(D, index));
            }
            int32_t addr_signed;
            if (index == 4 && base == 4) {
                addr_signed = static_cast<int32_t>(base_val * scale + disp);
            } else {
                addr_signed =
                    static_cast<int32_t>(base_val) + static_cast<int32_t>(index_val) * scale + disp;
            }
            // Real-mode segment limit: store signed offset so limit check can fault on negative or
            // >= 64K
            last_ea_offset = static_cast<Dword>(addr_signed);
            return linear_addr21(os, static_cast<Word>(last_ea_offset));
        }
        // mod=0, r/m=5: [disp32] only, no base register (not [EBP])
        Dword rv = (rm_val == 5 && mod_val == 0) ? 0 : static_cast<Dword>(getReg(D, rm_val));
        if (rm_val == 5 && mod_val == 0) {
            disp = static_cast<int32_t>(static_cast<Dword>(
                opcode[plen + off] | (opcode[plen + off + 1] << 8) |
                (opcode[plen + off + 2] << 16) | (opcode[plen + off + 3] << 24)));
        } else if (mod_val == 1) {
            disp = (int8_t)opcode[plen + off];
        } else if (mod_val == 2) {
            disp = static_cast<int32_t>(static_cast<Dword>(
                opcode[plen + off] | (opcode[plen + off + 1] << 8) |
                (opcode[plen + off + 2] << 16) | (opcode[plen + off + 3] << 24)));
        }
        // Real-mode segment limit: store signed offset so limit check can fault on negative or >=
        // 64K
        last_ea_offset = static_cast<Dword>(static_cast<int32_t>(rv) + disp);
        return linear_addr21(os, static_cast<Word>(last_ea_offset));
    }

    // 16-bit addressing modes (8086)
    int disp;
    switch (mod_val) {
    default:
        disp = 0;
        break;
    case 1:
        disp = (int8_t)opcode[plen + 2];
        break;
    case 2:
        disp = opcode[plen + 2] | (opcode[plen + 3] << 8);
        break;
    }

    // 16-bit addressing: use low 16 bits of 32-bit base/index registers
    Word bx = static_cast<Word>(core.ebx), bp = static_cast<Word>(core.ebp);
    Word si = static_cast<Word>(core.esi), di = static_cast<Word>(core.edi);
    Dword full_sum = 0;
    switch (rm_val) {
    case 0b000:
        full_sum = bx + si + disp;
        break;
    case 0b001:
        full_sum = bx + di + disp;
        break;
    case 0b010:
        full_sum = bp + si + disp;
        break;
    case 0b011:
        full_sum = bp + di + disp;
        break;
    case 0b100:
        full_sum = si + disp;
        break;
    case 0b101:
        full_sum = di + disp;
        break;
    case 0b110:
        if (mod_val == 0)
            full_sum = opcode[plen + 2] | (opcode[plen + 3] << 8);
        else
            full_sum = bp + disp;
        break;
    case 0b111:
        full_sum = bx + disp;
        break;
    default:
        break;
    }
    last_ea_offset = static_cast<Word>(full_sum);
    return linear_addr21(os, static_cast<Word>(full_sum));
}

//
// Fetch 1, 2, or 4 bytes at CS:EIP, advance EIP.
//
int Intel386::fetch(int width)
{
    int bytes = (width == D) ? 4 : (width == W) ? 2 : 1;
    check_cs_fetch_limit(core.eip + bytes);
    unsigned addr = linear_addr32(core.cs, core.eip);
    int val       = machine.mem_fetch_byte(addr);
    if (width == W) {
        val |= machine.mem_fetch_byte(addr + 1) << 8;
    } else if (width == D) {
        val |= machine.mem_fetch_byte(addr + 1) << 8;
        val |= machine.mem_fetch_byte(addr + 2) << 16;
        val |= machine.mem_fetch_byte(addr + 3) << 24;
    }
    core.eip += (width == D) ? 4 : (1 + width);
    return val;
}

//
// Read byte, word or dword at linear address.
//
int Intel386::getMem(int width, unsigned addr)
{
    if (width == B)
        return machine.mem_load_byte(addr);
    if (width == W)
        return machine.mem_load_word(addr);
    return static_cast<int>(machine.mem_load_32(addr));
}

//
// Write byte, word or dword at linear address.
//
void Intel386::setMem(int width, unsigned addr, int val)
{
    if (width == B)
        machine.mem_store_byte(addr, val);
    else if (width == W)
        machine.mem_store_word(addr, val);
    else
        machine.mem_store_32(addr, val);
}

//
// Word access with 8086 segment offset wraparound (offset 0xFFFF -> second byte at seg:0).
//
int Intel386::getMemAtSegOff(int width, Word seg, Word off)
{
    if (width == B) {
        return machine.mem_load_byte(linear_addr21(seg, off));
    }
    if (width == D) {
        unsigned addr = linear_addr21(seg, off);
        return static_cast<int>(machine.mem_load_32(addr));
    }
    if (off == 0xffff) {
        Byte lo = machine.mem_load_byte(linear_addr21(seg, static_cast<Word>(0xffff)));
        Byte hi = machine.mem_load_byte(linear_addr21(seg, static_cast<Word>(0)));
        return lo | (hi << 8);
    }
    return machine.mem_load_word(linear_addr21(seg, off));
}

void Intel386::setMemAtSegOff(int width, Word seg, Word off, int val)
{
    if (width == B) {
        machine.mem_store_byte(linear_addr21(seg, off), val);
        return;
    }
    if (width == D) {
        unsigned addr = linear_addr21(seg, off);
        machine.mem_store_32(addr, static_cast<Dword>(val));
        return;
    }
    if (off == 0xffff) {
        machine.mem_store_byte(linear_addr21(seg, static_cast<Word>(0xffff)), val);
        machine.mem_store_byte(linear_addr21(seg, static_cast<Word>(0)), val >> 8);
        return;
    }
    machine.mem_store_word(linear_addr21(seg, off), val);
}

//
// Get general or pointer register (reg encoding: 0=AX/AL, 1=CX/CL, ..., 4=SP, 5=BP, 6=SI, 7=DI).
// Return sign extended value.
//
int Intel386::getReg(int width, unsigned r) const
{
    switch (width) {
    case B:
        switch (r) {
        case 0:
            return (int8_t)get_al();
        case 1:
            return (int8_t)get_cl();
        case 2:
            return (int8_t)get_dl();
        case 3:
            return (int8_t)get_bl();
        case 4:
            return (int8_t)get_ah();
        case 5:
            return (int8_t)get_ch();
        case 6:
            return (int8_t)get_dh();
        case 7:
            return (int8_t)get_bh();
        default:
            return 0;
        }
    case W:
        switch (r) {
        case 0:
            return (int16_t)get_ax();
        case 1:
            return (int16_t)get_cx();
        case 2:
            return (int16_t)get_dx();
        case 3:
            return (int16_t)get_bx();
        case 4:
            return (int16_t)get_sp();
        case 5:
            return (int16_t)get_bp();
        case 6:
            return (int16_t)get_si();
        case 7:
            return (int16_t)get_di();
        default:
            return 0;
        }
    case D:
    default:
        switch (r) {
        case 0:
            return (int32_t)core.eax;
        case 1:
            return (int32_t)core.ecx;
        case 2:
            return (int32_t)core.edx;
        case 3:
            return (int32_t)core.ebx;
        case 4:
            return (int32_t)core.esp;
        case 5:
            return (int32_t)core.ebp;
        case 6:
            return (int32_t)core.esi;
        case 7:
            return (int32_t)core.edi;
        default:
            return 0;
        }
    }
}

//
// Set general or pointer register.
//
void Intel386::setReg(int width, unsigned r, int val)
{
    if (width == B) {
        switch (r) {
        case 0:
            set_al(val);
            break;
        case 1:
            set_cl(val);
            break;
        case 2:
            set_dl(val);
            break;
        case 3:
            set_bl(val);
            break;
        case 4:
            set_ah(val);
            break;
        case 5:
            set_ch(val);
            break;
        case 6:
            set_dh(val);
            break;
        case 7:
            set_bh(val);
            break;
        default:
            break;
        }
    } else if (width == W) {
        Word v = val & 0xFFFF;
        switch (r) {
        case 0:
            set_ax(v);
            break;
        case 1:
            set_cx(v);
            break;
        case 2:
            set_dx(v);
            break;
        case 3:
            set_bx(v);
            break;
        case 4:
            set_sp(v);
            break;
        case 5:
            set_bp(v);
            break;
        case 6:
            set_si(v);
            break;
        case 7:
            set_di(v);
            break;
        default:
            break;
        }
    } else {
        Dword v = val & 0xFFFFFFFFu;
        switch (r) {
        case 0:
            core.eax = v;
            break;
        case 1:
            core.ecx = v;
            break;
        case 2:
            core.edx = v;
            break;
        case 3:
            core.ebx = v;
            break;
        case 4:
            core.esp = v;
            break;
        case 5:
            core.ebp = v;
            break;
        case 6:
            core.esi = v;
            break;
        case 7:
            core.edi = v;
            break;
        default:
            break;
        }
    }
}

//
// Get R/M operand (register or memory from mod/rm). Effective address from ModR/M and displacement.
// 8086 segment wraparound: word at offset 0xFFFF has high byte at offset 0 in same segment.
//
int Intel386::getRM(int width, unsigned mod_val, unsigned rm_val)
{
    if (mod_val == 0b11)
        return getReg(width, rm_val);
    unsigned addr  = getEA_cached(mod_val, rm_val);
    unsigned bytes = (width == D) ? 4 : (width == W) ? 2 : 1;
    if (last_ea_offset > 0x10000 - bytes)
        raise_segment_fault();
    return getMem(width, addr);
}

//
// Set R/M operand.
// 8086 segment wraparound: word at offset 0xFFFF has high byte at offset 0 in same segment.
//
void Intel386::setRM(int width, unsigned mod_val, unsigned rm_val, int val)
{
    if (mod_val == 0b11)
        setReg(width, rm_val, val);
    else {
        unsigned addr  = getEA_cached(mod_val, rm_val);
        unsigned bytes = (width == D) ? 4 : (width == W) ? 2 : 1;
        if (last_ea_offset > 0x10000 - bytes)
            raise_segment_fault();
        setMem(width, addr, val);
    }
}

//
// Get segment register (encoding 0=ES, 1=CS, 2=SS, 3=DS, 4=FS, 5=GS).
//
Word Intel386::getSegReg(unsigned r) const
{
    switch (r & 7) {
    case 0:
        return core.es;
    case 1:
        return core.cs;
    case 2:
        return core.ss;
    case 3:
        return core.ds;
    case 4:
        return core.fs;
    case 5:
        return core.gs;
    default:
        return 0;
    }
}

//
// Set segment register.
//
void Intel386::setSegReg(unsigned r, Word val)
{
    switch (r & 7) {
    case 0:
        core.es = val;
        break;
    case 1:
        core.cs = val;
        break;
    case 2:
        core.ss = val;
        break;
    case 3:
        core.ds = val;
        break;
    case 4:
        core.fs = val;
        break;
    case 5:
        core.gs = val;
        break;
    default:
        break;
    }
}

//
// Decode ModR/M byte from opcode; advance IP by 1, 2, or 3.
//
void Intel386::decode()
{
    ensure_opcode_bytes(2);
    mod = (opcode[plen + 1] >> 6) & 0b11;
    reg = (opcode[plen + 1] >> 3) & 0b111;
    rm  = opcode[plen + 1] & 0b111;

    if (address_32 && mod != 0b11) {
        int advance = 1; // ModR/M byte
        if (rm == 4) {
            ensure_opcode_bytes(3);
            Byte sib = opcode[plen + 2];
            int base = sib & 7;
            advance++; // SIB byte
            // SS when base is ESP or EBP (except mod=0 base=5 which uses disp32, no base).
            if (!segment_override && (base == 4 || (base == 5 && mod != 0))) {
                os       = core.ss;
                os_is_ss = true;
            }
            if ((mod == 0 && base == 5) || mod == 2) {
                ensure_opcode_bytes(7);
                advance += 4;
            } else if (mod == 1) {
                ensure_opcode_bytes(4);
                advance += 1;
            } else {
                ensure_opcode_bytes(3);
            }
        } else {
            // mod!=0, rm=5: [EBP+disp]; mod=0, rm=5: [disp32] uses DS
            if (!segment_override && rm == 5 && mod != 0) {
                os       = core.ss;
                os_is_ss = true;
            }
            if (mod == 0 && rm == 5) {
                ensure_opcode_bytes(6);
                advance += 4;
            } else if (mod == 1) {
                ensure_opcode_bytes(4);
                advance += 1;
            } else if (mod == 2) {
                ensure_opcode_bytes(6);
                advance += 4;
            } else {
                ensure_opcode_bytes(2);
            }
        }
        core.eip += advance;
        return;
    }
    // 16-bit addressing
    if (mod == 0b01) {
        ensure_opcode_bytes(3);
        core.eip += 2;
    } else if ((mod == 0b00 && rm == 0b110) || mod == 0b10) {
        ensure_opcode_bytes(4); // ModR/M + disp16 (need plen+1..plen+3)
        core.eip += 3;
    } else {
        core.eip += 1;
    }

    // Default segment: use SS when effective address uses BP (no segment override).
    if (!segment_override && mod != 0b11 && (rm == 2 || rm == 3 || (rm == 6 && mod != 0))) {
        os       = core.ss;
        os_is_ss = true;
    }
}

//
// Stack is SS:SP; 16-bit little-endian. Pop word.
//
int Intel386::pop()
{
    int val = getMemAtSegOff(W, core.ss, static_cast<Word>(core.esp));
    set_sp(get_sp() + 2);
    return val;
}

//
// Push word onto stack.
//
void Intel386::push(int val)
{
    set_sp(get_sp() - 2);
    setMemAtSegOff(W, core.ss, static_cast<Word>(core.esp), val);
}

int Intel386::pop32()
{
    Word sp = static_cast<Word>(core.esp);
    int val;
    // Real-mode wrap: pop at top of segment wraps within the first 64K (matches pop_esp,
    // o32_pop_ds).
    if (sp > 0x10000 - 4) {
        val = 0;
        for (int i = 0; i < 4; i++)
            val |= static_cast<int>(
                       machine.mem_load_byte(linear_addr21(core.ss, static_cast<Word>(sp + i))))
                   << (i * 8);
    } else {
        val = getMem(D, linear_addr21(core.ss, sp));
    }
    set_sp(get_sp() + 4);
    return val;
}

void Intel386::push32(Dword val)
{
    Word sp = static_cast<Word>(get_sp() - 4);
    set_sp(sp);
    if (sp > 0x10000 - 4) {
        // Wrap when crossing segment boundary (match pop32 behavior)
        for (int i = 0; i < 4; i++)
            machine.mem_store_byte(linear_addr21(core.ss, static_cast<Word>(sp + i)),
                                   static_cast<Byte>(val >> (i * 8)));
    } else {
        unsigned addr = linear_addr21(core.ss, sp);
        machine.mem_store_byte(addr, val);
        machine.mem_store_byte(addr + 1, val >> 8);
        machine.mem_store_byte(addr + 2, val >> 16);
        machine.mem_store_byte(addr + 3, val >> 24);
    }
}

//
// Software interrupt: push FLAGS, CS, IP; jump to vector.
//
void Intel386::call_int(int type)
{
    if (machine.is_syscall(type)) {
        // Intercept syscalls.
        machine.process_syscall(type);
        return;
    }

    // Fetch interrupt vector.
    Word offset = getMem(W, type * 4);
    Word seg    = getMem(W, type * 4 + 2);
#if 1
    if (machine.trace_enabled()) {
        machine.print_syscall(type);
    }
#endif
    // Take interrupt: push FLAGS first (with IF/TF as-is), then clear them.
    push(core.flags.w);
    core.flags.f.ifl = 0;
    core.flags.f.tf  = 0;
    push(core.cs);
    push(core.eip);
    core.eip = offset;
    core.cs  = seg;
}

//
// Real-mode segment limit violation: set fault EIP and take #SS or #GP.
//
void Intel386::raise_segment_fault()
{
    core.eip = fault_eip;
    call_int(os_is_ss ? 12 : 13);
    throw SegmentFault{};
}

//
// Real-mode code segment limit: if fetch would read past offset 0xFFFF, take #GP.
//
void Intel386::check_cs_fetch_limit(Dword fetch_end_exclusive)
{
    if (!(core.cr0 & 1)) { // real mode
        if (fetch_end_exclusive > 0x10000u) {
            core.eip = fault_eip;
            call_int(13);
            throw SegmentFault{};
        }
    }
}

//
// Ensure opcode[] has at least plen + n bytes; fetch from CS:EIP one byte at a time with CS limit check.
//
void Intel386::ensure_opcode_bytes(unsigned n)
{
    while (opcode.size() < plen + n) {
        // Next byte to fetch: at EIP when size==plen (first opcode byte), else at EIP+(size-plen-1).
        unsigned need = static_cast<unsigned>(opcode.size() - plen);
        unsigned off  = (need == 0) ? 0 : (need - 1);
        check_cs_fetch_limit(core.eip + off + 1);
        opcode.push_back(machine.mem_fetch_byte(linear_addr32(core.cs, core.eip + off)));
    }
}

//
// ALU helpers (set CF, AF, OF, PF, ZF, SF).
//
int Intel386::add(int width, int dst, int src)
{
    int res = (dst + src) & MASK[width];
    // Update only arithmetic flags; preserve IF, TF, etc.
    Dword mask = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;
    core.flags.w &= ~mask;
    Dword udst = dst & MASK[width], ures = res & MASK[width];
    core.flags.w |= (ures < udst ? CF_MASK : 0);
    core.flags.w |= (((res ^ dst ^ src) & 0x10) ? AF_MASK : 0);
    core.flags.w |= (((dst ^ ~src) & (dst ^ res) & SIGN[width]) ? OF_MASK : 0);
    update_flags_zsp(width, res);
    return res;
}

int Intel386::adc(int width, int dst, int src)
{
    int carry       = core.flags.f.cf;
    int res         = (dst + src + carry) & MASK[width];
    Dword udst      = dst & MASK[width];
    Dword ures      = res & MASK[width];
    core.flags.f.cf = carry ? (ures <= udst) : (ures < udst);
    core.flags.f.af = (((dst & 0xF) + (src & 0xF) + (carry ? 1 : 0)) & 0x10) != 0;
    core.flags.f.of = ((dst ^ ~src) & (dst ^ res) & SIGN[width]) != 0;
    update_flags_zsp(width, res);
    return res;
}

int Intel386::sub(int width, int dst, int src)
{
    int res         = (dst - src) & MASK[width];
    Dword udst      = dst & MASK[width];
    Dword usrc      = src & MASK[width];
    core.flags.f.cf = udst < usrc;
    core.flags.f.af = ((res ^ dst ^ src) & 0x10) != 0;
    core.flags.f.of = ((dst ^ src) & (dst ^ res) & SIGN[width]) != 0;
    update_flags_zsp(width, res);
    return res;
}

int Intel386::sbb(int width, int dst, int src)
{
    int carry  = core.flags.f.cf;
    int res    = (dst - src - carry) & MASK[width];
    Dword udst = dst & MASK[width];
    Dword usrc = src & MASK[width];
    // Compare in 64-bit so (usrc + carry) cannot overflow and produce wrong CF
    core.flags.f.cf =
        (static_cast<uint64_t>(udst) < static_cast<uint64_t>(usrc) + (carry ? 1u : 0u));
    core.flags.f.af = ((res ^ dst ^ src) & 0x10) != 0;
    core.flags.f.of = ((dst ^ src) & (dst ^ res) & SIGN[width]) != 0;
    update_flags_zsp(width, res);
    return res;
}

int Intel386::inc(int width, int dst)
{
    unsigned res    = (dst + 1) & MASK[width];
    core.flags.f.af = ((res ^ dst ^ 1) & 0x10) != 0;
    core.flags.f.of = res == SIGN[width];
    update_flags_zsp(width, res);
    return res;
}

int Intel386::dec(int width, int dst)
{
    unsigned res    = (dst - 1) & MASK[width];
    core.flags.f.af = ((res ^ dst ^ 1) & 0x10) != 0;
    core.flags.f.of = res == SIGN[width] - 1;
    update_flags_zsp(width, res);
    return res;
}

void Intel386::logic(int width, int res)
{
    core.flags.f.cf = 0;
    core.flags.f.of = 0;
    core.flags.f.af = 0; // undefined per Intel; real 8086 clears it
    update_flags_zsp(width, res);
}

void Intel386::do_bit_test(BitTestAction action)
{
    decode();
    int eff_w        = operand_32 ? D : W;
    int bit_off      = getReg(eff_w, reg);
    int shift        = bit_off & (operand_32 ? 31 : 15);
    int byte_offset  = (bit_off & (operand_32 ? ~0x1fLL : ~0x0fLL)) / 8;
    unsigned addr    = 0;
    Word off         = 0;
    bool use_seg_off = false;
    Dword base;
    if (mod == 0b11) {
        base = getRM(eff_w, mod, rm);
    } else {
        addr      = getEA(mod, rm);
        int bytes = (eff_w == D) ? 4 : 2;
        if (address_32) {
            // Real mode: fault if final BT-expanded offset is out of segment; then use 16-bit
            // offset.
            Dword adj_offset = last_ea_offset + byte_offset;
            if (static_cast<int32_t>(adj_offset) < 0 ||
                adj_offset > 0x10000u - static_cast<unsigned>(bytes))
                raise_segment_fault();
            Word seg_off = static_cast<Word>(adj_offset);
            addr         = linear_addr21(os, seg_off);
            base         = getMem(eff_w, addr);
        } else {
            // 8086-style address-size wrap: apply BT extension in 16-bit offset domain.
            // Truncate to Word first so large byte_offset wraps; then check segment limit.
            use_seg_off = true;
            off         = static_cast<Word>(addr - static_cast<unsigned>(os << 4) + byte_offset);
            if (off > 0x10000 - bytes)
                raise_segment_fault();
            base = getMemAtSegOff(eff_w, os, off);
        }
    }
    core.flags.f.cf     = (base >> shift) & 1;
    unpredictable_flags = OF_MASK | SF_MASK | AF_MASK | PF_MASK | ZF_MASK;

    int result;
    switch (action) {
    case BitTestAction::complement:
        result = base ^ (1 << shift);
        break;
    case BitTestAction::reset:
        result = base & ~(1 << shift);
        break;
    case BitTestAction::set:
        result = base | (1 << shift);
        break;
    default:
        return;
    }
    if (mod == 0b11)
        setReg(eff_w, rm, result);
    else if (use_seg_off)
        setMemAtSegOff(eff_w, os, off, result);
    else
        setMem(eff_w, addr, result);
}

// 0F BA /4-/7: BT/BTS/BTR/BTC r/m, imm8 (bit offset from immediate)
void Intel386::do_bit_test_imm()
{
    decode();
    int bit_off = fetch(B);
    BitTestAction action;
    switch (reg) {
    case 4:
        action = BitTestAction::test;
        break;
    case 5:
        action = BitTestAction::set;
        break;
    case 6:
        action = BitTestAction::reset;
        break;
    case 7:
        action = BitTestAction::complement;
        break;
    default:
        return;
    }
    int eff_w = operand_32 ? D : W;
    int shift = bit_off & (operand_32 ? 31 : 15);
    int base;
    unsigned addr = 0;
    if (mod == 0b11) {
        base = getRM(eff_w, mod, rm);
    } else {
        addr = getEA(mod, rm);
        // Real-mode segment limit: fault before any access. 32-bit uses signed offset;
        // 16-bit uses wrapped offset (8086-style) so [bx+si] etc. do not fault on wrap.
        int bytes = (eff_w == D) ? 4 : 2;
        if (last_ea_offset > 0x10000u - bytes)
            raise_segment_fault();
        base = getMem(eff_w, addr);
    }
    core.flags.f.cf     = (base >> shift) & 1;
    unpredictable_flags = OF_MASK | SF_MASK | AF_MASK | PF_MASK | ZF_MASK;

    int result;
    switch (action) {
    case BitTestAction::complement:
        result = base ^ (1 << shift);
        break;
    case BitTestAction::reset:
        result = base & ~(1 << shift);
        break;
    case BitTestAction::set:
        result = base | (1 << shift);
        break;
    default:
        return;
    }
    if (mod == 0b11)
        setReg(eff_w, rm, result);
    else
        setMem(eff_w, addr, result);
}

int Intel386::signconv(int width, int x)
{
    if (width == B)
        return static_cast<signed char>(x);
    else
        return static_cast<short>(x);
}

bool Intel386::msb(int width, int x)
{
    return (x & SIGN[width]) == SIGN[width];
}

//
// Intercept syscalls.
//
void Intel386::intercept_bios_call()
{
    if (machine.process_bios_call(core.cs, core.eip)) {
        core.eip = pop();
        core.cs  = pop();
        pop(); // get rid of extra flags
    }
}

//
// Is it a REP string instruction?
//
bool Intel386::is_rep_instruction() const
{
    if (!rep) {
        return false;
    }
    switch (op) {
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xaa:
    case 0xab:
    case 0xac:
    case 0xad:
    case 0xae:
    case 0xaf:
        return true;
    default:
        return false;
    }
}

//
// Execute one instruction. One call = one instruction (prefixes consumed, then one opcode
// executed). Increment IP register. Emit exception in case of failure.
//
// If the instruction has a segment override prefix, that
// segment is used unconditionally for the memory operand.
// If no segment override prefix is present, the CPU selects
// the segment solely based on which base register(s) are used in
// the effective address.
// Summary as an exact decision algorithm:
//
// For each memory operand:
//  * If a segment override prefix is present
//      → Use the overridden segment
//  * Else if the instruction is a string instruction
//      → Use the instruction-defined segment(s)
//  * Else if the effective address uses BP or SP
//      → Use SS
//  * Else
//      → Use DS
//
void Intel386::step()
{
    fault_eip = core.eip;

    try {
        // Consume segment override and REP prefix bytes; set default segment and repetition mode.
        os               = core.ds;
        os_is_ss         = false;
        segment_override = false;
        operand_32       = false;
        address_32       = false;
        lock_prefix      = false;
        rep              = 0;
        opcode           = {};
        plen             = 0;
        ea               = -1; // reset effective-address cache
        for (;;) {
            check_cs_fetch_limit(core.eip + 1);
            unsigned addr = linear_addr32(core.cs, core.eip);
            Byte prefix   = machine.mem_fetch_byte(addr);
            switch (prefix) {
            case 0x26: // ES:
                segment_override = true;
                os_is_ss         = false;
                os               = core.es;
                break;
            case 0x2e: // CS:
                segment_override = true;
                os_is_ss         = false;
                os               = core.cs;
                break;
            case 0x36: // SS:
                segment_override = true;
                os_is_ss         = true;
                os               = core.ss;
                break;
            case 0x3e: // DS:
                segment_override = true;
                os_is_ss         = false;
                os               = core.ds;
                break;
            case 0x64: // FS:
                segment_override = true;
                os_is_ss         = false;
                os               = core.fs;
                break;
            case 0x65: // GS:
                segment_override = true;
                os_is_ss         = false;
                os               = core.gs;
                break;
            case 0x66: // Operand-size override
                operand_32 = true;
                break;
            case 0x67: // Address-size override
                address_32 = true;
                break;
            case 0xf0: // LOCK
                lock_prefix = true;
                break;
            case 0xf2: // REPNE, REPNZ
                rep = 2;
                break;
            case 0xf3: // REP, REPE, REPZ
                rep = 1;
                break;
            default:
                goto done_prefix;
            }
            opcode.push_back(prefix);
            plen++;
            core.eip += 1;
        }
    done_prefix:

        // Demand-driven opcode bytes: fetch only what we need, with real-mode CS limit check.
        ensure_opcode_bytes(1);
        unpredictable_flags = 0;

        // Show instruction: address, opcode and mnemonics.
        machine.trace_instruction();

        op = opcode[plen];
        d  = (op >> 1) & 1;
        w  = op & 1;
        core.eip += 1;

        // 386 two-byte opcodes (0F xx)
        if (op == 0x0f) {
            ensure_opcode_bytes(2);
            op = 0x100 | opcode[++plen];
            core.eip += 1;
        }

        if (is_rep_instruction()) {
            exe_rep();
        } else {
            exe_one();
        }
        // Real mode: if EIP advanced past 64K CS limit, #GP before next fetch (except when halted).
        // Push current FLAGS as left by the instruction; do not overwrite with a generic image.
        if (!(core.cr0 & 1) && core.eip > 0xFFFF && !is_halted()) {
            call_int(13);
            throw SegmentFault{};
        }
        set_eflags(get_eflags() & ~unpredictable_flags);
        if (unpredictable_flags)
            last_unpredictable_flags = unpredictable_flags;
    } catch (SegmentFault &) {
        // Exception already handled (call_int done). Clear unpredictable flags for test comparison.
        set_eflags(get_eflags() & ~unpredictable_flags);
        if (unpredictable_flags)
            last_unpredictable_flags = unpredictable_flags;
    } catch (InstructionFault &) {
        // e.g. #UD for invalid LOCK; REP must not have decremented ECX.
        set_eflags(get_eflags() & ~unpredictable_flags);
        if (unpredictable_flags)
            last_unpredictable_flags = unpredictable_flags;
    }

    // Show changed registers.
    machine.trace_registers();
}

//
// Execute REP string instruction: full REP loop in one step.
//
void Intel386::exe_rep()
{
    // REPE/REPZ (rep==1) and REPNE/REPNZ (rep==2) only check ZF for CMPS/SCAS (A6,A7,AE,AF).
    // For MOVS/LODS/STOS, repeat until CX==0 regardless of ZF.
    bool check_zf = (op == 0xa6 || op == 0xa7 || op == 0xae || op == 0xaf); // CMPS/SCAS only

    for (;;) {
        if (operand_32) {
            // In 32-bit mode use full ECX register.
            if (core.ecx == 0)
                break;
        } else {
            // In 16-bit mode use only lower part of ECX register.
            if (get_cx() == 0)
                break;
        }

        exe_one();
        core.ecx -= 1;

        if (check_zf && core.flags.f.zf != (rep & 1)) {
            break;
        }
    }
}

//
// Decode op, d, w and optional ModR/M; then execute the matching 8086 instruction.
//
void Intel386::exe_one()
{
    // LOCK prefix is only valid with specific memory-destination instructions.
    // Raise #UD (int 6) for any other use.
    if (lock_prefix) {
        ensure_opcode_bytes(2);
        Byte modrm         = opcode[plen + 1];
        unsigned modrm_mod = (modrm >> 6) & 3;
        unsigned modrm_reg = (modrm >> 3) & 7;
        bool valid         = false;
        switch (op) {
        case 0x00:
        case 0x01: // ADD r/m, r
        case 0x08:
        case 0x09: // OR r/m, r
        case 0x10:
        case 0x11: // ADC r/m, r
        case 0x18:
        case 0x19: // SBB r/m, r
        case 0x20:
        case 0x21: // AND r/m, r
        case 0x28:
        case 0x29: // SUB r/m, r
        case 0x30:
        case 0x31: // XOR r/m, r
        case 0x86:
        case 0x87: // XCHG r/m, r
            valid = (modrm_mod != 0b11);
            break;
        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
            valid = (modrm_reg != 7) && (modrm_mod != 0b11);
            break;
        case 0xf6:
        case 0xf7:
            valid = (modrm_reg == 2 || modrm_reg == 3) && (modrm_mod != 0b11);
            break;
        case 0xfe:
        case 0xff:
            valid = (modrm_reg <= 1) && (modrm_mod != 0b11);
            break;
        case 0x1ab:
        case 0x1b3:
        case 0x1bb: // BTS/BTR/BTC r/m, r
            valid = (modrm_mod != 0b11);
            break;
        case 0x1ba: // BT group: BTS(/5), BTR(/6), BTC(/7) only
            valid = (modrm_reg >= 5) && (modrm_mod != 0b11);
            break;
        default:
            break;
        }
        if (!valid) {
            core.eip = fault_eip;
            call_int(6);
            throw InstructionFault{};
        }
    }

    int dst, src, res;
    const int AX = 0; // accumulator index for getReg/setReg

    switch (op) {
    // --- MOV: register/memory and immediate, accum, segment ---
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            src = getReg(eff_w, reg);
            setRM(eff_w, mod, rm, src);
        } else {
            src = getRM(eff_w, mod, rm);
            setReg(eff_w, reg, src);
        }
        break;
    }

    // MOV reg/mem, immediate. 386: only ModR/M reg field 0 is MOV; other encodings are #UD.
    case 0xc6:
    case 0xc7: {
        decode();
        if (reg != 0) {
            core.eip = fault_eip;
            call_int(6);
            break;
        }
        int eff_w = (op == 0xc7 && operand_32) ? D : (op == 0xc7 ? W : B);
        if (mod == 0b11) {
            src = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
            setReg(eff_w, rm, src);
        } else {
            unsigned addr  = getEA(mod, rm);
            unsigned bytes = (eff_w == D) ? 4 : (eff_w == W) ? 2 : 1;
            if (last_ea_offset > 0x10000 - bytes) {
                // Intel: #GP when memory operand EA outside segment limit (0x10000 in real mode).
                os_is_ss = false;
                raise_segment_fault();
            }
            src = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
            setMem(eff_w, addr, src);
        }
        break;
    }

    // MOV reg, immediate (B0-BF)
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb4:
    case 0xb5:
    case 0xb6:
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf: {
        w         = (op >> 3) & 1;
        reg       = op & 0b111;
        int eff_w = (operand_32 && w) ? D : (w ? W : B);
        src       = fetch(eff_w);
        setReg(eff_w, reg, src);
        break;
    }

    // MOV accum, mem and MOV mem, accum
    case 0xa0:
    case 0xa1:
    case 0xa2:
    case 0xa3: {
        unsigned addr;
        if (address_32) {
            Dword disp32 = fetch(W) | (static_cast<Dword>(fetch(W)) << 16);
            addr         = linear_addr32(os, disp32);
        } else {
            addr = linear_addr21(os, static_cast<Word>(fetch(W)));
        }
        int eff_w = ((op == 0xa1 || op == 0xa3) && operand_32) ? D : (w ? W : B);
        if (d == 0) {
            src = getMem(eff_w, addr);
            setReg(eff_w, AX, src);
        } else {
            src = getReg(eff_w, AX);
            setMem(eff_w, addr, src);
        }
        break;
    }

    // MOV reg/mem, segreg and MOV segreg, reg/mem
    case 0x8c:
    case 0x8e:
        decode();
        if (d == 0) {
            // MOV r/m, segreg: when reg dest with operand_32, zero-extend segment to 32 bits
            int eff_w = (mod == 0b11 && operand_32) ? D : W;
            setRM(eff_w, mod, rm, getSegReg(reg));
        } else {
            // 8E: MOV Sreg, r/m16 — CS (reg==1) and encodings 6/7 are invalid; raise #UD
            if (op == 0x8e && (reg == 1 || reg > 5)) {
                core.eip = fault_eip;
                call_int(6);
                break;
            }
            setSegReg(reg, getRM(W, mod, rm));
        }
        break;

    // --- PUSH/POP: general and segment registers ---
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
        reg = op & 0b111;
        if (operand_32) {
            // PUSH r32: 386 PUSH ESP pushes the value before the push (current ESP)
            src = getReg(D, reg);
            push32(static_cast<Dword>(src));
        } else {
            // 386 PUSH SP pushes the value before the push (current SP); 8086 had SP-2 quirk
            src = getReg(W, reg);
            push(src);
        }
        break;

    // PUSH segment register
    case 0x06:
    case 0x0e:
    case 0x16:
    case 0x1e: {
        reg      = (op >> 3) & 0b111;
        Word seg = getSegReg(reg);
        if (operand_32)
            push32(static_cast<Dword>(seg));
        else
            push(seg);
        break;
    }

    // POP general register
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
        reg = op & 0b111;
        if (operand_32) {
            // 386: 4-byte pop crossing 64K segment boundary triggers #SS (per batch4).
            if (get_sp() > 0x10000 - 4) {
                os_is_ss = true;
                raise_segment_fault();
            }
            setReg(D, reg, pop32());
        } else {
            setReg(W, reg, pop());
        }
        break;

    // POP segment register
    case 0x07:
    case 0x0f:
    case 0x17:
    case 0x1f:
        reg = (op >> 3) & 0b111;
        setSegReg(reg, operand_32 ? (pop32() & 0xFFFF) : pop());
        break;

    // XCHG reg, reg/mem
    case 0x86:
    case 0x87: {
        decode();
        int eff_w = (operand_32 && w) ? D : (w ? W : B);
        dst       = getReg(eff_w, reg);
        if (mod == 0b11) {
            src = getRM(eff_w, mod, rm);
            setReg(eff_w, reg, src);
            setRM(eff_w, mod, rm, dst);
        } else {
            unsigned addr  = getEA(mod, rm);
            unsigned bytes = (eff_w == D) ? 4 : (eff_w == W) ? 2 : 1;
            if (last_ea_offset > 0x10000 - bytes)
                raise_segment_fault();
            src = getMem(eff_w, addr);
            setReg(eff_w, reg, src);
            setMem(eff_w, addr, dst);
        }
        break;
    }

    // XCHG AX, reg (16-bit or 32-bit per operand_32)
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97: {
        reg       = op & 0b111;
        int eff_w = operand_32 ? D : W;
        dst       = getReg(eff_w, 0); // AX/EAX
        src       = getReg(eff_w, reg);
        setReg(eff_w, 0, src);
        setReg(eff_w, reg, dst);
        break;
    }

    // SALC: Set AL from Carry (undocumented 8086)
    case 0xd6:
        set_al(core.flags.f.cf ? 0xff : 0);
        break;

    // XLAT
    case 0xd7: {
        Dword base = address_32 ? core.ebx : static_cast<Dword>(core.ebx & 0xFFFF);
        set_al(getMem(B, linear_addr32(os, base + get_al())));
        break;
    }

    // IN accum, port (immed and DX)
    case 0xe4:
    case 0xe5: {
        src       = fetch(B);
        int eff_w = (op == 0xe5 && operand_32) ? D : (w ? W : B);
        if (eff_w == B)
            res = machine.port_in_byte(src);
        else if (eff_w == D)
            res = static_cast<int>(machine.port_in_32(src));
        else
            res = machine.port_in_word(src);
        setReg(eff_w, AX, res);
        break;
    }
    case 0xec:
    case 0xed: {
        src       = core.edx & 0xFFFF;
        int eff_w = (op == 0xed && operand_32) ? D : (w ? W : B);
        if (eff_w == B)
            res = machine.port_in_byte(src);
        else if (eff_w == D)
            res = static_cast<int>(machine.port_in_32(src));
        else
            res = machine.port_in_word(src);
        setReg(eff_w, AX, res);
        break;
    }

    // OUT port, accum
    case 0xe6:
    case 0xe7:
        src = fetch(B);
        res = getReg(w, AX);
        if (w == B)
            machine.port_out_byte(src, res);
        else
            machine.port_out_word(src, res);
        break;
    case 0xee:
    case 0xef:
        src = core.edx;
        res = getReg(w, AX);
        if (w == B)
            machine.port_out_byte(src, res);
        else
            machine.port_out_word(src, res);
        break;

    // LEA
    case 0x8d: {
        decode();
        if (mod == 0b11) {
            core.eip = fault_eip;
            call_int(6); // #UD
            break;
        }
        Dword offset;
        if (address_32) {
            // Reuse getEA so mod=0 rm=5 [disp32] and SIB are identical to memory operands.
            (void)getEA(mod, rm);
            offset = last_ea_offset;
        } else {
            unsigned linear = getEA(mod, rm);
            offset          = linear - (static_cast<Dword>(os) << 4);
        }
        int eff_w = operand_32 ? D : W;
        setReg(eff_w, reg,
               eff_w == D ? static_cast<int>(offset) : static_cast<int>(offset & 0xFFFF));
        break;
    }

    // LDS (loads offset into reg, segment into DS). 16-bit: 4 bytes; 32-bit: 6 bytes.
    case 0xc5: {
        decode();
        unsigned addr = getEA(mod, rm);
        int far_size  = operand_32 ? 6 : 4;
        if (last_ea_offset > 0x10000u - far_size)
            raise_segment_fault();
        if (operand_32) {
            int off32 = getMem(D, addr);
            Word seg  = getMem(W, addr + 4);
            setReg(D, reg, off32);
            core.ds = seg;
        } else {
            int off16 = getMem(W, addr);
            Word seg  = getMem(W, addr + 2);
            setReg(W, reg, off16);
            core.ds = seg;
        }
        break;
    }

    // LES. 16-bit: 4 bytes (offset+seg); 32-bit with 66h: 6 bytes (offset+seg).
    case 0xc4: {
        decode();
        unsigned addr = getEA(mod, rm);
        int far_size  = operand_32 ? 6 : 4;
        if (last_ea_offset > 0x10000u - far_size)
            raise_segment_fault();
        if (operand_32) {
            int off32 = getMem(D, addr);
            Word seg  = getMem(W, addr + 4);
            setReg(D, reg, off32);
            core.es = seg;
        } else {
            unsigned off = addr - (os << 4);
            setReg(W, reg, getMemAtSegOff(W, os, off));
            core.es = getMemAtSegOff(W, os, off + 2);
        }
        break;
    }

    // LSS (0F B2), LFS (0F B4), LGS (0F B5): load far pointer into segment + reg.
    // 386: only memory operand (mod != 11); register form is #UD.
    case 0x1b2:
    case 0x1b4:
    case 0x1b5: {
        decode();
        if (mod == 0b11) {
            core.eip = fault_eip;
            call_int(6);
            break;
        }
        unsigned addr = getEA(mod, rm);
        int far_size  = operand_32 ? 6 : 4;
        if (last_ea_offset > 0x10000u - far_size)
            raise_segment_fault();
        Word seg;
        if (operand_32) {
            int off32 = getMem(D, addr);
            seg       = getMem(W, addr + 4);
            setReg(D, reg, off32);
        } else {
            int off16 = getMem(W, addr);
            seg       = getMem(W, addr + 2);
            setReg(W, reg, off16);
        }
        if (op == 0x1b2)
            core.ss = seg;
        else if (op == 0x1b4)
            core.fs = seg;
        else
            core.gs = seg;
        break;
    }

    // LAHF
    case 0x9f:
        set_ah(core.flags.w);
        break;

    // SAHF
    case 0x9e:
        set_flags((core.flags.w & 0xff00) | get_ah());
        break;

    // PUSHF / PUSHFD
    case 0x9c:
        if (operand_32)
            push32(core.flags.w & 0xFFFF); // PUSHFD: 386 stores upper 16 bits as 0
        else
            push(core.flags.w);
        break;
    case 0x9d:
        if (operand_32) {
            Word sp = get_sp();
            if (sp > 0x10000 - 4) {
                os_is_ss = true;
                raise_segment_fault();
            }
            set_eflags(static_cast<Dword>(pop32()));
        } else
            set_flags(pop());
        break;

    // ADD reg/mem, reg and ADD reg, reg/mem
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
            res = add(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
            res = add(eff_w, dst, src);
            setReg(eff_w, reg, res);
        }
        break;
    }

    // ADD accum, immediate
    case 0x04:
    case 0x05: {
        int eff_w = (op == 0x05 && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        setReg(eff_w, AX, add(eff_w, dst, src));
        break;
    }

    // ADC (same pattern)
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
            res = adc(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
            res = adc(eff_w, dst, src);
            setReg(eff_w, reg, res);
        }
        break;
    }
    case 0x14:
    case 0x15: {
        int eff_w = (op == 0x15 && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        setReg(eff_w, AX, adc(eff_w, dst, src));
        break;
    }

    // INC general register
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47: {
        reg    = op & 0b111;
        int sz = operand_32 ? D : W;
        setReg(sz, reg, inc(sz, getReg(sz, reg)));
        break;
    }

    // AAA: ASCII adjust for addition (real 386: 16-bit AX adjust, then clear AL high nibble)
    case 0x37: {
        // OF, SF, ZF, PF undefined per Intel; mask for test comparison
        unpredictable_flags = OF_MASK | SF_MASK | ZF_MASK | PF_MASK;

        Word ax = get_ax();
        if (core.flags.f.af || (get_al() & 0xf) > 9) {
            ax += 0x106; // 6 in low byte, 1 in high (carry into AH)
            core.flags.f.cf = 1;
            core.flags.f.af = 1;
        } else {
            core.flags.f.cf = 0;
            core.flags.f.af = 0;
        }
        ax &= 0xff0f; // AL high nibble cleared per Intel
        set_ax(ax);
        Byte al         = get_al();
        core.flags.f.zf = (al == 0);
        core.flags.f.pf = PARITY[al];
        break;
    }

    // DAA: Decimal adjust for addition
    case 0x27: {
        // Overflow is unpredictable
        unpredictable_flags = OF_MASK;

        // First adjustment (low nibble).
        Byte al = get_al();
        if (core.flags.f.af || (al & 0x0f) > 9) {
            al += 6;
            if (!core.flags.f.af && (al >> 4) > 9) {
                core.flags.f.cf = 1;
            }
            core.flags.f.af = 1;
        }
        // Second adjustment (high nibble).
        // Note: decision uses original AL but new CF.
        if (core.flags.f.cf || (get_al() >> 4) > 9) {
            al += 0x60;
            core.flags.f.cf = 1;
        }
        set_al(al);
        update_flags_zsp(B, get_al());
        break;
    }

    // --- SUB, SBB, CMP, INC, DEC: arithmetic and compare ---
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
            res = sub(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
            res = sub(eff_w, dst, src);
            setReg(eff_w, reg, res);
        }
        break;
    }
    case 0x2c:
    case 0x2d: {
        int eff_w = (op == 0x2d && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        setReg(eff_w, AX, sub(eff_w, dst, src));
        break;
    }

    // SBB
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
            res = sbb(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
            res = sbb(eff_w, dst, src);
            setReg(eff_w, reg, res);
        }
        break;
    }
    case 0x1c:
    case 0x1d: {
        int eff_w = (op == 0x1d && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        setReg(eff_w, AX, sbb(eff_w, dst, src));
        break;
    }

    // DEC general register
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f: {
        reg    = op & 0b111;
        int sz = operand_32 ? D : W;
        setReg(sz, reg, dec(sz, getReg(sz, reg)));
        break;
    }

    // CMP
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
        }
        sub(eff_w, dst, src);
        break;
    }
    case 0x3c:
    case 0x3d: {
        int eff_w = (op == 0x3d && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        sub(eff_w, dst, src);
        break;
    }

    // AAS: ASCII adjust for subtraction
    case 0x3f: {
        // Overflow, parity, sign and zero are unpredictable
        unpredictable_flags = OF_MASK | PF_MASK | SF_MASK | ZF_MASK;

        Word ax = get_ax();
        if (core.flags.f.af || (ax & 0xf) > 9) {
            ax -= 0x106;
            core.flags.f.cf = 1;
            core.flags.f.af = 1;
        } else {
            core.flags.f.cf = 0;
            core.flags.f.af = 0;
        }
        set_ax(ax & 0xff0f);
        core.flags.f.zf = (get_al() == 0);
        break;
    }

    // DAS: Decimal adjust for subtraction (Intel: CF = old_CF or borrow from first/subtract; second
    // uses old_AL/old_CF)
    case 0x2f: {
        unpredictable_flags = OF_MASK;
        Byte old_al         = get_al();
        bool old_cf         = core.flags.f.cf;
        core.flags.f.cf     = 0;
        Byte al             = old_al;
        if (core.flags.f.af || (al & 0x0f) > 9) {
            al -= 6;
            core.flags.f.cf = old_cf || (old_al < 6); // borrow from AL - 6
            core.flags.f.af = 1;
        } else {
            core.flags.f.af = 0;
        }
        if (old_al > 0x99 || old_cf) {
            al -= 0x60;
            core.flags.f.cf = 1;
        }
        set_al(al);
        update_flags_zsp(B, get_al());
        break;
    }

    // AAM: ASCII adjust for multiply
    case 0xd4:
        // Overflow is unpredictable
        unpredictable_flags = OF_MASK;

        src             = fetch(B);
        core.flags.f.cf = 0;
        core.flags.f.af = 0;
        if (src == 0) {
            update_flags_zsp(B, 0);
            call_int(0);
        } else {
            set_ah(get_al() / src);
            set_al(get_al() % src);
            update_flags_zsp(B, get_al());
        }
        break;

    // AAD: ASCII adjust for division
    case 0xd5: {
        // Overflow is unpredictable
        unpredictable_flags = OF_MASK;

        src          = fetch(B);
        int ah_orig  = get_ah();
        int al_orig  = get_al();
        int sum      = al_orig + (Byte)(ah_orig * src);
        int half_sum = (al_orig & 0x0F) + ((ah_orig * src) & 0x0F);
        set_al(sum);
        set_ah(0);
        update_flags_zsp(B, get_al());
        core.flags.f.cf = (sum >= 256);
        core.flags.f.af = (half_sum > 15);
        core.flags.f.tf = 0;
        break;
    }

    // CBW/CWDE (98): CBW sign-extends AL to AX; CWDE (with 66h) sign-extends AX to EAX
    case 0x98:
        if (operand_32) {
            // CWDE: sign-extend AX to EAX
            core.eax =
                static_cast<Dword>(static_cast<int32_t>(static_cast<int16_t>(core.eax & 0xFFFF)));
        } else {
            // CBW: sign-extend AL to AX, preserve upper 16 bits of EAX
            Word ax = (get_al() & 0x80) ? (get_al() | 0xff00) : static_cast<Word>(get_al());
            set_ax(ax);
        }
        break;

    // CWD / CDQ
    case 0x99:
        if (operand_32) {
            // CDQ: Convert Doubleword to Quadword
            if (core.eax & 0x80000000u)
                core.edx = 0xffffffffu;
            else
                core.edx = 0;
        } else {
            // CWD: Convert Word to Doubleword
            Word dx = (core.eax & 0x8000) ? 0xffff : 0;
            set_dx(dx);
        }
        break;

    // AND, OR, XOR, TEST (logic)
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
            res = dst & src;
            logic(eff_w, res);
            setRM(eff_w, mod, rm, res);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
            res = dst & src;
            logic(eff_w, res);
            setReg(eff_w, reg, res);
        }
        break;
    }
    case 0x24:
    case 0x25: {
        int eff_w = (op == 0x25 && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        res       = dst & src;
        logic(eff_w, res);
        setReg(eff_w, AX, res);
        break;
    }
    case 0x08:
    case 0x09:
    case 0x0a:
    case 0x0b: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
            res = dst | src;
            logic(eff_w, res);
            setRM(eff_w, mod, rm, res);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
            res = dst | src;
            logic(eff_w, res);
            setReg(eff_w, reg, res);
        }
        break;
    }
    case 0x0c:
    case 0x0d: {
        int eff_w = (op == 0x0d && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        res       = dst | src;
        logic(eff_w, res);
        setReg(eff_w, AX, res);
        break;
    }
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33: {
        decode();
        int eff_w = operand_32 ? D : (w ? W : B);
        if (d == 0) {
            dst = getRM(eff_w, mod, rm);
            src = getReg(eff_w, reg);
            res = dst ^ src;
            logic(eff_w, res);
            setRM(eff_w, mod, rm, res);
        } else {
            dst = getReg(eff_w, reg);
            src = getRM(eff_w, mod, rm);
            res = dst ^ src;
            logic(eff_w, res);
            setReg(eff_w, reg, res);
        }
        break;
    }
    case 0x34:
    case 0x35: {
        int eff_w = (op == 0x35 && operand_32) ? D : (w ? W : B);
        dst       = getReg(eff_w, AX);
        src       = eff_w == D ? fetch(D) : (eff_w == W ? fetch(W) : fetch(B));
        logic(eff_w, dst ^ src);
        setReg(eff_w, AX, dst ^ src);
        break;
    }
    case 0x84:
    case 0x85: {
        decode();
        int eff_w = (operand_32 && w) ? D : (w ? W : B);
        logic(eff_w, getRM(eff_w, mod, rm) & getReg(eff_w, reg));
        break;
    }
    case 0xa8:
    case 0xa9:
        logic(w, getReg(w, AX) & fetch(w));
        break;

    // String ops (one iteration each)
    case 0xa4: // MOVS
    case 0xa5: {
        int eff_w  = (w && operand_32) ? D : (w ? W : B);
        int delta  = (eff_w == B) ? 1 : (eff_w == W ? 2 : 4);
        int stride = (core.flags.f.df ? -1 : 1) * delta;
        if (address_32) {
            // Real-mode segment limit: fault before any access or register update
            Word si_off = static_cast<Word>(core.esi), di_off = static_cast<Word>(core.edi);
            if (si_off > 0x10000 - delta) {
                os_is_ss = (os == core.ss);
                raise_segment_fault();
            }
            if (di_off > 0x10000 - delta) {
                os_is_ss = (core.es == core.ss);
                raise_segment_fault();
            }
            src = getMem(eff_w, linear_addr32(os, core.esi));
            setMem(eff_w, linear_addr32(core.es, core.edi), src);
            core.esi += stride;
            core.edi += stride;
        } else {
            Word si_off = static_cast<Word>(core.esi), di_off = static_cast<Word>(core.edi);
            if (si_off > 0x10000 - delta) {
                os_is_ss = (os == core.ss);
                raise_segment_fault();
            }
            if (di_off > 0x10000 - delta) {
                os_is_ss = (core.es == core.ss);
                raise_segment_fault();
            }
            src = getMemAtSegOff(eff_w, os, si_off);
            setMemAtSegOff(eff_w, core.es, di_off, src);
            set_si(get_si() + stride);
            set_di(get_di() + stride);
        }
        break;
    }
    case 0xa6:
    case 0xa7: {
        // CMPS: temp = SRC1 - SRC2, SRC1=[DS:SI/override], SRC2=[ES:DI]
        int eff_w  = (w && operand_32) ? D : (w ? W : B);
        int delta  = (eff_w == B) ? 1 : (eff_w == W ? 2 : 4);
        int stride = (core.flags.f.df ? -1 : 1) * delta;
        int src1, src2;
        if (address_32) {
            Word si_off = static_cast<Word>(core.esi), di_off = static_cast<Word>(core.edi);
            if (si_off > 0x10000 - delta) {
                os_is_ss = (os == core.ss);
                raise_segment_fault();
            }
            if (di_off > 0x10000 - delta) {
                os_is_ss = (core.es == core.ss);
                raise_segment_fault();
            }
            src1 = getMem(eff_w, linear_addr32(os, core.esi));
            src2 = getMem(eff_w, linear_addr32(core.es, core.edi));
        } else {
            Word si_off = static_cast<Word>(core.esi), di_off = static_cast<Word>(core.edi);
            if (si_off > 0x10000 - delta || di_off > 0x10000 - delta)
                raise_segment_fault();
            src1 = getMemAtSegOff(eff_w, os, si_off);
            src2 = getMemAtSegOff(eff_w, core.es, di_off);
        }
        sub(eff_w, src1, src2);
        if (address_32) {
            core.esi += stride;
            core.edi += stride;
        } else {
            set_si(get_si() + stride);
            set_di(get_di() + stride);
        }
        break;
    }
    case 0xae:
    case 0xaf: {
        int eff_w  = (w && operand_32) ? D : (w ? W : B);
        int delta  = (eff_w == B) ? 1 : (eff_w == W ? 2 : 4);
        int stride = (core.flags.f.df ? -1 : 1) * delta;
        if (address_32) {
            Word di_off = static_cast<Word>(core.edi);
            if (di_off > 0x10000 - delta) {
                os_is_ss = (core.es == core.ss);
                raise_segment_fault();
            }
        } else {
            Word di_off = static_cast<Word>(core.edi);
            if (di_off > 0x10000 - delta) {
                os_is_ss = (core.es == core.ss);
                raise_segment_fault();
            }
        }
        dst = address_32 ? getMem(eff_w, linear_addr32(core.es, core.edi))
                         : getMemAtSegOff(eff_w, core.es, static_cast<Word>(core.edi));
        src = getReg(eff_w, AX);
        sub(eff_w, src, dst);
        if (address_32)
            core.edi += stride;
        else
            set_di(get_di() + stride);
        break;
    }
    case 0xac:
    case 0xad: {
        int eff_w = (w && operand_32) ? D : (w ? W : B);
        int delta = (eff_w == B) ? 1 : (eff_w == W ? 2 : 4);
        if (address_32) {
            if (static_cast<Word>(core.esi) > 0x10000 - delta) {
                os_is_ss = (os == core.ss);
                raise_segment_fault();
            }
            src = getMem(eff_w, linear_addr32(os, core.esi));
            core.esi += (core.flags.f.df ? -1 : 1) * delta;
        } else {
            Word si_off = static_cast<Word>(core.esi);
            if (si_off > 0x10000 - delta)
                raise_segment_fault();
            src      = getMemAtSegOff(eff_w, os, si_off);
            Word si  = static_cast<Word>(core.esi + (core.flags.f.df ? -1 : 1) * delta);
            core.esi = (core.esi & 0xFFFF0000u) | si;
        }
        setReg(eff_w, AX, src);
        break;
    }
    case 0xaa:
    case 0xab: {
        int eff_w  = (w && operand_32) ? D : (w ? W : B);
        int delta  = (eff_w == B) ? 1 : (eff_w == W ? 2 : 4);
        int stride = (core.flags.f.df ? -1 : 1) * delta;
        if (address_32) {
            Word di_off = static_cast<Word>(core.edi);
            if (di_off > 0x10000 - delta) {
                os_is_ss = (core.es == core.ss);
                raise_segment_fault();
            }
            setMem(eff_w, linear_addr32(core.es, core.edi), getReg(eff_w, AX));
            core.edi += stride;
        } else {
            Word di_off = static_cast<Word>(core.edi);
            if (di_off > 0x10000 - delta) {
                os_is_ss = (core.es == core.ss);
                raise_segment_fault();
            }
            setMemAtSegOff(eff_w, core.es, di_off, getReg(eff_w, AX));
            set_di(get_di() + stride);
        }
        break;
    }

    // --- CALL, RET, JMP: transfer and conditional jumps ---
    case 0xe8:
        if (operand_32) {
            dst = static_cast<int>(static_cast<int32_t>(fetch(D)));
            push32(core.eip); // return addr = byte after rel32
        } else {
            dst = signconv(W, fetch(W));
            push(core.eip); // return addr = byte after rel16
        }
        core.eip += dst;
        if (!operand_32)
            core.eip &= 0xFFFFu;
        break;
    case 0x9a: {
        if (operand_32) {
            dst = fetch(D);   // 32-bit offset
            src = fetch(W);   // segment is always 16-bit
            push32(core.cs);  // push CS as dword (zero-extended)
            push32(core.eip); // push 32-bit return address
        } else {
            dst = fetch(W);
            src = fetch(W);
            push(core.cs);
            push(core.eip);
        }
        core.eip = dst;
        core.cs  = src;
        intercept_bios_call();
        break;
    }
    case 0xc2: {
        src = fetch(W);
        if (operand_32) {
            Dword ret_eip = static_cast<Dword>(pop32());
            if (ret_eip > 0xFFFF) {
                set_sp(get_sp() - 4); // undo the pop
                os_is_ss = false;
                raise_segment_fault();
            }
            core.eip = ret_eip;
        } else {
            core.eip = pop();
        }
        // 16-bit stack: add imm16 to SP with wrap
        set_sp(static_cast<Word>((get_sp() + src) & 0xFFFF));
        break;
    }
    case 0xc3: {
        if (operand_32) {
            Dword ret_eip = pop32();
            if (ret_eip > 0xFFFF) {
                set_sp(get_sp() - 4); // undo the pop
                os_is_ss = false;
                raise_segment_fault();
            }
            core.eip = ret_eip;
        } else {
            core.eip = pop();
        }
        break;
    }
    case 0xc9: { // LEAVE (386): mov esp,ebp; pop ebp
        if (operand_32) {
            // 32-bit leave with 16-bit stack (real mode): use only low 16 bits of EBP for SP
            set_sp(get_bp());
            core.ebp = pop32();
            // Real mode: stack pointer is 16-bit; zero high bits of ESP
            core.esp &= 0xFFFFu;
        } else {
            set_sp(get_bp());
            set_bp(static_cast<Word>(pop()));
        }
        break;
    }
    case 0xcb: { // RETF/RETFD: far return, pop offset then CS
        if (operand_32) {
            Word sp = get_sp();
            if (sp > 0x10000 - 8) {
                os_is_ss = true;
                raise_segment_fault();
            }
            Dword new_eip = static_cast<Dword>(getMem(D, linear_addr21(core.ss, sp)));
            if (new_eip > 0xFFFF) {
                os_is_ss = false;
                core.eip = fault_eip;
                call_int(13);
            } else {
                core.eip = new_eip;
                core.cs  = getMem(W, linear_addr21(core.ss, sp) + 4);
                set_sp(get_sp() + 8);
                intercept_bios_call();
            }
        } else {
            // 16-bit stack: fault #SS when first word pop would cross segment (SP > 0xFFFE)
            Word sp = get_sp();
            if (sp > 0xFFFE) {
                os_is_ss = true;
                raise_segment_fault();
            }
            core.eip = pop();
            core.cs  = pop();
            intercept_bios_call();
        }
        break;
    }
    case 0xc8: { // ENTER (186+): make stack frame
        int alloc = fetch(W);
        int level = fetch(B) & 0x1F;
        int sz    = operand_32 ? 4 : 2;
        if (operand_32) {
            push32(core.ebp);
        } else {
            push(static_cast<int>(core.ebp & 0xFFFF));
        }
        Dword frame_temp = core.esp;
        for (int i = 1; i < level; ++i) {
            Dword ptr     = (operand_32 ? core.ebp : (core.ebp & 0xFFFF)) - sz * i;
            unsigned addr = linear_addr21(core.ss, static_cast<Word>(ptr & 0xFFFF));
            if (operand_32) {
                push32(static_cast<Dword>(getMem(D, addr)));
            } else {
                push(getMem(W, addr));
            }
        }
        if (level > 0) {
            if (operand_32) {
                push32(frame_temp);
            } else {
                push(static_cast<int>(frame_temp & 0xFFFF));
            }
        }
        if (operand_32) {
            core.ebp = frame_temp;
            core.esp -= alloc;
            core.esp &= 0xFFFFu; // real mode: stack pointer is 16-bit
        } else {
            set_bp(static_cast<Word>(frame_temp & 0xFFFF));
            set_sp(static_cast<Word>((core.esp - alloc) & 0xFFFF));
        }
        break;
    }
    case 0xca: { // RETF imm16 / RETFD imm16: pop offset, pop CS, add imm to SP (16-bit wrap)
        src = fetch(W);
        if (operand_32) {
            Word sp = get_sp();
            if (sp > 0x10000 - 8) {
                os_is_ss = true;
                raise_segment_fault();
            }
            unsigned addr = linear_addr21(core.ss, sp);
            Dword new_eip = static_cast<Dword>(getMem(D, addr));
            if (new_eip > 0xFFFF) {
                os_is_ss = false;
                core.eip = fault_eip;
                call_int(13);
            } else {
                core.eip = new_eip;
                core.cs  = getMem(W, addr + 4);
                set_sp(get_sp() + 8);
                set_sp(static_cast<Word>((get_sp() + src) & 0xFFFF));
                intercept_bios_call();
            }
        } else {
            // 16-bit stack: fault #SS only when first word crosses segment (SP==0xFFFF); second
            // word may wrap.
            Word sp = get_sp();
            if (sp > 0xFFFE) {
                os_is_ss = true;
                raise_segment_fault();
            }
            core.eip = pop();
            core.cs  = pop();
            set_sp(static_cast<Word>((get_sp() + src) & 0xFFFF));
            intercept_bios_call();
        }
        break;
    }
    case 0xe9:
        dst = operand_32 ? static_cast<int>(static_cast<int32_t>(fetch(D))) : signconv(W, fetch(W));
        core.eip += dst;
        if (!operand_32)
            core.eip &= 0xFFFFu;
        break;
    case 0xeb:
        dst = signconv(B, fetch(B));
        core.eip += dst;
        break;
    case 0xea: // JMP far
        dst      = operand_32 ? fetch(D) : fetch(W);
        src      = fetch(W);
        core.eip = dst;
        core.cs  = src;
        intercept_bios_call();
        break;

    //
    // PUSHA/PUSHAD - Push all general-purpose registers
    //
    case 0x60: {
        if (operand_32) {
            Dword esp_save = core.esp & 0xFFFF;
            push32(core.eax);
            push32(core.ecx);
            push32(core.edx);
            push32(core.ebx);
            push32(esp_save);
            push32(core.ebp);
            push32(core.esi);
            push32(core.edi);
        } else {
            Word sp_save = get_sp();
            push(get_ax());
            push(get_cx());
            push(get_dx());
            push(get_bx());
            push(sp_save);
            push(get_bp());
            push(get_si());
            push(get_di());
        }
        break;
    }

    //
    // Conditional jumps (Jcc)
    //
    case 0x70: // JO - Overflow
        dst = signconv(B, fetch(B));
        if (core.flags.f.of)
            core.eip += dst;
        break;

    case 0x61: { // POPA/POPAD
        if (operand_32) {
            // 16-bit stack: real 386 faults #SS if 32-byte frame would wrap (before any pops).
            if (!address_32 && get_sp() > 0x10000 - 32) {
                os_is_ss = true;
                raise_segment_fault();
            }
            core.edi     = pop32();
            core.esi     = pop32();
            core.ebp     = pop32();
            auto new_esp = pop32(); // skip ESP slot
            core.ebx     = pop32();
            core.edx     = pop32();
            core.ecx     = pop32();
            core.eax     = pop32();
            if (!address_32) {
                // Update upper bits of ESP.
                set_esp((new_esp & 0xffff0000) | get_sp());
            }
        } else {
            set_di(pop());
            set_si(pop());
            set_bp(pop());
            set_sp(get_sp() + 2); // skip SP slot
            set_bx(pop());
            set_dx(pop());
            set_cx(pop());
            set_ax(pop());
        }
        break;
    }
    case 0x71: // JNO - No overflow
        dst = signconv(B, fetch(B));
        if (!core.flags.f.of)
            core.eip += dst;
        break;

    case 0x62: { // BOUND (386): check array index against bounds, INT 5 if out of range (signed
                 // comparison). Real 386: mod=11 (invalid reg,reg form) also faults via INT 5.
        Dword bound_eip = core.eip; // save for fault address
        decode();
        if (mod == 0b11) {
            // Real 386: BOUND with register as second operand triggers INT 6 (#UD), not INT 5.
            core.eip = bound_eip - 1 - static_cast<Dword>(plen);
            call_int(6);
            break;
        }
        unsigned addr        = getEA(mod, rm);
        unsigned bound_bytes = operand_32 ? 8u : 4u;
        if (last_ea_offset > 0x10000u - bound_bytes) {
            core.eip = bound_eip - 1 - plen;
            call_int(os_is_ss ? 12 : 13); // #SS for SS, #GP for others
            break;
        }
        int index, lower, upper;
        if (operand_32) {
            index = static_cast<int32_t>(getReg(D, reg));
            lower = static_cast<int32_t>(getMem(D, addr));
            upper = static_cast<int32_t>(getMem(D, addr + 4));
        } else {
            index = signconv(W, getReg(W, reg));
            lower = signconv(W, getMem(W, addr));
            upper = signconv(W, getMem(W, addr + 2));
        }
        if (index < lower || index > upper) {
            core.eip = bound_eip - 1 - static_cast<Dword>(plen); // fault at start of instruction
            call_int(5);
        }
        break;
    }
    case 0x72: // JB, JC, JNAE - Below / Carry
        dst = signconv(B, fetch(B));
        if (core.flags.f.cf)
            core.eip += dst;
        break;

    case 0x63: // Undocumented
        [[fallthrough]];
    case 0x73: // JNB, JNC, JAE - Above or equal / No carry
        dst = signconv(B, fetch(B));
        if (!core.flags.f.cf)
            core.eip += dst;
        break;

    case 0x64: // Undocumented
        [[fallthrough]];
    case 0x74: // JE, JZ - Equal / Zero
        dst = signconv(B, fetch(B));
        if (core.flags.f.zf)
            core.eip += dst;
        break;

    case 0x65: // Undocumented
        [[fallthrough]];
    case 0x75: // JNE, JNZ - Not equal / Not zero
        dst = signconv(B, fetch(B));
        if (!core.flags.f.zf)
            core.eip += dst;
        break;

    case 0x66: // Undocumented
        [[fallthrough]];
    case 0x76: // JBE, JNA - Below or equal
        dst = signconv(B, fetch(B));
        if (core.flags.f.cf || core.flags.f.zf)
            core.eip += dst;
        break;

    case 0x67: // Undocumented
        [[fallthrough]];
    case 0x77: // JA, JNBE - Above
        dst = signconv(B, fetch(B));
        if (!(core.flags.f.cf || core.flags.f.zf))
            core.eip += dst;
        break;

    case 0x68: { // PUSH imm16/32
        int imm = operand_32 ? static_cast<int>(fetch(D)) : signconv(W, fetch(W));
        if (operand_32)
            push32(static_cast<Dword>(imm));
        else
            push(imm);
        break;
    }
    case 0x78: // JS - Sign
        dst = signconv(B, fetch(B));
        if (core.flags.f.sf)
            core.eip += dst;
        break;

    case 0x69: { // IMUL r16/r32, r/m16/r32, imm16/32
        decode();
        int eff_w = operand_32 ? D : W;
        dst       = getRM(eff_w, mod, rm);
        src       = eff_w == D ? fetch(D) : fetch(W);
        int64_t prod;
        if (eff_w == D) {
            prod = static_cast<int64_t>(static_cast<int32_t>(dst)) * static_cast<int32_t>(src);
        } else {
            prod = static_cast<int64_t>(signconv(W, dst)) * signconv(W, src);
        }
        res = static_cast<int>(prod & MASK[eff_w]);
        setReg(eff_w, reg, res);
        int64_t sext  = (eff_w == D)
                            ? static_cast<int64_t>(static_cast<int32_t>(res))
                            : static_cast<int64_t>(static_cast<int32_t>(static_cast<int16_t>(res)));
        bool overflow = (prod != sext);
        core.flags.f.cf = overflow;
        core.flags.f.of = overflow;
        // AF, SF, ZF, PF undefined per Intel
        unpredictable_flags = AF_MASK | SF_MASK | ZF_MASK | PF_MASK;
        break;
    }
    case 0x79: // JNS - Not sign
        dst = signconv(B, fetch(B));
        if (!core.flags.f.sf)
            core.eip += dst;
        break;

    case 0x6a: { // PUSH imm8 (sign-extended)
        int imm = signconv(B, fetch(B));
        if (operand_32)
            push32(static_cast<Dword>(imm));
        else
            push(imm);
        break;
    }
    case 0x7a: // JP, JPE - Parity even
        dst = signconv(B, fetch(B));
        if (core.flags.f.pf)
            core.eip += dst;
        break;

    case 0x6b: { // IMUL r16/r32, r/m16/r32, imm8 (sign-extended)
        decode();
        int eff_w = operand_32 ? D : W;
        dst       = getRM(eff_w, mod, rm);
        src       = signconv(B, fetch(B)); // imm8 sign-extended to operand size
        int64_t prod;
        if (eff_w == D) {
            prod = static_cast<int64_t>(static_cast<int32_t>(dst)) * static_cast<int32_t>(src);
        } else {
            prod = static_cast<int64_t>(signconv(W, dst)) * static_cast<int32_t>(src);
        }
        res = static_cast<int>(prod & MASK[eff_w]);
        setReg(eff_w, reg, res);
        int64_t sext  = (eff_w == D)
                            ? static_cast<int64_t>(static_cast<int32_t>(res))
                            : static_cast<int64_t>(static_cast<int32_t>(static_cast<int16_t>(res)));
        bool overflow = (prod != sext);
        core.flags.f.cf = overflow;
        core.flags.f.of = overflow;
        // AF, SF, ZF, PF undefined per Intel
        unpredictable_flags = AF_MASK | SF_MASK | ZF_MASK | PF_MASK;
        break;
    }
    case 0x7b: // JNP, JPO - Parity odd
        dst = signconv(B, fetch(B));
        if (!core.flags.f.pf)
            core.eip += dst;
        break;

    case 0x6c: { // INSB - Input string byte from port
        Dword ptr         = address_32 ? core.edi : static_cast<Dword>(static_cast<Word>(core.edi));
        unsigned dst_addr = linear_addr32(core.es, ptr);
        int val           = machine.port_in_byte(static_cast<unsigned>(core.edx & 0xFFFF));
        setMem(B, dst_addr, val);
        if (address_32)
            core.edi += (core.flags.f.df ? -1 : 1);
        else
            set_di(get_di() + (core.flags.f.df ? -1 : 1));
        break;
    }
    case 0x6d: { // INSW/INSD - Input string word/dword from port
        int eff_w         = operand_32 ? D : W;
        int delta         = (eff_w == D) ? 4 : 2;
        int stride        = (core.flags.f.df ? -1 : 1) * delta;
        Dword ptr         = address_32 ? core.edi : static_cast<Dword>(static_cast<Word>(core.edi));
        unsigned dst_addr = linear_addr32(core.es, ptr);
        int val =
            (eff_w == D)
                ? static_cast<int>(machine.port_in_32(static_cast<unsigned>(core.edx & 0xFFFF)))
                : machine.port_in_word(static_cast<unsigned>(core.edx & 0xFFFF));
        setMem(eff_w, dst_addr, val);
        if (address_32)
            core.edi += stride;
        else
            set_di(get_di() + stride);
        break;
    }
    case 0x7c: // JL, JNGE - Less (signed)
        dst = signconv(B, fetch(B));
        if (core.flags.f.sf != core.flags.f.of)
            core.eip += dst;
        break;

    case 0x7d: // JGE, JNL - Greater or equal (signed)
        dst = signconv(B, fetch(B));
        if (core.flags.f.sf == core.flags.f.of)
            core.eip += dst;
        break;

    case 0x6e: { // OUTSB - Output string byte to port
        const unsigned delta = 1;
        if (address_32) {
            if (static_cast<unsigned>(static_cast<Word>(core.esi)) > 0x10000 - delta) {
                os_is_ss = (os == core.ss);
                raise_segment_fault();
            }
        } else {
            unsigned si_off = static_cast<Word>(core.esi);
            if (si_off > 0x10000 - delta)
                raise_segment_fault();
        }
        Dword ptr         = address_32 ? core.esi : static_cast<Dword>(static_cast<Word>(core.esi));
        unsigned src_addr = linear_addr32(os, ptr);
        int val           = getMem(B, src_addr);
        unsigned port     = static_cast<unsigned>(core.edx & 0xFFFF);
        machine.port_out_byte(port, static_cast<Byte>(val));
        if (address_32)
            core.esi += (core.flags.f.df ? -1 : 1);
        else
            set_si(get_si() + (core.flags.f.df ? -1 : 1));
        break;
    }
    case 0x6f: { // OUTSW/OUTSD - Output string to port
        int eff_w              = operand_32 ? D : W;
        int delta              = (eff_w == D) ? 4 : 2;
        int stride             = (core.flags.f.df ? -1 : 1) * delta;
        const unsigned delta_u = static_cast<unsigned>(delta);
        if (address_32) {
            if (static_cast<unsigned>(static_cast<Word>(core.esi)) > 0x10000 - delta_u) {
                os_is_ss = (os == core.ss);
                raise_segment_fault();
            }
        } else {
            unsigned si_off = static_cast<Word>(core.esi);
            if (si_off > 0x10000 - delta_u)
                raise_segment_fault();
        }
        Dword ptr         = address_32 ? core.esi : static_cast<Dword>(static_cast<Word>(core.esi));
        unsigned src_addr = linear_addr32(os, ptr);
        int val           = getMem(eff_w, src_addr);
        unsigned port     = static_cast<unsigned>(core.edx & 0xFFFF);
        if (eff_w == D)
            machine.port_out_32(port, static_cast<Dword>(val));
        else
            machine.port_out_word(port, static_cast<Word>(val));
        if (address_32)
            core.esi += stride;
        else
            set_si(get_si() + stride);
        break;
    }
    case 0x7e: // JLE, JNG - Less or equal (signed)
        dst = signconv(B, fetch(B));
        if (core.flags.f.zf || (core.flags.f.sf != core.flags.f.of))
            core.eip += dst;
        break;
    case 0x7f: // JG, JNLE - Greater (signed)
        dst = signconv(B, fetch(B));
        if (!core.flags.f.zf && (core.flags.f.sf == core.flags.f.of))
            core.eip += dst;
        break;

    // IMUL r16/r32, r/m16/r32 (0F AF): two-operand form, dest = dest * r/m
    case 0x1af: {
        decode();
        int eff_w = operand_32 ? D : W;
        dst       = getReg(eff_w, reg);
        src       = getRM(eff_w, mod, rm);
        int64_t prod;
        if (eff_w == D) {
            prod = static_cast<int64_t>(static_cast<int32_t>(dst)) * static_cast<int32_t>(src);
        } else {
            prod = static_cast<int64_t>(signconv(W, dst)) * signconv(W, src);
        }
        res = static_cast<int>(prod & MASK[eff_w]);
        setReg(eff_w, reg, res);
        int64_t sext  = (eff_w == D)
                            ? static_cast<int64_t>(static_cast<int32_t>(res))
                            : static_cast<int64_t>(static_cast<int32_t>(static_cast<int16_t>(res)));
        bool overflow = (prod != sext);
        core.flags.f.cf     = overflow;
        core.flags.f.of     = overflow;
        unpredictable_flags = AF_MASK | SF_MASK | ZF_MASK | PF_MASK;
        break;
    }

    case 0x1a0: // PUSH FS (0F A0); o32 pushes 4 bytes (zero-extended)
        operand_32 ? push32(core.fs) : push(core.fs);
        break;
    case 0x1a1: // POP FS (0F A1); o32 pops 4 bytes, uses low 16 for FS
        core.fs = operand_32 ? (pop32() & 0xFFFF) : pop();
        break;
    case 0x1a8: // PUSH GS (0F A8); o32 pushes 4 bytes (zero-extended)
        operand_32 ? push32(core.gs) : push(core.gs);
        break;
    case 0x1a9: // POP GS (0F A9); o32 pops 4 bytes, uses low 16 for GS
        core.gs = operand_32 ? (pop32() & 0xFFFF) : pop();
        break;

    // SHLD (0F A4 imm8, 0F A5 CL): Double-precision shift left
    // Per 386: count MOD 32; if count=0 no-op; if count>=OperandSize result/flags undefined.
    // Memory destination: validate EA/segment limit before count==0 early-exit (fault order).
    case 0x1a4:
    case 0x1a5: {
        decode();
        int eff_w = operand_32 ? D : W;
        int count = (op == 0x1a5) ? (get_cl() & 0x1F) : (fetch(B) & 0x1F);
        int nbits = (eff_w == D) ? 32 : 16;
        if (mod != 0b11) {
            (void)getEA_cached(mod, rm);
            unsigned bytes = (eff_w == D) ? 4 : 2;
            if (last_ea_offset > 0x10000u - bytes)
                raise_segment_fault();
        }
        if (count == 0)
            break; // no operation, flags unchanged

        dst = getRM(eff_w, mod, rm);
        src = getReg(eff_w, reg);

        // SHLD: concat [dest|src], shift left; dest receives high nbits of result
        // For 16-bit, use 48-bit concat (dest:src:src) when count>16 so source wraps.
        uint64_t dbl;
        uint64_t shifted;
        int result;
        if (eff_w == W) {
            unsigned udst = dst & MASK[eff_w], usrc = src & MASK[eff_w];
            dbl = (static_cast<uint64_t>(udst) << 32) | (static_cast<uint64_t>(usrc) << 16) | usrc;
            shifted         = dbl << count;
            result          = static_cast<int>((shifted >> 32) & 0xFFFF);
            core.flags.f.cf = ((shifted >> 48) & 1) != 0;
        } else {
            dbl     = (static_cast<uint64_t>(dst & MASK[eff_w]) << nbits) | (src & MASK[eff_w]);
            shifted = dbl << count;
            result  = static_cast<int>((shifted >> nbits) & MASK[eff_w]);
            core.flags.f.cf = ((dst >> (nbits - count)) & 1) != 0;
        }
        setRM(eff_w, mod, rm, result);
        core.flags.f.of = (count == 1) ? (msb(eff_w, result) != core.flags.f.cf) : 0;
        if (count > 1)
            unpredictable_flags = OF_MASK;
        core.flags.f.zf = (result == 0);
        core.flags.f.sf = (result & SIGN[eff_w]) != 0;
        core.flags.f.pf = PARITY[result & 0xFF];
        unpredictable_flags |= AF_MASK; // AF undefined for SHLD
        break;
    }

    // SHRD (0F AC imm8, 0F AD CL): Double-precision shift right
    // Memory destination: validate EA/segment limit before count==0 early-exit (fault order).
    case 0x1ac:
    case 0x1ad: {
        decode();
        int eff_w = operand_32 ? D : W;
        int count = (op == 0x1ad) ? (get_cl() & 0x1F) : (fetch(B) & 0x1F);
        int nbits = (eff_w == D) ? 32 : 16;
        if (mod != 0b11) {
            (void)getEA_cached(mod, rm);
            unsigned bytes = (eff_w == D) ? 4 : 2;
            if (last_ea_offset > 0x10000u - bytes)
                raise_segment_fault();
        }
        if (count == 0)
            break;

        dst = getRM(eff_w, mod, rm);
        src = getReg(eff_w, reg);

        // SHRD: concat [src|dest], shift right; dest receives low nbits of result
        // For 16-bit, use 48-bit concat (src:src:dest) when count>16 so source wraps.
        unsigned udst = dst & MASK[eff_w], usrc = src & MASK[eff_w];
        uint64_t dbl;
        int result;
        if (eff_w == W) {
            dbl = (static_cast<uint64_t>(usrc) << 32) | (static_cast<uint64_t>(usrc) << 16) | udst;
            result          = static_cast<int>((dbl >> count) & 0xFFFF);
            core.flags.f.cf = ((dbl >> (count - 1)) & 1) != 0;
        } else {
            dbl             = (static_cast<uint64_t>(usrc) << nbits) | udst;
            result          = static_cast<int>((dbl >> count) & MASK[eff_w]);
            core.flags.f.cf = (count > 0) ? ((udst >> (count - 1)) & 1) != 0 : core.flags.f.cf;
        }
        setRM(eff_w, mod, rm, result);
        core.flags.f.of =
            (count == 1) ? (msb(eff_w, static_cast<int>(udst)) != msb(eff_w, result)) : 0;
        if (count > 1)
            unpredictable_flags = OF_MASK;
        core.flags.f.zf = (result == 0);
        core.flags.f.sf = (result & SIGN[eff_w]) != 0;
        core.flags.f.pf = PARITY[result & 0xFF];
        unpredictable_flags |= AF_MASK;
        break;
    }

    // BT (0F A3): Bit Test - store selected bit in CF
    case 0x1a3:
        do_bit_test(BitTestAction::test);
        break;

    // BTC (0F BB): Bit Test and Complement
    case 0x1bb:
        do_bit_test(BitTestAction::complement);
        break;

    // BTR (0F B3): Bit Test and Reset
    case 0x1b3:
        do_bit_test(BitTestAction::reset);
        break;

    // BTS (0F AB): Bit Test and Set
    case 0x1ab:
        do_bit_test(BitTestAction::set);
        break;

    // BT/BTS/BTR/BTC (0F BA /4-/7): r/m, imm8 - bit offset from immediate
    case 0x1ba:
        do_bit_test_imm();
        break;

    // MOVSX (0F BE): Move with sign extension, r16/r32 <- r/m8
    case 0x1be: {
        decode();
        int dest_w = operand_32 ? D : W;
        int val    = getRM(B, mod, rm);
        setReg(dest_w, reg, signconv(B, val));
        break;
    }

    // MOVSX (0F BF): Move with sign extension, r16/r32 <- r/m16
    case 0x1bf: {
        decode();
        int dest_w = operand_32 ? D : W;
        int val    = getRM(W, mod, rm);
        setReg(dest_w, reg, signconv(W, val));
        break;
    }

    // MOVZX (0F B6): Move with zero extension, r16/r32 <- r/m8
    case 0x1b6: {
        decode();
        int dest_w = operand_32 ? D : W;
        int val    = getRM(B, mod, rm);
        setReg(dest_w, reg, val & 0xFF);
        break;
    }

    // MOVZX (0F B7): Move with zero extension, r16/r32 <- r/m16
    case 0x1b7: {
        decode();
        int dest_w = operand_32 ? D : W;
        int val    = getRM(W, mod, rm);
        setReg(dest_w, reg, val & 0xFFFF);
        break;
    }

    // BSF (0F BC): Bit Scan Forward
    case 0x1bc: {
        decode();
        int eff_w  = operand_32 ? D : W;
        int srcval = getRM(eff_w, mod, rm);
        if (srcval == 0) {
            core.flags.f.zf = 1;
            core.flags.f.pf = 1; // real 386 when src=0 (captured in tests)
            core.flags.f.of = core.flags.f.sf = core.flags.f.af = core.flags.f.cf = 0;
            unpredictable_flags = OF_MASK | SF_MASK | AF_MASK | CF_MASK; // PF not unpredictable
            // dest undefined when src=0
        } else {
            int i = 0;
            while (((srcval >> i) & 1) == 0)
                ++i;
            setReg(eff_w, reg, i);
            core.flags.f.zf = 0;
            // OF, SF, AF, PF, CF undefined per Intel; mark so tests from real 386 can pass
            unpredictable_flags = OF_MASK | SF_MASK | AF_MASK | PF_MASK | CF_MASK;
        }
        break;
    }

    // BSR (0F BD): Bit Scan Reverse
    case 0x1bd: {
        decode();
        int eff_w  = operand_32 ? D : W;
        int srcval = getRM(eff_w, mod, rm);
        int nbits  = (eff_w == D) ? 32 : 16;
        if (srcval == 0) {
            core.flags.f.zf = 1;
            core.flags.f.pf = 1; // real 386 when src=0 (captured in tests)
            core.flags.f.of = core.flags.f.sf = core.flags.f.af = core.flags.f.cf = 0;
            unpredictable_flags = OF_MASK | SF_MASK | AF_MASK | CF_MASK; // PF not unpredictable
            // dest undefined when src=0
        } else {
            int i = nbits - 1;
            while (((srcval >> i) & 1) == 0)
                --i;
            setReg(eff_w, reg, i);
            core.flags.f.zf     = 0;
            unpredictable_flags = OF_MASK | SF_MASK | AF_MASK | PF_MASK | CF_MASK;
        }
        break;
    }

    // SETcc (0F 90-9F): Set byte to 0/1 based on condition
    case 0x190:
    case 0x191:
    case 0x192:
    case 0x193:
    case 0x194:
    case 0x195:
    case 0x196:
    case 0x197:
    case 0x198:
    case 0x199:
    case 0x19a:
    case 0x19b:
    case 0x19c:
    case 0x19d:
    case 0x19e:
    case 0x19f: {
        decode();
        bool cond = false;
        switch (op) {
        case 0x190:
            cond = core.flags.f.of;
            break;
        case 0x191:
            cond = !core.flags.f.of;
            break;
        case 0x192:
            cond = core.flags.f.cf;
            break;
        case 0x193:
            cond = !core.flags.f.cf;
            break;
        case 0x194:
            cond = core.flags.f.zf;
            break;
        case 0x195:
            cond = !core.flags.f.zf;
            break;
        case 0x196:
            cond = core.flags.f.cf || core.flags.f.zf;
            break;
        case 0x197:
            cond = !core.flags.f.cf && !core.flags.f.zf;
            break; // SETA
        case 0x198:
            cond = core.flags.f.sf;
            break;
        case 0x199:
            cond = !core.flags.f.sf;
            break;
        case 0x19a:
            cond = core.flags.f.pf;
            break;
        case 0x19b:
            cond = !core.flags.f.pf;
            break;
        case 0x19c:
            cond = core.flags.f.sf != core.flags.f.of;
            break;
        case 0x19d:
            cond = core.flags.f.sf == core.flags.f.of;
            break;
        case 0x19e:
            cond = core.flags.f.zf || (core.flags.f.sf != core.flags.f.of);
            break;
        case 0x19f:
            cond = !core.flags.f.zf && (core.flags.f.sf == core.flags.f.of);
            break;
        default:
            break;
        }
        setRM(B, mod, rm, cond ? 1 : 0);
        break;
    }

    // 386 Jcc with 16/32-bit displacement (0F 80-8F): rel16 (cw) or rel32 (cd) per operand size.
    // Real 386 rel32 base: last byte of disp when |disp|<256, else byte after.
    case 0x180:
    case 0x181:
    case 0x182:
    case 0x183:
    case 0x184:
    case 0x185:
    case 0x186:
    case 0x187:
    case 0x188:
    case 0x189:
    case 0x18a:
    case 0x18b:
    case 0x18c:
    case 0x18d:
    case 0x18e:
    case 0x18f: {
        int disp = operand_32 ? static_cast<int>(fetch(D)) : signconv(W, fetch(W));
        Dword jccbase =
            operand_32 ? ((disp >= -255 && disp <= 255) ? core.eip - 1 : core.eip) : core.eip;
        bool take = false;
        switch (op) {
        case 0x180:
            take = core.flags.f.of;
            break;
        case 0x181:
            take = !core.flags.f.of;
            break;
        case 0x182:
            take = core.flags.f.cf;
            break;
        case 0x183:
            take = !core.flags.f.cf;
            break;
        case 0x184:
            take = core.flags.f.zf;
            break;
        case 0x185:
            take = !core.flags.f.zf;
            break;
        case 0x186:
            take = core.flags.f.cf || core.flags.f.zf;
            break;
        case 0x187:
            take = !core.flags.f.cf && !core.flags.f.zf;
            break;
        case 0x188:
            take = core.flags.f.sf;
            break;
        case 0x189:
            take = !core.flags.f.sf;
            break;
        case 0x18a:
            take = core.flags.f.pf;
            break;
        case 0x18b:
            take = !core.flags.f.pf;
            break;
        case 0x18c:
            take = core.flags.f.sf != core.flags.f.of;
            break;
        case 0x18d:
            take = core.flags.f.sf == core.flags.f.of;
            break;
        case 0x18e:
            take = core.flags.f.zf || (core.flags.f.sf != core.flags.f.of);
            break;
        case 0x18f:
            take = !core.flags.f.zf && (core.flags.f.sf == core.flags.f.of);
            break;
        default:
            break;
        }
        if (take) {
            core.eip = static_cast<Dword>(jccbase + disp);
            core.eip &= 0xFFFFu; // Real mode: 16-bit EIP
        }
        break;
    }

    // LOOP, LOOPE, LOOPNE, JCXZ — counter is CX in 16-bit address size, ECX in 32-bit
    case 0xe2:
        dst = signconv(B, fetch(B));
        if (address_32) {
            core.ecx -= 1;
            if (core.ecx != 0)
                core.eip += dst;
        } else {
            set_cx(get_cx() - 1);
            if (get_cx() != 0) {
                core.eip += dst;
                core.eip &= 0xFFFFu;
            }
        }
        break;
    case 0xe1:
        dst = signconv(B, fetch(B));
        if (address_32) {
            core.ecx -= 1;
            if (core.ecx != 0 && core.flags.f.zf)
                core.eip += dst;
        } else {
            set_cx(get_cx() - 1);
            if (get_cx() != 0 && core.flags.f.zf) {
                core.eip += dst;
                core.eip &= 0xFFFFu;
            }
        }
        break;
    case 0xe0:
        dst = signconv(B, fetch(B));
        if (address_32) {
            core.ecx -= 1;
            if (core.ecx != 0 && !core.flags.f.zf)
                core.eip += dst;
        } else {
            set_cx(get_cx() - 1);
            if (get_cx() != 0 && !core.flags.f.zf) {
                core.eip += dst;
                core.eip &= 0xFFFFu;
            }
        }
        break;
    case 0xe3: {
        dst          = signconv(B, fetch(B));
        Dword cx_val = address_32 ? core.ecx : (core.ecx & 0xFFFF);
        if (cx_val == 0) {
            core.eip += dst;
            if (!address_32) // 16-bit code segment: keep EIP in 16 bits
                core.eip &= 0xFFFFu;
        }
        break;
    }

    // INT3, INT, INTO: software interrupt
    case 0xcc:
        call_int(3);
        break;
    case 0xcd:
        call_int(fetch(B));
        break;
    case 0xce:
        if (core.flags.f.of) {
            call_int(4);
        }
        break;

    // IRET / IRETD: pop IP/EIP, CS, FLAGS/EFLAGS
    case 0xcf:
        if (operand_32) {
            // IRETD: pop EIP(4), CS(4), EFLAGS(4). In real mode validate return EIP before
            // committing. Stack read may wrap within 64K segment; only fault if return EIP invalid.
            Word sp         = get_sp();
            Dword ret_eip   = getMem(D, linear_addr21(core.ss, sp));
            Dword ret_cs    = getMem(D, linear_addr21(core.ss, static_cast<Word>(sp + 4)));
            Dword ret_flags = getMem(D, linear_addr21(core.ss, static_cast<Word>(sp + 8)));
            if (ret_eip > 0xFFFF) {
                os_is_ss = false;
                raise_segment_fault();
            }
            set_sp(sp + 12);
            core.eip = ret_eip;
            core.cs  = ret_cs & 0xFFFF;
            set_eflags(ret_flags);
        } else {
            set_ip(pop());
            core.cs = pop();
            set_flags(static_cast<Word>(pop()));
        }
        intercept_bios_call();
        break;

    // Flag ops
    case 0xf8:
        core.flags.f.cf = 0; // CLC
        break;
    case 0xf5:
        core.flags.f.cf = !core.flags.f.cf; // CMC
        break;
    case 0xf9:
        core.flags.f.cf = 1; // STC
        break;
    case 0xfc:
        core.flags.f.df = 0; // CLD
        break;
    case 0xfd:
        core.flags.f.df = 1; // STD
        break;
    case 0xfa:
        core.flags.f.ifl = 0; // CLI
        break;
    case 0xfb:
        core.flags.f.ifl = 1; // STI
        break;

    // HLT: Pause until an external interrupt is received
    case 0xf4:
        break;

    // WAIT
    case 0x9b:
        break;

    // ESC: Escape
    case 0xd8:
    case 0xd9:
    case 0xda:
    case 0xdb:
    case 0xdc:
    case 0xdd:
    case 0xde:
    case 0xdf:
        decode();
        break;

    // NOP
    case 0x90:
        break;

    // --- Group 80/81/82/83: ALU with immediate; D0-D3: shift/rotate; F6/F7: TEST/NOT/NEG/MUL/DIV;
    // FE/FF: INC/DEC/CALL/JMP/PUSH ---
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83: {
        decode();
        int eff_w = (operand_32 && w) ? D : (w ? W : B);
        dst       = getRM(eff_w, mod, rm);
        if (op == 0x81)
            src = eff_w == D ? fetch(D) : (fetch(B) | (fetch(B) << 8));
        else if (op == 0x83) {
            src = fetch(B);
            src = eff_w == D ? static_cast<int>(static_cast<int32_t>(static_cast<int8_t>(src)))
                             : ((src & SIGN[B]) != 0 ? (src | 0xff00) : src);
        } else
            src = fetch(B);
        switch (reg) {
        case 0:
            res = add(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
            break;
        case 1:
            if (op == 0x80 || op == 0x81 || op == 0x82 || op == 0x83) {
                res = dst | src;
                logic(eff_w, res);
                setRM(eff_w, mod, rm, res);
            }
            break;
        case 2:
            res = adc(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
            break;
        case 3:
            res = sbb(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
            break;
        case 4:
            if (op == 0x80 || op == 0x81 || op == 0x82 || op == 0x83) {
                res = dst & src;
                logic(eff_w, res);
                setRM(eff_w, mod, rm, res);
            }
            break;
        case 5:
            res = sub(eff_w, dst, src);
            setRM(eff_w, mod, rm, res);
            break;
        case 6:
            if (op == 0x80 || op == 0x81 || op == 0x82 || op == 0x83) {
                res = dst ^ src;
                logic(eff_w, res);
                setRM(eff_w, mod, rm, res);
            }
            break;
        case 7:
            sub(eff_w, dst, src);
            break;
        default:
            break;
        }
        break;
    }

    // POP reg/mem (386 requires reg=0; other reg values generate #UD)
    case 0x8f:
        decode();
        if (reg != 0) {
            core.eip = fault_eip;
            call_int(6);
            break;
        }
        if (operand_32) {
            // 386: 4-byte pop crossing 64K segment boundary triggers #SS (per batch4).
            if (get_sp() > 0x10000 - 4) {
                os_is_ss = true;
                raise_segment_fault();
            }
            // Validate destination EA before consuming stack (fault order per real 386).
            (void)getEA_cached(mod, rm);
            if (mod != 0b11) {
                if (last_ea_offset > 0x10000 - 4)
                    raise_segment_fault();
            }
            setRM(D, mod, rm, pop32());
        } else {
            (void)getEA_cached(mod, rm);
            if (mod != 0b11) {
                if (last_ea_offset > 0x10000 - 2)
                    raise_segment_fault();
            }
            setRM(W, mod, rm, pop());
        }
        break;

    // Shift/rotate: C0/C1 by immediate, D0-D3 by 1 or CL
    case 0xc0:
    case 0xc1:
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3: {
        decode();
        int eff_w = (operand_32 && w) ? D : (w ? W : B);
        dst       = getRM(eff_w, mod, rm);
        if (op == 0xc0 || op == 0xc1)
            src = fetch(B) & 0x1F; // 386: count masked to 5 bits
        else if (op == 0xd0 || op == 0xd1)
            src = 1;
        else {
            // 386: count masked to 5 bits for all shift/rotate
            int cnt = get_cl() & 0x1F;
            if (reg == 2 || reg == 3) {
                int n = (eff_w == B) ? 9 : (eff_w == W ? 17 : 33);
                src   = cnt % n;
            } else if (reg == 0 || reg == 1) {
                int n = (eff_w == B) ? 8 : (eff_w == W ? 16 : 32);
                src   = cnt % n;
            } else
                src = cnt;
        }
        if (src == 0) {
            if ((op == 0xd2 || op == 0xd3) && (reg == 2 || reg == 3) && (get_cl() & 0x1F) != 0)
                unpredictable_flags |= OF_MASK;
            // Real 386 ROL: when count % size == 0 but CL masked != 0, CF = LSB of result.
            // OF is left undefined per manual; do not force it so legacy captures (e.g. batch20) match.
            if ((op == 0xd2 || op == 0xd3) && reg == 0 && (get_cl() & 0x1F) != 0) {
                core.flags.f.cf = (dst & 1) != 0;
                unpredictable_flags |= OF_MASK;
            }
            // Real 386 ROR: when count % size == 0 but CL masked != 0, CF = MSB(result), OF = MSB XOR MSB(result<<1)
            if ((op == 0xd2 || op == 0xd3) && reg == 1 && (get_cl() & 0x1F) != 0) {
                dst &= MASK[eff_w];
                core.flags.f.cf = msb(eff_w, dst);
                core.flags.f.of = msb(eff_w, dst) != msb(eff_w, (dst << 1) & MASK[eff_w]);
            }
            break;
        }
        bool temp_cf;
        switch (reg) {
        case 0: // ROL
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = msb(eff_w, dst);
                dst     = ((dst << 1) | (temp_cf ? 1 : 0)) & MASK[eff_w];
            }
            core.flags.f.cf = (dst & 1) != 0;
            core.flags.f.of = msb(eff_w, dst) != core.flags.f.cf; // 8086: same for count>=1
            break;
        case 1: { // ROR
            int rot_mod = (eff_w == B) ? 8 : (eff_w == W ? 16 : 32);
            int eff_cnt = src % rot_mod;
            dst &= MASK[eff_w]; // mask before rotate (getReg sign-extends byte/word)
            for (int cnt = 0; cnt < eff_cnt; ++cnt) {
                temp_cf = (dst & 1) != 0;
                dst =
                    ((static_cast<unsigned>(dst) >> 1) | (temp_cf ? SIGN[eff_w] : 0)) & MASK[eff_w];
            }
            if (eff_cnt != 0) {
                core.flags.f.cf = msb(eff_w, dst);
                core.flags.f.of = msb(eff_w, dst) != msb(eff_w, (dst << 1) & MASK[eff_w]);
            } else {
                // eff_cnt == 0: value unchanged; CF = MSB(result), OF = MSB XOR MSB(result<<1) per
                // real 386
                core.flags.f.cf = msb(eff_w, dst);
                core.flags.f.of = msb(eff_w, dst) != msb(eff_w, (dst << 1) & MASK[eff_w]);
            }
            break;
        }
        case 2: // RCL
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf         = msb(eff_w, dst);
                dst             = ((dst << 1) | core.flags.f.cf) & MASK[eff_w];
                core.flags.f.cf = temp_cf;
            }
            core.flags.f.of = msb(eff_w, dst) != core.flags.f.cf;
            break;
        case 3:                 // RCR
            dst &= MASK[eff_w]; // mask before rotate (getReg sign-extends byte/word)
            if (src == 1)
                core.flags.f.of = msb(eff_w, dst) != core.flags.f.cf;
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = (dst & 1) != 0;
                dst = ((static_cast<unsigned>(dst) >> 1) | (core.flags.f.cf ? SIGN[eff_w] : 0)) &
                      MASK[eff_w];
                core.flags.f.cf = temp_cf;
            }
            if (src != 1) {
                // The overflow flag is defined only for the single-rotate forms
                // of the instructions (second operand := 1).
                // It is undefined in all other cases.
                unpredictable_flags = OF_MASK;
            }
            break;
        case 4:
        case 6: { // SAL/SHL (reg 4 and 6 both encode SHL/SAL on 386)
            int shl_thresh = (eff_w == B) ? 8 : (eff_w == W ? 16 : 32);
            if (src >= shl_thresh) {
                // CF/OF when count >= width: Intel says undefined; clear and mark unpredictable
                // AF: real 386 sets AF=1 when result is 0
                core.flags.f.cf     = 0;
                core.flags.f.of     = 0;
                core.flags.f.af     = 1;
                unpredictable_flags = OF_MASK | CF_MASK;
                dst                 = 0;
                update_flags_zsp(eff_w, dst);
            } else {
                for (int cnt = 0; cnt < src; ++cnt) {
                    core.flags.f.cf = (dst & SIGN[eff_w]) != 0;
                    dst             = (dst << 1) & MASK[eff_w];
                }
                core.flags.f.of = ((dst & SIGN[eff_w]) != 0) != core.flags.f.cf;

                // AF undefined per Intel; OF/CF undefined when result is 0 (some CPUs)
                unpredictable_flags = AF_MASK;
                if (dst == 0)
                    unpredictable_flags |= OF_MASK | CF_MASK;

                if (src > 0)
                    update_flags_zsp(eff_w, dst);
            }
            break;
        }
        case 5: {               // SHR
            dst &= MASK[eff_w]; // mask (getReg sign-extends)
            int shr_thresh      = (eff_w == B) ? 8 : (eff_w == W ? 16 : 32);
            unpredictable_flags = AF_MASK; // AF undefined for SHR
            if (src >= shr_thresh) {
                // Result = 0. CF/OF undefined when count >= width (Intel 386); AF=1 when result 0
                core.flags.f.cf = ((static_cast<unsigned>(dst) >> (shr_thresh - 1)) & 1) != 0;
                dst             = 0;
                core.flags.f.of = 0;
                core.flags.f.af = 1;
                unpredictable_flags |= CF_MASK; // CF undefined per Intel when count >= width
                update_flags_zsp(eff_w, dst);
            } else {
                if (src == 1)
                    core.flags.f.of = (dst & SIGN[eff_w]) != 0;
                else if (src > 1)
                    core.flags.f.of = 0;
                for (int cnt = 0; cnt < src; ++cnt) {
                    core.flags.f.cf = (dst & 1) != 0;
                    dst             = (static_cast<unsigned>(dst) >> 1) & MASK[eff_w];
                }
                if (src > 0) {
                    core.flags.f.af = 0;
                    update_flags_zsp(eff_w, dst);
                }
            }
            break;
        }
        case 7: // SAR - 8086 uses original sign bit for all shift-ins
            if (src == 1)
                core.flags.f.of = 0;
            if (src > 0) {
                int signbit     = (dst & SIGN[eff_w]);
                int sign_thresh = (eff_w == B) ? 8 : (eff_w == W ? 16 : 32);
                if (src >= sign_thresh) {
                    core.flags.f.cf = signbit != 0;
                    core.flags.f.of = 0;
                    dst             = signbit ? MASK[eff_w] : 0;
                    // Real 386: AF=1 when result is all 1s (was negative), else 0
                    core.flags.f.af = signbit != 0;
                } else {
                    for (int cnt = 0; cnt < src; ++cnt) {
                        core.flags.f.cf = (dst & 1) != 0;
                        dst             = ((dst >> 1) | signbit) & MASK[eff_w];
                    }
                    core.flags.f.of = 0;
                    core.flags.f.af = 0;
                }
                // AF undefined per Intel
                unpredictable_flags = AF_MASK;
                update_flags_zsp(eff_w, dst);
            }
            break;
        default:
            break;
        }
        setRM(eff_w, mod, rm, dst);
        break;
    }

    // TEST imm, NOT, NEG, MUL, IMUL, DIV, IDIV
    case 0xf6:
    case 0xf7: {
        decode();
        int eff_w = (operand_32 && w) ? D : (w ? W : B);
        // Real 386: on segment fault reading MUL operand, pushed FLAGS low byte is 0x17.
        if (reg == 4 && mod != 0b11) {
            (void)getEA_cached(mod, rm);
            unsigned bytes = (eff_w == D) ? 4 : (eff_w == W) ? 2 : 1;
            if (last_ea_offset > 0x10000u - bytes) {
                core.flags.f.cf = 1;
                core.flags.f.pf = 1;
                core.flags.f.af = 1;
                core.flags.f.zf = 0;
                core.flags.f.sf = 0;
                raise_segment_fault();
            }
        }
        src = getRM(eff_w, mod, rm);
        switch (reg) {
        case 0:
        case 1: {
            // TEST r/m, imm. getRM already advanced EIP past ModR/M and disp (including
            // address_32 SIB+disp). Immediate is at current EIP.
            int imm = (op == 0xf7 && eff_w == D) ? fetch(D) : (op == 0xf7 ? fetch(W) : fetch(B));
            logic(eff_w, (imm & src));
            break;
        }
        case 2:
            setRM(eff_w, mod, rm, ~src);
            break;
        case 3: {
            dst             = sub(eff_w, 0, src);
            core.flags.f.cf = dst != 0;
            setRM(eff_w, mod, rm, dst);
            break;
        }
        case 4: // MUL
            if (w == B) {
                res = get_al() * static_cast<uint8_t>(src);
                if (rep != 0) {
                    // 8086 REP/REPNE with MUL negates product
                    res = (Word)-res;
                }
                set_ax(res & 0xFFFF);
                core.flags.f.cf = (res >> 8) != 0;
                core.flags.f.of = (res >> 8) != 0;
                core.flags.f.zf = ((res >> 8) == 0);
                core.flags.f.pf = PARITY[res >> 8]; // undefined per Intel; match 386 (parity of AH)
                core.flags.f.sf = (int16_t)(res & 0xFFFF) < 0;
                // AF, PF, SF, ZF undefined for byte MUL per Intel; PF varies by CPU
                unpredictable_flags = AF_MASK | PF_MASK | ZF_MASK | SF_MASK;
            } else if (eff_w == D) {
                // 32-bit MUL: EAX * r/m32 -> EDX:EAX
                uint64_t lres = static_cast<uint64_t>(core.eax) * static_cast<uint32_t>(src);
                if (rep != 0) {
                    lres = -lres;
                }
                core.eax            = lres;
                core.edx            = lres >> 32;
                core.flags.f.cf     = core.edx != 0;
                core.flags.f.of     = core.edx != 0;
                core.flags.f.sf     = (static_cast<int32_t>(core.edx) < 0);
                unpredictable_flags = PF_MASK | ZF_MASK | AF_MASK | SF_MASK;
            } else {
                // Word MUL: AX * r/m16 -> DX:AX (preserve high 16 bits of EAX, EDX)
                uint32_t lres = static_cast<uint32_t>(get_ax()) * static_cast<Word>(src);
                if (rep != 0) {
                    lres = -lres;
                }
                set_ax(lres);
                set_dx(lres >> 16);
                core.flags.f.cf = (lres >> 16) != 0;
                core.flags.f.of = (lres >> 16) != 0;
                core.flags.f.sf = (int16_t)(lres >> 16) < 0;

                // Word MUL: PF, ZF, SF, AF undefined per Intel; mask so tests do not compare.
                unpredictable_flags = PF_MASK | ZF_MASK | SF_MASK | AF_MASK;
            }
            break;
        case 5: // IMUL
            // AF, SF, ZF, PF undefined per Intel; only CF and OF are defined.
            unpredictable_flags = PF_MASK | AF_MASK | ZF_MASK | SF_MASK;

            if (w == B) {
                int s    = signconv(B, src);
                int dval = signconv(B, get_al());
                res      = (Word)(dval * s);
                if (rep != 0) {
                    // 8086 REP/REPNE with IMUL negates product
                    res = (Word)-res;
                }
                set_ax(res & 0xFFFF); // result to AX only
                bool byte_overflow = ((int16_t)res != (int8_t)(res & 0xFF));
                core.flags.f.cf    = byte_overflow;
                core.flags.f.of    = byte_overflow;
                // Real 386 sets undefined flags from result: SF/PF/ZF from AX, AF=0.
                core.flags.f.sf = (int16_t)(res & 0xFFFF) < 0;
                core.flags.f.zf = ((res >> 8) == 0);
                core.flags.f.pf = PARITY[res >> 8];
                core.flags.f.af = 0;
            } else if (eff_w == D) {
                int64_t prod = static_cast<int64_t>(static_cast<int32_t>(core.eax)) *
                               static_cast<int64_t>(static_cast<int32_t>(src));
                if (rep != 0)
                    prod = -prod;
                core.eax = static_cast<Dword>(prod & 0xFFFFFFFFu);
                core.edx = static_cast<Dword>(prod >> 32);
                bool dword_overflow =
                    (static_cast<int64_t>(static_cast<int32_t>(core.eax)) != prod);
                core.flags.f.cf = dword_overflow;
                core.flags.f.of = dword_overflow;
            } else {
                uint32_t lres = (long)signconv(W, core.eax) * (long)signconv(W, src);
                if (rep != 0) {
                    lres = -lres;
                }
                set_ax(lres & 0xFFFF);
                set_dx((lres >> 16) & 0xFFFF);
                bool word_overflow =
                    (static_cast<int32_t>(lres) != static_cast<int16_t>(lres & 0xFFFF));
                core.flags.f.cf = word_overflow;
                core.flags.f.of = word_overflow;
            }
            break;
        case 6: // DIV (unsigned)
            // In 8086 documentation, DIV leaves CF, OF, SF, ZF, PF, AF undefined.
            // Flags DF/IF/TF stay unchanged.
            unpredictable_flags = CF_MASK | OF_MASK | SF_MASK | ZF_MASK | PF_MASK | AF_MASK;

            if (w == B) {
                Byte divb = src;
                if (divb == 0) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = 0;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                Word dividend = static_cast<Word>(core.eax); // AX for byte DIV
                Word quo      = dividend / divb;
                Byte rem      = dividend % divb;
                if (quo > 0xFF) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                set_al(quo);
                set_ah(rem);
            } else if (eff_w == D) {
                uint32_t divd = static_cast<uint32_t>(src);
                if (divd == 0) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = 0;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                uint64_t ldst = (static_cast<uint64_t>(core.edx) << 32) | (core.eax & 0xFFFFFFFFu);
                uint64_t quo  = ldst / divd;
                uint32_t rem  = ldst % divd;
                if (quo > 0xFFFFFFFFu) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                core.eax = static_cast<uint32_t>(quo);
                core.edx = rem;
            } else {
                Word divw = src;
                if (divw == 0) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = 0;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                unsigned ldst = ((core.edx & 0xFFFFu) << 16) | (core.eax & 0xFFFFu);
                unsigned quo  = ldst / divw;
                unsigned rem  = ldst % divw;
                if (quo > 0xFFFF) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                set_ax(static_cast<Word>(quo));
                set_dx(static_cast<Word>(rem));
            }
            break;
        case 7: // IDIV (signed integer division)
            // According to the 8086 manual, the arithmetic flags are left
            // in an undefined state: CF, PF, AF, ZF, SF, OF.
            unpredictable_flags = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;

            if (eff_w == D) {
                // 32-bit IDIV: divide EDX:EAX by r/m32, quotient→EAX, remainder→EDX
                int32_t divs = static_cast<int32_t>(src);
                if (divs == 0) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = 0;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                int64_t dividend = (static_cast<int64_t>(static_cast<int32_t>(core.edx)) << 32) |
                                   (core.eax & 0xFFFFFFFFu);
                int64_t quo      = dividend / divs;
                int64_t rem      = dividend % divs;
                if (quo > 0x7FFFFFFF || quo < -2147483648LL) {
                    last_unpredictable_flags = unpredictable_flags | 0xFF00; // high byte undefined
                    unpredictable_flags      = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                core.eax = static_cast<uint32_t>(quo);
                core.edx = static_cast<uint32_t>(rem);
            } else if (w == B) {
                // Dividend is a signed 16-bit value in AX.
                // Divisor is a signed 8-bit value (register or memory).
                src = (int8_t)src;
                if (src == 0) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = 0;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                dst = (int16_t)core.eax;
                res = dst / src;
                // 8086/8088: min negative quotient is -127, not -128 (Q68599); -128 triggers INT 0.
                if (res > 0x7f || res < -0x7f) {
                    last_unpredictable_flags = unpredictable_flags | 0xFF00; // high byte undefined
                    unpredictable_flags      = 0;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                if (rep != 0) {
                    // 8086 REP/REPNE with IDIV negates quotient
                    res = -res;
                }
                set_al(res);
                set_ah(dst % src);
            } else {
                // Dividend is a signed 32-bit value in DX:AX (low 16 bits only).
                // Divisor is a signed 16-bit value (register or memory).
                src = (int16_t)src;
                if (src == 0) {
                    last_unpredictable_flags = unpredictable_flags;
                    unpredictable_flags      = 0;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                dst          = (int32_t)(((core.edx & 0xFFFFu) << 16) | (core.eax & 0xFFFFu));
                int64_t lres = (int64_t)dst / src;
                // 8086/8088: min negative quotient is -32767, not -32768 (Q68599); -32768 triggers
                // INT 0.
                if (lres > 0x7fff || lres < -0x7fff) {
                    last_unpredictable_flags = unpredictable_flags | 0xFF00; // high byte undefined
                    unpredictable_flags      = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;
                    core.eip                 = fault_eip;
                    call_int(0);
                    break;
                }
                if (rep != 0) {
                    // 8086 REP/REPNE with IDIV negates quotient
                    lres = -lres;
                }
                set_ax(static_cast<Word>(static_cast<uint32_t>(lres) & 0xFFFFu));
                set_dx(static_cast<Word>(static_cast<uint32_t>(dst % src) & 0xFFFFu));
            }
            break;
        default:
            break;
        }
        break;
    }

    // INC/DEC byte
    case 0xfe:
        decode();
        src = getRM(w, mod, rm);
        switch (reg) {
        case 0:
            setRM(w, mod, rm, inc(w, src));
            break;
        case 1:
            setRM(w, mod, rm, dec(w, src));
            break;
        default:
            break;
        }
        break;

    // INC/DEC word, CALL, JMP, PUSH
    case 0xff:
        decode();
        src = getRM(w, mod, rm);
        switch (reg) {
        case 0:
            setRM(w, mod, rm, inc(w, src));
            break;
        case 1:
            setRM(w, mod, rm, dec(w, src));
            break;
        case 2:
            push(core.eip);
            core.eip = src;
            break;
        case 3: { // LCALL
            unsigned addr = getEA(mod, rm);
            unsigned off  = addr - (os << 4);
            dst           = getMemAtSegOff(W, os, off);
            src           = getMemAtSegOff(W, os, off + 2);
            push(core.cs);
            push(core.eip);
            core.eip = dst;
            core.cs  = src;
            intercept_bios_call();
            break;
        }
        case 4:
            core.eip = src;
            break;
        case 5: { // LJMP
            unsigned addr = getEA(mod, rm);
            unsigned off  = addr - (os << 4);
            core.eip      = getMemAtSegOff(W, os, off);
            core.cs       = getMemAtSegOff(W, os, off + 2);
            intercept_bios_call();
            break;
        }
        case 6:
        case 7:
            // 8086 PUSH r/m (FF/6 and FF/7). PUSH SP (mod=11, rm=4) pushes SP-2, not SP.
            if (mod == 0b11 && rm == 4)
                src = core.esp - 2;
            push(src);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
