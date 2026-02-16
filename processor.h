//
// PC i86 processor unit.
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
#ifndef TILTTI_PROCESSOR_H
#define TILTTI_PROCESSOR_H

#include <array>
#include <cstdint>
#include <string>

#include "pc86_arch.h"

class Machine;
class Memory;

//
// Internal state of the processor.
//
//
// Visible architectural state (for trace and reset).
// Decode state (op, mod, reg, rm, ea, opcode) is internal to one instruction.
//
struct CoreState {
    Word ax{}, bx{}, cx{}, dx{}; // general (AX = AH:AL, etc.)
    Word sp{}, bp{}, si{}, di{}; // stack pointer, base, index
    Word cs{}, ds{}, ss{}, es{}; // segment registers
    Word ip{};                   // instruction pointer

    // Bits:  15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
    //        -----------------------------------------------
    // Flags: 1  1  1  1  OF DF IF TF SF ZF 0  AF 0 PF  1  CF
    union {
        Word w{};
        struct {
            unsigned c : 1;      // bit 0  - CF, Carry Flag
            unsigned _bit1 : 1;  //
            unsigned p : 1;      // bit 2  - PF, Parity Flag
            unsigned _bit3 : 1;  //
            unsigned a : 1;      // bit 4  - AF, Auxiliary Carry Flag
            unsigned _bit5 : 1;  //
            unsigned z : 1;      // bit 6  - ZF, Zero Flag
            unsigned s : 1;      // bit 7  - SF, Sign Flag
            unsigned t : 1;      // bit 8  - TF, Trap Flag
            unsigned i : 1;      // bit 9  - IF, Interrupt Flag
            unsigned d : 1;      // bit 10 - DF, Direction Flag
            unsigned o : 1;      // bit 11 - OF, Overflow Flag
            unsigned _bit12 : 1; //
            unsigned _bit13 : 1; //
            unsigned _bit14 : 1; //
            unsigned _bit15 : 1; //
        } f;
    } flags;
};

// Bitmasks for flags.
enum {
    CF_MASK = 1 << 0,  // Carry Flag
    PF_MASK = 1 << 2,  // Parity Flag
    AF_MASK = 1 << 4,  // Auxiliary Carry Flag
    ZF_MASK = 1 << 6,  // Zero Flag
    SF_MASK = 1 << 7,  // Sign Flag
    TF_MASK = 1 << 8,  // Trap Flag
    IF_MASK = 1 << 9,  // Interrupt Flag
    DF_MASK = 1 << 10, // Direction Flag
    OF_MASK = 1 << 11, // Overflow Flag
};

//
// PC i86 processor.
//
class Processor {
private:
    Machine &machine;        // Reference to the machine
    struct CoreState core{}; // Current state
    struct CoreState prev{}; // Previous state, for tracing

    // Current opcode being executed.
    std::vector<Byte> opcode{};
    unsigned plen{}; // prefix length

    // Decode state (internal to step()).
    unsigned op{}, d{}, w{}, mod{}, reg{}, rm{};
    int ea{ -1 };   // effective address cache
    unsigned rep{}; // 0=none, 1=REP/REPE/REPZ, 2=REPNE/REPNZ
    bool segment_override{};
    Word os{}; // segment override (default DS)

    // Bitmask of unpredictable flags for the last instruction.
    Word unpredictable_flags;

    // Helpers: effective address, register/memory access, stack, ALU, flags.
    unsigned getAddr(Word seg, Word off) const;
    unsigned getEA(unsigned mod_val, unsigned rm_val);
    int getMem(int width);
    int getMem(int width, unsigned addr);
    int getReg(int width, unsigned r) const;
    int getRM(int width, unsigned mod_val, unsigned rm_val);
    Word getSegReg(unsigned r) const;
    void setMem(int width, unsigned addr, int val);
    int getMemAtSegOff(int width, Word seg, Word off);
    void setMemAtSegOff(int width, Word seg, Word off, int val);
    void setReg(int width, unsigned r, int val);
    void setRM(int width, unsigned mod_val, unsigned rm_val, int val);
    void setSegReg(unsigned r, Word val);
    void decode();
    int pop();
    void push(int val);
    void callInt(int type);
    int add(int width, int dst, int src);
    int adc(int width, int dst, int src);
    int sub(int width, int dst, int src);
    int sbb(int width, int dst, int src);
    int inc(int width, int dst);
    int dec(int width, int dst);
    void logic(int width, int res);
    static int signconv(int width, int x);
    static bool msb(int width, int x);

