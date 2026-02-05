#include "fixture.h"

// Tests: mov

TEST_F(MachineTest, mov_ah_EAh)
{
    // Initial CPU State
    cpu.set_ax(0x9D6B);
    cpu.set_bx(0x1D6D);
    cpu.set_cx(0xCE3E);
    cpu.set_dx(0x44CA);
    cpu.set_cs(0xFDA3);
    cpu.set_ss(0x83D1);
    cpu.set_ds(0x0F44);
    cpu.set_es(0x3DFA);
    cpu.set_sp(0x6F5F);
    cpu.set_bp(0xD024);
    cpu.set_si(0xCBFE);
    cpu.set_di(0xEE02);
    cpu.set_ip(0x9986);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x073B6, 0xB4);
    machine.mem_store_byte(0x073B7, 0xEA);
    machine.mem_store_byte(0x073B8, 0x90);
    machine.mem_store_byte(0x073B9, 0x90);
    machine.mem_store_byte(0x073BA, 0x90);
    machine.mem_store_byte(0x073BB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xEA6B);
    EXPECT_EQ(cpu.get_ip(), 0x9988);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x073B6), 0xB4);
    EXPECT_EQ(memory.load8(0x073B7), 0xEA);
    EXPECT_EQ(memory.load8(0x073B8), 0x90);
    EXPECT_EQ(memory.load8(0x073B9), 0x90);
    EXPECT_EQ(memory.load8(0x073BA), 0x90);
    EXPECT_EQ(memory.load8(0x073BB), 0x90);
}


TEST_F(MachineTest, mov_ah_dh)
{
    // Initial CPU State
    cpu.set_ax(0xA88F);
    cpu.set_bx(0x8855);
    cpu.set_cx(0xE07C);
    cpu.set_dx(0xA867);
    cpu.set_cs(0xC049);
    cpu.set_ss(0x0D28);
    cpu.set_ds(0x77B3);
    cpu.set_es(0x235A);
    cpu.set_sp(0x6E42);
    cpu.set_bp(0x192D);
    cpu.set_si(0x885E);
    cpu.set_di(0x5F61);
    cpu.set_ip(0xCBE6);
    cpu.set_flags(0xF0D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCD076, 0x3E);
    machine.mem_store_byte(0xCD077, 0x88);
    machine.mem_store_byte(0xCD078, 0xF4);
    machine.mem_store_byte(0xCD079, 0x90);
    machine.mem_store_byte(0xCD07A, 0x90);
    machine.mem_store_byte(0xCD07B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCBE9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCD076), 0x3E);
    EXPECT_EQ(memory.load8(0xCD077), 0x88);
    EXPECT_EQ(memory.load8(0xCD078), 0xF4);
    EXPECT_EQ(memory.load8(0xCD079), 0x90);
    EXPECT_EQ(memory.load8(0xCD07A), 0x90);
    EXPECT_EQ(memory.load8(0xCD07B), 0x90);
}


TEST_F(MachineTest, mov_al_8Ah)
{
    // Initial CPU State
    cpu.set_ax(0xA991);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xFC22);
    cpu.set_dx(0xEC22);
    cpu.set_cs(0xEBB4);
    cpu.set_ss(0x39EB);
    cpu.set_ds(0x4C11);
    cpu.set_es(0x7D5A);
    cpu.set_sp(0x456B);
    cpu.set_bp(0x9128);
    cpu.set_si(0x7771);
    cpu.set_di(0x6B96);
    cpu.set_ip(0x5F6C);
    cpu.set_flags(0xFC83);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF1AAC, 0xB0);
    machine.mem_store_byte(0xF1AAD, 0x8A);
    machine.mem_store_byte(0xF1AAE, 0x90);
    machine.mem_store_byte(0xF1AAF, 0x90);
    machine.mem_store_byte(0xF1AB0, 0x90);
    machine.mem_store_byte(0xF1AB1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xA98A);
    EXPECT_EQ(cpu.get_ip(), 0x5F6E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF1AAC), 0xB0);
    EXPECT_EQ(memory.load8(0xF1AAD), 0x8A);
    EXPECT_EQ(memory.load8(0xF1AAE), 0x90);
    EXPECT_EQ(memory.load8(0xF1AAF), 0x90);
    EXPECT_EQ(memory.load8(0xF1AB0), 0x90);
    EXPECT_EQ(memory.load8(0xF1AB1), 0x90);
}


