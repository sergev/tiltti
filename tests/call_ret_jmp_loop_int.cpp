#include "fixture.h"

// Tests: call, callf, retn, retf, jmp, jmpf, loop, loope, loopne, jcxz, int, into, iret

TEST_F(MachineTest, call_F478h)
{
    // Initial CPU State
    cpu.set_ax(0x4CC1);
    cpu.set_bx(0x2CAA);
    cpu.set_cx(0x2154);
    cpu.set_dx(0x33F6);
    cpu.set_cs(0x2900);
    cpu.set_ss(0xA5EF);
    cpu.set_ds(0x7474);
    cpu.set_es(0xDAFF);
    cpu.set_sp(0x15D6);
    cpu.set_bp(0xA551);
    cpu.set_si(0xAF5D);
    cpu.set_di(0x0000);
    cpu.set_ip(0xC801);
    cpu.set_flags(0xF416);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x35801, 0xE8);
    machine.mem_store_byte(0x35802, 0x75);
    machine.mem_store_byte(0x35803, 0xF4);
    machine.mem_store_byte(0x35804, 0x90);
    machine.mem_store_byte(0x35805, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x15D4);
    EXPECT_EQ(cpu.get_ip(), 0xBC79);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x35801), 0xE8);
    EXPECT_EQ(memory.load8(0x35802), 0x75);
    EXPECT_EQ(memory.load8(0x35803), 0xF4);
    EXPECT_EQ(memory.load8(0x35804), 0x90);
    EXPECT_EQ(memory.load8(0x35805), 0x90);
    EXPECT_EQ(memory.load8(0xA74C4), 0x04);
    EXPECT_EQ(memory.load8(0xA74C5), 0xC8);
}

TEST_F(MachineTest, call_word_ss_bp_65h)
{
    // Initial CPU State
    cpu.set_ax(0xAF67);
    cpu.set_bx(0x5072);
    cpu.set_cx(0xBAE0);
    cpu.set_dx(0x3D33);
    cpu.set_cs(0xA272);
    cpu.set_ss(0xCD0B);
    cpu.set_ds(0xD2B2);
    cpu.set_es(0x9CCA);
    cpu.set_sp(0x8F7E);
    cpu.set_bp(0x35B8);
    cpu.set_si(0x418A);
    cpu.set_di(0x2B62);
    cpu.set_ip(0x8812);
    cpu.set_flags(0xF492);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAAF32, 0x36);
    machine.mem_store_byte(0xAAF33, 0xFF);
    machine.mem_store_byte(0xAAF34, 0x56);
    machine.mem_store_byte(0xAAF35, 0x65);
    machine.mem_store_byte(0xAAF36, 0x90);
    machine.mem_store_byte(0xAAF37, 0x90);
    machine.mem_store_byte(0xD06CD, 0xF0);
    machine.mem_store_byte(0xD06CE, 0x97);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x8F7C);
    EXPECT_EQ(cpu.get_ip(), 0x97F0);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAAF32), 0x36);
    EXPECT_EQ(memory.load8(0xAAF33), 0xFF);
    EXPECT_EQ(memory.load8(0xAAF34), 0x56);
    EXPECT_EQ(memory.load8(0xAAF35), 0x65);
    EXPECT_EQ(memory.load8(0xAAF36), 0x90);
    EXPECT_EQ(memory.load8(0xAAF37), 0x90);
    EXPECT_EQ(memory.load8(0xD06CD), 0xF0);
    EXPECT_EQ(memory.load8(0xD06CE), 0x97);
    EXPECT_EQ(memory.load8(0xD602C), 0x16);
    EXPECT_EQ(memory.load8(0xD602D), 0x88);
}

TEST_F(MachineTest, callf_3558h_7C02h)
{
    // Initial CPU State
    cpu.set_ax(0xD550);
    cpu.set_bx(0xA9C5);
    cpu.set_cx(0xF830);
    cpu.set_dx(0xF4FB);
    cpu.set_cs(0xCA8B);
    cpu.set_ss(0x061C);
    cpu.set_ds(0x6559);
    cpu.set_es(0xD3C1);
    cpu.set_sp(0x60DA);
    cpu.set_bp(0x64E3);
    cpu.set_si(0x6803);
    cpu.set_di(0xA2D0);
    cpu.set_ip(0x35F7);
    cpu.set_flags(0xF096);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCDEA7, 0x9A);
    machine.mem_store_byte(0xCDEA8, 0x02);
    machine.mem_store_byte(0xCDEA9, 0x7C);
    machine.mem_store_byte(0xCDEAA, 0x58);
    machine.mem_store_byte(0xCDEAB, 0x35);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x3558);
    EXPECT_EQ(cpu.get_sp(), 0x60D6);
    EXPECT_EQ(cpu.get_ip(), 0x7C02);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCDEA7), 0x9A);
    EXPECT_EQ(memory.load8(0xCDEA8), 0x02);
    EXPECT_EQ(memory.load8(0xCDEA9), 0x7C);
    EXPECT_EQ(memory.load8(0xCDEAA), 0x58);
    EXPECT_EQ(memory.load8(0xCDEAB), 0x35);
    EXPECT_EQ(memory.load8(0x0C298), 0x8B);
    EXPECT_EQ(memory.load8(0x0C299), 0xCA);
    EXPECT_EQ(memory.load8(0x0C296), 0xFC);
    EXPECT_EQ(memory.load8(0x0C297), 0x35);
}

