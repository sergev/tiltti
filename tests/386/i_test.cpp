#include "test386.h"

//
// idiv edi
//
TEST_F(Test386, idiv_edi)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x44846D20);
    cpu.set_ebx(0x00000001);
    cpu.set_ecx(0x75DCF65D);
    cpu.set_edx(0xDA458064);
    cpu.set_esi(0x06C38BF3);
    cpu.set_edi(0x7A8CC8BD);
    cpu.set_ebp(0x016EBFA7);
    cpu.set_esp(0x0000C679);
    cpu.set_cs(0x0000E7A8);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x000092C9);
    cpu.set_gs(0x0000D355);
    cpu.set_ss(0x0000FCA6);
    cpu.set_eip(0x00003F78);
    cpu.set_eflags(0xFFFC0487);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEB9F8, 0x67);
    machine.mem_store_byte(0xEB9F9, 0x66);
    machine.mem_store_byte(0xEB9FA, 0xF7);
    machine.mem_store_byte(0xEB9FB, 0xFF);
    machine.mem_store_byte(0xEB9FC, 0xF4);
    machine.mem_store_byte(0xEB9FD, 0xCA);
    machine.mem_store_byte(0xEB9FE, 0x2F);
    machine.mem_store_byte(0xEB9FF, 0x54);
    machine.mem_store_byte(0xEBA00, 0xCA);
    machine.mem_store_byte(0xEBA01, 0x8D);
    machine.mem_store_byte(0xEBA02, 0x62);
    machine.mem_store_byte(0xEBA03, 0x74);
    machine.mem_store_byte(0xEBA04, 0x5C);
    machine.mem_store_byte(0xEBA05, 0xA7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xB12FEF2B);
    EXPECT_EQ(cpu.get_ebx(), 0x00000001);
    EXPECT_EQ(cpu.get_ecx(), 0x75DCF65D);
    EXPECT_EQ(cpu.get_edx(), 0xB7C34261);
    EXPECT_EQ(cpu.get_esi(), 0x06C38BF3);
    EXPECT_EQ(cpu.get_edi(), 0x7A8CC8BD);
    EXPECT_EQ(cpu.get_ebp(), 0x016EBFA7);
    EXPECT_EQ(cpu.get_esp(), 0x0000C679);
    EXPECT_EQ(cpu.get_cs(), 0x0000E7A8);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x000092C9);
    EXPECT_EQ(cpu.get_gs(), 0x0000D355);
    EXPECT_EQ(cpu.get_ss(), 0x0000FCA6);
    EXPECT_EQ(cpu.get_eip(), 0x00003F7D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0407);

    // Final RAM entries
}

//
// idiv word [ss:bp+si-14EEh]
//
TEST_F(Test386, idiv_word_ss_bp_si_14EEh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x88FB4781);
    cpu.set_ebx(0x1CE0032A);
    cpu.set_ecx(0x28EC99B0);
    cpu.set_edx(0x57B9CF9E);
    cpu.set_esi(0xC647CA13);
    cpu.set_edi(0xF846A5B8);
    cpu.set_ebp(0x1BD877D8);
    cpu.set_esp(0x0000F2A4);
    cpu.set_cs(0x0000FC3E);
    cpu.set_ds(0x00003FDE);
    cpu.set_es(0x000007D2);
    cpu.set_fs(0x00000B9D);
    cpu.set_gs(0x0000C800);
    cpu.set_ss(0x0000D3BF);
    cpu.set_eip(0x00008B90);
    cpu.set_eflags(0xFFFC0493);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x104F70, 0xF7);
    machine.mem_store_byte(0x104F71, 0xBA);
    machine.mem_store_byte(0x104F72, 0x12);
    machine.mem_store_byte(0x104F73, 0xEB);
    machine.mem_store_byte(0x104F74, 0xF4);
    machine.mem_store_byte(0x104F75, 0xF3);
    machine.mem_store_byte(0x104F76, 0xB3);
    machine.mem_store_byte(0x104F77, 0x56);
    machine.mem_store_byte(0x104F78, 0x96);
    machine.mem_store_byte(0x104F79, 0xCE);
    machine.mem_store_byte(0xD68ED, 0xA4);
    machine.mem_store_byte(0xD68EE, 0x88);
    machine.mem_store_byte(0x104F7A, 0xE8);
    machine.mem_store_byte(0x104F7B, 0xD1);
    machine.mem_store_byte(0x104F7C, 0xD7);
    machine.mem_store_byte(0x104F7D, 0x4A);
    machine.mem_store_byte(0x104F7E, 0xD9);
    machine.mem_store_byte(0x104F7F, 0x70);
    machine.mem_store_byte(0x104F80, 0x87);
    machine.mem_store_byte(0x104F81, 0x6A);
    machine.mem_store_byte(0x104F82, 0x11);
    machine.mem_store_byte(0x104F83, 0x02);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x88FB67C4);
    EXPECT_EQ(cpu.get_ebx(), 0x1CE0032A);
    EXPECT_EQ(cpu.get_ecx(), 0x28EC99B0);
    EXPECT_EQ(cpu.get_edx(), 0x57B9ADF1);
    EXPECT_EQ(cpu.get_esi(), 0xC647CA13);
    EXPECT_EQ(cpu.get_edi(), 0xF846A5B8);
    EXPECT_EQ(cpu.get_ebp(), 0x1BD877D8);
    EXPECT_EQ(cpu.get_esp(), 0x0000F2A4);
    EXPECT_EQ(cpu.get_cs(), 0x0000FC3E);
    EXPECT_EQ(cpu.get_ds(), 0x00003FDE);
    EXPECT_EQ(cpu.get_es(), 0x000007D2);
    EXPECT_EQ(cpu.get_fs(), 0x00000B9D);
    EXPECT_EQ(cpu.get_gs(), 0x0000C800);
    EXPECT_EQ(cpu.get_ss(), 0x0000D3BF);
    EXPECT_EQ(cpu.get_eip(), 0x00008B95);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0416);

    // Final RAM entries
}