TEST_F(MachineTest, mov_al_byte_ds_8C42h)
{
    // Initial CPU State
    cpu.set_ax(0xF024);
    cpu.set_bx(0xEF9D);
    cpu.set_cx(0x8788);
    cpu.set_dx(0xD256);
    cpu.set_cs(0x350E);
    cpu.set_ss(0xD9DB);
    cpu.set_ds(0x5237);
    cpu.set_es(0x9586);
    cpu.set_sp(0x943A);
    cpu.set_bp(0xAE96);
    cpu.set_si(0x9907);
    cpu.set_di(0x6122);
    cpu.set_ip(0x224B);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3732B, 0xA0);
    machine.mem_store_byte(0x3732C, 0x42);
    machine.mem_store_byte(0x3732D, 0x8C);
    machine.mem_store_byte(0x3732E, 0x90);
    machine.mem_store_byte(0x3732F, 0x90);
    machine.mem_store_byte(0x5AFB2, 0x7E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xF07E);
    EXPECT_EQ(cpu.get_ip(), 0x224E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3732B), 0xA0);
    EXPECT_EQ(memory.load8(0x3732C), 0x42);
    EXPECT_EQ(memory.load8(0x3732D), 0x8C);
    EXPECT_EQ(memory.load8(0x3732E), 0x90);
    EXPECT_EQ(memory.load8(0x3732F), 0x90);
    EXPECT_EQ(memory.load8(0x5AFB2), 0x7E);
}


TEST_F(MachineTest, mov_ax_CBE2h)
{
    // Initial CPU State
    cpu.set_ax(0xA804);
    cpu.set_bx(0xFB40);
    cpu.set_cx(0x84A6);
    cpu.set_dx(0x2897);
    cpu.set_cs(0x9A20);
    cpu.set_ss(0x537C);
    cpu.set_ds(0x6A0A);
    cpu.set_es(0x5F64);
    cpu.set_sp(0x0BEB);
    cpu.set_bp(0x80D4);
    cpu.set_si(0xCC43);
    cpu.set_di(0x2999);
    cpu.set_ip(0xB601);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA5801, 0xB8);
    machine.mem_store_byte(0xA5802, 0xE2);
    machine.mem_store_byte(0xA5803, 0xCB);
    machine.mem_store_byte(0xA5804, 0x90);
    machine.mem_store_byte(0xA5805, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xCBE2);
    EXPECT_EQ(cpu.get_ip(), 0xB604);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA5801), 0xB8);
    EXPECT_EQ(memory.load8(0xA5802), 0xE2);
    EXPECT_EQ(memory.load8(0xA5803), 0xCB);
    EXPECT_EQ(memory.load8(0xA5804), 0x90);
    EXPECT_EQ(memory.load8(0xA5805), 0x90);
}


TEST_F(MachineTest, mov_ax_word_es_A2E9h)
{
    // Initial CPU State
    cpu.set_ax(0xA288);
    cpu.set_bx(0xCA78);
    cpu.set_cx(0xD734);
    cpu.set_dx(0xE014);
    cpu.set_cs(0xA610);
    cpu.set_ss(0x119F);
    cpu.set_ds(0xECC8);
    cpu.set_es(0x12A7);
    cpu.set_sp(0xA649);
    cpu.set_bp(0xE226);
    cpu.set_si(0xE0E9);
    cpu.set_di(0x228D);
    cpu.set_ip(0xC687);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB2787, 0x26);
    machine.mem_store_byte(0xB2788, 0xA1);
    machine.mem_store_byte(0xB2789, 0xE9);
    machine.mem_store_byte(0xB278A, 0xA2);
    machine.mem_store_byte(0xB278B, 0x90);
    machine.mem_store_byte(0x1CD59, 0x6B);
    machine.mem_store_byte(0x1CD5A, 0xF5);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xF56B);
    EXPECT_EQ(cpu.get_ip(), 0xC68B);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB2787), 0x26);
    EXPECT_EQ(memory.load8(0xB2788), 0xA1);
    EXPECT_EQ(memory.load8(0xB2789), 0xE9);
    EXPECT_EQ(memory.load8(0xB278A), 0xA2);
    EXPECT_EQ(memory.load8(0xB278B), 0x90);
    EXPECT_EQ(memory.load8(0x1CD59), 0x6B);
    EXPECT_EQ(memory.load8(0x1CD5A), 0xF5);
}


TEST_F(MachineTest, mov_ax_word_ss_bp_si)
{
    // Initial CPU State
    cpu.set_ax(0xD269);
    cpu.set_bx(0x0CAA);
    cpu.set_cx(0x2528);
    cpu.set_dx(0xD3A5);
    cpu.set_cs(0xCE53);
    cpu.set_ss(0x40E5);
    cpu.set_ds(0x5120);
    cpu.set_es(0x18CD);
    cpu.set_sp(0xE47A);
    cpu.set_bp(0x091D);
    cpu.set_si(0x6973);
    cpu.set_di(0x687B);
    cpu.set_ip(0xC875);
    cpu.set_flags(0xF857);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDADA5, 0x8B);
    machine.mem_store_byte(0xDADA6, 0x02);
    machine.mem_store_byte(0xDADA7, 0x90);
    machine.mem_store_byte(0xDADA8, 0x90);
    machine.mem_store_byte(0xDADA9, 0x90);
    machine.mem_store_byte(0x480E0, 0x1B);
    machine.mem_store_byte(0x480E1, 0xDF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xDF1B);
    EXPECT_EQ(cpu.get_ip(), 0xC877);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDADA5), 0x8B);
    EXPECT_EQ(memory.load8(0xDADA6), 0x02);
    EXPECT_EQ(memory.load8(0xDADA7), 0x90);
    EXPECT_EQ(memory.load8(0xDADA8), 0x90);
    EXPECT_EQ(memory.load8(0xDADA9), 0x90);
    EXPECT_EQ(memory.load8(0x480E0), 0x1B);
    EXPECT_EQ(memory.load8(0x480E1), 0xDF);
}


