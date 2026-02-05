#include "fixture.h"

//
// adc al, ABh
//
TEST_F(MachineTest, adc_al_ABh)
{
    // Initial CPU State
    cpu.set_ax(0xB861);
    cpu.set_bx(0xB3E9);
    cpu.set_cx(0x825A);
    cpu.set_dx(0x19EE);
    cpu.set_cs(0x5F51);
    cpu.set_ss(0xD1DB);
    cpu.set_ds(0x4E80);
    cpu.set_es(0x35F6);
    cpu.set_sp(0xDCE8);
    cpu.set_bp(0x5019);
    cpu.set_si(0xAC88);
    cpu.set_di(0xCF60);
    cpu.set_ip(0x0D96);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x602A6, 0x14);
    machine.mem_store_byte(0x602A7, 0xAB);
    machine.mem_store_byte(0x602A8, 0x90);
    machine.mem_store_byte(0x602A9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xB80D);
    EXPECT_EQ(cpu.get_ip(), 0x0D98);
    EXPECT_EQ(cpu.get_flags(), 0xF003);

    // Final RAM entries
}

//
// adc ax, 4D71h
//
TEST_F(MachineTest, adc_ax_4D71h)
{
    // Initial CPU State
    cpu.set_ax(0x7163);
    cpu.set_bx(0xADC4);
    cpu.set_cx(0xACA8);
    cpu.set_dx(0xDEF2);
    cpu.set_cs(0x9E2C);
    cpu.set_ss(0x2310);
    cpu.set_ds(0xE675);
    cpu.set_es(0x4AD9);
    cpu.set_sp(0x5F97);
    cpu.set_bp(0xBAA2);
    cpu.set_si(0x747D);
    cpu.set_di(0xE4CF);
    cpu.set_ip(0xE7BA);
    cpu.set_flags(0xF013);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xACA7A, 0x26);
    machine.mem_store_byte(0xACA7B, 0x15);
    machine.mem_store_byte(0xACA7C, 0x71);
    machine.mem_store_byte(0xACA7D, 0x4D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xBED5);
    EXPECT_EQ(cpu.get_ip(), 0xE7BE);
    EXPECT_EQ(cpu.get_flags(), 0xF882);

    // Final RAM entries
}

//
// adc ax, word [ds:di-60h]
//
TEST_F(MachineTest, adc_ax_word_ds_di_60h)
{
    // Initial CPU State
    cpu.set_ax(0x8DB5);
    cpu.set_bx(0xDDC1);
    cpu.set_cx(0x495C);
    cpu.set_dx(0xA570);
    cpu.set_cs(0xE8AA);
    cpu.set_ss(0x3666);
    cpu.set_ds(0xACE9);
    cpu.set_es(0x017C);
    cpu.set_sp(0x9468);
    cpu.set_bp(0xDE03);
    cpu.set_si(0x3DE9);
    cpu.set_di(0x5EDD);
    cpu.set_ip(0x61F8);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEEC98, 0x13);
    machine.mem_store_byte(0xEEC99, 0x45);
    machine.mem_store_byte(0xEEC9A, 0xA0);
    machine.mem_store_byte(0xEEC9B, 0x90);
    machine.mem_store_byte(0xB2D0D, 0x39);
    machine.mem_store_byte(0xB2D0E, 0x1B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xA8EF);
    EXPECT_EQ(cpu.get_ip(), 0x61FB);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
}

//
// adc byte [ds:di+342Bh], cl
//
TEST_F(MachineTest, adc_byte_ds_di_342Bh_cl)
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
    machine.mem_store_byte(0x3C737, 0x10);
    machine.mem_store_byte(0x3C738, 0x8D);
    machine.mem_store_byte(0x3C739, 0x2B);
    machine.mem_store_byte(0x3C73A, 0x34);
    machine.mem_store_byte(0x20427, 0x58);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB3FB);
    EXPECT_EQ(cpu.get_flags(), 0xFC92);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x20427), 0x92);
}

//
// adc byte [ds:si], 1h
//
TEST_F(MachineTest, adc_byte_ds_si_1h)
{
    // Initial CPU State
    cpu.set_ax(0x5992);
    cpu.set_bx(0xD772);
    cpu.set_cx(0xA820);
    cpu.set_dx(0x1F66);
    cpu.set_cs(0x5D3E);
    cpu.set_ss(0xA042);
    cpu.set_ds(0x3308);
    cpu.set_es(0x3C20);
    cpu.set_sp(0x7A26);
    cpu.set_bp(0x0493);
    cpu.set_si(0xF979);
    cpu.set_di(0xE72F);
    cpu.set_ip(0x88C3);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x65CA3, 0x82);
    machine.mem_store_byte(0x65CA4, 0x14);
    machine.mem_store_byte(0x65CA5, 0x01);
    machine.mem_store_byte(0x65CA6, 0x90);
    machine.mem_store_byte(0x429F9, 0x1B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x88C6);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x429F9), 0x1C);
}

