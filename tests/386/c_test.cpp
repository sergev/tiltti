#include "test386.h"

//
// call 3C2Bh:9312h
//
TEST_F(Test386, call_3C2Bh_9312h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE970DC70);
    cpu.set_ebx(0x4EA66F40);
    cpu.set_ecx(0xEEB592CB);
    cpu.set_edx(0x48B0FD0E);
    cpu.set_esi(0x19388EE2);
    cpu.set_edi(0xC02D4BAA);
    cpu.set_ebp(0x00020001);
    cpu.set_esp(0x00000800);
    cpu.set_cs(0x0000F35E);
    cpu.set_ds(0x00007FBD);
    cpu.set_es(0x00001E0E);
    cpu.set_fs(0x000000EF);
    cpu.set_gs(0x0000679F);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x0000E9B8);
    cpu.set_eflags(0xFFFC0882);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x101F98, 0x9A);
    machine.mem_store_byte(0x101F99, 0x12);
    machine.mem_store_byte(0x101F9A, 0x93);
    machine.mem_store_byte(0x101F9B, 0x2B);
    machine.mem_store_byte(0x101F9C, 0x3C);
    machine.mem_store_byte(0x101F9D, 0xF4);
    machine.mem_store_byte(0x101F9E, 0xF2);
    machine.mem_store_byte(0x101F9F, 0xE0);
    machine.mem_store_byte(0x101FA0, 0x23);
    machine.mem_store_byte(0x101FA1, 0xCA);
    machine.mem_store_byte(0x101FA2, 0x86);
    machine.mem_store_byte(0x101FA3, 0x99);
    machine.mem_store_byte(0x455C2, 0xF4);
    machine.mem_store_byte(0x455C3, 0xF4);
    machine.mem_store_byte(0x455C4, 0x7F);
    machine.mem_store_byte(0x455C5, 0x44);
    machine.mem_store_byte(0x455C6, 0x03);
    machine.mem_store_byte(0x455C7, 0xBF);
    machine.mem_store_byte(0x455C8, 0x7F);
    machine.mem_store_byte(0x455C9, 0xF4);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE970DC70);
    EXPECT_EQ(cpu.get_ebx(), 0x4EA66F40);
    EXPECT_EQ(cpu.get_ecx(), 0xEEB592CB);
    EXPECT_EQ(cpu.get_edx(), 0x48B0FD0E);
    EXPECT_EQ(cpu.get_esi(), 0x19388EE2);
    EXPECT_EQ(cpu.get_edi(), 0xC02D4BAA);
    EXPECT_EQ(cpu.get_ebp(), 0x00020001);
    EXPECT_EQ(cpu.get_esp(), 0x000007FC);
    EXPECT_EQ(cpu.get_cs(), 0x00003C2B);
    EXPECT_EQ(cpu.get_ds(), 0x00007FBD);
    EXPECT_EQ(cpu.get_es(), 0x00001E0E);
    EXPECT_EQ(cpu.get_fs(), 0x000000EF);
    EXPECT_EQ(cpu.get_gs(), 0x0000679F);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x00009313);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0882);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1007EE), 0x5E);
    EXPECT_EQ(memory.load8(0x1007EF), 0xF3);
    EXPECT_EQ(memory.load8(0x1007EC), 0xBD);
    EXPECT_EQ(memory.load8(0x1007ED), 0xE9);
}

