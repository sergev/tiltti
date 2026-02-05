#include "fixture.h"

// Tests: xchg, lea, lds, les

TEST_F(MachineTest, lds_sp_dword_ss_bx_si_3E2Ch)
{
    // Initial CPU State
    cpu.set_ax(0xCB3A);
    cpu.set_bx(0x1972);
    cpu.set_cx(0x027E);
    cpu.set_dx(0x3326);
    cpu.set_cs(0x60CE);
    cpu.set_ss(0x74C8);
    cpu.set_ds(0xCBE1);
    cpu.set_es(0x8891);
    cpu.set_sp(0x8EB9);
    cpu.set_bp(0xF5A4);
    cpu.set_si(0xAB9F);
    cpu.set_di(0xF107);
    cpu.set_ip(0x69D4);
    cpu.set_flags(0xF453);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x676B4, 0x36);
    machine.mem_store_byte(0x676B5, 0xC5);
    machine.mem_store_byte(0x676B6, 0xA0);
    machine.mem_store_byte(0x676B7, 0x2C);
    machine.mem_store_byte(0x676B8, 0x3E);
    machine.mem_store_byte(0x676B9, 0x90);
    machine.mem_store_byte(0x74FBD, 0xDB);
    machine.mem_store_byte(0x74FBE, 0x09);
    machine.mem_store_byte(0x74FBF, 0x88);
    machine.mem_store_byte(0x74FC0, 0x3E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ds(), 0x3E88);
    EXPECT_EQ(cpu.get_sp(), 0x09DB);
    EXPECT_EQ(cpu.get_ip(), 0x69D9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x676B4), 0x36);
    EXPECT_EQ(memory.load8(0x676B5), 0xC5);
    EXPECT_EQ(memory.load8(0x676B6), 0xA0);
    EXPECT_EQ(memory.load8(0x676B7), 0x2C);
    EXPECT_EQ(memory.load8(0x676B8), 0x3E);
    EXPECT_EQ(memory.load8(0x676B9), 0x90);
    EXPECT_EQ(memory.load8(0x74FBD), 0xDB);
    EXPECT_EQ(memory.load8(0x74FBE), 0x09);
    EXPECT_EQ(memory.load8(0x74FBF), 0x88);
    EXPECT_EQ(memory.load8(0x74FC0), 0x3E);
}

TEST_F(MachineTest, lea_sp_es_bp_si_75h)
{
    // Initial CPU State
    cpu.set_ax(0x0AA1);
    cpu.set_bx(0xFE6B);
    cpu.set_cx(0xF010);
    cpu.set_dx(0x7037);
    cpu.set_cs(0xEF9B);
    cpu.set_ss(0x5481);
    cpu.set_ds(0x4C3B);
    cpu.set_es(0x61A4);
    cpu.set_sp(0xD1FD);
    cpu.set_bp(0xD8DB);
    cpu.set_si(0x0B5D);
    cpu.set_di(0x2731);
    cpu.set_ip(0x8A65);
    cpu.set_flags(0xF412);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8415, 0x26);
    machine.mem_store_byte(0xF8416, 0x8D);
    machine.mem_store_byte(0xF8417, 0x62);
    machine.mem_store_byte(0xF8418, 0x8B);
    machine.mem_store_byte(0xF8419, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xE3C3);
    EXPECT_EQ(cpu.get_ip(), 0x8A69);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF8415), 0x26);
    EXPECT_EQ(memory.load8(0xF8416), 0x8D);
    EXPECT_EQ(memory.load8(0xF8417), 0x62);
    EXPECT_EQ(memory.load8(0xF8418), 0x8B);
    EXPECT_EQ(memory.load8(0xF8419), 0x90);
}

TEST_F(MachineTest, les_bx_dword_cs_bx_si_3Bh)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x1247);
    cpu.set_cx(0x1CB4);
    cpu.set_dx(0xDDC6);
    cpu.set_cs(0x4E35);
    cpu.set_ss(0x7C6A);
    cpu.set_ds(0xAA01);
    cpu.set_es(0xF069);
    cpu.set_sp(0x6FBE);
    cpu.set_bp(0x6B90);
    cpu.set_si(0xA70A);
    cpu.set_di(0xFD3F);
    cpu.set_ip(0x12CE);
    cpu.set_flags(0xF402);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4F61E, 0x2E);
    machine.mem_store_byte(0x4F61F, 0xC4);
    machine.mem_store_byte(0x4F620, 0x58);
    machine.mem_store_byte(0x4F621, 0x3B);
    machine.mem_store_byte(0x4F622, 0x90);
    machine.mem_store_byte(0x4F623, 0x90);
    machine.mem_store_byte(0x59CDC, 0x40);
    machine.mem_store_byte(0x59CDD, 0x90);
    machine.mem_store_byte(0x59CDE, 0x00);
    machine.mem_store_byte(0x59CDF, 0x2D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x9040);
    EXPECT_EQ(cpu.get_es(), 0x2D00);
    EXPECT_EQ(cpu.get_ip(), 0x12D2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4F61E), 0x2E);
    EXPECT_EQ(memory.load8(0x4F61F), 0xC4);
    EXPECT_EQ(memory.load8(0x4F620), 0x58);
    EXPECT_EQ(memory.load8(0x4F621), 0x3B);
    EXPECT_EQ(memory.load8(0x4F622), 0x90);
    EXPECT_EQ(memory.load8(0x4F623), 0x90);
    EXPECT_EQ(memory.load8(0x59CDC), 0x40);
    EXPECT_EQ(memory.load8(0x59CDD), 0x90);
    EXPECT_EQ(memory.load8(0x59CDE), 0x00);
    EXPECT_EQ(memory.load8(0x59CDF), 0x2D);
}

