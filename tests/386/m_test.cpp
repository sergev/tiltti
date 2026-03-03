#include "test386.h"

//
// mov al,[dword ds:69Ch]
//
TEST_F(Test386, mov_al_dword_ds_69Ch)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x23055590);
    cpu.set_ebx(0x2C80B36A);
    cpu.set_ecx(0xCFAAD080);
    cpu.set_edx(0x558DF363);
    cpu.set_esi(0x428CBD1C);
    cpu.set_edi(0x9FA3324A);
    cpu.set_ebp(0x00010001);
    cpu.set_esp(0x0000CA0A);
    cpu.set_cs(0x00005780);
    cpu.set_ds(0x00003DE7);
    cpu.set_es(0x0000362C);
    cpu.set_fs(0x0000FE05);
    cpu.set_gs(0x0000A4C9);
    cpu.set_ss(0x0000246B);
    cpu.set_eip(0x0000C4E8);
    cpu.set_eflags(0xFFFC0047);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x63CE8, 0x67);
    machine.mem_store_byte(0x63CE9, 0xA0);
    machine.mem_store_byte(0x63CEA, 0x9C);
    machine.mem_store_byte(0x63CEB, 0x06);
    machine.mem_store_byte(0x63CEC, 0x00);
    machine.mem_store_byte(0x63CED, 0x00);
    machine.mem_store_byte(0x63CEE, 0xF4);
    machine.mem_store_byte(0x63CEF, 0xC9);
    machine.mem_store_byte(0x63CF0, 0x1E);
    machine.mem_store_byte(0x63CF1, 0xDC);
    machine.mem_store_byte(0x63CF2, 0x03);
    machine.mem_store_byte(0x63CF3, 0xCB);
    machine.mem_store_byte(0x3E50C, 0x21);
    machine.mem_store_byte(0x63CF4, 0x14);
    machine.mem_store_byte(0x63CF5, 0x19);
    machine.mem_store_byte(0x63CF6, 0x20);
    machine.mem_store_byte(0x63CF7, 0x58);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x23055521);
    EXPECT_EQ(cpu.get_ebx(), 0x2C80B36A);
    EXPECT_EQ(cpu.get_ecx(), 0xCFAAD080);
    EXPECT_EQ(cpu.get_edx(), 0x558DF363);
    EXPECT_EQ(cpu.get_esi(), 0x428CBD1C);
    EXPECT_EQ(cpu.get_edi(), 0x9FA3324A);
    EXPECT_EQ(cpu.get_ebp(), 0x00010001);
    EXPECT_EQ(cpu.get_esp(), 0x0000CA0A);
    EXPECT_EQ(cpu.get_cs(), 0x00005780);
    EXPECT_EQ(cpu.get_ds(), 0x00003DE7);
    EXPECT_EQ(cpu.get_es(), 0x0000362C);
    EXPECT_EQ(cpu.get_fs(), 0x0000FE05);
    EXPECT_EQ(cpu.get_gs(), 0x0000A4C9);
    EXPECT_EQ(cpu.get_ss(), 0x0000246B);
    EXPECT_EQ(cpu.get_eip(), 0x0000C4EF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0047);

    // Final RAM entries
}

//
// mov byte [ss:ebp+6E97h],D4h
//
TEST_F(Test386, mov_byte_ss_ebp_6E97h_D4h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00008081);
    cpu.set_ebx(0x89233A9A);
    cpu.set_ecx(0x7FFFFFFF);
    cpu.set_edx(0xE2572916);
    cpu.set_esi(0x0852281E);
    cpu.set_edi(0x69F8119B);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x00008000);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000E551);
    cpu.set_es(0x0000D3CC);
    cpu.set_fs(0x000047D7);
    cpu.set_gs(0x00000008);
    cpu.set_ss(0x0000215C);
    cpu.set_eip(0x0000D4E8);
    cpu.set_eflags(0xFFFC04D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0D4E8, 0x67);
    machine.mem_store_byte(0x0D4E9, 0xC6);
    machine.mem_store_byte(0x0D4EA, 0x85);
    machine.mem_store_byte(0x0D4EB, 0x97);
    machine.mem_store_byte(0x0D4EC, 0x6E);
    machine.mem_store_byte(0x0D4ED, 0x00);
    machine.mem_store_byte(0x0D4EE, 0x00);
    machine.mem_store_byte(0x0D4EF, 0xD4);
    machine.mem_store_byte(0x0D4F0, 0xF4);
    machine.mem_store_byte(0x0D4F1, 0x96);
    machine.mem_store_byte(0x0D4F2, 0x51);
    machine.mem_store_byte(0x0D4F3, 0xF5);
    machine.mem_store_byte(0x0D4F4, 0xDD);
    machine.mem_store_byte(0x0D4F5, 0x2E);
    machine.mem_store_byte(0x0D4F6, 0x3C);
    machine.mem_store_byte(0x0D4F7, 0xD1);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00008081);
    EXPECT_EQ(cpu.get_ebx(), 0x89233A9A);
    EXPECT_EQ(cpu.get_ecx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xE2572916);
    EXPECT_EQ(cpu.get_esi(), 0x0852281E);
    EXPECT_EQ(cpu.get_edi(), 0x69F8119B);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x00008000);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000E551);
    EXPECT_EQ(cpu.get_es(), 0x0000D3CC);
    EXPECT_EQ(cpu.get_fs(), 0x000047D7);
    EXPECT_EQ(cpu.get_gs(), 0x00000008);
    EXPECT_EQ(cpu.get_ss(), 0x0000215C);
    EXPECT_EQ(cpu.get_eip(), 0x0000D4F1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04D2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30456), 0xD4);
}

