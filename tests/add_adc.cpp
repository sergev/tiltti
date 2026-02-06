#include "fixture.h"

// Tests: add, adc

TEST_F(MachineTest, adc_al_45h)
{
    // Initial CPU State
    cpu.set_ax(0xADEE);
    cpu.set_bx(0xFD34);
    cpu.set_cx(0xA1B4);
    cpu.set_dx(0x4038);
    cpu.set_cs(0xD271);
    cpu.set_ss(0xF076);
    cpu.set_ds(0x8702);
    cpu.set_es(0xCE41);
    cpu.set_sp(0x5BDF);
    cpu.set_bp(0xD8D9);
    cpu.set_si(0x0000);
    cpu.set_di(0x2DB1);
    cpu.set_ip(0x8490);
    cpu.set_flags(0xF4C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDABA0, 0x3E);
    machine.mem_store_byte(0xDABA1, 0x14);
    machine.mem_store_byte(0xDABA2, 0x45);
    machine.mem_store_byte(0xDABA3, 0x90);
    machine.mem_store_byte(0xDABA4, 0x90);
    machine.mem_store_byte(0xDABA5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xAD34);
    EXPECT_EQ(cpu.get_ip(), 0x8493);
    EXPECT_EQ(cpu.get_flags(), 0xF413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDABA0), 0x3E);
    EXPECT_EQ(memory.load8(0xDABA1), 0x14);
    EXPECT_EQ(memory.load8(0xDABA2), 0x45);
    EXPECT_EQ(memory.load8(0xDABA3), 0x90);
    EXPECT_EQ(memory.load8(0xDABA4), 0x90);
    EXPECT_EQ(memory.load8(0xDABA5), 0x90);
}

TEST_F(MachineTest, adc_ax_3085h)
{
    // Initial CPU State
    cpu.set_ax(0xED4A);
    cpu.set_bx(0x1B58);
    cpu.set_cx(0x2E6C);
    cpu.set_dx(0x6A11);
    cpu.set_cs(0x89CC);
    cpu.set_ss(0xA8B6);
    cpu.set_ds(0x8FFD);
    cpu.set_es(0xAB02);
    cpu.set_sp(0x96B2);
    cpu.set_bp(0x5292);
    cpu.set_si(0x5574);
    cpu.set_di(0x3F46);
    cpu.set_ip(0x9D45);
    cpu.set_flags(0xF087);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x93A05, 0x26);
    machine.mem_store_byte(0x93A06, 0x15);
    machine.mem_store_byte(0x93A07, 0x85);
    machine.mem_store_byte(0x93A08, 0x30);
    machine.mem_store_byte(0x93A09, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1DD0);
    EXPECT_EQ(cpu.get_ip(), 0x9D49);
    EXPECT_EQ(cpu.get_flags(), 0xF013) << show_flags(0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x93A05), 0x26);
    EXPECT_EQ(memory.load8(0x93A06), 0x15);
    EXPECT_EQ(memory.load8(0x93A07), 0x85);
    EXPECT_EQ(memory.load8(0x93A08), 0x30);
    EXPECT_EQ(memory.load8(0x93A09), 0x90);
}

TEST_F(MachineTest, adc_bh_bl)
{
    // Initial CPU State
    cpu.set_ax(0x5E35);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xC456);
    cpu.set_dx(0x7271);
    cpu.set_cs(0xE373);
    cpu.set_ss(0xA9FC);
    cpu.set_ds(0x5A79);
    cpu.set_es(0x92D5);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x0000);
    cpu.set_si(0x1B42);
    cpu.set_di(0x93F4);
    cpu.set_ip(0x3F1B);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE764B, 0x12);
    machine.mem_store_byte(0xE764C, 0xFB);
    machine.mem_store_byte(0xE764D, 0x90);
    machine.mem_store_byte(0xE764E, 0x90);
    machine.mem_store_byte(0xE764F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x0100);
    EXPECT_EQ(cpu.get_ip(), 0x3F1D);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE764B), 0x12);
    EXPECT_EQ(memory.load8(0xE764C), 0xFB);
    EXPECT_EQ(memory.load8(0xE764D), 0x90);
    EXPECT_EQ(memory.load8(0xE764E), 0x90);
    EXPECT_EQ(memory.load8(0xE764F), 0x90);
}

