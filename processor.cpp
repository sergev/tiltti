//
// i86 processor.
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
#include "machine.h"

//
// 8086 size codes (B=byte, W=word).
//
static const int B            = 0;
static const int W            = 1;
static const int BITS[2]      = { 8, 16 };
static const unsigned SIGN[2] = { 0x80u, 0x8000u };
static const unsigned MASK[2] = { 0xffu, 0xffffu };

static const int PARITY[256] = {
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1
};

static int shift(int x, int n)
{
    return n >= 0 ? x << n : x >> -n;
}

//
// Initialize the processor.
//
Processor::Processor(Machine &mach) : machine(mach)
{
    reset();
}

//
// Reset routine: all registers and opcode to initial 8086 state.
//
void Processor::reset()
{
    core    = {};
    core.ip = 0x0000;
    core.cs = 0xffff;
    core.ds = 0x0000;
    core.ss = 0x0000;
    core.es = 0x0000;
    set_flags(0);
    opcode           = {};
    plen             = 0;
    rep              = 0;
    segment_override = false;
    os               = core.ds;
    ea               = -1;

    // Show initial state.
    machine.trace_exception("Reset");
    machine.trace_registers();
}

//
// Set FLAGS register.
//
void Processor::set_flags(Word val)
{
    // Bits 1,3,5 reserved (1,0,0).
    static const unsigned FLAGS_WRITABLE = 0x0FD5; // bits 0,2,4,6-11 writable
    static const unsigned FLAGS_ONES     = 0xF002; // bits 1,12-15 always 1

    core.flags.w = (val & FLAGS_WRITABLE) | FLAGS_ONES;
}

void Processor::update_flags_zsp(int width, int res)
{
    // Zero flag.
    core.flags.f.z = res == 0;

    // Sign flag.
    if (width == B) {
        core.flags.f.s = (int8_t)res < 0;
    } else {
        core.flags.f.s = (int16_t)res < 0;
    }

    // Parity flag.
    core.flags.f.p = PARITY[(Byte)res];
}

//
// Effective address from ModR/M and displacement; 8086 addressing modes.
//
unsigned Processor::getEA(unsigned mod_val, unsigned rm_val)
{
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

    switch (rm_val) {
    case 0b000:
        return pc86_linear_addr(os, core.bx + core.si + disp);
    case 0b001:
        return pc86_linear_addr(os, core.bx + core.di + disp);
    case 0b010:
        return pc86_linear_addr(os, core.bp + core.si + disp);
    case 0b011:
        return pc86_linear_addr(os, core.bp + core.di + disp);
    case 0b100:
        return pc86_linear_addr(os, core.si + disp);
    case 0b101:
        return pc86_linear_addr(os, core.di + disp);
    case 0b110:
        if (mod_val == 0)
            return pc86_linear_addr(os, opcode[plen + 2] | (opcode[plen + 3] << 8));
        else
            return pc86_linear_addr(os, core.bp + disp);
    case 0b111:
        return pc86_linear_addr(os, core.bx + disp);
    default:
        // Cannot happen
        return pc86_linear_addr(os, 0);
    }
}

//
// Fetch 1 or 2 bytes at CS:IP, advance IP.
//
int Processor::getMem(int width)
{
    Word val = machine.mem_fetch_byte(pc86_linear_addr(core.cs, core.ip));
    if (width == W) {
        val |= machine.mem_fetch_byte(pc86_linear_addr(core.cs, core.ip + 1)) << 8;
    }
    core.ip += 1 + width;
    return val;
}

//
// Read byte or word at linear address.
//
int Processor::getMem(int width, unsigned addr)
{
    if (width == B)
        return machine.mem_load_byte(addr);
    return machine.mem_load_word(addr);
}

//
// Write byte or word at linear address.
//
void Processor::setMem(int width, unsigned addr, int val)
{
    if (width == B)
        machine.mem_store_byte(addr, val);
    else
        machine.mem_store_word(addr, val);
}

//
// Word access with 8086 segment offset wraparound (offset 0xFFFF -> second byte at seg:0).
//
int Processor::getMemAtSegOff(int width, Word seg, Word off)
{
    if (width == B) {
        return machine.mem_load_byte(pc86_linear_addr(seg, off));
    }
    if (off == 0xffff) {
        Byte lo = machine.mem_load_byte(pc86_linear_addr(seg, 0xffff));
        Byte hi = machine.mem_load_byte(pc86_linear_addr(seg, 0));
        return lo | (hi << 8);
    }
    return machine.mem_load_word(pc86_linear_addr(seg, off));
}

void Processor::setMemAtSegOff(int width, Word seg, Word off, int val)
{
    if (width == B) {
        machine.mem_store_byte(pc86_linear_addr(seg, off), val);
        return;
    }
    if (off == 0xffff) {
        machine.mem_store_byte(pc86_linear_addr(seg, 0xffff), val);
        machine.mem_store_byte(pc86_linear_addr(seg, 0), val >> 8);
        return;
    }
    machine.mem_store_word(pc86_linear_addr(seg, off), val);
}

//
// Get general or pointer register (reg encoding: 0=AX/AL, 1=CX/CL, ..., 4=SP, 5=BP, 6=SI, 7=DI).
//
int Processor::getReg(int width, unsigned r) const
{
    if (width == B) {
        switch (r) {
        case 0:
            return get_al();
        case 1:
            return get_cl();
        case 2:
            return get_dl();
        case 3:
            return get_bl();
        case 4:
            return get_ah();
        case 5:
            return get_ch();
        case 6:
            return get_dh();
        case 7:
            return get_bh();
        default:
            return 0;
        }
    } else {
        switch (r) {
        case 0:
            return core.ax;
        case 1:
            return core.cx;
        case 2:
            return core.dx;
        case 3:
            return core.bx;
        case 4:
            return core.sp;
        case 5:
            return core.bp;
        case 6:
            return core.si;
        case 7:
            return core.di;
        default:
            return 0;
        }
    }
}

