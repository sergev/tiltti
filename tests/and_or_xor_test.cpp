#include "fixture.h"

//
// and al, 70h
//
TEST_F(MachineTest, and_al_70h)
{
    // Initial CPU State
    cpu.set_ax(0x678E);
    cpu.set_bx(0x6B31);
    cpu.set_cx(0xEA8C);
    cpu.set_dx(0x22F8);
    cpu.set_cs(0x29AE);
    cpu.set_ss(0x3188);
    cpu.set_ds(0xA14E);
    cpu.set_es(0x63CD);
    cpu.set_sp(0x9194);
    cpu.set_bp(0xAC47);
    cpu.set_si(0xB1BD);
    cpu.set_di(0x231D);
    cpu.set_ip(0x8205);
    cpu.set_flags(0xF483);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x31CE5, 0x26);
    machine.mem_store_byte(0x31CE6, 0x24);
    machine.mem_store_byte(0x31CE7, 0x70);
    machine.mem_store_byte(0x31CE8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x6700);
    EXPECT_EQ(cpu.get_ip(), 0x8208);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
}

//
// and ax, D658h
//
TEST_F(MachineTest, and_ax_D658h)
{
    // Initial CPU State
    cpu.set_ax(0xE6D7);
    cpu.set_bx(0xDD99);
    cpu.set_cx(0x844E);
    cpu.set_dx(0xD1CE);
    cpu.set_cs(0x1748);
    cpu.set_ss(0x873C);
    cpu.set_ds(0x357F);
    cpu.set_es(0xB181);
    cpu.set_sp(0x55D9);
    cpu.set_bp(0xD924);
    cpu.set_si(0xAA4D);
    cpu.set_di(0x356F);
    cpu.set_ip(0x0FEE);
    cpu.set_flags(0xF082);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1846E, 0x25);
    machine.mem_store_byte(0x1846F, 0x58);
    machine.mem_store_byte(0x18470, 0xD6);
    machine.mem_store_byte(0x18471, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xC650);
    EXPECT_EQ(cpu.get_ip(), 0x0FF1);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// and bl, byte [ds:bx+si+13h]
//
TEST_F(MachineTest, and_bl_byte_ds_bx_si_13h)
{
    // Initial CPU State
    cpu.set_ax(0x0A96);
    cpu.set_bx(0xE982);
    cpu.set_cx(0xAF06);
    cpu.set_dx(0x04D9);
    cpu.set_cs(0xFF3B);
    cpu.set_ss(0x2134);
    cpu.set_ds(0xB937);
    cpu.set_es(0xFE90);
    cpu.set_sp(0xFB25);
    cpu.set_bp(0xC31E);
    cpu.set_si(0x9A4F);
    cpu.set_di(0xA9AA);
    cpu.set_ip(0xFF60);
    cpu.set_flags(0xF4D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0F310, 0x3E);
    machine.mem_store_byte(0x0F311, 0x22);
    machine.mem_store_byte(0x0F312, 0x58);
    machine.mem_store_byte(0x0F313, 0x13);
    machine.mem_store_byte(0xC1754, 0xD1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xE980);
    EXPECT_EQ(cpu.get_ip(), 0xFF64);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
}

//
// and bp, FFE4h
//
TEST_F(MachineTest, and_bp_FFE4h)
{
    // Initial CPU State
    cpu.set_ax(0xCDF7);
    cpu.set_bx(0xB3B2);
    cpu.set_cx(0xF644);
    cpu.set_dx(0x7BCE);
    cpu.set_cs(0xE0BB);
    cpu.set_ss(0x9999);
    cpu.set_ds(0x6340);
    cpu.set_es(0x18C0);
    cpu.set_sp(0xB7F3);
    cpu.set_bp(0x07D6);
    cpu.set_si(0x7174);
    cpu.set_di(0xEDE0);
    cpu.set_ip(0x78C0);
    cpu.set_flags(0xF803);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE8470, 0x83);
    machine.mem_store_byte(0xE8471, 0xE5);
    machine.mem_store_byte(0xE8472, 0xE4);
    machine.mem_store_byte(0xE8473, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x07C4);
    EXPECT_EQ(cpu.get_ip(), 0x78C3);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
}