TEST_F(MachineTest, adc_byte_ds_bp_di_2h_F8h)
{
    // Initial CPU State
    cpu.set_ax(0xAB64);
    cpu.set_bx(0xCCA7);
    cpu.set_cx(0x908A);
    cpu.set_dx(0x4F0D);
    cpu.set_cs(0x56A8);
    cpu.set_ss(0x29AC);
    cpu.set_ds(0x96AE);
    cpu.set_es(0x12C7);
    cpu.set_sp(0x3F37);
    cpu.set_bp(0xC1B0);
    cpu.set_si(0xB34A);
    cpu.set_di(0xB920);
    cpu.set_ip(0x0335);
    cpu.set_flags(0xFC96);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x56DB5, 0x3E);
    machine.mem_store_byte(0x56DB6, 0x80);
    machine.mem_store_byte(0x56DB7, 0x53);
    machine.mem_store_byte(0x56DB8, 0xFE);
    machine.mem_store_byte(0x56DB9, 0xF8);
    machine.mem_store_byte(0x9E5AE, 0xA5);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x033A);
    EXPECT_EQ(cpu.get_flags(), 0xF483);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x56DB5), 0x3E);
    EXPECT_EQ(memory.load8(0x56DB6), 0x80);
    EXPECT_EQ(memory.load8(0x56DB7), 0x53);
    EXPECT_EQ(memory.load8(0x56DB8), 0xFE);
    EXPECT_EQ(memory.load8(0x56DB9), 0xF8);
    EXPECT_EQ(memory.load8(0x9E5AE), 0x9D);
}

TEST_F(MachineTest, adc_byte_ds_bx_di_BEBh_bl)
{
    // Initial CPU State
    cpu.set_ax(0x8849);
    cpu.set_bx(0x67DB);
    cpu.set_cx(0x8E48);
    cpu.set_dx(0x9548);
    cpu.set_cs(0x5944);
    cpu.set_ss(0x2599);
    cpu.set_ds(0xE2A0);
    cpu.set_es(0x5A5C);
    cpu.set_sp(0x2E53);
    cpu.set_bp(0x2160);
    cpu.set_si(0xA43D);
    cpu.set_di(0x043A);
    cpu.set_ip(0x6AED);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5FF2D, 0x10);
    machine.mem_store_byte(0x5FF2E, 0x99);
    machine.mem_store_byte(0x5FF2F, 0xEB);
    machine.mem_store_byte(0x5FF30, 0x0B);
    machine.mem_store_byte(0x5FF31, 0x90);
    machine.mem_store_byte(0xEA200, 0x56);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6AF1);
    EXPECT_EQ(cpu.get_flags(), 0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5FF2D), 0x10);
    EXPECT_EQ(memory.load8(0x5FF2E), 0x99);
    EXPECT_EQ(memory.load8(0x5FF2F), 0xEB);
    EXPECT_EQ(memory.load8(0x5FF30), 0x0B);
    EXPECT_EQ(memory.load8(0x5FF31), 0x90);
    EXPECT_EQ(memory.load8(0xEA200), 0x31);
}

