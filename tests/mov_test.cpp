#include "fixture.h"

//
// mov ah, 2Dh
//
TEST_F(MachineTest, mov_ah_2Dh)
{
    // Initial CPU State
    cpu.set_ax(0xBE84);
    cpu.set_bx(0xACEF);
    cpu.set_cx(0x1296);
    cpu.set_dx(0x9A86);
    cpu.set_cs(0x76AB);
    cpu.set_ss(0xCBB3);
    cpu.set_ds(0x2445);
    cpu.set_es(0x02C4);
    cpu.set_sp(0xE67D);
    cpu.set_bp(0x1B2A);
    cpu.set_si(0x9BCA);
    cpu.set_di(0xFA0A);
    cpu.set_ip(0x01C8);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x76C78, 0xB4);
    machine.mem_store_byte(0x76C79, 0x2D);
    machine.mem_store_byte(0x76C7A, 0x90);
    machine.mem_store_byte(0x76C7B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2D84);
    EXPECT_EQ(cpu.get_ip(), 0x01CA);

    // Final RAM entries
}

//
// mov al, 4Bh
//
TEST_F(MachineTest, mov_al_4Bh)
{
    // Initial CPU State
    cpu.set_ax(0x52A1);
    cpu.set_bx(0xE724);
    cpu.set_cx(0x81C8);
    cpu.set_dx(0xF0F7);
    cpu.set_cs(0x31ED);
    cpu.set_ss(0x1D03);
    cpu.set_ds(0x0258);
    cpu.set_es(0xCCC3);
    cpu.set_sp(0xBF76);
    cpu.set_bp(0x2608);
    cpu.set_si(0xCB21);
    cpu.set_di(0x2729);
    cpu.set_ip(0x02B6);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x32186, 0xB0);
    machine.mem_store_byte(0x32187, 0x4B);
    machine.mem_store_byte(0x32188, 0x90);
    machine.mem_store_byte(0x32189, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x524B);
    EXPECT_EQ(cpu.get_ip(), 0x02B8);

    // Final RAM entries
}

//
// mov al, byte [ds:7156h]
//
TEST_F(MachineTest, mov_al_byte_ds_7156h)
{
    // Initial CPU State
    cpu.set_ax(0x5153);
    cpu.set_bx(0xBD8C);
    cpu.set_cx(0xFF62);
    cpu.set_dx(0x92DD);
    cpu.set_cs(0x2148);
    cpu.set_ss(0xAD24);
    cpu.set_ds(0xC064);
    cpu.set_es(0x1944);
    cpu.set_sp(0x741E);
    cpu.set_bp(0xFF7A);
    cpu.set_si(0x0D89);
    cpu.set_di(0x3AFE);
    cpu.set_ip(0xE6BB);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2FB3B, 0x3E);
    machine.mem_store_byte(0x2FB3C, 0xA0);
    machine.mem_store_byte(0x2FB3D, 0x56);
    machine.mem_store_byte(0x2FB3E, 0x71);
    machine.mem_store_byte(0xC7796, 0xE8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x51E8);
    EXPECT_EQ(cpu.get_ip(), 0xE6BF);

    // Final RAM entries
}

//
// mov ax, 9AAAh
//
TEST_F(MachineTest, mov_ax_9AAAh)
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
    machine.mem_store_byte(0x76C61, 0xB8);
    machine.mem_store_byte(0x76C62, 0xAA);
    machine.mem_store_byte(0x76C63, 0x9A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9AAA);
    EXPECT_EQ(cpu.get_ip(), 0x0F34);

    // Final RAM entries
}

//
// mov ax, word [ds:D5B8h]
//
TEST_F(MachineTest, mov_ax_word_ds_D5B8h)
{
    // Initial CPU State
    cpu.set_ax(0x6237);
    cpu.set_bx(0xE53A);
    cpu.set_cx(0xFA32);
    cpu.set_dx(0x0FC8);
    cpu.set_cs(0x0BBE);
    cpu.set_ss(0x2143);
    cpu.set_ds(0x496D);
    cpu.set_es(0xC311);
    cpu.set_sp(0x4016);
    cpu.set_bp(0x3810);
    cpu.set_si(0x8763);
    cpu.set_di(0xFE8E);
    cpu.set_ip(0x7771);
    cpu.set_flags(0xFC17);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x13351, 0x3E);
    machine.mem_store_byte(0x13352, 0xA1);
    machine.mem_store_byte(0x13353, 0xB8);
    machine.mem_store_byte(0x13354, 0xD5);
    machine.mem_store_byte(0x56C88, 0x18);
    machine.mem_store_byte(0x56C89, 0xED);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xED18);
    EXPECT_EQ(cpu.get_ip(), 0x7775);

    // Final RAM entries
}

