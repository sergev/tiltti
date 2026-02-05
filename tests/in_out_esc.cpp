#include "fixture.h"

// Tests: in, out, esc

TEST_F(MachineTest, esc_word_cs_bx_di_44h)
{
    // Initial CPU State
    cpu.set_ax(0x50F6);
    cpu.set_bx(0x6565);
    cpu.set_cx(0xFFD0);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xAE72);
    cpu.set_ss(0x4F1C);
    cpu.set_ds(0xB300);
    cpu.set_es(0x7C8B);
    cpu.set_sp(0xBBF1);
    cpu.set_bp(0xADC4);
    cpu.set_si(0x0D8E);
    cpu.set_di(0x7E6F);
    cpu.set_ip(0xFCD8);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBE3F8, 0x2E);
    machine.mem_store_byte(0xBE3F9, 0xD9);
    machine.mem_store_byte(0xBE3FA, 0x41);
    machine.mem_store_byte(0xBE3FB, 0x44);
    machine.mem_store_byte(0xBE3FC, 0x90);
    machine.mem_store_byte(0xBE3FD, 0x90);
    machine.mem_store_byte(0xBCB38, 0x48);
    machine.mem_store_byte(0xBCB39, 0xAD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xFCDC);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBE3F8), 0x2E);
    EXPECT_EQ(memory.load8(0xBE3F9), 0xD9);
    EXPECT_EQ(memory.load8(0xBE3FA), 0x41);
    EXPECT_EQ(memory.load8(0xBE3FB), 0x44);
    EXPECT_EQ(memory.load8(0xBE3FC), 0x90);
    EXPECT_EQ(memory.load8(0xBE3FD), 0x90);
    EXPECT_EQ(memory.load8(0xBCB38), 0x48);
    EXPECT_EQ(memory.load8(0xBCB39), 0xAD);
}


TEST_F(MachineTest, esc_word_ds_bx_di_3h)
{
    // Initial CPU State
    cpu.set_ax(0x3A6D);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x23D6);
    cpu.set_dx(0x3DD2);
    cpu.set_cs(0x783D);
    cpu.set_ss(0x2A44);
    cpu.set_ds(0x4444);
    cpu.set_es(0xC7B6);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x103A);
    cpu.set_si(0xA7DE);
    cpu.set_di(0xC631);
    cpu.set_ip(0x06A1);
    cpu.set_flags(0xF8D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x78A71, 0xDA);
    machine.mem_store_byte(0x78A72, 0x71);
    machine.mem_store_byte(0x78A73, 0x03);
    machine.mem_store_byte(0x78A74, 0x90);
    machine.mem_store_byte(0x78A75, 0x90);
    machine.mem_store_byte(0x50A74, 0x9D);
    machine.mem_store_byte(0x50A75, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x06A4);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x78A71), 0xDA);
    EXPECT_EQ(memory.load8(0x78A72), 0x71);
    EXPECT_EQ(memory.load8(0x78A73), 0x03);
    EXPECT_EQ(memory.load8(0x78A74), 0x90);
    EXPECT_EQ(memory.load8(0x78A75), 0x90);
    EXPECT_EQ(memory.load8(0x50A74), 0x9D);
    EXPECT_EQ(memory.load8(0x50A75), 0x90);
}


