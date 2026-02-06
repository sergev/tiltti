#include "fixture.h"

//
// mul bl
//
TEST_F(MachineTest, mul_bl)
{
    // Initial CPU State
    cpu.set_ax(0x4F0B);
    cpu.set_bx(0x7AC7);
    cpu.set_cx(0xECC6);
    cpu.set_dx(0x6D2F);
    cpu.set_cs(0xACC3);
    cpu.set_ss(0x08BD);
    cpu.set_ds(0xFABD);
    cpu.set_es(0x9DFD);
    cpu.set_sp(0x8B9A);
    cpu.set_bp(0xA4A9);
    cpu.set_si(0xC241);
    cpu.set_di(0x9F1F);
    cpu.set_ip(0xC3C8);
    cpu.set_flags(0xF816);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB8FF8, 0xF6);
    machine.mem_store_byte(0xB8FF9, 0xE3);
    machine.mem_store_byte(0xB8FFA, 0x90);
    machine.mem_store_byte(0xB8FFB, 0x90);
    machine.mem_store_byte(0xB8FFC, 0x90);
    machine.mem_store_byte(0xB8FFD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x088D);
    EXPECT_EQ(cpu.get_ip(), 0xC3CA);
    EXPECT_EQ(cpu.get_flags(), 0xF803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB8FF8), 0xF6);
    EXPECT_EQ(memory.load8(0xB8FF9), 0xE3);
    EXPECT_EQ(memory.load8(0xB8FFA), 0x90);
    EXPECT_EQ(memory.load8(0xB8FFB), 0x90);
    EXPECT_EQ(memory.load8(0xB8FFC), 0x90);
    EXPECT_EQ(memory.load8(0xB8FFD), 0x90);
}

//
// mul byte [cs:bx+di]
//
TEST_F(MachineTest, mul_byte_cs_bx_di)
{
    // Initial CPU State
    cpu.set_ax(0x2F75);
    cpu.set_bx(0xCDB4);
    cpu.set_cx(0x689C);
    cpu.set_dx(0x8C9E);
    cpu.set_cs(0x5A28);
    cpu.set_ss(0xDB66);
    cpu.set_ds(0xBA2A);
    cpu.set_es(0x2D9F);
    cpu.set_sp(0x3212);
    cpu.set_bp(0x7DCA);
    cpu.set_si(0x5337);
    cpu.set_di(0x3145);
    cpu.set_ip(0x5402);
    cpu.set_flags(0xF406);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5F682, 0x2E);
    machine.mem_store_byte(0x5F683, 0xF6);
    machine.mem_store_byte(0x5F684, 0x21);
    machine.mem_store_byte(0x5F685, 0x90);
    machine.mem_store_byte(0x5F686, 0x90);
    machine.mem_store_byte(0x5F687, 0x90);
    machine.mem_store_byte(0x6A179, 0x1C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0CCC);
    EXPECT_EQ(cpu.get_ip(), 0x5405);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5F682), 0x2E);
    EXPECT_EQ(memory.load8(0x5F683), 0xF6);
    EXPECT_EQ(memory.load8(0x5F684), 0x21);
    EXPECT_EQ(memory.load8(0x5F685), 0x90);
    EXPECT_EQ(memory.load8(0x5F686), 0x90);
    EXPECT_EQ(memory.load8(0x5F687), 0x90);
    EXPECT_EQ(memory.load8(0x6A179), 0x1C);
}