//
// mov bh, FDh
//
TEST_F(MachineTest, mov_bh_FDh)
{
    // Initial CPU State
    cpu.set_ax(0xB80E);
    cpu.set_bx(0xFDB5);
    cpu.set_cx(0x33EE);
    cpu.set_dx(0xE214);
    cpu.set_cs(0x7BD3);
    cpu.set_ss(0x42ED);
    cpu.set_ds(0xFE59);
    cpu.set_es(0xB313);
    cpu.set_sp(0xFF22);
    cpu.set_bp(0x7033);
    cpu.set_si(0xE35E);
    cpu.set_di(0x4592);
    cpu.set_ip(0xDCD0);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x89A00, 0x36);
    machine.mem_store_byte(0x89A01, 0xB7);
    machine.mem_store_byte(0x89A02, 0xFD);
    machine.mem_store_byte(0x89A03, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDCD3);

    // Final RAM entries
}

//
// mov bl, 91h
//
TEST_F(MachineTest, mov_bl_91h)
{
    // Initial CPU State
    cpu.set_ax(0x5EE5);
    cpu.set_bx(0x7DAD);
    cpu.set_cx(0x5500);
    cpu.set_dx(0xBDEF);
    cpu.set_cs(0xE827);
    cpu.set_ss(0x33BD);
    cpu.set_ds(0x4C52);
    cpu.set_es(0x1809);
    cpu.set_sp(0x978F);
    cpu.set_bp(0xB925);
    cpu.set_si(0xE87B);
    cpu.set_di(0xCFA4);
    cpu.set_ip(0x331F);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEB58F, 0xB3);
    machine.mem_store_byte(0xEB590, 0x91);
    machine.mem_store_byte(0xEB591, 0x90);
    machine.mem_store_byte(0xEB592, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x7D91);
    EXPECT_EQ(cpu.get_ip(), 0x3321);

    // Final RAM entries
}

//
// mov bp, 1559h
//
TEST_F(MachineTest, mov_bp_1559h)
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
    machine.mem_store_byte(0x9222D, 0xBD);
    machine.mem_store_byte(0x9222E, 0x59);
    machine.mem_store_byte(0x9222F, 0x15);
    machine.mem_store_byte(0x92230, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x1559);
    EXPECT_EQ(cpu.get_ip(), 0x87F0);

    // Final RAM entries
}

//
// mov bx, 12E7h
//
TEST_F(MachineTest, mov_bx_12E7h)
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
    machine.mem_store_byte(0xEA71D, 0xBB);
    machine.mem_store_byte(0xEA71E, 0xE7);
    machine.mem_store_byte(0xEA71F, 0x12);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x12E7);
    EXPECT_EQ(cpu.get_ip(), 0x16C0);

    // Final RAM entries
}

//
// mov byte [cs:B3FCh], al
//
TEST_F(MachineTest, mov_byte_cs_B3FCh_al)
{
    // Initial CPU State
    cpu.set_ax(0x6E1E);
    cpu.set_bx(0x5A75);
    cpu.set_cx(0xEB68);
    cpu.set_dx(0xD93A);
    cpu.set_cs(0xC222);
    cpu.set_ss(0xDA70);
    cpu.set_ds(0xAA78);
    cpu.set_es(0x7438);
    cpu.set_sp(0xCB62);
    cpu.set_bp(0x717F);
    cpu.set_si(0x8861);
    cpu.set_di(0x15C5);
    cpu.set_ip(0x5DC2);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC7FE2, 0x2E);
    machine.mem_store_byte(0xC7FE3, 0xA2);
    machine.mem_store_byte(0xC7FE4, 0xFC);
    machine.mem_store_byte(0xC7FE5, 0xB3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5DC6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCD61C), 0x1E);
}