//
// and byte [ds:CBC8h], 11h
//
TEST_F(MachineTest, and_byte_ds_CBC8h_11h)
{
    // Initial CPU State
    cpu.set_ax(0xBAFF);
    cpu.set_bx(0x8D60);
    cpu.set_cx(0x98EE);
    cpu.set_dx(0x74B1);
    cpu.set_cs(0x899E);
    cpu.set_ss(0xBF8E);
    cpu.set_ds(0x51D8);
    cpu.set_es(0x396E);
    cpu.set_sp(0x7871);
    cpu.set_bp(0xA93B);
    cpu.set_si(0x6A41);
    cpu.set_di(0xC348);
    cpu.set_ip(0xD7BB);
    cpu.set_flags(0xFC56);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9719B, 0x80);
    machine.mem_store_byte(0x9719C, 0x26);
    machine.mem_store_byte(0x9719D, 0xC8);
    machine.mem_store_byte(0x9719E, 0xCB);
    machine.mem_store_byte(0x9719F, 0x11);
    machine.mem_store_byte(0x5E948, 0x17);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xD7C0);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5E948), 0x11);
}

//
// and byte [ds:bx-50F2h], dh
//
TEST_F(MachineTest, and_byte_ds_bx_50F2h_dh)
{
    // Initial CPU State
    cpu.set_ax(0x016F);
    cpu.set_bx(0xB06D);
    cpu.set_cx(0xEA8E);
    cpu.set_dx(0xC177);
    cpu.set_cs(0x2D72);
    cpu.set_ss(0x1B88);
    cpu.set_ds(0xB420);
    cpu.set_es(0xA1A2);
    cpu.set_sp(0xD2C4);
    cpu.set_bp(0xE1B3);
    cpu.set_si(0xE094);
    cpu.set_di(0x3411);
    cpu.set_ip(0xDC03);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3B323, 0x3E);
    machine.mem_store_byte(0x3B324, 0x20);
    machine.mem_store_byte(0x3B325, 0xB7);
    machine.mem_store_byte(0x3B326, 0x0E);
    machine.mem_store_byte(0x3B327, 0xAF);
    machine.mem_store_byte(0xBA17B, 0xD7);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDC08);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBA17B), 0xC1);
}

//
// and byte [ss:bp+di-Dh], F5h
//
TEST_F(MachineTest, and_byte_ss_bp_di_Dh_F5h)
{
    // Initial CPU State
    cpu.set_ax(0xB504);
    cpu.set_bx(0x13BA);
    cpu.set_cx(0xD71E);
    cpu.set_dx(0x8F10);
    cpu.set_cs(0x489A);
    cpu.set_ss(0xB2BE);
    cpu.set_ds(0xF8FC);
    cpu.set_es(0x8DF0);
    cpu.set_sp(0xA554);
    cpu.set_bp(0x52CA);
    cpu.set_si(0x51D9);
    cpu.set_di(0xDF90);
    cpu.set_ip(0x17CF);
    cpu.set_flags(0xFC93);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4A16F, 0x36);
    machine.mem_store_byte(0x4A170, 0x82);
    machine.mem_store_byte(0x4A171, 0x63);
    machine.mem_store_byte(0x4A172, 0xF3);
    machine.mem_store_byte(0x4A173, 0xF5);
    machine.mem_store_byte(0xB5E2D, 0x7E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x17D4);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB5E2D), 0x74);
}

