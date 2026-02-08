#include "fixture.h"

//
// aaa
//
TEST_F(MachineTest, aaa_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xAC81);
    cpu.set_bx(0x7002);
    cpu.set_cx(0x93C6);
    cpu.set_dx(0x249F);
    cpu.set_cs(0x9CD5);
    cpu.set_ss(0x17BE);
    cpu.set_ds(0x9382);
    cpu.set_es(0x6E4E);
    cpu.set_sp(0x40DC);
    cpu.set_bp(0x6CE4);
    cpu.set_si(0xA562);
    cpu.set_di(0x634D);
    cpu.set_ip(0xC9B8);
    cpu.set_flags(0xF087);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA9708, 0x37);
    machine.mem_store_byte(0xA9709, 0x90);
    machine.mem_store_byte(0xA970A, 0x90);
    machine.mem_store_byte(0xA970B, 0x90);
    machine.mem_store_byte(0xA970C, 0x90);
    machine.mem_store_byte(0xA970D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xAC01);
    EXPECT_EQ(cpu.get_ip(), 0xC9B9);
    EXPECT_FLAGS(0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA9708), 0x37);
    EXPECT_EQ(memory.load8(0xA9709), 0x90);
    EXPECT_EQ(memory.load8(0xA970A), 0x90);
    EXPECT_EQ(memory.load8(0xA970B), 0x90);
    EXPECT_EQ(memory.load8(0xA970C), 0x90);
    EXPECT_EQ(memory.load8(0xA970D), 0x90);
}

//
// aas
//
TEST_F(MachineTest, aas_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x3E73);
    cpu.set_bx(0x546C);
    cpu.set_cx(0x0504);
    cpu.set_dx(0xDB99);
    cpu.set_cs(0x6708);
    cpu.set_ss(0x3F05);
    cpu.set_ds(0x572C);
    cpu.set_es(0xF383);
    cpu.set_sp(0xBA88);
    cpu.set_bp(0x0000);
    cpu.set_si(0x5E6A);
    cpu.set_di(0xFD20);
    cpu.set_ip(0xCEAD);
    cpu.set_flags(0xF807);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x73F2D, 0x3F);
    machine.mem_store_byte(0x73F2E, 0x90);
    machine.mem_store_byte(0x73F2F, 0x90);
    machine.mem_store_byte(0x73F30, 0x90);
    machine.mem_store_byte(0x73F31, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x3E03);
    EXPECT_EQ(cpu.get_ip(), 0xCEAE);
    EXPECT_FLAGS(0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x73F2D), 0x3F);
    EXPECT_EQ(memory.load8(0x73F2E), 0x90);
    EXPECT_EQ(memory.load8(0x73F2F), 0x90);
    EXPECT_EQ(memory.load8(0x73F30), 0x90);
    EXPECT_EQ(memory.load8(0x73F31), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xD51C);
    cpu.set_bx(0xC219);
    cpu.set_cx(0xF928);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x54B0);
    cpu.set_ss(0x8074);
    cpu.set_ds(0x00A6);
    cpu.set_es(0x7F07);
    cpu.set_sp(0x83A2);
    cpu.set_bp(0x84DC);
    cpu.set_si(0xE749);
    cpu.set_di(0x0536);
    cpu.set_ip(0xD2AC);
    cpu.set_flags(0xFC56);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x61DAC, 0x27);
    machine.mem_store_byte(0x61DAD, 0x90);
    machine.mem_store_byte(0x61DAE, 0x90);
    machine.mem_store_byte(0x61DAF, 0x90);
    machine.mem_store_byte(0x61DB0, 0x90);
    machine.mem_store_byte(0x61DB1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD522);
    EXPECT_EQ(cpu.get_ip(), 0xD2AD);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x61DAC), 0x27);
    EXPECT_EQ(memory.load8(0x61DAD), 0x90);
    EXPECT_EQ(memory.load8(0x61DAE), 0x90);
    EXPECT_EQ(memory.load8(0x61DAF), 0x90);
    EXPECT_EQ(memory.load8(0x61DB0), 0x90);
    EXPECT_EQ(memory.load8(0x61DB1), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x8A7B);
    cpu.set_bx(0xAD3F);
    cpu.set_cx(0x46BE);
    cpu.set_dx(0x9EF7);
    cpu.set_cs(0x22FB);
    cpu.set_ss(0x164F);
    cpu.set_ds(0xD041);
    cpu.set_es(0x9DE4);
    cpu.set_sp(0x5A59);
    cpu.set_bp(0x7016);
    cpu.set_si(0xC611);
    cpu.set_di(0x01B6);
    cpu.set_ip(0x6710);
    cpu.set_flags(0xFC56);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x296C0, 0x2F);
    machine.mem_store_byte(0x296C1, 0x90);
    machine.mem_store_byte(0x296C2, 0x90);
    machine.mem_store_byte(0x296C3, 0x90);
    machine.mem_store_byte(0x296C4, 0x90);
    machine.mem_store_byte(0x296C5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8A75);
    EXPECT_EQ(cpu.get_ip(), 0x6711);
    EXPECT_FLAGS(0xF412);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x296C0), 0x2F);
    EXPECT_EQ(memory.load8(0x296C1), 0x90);
    EXPECT_EQ(memory.load8(0x296C2), 0x90);
    EXPECT_EQ(memory.load8(0x296C3), 0x90);
    EXPECT_EQ(memory.load8(0x296C4), 0x90);
    EXPECT_EQ(memory.load8(0x296C5), 0x90);
}

