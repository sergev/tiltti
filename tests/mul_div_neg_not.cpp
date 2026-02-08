#include "fixture.h"

// Tests: mul, imul, div, idiv, neg, not

TEST_F(MachineTest, div_byte_ds_bx)
{
    // Initial CPU State
    cpu.set_ax(0x16B1);
    cpu.set_bx(0x4144);
    cpu.set_cx(0xF8DE);
    cpu.set_dx(0x3140);
    cpu.set_cs(0xE255);
    cpu.set_ss(0xB5F6);
    cpu.set_ds(0x54DD);
    cpu.set_es(0x39F6);
    cpu.set_sp(0x9771);
    cpu.set_bp(0x0000);
    cpu.set_si(0xAF49);
    cpu.set_di(0x0000);
    cpu.set_ip(0x8096);
    cpu.set_flags(0xF8D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEA5E6, 0xF6);
    machine.mem_store_byte(0xEA5E7, 0x37);
    machine.mem_store_byte(0xEA5E8, 0x90);
    machine.mem_store_byte(0xEA5E9, 0x90);
    machine.mem_store_byte(0xEA5EA, 0x90);
    machine.mem_store_byte(0xEA5EB, 0x90);
    machine.mem_store_byte(0x58F14, 0x82);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x592C);
    EXPECT_EQ(cpu.get_ip(), 0x8098);
    EXPECT_FLAGS(0xF887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEA5E6), 0xF6);
    EXPECT_EQ(memory.load8(0xEA5E7), 0x37);
    EXPECT_EQ(memory.load8(0xEA5E8), 0x90);
    EXPECT_EQ(memory.load8(0xEA5E9), 0x90);
    EXPECT_EQ(memory.load8(0xEA5EA), 0x90);
    EXPECT_EQ(memory.load8(0xEA5EB), 0x90);
    EXPECT_EQ(memory.load8(0x58F14), 0x82);
}

TEST_F(MachineTest, div_word_ds_si_39h)
{
    // Initial CPU State
    cpu.set_ax(0x1DAE);
    cpu.set_bx(0x229F);
    cpu.set_cx(0xB956);
    cpu.set_dx(0x9C34);
    cpu.set_cs(0x7AEF);
    cpu.set_ss(0xE97D);
    cpu.set_ds(0x4052);
    cpu.set_es(0x0EB9);
    cpu.set_sp(0xE763);
    cpu.set_bp(0x3BAE);
    cpu.set_si(0xA930);
    cpu.set_di(0xEE81);
    cpu.set_ip(0x4FF0);
    cpu.set_flags(0xF842);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7FEE0, 0xF7);
    machine.mem_store_byte(0x7FEE1, 0x74);
    machine.mem_store_byte(0x7FEE2, 0xC7);
    machine.mem_store_byte(0x7FEE3, 0x90);
    machine.mem_store_byte(0x7FEE4, 0x90);
    machine.mem_store_byte(0x7FEE5, 0x90);
    machine.mem_store_byte(0x4AE17, 0x12);
    machine.mem_store_byte(0x4AE18, 0xC2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xCE0C);
    EXPECT_EQ(cpu.get_dx(), 0x88D6);
    EXPECT_EQ(cpu.get_ip(), 0x4FF3);
    EXPECT_FLAGS(0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7FEE0), 0xF7);
    EXPECT_EQ(memory.load8(0x7FEE1), 0x74);
    EXPECT_EQ(memory.load8(0x7FEE2), 0xC7);
    EXPECT_EQ(memory.load8(0x7FEE3), 0x90);
    EXPECT_EQ(memory.load8(0x7FEE4), 0x90);
    EXPECT_EQ(memory.load8(0x7FEE5), 0x90);
    EXPECT_EQ(memory.load8(0x4AE17), 0x12);
    EXPECT_EQ(memory.load8(0x4AE18), 0xC2);
}

