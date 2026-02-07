#include "fixture.h"

// Tests: shl, shr, sar, rol, ror, rcl, rcr, setmo, setmoc

TEST_F(MachineTest, rcl_byte_ds_si_33h)
{
    // Initial CPU State
    cpu.set_ax(0x1EE3);
    cpu.set_bx(0x6DDE);
    cpu.set_cx(0x1F06);
    cpu.set_dx(0xB1A9);
    cpu.set_cs(0x7A9E);
    cpu.set_ss(0x974A);
    cpu.set_ds(0x4562);
    cpu.set_es(0x1C76);
    cpu.set_sp(0x2DAC);
    cpu.set_bp(0xCAD5);
    cpu.set_si(0xA640);
    cpu.set_di(0xACBF);
    cpu.set_ip(0x7A6E);
    cpu.set_flags(0xFC56);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8244E, 0xD0);
    machine.mem_store_byte(0x8244F, 0x54);
    machine.mem_store_byte(0x82450, 0x33);
    machine.mem_store_byte(0x82451, 0x90);
    machine.mem_store_byte(0x82452, 0x90);
    machine.mem_store_byte(0x82453, 0x90);
    machine.mem_store_byte(0x4FC93, 0x25);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x7A71);
    EXPECT_EQ(cpu.get_flags(), 0xF456) << show_flags(0xF456);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8244E), 0xD0);
    EXPECT_EQ(memory.load8(0x8244F), 0x54);
    EXPECT_EQ(memory.load8(0x82450), 0x33);
    EXPECT_EQ(memory.load8(0x82451), 0x90);
    EXPECT_EQ(memory.load8(0x82452), 0x90);
    EXPECT_EQ(memory.load8(0x82453), 0x90);
    EXPECT_EQ(memory.load8(0x4FC93), 0x4A);
}

TEST_F(MachineTest, rcl_byte_ss_bp_30h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC90D);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x9110);
    cpu.set_dx(0xCB98);
    cpu.set_cs(0x3A44);
    cpu.set_ss(0x2E62);
    cpu.set_ds(0x679D);
    cpu.set_es(0x307B);
    cpu.set_sp(0x7E0A);
    cpu.set_bp(0x6B29);
    cpu.set_si(0xAD7C);
    cpu.set_di(0xD649);
    cpu.set_ip(0x9F61);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x443A1, 0xD2);
    machine.mem_store_byte(0x443A2, 0x56);
    machine.mem_store_byte(0x443A3, 0x30);
    machine.mem_store_byte(0x443A4, 0x90);
    machine.mem_store_byte(0x443A5, 0x90);
    machine.mem_store_byte(0x35179, 0xFB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9F64);
    EXPECT_EQ(cpu.get_flags(), 0xF0C7) << show_flags(0xF0C7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x443A1), 0xD2);
    EXPECT_EQ(memory.load8(0x443A2), 0x56);
    EXPECT_EQ(memory.load8(0x443A3), 0x30);
    EXPECT_EQ(memory.load8(0x443A4), 0x90);
    EXPECT_EQ(memory.load8(0x443A5), 0x90);
    EXPECT_EQ(memory.load8(0x35179), 0xBE);
}

TEST_F(MachineTest, rcl_word_ds_bx_39CEh)
{
    // Initial CPU State
    cpu.set_ax(0x41A6);
    cpu.set_bx(0x9D92);
    cpu.set_cx(0x471E);
    cpu.set_dx(0xBF08);
    cpu.set_cs(0x63CE);
    cpu.set_ss(0x7755);
    cpu.set_ds(0x0914);
    cpu.set_es(0x9463);
    cpu.set_sp(0xFE69);
    cpu.set_bp(0xEE26);
    cpu.set_si(0x53C3);
    cpu.set_di(0x4003);
    cpu.set_ip(0xCAB2);
    cpu.set_flags(0xFC96);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x70792, 0xD1);
    machine.mem_store_byte(0x70793, 0x97);
    machine.mem_store_byte(0x70794, 0xCE);
    machine.mem_store_byte(0x70795, 0x39);
    machine.mem_store_byte(0x70796, 0x90);
    machine.mem_store_byte(0x70797, 0x90);
    machine.mem_store_byte(0x168A0, 0x67);
    machine.mem_store_byte(0x168A1, 0xCB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCAB6);
    EXPECT_EQ(cpu.get_flags(), 0xF497) << show_flags(0xF497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x70792), 0xD1);
    EXPECT_EQ(memory.load8(0x70793), 0x97);
    EXPECT_EQ(memory.load8(0x70794), 0xCE);
    EXPECT_EQ(memory.load8(0x70795), 0x39);
    EXPECT_EQ(memory.load8(0x70796), 0x90);
    EXPECT_EQ(memory.load8(0x70797), 0x90);
    EXPECT_EQ(memory.load8(0x168A0), 0xCE);
    EXPECT_EQ(memory.load8(0x168A1), 0x96);
}

TEST_F(MachineTest, rcl_word_ds_bx_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0x3157);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x9A24);
    cpu.set_dx(0xE138);
    cpu.set_cs(0x8AFF);
    cpu.set_ss(0x14CD);
    cpu.set_ds(0x25A9);
    cpu.set_es(0xEDDC);
    cpu.set_sp(0x8EAE);
    cpu.set_bp(0x2F4A);
    cpu.set_si(0xD011);
    cpu.set_di(0x255C);
    cpu.set_ip(0x0A17);
    cpu.set_flags(0xF483);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8BA07, 0x3E);
    machine.mem_store_byte(0x8BA08, 0xD3);
    machine.mem_store_byte(0x8BA09, 0x11);
    machine.mem_store_byte(0x8BA0A, 0x90);
    machine.mem_store_byte(0x8BA0B, 0x90);
    machine.mem_store_byte(0x27FEC, 0x29);
    machine.mem_store_byte(0x27FED, 0x16);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0A1A);
    EXPECT_EQ(cpu.get_flags(), 0xF482) << show_flags(0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8BA07), 0x3E);
    EXPECT_EQ(memory.load8(0x8BA08), 0xD3);
    EXPECT_EQ(memory.load8(0x8BA09), 0x11);
    EXPECT_EQ(memory.load8(0x8BA0A), 0x90);
    EXPECT_EQ(memory.load8(0x8BA0B), 0x90);
    EXPECT_EQ(memory.load8(0x27FEC), 0xA6);
    EXPECT_EQ(memory.load8(0x27FED), 0x58);
}