//
// mov byte [ss:bp+di], 15h
//
TEST_F(MachineTest, mov_byte_ss_bp_di_15h)
{
    // Initial CPU State
    cpu.set_ax(0x9FA5);
    cpu.set_bx(0x73A2);
    cpu.set_cx(0xC398);
    cpu.set_dx(0xCC50);
    cpu.set_cs(0x6C00);
    cpu.set_ss(0x21E6);
    cpu.set_ds(0x65FF);
    cpu.set_es(0xE9AC);
    cpu.set_sp(0xABDE);
    cpu.set_bp(0x29E4);
    cpu.set_si(0xC541);
    cpu.set_di(0x43F3);
    cpu.set_ip(0x1767);
    cpu.set_flags(0xF406);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6D767, 0xC6);
    machine.mem_store_byte(0x6D768, 0x03);
    machine.mem_store_byte(0x6D769, 0x15);
    machine.mem_store_byte(0x6D76A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x176A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x28C37), 0x15);
}

//
// mov ch, EFh
//
TEST_F(MachineTest, mov_ch_EFh)
{
    // Initial CPU State
    cpu.set_ax(0x5165);
    cpu.set_bx(0xE748);
    cpu.set_cx(0x13C4);
    cpu.set_dx(0xDDE0);
    cpu.set_cs(0x618C);
    cpu.set_ss(0x3D1E);
    cpu.set_ds(0x6E09);
    cpu.set_es(0x04E7);
    cpu.set_sp(0xF958);
    cpu.set_bp(0xD5E6);
    cpu.set_si(0xD4A8);
    cpu.set_di(0xD855);
    cpu.set_ip(0xBD15);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6D5D5, 0xB5);
    machine.mem_store_byte(0x6D5D6, 0xEF);
    machine.mem_store_byte(0x6D5D7, 0x90);
    machine.mem_store_byte(0x6D5D8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xEFC4);
    EXPECT_EQ(cpu.get_ip(), 0xBD17);

    // Final RAM entries
}

//
// mov cl, E2h
//
TEST_F(MachineTest, mov_cl_E2h)
{
    // Initial CPU State
    cpu.set_ax(0x634C);
    cpu.set_bx(0xD4B7);
    cpu.set_cx(0x3A92);
    cpu.set_dx(0x9001);
    cpu.set_cs(0xA070);
    cpu.set_ss(0xFBF1);
    cpu.set_ds(0xBD4A);
    cpu.set_es(0xA238);
    cpu.set_sp(0xE657);
    cpu.set_bp(0xA49C);
    cpu.set_si(0x9BC4);
    cpu.set_di(0xB7E7);
    cpu.set_ip(0x94E2);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA9BE2, 0xB1);
    machine.mem_store_byte(0xA9BE3, 0xE2);
    machine.mem_store_byte(0xA9BE4, 0x90);
    machine.mem_store_byte(0xA9BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x3AE2);
    EXPECT_EQ(cpu.get_ip(), 0x94E4);

    // Final RAM entries
}

//
// mov cl, byte [ss:bp+di-64h]
//
TEST_F(MachineTest, mov_cl_byte_ss_bp_di_64h)
{
    // Initial CPU State
    cpu.set_ax(0x52A1);
    cpu.set_bx(0xE724);
    cpu.set_cx(0x81C8);
    cpu.set_dx(0xF0F7);
    cpu.set_cs(0x31ED);
    cpu.set_ss(0x1D03);
    cpu.set_ds(0x0258);
    cpu.set_es(0xCCC3);
    cpu.set_sp(0xBF76);
    cpu.set_bp(0x2608);
    cpu.set_si(0xCB21);
    cpu.set_di(0x2729);
    cpu.set_ip(0x02B6);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x32186, 0x8A);
    machine.mem_store_byte(0x32187, 0x4B);
    machine.mem_store_byte(0x32188, 0x9C);
    machine.mem_store_byte(0x32189, 0x90);
    machine.mem_store_byte(0x21CFD, 0x14);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x8114);
    EXPECT_EQ(cpu.get_ip(), 0x02B9);

    // Final RAM entries
}