//
// div al
//
TEST_F(MachineTest, div_al_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xAA0A);
    cpu.set_bx(0x15C1);
    cpu.set_cx(0x034A);
    cpu.set_dx(0x85E5);
    cpu.set_cs(0xE1C0);
    cpu.set_ss(0xFF6A);
    cpu.set_ds(0xE3F0);
    cpu.set_es(0x2A4A);
    cpu.set_sp(0x1257);
    cpu.set_bp(0x15BB);
    cpu.set_si(0xD455);
    cpu.set_di(0xA66B);
    cpu.set_ip(0x0E12);
    cpu.set_flags(0xF053);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE2A12, 0x26);
    machine.mem_store_byte(0xE2A13, 0xF6);
    machine.mem_store_byte(0xE2A14, 0xF0);
    machine.mem_store_byte(0xE2A15, 0x90);
    machine.mem_store_byte(0xE2A16, 0x90);
    machine.mem_store_byte(0xE2A17, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x1251);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE2A12), 0x26);
    EXPECT_EQ(memory.load8(0xE2A13), 0xF6);
    EXPECT_EQ(memory.load8(0xE2A14), 0xF0);
    EXPECT_EQ(memory.load8(0xE2A15), 0x90);
    EXPECT_EQ(memory.load8(0xE2A16), 0x90);
    EXPECT_EQ(memory.load8(0xE2A17), 0x90);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x008F5), 0x86 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0x008F6), 0xF0 & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0x008F3), 0xC0);
    EXPECT_EQ(memory.load8(0x008F4), 0xE1);
    EXPECT_EQ(memory.load8(0x008F1), 0x15);
    EXPECT_EQ(memory.load8(0x008F2), 0x0E);
}

//
// div ax
//
TEST_F(MachineTest, div_ax_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x3A4D);
    cpu.set_bx(0xDA8C);
    cpu.set_cx(0x2BA2);
    cpu.set_dx(0xC004);
    cpu.set_cs(0xDF47);
    cpu.set_ss(0x8503);
    cpu.set_ds(0xAD8B);
    cpu.set_es(0x7185);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x1989);
    cpu.set_si(0xC848);
    cpu.set_di(0x0000);
    cpu.set_ip(0xF347);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE7B7, 0x2E);
    machine.mem_store_byte(0xEE7B8, 0xF7);
    machine.mem_store_byte(0xEE7B9, 0xF0);
    machine.mem_store_byte(0xEE7BA, 0x90);
    machine.mem_store_byte(0xEE7BB, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0xFFFA);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF096);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE7B7), 0x2E);
    EXPECT_EQ(memory.load8(0xEE7B8), 0xF7);
    EXPECT_EQ(memory.load8(0xEE7B9), 0xF0);
    EXPECT_EQ(memory.load8(0xEE7BA), 0x90);
    EXPECT_EQ(memory.load8(0xEE7BB), 0x90);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x9502E), 0x96 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0x9502F), 0xF0 & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0x9502C), 0x47);
    EXPECT_EQ(memory.load8(0x9502D), 0xDF);
    EXPECT_EQ(memory.load8(0x9502A), 0x4A);
    EXPECT_EQ(memory.load8(0x9502B), 0xF3);
}

//
// div byte [cs:di-4636h]
//
TEST_F(MachineTest, div_byte_cs_di_4636h_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x23CD);
    cpu.set_bx(0x42DF);
    cpu.set_cx(0xF874);
    cpu.set_dx(0x20D7);
    cpu.set_cs(0xAB5B);
    cpu.set_ss(0xED43);
    cpu.set_ds(0x9E85);
    cpu.set_es(0x1F8D);
    cpu.set_sp(0x9552);
    cpu.set_bp(0x62B2);
    cpu.set_si(0xA017);
    cpu.set_di(0x8B4F);
    cpu.set_ip(0xB066);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB6616, 0x2E);
    machine.mem_store_byte(0xB6617, 0xF6);
    machine.mem_store_byte(0xB6618, 0xB5);
    machine.mem_store_byte(0xB6619, 0xCA);
    machine.mem_store_byte(0xB661A, 0xB9);
    machine.mem_store_byte(0xB661B, 0x90);
    machine.mem_store_byte(0xAFAC9, 0xF2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD325);
    EXPECT_EQ(cpu.get_ip(), 0xB06B);
    EXPECT_FLAGS(0xF087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB6616), 0x2E);
    EXPECT_EQ(memory.load8(0xB6617), 0xF6);
    EXPECT_EQ(memory.load8(0xB6618), 0xB5);
    EXPECT_EQ(memory.load8(0xB6619), 0xCA);
    EXPECT_EQ(memory.load8(0xB661A), 0xB9);
    EXPECT_EQ(memory.load8(0xB661B), 0x90);
    EXPECT_EQ(memory.load8(0xAFAC9), 0xF2);
}