TEST_F(MachineTest, idiv_byte_ds_bx_si_5AD8h)
{
    // Initial CPU State
    cpu.set_ax(0x7E46);
    cpu.set_bx(0x2E0F);
    cpu.set_cx(0x65F2);
    cpu.set_dx(0xD127);
    cpu.set_cs(0x6CB7);
    cpu.set_ss(0xC56C);
    cpu.set_ds(0xBE56);
    cpu.set_es(0x81F1);
    cpu.set_sp(0x4355);
    cpu.set_bp(0x60F7);
    cpu.set_si(0x49FF);
    cpu.set_di(0xFD3D);
    cpu.set_ip(0x123C);
    cpu.set_flags(0xF842);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6DDAC, 0x3E);
    machine.mem_store_byte(0x6DDAD, 0xF6);
    machine.mem_store_byte(0x6DDAE, 0xB8);
    machine.mem_store_byte(0x6DDAF, 0xD8);
    machine.mem_store_byte(0x6DDB0, 0x5A);
    machine.mem_store_byte(0x6DDB1, 0x90);
    machine.mem_store_byte(0xCB846, 0x1F);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x434F);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6DDAC), 0x3E);
    EXPECT_EQ(memory.load8(0x6DDAD), 0xF6);
    EXPECT_EQ(memory.load8(0x6DDAE), 0xB8);
    EXPECT_EQ(memory.load8(0x6DDAF), 0xD8);
    EXPECT_EQ(memory.load8(0x6DDB0), 0x5A);
    EXPECT_EQ(memory.load8(0x6DDB1), 0x90);
    EXPECT_EQ(memory.load8(0xCB846), 0x1F);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_FLAGS_LO(0xC9A13, 0x16);
    EXPECT_FLAGS_HI(0xC9A14, 0xF0);
    EXPECT_EQ(memory.load8(0xC9A11), 0xB7);
    EXPECT_EQ(memory.load8(0xC9A12), 0x6C);
    EXPECT_EQ(memory.load8(0xC9A0F), 0x41);
    EXPECT_EQ(memory.load8(0xC9A10), 0x12);
}

TEST_F(MachineTest, idiv_word_ss_bp_di)
{
    // Initial CPU State
    cpu.set_ax(0xCB93);
    cpu.set_bx(0xE9F9);
    cpu.set_cx(0x1C52);
    cpu.set_dx(0x1853);
    cpu.set_cs(0x45C8);
    cpu.set_ss(0x4C7A);
    cpu.set_ds(0xF01A);
    cpu.set_es(0x6871);
    cpu.set_sp(0x08B6);
    cpu.set_bp(0x2F9D);
    cpu.set_si(0x6C32);
    cpu.set_di(0xC961);
    cpu.set_ip(0x4566);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4A1E6, 0xF7);
    machine.mem_store_byte(0x4A1E7, 0x3B);
    machine.mem_store_byte(0x4A1E8, 0x90);
    machine.mem_store_byte(0x4A1E9, 0x90);
    machine.mem_store_byte(0x4A1EA, 0x90);
    machine.mem_store_byte(0x4A1EB, 0x90);
    machine.mem_store_byte(0x5C09E, 0x7B);
    machine.mem_store_byte(0x5C09F, 0x00);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x08B0);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4A1E6), 0xF7);
    EXPECT_EQ(memory.load8(0x4A1E7), 0x3B);
    EXPECT_EQ(memory.load8(0x4A1E8), 0x90);
    EXPECT_EQ(memory.load8(0x4A1E9), 0x90);
    EXPECT_EQ(memory.load8(0x4A1EA), 0x90);
    EXPECT_EQ(memory.load8(0x4A1EB), 0x90);
    EXPECT_EQ(memory.load8(0x5C09E), 0x7B);
    EXPECT_EQ(memory.load8(0x5C09F), 0x00);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x4D054), 0x16 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0x4D055), 0xF4 & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0x4D052), 0xC8);
    EXPECT_EQ(memory.load8(0x4D053), 0x45);
    EXPECT_EQ(memory.load8(0x4D050), 0x68);
    EXPECT_EQ(memory.load8(0x4D051), 0x45);
}