//
// mov eax,ebx
//
TEST_F(Test386, mov_eax_ebx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xCCAAF0F6);
    cpu.set_ebx(0xE3E63584);
    cpu.set_ecx(0x2F98329B);
    cpu.set_edx(0x00080001);
    cpu.set_esi(0x0673FA6B);
    cpu.set_edi(0x3CEA5B06);
    cpu.set_ebp(0x368AB0F9);
    cpu.set_esp(0x0000DC16);
    cpu.set_cs(0x00005FC9);
    cpu.set_ds(0x00001DF7);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00002001);
    cpu.set_gs(0x0000925E);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00003270);
    cpu.set_eflags(0xFFFC0852);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x62F00, 0x2E);
    machine.mem_store_byte(0x62F01, 0x26);
    machine.mem_store_byte(0x62F02, 0x67);
    machine.mem_store_byte(0x62F03, 0x66);
    machine.mem_store_byte(0x62F04, 0x8B);
    machine.mem_store_byte(0x62F05, 0xC3);
    machine.mem_store_byte(0x62F06, 0xF4);
    machine.mem_store_byte(0x62F07, 0xE1);
    machine.mem_store_byte(0x62F08, 0x93);
    machine.mem_store_byte(0x62F09, 0x32);
    machine.mem_store_byte(0x62F0A, 0xB0);
    machine.mem_store_byte(0x62F0B, 0x1C);
    machine.mem_store_byte(0x62F0C, 0x04);
    machine.mem_store_byte(0x62F0D, 0x32);
    machine.mem_store_byte(0x62F0E, 0xF3);
    machine.mem_store_byte(0x62F0F, 0xB0);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE3E63584);
    EXPECT_EQ(cpu.get_ebx(), 0xE3E63584);
    EXPECT_EQ(cpu.get_ecx(), 0x2F98329B);
    EXPECT_EQ(cpu.get_edx(), 0x00080001);
    EXPECT_EQ(cpu.get_esi(), 0x0673FA6B);
    EXPECT_EQ(cpu.get_edi(), 0x3CEA5B06);
    EXPECT_EQ(cpu.get_ebp(), 0x368AB0F9);
    EXPECT_EQ(cpu.get_esp(), 0x0000DC16);
    EXPECT_EQ(cpu.get_cs(), 0x00005FC9);
    EXPECT_EQ(cpu.get_ds(), 0x00001DF7);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00002001);
    EXPECT_EQ(cpu.get_gs(), 0x0000925E);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x00003277);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0852);

    // Final RAM entries
}

//
// mov [ds:CF18h],eax
//
TEST_F(Test386, mov_ds_CF18h_eax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x23D9DC15);
    cpu.set_ebx(0x15B8347A);
    cpu.set_ecx(0x9E8E8471);
    cpu.set_edx(0xF6908B51);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0xDB04848F);
    cpu.set_ebp(0x1473799D);
    cpu.set_esp(0x00005556);
    cpu.set_cs(0x0000BB4B);
    cpu.set_ds(0x00000201);
    cpu.set_es(0x00008182);
    cpu.set_fs(0x00000AB9);
    cpu.set_gs(0x0000C9E5);
    cpu.set_ss(0x00000115);
    cpu.set_eip(0x0000AB70);
    cpu.set_eflags(0xFFFC0042);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC6020, 0x66);
    machine.mem_store_byte(0xC6021, 0xA3);
    machine.mem_store_byte(0xC6022, 0x18);
    machine.mem_store_byte(0xC6023, 0xCF);
    machine.mem_store_byte(0xC6024, 0xF4);
    machine.mem_store_byte(0xC6025, 0xFF);
    machine.mem_store_byte(0xC6026, 0xFF);
    machine.mem_store_byte(0xC6027, 0xFF);
    machine.mem_store_byte(0xC6028, 0xFF);
    machine.mem_store_byte(0xC6029, 0xFF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x23D9DC15);
    EXPECT_EQ(cpu.get_ebx(), 0x15B8347A);
    EXPECT_EQ(cpu.get_ecx(), 0x9E8E8471);
    EXPECT_EQ(cpu.get_edx(), 0xF6908B51);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0xDB04848F);
    EXPECT_EQ(cpu.get_ebp(), 0x1473799D);
    EXPECT_EQ(cpu.get_esp(), 0x00005556);
    EXPECT_EQ(cpu.get_cs(), 0x0000BB4B);
    EXPECT_EQ(cpu.get_ds(), 0x00000201);
    EXPECT_EQ(cpu.get_es(), 0x00008182);
    EXPECT_EQ(cpu.get_fs(), 0x00000AB9);
    EXPECT_EQ(cpu.get_gs(), 0x0000C9E5);
    EXPECT_EQ(cpu.get_ss(), 0x00000115);
    EXPECT_EQ(cpu.get_eip(), 0x0000AB75);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0042);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0EF28), 0x15);
    EXPECT_EQ(memory.load8(0x0EF29), 0xDC);
    EXPECT_EQ(memory.load8(0x0EF2A), 0xD9);
    EXPECT_EQ(memory.load8(0x0EF2B), 0x23);
}