TEST_F(MachineTest, mov_bh_56h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x99D3);
    cpu.set_cx(0x8FB6);
    cpu.set_dx(0xF4B9);
    cpu.set_cs(0xBD4E);
    cpu.set_ss(0xFBE3);
    cpu.set_ds(0xD67D);
    cpu.set_es(0xA572);
    cpu.set_sp(0xB850);
    cpu.set_bp(0xE412);
    cpu.set_si(0x7552);
    cpu.set_di(0x80B5);
    cpu.set_ip(0xC3A7);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC9887, 0xB7);
    machine.mem_store_byte(0xC9888, 0x56);
    machine.mem_store_byte(0xC9889, 0x90);
    machine.mem_store_byte(0xC988A, 0x90);
    machine.mem_store_byte(0xC988B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x56D3);
    EXPECT_EQ(cpu.get_ip(), 0xC3A9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC9887), 0xB7);
    EXPECT_EQ(memory.load8(0xC9888), 0x56);
    EXPECT_EQ(memory.load8(0xC9889), 0x90);
    EXPECT_EQ(memory.load8(0xC988A), 0x90);
    EXPECT_EQ(memory.load8(0xC988B), 0x90);
}


TEST_F(MachineTest, mov_bl_E2h)
{
    // Initial CPU State
    cpu.set_ax(0x66C8);
    cpu.set_bx(0x82DA);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x5BE8);
    cpu.set_cs(0x897B);
    cpu.set_ss(0xBA3E);
    cpu.set_ds(0x8BA2);
    cpu.set_es(0xFF4D);
    cpu.set_sp(0x1502);
    cpu.set_bp(0x0EBD);
    cpu.set_si(0x835D);
    cpu.set_di(0x3183);
    cpu.set_ip(0xF9D3);
    cpu.set_flags(0xF8C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x99183, 0xB3);
    machine.mem_store_byte(0x99184, 0xE2);
    machine.mem_store_byte(0x99185, 0x90);
    machine.mem_store_byte(0x99186, 0x90);
    machine.mem_store_byte(0x99187, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x82E2);
    EXPECT_EQ(cpu.get_ip(), 0xF9D5);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x99183), 0xB3);
    EXPECT_EQ(memory.load8(0x99184), 0xE2);
    EXPECT_EQ(memory.load8(0x99185), 0x90);
    EXPECT_EQ(memory.load8(0x99186), 0x90);
    EXPECT_EQ(memory.load8(0x99187), 0x90);
}


TEST_F(MachineTest, mov_bl_byte_ds_bx_di_F4h)
{
    // Initial CPU State
    cpu.set_ax(0x3C09);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xC904);
    cpu.set_dx(0xEE98);
    cpu.set_cs(0x2DE9);
    cpu.set_ss(0x1BFD);
    cpu.set_ds(0xEE7A);
    cpu.set_es(0x2DC4);
    cpu.set_sp(0xE156);
    cpu.set_bp(0x9F82);
    cpu.set_si(0x28A5);
    cpu.set_di(0xE985);
    cpu.set_ip(0x2F0C);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x30D9C, 0x8A);
    machine.mem_store_byte(0x30D9D, 0x99);
    machine.mem_store_byte(0x30D9E, 0xF4);
    machine.mem_store_byte(0x30D9F, 0x00);
    machine.mem_store_byte(0x30DA0, 0x90);
    machine.mem_store_byte(0x30DA1, 0x90);
    machine.mem_store_byte(0xFD219, 0x7D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x007D);
    EXPECT_EQ(cpu.get_ip(), 0x2F10);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30D9C), 0x8A);
    EXPECT_EQ(memory.load8(0x30D9D), 0x99);
    EXPECT_EQ(memory.load8(0x30D9E), 0xF4);
    EXPECT_EQ(memory.load8(0x30D9F), 0x00);
    EXPECT_EQ(memory.load8(0x30DA0), 0x90);
    EXPECT_EQ(memory.load8(0x30DA1), 0x90);
    EXPECT_EQ(memory.load8(0xFD219), 0x7D);
}


TEST_F(MachineTest, mov_bp_A24h)
{
    // Initial CPU State
    cpu.set_ax(0x9280);
    cpu.set_bx(0x2476);
    cpu.set_cx(0xD8F6);
    cpu.set_dx(0xC7C7);
    cpu.set_cs(0xDE35);
    cpu.set_ss(0x94B0);
    cpu.set_ds(0x7075);
    cpu.set_es(0x7092);
    cpu.set_sp(0x3685);
    cpu.set_bp(0x32C5);
    cpu.set_si(0xC231);
    cpu.set_di(0xB4C8);
    cpu.set_ip(0xE001);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEC351, 0xBD);
    machine.mem_store_byte(0xEC352, 0x24);
    machine.mem_store_byte(0xEC353, 0x0A);
    machine.mem_store_byte(0xEC354, 0x90);
    machine.mem_store_byte(0xEC355, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x0A24);
    EXPECT_EQ(cpu.get_ip(), 0xE004);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEC351), 0xBD);
    EXPECT_EQ(memory.load8(0xEC352), 0x24);
    EXPECT_EQ(memory.load8(0xEC353), 0x0A);
    EXPECT_EQ(memory.load8(0xEC354), 0x90);
    EXPECT_EQ(memory.load8(0xEC355), 0x90);
}