//
// div byte [ds:bx+di+66h]
//
TEST_F(MachineTest, div_byte_ds_bx_di_66h_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x779D);
    cpu.set_bx(0x4373);
    cpu.set_cx(0xF2C6);
    cpu.set_dx(0x8B23);
    cpu.set_cs(0x3936);
    cpu.set_ss(0x7EE9);
    cpu.set_ds(0x590F);
    cpu.set_es(0x1B08);
    cpu.set_sp(0x5704);
    cpu.set_bp(0xB130);
    cpu.set_si(0xFD2C);
    cpu.set_di(0x6B84);
    cpu.set_ip(0xFA39);
    cpu.set_flags(0xF8C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x48D99, 0xF6);
    machine.mem_store_byte(0x48D9A, 0x71);
    machine.mem_store_byte(0x48D9B, 0x66);
    machine.mem_store_byte(0x48D9C, 0x90);
    machine.mem_store_byte(0x48D9D, 0x90);
    machine.mem_store_byte(0x6404D, 0xAA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x15B4);
    EXPECT_EQ(cpu.get_ip(), 0xFA3C);
    EXPECT_FLAGS(0xF012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x48D99), 0xF6);
    EXPECT_EQ(memory.load8(0x48D9A), 0x71);
    EXPECT_EQ(memory.load8(0x48D9B), 0x66);
    EXPECT_EQ(memory.load8(0x48D9C), 0x90);
    EXPECT_EQ(memory.load8(0x48D9D), 0x90);
    EXPECT_EQ(memory.load8(0x6404D), 0xAA);
}

//
// div byte [ss:bp+di-7h]
//
TEST_F(MachineTest, div_byte_ss_bp_di_7h_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xC864);
    cpu.set_bx(0x494A);
    cpu.set_cx(0x0D98);
    cpu.set_dx(0x8EBE);
    cpu.set_cs(0x36A7);
    cpu.set_ss(0xAD46);
    cpu.set_ds(0x462D);
    cpu.set_es(0x72D2);
    cpu.set_sp(0x5B03);
    cpu.set_bp(0xDB2A);
    cpu.set_si(0x0000);
    cpu.set_di(0x5EFA);
    cpu.set_ip(0xB7B7);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x42227, 0x36);
    machine.mem_store_byte(0x42228, 0xF6);
    machine.mem_store_byte(0x42229, 0x73);
    machine.mem_store_byte(0x4222A, 0xF9);
    machine.mem_store_byte(0x4222B, 0x90);
    machine.mem_store_byte(0xB0E7D, 0x5B);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x5AFD);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF812);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x42227), 0x36);
    EXPECT_EQ(memory.load8(0x42228), 0xF6);
    EXPECT_EQ(memory.load8(0x42229), 0x73);
    EXPECT_EQ(memory.load8(0x4222A), 0xF9);
    EXPECT_EQ(memory.load8(0x4222B), 0x90);
    EXPECT_EQ(memory.load8(0xB0E7D), 0x5B);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0xB2F61), 0x12 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0xB2F62), 0xF8 & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0xB2F5F), 0xA7);
    EXPECT_EQ(memory.load8(0xB2F60), 0x36);
    EXPECT_EQ(memory.load8(0xB2F5D), 0xBB);
    EXPECT_EQ(memory.load8(0xB2F5E), 0xB7);
}

//
// div sp
//
TEST_F(MachineTest, div_sp_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x29D1);
    cpu.set_bx(0x8BE9);
    cpu.set_cx(0x521C);
    cpu.set_dx(0x28DD);
    cpu.set_cs(0x269F);
    cpu.set_ss(0x0815);
    cpu.set_ds(0x7444);
    cpu.set_es(0xAD17);
    cpu.set_sp(0x6A7F);
    cpu.set_bp(0x57A8);
    cpu.set_si(0xEA3E);
    cpu.set_di(0x86B4);
    cpu.set_ip(0xECAF);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3569F, 0xF7);
    machine.mem_store_byte(0x356A0, 0xF4);
    machine.mem_store_byte(0x356A1, 0x90);
    machine.mem_store_byte(0x356A2, 0x90);
    machine.mem_store_byte(0x356A3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x623B);
    EXPECT_EQ(cpu.get_dx(), 0x008C);
    EXPECT_EQ(cpu.get_ip(), 0xECB1);
    EXPECT_FLAGS(0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3569F), 0xF7);
    EXPECT_EQ(memory.load8(0x356A0), 0xF4);
    EXPECT_EQ(memory.load8(0x356A1), 0x90);
    EXPECT_EQ(memory.load8(0x356A2), 0x90);
    EXPECT_EQ(memory.load8(0x356A3), 0x90);
}

