#include "fixture.h"

// Tests: pop

TEST_F(MachineTest, pop_ax)
{
    // Initial CPU State
    cpu.set_ax(0x2BA2);
    cpu.set_bx(0x4F78);
    cpu.set_cx(0x010E);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x92C7);
    cpu.set_ss(0xB3BE);
    cpu.set_ds(0x667A);
    cpu.set_es(0x8C59);
    cpu.set_sp(0xBB97);
    cpu.set_bp(0xC5AE);
    cpu.set_si(0x7D56);
    cpu.set_di(0x4987);
    cpu.set_ip(0xD5B6);
    cpu.set_flags(0xF446);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA0226, 0x58);
    machine.mem_store_byte(0xA0227, 0x90);
    machine.mem_store_byte(0xA0228, 0x90);
    machine.mem_store_byte(0xA0229, 0x90);
    machine.mem_store_byte(0xA022A, 0x90);
    machine.mem_store_byte(0xA022B, 0x90);
    machine.mem_store_byte(0xBF777, 0x81);
    machine.mem_store_byte(0xBF778, 0x7D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7D81);
    EXPECT_EQ(cpu.get_sp(), 0xBB99);
    EXPECT_EQ(cpu.get_ip(), 0xD5B7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA0226), 0x58);
    EXPECT_EQ(memory.load8(0xA0227), 0x90);
    EXPECT_EQ(memory.load8(0xA0228), 0x90);
    EXPECT_EQ(memory.load8(0xA0229), 0x90);
    EXPECT_EQ(memory.load8(0xA022A), 0x90);
    EXPECT_EQ(memory.load8(0xA022B), 0x90);
    EXPECT_EQ(memory.load8(0xBF777), 0x81);
    EXPECT_EQ(memory.load8(0xBF778), 0x7D);
}

TEST_F(MachineTest, pop_bp)
{
    // Initial CPU State
    cpu.set_ax(0x1EDB);
    cpu.set_bx(0x9550);
    cpu.set_cx(0xDF80);
    cpu.set_dx(0x810B);
    cpu.set_cs(0xDE67);
    cpu.set_ss(0x6FC0);
    cpu.set_ds(0x3AAB);
    cpu.set_es(0x66C5);
    cpu.set_sp(0x24BB);
    cpu.set_bp(0x5E52);
    cpu.set_si(0xEC5F);
    cpu.set_di(0xDF3F);
    cpu.set_ip(0xC50C);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEAB7C, 0x5D);
    machine.mem_store_byte(0xEAB7D, 0x90);
    machine.mem_store_byte(0xEAB7E, 0x90);
    machine.mem_store_byte(0xEAB7F, 0x90);
    machine.mem_store_byte(0xEAB80, 0x90);
    machine.mem_store_byte(0xEAB81, 0x90);
    machine.mem_store_byte(0x720BB, 0x21);
    machine.mem_store_byte(0x720BC, 0x62);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x24BD);
    EXPECT_EQ(cpu.get_bp(), 0x6221);
    EXPECT_EQ(cpu.get_ip(), 0xC50D);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEAB7C), 0x5D);
    EXPECT_EQ(memory.load8(0xEAB7D), 0x90);
    EXPECT_EQ(memory.load8(0xEAB7E), 0x90);
    EXPECT_EQ(memory.load8(0xEAB7F), 0x90);
    EXPECT_EQ(memory.load8(0xEAB80), 0x90);
    EXPECT_EQ(memory.load8(0xEAB81), 0x90);
    EXPECT_EQ(memory.load8(0x720BB), 0x21);
    EXPECT_EQ(memory.load8(0x720BC), 0x62);
}