//
// imul ax,[ss:bp+di+7686h],B10Fh
//
TEST_F(Test386, imul_ax_ss_bp_di_7686h_B10Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x7339F584);
    cpu.set_ecx(0x000000AF);
    cpu.set_edx(0x80000000);
    cpu.set_esi(0x26F846C2);
    cpu.set_edi(0x4DB1BF46);
    cpu.set_ebp(0x924B6744);
    cpu.set_esp(0x00009D56);
    cpu.set_cs(0x00000001);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00006A58);
    cpu.set_fs(0x0000FB69);
    cpu.set_gs(0x0000EE43);
    cpu.set_ss(0x000070FC);
    cpu.set_eip(0x0000AAB8);
    cpu.set_eflags(0xFFFC00D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0AAC8, 0x69);
    machine.mem_store_byte(0x0AAC9, 0x83);
    machine.mem_store_byte(0x0AACA, 0x86);
    machine.mem_store_byte(0x0AACB, 0x76);
    machine.mem_store_byte(0x0AACC, 0x0F);
    machine.mem_store_byte(0x0AACD, 0xB1);
    machine.mem_store_byte(0x0AACE, 0xF4);
    machine.mem_store_byte(0x0AACF, 0x54);
    machine.mem_store_byte(0x0AAD0, 0xF3);
    machine.mem_store_byte(0x0AAD1, 0x3A);
    machine.mem_store_byte(0x0AAD2, 0x92);
    machine.mem_store_byte(0x0AAD3, 0xFB);
    machine.mem_store_byte(0x7ACD0, 0x22);
    machine.mem_store_byte(0x7ACD1, 0x5A);
    machine.mem_store_byte(0x0AAD4, 0xB0);
    machine.mem_store_byte(0x0AAD5, 0x7E);
    machine.mem_store_byte(0x0AAD6, 0x06);
    machine.mem_store_byte(0x0AAD7, 0x14);
    machine.mem_store_byte(0x0AAD8, 0xD3);
    machine.mem_store_byte(0x0AAD9, 0x14);
    machine.mem_store_byte(0x0AADA, 0x67);
    machine.mem_store_byte(0x0AADB, 0x77);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0000C9FE);
    EXPECT_EQ(cpu.get_ebx(), 0x7339F584);
    EXPECT_EQ(cpu.get_ecx(), 0x000000AF);
    EXPECT_EQ(cpu.get_edx(), 0x80000000);
    EXPECT_EQ(cpu.get_esi(), 0x26F846C2);
    EXPECT_EQ(cpu.get_edi(), 0x4DB1BF46);
    EXPECT_EQ(cpu.get_ebp(), 0x924B6744);
    EXPECT_EQ(cpu.get_esp(), 0x00009D56);
    EXPECT_EQ(cpu.get_cs(), 0x00000001);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00006A58);
    EXPECT_EQ(cpu.get_fs(), 0x0000FB69);
    EXPECT_EQ(cpu.get_gs(), 0x0000EE43);
    EXPECT_EQ(cpu.get_ss(), 0x000070FC);
    EXPECT_EQ(cpu.get_eip(), 0x0000AABF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0883);

    // Final RAM entries
}