TEST_F(MachineTest, callf_word_ss_bp_4Ch)
{
    // Initial CPU State
    cpu.set_ax(0x0E1F);
    cpu.set_bx(0xEE2D);
    cpu.set_cx(0xF48E);
    cpu.set_dx(0x3AD8);
    cpu.set_cs(0xE899);
    cpu.set_ss(0x3C95);
    cpu.set_ds(0xDA66);
    cpu.set_es(0xA074);
    cpu.set_sp(0x81CF);
    cpu.set_bp(0x6D06);
    cpu.set_si(0xB1ED);
    cpu.set_di(0xEF46);
    cpu.set_ip(0x5891);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE221, 0xFF);
    machine.mem_store_byte(0xEE222, 0x5E);
    machine.mem_store_byte(0xEE223, 0x4C);
    machine.mem_store_byte(0xEE224, 0x90);
    machine.mem_store_byte(0xEE225, 0x90);
    machine.mem_store_byte(0x436A2, 0x10);
    machine.mem_store_byte(0x436A3, 0x48);
    machine.mem_store_byte(0x436A4, 0x9F);
    machine.mem_store_byte(0x436A5, 0x50);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x509F);
    EXPECT_EQ(cpu.get_sp(), 0x81CB);
    EXPECT_EQ(cpu.get_ip(), 0x4810);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE221), 0xFF);
    EXPECT_EQ(memory.load8(0xEE222), 0x5E);
    EXPECT_EQ(memory.load8(0xEE223), 0x4C);
    EXPECT_EQ(memory.load8(0xEE224), 0x90);
    EXPECT_EQ(memory.load8(0xEE225), 0x90);
    EXPECT_EQ(memory.load8(0x436A2), 0x10);
    EXPECT_EQ(memory.load8(0x436A3), 0x48);
    EXPECT_EQ(memory.load8(0x436A4), 0x9F);
    EXPECT_EQ(memory.load8(0x436A5), 0x50);
    EXPECT_EQ(memory.load8(0x44B1D), 0x99);
    EXPECT_EQ(memory.load8(0x44B1E), 0xE8);
    EXPECT_EQ(memory.load8(0x44B1B), 0x94);
    EXPECT_EQ(memory.load8(0x44B1C), 0x58);
}

TEST_F(MachineTest, int3)
{
    // Initial CPU State
    cpu.set_ax(0xBFAB);
    cpu.set_bx(0x97F0);
    cpu.set_cx(0x5472);
    cpu.set_dx(0x3BA9);
    cpu.set_cs(0x66F4);
    cpu.set_ss(0xF8CD);
    cpu.set_ds(0x044F);
    cpu.set_es(0xDEB3);
    cpu.set_sp(0x6A84);
    cpu.set_bp(0x686F);
    cpu.set_si(0xE9F4);
    cpu.set_di(0xBA15);
    cpu.set_ip(0x207C);
    cpu.set_flags(0xF8C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x68FBC, 0xCC);
    machine.mem_store_byte(0x68FBD, 0x90);
    machine.mem_store_byte(0x68FBE, 0x90);
    machine.mem_store_byte(0x68FBF, 0x90);
    machine.mem_store_byte(0x68FC0, 0x90);
    machine.mem_store_byte(0x68FC1, 0x90);
    machine.mem_store_byte(0x0000C, 0xD2);
    machine.mem_store_byte(0x0000D, 0xFC);
    machine.mem_store_byte(0x0000E, 0x14);
    machine.mem_store_byte(0x0000F, 0x7A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x7A14);
    EXPECT_EQ(cpu.get_sp(), 0x6A7E);
    EXPECT_EQ(cpu.get_ip(), 0xFCD2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x68FBC), 0xCC);
    EXPECT_EQ(memory.load8(0x68FBD), 0x90);
    EXPECT_EQ(memory.load8(0x68FBE), 0x90);
    EXPECT_EQ(memory.load8(0x68FBF), 0x90);
    EXPECT_EQ(memory.load8(0x68FC0), 0x90);
    EXPECT_EQ(memory.load8(0x68FC1), 0x90);
    EXPECT_EQ(memory.load8(0x0000C), 0xD2);
    EXPECT_EQ(memory.load8(0x0000D), 0xFC);
    EXPECT_EQ(memory.load8(0x0000E), 0x14);
    EXPECT_EQ(memory.load8(0x0000F), 0x7A);
    EXPECT_EQ(memory.load8(0xFF752), 0xC6);
    EXPECT_EQ(memory.load8(0xFF753), 0xF8);
    EXPECT_EQ(memory.load8(0xFF750), 0xF4);
    EXPECT_EQ(memory.load8(0xFF751), 0x66);
    EXPECT_EQ(memory.load8(0xFF74E), 0x7D);
    EXPECT_EQ(memory.load8(0xFF74F), 0x20);
}