TEST_F(MachineTest, pop_bx)
{
    // Initial CPU State
    cpu.set_ax(0xB674);
    cpu.set_bx(0x56B0);
    cpu.set_cx(0xE6B6);
    cpu.set_dx(0x763B);
    cpu.set_cs(0x25A4);
    cpu.set_ss(0xB31D);
    cpu.set_ds(0x40E6);
    cpu.set_es(0x3C8C);
    cpu.set_sp(0x62B3);
    cpu.set_bp(0x675B);
    cpu.set_si(0x4937);
    cpu.set_di(0xD66C);
    cpu.set_ip(0xD6FA);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3313A, 0x5B);
    machine.mem_store_byte(0x3313B, 0x90);
    machine.mem_store_byte(0x3313C, 0x90);
    machine.mem_store_byte(0x3313D, 0x90);
    machine.mem_store_byte(0x3313E, 0x90);
    machine.mem_store_byte(0x3313F, 0x90);
    machine.mem_store_byte(0xB9483, 0x4A);
    machine.mem_store_byte(0xB9484, 0x47);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x474A);
    EXPECT_EQ(cpu.get_sp(), 0x62B5);
    EXPECT_EQ(cpu.get_ip(), 0xD6FB);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3313A), 0x5B);
    EXPECT_EQ(memory.load8(0x3313B), 0x90);
    EXPECT_EQ(memory.load8(0x3313C), 0x90);
    EXPECT_EQ(memory.load8(0x3313D), 0x90);
    EXPECT_EQ(memory.load8(0x3313E), 0x90);
    EXPECT_EQ(memory.load8(0x3313F), 0x90);
    EXPECT_EQ(memory.load8(0xB9483), 0x4A);
    EXPECT_EQ(memory.load8(0xB9484), 0x47);
}

TEST_F(MachineTest, pop_cx)
{
    // Initial CPU State
    cpu.set_ax(0x9871);
    cpu.set_bx(0x0D12);
    cpu.set_cx(0xAA00);
    cpu.set_dx(0x19ED);
    cpu.set_cs(0xFB2D);
    cpu.set_ss(0xF872);
    cpu.set_ds(0x6CEF);
    cpu.set_es(0xED24);
    cpu.set_sp(0x5263);
    cpu.set_bp(0xFE1F);
    cpu.set_si(0x5B61);
    cpu.set_di(0xB515);
    cpu.set_ip(0x321D);
    cpu.set_flags(0xF857);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFE4ED, 0x59);
    machine.mem_store_byte(0xFE4EE, 0x90);
    machine.mem_store_byte(0xFE4EF, 0x90);
    machine.mem_store_byte(0xFE4F0, 0x90);
    machine.mem_store_byte(0xFE4F1, 0x90);
    machine.mem_store_byte(0xFD983, 0xD5);
    machine.mem_store_byte(0xFD984, 0xFC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xFCD5);
    EXPECT_EQ(cpu.get_sp(), 0x5265);
    EXPECT_EQ(cpu.get_ip(), 0x321E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFE4ED), 0x59);
    EXPECT_EQ(memory.load8(0xFE4EE), 0x90);
    EXPECT_EQ(memory.load8(0xFE4EF), 0x90);
    EXPECT_EQ(memory.load8(0xFE4F0), 0x90);
    EXPECT_EQ(memory.load8(0xFE4F1), 0x90);
    EXPECT_EQ(memory.load8(0xFD983), 0xD5);
    EXPECT_EQ(memory.load8(0xFD984), 0xFC);
}

TEST_F(MachineTest, pop_di)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xD0EE);
    cpu.set_dx(0xF0C3);
    cpu.set_cs(0xE67E);
    cpu.set_ss(0xAB05);
    cpu.set_ds(0xE711);
    cpu.set_es(0xEFDF);
    cpu.set_sp(0x4F31);
    cpu.set_bp(0x0248);
    cpu.set_si(0xB527);
    cpu.set_di(0x2379);
    cpu.set_ip(0xE6C9);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF4EA9, 0x5F);
    machine.mem_store_byte(0xF4EAA, 0x90);
    machine.mem_store_byte(0xF4EAB, 0x90);
    machine.mem_store_byte(0xF4EAC, 0x90);
    machine.mem_store_byte(0xF4EAD, 0x90);
    machine.mem_store_byte(0xAFF81, 0x7D);
    machine.mem_store_byte(0xAFF82, 0x6F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x4F33);
    EXPECT_EQ(cpu.get_di(), 0x6F7D);
    EXPECT_EQ(cpu.get_ip(), 0xE6CA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF4EA9), 0x5F);
    EXPECT_EQ(memory.load8(0xF4EAA), 0x90);
    EXPECT_EQ(memory.load8(0xF4EAB), 0x90);
    EXPECT_EQ(memory.load8(0xF4EAC), 0x90);
    EXPECT_EQ(memory.load8(0xF4EAD), 0x90);
    EXPECT_EQ(memory.load8(0xAFF81), 0x7D);
    EXPECT_EQ(memory.load8(0xAFF82), 0x6F);
}

