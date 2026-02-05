#include "fixture.h"

//
// esc bp
//
TEST_F(MachineTest, esc_bp)
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
    machine.mem_store_byte(0x89A01, 0xDB);
    machine.mem_store_byte(0x89A02, 0xFD);
    machine.mem_store_byte(0x89A03, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDCD3);

    // Final RAM entries
}

//
// esc di
//
TEST_F(MachineTest, esc_di)
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
    machine.mem_store_byte(0xEA71D, 0xDF);
    machine.mem_store_byte(0xEA71E, 0xE7);
    machine.mem_store_byte(0xEA71F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x16BF);

    // Final RAM entries
}

//
// esc si
//
TEST_F(MachineTest, esc_si)
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
    machine.mem_store_byte(0xF8478, 0xDD);
    machine.mem_store_byte(0xF8479, 0xC6);
    machine.mem_store_byte(0xF847A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4C7A);

    // Final RAM entries
}

//
// esc word [ds:bp+di]
//
TEST_F(MachineTest, esc_word_ds_bp_di)
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
    machine.mem_store_byte(0xC2A89, 0xDA);
    machine.mem_store_byte(0xC2A8A, 0x0B);
    machine.mem_store_byte(0xC2A8B, 0x90);
    machine.mem_store_byte(0xCDE58, 0x59);
    machine.mem_store_byte(0xCDE59, 0x41);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCF2B);

    // Final RAM entries
}

//
// esc word [ds:di]
//
TEST_F(MachineTest, esc_word_ds_di)
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
    machine.mem_store_byte(0x76C78, 0xD8);
    machine.mem_store_byte(0x76C79, 0x2D);
    machine.mem_store_byte(0x76C7A, 0x90);
    machine.mem_store_byte(0x76C7B, 0x90);
    machine.mem_store_byte(0x33E5A, 0x07);
    machine.mem_store_byte(0x33E5B, 0x3F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x01CA);

    // Final RAM entries
}

//
// esc word [ss:F29Ah]
//
TEST_F(MachineTest, esc_word_ss_F29Ah)
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
    machine.mem_store_byte(0xCE7CB, 0xDE);
    machine.mem_store_byte(0xCE7CC, 0x2E);
    machine.mem_store_byte(0xCE7CD, 0x9A);
    machine.mem_store_byte(0xCE7CE, 0xF2);
    machine.mem_store_byte(0x6BD5A, 0xAD);
    machine.mem_store_byte(0x6BD5B, 0x7B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3EEF);

    // Final RAM entries
}

//
// esc word [ss:bp+si+619Ah]
//
TEST_F(MachineTest, esc_word_ss_bp_si_619Ah)
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
    machine.mem_store_byte(0x76C61, 0xDC);
    machine.mem_store_byte(0x76C62, 0xAA);
    machine.mem_store_byte(0x76C63, 0x9A);
    machine.mem_store_byte(0x76C64, 0x61);
    machine.mem_store_byte(0x3F15C, 0xBB);
    machine.mem_store_byte(0x3F15D, 0x44);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0F35);

    // Final RAM entries
}