//
// adc ch, AAh
//
TEST_F(MachineTest, adc_ch_AAh)
{
    // Initial CPU State
    cpu.set_ax(0x1DD1);
    cpu.set_bx(0xEE8D);
    cpu.set_cx(0x920A);
    cpu.set_dx(0x9342);
    cpu.set_cs(0x4574);
    cpu.set_ss(0xE421);
    cpu.set_ds(0x7065);
    cpu.set_es(0xBDE0);
    cpu.set_sp(0x7C45);
    cpu.set_bp(0x15B6);
    cpu.set_si(0x24A4);
    cpu.set_di(0x650B);
    cpu.set_ip(0xC1E8);
    cpu.set_flags(0xF4C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x51928, 0x36);
    machine.mem_store_byte(0x51929, 0x80);
    machine.mem_store_byte(0x5192A, 0xD5);
    machine.mem_store_byte(0x5192B, 0xAA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x3C0A);
    EXPECT_EQ(cpu.get_ip(), 0xC1EC);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
}

//
// adc cl, byte [es:di-2008h]
//
TEST_F(MachineTest, adc_cl_byte_es_di_2008h)
{
    // Initial CPU State
    cpu.set_ax(0x830B);
    cpu.set_bx(0x4F53);
    cpu.set_cx(0x93C4);
    cpu.set_dx(0x3AEB);
    cpu.set_cs(0x97E7);
    cpu.set_ss(0xE621);
    cpu.set_ds(0x8ED9);
    cpu.set_es(0x99CC);
    cpu.set_sp(0xD373);
    cpu.set_bp(0x4A31);
    cpu.set_si(0x31BA);
    cpu.set_di(0xF413);
    cpu.set_ip(0xBEC3);
    cpu.set_flags(0xF056);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA3D33, 0x26);
    machine.mem_store_byte(0xA3D34, 0x12);
    machine.mem_store_byte(0xA3D35, 0x8D);
    machine.mem_store_byte(0xA3D36, 0xF8);
    machine.mem_store_byte(0xA3D37, 0xDF);
    machine.mem_store_byte(0xA70CB, 0xB1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x9375);
    EXPECT_EQ(cpu.get_ip(), 0xBEC8);
    EXPECT_EQ(cpu.get_flags(), 0xF803);

    // Final RAM entries
}

//
// adc word [cs:B1AAh], 76h
//
TEST_F(MachineTest, adc_word_cs_B1AAh_76h)
{
    // Initial CPU State
    cpu.set_ax(0x9FC8);
    cpu.set_bx(0x6C47);
    cpu.set_cx(0xD5EE);
    cpu.set_dx(0x8875);
    cpu.set_cs(0x3076);
    cpu.set_ss(0xAA57);
    cpu.set_ds(0xFE1C);
    cpu.set_es(0x3ED1);
    cpu.set_sp(0x0E8D);
    cpu.set_bp(0xE779);
    cpu.set_si(0xC68B);
    cpu.set_di(0xB655);
    cpu.set_ip(0x357B);
    cpu.set_flags(0xF093);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x33CDB, 0x2E);
    machine.mem_store_byte(0x33CDC, 0x83);
    machine.mem_store_byte(0x33CDD, 0x16);
    machine.mem_store_byte(0x33CDE, 0xAA);
    machine.mem_store_byte(0x33CDF, 0xB1);
    machine.mem_store_byte(0x33CE0, 0x76);
    machine.mem_store_byte(0x3B90A, 0x65);
    machine.mem_store_byte(0x3B90B, 0x8B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3581);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3B90A), 0xDC);
}