//
// mov eax,5C1A3C52h
//
TEST_F(Test386, mov_eax_5C1A3C52h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x90ADB179);
    cpu.set_ebx(0x91428FF9);
    cpu.set_ecx(0x8D628F3F);
    cpu.set_edx(0x1506C524);
    cpu.set_esi(0x23A1A322);
    cpu.set_edi(0x3B70337B);
    cpu.set_ebp(0xCCCDA3AD);
    cpu.set_esp(0x0000695C);
    cpu.set_cs(0x0000E973);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x0000C079);
    cpu.set_fs(0x0000A252);
    cpu.set_gs(0x00003F05);
    cpu.set_ss(0x0000BB36);
    cpu.set_eip(0x0000A8D0);
    cpu.set_eflags(0xFFFC0056);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF4000, 0x66);
    machine.mem_store_byte(0xF4001, 0xB8);
    machine.mem_store_byte(0xF4002, 0x52);
    machine.mem_store_byte(0xF4003, 0x3C);
    machine.mem_store_byte(0xF4004, 0x1A);
    machine.mem_store_byte(0xF4005, 0x5C);
    machine.mem_store_byte(0xF4006, 0xF4);
    machine.mem_store_byte(0xF4007, 0xBC);
    machine.mem_store_byte(0xF4008, 0xD7);
    machine.mem_store_byte(0xF4009, 0xED);
    machine.mem_store_byte(0xF400A, 0x83);
    machine.mem_store_byte(0xF400B, 0x4F);
    machine.mem_store_byte(0xF400C, 0x80);
    machine.mem_store_byte(0xF400D, 0x25);
    machine.mem_store_byte(0xF400E, 0x7E);
    machine.mem_store_byte(0xF400F, 0xCB);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x5C1A3C52);
    EXPECT_EQ(cpu.get_ebx(), 0x91428FF9);
    EXPECT_EQ(cpu.get_ecx(), 0x8D628F3F);
    EXPECT_EQ(cpu.get_edx(), 0x1506C524);
    EXPECT_EQ(cpu.get_esi(), 0x23A1A322);
    EXPECT_EQ(cpu.get_edi(), 0x3B70337B);
    EXPECT_EQ(cpu.get_ebp(), 0xCCCDA3AD);
    EXPECT_EQ(cpu.get_esp(), 0x0000695C);
    EXPECT_EQ(cpu.get_cs(), 0x0000E973);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x0000C079);
    EXPECT_EQ(cpu.get_fs(), 0x0000A252);
    EXPECT_EQ(cpu.get_gs(), 0x00003F05);
    EXPECT_EQ(cpu.get_ss(), 0x0000BB36);
    EXPECT_EQ(cpu.get_eip(), 0x0000A8D7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
}

//
// mov ebx,es
//
TEST_F(Test386, mov_ebx_es)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00040000);
    cpu.set_ebx(0x193479F9);
    cpu.set_ecx(0x00000000);
    cpu.set_edx(0x43F7BE41);
    cpu.set_esi(0x0000008F);
    cpu.set_edi(0x709EF573);
    cpu.set_ebp(0x0003FFFF);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00005F51);
    cpu.set_ds(0x000018C9);
    cpu.set_es(0x0000009F);
    cpu.set_fs(0x0000FFF6);
    cpu.set_gs(0x000040CF);
    cpu.set_ss(0x0000A391);
    cpu.set_eip(0x0000D9F8);
    cpu.set_eflags(0xFFFC04C2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6CF08, 0x67);
    machine.mem_store_byte(0x6CF09, 0x66);
    machine.mem_store_byte(0x6CF0A, 0x8C);
    machine.mem_store_byte(0x6CF0B, 0xC3);
    machine.mem_store_byte(0x6CF0C, 0xF4);
    machine.mem_store_byte(0x6CF0D, 0xBE);
    machine.mem_store_byte(0x6CF0E, 0x17);
    machine.mem_store_byte(0x6CF0F, 0x87);
    machine.mem_store_byte(0x6CF10, 0x8D);
    machine.mem_store_byte(0x6CF11, 0xE0);
    machine.mem_store_byte(0x6CF12, 0x72);
    machine.mem_store_byte(0x6CF13, 0x5B);
    machine.mem_store_byte(0x6CF14, 0xB9);
    machine.mem_store_byte(0x6CF15, 0x65);
    machine.mem_store_byte(0x6CF16, 0x4E);
    machine.mem_store_byte(0x6CF17, 0xD8);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00040000);
    EXPECT_EQ(cpu.get_ebx(), 0x0000009F);
    EXPECT_EQ(cpu.get_ecx(), 0x00000000);
    EXPECT_EQ(cpu.get_edx(), 0x43F7BE41);
    EXPECT_EQ(cpu.get_esi(), 0x0000008F);
    EXPECT_EQ(cpu.get_edi(), 0x709EF573);
    EXPECT_EQ(cpu.get_ebp(), 0x0003FFFF);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00005F51);
    EXPECT_EQ(cpu.get_ds(), 0x000018C9);
    EXPECT_EQ(cpu.get_es(), 0x0000009F);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFF6);
    EXPECT_EQ(cpu.get_gs(), 0x000040CF);
    EXPECT_EQ(cpu.get_ss(), 0x0000A391);
    EXPECT_EQ(cpu.get_eip(), 0x0000D9FD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C2);

    // Final RAM entries
}