TEST_F(MachineTest, pop_ds)
{
    // Initial CPU State
    cpu.set_ax(0x25ED);
    cpu.set_bx(0x1790);
    cpu.set_cx(0x3C18);
    cpu.set_dx(0xD750);
    cpu.set_cs(0x8C0A);
    cpu.set_ss(0x193A);
    cpu.set_ds(0x2D4D);
    cpu.set_es(0x136B);
    cpu.set_sp(0xD32D);
    cpu.set_bp(0x4E76);
    cpu.set_si(0x4CAE);
    cpu.set_di(0x2B00);
    cpu.set_ip(0xBCD3);
    cpu.set_flags(0xFC03);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97D73, 0x1F);
    machine.mem_store_byte(0x97D74, 0x90);
    machine.mem_store_byte(0x97D75, 0x90);
    machine.mem_store_byte(0x97D76, 0x90);
    machine.mem_store_byte(0x97D77, 0x90);
    machine.mem_store_byte(0x266CD, 0xF1);
    machine.mem_store_byte(0x266CE, 0x5D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ds(), 0x5DF1);
    EXPECT_EQ(cpu.get_sp(), 0xD32F);
    EXPECT_EQ(cpu.get_ip(), 0xBCD4);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x97D73), 0x1F);
    EXPECT_EQ(memory.load8(0x97D74), 0x90);
    EXPECT_EQ(memory.load8(0x97D75), 0x90);
    EXPECT_EQ(memory.load8(0x97D76), 0x90);
    EXPECT_EQ(memory.load8(0x97D77), 0x90);
    EXPECT_EQ(memory.load8(0x266CD), 0xF1);
    EXPECT_EQ(memory.load8(0x266CE), 0x5D);
}

TEST_F(MachineTest, pop_dx)
{
    // Initial CPU State
    cpu.set_ax(0xEF4C);
    cpu.set_bx(0x46C3);
    cpu.set_cx(0x133A);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x6AA1);
    cpu.set_ss(0xC2F6);
    cpu.set_ds(0x587F);
    cpu.set_es(0x48B6);
    cpu.set_sp(0x441C);
    cpu.set_bp(0x4F8F);
    cpu.set_si(0x9300);
    cpu.set_di(0xF6DB);
    cpu.set_ip(0x9554);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x73F64, 0x5A);
    machine.mem_store_byte(0x73F65, 0x90);
    machine.mem_store_byte(0x73F66, 0x90);
    machine.mem_store_byte(0x73F67, 0x90);
    machine.mem_store_byte(0x73F68, 0x90);
    machine.mem_store_byte(0x73F69, 0x90);
    machine.mem_store_byte(0xC737C, 0x6D);
    machine.mem_store_byte(0xC737D, 0xBF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xBF6D);
    EXPECT_EQ(cpu.get_sp(), 0x441E);
    EXPECT_EQ(cpu.get_ip(), 0x9555);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x73F64), 0x5A);
    EXPECT_EQ(memory.load8(0x73F65), 0x90);
    EXPECT_EQ(memory.load8(0x73F66), 0x90);
    EXPECT_EQ(memory.load8(0x73F67), 0x90);
    EXPECT_EQ(memory.load8(0x73F68), 0x90);
    EXPECT_EQ(memory.load8(0x73F69), 0x90);
    EXPECT_EQ(memory.load8(0xC737C), 0x6D);
    EXPECT_EQ(memory.load8(0xC737D), 0xBF);
}

