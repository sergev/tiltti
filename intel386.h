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
#ifndef TILTTI_INTEL386_H
#define TILTTI_INTEL386_H

#include <array>
#include <cstdint>
#include <string>

#include "pc_platform.h"

class Machine;
class Memory;

//
// Visible architectural state of the processor.
//
struct CoreState {
    Dword eax{}, ebx{}, ecx{}, edx{};        // general (AX = low 16 of EAX, etc.)
    Dword esp{}, ebp{}, esi{}, edi{};        // stack pointer, base, index
    Word cs{}, ds{}, ss{}, es{}, fs{}, gs{}; // segment registers
    Dword eip{};                             // instruction pointer

    // Bits:  17 16 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
    //        -----------------------------------------------------
    // Flags: VM RF 0  NT IO-PL OF DF IF TF SF ZF 0  AF 0 PF  1  CF
    union {
        Dword w{};
        struct {                 // bits 1,3,5,15,18-31 reserved
            unsigned cf : 1;     // bit 0  - Carry Flag
            unsigned _bit1 : 1;  //
            unsigned pf : 1;     // bit 2  - Parity Flag
            unsigned _bit3 : 1;  //
            unsigned af : 1;     // bit 4  - Auxiliary Carry Flag
            unsigned _bit5 : 1;  //
            unsigned zf : 1;     // bit 6  - Zero Flag
            unsigned sf : 1;     // bit 7  - Sign Flag
            unsigned tf : 1;     // bit 8  - Trap Flag
            unsigned ifl : 1;    // bit 9  - Interrupt FLag
            unsigned df : 1;     // bit 10 - Direction Flag
            unsigned of : 1;     // bit 11 - Overflow Flag
            unsigned iopl : 2;   // bits 12,13 - I/O Privilege Level
            unsigned nt : 1;     // bit 14 - Nested Task flag
            unsigned _bit15 : 1; //
            unsigned rf : 1;     // bit 16 - Resume Flag
            unsigned vm : 1;     // bit 17 - Virtual 8086 Mode
            unsigned _bits18to31 : 14;
        } f;
    } flags;

    Dword cr0{}, cr3{}, dr6{}, dr7{}; // control and debug registers
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

// BT-family instruction action (test-only, complement, reset, set)
enum class BitTestAction { test, complement, reset, set };

//
// PC i86 processor.
//
class Intel386 {
private:
    Machine &machine;        // Reference to the machine
    struct CoreState core{}; // Current state
    struct CoreState prev{}; // Previous state, for tracing

    // Current opcode being executed.
    std::vector<Byte> opcode{};
    unsigned plen{}; // prefix length

    // Decode state (internal to one instruction).
    unsigned op{}, d{}, w{}, mod{}, reg{}, rm{};
    int ea{ -1 };   // effective address cache
    unsigned rep{}; // 0=none, 1=REP/REPE/REPZ, 2=REPNE/REPNZ
    bool segment_override{};
    Word os{};         // segment override (default DS)
    bool os_is_ss{};   // true when effective segment is SS (for #SS vs #GP selection)
    bool operand_32{}; // 66h operand-size override (16-bit default in real mode)
    bool address_32{}; // 67h address-size override
    bool lock_prefix{}; // F0h LOCK prefix
    Dword last_ea_offset{}; // raw 32-bit offset from getEA (for BOUND segment limit check)
    Dword fault_eip{};     // instruction start EIP for segment fault reporting

    // Bitmask of unpredictable flags for the current/last instruction.
    Dword unpredictable_flags{};
    Dword last_unpredictable_flags{}; // preserved for u_flags() across steps

