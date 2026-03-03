#include "test386.h"

//
// bound esi,[gs:bp+5283h]
//
TEST_F(Test386, bound_esi_gs_bp_5283h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x80000000);
    cpu.set_ebx(0x37C9BF77);
    cpu.set_ecx(0x033F5868);
    cpu.set_edx(0xD3E7B32D);
    cpu.set_esi(0xF7AA0FB6);
    cpu.set_edi(0x1637BB67);
    cpu.set_ebp(0xDED841D2);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000DCF1);
    cpu.set_ds(0x00005740);
    cpu.set_es(0x00006CDE);
    cpu.set_fs(0x000000F6);
    cpu.set_gs(0x00009999);
    cpu.set_ss(0x0000AEA8);
    cpu.set_eip(0x0000C680);
    cpu.set_eflags(0xFFFC00C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE9590, 0x65);
    machine.mem_store_byte(0xE9591, 0x66);
    machine.mem_store_byte(0xE9592, 0x62);
    machine.mem_store_byte(0xE9593, 0xB6);
    machine.mem_store_byte(0xE9594, 0x83);
    machine.mem_store_byte(0xE9595, 0x52);
    machine.mem_store_byte(0xE9596, 0xF4);
    machine.mem_store_byte(0xE9597, 0x4F);
    machine.mem_store_byte(0xE9598, 0x71);
    machine.mem_store_byte(0xE9599, 0x06);
    machine.mem_store_byte(0xE959A, 0x12);
    machine.mem_store_byte(0xE959B, 0x2D);
    machine.mem_store_byte(0xA2DE8, 0x6A);
    machine.mem_store_byte(0xA2DE5, 0x99);
    machine.mem_store_byte(0xA2DE6, 0xE7);
    machine.mem_store_byte(0xA2DE7, 0x1F);
    machine.mem_store_byte(0xA2DEC, 0x8C);
    machine.mem_store_byte(0xA2DE9, 0x55);
    machine.mem_store_byte(0xA2DEA, 0x05);
    machine.mem_store_byte(0xA2DEB, 0x77);
    machine.mem_store_byte(0xE959C, 0xCF);
    machine.mem_store_byte(0xE959D, 0x24);
    machine.mem_store_byte(0xE959E, 0x61);
    machine.mem_store_byte(0xE959F, 0x6A);
    machine.mem_store_byte(0xE95A0, 0x52);
    machine.mem_store_byte(0xE95A1, 0x70);
    machine.mem_store_byte(0x00014, 0xBB);
    machine.mem_store_byte(0x00015, 0xD0);
    machine.mem_store_byte(0x00016, 0x3F);
    machine.mem_store_byte(0x00017, 0x6D);
    machine.mem_store_byte(0x7A4AA, 0x89);
    machine.mem_store_byte(0x7A4AB, 0xF4);
    machine.mem_store_byte(0x7A4AC, 0x7B);
    machine.mem_store_byte(0x7A4AD, 0xF4);
    machine.mem_store_byte(0x7A4AE, 0x2A);
    machine.mem_store_byte(0x7A4AF, 0xF4);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x80000000);
    EXPECT_EQ(cpu.get_ebx(), 0x37C9BF77);
    EXPECT_EQ(cpu.get_ecx(), 0x033F5868);
    EXPECT_EQ(cpu.get_edx(), 0xD3E7B32D);
    EXPECT_EQ(cpu.get_esi(), 0xF7AA0FB6);
    EXPECT_EQ(cpu.get_edi(), 0x1637BB67);
    EXPECT_EQ(cpu.get_ebp(), 0xDED841D2);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x00006D3F);
    EXPECT_EQ(cpu.get_ds(), 0x00005740);
    EXPECT_EQ(cpu.get_es(), 0x00006CDE);
    EXPECT_EQ(cpu.get_fs(), 0x000000F6);
    EXPECT_EQ(cpu.get_gs(), 0x00009999);
    EXPECT_EQ(cpu.get_ss(), 0x0000AEA8);
    EXPECT_EQ(cpu.get_eip(), 0x0000D0BC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBEA7C), 0xC6);
    EXPECT_EQ(memory.load8(0xBEA7D), 0x00);
    EXPECT_EQ(memory.load8(0xBEA7A), 0xF1);
    EXPECT_EQ(memory.load8(0xBEA7B), 0xDC);
    EXPECT_EQ(memory.load8(0xBEA78), 0x80);
    EXPECT_EQ(memory.load8(0xBEA79), 0xC6);
}

//
// bound ax,[ds:esi+1181h]
//
TEST_F(Test386, bound_ax_ds_esi_1181h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x4C00DE6B);
    cpu.set_ebx(0xF6A6BA12);
    cpu.set_ecx(0xB9B73087);
    cpu.set_edx(0x4B75F359);
    cpu.set_esi(0x00003916);
    cpu.set_edi(0xAD238C27);
    cpu.set_ebp(0x84553ADE);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x000041F9);
    cpu.set_ds(0x0000FCF9);
    cpu.set_es(0x00004602);
    cpu.set_fs(0x00002FBD);
    cpu.set_gs(0x00009E0E);
    cpu.set_ss(0x0000FF3F);
    cpu.set_eip(0x00004A38);
    cpu.set_eflags(0xFFFC00C7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x469C8, 0x3E);
    machine.mem_store_byte(0x469C9, 0x67);
    machine.mem_store_byte(0x469CA, 0x62);
    machine.mem_store_byte(0x469CB, 0x86);
    machine.mem_store_byte(0x469CC, 0x81);
    machine.mem_store_byte(0x469CD, 0x11);
    machine.mem_store_byte(0x469CE, 0x00);
    machine.mem_store_byte(0x469CF, 0x00);
    machine.mem_store_byte(0x469D0, 0xF4);
    machine.mem_store_byte(0x469D1, 0xEA);
    machine.mem_store_byte(0x469D2, 0x9E);
    machine.mem_store_byte(0x469D3, 0x62);
    machine.mem_store_byte(0x101A28, 0xBD);
    machine.mem_store_byte(0x101A27, 0xA9);
    machine.mem_store_byte(0x101A29, 0x1B);
    machine.mem_store_byte(0x101A2A, 0x75);
    machine.mem_store_byte(0x469D4, 0x4C);
    machine.mem_store_byte(0x469D5, 0x47);
    machine.mem_store_byte(0x469D6, 0xB9);
    machine.mem_store_byte(0x469D7, 0x37);
    machine.mem_store_byte(0x469D8, 0xEA);
    machine.mem_store_byte(0x469D9, 0x04);
    machine.mem_store_byte(0x469DA, 0xD6);
    machine.mem_store_byte(0x469DB, 0xCC);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x4C00DE6B);
    EXPECT_EQ(cpu.get_ebx(), 0xF6A6BA12);
    EXPECT_EQ(cpu.get_ecx(), 0xB9B73087);
    EXPECT_EQ(cpu.get_edx(), 0x4B75F359);
    EXPECT_EQ(cpu.get_esi(), 0x00003916);
    EXPECT_EQ(cpu.get_edi(), 0xAD238C27);
    EXPECT_EQ(cpu.get_ebp(), 0x84553ADE);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x000041F9);
    EXPECT_EQ(cpu.get_ds(), 0x0000FCF9);
    EXPECT_EQ(cpu.get_es(), 0x00004602);
    EXPECT_EQ(cpu.get_fs(), 0x00002FBD);
    EXPECT_EQ(cpu.get_gs(), 0x00009E0E);
    EXPECT_EQ(cpu.get_ss(), 0x0000FF3F);
    EXPECT_EQ(cpu.get_eip(), 0x00004A41);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C7);

    // Final RAM entries
}