//
// and di, word [ds:bx+di-30h]
//
TEST_F(MachineTest, and_di_word_ds_bx_di_30h)
{
    // Initial CPU State
    cpu.set_ax(0xDC62);
    cpu.set_bx(0x6A3A);
    cpu.set_cx(0xCE44);
    cpu.set_dx(0xC8CB);
    cpu.set_cs(0x5CD9);
    cpu.set_ss(0x66A0);
    cpu.set_ds(0xF28A);
    cpu.set_es(0x330D);
    cpu.set_sp(0xA8C9);
    cpu.set_bp(0x3B00);
    cpu.set_si(0x4FC6);
    cpu.set_di(0x5D90);
    cpu.set_ip(0xF34C);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6C0DC, 0x23);
    machine.mem_store_byte(0x6C0DD, 0x79);
    machine.mem_store_byte(0x6C0DE, 0xD0);
    machine.mem_store_byte(0x6C0DF, 0x90);
    machine.mem_store_byte(0xFF03A, 0x96);
    machine.mem_store_byte(0xFF03B, 0x30);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x1090);
    EXPECT_EQ(cpu.get_ip(), 0xF34F);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
}

//
// and word [cs:bp+di], bp
//
TEST_F(MachineTest, and_word_cs_bp_di_bp)
{
    // Initial CPU State
    cpu.set_ax(0xBB57);
    cpu.set_bx(0xC293);
    cpu.set_cx(0xEB8C);
    cpu.set_dx(0xAB13);
    cpu.set_cs(0xC792);
    cpu.set_ss(0xF583);
    cpu.set_ds(0xAF08);
    cpu.set_es(0x44E1);
    cpu.set_sp(0x1976);
    cpu.set_bp(0x3DF8);
    cpu.set_si(0x0D3A);
    cpu.set_di(0x87B5);
    cpu.set_ip(0xC16C);
    cpu.set_flags(0xF857);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD3A8C, 0x2E);
    machine.mem_store_byte(0xD3A8D, 0x21);
    machine.mem_store_byte(0xD3A8E, 0x2B);
    machine.mem_store_byte(0xD3A8F, 0x90);
    machine.mem_store_byte(0xD3ECD, 0x4D);
    machine.mem_store_byte(0xD3ECE, 0xE2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC16F);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD3ECD), 0x48);
    EXPECT_EQ(memory.load8(0xD3ECE), 0x20);
}

//
// and word [ss:bp+si+2Bh], 5BD4h
//
TEST_F(MachineTest, and_word_ss_bp_si_2Bh_5BD4h)
{
    // Initial CPU State
    cpu.set_ax(0x1AB1);
    cpu.set_bx(0x8FD2);
    cpu.set_cx(0x0AA6);
    cpu.set_dx(0x68A1);
    cpu.set_cs(0xFB12);
    cpu.set_ss(0x1428);
    cpu.set_ds(0x4B2C);
    cpu.set_es(0xC820);
    cpu.set_sp(0x9B39);
    cpu.set_bp(0x768A);
    cpu.set_si(0x0C43);
    cpu.set_di(0xBD4E);
    cpu.set_ip(0xDD1C);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x08E3C, 0x36);
    machine.mem_store_byte(0x08E3D, 0x81);
    machine.mem_store_byte(0x08E3E, 0x62);
    machine.mem_store_byte(0x08E3F, 0x2B);
    machine.mem_store_byte(0x08E40, 0xD4);
    machine.mem_store_byte(0x08E41, 0x5B);
    machine.mem_store_byte(0x1C578, 0xA2);
    machine.mem_store_byte(0x1C579, 0x03);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDD22);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1C578), 0x80);
}

//
// or al, 44h
//
TEST_F(MachineTest, or_al_44h)
{
    // Initial CPU State
    cpu.set_ax(0xD8B3);
    cpu.set_bx(0x3741);
    cpu.set_cx(0x894C);
    cpu.set_dx(0x3AA9);
    cpu.set_cs(0x8A49);
    cpu.set_ss(0xE4AE);
    cpu.set_ds(0x83DE);
    cpu.set_es(0xECBF);
    cpu.set_sp(0xA6D3);
    cpu.set_bp(0x85A2);
    cpu.set_si(0x0420);
    cpu.set_di(0x8CBF);
    cpu.set_ip(0xCBE0);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97070, 0x0C);
    machine.mem_store_byte(0x97071, 0x44);
    machine.mem_store_byte(0x97072, 0x90);
    machine.mem_store_byte(0x97073, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD8F7);
    EXPECT_EQ(cpu.get_ip(), 0xCBE2);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
}