//
// movsb
//
TEST_F(Test386, movsb)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0B237843);
    cpu.set_ebx(0x00008000);
    cpu.set_ecx(0x0A31127C);
    cpu.set_edx(0xBBCA8AA4);
    cpu.set_esi(0xED6626B9);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x80000000);
    cpu.set_esp(0x00008080);
    cpu.set_cs(0x000003B8);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x0000E1D0);
    cpu.set_fs(0x00000573);
    cpu.set_gs(0x0000DAB0);
    cpu.set_ss(0x0000C6B3);
    cpu.set_eip(0x000080B0);
    cpu.set_eflags(0xFFFC0407);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0BC30, 0xA4);
    machine.mem_store_byte(0x0BC31, 0xF4);
    machine.mem_store_byte(0x0BC32, 0x04);
    machine.mem_store_byte(0x0BC33, 0x1E);
    machine.mem_store_byte(0x0BC34, 0x03);
    machine.mem_store_byte(0x0BC35, 0xF1);
    machine.mem_store_byte(0x0BC36, 0x88);
    machine.mem_store_byte(0x0BC37, 0x83);
    machine.mem_store_byte(0x0BC38, 0x60);
    machine.mem_store_byte(0x0BC39, 0xDB);
    machine.mem_store_byte(0x1026A9, 0x48);
    machine.mem_store_byte(0x0BC3A, 0x68);
    machine.mem_store_byte(0x0BC3B, 0x8E);
    machine.mem_store_byte(0x0BC3C, 0xF0);
    machine.mem_store_byte(0x0BC3D, 0xB2);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0B237843);
    EXPECT_EQ(cpu.get_ebx(), 0x00008000);
    EXPECT_EQ(cpu.get_ecx(), 0x0A31127C);
    EXPECT_EQ(cpu.get_edx(), 0xBBCA8AA4);
    EXPECT_EQ(cpu.get_esi(), 0xED6626B8);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x80000000);
    EXPECT_EQ(cpu.get_esp(), 0x00008080);
    EXPECT_EQ(cpu.get_cs(), 0x000003B8);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x0000E1D0);
    EXPECT_EQ(cpu.get_fs(), 0x00000573);
    EXPECT_EQ(cpu.get_gs(), 0x0000DAB0);
    EXPECT_EQ(cpu.get_ss(), 0x0000C6B3);
    EXPECT_EQ(cpu.get_eip(), 0x000080B2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0407);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE1D00), 0x48);
}

//
// movsx dx,cx
//
TEST_F(Test386, movsx_dx_cx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x047496DF);
    cpu.set_ebx(0xF7F723A4);
    cpu.set_ecx(0x00000801);
    cpu.set_edx(0x37864AE4);
    cpu.set_esi(0x0358CA8D);
    cpu.set_edi(0x00200001);
    cpu.set_ebp(0x0F9041B3);
    cpu.set_esp(0x0000801E);
    cpu.set_cs(0x0000FFFE);
    cpu.set_ds(0x0000A3E0);
    cpu.set_es(0x0000EF6F);
    cpu.set_fs(0x0000393E);
    cpu.set_gs(0x0000F3C7);
    cpu.set_ss(0x00006EF7);
    cpu.set_eip(0x00005578);
    cpu.set_eflags(0xFFFC0846);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x105558, 0x67);
    machine.mem_store_byte(0x105559, 0x0F);
    machine.mem_store_byte(0x10555A, 0xBF);
    machine.mem_store_byte(0x10555B, 0xD1);
    machine.mem_store_byte(0x10555C, 0xF4);
    machine.mem_store_byte(0x10555D, 0x55);
    machine.mem_store_byte(0x10555E, 0xFC);
    machine.mem_store_byte(0x10555F, 0x61);
    machine.mem_store_byte(0x105560, 0xCD);
    machine.mem_store_byte(0x105561, 0xA8);
    machine.mem_store_byte(0x105562, 0x2A);
    machine.mem_store_byte(0x105563, 0x65);
    machine.mem_store_byte(0x105564, 0x27);
    machine.mem_store_byte(0x105565, 0x30);
    machine.mem_store_byte(0x105566, 0xCC);
    machine.mem_store_byte(0x105567, 0x80);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x047496DF);
    EXPECT_EQ(cpu.get_ebx(), 0xF7F723A4);
    EXPECT_EQ(cpu.get_ecx(), 0x00000801);
    EXPECT_EQ(cpu.get_edx(), 0x37860801);
    EXPECT_EQ(cpu.get_esi(), 0x0358CA8D);
    EXPECT_EQ(cpu.get_edi(), 0x00200001);
    EXPECT_EQ(cpu.get_ebp(), 0x0F9041B3);
    EXPECT_EQ(cpu.get_esp(), 0x0000801E);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_ds(), 0x0000A3E0);
    EXPECT_EQ(cpu.get_es(), 0x0000EF6F);
    EXPECT_EQ(cpu.get_fs(), 0x0000393E);
    EXPECT_EQ(cpu.get_gs(), 0x0000F3C7);
    EXPECT_EQ(cpu.get_ss(), 0x00006EF7);
    EXPECT_EQ(cpu.get_eip(), 0x0000557D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0846);

    // Final RAM entries
}