//
// call dword 00003321h
//
TEST_F(Test386, call_dword_00003321h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007FFF);
    cpu.set_ebx(0x0F1D0BE2);
    cpu.set_ecx(0x0868875A);
    cpu.set_edx(0xA35A1C5A);
    cpu.set_esi(0x546F8B08);
    cpu.set_edi(0x5DAE4081);
    cpu.set_ebp(0x0F67D6C9);
    cpu.set_esp(0x00000FD0);
    cpu.set_cs(0x00001DA8);
    cpu.set_ds(0x00007FFF);
    cpu.set_es(0x00005249);
    cpu.set_fs(0x00000001);
    cpu.set_gs(0x000009D9);
    cpu.set_ss(0x000008B6);
    cpu.set_eip(0x00008678);
    cpu.set_eflags(0xFFFC0883);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x260F8, 0x66);
    machine.mem_store_byte(0x260F9, 0xE8);
    machine.mem_store_byte(0x260FA, 0xA3);
    machine.mem_store_byte(0x260FB, 0xAC);
    machine.mem_store_byte(0x260FC, 0xFF);
    machine.mem_store_byte(0x260FD, 0xFF);
    machine.mem_store_byte(0x260FE, 0xF4);
    machine.mem_store_byte(0x260FF, 0x8A);
    machine.mem_store_byte(0x26100, 0x03);
    machine.mem_store_byte(0x26101, 0x3A);
    machine.mem_store_byte(0x26102, 0x33);
    machine.mem_store_byte(0x26103, 0xB3);
    machine.mem_store_byte(0x20DA0, 0x14);
    machine.mem_store_byte(0x20DA1, 0xF4);
    machine.mem_store_byte(0x20DA2, 0x0D);
    machine.mem_store_byte(0x20DA3, 0x77);
    machine.mem_store_byte(0x20DA4, 0xE1);
    machine.mem_store_byte(0x20DA5, 0xB8);
    machine.mem_store_byte(0x20DA6, 0xB6);
    machine.mem_store_byte(0x20DA7, 0xD0);
    machine.mem_store_byte(0x20DA8, 0x85);
    machine.mem_store_byte(0x20DA9, 0x9B);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebx(), 0x0F1D0BE2);
    EXPECT_EQ(cpu.get_ecx(), 0x0868875A);
    EXPECT_EQ(cpu.get_edx(), 0xA35A1C5A);
    EXPECT_EQ(cpu.get_esi(), 0x546F8B08);
    EXPECT_EQ(cpu.get_edi(), 0x5DAE4081);
    EXPECT_EQ(cpu.get_ebp(), 0x0F67D6C9);
    EXPECT_EQ(cpu.get_esp(), 0x00000FCC);
    EXPECT_EQ(cpu.get_cs(), 0x00001DA8);
    EXPECT_EQ(cpu.get_ds(), 0x00007FFF);
    EXPECT_EQ(cpu.get_es(), 0x00005249);
    EXPECT_EQ(cpu.get_fs(), 0x00000001);
    EXPECT_EQ(cpu.get_gs(), 0x000009D9);
    EXPECT_EQ(cpu.get_ss(), 0x000008B6);
    EXPECT_EQ(cpu.get_eip(), 0x00003322);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0883);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x09B2C), 0x7E);
    EXPECT_EQ(memory.load8(0x09B2D), 0x86);
    EXPECT_EQ(memory.load8(0x09B2E), 0x00);
    EXPECT_EQ(memory.load8(0x09B2F), 0x00);
}

//
// cbw
//
TEST_F(Test386, cbw)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x57E57906);
    cpu.set_ebx(0xCF5F17C8);
    cpu.set_ecx(0xFFFFFFDF);
    cpu.set_edx(0x14C27ACD);
    cpu.set_esi(0xA86C3187);
    cpu.set_edi(0x77AB9DD9);
    cpu.set_ebp(0x817E34C7);
    cpu.set_esp(0x000009F7);
    cpu.set_cs(0x0000FFF3);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x00009497);
    cpu.set_fs(0x0000008F);
    cpu.set_gs(0x000042F1);
    cpu.set_ss(0x0000FB65);
    cpu.set_eip(0x00008050);
    cpu.set_eflags(0xFFFC0CC3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x107F80, 0x98);
    machine.mem_store_byte(0x107F81, 0xF4);
    machine.mem_store_byte(0x107F82, 0xFF);
    machine.mem_store_byte(0x107F83, 0xFF);
    machine.mem_store_byte(0x107F84, 0xFF);
    machine.mem_store_byte(0x107F85, 0xFF);
    machine.mem_store_byte(0x107F86, 0xFF);
    machine.mem_store_byte(0x107F87, 0xFF);
    machine.mem_store_byte(0x107F88, 0xFF);
    machine.mem_store_byte(0x107F89, 0xFF);
    machine.mem_store_byte(0x107F8A, 0xFF);
    machine.mem_store_byte(0x107F8B, 0xFF);
    machine.mem_store_byte(0x107F8C, 0xFF);
    machine.mem_store_byte(0x107F8D, 0xFF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x57E50006);
    EXPECT_EQ(cpu.get_ebx(), 0xCF5F17C8);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFDF);
    EXPECT_EQ(cpu.get_edx(), 0x14C27ACD);
    EXPECT_EQ(cpu.get_esi(), 0xA86C3187);
    EXPECT_EQ(cpu.get_edi(), 0x77AB9DD9);
    EXPECT_EQ(cpu.get_ebp(), 0x817E34C7);
    EXPECT_EQ(cpu.get_esp(), 0x000009F7);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFF3);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x00009497);
    EXPECT_EQ(cpu.get_fs(), 0x0000008F);
    EXPECT_EQ(cpu.get_gs(), 0x000042F1);
    EXPECT_EQ(cpu.get_ss(), 0x0000FB65);
    EXPECT_EQ(cpu.get_eip(), 0x00008052);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CC3);

    // Final RAM entries
}