//
// bsf cx,bp
//
TEST_F(Test386, bsf_cx_bp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF8D565E4);
    cpu.set_ebx(0x12E575D4);
    cpu.set_ecx(0x9B4A031D);
    cpu.set_edx(0xB2577266);
    cpu.set_esi(0x0BCE6F01);
    cpu.set_edi(0xFCD84A68);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x0000F7D2);
    cpu.set_cs(0x0000ECDF);
    cpu.set_ds(0x0000920B);
    cpu.set_es(0x0000AF35);
    cpu.set_fs(0x0000FEA2);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x000043CD);
    cpu.set_eip(0x0000EBA8);
    cpu.set_eflags(0xFFFC0497);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFB998, 0x67);
    machine.mem_store_byte(0xFB999, 0x0F);
    machine.mem_store_byte(0xFB99A, 0xBC);
    machine.mem_store_byte(0xFB99B, 0xCD);
    machine.mem_store_byte(0xFB99C, 0xF4);
    machine.mem_store_byte(0xFB99D, 0x81);
    machine.mem_store_byte(0xFB99E, 0x43);
    machine.mem_store_byte(0xFB99F, 0x98);
    machine.mem_store_byte(0xFB9A0, 0x48);
    machine.mem_store_byte(0xFB9A1, 0xAB);
    machine.mem_store_byte(0xFB9A2, 0x71);
    machine.mem_store_byte(0xFB9A3, 0xED);
    machine.mem_store_byte(0xFB9A4, 0xE6);
    machine.mem_store_byte(0xFB9A5, 0x84);
    machine.mem_store_byte(0xFB9A6, 0xE9);
    machine.mem_store_byte(0xFB9A7, 0xFE);
    machine.mem_store_byte(0xFB9A8, 0xD7);
    machine.mem_store_byte(0xFB9A9, 0x4A);
    machine.mem_store_byte(0xFB9AA, 0x92);
    machine.mem_store_byte(0xFB9AB, 0x7C);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF8D565E4);
    EXPECT_EQ(cpu.get_ebx(), 0x12E575D4);
    EXPECT_EQ(cpu.get_ecx(), 0x9B4A031D);
    EXPECT_EQ(cpu.get_edx(), 0xB2577266);
    EXPECT_EQ(cpu.get_esi(), 0x0BCE6F01);
    EXPECT_EQ(cpu.get_edi(), 0xFCD84A68);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x0000F7D2);
    EXPECT_EQ(cpu.get_cs(), 0x0000ECDF);
    EXPECT_EQ(cpu.get_ds(), 0x0000920B);
    EXPECT_EQ(cpu.get_es(), 0x0000AF35);
    EXPECT_EQ(cpu.get_fs(), 0x0000FEA2);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x000043CD);
    EXPECT_EQ(cpu.get_eip(), 0x0000EBAD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
}

//
// bsf ax,[ss:bp-3D51h]
//
TEST_F(Test386, bsf_ax_ss_bp_3D51h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x05E25D5F);
    cpu.set_ecx(0x24A52DFA);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x00008000);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0xAF67A572);
    cpu.set_esp(0x000061D8);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x000087EC);
    cpu.set_es(0x00007380);
    cpu.set_fs(0x00004D69);
    cpu.set_gs(0x0000FD1D);
    cpu.set_ss(0x00009456);
    cpu.set_eip(0x00005250);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05250, 0x0F);
    machine.mem_store_byte(0x05251, 0xBC);
    machine.mem_store_byte(0x05252, 0x86);
    machine.mem_store_byte(0x05253, 0xAF);
    machine.mem_store_byte(0x05254, 0xC2);
    machine.mem_store_byte(0x05255, 0xF4);
    machine.mem_store_byte(0x05256, 0xD2);
    machine.mem_store_byte(0x05257, 0x45);
    machine.mem_store_byte(0x05258, 0xFD);
    machine.mem_store_byte(0x05259, 0x33);
    machine.mem_store_byte(0x0525A, 0x61);
    machine.mem_store_byte(0x0525B, 0x52);
    machine.mem_store_byte(0x9AD81, 0x6B);
    machine.mem_store_byte(0x9AD82, 0x96);
    machine.mem_store_byte(0x0525C, 0xC9);
    machine.mem_store_byte(0x0525D, 0x74);
    machine.mem_store_byte(0x0525E, 0x3B);
    machine.mem_store_byte(0x0525F, 0xCD);
    machine.mem_store_byte(0x05260, 0x77);
    machine.mem_store_byte(0x05261, 0xF2);
    machine.mem_store_byte(0x05262, 0xAD);
    machine.mem_store_byte(0x05263, 0x5A);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0x05E25D5F);
    EXPECT_EQ(cpu.get_ecx(), 0x24A52DFA);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x00008000);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0xAF67A572);
    EXPECT_EQ(cpu.get_esp(), 0x000061D8);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x000087EC);
    EXPECT_EQ(cpu.get_es(), 0x00007380);
    EXPECT_EQ(cpu.get_fs(), 0x00004D69);
    EXPECT_EQ(cpu.get_gs(), 0x0000FD1D);
    EXPECT_EQ(cpu.get_ss(), 0x00009456);
    EXPECT_EQ(cpu.get_eip(), 0x00005256);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C17);

    // Final RAM entries
}

//
// bsf eax,[ss:bp-3D51h]
//
TEST_F(Test386, bsf_eax_ss_bp_3D51h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x05E25D5F);
    cpu.set_ecx(0x24A52DFA);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x00008000);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0xAF67A572);
    cpu.set_esp(0x000061D8);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x000087EC);
    cpu.set_es(0x00007380);
    cpu.set_fs(0x00004D69);
    cpu.set_gs(0x0000FD1D);
    cpu.set_ss(0x00009456);
    cpu.set_eip(0x00005250);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05250, 0x66);
    machine.mem_store_byte(0x05251, 0x0F);
    machine.mem_store_byte(0x05252, 0xBC);
    machine.mem_store_byte(0x05253, 0x86);
    machine.mem_store_byte(0x05254, 0xAF);
    machine.mem_store_byte(0x05255, 0xC2);
    machine.mem_store_byte(0x05256, 0xF4);
    machine.mem_store_byte(0x05257, 0x45);
    machine.mem_store_byte(0x05258, 0xFD);
    machine.mem_store_byte(0x05259, 0x33);
    machine.mem_store_byte(0x0525A, 0x61);
    machine.mem_store_byte(0x0525B, 0x52);
    machine.mem_store_byte(0x9AD84, 0x6B);
    machine.mem_store_byte(0x9AD81, 0x6B);
    machine.mem_store_byte(0x9AD82, 0x96);
    machine.mem_store_byte(0x9AD83, 0xC7);
    machine.mem_store_byte(0x0525C, 0xC9);
    machine.mem_store_byte(0x0525D, 0x74);
    machine.mem_store_byte(0x0525E, 0x3B);
    machine.mem_store_byte(0x0525F, 0xCD);
    machine.mem_store_byte(0x05260, 0x77);
    machine.mem_store_byte(0x05261, 0xF2);
    machine.mem_store_byte(0x05262, 0xAD);
    machine.mem_store_byte(0x05263, 0x5A);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0x05E25D5F);
    EXPECT_EQ(cpu.get_ecx(), 0x24A52DFA);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x00008000);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0xAF67A572);
    EXPECT_EQ(cpu.get_esp(), 0x000061D8);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x000087EC);
    EXPECT_EQ(cpu.get_es(), 0x00007380);
    EXPECT_EQ(cpu.get_fs(), 0x00004D69);
    EXPECT_EQ(cpu.get_gs(), 0x0000FD1D);
    EXPECT_EQ(cpu.get_ss(), 0x00009456);
    EXPECT_EQ(cpu.get_eip(), 0x00005257);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0497);

    // Final RAM entries
}

