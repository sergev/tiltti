#include "fixture.h"

// Tests: cmp, test

TEST_F(MachineTest, cmp_al_DBh)
{
    // Initial CPU State
    cpu.set_ax(0xDFF6);
    cpu.set_bx(0x5070);
    cpu.set_cx(0x275E);
    cpu.set_dx(0x961A);
    cpu.set_cs(0x6441);
    cpu.set_ss(0x982B);
    cpu.set_ds(0x34E2);
    cpu.set_es(0xB9B1);
    cpu.set_sp(0x0CE2);
    cpu.set_bp(0x8922);
    cpu.set_si(0x561F);
    cpu.set_di(0x61DA);
    cpu.set_ip(0x0F81);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x65391, 0x3C);
    machine.mem_store_byte(0x65392, 0xDB);
    machine.mem_store_byte(0x65393, 0x90);
    machine.mem_store_byte(0x65394, 0x90);
    machine.mem_store_byte(0x65395, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0F83);
    EXPECT_EQ(cpu.get_flags(), 0xF016) << show_flags(0xF016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x65391), 0x3C);
    EXPECT_EQ(memory.load8(0x65392), 0xDB);
    EXPECT_EQ(memory.load8(0x65393), 0x90);
    EXPECT_EQ(memory.load8(0x65394), 0x90);
    EXPECT_EQ(memory.load8(0x65395), 0x90);
}

TEST_F(MachineTest, cmp_ax_494Bh)
{
    // Initial CPU State
    cpu.set_ax(0x5043);
    cpu.set_bx(0xAC00);
    cpu.set_cx(0x3F70);
    cpu.set_dx(0x2D18);
    cpu.set_cs(0xB640);
    cpu.set_ss(0xF5B4);
    cpu.set_ds(0x9437);
    cpu.set_es(0x6041);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xCE6B);
    cpu.set_si(0x71D3);
    cpu.set_di(0xC18C);
    cpu.set_ip(0x35D9);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB99D9, 0x36);
    machine.mem_store_byte(0xB99DA, 0x3D);
    machine.mem_store_byte(0xB99DB, 0x4B);
    machine.mem_store_byte(0xB99DC, 0x49);
    machine.mem_store_byte(0xB99DD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x35DD);
    EXPECT_EQ(cpu.get_flags(), 0xF012) << show_flags(0xF012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB99D9), 0x36);
    EXPECT_EQ(memory.load8(0xB99DA), 0x3D);
    EXPECT_EQ(memory.load8(0xB99DB), 0x4B);
    EXPECT_EQ(memory.load8(0xB99DC), 0x49);
    EXPECT_EQ(memory.load8(0xB99DD), 0x90);
}

TEST_F(MachineTest, cmp_byte_ss_bp_di_664h_ch)
{
    // Initial CPU State
    cpu.set_ax(0x6A3E);
    cpu.set_bx(0x0B7C);
    cpu.set_cx(0xEB24);
    cpu.set_dx(0x57F5);
    cpu.set_cs(0xE5EF);
    cpu.set_ss(0xA343);
    cpu.set_ds(0xE23E);
    cpu.set_es(0x0519);
    cpu.set_sp(0xC8EE);
    cpu.set_bp(0x433C);
    cpu.set_si(0x96DF);
    cpu.set_di(0x1701);
    cpu.set_ip(0xEE21);
    cpu.set_flags(0xF417);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF4D11, 0x36);
    machine.mem_store_byte(0xF4D12, 0x38);
    machine.mem_store_byte(0xF4D13, 0xAB);
    machine.mem_store_byte(0xF4D14, 0x9C);
    machine.mem_store_byte(0xF4D15, 0xF9);
    machine.mem_store_byte(0xA8809, 0x27);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEE26);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF4D11), 0x36);
    EXPECT_EQ(memory.load8(0xF4D12), 0x38);
    EXPECT_EQ(memory.load8(0xF4D13), 0xAB);
    EXPECT_EQ(memory.load8(0xF4D14), 0x9C);
    EXPECT_EQ(memory.load8(0xF4D15), 0xF9);
    EXPECT_EQ(memory.load8(0xA8809), 0x27);
}