TEST_F(MachineTest, int_F2h)
{
    // Initial CPU State
    cpu.set_ax(0xB767);
    cpu.set_bx(0x02EA);
    cpu.set_cx(0x55B2);
    cpu.set_dx(0x36D6);
    cpu.set_cs(0x71CB);
    cpu.set_ss(0x17C1);
    cpu.set_ds(0xE568);
    cpu.set_es(0xCC91);
    cpu.set_sp(0xEA49);
    cpu.set_bp(0x2DB3);
    cpu.set_si(0xAE5A);
    cpu.set_di(0x3548);
    cpu.set_ip(0x8C92);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7A942, 0xCD);
    machine.mem_store_byte(0x7A943, 0xF2);
    machine.mem_store_byte(0x7A944, 0x90);
    machine.mem_store_byte(0x7A945, 0x90);
    machine.mem_store_byte(0x7A946, 0x90);
    machine.mem_store_byte(0x7A947, 0x90);
    machine.mem_store_byte(0x003C8, 0x0A);
    machine.mem_store_byte(0x003C9, 0x1C);
    machine.mem_store_byte(0x003CA, 0x22);
    machine.mem_store_byte(0x003CB, 0xB8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0xB822);
    EXPECT_EQ(cpu.get_sp(), 0xEA43);
    EXPECT_EQ(cpu.get_ip(), 0x1C0A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7A942), 0xCD);
    EXPECT_EQ(memory.load8(0x7A943), 0xF2);
    EXPECT_EQ(memory.load8(0x7A944), 0x90);
    EXPECT_EQ(memory.load8(0x7A945), 0x90);
    EXPECT_EQ(memory.load8(0x7A946), 0x90);
    EXPECT_EQ(memory.load8(0x7A947), 0x90);
    EXPECT_EQ(memory.load8(0x003C8), 0x0A);
    EXPECT_EQ(memory.load8(0x003C9), 0x1C);
    EXPECT_EQ(memory.load8(0x003CA), 0x22);
    EXPECT_EQ(memory.load8(0x003CB), 0xB8);
    EXPECT_EQ(memory.load8(0x26657), 0xD2);
    EXPECT_EQ(memory.load8(0x26658), 0xFC);
    EXPECT_EQ(memory.load8(0x26655), 0xCB);
    EXPECT_EQ(memory.load8(0x26656), 0x71);
    EXPECT_EQ(memory.load8(0x26653), 0x94);
    EXPECT_EQ(memory.load8(0x26654), 0x8C);
}

TEST_F(MachineTest, into)
{
    // Initial CPU State
    cpu.set_ax(0x7378);
    cpu.set_bx(0x75B0);
    cpu.set_cx(0xBF86);
    cpu.set_dx(0xD3E1);
    cpu.set_cs(0x5F0C);
    cpu.set_ss(0xD763);
    cpu.set_ds(0xE982);
    cpu.set_es(0x8DE4);
    cpu.set_sp(0xD917);
    cpu.set_bp(0x08A2);
    cpu.set_si(0xC7B2);
    cpu.set_di(0x536F);
    cpu.set_ip(0x693B);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x659FB, 0xCE);
    machine.mem_store_byte(0x659FC, 0x90);
    machine.mem_store_byte(0x659FD, 0x90);
    machine.mem_store_byte(0x659FE, 0x90);
    machine.mem_store_byte(0x659FF, 0x90);
    machine.mem_store_byte(0x00010, 0xF4);
    machine.mem_store_byte(0x00011, 0x27);
    machine.mem_store_byte(0x00012, 0x00);
    machine.mem_store_byte(0x00013, 0x37);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x3700);
    EXPECT_EQ(cpu.get_sp(), 0xD911);
    EXPECT_EQ(cpu.get_ip(), 0x27F4);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x659FB), 0xCE);
    EXPECT_EQ(memory.load8(0x659FC), 0x90);
    EXPECT_EQ(memory.load8(0x659FD), 0x90);
    EXPECT_EQ(memory.load8(0x659FE), 0x90);
    EXPECT_EQ(memory.load8(0x659FF), 0x90);
    EXPECT_EQ(memory.load8(0x00010), 0xF4);
    EXPECT_EQ(memory.load8(0x00011), 0x27);
    EXPECT_EQ(memory.load8(0x00012), 0x00);
    EXPECT_EQ(memory.load8(0x00013), 0x37);
    EXPECT_EQ(memory.load8(0xE4F45), 0x12);
    EXPECT_EQ(memory.load8(0xE4F46), 0xF8);
    EXPECT_EQ(memory.load8(0xE4F43), 0x0C);
    EXPECT_EQ(memory.load8(0xE4F44), 0x5F);
    EXPECT_EQ(memory.load8(0xE4F41), 0x3C);
    EXPECT_EQ(memory.load8(0xE4F42), 0x69);
}