//
// bsr esi,[ds:ecx-70h]
//
TEST_F(Test386, bsr_esi_ds_ecx_70h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xBE8ABD51);
    cpu.set_ebx(0x015F3FF7);
    cpu.set_ecx(0x00006F28);
    cpu.set_edx(0x96A52E7C);
    cpu.set_esi(0x18762B26);
    cpu.set_edi(0x41F12272);
    cpu.set_ebp(0x8E57FDA5);
    cpu.set_esp(0x0000E5E4);
    cpu.set_cs(0x0000FF6C);
    cpu.set_ds(0x00007465);
    cpu.set_es(0x0000F668);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x0000E42E);
    cpu.set_ss(0x0000018C);
    cpu.set_eip(0x0000D568);
    cpu.set_eflags(0xFFFC0C56);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10CC28, 0x67);
    machine.mem_store_byte(0x10CC29, 0x66);
    machine.mem_store_byte(0x10CC2A, 0x0F);
    machine.mem_store_byte(0x10CC2B, 0xBD);
    machine.mem_store_byte(0x10CC2C, 0x71);
    machine.mem_store_byte(0x10CC2D, 0x90);
    machine.mem_store_byte(0x10CC2E, 0xF4);
    machine.mem_store_byte(0x10CC2F, 0xFE);
    machine.mem_store_byte(0x10CC30, 0x14);
    machine.mem_store_byte(0x10CC31, 0x45);
    machine.mem_store_byte(0x10CC32, 0x80);
    machine.mem_store_byte(0x10CC33, 0xF4);
    machine.mem_store_byte(0x10CC34, 0x53);
    machine.mem_store_byte(0x10CC35, 0x4D);
    machine.mem_store_byte(0x7B508, 0xBB);
    machine.mem_store_byte(0x7B509, 0xAB);
    machine.mem_store_byte(0x7B50A, 0xD4);
    machine.mem_store_byte(0x7B50B, 0x51);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xBE8ABD51);
    EXPECT_EQ(cpu.get_ebx(), 0x015F3FF7);
    EXPECT_EQ(cpu.get_ecx(), 0x00006F28);
    EXPECT_EQ(cpu.get_edx(), 0x96A52E7C);
    EXPECT_EQ(cpu.get_esi(), 0x0000001E);
    EXPECT_EQ(cpu.get_edi(), 0x41F12272);
    EXPECT_EQ(cpu.get_ebp(), 0x8E57FDA5);
    EXPECT_EQ(cpu.get_esp(), 0x0000E5E4);
    EXPECT_EQ(cpu.get_cs(), 0x0000FF6C);
    EXPECT_EQ(cpu.get_ds(), 0x00007465);
    EXPECT_EQ(cpu.get_es(), 0x0000F668);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000E42E);
    EXPECT_EQ(cpu.get_ss(), 0x0000018C);
    EXPECT_EQ(cpu.get_eip(), 0x0000D56F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C92);

    // Final RAM entries
}

//
// bt [ds:ecx+esi*1],dx
//
TEST_F(Test386, bt_ds_ecx_esi_1_dx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x108AD9DC);
    cpu.set_ebx(0x71DF7F71);
    cpu.set_ecx(0x00002516);
    cpu.set_edx(0xCE6CAE2E);
    cpu.set_esi(0x00007FFF);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x3BBAB5EB);
    cpu.set_esp(0x00006F11);
    cpu.set_cs(0x00004E41);
    cpu.set_ds(0x00008000);
    cpu.set_es(0x00000D51);
    cpu.set_fs(0x00007FFF);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x00007F20);
    cpu.set_eip(0x00005618);
    cpu.set_eflags(0xFFFC00D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x53A28, 0x67);
    machine.mem_store_byte(0x53A29, 0x0F);
    machine.mem_store_byte(0x53A2A, 0xA3);
    machine.mem_store_byte(0x53A2B, 0x14);
    machine.mem_store_byte(0x53A2C, 0x31);
    machine.mem_store_byte(0x53A2D, 0xF4);
    machine.mem_store_byte(0x53A2E, 0xFA);
    machine.mem_store_byte(0x53A2F, 0xD5);
    machine.mem_store_byte(0x53A30, 0x13);
    machine.mem_store_byte(0x53A31, 0x34);
    machine.mem_store_byte(0x53A32, 0x53);
    machine.mem_store_byte(0x53A33, 0x77);
    machine.mem_store_byte(0x53A34, 0xBC);
    machine.mem_store_byte(0x53A35, 0x5D);
    machine.mem_store_byte(0x53A36, 0x38);
    machine.mem_store_byte(0x53A37, 0x88);
    machine.mem_store_byte(0x53A38, 0x0C);
    machine.mem_store_byte(0x53A39, 0x57);
    machine.mem_store_byte(0x89AD9, 0x98);
    machine.mem_store_byte(0x89ADA, 0xD1);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x108AD9DC);
    EXPECT_EQ(cpu.get_ebx(), 0x71DF7F71);
    EXPECT_EQ(cpu.get_ecx(), 0x00002516);
    EXPECT_EQ(cpu.get_edx(), 0xCE6CAE2E);
    EXPECT_EQ(cpu.get_esi(), 0x00007FFF);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x3BBAB5EB);
    EXPECT_EQ(cpu.get_esp(), 0x00006F11);
    EXPECT_EQ(cpu.get_cs(), 0x00004E41);
    EXPECT_EQ(cpu.get_ds(), 0x00008000);
    EXPECT_EQ(cpu.get_es(), 0x00000D51);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x00007F20);
    EXPECT_EQ(cpu.get_eip(), 0x0000561E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D3);

    // Final RAM entries
}

//
// btc [ds:di-71CCh],dx
//
TEST_F(Test386, btc_ds_di_71CCh_dx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE9FA80ED);
    cpu.set_ebx(0x0000FF00);
    cpu.set_ecx(0x00000000);
    cpu.set_edx(0xD0660F6A);
    cpu.set_esi(0x1277FF18);
    cpu.set_edi(0xE1FFBC40);
    cpu.set_ebp(0x95E8BD16);
    cpu.set_esp(0x00005492);
    cpu.set_cs(0x000067FA);
    cpu.set_ds(0x0000FD2B);
    cpu.set_es(0x00006E66);
    cpu.set_fs(0x00009C17);
    cpu.set_gs(0x0000FCC7);
    cpu.set_ss(0x00007176);
    cpu.set_eip(0x0000D628);
    cpu.set_eflags(0xFFFC08D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x755C8, 0x0F);
    machine.mem_store_byte(0x755C9, 0xBB);
    machine.mem_store_byte(0x755CA, 0x95);
    machine.mem_store_byte(0x755CB, 0x34);
    machine.mem_store_byte(0x755CC, 0x8E);
    machine.mem_store_byte(0x755CD, 0xF4);
    machine.mem_store_byte(0x755CE, 0xC2);
    machine.mem_store_byte(0x755CF, 0xDA);
    machine.mem_store_byte(0x755D0, 0x84);
    machine.mem_store_byte(0x755D1, 0x76);
    machine.mem_store_byte(0x755D2, 0x78);
    machine.mem_store_byte(0x755D3, 0x01);
    machine.mem_store_byte(0x755D4, 0xC6);
    machine.mem_store_byte(0x755D5, 0xFB);
    machine.mem_store_byte(0x101F10, 0x64);
    machine.mem_store_byte(0x101F11, 0x15);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE9FA80ED);
    EXPECT_EQ(cpu.get_ebx(), 0x0000FF00);
    EXPECT_EQ(cpu.get_ecx(), 0x00000000);
    EXPECT_EQ(cpu.get_edx(), 0xD0660F6A);
    EXPECT_EQ(cpu.get_esi(), 0x1277FF18);
    EXPECT_EQ(cpu.get_edi(), 0xE1FFBC40);
    EXPECT_EQ(cpu.get_ebp(), 0x95E8BD16);
    EXPECT_EQ(cpu.get_esp(), 0x00005492);
    EXPECT_EQ(cpu.get_cs(), 0x000067FA);
    EXPECT_EQ(cpu.get_ds(), 0x0000FD2B);
    EXPECT_EQ(cpu.get_es(), 0x00006E66);
    EXPECT_EQ(cpu.get_fs(), 0x00009C17);
    EXPECT_EQ(cpu.get_gs(), 0x0000FCC7);
    EXPECT_EQ(cpu.get_ss(), 0x00007176);
    EXPECT_EQ(cpu.get_eip(), 0x0000D62E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x101F11), 0x11);
}