//
// cwd
//
TEST_F(Test386, cwd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x00000002);
    cpu.set_ecx(0x669E3C9B);
    cpu.set_edx(0xDBE62780);
    cpu.set_esi(0x10000000);
    cpu.set_edi(0x24881FF0);
    cpu.set_ebp(0xECD4A866);
    cpu.set_esp(0x00006E62);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000FF48);
    cpu.set_es(0x000058FA);
    cpu.set_fs(0x0000CE0B);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x0000C65E);
    cpu.set_eip(0x00001460);
    cpu.set_eflags(0xFFFC0807);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x01460, 0x99);
    machine.mem_store_byte(0x01461, 0xF4);
    machine.mem_store_byte(0x01462, 0x47);
    machine.mem_store_byte(0x01463, 0xC2);
    machine.mem_store_byte(0x01464, 0xDD);
    machine.mem_store_byte(0x01465, 0x2D);
    machine.mem_store_byte(0x01466, 0xBB);
    machine.mem_store_byte(0x01467, 0x85);
    machine.mem_store_byte(0x01468, 0xFC);
    machine.mem_store_byte(0x01469, 0xED);
    machine.mem_store_byte(0x0146A, 0xF1);
    machine.mem_store_byte(0x0146B, 0x68);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0x00000002);
    EXPECT_EQ(cpu.get_ecx(), 0x669E3C9B);
    EXPECT_EQ(cpu.get_edx(), 0xDBE60000);
    EXPECT_EQ(cpu.get_esi(), 0x10000000);
    EXPECT_EQ(cpu.get_edi(), 0x24881FF0);
    EXPECT_EQ(cpu.get_ebp(), 0xECD4A866);
    EXPECT_EQ(cpu.get_esp(), 0x00006E62);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000FF48);
    EXPECT_EQ(cpu.get_es(), 0x000058FA);
    EXPECT_EQ(cpu.get_fs(), 0x0000CE0B);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x0000C65E);
    EXPECT_EQ(cpu.get_eip(), 0x00001462);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0807);

    // Final RAM entries
}