TEST_F(MachineTest, pop_es)
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
    machine.mem_store_byte(0xC4AD2, 0x07);
    machine.mem_store_byte(0xC4AD3, 0x90);
    machine.mem_store_byte(0xC4AD4, 0x90);
    machine.mem_store_byte(0xC4AD5, 0x90);
    machine.mem_store_byte(0xC4AD6, 0x90);
    machine.mem_store_byte(0xC4AD7, 0x90);
    machine.mem_store_byte(0x55808, 0xDC);
    machine.mem_store_byte(0x55809, 0x65);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_es(), 0x65DC);
    EXPECT_EQ(cpu.get_sp(), 0x7CFA);
    EXPECT_EQ(cpu.get_ip(), 0x2FF3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC4AD2), 0x07);
    EXPECT_EQ(memory.load8(0xC4AD3), 0x90);
    EXPECT_EQ(memory.load8(0xC4AD4), 0x90);
    EXPECT_EQ(memory.load8(0xC4AD5), 0x90);
    EXPECT_EQ(memory.load8(0xC4AD6), 0x90);
    EXPECT_EQ(memory.load8(0xC4AD7), 0x90);
    EXPECT_EQ(memory.load8(0x55808), 0xDC);
    EXPECT_EQ(memory.load8(0x55809), 0x65);
}

TEST_F(MachineTest, pop_si)
{
    // Initial CPU State
    cpu.set_ax(0x89FE);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x8324);
    cpu.set_dx(0x3DF4);
    cpu.set_cs(0x6EDF);
    cpu.set_ss(0xF252);
    cpu.set_ds(0x238A);
    cpu.set_es(0xEC78);
    cpu.set_sp(0x8593);
    cpu.set_bp(0x5559);
    cpu.set_si(0x58B2);
    cpu.set_di(0x7FF2);
    cpu.set_ip(0xD136);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7BF26, 0x5E);
    machine.mem_store_byte(0x7BF27, 0x90);
    machine.mem_store_byte(0x7BF28, 0x90);
    machine.mem_store_byte(0x7BF29, 0x90);
    machine.mem_store_byte(0x7BF2A, 0x90);
    machine.mem_store_byte(0x7BF2B, 0x90);
    machine.mem_store_byte(0xFAAB3, 0x7E);
    machine.mem_store_byte(0xFAAB4, 0x7A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x8595);
    EXPECT_EQ(cpu.get_si(), 0x7A7E);
    EXPECT_EQ(cpu.get_ip(), 0xD137);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7BF26), 0x5E);
    EXPECT_EQ(memory.load8(0x7BF27), 0x90);
    EXPECT_EQ(memory.load8(0x7BF28), 0x90);
    EXPECT_EQ(memory.load8(0x7BF29), 0x90);
    EXPECT_EQ(memory.load8(0x7BF2A), 0x90);
    EXPECT_EQ(memory.load8(0x7BF2B), 0x90);
    EXPECT_EQ(memory.load8(0xFAAB3), 0x7E);
    EXPECT_EQ(memory.load8(0xFAAB4), 0x7A);
}

TEST_F(MachineTest, pop_sp)
{
    // Initial CPU State
    cpu.set_ax(0x338F);
    cpu.set_bx(0x4289);
    cpu.set_cx(0xC684);
    cpu.set_dx(0x76F6);
    cpu.set_cs(0x94D9);
    cpu.set_ss(0x4027);
    cpu.set_ds(0x352D);
    cpu.set_es(0x50DE);
    cpu.set_sp(0x76A2);
    cpu.set_bp(0x78C7);
    cpu.set_si(0x3438);
    cpu.set_di(0xB84B);
    cpu.set_ip(0x5B10);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9A8A0, 0x5C);
    machine.mem_store_byte(0x9A8A1, 0x90);
    machine.mem_store_byte(0x9A8A2, 0x90);
    machine.mem_store_byte(0x9A8A3, 0x90);
    machine.mem_store_byte(0x9A8A4, 0x90);
    machine.mem_store_byte(0x9A8A5, 0x90);
    machine.mem_store_byte(0x47912, 0x83);
    machine.mem_store_byte(0x47913, 0x72);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x7283);
    EXPECT_EQ(cpu.get_ip(), 0x5B11);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9A8A0), 0x5C);
    EXPECT_EQ(memory.load8(0x9A8A1), 0x90);
    EXPECT_EQ(memory.load8(0x9A8A2), 0x90);
    EXPECT_EQ(memory.load8(0x9A8A3), 0x90);
    EXPECT_EQ(memory.load8(0x9A8A4), 0x90);
    EXPECT_EQ(memory.load8(0x9A8A5), 0x90);
    EXPECT_EQ(memory.load8(0x47912), 0x83);
    EXPECT_EQ(memory.load8(0x47913), 0x72);
}