//
// btr cx,bp
//
TEST_F(Test386, btr_cx_bp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0805A97D);
    cpu.set_ebx(0xAD055ADF);
    cpu.set_ecx(0x074908E8);
    cpu.set_edx(0xD8D6A556);
    cpu.set_esi(0x334D3CB6);
    cpu.set_edi(0x10987C31);
    cpu.set_ebp(0xECD83A82);
    cpu.set_esp(0x00008000);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00001001);
    cpu.set_es(0x0000E6AA);
    cpu.set_fs(0x00006ED7);
    cpu.set_gs(0x0000D637);
    cpu.set_ss(0x0000FF09);
    cpu.set_eip(0x00005130);
    cpu.set_eflags(0xFFFC0CC7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x105120, 0x67);
    machine.mem_store_byte(0x105121, 0x0F);
    machine.mem_store_byte(0x105122, 0xB3);
    machine.mem_store_byte(0x105123, 0xE9);
    machine.mem_store_byte(0x105124, 0xF4);
    machine.mem_store_byte(0x105125, 0x94);
    machine.mem_store_byte(0x105126, 0x35);
    machine.mem_store_byte(0x105127, 0xD8);
    machine.mem_store_byte(0x105128, 0x69);
    machine.mem_store_byte(0x105129, 0x1D);
    machine.mem_store_byte(0x10512A, 0x18);
    machine.mem_store_byte(0x10512B, 0x0A);
    machine.mem_store_byte(0x10512C, 0x85);
    machine.mem_store_byte(0x10512D, 0x07);
    machine.mem_store_byte(0x10512E, 0x26);
    machine.mem_store_byte(0x10512F, 0xAA);
    machine.mem_store_byte(0x105130, 0xC4);
    machine.mem_store_byte(0x105131, 0x2E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0805A97D);
    EXPECT_EQ(cpu.get_ebx(), 0xAD055ADF);
    EXPECT_EQ(cpu.get_ecx(), 0x074908E8);
    EXPECT_EQ(cpu.get_edx(), 0xD8D6A556);
    EXPECT_EQ(cpu.get_esi(), 0x334D3CB6);
    EXPECT_EQ(cpu.get_edi(), 0x10987C31);
    EXPECT_EQ(cpu.get_ebp(), 0xECD83A82);
    EXPECT_EQ(cpu.get_esp(), 0x00008000);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x00001001);
    EXPECT_EQ(cpu.get_es(), 0x0000E6AA);
    EXPECT_EQ(cpu.get_fs(), 0x00006ED7);
    EXPECT_EQ(cpu.get_gs(), 0x0000D637);
    EXPECT_EQ(cpu.get_ss(), 0x0000FF09);
    EXPECT_EQ(cpu.get_eip(), 0x00005135);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C6);

    // Final RAM entries
}

//
// bts [ds:140Ah],esi
//
TEST_F(Test386, bts_ds_140Ah_esi)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x66BC5C6E);
    cpu.set_ebx(0x5C9A4CF0);
    cpu.set_ecx(0xA605EA81);
    cpu.set_edx(0xBF67CB2E);
    cpu.set_esi(0x000072C4);
    cpu.set_edi(0x5208CEA4);
    cpu.set_ebp(0xD669BF22);
    cpu.set_esp(0x0000E766);
    cpu.set_cs(0x0000370E);
    cpu.set_ds(0x000079F3);
    cpu.set_es(0x0000B2EC);
    cpu.set_fs(0x00009F48);
    cpu.set_gs(0x0000C715);
    cpu.set_ss(0x0000466B);
    cpu.set_eip(0x0000B338);
    cpu.set_eflags(0xFFFC0087);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x42418, 0x66);
    machine.mem_store_byte(0x42419, 0x67);
    machine.mem_store_byte(0x4241A, 0x0F);
    machine.mem_store_byte(0x4241B, 0xAB);
    machine.mem_store_byte(0x4241C, 0x35);
    machine.mem_store_byte(0x4241D, 0x0A);
    machine.mem_store_byte(0x4241E, 0x14);
    machine.mem_store_byte(0x4241F, 0x00);
    machine.mem_store_byte(0x42420, 0x00);
    machine.mem_store_byte(0x42421, 0xF4);
    machine.mem_store_byte(0x42422, 0x4D);
    machine.mem_store_byte(0x42423, 0xC6);
    machine.mem_store_byte(0x42424, 0xF7);
    machine.mem_store_byte(0x42425, 0xC0);
    machine.mem_store_byte(0x42426, 0xF7);
    machine.mem_store_byte(0x42427, 0xAB);
    machine.mem_store_byte(0x42428, 0xC5);
    machine.mem_store_byte(0x42429, 0xCC);
    machine.mem_store_byte(0x4242A, 0x1A);
    machine.mem_store_byte(0x4242B, 0xDF);
    machine.mem_store_byte(0x4242C, 0x0D);
    machine.mem_store_byte(0x4242D, 0x6D);
    machine.mem_store_byte(0x7C194, 0x01);
    machine.mem_store_byte(0x7C195, 0x21);
    machine.mem_store_byte(0x7C192, 0xF7);
    machine.mem_store_byte(0x7C193, 0xD9);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x66BC5C6E);
    EXPECT_EQ(cpu.get_ebx(), 0x5C9A4CF0);
    EXPECT_EQ(cpu.get_ecx(), 0xA605EA81);
    EXPECT_EQ(cpu.get_edx(), 0xBF67CB2E);
    EXPECT_EQ(cpu.get_esi(), 0x000072C4);
    EXPECT_EQ(cpu.get_edi(), 0x5208CEA4);
    EXPECT_EQ(cpu.get_ebp(), 0xD669BF22);
    EXPECT_EQ(cpu.get_esp(), 0x0000E766);
    EXPECT_EQ(cpu.get_cs(), 0x0000370E);
    EXPECT_EQ(cpu.get_ds(), 0x000079F3);
    EXPECT_EQ(cpu.get_es(), 0x0000B2EC);
    EXPECT_EQ(cpu.get_fs(), 0x00009F48);
    EXPECT_EQ(cpu.get_gs(), 0x0000C715);
    EXPECT_EQ(cpu.get_ss(), 0x0000466B);
    EXPECT_EQ(cpu.get_eip(), 0x0000B342);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0887);

    // Final RAM entries
}