TEST_F(MachineTest, imul_byte_es_bp_si_2Eh)
{
    // Initial CPU State
    cpu.set_ax(0x4F34);
    cpu.set_bx(0xA9AB);
    cpu.set_cx(0xAA96);
    cpu.set_dx(0x2450);
    cpu.set_cs(0x1574);
    cpu.set_ss(0x79D8);
    cpu.set_ds(0x6757);
    cpu.set_es(0x24FA);
    cpu.set_sp(0x81D7);
    cpu.set_bp(0x1423);
    cpu.set_si(0xEA35);
    cpu.set_di(0xDDB9);
    cpu.set_ip(0x50C7);
    cpu.set_flags(0xF886);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1A807, 0x26);
    machine.mem_store_byte(0x1A808, 0xF6);
    machine.mem_store_byte(0x1A809, 0x6A);
    machine.mem_store_byte(0x1A80A, 0x2E);
    machine.mem_store_byte(0x1A80B, 0x90);
    machine.mem_store_byte(0x34E26, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0x50CB);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1A807), 0x26);
    EXPECT_EQ(memory.load8(0x1A808), 0xF6);
    EXPECT_EQ(memory.load8(0x1A809), 0x6A);
    EXPECT_EQ(memory.load8(0x1A80A), 0x2E);
    EXPECT_EQ(memory.load8(0x1A80B), 0x90);
    EXPECT_EQ(memory.load8(0x34E26), 0x00);
}

TEST_F(MachineTest, imul_word_cs_si)
{
    // Initial CPU State
    cpu.set_ax(0xE4CD);
    cpu.set_bx(0x1536);
    cpu.set_cx(0x1EC0);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xD629);
    cpu.set_ss(0x1422);
    cpu.set_ds(0xDD51);
    cpu.set_es(0xE3AB);
    cpu.set_sp(0x693E);
    cpu.set_bp(0xACA9);
    cpu.set_si(0xFEA1);
    cpu.set_di(0x4302);
    cpu.set_ip(0x6012);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDC2A2, 0x2E);
    machine.mem_store_byte(0xDC2A3, 0xF7);
    machine.mem_store_byte(0xDC2A4, 0x2C);
    machine.mem_store_byte(0xDC2A5, 0x90);
    machine.mem_store_byte(0xDC2A6, 0x90);
    machine.mem_store_byte(0xDC2A7, 0x90);
    machine.mem_store_byte(0xE6131, 0x9B);
    machine.mem_store_byte(0xE6132, 0x5E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xCE1F);
    EXPECT_EQ(cpu.get_dx(), 0xF5F2);
    EXPECT_EQ(cpu.get_ip(), 0x6015);
    EXPECT_FLAGS(0xF887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDC2A2), 0x2E);
    EXPECT_EQ(memory.load8(0xDC2A3), 0xF7);
    EXPECT_EQ(memory.load8(0xDC2A4), 0x2C);
    EXPECT_EQ(memory.load8(0xDC2A5), 0x90);
    EXPECT_EQ(memory.load8(0xDC2A6), 0x90);
    EXPECT_EQ(memory.load8(0xDC2A7), 0x90);
    EXPECT_EQ(memory.load8(0xE6131), 0x9B);
    EXPECT_EQ(memory.load8(0xE6132), 0x5E);
}

TEST_F(MachineTest, mul_byte_ss_bp_di_79h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x6350);
    cpu.set_cx(0x351C);
    cpu.set_dx(0x5EEB);
    cpu.set_cs(0x3110);
    cpu.set_ss(0xE264);
    cpu.set_ds(0x12F9);
    cpu.set_es(0xD8A7);
    cpu.set_sp(0x26BA);
    cpu.set_bp(0xB579);
    cpu.set_si(0x41D4);
    cpu.set_di(0xFDCE);
    cpu.set_ip(0xAA9C);
    cpu.set_flags(0xF447);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3BB9C, 0xF6);
    machine.mem_store_byte(0x3BB9D, 0x63);
    machine.mem_store_byte(0x3BB9E, 0x79);
    machine.mem_store_byte(0x3BB9F, 0x90);
    machine.mem_store_byte(0x3BBA0, 0x90);
    machine.mem_store_byte(0x3BBA1, 0x90);
    machine.mem_store_byte(0xEDA00, 0xBC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAA9F);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3BB9C), 0xF6);
    EXPECT_EQ(memory.load8(0x3BB9D), 0x63);
    EXPECT_EQ(memory.load8(0x3BB9E), 0x79);
    EXPECT_EQ(memory.load8(0x3BB9F), 0x90);
    EXPECT_EQ(memory.load8(0x3BBA0), 0x90);
    EXPECT_EQ(memory.load8(0x3BBA1), 0x90);
    EXPECT_EQ(memory.load8(0xEDA00), 0xBC);
}