TEST_F(MachineTest, adc_byte_ss_bp_4Ch_50h)
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
    machine.mem_store_byte(0xEE221, 0x82);
    machine.mem_store_byte(0xEE222, 0x56);
    machine.mem_store_byte(0xEE223, 0x4C);
    machine.mem_store_byte(0xEE224, 0x50);
    machine.mem_store_byte(0xEE225, 0x90);
    machine.mem_store_byte(0x436A2, 0x10);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5895);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE221), 0x82);
    EXPECT_EQ(memory.load8(0xEE222), 0x56);
    EXPECT_EQ(memory.load8(0xEE223), 0x4C);
    EXPECT_EQ(memory.load8(0xEE224), 0x50);
    EXPECT_EQ(memory.load8(0xEE225), 0x90);
    EXPECT_EQ(memory.load8(0x436A2), 0x61);
}

TEST_F(MachineTest, adc_di_word_ds_bp_di_7Fh)
{
    // Initial CPU State
    cpu.set_ax(0x077C);
    cpu.set_bx(0x3CA9);
    cpu.set_cx(0x3DCE);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x6EE3);
    cpu.set_ss(0xB6B0);
    cpu.set_ds(0x7662);
    cpu.set_es(0xC45F);
    cpu.set_sp(0x43FB);
    cpu.set_bp(0xD0EE);
    cpu.set_si(0xC6C0);
    cpu.set_di(0x4E24);
    cpu.set_ip(0xEC9A);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7DACA, 0x3E);
    machine.mem_store_byte(0x7DACB, 0x13);
    machine.mem_store_byte(0x7DACC, 0x7B);
    machine.mem_store_byte(0x7DACD, 0x81);
    machine.mem_store_byte(0x7DACE, 0x90);
    machine.mem_store_byte(0x7DACF, 0x90);
    machine.mem_store_byte(0x784B3, 0x4F);
    machine.mem_store_byte(0x784B4, 0x01);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x4F73);
    EXPECT_EQ(cpu.get_ip(), 0xEC9E);
    EXPECT_EQ(cpu.get_flags(), 0xF412);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7DACA), 0x3E);
    EXPECT_EQ(memory.load8(0x7DACB), 0x13);
    EXPECT_EQ(memory.load8(0x7DACC), 0x7B);
    EXPECT_EQ(memory.load8(0x7DACD), 0x81);
    EXPECT_EQ(memory.load8(0x7DACE), 0x90);
    EXPECT_EQ(memory.load8(0x7DACF), 0x90);
    EXPECT_EQ(memory.load8(0x784B3), 0x4F);
    EXPECT_EQ(memory.load8(0x784B4), 0x01);
}

TEST_F(MachineTest, adc_word_cs_bx_si_Ch_134Bh)
{
    // Initial CPU State
    cpu.set_ax(0xFF71);
    cpu.set_bx(0x2BE0);
    cpu.set_cx(0x16CE);
    cpu.set_dx(0xE3AB);
    cpu.set_cs(0x4257);
    cpu.set_ss(0x8039);
    cpu.set_ds(0xA1ED);
    cpu.set_es(0xE23D);
    cpu.set_sp(0xD504);
    cpu.set_bp(0x368E);
    cpu.set_si(0x570D);
    cpu.set_di(0x848B);
    cpu.set_ip(0x103F);
    cpu.set_flags(0xF8D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x435AF, 0x2E);
    machine.mem_store_byte(0x435B0, 0x81);
    machine.mem_store_byte(0x435B1, 0x50);
    machine.mem_store_byte(0x435B2, 0xF4);
    machine.mem_store_byte(0x435B3, 0x4B);
    machine.mem_store_byte(0x435B4, 0x13);
    machine.mem_store_byte(0x4A851, 0xBD);
    machine.mem_store_byte(0x4A852, 0xFF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1045);
    EXPECT_EQ(cpu.get_flags(), 0xF017);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x435AF), 0x2E);
    EXPECT_EQ(memory.load8(0x435B0), 0x81);
    EXPECT_EQ(memory.load8(0x435B1), 0x50);
    EXPECT_EQ(memory.load8(0x435B2), 0xF4);
    EXPECT_EQ(memory.load8(0x435B3), 0x4B);
    EXPECT_EQ(memory.load8(0x435B4), 0x13);
    EXPECT_EQ(memory.load8(0x4A851), 0x09);
    EXPECT_EQ(memory.load8(0x4A852), 0x13);
}