//
// bt dword [ds:bx],AFh
//
TEST_F(Test386, bt_dword_ds_bx_AFh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xEBB87EBB);
    cpu.set_ebx(0xB426AD33);
    cpu.set_ecx(0x58F140A4);
    cpu.set_edx(0xD47A62E9);
    cpu.set_esi(0x976EF6D7);
    cpu.set_edi(0xC33DDCCD);
    cpu.set_ebp(0x939AD29A);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F6B4);
    cpu.set_ds(0x00001918);
    cpu.set_es(0x0000101B);
    cpu.set_fs(0x0000F9C6);
    cpu.set_gs(0x0000E7A5);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x00005B18);
    cpu.set_eflags(0xFFFC00D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFC658, 0x66);
    machine.mem_store_byte(0xFC659, 0x0F);
    machine.mem_store_byte(0xFC65A, 0xBA);
    machine.mem_store_byte(0xFC65B, 0x27);
    machine.mem_store_byte(0xFC65C, 0xAF);
    machine.mem_store_byte(0xFC65D, 0xF4);
    machine.mem_store_byte(0xFC65E, 0x3F);
    machine.mem_store_byte(0xFC65F, 0x7E);
    machine.mem_store_byte(0xFC660, 0xEB);
    machine.mem_store_byte(0xFC661, 0x21);
    machine.mem_store_byte(0xFC662, 0x85);
    machine.mem_store_byte(0xFC663, 0x52);
    machine.mem_store_byte(0x23EB4, 0xD0);
    machine.mem_store_byte(0x23EB5, 0xBF);
    machine.mem_store_byte(0x23EB6, 0x01);
    machine.mem_store_byte(0x23EB3, 0x1D);
    machine.mem_store_byte(0xFC664, 0x9C);
    machine.mem_store_byte(0xFC665, 0x68);
    machine.mem_store_byte(0xFC666, 0x38);
    machine.mem_store_byte(0xFC667, 0x36);
    machine.mem_store_byte(0xFC668, 0xCD);
    machine.mem_store_byte(0xFC669, 0x00);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xEBB87EBB);
    EXPECT_EQ(cpu.get_ebx(), 0xB426AD33);
    EXPECT_EQ(cpu.get_ecx(), 0x58F140A4);
    EXPECT_EQ(cpu.get_edx(), 0xD47A62E9);
    EXPECT_EQ(cpu.get_esi(), 0x976EF6D7);
    EXPECT_EQ(cpu.get_edi(), 0xC33DDCCD);
    EXPECT_EQ(cpu.get_ebp(), 0x939AD29A);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000F6B4);
    EXPECT_EQ(cpu.get_ds(), 0x00001918);
    EXPECT_EQ(cpu.get_es(), 0x0000101B);
    EXPECT_EQ(cpu.get_fs(), 0x0000F9C6);
    EXPECT_EQ(cpu.get_gs(), 0x0000E7A5);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x00005B1E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D3);

    // Final RAM entries
}

//
// btc dword [ds:edi*1-7CCBh],A9h
//
TEST_F(Test386, btc_dword_ds_edi_1_7CCBh_A9h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF62AAC8C);
    cpu.set_ebx(0x9BDB370D);
    cpu.set_ecx(0xA46DE187);
    cpu.set_edx(0xA854CCB2);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0x00009378);
    cpu.set_ebp(0xEEEFEC69);
    cpu.set_esp(0x00000012);
    cpu.set_cs(0x0000F3BF);
    cpu.set_ds(0x000027DF);
    cpu.set_es(0x00000013);
    cpu.set_fs(0x00005F71);
    cpu.set_gs(0x0000C3E1);
    cpu.set_ss(0x000064CE);
    cpu.set_eip(0x0000CB80);
    cpu.set_eflags(0xFFFC0083);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x100770, 0x66);
    machine.mem_store_byte(0x100771, 0x67);
    machine.mem_store_byte(0x100772, 0x0F);
    machine.mem_store_byte(0x100773, 0xBA);
    machine.mem_store_byte(0x100774, 0x3C);
    machine.mem_store_byte(0x100775, 0x3D);
    machine.mem_store_byte(0x100776, 0x35);
    machine.mem_store_byte(0x100777, 0x83);
    machine.mem_store_byte(0x100778, 0xFF);
    machine.mem_store_byte(0x100779, 0xFF);
    machine.mem_store_byte(0x10077A, 0xA9);
    machine.mem_store_byte(0x10077B, 0xF4);
    machine.mem_store_byte(0x10077C, 0x42);
    machine.mem_store_byte(0x10077D, 0xA7);
    machine.mem_store_byte(0x10077E, 0xD6);
    machine.mem_store_byte(0x10077F, 0x4D);
    machine.mem_store_byte(0x100780, 0x5B);
    machine.mem_store_byte(0x100781, 0x07);
    machine.mem_store_byte(0x294A0, 0x6C);
    machine.mem_store_byte(0x2949D, 0x04);
    machine.mem_store_byte(0x2949E, 0xD4);
    machine.mem_store_byte(0x2949F, 0x4B);
    machine.mem_store_byte(0x100782, 0xC3);
    machine.mem_store_byte(0x100783, 0xD4);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF62AAC8C);
    EXPECT_EQ(cpu.get_ebx(), 0x9BDB370D);
    EXPECT_EQ(cpu.get_ecx(), 0xA46DE187);
    EXPECT_EQ(cpu.get_edx(), 0xA854CCB2);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x00009378);
    EXPECT_EQ(cpu.get_ebp(), 0xEEEFEC69);
    EXPECT_EQ(cpu.get_esp(), 0x00000012);
    EXPECT_EQ(cpu.get_cs(), 0x0000F3BF);
    EXPECT_EQ(cpu.get_ds(), 0x000027DF);
    EXPECT_EQ(cpu.get_es(), 0x00000013);
    EXPECT_EQ(cpu.get_fs(), 0x00005F71);
    EXPECT_EQ(cpu.get_gs(), 0x0000C3E1);
    EXPECT_EQ(cpu.get_ss(), 0x000064CE);
    EXPECT_EQ(cpu.get_eip(), 0x0000CB8C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2949E), 0xD6);
}

