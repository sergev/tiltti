#include "fixture.h"

//
// div byte [ss:bp-54Eh]
//
TEST_F(MachineTest, div_byte_ss_bp_54Eh)
{
    // Initial CPU State
    cpu.set_ax(0x0118);
    cpu.set_bx(0xBBDF);
    cpu.set_cx(0xEF52);
    cpu.set_dx(0x835F);
    cpu.set_cs(0x3FB1);
    cpu.set_ss(0x1240);
    cpu.set_ds(0x0895);
    cpu.set_es(0x91FE);
    cpu.set_sp(0xF3B9);
    cpu.set_bp(0xFB05);
    cpu.set_si(0x6835);
    cpu.set_di(0xBEDA);
    cpu.set_ip(0x258F);
    cpu.set_flags(0xF402);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4209F, 0xF6);
    machine.mem_store_byte(0x420A0, 0xB6);
    machine.mem_store_byte(0x420A1, 0xB2);
    machine.mem_store_byte(0x420A2, 0xFA);
    machine.mem_store_byte(0x219B7, 0x27);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0707);
    EXPECT_EQ(cpu.get_ip(), 0x2593);
    EXPECT_EQ(cpu.get_flags(), 0xF403);

    // Final RAM entries
}

//
// div word [ds:si-458Dh]
//
TEST_F(MachineTest, div_word_ds_si_458Dh)
{
    // Initial CPU State
    cpu.set_ax(0x5736);
    cpu.set_bx(0x1834);
    cpu.set_cx(0xD5EC);
    cpu.set_dx(0xD9FD);
    cpu.set_cs(0xE298);
    cpu.set_ss(0x4A28);
    cpu.set_ds(0x521C);
    cpu.set_es(0xF398);
    cpu.set_sp(0x2A71);
    cpu.set_bp(0x86E5);
    cpu.set_si(0xF7A6);
    cpu.set_di(0x1696);
    cpu.set_ip(0xCEB1);
    cpu.set_flags(0xFC46);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEF831, 0xF7);
    machine.mem_store_byte(0xEF832, 0xB4);
    machine.mem_store_byte(0xEF833, 0x73);
    machine.mem_store_byte(0xEF834, 0xBA);
    machine.mem_store_byte(0x5D3D9, 0xFF);
    machine.mem_store_byte(0x5D3DA, 0xED);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xEA7A);
    EXPECT_EQ(cpu.get_dx(), 0xD5B0);
    EXPECT_EQ(cpu.get_ip(), 0xCEB5);
    EXPECT_EQ(cpu.get_flags(), 0xF496);

    // Final RAM entries
}

//
// idiv al
//
TEST_F(MachineTest, idiv_al)
{
    // Initial CPU State
    cpu.set_ax(0x139F);
    cpu.set_bx(0x54BC);
    cpu.set_cx(0x359E);
    cpu.set_dx(0xDE63);
    cpu.set_cs(0x9536);
    cpu.set_ss(0x2D80);
    cpu.set_ds(0x5F27);
    cpu.set_es(0xFE13);
    cpu.set_sp(0x6F1F);
    cpu.set_bp(0xEDAE);
    cpu.set_si(0x22B6);
    cpu.set_di(0x896C);
    cpu.set_ip(0xB285);
    cpu.set_flags(0xF4D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA05E5, 0xF6);
    machine.mem_store_byte(0xA05E6, 0xF8);
    machine.mem_store_byte(0xA05E7, 0x90);
    machine.mem_store_byte(0xA05E8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x4CCD);
    EXPECT_EQ(cpu.get_ip(), 0xB287);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// idiv ax
//
TEST_F(MachineTest, idiv_ax)
{
    // Initial CPU State
    cpu.set_ax(0xCBA9);
    cpu.set_bx(0xAB6F);
    cpu.set_cx(0xE148);
    cpu.set_dx(0xC574);
    cpu.set_cs(0xDA2B);
    cpu.set_ss(0xBB6A);
    cpu.set_ds(0x1846);
    cpu.set_es(0x581D);
    cpu.set_sp(0x160F);
    cpu.set_bp(0xFE82);
    cpu.set_si(0xEE5C);
    cpu.set_di(0xBDDD);
    cpu.set_ip(0x93EE);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE369E, 0x36);
    machine.mem_store_byte(0xE369F, 0xF7);
    machine.mem_store_byte(0xE36A0, 0xF8);
    machine.mem_store_byte(0xE36A1, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x1609);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBCCAD), 0x02);
    EXPECT_EQ(memory.load8(0xBCCAE), 0xF4);
    EXPECT_EQ(memory.load8(0xBCCAB), 0x2B);
    EXPECT_EQ(memory.load8(0xBCCAC), 0xDA);
    EXPECT_EQ(memory.load8(0xBCCA9), 0xF1);
    EXPECT_EQ(memory.load8(0xBCCAA), 0x93);
}