TEST_F(MachineTest, cmp_byte_ss_bp_si_1FF1h_46h)
{
    // Initial CPU State
    cpu.set_ax(0xF77B);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x2D9E);
    cpu.set_dx(0xEE4F);
    cpu.set_cs(0xC470);
    cpu.set_ss(0xF300);
    cpu.set_ds(0x60D4);
    cpu.set_es(0x4CA9);
    cpu.set_sp(0x5A60);
    cpu.set_bp(0x8057);
    cpu.set_si(0x0000);
    cpu.set_di(0x55ED);
    cpu.set_ip(0x24EC);
    cpu.set_flags(0xF492);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC6BEC, 0x80);
    machine.mem_store_byte(0xC6BED, 0xBA);
    machine.mem_store_byte(0xC6BEE, 0xF1);
    machine.mem_store_byte(0xC6BEF, 0x1F);
    machine.mem_store_byte(0xC6BF0, 0x46);
    machine.mem_store_byte(0xC6BF1, 0x90);
    machine.mem_store_byte(0xFD048, 0x57);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x24F1);
    EXPECT_EQ(cpu.get_flags(), 0xF406) << show_flags(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC6BEC), 0x80);
    EXPECT_EQ(memory.load8(0xC6BED), 0xBA);
    EXPECT_EQ(memory.load8(0xC6BEE), 0xF1);
    EXPECT_EQ(memory.load8(0xC6BEF), 0x1F);
    EXPECT_EQ(memory.load8(0xC6BF0), 0x46);
    EXPECT_EQ(memory.load8(0xC6BF1), 0x90);
    EXPECT_EQ(memory.load8(0xFD048), 0x57);
}

TEST_F(MachineTest, cmp_byte_ss_bp_si_3Bh)
{
    // Initial CPU State
    cpu.set_ax(0x51D4);
    cpu.set_bx(0x91AB);
    cpu.set_cx(0x8352);
    cpu.set_dx(0x303A);
    cpu.set_cs(0x3C90);
    cpu.set_ss(0x3051);
    cpu.set_ds(0x3234);
    cpu.set_es(0x2097);
    cpu.set_sp(0xB2E3);
    cpu.set_bp(0x325F);
    cpu.set_si(0xEFEA);
    cpu.set_di(0x0000);
    cpu.set_ip(0x916F);
    cpu.set_flags(0xF457);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x45A6F, 0x36);
    machine.mem_store_byte(0x45A70, 0x82);
    machine.mem_store_byte(0x45A71, 0x3A);
    machine.mem_store_byte(0x45A72, 0x3B);
    machine.mem_store_byte(0x45A73, 0x90);
    machine.mem_store_byte(0x32759, 0x8C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9173);
    EXPECT_EQ(cpu.get_flags(), 0xFC02) << show_flags(0xFC02);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x45A6F), 0x36);
    EXPECT_EQ(memory.load8(0x45A70), 0x82);
    EXPECT_EQ(memory.load8(0x45A71), 0x3A);
    EXPECT_EQ(memory.load8(0x45A72), 0x3B);
    EXPECT_EQ(memory.load8(0x45A73), 0x90);
    EXPECT_EQ(memory.load8(0x32759), 0x8C);
}