TEST_F(MachineTest, rcr_byte_ds_bx_1405h)
{
    // Initial CPU State
    cpu.set_ax(0x25A7);
    cpu.set_bx(0xEA01);
    cpu.set_cx(0x622C);
    cpu.set_dx(0xA7C1);
    cpu.set_cs(0x7FFB);
    cpu.set_ss(0xB2CA);
    cpu.set_ds(0x3836);
    cpu.set_es(0x6157);
    cpu.set_sp(0x641A);
    cpu.set_bp(0x99D9);
    cpu.set_si(0x6ACE);
    cpu.set_di(0x62B8);
    cpu.set_ip(0x01C6);
    cpu.set_flags(0xF0D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x80176, 0x3E);
    machine.mem_store_byte(0x80177, 0xD0);
    machine.mem_store_byte(0x80178, 0x9F);
    machine.mem_store_byte(0x80179, 0xFB);
    machine.mem_store_byte(0x8017A, 0xEB);
    machine.mem_store_byte(0x8017B, 0x90);
    machine.mem_store_byte(0x4595C, 0xE8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x01CB);
    EXPECT_EQ(cpu.get_flags(), 0xF0D2) << show_flags(0xF0D2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x80176), 0x3E);
    EXPECT_EQ(memory.load8(0x80177), 0xD0);
    EXPECT_EQ(memory.load8(0x80178), 0x9F);
    EXPECT_EQ(memory.load8(0x80179), 0xFB);
    EXPECT_EQ(memory.load8(0x8017A), 0xEB);
    EXPECT_EQ(memory.load8(0x8017B), 0x90);
    EXPECT_EQ(memory.load8(0x4595C), 0xF4);
}

TEST_F(MachineTest, rcr_byte_ds_si_5h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x1954);
    cpu.set_bx(0x8ED1);
    cpu.set_cx(0x4304);
    cpu.set_dx(0x81F2);
    cpu.set_cs(0xC200);
    cpu.set_ss(0x990F);
    cpu.set_ds(0x0CA8);
    cpu.set_es(0xF91B);
    cpu.set_sp(0x93AE);
    cpu.set_bp(0xF14F);
    cpu.set_si(0xFFB9);
    cpu.set_di(0xE374);
    cpu.set_ip(0xFEB9);
    cpu.set_flags(0xF842);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD1EB9, 0xD2);
    machine.mem_store_byte(0xD1EBA, 0x5C);
    machine.mem_store_byte(0xD1EBB, 0xFB);
    machine.mem_store_byte(0xD1EBC, 0x90);
    machine.mem_store_byte(0xD1EBD, 0x90);
    machine.mem_store_byte(0x1CA34, 0x56);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xFEBC);
    EXPECT_EQ(cpu.get_flags(), 0xF042) << show_flags(0xF042);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD1EB9), 0xD2);
    EXPECT_EQ(memory.load8(0xD1EBA), 0x5C);
    EXPECT_EQ(memory.load8(0xD1EBB), 0xFB);
    EXPECT_EQ(memory.load8(0xD1EBC), 0x90);
    EXPECT_EQ(memory.load8(0xD1EBD), 0x90);
    EXPECT_EQ(memory.load8(0x1CA34), 0xC5);
}

TEST_F(MachineTest, rcr_word_ss_bp_5813h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x6F9D);
    cpu.set_bx(0x4863);
    cpu.set_cx(0xF820);
    cpu.set_dx(0x07AB);
    cpu.set_cs(0xE015);
    cpu.set_ss(0x66AB);
    cpu.set_ds(0xEAA6);
    cpu.set_es(0x0753);
    cpu.set_sp(0x90E7);
    cpu.set_bp(0x77DB);
    cpu.set_si(0xF5FB);
    cpu.set_di(0xE9D4);
    cpu.set_ip(0xE5E8);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE738, 0xD3);
    machine.mem_store_byte(0xEE739, 0x9E);
    machine.mem_store_byte(0xEE73A, 0xED);
    machine.mem_store_byte(0xEE73B, 0xA7);
    machine.mem_store_byte(0xEE73C, 0x90);
    machine.mem_store_byte(0xEE73D, 0x90);
    machine.mem_store_byte(0x68A78, 0x2B);
    machine.mem_store_byte(0x68A79, 0x9B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE5EC);
    EXPECT_EQ(cpu.get_flags(), 0xFC56) << show_flags(0xFC56);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE738), 0xD3);
    EXPECT_EQ(memory.load8(0xEE739), 0x9E);
    EXPECT_EQ(memory.load8(0xEE73A), 0xED);
    EXPECT_EQ(memory.load8(0xEE73B), 0xA7);
    EXPECT_EQ(memory.load8(0xEE73C), 0x90);
    EXPECT_EQ(memory.load8(0xEE73D), 0x90);
    EXPECT_EQ(memory.load8(0x68A78), 0xAD);
    EXPECT_EQ(memory.load8(0x68A79), 0x6C);
}

TEST_F(MachineTest, rcr_word_ss_di)
{
    // Initial CPU State
    cpu.set_ax(0x0411);
    cpu.set_bx(0xB682);
    cpu.set_cx(0x3326);
    cpu.set_dx(0xFFA8);
    cpu.set_cs(0xFF60);
    cpu.set_ss(0xEC89);
    cpu.set_ds(0x17D9);
    cpu.set_es(0xB9A8);
    cpu.set_sp(0x457F);
    cpu.set_bp(0x6471);
    cpu.set_si(0x3173);
    cpu.set_di(0x3D2C);
    cpu.set_ip(0x7FC3);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x075C3, 0x36);
    machine.mem_store_byte(0x075C4, 0xD1);
    machine.mem_store_byte(0x075C5, 0x1D);
    machine.mem_store_byte(0x075C6, 0x90);
    machine.mem_store_byte(0x075C7, 0x90);
    machine.mem_store_byte(0xF05BC, 0x4A);
    machine.mem_store_byte(0xF05BD, 0x2F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x7FC6);
    EXPECT_EQ(cpu.get_flags(), 0xF402) << show_flags(0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x075C3), 0x36);
    EXPECT_EQ(memory.load8(0x075C4), 0xD1);
    EXPECT_EQ(memory.load8(0x075C5), 0x1D);
    EXPECT_EQ(memory.load8(0x075C6), 0x90);
    EXPECT_EQ(memory.load8(0x075C7), 0x90);
    EXPECT_EQ(memory.load8(0xF05BC), 0xA5);
    EXPECT_EQ(memory.load8(0xF05BD), 0x17);
}