TEST_F(MachineTest, esc_word_ds_di)
{
    // Initial CPU State
    cpu.set_ax(0x34F9);
    cpu.set_bx(0x175C);
    cpu.set_cx(0x2034);
    cpu.set_dx(0x427B);
    cpu.set_cs(0x7860);
    cpu.set_ss(0x4AD8);
    cpu.set_ds(0x1B08);
    cpu.set_es(0x5710);
    cpu.set_sp(0xB0F7);
    cpu.set_bp(0x01A8);
    cpu.set_si(0x0000);
    cpu.set_di(0xE76B);
    cpu.set_ip(0xDB67);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x86167, 0xDC);
    machine.mem_store_byte(0x86168, 0x3D);
    machine.mem_store_byte(0x86169, 0x90);
    machine.mem_store_byte(0x8616A, 0x90);
    machine.mem_store_byte(0x8616B, 0x90);
    machine.mem_store_byte(0x297EB, 0x62);
    machine.mem_store_byte(0x297EC, 0x6C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDB69);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x86167), 0xDC);
    EXPECT_EQ(memory.load8(0x86168), 0x3D);
    EXPECT_EQ(memory.load8(0x86169), 0x90);
    EXPECT_EQ(memory.load8(0x8616A), 0x90);
    EXPECT_EQ(memory.load8(0x8616B), 0x90);
    EXPECT_EQ(memory.load8(0x297EB), 0x62);
    EXPECT_EQ(memory.load8(0x297EC), 0x6C);
}


TEST_F(MachineTest, esc_word_ds_si)
{
    // Initial CPU State
    cpu.set_ax(0x975C);
    cpu.set_bx(0x843D);
    cpu.set_cx(0x16D2);
    cpu.set_dx(0x6A3F);
    cpu.set_cs(0xE245);
    cpu.set_ss(0xD1C4);
    cpu.set_ds(0xA3F4);
    cpu.set_es(0x322B);
    cpu.set_sp(0x43E9);
    cpu.set_bp(0xFE89);
    cpu.set_si(0x0000);
    cpu.set_di(0x6F60);
    cpu.set_ip(0x0120);
    cpu.set_flags(0xF0D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE2570, 0xD8);
    machine.mem_store_byte(0xE2571, 0x14);
    machine.mem_store_byte(0xE2572, 0x90);
    machine.mem_store_byte(0xE2573, 0x90);
    machine.mem_store_byte(0xE2574, 0x90);
    machine.mem_store_byte(0xE2575, 0x90);
    machine.mem_store_byte(0xA3F40, 0x11);
    machine.mem_store_byte(0xA3F41, 0x48);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0122);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE2570), 0xD8);
    EXPECT_EQ(memory.load8(0xE2571), 0x14);
    EXPECT_EQ(memory.load8(0xE2572), 0x90);
    EXPECT_EQ(memory.load8(0xE2573), 0x90);
    EXPECT_EQ(memory.load8(0xE2574), 0x90);
    EXPECT_EQ(memory.load8(0xE2575), 0x90);
    EXPECT_EQ(memory.load8(0xA3F40), 0x11);
    EXPECT_EQ(memory.load8(0xA3F41), 0x48);
}


TEST_F(MachineTest, esc_word_es_bp_22C0h)
{
    // Initial CPU State
    cpu.set_ax(0x7EDE);
    cpu.set_bx(0x407A);
    cpu.set_cx(0x7FF0);
    cpu.set_dx(0x3B7A);
    cpu.set_cs(0x45F9);
    cpu.set_ss(0x3595);
    cpu.set_ds(0x5379);
    cpu.set_es(0x0A0E);
    cpu.set_sp(0xF58B);
    cpu.set_bp(0x8339);
    cpu.set_si(0x6CDA);
    cpu.set_di(0x2270);
    cpu.set_ip(0xE4CC);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5445C, 0x26);
    machine.mem_store_byte(0x5445D, 0xDE);
    machine.mem_store_byte(0x5445E, 0xA6);
    machine.mem_store_byte(0x5445F, 0xC0);
    machine.mem_store_byte(0x54460, 0x22);
    machine.mem_store_byte(0x54461, 0x90);
    machine.mem_store_byte(0x146D9, 0xC3);
    machine.mem_store_byte(0x146DA, 0xA2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE4D1);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5445C), 0x26);
    EXPECT_EQ(memory.load8(0x5445D), 0xDE);
    EXPECT_EQ(memory.load8(0x5445E), 0xA6);
    EXPECT_EQ(memory.load8(0x5445F), 0xC0);
    EXPECT_EQ(memory.load8(0x54460), 0x22);
    EXPECT_EQ(memory.load8(0x54461), 0x90);
    EXPECT_EQ(memory.load8(0x146D9), 0xC3);
    EXPECT_EQ(memory.load8(0x146DA), 0xA2);
}