//
// imul byte [ds:bx+di+11h]
//
TEST_F(Test386, imul_byte_ds_bx_di_11h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE73E12D9);
    cpu.set_ebx(0xB35B03EF);
    cpu.set_ecx(0x130F92AC);
    cpu.set_edx(0xD5511D7E);
    cpu.set_esi(0x0080FFE6);
    cpu.set_edi(0x7FFFFFFF);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x0000000E);
    cpu.set_cs(0x0000FCB7);
    cpu.set_ds(0x00007FFF);
    cpu.set_es(0x0000D0A6);
    cpu.set_fs(0x0000C8AB);
    cpu.set_gs(0x000005B5);
    cpu.set_ss(0x00000FE9);
    cpu.set_eip(0x00000090);
    cpu.set_eflags(0xFFFC0C03);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFCC00, 0xF6);
    machine.mem_store_byte(0xFCC01, 0x69);
    machine.mem_store_byte(0xFCC02, 0x11);
    machine.mem_store_byte(0xFCC03, 0xF4);
    machine.mem_store_byte(0xFCC04, 0x3D);
    machine.mem_store_byte(0xFCC05, 0x81);
    machine.mem_store_byte(0xFCC06, 0x6E);
    machine.mem_store_byte(0xFCC07, 0x01);
    machine.mem_store_byte(0xFCC08, 0x1A);
    machine.mem_store_byte(0xFCC09, 0x9E);
    machine.mem_store_byte(0x803EF, 0x6F);
    machine.mem_store_byte(0xFCC0A, 0x78);
    machine.mem_store_byte(0xFCC0B, 0xEC);
    machine.mem_store_byte(0xFCC0C, 0x40);
    machine.mem_store_byte(0xFCC0D, 0xDF);
    machine.mem_store_byte(0xFCC0E, 0x75);
    machine.mem_store_byte(0xFCC0F, 0xF6);
    machine.mem_store_byte(0xFCC10, 0xC6);
    machine.mem_store_byte(0xFCC11, 0xC6);
    machine.mem_store_byte(0xFCC12, 0x8B);
    machine.mem_store_byte(0xFCC13, 0x3E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE73EEF17);
    EXPECT_EQ(cpu.get_ebx(), 0xB35B03EF);
    EXPECT_EQ(cpu.get_ecx(), 0x130F92AC);
    EXPECT_EQ(cpu.get_edx(), 0xD5511D7E);
    EXPECT_EQ(cpu.get_esi(), 0x0080FFE6);
    EXPECT_EQ(cpu.get_edi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000000E);
    EXPECT_EQ(cpu.get_cs(), 0x0000FCB7);
    EXPECT_EQ(cpu.get_ds(), 0x00007FFF);
    EXPECT_EQ(cpu.get_es(), 0x0000D0A6);
    EXPECT_EQ(cpu.get_fs(), 0x0000C8AB);
    EXPECT_EQ(cpu.get_gs(), 0x000005B5);
    EXPECT_EQ(cpu.get_ss(), 0x00000FE9);
    EXPECT_EQ(cpu.get_eip(), 0x00000094);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C83);

    // Final RAM entries
}