TEST_F(MachineTest, rol_byte_ds_bp_di_7595h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xEFB2);
    cpu.set_bx(0x821D);
    cpu.set_cx(0x0508);
    cpu.set_dx(0x99C3);
    cpu.set_cs(0x69A3);
    cpu.set_ss(0x3B61);
    cpu.set_ds(0xBEF2);
    cpu.set_es(0xB64D);
    cpu.set_sp(0x2DDD);
    cpu.set_bp(0x3786);
    cpu.set_si(0xFD42);
    cpu.set_di(0x2D70);
    cpu.set_ip(0x142F);
    cpu.set_flags(0xF883);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6AE5F, 0x3E);
    machine.mem_store_byte(0x6AE60, 0xD2);
    machine.mem_store_byte(0x6AE61, 0x83);
    machine.mem_store_byte(0x6AE62, 0x6B);
    machine.mem_store_byte(0x6AE63, 0x8A);
    machine.mem_store_byte(0xCDE81, 0x03);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1434);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6AE5F), 0x3E);
    EXPECT_EQ(memory.load8(0x6AE60), 0xD2);
    EXPECT_EQ(memory.load8(0x6AE61), 0x83);
    EXPECT_EQ(memory.load8(0x6AE62), 0x6B);
    EXPECT_EQ(memory.load8(0x6AE63), 0x8A);
    EXPECT_EQ(memory.load8(0xCDE81), 0x03);
}

TEST_F(MachineTest, rol_byte_ss_bp_si)
{
    // Initial CPU State
    cpu.set_ax(0xC203);
    cpu.set_bx(0x3808);
    cpu.set_cx(0xC812);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x693C);
    cpu.set_ss(0x1450);
    cpu.set_ds(0x23E9);
    cpu.set_es(0xA000);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x799B);
    cpu.set_si(0x1EE9);
    cpu.set_di(0xB57F);
    cpu.set_ip(0xA6C1);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x73A81, 0xD0);
    machine.mem_store_byte(0x73A82, 0x02);
    machine.mem_store_byte(0x73A83, 0x90);
    machine.mem_store_byte(0x73A84, 0x90);
    machine.mem_store_byte(0x73A85, 0x90);
    machine.mem_store_byte(0x1DD84, 0x21);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA6C3);
    EXPECT_EQ(cpu.get_flags(), 0xF046) << show_flags(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x73A81), 0xD0);
    EXPECT_EQ(memory.load8(0x73A82), 0x02);
    EXPECT_EQ(memory.load8(0x73A83), 0x90);
    EXPECT_EQ(memory.load8(0x73A84), 0x90);
    EXPECT_EQ(memory.load8(0x73A85), 0x90);
    EXPECT_EQ(memory.load8(0x1DD84), 0x42);
}

TEST_F(MachineTest, rol_si_cl)
{
    // Initial CPU State
    cpu.set_ax(0x9EFB);
    cpu.set_bx(0x2A3B);
    cpu.set_cx(0xF030);
    cpu.set_dx(0x7A5C);
    cpu.set_cs(0xEC37);
    cpu.set_ss(0x28FB);
    cpu.set_ds(0x0680);
    cpu.set_es(0xAA9C);
    cpu.set_sp(0x677E);
    cpu.set_bp(0x487E);
    cpu.set_si(0x9C56);
    cpu.set_di(0x1789);
    cpu.set_ip(0x63D9);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF2749, 0x36);
    machine.mem_store_byte(0xF274A, 0xD3);
    machine.mem_store_byte(0xF274B, 0xC6);
    machine.mem_store_byte(0xF274C, 0x90);
    machine.mem_store_byte(0xF274D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x63DC);
    EXPECT_EQ(cpu.get_flags(), 0xFC56) << show_flags(0xFC56);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF2749), 0x36);
    EXPECT_EQ(memory.load8(0xF274A), 0xD3);
    EXPECT_EQ(memory.load8(0xF274B), 0xC6);
    EXPECT_EQ(memory.load8(0xF274C), 0x90);
    EXPECT_EQ(memory.load8(0xF274D), 0x90);
}

TEST_F(MachineTest, rol_word_ds_bx_si_14h)
{
    // Initial CPU State
    cpu.set_ax(0xFFEB);
    cpu.set_bx(0x46D0);
    cpu.set_cx(0x6F0A);
    cpu.set_dx(0x953A);
    cpu.set_cs(0x9C73);
    cpu.set_ss(0x8FC8);
    cpu.set_ds(0x3F26);
    cpu.set_es(0x3156);
    cpu.set_sp(0xE03C);
    cpu.set_bp(0xEB6A);
    cpu.set_si(0x59EC);
    cpu.set_di(0xF2AF);
    cpu.set_ip(0x33F9);
    cpu.set_flags(0xF003);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9FB29, 0xD1);
    machine.mem_store_byte(0x9FB2A, 0x40);
    machine.mem_store_byte(0x9FB2B, 0x14);
    machine.mem_store_byte(0x9FB2C, 0x90);
    machine.mem_store_byte(0x9FB2D, 0x90);
    machine.mem_store_byte(0x49330, 0x0C);
    machine.mem_store_byte(0x49331, 0x9D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x33FC);
    EXPECT_EQ(cpu.get_flags(), 0xF803) << show_flags(0xF803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9FB29), 0xD1);
    EXPECT_EQ(memory.load8(0x9FB2A), 0x40);
    EXPECT_EQ(memory.load8(0x9FB2B), 0x14);
    EXPECT_EQ(memory.load8(0x9FB2C), 0x90);
    EXPECT_EQ(memory.load8(0x9FB2D), 0x90);
    EXPECT_EQ(memory.load8(0x49330), 0x19);
    EXPECT_EQ(memory.load8(0x49331), 0x3A);
}