TEST_F(MachineTest, iret)
{
    // Initial CPU State
    cpu.set_ax(0x08AC);
    cpu.set_bx(0xCBDE);
    cpu.set_cx(0xEEF2);
    cpu.set_dx(0xAEEC);
    cpu.set_cs(0xD5CE);
    cpu.set_ss(0x8AE7);
    cpu.set_ds(0x41D3);
    cpu.set_es(0x1F65);
    cpu.set_sp(0xA23C);
    cpu.set_bp(0xE09A);
    cpu.set_si(0xF8C0);
    cpu.set_di(0x0360);
    cpu.set_ip(0x47B9);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDA499, 0xCF);
    machine.mem_store_byte(0xDA49A, 0x90);
    machine.mem_store_byte(0xDA49B, 0x90);
    machine.mem_store_byte(0xDA49C, 0x90);
    machine.mem_store_byte(0xDA49D, 0x90);
    machine.mem_store_byte(0x950AC, 0xBE);
    machine.mem_store_byte(0x950AD, 0x32);
    machine.mem_store_byte(0x950AE, 0xCB);
    machine.mem_store_byte(0x950AF, 0x00);
    machine.mem_store_byte(0x950B0, 0xFF);
    machine.mem_store_byte(0x950B1, 0x58);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x00CB);
    EXPECT_EQ(cpu.get_sp(), 0xA242);
    EXPECT_EQ(cpu.get_ip(), 0x32BE);
    EXPECT_EQ(cpu.get_flags(), 0xF8D7) << show_flags(0xF8D7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDA499), 0xCF);
    EXPECT_EQ(memory.load8(0xDA49A), 0x90);
    EXPECT_EQ(memory.load8(0xDA49B), 0x90);
    EXPECT_EQ(memory.load8(0xDA49C), 0x90);
    EXPECT_EQ(memory.load8(0xDA49D), 0x90);
    EXPECT_EQ(memory.load8(0x950AC), 0xBE);
    EXPECT_EQ(memory.load8(0x950AD), 0x32);
    EXPECT_EQ(memory.load8(0x950AE), 0xCB);
    EXPECT_EQ(memory.load8(0x950AF), 0x00);
    EXPECT_EQ(memory.load8(0x950B0), 0xFF);
    EXPECT_EQ(memory.load8(0x950B1), 0x58);
}

TEST_F(MachineTest, jcxz_FFA1h)
{
    // Initial CPU State
    cpu.set_ax(0x8903);
    cpu.set_bx(0x6AC9);
    cpu.set_cx(0xC390);
    cpu.set_dx(0x672D);
    cpu.set_cs(0x6829);
    cpu.set_ss(0x7875);
    cpu.set_ds(0x21F9);
    cpu.set_es(0x359C);
    cpu.set_sp(0x04A0);
    cpu.set_bp(0xCA5A);
    cpu.set_si(0x71B2);
    cpu.set_di(0xC346);
    cpu.set_ip(0x956D);
    cpu.set_flags(0xF857);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x717FD, 0xE3);
    machine.mem_store_byte(0x717FE, 0x9F);
    machine.mem_store_byte(0x717FF, 0x90);
    machine.mem_store_byte(0x71800, 0x90);
    machine.mem_store_byte(0x71801, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x956F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x717FD), 0xE3);
    EXPECT_EQ(memory.load8(0x717FE), 0x9F);
    EXPECT_EQ(memory.load8(0x717FF), 0x90);
    EXPECT_EQ(memory.load8(0x71800), 0x90);
    EXPECT_EQ(memory.load8(0x71801), 0x90);
}

TEST_F(MachineTest, jmp_000Bh)
{
    // Initial CPU State
    cpu.set_ax(0xF329);
    cpu.set_bx(0xEE28);
    cpu.set_cx(0xFC80);
    cpu.set_dx(0x201D);
    cpu.set_cs(0x0E97);
    cpu.set_ss(0x2246);
    cpu.set_ds(0x8D4F);
    cpu.set_es(0xD24F);
    cpu.set_sp(0xE2A8);
    cpu.set_bp(0xEDC7);
    cpu.set_si(0xE949);
    cpu.set_di(0x35E3);
    cpu.set_ip(0xB3AD);
    cpu.set_flags(0xFCC6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x19D1D, 0xEB);
    machine.mem_store_byte(0x19D1E, 0x09);
    machine.mem_store_byte(0x19D1F, 0x90);
    machine.mem_store_byte(0x19D20, 0x90);
    machine.mem_store_byte(0x19D21, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB3B8);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x19D1D), 0xEB);
    EXPECT_EQ(memory.load8(0x19D1E), 0x09);
    EXPECT_EQ(memory.load8(0x19D1F), 0x90);
    EXPECT_EQ(memory.load8(0x19D20), 0x90);
    EXPECT_EQ(memory.load8(0x19D21), 0x90);
}

TEST_F(MachineTest, jmp_C068h)
{
    // Initial CPU State
    cpu.set_ax(0xF6F0);
    cpu.set_bx(0xBF7E);
    cpu.set_cx(0x708A);
    cpu.set_dx(0xA6C0);
    cpu.set_cs(0x155A);
    cpu.set_ss(0xA9FD);
    cpu.set_ds(0x929C);
    cpu.set_es(0x710F);
    cpu.set_sp(0x41F2);
    cpu.set_bp(0x4A3F);
    cpu.set_si(0x0000);
    cpu.set_di(0xC1D6);
    cpu.set_ip(0x4241);
    cpu.set_flags(0xF802);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x197E1, 0x3E);
    machine.mem_store_byte(0x197E2, 0xE9);
    machine.mem_store_byte(0x197E3, 0x64);
    machine.mem_store_byte(0x197E4, 0xC0);
    machine.mem_store_byte(0x197E5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x02A9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x197E1), 0x3E);
    EXPECT_EQ(memory.load8(0x197E2), 0xE9);
    EXPECT_EQ(memory.load8(0x197E3), 0x64);
    EXPECT_EQ(memory.load8(0x197E4), 0xC0);
    EXPECT_EQ(memory.load8(0x197E5), 0x90);
}