//
// imul di,[gs:bx+si+40C6h],FFC4h
//
TEST_F(Test386, imul_di_gs_bx_si_40C6h_FFC4h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x05558EE0);
    cpu.set_ebx(0x336BA138);
    cpu.set_ecx(0xADC424AC);
    cpu.set_edx(0xF9D1C9CC);
    cpu.set_esi(0x23B94FB8);
    cpu.set_edi(0xB875D79B);
    cpu.set_ebp(0x96C3C22B);
    cpu.set_esp(0x00008F5A);
    cpu.set_cs(0x00005EE3);
    cpu.set_ds(0x00000095);
    cpu.set_es(0x00000BE9);
    cpu.set_fs(0x0000B5AA);
    cpu.set_gs(0x00005CCE);
    cpu.set_ss(0x00006AC1);
    cpu.set_eip(0x0000D438);
    cpu.set_eflags(0xFFFC08D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6C268, 0x3E);
    machine.mem_store_byte(0x6C269, 0x65);
    machine.mem_store_byte(0x6C26A, 0x6B);
    machine.mem_store_byte(0x6C26B, 0xB8);
    machine.mem_store_byte(0x6C26C, 0xC6);
    machine.mem_store_byte(0x6C26D, 0x40);
    machine.mem_store_byte(0x6C26E, 0xC4);
    machine.mem_store_byte(0x6C26F, 0xF4);
    machine.mem_store_byte(0x6C270, 0xFF);
    machine.mem_store_byte(0x6C271, 0xFF);
    machine.mem_store_byte(0x6C272, 0xFF);
    machine.mem_store_byte(0x6C273, 0xFF);
    machine.mem_store_byte(0x6C274, 0xFF);
    machine.mem_store_byte(0x6C275, 0xFF);
    machine.mem_store_byte(0x5FE96, 0xFF);
    machine.mem_store_byte(0x5FE97, 0xFF);
    machine.mem_store_byte(0x6C276, 0xFF);
    machine.mem_store_byte(0x6C277, 0xFF);
    machine.mem_store_byte(0x6C278, 0xFF);
    machine.mem_store_byte(0x6C279, 0xFF);
    machine.mem_store_byte(0x6C27A, 0xFF);
    machine.mem_store_byte(0x6C27B, 0xFF);
    machine.mem_store_byte(0x6C27C, 0xFF);
    machine.mem_store_byte(0x6C27D, 0xFF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x05558EE0);
    EXPECT_EQ(cpu.get_ebx(), 0x336BA138);
    EXPECT_EQ(cpu.get_ecx(), 0xADC424AC);
    EXPECT_EQ(cpu.get_edx(), 0xF9D1C9CC);
    EXPECT_EQ(cpu.get_esi(), 0x23B94FB8);
    EXPECT_EQ(cpu.get_edi(), 0xB875003C);
    EXPECT_EQ(cpu.get_ebp(), 0x96C3C22B);
    EXPECT_EQ(cpu.get_esp(), 0x00008F5A);
    EXPECT_EQ(cpu.get_cs(), 0x00005EE3);
    EXPECT_EQ(cpu.get_ds(), 0x00000095);
    EXPECT_EQ(cpu.get_es(), 0x00000BE9);
    EXPECT_EQ(cpu.get_fs(), 0x0000B5AA);
    EXPECT_EQ(cpu.get_gs(), 0x00005CCE);
    EXPECT_EQ(cpu.get_ss(), 0x00006AC1);
    EXPECT_EQ(cpu.get_eip(), 0x0000D440);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0012);

    // Final RAM entries
}

//
// imul dword [ds:ebx-1B8Fh]
//
TEST_F(Test386, imul_dword_ds_ebx_1B8Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB8573002);
    cpu.set_ebx(0x0000FFFF);
    cpu.set_ecx(0x00008000);
    cpu.set_edx(0x790E02DC);
    cpu.set_esi(0xEF7BF5BA);
    cpu.set_edi(0x20A6C341);
    cpu.set_ebp(0x12015F8A);
    cpu.set_esp(0x0000A74C);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00002077);
    cpu.set_es(0x00000269);
    cpu.set_fs(0x000033A5);
    cpu.set_gs(0x0000F7F8);
    cpu.set_ss(0x00000081);
    cpu.set_eip(0x00004398);
    cpu.set_eflags(0xFFFC04D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x104388, 0x66);
    machine.mem_store_byte(0x104389, 0x67);
    machine.mem_store_byte(0x10438A, 0xF7);
    machine.mem_store_byte(0x10438B, 0xAB);
    machine.mem_store_byte(0x10438C, 0x71);
    machine.mem_store_byte(0x10438D, 0xE4);
    machine.mem_store_byte(0x10438E, 0xFF);
    machine.mem_store_byte(0x10438F, 0xFF);
    machine.mem_store_byte(0x104390, 0xF4);
    machine.mem_store_byte(0x104391, 0x5D);
    machine.mem_store_byte(0x104392, 0x46);
    machine.mem_store_byte(0x104393, 0x93);
    machine.mem_store_byte(0x2EBE0, 0xD6);
    machine.mem_store_byte(0x2EBE1, 0x42);
    machine.mem_store_byte(0x2EBE2, 0x49);
    machine.mem_store_byte(0x2EBE3, 0x6A);
    machine.mem_store_byte(0x104394, 0x4A);
    machine.mem_store_byte(0x104395, 0xF2);
    machine.mem_store_byte(0x104396, 0x93);
    machine.mem_store_byte(0x104397, 0x28);
    machine.mem_store_byte(0x104398, 0x18);
    machine.mem_store_byte(0x104399, 0xE2);
    machine.mem_store_byte(0x10439A, 0x5E);
    machine.mem_store_byte(0x10439B, 0xED);
    machine.mem_store_byte(0x10439C, 0x0B);
    machine.mem_store_byte(0x10439D, 0x5E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x17D4A5AC);
    EXPECT_EQ(cpu.get_ebx(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x00008000);
    EXPECT_EQ(cpu.get_edx(), 0xE23F9808);
    EXPECT_EQ(cpu.get_esi(), 0xEF7BF5BA);
    EXPECT_EQ(cpu.get_edi(), 0x20A6C341);
    EXPECT_EQ(cpu.get_ebp(), 0x12015F8A);
    EXPECT_EQ(cpu.get_esp(), 0x0000A74C);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x00002077);
    EXPECT_EQ(cpu.get_es(), 0x00000269);
    EXPECT_EQ(cpu.get_fs(), 0x000033A5);
    EXPECT_EQ(cpu.get_gs(), 0x0000F7F8);
    EXPECT_EQ(cpu.get_ss(), 0x00000081);
    EXPECT_EQ(cpu.get_eip(), 0x000043A1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C93);

    // Final RAM entries
}