TEST_F(MachineTest, ror_byte_cs_si_76h)
{
    // Initial CPU State
    cpu.set_ax(0xFEF0);
    cpu.set_bx(0x377B);
    cpu.set_cx(0x7324);
    cpu.set_dx(0x3C92);
    cpu.set_cs(0xBA79);
    cpu.set_ss(0x8781);
    cpu.set_ds(0x850E);
    cpu.set_es(0x0173);
    cpu.set_sp(0xE922);
    cpu.set_bp(0x6295);
    cpu.set_si(0x8056);
    cpu.set_di(0xA5CE);
    cpu.set_ip(0x7363);
    cpu.set_flags(0xFCC2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC1AF3, 0x2E);
    machine.mem_store_byte(0xC1AF4, 0xD0);
    machine.mem_store_byte(0xC1AF5, 0x4C);
    machine.mem_store_byte(0xC1AF6, 0x76);
    machine.mem_store_byte(0xC1AF7, 0x90);
    machine.mem_store_byte(0xC285C, 0xF6);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x7367);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC1AF3), 0x2E);
    EXPECT_EQ(memory.load8(0xC1AF4), 0xD0);
    EXPECT_EQ(memory.load8(0xC1AF5), 0x4C);
    EXPECT_EQ(memory.load8(0xC1AF6), 0x76);
    EXPECT_EQ(memory.load8(0xC1AF7), 0x90);
    EXPECT_EQ(memory.load8(0xC285C), 0x7B);
}

TEST_F(MachineTest, ror_byte_ds_bx_si_45F3h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x5D07);
    cpu.set_bx(0x1351);
    cpu.set_cx(0x5F30);
    cpu.set_dx(0xFC75);
    cpu.set_cs(0x8A3D);
    cpu.set_ss(0x8C5F);
    cpu.set_ds(0x8C88);
    cpu.set_es(0x49B9);
    cpu.set_sp(0xB9F8);
    cpu.set_bp(0x7769);
    cpu.set_si(0xF6FB);
    cpu.set_di(0xE264);
    cpu.set_ip(0x654B);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9091B, 0xD2);
    machine.mem_store_byte(0x9091C, 0x88);
    machine.mem_store_byte(0x9091D, 0xF3);
    machine.mem_store_byte(0x9091E, 0x45);
    machine.mem_store_byte(0x9091F, 0x90);
    machine.mem_store_byte(0x918BF, 0x57);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x654F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9091B), 0xD2);
    EXPECT_EQ(memory.load8(0x9091C), 0x88);
    EXPECT_EQ(memory.load8(0x9091D), 0xF3);
    EXPECT_EQ(memory.load8(0x9091E), 0x45);
    EXPECT_EQ(memory.load8(0x9091F), 0x90);
    EXPECT_EQ(memory.load8(0x918BF), 0x57);
}

TEST_F(MachineTest, ror_dx)
{
    // Initial CPU State
    cpu.set_ax(0x5A99);
    cpu.set_bx(0x3FE9);
    cpu.set_cx(0xD512);
    cpu.set_dx(0x90A5);
    cpu.set_cs(0x4F8E);
    cpu.set_ss(0xF657);
    cpu.set_ds(0x722F);
    cpu.set_es(0x51C1);
    cpu.set_sp(0x5C2C);
    cpu.set_bp(0x2086);
    cpu.set_si(0x9D8F);
    cpu.set_di(0xB9BD);
    cpu.set_ip(0xBB3C);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5B41C, 0x2E);
    machine.mem_store_byte(0x5B41D, 0xD1);
    machine.mem_store_byte(0x5B41E, 0xCA);
    machine.mem_store_byte(0x5B41F, 0x90);
    machine.mem_store_byte(0x5B420, 0x90);
    machine.mem_store_byte(0x5B421, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xC852);
    EXPECT_EQ(cpu.get_ip(), 0xBB3F);
    EXPECT_EQ(cpu.get_flags(), 0xF4D7) << show_flags(0xF4D7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5B41C), 0x2E);
    EXPECT_EQ(memory.load8(0x5B41D), 0xD1);
    EXPECT_EQ(memory.load8(0x5B41E), 0xCA);
    EXPECT_EQ(memory.load8(0x5B41F), 0x90);
    EXPECT_EQ(memory.load8(0x5B420), 0x90);
    EXPECT_EQ(memory.load8(0x5B421), 0x90);
}

TEST_F(MachineTest, ror_word_es_bp_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC06A);
    cpu.set_bx(0x49CE);
    cpu.set_cx(0xC508);
    cpu.set_dx(0xEF9C);
    cpu.set_cs(0x8D38);
    cpu.set_ss(0xFEDA);
    cpu.set_ds(0x7A67);
    cpu.set_es(0x4925);
    cpu.set_sp(0x5250);
    cpu.set_bp(0xB4B9);
    cpu.set_si(0x0FB9);
    cpu.set_di(0xAB58);
    cpu.set_ip(0x231A);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8F69A, 0x26);
    machine.mem_store_byte(0x8F69B, 0xD3);
    machine.mem_store_byte(0x8F69C, 0x0B);
    machine.mem_store_byte(0x8F69D, 0x90);
    machine.mem_store_byte(0x8F69E, 0x90);
    machine.mem_store_byte(0x8F69F, 0x90);
    machine.mem_store_byte(0x4F261, 0x11);
    machine.mem_store_byte(0x4F262, 0x06);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x231D);
    EXPECT_EQ(cpu.get_flags(), 0xF016) << show_flags(0xF016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8F69A), 0x26);
    EXPECT_EQ(memory.load8(0x8F69B), 0xD3);
    EXPECT_EQ(memory.load8(0x8F69C), 0x0B);
    EXPECT_EQ(memory.load8(0x8F69D), 0x90);
    EXPECT_EQ(memory.load8(0x8F69E), 0x90);
    EXPECT_EQ(memory.load8(0x8F69F), 0x90);
    EXPECT_EQ(memory.load8(0x4F261), 0x06);
    EXPECT_EQ(memory.load8(0x4F262), 0x11);
}