//
// movzx di,word [ds:di]
//
TEST_F(Test386, movzx_di_word_ds_di)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFEE75B63);
    cpu.set_ebx(0xF04D68B3);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0x0C72A964);
    cpu.set_esi(0xF9BA6D8D);
    cpu.set_edi(0xBD2774C7);
    cpu.set_ebp(0x1404CC26);
    cpu.set_esp(0x00003C60);
    cpu.set_cs(0x00009572);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00005B1E);
    cpu.set_fs(0x0000D4DE);
    cpu.set_gs(0x000005AA);
    cpu.set_ss(0x00006EEA);
    cpu.set_eip(0x00004238);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x99958, 0x0F);
    machine.mem_store_byte(0x99959, 0xB7);
    machine.mem_store_byte(0x9995A, 0x3D);
    machine.mem_store_byte(0x9995B, 0xF4);
    machine.mem_store_byte(0x9995C, 0x00);
    machine.mem_store_byte(0x9995D, 0x00);
    machine.mem_store_byte(0x9995E, 0x00);
    machine.mem_store_byte(0x9995F, 0x00);
    machine.mem_store_byte(0x99960, 0x00);
    machine.mem_store_byte(0x99961, 0x00);
    machine.mem_store_byte(0x1074B8, 0x00);
    machine.mem_store_byte(0x1074B7, 0x00);
    machine.mem_store_byte(0x99962, 0x00);
    machine.mem_store_byte(0x99963, 0x00);
    machine.mem_store_byte(0x99964, 0x00);
    machine.mem_store_byte(0x99965, 0x00);
    machine.mem_store_byte(0x99966, 0x00);
    machine.mem_store_byte(0x99967, 0x00);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFEE75B63);
    EXPECT_EQ(cpu.get_ebx(), 0xF04D68B3);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x0C72A964);
    EXPECT_EQ(cpu.get_esi(), 0xF9BA6D8D);
    EXPECT_EQ(cpu.get_edi(), 0xBD270000);
    EXPECT_EQ(cpu.get_ebp(), 0x1404CC26);
    EXPECT_EQ(cpu.get_esp(), 0x00003C60);
    EXPECT_EQ(cpu.get_cs(), 0x00009572);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00005B1E);
    EXPECT_EQ(cpu.get_fs(), 0x0000D4DE);
    EXPECT_EQ(cpu.get_gs(), 0x000005AA);
    EXPECT_EQ(cpu.get_ss(), 0x00006EEA);
    EXPECT_EQ(cpu.get_eip(), 0x0000423C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
}

//
// mul byte [ds:ecx]
//
TEST_F(Test386, mul_byte_ds_ecx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDDBAD90E);
    cpu.set_ebx(0xE3140728);
    cpu.set_ecx(0x000060DE);
    cpu.set_edx(0xC9BE7651);
    cpu.set_esi(0xBFA050B8);
    cpu.set_edi(0xA9D3E5A3);
    cpu.set_ebp(0xFFFBFFFF);
    cpu.set_esp(0x0000DD50);
    cpu.set_cs(0x0000E1FF);
    cpu.set_ds(0x0000D937);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x00000AC7);
    cpu.set_gs(0x000006B9);
    cpu.set_ss(0x0000E042);
    cpu.set_eip(0x00008B48);
    cpu.set_eflags(0xFFFC0017);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEAB38, 0x67);
    machine.mem_store_byte(0xEAB39, 0xF6);
    machine.mem_store_byte(0xEAB3A, 0x21);
    machine.mem_store_byte(0xEAB3B, 0xF4);
    machine.mem_store_byte(0xEAB3C, 0x7C);
    machine.mem_store_byte(0xEAB3D, 0x6E);
    machine.mem_store_byte(0xEAB3E, 0x1A);
    machine.mem_store_byte(0xEAB3F, 0xC0);
    machine.mem_store_byte(0xEAB40, 0x2C);
    machine.mem_store_byte(0xEAB41, 0x71);
    machine.mem_store_byte(0xDF44E, 0xEA);
    machine.mem_store_byte(0xEAB42, 0xA7);
    machine.mem_store_byte(0xEAB43, 0xDA);
    machine.mem_store_byte(0xEAB44, 0x51);
    machine.mem_store_byte(0xEAB45, 0x7C);
    machine.mem_store_byte(0xEAB46, 0x15);
    machine.mem_store_byte(0xEAB47, 0xC7);
    machine.mem_store_byte(0xEAB48, 0xF1);
    machine.mem_store_byte(0xEAB49, 0xC2);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDDBA0CCC);
    EXPECT_EQ(cpu.get_ebx(), 0xE3140728);
    EXPECT_EQ(cpu.get_ecx(), 0x000060DE);
    EXPECT_EQ(cpu.get_edx(), 0xC9BE7651);
    EXPECT_EQ(cpu.get_esi(), 0xBFA050B8);
    EXPECT_EQ(cpu.get_edi(), 0xA9D3E5A3);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFBFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000DD50);
    EXPECT_EQ(cpu.get_cs(), 0x0000E1FF);
    EXPECT_EQ(cpu.get_ds(), 0x0000D937);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x00000AC7);
    EXPECT_EQ(cpu.get_gs(), 0x000006B9);
    EXPECT_EQ(cpu.get_ss(), 0x0000E042);
    EXPECT_EQ(cpu.get_eip(), 0x00008B4C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0813);

    // Final RAM entries
}