TEST_F(MachineTest, cmp_ch_byte_cs_bp_79h)
{
    // Initial CPU State
    cpu.set_ax(0x9251);
    cpu.set_bx(0xFCCF);
    cpu.set_cx(0xB670);
    cpu.set_dx(0x8ACB);
    cpu.set_cs(0x331A);
    cpu.set_ss(0x20A5);
    cpu.set_ds(0x97A6);
    cpu.set_es(0x077B);
    cpu.set_sp(0x1FD3);
    cpu.set_bp(0x0000);
    cpu.set_si(0x20D9);
    cpu.set_di(0x2495);
    cpu.set_ip(0x2443);
    cpu.set_flags(0xF043);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x355E3, 0x2E);
    machine.mem_store_byte(0x355E4, 0x3A);
    machine.mem_store_byte(0x355E5, 0x6E);
    machine.mem_store_byte(0x355E6, 0x87);
    machine.mem_store_byte(0x355E7, 0x90);
    machine.mem_store_byte(0x43127, 0x29);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2447);
    EXPECT_EQ(cpu.get_flags(), 0xF096) << show_flags(0xF096);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x355E3), 0x2E);
    EXPECT_EQ(memory.load8(0x355E4), 0x3A);
    EXPECT_EQ(memory.load8(0x355E5), 0x6E);
    EXPECT_EQ(memory.load8(0x355E6), 0x87);
    EXPECT_EQ(memory.load8(0x355E7), 0x90);
    EXPECT_EQ(memory.load8(0x43127), 0x29);
}

TEST_F(MachineTest, cmp_dx_word_ss_bp_di_74EFh)
{
    // Initial CPU State
    cpu.set_ax(0xD709);
    cpu.set_bx(0xE67E);
    cpu.set_cx(0x2876);
    cpu.set_dx(0xBCEF);
    cpu.set_cs(0x4FE1);
    cpu.set_ss(0x2AA4);
    cpu.set_ds(0x94DD);
    cpu.set_es(0x59CD);
    cpu.set_sp(0xFF82);
    cpu.set_bp(0x0000);
    cpu.set_si(0x405D);
    cpu.set_di(0x592C);
    cpu.set_ip(0x65C2);
    cpu.set_flags(0xF013);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x563D2, 0x3B);
    machine.mem_store_byte(0x563D3, 0x93);
    machine.mem_store_byte(0x563D4, 0xEF);
    machine.mem_store_byte(0x563D5, 0x74);
    machine.mem_store_byte(0x563D6, 0x90);
    machine.mem_store_byte(0x563D7, 0x90);
    machine.mem_store_byte(0x3785B, 0x6F);
    machine.mem_store_byte(0x3785C, 0xE7);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x65C6);
    EXPECT_EQ(cpu.get_flags(), 0xF083) << show_flags(0xF083);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x563D2), 0x3B);
    EXPECT_EQ(memory.load8(0x563D3), 0x93);
    EXPECT_EQ(memory.load8(0x563D4), 0xEF);
    EXPECT_EQ(memory.load8(0x563D5), 0x74);
    EXPECT_EQ(memory.load8(0x563D6), 0x90);
    EXPECT_EQ(memory.load8(0x563D7), 0x90);
    EXPECT_EQ(memory.load8(0x3785B), 0x6F);
    EXPECT_EQ(memory.load8(0x3785C), 0xE7);
}

TEST_F(MachineTest, cmp_sp_sp)
{
    // Initial CPU State
    cpu.set_ax(0xE0E2);
    cpu.set_bx(0x47B1);
    cpu.set_cx(0x5992);
    cpu.set_dx(0x8FF2);
    cpu.set_cs(0xE709);
    cpu.set_ss(0x4368);
    cpu.set_ds(0xF43A);
    cpu.set_es(0x6CAF);
    cpu.set_sp(0xB8E7);
    cpu.set_bp(0x9AE9);
    cpu.set_si(0x1438);
    cpu.set_di(0x6445);
    cpu.set_ip(0xE393);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF5423, 0x36);
    machine.mem_store_byte(0xF5424, 0x39);
    machine.mem_store_byte(0xF5425, 0xE4);
    machine.mem_store_byte(0xF5426, 0x90);
    machine.mem_store_byte(0xF5427, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE396);
    EXPECT_EQ(cpu.get_flags(), 0xF446) << show_flags(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF5423), 0x36);
    EXPECT_EQ(memory.load8(0xF5424), 0x39);
    EXPECT_EQ(memory.load8(0xF5425), 0xE4);
    EXPECT_EQ(memory.load8(0xF5426), 0x90);
    EXPECT_EQ(memory.load8(0xF5427), 0x90);
}