//
// mov cx, 9BC6h
//
TEST_F(MachineTest, mov_cx_9BC6h)
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
    machine.mem_store_byte(0xF8478, 0xB9);
    machine.mem_store_byte(0xF8479, 0xC6);
    machine.mem_store_byte(0xF847A, 0x9B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x9BC6);
    EXPECT_EQ(cpu.get_ip(), 0x4C7B);

    // Final RAM entries
}

//
// mov dh, Bh
//
TEST_F(MachineTest, mov_dh_Bh)
{
    // Initial CPU State
    cpu.set_ax(0xB20F);
    cpu.set_bx(0x9004);
    cpu.set_cx(0xF438);
    cpu.set_dx(0x110B);
    cpu.set_cs(0xB5B6);
    cpu.set_ss(0x6ADD);
    cpu.set_ds(0xC31E);
    cpu.set_es(0xC1E4);
    cpu.set_sp(0x08FD);
    cpu.set_bp(0xB363);
    cpu.set_si(0x4C83);
    cpu.set_di(0xF915);
    cpu.set_ip(0xCF28);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC2A88, 0x3E);
    machine.mem_store_byte(0xC2A89, 0xB6);
    machine.mem_store_byte(0xC2A8A, 0x0B);
    machine.mem_store_byte(0xC2A8B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0B0B);
    EXPECT_EQ(cpu.get_ip(), 0xCF2B);

    // Final RAM entries
}

//
// mov dh, dh
//
TEST_F(MachineTest, mov_dh_dh)
{
    // Initial CPU State
    cpu.set_ax(0xA46B);
    cpu.set_bx(0x9D00);
    cpu.set_cx(0x758A);
    cpu.set_dx(0x7154);
    cpu.set_cs(0x7A07);
    cpu.set_ss(0xCD04);
    cpu.set_ds(0xCE8F);
    cpu.set_es(0x815D);
    cpu.set_sp(0x1FE8);
    cpu.set_bp(0xE950);
    cpu.set_si(0x291F);
    cpu.set_di(0x503B);
    cpu.set_ip(0x32BE);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7D32E, 0x2E);
    machine.mem_store_byte(0x7D32F, 0x88);
    machine.mem_store_byte(0x7D330, 0xF6);
    machine.mem_store_byte(0x7D331, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x32C1);

    // Final RAM entries
}

//
// mov di, 2B8Dh
//
TEST_F(MachineTest, mov_di_2B8Dh)
{
    // Initial CPU State
    cpu.set_ax(0x846C);
    cpu.set_bx(0x0302);
    cpu.set_cx(0xEC3A);
    cpu.set_dx(0xD57F);
    cpu.set_cs(0x3134);
    cpu.set_ss(0x20B4);
    cpu.set_ds(0x15F0);
    cpu.set_es(0x793F);
    cpu.set_sp(0xC331);
    cpu.set_bp(0xDD80);
    cpu.set_si(0x87EA);
    cpu.set_di(0x70FC);
    cpu.set_ip(0xB3F7);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3C737, 0xBF);
    machine.mem_store_byte(0x3C738, 0x8D);
    machine.mem_store_byte(0x3C739, 0x2B);
    machine.mem_store_byte(0x3C73A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x2B8D);
    EXPECT_EQ(cpu.get_ip(), 0xB3FA);

    // Final RAM entries
}

//
// mov dl, Fh
//
TEST_F(MachineTest, mov_dl_Fh)
{
    // Initial CPU State
    cpu.set_ax(0x4568);
    cpu.set_bx(0xCEEC);
    cpu.set_cx(0x6D72);
    cpu.set_dx(0xD1B6);
    cpu.set_cs(0x3CFE);
    cpu.set_ss(0x74B5);
    cpu.set_ds(0x0894);
    cpu.set_es(0xD1F6);
    cpu.set_sp(0x60D6);
    cpu.set_bp(0x6EDE);
    cpu.set_si(0x6A6B);
    cpu.set_di(0x1F09);
    cpu.set_ip(0x283B);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3F81B, 0x36);
    machine.mem_store_byte(0x3F81C, 0xB2);
    machine.mem_store_byte(0x3F81D, 0x0F);
    machine.mem_store_byte(0x3F81E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xD10F);
    EXPECT_EQ(cpu.get_ip(), 0x283E);

    // Final RAM entries
}