//
// adc word [ds:si-69AAh], CFBCh
//
TEST_F(MachineTest, adc_word_ds_si_69AAh_CFBCh)
{
    // Initial CPU State
    cpu.set_ax(0x0BA3);
    cpu.set_bx(0x6928);
    cpu.set_cx(0x0632);
    cpu.set_dx(0x7615);
    cpu.set_cs(0x997E);
    cpu.set_ss(0xAE88);
    cpu.set_ds(0xF1DB);
    cpu.set_es(0x4505);
    cpu.set_sp(0x175B);
    cpu.set_bp(0x398C);
    cpu.set_si(0x5327);
    cpu.set_di(0x6403);
    cpu.set_ip(0xF20E);
    cpu.set_flags(0xF406);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA89EE, 0x3E);
    machine.mem_store_byte(0xA89EF, 0x81);
    machine.mem_store_byte(0xA89F0, 0x94);
    machine.mem_store_byte(0xA89F1, 0x56);
    machine.mem_store_byte(0xA89F2, 0x96);
    machine.mem_store_byte(0xA89F3, 0xBC);
    machine.mem_store_byte(0xA89F4, 0xCF);
    machine.mem_store_byte(0x0072D, 0x51);
    machine.mem_store_byte(0x0072E, 0x0D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF215);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0072D), 0x0D);
    EXPECT_EQ(memory.load8(0x0072E), 0xDD);
}

//
// adc word [ss:bp+di], bx
//
TEST_F(MachineTest, adc_word_ss_bp_di_bx)
{
    // Initial CPU State
    cpu.set_ax(0x9960);
    cpu.set_bx(0x4576);
    cpu.set_cx(0xE6AA);
    cpu.set_dx(0xFC78);
    cpu.set_cs(0x4AB0);
    cpu.set_ss(0x30E6);
    cpu.set_ds(0xCB24);
    cpu.set_es(0x1499);
    cpu.set_sp(0xED88);
    cpu.set_bp(0x1EA7);
    cpu.set_si(0xCAFA);
    cpu.set_di(0xEFB2);
    cpu.set_ip(0x5B9C);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5069C, 0x11);
    machine.mem_store_byte(0x5069D, 0x1B);
    machine.mem_store_byte(0x5069E, 0x90);
    machine.mem_store_byte(0x5069F, 0x90);
    machine.mem_store_byte(0x31CB9, 0xD0);
    machine.mem_store_byte(0x31CBA, 0xA5);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5B9E);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x31CB9), 0x47);
    EXPECT_EQ(memory.load8(0x31CBA), 0xEB);
}

//
// add al, 2Dh
//
TEST_F(MachineTest, add_al_2Dh)
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
    machine.mem_store_byte(0x76C78, 0x04);
    machine.mem_store_byte(0x76C79, 0x2D);
    machine.mem_store_byte(0x76C7A, 0x90);
    machine.mem_store_byte(0x76C7B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xBEB1);
    EXPECT_EQ(cpu.get_ip(), 0x01CA);
    EXPECT_EQ(cpu.get_flags(), 0xF096);

    // Final RAM entries
}

//
// add ax, 80EFh
//
TEST_F(MachineTest, add_ax_80EFh)
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
    machine.mem_store_byte(0x6D5D5, 0x05);
    machine.mem_store_byte(0x6D5D6, 0xEF);
    machine.mem_store_byte(0x6D5D7, 0x80);
    machine.mem_store_byte(0x6D5D8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD254);
    EXPECT_EQ(cpu.get_ip(), 0xBD18);
    EXPECT_EQ(cpu.get_flags(), 0xF492);

    // Final RAM entries
}

//
// add bh, EFh
//
TEST_F(MachineTest, add_bh_EFh)
{
    // Initial CPU State
    cpu.set_ax(0xCF3F);
    cpu.set_bx(0x8BCA);
    cpu.set_cx(0xCB1C);
    cpu.set_dx(0x4C33);
    cpu.set_cs(0x52F9);
    cpu.set_ss(0xAA3D);
    cpu.set_ds(0xD82E);
    cpu.set_es(0x90DD);
    cpu.set_sp(0x8A0B);
    cpu.set_bp(0x542F);
    cpu.set_si(0xCBD2);
    cpu.set_di(0xE461);
    cpu.set_ip(0xB932);
    cpu.set_flags(0xFC87);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5E8C2, 0x26);
    machine.mem_store_byte(0x5E8C3, 0x82);
    machine.mem_store_byte(0x5E8C4, 0xC7);
    machine.mem_store_byte(0x5E8C5, 0xEF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x7ACA);
    EXPECT_EQ(cpu.get_ip(), 0xB936);
    EXPECT_EQ(cpu.get_flags(), 0xFC13);

    // Final RAM entries
}

//
// add byte [ds:bx+si-64h], FAh
//
TEST_F(MachineTest, add_byte_ds_bx_si_64h_FAh)
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
    machine.mem_store_byte(0x32186, 0x80);
    machine.mem_store_byte(0x32187, 0x40);
    machine.mem_store_byte(0x32188, 0x9C);
    machine.mem_store_byte(0x32189, 0xFA);
    machine.mem_store_byte(0x0D761, 0x59);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x02BA);
    EXPECT_EQ(cpu.get_flags(), 0xF417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0D761), 0x53);
}