    // Execute one opcode (used by step and REP loop).
    void exe_one();

public:
    // Constructor.
    Processor(Machine &machine);

    // Reset to initial state.
    void reset();

    // Simulate one instruction.
    void step();

    // Finalize the processor.
    void finish();

    // Set register value.
    void set_ip(unsigned val) { core.ip = val; }

    // Get register value.
    unsigned get_ip() const { return core.ip; }

    // Get first byte of opcode.
    unsigned get_op() const { return op; }

    // General registers
    Word get_ax() const { return core.ax; }
    void set_ax(Word val) { core.ax = val; }
    Word get_bx() const { return core.bx; }
    void set_bx(Word val) { core.bx = val; }
    Word get_cx() const { return core.cx; }
    void set_cx(Word val) { core.cx = val; }
    Word get_dx() const { return core.dx; }
    void set_dx(Word val) { core.dx = val; }

    //
    // Byte halves of general registers
    //
    Byte get_al() const { return core.ax; }
    Byte get_ah() const { return core.ax >> 8; }
    void set_al(Byte val) { core.ax = (core.ax & 0xff00) | val; }
    void set_ah(Byte val) { core.ax = (core.ax & 0x00ff) | (val << 8); }

    Byte get_bl() const { return core.bx; }
    Byte get_bh() const { return core.bx >> 8; }
    void set_bl(Byte val) { core.bx = (core.bx & 0xff00) | val; }
    void set_bh(Byte val) { core.bx = (core.bx & 0x00ff) | (val << 8); }

    Byte get_cl() const { return core.cx; }
    Byte get_ch() const { return core.cx >> 8; }
    void set_cl(Byte val) { core.cx = (core.cx & 0xff00) | val; }
    void set_ch(Byte val) { core.cx = (core.cx & 0x00ff) | (val << 8); }

    Byte get_dl() const { return core.dx; }
    Byte get_dh() const { return core.dx >> 8; }
    void set_dl(Byte val) { core.dx = (core.dx & 0xff00) | val; }
    void set_dh(Byte val) { core.dx = (core.dx & 0x00ff) | (val << 8); }

    // Pointer/index registers
    Word get_sp() const { return core.sp; }
    void set_sp(Word val) { core.sp = val; }
    Word get_bp() const { return core.bp; }
    void set_bp(Word val) { core.bp = val; }
    Word get_si() const { return core.si; }
    void set_si(Word val) { core.si = val; }
    Word get_di() const { return core.di; }
    void set_di(Word val) { core.di = val; }

    // Segment registers
    Word get_cs() const { return core.cs; }
    void set_cs(Word val) { core.cs = val; }
    Word get_ds() const { return core.ds; }
    void set_ds(Word val) { core.ds = val; }
    Word get_ss() const { return core.ss; }
    void set_ss(Word val) { core.ss = val; }
    Word get_es() const { return core.es; }
    void set_es(Word val) { core.es = val; }

    // Flags (set_flags normalizes reserved bits to match POPF/8086)
    Word get_flags() const { return core.flags.w; }
    void set_flags(Word val);
    void update_flags_zsp(int width, int res);
    Word u_flags() { return unpredictable_flags; }

    void set_cf(bool bit) { core.flags.f.c = bit; } // CF, Carry Flag
    void set_pf(bool bit) { core.flags.f.p = bit; } // PF, Parity Flag
    void set_af(bool bit) { core.flags.f.a = bit; } // AF, Auxiliary Carry Flag
    void set_zf(bool bit) { core.flags.f.z = bit; } // ZF, Zero Flag
    void set_sf(bool bit) { core.flags.f.s = bit; } // SF, Sign Flag
    void set_tf(bool bit) { core.flags.f.t = bit; } // TF, Trap Flag
    void set_if(bool bit) { core.flags.f.i = bit; } // IF, Interrupt Flag
    void set_df(bool bit) { core.flags.f.d = bit; } // DF, Direction Flag
    void set_of(bool bit) { core.flags.f.o = bit; } // OF, Overflow Flag

    // Print trace info.
    void print_instruction();
    void print_registers();
    void print_syscall(int type);
};

#endif // TILTTI_PROCESSOR_H