TEST_F(MachineTest, mul_word_es_bp_di_75h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0xDD89);
    cpu.set_cx(0xA2B8);
    cpu.set_dx(0xE942);
    cpu.set_cs(0x820A);
    cpu.set_ss(0x5ED0);
    cpu.set_ds(0x18CD);
    cpu.set_es(0x4BEB);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x63A7);
    cpu.set_si(0x7379);
    cpu.set_di(0xF73B);
    cpu.set_ip(0x9F4A);
    cpu.set_flags(0xF856);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8BFEA, 0x26);
    machine.mem_store_byte(0x8BFEB, 0xF7);
    machine.mem_store_byte(0x8BFEC, 0x63);
    machine.mem_store_byte(0x8BFED, 0x8B);
    machine.mem_store_byte(0x8BFEE, 0x90);
    machine.mem_store_byte(0x8BFEF, 0x90);
    machine.mem_store_byte(0x5191D, 0x91);
    machine.mem_store_byte(0x5191E, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0x9F4E);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8BFEA), 0x26);
    EXPECT_EQ(memory.load8(0x8BFEB), 0xF7);
    EXPECT_EQ(memory.load8(0x8BFEC), 0x63);
    EXPECT_EQ(memory.load8(0x8BFED), 0x8B);
    EXPECT_EQ(memory.load8(0x8BFEE), 0x90);
    EXPECT_EQ(memory.load8(0x8BFEF), 0x90);
    EXPECT_EQ(memory.load8(0x5191D), 0x91);
    EXPECT_EQ(memory.load8(0x5191E), 0x00);
}

TEST_F(MachineTest, neg_ah)
{
    // Initial CPU State
    cpu.set_ax(0xCC37);
    cpu.set_bx(0xABAC);
    cpu.set_cx(0xAB1C);
    cpu.set_dx(0xCEC1);
    cpu.set_cs(0x61AD);
    cpu.set_ss(0x3881);
    cpu.set_ds(0x0897);
    cpu.set_es(0x26C5);
    cpu.set_sp(0x120D);
    cpu.set_bp(0x1626);
    cpu.set_si(0x1704);
    cpu.set_di(0x720C);
    cpu.set_ip(0xCEDD);
    cpu.set_flags(0xF4D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6E9AD, 0xF6);
    machine.mem_store_byte(0x6E9AE, 0xDC);
    machine.mem_store_byte(0x6E9AF, 0x90);
    machine.mem_store_byte(0x6E9B0, 0x90);
    machine.mem_store_byte(0x6E9B1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x3437);
    EXPECT_EQ(cpu.get_ip(), 0xCEDF);
    EXPECT_FLAGS(0xF413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6E9AD), 0xF6);
    EXPECT_EQ(memory.load8(0x6E9AE), 0xDC);
    EXPECT_EQ(memory.load8(0x6E9AF), 0x90);
    EXPECT_EQ(memory.load8(0x6E9B0), 0x90);
    EXPECT_EQ(memory.load8(0x6E9B1), 0x90);
}

TEST_F(MachineTest, neg_word_ds_si_3h)
{
    // Initial CPU State
    cpu.set_ax(0x276E);
    cpu.set_bx(0x439E);
    cpu.set_cx(0xA270);
    cpu.set_dx(0x6EBC);
    cpu.set_cs(0x36D8);
    cpu.set_ss(0xA2EC);
    cpu.set_ds(0x98ED);
    cpu.set_es(0x4CE6);
    cpu.set_sp(0x926D);
    cpu.set_bp(0x472F);
    cpu.set_si(0x2FEF);
    cpu.set_di(0x2D46);
    cpu.set_ip(0x68AE);
    cpu.set_flags(0xF407);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3D62E, 0xF7);
    machine.mem_store_byte(0x3D62F, 0x5C);
    machine.mem_store_byte(0x3D630, 0xFD);
    machine.mem_store_byte(0x3D631, 0x90);
    machine.mem_store_byte(0x3D632, 0x90);
    machine.mem_store_byte(0x3D633, 0x90);
    machine.mem_store_byte(0x9BEBC, 0x28);
    machine.mem_store_byte(0x9BEBD, 0x97);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x68B1);
    EXPECT_FLAGS(0xF417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3D62E), 0xF7);
    EXPECT_EQ(memory.load8(0x3D62F), 0x5C);
    EXPECT_EQ(memory.load8(0x3D630), 0xFD);
    EXPECT_EQ(memory.load8(0x3D631), 0x90);
    EXPECT_EQ(memory.load8(0x3D632), 0x90);
    EXPECT_EQ(memory.load8(0x3D633), 0x90);
    EXPECT_EQ(memory.load8(0x9BEBC), 0xD8);
    EXPECT_EQ(memory.load8(0x9BEBD), 0x68);
}