//
// add byte [ss:bp+di-64h], cl
//
TEST_F(MachineTest, add_byte_ss_bp_di_64h_cl)
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
    machine.mem_store_byte(0x32186, 0x00);
    machine.mem_store_byte(0x32187, 0x4B);
    machine.mem_store_byte(0x32188, 0x9C);
    machine.mem_store_byte(0x32189, 0x90);
    machine.mem_store_byte(0x21CFD, 0x14);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x02B9);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x21CFD), 0xDC);
}

//
// add cl, byte [ss:bx]
//
TEST_F(MachineTest, add_cl_byte_ss_bx)
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
    machine.mem_store_byte(0x3F81C, 0x02);
    machine.mem_store_byte(0x3F81D, 0x0F);
    machine.mem_store_byte(0x3F81E, 0x90);
    machine.mem_store_byte(0x81A3C, 0xB9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x6D2B);
    EXPECT_EQ(cpu.get_ip(), 0x283E);
    EXPECT_EQ(cpu.get_flags(), 0xF407);

    // Final RAM entries
}

//
// add di, 15h
//
TEST_F(MachineTest, add_di_15h)
{
    // Initial CPU State
    cpu.set_ax(0x556D);
    cpu.set_bx(0x7FD7);
    cpu.set_cx(0xCCAE);
    cpu.set_dx(0x657D);
    cpu.set_cs(0xB396);
    cpu.set_ss(0x0266);
    cpu.set_ds(0xCF2B);
    cpu.set_es(0x3F98);
    cpu.set_sp(0x6FB1);
    cpu.set_bp(0x3EB2);
    cpu.set_si(0x9E66);
    cpu.set_di(0xDD24);
    cpu.set_ip(0xCEE6);
    cpu.set_flags(0xF087);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC0846, 0x83);
    machine.mem_store_byte(0xC0847, 0xC7);
    machine.mem_store_byte(0xC0848, 0x15);
    machine.mem_store_byte(0xC0849, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xDD39);
    EXPECT_EQ(cpu.get_ip(), 0xCEE9);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// add dx, sp
//
TEST_F(MachineTest, add_dx_sp)
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
    machine.mem_store_byte(0xA9BE2, 0x01);
    machine.mem_store_byte(0xA9BE3, 0xE2);
    machine.mem_store_byte(0xA9BE4, 0x90);
    machine.mem_store_byte(0xA9BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x7658);
    EXPECT_EQ(cpu.get_ip(), 0x94E4);
    EXPECT_EQ(cpu.get_flags(), 0xFC03);

    // Final RAM entries
}

//
// add dx, word [ds:bx+di-46FDh]
//
TEST_F(MachineTest, add_dx_word_ds_bx_di_46FDh)
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
    machine.mem_store_byte(0xEB58F, 0x03);
    machine.mem_store_byte(0xEB590, 0x91);
    machine.mem_store_byte(0xEB591, 0x03);
    machine.mem_store_byte(0xEB592, 0xB9);
    machine.mem_store_byte(0x4CB74, 0x74);
    machine.mem_store_byte(0x4CB75, 0x73);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x3163);
    EXPECT_EQ(cpu.get_ip(), 0x3323);
    EXPECT_EQ(cpu.get_flags(), 0xF017);

    // Final RAM entries
}

//
// add word [ss:bx], B9E5h
//
TEST_F(MachineTest, add_word_ss_bx_B9E5h)
{
    // Initial CPU State
    cpu.set_ax(0x6694);
    cpu.set_bx(0x9ACA);
    cpu.set_cx(0x6E3C);
    cpu.set_dx(0x58A1);
    cpu.set_cs(0xF5E5);
    cpu.set_ss(0xE377);
    cpu.set_ds(0xAE36);
    cpu.set_es(0x3E4B);
    cpu.set_sp(0x2443);
    cpu.set_bp(0x31F2);
    cpu.set_si(0xD82D);
    cpu.set_di(0xB03D);
    cpu.set_ip(0x7526);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD376, 0x36);
    machine.mem_store_byte(0xFD377, 0x81);
    machine.mem_store_byte(0xFD378, 0x07);
    machine.mem_store_byte(0xFD379, 0xE5);
    machine.mem_store_byte(0xFD37A, 0xB9);
    machine.mem_store_byte(0xED23A, 0xA6);
    machine.mem_store_byte(0xED23B, 0xC1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x752B);
    EXPECT_EQ(cpu.get_flags(), 0xF807);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xED23A), 0x8B);
    EXPECT_EQ(memory.load8(0xED23B), 0x7B);
}