TEST_F(MachineTest, adc_word_ss_bp_si_17h)
{
    // Initial CPU State
    cpu.set_ax(0xD05A);
    cpu.set_bx(0xE44F);
    cpu.set_cx(0x3798);
    cpu.set_dx(0x2C7D);
    cpu.set_cs(0x299C);
    cpu.set_ss(0x241F);
    cpu.set_ds(0xB2BD);
    cpu.set_es(0x4F39);
    cpu.set_sp(0xE4DF);
    cpu.set_bp(0xED65);
    cpu.set_si(0x0174);
    cpu.set_di(0x8988);
    cpu.set_ip(0x74A4);
    cpu.set_flags(0xF4C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x30E64, 0x83);
    machine.mem_store_byte(0x30E65, 0x12);
    machine.mem_store_byte(0x30E66, 0x17);
    machine.mem_store_byte(0x30E67, 0x90);
    machine.mem_store_byte(0x30E68, 0x90);
    machine.mem_store_byte(0x30E69, 0x90);
    machine.mem_store_byte(0x330C9, 0xCF);
    machine.mem_store_byte(0x330CA, 0xC3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x74A7);
    EXPECT_EQ(cpu.get_flags(), 0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30E64), 0x83);
    EXPECT_EQ(memory.load8(0x30E65), 0x12);
    EXPECT_EQ(memory.load8(0x30E66), 0x17);
    EXPECT_EQ(memory.load8(0x30E67), 0x90);
    EXPECT_EQ(memory.load8(0x30E68), 0x90);
    EXPECT_EQ(memory.load8(0x30E69), 0x90);
    EXPECT_EQ(memory.load8(0x330C9), 0xE7);
    EXPECT_EQ(memory.load8(0x330CA), 0xC3);
}

TEST_F(MachineTest, adc_word_ss_si_5119h_cx)
{
    // Initial CPU State
    cpu.set_ax(0x2C79);
    cpu.set_bx(0x2D77);
    cpu.set_cx(0xC1B8);
    cpu.set_dx(0x2DDB);
    cpu.set_cs(0xA256);
    cpu.set_ss(0x5239);
    cpu.set_ds(0x8B49);
    cpu.set_es(0x42E6);
    cpu.set_sp(0x8756);
    cpu.set_bp(0xB3B8);
    cpu.set_si(0x3DDF);
    cpu.set_di(0x57DD);
    cpu.set_ip(0x08FC);
    cpu.set_flags(0xF483);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA2E5C, 0x36);
    machine.mem_store_byte(0xA2E5D, 0x11);
    machine.mem_store_byte(0xA2E5E, 0x8C);
    machine.mem_store_byte(0xA2E5F, 0x19);
    machine.mem_store_byte(0xA2E60, 0x51);
    machine.mem_store_byte(0xA2E61, 0x90);
    machine.mem_store_byte(0x5B288, 0x72);
    machine.mem_store_byte(0x5B289, 0x25);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0901);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA2E5C), 0x36);
    EXPECT_EQ(memory.load8(0xA2E5D), 0x11);
    EXPECT_EQ(memory.load8(0xA2E5E), 0x8C);
    EXPECT_EQ(memory.load8(0xA2E5F), 0x19);
    EXPECT_EQ(memory.load8(0xA2E60), 0x51);
    EXPECT_EQ(memory.load8(0xA2E61), 0x90);
    EXPECT_EQ(memory.load8(0x5B288), 0x2B);
    EXPECT_EQ(memory.load8(0x5B289), 0xE7);
}