//
// or ax, 1559h
//
TEST_F(MachineTest, or_ax_1559h)
{
    // Initial CPU State
    cpu.set_ax(0x0AB0);
    cpu.set_bx(0x0428);
    cpu.set_cx(0x81F8);
    cpu.set_dx(0x1C79);
    cpu.set_cs(0x89A4);
    cpu.set_ss(0x656C);
    cpu.set_ds(0x79C8);
    cpu.set_es(0xC984);
    cpu.set_sp(0xAF26);
    cpu.set_bp(0x5BF9);
    cpu.set_si(0x1EB5);
    cpu.set_di(0xD90D);
    cpu.set_ip(0x87ED);
    cpu.set_flags(0xF843);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9222D, 0x0D);
    machine.mem_store_byte(0x9222E, 0x59);
    machine.mem_store_byte(0x9222F, 0x15);
    machine.mem_store_byte(0x92230, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1FF9);
    EXPECT_EQ(cpu.get_ip(), 0x87F0);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
}

//
// or byte [cs:bp+566Bh], 46h
//
TEST_F(MachineTest, or_byte_cs_bp_566Bh_46h)
{
    // Initial CPU State
    cpu.set_ax(0x0909);
    cpu.set_bx(0x5584);
    cpu.set_cx(0xA7FE);
    cpu.set_dx(0x092D);
    cpu.set_cs(0x294A);
    cpu.set_ss(0x7AFD);
    cpu.set_ds(0x92A2);
    cpu.set_es(0x0E67);
    cpu.set_sp(0xE933);
    cpu.set_bp(0x7A12);
    cpu.set_si(0x28DF);
    cpu.set_di(0x267A);
    cpu.set_ip(0xE9CA);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x37E6A, 0x2E);
    machine.mem_store_byte(0x37E6B, 0x82);
    machine.mem_store_byte(0x37E6C, 0x8E);
    machine.mem_store_byte(0x37E6D, 0x6B);
    machine.mem_store_byte(0x37E6E, 0x56);
    machine.mem_store_byte(0x37E6F, 0x46);
    machine.mem_store_byte(0x3651D, 0x82);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE9D0);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3651D), 0xC6);
}

//
// or byte [ds:di+37h], E3h
//
TEST_F(MachineTest, or_byte_ds_di_37h_E3h)
{
    // Initial CPU State
    cpu.set_ax(0x3FFF);
    cpu.set_bx(0xBE1A);
    cpu.set_cx(0x168E);
    cpu.set_dx(0x62D4);
    cpu.set_cs(0x06EB);
    cpu.set_ss(0x8F9A);
    cpu.set_ds(0x8FEA);
    cpu.set_es(0xF824);
    cpu.set_sp(0x47DA);
    cpu.set_bp(0x0D1E);
    cpu.set_si(0xC5D6);
    cpu.set_di(0xC76F);
    cpu.set_ip(0xA0E7);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10F97, 0x80);
    machine.mem_store_byte(0x10F98, 0x4D);
    machine.mem_store_byte(0x10F99, 0x37);
    machine.mem_store_byte(0x10F9A, 0xE3);
    machine.mem_store_byte(0x9C646, 0x65);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA0EB);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9C646), 0xE7);
}

//
// or byte [ss:bp+si+619Ah], ch
//
TEST_F(MachineTest, or_byte_ss_bp_si_619Ah_ch)
{
    // Initial CPU State
    cpu.set_ax(0xB2D9);
    cpu.set_bx(0x6367);
    cpu.set_cx(0x8BC2);
    cpu.set_dx(0x98BD);
    cpu.set_cs(0x75D3);
    cpu.set_ss(0x3A7C);
    cpu.set_ds(0xC899);
    cpu.set_es(0x08E2);
    cpu.set_sp(0x288A);
    cpu.set_bp(0xFB26);
    cpu.set_si(0xECDC);
    cpu.set_di(0xE773);
    cpu.set_ip(0x0F30);
    cpu.set_flags(0xFC42);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x76C60, 0x36);
    machine.mem_store_byte(0x76C61, 0x08);
    machine.mem_store_byte(0x76C62, 0xAA);
    machine.mem_store_byte(0x76C63, 0x9A);
    machine.mem_store_byte(0x76C64, 0x61);
    machine.mem_store_byte(0x3F15C, 0xBB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0F35);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
}