//
// div word [ds:di]
//
TEST_F(MachineTest, div_word_ds_di_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x16A9);
    cpu.set_bx(0x3027);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x2548);
    cpu.set_ss(0x08C5);
    cpu.set_ds(0xC9CC);
    cpu.set_es(0x699C);
    cpu.set_sp(0xBB3B);
    cpu.set_bp(0xA1C5);
    cpu.set_si(0xB704);
    cpu.set_di(0x9EC4);
    cpu.set_ip(0xFC55);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x350D5, 0xF7);
    machine.mem_store_byte(0x350D6, 0x35);
    machine.mem_store_byte(0x350D7, 0x90);
    machine.mem_store_byte(0x350D8, 0x90);
    machine.mem_store_byte(0x350D9, 0x90);
    machine.mem_store_byte(0xD3B84, 0x26);
    machine.mem_store_byte(0xD3B85, 0xBC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0000);
    EXPECT_EQ(cpu.get_dx(), 0x16A9);
    EXPECT_EQ(cpu.get_ip(), 0xFC57);
    EXPECT_FLAGS(0xF003);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x350D5), 0xF7);
    EXPECT_EQ(memory.load8(0x350D6), 0x35);
    EXPECT_EQ(memory.load8(0x350D7), 0x90);
    EXPECT_EQ(memory.load8(0x350D8), 0x90);
    EXPECT_EQ(memory.load8(0x350D9), 0x90);
    EXPECT_EQ(memory.load8(0xD3B84), 0x26);
    EXPECT_EQ(memory.load8(0xD3B85), 0xBC);
}

//
// div word [ss:bp+di-5Bh]
//
TEST_F(MachineTest, div_word_ss_bp_di_5Bh_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x2927);
    cpu.set_cx(0xE63E);
    cpu.set_dx(0x391C);
    cpu.set_cs(0x4ED6);
    cpu.set_ss(0x513A);
    cpu.set_ds(0xAABA);
    cpu.set_es(0x6D2D);
    cpu.set_sp(0x1DD5);
    cpu.set_bp(0x06A8);
    cpu.set_si(0x8A8A);
    cpu.set_di(0x407D);
    cpu.set_ip(0x676E);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x554CE, 0xF7);
    machine.mem_store_byte(0x554CF, 0x73);
    machine.mem_store_byte(0x554D0, 0xA5);
    machine.mem_store_byte(0x554D1, 0x90);
    machine.mem_store_byte(0x554D2, 0x90);
    machine.mem_store_byte(0x554D3, 0x90);
    machine.mem_store_byte(0x55A6A, 0x35);
    machine.mem_store_byte(0x55A6B, 0x59);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xA3E3);
    EXPECT_EQ(cpu.get_dx(), 0x2701);
    EXPECT_EQ(cpu.get_ip(), 0x6771);
    EXPECT_FLAGS(0xF802);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x554CE), 0xF7);
    EXPECT_EQ(memory.load8(0x554CF), 0x73);
    EXPECT_EQ(memory.load8(0x554D0), 0xA5);
    EXPECT_EQ(memory.load8(0x554D1), 0x90);
    EXPECT_EQ(memory.load8(0x554D2), 0x90);
    EXPECT_EQ(memory.load8(0x554D3), 0x90);
    EXPECT_EQ(memory.load8(0x55A6A), 0x35);
    EXPECT_EQ(memory.load8(0x55A6B), 0x59);
}

//
// idiv byte [ds:bx+di]
//
TEST_F(MachineTest, idiv_byte_ds_bx_di_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x60E7);
    cpu.set_bx(0x8C38);
    cpu.set_cx(0xBB5E);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xF28F);
    cpu.set_ss(0x7E36);
    cpu.set_ds(0x33DE);
    cpu.set_es(0x843F);
    cpu.set_sp(0x3F9A);
    cpu.set_bp(0x75A7);
    cpu.set_si(0x0000);
    cpu.set_di(0xDFDD);
    cpu.set_ip(0x8DEA);
    cpu.set_flags(0xF4C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFB6DA, 0xF3);
    machine.mem_store_byte(0xFB6DB, 0xF6);
    machine.mem_store_byte(0xFB6DC, 0x39);
    machine.mem_store_byte(0xFB6DD, 0x90);
    machine.mem_store_byte(0xFB6DE, 0x90);
    machine.mem_store_byte(0xFB6DF, 0x90);
    machine.mem_store_byte(0x3A9F5, 0x73);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x3F94);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xFC02);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFB6DA), 0xF3);
    EXPECT_EQ(memory.load8(0xFB6DB), 0xF6);
    EXPECT_EQ(memory.load8(0xFB6DC), 0x39);
    EXPECT_EQ(memory.load8(0xFB6DD), 0x90);
    EXPECT_EQ(memory.load8(0xFB6DE), 0x90);
    EXPECT_EQ(memory.load8(0xFB6DF), 0x90);
    EXPECT_EQ(memory.load8(0x3A9F5), 0x73);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x822F8), 0x02 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0x822F9), 0xFC & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0x822F6), 0x8F);
    EXPECT_EQ(memory.load8(0x822F7), 0xF2);
    EXPECT_EQ(memory.load8(0x822F4), 0xED);
    EXPECT_EQ(memory.load8(0x822F5), 0x8D);
}