//
// cmp dword [ds:bx-298h],58h
//
TEST_F(Test386, cmp_dword_ds_bx_298h_58h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000400);
    cpu.set_ebx(0x000000F1);
    cpu.set_ecx(0x0FB4BF66);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xF8436EF7);
    cpu.set_edi(0x00007FFF);
    cpu.set_ebp(0x6ED895A1);
    cpu.set_esp(0x0000FBFE);
    cpu.set_cs(0x00001357);
    cpu.set_ds(0x00000201);
    cpu.set_es(0x000000CF);
    cpu.set_fs(0x0000D5B3);
    cpu.set_gs(0x0000B8C9);
    cpu.set_ss(0x000067DE);
    cpu.set_eip(0x0000BB20);
    cpu.set_eflags(0xFFFC0046);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1F090, 0x66);
    machine.mem_store_byte(0x1F091, 0x83);
    machine.mem_store_byte(0x1F092, 0xBF);
    machine.mem_store_byte(0x1F093, 0x68);
    machine.mem_store_byte(0x1F094, 0xFD);
    machine.mem_store_byte(0x1F095, 0x58);
    machine.mem_store_byte(0x1F096, 0xF4);
    machine.mem_store_byte(0x1F097, 0xC4);
    machine.mem_store_byte(0x1F098, 0xE1);
    machine.mem_store_byte(0x1F099, 0xE2);
    machine.mem_store_byte(0x1F09A, 0xFB);
    machine.mem_store_byte(0x1F09B, 0xD5);
    machine.mem_store_byte(0x1F09C, 0xFF);
    machine.mem_store_byte(0x1F09D, 0x39);
    machine.mem_store_byte(0x11E6C, 0x58);
    machine.mem_store_byte(0x11E69, 0xEC);
    machine.mem_store_byte(0x11E6A, 0x91);
    machine.mem_store_byte(0x11E6B, 0x31);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000400);
    EXPECT_EQ(cpu.get_ebx(), 0x000000F1);
    EXPECT_EQ(cpu.get_ecx(), 0x0FB4BF66);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xF8436EF7);
    EXPECT_EQ(cpu.get_edi(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebp(), 0x6ED895A1);
    EXPECT_EQ(cpu.get_esp(), 0x0000FBFE);
    EXPECT_EQ(cpu.get_cs(), 0x00001357);
    EXPECT_EQ(cpu.get_ds(), 0x00000201);
    EXPECT_EQ(cpu.get_es(), 0x000000CF);
    EXPECT_EQ(cpu.get_fs(), 0x0000D5B3);
    EXPECT_EQ(cpu.get_gs(), 0x0000B8C9);
    EXPECT_EQ(cpu.get_ss(), 0x000067DE);
    EXPECT_EQ(cpu.get_eip(), 0x0000BB27);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0002);

    // Final RAM entries
}

//
// cmp eax,D814CA37h
//
TEST_F(Test386, cmp_eax_D814CA37h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0233A3AA);
    cpu.set_ebx(0x00000000);
    cpu.set_ecx(0xECD3D74E);
    cpu.set_edx(0x0F0F0F0F);
    cpu.set_esi(0x83F3D83A);
    cpu.set_edi(0x0000FFFF);
    cpu.set_ebp(0x71F6FDFC);
    cpu.set_esp(0x00000040);
    cpu.set_cs(0x0000BD3C);
    cpu.set_ds(0x000098EB);
    cpu.set_es(0x0000C437);
    cpu.set_fs(0x0000E873);
    cpu.set_gs(0x000017BF);
    cpu.set_ss(0x00001824);
    cpu.set_eip(0x00002A60);
    cpu.set_eflags(0xFFFC0412);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBFE20, 0x66);
    machine.mem_store_byte(0xBFE21, 0x3D);
    machine.mem_store_byte(0xBFE22, 0x37);
    machine.mem_store_byte(0xBFE23, 0xCA);
    machine.mem_store_byte(0xBFE24, 0x14);
    machine.mem_store_byte(0xBFE25, 0xD8);
    machine.mem_store_byte(0xBFE26, 0xF4);
    machine.mem_store_byte(0xBFE27, 0x4C);
    machine.mem_store_byte(0xBFE28, 0x8F);
    machine.mem_store_byte(0xBFE29, 0xFA);
    machine.mem_store_byte(0xBFE2A, 0x33);
    machine.mem_store_byte(0xBFE2B, 0x5D);
    machine.mem_store_byte(0xBFE2C, 0x15);
    machine.mem_store_byte(0xBFE2D, 0xD1);
    machine.mem_store_byte(0xBFE2E, 0x29);
    machine.mem_store_byte(0xBFE2F, 0xC7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0233A3AA);
    EXPECT_EQ(cpu.get_ebx(), 0x00000000);
    EXPECT_EQ(cpu.get_ecx(), 0xECD3D74E);
    EXPECT_EQ(cpu.get_edx(), 0x0F0F0F0F);
    EXPECT_EQ(cpu.get_esi(), 0x83F3D83A);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x71F6FDFC);
    EXPECT_EQ(cpu.get_esp(), 0x00000040);
    EXPECT_EQ(cpu.get_cs(), 0x0000BD3C);
    EXPECT_EQ(cpu.get_ds(), 0x000098EB);
    EXPECT_EQ(cpu.get_es(), 0x0000C437);
    EXPECT_EQ(cpu.get_fs(), 0x0000E873);
    EXPECT_EQ(cpu.get_gs(), 0x000017BF);
    EXPECT_EQ(cpu.get_ss(), 0x00001824);
    EXPECT_EQ(cpu.get_eip(), 0x00002A67);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0403);

    // Final RAM entries
}