TEST_F(MachineTest, mov_bx_9B7Bh)
{
    // Initial CPU State
    cpu.set_ax(0x9AFE);
    cpu.set_bx(0x70F3);
    cpu.set_cx(0xDA02);
    cpu.set_dx(0x67EC);
    cpu.set_cs(0xCB2F);
    cpu.set_ss(0xC2B2);
    cpu.set_ds(0x77E4);
    cpu.set_es(0xCE58);
    cpu.set_sp(0x367A);
    cpu.set_bp(0x7E1B);
    cpu.set_si(0x5871);
    cpu.set_di(0x5877);
    cpu.set_ip(0x3F6B);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCF25B, 0xBB);
    machine.mem_store_byte(0xCF25C, 0x7B);
    machine.mem_store_byte(0xCF25D, 0x9B);
    machine.mem_store_byte(0xCF25E, 0x90);
    machine.mem_store_byte(0xCF25F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x9B7B);
    EXPECT_EQ(cpu.get_ip(), 0x3F6E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCF25B), 0xBB);
    EXPECT_EQ(memory.load8(0xCF25C), 0x7B);
    EXPECT_EQ(memory.load8(0xCF25D), 0x9B);
    EXPECT_EQ(memory.load8(0xCF25E), 0x90);
    EXPECT_EQ(memory.load8(0xCF25F), 0x90);
}


TEST_F(MachineTest, mov_byte_ds_34A2h_6Ch)
{
    // Initial CPU State
    cpu.set_ax(0xE765);
    cpu.set_bx(0x3E74);
    cpu.set_cx(0x86CC);
    cpu.set_dx(0x6B1E);
    cpu.set_cs(0xAD28);
    cpu.set_ss(0xF04A);
    cpu.set_ds(0xD2A0);
    cpu.set_es(0x1000);
    cpu.set_sp(0xD195);
    cpu.set_bp(0x990C);
    cpu.set_si(0x2901);
    cpu.set_di(0x2BAF);
    cpu.set_ip(0xECBD);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBBF3D, 0xC6);
    machine.mem_store_byte(0xBBF3E, 0x3E);
    machine.mem_store_byte(0xBBF3F, 0xA2);
    machine.mem_store_byte(0xBBF40, 0x34);
    machine.mem_store_byte(0xBBF41, 0x6C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xECC2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBBF3D), 0xC6);
    EXPECT_EQ(memory.load8(0xBBF3E), 0x3E);
    EXPECT_EQ(memory.load8(0xBBF3F), 0xA2);
    EXPECT_EQ(memory.load8(0xBBF40), 0x34);
    EXPECT_EQ(memory.load8(0xBBF41), 0x6C);
    EXPECT_EQ(memory.load8(0xD5EA2), 0x6C);
}


TEST_F(MachineTest, mov_byte_ds_ABA1h_al)
{
    // Initial CPU State
    cpu.set_ax(0x7D00);
    cpu.set_bx(0x16A3);
    cpu.set_cx(0xDEBA);
    cpu.set_dx(0x5E20);
    cpu.set_cs(0xB127);
    cpu.set_ss(0x4846);
    cpu.set_ds(0xE260);
    cpu.set_es(0xCE19);
    cpu.set_sp(0xD51E);
    cpu.set_bp(0xAAE4);
    cpu.set_si(0x981D);
    cpu.set_di(0xE2D4);
    cpu.set_ip(0x5DF0);
    cpu.set_flags(0xF087);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB7060, 0x3E);
    machine.mem_store_byte(0xB7061, 0xA2);
    machine.mem_store_byte(0xB7062, 0xA1);
    machine.mem_store_byte(0xB7063, 0xAB);
    machine.mem_store_byte(0xB7064, 0x90);
    machine.mem_store_byte(0xB7065, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5DF4);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB7060), 0x3E);
    EXPECT_EQ(memory.load8(0xB7061), 0xA2);
    EXPECT_EQ(memory.load8(0xB7062), 0xA1);
    EXPECT_EQ(memory.load8(0xB7063), 0xAB);
    EXPECT_EQ(memory.load8(0xB7064), 0x90);
    EXPECT_EQ(memory.load8(0xB7065), 0x90);
    EXPECT_EQ(memory.load8(0xED1A1), 0x00);
}


