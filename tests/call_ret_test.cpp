#include "fixture.h"

//
// call 4D75h
//
TEST_F(MachineTest, call_4D75h)
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
    machine.mem_store_byte(0xACA7B, 0xE8);
    machine.mem_store_byte(0xACA7C, 0x71);
    machine.mem_store_byte(0xACA7D, 0x4D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x5F95);
    EXPECT_EQ(cpu.get_ip(), 0x352F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x29095), 0xBE);
    EXPECT_EQ(memory.load8(0x29096), 0xE7);
}

//
// call word [cs:bx+55C0h]
//
TEST_F(MachineTest, call_word_cs_bx_55C0h)
{
    // Initial CPU State
    cpu.set_ax(0x25EC);
    cpu.set_bx(0x3105);
    cpu.set_cx(0x9364);
    cpu.set_dx(0xBBF0);
    cpu.set_cs(0xCE07);
    cpu.set_ss(0x3251);
    cpu.set_ds(0xA354);
    cpu.set_es(0x7894);
    cpu.set_sp(0x3FA0);
    cpu.set_bp(0xCA67);
    cpu.set_si(0x8D40);
    cpu.set_di(0xFEB1);
    cpu.set_ip(0x78D9);
    cpu.set_flags(0xF447);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD5949, 0x2E);
    machine.mem_store_byte(0xD594A, 0xFF);
    machine.mem_store_byte(0xD594B, 0x97);
    machine.mem_store_byte(0xD594C, 0xC0);
    machine.mem_store_byte(0xD594D, 0x55);
    machine.mem_store_byte(0xD6735, 0xFA);
    machine.mem_store_byte(0xD6736, 0xAB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x3F9E);
    EXPECT_EQ(cpu.get_ip(), 0xABFA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x364AE), 0xDE);
    EXPECT_EQ(memory.load8(0x364AF), 0x78);
}

//
// callf 76C0h:A4E4h
//
TEST_F(MachineTest, callf_76C0h_A4E4h)
{
    // Initial CPU State
    cpu.set_ax(0xC408);
    cpu.set_bx(0x53CC);
    cpu.set_cx(0x279E);
    cpu.set_dx(0x5714);
    cpu.set_cs(0x055B);
    cpu.set_ss(0xD083);
    cpu.set_ds(0xAB5D);
    cpu.set_es(0x2DB1);
    cpu.set_sp(0x4BBC);
    cpu.set_bp(0x3A51);
    cpu.set_si(0x7DAB);
    cpu.set_di(0xEBE5);
    cpu.set_ip(0xFA6F);
    cpu.set_flags(0xF003);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1501F, 0x9A);
    machine.mem_store_byte(0x15020, 0xE4);
    machine.mem_store_byte(0x15021, 0xA4);
    machine.mem_store_byte(0x15022, 0xC0);
    machine.mem_store_byte(0x15023, 0x76);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x76C0);
    EXPECT_EQ(cpu.get_sp(), 0x4BB8);
    EXPECT_EQ(cpu.get_ip(), 0xA4E4);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD53EA), 0x5B);
    EXPECT_EQ(memory.load8(0xD53EB), 0x05);
    EXPECT_EQ(memory.load8(0xD53E8), 0x74);
    EXPECT_EQ(memory.load8(0xD53E9), 0xFA);
}

