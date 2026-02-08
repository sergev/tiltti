#include "fixture.h"

// Tests: sub, sbb

TEST_F(MachineTest, sbb_al_DAh)
{
    // Initial CPU State
    cpu.set_ax(0x9346);
    cpu.set_bx(0xA89F);
    cpu.set_cx(0x2216);
    cpu.set_dx(0xC3FF);
    cpu.set_cs(0xCE53);
    cpu.set_ss(0xE194);
    cpu.set_ds(0x9B66);
    cpu.set_es(0xF92E);
    cpu.set_sp(0xADDD);
    cpu.set_bp(0x6585);
    cpu.set_si(0xB121);
    cpu.set_di(0x2542);
    cpu.set_ip(0xC875);
    cpu.set_flags(0xF402);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDADA5, 0x36);
    machine.mem_store_byte(0xDADA6, 0x1C);
    machine.mem_store_byte(0xDADA7, 0xDA);
    machine.mem_store_byte(0xDADA8, 0x90);
    machine.mem_store_byte(0xDADA9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x936C);
    EXPECT_EQ(cpu.get_ip(), 0xC878);
    EXPECT_FLAGS(0xF417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDADA5), 0x36);
    EXPECT_EQ(memory.load8(0xDADA6), 0x1C);
    EXPECT_EQ(memory.load8(0xDADA7), 0xDA);
    EXPECT_EQ(memory.load8(0xDADA8), 0x90);
    EXPECT_EQ(memory.load8(0xDADA9), 0x90);
}

TEST_F(MachineTest, sbb_ax_78C6h)
{
    // Initial CPU State
    cpu.set_ax(0xC0A2);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x0C90);
    cpu.set_dx(0xF6F1);
    cpu.set_cs(0x0FBD);
    cpu.set_ss(0x38B9);
    cpu.set_ds(0xA06B);
    cpu.set_es(0xB23B);
    cpu.set_sp(0xCB3E);
    cpu.set_bp(0x6C82);
    cpu.set_si(0xB36C);
    cpu.set_di(0x37AE);
    cpu.set_ip(0x0B7F);
    cpu.set_flags(0xFC86);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1074F, 0x1D);
    machine.mem_store_byte(0x10750, 0xC6);
    machine.mem_store_byte(0x10751, 0x78);
    machine.mem_store_byte(0x10752, 0x90);
    machine.mem_store_byte(0x10753, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x47DC);
    EXPECT_EQ(cpu.get_ip(), 0x0B82);
    EXPECT_FLAGS(0xFC12);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1074F), 0x1D);
    EXPECT_EQ(memory.load8(0x10750), 0xC6);
    EXPECT_EQ(memory.load8(0x10751), 0x78);
    EXPECT_EQ(memory.load8(0x10752), 0x90);
    EXPECT_EQ(memory.load8(0x10753), 0x90);
}

TEST_F(MachineTest, sbb_bl_byte_ds_bx_si_63h)
{
    // Initial CPU State
    cpu.set_ax(0x5581);
    cpu.set_bx(0x69C1);
    cpu.set_cx(0x4010);
    cpu.set_dx(0x09F5);
    cpu.set_cs(0x871E);
    cpu.set_ss(0x928A);
    cpu.set_ds(0xD480);
    cpu.set_es(0xEA0A);
    cpu.set_sp(0x81ED);
    cpu.set_bp(0xD923);
    cpu.set_si(0x3F06);
    cpu.set_di(0x8E8B);
    cpu.set_ip(0x155D);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8873D, 0x1A);
    machine.mem_store_byte(0x8873E, 0x58);
    machine.mem_store_byte(0x8873F, 0x9D);
    machine.mem_store_byte(0x88740, 0x90);
    machine.mem_store_byte(0x88741, 0x90);
    machine.mem_store_byte(0xDF064, 0xB7);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x6909);
    EXPECT_EQ(cpu.get_ip(), 0x1560);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8873D), 0x1A);
    EXPECT_EQ(memory.load8(0x8873E), 0x58);
    EXPECT_EQ(memory.load8(0x8873F), 0x9D);
    EXPECT_EQ(memory.load8(0x88740), 0x90);
    EXPECT_EQ(memory.load8(0x88741), 0x90);
    EXPECT_EQ(memory.load8(0xDF064), 0xB7);
}