TEST_F(MachineTest, mov_ch_7Ch)
{
    // Initial CPU State
    cpu.set_ax(0xD70D);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xB4DC);
    cpu.set_dx(0x83DB);
    cpu.set_cs(0x8114);
    cpu.set_ss(0xBCA7);
    cpu.set_ds(0xF4F6);
    cpu.set_es(0x24C7);
    cpu.set_sp(0x9842);
    cpu.set_bp(0x4514);
    cpu.set_si(0x0000);
    cpu.set_di(0x76F1);
    cpu.set_ip(0x6662);
    cpu.set_flags(0xF843);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x877A2, 0xB5);
    machine.mem_store_byte(0x877A3, 0x7C);
    machine.mem_store_byte(0x877A4, 0x90);
    machine.mem_store_byte(0x877A5, 0x90);
    machine.mem_store_byte(0x877A6, 0x90);
    machine.mem_store_byte(0x877A7, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x7CDC);
    EXPECT_EQ(cpu.get_ip(), 0x6664);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x877A2), 0xB5);
    EXPECT_EQ(memory.load8(0x877A3), 0x7C);
    EXPECT_EQ(memory.load8(0x877A4), 0x90);
    EXPECT_EQ(memory.load8(0x877A5), 0x90);
    EXPECT_EQ(memory.load8(0x877A6), 0x90);
    EXPECT_EQ(memory.load8(0x877A7), 0x90);
}


TEST_F(MachineTest, mov_cl_45h)
{
    // Initial CPU State
    cpu.set_ax(0x5790);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xABEE);
    cpu.set_dx(0x3811);
    cpu.set_cs(0x5068);
    cpu.set_ss(0xF6E1);
    cpu.set_ds(0x2341);
    cpu.set_es(0x8193);
    cpu.set_sp(0x5A2C);
    cpu.set_bp(0x03A1);
    cpu.set_si(0x0187);
    cpu.set_di(0x21CD);
    cpu.set_ip(0x730E);
    cpu.set_flags(0xF4C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5798E, 0xB1);
    machine.mem_store_byte(0x5798F, 0x45);
    machine.mem_store_byte(0x57990, 0x90);
    machine.mem_store_byte(0x57991, 0x90);
    machine.mem_store_byte(0x57992, 0x90);
    machine.mem_store_byte(0x57993, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xAB45);
    EXPECT_EQ(cpu.get_ip(), 0x7310);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5798E), 0xB1);
    EXPECT_EQ(memory.load8(0x5798F), 0x45);
    EXPECT_EQ(memory.load8(0x57990), 0x90);
    EXPECT_EQ(memory.load8(0x57991), 0x90);
    EXPECT_EQ(memory.load8(0x57992), 0x90);
    EXPECT_EQ(memory.load8(0x57993), 0x90);
}


TEST_F(MachineTest, mov_cx_1D9Fh)
{
    // Initial CPU State
    cpu.set_ax(0x3AEE);
    cpu.set_bx(0x39AF);
    cpu.set_cx(0xF57C);
    cpu.set_dx(0xCDBB);
    cpu.set_cs(0x7F30);
    cpu.set_ss(0x15BF);
    cpu.set_ds(0xE01D);
    cpu.set_es(0xBC12);
    cpu.set_sp(0x06FA);
    cpu.set_bp(0x85DF);
    cpu.set_si(0x6A70);
    cpu.set_di(0x876B);
    cpu.set_ip(0xDFD8);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8D2D8, 0xB9);
    machine.mem_store_byte(0x8D2D9, 0x9F);
    machine.mem_store_byte(0x8D2DA, 0x1D);
    machine.mem_store_byte(0x8D2DB, 0x90);
    machine.mem_store_byte(0x8D2DC, 0x90);
    machine.mem_store_byte(0x8D2DD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x1D9F);
    EXPECT_EQ(cpu.get_ip(), 0xDFDB);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8D2D8), 0xB9);
    EXPECT_EQ(memory.load8(0x8D2D9), 0x9F);
    EXPECT_EQ(memory.load8(0x8D2DA), 0x1D);
    EXPECT_EQ(memory.load8(0x8D2DB), 0x90);
    EXPECT_EQ(memory.load8(0x8D2DC), 0x90);
    EXPECT_EQ(memory.load8(0x8D2DD), 0x90);
}


TEST_F(MachineTest, mov_dh_90h)
{
    // Initial CPU State
    cpu.set_ax(0xB8F4);
    cpu.set_bx(0x459A);
    cpu.set_cx(0xA7F4);
    cpu.set_dx(0xEF65);
    cpu.set_cs(0x9513);
    cpu.set_ss(0x15DB);
    cpu.set_ds(0x9EA9);
    cpu.set_es(0xDB26);
    cpu.set_sp(0x02E0);
    cpu.set_bp(0xC914);
    cpu.set_si(0xA7D3);
    cpu.set_di(0x0000);
    cpu.set_ip(0x9C53);
    cpu.set_flags(0xFC43);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9ED83, 0xB6);
    machine.mem_store_byte(0x9ED84, 0x90);
    machine.mem_store_byte(0x9ED85, 0x90);
    machine.mem_store_byte(0x9ED86, 0x90);
    machine.mem_store_byte(0x9ED87, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x9065);
    EXPECT_EQ(cpu.get_ip(), 0x9C55);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9ED83), 0xB6);
    EXPECT_EQ(memory.load8(0x9ED84), 0x90);
    EXPECT_EQ(memory.load8(0x9ED85), 0x90);
    EXPECT_EQ(memory.load8(0x9ED86), 0x90);
    EXPECT_EQ(memory.load8(0x9ED87), 0x90);
}