TEST_F(MachineTest, jmp_word_ds_bx_si_50EFh)
{
    // Initial CPU State
    cpu.set_ax(0x119D);
    cpu.set_bx(0x839F);
    cpu.set_cx(0xB6B8);
    cpu.set_dx(0xDBDE);
    cpu.set_cs(0xC1AE);
    cpu.set_ss(0xB1B4);
    cpu.set_ds(0xB609);
    cpu.set_es(0x5CFD);
    cpu.set_sp(0xFC7B);
    cpu.set_bp(0xCD33);
    cpu.set_si(0xA4EC);
    cpu.set_di(0x5A2C);
    cpu.set_ip(0x2FF2);
    cpu.set_flags(0xF843);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC4AD2, 0xFF);
    machine.mem_store_byte(0xC4AD3, 0xA0);
    machine.mem_store_byte(0xC4AD4, 0x11);
    machine.mem_store_byte(0xC4AD5, 0xAF);
    machine.mem_store_byte(0xC4AD6, 0x90);
    machine.mem_store_byte(0xC4AD7, 0x90);
    machine.mem_store_byte(0xC382C, 0xAF);
    machine.mem_store_byte(0xC382D, 0xD2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xD2AF);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC4AD2), 0xFF);
    EXPECT_EQ(memory.load8(0xC4AD3), 0xA0);
    EXPECT_EQ(memory.load8(0xC4AD4), 0x11);
    EXPECT_EQ(memory.load8(0xC4AD5), 0xAF);
    EXPECT_EQ(memory.load8(0xC4AD6), 0x90);
    EXPECT_EQ(memory.load8(0xC4AD7), 0x90);
    EXPECT_EQ(memory.load8(0xC382C), 0xAF);
    EXPECT_EQ(memory.load8(0xC382D), 0xD2);
}

TEST_F(MachineTest, jmpf_819Bh_257Eh)
{
    // Initial CPU State
    cpu.set_ax(0xA0AF);
    cpu.set_bx(0xFA5B);
    cpu.set_cx(0x6B16);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x9ACA);
    cpu.set_ss(0x0A6C);
    cpu.set_ds(0x58C1);
    cpu.set_es(0x9702);
    cpu.set_sp(0x8F5A);
    cpu.set_bp(0x7943);
    cpu.set_si(0x8E03);
    cpu.set_di(0x1930);
    cpu.set_ip(0x638F);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA102F, 0xEA);
    machine.mem_store_byte(0xA1030, 0x7E);
    machine.mem_store_byte(0xA1031, 0x25);
    machine.mem_store_byte(0xA1032, 0x9B);
    machine.mem_store_byte(0xA1033, 0x81);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x819B);
    EXPECT_EQ(cpu.get_ip(), 0x257E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA102F), 0xEA);
    EXPECT_EQ(memory.load8(0xA1030), 0x7E);
    EXPECT_EQ(memory.load8(0xA1031), 0x25);
    EXPECT_EQ(memory.load8(0xA1032), 0x9B);
    EXPECT_EQ(memory.load8(0xA1033), 0x81);
}

TEST_F(MachineTest, jmpf_word_cs_si)
{
    // Initial CPU State
    cpu.set_ax(0x1B5B);
    cpu.set_bx(0xCBDB);
    cpu.set_cx(0x5A5A);
    cpu.set_dx(0xD839);
    cpu.set_cs(0xA272);
    cpu.set_ss(0x5E81);
    cpu.set_ds(0xF219);
    cpu.set_es(0xEF1E);
    cpu.set_sp(0x5850);
    cpu.set_bp(0x646C);
    cpu.set_si(0x8953);
    cpu.set_di(0x0E0A);
    cpu.set_ip(0x8812);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAAF32, 0x2E);
    machine.mem_store_byte(0xAAF33, 0xFF);
    machine.mem_store_byte(0xAAF34, 0x2C);
    machine.mem_store_byte(0xAAF35, 0x90);
    machine.mem_store_byte(0xAAF36, 0x90);
    machine.mem_store_byte(0xAAF37, 0x90);
    machine.mem_store_byte(0xAB073, 0x7A);
    machine.mem_store_byte(0xAB074, 0x96);
    machine.mem_store_byte(0xAB075, 0x3E);
    machine.mem_store_byte(0xAB076, 0xF3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0xF33E);
    EXPECT_EQ(cpu.get_ip(), 0x967A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAAF32), 0x2E);
    EXPECT_EQ(memory.load8(0xAAF33), 0xFF);
    EXPECT_EQ(memory.load8(0xAAF34), 0x2C);
    EXPECT_EQ(memory.load8(0xAAF35), 0x90);
    EXPECT_EQ(memory.load8(0xAAF36), 0x90);
    EXPECT_EQ(memory.load8(0xAAF37), 0x90);
    EXPECT_EQ(memory.load8(0xAB073), 0x7A);
    EXPECT_EQ(memory.load8(0xAB074), 0x96);
    EXPECT_EQ(memory.load8(0xAB075), 0x3E);
    EXPECT_EQ(memory.load8(0xAB076), 0xF3);
}