//
// callf word [ds:bx+di]
//
TEST_F(MachineTest, callf_word_ds_bx_di)
{
    // Initial CPU State
    cpu.set_ax(0xF176);
    cpu.set_bx(0x147B);
    cpu.set_cx(0x6FE2);
    cpu.set_dx(0x4183);
    cpu.set_cs(0xE2B7);
    cpu.set_ss(0x59B0);
    cpu.set_ds(0xB511);
    cpu.set_es(0xB30D);
    cpu.set_sp(0xD040);
    cpu.set_bp(0xA92A);
    cpu.set_si(0x5CD3);
    cpu.set_di(0xB72B);
    cpu.set_ip(0x203E);
    cpu.set_flags(0xF483);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE4BAE, 0xFF);
    machine.mem_store_byte(0xE4BAF, 0x19);
    machine.mem_store_byte(0xE4BB0, 0x90);
    machine.mem_store_byte(0xE4BB1, 0x90);
    machine.mem_store_byte(0xC1CB6, 0x7B);
    machine.mem_store_byte(0xC1CB7, 0x10);
    machine.mem_store_byte(0xC1CB8, 0x93);
    machine.mem_store_byte(0xC1CB9, 0xDD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0xDD93);
    EXPECT_EQ(cpu.get_sp(), 0xD03C);
    EXPECT_EQ(cpu.get_ip(), 0x107B);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x66B3E), 0xB7);
    EXPECT_EQ(memory.load8(0x66B3F), 0xE2);
    EXPECT_EQ(memory.load8(0x66B3C), 0x40);
    EXPECT_EQ(memory.load8(0x66B3D), 0x20);
}

//
// retf
//
TEST_F(MachineTest, retf)
{
    // Initial CPU State
    cpu.set_ax(0x3255);
    cpu.set_bx(0xD5A4);
    cpu.set_cx(0x7142);
    cpu.set_dx(0x8593);
    cpu.set_cs(0x3189);
    cpu.set_ss(0xE317);
    cpu.set_ds(0x06A1);
    cpu.set_es(0xDE1E);
    cpu.set_sp(0x6E63);
    cpu.set_bp(0xEC05);
    cpu.set_si(0x4161);
    cpu.set_di(0x928E);
    cpu.set_ip(0x5124);
    cpu.set_flags(0xF486);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x369B4, 0xCB);
    machine.mem_store_byte(0x369B5, 0x90);
    machine.mem_store_byte(0x369B6, 0x90);
    machine.mem_store_byte(0x369B7, 0x90);
    machine.mem_store_byte(0xE9FD3, 0x0D);
    machine.mem_store_byte(0xE9FD4, 0x50);
    machine.mem_store_byte(0xE9FD5, 0x24);
    machine.mem_store_byte(0xE9FD6, 0xA3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0xA324);
    EXPECT_EQ(cpu.get_sp(), 0x6E67);
    EXPECT_EQ(cpu.get_ip(), 0x500D);

    // Final RAM entries
}

//
// retf 473Dh
//
TEST_F(MachineTest, retf_473Dh)
{
    // Initial CPU State
    cpu.set_ax(0xF6E6);
    cpu.set_bx(0xD83E);
    cpu.set_cx(0x3DB6);
    cpu.set_dx(0x8F01);
    cpu.set_cs(0x672C);
    cpu.set_ss(0x27A9);
    cpu.set_ds(0xAEFD);
    cpu.set_es(0xA8EA);
    cpu.set_sp(0xC7DC);
    cpu.set_bp(0x7EE3);
    cpu.set_si(0x8295);
    cpu.set_di(0xBD28);
    cpu.set_ip(0xA675);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x71935, 0xC8);
    machine.mem_store_byte(0x71936, 0x3D);
    machine.mem_store_byte(0x71937, 0x47);
    machine.mem_store_byte(0x71938, 0x90);
    machine.mem_store_byte(0x3426C, 0xBE);
    machine.mem_store_byte(0x3426D, 0xAF);
    machine.mem_store_byte(0x3426E, 0x2F);
    machine.mem_store_byte(0x3426F, 0x71);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x712F);
    EXPECT_EQ(cpu.get_sp(), 0x0F1D);
    EXPECT_EQ(cpu.get_ip(), 0xAFBE);

    // Final RAM entries
}