TEST_F(MachineTest, mov_di_80B0h)
{
    // Initial CPU State
    cpu.set_ax(0xC60C);
    cpu.set_bx(0x11B3);
    cpu.set_cx(0xA02A);
    cpu.set_dx(0xF858);
    cpu.set_cs(0x52A5);
    cpu.set_ss(0x297B);
    cpu.set_ds(0x09D0);
    cpu.set_es(0xEC56);
    cpu.set_sp(0x381F);
    cpu.set_bp(0x9546);
    cpu.set_si(0x1338);
    cpu.set_di(0x0000);
    cpu.set_ip(0x81A8);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5ABF8, 0xBF);
    machine.mem_store_byte(0x5ABF9, 0xB0);
    machine.mem_store_byte(0x5ABFA, 0x80);
    machine.mem_store_byte(0x5ABFB, 0x90);
    machine.mem_store_byte(0x5ABFC, 0x90);
    machine.mem_store_byte(0x5ABFD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x80B0);
    EXPECT_EQ(cpu.get_ip(), 0x81AB);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5ABF8), 0xBF);
    EXPECT_EQ(memory.load8(0x5ABF9), 0xB0);
    EXPECT_EQ(memory.load8(0x5ABFA), 0x80);
    EXPECT_EQ(memory.load8(0x5ABFB), 0x90);
    EXPECT_EQ(memory.load8(0x5ABFC), 0x90);
    EXPECT_EQ(memory.load8(0x5ABFD), 0x90);
}


TEST_F(MachineTest, mov_di_ds)
{
    // Initial CPU State
    cpu.set_ax(0xC427);
    cpu.set_bx(0xD415);
    cpu.set_cx(0xA2EE);
    cpu.set_dx(0xEC0B);
    cpu.set_cs(0x0FBD);
    cpu.set_ss(0xB578);
    cpu.set_ds(0x4A9D);
    cpu.set_es(0xD7B9);
    cpu.set_sp(0x0043);
    cpu.set_bp(0x05A3);
    cpu.set_si(0xB098);
    cpu.set_di(0x2770);
    cpu.set_ip(0x0B7F);
    cpu.set_flags(0xF093);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1074F, 0x8C);
    machine.mem_store_byte(0x10750, 0xDF);
    machine.mem_store_byte(0x10751, 0x90);
    machine.mem_store_byte(0x10752, 0x90);
    machine.mem_store_byte(0x10753, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x4A9D);
    EXPECT_EQ(cpu.get_ip(), 0x0B81);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1074F), 0x8C);
    EXPECT_EQ(memory.load8(0x10750), 0xDF);
    EXPECT_EQ(memory.load8(0x10751), 0x90);
    EXPECT_EQ(memory.load8(0x10752), 0x90);
    EXPECT_EQ(memory.load8(0x10753), 0x90);
}


TEST_F(MachineTest, mov_dl_3Ah)
{
    // Initial CPU State
    cpu.set_ax(0xCA56);
    cpu.set_bx(0xE47F);
    cpu.set_cx(0x7A1A);
    cpu.set_dx(0x64B7);
    cpu.set_cs(0x8139);
    cpu.set_ss(0x94DF);
    cpu.set_ds(0x754D);
    cpu.set_es(0xAAD6);
    cpu.set_sp(0xACAF);
    cpu.set_bp(0x6FDA);
    cpu.set_si(0x36DD);
    cpu.set_di(0x6E49);
    cpu.set_ip(0x351A);
    cpu.set_flags(0xFC56);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x848AA, 0xB2);
    machine.mem_store_byte(0x848AB, 0x3A);
    machine.mem_store_byte(0x848AC, 0x90);
    machine.mem_store_byte(0x848AD, 0x90);
    machine.mem_store_byte(0x848AE, 0x90);
    machine.mem_store_byte(0x848AF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x643A);
    EXPECT_EQ(cpu.get_ip(), 0x351C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x848AA), 0xB2);
    EXPECT_EQ(memory.load8(0x848AB), 0x3A);
    EXPECT_EQ(memory.load8(0x848AC), 0x90);
    EXPECT_EQ(memory.load8(0x848AD), 0x90);
    EXPECT_EQ(memory.load8(0x848AE), 0x90);
    EXPECT_EQ(memory.load8(0x848AF), 0x90);
}