TEST_F(MachineTest, sar_byte_ds_bx_80h)
{
    // Initial CPU State
    cpu.set_ax(0x24FC);
    cpu.set_bx(0x1048);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x5923);
    cpu.set_cs(0x18B0);
    cpu.set_ss(0x9A8D);
    cpu.set_ds(0x6873);
    cpu.set_es(0x7D1A);
    cpu.set_sp(0xE308);
    cpu.set_bp(0xE5EC);
    cpu.set_si(0x1072);
    cpu.set_di(0xBB7E);
    cpu.set_ip(0x68E7);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1F3E7, 0xD0);
    machine.mem_store_byte(0x1F3E8, 0x7F);
    machine.mem_store_byte(0x1F3E9, 0x80);
    machine.mem_store_byte(0x1F3EA, 0x90);
    machine.mem_store_byte(0x1F3EB, 0x90);
    machine.mem_store_byte(0x696F8, 0x6E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x68EA);
    EXPECT_EQ(cpu.get_flags(), 0xF002) << show_flags(0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1F3E7), 0xD0);
    EXPECT_EQ(memory.load8(0x1F3E8), 0x7F);
    EXPECT_EQ(memory.load8(0x1F3E9), 0x80);
    EXPECT_EQ(memory.load8(0x1F3EA), 0x90);
    EXPECT_EQ(memory.load8(0x1F3EB), 0x90);
    EXPECT_EQ(memory.load8(0x696F8), 0x37);
}

TEST_F(MachineTest, sar_byte_ds_si_75h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC540);
    cpu.set_bx(0x1A8E);
    cpu.set_cx(0x5434);
    cpu.set_dx(0x34D1);
    cpu.set_cs(0xDADD);
    cpu.set_ss(0xC2A3);
    cpu.set_ds(0x3F76);
    cpu.set_es(0x81D5);
    cpu.set_sp(0x1FDD);
    cpu.set_bp(0x2910);
    cpu.set_si(0xFA49);
    cpu.set_di(0xF0EA);
    cpu.set_ip(0x611F);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE0EEF, 0xD2);
    machine.mem_store_byte(0xE0EF0, 0x7C);
    machine.mem_store_byte(0xE0EF1, 0x75);
    machine.mem_store_byte(0xE0EF2, 0x90);
    machine.mem_store_byte(0xE0EF3, 0x90);
    machine.mem_store_byte(0x4F21E, 0x83);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6122);
    EXPECT_EQ(cpu.get_flags(), 0xF087) << show_flags(0xF087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE0EEF), 0xD2);
    EXPECT_EQ(memory.load8(0xE0EF0), 0x7C);
    EXPECT_EQ(memory.load8(0xE0EF1), 0x75);
    EXPECT_EQ(memory.load8(0xE0EF2), 0x90);
    EXPECT_EQ(memory.load8(0xE0EF3), 0x90);
    EXPECT_EQ(memory.load8(0x4F21E), 0xFF);
}

TEST_F(MachineTest, sar_di)
{
    // Initial CPU State
    cpu.set_ax(0xFB79);
    cpu.set_bx(0x1BC4);
    cpu.set_cx(0x5824);
    cpu.set_dx(0x9EBB);
    cpu.set_cs(0x1D23);
    cpu.set_ss(0xA5B6);
    cpu.set_ds(0x1A92);
    cpu.set_es(0x10A2);
    cpu.set_sp(0xE994);
    cpu.set_bp(0x3762);
    cpu.set_si(0x0000);
    cpu.set_di(0xE845);
    cpu.set_ip(0xACDC);
    cpu.set_flags(0xF402);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x27F0C, 0xD1);
    machine.mem_store_byte(0x27F0D, 0xFF);
    machine.mem_store_byte(0x27F0E, 0x90);
    machine.mem_store_byte(0x27F0F, 0x90);
    machine.mem_store_byte(0x27F10, 0x90);
    machine.mem_store_byte(0x27F11, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xF422);
    EXPECT_EQ(cpu.get_ip(), 0xACDE);
    EXPECT_EQ(cpu.get_flags(), 0xF487) << show_flags(0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x27F0C), 0xD1);
    EXPECT_EQ(memory.load8(0x27F0D), 0xFF);
    EXPECT_EQ(memory.load8(0x27F0E), 0x90);
    EXPECT_EQ(memory.load8(0x27F0F), 0x90);
    EXPECT_EQ(memory.load8(0x27F10), 0x90);
    EXPECT_EQ(memory.load8(0x27F11), 0x90);
}

TEST_F(MachineTest, sar_word_ds_bx_si_18h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xF3DC);
    cpu.set_bx(0xDAAD);
    cpu.set_cx(0xAA28);
    cpu.set_dx(0x04F5);
    cpu.set_cs(0xCAD4);
    cpu.set_ss(0x4081);
    cpu.set_ds(0x8781);
    cpu.set_es(0x105A);
    cpu.set_sp(0x95A5);
    cpu.set_bp(0x8FF5);
    cpu.set_si(0x9CF8);
    cpu.set_di(0x10EC);
    cpu.set_ip(0x0C7A);
    cpu.set_flags(0xF802);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCB9BA, 0xD3);
    machine.mem_store_byte(0xCB9BB, 0x78);
    machine.mem_store_byte(0xCB9BC, 0xE8);
    machine.mem_store_byte(0xCB9BD, 0x90);
    machine.mem_store_byte(0xCB9BE, 0x90);
    machine.mem_store_byte(0xCB9BF, 0x90);
    machine.mem_store_byte(0x8EF9D, 0x4A);
    machine.mem_store_byte(0x8EF9E, 0x92);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0C7D);
    EXPECT_EQ(cpu.get_flags(), 0xF087) << show_flags(0xF087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCB9BA), 0xD3);
    EXPECT_EQ(memory.load8(0xCB9BB), 0x78);
    EXPECT_EQ(memory.load8(0xCB9BC), 0xE8);
    EXPECT_EQ(memory.load8(0xCB9BD), 0x90);
    EXPECT_EQ(memory.load8(0xCB9BE), 0x90);
    EXPECT_EQ(memory.load8(0xCB9BF), 0x90);
    EXPECT_EQ(memory.load8(0x8EF9D), 0xFF);
    EXPECT_EQ(memory.load8(0x8EF9E), 0xFF);
}