//
// movsx esp,byte [ds:esi-5]
//
TEST_F(Test386, movsx_esp_byte_ds_esi_5)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x498454B5);
    cpu.set_ebx(0xFCDEFA96);
    cpu.set_ecx(0xF19C4932);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x0000B9EF);
    cpu.set_edi(0x80000000);
    cpu.set_ebp(0x8527FD13);
    cpu.set_esp(0x00001496);
    cpu.set_cs(0x0000FD0E);
    cpu.set_ds(0x0000FDBD);
    cpu.set_es(0x0000003F);
    cpu.set_fs(0x00004E9A);
    cpu.set_gs(0x0000FE19);
    cpu.set_ss(0x00000048);
    cpu.set_eip(0x0000A3C0);
    cpu.set_eflags(0xFFFC04C3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1074A0, 0x67);
    machine.mem_store_byte(0x1074A1, 0x66);
    machine.mem_store_byte(0x1074A2, 0x0F);
    machine.mem_store_byte(0x1074A3, 0xBE);
    machine.mem_store_byte(0x1074A4, 0x66);
    machine.mem_store_byte(0x1074A5, 0xFB);
    machine.mem_store_byte(0x1074A6, 0xF4);
    machine.mem_store_byte(0x1074A7, 0x0E);
    machine.mem_store_byte(0x1074A8, 0x15);
    machine.mem_store_byte(0x1074A9, 0xA8);
    machine.mem_store_byte(0x1074AA, 0x17);
    machine.mem_store_byte(0x1074AB, 0xDD);
    machine.mem_store_byte(0x1074AC, 0x3A);
    machine.mem_store_byte(0x1074AD, 0xDA);
    machine.mem_store_byte(0x1095BA, 0x44);
    machine.mem_store_byte(0x1074AE, 0x4A);
    machine.mem_store_byte(0x1074AF, 0xA5);
    machine.mem_store_byte(0x1074B0, 0xEB);
    machine.mem_store_byte(0x1074B1, 0x98);
    machine.mem_store_byte(0x1074B2, 0x6D);
    machine.mem_store_byte(0x1074B3, 0x73);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x498454B5);
    EXPECT_EQ(cpu.get_ebx(), 0xFCDEFA96);
    EXPECT_EQ(cpu.get_ecx(), 0xF19C4932);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x0000B9EF);
    EXPECT_EQ(cpu.get_edi(), 0x80000000);
    EXPECT_EQ(cpu.get_ebp(), 0x8527FD13);
    EXPECT_EQ(cpu.get_esp(), 0x00000044);
    EXPECT_EQ(cpu.get_cs(), 0x0000FD0E);
    EXPECT_EQ(cpu.get_ds(), 0x0000FDBD);
    EXPECT_EQ(cpu.get_es(), 0x0000003F);
    EXPECT_EQ(cpu.get_fs(), 0x00004E9A);
    EXPECT_EQ(cpu.get_gs(), 0x0000FE19);
    EXPECT_EQ(cpu.get_ss(), 0x00000048);
    EXPECT_EQ(cpu.get_eip(), 0x0000A3C7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C3);

    // Final RAM entries
}

//
// movzx dx,dl
//
TEST_F(Test386, movzx_dx_dl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1EE93790);
    cpu.set_ebx(0xA9BD5A36);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0x3F79B92E);
    cpu.set_esi(0x08C03CE4);
    cpu.set_edi(0x64EB6550);
    cpu.set_ebp(0xDE50DEC9);
    cpu.set_esp(0x0000B440);
    cpu.set_cs(0x000052E8);
    cpu.set_ds(0x000069E9);
    cpu.set_es(0x0000D169);
    cpu.set_fs(0x00007FFF);
    cpu.set_gs(0x00005C99);
    cpu.set_ss(0x0000FF61);
    cpu.set_eip(0x00002410);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x55290, 0x67);
    machine.mem_store_byte(0x55291, 0x0F);
    machine.mem_store_byte(0x55292, 0xB6);
    machine.mem_store_byte(0x55293, 0xD2);
    machine.mem_store_byte(0x55294, 0xF4);
    machine.mem_store_byte(0x55295, 0x8E);
    machine.mem_store_byte(0x55296, 0x23);
    machine.mem_store_byte(0x55297, 0xBD);
    machine.mem_store_byte(0x55298, 0x77);
    machine.mem_store_byte(0x55299, 0xC0);
    machine.mem_store_byte(0x5529A, 0x52);
    machine.mem_store_byte(0x5529B, 0x31);
    machine.mem_store_byte(0x5529C, 0x6B);
    machine.mem_store_byte(0x5529D, 0x74);
    machine.mem_store_byte(0x5529E, 0x93);
    machine.mem_store_byte(0x5529F, 0xE4);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1EE93790);
    EXPECT_EQ(cpu.get_ebx(), 0xA9BD5A36);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x3F79002E);
    EXPECT_EQ(cpu.get_esi(), 0x08C03CE4);
    EXPECT_EQ(cpu.get_edi(), 0x64EB6550);
    EXPECT_EQ(cpu.get_ebp(), 0xDE50DEC9);
    EXPECT_EQ(cpu.get_esp(), 0x0000B440);
    EXPECT_EQ(cpu.get_cs(), 0x000052E8);
    EXPECT_EQ(cpu.get_ds(), 0x000069E9);
    EXPECT_EQ(cpu.get_es(), 0x0000D169);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x00005C99);
    EXPECT_EQ(cpu.get_ss(), 0x0000FF61);
    EXPECT_EQ(cpu.get_eip(), 0x00002415);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
}