TEST_F(MachineTest, loop_0025h)
{
    // Initial CPU State
    cpu.set_ax(0x9479);
    cpu.set_bx(0xEE48);
    cpu.set_cx(0x5922);
    cpu.set_dx(0x5D32);
    cpu.set_cs(0xDFAA);
    cpu.set_ss(0x5962);
    cpu.set_ds(0xA238);
    cpu.set_es(0x19FE);
    cpu.set_sp(0x87CB);
    cpu.set_bp(0x1CC4);
    cpu.set_si(0x0000);
    cpu.set_di(0x5CBE);
    cpu.set_ip(0xAB8C);
    cpu.set_flags(0xF803);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEA62C, 0xE2);
    machine.mem_store_byte(0xEA62D, 0x23);
    machine.mem_store_byte(0xEA62E, 0x90);
    machine.mem_store_byte(0xEA62F, 0x90);
    machine.mem_store_byte(0xEA630, 0x90);
    machine.mem_store_byte(0xEA631, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x5921);
    EXPECT_EQ(cpu.get_ip(), 0xABB1);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEA62C), 0xE2);
    EXPECT_EQ(memory.load8(0xEA62D), 0x23);
    EXPECT_EQ(memory.load8(0xEA62E), 0x90);
    EXPECT_EQ(memory.load8(0xEA62F), 0x90);
    EXPECT_EQ(memory.load8(0xEA630), 0x90);
    EXPECT_EQ(memory.load8(0xEA631), 0x90);
}

TEST_F(MachineTest, loope_FFF8h)
{
    // Initial CPU State
    cpu.set_ax(0x37EC);
    cpu.set_bx(0x5B4B);
    cpu.set_cx(0x5722);
    cpu.set_dx(0x3B96);
    cpu.set_cs(0x34D5);
    cpu.set_ss(0xA1F6);
    cpu.set_ds(0xB0FC);
    cpu.set_es(0xCE95);
    cpu.set_sp(0xB04E);
    cpu.set_bp(0x0000);
    cpu.set_si(0x9E8A);
    cpu.set_di(0xF95F);
    cpu.set_ip(0x763F);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3C38F, 0x2E);
    machine.mem_store_byte(0x3C390, 0xE1);
    machine.mem_store_byte(0x3C391, 0xF5);
    machine.mem_store_byte(0x3C392, 0x90);
    machine.mem_store_byte(0x3C393, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x5721);
    EXPECT_EQ(cpu.get_ip(), 0x7637);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3C38F), 0x2E);
    EXPECT_EQ(memory.load8(0x3C390), 0xE1);
    EXPECT_EQ(memory.load8(0x3C391), 0xF5);
    EXPECT_EQ(memory.load8(0x3C392), 0x90);
    EXPECT_EQ(memory.load8(0x3C393), 0x90);
}

TEST_F(MachineTest, loopne_FFCAh)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0xDDD7);
    cpu.set_cx(0x6E02);
    cpu.set_dx(0x2B73);
    cpu.set_cs(0x7132);
    cpu.set_ss(0x2E04);
    cpu.set_ds(0x74EF);
    cpu.set_es(0x58C2);
    cpu.set_sp(0xCB8D);
    cpu.set_bp(0xFD39);
    cpu.set_si(0x1B29);
    cpu.set_di(0x203D);
    cpu.set_ip(0xA72A);
    cpu.set_flags(0xF443);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7BA4A, 0x2E);
    machine.mem_store_byte(0x7BA4B, 0xE0);
    machine.mem_store_byte(0x7BA4C, 0xC7);
    machine.mem_store_byte(0x7BA4D, 0x90);
    machine.mem_store_byte(0x7BA4E, 0x90);
    machine.mem_store_byte(0x7BA4F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x6E01);
    EXPECT_EQ(cpu.get_ip(), 0xA72D);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7BA4A), 0x2E);
    EXPECT_EQ(memory.load8(0x7BA4B), 0xE0);
    EXPECT_EQ(memory.load8(0x7BA4C), 0xC7);
    EXPECT_EQ(memory.load8(0x7BA4D), 0x90);
    EXPECT_EQ(memory.load8(0x7BA4E), 0x90);
    EXPECT_EQ(memory.load8(0x7BA4F), 0x90);
}