TEST_F(MachineTest, setmo_byte_ds_bx)
{
    // Initial CPU State
    cpu.set_ax(0xCD98);
    cpu.set_bx(0x4714);
    cpu.set_cx(0x0438);
    cpu.set_dx(0x5691);
    cpu.set_cs(0x5176);
    cpu.set_ss(0xD9FC);
    cpu.set_ds(0x574B);
    cpu.set_es(0x415A);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x08A9);
    cpu.set_si(0xFC22);
    cpu.set_di(0x6F11);
    cpu.set_ip(0x07EE);
    cpu.set_flags(0xF402);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x51F4E, 0xD0);
    machine.mem_store_byte(0x51F4F, 0x37);
    machine.mem_store_byte(0x51F50, 0x90);
    machine.mem_store_byte(0x51F51, 0x90);
    machine.mem_store_byte(0x51F52, 0x90);
    machine.mem_store_byte(0x51F53, 0x90);
    machine.mem_store_byte(0x5BBC4, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x07F0);
    EXPECT_EQ(cpu.get_flags(), 0xF486) << show_flags(0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x51F4E), 0xD0);
    EXPECT_EQ(memory.load8(0x51F4F), 0x37);
    EXPECT_EQ(memory.load8(0x51F50), 0x90);
    EXPECT_EQ(memory.load8(0x51F51), 0x90);
    EXPECT_EQ(memory.load8(0x51F52), 0x90);
    EXPECT_EQ(memory.load8(0x51F53), 0x90);
    EXPECT_EQ(memory.load8(0x5BBC4), 0xFF);
}

TEST_F(MachineTest, setmo_di)
{
    // Initial CPU State
    cpu.set_ax(0x8A67);
    cpu.set_bx(0xEF41);
    cpu.set_cx(0xD414);
    cpu.set_dx(0xFD62);
    cpu.set_cs(0xE2DA);
    cpu.set_ss(0x3ACA);
    cpu.set_ds(0x6C32);
    cpu.set_es(0xF8DD);
    cpu.set_sp(0x64DE);
    cpu.set_bp(0x0131);
    cpu.set_si(0x42DE);
    cpu.set_di(0x0B95);
    cpu.set_ip(0x72C6);
    cpu.set_flags(0xF413);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEA066, 0xD1);
    machine.mem_store_byte(0xEA067, 0xF7);
    machine.mem_store_byte(0xEA068, 0x90);
    machine.mem_store_byte(0xEA069, 0x90);
    machine.mem_store_byte(0xEA06A, 0x90);
    machine.mem_store_byte(0xEA06B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0x72C8);
    EXPECT_EQ(cpu.get_flags(), 0xF486) << show_flags(0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEA066), 0xD1);
    EXPECT_EQ(memory.load8(0xEA067), 0xF7);
    EXPECT_EQ(memory.load8(0xEA068), 0x90);
    EXPECT_EQ(memory.load8(0xEA069), 0x90);
    EXPECT_EQ(memory.load8(0xEA06A), 0x90);
    EXPECT_EQ(memory.load8(0xEA06B), 0x90);
}

TEST_F(MachineTest, setmoc_bp_cl)
{
    // Initial CPU State
    cpu.set_ax(0x1586);
    cpu.set_bx(0xCB49);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x7825);
    cpu.set_cs(0x0EC5);
    cpu.set_ss(0xB93A);
    cpu.set_ds(0x22E9);
    cpu.set_es(0xD3E5);
    cpu.set_sp(0x61D8);
    cpu.set_bp(0x1F06);
    cpu.set_si(0x75DF);
    cpu.set_di(0x5B10);
    cpu.set_ip(0x6C36);
    cpu.set_flags(0xF886);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x15886, 0x3E);
    machine.mem_store_byte(0x15887, 0xD3);
    machine.mem_store_byte(0x15888, 0xF5);
    machine.mem_store_byte(0x15889, 0x90);
    machine.mem_store_byte(0x1588A, 0x90);
    machine.mem_store_byte(0x1588B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6C39);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x15886), 0x3E);
    EXPECT_EQ(memory.load8(0x15887), 0xD3);
    EXPECT_EQ(memory.load8(0x15888), 0xF5);
    EXPECT_EQ(memory.load8(0x15889), 0x90);
    EXPECT_EQ(memory.load8(0x1588A), 0x90);
    EXPECT_EQ(memory.load8(0x1588B), 0x90);
}

TEST_F(MachineTest, setmoc_dl_cl)
{
    // Initial CPU State
    cpu.set_ax(0xAE3D);
    cpu.set_bx(0xC65C);
    cpu.set_cx(0xB426);
    cpu.set_dx(0x07EA);
    cpu.set_cs(0x99E2);
    cpu.set_ss(0x7C92);
    cpu.set_ds(0xC147);
    cpu.set_es(0x4FFE);
    cpu.set_sp(0x630A);
    cpu.set_bp(0x9264);
    cpu.set_si(0xD7AF);
    cpu.set_di(0xE113);
    cpu.set_ip(0x3556);
    cpu.set_flags(0xF092);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9D376, 0x36);
    machine.mem_store_byte(0x9D377, 0xD2);
    machine.mem_store_byte(0x9D378, 0xF2);
    machine.mem_store_byte(0x9D379, 0x90);
    machine.mem_store_byte(0x9D37A, 0x90);
    machine.mem_store_byte(0x9D37B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x07FF);
    EXPECT_EQ(cpu.get_ip(), 0x3559);
    EXPECT_EQ(cpu.get_flags(), 0xF086) << show_flags(0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9D376), 0x36);
    EXPECT_EQ(memory.load8(0x9D377), 0xD2);
    EXPECT_EQ(memory.load8(0x9D378), 0xF2);
    EXPECT_EQ(memory.load8(0x9D379), 0x90);
    EXPECT_EQ(memory.load8(0x9D37A), 0x90);
    EXPECT_EQ(memory.load8(0x9D37B), 0x90);
}