//
// imul ah
//
TEST_F(MachineTest, imul_ah)
{
    // Initial CPU State
    cpu.set_ax(0x4D26);
    cpu.set_bx(0xB28A);
    cpu.set_cx(0xA70E);
    cpu.set_dx(0x710E);
    cpu.set_cs(0xDF29);
    cpu.set_ss(0xA0E8);
    cpu.set_ds(0x6F57);
    cpu.set_es(0xAFD5);
    cpu.set_sp(0xCEB4);
    cpu.set_bp(0xFFB4);
    cpu.set_si(0xF11F);
    cpu.set_di(0x34AD);
    cpu.set_ip(0x4F09);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE4199, 0xF6);
    machine.mem_store_byte(0xE419A, 0xEC);
    machine.mem_store_byte(0xE419B, 0x90);
    machine.mem_store_byte(0xE419C, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0B6E);
    EXPECT_EQ(cpu.get_ip(), 0x4F0B);
    EXPECT_EQ(cpu.get_flags(), 0xFC03);

    // Final RAM entries
}

//
// imul word [ss:bp+di-71h]
//
TEST_F(MachineTest, imul_word_ss_bp_di_71h)
{
    // Initial CPU State
    cpu.set_ax(0x4577);
    cpu.set_bx(0xF60F);
    cpu.set_cx(0x2CAA);
    cpu.set_dx(0xE7B8);
    cpu.set_cs(0x7571);
    cpu.set_ss(0x862E);
    cpu.set_ds(0xD83A);
    cpu.set_es(0x47D5);
    cpu.set_sp(0x8729);
    cpu.set_bp(0x1B8E);
    cpu.set_si(0xC346);
    cpu.set_di(0x2639);
    cpu.set_ip(0x161B);
    cpu.set_flags(0xF442);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x76D2B, 0xF7);
    machine.mem_store_byte(0x76D2C, 0x6B);
    machine.mem_store_byte(0x76D2D, 0x8F);
    machine.mem_store_byte(0x76D2E, 0x90);
    machine.mem_store_byte(0x8A436, 0x65);
    machine.mem_store_byte(0x8A437, 0x0E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xE9F3);
    EXPECT_EQ(cpu.get_dx(), 0x03E7);
    EXPECT_EQ(cpu.get_ip(), 0x161E);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
}

//
// mul byte [ds:si+3F00h]
//
TEST_F(MachineTest, mul_byte_ds_si_3F00h)
{
    // Initial CPU State
    cpu.set_ax(0x3315);
    cpu.set_bx(0xFBA7);
    cpu.set_cx(0xBAD2);
    cpu.set_dx(0x6C6B);
    cpu.set_cs(0x0B4C);
    cpu.set_ss(0xA4B7);
    cpu.set_ds(0x041D);
    cpu.set_es(0xD89B);
    cpu.set_sp(0xA0B0);
    cpu.set_bp(0x84D1);
    cpu.set_si(0x2AFB);
    cpu.set_di(0xC1A1);
    cpu.set_ip(0x9C5A);
    cpu.set_flags(0xFCC6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1511A, 0xF6);
    machine.mem_store_byte(0x1511B, 0xA4);
    machine.mem_store_byte(0x1511C, 0x00);
    machine.mem_store_byte(0x1511D, 0x3F);
    machine.mem_store_byte(0x0ABCB, 0xE4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x12B4);
    EXPECT_EQ(cpu.get_ip(), 0x9C5E);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
}

//
// mul word [ds:bx-5934h]
//
TEST_F(MachineTest, mul_word_ds_bx_5934h)
{
    // Initial CPU State
    cpu.set_ax(0xF5DE);
    cpu.set_bx(0xD223);
    cpu.set_cx(0x4C84);
    cpu.set_dx(0xDA8E);
    cpu.set_cs(0x1F27);
    cpu.set_ss(0x664D);
    cpu.set_ds(0xAC7E);
    cpu.set_es(0x08D6);
    cpu.set_sp(0x75B4);
    cpu.set_bp(0xBC1F);
    cpu.set_si(0x327E);
    cpu.set_di(0xE205);
    cpu.set_ip(0x2868);
    cpu.set_flags(0xFC46);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x21AD8, 0x3E);
    machine.mem_store_byte(0x21AD9, 0xF7);
    machine.mem_store_byte(0x21ADA, 0xA7);
    machine.mem_store_byte(0x21ADB, 0xCC);
    machine.mem_store_byte(0x21ADC, 0xA6);
    machine.mem_store_byte(0xB40CF, 0x73);
    machine.mem_store_byte(0xB40D0, 0x73);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2CBA);
    EXPECT_EQ(cpu.get_dx(), 0x6EE1);
    EXPECT_EQ(cpu.get_ip(), 0x286D);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
}