//
// imul eax,[ss:bp+di+7686h],9C25B10Fh
//
TEST_F(Test386, imul_eax_ss_bp_di_7686h_9C25B10Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x7339F584);
    cpu.set_ecx(0x000000AF);
    cpu.set_edx(0x80000000);
    cpu.set_esi(0x26F846C2);
    cpu.set_edi(0x4DB1BF46);
    cpu.set_ebp(0x924B6744);
    cpu.set_esp(0x00009D56);
    cpu.set_cs(0x00000001);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00006A58);
    cpu.set_fs(0x0000FB69);
    cpu.set_gs(0x0000EE43);
    cpu.set_ss(0x000070FC);
    cpu.set_eip(0x0000AAB8);
    cpu.set_eflags(0xFFFC00D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0AAC8, 0x66);
    machine.mem_store_byte(0x0AAC9, 0x69);
    machine.mem_store_byte(0x0AACA, 0x83);
    machine.mem_store_byte(0x0AACB, 0x86);
    machine.mem_store_byte(0x0AACC, 0x76);
    machine.mem_store_byte(0x0AACD, 0x0F);
    machine.mem_store_byte(0x0AACE, 0xB1);
    machine.mem_store_byte(0x0AACF, 0x25);
    machine.mem_store_byte(0x0AAD0, 0x9C);
    machine.mem_store_byte(0x0AAD1, 0xF4);
    machine.mem_store_byte(0x0AAD2, 0x92);
    machine.mem_store_byte(0x0AAD3, 0xFB);
    machine.mem_store_byte(0x0AAD4, 0xB0);
    machine.mem_store_byte(0x0AAD5, 0x7E);
    machine.mem_store_byte(0x0AAD6, 0x06);
    machine.mem_store_byte(0x0AAD7, 0x14);
    machine.mem_store_byte(0x7ACD0, 0x22);
    machine.mem_store_byte(0x7ACD1, 0x5A);
    machine.mem_store_byte(0x7ACD2, 0xA2);
    machine.mem_store_byte(0x7ACD3, 0xB8);
    machine.mem_store_byte(0x0AAD8, 0xD3);
    machine.mem_store_byte(0x0AAD9, 0x14);
    machine.mem_store_byte(0x0AADA, 0x67);
    machine.mem_store_byte(0x0AADB, 0x77);
    machine.mem_store_byte(0x0AADC, 0x6C);
    machine.mem_store_byte(0x0AADD, 0xBE);
    machine.mem_store_byte(0x0AADE, 0xCA);
    machine.mem_store_byte(0x0AADF, 0xEF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD0BEC9FE);
    EXPECT_EQ(cpu.get_ebx(), 0x7339F584);
    EXPECT_EQ(cpu.get_ecx(), 0x000000AF);
    EXPECT_EQ(cpu.get_edx(), 0x80000000);
    EXPECT_EQ(cpu.get_esi(), 0x26F846C2);
    EXPECT_EQ(cpu.get_edi(), 0x4DB1BF46);
    EXPECT_EQ(cpu.get_ebp(), 0x924B6744);
    EXPECT_EQ(cpu.get_esp(), 0x00009D56);
    EXPECT_EQ(cpu.get_cs(), 0x00000001);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00006A58);
    EXPECT_EQ(cpu.get_fs(), 0x0000FB69);
    EXPECT_EQ(cpu.get_gs(), 0x0000EE43);
    EXPECT_EQ(cpu.get_ss(), 0x000070FC);
    EXPECT_EQ(cpu.get_eip(), 0x0000AAC2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
}

