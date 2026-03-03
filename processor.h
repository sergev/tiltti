//
// Abstract processor unit.
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

#include "pc86_arch.h"

class Machine;

//
// Abstract processor interface used by the rest of the code.
// Concrete implementations (e.g. Intel8086) are not visible here.
//
class Processor {
public:
    virtual ~Processor() = default;

    // Simulate one instruction.
    virtual void step() = 0;

    // Take interrupt.
    virtual void call_int(int type) = 0;

    // Instruction pointer
    virtual void set_ip(unsigned val) = 0;
    virtual unsigned get_ip() const = 0;

    // First byte of current opcode
    virtual unsigned get_op() const = 0;

    // General registers
    virtual Word get_ax() const = 0;
    virtual void set_ax(Word val) = 0;
    virtual Word get_bx() const = 0;
    virtual void set_bx(Word val) = 0;
    virtual Word get_cx() const = 0;
    virtual void set_cx(Word val) = 0;
    virtual Word get_dx() const = 0;
    virtual void set_dx(Word val) = 0;

    // Byte halves of general registers
    virtual Byte get_al() const = 0;
    virtual Byte get_ah() const = 0;
    virtual void set_al(Byte val) = 0;
    virtual void set_ah(Byte val) = 0;
    virtual Byte get_bl() const = 0;
    virtual Byte get_bh() const = 0;
    virtual void set_bl(Byte val) = 0;
    virtual void set_bh(Byte val) = 0;
    virtual Byte get_cl() const = 0;
    virtual Byte get_ch() const = 0;
    virtual void set_cl(Byte val) = 0;
    virtual void set_ch(Byte val) = 0;
    virtual Byte get_dl() const = 0;
    virtual Byte get_dh() const = 0;
    virtual void set_dl(Byte val) = 0;
    virtual void set_dh(Byte val) = 0;

    // Pointer/index registers
    virtual Word get_sp() const = 0;
    virtual void set_sp(Word val) = 0;
    virtual Word get_bp() const = 0;
    virtual void set_bp(Word val) = 0;
    virtual Word get_si() const = 0;
    virtual void set_si(Word val) = 0;
    virtual Word get_di() const = 0;
    virtual void set_di(Word val) = 0;

    // Segment registers
    virtual Word get_cs() const = 0;
    virtual void set_cs(Word val) = 0;
    virtual Word get_ds() const = 0;
    virtual void set_ds(Word val) = 0;
    virtual Word get_ss() const = 0;
    virtual void set_ss(Word val) = 0;
    virtual Word get_es() const = 0;
    virtual void set_es(Word val) = 0;

    // Flags
    virtual Word get_flags() const = 0;
    virtual void set_flags(Word val) = 0;
    virtual Word u_flags() = 0;

    virtual void set_cf(bool bit) = 0;
    virtual void set_pf(bool bit) = 0;
    virtual void set_af(bool bit) = 0;
    virtual void set_zf(bool bit) = 0;
    virtual void set_sf(bool bit) = 0;
    virtual void set_tf(bool bit) = 0;
    virtual void set_if(bool bit) = 0;
    virtual void set_df(bool bit) = 0;
    virtual void set_of(bool bit) = 0;

    // Print trace info
    virtual void print_instruction() = 0;
    virtual void print_registers() = 0;

protected:
    Processor() = default;
};

#endif // TILTTI_PROCESSOR_H