//
// mul byte [es:bx+di-67C4h]
//
TEST_F(MachineTest, mul_byte_es_bx_di_67C4h)
{
    // Initial CPU State
    cpu.set_ax(0x3715);
    cpu.set_bx(0x5297);
    cpu.set_cx(0xD578);
    cpu.set_dx(0x6DCC);
    cpu.set_cs(0xD89E);
    cpu.set_ss(0xB5FE);
    cpu.set_ds(0xFB3A);
    cpu.set_es(0xB19D);
    cpu.set_sp(0xE107);
    cpu.set_bp(0x2A00);
    cpu.set_si(0xA5B8);
    cpu.set_di(0x2837);
    cpu.set_ip(0xB0A2);
    cpu.set_flags(0xFC96);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE3A82, 0x26);
    machine.mem_store_byte(0xE3A83, 0xF6);
    machine.mem_store_byte(0xE3A84, 0xA1);
    machine.mem_store_byte(0xE3A85, 0x3C);
    machine.mem_store_byte(0xE3A86, 0x98);
    machine.mem_store_byte(0xE3A87, 0x90);
    machine.mem_store_byte(0xB2CDA, 0x50);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0690);
    EXPECT_EQ(cpu.get_ip(), 0xB0A7);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE3A82), 0x26);
    EXPECT_EQ(memory.load8(0xE3A83), 0xF6);
    EXPECT_EQ(memory.load8(0xE3A84), 0xA1);
    EXPECT_EQ(memory.load8(0xE3A85), 0x3C);
    EXPECT_EQ(memory.load8(0xE3A86), 0x98);
    EXPECT_EQ(memory.load8(0xE3A87), 0x90);
    EXPECT_EQ(memory.load8(0xB2CDA), 0x50);
}

//
// mul cx
//
TEST_F(MachineTest, mul_cx)
{
    // Initial CPU State
    cpu.set_ax(0x330D);
    cpu.set_bx(0xE9A5);
    cpu.set_cx(0x81FC);
    cpu.set_dx(0xF111);
    cpu.set_cs(0x2D25);
    cpu.set_ss(0xAF55);
    cpu.set_ds(0x1E95);
    cpu.set_es(0x0712);
    cpu.set_sp(0x6CF2);
    cpu.set_bp(0x9BFF);
    cpu.set_si(0x0000);
    cpu.set_di(0x9C00);
    cpu.set_ip(0xF173);
    cpu.set_flags(0xF8C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3C3C3, 0xF7);
    machine.mem_store_byte(0x3C3C4, 0xE1);
    machine.mem_store_byte(0x3C3C5, 0x90);
    machine.mem_store_byte(0x3C3C6, 0x90);
    machine.mem_store_byte(0x3C3C7, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xCDCC);
    EXPECT_EQ(cpu.get_dx(), 0x19EB);
    EXPECT_EQ(cpu.get_ip(), 0xF175);
    EXPECT_EQ(cpu.get_flags(), 0xF807);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3C3C3), 0xF7);
    EXPECT_EQ(memory.load8(0x3C3C4), 0xE1);
    EXPECT_EQ(memory.load8(0x3C3C5), 0x90);
    EXPECT_EQ(memory.load8(0x3C3C6), 0x90);
    EXPECT_EQ(memory.load8(0x3C3C7), 0x90);
}

//
// mul word [ds:bx+di+5C06h]
//
TEST_F(MachineTest, mul_word_ds_bx_di_5C06h)
{
    // Initial CPU State
    cpu.set_ax(0xCDBD);
    cpu.set_bx(0xD399);
    cpu.set_cx(0xFE0A);
    cpu.set_dx(0x7FA6);
    cpu.set_cs(0xC9C9);
    cpu.set_ss(0x10E8);
    cpu.set_ds(0x722C);
    cpu.set_es(0x446F);
    cpu.set_sp(0xDA64);
    cpu.set_bp(0x71DB);
    cpu.set_si(0x9099);
    cpu.set_di(0x0000);
    cpu.set_ip(0xFCD3);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD9963, 0xF7);
    machine.mem_store_byte(0xD9964, 0xA1);
    machine.mem_store_byte(0xD9965, 0x06);
    machine.mem_store_byte(0xD9966, 0x5C);
    machine.mem_store_byte(0xD9967, 0x90);
    machine.mem_store_byte(0x7525F, 0x04);
    machine.mem_store_byte(0x75260, 0xE9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x3BF4);
    EXPECT_EQ(cpu.get_dx(), 0xBB44);
    EXPECT_EQ(cpu.get_ip(), 0xFCD7);
    EXPECT_EQ(cpu.get_flags(), 0xF887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD9963), 0xF7);
    EXPECT_EQ(memory.load8(0xD9964), 0xA1);
    EXPECT_EQ(memory.load8(0xD9965), 0x06);
    EXPECT_EQ(memory.load8(0xD9966), 0x5C);
    EXPECT_EQ(memory.load8(0xD9967), 0x90);
    EXPECT_EQ(memory.load8(0x7525F), 0x04);
    EXPECT_EQ(memory.load8(0x75260), 0xE9);
}