//
// in eax,7Fh
//
TEST_F(Test386, in_eax_7Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0FDE6BCB);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x4D69E7FA);
    cpu.set_edx(0x32A5F51E);
    cpu.set_esi(0xECB04969);
    cpu.set_edi(0x000000A0);
    cpu.set_ebp(0x496FAAD3);
    cpu.set_esp(0x00008E06);
    cpu.set_cs(0x0000A490);
    cpu.set_ds(0x0000ED61);
    cpu.set_es(0x0000F4E2);
    cpu.set_fs(0x00006DF7);
    cpu.set_gs(0x0000D953);
    cpu.set_ss(0x0000FE83);
    cpu.set_eip(0x00007E90);
    cpu.set_eflags(0xFFFC0402);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAC790, 0x66);
    machine.mem_store_byte(0xAC791, 0xE5);
    machine.mem_store_byte(0xAC792, 0x7F);
    machine.mem_store_byte(0xAC793, 0xF4);
    machine.mem_store_byte(0xAC794, 0x2F);
    machine.mem_store_byte(0xAC795, 0x38);
    machine.mem_store_byte(0xAC796, 0x23);
    machine.mem_store_byte(0xAC797, 0xA8);
    machine.mem_store_byte(0xAC798, 0x25);
    machine.mem_store_byte(0xAC799, 0xEC);
    machine.mem_store_byte(0xAC79A, 0xA4);
    machine.mem_store_byte(0xAC79B, 0xEC);
    machine.mem_store_byte(0xAC79C, 0x75);
    machine.mem_store_byte(0xAC79D, 0x8D);
    machine.mem_store_byte(0xAC79E, 0x8D);
    machine.mem_store_byte(0xAC79F, 0x84);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x4D69E7FA);
    EXPECT_EQ(cpu.get_edx(), 0x32A5F51E);
    EXPECT_EQ(cpu.get_esi(), 0xECB04969);
    EXPECT_EQ(cpu.get_edi(), 0x000000A0);
    EXPECT_EQ(cpu.get_ebp(), 0x496FAAD3);
    EXPECT_EQ(cpu.get_esp(), 0x00008E06);
    EXPECT_EQ(cpu.get_cs(), 0x0000A490);
    EXPECT_EQ(cpu.get_ds(), 0x0000ED61);
    EXPECT_EQ(cpu.get_es(), 0x0000F4E2);
    EXPECT_EQ(cpu.get_fs(), 0x00006DF7);
    EXPECT_EQ(cpu.get_gs(), 0x0000D953);
    EXPECT_EQ(cpu.get_ss(), 0x0000FE83);
    EXPECT_EQ(cpu.get_eip(), 0x00007E94);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0402);

    // Final RAM entries
}

//
// inc eax
//
TEST_F(Test386, inc_eax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD1AD09C5);
    cpu.set_ebx(0x1C5A91DA);
    cpu.set_ecx(0xA235695C);
    cpu.set_edx(0x5AF14370);
    cpu.set_esi(0x276D2B75);
    cpu.set_edi(0x26C79842);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x00005AE4);
    cpu.set_cs(0x0000C314);
    cpu.set_ds(0x00002517);
    cpu.set_es(0x0000F1A3);
    cpu.set_fs(0x00002014);
    cpu.set_gs(0x000081DA);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x00001818);
    cpu.set_eflags(0xFFFC0816);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC4958, 0x66);
    machine.mem_store_byte(0xC4959, 0x40);
    machine.mem_store_byte(0xC495A, 0xF4);
    machine.mem_store_byte(0xC495B, 0xAF);
    machine.mem_store_byte(0xC495C, 0x71);
    machine.mem_store_byte(0xC495D, 0x30);
    machine.mem_store_byte(0xC495E, 0x4A);
    machine.mem_store_byte(0xC495F, 0x6F);
    machine.mem_store_byte(0xC4960, 0x3A);
    machine.mem_store_byte(0xC4961, 0x08);
    machine.mem_store_byte(0xC4962, 0x57);
    machine.mem_store_byte(0xC4963, 0x78);
    machine.mem_store_byte(0xC4964, 0x64);
    machine.mem_store_byte(0xC4965, 0x90);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD1AD09C6);
    EXPECT_EQ(cpu.get_ebx(), 0x1C5A91DA);
    EXPECT_EQ(cpu.get_ecx(), 0xA235695C);
    EXPECT_EQ(cpu.get_edx(), 0x5AF14370);
    EXPECT_EQ(cpu.get_esi(), 0x276D2B75);
    EXPECT_EQ(cpu.get_edi(), 0x26C79842);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x00005AE4);
    EXPECT_EQ(cpu.get_cs(), 0x0000C314);
    EXPECT_EQ(cpu.get_ds(), 0x00002517);
    EXPECT_EQ(cpu.get_es(), 0x0000F1A3);
    EXPECT_EQ(cpu.get_fs(), 0x00002014);
    EXPECT_EQ(cpu.get_gs(), 0x000081DA);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x0000181B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0086);

    // Final RAM entries
}