TEST_F(MachineTest, shl_byte_ds_bx_3C8Dh_cl)
{
    // Initial CPU State
    cpu.set_ax(0x1832);
    cpu.set_bx(0x79CA);
    cpu.set_cx(0xDD38);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x464D);
    cpu.set_ss(0x9120);
    cpu.set_ds(0x9F3A);
    cpu.set_es(0xA852);
    cpu.set_sp(0xDE7B);
    cpu.set_bp(0x5EDE);
    cpu.set_si(0x4363);
    cpu.set_di(0x324A);
    cpu.set_ip(0x05AE);
    cpu.set_flags(0xFC53);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x46A7E, 0xD2);
    machine.mem_store_byte(0x46A7F, 0xA7);
    machine.mem_store_byte(0x46A80, 0x8D);
    machine.mem_store_byte(0x46A81, 0x3C);
    machine.mem_store_byte(0x46A82, 0x90);
    machine.mem_store_byte(0x46A83, 0x90);
    machine.mem_store_byte(0xAA9F7, 0x72);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x05B2);
    EXPECT_EQ(cpu.get_flags(), 0xF446) << show_flags(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x46A7E), 0xD2);
    EXPECT_EQ(memory.load8(0x46A7F), 0xA7);
    EXPECT_EQ(memory.load8(0x46A80), 0x8D);
    EXPECT_EQ(memory.load8(0x46A81), 0x3C);
    EXPECT_EQ(memory.load8(0x46A82), 0x90);
    EXPECT_EQ(memory.load8(0x46A83), 0x90);
    EXPECT_EQ(memory.load8(0xAA9F7), 0x00);
}

TEST_F(MachineTest, shl_byte_ss_bx_di_39h)
{
    // Initial CPU State
    cpu.set_ax(0x162D);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x8F2A);
    cpu.set_dx(0xB2FA);
    cpu.set_cs(0xB57D);
    cpu.set_ss(0xF922);
    cpu.set_ds(0xF748);
    cpu.set_es(0x75FD);
    cpu.set_sp(0xA361);
    cpu.set_bp(0x5482);
    cpu.set_si(0xF432);
    cpu.set_di(0xA7DF);
    cpu.set_ip(0xBD74);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC1544, 0x36);
    machine.mem_store_byte(0xC1545, 0xD0);
    machine.mem_store_byte(0xC1546, 0x61);
    machine.mem_store_byte(0xC1547, 0x39);
    machine.mem_store_byte(0xC1548, 0x90);
    machine.mem_store_byte(0xC1549, 0x90);
    machine.mem_store_byte(0x03A38, 0x95);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBD78);
    EXPECT_EQ(cpu.get_flags(), 0xFC03) << show_flags(0xFC03);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC1544), 0x36);
    EXPECT_EQ(memory.load8(0xC1545), 0xD0);
    EXPECT_EQ(memory.load8(0xC1546), 0x61);
    EXPECT_EQ(memory.load8(0xC1547), 0x39);
    EXPECT_EQ(memory.load8(0xC1548), 0x90);
    EXPECT_EQ(memory.load8(0xC1549), 0x90);
    EXPECT_EQ(memory.load8(0x03A38), 0x2A);
}

TEST_F(MachineTest, shl_word_ds_bx_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0x6446);
    cpu.set_bx(0xB8DE);
    cpu.set_cx(0x0000);
    cpu.set_dx(0xF745);
    cpu.set_cs(0xD3A3);
    cpu.set_ss(0xCB10);
    cpu.set_ds(0x2B54);
    cpu.set_es(0x2D4B);
    cpu.set_sp(0xB90D);
    cpu.set_bp(0x5CB5);
    cpu.set_si(0x31C9);
    cpu.set_di(0x9BB1);
    cpu.set_ip(0xA66C);
    cpu.set_flags(0xFC12);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDE09C, 0xD3);
    machine.mem_store_byte(0xDE09D, 0x21);
    machine.mem_store_byte(0xDE09E, 0x90);
    machine.mem_store_byte(0xDE09F, 0x90);
    machine.mem_store_byte(0xDE0A0, 0x90);
    machine.mem_store_byte(0xDE0A1, 0x90);
    machine.mem_store_byte(0x309CF, 0xBD);
    machine.mem_store_byte(0x309D0, 0x0E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA66E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDE09C), 0xD3);
    EXPECT_EQ(memory.load8(0xDE09D), 0x21);
    EXPECT_EQ(memory.load8(0xDE09E), 0x90);
    EXPECT_EQ(memory.load8(0xDE09F), 0x90);
    EXPECT_EQ(memory.load8(0xDE0A0), 0x90);
    EXPECT_EQ(memory.load8(0xDE0A1), 0x90);
    EXPECT_EQ(memory.load8(0x309CF), 0xBD);
    EXPECT_EQ(memory.load8(0x309D0), 0x0E);
}

TEST_F(MachineTest, shl_word_ss_bp_3Ch)
{
    // Initial CPU State
    cpu.set_ax(0x7EEA);
    cpu.set_bx(0xCAE6);
    cpu.set_cx(0x5E30);
    cpu.set_dx(0xE340);
    cpu.set_cs(0x9644);
    cpu.set_ss(0xC8BD);
    cpu.set_ds(0x1F0D);
    cpu.set_es(0xA367);
    cpu.set_sp(0x0858);
    cpu.set_bp(0x9DCF);
    cpu.set_si(0x8B91);
    cpu.set_di(0x8EA4);
    cpu.set_ip(0x401C);
    cpu.set_flags(0xF483);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9A45C, 0x36);
    machine.mem_store_byte(0x9A45D, 0xD1);
    machine.mem_store_byte(0x9A45E, 0x66);
    machine.mem_store_byte(0x9A45F, 0x3C);
    machine.mem_store_byte(0x9A460, 0x90);
    machine.mem_store_byte(0x9A461, 0x90);
    machine.mem_store_byte(0xD29DB, 0x12);
    machine.mem_store_byte(0xD29DC, 0xBF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4020);
    EXPECT_EQ(cpu.get_flags(), 0xFC07) << show_flags(0xFC07);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9A45C), 0x36);
    EXPECT_EQ(memory.load8(0x9A45D), 0xD1);
    EXPECT_EQ(memory.load8(0x9A45E), 0x66);
    EXPECT_EQ(memory.load8(0x9A45F), 0x3C);
    EXPECT_EQ(memory.load8(0x9A460), 0x90);
    EXPECT_EQ(memory.load8(0x9A461), 0x90);
    EXPECT_EQ(memory.load8(0xD29DB), 0x24);
    EXPECT_EQ(memory.load8(0xD29DC), 0x7E);
}