//
// mul word [ds:bx+si]
//
TEST_F(MachineTest, mul_word_ds_bx_si)
{
    // Initial CPU State
    cpu.set_ax(0x4F3A);
    cpu.set_bx(0xD486);
    cpu.set_cx(0x2FCA);
    cpu.set_dx(0xCA79);
    cpu.set_cs(0x7D4E);
    cpu.set_ss(0xD11C);
    cpu.set_ds(0x90AB);
    cpu.set_es(0x6692);
    cpu.set_sp(0x91F1);
    cpu.set_bp(0x342B);
    cpu.set_si(0x5040);
    cpu.set_di(0xA739);
    cpu.set_ip(0xBDC2);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x892A2, 0xF7);
    machine.mem_store_byte(0x892A3, 0x20);
    machine.mem_store_byte(0x892A4, 0x90);
    machine.mem_store_byte(0x892A5, 0x90);
    machine.mem_store_byte(0x892A6, 0x90);
    machine.mem_store_byte(0x892A7, 0x90);
    machine.mem_store_byte(0x92F76, 0xE9);
    machine.mem_store_byte(0x92F77, 0xD0);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x3BCA);
    EXPECT_EQ(cpu.get_dx(), 0x40A7);
    EXPECT_EQ(cpu.get_ip(), 0xBDC4);
    EXPECT_EQ(cpu.get_flags(), 0xF803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x892A2), 0xF7);
    EXPECT_EQ(memory.load8(0x892A3), 0x20);
    EXPECT_EQ(memory.load8(0x892A4), 0x90);
    EXPECT_EQ(memory.load8(0x892A5), 0x90);
    EXPECT_EQ(memory.load8(0x892A6), 0x90);
    EXPECT_EQ(memory.load8(0x892A7), 0x90);
    EXPECT_EQ(memory.load8(0x92F76), 0xE9);
    EXPECT_EQ(memory.load8(0x92F77), 0xD0);
}

//
// imul bh
//
TEST_F(MachineTest, imul_bh)
{
    // Initial CPU State
    cpu.set_ax(0x2064);
    cpu.set_bx(0x4B90);
    cpu.set_cx(0xA136);
    cpu.set_dx(0x1AE4);
    cpu.set_cs(0x54DE);
    cpu.set_ss(0x0441);
    cpu.set_ds(0x49C4);
    cpu.set_es(0x0025);
    cpu.set_sp(0xDC74);
    cpu.set_bp(0xEF30);
    cpu.set_si(0x4B83);
    cpu.set_di(0xD6F1);
    cpu.set_ip(0x82EC);
    cpu.set_flags(0xF0D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5D0CC, 0x3E);
    machine.mem_store_byte(0x5D0CD, 0xF6);
    machine.mem_store_byte(0x5D0CE, 0xEF);
    machine.mem_store_byte(0x5D0CF, 0x90);
    machine.mem_store_byte(0x5D0D0, 0x90);
    machine.mem_store_byte(0x5D0D1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1D4C);
    EXPECT_EQ(cpu.get_ip(), 0x82EF);
    EXPECT_EQ(cpu.get_flags(), 0xF807);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5D0CC), 0x3E);
    EXPECT_EQ(memory.load8(0x5D0CD), 0xF6);
    EXPECT_EQ(memory.load8(0x5D0CE), 0xEF);
    EXPECT_EQ(memory.load8(0x5D0CF), 0x90);
    EXPECT_EQ(memory.load8(0x5D0D0), 0x90);
    EXPECT_EQ(memory.load8(0x5D0D1), 0x90);
}