//
// cmp [ss:bp+si+6142h],eax
//
TEST_F(Test386, cmp_ss_bp_si_6142h_eax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1AF8D8E9);
    cpu.set_ebx(0xC419872C);
    cpu.set_ecx(0x8056D3B8);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x7DCC9B40);
    cpu.set_edi(0xAD10C6FD);
    cpu.set_ebp(0x4D75832C);
    cpu.set_esp(0x0000F0F0);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000D4DA);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00009246);
    cpu.set_gs(0x00008043);
    cpu.set_ss(0x0000002A);
    cpu.set_eip(0x00004BA0);
    cpu.set_eflags(0xFFFC0447);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x04BA0, 0x66);
    machine.mem_store_byte(0x04BA1, 0x39);
    machine.mem_store_byte(0x04BA2, 0x82);
    machine.mem_store_byte(0x04BA3, 0x42);
    machine.mem_store_byte(0x04BA4, 0x61);
    machine.mem_store_byte(0x04BA5, 0xF4);
    machine.mem_store_byte(0x04BA6, 0x63);
    machine.mem_store_byte(0x04BA7, 0xD4);
    machine.mem_store_byte(0x04BA8, 0xC7);
    machine.mem_store_byte(0x04BA9, 0xE6);
    machine.mem_store_byte(0x04BAA, 0x29);
    machine.mem_store_byte(0x04BAB, 0x79);
    machine.mem_store_byte(0x08250, 0x48);
    machine.mem_store_byte(0x08251, 0x57);
    machine.mem_store_byte(0x0824E, 0x2F);
    machine.mem_store_byte(0x0824F, 0x2E);
    machine.mem_store_byte(0x04BAC, 0xF6);
    machine.mem_store_byte(0x04BAD, 0xDB);
    machine.mem_store_byte(0x04BAE, 0x6B);
    machine.mem_store_byte(0x04BAF, 0xFE);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1AF8D8E9);
    EXPECT_EQ(cpu.get_ebx(), 0xC419872C);
    EXPECT_EQ(cpu.get_ecx(), 0x8056D3B8);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x7DCC9B40);
    EXPECT_EQ(cpu.get_edi(), 0xAD10C6FD);
    EXPECT_EQ(cpu.get_ebp(), 0x4D75832C);
    EXPECT_EQ(cpu.get_esp(), 0x0000F0F0);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000D4DA);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00009246);
    EXPECT_EQ(cpu.get_gs(), 0x00008043);
    EXPECT_EQ(cpu.get_ss(), 0x0000002A);
    EXPECT_EQ(cpu.get_eip(), 0x00004BA6);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0402);

    // Final RAM entries
}

//
// cwde
//
TEST_F(Test386, cwde)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x57E57906);
    cpu.set_ebx(0xCF5F17C8);
    cpu.set_ecx(0xFFFFFFDF);
    cpu.set_edx(0x14C27ACD);
    cpu.set_esi(0xA86C3187);
    cpu.set_edi(0x77AB9DD9);
    cpu.set_ebp(0x817E34C7);
    cpu.set_esp(0x000009F7);
    cpu.set_cs(0x0000FFF3);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x00009497);
    cpu.set_fs(0x0000008F);
    cpu.set_gs(0x000042F1);
    cpu.set_ss(0x0000FB65);
    cpu.set_eip(0x00008050);
    cpu.set_eflags(0xFFFC0CC3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x107F80, 0x66);
    machine.mem_store_byte(0x107F81, 0x98);
    machine.mem_store_byte(0x107F82, 0xF4);
    machine.mem_store_byte(0x107F83, 0xFF);
    machine.mem_store_byte(0x107F84, 0xFF);
    machine.mem_store_byte(0x107F85, 0xFF);
    machine.mem_store_byte(0x107F86, 0xFF);
    machine.mem_store_byte(0x107F87, 0xFF);
    machine.mem_store_byte(0x107F88, 0xFF);
    machine.mem_store_byte(0x107F89, 0xFF);
    machine.mem_store_byte(0x107F8A, 0xFF);
    machine.mem_store_byte(0x107F8B, 0xFF);
    machine.mem_store_byte(0x107F8C, 0xFF);
    machine.mem_store_byte(0x107F8D, 0xFF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007906);
    EXPECT_EQ(cpu.get_ebx(), 0xCF5F17C8);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFDF);
    EXPECT_EQ(cpu.get_edx(), 0x14C27ACD);
    EXPECT_EQ(cpu.get_esi(), 0xA86C3187);
    EXPECT_EQ(cpu.get_edi(), 0x77AB9DD9);
    EXPECT_EQ(cpu.get_ebp(), 0x817E34C7);
    EXPECT_EQ(cpu.get_esp(), 0x000009F7);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFF3);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x00009497);
    EXPECT_EQ(cpu.get_fs(), 0x0000008F);
    EXPECT_EQ(cpu.get_gs(), 0x000042F1);
    EXPECT_EQ(cpu.get_ss(), 0x0000FB65);
    EXPECT_EQ(cpu.get_eip(), 0x00008053);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CC3);

    // Final RAM entries
}