TEST_F(MachineTest, cmp_word_ss_BC2h_FFF4h)
{
    // Initial CPU State
    cpu.set_ax(0xC65C);
    cpu.set_bx(0xB985);
    cpu.set_cx(0xACA4);
    cpu.set_dx(0xE372);
    cpu.set_cs(0xD271);
    cpu.set_ss(0x003F);
    cpu.set_ds(0xD5D1);
    cpu.set_es(0x7418);
    cpu.set_sp(0xE927);
    cpu.set_bp(0x4681);
    cpu.set_si(0x3583);
    cpu.set_di(0x0974);
    cpu.set_ip(0x8490);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDABA0, 0x36);
    machine.mem_store_byte(0xDABA1, 0x83);
    machine.mem_store_byte(0xDABA2, 0x3E);
    machine.mem_store_byte(0xDABA3, 0xC2);
    machine.mem_store_byte(0xDABA4, 0x0B);
    machine.mem_store_byte(0xDABA5, 0xF4);
    machine.mem_store_byte(0x00FB2, 0x51);
    machine.mem_store_byte(0x00FB3, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8496);
    EXPECT_EQ(cpu.get_flags(), 0xF013) << show_flags(0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDABA0), 0x36);
    EXPECT_EQ(memory.load8(0xDABA1), 0x83);
    EXPECT_EQ(memory.load8(0xDABA2), 0x3E);
    EXPECT_EQ(memory.load8(0xDABA3), 0xC2);
    EXPECT_EQ(memory.load8(0xDABA4), 0x0B);
    EXPECT_EQ(memory.load8(0xDABA5), 0xF4);
    EXPECT_EQ(memory.load8(0x00FB2), 0x51);
    EXPECT_EQ(memory.load8(0x00FB3), 0x00);
}

TEST_F(MachineTest, cmp_word_ss_bp_4Ch_4050h)
{
    // Initial CPU State
    cpu.set_ax(0x0E1F);
    cpu.set_bx(0xEE2D);
    cpu.set_cx(0xF48E);
    cpu.set_dx(0x3AD8);
    cpu.set_cs(0xE899);
    cpu.set_ss(0x3C95);
    cpu.set_ds(0xDA66);
    cpu.set_es(0xA074);
    cpu.set_sp(0x81CF);
    cpu.set_bp(0x6D06);
    cpu.set_si(0xB1ED);
    cpu.set_di(0xEF46);
    cpu.set_ip(0x5891);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE221, 0x81);
    machine.mem_store_byte(0xEE222, 0x7E);
    machine.mem_store_byte(0xEE223, 0x4C);
    machine.mem_store_byte(0xEE224, 0x50);
    machine.mem_store_byte(0xEE225, 0x40);
    machine.mem_store_byte(0x436A2, 0x10);
    machine.mem_store_byte(0x436A3, 0x48);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5896);
    EXPECT_EQ(cpu.get_flags(), 0xF006) << show_flags(0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE221), 0x81);
    EXPECT_EQ(memory.load8(0xEE222), 0x7E);
    EXPECT_EQ(memory.load8(0xEE223), 0x4C);
    EXPECT_EQ(memory.load8(0xEE224), 0x50);
    EXPECT_EQ(memory.load8(0xEE225), 0x40);
    EXPECT_EQ(memory.load8(0x436A2), 0x10);
    EXPECT_EQ(memory.load8(0x436A3), 0x48);
}