//
// mul byte [ss:bp+si]
//
TEST_F(Test386, mul_byte_ss_bp_si)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDDBAD90E);
    cpu.set_ebx(0xE3140728);
    cpu.set_ecx(0x2D1A60DE);
    cpu.set_edx(0xC9BE7651);
    cpu.set_esi(0xBFA050B8);
    cpu.set_edi(0xA9D3E5A3);
    cpu.set_ebp(0xFFFBFFFF);
    cpu.set_esp(0x0000DD50);
    cpu.set_cs(0x0000E1FF);
    cpu.set_ds(0x0000D937);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x00000AC7);
    cpu.set_gs(0x000006B9);
    cpu.set_ss(0x0000E042);
    cpu.set_eip(0x00008B48);
    cpu.set_eflags(0xFFFC0017);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEAB38, 0xF6);
    machine.mem_store_byte(0xEAB39, 0x22);
    machine.mem_store_byte(0xEAB3A, 0xF4);
    machine.mem_store_byte(0xEAB3B, 0x6F);
    machine.mem_store_byte(0xEAB3C, 0x7C);
    machine.mem_store_byte(0xEAB3D, 0x6E);
    machine.mem_store_byte(0xEAB3E, 0x1A);
    machine.mem_store_byte(0xEAB3F, 0xC0);
    machine.mem_store_byte(0xEAB40, 0x2C);
    machine.mem_store_byte(0xEAB41, 0x71);
    machine.mem_store_byte(0xE54D7, 0x37);
    machine.mem_store_byte(0xEAB42, 0xA7);
    machine.mem_store_byte(0xEAB43, 0xDA);
    machine.mem_store_byte(0xEAB44, 0x51);
    machine.mem_store_byte(0xEAB45, 0x7C);
    machine.mem_store_byte(0xEAB46, 0x15);
    machine.mem_store_byte(0xEAB47, 0xC7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDDBA0302);
    EXPECT_EQ(cpu.get_ebx(), 0xE3140728);
    EXPECT_EQ(cpu.get_ecx(), 0x2D1A60DE);
    EXPECT_EQ(cpu.get_edx(), 0xC9BE7651);
    EXPECT_EQ(cpu.get_esi(), 0xBFA050B8);
    EXPECT_EQ(cpu.get_edi(), 0xA9D3E5A3);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFBFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000DD50);
    EXPECT_EQ(cpu.get_cs(), 0x0000E1FF);
    EXPECT_EQ(cpu.get_ds(), 0x0000D937);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x00000AC7);
    EXPECT_EQ(cpu.get_gs(), 0x000006B9);
    EXPECT_EQ(cpu.get_ss(), 0x0000E042);
    EXPECT_EQ(cpu.get_eip(), 0x00008B4B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0817);

    // Final RAM entries
}

//
// mul dword [fs:esi-19h]
//
TEST_F(Test386, mul_dword_fs_esi_19h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2B879659);
    cpu.set_ebx(0x305339E8);
    cpu.set_ecx(0xE713D7BC);
    cpu.set_edx(0xB2368D6F);
    cpu.set_esi(0x00005F78);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x27605143);
    cpu.set_esp(0x000061F0);
    cpu.set_cs(0x00005D39);
    cpu.set_ds(0x00006C43);
    cpu.set_es(0x0000E6BE);
    cpu.set_fs(0x0000ACC4);
    cpu.set_gs(0x00003312);
    cpu.set_ss(0x0000386D);
    cpu.set_eip(0x00004310);
    cpu.set_eflags(0xFFFC0CD7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x616A0, 0x64);
    machine.mem_store_byte(0x616A1, 0x67);
    machine.mem_store_byte(0x616A2, 0x66);
    machine.mem_store_byte(0x616A3, 0xF7);
    machine.mem_store_byte(0x616A4, 0x66);
    machine.mem_store_byte(0x616A5, 0xE7);
    machine.mem_store_byte(0x616A6, 0xF4);
    machine.mem_store_byte(0x616A7, 0xAE);
    machine.mem_store_byte(0x616A8, 0x12);
    machine.mem_store_byte(0x616A9, 0xBE);
    machine.mem_store_byte(0x616AA, 0xBA);
    machine.mem_store_byte(0x616AB, 0x4B);
    machine.mem_store_byte(0x616AC, 0x60);
    machine.mem_store_byte(0x616AD, 0xAC);
    machine.mem_store_byte(0xB2BA0, 0xF6);
    machine.mem_store_byte(0xB2BA1, 0xA5);
    machine.mem_store_byte(0xB2BA2, 0xC8);
    machine.mem_store_byte(0xB2B9F, 0xB2);
    machine.mem_store_byte(0x616AE, 0xBA);
    machine.mem_store_byte(0x616AF, 0x86);
    machine.mem_store_byte(0x616B0, 0xE0);
    machine.mem_store_byte(0x616B1, 0x36);
    machine.mem_store_byte(0x616B2, 0xDD);
    machine.mem_store_byte(0x616B3, 0x45);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFE1D0FE2);
    EXPECT_EQ(cpu.get_ebx(), 0x305339E8);
    EXPECT_EQ(cpu.get_ecx(), 0xE713D7BC);
    EXPECT_EQ(cpu.get_edx(), 0x221E25CB);
    EXPECT_EQ(cpu.get_esi(), 0x00005F78);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x27605143);
    EXPECT_EQ(cpu.get_esp(), 0x000061F0);
    EXPECT_EQ(cpu.get_cs(), 0x00005D39);
    EXPECT_EQ(cpu.get_ds(), 0x00006C43);
    EXPECT_EQ(cpu.get_es(), 0x0000E6BE);
    EXPECT_EQ(cpu.get_fs(), 0x0000ACC4);
    EXPECT_EQ(cpu.get_gs(), 0x00003312);
    EXPECT_EQ(cpu.get_ss(), 0x0000386D);
    EXPECT_EQ(cpu.get_eip(), 0x00004317);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    // AF undefined for MUL per Intel; reference may preserve it
    EXPECT_FLAGS(0xFFFC0C03);

    // Final RAM entries
}