TEST_F(MachineTest, esc_word_es_bp_F08h)
{
    // Initial CPU State
    cpu.set_ax(0xC25C);
    cpu.set_bx(0x666F);
    cpu.set_cx(0x7CDC);
    cpu.set_dx(0x855C);
    cpu.set_cs(0x7B04);
    cpu.set_ss(0xE366);
    cpu.set_ds(0x6E3C);
    cpu.set_es(0x4365);
    cpu.set_sp(0xDE26);
    cpu.set_bp(0xCC07);
    cpu.set_si(0x5675);
    cpu.set_di(0xBCA4);
    cpu.set_ip(0x97E8);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x84828, 0x26);
    machine.mem_store_byte(0x84829, 0xDD);
    machine.mem_store_byte(0x8482A, 0xBE);
    machine.mem_store_byte(0x8482B, 0x08);
    machine.mem_store_byte(0x8482C, 0x0F);
    machine.mem_store_byte(0x8482D, 0x90);
    machine.mem_store_byte(0x5115F, 0x47);
    machine.mem_store_byte(0x51160, 0xE7);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x97ED);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x84828), 0x26);
    EXPECT_EQ(memory.load8(0x84829), 0xDD);
    EXPECT_EQ(memory.load8(0x8482A), 0xBE);
    EXPECT_EQ(memory.load8(0x8482B), 0x08);
    EXPECT_EQ(memory.load8(0x8482C), 0x0F);
    EXPECT_EQ(memory.load8(0x8482D), 0x90);
    EXPECT_EQ(memory.load8(0x5115F), 0x47);
    EXPECT_EQ(memory.load8(0x51160), 0xE7);
}


TEST_F(MachineTest, esc_word_es_bx_di_23h)
{
    // Initial CPU State
    cpu.set_ax(0xDB8C);
    cpu.set_bx(0x22C2);
    cpu.set_cx(0xBD6E);
    cpu.set_dx(0xF94F);
    cpu.set_cs(0x1290);
    cpu.set_ss(0xDE3B);
    cpu.set_ds(0x9BC0);
    cpu.set_es(0x32F0);
    cpu.set_sp(0x6A4F);
    cpu.set_bp(0x5D72);
    cpu.set_si(0x459C);
    cpu.set_di(0xCB89);
    cpu.set_ip(0xE69E);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x20F9E, 0x26);
    machine.mem_store_byte(0x20F9F, 0xDF);
    machine.mem_store_byte(0x20FA0, 0x59);
    machine.mem_store_byte(0x20FA1, 0x23);
    machine.mem_store_byte(0x20FA2, 0x90);
    machine.mem_store_byte(0x20FA3, 0x90);
    machine.mem_store_byte(0x41D6E, 0x60);
    machine.mem_store_byte(0x41D6F, 0x35);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE6A2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x20F9E), 0x26);
    EXPECT_EQ(memory.load8(0x20F9F), 0xDF);
    EXPECT_EQ(memory.load8(0x20FA0), 0x59);
    EXPECT_EQ(memory.load8(0x20FA1), 0x23);
    EXPECT_EQ(memory.load8(0x20FA2), 0x90);
    EXPECT_EQ(memory.load8(0x20FA3), 0x90);
    EXPECT_EQ(memory.load8(0x41D6E), 0x60);
    EXPECT_EQ(memory.load8(0x41D6F), 0x35);
}