//
// btr edx,53h
//
TEST_F(Test386, btr_edx_53h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x362B99F1);
    cpu.set_ebx(0x0F2A2AD7);
    cpu.set_ecx(0x0AAE5498);
    cpu.set_edx(0xDC646D16);
    cpu.set_esi(0x00CDC785);
    cpu.set_edi(0x00020001);
    cpu.set_ebp(0xFFFFFFFF);
    cpu.set_esp(0x0000C672);
    cpu.set_cs(0x0000BDD4);
    cpu.set_ds(0x00007D0B);
    cpu.set_es(0x0000F548);
    cpu.set_fs(0x00007CA7);
    cpu.set_gs(0x000078D2);
    cpu.set_ss(0x00000EBD);
    cpu.set_eip(0x00003860);
    cpu.set_eflags(0xFFFC0C13);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC15A0, 0x67);
    machine.mem_store_byte(0xC15A1, 0x66);
    machine.mem_store_byte(0xC15A2, 0x0F);
    machine.mem_store_byte(0xC15A3, 0xBA);
    machine.mem_store_byte(0xC15A4, 0xF2);
    machine.mem_store_byte(0xC15A5, 0x53);
    machine.mem_store_byte(0xC15A6, 0xF4);
    machine.mem_store_byte(0xC15A7, 0x19);
    machine.mem_store_byte(0xC15A8, 0x74);
    machine.mem_store_byte(0xC15A9, 0xA4);
    machine.mem_store_byte(0xC15AA, 0xA9);
    machine.mem_store_byte(0xC15AB, 0x5C);
    machine.mem_store_byte(0xC15AC, 0x8E);
    machine.mem_store_byte(0xC15AD, 0xC7);
    machine.mem_store_byte(0xC15AE, 0xB5);
    machine.mem_store_byte(0xC15AF, 0x5C);
    machine.mem_store_byte(0xC15B0, 0x00);
    machine.mem_store_byte(0xC15B1, 0x39);
    machine.mem_store_byte(0xC15B2, 0x7F);
    machine.mem_store_byte(0xC15B3, 0xD7);
    machine.mem_store_byte(0xC15B4, 0x61);
    machine.mem_store_byte(0xC15B5, 0xED);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x362B99F1);
    EXPECT_EQ(cpu.get_ebx(), 0x0F2A2AD7);
    EXPECT_EQ(cpu.get_ecx(), 0x0AAE5498);
    EXPECT_EQ(cpu.get_edx(), 0xDC646D16);
    EXPECT_EQ(cpu.get_esi(), 0x00CDC785);
    EXPECT_EQ(cpu.get_edi(), 0x00020001);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000C672);
    EXPECT_EQ(cpu.get_cs(), 0x0000BDD4);
    EXPECT_EQ(cpu.get_ds(), 0x00007D0B);
    EXPECT_EQ(cpu.get_es(), 0x0000F548);
    EXPECT_EQ(cpu.get_fs(), 0x00007CA7);
    EXPECT_EQ(cpu.get_gs(), 0x000078D2);
    EXPECT_EQ(cpu.get_ss(), 0x00000EBD);
    EXPECT_EQ(cpu.get_eip(), 0x00003867);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C12);

    // Final RAM entries
}

//
// bts dword [ds:bx],AFh
//
TEST_F(Test386, bts_dword_ds_bx_AFh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xEBB87EBB);
    cpu.set_ebx(0xB426AD33);
    cpu.set_ecx(0x58F140A4);
    cpu.set_edx(0xD47A62E9);
    cpu.set_esi(0x976EF6D7);
    cpu.set_edi(0xC33DDCCD);
    cpu.set_ebp(0x939AD29A);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F6B4);
    cpu.set_ds(0x00001918);
    cpu.set_es(0x0000101B);
    cpu.set_fs(0x0000F9C6);
    cpu.set_gs(0x0000E7A5);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x00005B18);
    cpu.set_eflags(0xFFFC00D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFC658, 0x66);
    machine.mem_store_byte(0xFC659, 0x0F);
    machine.mem_store_byte(0xFC65A, 0xBA);
    machine.mem_store_byte(0xFC65B, 0x2F);
    machine.mem_store_byte(0xFC65C, 0xAF);
    machine.mem_store_byte(0xFC65D, 0xF4);
    machine.mem_store_byte(0xFC65E, 0xF3);
    machine.mem_store_byte(0xFC65F, 0x50);
    machine.mem_store_byte(0xFC660, 0x57);
    machine.mem_store_byte(0xFC661, 0x8C);
    machine.mem_store_byte(0xFC662, 0x18);
    machine.mem_store_byte(0xFC663, 0x05);
    machine.mem_store_byte(0x23EB4, 0x51);
    machine.mem_store_byte(0x23EB5, 0xA3);
    machine.mem_store_byte(0x23EB6, 0xDB);
    machine.mem_store_byte(0x23EB3, 0x35);
    machine.mem_store_byte(0xFC664, 0x43);
    machine.mem_store_byte(0xFC665, 0x94);
    machine.mem_store_byte(0xFC666, 0x04);
    machine.mem_store_byte(0xFC667, 0xD3);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xEBB87EBB);
    EXPECT_EQ(cpu.get_ebx(), 0xB426AD33);
    EXPECT_EQ(cpu.get_ecx(), 0x58F140A4);
    EXPECT_EQ(cpu.get_edx(), 0xD47A62E9);
    EXPECT_EQ(cpu.get_esi(), 0x976EF6D7);
    EXPECT_EQ(cpu.get_edi(), 0xC33DDCCD);
    EXPECT_EQ(cpu.get_ebp(), 0x939AD29A);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000F6B4);
    EXPECT_EQ(cpu.get_ds(), 0x00001918);
    EXPECT_EQ(cpu.get_es(), 0x0000101B);
    EXPECT_EQ(cpu.get_fs(), 0x0000F9C6);
    EXPECT_EQ(cpu.get_gs(), 0x0000E7A5);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x00005B1E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x23EB4), 0xD1);
}

//
// bt [ss:bp+di],edx
//
TEST_F(Test386, bt_ss_bp_di_edx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x108AD9DC);
    cpu.set_ebx(0x71DF7F71);
    cpu.set_ecx(0xE8002516);
    cpu.set_edx(0xCE6CAE2E);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x3BBAB5EB);
    cpu.set_esp(0x00006F11);
    cpu.set_cs(0x00004E41);
    cpu.set_ds(0x00008000);
    cpu.set_es(0x00000D51);
    cpu.set_fs(0x00007FFF);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x00007F20);
    cpu.set_eip(0x00005618);
    cpu.set_eflags(0xFFFC00D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x53A28, 0x66);
    machine.mem_store_byte(0x53A29, 0x0F);
    machine.mem_store_byte(0x53A2A, 0xA3);
    machine.mem_store_byte(0x53A2B, 0x13);
    machine.mem_store_byte(0x53A2C, 0xF4);
    machine.mem_store_byte(0x53A2D, 0x8E);
    machine.mem_store_byte(0x53A2E, 0xFA);
    machine.mem_store_byte(0x53A2F, 0xD5);
    machine.mem_store_byte(0x53A30, 0x13);
    machine.mem_store_byte(0x53A31, 0x34);
    machine.mem_store_byte(0x53A32, 0x53);
    machine.mem_store_byte(0x53A33, 0x77);
    machine.mem_store_byte(0x53A34, 0xBC);
    machine.mem_store_byte(0x53A35, 0x5D);
    machine.mem_store_byte(0x53A36, 0x38);
    machine.mem_store_byte(0x53A37, 0x88);
    machine.mem_store_byte(0x53A38, 0x0C);
    machine.mem_store_byte(0x53A39, 0x57);
    machine.mem_store_byte(0x83DB0, 0x09);
    machine.mem_store_byte(0x83DB1, 0xAA);
    machine.mem_store_byte(0x83DAE, 0x93);
    machine.mem_store_byte(0x83DAF, 0x63);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x108AD9DC);
    EXPECT_EQ(cpu.get_ebx(), 0x71DF7F71);
    EXPECT_EQ(cpu.get_ecx(), 0xE8002516);
    EXPECT_EQ(cpu.get_edx(), 0xCE6CAE2E);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x3BBAB5EB);
    EXPECT_EQ(cpu.get_esp(), 0x00006F11);
    EXPECT_EQ(cpu.get_cs(), 0x00004E41);
    EXPECT_EQ(cpu.get_ds(), 0x00008000);
    EXPECT_EQ(cpu.get_es(), 0x00000D51);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x00007F20);
    EXPECT_EQ(cpu.get_eip(), 0x0000561D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D3);

    // Final RAM entries
}