TEST_F(MachineTest, add_ah_cl)
{
    // Initial CPU State
    cpu.set_ax(0xABC4);
    cpu.set_bx(0xED8A);
    cpu.set_cx(0xA80E);
    cpu.set_dx(0x864F);
    cpu.set_cs(0xA272);
    cpu.set_ss(0xC6CC);
    cpu.set_ds(0x5AB4);
    cpu.set_es(0x76DF);
    cpu.set_sp(0x7CA4);
    cpu.set_bp(0xCA43);
    cpu.set_si(0xF8D3);
    cpu.set_di(0xD6EC);
    cpu.set_ip(0x8812);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAAF32, 0x02);
    machine.mem_store_byte(0xAAF33, 0xE1);
    machine.mem_store_byte(0xAAF34, 0x90);
    machine.mem_store_byte(0xAAF35, 0x90);
    machine.mem_store_byte(0xAAF36, 0x90);
    machine.mem_store_byte(0xAAF37, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xB9C4);
    EXPECT_EQ(cpu.get_ip(), 0x8814);
    EXPECT_EQ(cpu.get_flags(), 0xF492);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAAF32), 0x02);
    EXPECT_EQ(memory.load8(0xAAF33), 0xE1);
    EXPECT_EQ(memory.load8(0xAAF34), 0x90);
    EXPECT_EQ(memory.load8(0xAAF35), 0x90);
    EXPECT_EQ(memory.load8(0xAAF36), 0x90);
    EXPECT_EQ(memory.load8(0xAAF37), 0x90);
}

TEST_F(MachineTest, add_al_7Eh)
{
    // Initial CPU State
    cpu.set_ax(0x3C00);
    cpu.set_bx(0xF821);
    cpu.set_cx(0xEB98);
    cpu.set_dx(0x3BAF);
    cpu.set_cs(0x296C);
    cpu.set_ss(0xFFB5);
    cpu.set_ds(0x5B52);
    cpu.set_es(0x82C6);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xD37F);
    cpu.set_si(0x96F9);
    cpu.set_di(0x2CDE);
    cpu.set_ip(0xF8A3);
    cpu.set_flags(0xF8C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x38F63, 0x2E);
    machine.mem_store_byte(0x38F64, 0x04);
    machine.mem_store_byte(0x38F65, 0x7E);
    machine.mem_store_byte(0x38F66, 0x90);
    machine.mem_store_byte(0x38F67, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x3C7E);
    EXPECT_EQ(cpu.get_ip(), 0xF8A6);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x38F63), 0x2E);
    EXPECT_EQ(memory.load8(0x38F64), 0x04);
    EXPECT_EQ(memory.load8(0x38F65), 0x7E);
    EXPECT_EQ(memory.load8(0x38F66), 0x90);
    EXPECT_EQ(memory.load8(0x38F67), 0x90);
}

TEST_F(MachineTest, add_ax_E83Ch)
{
    // Initial CPU State
    cpu.set_ax(0xFA8D);
    cpu.set_bx(0xDE12);
    cpu.set_cx(0xCBBC);
    cpu.set_dx(0x89BB);
    cpu.set_cs(0x3C90);
    cpu.set_ss(0xCA15);
    cpu.set_ds(0x5194);
    cpu.set_es(0x91C1);
    cpu.set_sp(0xB37A);
    cpu.set_bp(0x82D8);
    cpu.set_si(0x10AB);
    cpu.set_di(0xEA36);
    cpu.set_ip(0x916F);
    cpu.set_flags(0xFC46);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x45A6F, 0x3E);
    machine.mem_store_byte(0x45A70, 0x05);
    machine.mem_store_byte(0x45A71, 0x3C);
    machine.mem_store_byte(0x45A72, 0xE8);
    machine.mem_store_byte(0x45A73, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xE2C9);
    EXPECT_EQ(cpu.get_ip(), 0x9173);
    EXPECT_EQ(cpu.get_flags(), 0xF497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x45A6F), 0x3E);
    EXPECT_EQ(memory.load8(0x45A70), 0x05);
    EXPECT_EQ(memory.load8(0x45A71), 0x3C);
    EXPECT_EQ(memory.load8(0x45A72), 0xE8);
    EXPECT_EQ(memory.load8(0x45A73), 0x90);
}