TEST_F(MachineTest, sbb_byte_ds_bp_di_5123h_dh)
{
    // Initial CPU State
    cpu.set_ax(0x61FF);
    cpu.set_bx(0x0B5C);
    cpu.set_cx(0xFC8E);
    cpu.set_dx(0x06A4);
    cpu.set_cs(0x93AB);
    cpu.set_ss(0xBA9D);
    cpu.set_ds(0xAA60);
    cpu.set_es(0xF95C);
    cpu.set_sp(0x6CE7);
    cpu.set_bp(0x90FE);
    cpu.set_si(0x1A51);
    cpu.set_di(0xA881);
    cpu.set_ip(0x9C4E);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9D6FE, 0x3E);
    machine.mem_store_byte(0x9D6FF, 0x18);
    machine.mem_store_byte(0x9D700, 0xB3);
    machine.mem_store_byte(0x9D701, 0x23);
    machine.mem_store_byte(0x9D702, 0x51);
    machine.mem_store_byte(0x9D703, 0x90);
    machine.mem_store_byte(0xB30A2, 0xD7);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9C53);
    EXPECT_FLAGS(0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9D6FE), 0x3E);
    EXPECT_EQ(memory.load8(0x9D6FF), 0x18);
    EXPECT_EQ(memory.load8(0x9D700), 0xB3);
    EXPECT_EQ(memory.load8(0x9D701), 0x23);
    EXPECT_EQ(memory.load8(0x9D702), 0x51);
    EXPECT_EQ(memory.load8(0x9D703), 0x90);
    EXPECT_EQ(memory.load8(0xB30A2), 0xD0);
}

TEST_F(MachineTest, sbb_byte_es_si_3AE9h_9Ch)
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
    machine.mem_store_byte(0xC4AD4, 0x9C);
    machine.mem_store_byte(0xC4AD5, 0x17);
    machine.mem_store_byte(0xC4AD6, 0xC5);
    machine.mem_store_byte(0xC4AD7, 0x9C);
    machine.mem_store_byte(0xC47E7, 0x5C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2FF8);
    EXPECT_FLAGS(0xF887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC4AD2), 0x26);
    EXPECT_EQ(memory.load8(0xC4AD3), 0x82);
    EXPECT_EQ(memory.load8(0xC4AD4), 0x9C);
    EXPECT_EQ(memory.load8(0xC4AD5), 0x17);
    EXPECT_EQ(memory.load8(0xC4AD6), 0xC5);
    EXPECT_EQ(memory.load8(0xC4AD7), 0x9C);
    EXPECT_EQ(memory.load8(0xC47E7), 0xC0);
}

TEST_F(MachineTest, sbb_byte_ss_bx_di_5h_2Dh)
{
    // Initial CPU State
    cpu.set_ax(0x5388);
    cpu.set_bx(0x55D4);
    cpu.set_cx(0x2ABE);
    cpu.set_dx(0x086D);
    cpu.set_cs(0x74D6);
    cpu.set_ss(0x8586);
    cpu.set_ds(0x6B81);
    cpu.set_es(0xDF73);
    cpu.set_sp(0xF202);
    cpu.set_bp(0x8E7F);
    cpu.set_si(0x3FAA);
    cpu.set_di(0x4AE8);
    cpu.set_ip(0x5ECC);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7AC2C, 0x36);
    machine.mem_store_byte(0x7AC2D, 0x80);
    machine.mem_store_byte(0x7AC2E, 0x59);
    machine.mem_store_byte(0x7AC2F, 0x05);
    machine.mem_store_byte(0x7AC30, 0x2D);
    machine.mem_store_byte(0x7AC31, 0x90);
    machine.mem_store_byte(0x8F921, 0x33);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5ED1);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7AC2C), 0x36);
    EXPECT_EQ(memory.load8(0x7AC2D), 0x80);
    EXPECT_EQ(memory.load8(0x7AC2E), 0x59);
    EXPECT_EQ(memory.load8(0x7AC2F), 0x05);
    EXPECT_EQ(memory.load8(0x7AC30), 0x2D);
    EXPECT_EQ(memory.load8(0x7AC31), 0x90);
    EXPECT_EQ(memory.load8(0x8F921), 0x05);
}