TEST_F(MachineTest, test_al_99h)
{
    // Initial CPU State
    cpu.set_ax(0x10CA);
    cpu.set_bx(0xDF8E);
    cpu.set_cx(0xD4B2);
    cpu.set_dx(0x840D);
    cpu.set_cs(0x49B4);
    cpu.set_ss(0xA822);
    cpu.set_ds(0x70E7);
    cpu.set_es(0xD6C6);
    cpu.set_sp(0x5B3B);
    cpu.set_bp(0x85C8);
    cpu.set_si(0x5581);
    cpu.set_di(0x3052);
    cpu.set_ip(0x5CC5);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4F805, 0xA8);
    machine.mem_store_byte(0x4F806, 0x99);
    machine.mem_store_byte(0x4F807, 0x90);
    machine.mem_store_byte(0x4F808, 0x90);
    machine.mem_store_byte(0x4F809, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5CC7);
    EXPECT_EQ(cpu.get_flags(), 0xF086) << show_flags(0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4F805), 0xA8);
    EXPECT_EQ(memory.load8(0x4F806), 0x99);
    EXPECT_EQ(memory.load8(0x4F807), 0x90);
    EXPECT_EQ(memory.load8(0x4F808), 0x90);
    EXPECT_EQ(memory.load8(0x4F809), 0x90);
}

TEST_F(MachineTest, test_ax_E5F7h)
{
    // Initial CPU State
    cpu.set_ax(0x2817);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xEA94);
    cpu.set_dx(0x0C55);
    cpu.set_cs(0x3EAC);
    cpu.set_ss(0x35D4);
    cpu.set_ds(0xE311);
    cpu.set_es(0x82A8);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xB820);
    cpu.set_si(0x59EC);
    cpu.set_di(0x64AE);
    cpu.set_ip(0xBD21);
    cpu.set_flags(0xF803);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4A7E1, 0xA9);
    machine.mem_store_byte(0x4A7E2, 0xF7);
    machine.mem_store_byte(0x4A7E3, 0xE5);
    machine.mem_store_byte(0x4A7E4, 0x90);
    machine.mem_store_byte(0x4A7E5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBD24);
    EXPECT_EQ(cpu.get_flags(), 0xF006) << show_flags(0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4A7E1), 0xA9);
    EXPECT_EQ(memory.load8(0x4A7E2), 0xF7);
    EXPECT_EQ(memory.load8(0x4A7E3), 0xE5);
    EXPECT_EQ(memory.load8(0x4A7E4), 0x90);
    EXPECT_EQ(memory.load8(0x4A7E5), 0x90);
}

TEST_F(MachineTest, test_byte_ss_bp_di_663Bh_al)
{
    // Initial CPU State
    cpu.set_ax(0x7EC9);
    cpu.set_bx(0x5311);
    cpu.set_cx(0xE544);
    cpu.set_dx(0x1712);
    cpu.set_cs(0x89CC);
    cpu.set_ss(0xF10D);
    cpu.set_ds(0xD8D2);
    cpu.set_es(0x5752);
    cpu.set_sp(0x5CBD);
    cpu.set_bp(0x40A0);
    cpu.set_si(0xE94F);
    cpu.set_di(0x607D);
    cpu.set_ip(0x9D45);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x93A05, 0x36);
    machine.mem_store_byte(0x93A06, 0x84);
    machine.mem_store_byte(0x93A07, 0x83);
    machine.mem_store_byte(0x93A08, 0x3B);
    machine.mem_store_byte(0x93A09, 0x66);
    machine.mem_store_byte(0xF1828, 0xB4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9D4A);
    EXPECT_EQ(cpu.get_flags(), 0xF082) << show_flags(0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x93A05), 0x36);
    EXPECT_EQ(memory.load8(0x93A06), 0x84);
    EXPECT_EQ(memory.load8(0x93A07), 0x83);
    EXPECT_EQ(memory.load8(0x93A08), 0x3B);
    EXPECT_EQ(memory.load8(0x93A09), 0x66);
    EXPECT_EQ(memory.load8(0xF1828), 0xB4);
}