TEST_F(MachineTest, xchg_bp_ax)
{
    // Initial CPU State
    cpu.set_ax(0x25A8);
    cpu.set_bx(0x929B);
    cpu.set_cx(0x358A);
    cpu.set_dx(0x2E3A);
    cpu.set_cs(0x8FE2);
    cpu.set_ss(0xEAA2);
    cpu.set_ds(0x0545);
    cpu.set_es(0x122E);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x9694);
    cpu.set_si(0x9C7E);
    cpu.set_di(0x9258);
    cpu.set_ip(0x5BD7);
    cpu.set_flags(0xF0D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x959F7, 0x95);
    machine.mem_store_byte(0x959F8, 0x90);
    machine.mem_store_byte(0x959F9, 0x90);
    machine.mem_store_byte(0x959FA, 0x90);
    machine.mem_store_byte(0x959FB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9694);
    EXPECT_EQ(cpu.get_bp(), 0x25A8);
    EXPECT_EQ(cpu.get_ip(), 0x5BD8);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x959F7), 0x95);
    EXPECT_EQ(memory.load8(0x959F8), 0x90);
    EXPECT_EQ(memory.load8(0x959F9), 0x90);
    EXPECT_EQ(memory.load8(0x959FA), 0x90);
    EXPECT_EQ(memory.load8(0x959FB), 0x90);
}

TEST_F(MachineTest, xchg_bx_ax)
{
    // Initial CPU State
    cpu.set_ax(0x06E3);
    cpu.set_bx(0x0329);
    cpu.set_cx(0x1476);
    cpu.set_dx(0xBB5B);
    cpu.set_cs(0x5CCF);
    cpu.set_ss(0x1A2D);
    cpu.set_ds(0xFE30);
    cpu.set_es(0x7BFC);
    cpu.set_sp(0x64E9);
    cpu.set_bp(0xC2DF);
    cpu.set_si(0xD4DF);
    cpu.set_di(0x928A);
    cpu.set_ip(0x452A);
    cpu.set_flags(0xF002);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6121A, 0x93);
    machine.mem_store_byte(0x6121B, 0x90);
    machine.mem_store_byte(0x6121C, 0x90);
    machine.mem_store_byte(0x6121D, 0x90);
    machine.mem_store_byte(0x6121E, 0x90);
    machine.mem_store_byte(0x6121F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0329);
    EXPECT_EQ(cpu.get_bx(), 0x06E3);
    EXPECT_EQ(cpu.get_ip(), 0x452B);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6121A), 0x93);
    EXPECT_EQ(memory.load8(0x6121B), 0x90);
    EXPECT_EQ(memory.load8(0x6121C), 0x90);
    EXPECT_EQ(memory.load8(0x6121D), 0x90);
    EXPECT_EQ(memory.load8(0x6121E), 0x90);
    EXPECT_EQ(memory.load8(0x6121F), 0x90);
}

TEST_F(MachineTest, xchg_cx_ax)
{
    // Initial CPU State
    cpu.set_ax(0x2E4B);
    cpu.set_bx(0xCCD1);
    cpu.set_cx(0x113A);
    cpu.set_dx(0x95BE);
    cpu.set_cs(0xB60A);
    cpu.set_ss(0xE615);
    cpu.set_ds(0xC3AA);
    cpu.set_es(0x4782);
    cpu.set_sp(0xFDA5);
    cpu.set_bp(0xADB4);
    cpu.set_si(0xE3B2);
    cpu.set_di(0xF90E);
    cpu.set_ip(0x287D);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB891D, 0x91);
    machine.mem_store_byte(0xB891E, 0x90);
    machine.mem_store_byte(0xB891F, 0x90);
    machine.mem_store_byte(0xB8920, 0x90);
    machine.mem_store_byte(0xB8921, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x113A);
    EXPECT_EQ(cpu.get_cx(), 0x2E4B);
    EXPECT_EQ(cpu.get_ip(), 0x287E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB891D), 0x91);
    EXPECT_EQ(memory.load8(0xB891E), 0x90);
    EXPECT_EQ(memory.load8(0xB891F), 0x90);
    EXPECT_EQ(memory.load8(0xB8920), 0x90);
    EXPECT_EQ(memory.load8(0xB8921), 0x90);
}