//
// idiv byte [ds:di]
//
TEST_F(MachineTest, idiv_byte_ds_di_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x5C1D);
    cpu.set_bx(0xE567);
    cpu.set_cx(0x9C76);
    cpu.set_dx(0xED1E);
    cpu.set_cs(0x1154);
    cpu.set_ss(0x9AB4);
    cpu.set_ds(0xBF00);
    cpu.set_es(0x997B);
    cpu.set_sp(0x4622);
    cpu.set_bp(0x0602);
    cpu.set_si(0x3BE3);
    cpu.set_di(0x0000);
    cpu.set_ip(0x58DA);
    cpu.set_flags(0xFC46);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x16E1A, 0xF6);
    machine.mem_store_byte(0x16E1B, 0x3D);
    machine.mem_store_byte(0x16E1C, 0x90);
    machine.mem_store_byte(0x16E1D, 0x90);
    machine.mem_store_byte(0x16E1E, 0x90);
    machine.mem_store_byte(0x16E1F, 0x90);
    machine.mem_store_byte(0xBF000, 0x03);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x461C);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x16E1A), 0xF6);
    EXPECT_EQ(memory.load8(0x16E1B), 0x3D);
    EXPECT_EQ(memory.load8(0x16E1C), 0x90);
    EXPECT_EQ(memory.load8(0x16E1D), 0x90);
    EXPECT_EQ(memory.load8(0x16E1E), 0x90);
    EXPECT_EQ(memory.load8(0x16E1F), 0x90);
    EXPECT_EQ(memory.load8(0xBF000), 0x03);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x9F160), 0x06 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0x9F161), 0xF4 & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0x9F15E), 0x54);
    EXPECT_EQ(memory.load8(0x9F15F), 0x11);
    EXPECT_EQ(memory.load8(0x9F15C), 0xDC);
    EXPECT_EQ(memory.load8(0x9F15D), 0x58);
}

//
// idiv byte [ds:si+5Fh]
//
TEST_F(MachineTest, idiv_byte_ds_si_5Fh_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xED70);
    cpu.set_bx(0x5038);
    cpu.set_cx(0xD7E0);
    cpu.set_dx(0x023B);
    cpu.set_cs(0xD8BA);
    cpu.set_ss(0x0394);
    cpu.set_ds(0x7005);
    cpu.set_es(0xD004);
    cpu.set_sp(0xCCDB);
    cpu.set_bp(0xC53B);
    cpu.set_si(0x38FA);
    cpu.set_di(0x3C9F);
    cpu.set_ip(0x56B0);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDE250, 0xF6);
    machine.mem_store_byte(0xDE251, 0x7C);
    machine.mem_store_byte(0xDE252, 0x5F);
    machine.mem_store_byte(0xDE253, 0x90);
    machine.mem_store_byte(0xDE254, 0x90);
    machine.mem_store_byte(0xDE255, 0x90);
    machine.mem_store_byte(0x739A9, 0xC9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xEA56);
    EXPECT_EQ(cpu.get_ip(), 0x56B3);
    EXPECT_FLAGS(0xF092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDE250), 0xF6);
    EXPECT_EQ(memory.load8(0xDE251), 0x7C);
    EXPECT_EQ(memory.load8(0xDE252), 0x5F);
    EXPECT_EQ(memory.load8(0xDE253), 0x90);
    EXPECT_EQ(memory.load8(0xDE254), 0x90);
    EXPECT_EQ(memory.load8(0xDE255), 0x90);
    EXPECT_EQ(memory.load8(0x739A9), 0xC9);
}

//
// idiv byte [ds:si+778h]
//
TEST_F(MachineTest, idiv_byte_ds_si_778h_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x3FBF);
    cpu.set_bx(0x24E0);
    cpu.set_cx(0xF2B6);
    cpu.set_dx(0x26AA);
    cpu.set_cs(0x94E7);
    cpu.set_ss(0x29EA);
    cpu.set_ds(0xF44A);
    cpu.set_es(0x8B29);
    cpu.set_sp(0xF8C0);
    cpu.set_bp(0x3435);
    cpu.set_si(0x2597);
    cpu.set_di(0x897D);
    cpu.set_ip(0xD6C8);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA2538, 0xF6);
    machine.mem_store_byte(0xA2539, 0xBC);
    machine.mem_store_byte(0xA253A, 0x78);
    machine.mem_store_byte(0xA253B, 0x07);
    machine.mem_store_byte(0xA253C, 0x90);
    machine.mem_store_byte(0xA253D, 0x90);
    machine.mem_store_byte(0xF71AF, 0xE4);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0xF8BA);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA2538), 0xF6);
    EXPECT_EQ(memory.load8(0xA2539), 0xBC);
    EXPECT_EQ(memory.load8(0xA253A), 0x78);
    EXPECT_EQ(memory.load8(0xA253B), 0x07);
    EXPECT_EQ(memory.load8(0xA253C), 0x90);
    EXPECT_EQ(memory.load8(0xA253D), 0x90);
    EXPECT_EQ(memory.load8(0xF71AF), 0xE4);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x3975E), 0x02);
    EXPECT_EQ(memory.load8(0x3975F), 0xF4);
    EXPECT_EQ(memory.load8(0x3975C), 0xE7);
    EXPECT_EQ(memory.load8(0x3975D), 0x94);
    EXPECT_EQ(memory.load8(0x3975A), 0xCC);
    EXPECT_EQ(memory.load8(0x3975B), 0xD6);
}