TEST_F(MachineTest, mov_dx_CF0Ch)
{
    // Initial CPU State
    cpu.set_ax(0x4758);
    cpu.set_bx(0x7B27);
    cpu.set_cx(0xAABC);
    cpu.set_dx(0xDA9E);
    cpu.set_cs(0x2DD9);
    cpu.set_ss(0xADE2);
    cpu.set_ds(0x23A6);
    cpu.set_es(0xDA76);
    cpu.set_sp(0x7C4E);
    cpu.set_bp(0x9267);
    cpu.set_si(0x6EE9);
    cpu.set_di(0xF27A);
    cpu.set_ip(0xC277);
    cpu.set_flags(0xF493);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3A007, 0xBA);
    machine.mem_store_byte(0x3A008, 0x0C);
    machine.mem_store_byte(0x3A009, 0xCF);
    machine.mem_store_byte(0x3A00A, 0x90);
    machine.mem_store_byte(0x3A00B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xCF0C);
    EXPECT_EQ(cpu.get_ip(), 0xC27A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3A007), 0xBA);
    EXPECT_EQ(memory.load8(0x3A008), 0x0C);
    EXPECT_EQ(memory.load8(0x3A009), 0xCF);
    EXPECT_EQ(memory.load8(0x3A00A), 0x90);
    EXPECT_EQ(memory.load8(0x3A00B), 0x90);
}


TEST_F(MachineTest, mov_es_word_ss_bp_di_7814h)
{
    // Initial CPU State
    cpu.set_ax(0x2DD6);
    cpu.set_bx(0xF390);
    cpu.set_cx(0x8478);
    cpu.set_dx(0x2FAF);
    cpu.set_cs(0x8C0A);
    cpu.set_ss(0x0948);
    cpu.set_ds(0x7C31);
    cpu.set_es(0x0CD3);
    cpu.set_sp(0xA3A5);
    cpu.set_bp(0xA4E2);
    cpu.set_si(0xD11F);
    cpu.set_di(0xD555);
    cpu.set_ip(0xBCD3);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97D73, 0x8E);
    machine.mem_store_byte(0x97D74, 0x83);
    machine.mem_store_byte(0x97D75, 0xEC);
    machine.mem_store_byte(0x97D76, 0x87);
    machine.mem_store_byte(0x97D77, 0x90);
    machine.mem_store_byte(0x096A3, 0x63);
    machine.mem_store_byte(0x096A4, 0x63);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_es(), 0x6363);
    EXPECT_EQ(cpu.get_ip(), 0xBCD7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x97D73), 0x8E);
    EXPECT_EQ(memory.load8(0x97D74), 0x83);
    EXPECT_EQ(memory.load8(0x97D75), 0xEC);
    EXPECT_EQ(memory.load8(0x97D76), 0x87);
    EXPECT_EQ(memory.load8(0x97D77), 0x90);
    EXPECT_EQ(memory.load8(0x096A3), 0x63);
    EXPECT_EQ(memory.load8(0x096A4), 0x63);
}


TEST_F(MachineTest, mov_si_47A1h)
{
    // Initial CPU State
    cpu.set_ax(0x947F);
    cpu.set_bx(0xE9A1);
    cpu.set_cx(0x1FA2);
    cpu.set_dx(0xA5D5);
    cpu.set_cs(0x258C);
    cpu.set_ss(0x2A58);
    cpu.set_ds(0xD430);
    cpu.set_es(0x6CAA);
    cpu.set_sp(0x6949);
    cpu.set_bp(0x7765);
    cpu.set_si(0xDE79);
    cpu.set_di(0x0000);
    cpu.set_ip(0xC0AA);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3196A, 0xBE);
    machine.mem_store_byte(0x3196B, 0xA1);
    machine.mem_store_byte(0x3196C, 0x47);
    machine.mem_store_byte(0x3196D, 0x90);
    machine.mem_store_byte(0x3196E, 0x90);
    machine.mem_store_byte(0x3196F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x47A1);
    EXPECT_EQ(cpu.get_ip(), 0xC0AD);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3196A), 0xBE);
    EXPECT_EQ(memory.load8(0x3196B), 0xA1);
    EXPECT_EQ(memory.load8(0x3196C), 0x47);
    EXPECT_EQ(memory.load8(0x3196D), 0x90);
    EXPECT_EQ(memory.load8(0x3196E), 0x90);
    EXPECT_EQ(memory.load8(0x3196F), 0x90);
}


TEST_F(MachineTest, mov_sp_F0DFh)
{
    // Initial CPU State
    cpu.set_ax(0xDEF8);
    cpu.set_bx(0x71E3);
    cpu.set_cx(0x563A);
    cpu.set_dx(0x566E);
    cpu.set_cs(0xC73B);
    cpu.set_ss(0x237D);
    cpu.set_ds(0x707B);
    cpu.set_es(0x1B34);
    cpu.set_sp(0x33DC);
    cpu.set_bp(0x290A);
    cpu.set_si(0xC3AD);
    cpu.set_di(0x5C8C);
    cpu.set_ip(0x3DEB);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCB19B, 0xBC);
    machine.mem_store_byte(0xCB19C, 0xDF);
    machine.mem_store_byte(0xCB19D, 0xF0);
    machine.mem_store_byte(0xCB19E, 0x90);
    machine.mem_store_byte(0xCB19F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xF0DF);
    EXPECT_EQ(cpu.get_ip(), 0x3DEE);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCB19B), 0xBC);
    EXPECT_EQ(memory.load8(0xCB19C), 0xDF);
    EXPECT_EQ(memory.load8(0xCB19D), 0xF0);
    EXPECT_EQ(memory.load8(0xCB19E), 0x90);
    EXPECT_EQ(memory.load8(0xCB19F), 0x90);
}