TEST_F(MachineTest, retf)
{
    // Initial CPU State
    cpu.set_ax(0x5FEE);
    cpu.set_bx(0x0B19);
    cpu.set_cx(0x961E);
    cpu.set_dx(0x8470);
    cpu.set_cs(0x9750);
    cpu.set_ss(0x46BC);
    cpu.set_ds(0xA07C);
    cpu.set_es(0xF478);
    cpu.set_sp(0x38CF);
    cpu.set_bp(0xCF8C);
    cpu.set_si(0xD6EB);
    cpu.set_di(0x1275);
    cpu.set_ip(0xF319);
    cpu.set_flags(0xF0C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA6819, 0xCB);
    machine.mem_store_byte(0xA681A, 0x90);
    machine.mem_store_byte(0xA681B, 0x90);
    machine.mem_store_byte(0xA681C, 0x90);
    machine.mem_store_byte(0xA681D, 0x90);
    machine.mem_store_byte(0x4A48F, 0x51);
    machine.mem_store_byte(0x4A490, 0x5A);
    machine.mem_store_byte(0x4A491, 0x7E);
    machine.mem_store_byte(0x4A492, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x007E);
    EXPECT_EQ(cpu.get_sp(), 0x38D3);
    EXPECT_EQ(cpu.get_ip(), 0x5A51);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA6819), 0xCB);
    EXPECT_EQ(memory.load8(0xA681A), 0x90);
    EXPECT_EQ(memory.load8(0xA681B), 0x90);
    EXPECT_EQ(memory.load8(0xA681C), 0x90);
    EXPECT_EQ(memory.load8(0xA681D), 0x90);
    EXPECT_EQ(memory.load8(0x4A48F), 0x51);
    EXPECT_EQ(memory.load8(0x4A490), 0x5A);
    EXPECT_EQ(memory.load8(0x4A491), 0x7E);
    EXPECT_EQ(memory.load8(0x4A492), 0x00);
}

TEST_F(MachineTest, retf_3A14h)
{
    // Initial CPU State
    cpu.set_ax(0x3CCC);
    cpu.set_bx(0xD6A9);
    cpu.set_cx(0x458E);
    cpu.set_dx(0x7791);
    cpu.set_cs(0xB240);
    cpu.set_ss(0x5C08);
    cpu.set_ds(0xA903);
    cpu.set_es(0xD987);
    cpu.set_sp(0xD1F9);
    cpu.set_bp(0x5A4A);
    cpu.set_si(0x52AB);
    cpu.set_di(0xB443);
    cpu.set_ip(0xF288);
    cpu.set_flags(0xF4D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC1688, 0xC8);
    machine.mem_store_byte(0xC1689, 0x14);
    machine.mem_store_byte(0xC168A, 0x3A);
    machine.mem_store_byte(0xC168B, 0x90);
    machine.mem_store_byte(0xC168C, 0x90);
    machine.mem_store_byte(0xC168D, 0x90);
    machine.mem_store_byte(0x69279, 0x23);
    machine.mem_store_byte(0x6927A, 0xBB);
    machine.mem_store_byte(0x6927B, 0x49);
    machine.mem_store_byte(0x6927C, 0xDC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0xDC49);
    EXPECT_EQ(cpu.get_sp(), 0x0C11);
    EXPECT_EQ(cpu.get_ip(), 0xBB23);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC1688), 0xC8);
    EXPECT_EQ(memory.load8(0xC1689), 0x14);
    EXPECT_EQ(memory.load8(0xC168A), 0x3A);
    EXPECT_EQ(memory.load8(0xC168B), 0x90);
    EXPECT_EQ(memory.load8(0xC168C), 0x90);
    EXPECT_EQ(memory.load8(0xC168D), 0x90);
    EXPECT_EQ(memory.load8(0x69279), 0x23);
    EXPECT_EQ(memory.load8(0x6927A), 0xBB);
    EXPECT_EQ(memory.load8(0x6927B), 0x49);
    EXPECT_EQ(memory.load8(0x6927C), 0xDC);
}

TEST_F(MachineTest, retf_84A2h)
{
    // Initial CPU State
    cpu.set_ax(0x4C3D);
    cpu.set_bx(0x8D35);
    cpu.set_cx(0x190C);
    cpu.set_dx(0x4EF9);
    cpu.set_cs(0xC4BA);
    cpu.set_ss(0xA4C4);
    cpu.set_ds(0xF703);
    cpu.set_es(0x0E08);
    cpu.set_sp(0x0219);
    cpu.set_bp(0x5C94);
    cpu.set_si(0xF8AF);
    cpu.set_di(0xF603);
    cpu.set_ip(0x37AE);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC834E, 0xCA);
    machine.mem_store_byte(0xC834F, 0xA2);
    machine.mem_store_byte(0xC8350, 0x84);
    machine.mem_store_byte(0xC8351, 0x90);
    machine.mem_store_byte(0xC8352, 0x90);
    machine.mem_store_byte(0xC8353, 0x90);
    machine.mem_store_byte(0xA4E59, 0x64);
    machine.mem_store_byte(0xA4E5A, 0xA1);
    machine.mem_store_byte(0xA4E5B, 0xFA);
    machine.mem_store_byte(0xA4E5C, 0x37);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x37FA);
    EXPECT_EQ(cpu.get_sp(), 0x86BF);
    EXPECT_EQ(cpu.get_ip(), 0xA164);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC834E), 0xCA);
    EXPECT_EQ(memory.load8(0xC834F), 0xA2);
    EXPECT_EQ(memory.load8(0xC8350), 0x84);
    EXPECT_EQ(memory.load8(0xC8351), 0x90);
    EXPECT_EQ(memory.load8(0xC8352), 0x90);
    EXPECT_EQ(memory.load8(0xC8353), 0x90);
    EXPECT_EQ(memory.load8(0xA4E59), 0x64);
    EXPECT_EQ(memory.load8(0xA4E5A), 0xA1);
    EXPECT_EQ(memory.load8(0xA4E5B), 0xFA);
    EXPECT_EQ(memory.load8(0xA4E5C), 0x37);
}