//
// or ch, byte [ss:F29Ah]
//
TEST_F(MachineTest, or_ch_byte_ss_F29Ah)
{
    // Initial CPU State
    cpu.set_ax(0x86FA);
    cpu.set_bx(0xCADB);
    cpu.set_cx(0xF602);
    cpu.set_dx(0x176F);
    cpu.set_cs(0xCA8E);
    cpu.set_ss(0x5CAC);
    cpu.set_ds(0x009A);
    cpu.set_es(0x2C26);
    cpu.set_sp(0x9FAD);
    cpu.set_bp(0x64D2);
    cpu.set_si(0x6E77);
    cpu.set_di(0x5DF8);
    cpu.set_ip(0x3EEA);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCE7CA, 0x36);
    machine.mem_store_byte(0xCE7CB, 0x0A);
    machine.mem_store_byte(0xCE7CC, 0x2E);
    machine.mem_store_byte(0xCE7CD, 0x9A);
    machine.mem_store_byte(0xCE7CE, 0xF2);
    machine.mem_store_byte(0x6BD5A, 0xAD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xFF02);
    EXPECT_EQ(cpu.get_ip(), 0x3EEF);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
}

//
// or si, ax
//
TEST_F(MachineTest, or_si_ax)
{
    // Initial CPU State
    cpu.set_ax(0x1096);
    cpu.set_bx(0x96CC);
    cpu.set_cx(0xE564);
    cpu.set_dx(0x0D03);
    cpu.set_cs(0xF380);
    cpu.set_ss(0x230A);
    cpu.set_ds(0x1C7B);
    cpu.set_es(0xF82F);
    cpu.set_sp(0xA925);
    cpu.set_bp(0x35AD);
    cpu.set_si(0xEAF1);
    cpu.set_di(0xD515);
    cpu.set_ip(0x4C77);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8477, 0x3E);
    machine.mem_store_byte(0xF8478, 0x09);
    machine.mem_store_byte(0xF8479, 0xC6);
    machine.mem_store_byte(0xF847A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0xFAF7);
    EXPECT_EQ(cpu.get_ip(), 0x4C7A);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
}

//
// or sp, di
//
TEST_F(MachineTest, or_sp_di)
{
    // Initial CPU State
    cpu.set_ax(0xAD7C);
    cpu.set_bx(0x6C11);
    cpu.set_cx(0x088C);
    cpu.set_dx(0x3275);
    cpu.set_cs(0xE906);
    cpu.set_ss(0x313F);
    cpu.set_ds(0x13CC);
    cpu.set_es(0x668B);
    cpu.set_sp(0x988C);
    cpu.set_bp(0xB2E4);
    cpu.set_si(0xF749);
    cpu.set_di(0x1F2F);
    cpu.set_ip(0x16BC);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEA71C, 0x36);
    machine.mem_store_byte(0xEA71D, 0x0B);
    machine.mem_store_byte(0xEA71E, 0xE7);
    machine.mem_store_byte(0xEA71F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x9FAF);
    EXPECT_EQ(cpu.get_ip(), 0x16BF);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// or word [ds:bx+si-2Fh], FFC7h
//
TEST_F(MachineTest, or_word_ds_bx_si_2Fh_FFC7h)
{
    // Initial CPU State
    cpu.set_ax(0xD59F);
    cpu.set_bx(0x6B6D);
    cpu.set_cx(0x369C);
    cpu.set_dx(0x09ED);
    cpu.set_cs(0xBF2B);
    cpu.set_ss(0x7EC3);
    cpu.set_ds(0x7EA6);
    cpu.set_es(0xB6EB);
    cpu.set_sp(0x83E7);
    cpu.set_bp(0x4657);
    cpu.set_si(0xEB32);
    cpu.set_di(0x8B87);
    cpu.set_ip(0xF313);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCE5C3, 0x83);
    machine.mem_store_byte(0xCE5C4, 0x48);
    machine.mem_store_byte(0xCE5C5, 0xD1);
    machine.mem_store_byte(0xCE5C6, 0xC7);
    machine.mem_store_byte(0x840D0, 0xFE);
    machine.mem_store_byte(0x840D1, 0x39);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF317);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x840D0), 0xFF);
    EXPECT_EQ(memory.load8(0x840D1), 0xFF);
}