//
// btc [ds:esi-EF39h],dx
//
TEST_F(Test386, btc_ds_esi_EF39h_dx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE9FA80ED);
    cpu.set_ebx(0x0000FF00);
    cpu.set_ecx(0x00000000);
    cpu.set_edx(0xD0660F6A);
    cpu.set_esi(0x0000FF18);
    cpu.set_edi(0xE1FFBC40);
    cpu.set_ebp(0x95E8BD16);
    cpu.set_esp(0x00005492);
    cpu.set_cs(0x000067FA);
    cpu.set_ds(0x0000FD2B);
    cpu.set_es(0x00006E66);
    cpu.set_fs(0x00009C17);
    cpu.set_gs(0x0000FCC7);
    cpu.set_ss(0x00007176);
    cpu.set_eip(0x0000D628);
    cpu.set_eflags(0xFFFC08D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x755C8, 0x67);
    machine.mem_store_byte(0x755C9, 0x0F);
    machine.mem_store_byte(0x755CA, 0xBB);
    machine.mem_store_byte(0x755CB, 0x96);
    machine.mem_store_byte(0x755CC, 0xC7);
    machine.mem_store_byte(0x755CD, 0x10);
    machine.mem_store_byte(0x755CE, 0xFF);
    machine.mem_store_byte(0x755CF, 0xFF);
    machine.mem_store_byte(0x755D0, 0xF4);
    machine.mem_store_byte(0x755D1, 0x76);
    machine.mem_store_byte(0x755D2, 0x78);
    machine.mem_store_byte(0x755D3, 0x01);
    machine.mem_store_byte(0x755D4, 0xC6);
    machine.mem_store_byte(0x755D5, 0xFB);
    machine.mem_store_byte(0x755D6, 0x5B);
    machine.mem_store_byte(0x755D7, 0x76);
    machine.mem_store_byte(0x755D8, 0x50);
    machine.mem_store_byte(0x755D9, 0x5B);
    machine.mem_store_byte(0xFE47C, 0xF6);
    machine.mem_store_byte(0xFE47B, 0xAD);
    machine.mem_store_byte(0x755DA, 0x32);
    machine.mem_store_byte(0x755DB, 0xE7);
    machine.mem_store_byte(0x755DC, 0x83);
    machine.mem_store_byte(0x755DD, 0x41);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE9FA80ED);
    EXPECT_EQ(cpu.get_ebx(), 0x0000FF00);
    EXPECT_EQ(cpu.get_ecx(), 0x00000000);
    EXPECT_EQ(cpu.get_edx(), 0xD0660F6A);
    EXPECT_EQ(cpu.get_esi(), 0x0000FF18);
    EXPECT_EQ(cpu.get_edi(), 0xE1FFBC40);
    EXPECT_EQ(cpu.get_ebp(), 0x95E8BD16);
    EXPECT_EQ(cpu.get_esp(), 0x00005492);
    EXPECT_EQ(cpu.get_cs(), 0x000067FA);
    EXPECT_EQ(cpu.get_ds(), 0x0000FD2B);
    EXPECT_EQ(cpu.get_es(), 0x00006E66);
    EXPECT_EQ(cpu.get_fs(), 0x00009C17);
    EXPECT_EQ(cpu.get_gs(), 0x0000FCC7);
    EXPECT_EQ(cpu.get_ss(), 0x00007176);
    EXPECT_EQ(cpu.get_eip(), 0x0000D631);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFE47C), 0xF2);
}

//
// bound esi,[ss:edx-E325h]
//
TEST_F(Test386, bound_esi_ss_edx_E325h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x80000000);
    cpu.set_ebx(0x37C9BF77);
    cpu.set_ecx(0x033F5868);
    cpu.set_edx(0x0000B32D);
    cpu.set_esi(0xF7AA0FB6);
    cpu.set_edi(0x1637BB67);
    cpu.set_ebp(0xDED841D2);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000DCF1);
    cpu.set_ds(0x00005740);
    cpu.set_es(0x00006CDE);
    cpu.set_fs(0x000000F6);
    cpu.set_gs(0x00009999);
    cpu.set_ss(0x0000AEA8);
    cpu.set_eip(0x0000C680);
    cpu.set_eflags(0xFFFC00C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE9590, 0x36);
    machine.mem_store_byte(0xE9591, 0x66);
    machine.mem_store_byte(0xE9592, 0x67);
    machine.mem_store_byte(0xE9593, 0x62);
    machine.mem_store_byte(0xE9594, 0xB2);
    machine.mem_store_byte(0xE9595, 0xDB);
    machine.mem_store_byte(0xE9596, 0x1C);
    machine.mem_store_byte(0xE9597, 0xFF);
    machine.mem_store_byte(0xE9598, 0xFF);
    machine.mem_store_byte(0xE9599, 0xF4);
    machine.mem_store_byte(0xE959A, 0x12);
    machine.mem_store_byte(0xE959B, 0x2D);
    machine.mem_store_byte(0xE959C, 0xCF);
    machine.mem_store_byte(0xE959D, 0x24);
    machine.mem_store_byte(0xE959E, 0x61);
    machine.mem_store_byte(0xE959F, 0x6A);
    machine.mem_store_byte(0xE95A0, 0x52);
    machine.mem_store_byte(0xE95A1, 0x70);
    machine.mem_store_byte(0xE95A2, 0xF7);
    machine.mem_store_byte(0xE95A3, 0x04);
    machine.mem_store_byte(0xE95A4, 0xA9);
    machine.mem_store_byte(0xE95A5, 0x11);
    machine.mem_store_byte(0xE95A6, 0x05);
    machine.mem_store_byte(0xE95A7, 0x02);
    machine.mem_store_byte(0x00030, 0xCF);
    machine.mem_store_byte(0x00031, 0x30);
    machine.mem_store_byte(0x00032, 0xC3);
    machine.mem_store_byte(0x00033, 0x4F);
    machine.mem_store_byte(0x52CFE, 0xCF);
    machine.mem_store_byte(0x52CFF, 0xF4);
    machine.mem_store_byte(0x52D00, 0xB3);
    machine.mem_store_byte(0x52D01, 0xF4);
    machine.mem_store_byte(0x52D02, 0xC0);
    machine.mem_store_byte(0x52D03, 0xF4);
    machine.mem_store_byte(0x52D04, 0x9A);
    machine.mem_store_byte(0x52D05, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x80000000);
    EXPECT_EQ(cpu.get_ebx(), 0x37C9BF77);
    EXPECT_EQ(cpu.get_ecx(), 0x033F5868);
    EXPECT_EQ(cpu.get_edx(), 0x0000B32D);
    EXPECT_EQ(cpu.get_esi(), 0xF7AA0FB6);
    EXPECT_EQ(cpu.get_edi(), 0x1637BB67);
    EXPECT_EQ(cpu.get_ebp(), 0xDED841D2);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x00004FC3);
    EXPECT_EQ(cpu.get_ds(), 0x00005740);
    EXPECT_EQ(cpu.get_es(), 0x00006CDE);
    EXPECT_EQ(cpu.get_fs(), 0x000000F6);
    EXPECT_EQ(cpu.get_gs(), 0x00009999);
    EXPECT_EQ(cpu.get_ss(), 0x0000AEA8);
    EXPECT_EQ(cpu.get_eip(), 0x000030D0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBEA7C), 0xC6);
    EXPECT_EQ(memory.load8(0xBEA7D), 0x00);
    EXPECT_EQ(memory.load8(0xBEA7A), 0xF1);
    EXPECT_EQ(memory.load8(0xBEA7B), 0xDC);
    EXPECT_EQ(memory.load8(0xBEA78), 0x80);
    EXPECT_EQ(memory.load8(0xBEA79), 0xC6);
}