TEST_F(MachineTest, sbb_di_F15Eh)
{
    // Initial CPU State
    cpu.set_ax(0xC8B7);
    cpu.set_bx(0xACCC);
    cpu.set_cx(0x9486);
    cpu.set_dx(0x0485);
    cpu.set_cs(0xB8D9);
    cpu.set_ss(0x478A);
    cpu.set_ds(0x2C8C);
    cpu.set_es(0x047C);
    cpu.set_sp(0x11CB);
    cpu.set_bp(0xDE87);
    cpu.set_si(0xE293);
    cpu.set_di(0xEFCA);
    cpu.set_ip(0x53CD);
    cpu.set_flags(0xFC52);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBE15D, 0x81);
    machine.mem_store_byte(0xBE15E, 0xDF);
    machine.mem_store_byte(0xBE15F, 0x5E);
    machine.mem_store_byte(0xBE160, 0xF1);
    machine.mem_store_byte(0xBE161, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xFE6C);
    EXPECT_EQ(cpu.get_ip(), 0x53D1);
    EXPECT_FLAGS(0xF497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBE15D), 0x81);
    EXPECT_EQ(memory.load8(0xBE15E), 0xDF);
    EXPECT_EQ(memory.load8(0xBE15F), 0x5E);
    EXPECT_EQ(memory.load8(0xBE160), 0xF1);
    EXPECT_EQ(memory.load8(0xBE161), 0x90);
}

TEST_F(MachineTest, sbb_si_word_ss_si_796Bh)
{
    // Initial CPU State
    cpu.set_ax(0x97AE);
    cpu.set_bx(0xA5D3);
    cpu.set_cx(0x2250);
    cpu.set_dx(0x069B);
    cpu.set_cs(0x2DE9);
    cpu.set_ss(0xB963);
    cpu.set_ds(0x7B6D);
    cpu.set_es(0xF00B);
    cpu.set_sp(0xE05C);
    cpu.set_bp(0x0000);
    cpu.set_si(0x56C8);
    cpu.set_di(0x5B43);
    cpu.set_ip(0x2F0C);
    cpu.set_flags(0xF093);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x30D9C, 0x36);
    machine.mem_store_byte(0x30D9D, 0x1B);
    machine.mem_store_byte(0x30D9E, 0xB4);
    machine.mem_store_byte(0x30D9F, 0x95);
    machine.mem_store_byte(0x30DA0, 0x86);
    machine.mem_store_byte(0x30DA1, 0x90);
    machine.mem_store_byte(0xC738D, 0xE7);
    machine.mem_store_byte(0xC738E, 0x4E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x07E0);
    EXPECT_EQ(cpu.get_ip(), 0x2F11);
    EXPECT_FLAGS(0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30D9C), 0x36);
    EXPECT_EQ(memory.load8(0x30D9D), 0x1B);
    EXPECT_EQ(memory.load8(0x30D9E), 0xB4);
    EXPECT_EQ(memory.load8(0x30D9F), 0x95);
    EXPECT_EQ(memory.load8(0x30DA0), 0x86);
    EXPECT_EQ(memory.load8(0x30DA1), 0x90);
    EXPECT_EQ(memory.load8(0xC738D), 0xE7);
    EXPECT_EQ(memory.load8(0xC738E), 0x4E);
}

TEST_F(MachineTest, sbb_word_ds_di_Eh)
{
    // Initial CPU State
    cpu.set_ax(0x9CAD);
    cpu.set_bx(0xB1C4);
    cpu.set_cx(0x4F28);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x5944);
    cpu.set_ss(0xF80B);
    cpu.set_ds(0xB801);
    cpu.set_es(0x5A75);
    cpu.set_sp(0x1B3E);
    cpu.set_bp(0xE900);
    cpu.set_si(0xF0A5);
    cpu.set_di(0x1D30);
    cpu.set_ip(0x6AED);
    cpu.set_flags(0xF4C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5FF2D, 0x83);
    machine.mem_store_byte(0x5FF2E, 0x1D);
    machine.mem_store_byte(0x5FF2F, 0x0E);
    machine.mem_store_byte(0x5FF30, 0x90);
    machine.mem_store_byte(0x5FF31, 0x90);
    machine.mem_store_byte(0xB9D40, 0xBD);
    machine.mem_store_byte(0xB9D41, 0x81);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6AF0);
    EXPECT_FLAGS(0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5FF2D), 0x83);
    EXPECT_EQ(memory.load8(0x5FF2E), 0x1D);
    EXPECT_EQ(memory.load8(0x5FF2F), 0x0E);
    EXPECT_EQ(memory.load8(0x5FF30), 0x90);
    EXPECT_EQ(memory.load8(0x5FF31), 0x90);
    EXPECT_EQ(memory.load8(0xB9D40), 0xAF);
    EXPECT_EQ(memory.load8(0xB9D41), 0x81);
}