TEST_F(MachineTest, esc_word_ss_bp_si)
{
    // Initial CPU State
    cpu.set_ax(0x064E);
    cpu.set_bx(0xA24F);
    cpu.set_cx(0x133A);
    cpu.set_dx(0x0E56);
    cpu.set_cs(0xCE54);
    cpu.set_ss(0xFD1B);
    cpu.set_ds(0xE837);
    cpu.set_es(0xFC3E);
    cpu.set_sp(0x1121);
    cpu.set_bp(0xEC54);
    cpu.set_si(0xA697);
    cpu.set_di(0x8EFA);
    cpu.set_ip(0xE8D6);
    cpu.set_flags(0xF457);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDCE16, 0x36);
    machine.mem_store_byte(0xDCE17, 0xDB);
    machine.mem_store_byte(0xDCE18, 0x32);
    machine.mem_store_byte(0xDCE19, 0x90);
    machine.mem_store_byte(0xDCE1A, 0x90);
    machine.mem_store_byte(0xDCE1B, 0x90);
    machine.mem_store_byte(0x0649B, 0x4A);
    machine.mem_store_byte(0x0649C, 0xBE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE8D9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDCE16), 0x36);
    EXPECT_EQ(memory.load8(0xDCE17), 0xDB);
    EXPECT_EQ(memory.load8(0xDCE18), 0x32);
    EXPECT_EQ(memory.load8(0xDCE19), 0x90);
    EXPECT_EQ(memory.load8(0xDCE1A), 0x90);
    EXPECT_EQ(memory.load8(0xDCE1B), 0x90);
    EXPECT_EQ(memory.load8(0x0649B), 0x4A);
    EXPECT_EQ(memory.load8(0x0649C), 0xBE);
}


TEST_F(MachineTest, in_al_80h)
{
    // Initial CPU State
    cpu.set_ax(0xEE83);
    cpu.set_bx(0xF6C7);
    cpu.set_cx(0x697E);
    cpu.set_dx(0x7E50);
    cpu.set_cs(0x978F);
    cpu.set_ss(0xD579);
    cpu.set_ds(0x3AE8);
    cpu.set_es(0xFA8E);
    cpu.set_sp(0xDB42);
    cpu.set_bp(0xECEB);
    cpu.set_si(0xAA17);
    cpu.set_di(0x95D2);
    cpu.set_ip(0x8D87);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA0677, 0xE4);
    machine.mem_store_byte(0xA0678, 0x80);
    machine.mem_store_byte(0xA0679, 0x90);
    machine.mem_store_byte(0xA067A, 0x90);
    machine.mem_store_byte(0xA067B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xEEFF);
    EXPECT_EQ(cpu.get_ip(), 0x8D89);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA0677), 0xE4);
    EXPECT_EQ(memory.load8(0xA0678), 0x80);
    EXPECT_EQ(memory.load8(0xA0679), 0x90);
    EXPECT_EQ(memory.load8(0xA067A), 0x90);
    EXPECT_EQ(memory.load8(0xA067B), 0x90);
}


TEST_F(MachineTest, in_al_dx)
{
    // Initial CPU State
    cpu.set_ax(0x001F);
    cpu.set_bx(0xED04);
    cpu.set_cx(0xC68E);
    cpu.set_dx(0x3277);
    cpu.set_cs(0x6A8A);
    cpu.set_ss(0x9699);
    cpu.set_ds(0x63D2);
    cpu.set_es(0x0795);
    cpu.set_sp(0x25C8);
    cpu.set_bp(0x3BDE);
    cpu.set_si(0xD8F7);
    cpu.set_di(0x6A92);
    cpu.set_ip(0x1B79);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6C419, 0xEC);
    machine.mem_store_byte(0x6C41A, 0x90);
    machine.mem_store_byte(0x6C41B, 0x90);
    machine.mem_store_byte(0x6C41C, 0x90);
    machine.mem_store_byte(0x6C41D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x00FF);
    EXPECT_EQ(cpu.get_ip(), 0x1B7A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6C419), 0xEC);
    EXPECT_EQ(memory.load8(0x6C41A), 0x90);
    EXPECT_EQ(memory.load8(0x6C41B), 0x90);
    EXPECT_EQ(memory.load8(0x6C41C), 0x90);
    EXPECT_EQ(memory.load8(0x6C41D), 0x90);
}