//
// iretd
//
TEST_F(Test386, iretd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000040);
    cpu.set_ebx(0x5A3A3442);
    cpu.set_ecx(0x048530C5);
    cpu.set_edx(0xFDE25D6F);
    cpu.set_esi(0x12BBBE85);
    cpu.set_edi(0x18C09199);
    cpu.set_ebp(0xF623044B);
    cpu.set_esp(0x0000FFFC);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x00008081);
    cpu.set_es(0x0000F007);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x0000A60D);
    cpu.set_ss(0x0000FF8F);
    cpu.set_eip(0x0000A888);
    cpu.set_eflags(0xFFFC0053);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0A888, 0x66);
    machine.mem_store_byte(0x0A889, 0xCF);
    machine.mem_store_byte(0x0A88A, 0xF4);
    machine.mem_store_byte(0x0A88B, 0x00);
    machine.mem_store_byte(0x0A88C, 0x00);
    machine.mem_store_byte(0x0A88D, 0x00);
    machine.mem_store_byte(0x0A88E, 0x00);
    machine.mem_store_byte(0x0A88F, 0x00);
    machine.mem_store_byte(0x10F8EC, 0x00);
    machine.mem_store_byte(0x10F8ED, 0x00);
    machine.mem_store_byte(0x10F8EE, 0x00);
    machine.mem_store_byte(0x10F8EF, 0x00);
    machine.mem_store_byte(0xFF8F0, 0x00);
    machine.mem_store_byte(0xFF8F1, 0x00);
    machine.mem_store_byte(0xFF8F2, 0x00);
    machine.mem_store_byte(0xFF8F3, 0x00);
    machine.mem_store_byte(0xFF8F4, 0x00);
    machine.mem_store_byte(0xFF8F5, 0x08);
    machine.mem_store_byte(0xFF8F6, 0x00);
    machine.mem_store_byte(0xFF8F7, 0x00);
    machine.mem_store_byte(0x00000, 0xF4);
    machine.mem_store_byte(0x00001, 0xF4);
    machine.mem_store_byte(0x00002, 0x34);
    machine.mem_store_byte(0x00003, 0xAD);
    machine.mem_store_byte(0x00004, 0xA8);
    machine.mem_store_byte(0x00005, 0x4A);
    machine.mem_store_byte(0x00006, 0x1A);
    machine.mem_store_byte(0x00007, 0x34);
    machine.mem_store_byte(0x00008, 0xE3);
    machine.mem_store_byte(0x00009, 0x3E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000040);
    EXPECT_EQ(cpu.get_ebx(), 0x5A3A3442);
    EXPECT_EQ(cpu.get_ecx(), 0x048530C5);
    EXPECT_EQ(cpu.get_edx(), 0xFDE25D6F);
    EXPECT_EQ(cpu.get_esi(), 0x12BBBE85);
    EXPECT_EQ(cpu.get_edi(), 0x18C09199);
    EXPECT_EQ(cpu.get_ebp(), 0xF623044B);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x00008081);
    EXPECT_EQ(cpu.get_es(), 0x0000F007);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000A60D);
    EXPECT_EQ(cpu.get_ss(), 0x0000FF8F);
    EXPECT_EQ(cpu.get_eip(), 0x00000001);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0802);

    // Final RAM entries
}