TEST_F(MachineTest, sbb_word_ds_di_sp)
{
    // Initial CPU State
    cpu.set_ax(0x99CC);
    cpu.set_bx(0xC317);
    cpu.set_cx(0x91A4);
    cpu.set_dx(0x8625);
    cpu.set_cs(0xC049);
    cpu.set_ss(0xA950);
    cpu.set_ds(0x927D);
    cpu.set_es(0xB101);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xE3B4);
    cpu.set_si(0x7824);
    cpu.set_di(0x2C24);
    cpu.set_ip(0xCBE6);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCD076, 0x19);
    machine.mem_store_byte(0xCD077, 0x25);
    machine.mem_store_byte(0xCD078, 0x90);
    machine.mem_store_byte(0xCD079, 0x90);
    machine.mem_store_byte(0xCD07A, 0x90);
    machine.mem_store_byte(0xCD07B, 0x90);
    machine.mem_store_byte(0x953F4, 0x9A);
    machine.mem_store_byte(0x953F5, 0x88);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCBE8);
    EXPECT_FLAGS(0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCD076), 0x19);
    EXPECT_EQ(memory.load8(0xCD077), 0x25);
    EXPECT_EQ(memory.load8(0xCD078), 0x90);
    EXPECT_EQ(memory.load8(0xCD079), 0x90);
    EXPECT_EQ(memory.load8(0xCD07A), 0x90);
    EXPECT_EQ(memory.load8(0xCD07B), 0x90);
    EXPECT_EQ(memory.load8(0x953F4), 0x9A);
    EXPECT_EQ(memory.load8(0x953F5), 0x88);
}

TEST_F(MachineTest, sub_al_26h)
{
    // Initial CPU State
    cpu.set_ax(0xD465);
    cpu.set_bx(0xB10C);
    cpu.set_cx(0x7B66);
    cpu.set_dx(0x2E35);
    cpu.set_cs(0xCA8B);
    cpu.set_ss(0xE227);
    cpu.set_ds(0x228C);
    cpu.set_es(0x8093);
    cpu.set_sp(0x9B76);
    cpu.set_bp(0xA4CA);
    cpu.set_si(0xA9C5);
    cpu.set_di(0x1451);
    cpu.set_ip(0x35F7);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCDEA7, 0x26);
    machine.mem_store_byte(0xCDEA8, 0x2C);
    machine.mem_store_byte(0xCDEA9, 0x26);
    machine.mem_store_byte(0xCDEAA, 0x90);
    machine.mem_store_byte(0xCDEAB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD43F);
    EXPECT_EQ(cpu.get_ip(), 0x35FA);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCDEA7), 0x26);
    EXPECT_EQ(memory.load8(0xCDEA8), 0x2C);
    EXPECT_EQ(memory.load8(0xCDEA9), 0x26);
    EXPECT_EQ(memory.load8(0xCDEAA), 0x90);
    EXPECT_EQ(memory.load8(0xCDEAB), 0x90);
}

TEST_F(MachineTest, sub_ax_8FC7h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0xEA8F);
    cpu.set_cx(0x3DC0);
    cpu.set_dx(0x8564);
    cpu.set_cs(0x7EBF);
    cpu.set_ss(0xE63C);
    cpu.set_ds(0x7C53);
    cpu.set_es(0x09FC);
    cpu.set_sp(0x8629);
    cpu.set_bp(0x058E);
    cpu.set_si(0x7504);
    cpu.set_di(0xB9F6);
    cpu.set_ip(0x96E9);
    cpu.set_flags(0xF493);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x882D9, 0x2E);
    machine.mem_store_byte(0x882DA, 0x2D);
    machine.mem_store_byte(0x882DB, 0xC7);
    machine.mem_store_byte(0x882DC, 0x8F);
    machine.mem_store_byte(0x882DD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7039);
    EXPECT_EQ(cpu.get_ip(), 0x96ED);
    EXPECT_FLAGS(0xF417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x882D9), 0x2E);
    EXPECT_EQ(memory.load8(0x882DA), 0x2D);
    EXPECT_EQ(memory.load8(0x882DB), 0xC7);
    EXPECT_EQ(memory.load8(0x882DC), 0x8F);
    EXPECT_EQ(memory.load8(0x882DD), 0x90);
}