//
// idiv dh
//
TEST_F(MachineTest, idiv_dh_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xC635);
    cpu.set_bx(0x6D9E);
    cpu.set_cx(0xEED8);
    cpu.set_dx(0x4435);
    cpu.set_cs(0x1830);
    cpu.set_ss(0xD173);
    cpu.set_ds(0xCB22);
    cpu.set_es(0xACEC);
    cpu.set_sp(0x3A15);
    cpu.set_bp(0x56C3);
    cpu.set_si(0x72CD);
    cpu.set_di(0x0000);
    cpu.set_ip(0x8ECF);
    cpu.set_flags(0xF443);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x211CF, 0xF3);
    machine.mem_store_byte(0x211D0, 0xF6);
    machine.mem_store_byte(0x211D1, 0xFE);
    machine.mem_store_byte(0x211D2, 0x90);
    machine.mem_store_byte(0x211D3, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x3A0F);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x211CF), 0xF3);
    EXPECT_EQ(memory.load8(0x211D0), 0xF6);
    EXPECT_EQ(memory.load8(0x211D1), 0xFE);
    EXPECT_EQ(memory.load8(0x211D2), 0x90);
    EXPECT_EQ(memory.load8(0x211D3), 0x90);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0xD5143), 0x06 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0xD5144), 0xF4 & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0xD5141), 0x30);
    EXPECT_EQ(memory.load8(0xD5142), 0x18);
    EXPECT_EQ(memory.load8(0xD513F), 0xD2);
    EXPECT_EQ(memory.load8(0xD5140), 0x8E);
}

//
// idiv word [cs:bp-3737h]
//
TEST_F(MachineTest, idiv_word_cs_bp_3737h_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x8BF1);
    cpu.set_bx(0x8D9F);
    cpu.set_cx(0x23EA);
    cpu.set_dx(0xFDBF);
    cpu.set_cs(0x8670);
    cpu.set_ss(0x150E);
    cpu.set_ds(0x2F20);
    cpu.set_es(0x0DF0);
    cpu.set_sp(0x5F4F);
    cpu.set_bp(0x5AF6);
    cpu.set_si(0x0000);
    cpu.set_di(0xF9FB);
    cpu.set_ip(0x657F);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8CC7F, 0x2E);
    machine.mem_store_byte(0x8CC80, 0xF7);
    machine.mem_store_byte(0x8CC81, 0xBE);
    machine.mem_store_byte(0x8CC82, 0xC9);
    machine.mem_store_byte(0x8CC83, 0xC8);
    machine.mem_store_byte(0x88ABF, 0x1F);
    machine.mem_store_byte(0x88AC0, 0xCD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0B54);
    EXPECT_EQ(cpu.get_dx(), 0xE8C5);
    EXPECT_EQ(cpu.get_ip(), 0x6584);
    EXPECT_FLAGS(0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8CC7F), 0x2E);
    EXPECT_EQ(memory.load8(0x8CC80), 0xF7);
    EXPECT_EQ(memory.load8(0x8CC81), 0xBE);
    EXPECT_EQ(memory.load8(0x8CC82), 0xC9);
    EXPECT_EQ(memory.load8(0x8CC83), 0xC8);
    EXPECT_EQ(memory.load8(0x88ABF), 0x1F);
    EXPECT_EQ(memory.load8(0x88AC0), 0xCD);
}

//
// idiv word [ss:bp+di]
//
TEST_F(MachineTest, idiv_word_ss_bp_di_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xE221);
    cpu.set_bx(0x8521);
    cpu.set_cx(0x5A6C);
    cpu.set_dx(0xE87F);
    cpu.set_cs(0x23C0);
    cpu.set_ss(0x2A5D);
    cpu.set_ds(0x3F4E);
    cpu.set_es(0x40E0);
    cpu.set_sp(0x73DF);
    cpu.set_bp(0x0000);
    cpu.set_si(0x84B1);
    cpu.set_di(0x0000);
    cpu.set_ip(0xA42C);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2E02C, 0xF7);
    machine.mem_store_byte(0x2E02D, 0x3B);
    machine.mem_store_byte(0x2E02E, 0x90);
    machine.mem_store_byte(0x2E02F, 0x90);
    machine.mem_store_byte(0x2E030, 0x90);
    machine.mem_store_byte(0x2E031, 0x90);
    machine.mem_store_byte(0x2A5D0, 0x19);
    machine.mem_store_byte(0x2A5D1, 0xA4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x4176);
    EXPECT_EQ(cpu.get_dx(), 0xE59B);
    EXPECT_EQ(cpu.get_ip(), 0xA42E);
    EXPECT_FLAGS(0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2E02C), 0xF7);
    EXPECT_EQ(memory.load8(0x2E02D), 0x3B);
    EXPECT_EQ(memory.load8(0x2E02E), 0x90);
    EXPECT_EQ(memory.load8(0x2E02F), 0x90);
    EXPECT_EQ(memory.load8(0x2E030), 0x90);
    EXPECT_EQ(memory.load8(0x2E031), 0x90);
    EXPECT_EQ(memory.load8(0x2A5D0), 0x19);
    EXPECT_EQ(memory.load8(0x2A5D1), 0xA4);
}