    // Helpers: effective address, register/memory access, stack, ALU, flags.
    unsigned getAddr(Word seg, Word off) const;
    unsigned getEA(unsigned mod_val, unsigned rm_val);
    unsigned getEA_cached(unsigned mod_val, unsigned rm_val); // caches to avoid double EIP advance
    int fetch(int width);
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
    int pop32();
    void push(int val);
    void push32(Dword val);
    int add(int width, int dst, int src);
    int adc(int width, int dst, int src);
    int sub(int width, int dst, int src);
    int sbb(int width, int dst, int src);
    int inc(int width, int dst);
    int dec(int width, int dst);
    void logic(int width, int res);
    void do_bit_test(BitTestAction action);
    void do_bit_test_imm();
    static int signconv(int width, int x);
    static bool msb(int width, int x);
    void intercept_bios_call();
    [[noreturn]] void raise_segment_fault();

    // Execute one opcode (used by step and REP loop).
    void exe_one();

public:
    // Constructor.
    explicit Intel386(Machine &machine);

    // Reset to initial state.
    void reset();

    // Simulate one instruction.
    void step();

    // Finalize the processor.
    void finish();

    // Take interrupt.
    void call_int(int type);

    // Set instruction pointer.
    void set_ip(Word val) { core.eip = (core.eip & 0xFFFF0000u) | val; }
    void set_eip(Dword val) { core.eip = val; }

    // Get instruction pointer.
    unsigned get_ip() const { return static_cast<Word>(core.eip); }
    Dword get_eip() const { return core.eip; }

    // Get first byte of opcode.
    unsigned get_op() const { return op; }
    bool is_halted() const { return op == 0xf4; }

    // General registers (32-bit)
    Dword get_eax() const { return core.eax; }
    void set_eax(Dword val) { core.eax = val; }
    Dword get_ebx() const { return core.ebx; }
    void set_ebx(Dword val) { core.ebx = val; }
    Dword get_ecx() const { return core.ecx; }
    void set_ecx(Dword val) { core.ecx = val; }
    Dword get_edx() const { return core.edx; }
    void set_edx(Dword val) { core.edx = val; }

    Word get_ax() const { return static_cast<Word>(core.eax); }
    void set_ax(Word val) { core.eax = (core.eax & 0xFFFF0000u) | val; }
    Word get_bx() const { return static_cast<Word>(core.ebx); }
    void set_bx(Word val) { core.ebx = (core.ebx & 0xFFFF0000u) | val; }
    Word get_cx() const { return static_cast<Word>(core.ecx); }
    void set_cx(Word val) { core.ecx = (core.ecx & 0xFFFF0000u) | val; }
    Word get_dx() const { return static_cast<Word>(core.edx); }
    void set_dx(Word val) { core.edx = (core.edx & 0xFFFF0000u) | val; }

    //
    // Byte halves of general registers
    //
    Byte get_al() const { return static_cast<Byte>(core.eax); }
    Byte get_ah() const { return static_cast<Byte>(core.eax >> 8); }
    void set_al(Byte val) { core.eax = (core.eax & 0xFFFFFF00u) | val; }
    void set_ah(Byte val) { core.eax = (core.eax & 0xFFFF00FFu) | (static_cast<Dword>(val) << 8); }

    Byte get_bl() const { return static_cast<Byte>(core.ebx); }
    Byte get_bh() const { return static_cast<Byte>(core.ebx >> 8); }
    void set_bl(Byte val) { core.ebx = (core.ebx & 0xFFFFFF00u) | val; }
    void set_bh(Byte val) { core.ebx = (core.ebx & 0xFFFF00FFu) | (static_cast<Dword>(val) << 8); }

    Byte get_cl() const { return static_cast<Byte>(core.ecx); }
    Byte get_ch() const { return static_cast<Byte>(core.ecx >> 8); }
    void set_cl(Byte val) { core.ecx = (core.ecx & 0xFFFFFF00u) | val; }
    void set_ch(Byte val) { core.ecx = (core.ecx & 0xFFFF00FFu) | (static_cast<Dword>(val) << 8); }