//
// mul word [fs:esi-19h]
//
TEST_F(Test386, mul_word_fs_esi_19h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2B879659);
    cpu.set_ebx(0x305339E8);
    cpu.set_ecx(0xE713D7BC);
    cpu.set_edx(0xB2368D6F);
    cpu.set_esi(0x00005F78);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x27605143);
    cpu.set_esp(0x000061F0);
    cpu.set_cs(0x00005D39);
    cpu.set_ds(0x00006C43);
    cpu.set_es(0x0000E6BE);
    cpu.set_fs(0x0000ACC4);
    cpu.set_gs(0x00003312);
    cpu.set_ss(0x0000386D);
    cpu.set_eip(0x00004310);
    cpu.set_eflags(0xFFFC0CD7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x616A0, 0x64);
    machine.mem_store_byte(0x616A1, 0x67);
    machine.mem_store_byte(0x616A2, 0xF7);
    machine.mem_store_byte(0x616A3, 0x66);
    machine.mem_store_byte(0x616A4, 0xE7);
    machine.mem_store_byte(0x616A5, 0xF4);
    machine.mem_store_byte(0x616A6, 0x52);
    machine.mem_store_byte(0x616A7, 0xAE);
    machine.mem_store_byte(0x616A8, 0x12);
    machine.mem_store_byte(0x616A9, 0xBE);
    machine.mem_store_byte(0x616AA, 0xBA);
    machine.mem_store_byte(0x616AB, 0x4B);
    machine.mem_store_byte(0xB2BA0, 0xF6);
    machine.mem_store_byte(0xB2B9F, 0xB2);
    machine.mem_store_byte(0x616AC, 0x60);
    machine.mem_store_byte(0x616AD, 0xAC);
    machine.mem_store_byte(0x616AE, 0xBA);
    machine.mem_store_byte(0x616AF, 0x86);
    machine.mem_store_byte(0x616B0, 0xE0);
    machine.mem_store_byte(0x616B1, 0x36);
    machine.mem_store_byte(0x616B2, 0xDD);
    machine.mem_store_byte(0x616B3, 0x45);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x2B870FE2);
    EXPECT_EQ(cpu.get_ebx(), 0x305339E8);
    EXPECT_EQ(cpu.get_ecx(), 0xE713D7BC);
    EXPECT_EQ(cpu.get_edx(), 0xB23690E2);
    EXPECT_EQ(cpu.get_esi(), 0x00005F78);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x27605143);
    EXPECT_EQ(cpu.get_esp(), 0x000061F0);
    EXPECT_EQ(cpu.get_cs(), 0x00005D39);
    EXPECT_EQ(cpu.get_ds(), 0x00006C43);
    EXPECT_EQ(cpu.get_es(), 0x0000E6BE);
    EXPECT_EQ(cpu.get_fs(), 0x0000ACC4);
    EXPECT_EQ(cpu.get_gs(), 0x00003312);
    EXPECT_EQ(cpu.get_ss(), 0x0000386D);
    EXPECT_EQ(cpu.get_eip(), 0x00004316);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C13);

    // Final RAM entries
}

//
// mul word [ss:bp+di+24h]
//
TEST_F(Test386, mul_word_ss_bp_di_24h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2B879659);
    cpu.set_ebx(0x305339E8);
    cpu.set_ecx(0xE713D7BC);
    cpu.set_edx(0xB2368D6F);
    cpu.set_esi(0x4B365F78);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x27605143);
    cpu.set_esp(0x000061F0);
    cpu.set_cs(0x00005D39);
    cpu.set_ds(0x00006C43);
    cpu.set_es(0x0000E6BE);
    cpu.set_fs(0x0000ACC4);
    cpu.set_gs(0x00003312);
    cpu.set_ss(0x0000386D);
    cpu.set_eip(0x00004310);
    cpu.set_eflags(0xFFFC0CD7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x616A0, 0xF7);
    machine.mem_store_byte(0x616A1, 0x63);
    machine.mem_store_byte(0x616A2, 0x24);
    machine.mem_store_byte(0x616A3, 0xF4);
    machine.mem_store_byte(0x616A4, 0xF7);
    machine.mem_store_byte(0x616A5, 0x3A);
    machine.mem_store_byte(0x616A6, 0x52);
    machine.mem_store_byte(0x616A7, 0xAE);
    machine.mem_store_byte(0x616A8, 0x12);
    machine.mem_store_byte(0x616A9, 0xBE);
    machine.mem_store_byte(0x3D836, 0x07);
    machine.mem_store_byte(0x3D837, 0x0E);
    machine.mem_store_byte(0x616AA, 0xBA);
    machine.mem_store_byte(0x616AB, 0x4B);
    machine.mem_store_byte(0x616AC, 0x60);
    machine.mem_store_byte(0x616AD, 0xAC);
    machine.mem_store_byte(0x616AE, 0xBA);
    machine.mem_store_byte(0x616AF, 0x86);
    machine.mem_store_byte(0x616B0, 0xE0);
    machine.mem_store_byte(0x616B1, 0x36);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x2B87FA6F);
    EXPECT_EQ(cpu.get_ebx(), 0x305339E8);
    EXPECT_EQ(cpu.get_ecx(), 0xE713D7BC);
    EXPECT_EQ(cpu.get_edx(), 0xB236083C);
    EXPECT_EQ(cpu.get_esi(), 0x4B365F78);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x27605143);
    EXPECT_EQ(cpu.get_esp(), 0x000061F0);
    EXPECT_EQ(cpu.get_cs(), 0x00005D39);
    EXPECT_EQ(cpu.get_ds(), 0x00006C43);
    EXPECT_EQ(cpu.get_es(), 0x0000E6BE);
    EXPECT_EQ(cpu.get_fs(), 0x0000ACC4);
    EXPECT_EQ(cpu.get_gs(), 0x00003312);
    EXPECT_EQ(cpu.get_ss(), 0x0000386D);
    EXPECT_EQ(cpu.get_eip(), 0x00004314);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C07);

    // Final RAM entries
}
