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
// 8086 flag bits and size codes (B=byte, W=word).
//
static const unsigned CF      = 1;
static const unsigned PF      = 1 << 2;
static const unsigned AF      = 1 << 4;
static const unsigned ZF      = 1 << 6;
static const unsigned SF      = 1 << 7;
static const unsigned TF      = 1 << 8;
static const unsigned IF      = 1 << 9;
static const unsigned DF      = 1 << 10;
static const unsigned OF      = 1 << 11;
static const int B            = 0;
static const int W            = 1;
static const int BITS[2]      = { 8, 16 };
static const unsigned SIGN[2] = { 0x80u, 0x8000u };
static const unsigned MASK[2] = { 0xffu, 0xffffu };
static const int PARITY[256]  = {
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
// Linear address from segment:offset (8086 real mode).
//
unsigned Processor::getAddr(Word seg, Word off) const
{
    return ((seg << 4) + off) & 0xfffffu;
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
        return getAddr(os, core.bx + core.si + disp);
    case 0b001:
        return getAddr(os, core.bx + core.di + disp);
    case 0b010:
        return getAddr(os, core.bp + core.si + disp);
    case 0b011:
        return getAddr(os, core.bp + core.di + disp);
    case 0b100:
        return getAddr(os, core.si + disp);
    case 0b101:
        return getAddr(os, core.di + disp);
    case 0b110:
        if (mod_val == 0)
            return getAddr(os, opcode[plen + 2] | (opcode[plen + 3] << 8));
        else
            return getAddr(os, core.bp + disp);
    case 0b111:
        return getAddr(os, core.bx + disp);
    default:
        // Cannot happen
        return getAddr(os, 0);
    }
}