TEST_F(MachineTest, test_byte_ss_bp_di_9h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x10E4);
    cpu.set_cx(0xD780);
    cpu.set_dx(0x2E4E);
    cpu.set_cs(0xC4AD);
    cpu.set_ss(0xAD85);
    cpu.set_ds(0x4757);
    cpu.set_es(0x2763);
    cpu.set_sp(0xDFB9);
    cpu.set_bp(0xC988);
    cpu.set_si(0xBDCA);
    cpu.set_di(0xF74D);
    cpu.set_ip(0xD241);
    cpu.set_flags(0xF416);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD1D11, 0xF6);
    machine.mem_store_byte(0xD1D12, 0x0B);
    machine.mem_store_byte(0xD1D13, 0x09);
    machine.mem_store_byte(0xD1D14, 0x90);
    machine.mem_store_byte(0xD1D15, 0x90);
    machine.mem_store_byte(0xB9925, 0xC9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xD244);
    EXPECT_EQ(cpu.get_flags(), 0xF406) << show_flags(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD1D11), 0xF6);
    EXPECT_EQ(memory.load8(0xD1D12), 0x0B);
    EXPECT_EQ(memory.load8(0xD1D13), 0x09);
    EXPECT_EQ(memory.load8(0xD1D14), 0x90);
    EXPECT_EQ(memory.load8(0xD1D15), 0x90);
    EXPECT_EQ(memory.load8(0xB9925), 0xC9);
}

TEST_F(MachineTest, test_byte_ss_si_3055h_DFh)
{
    // Initial CPU State
    cpu.set_ax(0xEEF4);
    cpu.set_bx(0xEB16);
    cpu.set_cx(0x41FE);
    cpu.set_dx(0xB446);
    cpu.set_cs(0xA9F1);
    cpu.set_ss(0x95E7);
    cpu.set_ds(0xA4FB);
    cpu.set_es(0x9ED1);
    cpu.set_sp(0x038B);
    cpu.set_bp(0x0D00);
    cpu.set_si(0x7E64);
    cpu.set_di(0xF95E);
    cpu.set_ip(0xB21A);
    cpu.set_flags(0xF416);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB512A, 0x36);
    machine.mem_store_byte(0xB512B, 0xF6);
    machine.mem_store_byte(0xB512C, 0x84);
    machine.mem_store_byte(0xB512D, 0x55);
    machine.mem_store_byte(0xB512E, 0x30);
    machine.mem_store_byte(0xB512F, 0xDF);
    machine.mem_store_byte(0xA0D29, 0xDE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB220);
    EXPECT_EQ(cpu.get_flags(), 0xF486) << show_flags(0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB512A), 0x36);
    EXPECT_EQ(memory.load8(0xB512B), 0xF6);
    EXPECT_EQ(memory.load8(0xB512C), 0x84);
    EXPECT_EQ(memory.load8(0xB512D), 0x55);
    EXPECT_EQ(memory.load8(0xB512E), 0x30);
    EXPECT_EQ(memory.load8(0xB512F), 0xDF);
    EXPECT_EQ(memory.load8(0xA0D29), 0xDE);
}

TEST_F(MachineTest, test_word_ds_B835h_bx)
{
    // Initial CPU State
    cpu.set_ax(0xC43F);
    cpu.set_bx(0xC909);
    cpu.set_cx(0xEADA);
    cpu.set_dx(0xF2D5);
    cpu.set_cs(0x6484);
    cpu.set_ss(0xBCDD);
    cpu.set_ds(0x4E5E);
    cpu.set_es(0x0C9B);
    cpu.set_sp(0x54A6);
    cpu.set_bp(0x8112);
    cpu.set_si(0x4F36);
    cpu.set_di(0x196F);
    cpu.set_ip(0xAEA6);
    cpu.set_flags(0xF8C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6F6E6, 0x3E);
    machine.mem_store_byte(0x6F6E7, 0x85);
    machine.mem_store_byte(0x6F6E8, 0x1E);
    machine.mem_store_byte(0x6F6E9, 0x35);
    machine.mem_store_byte(0x6F6EA, 0xB8);
    machine.mem_store_byte(0x6F6EB, 0x90);
    machine.mem_store_byte(0x59E15, 0x25);
    machine.mem_store_byte(0x59E16, 0x4D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAEAB);
    EXPECT_EQ(cpu.get_flags(), 0xF002) << show_flags(0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6F6E6), 0x3E);
    EXPECT_EQ(memory.load8(0x6F6E7), 0x85);
    EXPECT_EQ(memory.load8(0x6F6E8), 0x1E);
    EXPECT_EQ(memory.load8(0x6F6E9), 0x35);
    EXPECT_EQ(memory.load8(0x6F6EA), 0xB8);
    EXPECT_EQ(memory.load8(0x6F6EB), 0x90);
    EXPECT_EQ(memory.load8(0x59E15), 0x25);
    EXPECT_EQ(memory.load8(0x59E16), 0x4D);
}