//
// bound si,[ss:edx-E325h]
//
TEST_F(Test386, bound_si_ss_edx_E325h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x80000000);
    cpu.set_ebx(0x37C9BF77);
    cpu.set_ecx(0x033F5868);
    cpu.set_edx(0x0000B32D);
    cpu.set_esi(0xF7AA0FB6);
    cpu.set_edi(0x1637BB67);
    cpu.set_ebp(0xDED841D2);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000DCF1);
    cpu.set_ds(0x00005740);
    cpu.set_es(0x00006CDE);
    cpu.set_fs(0x000000F6);
    cpu.set_gs(0x00009999);
    cpu.set_ss(0x0000AEA8);
    cpu.set_eip(0x0000C680);
    cpu.set_eflags(0xFFFC00C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE9590, 0x36);
    machine.mem_store_byte(0xE9591, 0x67);
    machine.mem_store_byte(0xE9592, 0x62);
    machine.mem_store_byte(0xE9593, 0xB2);
    machine.mem_store_byte(0xE9594, 0xDB);
    machine.mem_store_byte(0xE9595, 0x1C);
    machine.mem_store_byte(0xE9596, 0xFF);
    machine.mem_store_byte(0xE9597, 0xFF);
    machine.mem_store_byte(0xE9598, 0xF4);
    machine.mem_store_byte(0xE9599, 0x06);
    machine.mem_store_byte(0xE959A, 0x12);
    machine.mem_store_byte(0xE959B, 0x2D);
    machine.mem_store_byte(0xE959C, 0xCF);
    machine.mem_store_byte(0xE959D, 0x24);
    machine.mem_store_byte(0xE959E, 0x61);
    machine.mem_store_byte(0xE959F, 0x6A);
    machine.mem_store_byte(0xE95A0, 0x52);
    machine.mem_store_byte(0xE95A1, 0x70);
    machine.mem_store_byte(0xE95A2, 0xF7);
    machine.mem_store_byte(0xE95A3, 0x04);
    machine.mem_store_byte(0x00030, 0xCF);
    machine.mem_store_byte(0x00031, 0x30);
    machine.mem_store_byte(0x00032, 0xC3);
    machine.mem_store_byte(0x00033, 0x4F);
    machine.mem_store_byte(0x52CFE, 0xCF);
    machine.mem_store_byte(0x52CFF, 0xF4);
    machine.mem_store_byte(0x52D00, 0xB3);
    machine.mem_store_byte(0x52D01, 0xF4);
    machine.mem_store_byte(0x52D02, 0xC0);
    machine.mem_store_byte(0x52D03, 0xF4);
    machine.mem_store_byte(0x52D04, 0x9A);
    machine.mem_store_byte(0x52D05, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x80000000);
    EXPECT_EQ(cpu.get_ebx(), 0x37C9BF77);
    EXPECT_EQ(cpu.get_ecx(), 0x033F5868);
    EXPECT_EQ(cpu.get_edx(), 0x0000B32D);
    EXPECT_EQ(cpu.get_esi(), 0xF7AA0FB6);
    EXPECT_EQ(cpu.get_edi(), 0x1637BB67);
    EXPECT_EQ(cpu.get_ebp(), 0xDED841D2);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x00004FC3);
    EXPECT_EQ(cpu.get_ds(), 0x00005740);
    EXPECT_EQ(cpu.get_es(), 0x00006CDE);
    EXPECT_EQ(cpu.get_fs(), 0x000000F6);
    EXPECT_EQ(cpu.get_gs(), 0x00009999);
    EXPECT_EQ(cpu.get_ss(), 0x0000AEA8);
    EXPECT_EQ(cpu.get_eip(), 0x000030D0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBEA7C), 0xC6);
    EXPECT_EQ(memory.load8(0xBEA7D), 0x00);
    EXPECT_EQ(memory.load8(0xBEA7A), 0xF1);
    EXPECT_EQ(memory.load8(0xBEA7B), 0xDC);
    EXPECT_EQ(memory.load8(0xBEA78), 0x80);
    EXPECT_EQ(memory.load8(0xBEA79), 0xC6);
}

//
// (bad) pop dword [ds:bx+di+32C5h]
//
TEST_F(Test386, bad_pop_dword_ds_bx_di_32C5h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDBB64193);
    cpu.set_ebx(0x00004000);
    cpu.set_ecx(0x003FFFFF);
    cpu.set_edx(0xFD40B165);
    cpu.set_esi(0x528F9277);
    cpu.set_edi(0x9C963B69);
    cpu.set_ebp(0x7F000000);
    cpu.set_esp(0x0000D164);
    cpu.set_cs(0x0000FC69);
    cpu.set_ds(0x0000DEFE);
    cpu.set_es(0x00000015);
    cpu.set_fs(0x0000BAE1);
    cpu.set_gs(0x0000E640);
    cpu.set_ss(0x0000813B);
    cpu.set_eip(0x0000DBF8);
    cpu.set_eflags(0xFFFC0853);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10A288, 0x66);
    machine.mem_store_byte(0x10A289, 0x8F);
    machine.mem_store_byte(0x10A28A, 0x99);
    machine.mem_store_byte(0x10A28B, 0xC5);
    machine.mem_store_byte(0x10A28C, 0x32);
    machine.mem_store_byte(0x10A28D, 0xF4);
    machine.mem_store_byte(0x10A28E, 0x95);
    machine.mem_store_byte(0x10A28F, 0x7F);
    machine.mem_store_byte(0x10A290, 0xE8);
    machine.mem_store_byte(0x10A291, 0x94);
    machine.mem_store_byte(0x10A292, 0x97);
    machine.mem_store_byte(0x10A293, 0xA6);
    machine.mem_store_byte(0x10A294, 0x65);
    machine.mem_store_byte(0x10A295, 0xC3);
    machine.mem_store_byte(0x10A296, 0xC8);
    machine.mem_store_byte(0x10A297, 0xBC);
    machine.mem_store_byte(0x00018, 0x7B);
    machine.mem_store_byte(0x00019, 0x56);
    machine.mem_store_byte(0x0001A, 0x9F);
    machine.mem_store_byte(0x0001B, 0xE1);
    machine.mem_store_byte(0xE706A, 0x38);
    machine.mem_store_byte(0xE706B, 0xF4);
    machine.mem_store_byte(0xE706C, 0x33);
    machine.mem_store_byte(0xE706D, 0xF4);
    machine.mem_store_byte(0xE706E, 0x20);
    machine.mem_store_byte(0xE706F, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDBB64193);
    EXPECT_EQ(cpu.get_ebx(), 0x00004000);
    EXPECT_EQ(cpu.get_ecx(), 0x003FFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xFD40B165);
    EXPECT_EQ(cpu.get_esi(), 0x528F9277);
    EXPECT_EQ(cpu.get_edi(), 0x9C963B69);
    EXPECT_EQ(cpu.get_ebp(), 0x7F000000);
    EXPECT_EQ(cpu.get_esp(), 0x0000D15E);
    EXPECT_EQ(cpu.get_cs(), 0x0000E19F);
    EXPECT_EQ(cpu.get_ds(), 0x0000DEFE);
    EXPECT_EQ(cpu.get_es(), 0x00000015);
    EXPECT_EQ(cpu.get_fs(), 0x0000BAE1);
    EXPECT_EQ(cpu.get_gs(), 0x0000E640);
    EXPECT_EQ(cpu.get_ss(), 0x0000813B);
    EXPECT_EQ(cpu.get_eip(), 0x0000567C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0853);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8E512), 0x53);
    EXPECT_EQ(memory.load8(0x8E513), 0x08);
    EXPECT_EQ(memory.load8(0x8E510), 0x69);
    EXPECT_EQ(memory.load8(0x8E511), 0xFC);
    EXPECT_EQ(memory.load8(0x8E50E), 0xF8);
    EXPECT_EQ(memory.load8(0x8E50F), 0xDB);
}