TEST_F(MachineTest, sub_bh_cl)
{
    // Initial CPU State
    cpu.set_ax(0x6BCA);
    cpu.set_bx(0x39EF);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x21D1);
    cpu.set_cs(0x1511);
    cpu.set_ss(0xB777);
    cpu.set_ds(0x5209);
    cpu.set_es(0x1A63);
    cpu.set_sp(0x84CE);
    cpu.set_bp(0x8421);
    cpu.set_si(0xD7B4);
    cpu.set_di(0xEB25);
    cpu.set_ip(0x5B9E);
    cpu.set_flags(0xFCC6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1ACAE, 0x26);
    machine.mem_store_byte(0x1ACAF, 0x28);
    machine.mem_store_byte(0x1ACB0, 0xCF);
    machine.mem_store_byte(0x1ACB1, 0x90);
    machine.mem_store_byte(0x1ACB2, 0x90);
    machine.mem_store_byte(0x1ACB3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5BA1);
    EXPECT_FLAGS(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1ACAE), 0x26);
    EXPECT_EQ(memory.load8(0x1ACAF), 0x28);
    EXPECT_EQ(memory.load8(0x1ACB0), 0xCF);
    EXPECT_EQ(memory.load8(0x1ACB1), 0x90);
    EXPECT_EQ(memory.load8(0x1ACB2), 0x90);
    EXPECT_EQ(memory.load8(0x1ACB3), 0x90);
}

TEST_F(MachineTest, sub_bx_word_ds_bx_di_1263h)
{
    // Initial CPU State
    cpu.set_ax(0x74B8);
    cpu.set_bx(0x9509);
    cpu.set_cx(0xAC4C);
    cpu.set_dx(0x4FD3);
    cpu.set_cs(0xFBB3);
    cpu.set_ss(0xB56B);
    cpu.set_ds(0x36F3);
    cpu.set_es(0xEF18);
    cpu.set_sp(0x39E7);
    cpu.set_bp(0xD238);
    cpu.set_si(0xF0B1);
    cpu.set_di(0xC279);
    cpu.set_ip(0xA38B);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05EBB, 0x2B);
    machine.mem_store_byte(0x05EBC, 0x99);
    machine.mem_store_byte(0x05EBD, 0x9D);
    machine.mem_store_byte(0x05EBE, 0xED);
    machine.mem_store_byte(0x05EBF, 0x90);
    machine.mem_store_byte(0x3B44F, 0x9E);
    machine.mem_store_byte(0x3B450, 0x3A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x5A6B);
    EXPECT_EQ(cpu.get_ip(), 0xA38F);
    EXPECT_FLAGS(0xF812);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x05EBB), 0x2B);
    EXPECT_EQ(memory.load8(0x05EBC), 0x99);
    EXPECT_EQ(memory.load8(0x05EBD), 0x9D);
    EXPECT_EQ(memory.load8(0x05EBE), 0xED);
    EXPECT_EQ(memory.load8(0x05EBF), 0x90);
    EXPECT_EQ(memory.load8(0x3B44F), 0x9E);
    EXPECT_EQ(memory.load8(0x3B450), 0x3A);
}

TEST_F(MachineTest, sub_byte_ds_bx_si_61h_4h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x99AA);
    cpu.set_dx(0xCAB7);
    cpu.set_cs(0x3623);
    cpu.set_ss(0xDE07);
    cpu.set_ds(0x8493);
    cpu.set_es(0x73D1);
    cpu.set_sp(0x7492);
    cpu.set_bp(0x72B4);
    cpu.set_si(0x8E3F);
    cpu.set_di(0x7F19);
    cpu.set_ip(0x4104);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3A334, 0x80);
    machine.mem_store_byte(0x3A335, 0x68);
    machine.mem_store_byte(0x3A336, 0x9F);
    machine.mem_store_byte(0x3A337, 0x04);
    machine.mem_store_byte(0x3A338, 0x90);
    machine.mem_store_byte(0x3A339, 0x90);
    machine.mem_store_byte(0x8D70E, 0x08);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4108);
    EXPECT_FLAGS(0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3A334), 0x80);
    EXPECT_EQ(memory.load8(0x3A335), 0x68);
    EXPECT_EQ(memory.load8(0x3A336), 0x9F);
    EXPECT_EQ(memory.load8(0x3A337), 0x04);
    EXPECT_EQ(memory.load8(0x3A338), 0x90);
    EXPECT_EQ(memory.load8(0x3A339), 0x90);
    EXPECT_EQ(memory.load8(0x8D70E), 0x04);
}