//
// or word [ss:si], 4BE9h
//
TEST_F(MachineTest, or_word_ss_si_4BE9h)
{
    // Initial CPU State
    cpu.set_ax(0x6572);
    cpu.set_bx(0xA14C);
    cpu.set_cx(0x8D8C);
    cpu.set_dx(0x2D58);
    cpu.set_cs(0xF5C1);
    cpu.set_ss(0x6AC3);
    cpu.set_ds(0x5445);
    cpu.set_es(0x6408);
    cpu.set_sp(0xEE62);
    cpu.set_bp(0x3475);
    cpu.set_si(0x6376);
    cpu.set_di(0x9149);
    cpu.set_ip(0x078E);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF639E, 0x36);
    machine.mem_store_byte(0xF639F, 0x81);
    machine.mem_store_byte(0xF63A0, 0x0C);
    machine.mem_store_byte(0xF63A1, 0xE9);
    machine.mem_store_byte(0xF63A2, 0x4B);
    machine.mem_store_byte(0x70FA6, 0x3E);
    machine.mem_store_byte(0x70FA7, 0x27);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0793);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x70FA6), 0xFF);
    EXPECT_EQ(memory.load8(0x70FA7), 0x6F);
}

//
// xor ah, bh
//
TEST_F(MachineTest, xor_ah_bh)
{
    // Initial CPU State
    cpu.set_ax(0x8640);
    cpu.set_bx(0x28B1);
    cpu.set_cx(0xB57C);
    cpu.set_dx(0x6450);
    cpu.set_cs(0x888A);
    cpu.set_ss(0xE467);
    cpu.set_ds(0x3B1D);
    cpu.set_es(0x5DE6);
    cpu.set_sp(0xFD71);
    cpu.set_bp(0xFF69);
    cpu.set_si(0x8EB7);
    cpu.set_di(0xC45F);
    cpu.set_ip(0x0778);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x89018, 0x26);
    machine.mem_store_byte(0x89019, 0x32);
    machine.mem_store_byte(0x8901A, 0xE7);
    machine.mem_store_byte(0x8901B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xAE40);
    EXPECT_EQ(cpu.get_ip(), 0x077B);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
}

//
// xor al, 43h
//
TEST_F(MachineTest, xor_al_43h)
{
    // Initial CPU State
    cpu.set_ax(0x702B);
    cpu.set_bx(0xC538);
    cpu.set_cx(0xC386);
    cpu.set_dx(0x600D);
    cpu.set_cs(0x0DA9);
    cpu.set_ss(0xF0B8);
    cpu.set_ds(0xCEE0);
    cpu.set_es(0x8E1A);
    cpu.set_sp(0x5B51);
    cpu.set_bp(0xA595);
    cpu.set_si(0x100B);
    cpu.set_di(0x1FD5);
    cpu.set_ip(0x6002);
    cpu.set_flags(0xF013);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x13A92, 0x34);
    machine.mem_store_byte(0x13A93, 0x43);
    machine.mem_store_byte(0x13A94, 0x90);
    machine.mem_store_byte(0x13A95, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7068);
    EXPECT_EQ(cpu.get_ip(), 0x6004);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
}

//
// xor ax, B82Dh
//
TEST_F(MachineTest, xor_ax_B82Dh)
{
    // Initial CPU State
    cpu.set_ax(0x05A7);
    cpu.set_bx(0x81F8);
    cpu.set_cx(0xA3B4);
    cpu.set_dx(0x1051);
    cpu.set_cs(0xD2EC);
    cpu.set_ss(0xA4F6);
    cpu.set_ds(0x0EB0);
    cpu.set_es(0xB852);
    cpu.set_sp(0xC35A);
    cpu.set_bp(0x7315);
    cpu.set_si(0x9D7C);
    cpu.set_di(0x3BE0);
    cpu.set_ip(0xAE5D);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDDD1D, 0x3E);
    machine.mem_store_byte(0xDDD1E, 0x35);
    machine.mem_store_byte(0xDDD1F, 0x2D);
    machine.mem_store_byte(0xDDD20, 0xB8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xBD8A);
    EXPECT_EQ(cpu.get_ip(), 0xAE61);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
}