TEST_F(MachineTest, in_ax_67h)
{
    // Initial CPU State
    cpu.set_ax(0x051D);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xCF20);
    cpu.set_dx(0x5833);
    cpu.set_cs(0x48ED);
    cpu.set_ss(0xCBE3);
    cpu.set_ds(0xEE04);
    cpu.set_es(0xF5E6);
    cpu.set_sp(0x9EA9);
    cpu.set_bp(0x0000);
    cpu.set_si(0x66E2);
    cpu.set_di(0xF7F2);
    cpu.set_ip(0xA742);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x53612, 0xE5);
    machine.mem_store_byte(0x53613, 0x67);
    machine.mem_store_byte(0x53614, 0x90);
    machine.mem_store_byte(0x53615, 0x90);
    machine.mem_store_byte(0x53616, 0x90);
    machine.mem_store_byte(0x53617, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0xA744);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x53612), 0xE5);
    EXPECT_EQ(memory.load8(0x53613), 0x67);
    EXPECT_EQ(memory.load8(0x53614), 0x90);
    EXPECT_EQ(memory.load8(0x53615), 0x90);
    EXPECT_EQ(memory.load8(0x53616), 0x90);
    EXPECT_EQ(memory.load8(0x53617), 0x90);
}


TEST_F(MachineTest, in_ax_dx)
{
    // Initial CPU State
    cpu.set_ax(0x0FF0);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xE67E);
    cpu.set_dx(0x5773);
    cpu.set_cs(0x9DE7);
    cpu.set_ss(0x1308);
    cpu.set_ds(0xF40A);
    cpu.set_es(0x5D94);
    cpu.set_sp(0xE53D);
    cpu.set_bp(0xCD70);
    cpu.set_si(0x00FA);
    cpu.set_di(0x0000);
    cpu.set_ip(0xECAA);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xACB1A, 0xED);
    machine.mem_store_byte(0xACB1B, 0x90);
    machine.mem_store_byte(0xACB1C, 0x90);
    machine.mem_store_byte(0xACB1D, 0x90);
    machine.mem_store_byte(0xACB1E, 0x90);
    machine.mem_store_byte(0xACB1F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0xECAB);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xACB1A), 0xED);
    EXPECT_EQ(memory.load8(0xACB1B), 0x90);
    EXPECT_EQ(memory.load8(0xACB1C), 0x90);
    EXPECT_EQ(memory.load8(0xACB1D), 0x90);
    EXPECT_EQ(memory.load8(0xACB1E), 0x90);
    EXPECT_EQ(memory.load8(0xACB1F), 0x90);
}


TEST_F(MachineTest, out_62h_al)
{
    // Initial CPU State
    cpu.set_ax(0x1F31);
    cpu.set_bx(0xF08D);
    cpu.set_cx(0x13F0);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xAFDD);
    cpu.set_ss(0x737C);
    cpu.set_ds(0x2A5B);
    cpu.set_es(0xA732);
    cpu.set_sp(0x96C4);
    cpu.set_bp(0x7F80);
    cpu.set_si(0x45FC);
    cpu.set_di(0xDB3C);
    cpu.set_ip(0x8F61);
    cpu.set_flags(0xFC43);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB8D31, 0xE6);
    machine.mem_store_byte(0xB8D32, 0x62);
    machine.mem_store_byte(0xB8D33, 0x90);
    machine.mem_store_byte(0xB8D34, 0x90);
    machine.mem_store_byte(0xB8D35, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8F63);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB8D31), 0xE6);
    EXPECT_EQ(memory.load8(0xB8D32), 0x62);
    EXPECT_EQ(memory.load8(0xB8D33), 0x90);
    EXPECT_EQ(memory.load8(0xB8D34), 0x90);
    EXPECT_EQ(memory.load8(0xB8D35), 0x90);
}