//
// idiv word [ss:bp+si+16h]
//
TEST_F(MachineTest, idiv_word_ss_bp_si_16h_batch4)
{
    // Initial CPU State
    cpu.set_ax(0xBEF8);
    cpu.set_bx(0x3650);
    cpu.set_cx(0x2162);
    cpu.set_dx(0xD88F);
    cpu.set_cs(0x8D56);
    cpu.set_ss(0x3931);
    cpu.set_ds(0xC770);
    cpu.set_es(0xBC0B);
    cpu.set_sp(0x47E9);
    cpu.set_bp(0xD4D7);
    cpu.set_si(0x2031);
    cpu.set_di(0x7EE2);
    cpu.set_ip(0x7C80);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x951E0, 0x36);
    machine.mem_store_byte(0x951E1, 0xF7);
    machine.mem_store_byte(0x951E2, 0x7A);
    machine.mem_store_byte(0x951E3, 0x16);
    machine.mem_store_byte(0x951E4, 0x90);
    machine.mem_store_byte(0x951E5, 0x90);
    machine.mem_store_byte(0x4882E, 0x44);
    machine.mem_store_byte(0x4882F, 0x37);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x47E3);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x951E0), 0x36);
    EXPECT_EQ(memory.load8(0x951E1), 0xF7);
    EXPECT_EQ(memory.load8(0x951E2), 0x7A);
    EXPECT_EQ(memory.load8(0x951E3), 0x16);
    EXPECT_EQ(memory.load8(0x951E4), 0x90);
    EXPECT_EQ(memory.load8(0x951E5), 0x90);
    EXPECT_EQ(memory.load8(0x4882E), 0x44);
    EXPECT_EQ(memory.load8(0x4882F), 0x37);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x3DAF7), 0x12 & ~cpu.u_flags());
    EXPECT_EQ(memory.load8(0x3DAF8), 0xF0 & ~(cpu.u_flags() >> 8));
    EXPECT_EQ(memory.load8(0x3DAF5), 0x56);
    EXPECT_EQ(memory.load8(0x3DAF6), 0x8D);
    EXPECT_EQ(memory.load8(0x3DAF3), 0x84);
    EXPECT_EQ(memory.load8(0x3DAF4), 0x7C);
}

//
// rcl byte [ds:bp+di-1180h], cl
//
TEST_F(MachineTest, rcl_byte_ds_bp_di_1180h_cl_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x00C2);
    cpu.set_bx(0x7391);
    cpu.set_cx(0xBE28);
    cpu.set_dx(0x81CC);
    cpu.set_cs(0x25A5);
    cpu.set_ss(0x58BD);
    cpu.set_ds(0x61A8);
    cpu.set_es(0x7CF7);
    cpu.set_sp(0x1AB9);
    cpu.set_bp(0xCECB);
    cpu.set_si(0x179C);
    cpu.set_di(0xC0A7);
    cpu.set_ip(0x23D8);
    cpu.set_flags(0xF4C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x27E28, 0x3E);
    machine.mem_store_byte(0x27E29, 0xD2);
    machine.mem_store_byte(0x27E2A, 0x93);
    machine.mem_store_byte(0x27E2B, 0x80);
    machine.mem_store_byte(0x27E2C, 0xEE);
    machine.mem_store_byte(0x27E2D, 0x90);
    machine.mem_store_byte(0x69872, 0x89);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x23DD);
    EXPECT_FLAGS(0xFCC6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x27E28), 0x3E);
    EXPECT_EQ(memory.load8(0x27E29), 0xD2);
    EXPECT_EQ(memory.load8(0x27E2A), 0x93);
    EXPECT_EQ(memory.load8(0x27E2B), 0x80);
    EXPECT_EQ(memory.load8(0x27E2C), 0xEE);
    EXPECT_EQ(memory.load8(0x27E2D), 0x90);
    EXPECT_EQ(memory.load8(0x69872), 0x9C);
}

//
// rcl di, cl
//
TEST_F(MachineTest, rcl_di_cl_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x548C);
    cpu.set_bx(0xDD33);
    cpu.set_cx(0x933E);
    cpu.set_dx(0x7CA4);
    cpu.set_cs(0x28F2);
    cpu.set_ss(0x95BD);
    cpu.set_ds(0x8644);
    cpu.set_es(0x3D0A);
    cpu.set_sp(0xD87B);
    cpu.set_bp(0x08CD);
    cpu.set_si(0x4A29);
    cpu.set_di(0xEE18);
    cpu.set_ip(0x05CE);
    cpu.set_flags(0xF493);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x294EE, 0xD3);
    machine.mem_store_byte(0x294EF, 0xD7);
    machine.mem_store_byte(0x294F0, 0x90);
    machine.mem_store_byte(0x294F1, 0x90);
    machine.mem_store_byte(0x294F2, 0x90);
    machine.mem_store_byte(0x294F3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xC7B8);
    EXPECT_EQ(cpu.get_ip(), 0x05D0);
    EXPECT_FLAGS(0xFC92);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x294EE), 0xD3);
    EXPECT_EQ(memory.load8(0x294EF), 0xD7);
    EXPECT_EQ(memory.load8(0x294F0), 0x90);
    EXPECT_EQ(memory.load8(0x294F1), 0x90);
    EXPECT_EQ(memory.load8(0x294F2), 0x90);
    EXPECT_EQ(memory.load8(0x294F3), 0x90);
}