//
// imul byte [es:bx+di+21h]
//
TEST_F(MachineTest, imul_byte_es_bx_di_21h)
{
    // Initial CPU State
    cpu.set_ax(0x2B44);
    cpu.set_bx(0x247C);
    cpu.set_cx(0x88A2);
    cpu.set_dx(0xAA44);
    cpu.set_cs(0xA73C);
    cpu.set_ss(0x8DEA);
    cpu.set_ds(0x868C);
    cpu.set_es(0x333F);
    cpu.set_sp(0x310B);
    cpu.set_bp(0x8EE6);
    cpu.set_si(0xCBD3);
    cpu.set_di(0x9871);
    cpu.set_ip(0x1567);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA8927, 0x26);
    machine.mem_store_byte(0xA8928, 0xF6);
    machine.mem_store_byte(0xA8929, 0x69);
    machine.mem_store_byte(0xA892A, 0x21);
    machine.mem_store_byte(0xA892B, 0x90);
    machine.mem_store_byte(0x3F0FE, 0x30);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0CC0);
    EXPECT_EQ(cpu.get_ip(), 0x156B);
    EXPECT_EQ(cpu.get_flags(), 0xFC03);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA8927), 0x26);
    EXPECT_EQ(memory.load8(0xA8928), 0xF6);
    EXPECT_EQ(memory.load8(0xA8929), 0x69);
    EXPECT_EQ(memory.load8(0xA892A), 0x21);
    EXPECT_EQ(memory.load8(0xA892B), 0x90);
    EXPECT_EQ(memory.load8(0x3F0FE), 0x30);
}

//
// imul di
//
TEST_F(MachineTest, imul_di)
{
    // Initial CPU State
    cpu.set_ax(0x28DB);
    cpu.set_bx(0x2D1C);
    cpu.set_cx(0x9D00);
    cpu.set_dx(0x9125);
    cpu.set_cs(0x0192);
    cpu.set_ss(0x4221);
    cpu.set_ds(0x00C7);
    cpu.set_es(0xA9DB);
    cpu.set_sp(0xCEC7);
    cpu.set_bp(0x1594);
    cpu.set_si(0x0EDD);
    cpu.set_di(0x696B);
    cpu.set_ip(0x1351);
    cpu.set_flags(0xF447);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02C71, 0xF7);
    machine.mem_store_byte(0x02C72, 0xEF);
    machine.mem_store_byte(0x02C73, 0x90);
    machine.mem_store_byte(0x02C74, 0x90);
    machine.mem_store_byte(0x02C75, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xE689);
    EXPECT_EQ(cpu.get_dx(), 0x10D2);
    EXPECT_EQ(cpu.get_ip(), 0x1353);
    EXPECT_EQ(cpu.get_flags(), 0xFC03);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02C71), 0xF7);
    EXPECT_EQ(memory.load8(0x02C72), 0xEF);
    EXPECT_EQ(memory.load8(0x02C73), 0x90);
    EXPECT_EQ(memory.load8(0x02C74), 0x90);
    EXPECT_EQ(memory.load8(0x02C75), 0x90);
}

//
// imul word [ds:bx+di+6Fh]
//
TEST_F(MachineTest, imul_word_ds_bx_di_6Fh)
{
    // Initial CPU State
    cpu.set_ax(0x6D0D);
    cpu.set_bx(0xF3F1);
    cpu.set_cx(0x20CA);
    cpu.set_dx(0x49DB);
    cpu.set_cs(0x84D0);
    cpu.set_ss(0xF4F1);
    cpu.set_ds(0x182F);
    cpu.set_es(0x6919);
    cpu.set_sp(0x799B);
    cpu.set_bp(0xD8A9);
    cpu.set_si(0xFD97);
    cpu.set_di(0xBAF8);
    cpu.set_ip(0x6C19);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8B919, 0xF7);
    machine.mem_store_byte(0x8B91A, 0x69);
    machine.mem_store_byte(0x8B91B, 0x6F);
    machine.mem_store_byte(0x8B91C, 0x90);
    machine.mem_store_byte(0x8B91D, 0x90);
    machine.mem_store_byte(0x23248, 0x5D);
    machine.mem_store_byte(0x23249, 0xE9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x72B9);
    EXPECT_EQ(cpu.get_dx(), 0xF65B);
    EXPECT_EQ(cpu.get_ip(), 0x6C1C);
    EXPECT_EQ(cpu.get_flags(), 0xF883);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8B919), 0xF7);
    EXPECT_EQ(memory.load8(0x8B91A), 0x69);
    EXPECT_EQ(memory.load8(0x8B91B), 0x6F);
    EXPECT_EQ(memory.load8(0x8B91C), 0x90);
    EXPECT_EQ(memory.load8(0x8B91D), 0x90);
    EXPECT_EQ(memory.load8(0x23248), 0x5D);
    EXPECT_EQ(memory.load8(0x23249), 0xE9);
}