TEST_F(MachineTest, add_bp_di)
{
    // Initial CPU State
    cpu.set_ax(0x18EA);
    cpu.set_bx(0x854A);
    cpu.set_cx(0x8F8E);
    cpu.set_dx(0x31E1);
    cpu.set_cs(0x00FE);
    cpu.set_ss(0x0E56);
    cpu.set_ds(0xFBDD);
    cpu.set_es(0xDA05);
    cpu.set_sp(0x77BE);
    cpu.set_bp(0xD3A2);
    cpu.set_si(0x237E);
    cpu.set_di(0x0000);
    cpu.set_ip(0x1174);
    cpu.set_flags(0xFC17);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02154, 0x26);
    machine.mem_store_byte(0x02155, 0x03);
    machine.mem_store_byte(0x02156, 0xEF);
    machine.mem_store_byte(0x02157, 0x90);
    machine.mem_store_byte(0x02158, 0x90);
    machine.mem_store_byte(0x02159, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1177);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02154), 0x26);
    EXPECT_EQ(memory.load8(0x02155), 0x03);
    EXPECT_EQ(memory.load8(0x02156), 0xEF);
    EXPECT_EQ(memory.load8(0x02157), 0x90);
    EXPECT_EQ(memory.load8(0x02158), 0x90);
    EXPECT_EQ(memory.load8(0x02159), 0x90);
}

TEST_F(MachineTest, add_byte_es_bp_di_1F2Ch_70h)
{
    // Initial CPU State
    cpu.set_ax(0xBC52);
    cpu.set_bx(0x0573);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x1EF3);
    cpu.set_cs(0x0D02);
    cpu.set_ss(0xB630);
    cpu.set_ds(0x4CF5);
    cpu.set_es(0x8FE3);
    cpu.set_sp(0x3CA5);
    cpu.set_bp(0x9EAE);
    cpu.set_si(0x19C9);
    cpu.set_di(0xDFE8);
    cpu.set_ip(0xF959);
    cpu.set_flags(0xF443);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1C979, 0x26);
    machine.mem_store_byte(0x1C97A, 0x80);
    machine.mem_store_byte(0x1C97B, 0x83);
    machine.mem_store_byte(0x1C97C, 0xD4);
    machine.mem_store_byte(0x1C97D, 0xE0);
    machine.mem_store_byte(0x1C97E, 0x70);
    machine.mem_store_byte(0x95D9A, 0x59);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF95F);
    EXPECT_EQ(cpu.get_flags(), 0xFC86);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1C979), 0x26);
    EXPECT_EQ(memory.load8(0x1C97A), 0x80);
    EXPECT_EQ(memory.load8(0x1C97B), 0x83);
    EXPECT_EQ(memory.load8(0x1C97C), 0xD4);
    EXPECT_EQ(memory.load8(0x1C97D), 0xE0);
    EXPECT_EQ(memory.load8(0x1C97E), 0x70);
    EXPECT_EQ(memory.load8(0x95D9A), 0xC9);
}