//
// rcl word [ds:bp+di+687Eh], cl
//
TEST_F(MachineTest, rcl_word_ds_bp_di_687Eh_cl_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x8B27);
    cpu.set_bx(0x35E6);
    cpu.set_cx(0xD71E);
    cpu.set_dx(0xE8E6);
    cpu.set_cs(0x50FF);
    cpu.set_ss(0x375F);
    cpu.set_ds(0x5392);
    cpu.set_es(0x4F58);
    cpu.set_sp(0x6712);
    cpu.set_bp(0x4F6B);
    cpu.set_si(0x7CDD);
    cpu.set_di(0x479D);
    cpu.set_ip(0x6EC8);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x57EB8, 0x3E);
    machine.mem_store_byte(0x57EB9, 0xD3);
    machine.mem_store_byte(0x57EBA, 0x93);
    machine.mem_store_byte(0x57EBB, 0x7E);
    machine.mem_store_byte(0x57EBC, 0x68);
    machine.mem_store_byte(0x57EBD, 0x90);
    machine.mem_store_byte(0x638A6, 0xF5);
    machine.mem_store_byte(0x638A7, 0xD8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6ECD);
    EXPECT_FLAGS(0xFC96);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x57EB8), 0x3E);
    EXPECT_EQ(memory.load8(0x57EB9), 0xD3);
    EXPECT_EQ(memory.load8(0x57EBA), 0x93);
    EXPECT_EQ(memory.load8(0x57EBB), 0x7E);
    EXPECT_EQ(memory.load8(0x57EBC), 0x68);
    EXPECT_EQ(memory.load8(0x57EBD), 0x90);
    EXPECT_EQ(memory.load8(0x638A6), 0x8F);
    EXPECT_EQ(memory.load8(0x638A7), 0xBD);
}

//
// sar byte [ss:bp+si+7D9h], cl
//
TEST_F(MachineTest, sar_byte_ss_bp_si_7D9h_cl_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x25F7);
    cpu.set_bx(0xC9E5);
    cpu.set_cx(0x6104);
    cpu.set_dx(0x2017);
    cpu.set_cs(0xC07A);
    cpu.set_ss(0x6882);
    cpu.set_ds(0x55F0);
    cpu.set_es(0xF543);
    cpu.set_sp(0x4118);
    cpu.set_bp(0xEC92);
    cpu.set_si(0x6D5A);
    cpu.set_di(0xCAC9);
    cpu.set_ip(0x662C);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC6DCC, 0xD2);
    machine.mem_store_byte(0xC6DCD, 0xBA);
    machine.mem_store_byte(0xC6DCE, 0xD9);
    machine.mem_store_byte(0xC6DCF, 0x07);
    machine.mem_store_byte(0xC6DD0, 0x90);
    machine.mem_store_byte(0xC6DD1, 0x90);
    machine.mem_store_byte(0x6E9E5, 0x8F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6630);
    EXPECT_FLAGS(0xF483);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC6DCC), 0xD2);
    EXPECT_EQ(memory.load8(0xC6DCD), 0xBA);
    EXPECT_EQ(memory.load8(0xC6DCE), 0xD9);
    EXPECT_EQ(memory.load8(0xC6DCF), 0x07);
    EXPECT_EQ(memory.load8(0xC6DD0), 0x90);
    EXPECT_EQ(memory.load8(0xC6DD1), 0x90);
    EXPECT_EQ(memory.load8(0x6E9E5), 0xF8);
}

//
// sar word [ds:di], cl
//
TEST_F(MachineTest, sar_word_ds_di_cl_batch4)
{
    // Initial CPU State
    cpu.set_ax(0x8DC3);
    cpu.set_bx(0xAEA6);
    cpu.set_cx(0x0F0E);
    cpu.set_dx(0xAB12);
    cpu.set_cs(0xDCA3);
    cpu.set_ss(0x8D1B);
    cpu.set_ds(0xD9EC);
    cpu.set_es(0x6730);
    cpu.set_sp(0x41D4);
    cpu.set_bp(0x998B);
    cpu.set_si(0x21BA);
    cpu.set_di(0x1446);
    cpu.set_ip(0x4BFF);
    cpu.set_flags(0xF853);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE162F, 0xD3);
    machine.mem_store_byte(0xE1630, 0x3D);
    machine.mem_store_byte(0xE1631, 0x90);
    machine.mem_store_byte(0xE1632, 0x90);
    machine.mem_store_byte(0xE1633, 0x90);
    machine.mem_store_byte(0xDB306, 0x8C);
    machine.mem_store_byte(0xDB307, 0x84);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4C01);
    EXPECT_FLAGS(0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE162F), 0xD3);
    EXPECT_EQ(memory.load8(0xE1630), 0x3D);
    EXPECT_EQ(memory.load8(0xE1631), 0x90);
    EXPECT_EQ(memory.load8(0xE1632), 0x90);
    EXPECT_EQ(memory.load8(0xE1633), 0x90);
    EXPECT_EQ(memory.load8(0xDB306), 0xFE);
    EXPECT_EQ(memory.load8(0xDB307), 0xFF);
}