//
// retf 6ED3h
//
TEST_F(MachineTest, retf_6ED3h)
{
    // Initial CPU State
    cpu.set_ax(0xFAEE);
    cpu.set_bx(0x402E);
    cpu.set_cx(0x3EFE);
    cpu.set_dx(0xF82D);
    cpu.set_cs(0x2C7F);
    cpu.set_ss(0x04CE);
    cpu.set_ds(0x8242);
    cpu.set_es(0x350D);
    cpu.set_sp(0x027E);
    cpu.set_bp(0x5887);
    cpu.set_si(0x3E55);
    cpu.set_di(0x167B);
    cpu.set_ip(0x15DB);
    cpu.set_flags(0xF816);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2DDCB, 0xCA);
    machine.mem_store_byte(0x2DDCC, 0xD3);
    machine.mem_store_byte(0x2DDCD, 0x6E);
    machine.mem_store_byte(0x2DDCE, 0x90);
    machine.mem_store_byte(0x04F5E, 0x9E);
    machine.mem_store_byte(0x04F5F, 0x22);
    machine.mem_store_byte(0x04F60, 0x52);
    machine.mem_store_byte(0x04F61, 0x4E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x4E52);
    EXPECT_EQ(cpu.get_sp(), 0x7155);
    EXPECT_EQ(cpu.get_ip(), 0x229E);

    // Final RAM entries
}

//
// retn
//
TEST_F(MachineTest, retn)
{
    // Initial CPU State
    cpu.set_ax(0x2A52);
    cpu.set_bx(0x6BC5);
    cpu.set_cx(0x2D7A);
    cpu.set_dx(0x527E);
    cpu.set_cs(0x8B27);
    cpu.set_ss(0x1EBA);
    cpu.set_ds(0x316E);
    cpu.set_es(0x35BF);
    cpu.set_sp(0xEAAF);
    cpu.set_bp(0x4CBF);
    cpu.set_si(0xDEEF);
    cpu.set_di(0x62D6);
    cpu.set_ip(0x5819);
    cpu.set_flags(0xF486);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x90A89, 0xC3);
    machine.mem_store_byte(0x90A8A, 0x90);
    machine.mem_store_byte(0x90A8B, 0x90);
    machine.mem_store_byte(0x90A8C, 0x90);
    machine.mem_store_byte(0x2D64F, 0x4C);
    machine.mem_store_byte(0x2D650, 0xAB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xEAB1);
    EXPECT_EQ(cpu.get_ip(), 0xAB4C);

    // Final RAM entries
}

//
// retn 5706h
//
TEST_F(MachineTest, retn_5706h)
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
    machine.mem_store_byte(0x5069C, 0xC0);
    machine.mem_store_byte(0x5069D, 0x06);
    machine.mem_store_byte(0x5069E, 0x57);
    machine.mem_store_byte(0x5069F, 0x90);
    machine.mem_store_byte(0x3FBE8, 0xE1);
    machine.mem_store_byte(0x3FBE9, 0x45);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x4490);
    EXPECT_EQ(cpu.get_ip(), 0x45E1);

    // Final RAM entries
}

//
// retn D324h
//
TEST_F(MachineTest, retn_D324h)
{
    // Initial CPU State
    cpu.set_ax(0x300C);
    cpu.set_bx(0xC495);
    cpu.set_cx(0x26BC);
    cpu.set_dx(0x7C9E);
    cpu.set_cs(0xAA49);
    cpu.set_ss(0x4A7E);
    cpu.set_ds(0xCE91);
    cpu.set_es(0xC14D);
    cpu.set_sp(0x0DDF);
    cpu.set_bp(0x090A);
    cpu.set_si(0x76F3);
    cpu.set_di(0x28BB);
    cpu.set_ip(0x6A0B);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB0E9B, 0xC2);
    machine.mem_store_byte(0xB0E9C, 0x24);
    machine.mem_store_byte(0xB0E9D, 0xD3);
    machine.mem_store_byte(0xB0E9E, 0x90);
    machine.mem_store_byte(0x4B5BF, 0x90);
    machine.mem_store_byte(0x4B5C0, 0x80);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xE105);
    EXPECT_EQ(cpu.get_ip(), 0x8090);

    // Final RAM entries
}