TEST_F(MachineTest, add_byte_es_si_3AE9h_9Ch)
{
    // Initial CPU State
    cpu.set_ax(0x6AF1);
    cpu.set_bx(0x8A14);
    cpu.set_cx(0xF8D6);
    cpu.set_dx(0x0BCC);
    cpu.set_cs(0xC1AE);
    cpu.set_ss(0x3FA2);
    cpu.set_ds(0x4DDB);
    cpu.set_es(0xB82D);
    cpu.set_sp(0x1626);
    cpu.set_bp(0x0000);
    cpu.set_si(0x0000);
    cpu.set_di(0xCCC2);
    cpu.set_ip(0x2FF2);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC4AD2, 0x26);
    machine.mem_store_byte(0xC4AD3, 0x82);
    machine.mem_store_byte(0xC4AD4, 0x84);
    machine.mem_store_byte(0xC4AD5, 0x17);
    machine.mem_store_byte(0xC4AD6, 0xC5);
    machine.mem_store_byte(0xC4AD7, 0x9C);
    machine.mem_store_byte(0xC47E7, 0x5C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2FF8);
    EXPECT_EQ(cpu.get_flags(), 0xF092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC4AD2), 0x26);
    EXPECT_EQ(memory.load8(0xC4AD3), 0x82);
    EXPECT_EQ(memory.load8(0xC4AD4), 0x84);
    EXPECT_EQ(memory.load8(0xC4AD5), 0x17);
    EXPECT_EQ(memory.load8(0xC4AD6), 0xC5);
    EXPECT_EQ(memory.load8(0xC4AD7), 0x9C);
    EXPECT_EQ(memory.load8(0xC47E7), 0xF8);
}

TEST_F(MachineTest, add_cl_ah)
{
    // Initial CPU State
    cpu.set_ax(0x339C);
    cpu.set_bx(0xB0E4);
    cpu.set_cx(0xBAA8);
    cpu.set_dx(0xAA04);
    cpu.set_cs(0xE899);
    cpu.set_ss(0xEF46);
    cpu.set_ds(0x0C72);
    cpu.set_es(0xDA66);
    cpu.set_sp(0xF9A1);
    cpu.set_bp(0x39A1);
    cpu.set_si(0xA73E);
    cpu.set_di(0x0000);
    cpu.set_ip(0x5891);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE221, 0x00);
    machine.mem_store_byte(0xEE222, 0xE1);
    machine.mem_store_byte(0xEE223, 0x90);
    machine.mem_store_byte(0xEE224, 0x90);
    machine.mem_store_byte(0xEE225, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xBADB);
    EXPECT_EQ(cpu.get_ip(), 0x5893);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE221), 0x00);
    EXPECT_EQ(memory.load8(0xEE222), 0xE1);
    EXPECT_EQ(memory.load8(0xEE223), 0x90);
    EXPECT_EQ(memory.load8(0xEE224), 0x90);
    EXPECT_EQ(memory.load8(0xEE225), 0x90);
}

TEST_F(MachineTest, add_word_ds_bx_si_DE2h_92E7h)
{
    // Initial CPU State
    cpu.set_ax(0xE997);
    cpu.set_bx(0x2292);
    cpu.set_cx(0x5EB0);
    cpu.set_dx(0xF161);
    cpu.set_cs(0x94C7);
    cpu.set_ss(0xF2CF);
    cpu.set_ds(0x07AD);
    cpu.set_es(0x07F9);
    cpu.set_sp(0x34B3);
    cpu.set_bp(0x0F98);
    cpu.set_si(0x348E);
    cpu.set_di(0x7C8B);
    cpu.set_ip(0x2442);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x970B2, 0x81);
    machine.mem_store_byte(0x970B3, 0x80);
    machine.mem_store_byte(0x970B4, 0xE2);
    machine.mem_store_byte(0x970B5, 0x0D);
    machine.mem_store_byte(0x970B6, 0xE7);
    machine.mem_store_byte(0x970B7, 0x92);
    machine.mem_store_byte(0x0DFD2, 0xB9);
    machine.mem_store_byte(0x0DFD3, 0x9F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2448);
    EXPECT_EQ(cpu.get_flags(), 0xFC17);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x970B2), 0x81);
    EXPECT_EQ(memory.load8(0x970B3), 0x80);
    EXPECT_EQ(memory.load8(0x970B4), 0xE2);
    EXPECT_EQ(memory.load8(0x970B5), 0x0D);
    EXPECT_EQ(memory.load8(0x970B6), 0xE7);
    EXPECT_EQ(memory.load8(0x970B7), 0x92);
    EXPECT_EQ(memory.load8(0x0DFD2), 0xA0);
    EXPECT_EQ(memory.load8(0x0DFD3), 0x32);
}