TEST_F(MachineTest, shr_byte_ss_4C72h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xF760);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x921C);
    cpu.set_dx(0x6944);
    cpu.set_cs(0x9FA0);
    cpu.set_ss(0x1025);
    cpu.set_ds(0x4FDB);
    cpu.set_es(0x5627);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xD3F6);
    cpu.set_si(0xD831);
    cpu.set_di(0x65E4);
    cpu.set_ip(0x4172);
    cpu.set_flags(0xF082);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA3B72, 0x36);
    machine.mem_store_byte(0xA3B73, 0xD2);
    machine.mem_store_byte(0xA3B74, 0x2E);
    machine.mem_store_byte(0xA3B75, 0x72);
    machine.mem_store_byte(0xA3B76, 0x4C);
    machine.mem_store_byte(0xA3B77, 0x90);
    machine.mem_store_byte(0x14EC2, 0x63);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4177);
    EXPECT_EQ(cpu.get_flags(), 0xF046) << show_flags(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA3B72), 0x36);
    EXPECT_EQ(memory.load8(0xA3B73), 0xD2);
    EXPECT_EQ(memory.load8(0xA3B74), 0x2E);
    EXPECT_EQ(memory.load8(0xA3B75), 0x72);
    EXPECT_EQ(memory.load8(0xA3B76), 0x4C);
    EXPECT_EQ(memory.load8(0xA3B77), 0x90);
    EXPECT_EQ(memory.load8(0x14EC2), 0x00);
}

TEST_F(MachineTest, shr_dh)
{
    // Initial CPU State
    cpu.set_ax(0xCFF7);
    cpu.set_bx(0x6122);
    cpu.set_cx(0x1A2E);
    cpu.set_dx(0x0795);
    cpu.set_cs(0x1244);
    cpu.set_ss(0x5EC9);
    cpu.set_ds(0xE09A);
    cpu.set_es(0x5A88);
    cpu.set_sp(0x01D3);
    cpu.set_bp(0x9972);
    cpu.set_si(0x7421);
    cpu.set_di(0xFF0A);
    cpu.set_ip(0x4ABC);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x16EFC, 0xD0);
    machine.mem_store_byte(0x16EFD, 0xEE);
    machine.mem_store_byte(0x16EFE, 0x90);
    machine.mem_store_byte(0x16EFF, 0x90);
    machine.mem_store_byte(0x16F00, 0x90);
    machine.mem_store_byte(0x16F01, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0395);
    EXPECT_EQ(cpu.get_ip(), 0x4ABE);
    EXPECT_EQ(cpu.get_flags(), 0xF407) << show_flags(0xF407);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x16EFC), 0xD0);
    EXPECT_EQ(memory.load8(0x16EFD), 0xEE);
    EXPECT_EQ(memory.load8(0x16EFE), 0x90);
    EXPECT_EQ(memory.load8(0x16EFF), 0x90);
    EXPECT_EQ(memory.load8(0x16F00), 0x90);
    EXPECT_EQ(memory.load8(0x16F01), 0x90);
}

TEST_F(MachineTest, shr_word_ds_si_cl)
{
    // Initial CPU State
    cpu.set_ax(0x0294);
    cpu.set_bx(0xFA06);
    cpu.set_cx(0x0938);
    cpu.set_dx(0x5E6D);
    cpu.set_cs(0x2BAD);
    cpu.set_ss(0x0CCA);
    cpu.set_ds(0x8CDB);
    cpu.set_es(0x39E1);
    cpu.set_sp(0x203F);
    cpu.set_bp(0x40E0);
    cpu.set_si(0xCD48);
    cpu.set_di(0xD104);
    cpu.set_ip(0x4E35);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x30905, 0xD3);
    machine.mem_store_byte(0x30906, 0x2C);
    machine.mem_store_byte(0x30907, 0x90);
    machine.mem_store_byte(0x30908, 0x90);
    machine.mem_store_byte(0x30909, 0x90);
    machine.mem_store_byte(0x99AF8, 0x3C);
    machine.mem_store_byte(0x99AF9, 0xE9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4E37);
    EXPECT_EQ(cpu.get_flags(), 0xF046) << show_flags(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30905), 0xD3);
    EXPECT_EQ(memory.load8(0x30906), 0x2C);
    EXPECT_EQ(memory.load8(0x30907), 0x90);
    EXPECT_EQ(memory.load8(0x30908), 0x90);
    EXPECT_EQ(memory.load8(0x30909), 0x90);
    EXPECT_EQ(memory.load8(0x99AF8), 0x00);
    EXPECT_EQ(memory.load8(0x99AF9), 0x00);
}

TEST_F(MachineTest, shr_word_ss_bp_si_3D28h)
{
    // Initial CPU State
    cpu.set_ax(0x85F7);
    cpu.set_bx(0x427F);
    cpu.set_cx(0xE32E);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xA976);
    cpu.set_ss(0x27FA);
    cpu.set_ds(0xE190);
    cpu.set_es(0x7331);
    cpu.set_sp(0x7F2E);
    cpu.set_bp(0xCE08);
    cpu.set_si(0xBEA1);
    cpu.set_di(0xC241);
    cpu.set_ip(0xB777);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB4ED7, 0xD1);
    machine.mem_store_byte(0xB4ED8, 0xAA);
    machine.mem_store_byte(0xB4ED9, 0x28);
    machine.mem_store_byte(0xB4EDA, 0x3D);
    machine.mem_store_byte(0xB4EDB, 0x90);
    machine.mem_store_byte(0x34971, 0x23);
    machine.mem_store_byte(0x34972, 0xAC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB77B);
    EXPECT_EQ(cpu.get_flags(), 0xFC07) << show_flags(0xFC07);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB4ED7), 0xD1);
    EXPECT_EQ(memory.load8(0xB4ED8), 0xAA);
    EXPECT_EQ(memory.load8(0xB4ED9), 0x28);
    EXPECT_EQ(memory.load8(0xB4EDA), 0x3D);
    EXPECT_EQ(memory.load8(0xB4EDB), 0x90);
    EXPECT_EQ(memory.load8(0x34971), 0x11);
    EXPECT_EQ(memory.load8(0x34972), 0x56);
}
