#include "fixture.h"

//
// int3
//
TEST_F(MachineTest, int3)
{
    // Initial CPU State
    cpu.set_ax(0x45D6);
    cpu.set_bx(0x3F17);
    cpu.set_cx(0x1A5C);
    cpu.set_dx(0x02D1);
    cpu.set_cs(0xE0D1);
    cpu.set_ss(0x8803);
    cpu.set_ds(0xD0E1);
    cpu.set_es(0xED94);
    cpu.set_sp(0x85D4);
    cpu.set_bp(0x1074);
    cpu.set_si(0x26D3);
    cpu.set_di(0x1801);
    cpu.set_ip(0xF8C9);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF05D9, 0xCC);
    machine.mem_store_byte(0xF05DA, 0x90);
    machine.mem_store_byte(0xF05DB, 0x90);
    machine.mem_store_byte(0xF05DC, 0x90);
    machine.mem_store_byte(0x0000C, 0x3C);
    machine.mem_store_byte(0x0000D, 0x28);
    machine.mem_store_byte(0x0000E, 0x88);
    machine.mem_store_byte(0x0000F, 0x06);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0688);
    EXPECT_EQ(cpu.get_sp(), 0x85CE);
    EXPECT_EQ(cpu.get_ip(), 0x283C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x90602), 0x52);
    EXPECT_EQ(memory.load8(0x90603), 0xF8);
    EXPECT_EQ(memory.load8(0x90600), 0xD1);
    EXPECT_EQ(memory.load8(0x90601), 0xE0);
    EXPECT_EQ(memory.load8(0x905FE), 0xCA);
    EXPECT_EQ(memory.load8(0x905FF), 0xF8);
}

//
// int C6h
//
TEST_F(MachineTest, int_C6h)
{
    // Initial CPU State
    cpu.set_ax(0x81A5);
    cpu.set_bx(0x1932);
    cpu.set_cx(0x37B4);
    cpu.set_dx(0x78BF);
    cpu.set_cs(0x402F);
    cpu.set_ss(0x5D13);
    cpu.set_ds(0x65B7);
    cpu.set_es(0xFA40);
    cpu.set_sp(0xD05A);
    cpu.set_bp(0x9BDC);
    cpu.set_si(0x496C);
    cpu.set_di(0x66DA);
    cpu.set_ip(0x5BE6);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x45ED6, 0xCD);
    machine.mem_store_byte(0x45ED7, 0xC6);
    machine.mem_store_byte(0x45ED8, 0x90);
    machine.mem_store_byte(0x45ED9, 0x90);
    machine.mem_store_byte(0x00318, 0x6C);
    machine.mem_store_byte(0x00319, 0x59);
    machine.mem_store_byte(0x0031A, 0xA4);
    machine.mem_store_byte(0x0031B, 0x7A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x7AA4);
    EXPECT_EQ(cpu.get_sp(), 0xD054);
    EXPECT_EQ(cpu.get_ip(), 0x596C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6A188), 0x82);
    EXPECT_EQ(memory.load8(0x6A189), 0xF8);
    EXPECT_EQ(memory.load8(0x6A186), 0x2F);
    EXPECT_EQ(memory.load8(0x6A187), 0x40);
    EXPECT_EQ(memory.load8(0x6A184), 0xE8);
    EXPECT_EQ(memory.load8(0x6A185), 0x5B);
}

//
// into
//
TEST_F(MachineTest, into)
{
    // Initial CPU State
    cpu.set_ax(0xC325);
    cpu.set_bx(0xD068);
    cpu.set_cx(0xD516);
    cpu.set_dx(0x9563);
    cpu.set_cs(0xC8CA);
    cpu.set_ss(0x033C);
    cpu.set_ds(0x1153);
    cpu.set_es(0xF5B1);
    cpu.set_sp(0xD82F);
    cpu.set_bp(0x49F5);
    cpu.set_si(0x7462);
    cpu.set_di(0x5F30);
    cpu.set_ip(0x659F);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCF23F, 0xCE);
    machine.mem_store_byte(0xCF240, 0x90);
    machine.mem_store_byte(0xCF241, 0x90);
    machine.mem_store_byte(0xCF242, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x65A0);

    // Final RAM entries
}

//
// iret
//
TEST_F(MachineTest, iret)
{
    // Initial CPU State
    cpu.set_ax(0xBEE1);
    cpu.set_bx(0x594C);
    cpu.set_cx(0xEFDA);
    cpu.set_dx(0x39A3);
    cpu.set_cs(0xEBB0);
    cpu.set_ss(0x8B56);
    cpu.set_ds(0x02E7);
    cpu.set_es(0x389D);
    cpu.set_sp(0x6696);
    cpu.set_bp(0xBA48);
    cpu.set_si(0x816F);
    cpu.set_di(0xD321);
    cpu.set_ip(0xB0CE);
    cpu.set_flags(0xFCC6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF6BCE, 0xCF);
    machine.mem_store_byte(0xF6BCF, 0x90);
    machine.mem_store_byte(0xF6BD0, 0x90);
    machine.mem_store_byte(0xF6BD1, 0x90);
    machine.mem_store_byte(0x91BF6, 0x10);
    machine.mem_store_byte(0x91BF7, 0xCE);
    machine.mem_store_byte(0x91BF8, 0x6B);
    machine.mem_store_byte(0x91BF9, 0x19);
    machine.mem_store_byte(0x91BFA, 0xCF);
    machine.mem_store_byte(0x91BFB, 0x28);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x196B);
    EXPECT_EQ(cpu.get_sp(), 0x669C);
    EXPECT_EQ(cpu.get_ip(), 0xCE10);
    EXPECT_EQ(cpu.get_flags(), 0xF8C7);

    // Final RAM entries
}