TEST_F(MachineTest, xchg_dh_dh)
{
    // Initial CPU State
    cpu.set_ax(0x32CE);
    cpu.set_bx(0x6ECD);
    cpu.set_cx(0x4CE8);
    cpu.set_dx(0x2E23);
    cpu.set_cs(0x2E77);
    cpu.set_ss(0x1DAF);
    cpu.set_ds(0xE975);
    cpu.set_es(0x40E7);
    cpu.set_sp(0x19B8);
    cpu.set_bp(0xF7EC);
    cpu.set_si(0x8F05);
    cpu.set_di(0x8486);
    cpu.set_ip(0x5136);
    cpu.set_flags(0xF8D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x338A6, 0x36);
    machine.mem_store_byte(0x338A7, 0x86);
    machine.mem_store_byte(0x338A8, 0xF6);
    machine.mem_store_byte(0x338A9, 0x90);
    machine.mem_store_byte(0x338AA, 0x90);
    machine.mem_store_byte(0x338AB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5139);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x338A6), 0x36);
    EXPECT_EQ(memory.load8(0x338A7), 0x86);
    EXPECT_EQ(memory.load8(0x338A8), 0xF6);
    EXPECT_EQ(memory.load8(0x338A9), 0x90);
    EXPECT_EQ(memory.load8(0x338AA), 0x90);
    EXPECT_EQ(memory.load8(0x338AB), 0x90);
}

TEST_F(MachineTest, xchg_di_ax)
{
    // Initial CPU State
    cpu.set_ax(0x159D);
    cpu.set_bx(0x706F);
    cpu.set_cx(0x7AC4);
    cpu.set_dx(0xD116);
    cpu.set_cs(0x7559);
    cpu.set_ss(0xD583);
    cpu.set_ds(0xF000);
    cpu.set_es(0x4E55);
    cpu.set_sp(0x8C88);
    cpu.set_bp(0x0624);
    cpu.set_si(0x155E);
    cpu.set_di(0xB8C4);
    cpu.set_ip(0x405E);
    cpu.set_flags(0xF0D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x795EE, 0x97);
    machine.mem_store_byte(0x795EF, 0x90);
    machine.mem_store_byte(0x795F0, 0x90);
    machine.mem_store_byte(0x795F1, 0x90);
    machine.mem_store_byte(0x795F2, 0x90);
    machine.mem_store_byte(0x795F3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xB8C4);
    EXPECT_EQ(cpu.get_di(), 0x159D);
    EXPECT_EQ(cpu.get_ip(), 0x405F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x795EE), 0x97);
    EXPECT_EQ(memory.load8(0x795EF), 0x90);
    EXPECT_EQ(memory.load8(0x795F0), 0x90);
    EXPECT_EQ(memory.load8(0x795F1), 0x90);
    EXPECT_EQ(memory.load8(0x795F2), 0x90);
    EXPECT_EQ(memory.load8(0x795F3), 0x90);
}

TEST_F(MachineTest, xchg_di_word_ss_bp_si_31F6h)
{
    // Initial CPU State
    cpu.set_ax(0xB4B0);
    cpu.set_bx(0x696C);
    cpu.set_cx(0x9868);
    cpu.set_dx(0x91AD);
    cpu.set_cs(0x93AB);
    cpu.set_ss(0xBBF6);
    cpu.set_ds(0xBEA6);
    cpu.set_es(0xBACE);
    cpu.set_sp(0x9872);
    cpu.set_bp(0x825B);
    cpu.set_si(0x8F64);
    cpu.set_di(0xEE5B);
    cpu.set_ip(0x9C4E);
    cpu.set_flags(0xF082);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9D6FE, 0x87);
    machine.mem_store_byte(0x9D6FF, 0xBA);
    machine.mem_store_byte(0x9D700, 0x0A);
    machine.mem_store_byte(0x9D701, 0xCE);
    machine.mem_store_byte(0x9D702, 0x90);
    machine.mem_store_byte(0x9D703, 0x90);
    machine.mem_store_byte(0xC9F29, 0x19);
    machine.mem_store_byte(0xC9F2A, 0xD3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xD319);
    EXPECT_EQ(cpu.get_ip(), 0x9C52);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9D6FE), 0x87);
    EXPECT_EQ(memory.load8(0x9D6FF), 0xBA);
    EXPECT_EQ(memory.load8(0x9D700), 0x0A);
    EXPECT_EQ(memory.load8(0x9D701), 0xCE);
    EXPECT_EQ(memory.load8(0x9D702), 0x90);
    EXPECT_EQ(memory.load8(0x9D703), 0x90);
    EXPECT_EQ(memory.load8(0xC9F29), 0x5B);
    EXPECT_EQ(memory.load8(0xC9F2A), 0xEE);
}