TEST_F(MachineTest, not_byte_ds_bx_di_26h)
{
    // Initial CPU State
    cpu.set_ax(0x8B8D);
    cpu.set_bx(0xBCDC);
    cpu.set_cx(0x5354);
    cpu.set_dx(0xBCC7);
    cpu.set_cs(0xE4C1);
    cpu.set_ss(0xD726);
    cpu.set_ds(0x27D4);
    cpu.set_es(0x8E1F);
    cpu.set_sp(0xE541);
    cpu.set_bp(0x7A17);
    cpu.set_si(0xEE72);
    cpu.set_di(0x0804);
    cpu.set_ip(0x75BC);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEC1CC, 0xF6);
    machine.mem_store_byte(0xEC1CD, 0x51);
    machine.mem_store_byte(0xEC1CE, 0xDA);
    machine.mem_store_byte(0xEC1CF, 0x90);
    machine.mem_store_byte(0xEC1D0, 0x90);
    machine.mem_store_byte(0xEC1D1, 0x90);
    machine.mem_store_byte(0x341FA, 0x13);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x75BF);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEC1CC), 0xF6);
    EXPECT_EQ(memory.load8(0xEC1CD), 0x51);
    EXPECT_EQ(memory.load8(0xEC1CE), 0xDA);
    EXPECT_EQ(memory.load8(0xEC1CF), 0x90);
    EXPECT_EQ(memory.load8(0xEC1D0), 0x90);
    EXPECT_EQ(memory.load8(0xEC1D1), 0x90);
    EXPECT_EQ(memory.load8(0x341FA), 0xEC);
}

TEST_F(MachineTest, not_word_ss_bp_Eh)
{
    // Initial CPU State
    cpu.set_ax(0x356C);
    cpu.set_bx(0xBA6E);
    cpu.set_cx(0x4CC4);
    cpu.set_dx(0xC273);
    cpu.set_cs(0xE075);
    cpu.set_ss(0xA695);
    cpu.set_ds(0x2C9E);
    cpu.set_es(0xF816);
    cpu.set_sp(0x3508);
    cpu.set_bp(0xD0B0);
    cpu.set_si(0x33FF);
    cpu.set_di(0x05CC);
    cpu.set_ip(0x6EFA);
    cpu.set_flags(0xF892);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE764A, 0xF7);
    machine.mem_store_byte(0xE764B, 0x56);
    machine.mem_store_byte(0xE764C, 0x0E);
    machine.mem_store_byte(0xE764D, 0x90);
    machine.mem_store_byte(0xE764E, 0x90);
    machine.mem_store_byte(0xE764F, 0x90);
    machine.mem_store_byte(0xB3A0E, 0xC5);
    machine.mem_store_byte(0xB3A0F, 0xD4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6EFD);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE764A), 0xF7);
    EXPECT_EQ(memory.load8(0xE764B), 0x56);
    EXPECT_EQ(memory.load8(0xE764C), 0x0E);
    EXPECT_EQ(memory.load8(0xE764D), 0x90);
    EXPECT_EQ(memory.load8(0xE764E), 0x90);
    EXPECT_EQ(memory.load8(0xE764F), 0x90);
    EXPECT_EQ(memory.load8(0xB3A0E), 0x3A);
    EXPECT_EQ(memory.load8(0xB3A0F), 0x2B);
}