//
// call dword F68Ah:00009312h
//
TEST_F(Test386, call_dword_F68Ah_00009312h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE970DC70);
    cpu.set_ebx(0x4EA66F40);
    cpu.set_ecx(0xEEB592CB);
    cpu.set_edx(0x48B0FD0E);
    cpu.set_esi(0x19388EE2);
    cpu.set_edi(0xC02D4BAA);
    cpu.set_ebp(0x00020001);
    cpu.set_esp(0x00000800);
    cpu.set_cs(0x0000F35E);
    cpu.set_ds(0x00007FBD);
    cpu.set_es(0x00001E0E);
    cpu.set_fs(0x000000EF);
    cpu.set_gs(0x0000679F);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x0000E9B8);
    cpu.set_eflags(0xFFFC0882);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x101F98, 0x66);
    machine.mem_store_byte(0x101F99, 0x9A);
    machine.mem_store_byte(0x101F9A, 0x12);
    machine.mem_store_byte(0x101F9B, 0x93);
    machine.mem_store_byte(0x101F9C, 0x00);
    machine.mem_store_byte(0x101F9D, 0x00);
    machine.mem_store_byte(0x101F9E, 0x8A);
    machine.mem_store_byte(0x101F9F, 0xF6);
    machine.mem_store_byte(0x101FA0, 0xF4);
    machine.mem_store_byte(0x101FA1, 0xCA);
    machine.mem_store_byte(0x101FA2, 0x86);
    machine.mem_store_byte(0x101FA3, 0x99);
    machine.mem_store_byte(0xFFBB2, 0xF4);
    machine.mem_store_byte(0xFFBB3, 0xF4);
    machine.mem_store_byte(0xFFBB4, 0x9B);
    machine.mem_store_byte(0xFFBB5, 0xCD);
    machine.mem_store_byte(0xFFBB6, 0xB8);
    machine.mem_store_byte(0xFFBB7, 0xD8);
    machine.mem_store_byte(0xFFBB8, 0xEA);
    machine.mem_store_byte(0xFFBB9, 0xFD);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE970DC70);
    EXPECT_EQ(cpu.get_ebx(), 0x4EA66F40);
    EXPECT_EQ(cpu.get_ecx(), 0xEEB592CB);
    EXPECT_EQ(cpu.get_edx(), 0x48B0FD0E);
    EXPECT_EQ(cpu.get_esi(), 0x19388EE2);
    EXPECT_EQ(cpu.get_edi(), 0xC02D4BAA);
    EXPECT_EQ(cpu.get_ebp(), 0x00020001);
    EXPECT_EQ(cpu.get_esp(), 0x000007F8);
    EXPECT_EQ(cpu.get_cs(), 0x0000F68A);
    EXPECT_EQ(cpu.get_ds(), 0x00007FBD);
    EXPECT_EQ(cpu.get_es(), 0x00001E0E);
    EXPECT_EQ(cpu.get_fs(), 0x000000EF);
    EXPECT_EQ(cpu.get_gs(), 0x0000679F);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x00009313);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0882);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1007EC), 0x5E);
    EXPECT_EQ(memory.load8(0x1007ED), 0xF3);
    EXPECT_EQ(memory.load8(0x1007EE), 0x00);
    EXPECT_EQ(memory.load8(0x1007EF), 0x00);
    EXPECT_EQ(memory.load8(0x1007E8), 0xC0);
    EXPECT_EQ(memory.load8(0x1007E9), 0xE9);
    EXPECT_EQ(memory.load8(0x1007EA), 0x00);
    EXPECT_EQ(memory.load8(0x1007EB), 0x00);
}