//
// imul esi,[ds:bx+di+127Ah]
//
TEST_F(Test386, imul_esi_ds_bx_di_127Ah)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xBCDCB967);
    cpu.set_ebx(0x25B9F876);
    cpu.set_ecx(0xCB6FCBC1);
    cpu.set_edx(0x54DFC526);
    cpu.set_esi(0x2492F0A9);
    cpu.set_edi(0x00008000);
    cpu.set_ebp(0xFB67EFC8);
    cpu.set_esp(0x00003812);
    cpu.set_cs(0x0000000D);
    cpu.set_ds(0x00009E31);
    cpu.set_es(0x0000FA5D);
    cpu.set_fs(0x00009E2A);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x00001743);
    cpu.set_eip(0x00003488);
    cpu.set_eflags(0xFFFC0C82);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x03558, 0x66);
    machine.mem_store_byte(0x03559, 0x0F);
    machine.mem_store_byte(0x0355A, 0xAF);
    machine.mem_store_byte(0x0355B, 0xB1);
    machine.mem_store_byte(0x0355C, 0x7A);
    machine.mem_store_byte(0x0355D, 0x12);
    machine.mem_store_byte(0x0355E, 0xF4);
    machine.mem_store_byte(0x0355F, 0xFE);
    machine.mem_store_byte(0x03560, 0x00);
    machine.mem_store_byte(0x03561, 0xCE);
    machine.mem_store_byte(0x03562, 0x44);
    machine.mem_store_byte(0x03563, 0x7F);
    machine.mem_store_byte(0xA6E00, 0x56);
    machine.mem_store_byte(0xA6E01, 0x00);
    machine.mem_store_byte(0xA6E02, 0x96);
    machine.mem_store_byte(0xA6E03, 0x0E);
    machine.mem_store_byte(0x03564, 0x9E);
    machine.mem_store_byte(0x03565, 0xDF);
    machine.mem_store_byte(0x03566, 0x98);
    machine.mem_store_byte(0x03567, 0x07);
    machine.mem_store_byte(0x03568, 0x49);
    machine.mem_store_byte(0x03569, 0x7F);
    machine.mem_store_byte(0x0356A, 0x72);
    machine.mem_store_byte(0x0356B, 0xC7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xBCDCB967);
    EXPECT_EQ(cpu.get_ebx(), 0x25B9F876);
    EXPECT_EQ(cpu.get_ecx(), 0xCB6FCBC1);
    EXPECT_EQ(cpu.get_edx(), 0x54DFC526);
    EXPECT_EQ(cpu.get_esi(), 0x8A62D8C6);
    EXPECT_EQ(cpu.get_edi(), 0x00008000);
    EXPECT_EQ(cpu.get_ebp(), 0xFB67EFC8);
    EXPECT_EQ(cpu.get_esp(), 0x00003812);
    EXPECT_EQ(cpu.get_cs(), 0x0000000D);
    EXPECT_EQ(cpu.get_ds(), 0x00009E31);
    EXPECT_EQ(cpu.get_es(), 0x0000FA5D);
    EXPECT_EQ(cpu.get_fs(), 0x00009E2A);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x00001743);
    EXPECT_EQ(cpu.get_eip(), 0x0000348F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C17);

    // Final RAM entries
}

//
// imul word [ds:ebx-1B8Fh]
//
TEST_F(Test386, imul_word_ds_ebx_1B8Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB8573002);
    cpu.set_ebx(0x0000FFFF);
    cpu.set_ecx(0x00008000);
    cpu.set_edx(0x790E02DC);
    cpu.set_esi(0xEF7BF5BA);
    cpu.set_edi(0x20A6C341);
    cpu.set_ebp(0x12015F8A);
    cpu.set_esp(0x0000A74C);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00002077);
    cpu.set_es(0x00000269);
    cpu.set_fs(0x000033A5);
    cpu.set_gs(0x0000F7F8);
    cpu.set_ss(0x00000081);
    cpu.set_eip(0x00004398);
    cpu.set_eflags(0xFFFC04D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x104388, 0x67);
    machine.mem_store_byte(0x104389, 0xF7);
    machine.mem_store_byte(0x10438A, 0xAB);
    machine.mem_store_byte(0x10438B, 0x71);
    machine.mem_store_byte(0x10438C, 0xE4);
    machine.mem_store_byte(0x10438D, 0xFF);
    machine.mem_store_byte(0x10438E, 0xFF);
    machine.mem_store_byte(0x10438F, 0xF4);
    machine.mem_store_byte(0x104390, 0x58);
    machine.mem_store_byte(0x104391, 0x5D);
    machine.mem_store_byte(0x104392, 0x46);
    machine.mem_store_byte(0x104393, 0x93);
    machine.mem_store_byte(0x2EBE0, 0xD6);
    machine.mem_store_byte(0x2EBE1, 0x42);
    machine.mem_store_byte(0x104394, 0x4A);
    machine.mem_store_byte(0x104395, 0xF2);
    machine.mem_store_byte(0x104396, 0x93);
    machine.mem_store_byte(0x104397, 0x28);
    machine.mem_store_byte(0x104398, 0x18);
    machine.mem_store_byte(0x104399, 0xE2);
    machine.mem_store_byte(0x10439A, 0x5E);
    machine.mem_store_byte(0x10439B, 0xED);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xB857A5AC);
    EXPECT_EQ(cpu.get_ebx(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x00008000);
    EXPECT_EQ(cpu.get_edx(), 0x790E0C88);
    EXPECT_EQ(cpu.get_esi(), 0xEF7BF5BA);
    EXPECT_EQ(cpu.get_edi(), 0x20A6C341);
    EXPECT_EQ(cpu.get_ebp(), 0x12015F8A);
    EXPECT_EQ(cpu.get_esp(), 0x0000A74C);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x00002077);
    EXPECT_EQ(cpu.get_es(), 0x00000269);
    EXPECT_EQ(cpu.get_fs(), 0x000033A5);
    EXPECT_EQ(cpu.get_gs(), 0x0000F7F8);
    EXPECT_EQ(cpu.get_ss(), 0x00000081);
    EXPECT_EQ(cpu.get_eip(), 0x000043A0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C07);

    // Final RAM entries
}