TEST_F(MachineTest, add_word_ds_si_25h_dx)
{
    // Initial CPU State
    cpu.set_ax(0xF65A);
    cpu.set_bx(0xC4E2);
    cpu.set_cx(0x5364);
    cpu.set_dx(0xD2BD);
    cpu.set_cs(0xC1AE);
    cpu.set_ss(0x4DB1);
    cpu.set_ds(0xD966);
    cpu.set_es(0xD574);
    cpu.set_sp(0x7CF8);
    cpu.set_bp(0xCDDC);
    cpu.set_si(0xB324);
    cpu.set_di(0x05C1);
    cpu.set_ip(0x2FF2);
    cpu.set_flags(0xF0D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC4AD2, 0x01);
    machine.mem_store_byte(0xC4AD3, 0x54);
    machine.mem_store_byte(0xC4AD4, 0xDB);
    machine.mem_store_byte(0xC4AD5, 0x90);
    machine.mem_store_byte(0xC4AD6, 0x90);
    machine.mem_store_byte(0xC4AD7, 0x90);
    machine.mem_store_byte(0xE495F, 0xB7);
    machine.mem_store_byte(0xE4960, 0xF6);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2FF5);
    EXPECT_EQ(cpu.get_flags(), 0xF097);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC4AD2), 0x01);
    EXPECT_EQ(memory.load8(0xC4AD3), 0x54);
    EXPECT_EQ(memory.load8(0xC4AD4), 0xDB);
    EXPECT_EQ(memory.load8(0xC4AD5), 0x90);
    EXPECT_EQ(memory.load8(0xC4AD6), 0x90);
    EXPECT_EQ(memory.load8(0xC4AD7), 0x90);
    EXPECT_EQ(memory.load8(0xE495F), 0x74);
    EXPECT_EQ(memory.load8(0xE4960), 0xC9);
}

TEST_F(MachineTest, add_word_ss_bx_di_1Eh_FFEDh)
{
    // Initial CPU State
    cpu.set_ax(0x6C31);
    cpu.set_bx(0x47D7);
    cpu.set_cx(0x1418);
    cpu.set_dx(0x65B0);
    cpu.set_cs(0xFB20);
    cpu.set_ss(0x1352);
    cpu.set_ds(0x8390);
    cpu.set_es(0xCD70);
    cpu.set_sp(0x9316);
    cpu.set_bp(0xA611);
    cpu.set_si(0xA1E0);
    cpu.set_di(0x3FA8);
    cpu.set_ip(0x3D06);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFEF06, 0x36);
    machine.mem_store_byte(0xFEF07, 0x83);
    machine.mem_store_byte(0xFEF08, 0x41);
    machine.mem_store_byte(0xFEF09, 0x1E);
    machine.mem_store_byte(0xFEF0A, 0xED);
    machine.mem_store_byte(0xFEF0B, 0x90);
    machine.mem_store_byte(0x1BCBD, 0x2D);
    machine.mem_store_byte(0x1BCBE, 0x51);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3D0B);
    EXPECT_EQ(cpu.get_flags(), 0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFEF06), 0x36);
    EXPECT_EQ(memory.load8(0xFEF07), 0x83);
    EXPECT_EQ(memory.load8(0xFEF08), 0x41);
    EXPECT_EQ(memory.load8(0xFEF09), 0x1E);
    EXPECT_EQ(memory.load8(0xFEF0A), 0xED);
    EXPECT_EQ(memory.load8(0xFEF0B), 0x90);
    EXPECT_EQ(memory.load8(0x1BCBD), 0x1A);
    EXPECT_EQ(memory.load8(0x1BCBE), 0x51);
}