TEST_F(MachineTest, sub_byte_es_bp_di_6Ah)
{
    // Initial CPU State
    cpu.set_ax(0x8E62);
    cpu.set_bx(0x1C5D);
    cpu.set_cx(0x5192);
    cpu.set_dx(0x6F8D);
    cpu.set_cs(0x00FE);
    cpu.set_ss(0x669C);
    cpu.set_ds(0xDBFE);
    cpu.set_es(0x7DA4);
    cpu.set_sp(0xEBE4);
    cpu.set_bp(0x3FB2);
    cpu.set_si(0x0000);
    cpu.set_di(0xDA35);
    cpu.set_ip(0x1174);
    cpu.set_flags(0xF096);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02154, 0x26);
    machine.mem_store_byte(0x02155, 0x82);
    machine.mem_store_byte(0x02156, 0x2B);
    machine.mem_store_byte(0x02157, 0x6A);
    machine.mem_store_byte(0x02158, 0x90);
    machine.mem_store_byte(0x02159, 0x90);
    machine.mem_store_byte(0x7F427, 0x40);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1178);
    EXPECT_FLAGS(0xF093);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02154), 0x26);
    EXPECT_EQ(memory.load8(0x02155), 0x82);
    EXPECT_EQ(memory.load8(0x02156), 0x2B);
    EXPECT_EQ(memory.load8(0x02157), 0x6A);
    EXPECT_EQ(memory.load8(0x02158), 0x90);
    EXPECT_EQ(memory.load8(0x02159), 0x90);
    EXPECT_EQ(memory.load8(0x7F427), 0xD6);
}

TEST_F(MachineTest, sub_ch_byte_ds_si_28h)
{
    // Initial CPU State
    cpu.set_ax(0x0946);
    cpu.set_bx(0x2663);
    cpu.set_cx(0xA3C0);
    cpu.set_dx(0xC37D);
    cpu.set_cs(0xF79F);
    cpu.set_ss(0x3588);
    cpu.set_ds(0xA8A3);
    cpu.set_es(0x49B7);
    cpu.set_sp(0x9D98);
    cpu.set_bp(0xFB7A);
    cpu.set_si(0xD05E);
    cpu.set_di(0x405A);
    cpu.set_ip(0x7111);
    cpu.set_flags(0xF413);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFEB01, 0x2A);
    machine.mem_store_byte(0xFEB02, 0x6C);
    machine.mem_store_byte(0xFEB03, 0xD8);
    machine.mem_store_byte(0xFEB04, 0x90);
    machine.mem_store_byte(0xFEB05, 0x90);
    machine.mem_store_byte(0xB5A66, 0x9A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x09C0);
    EXPECT_EQ(cpu.get_ip(), 0x7114);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFEB01), 0x2A);
    EXPECT_EQ(memory.load8(0xFEB02), 0x6C);
    EXPECT_EQ(memory.load8(0xFEB03), 0xD8);
    EXPECT_EQ(memory.load8(0xFEB04), 0x90);
    EXPECT_EQ(memory.load8(0xFEB05), 0x90);
    EXPECT_EQ(memory.load8(0xB5A66), 0x9A);
}