TEST_F(MachineTest, out_A1h_ax)
{
    // Initial CPU State
    cpu.set_ax(0xB4FF);
    cpu.set_bx(0x0EBF);
    cpu.set_cx(0x5748);
    cpu.set_dx(0xF510);
    cpu.set_cs(0xB9BB);
    cpu.set_ss(0xD133);
    cpu.set_ds(0xC87E);
    cpu.set_es(0x66CC);
    cpu.set_sp(0xA854);
    cpu.set_bp(0x6A9F);
    cpu.set_si(0xEDFF);
    cpu.set_di(0xA815);
    cpu.set_ip(0x5B7E);
    cpu.set_flags(0xF896);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBF72E, 0xE7);
    machine.mem_store_byte(0xBF72F, 0xA1);
    machine.mem_store_byte(0xBF730, 0x90);
    machine.mem_store_byte(0xBF731, 0x90);
    machine.mem_store_byte(0xBF732, 0x90);
    machine.mem_store_byte(0xBF733, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5B80);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBF72E), 0xE7);
    EXPECT_EQ(memory.load8(0xBF72F), 0xA1);
    EXPECT_EQ(memory.load8(0xBF730), 0x90);
    EXPECT_EQ(memory.load8(0xBF731), 0x90);
    EXPECT_EQ(memory.load8(0xBF732), 0x90);
    EXPECT_EQ(memory.load8(0xBF733), 0x90);
}


TEST_F(MachineTest, out_dx_al)
{
    // Initial CPU State
    cpu.set_ax(0x05D5);
    cpu.set_bx(0xCF0C);
    cpu.set_cx(0x13FA);
    cpu.set_dx(0x7F2E);
    cpu.set_cs(0xFFB5);
    cpu.set_ss(0xC3D6);
    cpu.set_ds(0xE101);
    cpu.set_es(0x3E63);
    cpu.set_sp(0x74E4);
    cpu.set_bp(0x42EF);
    cpu.set_si(0xCB97);
    cpu.set_di(0xA53B);
    cpu.set_ip(0xC316);
    cpu.set_flags(0xF0D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0BE66, 0xEE);
    machine.mem_store_byte(0x0BE67, 0x90);
    machine.mem_store_byte(0x0BE68, 0x90);
    machine.mem_store_byte(0x0BE69, 0x90);
    machine.mem_store_byte(0x0BE6A, 0x90);
    machine.mem_store_byte(0x0BE6B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC317);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0BE66), 0xEE);
    EXPECT_EQ(memory.load8(0x0BE67), 0x90);
    EXPECT_EQ(memory.load8(0x0BE68), 0x90);
    EXPECT_EQ(memory.load8(0x0BE69), 0x90);
    EXPECT_EQ(memory.load8(0x0BE6A), 0x90);
    EXPECT_EQ(memory.load8(0x0BE6B), 0x90);
}


TEST_F(MachineTest, out_dx_ax)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x97F5);
    cpu.set_cx(0xFA62);
    cpu.set_dx(0xB153);
    cpu.set_cs(0x0FFE);
    cpu.set_ss(0xF653);
    cpu.set_ds(0xAD35);
    cpu.set_es(0xC29C);
    cpu.set_sp(0x42C8);
    cpu.set_bp(0xDBF8);
    cpu.set_si(0x9D7C);
    cpu.set_di(0x190D);
    cpu.set_ip(0xA62A);
    cpu.set_flags(0xF807);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1A60A, 0xEF);
    machine.mem_store_byte(0x1A60B, 0x90);
    machine.mem_store_byte(0x1A60C, 0x90);
    machine.mem_store_byte(0x1A60D, 0x90);
    machine.mem_store_byte(0x1A60E, 0x90);
    machine.mem_store_byte(0x1A60F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA62B);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1A60A), 0xEF);
    EXPECT_EQ(memory.load8(0x1A60B), 0x90);
    EXPECT_EQ(memory.load8(0x1A60C), 0x90);
    EXPECT_EQ(memory.load8(0x1A60D), 0x90);
    EXPECT_EQ(memory.load8(0x1A60E), 0x90);
    EXPECT_EQ(memory.load8(0x1A60F), 0x90);
}