TEST_F(MachineTest, test_word_ds_bp_67h_91B9h)
{
    // Initial CPU State
    cpu.set_ax(0xD5FD);
    cpu.set_bx(0x5F8F);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x4C6E);
    cpu.set_cs(0x6531);
    cpu.set_ss(0x4C8D);
    cpu.set_ds(0x1E39);
    cpu.set_es(0x2674);
    cpu.set_sp(0x1559);
    cpu.set_bp(0x6C55);
    cpu.set_si(0x39B8);
    cpu.set_di(0xACF2);
    cpu.set_ip(0xC910);
    cpu.set_flags(0xF013);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x71C20, 0x3E);
    machine.mem_store_byte(0x71C21, 0xF7);
    machine.mem_store_byte(0x71C22, 0x46);
    machine.mem_store_byte(0x71C23, 0x99);
    machine.mem_store_byte(0x71C24, 0xB9);
    machine.mem_store_byte(0x71C25, 0x91);
    machine.mem_store_byte(0x24F7E, 0x16);
    machine.mem_store_byte(0x24F7F, 0x0A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC916);
    EXPECT_EQ(cpu.get_flags(), 0xF002) << show_flags(0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x71C20), 0x3E);
    EXPECT_EQ(memory.load8(0x71C21), 0xF7);
    EXPECT_EQ(memory.load8(0x71C22), 0x46);
    EXPECT_EQ(memory.load8(0x71C23), 0x99);
    EXPECT_EQ(memory.load8(0x71C24), 0xB9);
    EXPECT_EQ(memory.load8(0x71C25), 0x91);
    EXPECT_EQ(memory.load8(0x24F7E), 0x16);
    EXPECT_EQ(memory.load8(0x24F7F), 0x0A);
}

TEST_F(MachineTest, test_word_ss_bp_si_DFB1h)
{
    // Initial CPU State
    cpu.set_ax(0xF3A0);
    cpu.set_bx(0xFB0C);
    cpu.set_cx(0xEF7E);
    cpu.set_dx(0x0288);
    cpu.set_cs(0x2398);
    cpu.set_ss(0xD9E0);
    cpu.set_ds(0x2110);
    cpu.set_es(0xA2C9);
    cpu.set_sp(0xEC47);
    cpu.set_bp(0x1647);
    cpu.set_si(0x5304);
    cpu.set_di(0xC3C4);
    cpu.set_ip(0x5797);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x29117, 0xF7);
    machine.mem_store_byte(0x29118, 0x0A);
    machine.mem_store_byte(0x29119, 0xB1);
    machine.mem_store_byte(0x2911A, 0xDF);
    machine.mem_store_byte(0x2911B, 0x90);
    machine.mem_store_byte(0xE074B, 0xA0);
    machine.mem_store_byte(0xE074C, 0x99);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x579B);
    EXPECT_EQ(cpu.get_flags(), 0xF086) << show_flags(0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x29117), 0xF7);
    EXPECT_EQ(memory.load8(0x29118), 0x0A);
    EXPECT_EQ(memory.load8(0x29119), 0xB1);
    EXPECT_EQ(memory.load8(0x2911A), 0xDF);
    EXPECT_EQ(memory.load8(0x2911B), 0x90);
    EXPECT_EQ(memory.load8(0xE074B), 0xA0);
    EXPECT_EQ(memory.load8(0xE074C), 0x99);
}