    Byte get_dl() const { return static_cast<Byte>(core.edx); }
    Byte get_dh() const { return static_cast<Byte>(core.edx >> 8); }
    void set_dl(Byte val) { core.edx = (core.edx & 0xFFFFFF00u) | val; }
    void set_dh(Byte val) { core.edx = (core.edx & 0xFFFF00FFu) | (static_cast<Dword>(val) << 8); }

    // Pointer/index registers (32-bit)
    Dword get_esp() const { return core.esp; }
    void set_esp(Dword val) { core.esp = val; }
    Dword get_ebp() const { return core.ebp; }
    void set_ebp(Dword val) { core.ebp = val; }
    Dword get_esi() const { return core.esi; }
    void set_esi(Dword val) { core.esi = val; }
    Dword get_edi() const { return core.edi; }
    void set_edi(Dword val) { core.edi = val; }

    Word get_sp() const { return static_cast<Word>(core.esp); }
    void set_sp(Word val) { core.esp = (core.esp & 0xFFFF0000u) | val; }
    Word get_bp() const { return static_cast<Word>(core.ebp); }
    void set_bp(Word val) { core.ebp = (core.ebp & 0xFFFF0000u) | val; }
    Word get_si() const { return static_cast<Word>(core.esi); }
    void set_si(Word val) { core.esi = (core.esi & 0xFFFF0000u) | val; }
    Word get_di() const { return static_cast<Word>(core.edi); }
    void set_di(Word val) { core.edi = (core.edi & 0xFFFF0000u) | val; }

    // Segment registers
    Word get_cs() const { return core.cs; }
    void set_cs(Word val) { core.cs = val; }
    Word get_ds() const { return core.ds; }
    void set_ds(Word val) { core.ds = val; }
    Word get_ss() const { return core.ss; }
    void set_ss(Word val) { core.ss = val; }
    Word get_es() const { return core.es; }
    void set_es(Word val) { core.es = val; }
    Word get_fs() const { return core.fs; }
    void set_fs(Word val) { core.fs = val; }
    Word get_gs() const { return core.gs; }
    void set_gs(Word val) { core.gs = val; }

    // Flags (set_flags normalizes reserved bits per 386)
    Word get_flags() const { return static_cast<Word>(core.flags.w); }
    Dword get_eflags() const { return core.flags.w; }
    void set_flags(Word val);
    void set_eflags(Dword val);
    void update_flags_zsp(int width, int res);
    Dword u_flags() { return last_unpredictable_flags; }

    void set_cf(bool bit) { core.flags.f.cf = bit; }  // CF, Carry Flag
    void set_pf(bool bit) { core.flags.f.pf = bit; }  // PF, Parity Flag
    void set_af(bool bit) { core.flags.f.af = bit; }  // AF, Auxiliary Carry Flag
    void set_zf(bool bit) { core.flags.f.zf = bit; }  // ZF, Zero Flag
    void set_sf(bool bit) { core.flags.f.sf = bit; }  // SF, Sign Flag
    void set_tf(bool bit) { core.flags.f.tf = bit; }  // TF, Trap Flag
    void set_if(bool bit) { core.flags.f.ifl = bit; } // IF, Interrupt Flag
    void set_df(bool bit) { core.flags.f.df = bit; }  // DF, Direction Flag
    void set_of(bool bit) { core.flags.f.of = bit; }  // OF, Overflow Flag

    // Control and debug registers
    Dword get_cr0() const { return core.cr0; }
    void set_cr0(Dword val) { core.cr0 = val; }
    Dword get_cr3() const { return core.cr3; }
    void set_cr3(Dword val) { core.cr3 = val; }
    Dword get_dr6() const { return core.dr6; }
    void set_dr6(Dword val) { core.dr6 = val; }
    Dword get_dr7() const { return core.dr7; }
    void set_dr7(Dword val) { core.dr7 = val; }

    // Print trace info.
    void print_instruction();
    void print_registers();
};

#endif // TILTTI_INTEL386_H