TEST_F(MachineTest, pop_ss)
{
    // Initial CPU State
    cpu.set_ax(0x8DA2);
    cpu.set_bx(0xAD90);
    cpu.set_cx(0xA2A4);
    cpu.set_dx(0x384A);
    cpu.set_cs(0x2E77);
    cpu.set_ss(0x4ACC);
    cpu.set_ds(0xAD80);
    cpu.set_es(0xE163);
    cpu.set_sp(0x7580);
    cpu.set_bp(0x0C47);
    cpu.set_si(0xF001);
    cpu.set_di(0x996C);
    cpu.set_ip(0x5136);
    cpu.set_flags(0xFC52);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x338A6, 0x17);
    machine.mem_store_byte(0x338A7, 0x90);
    machine.mem_store_byte(0x338A8, 0x90);
    machine.mem_store_byte(0x338A9, 0x90);
    machine.mem_store_byte(0x338AA, 0x90);
    machine.mem_store_byte(0x338AB, 0x90);
    machine.mem_store_byte(0x52240, 0x42);
    machine.mem_store_byte(0x52241, 0x4B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ss(), 0x4B42);
    EXPECT_EQ(cpu.get_sp(), 0x7582);
    EXPECT_EQ(cpu.get_ip(), 0x5137);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x338A6), 0x17);
    EXPECT_EQ(memory.load8(0x338A7), 0x90);
    EXPECT_EQ(memory.load8(0x338A8), 0x90);
    EXPECT_EQ(memory.load8(0x338A9), 0x90);
    EXPECT_EQ(memory.load8(0x338AA), 0x90);
    EXPECT_EQ(memory.load8(0x338AB), 0x90);
    EXPECT_EQ(memory.load8(0x52240), 0x42);
    EXPECT_EQ(memory.load8(0x52241), 0x4B);
}

TEST_F(MachineTest, pop_word_es_bx_32h)
{
    // Initial CPU State
    cpu.set_ax(0x880D);
    cpu.set_bx(0x9F36);
    cpu.set_cx(0xCE74);
    cpu.set_dx(0xD825);
    cpu.set_cs(0x474F);
    cpu.set_ss(0x719D);
    cpu.set_ds(0x5637);
    cpu.set_es(0xA441);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xE0F5);
    cpu.set_si(0xED89);
    cpu.set_di(0x4038);
    cpu.set_ip(0x029C);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4778C, 0x26);
    machine.mem_store_byte(0x4778D, 0x8F);
    machine.mem_store_byte(0x4778E, 0x57);
    machine.mem_store_byte(0x4778F, 0x32);
    machine.mem_store_byte(0x47790, 0x90);
    machine.mem_store_byte(0x47791, 0x90);
    machine.mem_store_byte(0x719D0, 0x5B);
    machine.mem_store_byte(0x719D1, 0x04);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x0002);
    EXPECT_EQ(cpu.get_ip(), 0x02A0);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4778C), 0x26);
    EXPECT_EQ(memory.load8(0x4778D), 0x8F);
    EXPECT_EQ(memory.load8(0x4778E), 0x57);
    EXPECT_EQ(memory.load8(0x4778F), 0x32);
    EXPECT_EQ(memory.load8(0x47790), 0x90);
    EXPECT_EQ(memory.load8(0x47791), 0x90);
    EXPECT_EQ(memory.load8(0x719D0), 0x5B);
    EXPECT_EQ(memory.load8(0x719D1), 0x04);
    EXPECT_EQ(memory.load8(0xAE378), 0x5B);
    EXPECT_EQ(memory.load8(0xAE379), 0x04);
}