//
// mov dx, 9A2Eh
//
TEST_F(MachineTest, mov_dx_9A2Eh)
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
    machine.mem_store_byte(0xCE7CB, 0xBA);
    machine.mem_store_byte(0xCE7CC, 0x2E);
    machine.mem_store_byte(0xCE7CD, 0x9A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x9A2E);
    EXPECT_EQ(cpu.get_ip(), 0x3EEE);

    // Final RAM entries
}

//
// mov si, DC7Eh
//
TEST_F(MachineTest, mov_si_DC7Eh)
{
    // Initial CPU State
    cpu.set_ax(0x2275);
    cpu.set_bx(0x79AA);
    cpu.set_cx(0x1CF6);
    cpu.set_dx(0x99B0);
    cpu.set_cs(0xC6D7);
    cpu.set_ss(0x3DE0);
    cpu.set_ds(0x9691);
    cpu.set_es(0xB2E3);
    cpu.set_sp(0x0A19);
    cpu.set_bp(0xCECF);
    cpu.set_si(0x395F);
    cpu.set_di(0x386D);
    cpu.set_ip(0x4E40);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCBBB0, 0xBE);
    machine.mem_store_byte(0xCBBB1, 0x7E);
    machine.mem_store_byte(0xCBBB2, 0xDC);
    machine.mem_store_byte(0xCBBB3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0xDC7E);
    EXPECT_EQ(cpu.get_ip(), 0x4E43);

    // Final RAM entries
}

//
// mov sp, 5444h
//
TEST_F(MachineTest, mov_sp_5444h)
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
    machine.mem_store_byte(0x97070, 0xBC);
    machine.mem_store_byte(0x97071, 0x44);
    machine.mem_store_byte(0x97072, 0x54);
    machine.mem_store_byte(0x97073, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x5444);
    EXPECT_EQ(cpu.get_ip(), 0xCBE3);

    // Final RAM entries
}

//
// mov sp, dx
//
TEST_F(MachineTest, mov_sp_dx)
{
    // Initial CPU State
    cpu.set_ax(0x634C);
    cpu.set_bx(0xD4B7);
    cpu.set_cx(0x3A92);
    cpu.set_dx(0x9001);
    cpu.set_cs(0xA070);
    cpu.set_ss(0xFBF1);
    cpu.set_ds(0xBD4A);
    cpu.set_es(0xA238);
    cpu.set_sp(0xE657);
    cpu.set_bp(0xA49C);
    cpu.set_si(0x9BC4);
    cpu.set_di(0xB7E7);
    cpu.set_ip(0x94E2);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA9BE2, 0x8B);
    machine.mem_store_byte(0xA9BE3, 0xE2);
    machine.mem_store_byte(0xA9BE4, 0x90);
    machine.mem_store_byte(0xA9BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x9001);
    EXPECT_EQ(cpu.get_ip(), 0x94E4);

    // Final RAM entries
}

//
// mov ss, word [es:bx+si-6h]
//
TEST_F(MachineTest, mov_ss_word_es_bx_si_6h)
{
    // Initial CPU State
    cpu.set_ax(0x52A1);
    cpu.set_bx(0xE724);
    cpu.set_cx(0x81C8);
    cpu.set_dx(0xF0F7);
    cpu.set_cs(0x31ED);
    cpu.set_ss(0x1D03);
    cpu.set_ds(0x0258);
    cpu.set_es(0xCCC3);
    cpu.set_sp(0xBF76);
    cpu.set_bp(0x2608);
    cpu.set_si(0xCB21);
    cpu.set_di(0x2729);
    cpu.set_ip(0x02B6);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x32186, 0x26);
    machine.mem_store_byte(0x32187, 0x8E);
    machine.mem_store_byte(0x32188, 0x50);
    machine.mem_store_byte(0x32189, 0xFA);
    machine.mem_store_byte(0xD7E6F, 0x47);
    machine.mem_store_byte(0xD7E70, 0x74);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ss(), 0x7447);
    EXPECT_EQ(cpu.get_ip(), 0x02BA);

    // Final RAM entries
}