//
// xor bp, sp
//
TEST_F(MachineTest, xor_bp_sp)
{
    // Initial CPU State
    cpu.set_ax(0x3698);
    cpu.set_bx(0xB820);
    cpu.set_cx(0xA642);
    cpu.set_dx(0xF243);
    cpu.set_cs(0x5C4C);
    cpu.set_ss(0x11E2);
    cpu.set_ds(0x0430);
    cpu.set_es(0x1EE2);
    cpu.set_sp(0x7B07);
    cpu.set_bp(0xEB13);
    cpu.set_si(0x97E2);
    cpu.set_di(0x8EF5);
    cpu.set_ip(0xC543);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x68A03, 0x36);
    machine.mem_store_byte(0x68A04, 0x31);
    machine.mem_store_byte(0x68A05, 0xE5);
    machine.mem_store_byte(0x68A06, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x9014);
    EXPECT_EQ(cpu.get_ip(), 0xC546);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// xor bx, word [cs:bp+7Dh]
//
TEST_F(MachineTest, xor_bx_word_cs_bp_7Dh)
{
    // Initial CPU State
    cpu.set_ax(0x7FD9);
    cpu.set_bx(0x3830);
    cpu.set_cx(0x2B72);
    cpu.set_dx(0x5A19);
    cpu.set_cs(0x71AC);
    cpu.set_ss(0xFD7A);
    cpu.set_ds(0x9D93);
    cpu.set_es(0x1D6D);
    cpu.set_sp(0xD7F6);
    cpu.set_bp(0x8178);
    cpu.set_si(0xCF64);
    cpu.set_di(0x4493);
    cpu.set_ip(0xEAC0);
    cpu.set_flags(0xF4D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x80580, 0x2E);
    machine.mem_store_byte(0x80581, 0x33);
    machine.mem_store_byte(0x80582, 0x5E);
    machine.mem_store_byte(0x80583, 0x7D);
    machine.mem_store_byte(0x79CB5, 0xFD);
    machine.mem_store_byte(0x79CB6, 0xE0);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xD8CD);
    EXPECT_EQ(cpu.get_ip(), 0xEAC4);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
}

//
// xor byte [ds:bx+di+76h], 84h
//
TEST_F(MachineTest, xor_byte_ds_bx_di_76h_84h)
{
    // Initial CPU State
    cpu.set_ax(0x0149);
    cpu.set_bx(0xF150);
    cpu.set_cx(0x0794);
    cpu.set_dx(0x2A18);
    cpu.set_cs(0xFCCA);
    cpu.set_ss(0xC82E);
    cpu.set_ds(0xF64C);
    cpu.set_es(0x8D8A);
    cpu.set_sp(0x96C1);
    cpu.set_bp(0x95B5);
    cpu.set_si(0x3DB2);
    cpu.set_di(0x703C);
    cpu.set_ip(0x5CB9);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02959, 0x82);
    machine.mem_store_byte(0x0295A, 0x71);
    machine.mem_store_byte(0x0295B, 0x76);
    machine.mem_store_byte(0x0295C, 0x84);
    machine.mem_store_byte(0xFC6C2, 0x6E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5CBD);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFC6C2), 0xEA);
}