//
// neg ah
//
TEST_F(MachineTest, neg_ah)
{
    // Initial CPU State
    cpu.set_ax(0x7FA4);
    cpu.set_bx(0x76E4);
    cpu.set_cx(0x1036);
    cpu.set_dx(0xB9A3);
    cpu.set_cs(0x32D7);
    cpu.set_ss(0x42B6);
    cpu.set_ds(0xEFEE);
    cpu.set_es(0xE4DC);
    cpu.set_sp(0xCE6F);
    cpu.set_bp(0x5B9D);
    cpu.set_si(0x77DB);
    cpu.set_di(0x0CE1);
    cpu.set_ip(0x765C);
    cpu.set_flags(0xF486);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3A3CC, 0x3E);
    machine.mem_store_byte(0x3A3CD, 0xF6);
    machine.mem_store_byte(0x3A3CE, 0xDC);
    machine.mem_store_byte(0x3A3CF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x81A4);
    EXPECT_EQ(cpu.get_ip(), 0x765F);
    EXPECT_EQ(cpu.get_flags(), 0xF497);

    // Final RAM entries
}

//
// neg word [ss:bp+si]
//
TEST_F(MachineTest, neg_word_ss_bp_si)
{
    // Initial CPU State
    cpu.set_ax(0x49C3);
    cpu.set_bx(0xAB40);
    cpu.set_cx(0xE324);
    cpu.set_dx(0x7F12);
    cpu.set_cs(0x22BA);
    cpu.set_ss(0x1AE5);
    cpu.set_ds(0x4E21);
    cpu.set_es(0x26C1);
    cpu.set_sp(0x6E46);
    cpu.set_bp(0x2A2C);
    cpu.set_si(0x2931);
    cpu.set_di(0xEEC6);
    cpu.set_ip(0xBAE1);
    cpu.set_flags(0xF803);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2E681, 0x36);
    machine.mem_store_byte(0x2E682, 0xF7);
    machine.mem_store_byte(0x2E683, 0x1A);
    machine.mem_store_byte(0x2E684, 0x90);
    machine.mem_store_byte(0x201AD, 0xD9);
    machine.mem_store_byte(0x201AE, 0x48);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBAE4);
    EXPECT_EQ(cpu.get_flags(), 0xF097);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x201AD), 0x27);
    EXPECT_EQ(memory.load8(0x201AE), 0xB7);
}

//
// not byte [cs:bx]
//
TEST_F(MachineTest, not_byte_cs_bx)
{
    // Initial CPU State
    cpu.set_ax(0xF41B);
    cpu.set_bx(0x4A45);
    cpu.set_cx(0xE7A8);
    cpu.set_dx(0x2CDD);
    cpu.set_cs(0x8377);
    cpu.set_ss(0xCD14);
    cpu.set_ds(0x5D81);
    cpu.set_es(0x9444);
    cpu.set_sp(0xB1E1);
    cpu.set_bp(0x9962);
    cpu.set_si(0xFC0E);
    cpu.set_di(0xE416);
    cpu.set_ip(0x82C6);
    cpu.set_flags(0xF457);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8BA36, 0x2E);
    machine.mem_store_byte(0x8BA37, 0xF6);
    machine.mem_store_byte(0x8BA38, 0x17);
    machine.mem_store_byte(0x8BA39, 0x90);
    machine.mem_store_byte(0x881B5, 0xE3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x82C9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x881B5), 0x1C);
}

//
// not word [ds:bx+di]
//
TEST_F(MachineTest, not_word_ds_bx_di)
{
    // Initial CPU State
    cpu.set_ax(0x7FD1);
    cpu.set_bx(0x7E34);
    cpu.set_cx(0x562C);
    cpu.set_dx(0xB27B);
    cpu.set_cs(0x288F);
    cpu.set_ss(0xBB82);
    cpu.set_ds(0x30C9);
    cpu.set_es(0x6EC8);
    cpu.set_sp(0x2A33);
    cpu.set_bp(0x9F2C);
    cpu.set_si(0xE869);
    cpu.set_di(0x4918);
    cpu.set_ip(0xBE91);
    cpu.set_flags(0xF886);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x34781, 0xF7);
    machine.mem_store_byte(0x34782, 0x11);
    machine.mem_store_byte(0x34783, 0x90);
    machine.mem_store_byte(0x34784, 0x90);
    machine.mem_store_byte(0x3D3DC, 0x8A);
    machine.mem_store_byte(0x3D3DD, 0x4A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBE93);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3D3DC), 0x75);
    EXPECT_EQ(memory.load8(0x3D3DD), 0xB5);
}