//
// cmp [ds:bx+di],di
//
TEST_F(Test386, cmp_ds_bx_di_di)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x066220AD);
    cpu.set_ebx(0x0001FFFF);
    cpu.set_ecx(0xA10C97E1);
    cpu.set_edx(0xAC645D04);
    cpu.set_esi(0xFFFC0000);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x21D78E57);
    cpu.set_esp(0x0000E8E6);
    cpu.set_cs(0x00000C02);
    cpu.set_ds(0x0000B6AE);
    cpu.set_es(0x0000B48C);
    cpu.set_fs(0x0000BFFF);
    cpu.set_gs(0x0000D3FF);
    cpu.set_ss(0x00000C7F);
    cpu.set_eip(0x00009AC8);
    cpu.set_eflags(0xFFFC0402);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x15AE8, 0x39);
    machine.mem_store_byte(0x15AE9, 0x39);
    machine.mem_store_byte(0x15AEA, 0xF4);
    machine.mem_store_byte(0x15AEB, 0x40);
    machine.mem_store_byte(0x15AEC, 0x5B);
    machine.mem_store_byte(0x15AED, 0x70);
    machine.mem_store_byte(0x15AEE, 0xEF);
    machine.mem_store_byte(0x15AEF, 0xB1);
    machine.mem_store_byte(0x15AF0, 0xF3);
    machine.mem_store_byte(0x15AF1, 0x6C);
    machine.mem_store_byte(0x15AF2, 0xC9);
    machine.mem_store_byte(0x15AF3, 0x18);
    machine.mem_store_byte(0x15AF4, 0x97);
    machine.mem_store_byte(0x15AF5, 0xED);
    machine.mem_store_byte(0x15AF6, 0x38);
    machine.mem_store_byte(0x15AF7, 0x91);
    machine.mem_store_byte(0x00034, 0x24);
    machine.mem_store_byte(0x00035, 0x7B);
    machine.mem_store_byte(0x00036, 0x8B);
    machine.mem_store_byte(0x00037, 0x63);
    machine.mem_store_byte(0x6B3D4, 0xF4);
    machine.mem_store_byte(0x6B3D5, 0x8F);
    machine.mem_store_byte(0x6B3D6, 0xF4);
    machine.mem_store_byte(0x6B3D7, 0x37);
    machine.mem_store_byte(0x6B3D8, 0xF4);
    machine.mem_store_byte(0x6B3D9, 0x4A);
    machine.mem_store_byte(0x6B3DA, 0xF4);
    machine.mem_store_byte(0x6B3DB, 0x1F);
    machine.mem_store_byte(0x6B3DC, 0xF4);
    machine.mem_store_byte(0x6B3DD, 0x53);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x066220AD);
    EXPECT_EQ(cpu.get_ebx(), 0x0001FFFF);
    EXPECT_EQ(cpu.get_ecx(), 0xA10C97E1);
    EXPECT_EQ(cpu.get_edx(), 0xAC645D04);
    EXPECT_EQ(cpu.get_esi(), 0xFFFC0000);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x21D78E57);
    EXPECT_EQ(cpu.get_esp(), 0x0000E8E0);
    EXPECT_EQ(cpu.get_cs(), 0x0000638B);
    EXPECT_EQ(cpu.get_ds(), 0x0000B6AE);
    EXPECT_EQ(cpu.get_es(), 0x0000B48C);
    EXPECT_EQ(cpu.get_fs(), 0x0000BFFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000D3FF);
    EXPECT_EQ(cpu.get_ss(), 0x00000C7F);
    EXPECT_EQ(cpu.get_eip(), 0x00007B25);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1B0D4), 0x02);
    EXPECT_EQ(memory.load8(0x1B0D5), 0x04);
    EXPECT_EQ(memory.load8(0x1B0D2), 0x02);
    EXPECT_EQ(memory.load8(0x1B0D3), 0x0C);
    EXPECT_EQ(memory.load8(0x1B0D0), 0xC8);
    EXPECT_EQ(memory.load8(0x1B0D1), 0x9A);
}