//
// mov word [ds:D4Ah], ax
//
TEST_F(MachineTest, mov_word_ds_D4Ah_ax)
{
    // Initial CPU State
    cpu.set_ax(0x83E9);
    cpu.set_bx(0x2176);
    cpu.set_cx(0x0D1C);
    cpu.set_dx(0xB41E);
    cpu.set_cs(0x0710);
    cpu.set_ss(0xD332);
    cpu.set_ds(0xC70B);
    cpu.set_es(0x36A3);
    cpu.set_sp(0xB868);
    cpu.set_bp(0xDBF8);
    cpu.set_si(0xA311);
    cpu.set_di(0x04C9);
    cpu.set_ip(0x26B2);
    cpu.set_flags(0xF046);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x097B2, 0xA3);
    machine.mem_store_byte(0x097B3, 0x4A);
    machine.mem_store_byte(0x097B4, 0x0D);
    machine.mem_store_byte(0x097B5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x26B5);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC7DFA), 0xE9);
    EXPECT_EQ(memory.load8(0xC7DFB), 0x83);
}

//
// mov word [es:si], B938h
//
TEST_F(MachineTest, mov_word_es_si_B938h)
{
    // Initial CPU State
    cpu.set_ax(0x2410);
    cpu.set_bx(0xF0F1);
    cpu.set_cx(0x09CC);
    cpu.set_dx(0x0CBB);
    cpu.set_cs(0x5FDE);
    cpu.set_ss(0xF27E);
    cpu.set_ds(0x86B4);
    cpu.set_es(0xB7B4);
    cpu.set_sp(0x979A);
    cpu.set_bp(0xE376);
    cpu.set_si(0x688E);
    cpu.set_di(0xDA5F);
    cpu.set_ip(0x4385);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x64165, 0x26);
    machine.mem_store_byte(0x64166, 0xC7);
    machine.mem_store_byte(0x64167, 0x34);
    machine.mem_store_byte(0x64168, 0x38);
    machine.mem_store_byte(0x64169, 0xB9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x438A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBE3CE), 0x38);
    EXPECT_EQ(memory.load8(0xBE3CF), 0xB9);
}

//
// mov word [ss:bp+si+47B5h], dx
//
TEST_F(MachineTest, mov_word_ss_bp_si_47B5h_dx)
{
    // Initial CPU State
    cpu.set_ax(0x9E3C);
    cpu.set_bx(0x74EB);
    cpu.set_cx(0x4CBC);
    cpu.set_dx(0xF13F);
    cpu.set_cs(0x4E32);
    cpu.set_ss(0x1BF2);
    cpu.set_ds(0xBBE8);
    cpu.set_es(0x6D2C);
    cpu.set_sp(0x9D7E);
    cpu.set_bp(0x611D);
    cpu.set_si(0x4432);
    cpu.set_di(0x784B);
    cpu.set_ip(0x4595);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x528B5, 0x36);
    machine.mem_store_byte(0x528B6, 0x89);
    machine.mem_store_byte(0x528B7, 0x92);
    machine.mem_store_byte(0x528B8, 0xB5);
    machine.mem_store_byte(0x528B9, 0x47);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x459A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2AC24), 0x3F);
    EXPECT_EQ(memory.load8(0x2AC25), 0xF1);
}

//
// mov word [ss:bx], cs
//
TEST_F(MachineTest, mov_word_ss_bx_cs)
{
    // Initial CPU State
    cpu.set_ax(0x4568);
    cpu.set_bx(0xCEEC);
    cpu.set_cx(0x6D72);
    cpu.set_dx(0xD1B6);
    cpu.set_cs(0x3CFE);
    cpu.set_ss(0x74B5);
    cpu.set_ds(0x0894);
    cpu.set_es(0xD1F6);
    cpu.set_sp(0x60D6);
    cpu.set_bp(0x6EDE);
    cpu.set_si(0x6A6B);
    cpu.set_di(0x1F09);
    cpu.set_ip(0x283B);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3F81B, 0x36);
    machine.mem_store_byte(0x3F81C, 0x8C);
    machine.mem_store_byte(0x3F81D, 0x0F);
    machine.mem_store_byte(0x3F81E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x283E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x81A3C), 0xFE);
    EXPECT_EQ(memory.load8(0x81A3D), 0x3C);
}
