#include "fixture.h"

//
// Single-step through MOV immediate instructions and verify register values.
//
TEST_F(MachineTest, SingleStepMoves)
{
    // Write instructions at 0x7c00:
    // MOV AX, 0x1234  (B8 34 12)
    // MOV BX, 0x5678  (BB 78 56)
    // MOV CX, 0x9abc  (B9 BC 9A)
    // HLT             (F4)
    machine.mem_store_byte(BOOT_ADDR + 0, 0xb8);
    machine.mem_store_byte(BOOT_ADDR + 1, 0x34);
    machine.mem_store_byte(BOOT_ADDR + 2, 0x12);

    machine.mem_store_byte(BOOT_ADDR + 3, 0xbb);
    machine.mem_store_byte(BOOT_ADDR + 4, 0x78);
    machine.mem_store_byte(BOOT_ADDR + 5, 0x56);

    machine.mem_store_byte(BOOT_ADDR + 6, 0xb9);
    machine.mem_store_byte(BOOT_ADDR + 7, 0xbc);
    machine.mem_store_byte(BOOT_ADDR + 8, 0x9a);

    machine.mem_store_byte(BOOT_ADDR + 9, 0xf4);

    // Set CS:IP to fetch from 0x7c00
    cpu.set_cs(BOOT_ADDR >> 4);
    cpu.set_ip(0);
    machine.trace_registers();

    // Single-step through the 3 MOV instructions
    cpu.step();
    cpu.step();
    cpu.step();

    EXPECT_EQ(cpu.get_ax(), 0x1234u);
    EXPECT_EQ(cpu.get_bx(), 0x5678u);
    EXPECT_EQ(cpu.get_cx(), 0x9abcu);

    // Fourth step executes HLT.
    cpu.step();
    EXPECT_EQ(cpu.get_op(), 0xf4);
}

//
// Byte register halves: get/set AH, AL, BH, BL, CH, CL, DH, DL.
//
TEST_F(MachineTest, ByteRegisterHalves)
{
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