TEST_F(MachineTest, xchg_dx_ax)
{
    // Initial CPU State
    cpu.set_ax(0x58A1);
    cpu.set_bx(0xAFDE);
    cpu.set_cx(0x916A);
    cpu.set_dx(0x974D);
    cpu.set_cs(0x9513);
    cpu.set_ss(0x6F1A);
    cpu.set_ds(0x1D1F);
    cpu.set_es(0x6D26);
    cpu.set_sp(0xA366);
    cpu.set_bp(0x1D83);
    cpu.set_si(0x81D5);
    cpu.set_di(0xBD09);
    cpu.set_ip(0xFBDD);
    cpu.set_flags(0xF092);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA4D0D, 0x92);
    machine.mem_store_byte(0xA4D0E, 0x90);
    machine.mem_store_byte(0xA4D0F, 0x90);
    machine.mem_store_byte(0xA4D10, 0x90);
    machine.mem_store_byte(0xA4D11, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x974D);
    EXPECT_EQ(cpu.get_dx(), 0x58A1);
    EXPECT_EQ(cpu.get_ip(), 0xFBDE);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA4D0D), 0x92);
    EXPECT_EQ(memory.load8(0xA4D0E), 0x90);
    EXPECT_EQ(memory.load8(0xA4D0F), 0x90);
    EXPECT_EQ(memory.load8(0xA4D10), 0x90);
    EXPECT_EQ(memory.load8(0xA4D11), 0x90);
}

TEST_F(MachineTest, xchg_si_ax)
{
    // Initial CPU State
    cpu.set_ax(0x3D31);
    cpu.set_bx(0xC18E);
    cpu.set_cx(0x0000);
    cpu.set_dx(0xFF05);
    cpu.set_cs(0x1511);
    cpu.set_ss(0x4778);
    cpu.set_ds(0xDDB7);
    cpu.set_es(0xFB2E);
    cpu.set_sp(0x9789);
    cpu.set_bp(0xE8CE);
    cpu.set_si(0x2520);
    cpu.set_di(0xD369);
    cpu.set_ip(0x5B9E);
    cpu.set_flags(0xF446);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1ACAE, 0x96);
    machine.mem_store_byte(0x1ACAF, 0x90);
    machine.mem_store_byte(0x1ACB0, 0x90);
    machine.mem_store_byte(0x1ACB1, 0x90);
    machine.mem_store_byte(0x1ACB2, 0x90);
    machine.mem_store_byte(0x1ACB3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2520);
    EXPECT_EQ(cpu.get_si(), 0x3D31);
    EXPECT_EQ(cpu.get_ip(), 0x5B9F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1ACAE), 0x96);
    EXPECT_EQ(memory.load8(0x1ACAF), 0x90);
    EXPECT_EQ(memory.load8(0x1ACB0), 0x90);
    EXPECT_EQ(memory.load8(0x1ACB1), 0x90);
    EXPECT_EQ(memory.load8(0x1ACB2), 0x90);
    EXPECT_EQ(memory.load8(0x1ACB3), 0x90);
}

TEST_F(MachineTest, xchg_sp_ax)
{
    // Initial CPU State
    cpu.set_ax(0x3ECB);
    cpu.set_bx(0x50DF);
    cpu.set_cx(0xF48E);
    cpu.set_dx(0xB4B0);
    cpu.set_cs(0x6000);
    cpu.set_ss(0xAACF);
    cpu.set_ds(0x8823);
    cpu.set_es(0x3B09);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x4C9C);
    cpu.set_si(0x1752);
    cpu.set_di(0x7C13);
    cpu.set_ip(0xFE7C);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6FE7C, 0x94);
    machine.mem_store_byte(0x6FE7D, 0x90);
    machine.mem_store_byte(0x6FE7E, 0x90);
    machine.mem_store_byte(0x6FE7F, 0x90);
    machine.mem_store_byte(0x6FE80, 0x90);
    machine.mem_store_byte(0x6FE81, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x3ECB);
    EXPECT_EQ(cpu.get_ip(), 0xFE7D);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6FE7C), 0x94);
    EXPECT_EQ(memory.load8(0x6FE7D), 0x90);
    EXPECT_EQ(memory.load8(0x6FE7E), 0x90);
    EXPECT_EQ(memory.load8(0x6FE7F), 0x90);
    EXPECT_EQ(memory.load8(0x6FE80), 0x90);
    EXPECT_EQ(memory.load8(0x6FE81), 0x90);
}