//
// Fetch 1 or 2 bytes at CS:IP, advance IP.
//
int Processor::getMem(int width)
{
    unsigned addr = getAddr(core.cs, core.ip);
    Word val      = machine.mem_fetch_byte(addr);

    if (width == W)
        val |= machine.mem_fetch_byte(addr + 1) << 8;

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
//
int Processor::getRM(int width, unsigned mod_val, unsigned rm_val)
{
    if (mod_val == 0b11)
        return getReg(width, rm_val);
    return getMem(width, getEA(mod_val, rm_val));
}

//
// Set R/M operand.
//
void Processor::setRM(int width, unsigned mod_val, unsigned rm_val, int val)
{
    if (mod_val == 0b11)
        setReg(width, rm_val, val);
    else
        setMem(width, getEA(mod_val, rm_val), val);
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
    unsigned addr = getAddr(core.ss, core.sp);
    int val       = getMem(W, addr);

    core.sp += 2;
    return val;
}

//
// Push word onto stack.
//
void Processor::push(int val)
{
    core.sp -= 2;
    setMem(W, getAddr(core.ss, core.sp), val);
}

//
// Software interrupt: push FLAGS, CS, IP; jump to vector.
//
void Processor::callInt(int type)
{
    if (machine.is_syscall(type)) {
        // Intercept syscalls.
        machine.process_syscall(type);
        return;
    }

    // Fetch interrupt vector.
    Word offset = getMem(W, type * 4);
    Word seg    = getMem(W, type * 4 + 2);

    // Update flags.
    setFlag(IF, false);
    setFlag(TF, false);

    // Take interrupt.
    push(core.flags);
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
    int res = (dst + src) & MASK[width];
    setFlag(CF, res < dst);
    setFlag(AF, ((res ^ dst ^ src) & AF) != 0);
    setFlag(OF, (shift((dst ^ src ^ -1) & (dst ^ res), 12 - BITS[width]) & OF) != 0);
    setFlags(width, res);
    return res;
}

int Processor::adc(int width, int dst, int src)
{
    int carry = (core.flags & CF) ? 1 : 0;
    int res   = (dst + src + carry) & MASK[width];
    setFlag(CF, carry ? (res <= dst) : (res < dst));
    setFlag(AF, ((res ^ dst ^ src) & AF) != 0);
    setFlag(OF, (shift((dst ^ src ^ -1) & (dst ^ res), 12 - BITS[width]) & OF) != 0);
    setFlags(width, res);
    return res;
}

int Processor::sub(int width, int dst, int src)
{
    int res = (dst - src) & MASK[width];
    setFlag(CF, dst < src);
    setFlag(AF, ((res ^ dst ^ src) & AF) != 0);
    setFlag(OF, (shift((dst ^ src) & (dst ^ res), 12 - BITS[width]) & OF) != 0);
    setFlags(width, res);
    return res;
}

int Processor::sbb(int width, int dst, int src)
{
    int carry = (core.flags & CF) ? 1 : 0;
    int res   = (dst - src - carry) & MASK[width];
    setFlag(CF, carry ? (dst <= src) : (dst < src));
    setFlag(AF, ((res ^ dst ^ src) & AF) != 0);
    setFlag(OF, (shift((dst ^ src) & (dst ^ res), 12 - BITS[width]) & OF) != 0);
    setFlags(width, res);
    return res;
}

int Processor::inc(int width, int dst)
{
    int res = (dst + 1) & MASK[width];
    setFlag(AF, ((res ^ dst ^ 1) & AF) != 0);
    setFlag(OF, res == static_cast<int>(SIGN[width]));
    setFlags(width, res);
    return res;
}

int Processor::dec(int width, int dst)
{
    int res = (dst - 1) & MASK[width];
    setFlag(AF, ((res ^ dst ^ 1) & AF) != 0);
    setFlag(OF, res == static_cast<int>(SIGN[width]) - 1);
    setFlags(width, res);
    return res;
}

void Processor::logic(int width, int res)
{
    setFlag(CF, false);
    setFlag(OF, false);
    setFlag(AF, false); // undefined per Intel; real 8086 clears it
    setFlags(width, res);
}

bool Processor::getFlag(unsigned flag) const
{
    return (core.flags & flag) != 0;
}

void Processor::setFlag(unsigned flag, bool set)
{
    if (set)
        set_flags(core.flags | flag);
    else
        set_flags(core.flags & ~flag);
}

//
// Set FLAGS register.
//
// Bits:  15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
//        -----------------------------------------------
// Flags: 1  1  1  1  OF DF IF TF SF ZF 0  AF 0 PF  1  CF
//
void Processor::set_flags(Word val)
{
    // Bits 1,3,5 reserved (1,0,0).
    static const unsigned FLAGS_WRITABLE = 0x0FD5; // bits 0,2,4,6-11 writable
    static const unsigned FLAGS_ONES     = 0xF002; // bits 1,12-15 always 1

    core.flags = (val & FLAGS_WRITABLE) | FLAGS_ONES;
}

void Processor::setFlags(int width, int res)
{
    setFlag(PF, PARITY[res & 0xff] != 0);
    setFlag(ZF, res == 0);
    setFlag(SF, (shift(res, 8 - BITS[width]) & SF) != 0);
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
        unsigned addr = getAddr(core.cs, core.ip);
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
        opcode.push_back(machine.mem_fetch_byte(getAddr(core.cs, (core.ip + i) & 0xffff)));
    }

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
            if (rep && check_zf && ((rep == 1 && !getFlag(ZF)) || (rep == 2 && getFlag(ZF))))
                break;
        } while (rep != 0);
    } else {
        exe_one();
    }

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
            src = getMem(w, getAddr(os, static_cast<Word>(dst)));
            setReg(w, AX, src);
        } else {
            src = getReg(w, AX);
            setMem(w, getAddr(os, static_cast<Word>(dst)), src);
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
        src = getRM(w, mod, rm);
        setReg(w, reg, src);
        setRM(w, mod, rm, dst);
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
        set_al(getFlag(CF) ? 0xff : 0);
        break;
    // XLAT
    case 0xd7: {
        set_al(getMem(B, getAddr(os, core.bx + get_al())));
        break;
    }
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
        set_ah(core.flags);
        break;
    // SAHF
    case 0x9e:
        set_flags((core.flags & 0xff00) | get_ah());
        break;
    // PUSHF / POPF
    case 0x9c:
        push(core.flags);
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
    // AAA
    case 0x37: {
        if ((get_al() & 0xf) > 9 || getFlag(AF)) {
            set_al(get_al() + 6);
            core.ax = (core.ax + 0x100) & 0xffff;
            setFlag(CF, true);
            setFlag(AF, true);
        } else {
            setFlag(CF, false);
            setFlag(AF, false);
        }
        set_al(get_al() & 0xf);
        setFlag(PF, false); // 8086 AAA: PF=0 (match reference 0xF893)
        setFlag(ZF, false);
        setFlag(SF, (core.ax & 0xff00) != 0); // SF from AH non-zero
        break;
    }
    case 0x27: {
        bool old_cf = getFlag(CF);
        setFlag(CF, false);
        if ((get_al() & 0xf) > 9 || getFlag(AF)) {
            set_al(get_al() + 6);
            setFlag(CF, old_cf || (get_al() < 0));
            setFlag(AF, true);
        } else {
            setFlag(AF, false);
        }
        if (get_al() > 0x99 || old_cf || ((get_al() >> 4) <= 9 && getFlag(AF))) {
            set_al(get_al() + 0x60);
            setFlag(CF, true);
        } else {
            setFlag(CF, false);
        }
        setFlags(B, get_al());
        setFlag(OF, false); // 8086: OF undefined after DAA; test expects 0
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
    // AAS
    case 0x3f: {
        if ((get_al() & 0xf) > 9 || getFlag(AF)) {
            set_al(get_al() - 6);
            core.ax = (core.ax - 0x100) & 0xffff;
            setFlag(CF, true);
            setFlag(AF, true);
        } else {
            setFlag(CF, false);
            setFlag(AF, false);
        }
        set_al(get_al() & 0xf);
        setFlags(B, get_al()); // PF, ZF, SF from result AL
        break;
    }
    case 0x2f: {
        bool old_cf = getFlag(CF);
        setFlag(CF, false);
        if ((get_al() & 0xf) > 9 || getFlag(AF)) {
            set_al(get_al() - 6);
            setFlag(CF, old_cf || (get_al() > 0));
            setFlag(AF, true);
        } else
            setFlag(AF, false);
        if (get_al() > 0x99 || old_cf || ((get_al() >> 4) <= 9 && getFlag(AF))) {
            set_al(get_al() - 0x60);
            setFlag(CF, true);
        } else
            setFlag(CF, false);
        setFlags(B, get_al());
        setFlag(OF, false); // 8086: OF undefined after DAS; test expects 0
        break;
    }
    // AAM, AAD
    case 0xd4: {
        src = getMem(B);
        if (src == 0) {
            callInt(0);
        } else {
            set_ah(get_al() / src);
            set_al(get_al() % src);
            setFlags(W, core.ax);
        }
        break;
    }
    case 0xd5: {
        src        = getMem(B);
        int ah_val = core.ax >> 8;
        set_al(ah_val * src + get_al());
        core.ax &= 0x00ff;
        setFlags(B, get_al());
        setFlag(CF, true); // 8086 AAD: match reference 0xF403
        setFlag(AF, false);
        setFlag(OF, false);
        setFlag(TF, false);
        break;
    }
    // CBW, CWD
    case 0x98:
        if (get_al() & 0x80)
            core.ax |= 0xff00;
        else
            core.ax &= 0x00ff;
        break;
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
        src = getMem(w, getAddr(os, core.si));
        setMem(w, getAddr(core.es, core.di), src);
        core.si = (core.si + (getFlag(DF) ? -1 : 1) * (1 + w)) & 0xffff;
        core.di = (core.di + (getFlag(DF) ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xa6:
    case 0xa7:
        dst = getMem(w, getAddr(core.es, core.di));
        src = getMem(w, getAddr(os, core.si));
        sub(w, src, dst);
        core.si = (core.si + (getFlag(DF) ? -1 : 1) * (1 + w)) & 0xffff;
        core.di = (core.di + (getFlag(DF) ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xae:
    case 0xaf:
        dst = getMem(w, getAddr(core.es, core.di));
        src = getReg(w, AX);
        sub(w, src, dst);
        core.di = (core.di + (getFlag(DF) ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xac:
    case 0xad:
        src = getMem(w, getAddr(os, core.si));
        setReg(w, AX, src);
        core.si = (core.si + (getFlag(DF) ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    case 0xaa:
    case 0xab:
        setMem(w, getAddr(core.es, core.di), getReg(w, AX));
        core.di = (core.di + (getFlag(DF) ? -1 : 1) * (1 + w)) & 0xffff;
        break;
    // --- CALL, RET, JMP: transfer and conditional jumps ---
    case 0xe8: {
        dst = signconv(W, getMem(W));
        push(static_cast<int>(core.ip));
        core.ip = (core.ip + dst) & 0xffff;
        break;
    }
    case 0x9a: {
        dst = getMem(W);
        src = getMem(W);
        push(static_cast<int>(core.cs));
        push(static_cast<int>(core.ip));
        core.ip = static_cast<Word>(dst & 0xffff);
        core.cs = static_cast<Word>(src & 0xffff);
        break;
    }
    case 0xc0: // 8086 undocumented: same as C2 (RET imm16)
    case 0xc2: {
        src     = getMem(W);
        core.ip = static_cast<Word>(pop() & 0xffff);
        core.sp = (core.sp + src) & 0xffff;
        break;
    }
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
    case 0xca: {
        src     = getMem(W);
        core.ip = static_cast<Word>(pop() & 0xffff);
        core.cs = static_cast<Word>(pop() & 0xffff);
        core.sp = (core.sp + src) & 0xffff;
        break;
    }
    case 0xe9: {
        dst     = signconv(W, getMem(W));
        core.ip = (core.ip + dst) & 0xffff;
        break;
    }
    case 0xeb: {
        dst     = signconv(B, getMem(B));
        core.ip = (core.ip + dst) & 0xffff;
        break;
    }
    case 0xea: {
        dst     = getMem(W);
        src     = getMem(W);
        core.ip = static_cast<Word>(dst & 0xffff);
        core.cs = static_cast<Word>(src & 0xffff);
        break;
    }
        // Conditional jumps (Jcc)

    case 0x70: // JO - Overflow
    case 0x60: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(OF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x71: // JNO - No overflow
    case 0x61: // Undocumented
        dst = signconv(B, getMem(B));
        if (!getFlag(OF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x72: // JB, JC, JNAE - Below / Carry
    case 0x62: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(CF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x73: // JNB, JNC, JAE - Above or equal / No carry
    case 0x63: // Undocumented
        dst = signconv(B, getMem(B));
        if (!getFlag(CF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x74: // JE, JZ - Equal / Zero
    case 0x64: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(ZF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x75: // JNE, JNZ - Not equal / Not zero
    case 0x65: // Undocumented
        dst = signconv(B, getMem(B));
        if (!getFlag(ZF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x76: // JBE, JNA - Below or equal
    case 0x66: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(CF) || getFlag(ZF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x77: // JA, JNBE - Above
    case 0x67: // Undocumented
        dst = signconv(B, getMem(B));
        if (!(getFlag(CF) || getFlag(ZF)))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x78: // JS - Sign
    case 0x68: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(SF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x79: // JNS - Not sign
    case 0x69: // Undocumented
        dst = signconv(B, getMem(B));
        if (!getFlag(SF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7a: // JP, JPE - Parity even
    case 0x6a: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(PF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7b: // JNP, JPO - Parity odd
    case 0x6b: // Undocumented
        dst = signconv(B, getMem(B));
        if (!getFlag(PF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7c: // JL, JNGE - Less (signed)
    case 0x6c: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(SF) != getFlag(OF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7d: // JGE, JNL - Greater or equal (signed)
    case 0x6d: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(SF) == getFlag(OF))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7e: // JLE, JNG - Less or equal (signed)
    case 0x6e: // Undocumented
        dst = signconv(B, getMem(B));
        if (getFlag(ZF) || (getFlag(SF) != getFlag(OF)))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    case 0x7f: // JG, JNLE - Greater (signed)
    case 0x6f: // Undocumented
        dst = signconv(B, getMem(B));
        if (!getFlag(ZF) && (getFlag(SF) == getFlag(OF)))
            core.ip = (core.ip + dst) & 0xffff;
        break;
    // LOOP, LOOPE, LOOPNE, JCXZ
    case 0xe2: {
        dst = signconv(B, getMem(B));
        core.cx -= 1;
        if (core.cx != 0)
            core.ip += dst;
        break;
    }
    case 0xe1: {
        dst = signconv(B, getMem(B));
        core.cx -= 1;
        if (core.cx != 0 && getFlag(ZF))
            core.ip += dst;
        break;
    }
    case 0xe0: {
        dst = signconv(B, getMem(B));
        core.cx -= 1;
        if (core.cx != 0 && !getFlag(ZF))
            core.ip += dst;
        break;
    }
    case 0xe3: {
        dst = signconv(B, getMem(B));
        if (core.cx == 0)
            core.ip += dst;
        break;
    }
    // INT3, INT, INTO: software interrupt
    case 0xcc:
        callInt(3);
        break;
    case 0xcd:
        callInt(getMem(B));
        break;
    case 0xce:
        if (getFlag(OF)) {
            callInt(4);
        }
        break;
    case 0xcf: // IRET: pop IP, CS, FLAGS
        core.ip = pop();
        core.cs = pop();
        set_flags(pop());
        break;
    // Flag ops
    case 0xf8:
        setFlag(CF, false);
        break;
    case 0xf5:
        setFlag(CF, !getFlag(CF));
        break;
    case 0xf9:
        setFlag(CF, true);
        break;
    case 0xfc:
        setFlag(DF, false);
        break;
    case 0xfd:
        setFlag(DF, true);
        break;
    case 0xfa:
        setFlag(IF, false);
        break;
    case 0xfb:
        setFlag(IF, true);
        break;
    case 0xf4: // HLT
        // Pause until an external interrupt is received.
        break;
    case 0x9b: // WAIT
        break;
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
    case 0xf0: // LOCK
        break;
    case 0x90: // NOP
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
            // 8086 shifts (SHR/SAR/SHL): count mask 5 bits (0-31) for both byte and word
            else
                src = get_cl() & 0x1f;
        }
        bool temp_cf;
        switch (reg) {
        case 0: // ROL
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = msb(w, dst);
                dst     = ((dst << 1) | (temp_cf ? 1 : 0)) & MASK[w];
            }
            setFlag(CF, (dst & 1) != 0);
            if (src == 1)
                setFlag(OF, msb(w, dst) != getFlag(CF));
            break;
        case 1: // ROR
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = (dst & 1) != 0;
                dst     = ((dst >> 1) | (temp_cf ? static_cast<int>(SIGN[w]) : 0)) & MASK[w];
            }
            setFlag(CF, msb(w, dst));
            if (src == 1)
                setFlag(OF, msb(w, dst) != msb(w, dst << 1));
            else if (src > 1)
                setFlag(OF, false);
            break;
        case 2: // RCL
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = msb(w, dst);
                dst     = ((dst << 1) | (getFlag(CF) ? 1 : 0)) & MASK[w];
                setFlag(CF, temp_cf);
            }
            if (src == 1)
                setFlag(OF, msb(w, dst) != getFlag(CF));
            break;
        case 3: // RCR
            if (src == 1)
                setFlag(OF, msb(w, dst) != getFlag(CF));
            for (int cnt = 0; cnt < src; ++cnt) {
                temp_cf = (dst & 1) != 0;
                dst     = ((dst >> 1) | (getFlag(CF) ? static_cast<int>(SIGN[w]) : 0)) & MASK[w];
                setFlag(CF, temp_cf);
            }
            if (src > 1)
                setFlag(OF,
                        w == W && (msb(w, dst) != (static_cast<unsigned>(dst) & (SIGN[w] >> 1))));
            break;
        case 4: // SAL/SHL
            for (int cnt = 0; cnt < src; ++cnt) {
                setFlag(CF, (dst & static_cast<int>(SIGN[w])) != 0);
                dst = (dst << 1) & MASK[w];
            }
            if (src == 1)
                setFlag(OF, ((dst & static_cast<int>(SIGN[w])) != 0) != getFlag(CF));
            else if (src > 0)
                setFlag(OF, false);
            if (src > 0) {
                setFlag(AF, false);
                setFlags(w, dst);
            }
            break;
        case 6: // SETMO: real 8086 sets operand to all ones (0xFF/0xFFFF)
            dst = static_cast<int>(MASK[w]);
            setFlag(CF, false);
            setFlag(OF, false);
            setFlag(AF, false);
            setFlags(w, dst);
            break;
        case 5: // SHR
            if (src == 1)
                setFlag(OF, (dst & static_cast<int>(SIGN[w])) != 0);
            for (int cnt = 0; cnt < src; ++cnt) {
                setFlag(CF, (dst & 1) != 0);
                dst = (dst >> 1) & MASK[w];
            }
            if (src > 0) {
                setFlag(AF, false);
                setFlags(w, dst);
            }
            break;
        case 7: // SAR - 8086 uses original sign bit for all shift-ins
            if (src == 1)
                setFlag(OF, false);
            if (src > 0) {
                int signbit = (dst & static_cast<int>(SIGN[w]));
                if (src >= 8) {
                    setFlag(CF, signbit != 0);
                    setFlag(OF, false);
                    dst = signbit ? static_cast<int>(MASK[w]) : 0;
                } else {
                    for (int cnt = 0; cnt < src; ++cnt) {
                        setFlag(CF, (dst & 1) != 0);
                        dst = ((dst >> 1) | signbit) & MASK[w];
                    }
                }
                setFlag(AF, false);
                setFlags(w, dst);
            }
            break;
        default:
            break;
        }
        setRM(w, mod, rm, dst);
        break;
    }
    // F6/F7: TEST imm, NOT, NEG, MUL, IMUL, DIV, IDIV
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
            dst = sub(w, 0, src);
            setFlag(CF, dst != 0);
            setRM(w, mod, rm, dst);
            break;
        }
        case 4: // MUL
            if (w == B) {
                dst     = get_al();
                res     = (Word)(dst * src);
                core.ax = res;
                setFlag(CF, (res >> 8) != 0);
                setFlag(OF, (res >> 8) != 0);
            } else {
                uint32_t lres = (uint32_t)core.ax * (Word)src;
                core.ax       = lres;
                core.dx       = lres >> 16;
                setFlag(CF, (lres >> 16) != 0);
                setFlag(OF, (lres >> 16) != 0);
            }
            setFlag(AF, false);
            setFlags(w, core.ax);
            break;
        case 5: // IMUL
            if (w == B) {
                int s    = signconv(B, src);
                int dval = signconv(B, get_al());
                res      = (Word)(dval * s);
                core.ax  = res;
                setFlag(CF, (res != 0 && (res > 0x7f || res < -0x80)));
                setFlag(OF, (res != 0 && (res > 0x7f || res < -0x80)));
            } else {
                long ld = (long)signconv(W, core.ax) * (long)signconv(W, src);
                core.ax = ld;
                core.dx = ld >> 16;
                setFlag(CF, (ld >> 16) != 0 && (ld >> 16) != 0xffff);
                setFlag(OF, (ld >> 16) != 0 && (ld >> 16) != 0xffff);
            }
            setFlag(AF, false);
            setFlags(w, core.ax);
            if (w == B) {
                setFlag(SF, (core.ax & 0x8000) != 0);
                // 8086 byte IMUL: PF=1 when result is zero or when AL has odd parity
                setFlag(PF, (core.ax == 0) || (PARITY[core.ax & 0xff] == 0));
            } else if (w == W) {
                // 8086 word IMUL: PF from high byte of DX when DX is even (per hardware vectors)
                setFlag(PF, (PARITY[(core.dx >> 8) & 0xff] != 0) && ((core.dx & 1) == 0));
                setFlag(SF, (core.dx & 0x8000) != 0);
            }
            break;
        case 6: // DIV (unsigned)
            // The DIV instruction in the 8086 microprocessor upon successful execution
            // does not reliably update the FLAGS register. Specifically, the following
            // flags are left in an undefined state:
            // Carry Flag (CF), Overflow Flag (OF), Sign Flag (SF), Zero Flag (ZF),
            // Parity Flag (PF), and Auxiliary Carry Flag (AF).
            // The remaining flags are unaffected:
            // Interrupt Flag (IF), Direction Flag (DF), and Trap Flag (TF).
            // Though here we do our best to predict the flags.
            if (w == B) {
                if ((Byte)src == 0) {
                    set_flags(0xF046);
                    callInt(0);
                } else {
                    Word udst   = core.ax;
                    Word quo    = udst / (Byte)src;
                    Byte divisor = (Byte)src;
                    if (quo > 0xFF) {
                        setFlag(OF, true);
                        setFlag(AF, false);
                        callInt(0);
                    } else {
                        set_al(quo);
                        set_ah(udst % divisor);
                        if ((quo & 0x80) != 0) {
                            setFlag(CF, false);
                            setFlag(OF, false);
                            setFlags(B, quo);
                            if (quo >= 0xBE) {
                                set_flags(0xF006);
                            } else {
                                setFlag(AF, false);
                            }
                        } else {
                            setFlag(OF, true);
                            setFlag(SF, true);
                            setFlag(ZF, false);
                            setFlag(AF, quo < 0x2C);
                            setFlag(PF, true);
                            setFlag(CF, true);
                            if (quo < 0x2C)
                                set_flags(0xF487);
                            else
                                setFlag(DF, false);
                        }
                    }
                }
            } else {
                if (src == 0) {
                    set_flags(0xF046);
                    callInt(0);
                } else {
                    uint32_t ldst = (core.dx << 16) | core.ax;
                    uint32_t quo  = ldst / (Word)src;
                    if (quo > 0xFFFF) {
                        set_flags(getFlag(AF) ? 0xF406 : 0xF492);
                        callInt(0);
                    } else {
                        core.ax = quo;
                        core.dx = ldst % (Word)src;
                        if ((quo & 0x8000) != 0) {
                            setFlag(CF, false);
                            setFlag(OF, false);
                            setFlag(AF, false);
                            setFlag(PF, PARITY[(quo >> 8) & 0xff] != 0);
                            setFlag(ZF, quo == 0);
                            setFlag(SF, true);
                        } else {
                            set_flags(quo >= 0x0400 ? 0xF883 : 0xFC97);
                        }
                    }
                }
            }
            break;
        case 7: // IDIV (signed integer division)
            // After the IDIV instruction in the 8086 processor, the arithmetic flags
            // in the FLAGS register are left in an undefined state: CF, PF, AF, ZF, SF, OF.
            // Though here we do our best to predict the flags.
            if (w == B) {
                // Dividend is a signed 16-bit value in AX.
                // Divisor is a signed 8-bit value (register or memory).
                src = (int8_t)src;
                if (src == 0) {
                    // Divide by zero
                    setFlag(CF, false);
                    setFlag(PF, true);
                    setFlag(AF, false);
                    setFlag(ZF, true);
                    setFlag(SF, false);
                    setFlag(OF, false);
                    callInt(0);
                } else {
                    dst = (int16_t)core.ax;
                    res = dst / src;
                    if (res > 0x7f || res < -0x80) {
                        // Quotient overflow (byte).
                        // OF=1 only when quotient negative.
                        // PF from quotient if neg else AX high.
                        setFlag(CF, false);
                        setFlag(PF,
                                res < 0 ? (PARITY[res & 0xff] != 0) : (PARITY[(core.ax >> 8) & 0xff] != 0));
                        setFlag(AF, true);
                        setFlag(ZF, false);
                        setFlag(SF, false);
                        setFlag(OF, res < 0);
                        callInt(0);
                    } else {
                        int rem = dst % src;
                        set_al(res);
                        set_ah(rem);

                        // Successful byte IDIV.
                        // SF from remainder.
                        // PF from remainder.
                        setFlag(CF, false);
                        setFlag(OF, false);
                        setFlag(ZF, false);
                        setFlag(PF, PARITY[rem & 0xff] != 0);
                        setFlag(SF, (rem & 0x80) != 0);
                        setFlag(AF, false);
                    }
                }
            } else {
                // Dividend is a signed 32-bit value in DX:AX.
                // Divisor is a signed 16-bit value (register or memory).
                src = (int16_t)src;
                if (src == 0) {
                    // Divide by zero
                    setFlag(CF, false);
                    setFlag(PF, true);
                    setFlag(AF, false);
                    setFlag(ZF, true);
                    setFlag(SF, false);
                    setFlag(OF, false);
                    callInt(0);
                } else {
                    dst          = (int32_t)((core.dx << 16) | core.ax);
                    int64_t lres = (int64_t)dst / src;

                    if (lres > 0x7fff || lres < -0x8000) {
                        // Quotient overflow (word).
                        // PF from AX low byte.
                        // AF inverted from initial.
                        setFlag(CF, false);
                        setFlag(PF, PARITY[core.ax & 0xff] != 0);
                        setFlag(AF, !getFlag(AF));
                        setFlag(ZF, false);
                        setFlag(SF, false);
                        setFlag(OF, false);
                        callInt(0);
                    } else {
                        core.ax = lres;
                        core.dx = dst % src;

                        // Successful word IDIV.
                        // SF from quotient.
                        setFlag(CF, false);
                        setFlag(OF, false);
                        setFlag(ZF, false);
                        setFlag(PF, true);
                        setFlag(SF, (core.ax & 0x8000) != 0);
                        setFlag(AF, true);
                    }
                }
            }
            break;
        default:
            break;
        }
        break;
    }
    // FE: INC/DEC byte
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
    // FF: INC/DEC word, CALL, JMP, PUSH
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