//
// xor byte [ds:bx], dl
//
TEST_F(MachineTest, xor_byte_ds_bx_dl)
{
    // Initial CPU State
    cpu.set_ax(0xF8DF);
    cpu.set_bx(0x596A);
    cpu.set_cx(0x3E48);
    cpu.set_dx(0x5EED);
    cpu.set_cs(0x22E6);
    cpu.set_ss(0x523F);
    cpu.set_ds(0x37C2);
    cpu.set_es(0xBEAE);
    cpu.set_sp(0x0721);
    cpu.set_bp(0xD6D7);
    cpu.set_si(0xB320);
    cpu.set_di(0xF25E);
    cpu.set_ip(0x0582);
    cpu.set_flags(0xF486);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x233E2, 0x30);
    machine.mem_store_byte(0x233E3, 0x17);
    machine.mem_store_byte(0x233E4, 0x90);
    machine.mem_store_byte(0x233E5, 0x90);
    machine.mem_store_byte(0x3D58A, 0xDB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0584);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3D58A), 0x36);
}

//
// xor dl, 9Dh
//
TEST_F(MachineTest, xor_dl_9Dh)
{
    // Initial CPU State
    cpu.set_ax(0x2041);
    cpu.set_bx(0x70F6);
    cpu.set_cx(0x08B0);
    cpu.set_dx(0x36C0);
    cpu.set_cs(0xB714);
    cpu.set_ss(0x5EEE);
    cpu.set_ds(0x6A15);
    cpu.set_es(0xD040);
    cpu.set_sp(0xD83A);
    cpu.set_bp(0x5856);
    cpu.set_si(0x3206);
    cpu.set_di(0xA961);
    cpu.set_ip(0x4B71);
    cpu.set_flags(0xF0D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBBCB1, 0x80);
    machine.mem_store_byte(0xBBCB2, 0xF2);
    machine.mem_store_byte(0xBBCB3, 0x9D);
    machine.mem_store_byte(0xBBCB4, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x365D);
    EXPECT_EQ(cpu.get_ip(), 0x4B74);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
}

//
// xor word [cs:bp+di+3Bh], 24h
//
TEST_F(MachineTest, xor_word_cs_bp_di_3Bh_24h)
{
    // Initial CPU State
    cpu.set_ax(0x91A6);
    cpu.set_bx(0x1C50);
    cpu.set_cx(0xECF0);
    cpu.set_dx(0x3C78);
    cpu.set_cs(0x89DE);
    cpu.set_ss(0x0110);
    cpu.set_ds(0xB652);
    cpu.set_es(0xDAF8);
    cpu.set_sp(0x0C57);
    cpu.set_bp(0x8404);
    cpu.set_si(0x47ED);
    cpu.set_di(0x626A);
    cpu.set_ip(0x4C4E);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8EA2E, 0x2E);
    machine.mem_store_byte(0x8EA2F, 0x83);
    machine.mem_store_byte(0x8EA30, 0x73);
    machine.mem_store_byte(0x8EA31, 0x3B);
    machine.mem_store_byte(0x8EA32, 0x24);
    machine.mem_store_byte(0x98489, 0x52);
    machine.mem_store_byte(0x9848A, 0xF8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4C53);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x98489), 0x76);
}

//
// xor word [ds:bx+70h], 5BAEh
//
TEST_F(MachineTest, xor_word_ds_bx_70h_5BAEh)
{
    // Initial CPU State
    cpu.set_ax(0x01E5);
    cpu.set_bx(0x3DE9);
    cpu.set_cx(0xF812);
    cpu.set_dx(0x48D4);
    cpu.set_cs(0x3DF5);
    cpu.set_ss(0x6BDA);
    cpu.set_ds(0x5DB7);
    cpu.set_es(0xA80B);
    cpu.set_sp(0xDD4F);
    cpu.set_bp(0x943F);
    cpu.set_si(0xABB2);
    cpu.set_di(0x76C0);
    cpu.set_ip(0x5172);
    cpu.set_flags(0xF413);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x430C2, 0x81);
    machine.mem_store_byte(0x430C3, 0x77);
    machine.mem_store_byte(0x430C4, 0x70);
    machine.mem_store_byte(0x430C5, 0xAE);
    machine.mem_store_byte(0x430C6, 0x5B);
    machine.mem_store_byte(0x619C9, 0xB2);
    machine.mem_store_byte(0x619CA, 0x3C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5177);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x619C9), 0x1C);
    EXPECT_EQ(memory.load8(0x619CA), 0x67);
}