TEST_F(MachineTest, sub_si_7h)
{
    // Initial CPU State
    cpu.set_ax(0xBE48);
    cpu.set_bx(0x06EA);
    cpu.set_cx(0xD268);
    cpu.set_dx(0xD6A5);
    cpu.set_cs(0xE373);
    cpu.set_ss(0xDF83);
    cpu.set_ds(0x939C);
    cpu.set_es(0xD703);
    cpu.set_sp(0xDFC0);
    cpu.set_bp(0x09D4);
    cpu.set_si(0xF529);
    cpu.set_di(0x3773);
    cpu.set_ip(0x3F1B);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE764B, 0x26);
    machine.mem_store_byte(0xE764C, 0x83);
    machine.mem_store_byte(0xE764D, 0xEE);
    machine.mem_store_byte(0xE764E, 0x07);
    machine.mem_store_byte(0xE764F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0xF522);
    EXPECT_EQ(cpu.get_ip(), 0x3F1F);
    EXPECT_FLAGS(0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE764B), 0x26);
    EXPECT_EQ(memory.load8(0xE764C), 0x83);
    EXPECT_EQ(memory.load8(0xE764D), 0xEE);
    EXPECT_EQ(memory.load8(0xE764E), 0x07);
    EXPECT_EQ(memory.load8(0xE764F), 0x90);
}

TEST_F(MachineTest, sub_word_ds_di_77EEh_ax)
{
    // Initial CPU State
    cpu.set_ax(0x4FE9);
    cpu.set_bx(0x8CAD);
    cpu.set_cx(0xD916);
    cpu.set_dx(0xC0D9);
    cpu.set_cs(0x7559);
    cpu.set_ss(0x6CB7);
    cpu.set_ds(0xF9BC);
    cpu.set_es(0x18E9);
    cpu.set_sp(0x8227);
    cpu.set_bp(0xD5A1);
    cpu.set_si(0xA176);
    cpu.set_di(0x6D76);
    cpu.set_ip(0x405E);
    cpu.set_flags(0xF0D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x795EE, 0x29);
    machine.mem_store_byte(0x795EF, 0x85);
    machine.mem_store_byte(0x795F0, 0x12);
    machine.mem_store_byte(0x795F1, 0x88);
    machine.mem_store_byte(0x795F2, 0x90);
    machine.mem_store_byte(0x795F3, 0x90);
    machine.mem_store_byte(0x09148, 0x35);
    machine.mem_store_byte(0x09149, 0x67);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4062);
    EXPECT_FLAGS(0xF012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x795EE), 0x29);
    EXPECT_EQ(memory.load8(0x795EF), 0x85);
    EXPECT_EQ(memory.load8(0x795F0), 0x12);
    EXPECT_EQ(memory.load8(0x795F1), 0x88);
    EXPECT_EQ(memory.load8(0x795F2), 0x90);
    EXPECT_EQ(memory.load8(0x795F3), 0x90);
    EXPECT_EQ(memory.load8(0x09148), 0x4C);
    EXPECT_EQ(memory.load8(0x09149), 0x17);
}

TEST_F(MachineTest, sub_word_ss_si_3h_8F8Ah)
{
    // Initial CPU State
    cpu.set_ax(0xC7A5);
    cpu.set_bx(0x3FBF);
    cpu.set_cx(0x30EE);
    cpu.set_dx(0x3391);
    cpu.set_cs(0x2540);
    cpu.set_ss(0x7105);
    cpu.set_ds(0x10DD);
    cpu.set_es(0x5659);
    cpu.set_sp(0xA070);
    cpu.set_bp(0x2EBA);
    cpu.set_si(0x097E);
    cpu.set_di(0xE594);
    cpu.set_ip(0x4A66);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x29E66, 0x36);
    machine.mem_store_byte(0x29E67, 0x81);
    machine.mem_store_byte(0x29E68, 0x6C);
    machine.mem_store_byte(0x29E69, 0x03);
    machine.mem_store_byte(0x29E6A, 0x8A);
    machine.mem_store_byte(0x29E6B, 0x8F);
    machine.mem_store_byte(0x719D1, 0xC2);
    machine.mem_store_byte(0x719D2, 0x30);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4A6C);
    EXPECT_FLAGS(0xFC93);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x29E66), 0x36);
    EXPECT_EQ(memory.load8(0x29E67), 0x81);
    EXPECT_EQ(memory.load8(0x29E68), 0x6C);
    EXPECT_EQ(memory.load8(0x29E69), 0x03);
    EXPECT_EQ(memory.load8(0x29E6A), 0x8A);
    EXPECT_EQ(memory.load8(0x29E6B), 0x8F);
    EXPECT_EQ(memory.load8(0x719D1), 0x38);
    EXPECT_EQ(memory.load8(0x719D2), 0xA1);
}