//
// Set general or pointer register.
//
void Processor::setReg(int width, unsigned r, int val)
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
    } else {
        switch (r) {
        case 0:
            core.ax = val;
            break;
        case 1:
            core.cx = val;
            break;
        case 2:
            core.dx = val;
            break;
        case 3:
            core.bx = val;
            break;
        case 4:
            core.sp = val;
            break;
        case 5:
            core.bp = val;
            break;
        case 6:
            core.si = val;
            break;
        case 7:
            core.di = val;
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
int Processor::getRM(int width, unsigned mod_val, unsigned rm_val)
{
    if (mod_val == 0b11)
        return getReg(width, rm_val);
    unsigned addr = getEA(mod_val, rm_val);
    if (width == W) {
        Word off = addr - (os << 4);
        if (off == 0xffff)
            return getMemAtSegOff(W, os, 0xffff);
    }
    return getMem(width, addr);
}

//
// Set R/M operand.
// 8086 segment wraparound: word at offset 0xFFFF has high byte at offset 0 in same segment.
//
void Processor::setRM(int width, unsigned mod_val, unsigned rm_val, int val)
{
    if (mod_val == 0b11)
        setReg(width, rm_val, val);
    else {
        unsigned addr = getEA(mod_val, rm_val);
        if (width == W) {
            Word off = addr - (os << 4);
            if (off == 0xffff) {
                setMemAtSegOff(W, os, 0xffff, val);
                return;
            }
        }
        setMem(width, addr, val);
    }
}

//
// Get segment register (encoding 0=ES, 1=CS, 2=SS, 3=DS).
//
Word Processor::getSegReg(unsigned r) const
{
    switch (r & 3) {
    case 0:
        return core.es;
    case 1:
        return core.cs;
    case 2:
        return core.ss;
    case 3:
        return core.ds;
    default:
        return 0;
    }
}

//
// Set segment register.
//
void Processor::setSegReg(unsigned r, Word val)
{
    switch (r & 3) {
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
    default:
        break;
    }
}

//
// Decode ModR/M byte from opcode; advance IP by 1, 2, or 3.
//
void Processor::decode()
{
    mod = (opcode[plen + 1] >> 6) & 0b11;
    reg = (opcode[plen + 1] >> 3) & 0b111;
    rm  = opcode[plen + 1] & 0b111;

    if (mod == 0b01)
        core.ip = (core.ip + 2) & 0xffff;
    else if ((mod == 0b00 && rm == 0b110) || mod == 0b10)
        core.ip = (core.ip + 3) & 0xffff;
    else
        core.ip = (core.ip + 1) & 0xffff;

    // Default segment: use SS when effective address uses BP (no segment override).
    if (!segment_override && mod != 0b11 && (rm == 2 || rm == 3 || (rm == 6 && mod != 0)))
        os = core.ss;
}

//
// Stack is SS:SP; 16-bit little-endian. Pop word.
//
int Processor::pop()
{
    int val = getMemAtSegOff(W, core.ss, core.sp);

    core.sp += 2;
    return val;
}

//
// Push word onto stack.
//
void Processor::push(int val)
{
    core.sp -= 2;
    setMemAtSegOff(W, core.ss, core.sp, val);
}

//
// Software interrupt: push FLAGS, CS, IP; jump to vector.
//
void Processor::callInt(int type)
{
    core.flags.w &= ~unpredictable_flags;
    if (machine.is_syscall(type)) {
        // Intercept syscalls.
        machine.process_syscall(type);
        return;
    }

    // Fetch interrupt vector.
    Word offset = getMem(W, type * 4);
    Word seg    = getMem(W, type * 4 + 2);

    // Take interrupt: push FLAGS first (with IF/TF as-is), then clear them.
    push(core.flags.w);
    core.flags.f.i = 0;
    core.flags.f.t = 0;
    push(core.cs);
    push(core.ip);
    core.ip = offset;
    core.cs = seg;
}

//
// ALU helpers (set CF, AF, OF, PF, ZF, SF).
//
int Processor::add(int width, int dst, int src)
{
    int res        = (dst + src) & MASK[width];
    core.flags.f.c = res < dst;
    core.flags.f.a = ((res ^ dst ^ src) & 0x10) != 0;
    core.flags.f.o = (shift((dst ^ src ^ -1) & (dst ^ res), 12 - BITS[width]) & 0x800) != 0;
    update_flags_zsp(width, res);
    return res;
}

int Processor::adc(int width, int dst, int src)
{
    int carry      = core.flags.f.c;
    int res        = (dst + src + carry) & MASK[width];
    core.flags.f.c = carry ? (res <= dst) : (res < dst);
    core.flags.f.a = ((res ^ dst ^ src) & 0x10) != 0;
    core.flags.f.o = (shift((dst ^ src ^ -1) & (dst ^ res), 12 - BITS[width]) & 0x800) != 0;
    update_flags_zsp(width, res);
    return res;
}

int Processor::sub(int width, int dst, int src)
{
    int res        = (dst - src) & MASK[width];
    core.flags.f.c = dst < src;
    core.flags.f.a = ((res ^ dst ^ src) & 0x10) != 0;
    core.flags.f.o = (shift((dst ^ src) & (dst ^ res), 12 - BITS[width]) & 0x800) != 0;
    update_flags_zsp(width, res);
    return res;
}

int Processor::sbb(int width, int dst, int src)
{
    int carry      = core.flags.f.c;
    int res        = (dst - src - carry) & MASK[width];
    core.flags.f.c = carry ? (dst <= src) : (dst < src);
    core.flags.f.a = ((res ^ dst ^ src) & 0x10) != 0;
    core.flags.f.o = (shift((dst ^ src) & (dst ^ res), 12 - BITS[width]) & 0x800) != 0;
    update_flags_zsp(width, res);
    return res;
}

int Processor::inc(int width, int dst)
{
    int res        = (dst + 1) & MASK[width];
    core.flags.f.a = ((res ^ dst ^ 1) & 0x10) != 0;
    core.flags.f.o = res == static_cast<int>(SIGN[width]);
    update_flags_zsp(width, res);
    return res;
}

int Processor::dec(int width, int dst)
{
    int res        = (dst - 1) & MASK[width];
    core.flags.f.a = ((res ^ dst ^ 1) & 0x10) != 0;
    core.flags.f.o = res == static_cast<int>(SIGN[width]) - 1;
    update_flags_zsp(width, res);
    return res;
}

void Processor::logic(int width, int res)
{
    core.flags.f.c = 0;
    core.flags.f.o = 0;
    core.flags.f.a = 0; // undefined per Intel; real 8086 clears it
    update_flags_zsp(width, res);
}

int Processor::signconv(int width, int x)
{
    if (width == B)
        return static_cast<signed char>(x);
    return static_cast<short>(x);
}

bool Processor::msb(int width, int x)
{
    return (static_cast<unsigned>(x) & SIGN[width]) == SIGN[width];
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
void Processor::step()
{
    // Consume segment override and REP prefix bytes; set default segment and repetition mode.
    os               = core.ds;
    segment_override = false;
    rep              = 0;
    opcode           = {};
    plen             = 0;
    for (;;) {
        unsigned addr = pc86_linear_addr(core.cs, core.ip);
        Byte prefix   = machine.mem_fetch_byte(addr);
        switch (prefix) {
        case 0x26:
            segment_override = true;
            os               = core.es;
            break;
        case 0x2e:
            segment_override = true;
            os               = core.cs;
            break;
        case 0x36:
            segment_override = true;
            os               = core.ss;
            break;
        case 0x3e:
            segment_override = true;
            os               = core.ds;
            break;
        case 0xf2:
            rep = 2;
            break;
        case 0xf3:
            rep = 1;
            break;
        default:
            goto done_prefix;
        }
        opcode.push_back(prefix);
        plen++;
        core.ip = (core.ip + 1) & 0xffff;
    }
done_prefix:

    // Prefetch 6 bytes at CS:IP for decode.
    for (int i = 0; i < 6; ++i) {
        opcode.push_back(machine.mem_fetch_byte(pc86_linear_addr(core.cs, (core.ip + i) & 0xffff)));
    }
    unpredictable_flags = 0;

    // Show instruction: address, opcode and mnemonics.
    machine.trace_instruction();

    op      = opcode[plen];
    d       = (op >> 1) & 1;
    w       = op & 1;
    core.ip = (core.ip + 1) & 0xffff;

    // For REP string instructions: full REP loop in one step (match legacy cycle_opcode).
    if (rep != 0 && (op == 0xa4 || op == 0xa5 || op == 0xa6 || op == 0xa7 || op == 0xaa ||
                     op == 0xab || op == 0xac || op == 0xad || op == 0xae || op == 0xaf)) {
        // REPE/REPZ (rep==1) and REPNE/REPNZ (rep==2) only check ZF for CMPS/SCAS (A6,A7,AE,AF).
        // For MOVS/LODS/STOS, repeat until CX==0 regardless of ZF.
        bool check_zf = (op == 0xa6 || op == 0xa7 || op == 0xae || op == 0xaf);
        do {
            if (core.cx == 0) // CX
                break;
            if (rep)
                core.cx -= 1;
            exe_one();
            if (rep && check_zf && ((rep == 1 && !core.flags.f.z) || (rep == 2 && core.flags.f.z)))
                break;
        } while (rep != 0);
    } else {
        exe_one();
    }
    core.flags.w &= ~unpredictable_flags;

    // Show changed registers.
    machine.trace_registers();
}

//
// Decode op, d, w and optional ModR/M; then execute the matching 8086 instruction.
//
void Processor::exe_one()
{
    int dst, src, res;
    const int AX = 0; // accumulator index for getReg/setReg

    switch (op) {
    // --- MOV: register/memory and immediate, accum, segment ---
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
        decode();
        if (d == 0) {
            src = getReg(w, reg);
            setRM(w, mod, rm, src);
        } else {
            src = getRM(w, mod, rm);
            setReg(w, reg, src);
        }
        break;

    // MOV reg/mem, immediate (real 8086 executes for all reg values, e.g. ModR/M 3E)
    case 0xc6:
    case 0xc7:
        decode();
        src = getMem(w);
        setRM(w, mod, rm, src);
        break;

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
    case 0xbf:
        w   = (op >> 3) & 1;
        reg = op & 0b111;
        src = getMem(w);
        setReg(w, reg, src);
        break;

    // MOV accum, mem and MOV mem, accum
    case 0xa0:
    case 0xa1:
    case 0xa2:
    case 0xa3:
        dst = getMem(W);
        if (d == 0) {
            src = getMemAtSegOff(w, os, dst);
            setReg(w, AX, src);
        } else {
            src = getReg(w, AX);
            setMemAtSegOff(w, os, dst, src);
        }
        break;

    // MOV reg/mem, segreg and MOV segreg, reg/mem
    case 0x8c:
    case 0x8e:
        decode();
        if (d == 0) {
            setRM(W, mod, rm, static_cast<int>(getSegReg(reg)));
        } else {
            setSegReg(reg, static_cast<Word>(getRM(W, mod, rm)));
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
        // 8086 PUSH SP pushes the value SP will have after the push (SP-2), not pre-decrement SP
        src = (reg == 4) ? (static_cast<int>(core.sp) - 2) & 0xffff : getReg(W, reg);
        push(src);
        break;

    // PUSH segment register
    case 0x06:
    case 0x0e:
    case 0x16:
    case 0x1e:
        reg = (op >> 3) & 0b111;
        push(static_cast<int>(getSegReg(reg)));
        break;

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
        setReg(W, reg, pop());
        break;

    // POP segment register
    case 0x07:
    case 0x0f:
    case 0x17:
    case 0x1f:
        reg = (op >> 3) & 0b111;
        setSegReg(reg, static_cast<Word>(pop()));
        break;

    // XCHG reg, reg/mem
    case 0x86:
    case 0x87:
        decode();
        dst = getReg(w, reg);
        if (mod == 0b11) {
            src = getRM(w, mod, rm);
            setReg(w, reg, src);
            setRM(w, mod, rm, dst);
        } else {
            // Compute EA once for memory so store uses same address as load.
            unsigned addr = getEA(mod, rm);
            src           = getMem(w, addr);
            setReg(w, reg, src);
            setMem(w, addr, dst);
        }
        break;

    // XCHG AX, reg
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
        reg     = op & 0b111;
        dst     = core.ax;
        src     = getReg(W, reg);
        core.ax = src;
        setReg(W, reg, dst);
        break;

    // SALC: Set AL from Carry (undocumented 8086)
    case 0xd6:
        set_al(core.flags.f.c ? 0xff : 0);
        break;

    // XLAT
    case 0xd7:
        set_al(getMem(B, pc86_linear_addr(os, core.bx + get_al())));
        break;

    // IN accum, port (immed and DX)
    case 0xe4:
    case 0xe5:
        src = getMem(B);
        if (w == B)
            res = machine.port_in_byte(src);
        else
            res = machine.port_in_word(src);
        setReg(w, AX, res);
        break;
    case 0xec:
    case 0xed:
        src = core.dx;
        if (w == B)
            res = machine.port_in_byte(src);
        else
            res = machine.port_in_word(src);
        setReg(w, AX, res);
        break;

    // OUT port, accum
    case 0xe6:
    case 0xe7:
        src = getMem(B);
        res = getReg(w, AX);
        if (w == B)
            machine.port_out_byte(src, res);
        else
            machine.port_out_word(src, res);
        break;
    case 0xee:
    case 0xef:
        src = core.dx;
        res = getReg(w, AX);
        if (w == B)
            machine.port_out_byte(src, res);
        else
            machine.port_out_word(src, res);
        break;

    // LEA
    case 0x8d:
        decode();
        setReg(w, reg, (getEA(mod, rm) - (static_cast<unsigned>(os) << 4)) & 0xffff);
        break;

    // LDS (always loads 16-bit offset into reg)
    case 0xc5:
        decode();
        src = getEA(mod, rm);
        setReg(W, reg, getMem(W, src));
        core.ds = getMem(W, src + 2);
        break;

    // LES (always loads 16-bit offset into reg)
    case 0xc4:
        decode();
        src = getEA(mod, rm);
        setReg(W, reg, getMem(W, src));
        core.es = getMem(W, src + 2);
        break;

    // LAHF
    case 0x9f:
        set_ah(core.flags.w);
        break;

    // SAHF
    case 0x9e:
        set_flags((core.flags.w & 0xff00) | get_ah());
        break;

    // PUSHF / POPF
    case 0x9c:
        push(core.flags.w);
        break;
    case 0x9d:
        set_flags(pop());
        break;

    // ADD reg/mem, reg and ADD reg, reg/mem
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
            res = add(w, dst, src);
            setRM(w, mod, rm, res);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
            res = add(w, dst, src);
            setReg(w, reg, res);
        }
        break;

    // ADD accum, immediate
    case 0x04:
    case 0x05:
        dst = getReg(w, AX);
        src = getMem(w);
        setReg(w, AX, add(w, dst, src));
        break;

    // ADC (same pattern)
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
            res = adc(w, dst, src);
            setRM(w, mod, rm, res);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
            res = adc(w, dst, src);
            setReg(w, reg, res);
        }
        break;
    case 0x14:
    case 0x15:
        dst = getReg(w, AX);
        src = getMem(w);
        setReg(w, AX, adc(w, dst, src));
        break;

    // INC general register
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
        reg = op & 0b111;
        setReg(W, reg, inc(W, getReg(W, reg)));
        break;

    // AAA: ASCII adjust for addition
    case 0x37: {
        // Overflow, parity, sign and zero are unpredictable
        unpredictable_flags = OF_MASK | PF_MASK | SF_MASK | ZF_MASK;

        Byte al = get_al();
        if (core.flags.f.a || (al & 0xf) > 9) {
            al += 6;
            set_ah(get_ah() + 1);
            core.flags.f.c = 1;
            core.flags.f.a = 1;
        } else {
            core.flags.f.c = 0;
            core.flags.f.a = 0;
        }
        al &= 0xf;
        set_al(al);
        core.flags.f.z = (al == 0);
        break;
    }

    // DAA: Decimal adjust for addition
    case 0x27: {
        // Overflow is unpredictable
        unpredictable_flags = OF_MASK;

        Byte al        = get_al();
        bool update_lo = core.flags.f.a || (al & 0xf) > 9;
        bool update_hi = core.flags.f.c || (al > 0x9F) || (al >= 0x9A && al < 0x9F);
        if (update_lo) {
            al += 6;
            core.flags.f.a = 1;
        } else {
            core.flags.f.a = 0;
        }
        if (update_hi) {
            al += 0x60;
            core.flags.f.c = 1;
        } else if (!update_lo) {
            core.flags.f.c = 0;
        }
        set_al(al);
        update_flags_zsp(B, get_al());
        break;
    }

    // --- SUB, SBB, CMP, INC, DEC: arithmetic and compare ---
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
            res = sub(w, dst, src);
            setRM(w, mod, rm, res);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
            res = sub(w, dst, src);
            setReg(w, reg, res);
        }
        break;
    case 0x2c:
    case 0x2d:
        dst = getReg(w, AX);
        src = getMem(w);
        setReg(w, AX, sub(w, dst, src));
        break;

    // SBB
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
            res = sbb(w, dst, src);
            setRM(w, mod, rm, res);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
            res = sbb(w, dst, src);
            setReg(w, reg, res);
        }
        break;
    case 0x1c:
    case 0x1d:
        dst = getReg(w, AX);
        src = getMem(w);
        setReg(w, AX, sbb(w, dst, src));
        break;

    // DEC general register
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
        reg = op & 0b111;
        setReg(W, reg, dec(W, getReg(W, reg)));
        break;

    // CMP
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
        }
        sub(w, dst, src);
        break;
    case 0x3c:
    case 0x3d:
        dst = getReg(w, AX);
        src = getMem(w);
        sub(w, dst, src);
        break;

    // AAS: ASCII adjust for subtraction
    case 0x3f: {
        // Overflow, parity, sign and zero are unpredictable
        unpredictable_flags = OF_MASK | PF_MASK | SF_MASK | ZF_MASK;

        Byte al = get_al();
        if (core.flags.f.a || (al & 0xf) > 9) {
            al -= 6;
            set_ah(get_ah() - 1);
            core.flags.f.c = 1;
            core.flags.f.a = 1;
        } else {
            core.flags.f.c = 0;
            core.flags.f.a = 0;
        }
        al &= 0xf;
        set_al(al);
        core.flags.f.z = (al == 0);
        break;
    }

    // DAS: Decimal adjust for subtraction
    case 0x2f: {
        // Overflow is unpredictable
        unpredictable_flags = OF_MASK;

        Byte al        = get_al();
        bool update_lo = core.flags.f.a || (al & 0xf) > 9;
        bool update_hi = core.flags.f.c || (al > 0x9F) || (al >= 0x9A && al <= 0x9C);
        if (update_lo) {
            al -= 6;
            core.flags.f.a = 1;
        } else {
            core.flags.f.a = 0;
        }
        if (update_hi) {
            al -= 0x60;
            core.flags.f.c = 1;
        } else if (!update_lo) {
            core.flags.f.c = 0;
        }
        set_al(al);
        update_flags_zsp(B, al);
        break;
    }

    // AAM: ASCII adjust for multiply
    case 0xd4:
        // Overflow is unpredictable
        unpredictable_flags = OF_MASK;

        src = getMem(B);
        core.flags.f.c = 0;
        core.flags.f.a = 0;
        if (src == 0) {
            update_flags_zsp(B, 0);
            callInt(0);
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

        src          = getMem(B);
        int ah_orig  = get_ah();
        int al_orig  = get_al();
        int sum      = al_orig + (Byte)(ah_orig * src);
        int half_sum = (al_orig & 0x0F) + ((ah_orig * src) & 0x0F);
        set_al(sum);
        set_ah(0);
        update_flags_zsp(B, get_al());
        core.flags.f.c = (sum >= 256);
        core.flags.f.a = (half_sum > 15);
        core.flags.f.t = 0;
        break;
    }

    // CBW
    case 0x98:
        if (get_al() & 0x80)
            core.ax |= 0xff00;
        else
            core.ax &= 0x00ff;
        break;

    // CWD
    case 0x99:
        if (core.ax & 0x8000)
            core.dx = 0xffff;
        else
            core.dx = 0;
        break;

    // AND, OR, XOR, TEST (logic)
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
            res = dst & src;
            logic(w, res);
            setRM(w, mod, rm, res);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
            res = dst & src;
            logic(w, res);
            setReg(w, reg, res);
        }
        break;
    case 0x24:
    case 0x25:
        dst = getReg(w, AX);
        src = getMem(w);
        logic(w, dst & src);
        setReg(w, AX, dst & src);
        break;
    case 0x08:
    case 0x09:
    case 0x0a:
    case 0x0b:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
            res = dst | src;
            logic(w, res);
            setRM(w, mod, rm, res);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
            res = dst | src;
            logic(w, res);
            setReg(w, reg, res);
        }
        break;
    case 0x0c:
    case 0x0d:
        dst = getReg(w, AX);
        src = getMem(w);
        logic(w, dst | src);
        setReg(w, AX, dst | src);
        break;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
        decode();
        if (d == 0) {
            dst = getRM(w, mod, rm);
            src = getReg(w, reg);
            res = dst ^ src;
            logic(w, res);
            setRM(w, mod, rm, res);
        } else {
            dst = getReg(w, reg);
            src = getRM(w, mod, rm);
            res = dst ^ src;
            logic(w, res);
            setReg(w, reg, res);
        }
        break;
    case 0x34:
    case 0x35:
        dst = getReg(w, AX);
        src = getMem(w);
        logic(w, dst ^ src);
        setReg(w, AX, dst ^ src);
        break;
    case 0x84:
    case 0x85:
        decode();
        logic(w, getRM(w, mod, rm) & getReg(w, reg));
        break;
    case 0xa8:
    case 0xa9:
        logic(w, getReg(w, AX) & getMem(w));
        break;

    // String ops (one iteration each)
    case 0xa4: // MOVS
    case 0xa5:
        src = getMemAtSegOff(w, os, core.si);
        setMemAtSegOff(w, core.es, core.di, src);
        core.si = (core.si + (core.flags.f.d ? -1 : 1) * (1 + w)) & 0xffff;
        core.di = (core.di + (core.flags.f.d ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xa6:
    case 0xa7:
        dst = getMemAtSegOff(w, core.es, core.di);
        src = getMemAtSegOff(w, os, core.si);
        sub(w, src, dst);
        core.si = (core.si + (core.flags.f.d ? -1 : 1) * (1 + w)) & 0xffff;
        core.di = (core.di + (core.flags.f.d ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xae:
    case 0xaf:
        dst = getMemAtSegOff(w, core.es, core.di);
        src = getReg(w, AX);
        sub(w, src, dst);
        core.di = (core.di + (core.flags.f.d ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xac:
    case 0xad:
        src = getMemAtSegOff(w, os, core.si);
        setReg(w, AX, src);
        core.si = (core.si + (core.flags.f.d ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xaa:
    case 0xab:
        setMemAtSegOff(w, core.es, core.di, getReg(w, AX));
        core.di = (core.di + (core.flags.f.d ? -1 : 1) * (1 + w)) & 0xffff;
        break;

    // --- CALL, RET, JMP: transfer and conditional jumps ---
    case 0xe8:
        dst = signconv(W, getMem(W));
        push(static_cast<int>(core.ip));
        core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x9a:
        dst = getMem(W);
        src = getMem(W);
        push(static_cast<int>(core.cs));
        push(static_cast<int>(core.ip));
        core.ip = static_cast<Word>(dst & 0xffff);
        core.cs = static_cast<Word>(src & 0xffff);
        break;
    case 0xc0: // 8086 undocumented: same as C2 (RET imm16)
    case 0xc2:
        src     = getMem(W);
        core.ip = static_cast<Word>(pop() & 0xffff);
        core.sp = (core.sp + src) & 0xffff;
        break;
    case 0xc1: // 8086 undocumented: same as C3 (RET near)
    case 0xc3:
        core.ip = static_cast<Word>(pop() & 0xffff);
        break;
    case 0xc9: // 8086 undocumented: same as CB (RETF)
    case 0xcb:
        core.ip = static_cast<Word>(pop() & 0xffff);
        core.cs = static_cast<Word>(pop() & 0xffff);
        break;
    case 0xc8: // 8086: same as CA (RETF imm16); ENTER is 186+
    case 0xca:
        src     = getMem(W);
        core.ip = static_cast<Word>(pop() & 0xffff);
        core.cs = static_cast<Word>(pop() & 0xffff);
        core.sp = (core.sp + src) & 0xffff;
        break;
    case 0xe9:
        dst     = signconv(W, getMem(W));
        core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0xeb:
        dst     = signconv(B, getMem(B));
        core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0xea:
        dst     = getMem(W);
        src     = getMem(W);
        core.ip = static_cast<Word>(dst & 0xffff);
        core.cs = static_cast<Word>(src & 0xffff);
        break;

    // Conditional jumps (Jcc)
    case 0x70: // JO - Overflow
    case 0x60: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.o)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x71: // JNO - No overflow
    case 0x61: // Undocumented
        dst = signconv(B, getMem(B));
        if (!core.flags.f.o)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x72: // JB, JC, JNAE - Below / Carry
    case 0x62: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.c)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x73: // JNB, JNC, JAE - Above or equal / No carry
    case 0x63: // Undocumented
        dst = signconv(B, getMem(B));
        if (!core.flags.f.c)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x74: // JE, JZ - Equal / Zero
    case 0x64: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.z)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x75: // JNE, JNZ - Not equal / Not zero
    case 0x65: // Undocumented
        dst = signconv(B, getMem(B));
        if (!core.flags.f.z)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x76: // JBE, JNA - Below or equal
    case 0x66: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.c || core.flags.f.z)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x77: // JA, JNBE - Above
    case 0x67: // Undocumented
        dst = signconv(B, getMem(B));
        if (!(core.flags.f.c || core.flags.f.z))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x78: // JS - Sign
    case 0x68: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.s)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x79: // JNS - Not sign
    case 0x69: // Undocumented
        dst = signconv(B, getMem(B));
        if (!core.flags.f.s)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7a: // JP, JPE - Parity even
    case 0x6a: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.p)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7b: // JNP, JPO - Parity odd
    case 0x6b: // Undocumented
        dst = signconv(B, getMem(B));
        if (!core.flags.f.p)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7c: // JL, JNGE - Less (signed)
    case 0x6c: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.s != core.flags.f.o)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7d: // JGE, JNL - Greater or equal (signed)
    case 0x6d: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.s == core.flags.f.o)
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7e: // JLE, JNG - Less or equal (signed)
    case 0x6e: // Undocumented
        dst = signconv(B, getMem(B));
        if (core.flags.f.z || (core.flags.f.s != core.flags.f.o))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7f: // JG, JNLE - Greater (signed)
    case 0x6f: // Undocumented
        dst = signconv(B, getMem(B));
        if (!core.flags.f.z && (core.flags.f.s == core.flags.f.o))
            core.ip = (core.ip + dst) & 0xffff;
        break;

    // LOOP, LOOPE, LOOPNE, JCXZ
    case 0xe2:
        dst = signconv(B, getMem(B));
        core.cx -= 1;
        if (core.cx != 0)
            core.ip += dst;
        break;
    case 0xe1:
        dst = signconv(B, getMem(B));
        core.cx -= 1;
        if (core.cx != 0 && core.flags.f.z)
            core.ip += dst;
        break;
    case 0xe0:
        dst = signconv(B, getMem(B));
        core.cx -= 1;
        if (core.cx != 0 && !core.flags.f.z)
            core.ip += dst;
        break;
    case 0xe3:
        dst = signconv(B, getMem(B));
        if (core.cx == 0)
            core.ip += dst;
        break;

    // INT3, INT, INTO: software interrupt
    case 0xcc:
        callInt(3);
        break;
    case 0xcd:
        callInt(getMem(B));
        break;
    case 0xce:
        if (core.flags.f.o) {
            callInt(4);
        }
        break;

    // IRET: pop IP, CS, FLAGS
    case 0xcf:
        core.ip = pop();
        core.cs = pop();
        set_flags(pop());
        break;

    // Flag ops
    case 0xf8:
        core.flags.f.c = 0;
        break;
    case 0xf5:
        core.flags.f.c = !core.flags.f.c;
        break;
    case 0xf9:
        core.flags.f.c = 1;
        break;
    case 0xfc:
        core.flags.f.d = 0;
        break;
    case 0xfd:
        core.flags.f.d = 1;
        break;
    case 0xfa:
        core.flags.f.i = 0;
        break;
    case 0xfb:
        core.flags.f.i = 1;
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

    // LOCK
    case 0xf0:
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
        dst = getRM(w, mod, rm);
        src = getMem(B);
        if (op == 0x81)
            src |= getMem(B) << 8;
        else if (op == 0x83 && (src & static_cast<int>(SIGN[B])) != 0)
            src |= 0xff00;
        switch (reg) {
        case 0:
            res = add(w, dst, src);
            setRM(w, mod, rm, res);
            break;
        case 1:
            if (op == 0x80 || op == 0x81 || op == 0x82 || op == 0x83) {
                res = dst | src;
                logic(w, res);
                setRM(w, mod, rm, res);
            }
            break;
        case 2:
            res = adc(w, dst, src);
            setRM(w, mod, rm, res);
            break;
        case 3:
            res = sbb(w, dst, src);
            setRM(w, mod, rm, res);
            break;
        case 4:
            if (op == 0x80 || op == 0x81 || op == 0x82 || op == 0x83) {
                res = dst & src;
                logic(w, res);
                setRM(w, mod, rm, res);
            }
            break;
        case 5:
            res = sub(w, dst, src);
            setRM(w, mod, rm, res);
            break;
        case 6:
            if (op == 0x80 || op == 0x81 || op == 0x82 || op == 0x83) {
                res = dst ^ src;
                logic(w, res);
                setRM(w, mod, rm, res);
            }
            break;
        case 7:
            sub(w, dst, src);
            break;
        default:
            break;
        }
        break;
    }

    // POP reg/mem (real 8086 executes for all reg values, e.g. ModR/M 57)
    case 0x8f:
        decode();
        setRM(W, mod, rm, pop());
        break;

    // Shift/rotate group D0-D3
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3: {
        decode();
        dst = getRM(w, mod, rm);
        if (op == 0xd0 || op == 0xd1)
            src = 1;
        else {
            // 8086 RCL/RCR only: count mod 9 (byte) or mod 17 (word) - rotate through carry
            if (reg == 2 || reg == 3) {
                int n = (w == B) ? 9 : 17;
                src   = get_cl() % n;
            }
            // 8086 ROL/ROR: count mod 8 (byte) or mod 16 (word)
            else if (reg == 0 || reg == 1) {
                int n = (w == B) ? 8 : 16;
                src   = get_cl() % n;
            }
            // 8086 shifts (SHR/SAR/SHL): no masking - full CL; count >= operand bits yields 0
            else
                src = get_cl();
        }
        bool temp_cf;
        switch (reg) {
        case 0: // ROL
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = msb(w, dst);
                dst     = ((dst << 1) | (temp_cf ? 1 : 0)) & MASK[w];
            }
            core.flags.f.c = (dst & 1) != 0;
            core.flags.f.o = msb(w, dst) != core.flags.f.c; // 8086: same for count>=1
            break;
        case 1: // ROR
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = (dst & 1) != 0;
                dst     = ((dst >> 1) | (temp_cf ? static_cast<int>(SIGN[w]) : 0)) & MASK[w];
            }
            core.flags.f.c = msb(w, dst);
            core.flags.f.o = msb(w, dst) != msb(w, dst << 1); // 8086: same for count>=1
            break;
        case 2: // RCL
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf        = msb(w, dst);
                dst            = ((dst << 1) | core.flags.f.c) & MASK[w];
                core.flags.f.c = temp_cf;
            }
            core.flags.f.o = msb(w, dst) != core.flags.f.c;
            break;
        case 3: // RCR
            if (src == 1)
                core.flags.f.o = msb(w, dst) != core.flags.f.c;
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = (dst & 1) != 0;
                dst     = ((dst >> 1) | (core.flags.f.c ? static_cast<int>(SIGN[w]) : 0)) & MASK[w];
                core.flags.f.c = temp_cf;
            }
            if (src != 1) {
                // The overflow flag is defined only for the single-rotate forms
                // of the instructions (second operand := 1).
                // It is undefined in all other cases.
                unpredictable_flags = OF_MASK;
            }
            break;
        case 4: { // SAL/SHL
            int orig_dst   = dst;
            int shl_thresh = (w == B) ? 8 : 16;
            if (src >= shl_thresh) {
                // CF = last bit shifted out; when src > thresh, last shift shifts 0 so CF=0
                int last_bit = 0;
                if (src == shl_thresh) {
                    int eff_shift = shl_thresh - 1;
                    last_bit =
                        (static_cast<unsigned>(orig_dst) << eff_shift) & static_cast<unsigned>(MASK[w]) &
                        static_cast<unsigned>(SIGN[w]);
                }
                core.flags.f.c = last_bit != 0;
                core.flags.f.o = core.flags.f.c;
                dst            = 0;
                core.flags.f.a = 0;
                update_flags_zsp(w, dst);
            } else {
                for (int cnt = 0; cnt < src; ++cnt) {
                    core.flags.f.c = (dst & static_cast<int>(SIGN[w])) != 0;
                    dst            = (dst << 1) & MASK[w];
                }
                core.flags.f.o = ((dst & static_cast<int>(SIGN[w])) != 0) != core.flags.f.c;

                // AF undefined per Intel; batch5/batch6 expect different values - mark unpredictable
                unpredictable_flags = AF_MASK;

                if (src > 0)
                    update_flags_zsp(w, dst);
            }
            break;
        }
        case 6: // SETMO/SETMOC: set to all ones; when count 0 (D2/D3), no op
            if (op == 0xd0 || op == 0xd1 || src >= 1) {
                dst            = static_cast<int>(MASK[w]);
                core.flags.f.c = 0;
                core.flags.f.o = 0;
                core.flags.f.a = 0;
                update_flags_zsp(w, dst);
            }
            break;
        case 5: { // SHR
            int shr_thresh = (w == B) ? 8 : 16;
            if (src >= shr_thresh) {
                // CF = last bit shifted out; when src > thresh all bits gone so 0
                core.flags.f.c =
                    (src == shr_thresh) ? ((static_cast<unsigned>(dst) >> (src - 1)) & 1) : 0;
                dst = 0;
                core.flags.f.o = 0;
                core.flags.f.a = 0;
                update_flags_zsp(w, dst);
            } else {
                if (src == 1)
                    core.flags.f.o = (dst & static_cast<int>(SIGN[w])) != 0;
                else if (src > 1)
                    core.flags.f.o = 0;
                for (int cnt = 0; cnt < src; ++cnt) {
                    core.flags.f.c = (dst & 1) != 0;
                    dst            = (dst >> 1) & MASK[w];
                }
                if (src > 0) {
                    core.flags.f.a = 0;
                    update_flags_zsp(w, dst);
                }
            }
            break;
        }
        case 7: // SAR - 8086 uses original sign bit for all shift-ins
            if (src == 1)
                core.flags.f.o = 0;
            if (src > 0) {
                int signbit     = (dst & static_cast<int>(SIGN[w]));
                int sign_thresh = (w == B) ? 8 : 16;
                if (src >= sign_thresh) {
                    core.flags.f.c = signbit != 0;
                    core.flags.f.o = 0;
                    dst            = signbit ? static_cast<int>(MASK[w]) : 0;
                } else {
                    for (int cnt = 0; cnt < src; ++cnt) {
                        core.flags.f.c = (dst & 1) != 0;
                        dst            = ((dst >> 1) | signbit) & MASK[w];
                    }
                    core.flags.f.o = 0;
                }
                core.flags.f.a = 0;
                update_flags_zsp(w, dst);
            }
            break;
        default:
            break;
        }
        setRM(w, mod, rm, dst);
        break;
    }

    // TEST imm, NOT, NEG, MUL, IMUL, DIV, IDIV
    case 0xf6:
    case 0xf7: {
        decode();
        src = getRM(w, mod, rm);
        switch (reg) {
        case 0:
        case 1: {
            // TEST r/m, imm (reg 0 and 1 on real 8086). Immediate follows ModR/M and any
            // displacement.
            int imm_off = 2;
            if (mod == 0b01)
                imm_off = 3;
            else if (mod == 0b10 || (mod == 0b00 && rm == 0b110))
                imm_off = 4;
            int imm;
            if (op == 0xf7) {
                imm = opcode[plen + imm_off] | (opcode[plen + imm_off + 1] << 8);
                core.ip += 2;
            } else {
                imm = opcode[plen + imm_off];
                core.ip += 1;
            }
            logic(w, (imm & src));
            break;
        }
        case 2:
            setRM(w, mod, rm, ~src);
            break;
        case 3: {
            dst            = sub(w, 0, src);
            core.flags.f.c = dst != 0;
            setRM(w, mod, rm, dst);
            break;
        }
        case 4: // MUL
            if (w == B) {
                res = (Word)(get_al() * src);
                if (rep != 0) {
                    // 8086 REP/REPNE with MUL negates product
                    res = (Word)-res;
                }
                core.ax        = res;
                core.flags.f.c = (res >> 8) != 0;
                core.flags.f.o = (res >> 8) != 0;
                core.flags.f.z = ((res >> 8) == 0);
                core.flags.f.p = PARITY[(Byte)(res >> 8)];
                core.flags.f.s = (int16_t)core.ax < 0;
            } else {
                uint32_t lres = (uint32_t)core.ax * (Word)src;
                if (rep != 0) {
                    lres = -lres;
                }
                core.ax        = lres;
                core.dx        = lres >> 16;
                core.flags.f.c = (lres >> 16) != 0;
                core.flags.f.o = (lres >> 16) != 0;
                core.flags.f.z = (core.dx == 0 && core.ax == 0);
                core.flags.f.s = (int16_t)core.dx < 0;

                // Word MUL: PF undefined per reference; mask so tests do not compare it.
                unpredictable_flags = PF_MASK;
            }
            core.flags.f.a = 0;
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
                core.ax            = res;
                bool byte_overflow = ((int16_t)res != (int8_t)(res & 0xFF));
                core.flags.f.c     = byte_overflow;
                core.flags.f.o     = byte_overflow;
            } else {
                uint32_t lres = (long)signconv(W, core.ax) * (long)signconv(W, src);
                if (rep != 0) {
                    lres = -lres;
                }
                core.ax            = lres;
                core.dx            = lres >> 16;
                bool word_overflow = ((int32_t)lres != (int16_t)core.ax);
                core.flags.f.c     = word_overflow;
                core.flags.f.o     = word_overflow;
            }
            break;
        case 6: // DIV (unsigned)
            // In 8086 documentation, DIV leaves CF, OF, SF, ZF, PF, AF undefined.
            // Flags DF/IF/TF stay unchanged.
            unpredictable_flags = CF_MASK | OF_MASK | SF_MASK | ZF_MASK | PF_MASK | AF_MASK;

            if (w == B) {
                Byte divb = src;
                if (divb == 0) {
                    callInt(0);
                    break;
                }
                Word quo = core.ax / divb;
                Byte rem = core.ax % divb;
                if (quo > 0xFF) {
                    callInt(0);
                    break;
                }
                set_al(quo);
                set_ah(rem);
            } else {
                Word divw = src;
                if (divw == 0) {
                    callInt(0);
                    break;
                }
                unsigned ldst = (core.dx << 16) | core.ax;
                unsigned quo  = ldst / divw;
                unsigned rem  = ldst % divw;
                if (quo > 0xFFFF) {
                    callInt(0);
                    break;
                }
                core.ax = quo;
                core.dx = rem;
            }
            break;
        case 7: // IDIV (signed integer division)
            // According to the 8086 manual, the arithmetic flags are left
            // in an undefined state: CF, PF, AF, ZF, SF, OF.
            unpredictable_flags = CF_MASK | PF_MASK | AF_MASK | ZF_MASK | SF_MASK | OF_MASK;

            if (w == B) {
                // Dividend is a signed 16-bit value in AX.
                // Divisor is a signed 8-bit value (register or memory).
                src = (int8_t)src;
                if (src == 0) {
                    // Divide by zero
                    callInt(0);
                    break;
                }
                dst = (int16_t)core.ax;
                res = dst / src;
                // 8086/8088: min negative quotient is -127, not -128 (Q68599); -128 triggers INT 0.
                if (res > 0x7f || res < -0x7f) {
                    // Quotient overflow (byte).
                    callInt(0);
                    break;
                }
                if (rep != 0) {
                    // 8086 REP/REPNE with IDIV negates quotient
                    res = -res;
                }
                set_al(res);
                set_ah(dst % src);
            } else {
                // Dividend is a signed 32-bit value in DX:AX.
                // Divisor is a signed 16-bit value (register or memory).
                src = (int16_t)src;
                if (src == 0) {
                    // Divide by zero
                    callInt(0);
                    break;
                }
                dst          = (int32_t)((core.dx << 16) | core.ax);
                int64_t lres = (int64_t)dst / src;
                // 8086/8088: min negative quotient is -32767, not -32768 (Q68599); -32768 triggers INT 0.
                if (lres > 0x7fff || lres < -0x7fff) {
                    // Quotient overflow (word).
                    callInt(0);
                    break;
                }
                if (rep != 0) {
                    // 8086 REP/REPNE with IDIV negates quotient
                    lres = -lres;
                }
                core.ax = lres;
                core.dx = dst % src;
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
            push(core.ip);
            core.ip = src;
            break;
        case 3: {
            unsigned addr = getEA(mod, rm);
            push(core.cs);
            push(core.ip);
            core.ip = getMem(W, addr);
            core.cs = getMem(W, addr + 2);
            break;
        }
        case 4:
            core.ip = src;
            break;
        case 5: {
            unsigned addr = getEA(mod, rm);
            core.ip       = getMem(W, addr);
            core.cs       = getMem(W, addr + 2);
            break;
        }
        case 6:
        case 7:
            // 8086 PUSH r/m (FF/6 and FF/7). PUSH SP (mod=11, rm=4) pushes SP-2, not SP.
            if (mod == 0b11 && rm == 4)
                src = core.sp - 2;
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