TEST_F(MachineTest, mov_word_ds_bx_70ADh_sp)
{
    // Initial CPU State
    cpu.set_ax(0xECB6);
    cpu.set_bx(0xAD75);
    cpu.set_cx(0xEFE6);
    cpu.set_dx(0xE6E0);
    cpu.set_cs(0x871E);
    cpu.set_ss(0xC21C);
    cpu.set_ds(0x2093);
    cpu.set_es(0xEAEA);
    cpu.set_sp(0xD9DB);
    cpu.set_bp(0xFB11);
    cpu.set_si(0x1299);
    cpu.set_di(0x173F);
    cpu.set_ip(0x155D);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8873D, 0x89);
    machine.mem_store_byte(0x8873E, 0xA7);
    machine.mem_store_byte(0x8873F, 0x53);
    machine.mem_store_byte(0x88740, 0x8F);
    machine.mem_store_byte(0x88741, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1561);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8873D), 0x89);
    EXPECT_EQ(memory.load8(0x8873E), 0xA7);
    EXPECT_EQ(memory.load8(0x8873F), 0x53);
    EXPECT_EQ(memory.load8(0x88740), 0x8F);
    EXPECT_EQ(memory.load8(0x88741), 0x90);
    EXPECT_EQ(memory.load8(0x245F8), 0xDB);
    EXPECT_EQ(memory.load8(0x245F9), 0xD9);
}


TEST_F(MachineTest, mov_word_es_AA78h_ax)
{
    // Initial CPU State
    cpu.set_ax(0x492C);
    cpu.set_bx(0x0B55);
    cpu.set_cx(0xC9E0);
    cpu.set_dx(0xDFEE);
    cpu.set_cs(0xF2D4);
    cpu.set_ss(0x12B8);
    cpu.set_ds(0x4DA6);
    cpu.set_es(0x6F34);
    cpu.set_sp(0x2276);
    cpu.set_bp(0xB939);
    cpu.set_si(0xDDA4);
    cpu.set_di(0x3D85);
    cpu.set_ip(0x16B8);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF43F8, 0x26);
    machine.mem_store_byte(0xF43F9, 0xA3);
    machine.mem_store_byte(0xF43FA, 0x78);
    machine.mem_store_byte(0xF43FB, 0xAA);
    machine.mem_store_byte(0xF43FC, 0x90);
    machine.mem_store_byte(0xF43FD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x16BC);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF43F8), 0x26);
    EXPECT_EQ(memory.load8(0xF43F9), 0xA3);
    EXPECT_EQ(memory.load8(0xF43FA), 0x78);
    EXPECT_EQ(memory.load8(0xF43FB), 0xAA);
    EXPECT_EQ(memory.load8(0xF43FC), 0x90);
    EXPECT_EQ(memory.load8(0xF43FD), 0x90);
    EXPECT_EQ(memory.load8(0x79DB8), 0x2C);
    EXPECT_EQ(memory.load8(0x79DB9), 0x49);
}


TEST_F(MachineTest, mov_word_ss_bp_F7h_671Dh)
{
    // Initial CPU State
    cpu.set_ax(0xC9E4);
    cpu.set_bx(0x85D4);
    cpu.set_cx(0xE974);
    cpu.set_dx(0x3FCE);
    cpu.set_cs(0x14D2);
    cpu.set_ss(0x8E6B);
    cpu.set_ds(0xAFC9);
    cpu.set_es(0x600A);
    cpu.set_sp(0x60DE);
    cpu.set_bp(0x165A);
    cpu.set_si(0x6866);
    cpu.set_di(0xE867);
    cpu.set_ip(0xEA80);
    cpu.set_flags(0xF493);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x237A0, 0xC7);
    machine.mem_store_byte(0x237A1, 0x96);
    machine.mem_store_byte(0x237A2, 0x09);
    machine.mem_store_byte(0x237A3, 0xFF);
    machine.mem_store_byte(0x237A4, 0x1D);
    machine.mem_store_byte(0x237A5, 0x67);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEA86);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x237A0), 0xC7);
    EXPECT_EQ(memory.load8(0x237A1), 0x96);
    EXPECT_EQ(memory.load8(0x237A2), 0x09);
    EXPECT_EQ(memory.load8(0x237A3), 0xFF);
    EXPECT_EQ(memory.load8(0x237A4), 0x1D);
    EXPECT_EQ(memory.load8(0x237A5), 0x67);
    EXPECT_EQ(memory.load8(0x8FC13), 0x1D);
    EXPECT_EQ(memory.load8(0x8FC14), 0x67);
}
