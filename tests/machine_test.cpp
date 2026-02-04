//
// Unit tests for Memory and Machine.
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

#include <gtest/gtest.h>

#include "pc86_arch.h"

//
// Boot sector load address.
//
static const unsigned LOAD_ADDR = 0x7c00;

//
// Segment value so that (CS<<4)+IP = LOAD_ADDR when IP=0.
//
static const unsigned LOAD_SEG = 0x07c0;

//
// Single-step through MOV immediate instructions and verify register values.
//
TEST(MachineTest, SingleStepMoves)
{
    Memory memory;
    Machine machine(memory);

    // Write instructions at 0x7c00:
    // MOV AX, 0x1234  (B8 34 12)
    // MOV BX, 0x5678  (BB 78 56)
    // MOV CX, 0x9abc  (B9 BC 9A)
    // HLT             (F4)
    machine.mem_store_byte(LOAD_ADDR + 0, 0xb8);
    machine.mem_store_byte(LOAD_ADDR + 1, 0x34);
    machine.mem_store_byte(LOAD_ADDR + 2, 0x12);

    machine.mem_store_byte(LOAD_ADDR + 3, 0xbb);
    machine.mem_store_byte(LOAD_ADDR + 4, 0x78);
    machine.mem_store_byte(LOAD_ADDR + 5, 0x56);

    machine.mem_store_byte(LOAD_ADDR + 6, 0xb9);
    machine.mem_store_byte(LOAD_ADDR + 7, 0xbc);
    machine.mem_store_byte(LOAD_ADDR + 8, 0x9a);

    machine.mem_store_byte(LOAD_ADDR + 9, 0xf4);

    // Set CS:IP to fetch from 0x7c00
    machine.cpu.set_cs(LOAD_SEG);
    machine.cpu.set_ip(0);

    // Show trace.
    Machine::enable_trace("r");
    machine.trace_registers();

    // Single-step through the 3 MOV instructions
    machine.cpu.step();
    machine.cpu.step();
    machine.cpu.step();

    EXPECT_EQ(machine.cpu.get_ax(), 0x1234u);
    EXPECT_EQ(machine.cpu.get_bx(), 0x5678u);
    EXPECT_EQ(machine.cpu.get_cx(), 0x9abcu);

    // Fourth step executes HLT.
    machine.cpu.step();
    EXPECT_EQ(machine.cpu.get_op(), 0xf4);
}

//
// Byte register halves: get/set AH, AL, BH, BL, CH, CL, DH, DL.
//
TEST(MachineTest, ByteRegisterHalves)
{
    Memory memory;
    Machine machine(memory);
    Processor &cpu = machine.cpu;

    // set_ax(0x1234) -> get_ah()==0x12, get_al()==0x34
    cpu.set_ax(0x1234);
    EXPECT_EQ(cpu.get_ah(), 0x12u);
    EXPECT_EQ(cpu.get_al(), 0x34u);

    // set_ah(0xab) updates AX high byte only -> get_ax()==0xab34
    cpu.set_ah(0xab);
    EXPECT_EQ(cpu.get_ax(), 0xab34u);
    EXPECT_EQ(cpu.get_al(), 0x34u);

    // CX: set_cl/set_ch and word consistency
    cpu.set_cx(0x9abc);
    EXPECT_EQ(cpu.get_ch(), 0x9au);
    EXPECT_EQ(cpu.get_cl(), 0xbcu);
    cpu.set_cl(0x12);
    EXPECT_EQ(cpu.get_cx(), 0x9a12u);
    cpu.set_ch(0xef);
    EXPECT_EQ(cpu.get_cx(), 0xef12u);
}