TEST_F(MachineTest, retn)
{
    // Initial CPU State
    cpu.set_ax(0xB9F9);
    cpu.set_bx(0x5D16);
    cpu.set_cx(0xB612);
    cpu.set_dx(0x77EA);
    cpu.set_cs(0x5BDA);
    cpu.set_ss(0x3D66);
    cpu.set_ds(0x1865);
    cpu.set_es(0x97F6);
    cpu.set_sp(0x74E1);
    cpu.set_bp(0x2112);
    cpu.set_si(0xF5A7);
    cpu.set_di(0x72CB);
    cpu.set_ip(0xF989);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6B729, 0xC3);
    machine.mem_store_byte(0x6B72A, 0x90);
    machine.mem_store_byte(0x6B72B, 0x90);
    machine.mem_store_byte(0x6B72C, 0x90);
    machine.mem_store_byte(0x6B72D, 0x90);
    machine.mem_store_byte(0x44B41, 0xAD);
    machine.mem_store_byte(0x44B42, 0x40);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x74E3);
    EXPECT_EQ(cpu.get_ip(), 0x40AD);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6B729), 0xC3);
    EXPECT_EQ(memory.load8(0x6B72A), 0x90);
    EXPECT_EQ(memory.load8(0x6B72B), 0x90);
    EXPECT_EQ(memory.load8(0x6B72C), 0x90);
    EXPECT_EQ(memory.load8(0x6B72D), 0x90);
    EXPECT_EQ(memory.load8(0x44B41), 0xAD);
    EXPECT_EQ(memory.load8(0x44B42), 0x40);
}

TEST_F(MachineTest, retn_4D91h)
{
    // Initial CPU State
    cpu.set_ax(0xD0C2);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x28FC);
    cpu.set_dx(0xEA13);
    cpu.set_cs(0x05BB);
    cpu.set_ss(0x481C);
    cpu.set_ds(0xFF8E);
    cpu.set_es(0x835B);
    cpu.set_sp(0xBFD2);
    cpu.set_bp(0xC601);
    cpu.set_si(0x6952);
    cpu.set_di(0x3FC7);
    cpu.set_ip(0x8EFB);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0EAAB, 0xC2);
    machine.mem_store_byte(0x0EAAC, 0x91);
    machine.mem_store_byte(0x0EAAD, 0x4D);
    machine.mem_store_byte(0x0EAAE, 0x90);
    machine.mem_store_byte(0x0EAAF, 0x90);
    machine.mem_store_byte(0x54192, 0xE1);
    machine.mem_store_byte(0x54193, 0xB1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x0D65);
    EXPECT_EQ(cpu.get_ip(), 0xB1E1);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0EAAB), 0xC2);
    EXPECT_EQ(memory.load8(0x0EAAC), 0x91);
    EXPECT_EQ(memory.load8(0x0EAAD), 0x4D);
    EXPECT_EQ(memory.load8(0x0EAAE), 0x90);
    EXPECT_EQ(memory.load8(0x0EAAF), 0x90);
    EXPECT_EQ(memory.load8(0x54192), 0xE1);
    EXPECT_EQ(memory.load8(0x54193), 0xB1);
}

TEST_F(MachineTest, retn_F671h)
{
    // Initial CPU State
    cpu.set_ax(0xDE4B);
    cpu.set_bx(0x147C);
    cpu.set_cx(0xA574);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xC836);
    cpu.set_ss(0x4479);
    cpu.set_ds(0x85F6);
    cpu.set_es(0xEECC);
    cpu.set_sp(0xD3B7);
    cpu.set_bp(0x0000);
    cpu.set_si(0xBE49);
    cpu.set_di(0x24CD);
    cpu.set_ip(0x378D);
    cpu.set_flags(0xFCC6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCBAED, 0xC0);
    machine.mem_store_byte(0xCBAEE, 0x71);
    machine.mem_store_byte(0xCBAEF, 0xF6);
    machine.mem_store_byte(0xCBAF0, 0x90);
    machine.mem_store_byte(0xCBAF1, 0x90);
    machine.mem_store_byte(0x51B47, 0x21);
    machine.mem_store_byte(0x51B48, 0x87);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xCA2A);
    EXPECT_EQ(cpu.get_ip(), 0x8721);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCBAED), 0xC0);
    EXPECT_EQ(memory.load8(0xCBAEE), 0x71);
    EXPECT_EQ(memory.load8(0xCBAEF), 0xF6);
    EXPECT_EQ(memory.load8(0xCBAF0), 0x90);
    EXPECT_EQ(memory.load8(0xCBAF1), 0x90);
    EXPECT_EQ(memory.load8(0x51B47), 0x21);
    EXPECT_EQ(memory.load8(0x51B48), 0x87);
}
