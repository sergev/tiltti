#include "test386.h"

//
// aam 0
//
TEST_F(Test386, aam_0_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x5C81B4E3);
    cpu.set_ebx(0xD3BAD2BF);
    cpu.set_ecx(0x202D2A29);
    cpu.set_edx(0x00007FFF);
    cpu.set_esi(0x190B0043);
    cpu.set_edi(0x803DD0AD);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00000019);
    cpu.set_es(0x00000653);
    cpu.set_fs(0x000038D3);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x00002508);
    cpu.set_eip(0x00006E38);
    cpu.set_eflags(0xFFFC0042);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x106E28, 0xD4);
    machine.mem_store_byte(0x106E29, 0x00);
    machine.mem_store_byte(0x106E2A, 0xF4);
    machine.mem_store_byte(0x106E2B, 0x49);
    machine.mem_store_byte(0x106E2C, 0x8B);
    machine.mem_store_byte(0x106E2D, 0x21);
    machine.mem_store_byte(0x106E2E, 0x34);
    machine.mem_store_byte(0x106E2F, 0x33);
    machine.mem_store_byte(0x106E30, 0xDE);
    machine.mem_store_byte(0x106E31, 0x0A);
    machine.mem_store_byte(0x106E32, 0x68);
    machine.mem_store_byte(0x106E33, 0x12);
    machine.mem_store_byte(0x106E34, 0x8C);
    machine.mem_store_byte(0x106E35, 0x19);
    machine.mem_store_byte(0x106E36, 0x1F);
    machine.mem_store_byte(0x106E37, 0x8E);
    machine.mem_store_byte(0x00000, 0x9A);
    machine.mem_store_byte(0x00001, 0x43);
    machine.mem_store_byte(0x00002, 0xFA);
    machine.mem_store_byte(0x00003, 0x4E);
    machine.mem_store_byte(0x5333A, 0xF4);
    machine.mem_store_byte(0x5333B, 0x9D);
    machine.mem_store_byte(0x5333C, 0xF4);
    machine.mem_store_byte(0x5333D, 0xF2);
    machine.mem_store_byte(0x5333E, 0xF4);
    machine.mem_store_byte(0x5333F, 0xB6);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x5C81B4E3);
    EXPECT_EQ(cpu.get_ebx(), 0xD3BAD2BF);
    EXPECT_EQ(cpu.get_ecx(), 0x202D2A29);
    EXPECT_EQ(cpu.get_edx(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esi(), 0x190B0043);
    EXPECT_EQ(cpu.get_edi(), 0x803DD0AD);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x00004EFA);
    EXPECT_EQ(cpu.get_ds(), 0x00000019);
    EXPECT_EQ(cpu.get_es(), 0x00000653);
    EXPECT_EQ(cpu.get_fs(), 0x000038D3);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x00002508);
    EXPECT_EQ(cpu.get_eip(), 0x0000439B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0006);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x25086, 0x06);
    EXPECT_FLAGS_HI(0x25087, 0x00);
    EXPECT_EQ(memory.load8(0x25084), 0xFF);
    EXPECT_EQ(memory.load8(0x25085), 0xFF);
    EXPECT_EQ(memory.load8(0x25082), 0x38);
    EXPECT_EQ(memory.load8(0x25083), 0x6E);
}

//
// div word [fs:eax+34h]
//
TEST_F(Test386, div_word_fs_eax_34h_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0000592B);
    cpu.set_ebx(0xFC9218CF);
    cpu.set_ecx(0x055879FE);
    cpu.set_edx(0x59CAF95A);
    cpu.set_esi(0xCD44283E);
    cpu.set_edi(0x576CBAF3);
    cpu.set_ebp(0xC866FB77);
    cpu.set_esp(0x00007799);
    cpu.set_cs(0x0000E2BF);
    cpu.set_ds(0x0000B6AA);
    cpu.set_es(0x0000E5B1);
    cpu.set_fs(0x0000DBDB);
    cpu.set_gs(0x000005C0);
    cpu.set_ss(0x0000142F);
    cpu.set_eip(0x0000FC00);
    cpu.set_eflags(0xFFFC0813);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF27F0, 0x64);
    machine.mem_store_byte(0xF27F1, 0x67);
    machine.mem_store_byte(0xF27F2, 0xF7);
    machine.mem_store_byte(0xF27F3, 0x70);
    machine.mem_store_byte(0xF27F4, 0x34);
    machine.mem_store_byte(0xF27F5, 0xF4);
    machine.mem_store_byte(0xF27F6, 0xF7);
    machine.mem_store_byte(0xF27F7, 0xD9);
    machine.mem_store_byte(0xF27F8, 0xEE);
    machine.mem_store_byte(0xF27F9, 0x38);
    machine.mem_store_byte(0xF27FA, 0x38);
    machine.mem_store_byte(0xF27FB, 0xCC);
    machine.mem_store_byte(0xE1710, 0x53);
    machine.mem_store_byte(0xE170F, 0xC3);
    machine.mem_store_byte(0xF27FC, 0x3C);
    machine.mem_store_byte(0xF27FD, 0xC4);
    machine.mem_store_byte(0xF27FE, 0xB2);
    machine.mem_store_byte(0xF27FF, 0xE7);
    machine.mem_store_byte(0xF2800, 0xD9);
    machine.mem_store_byte(0xF2801, 0xD8);
    machine.mem_store_byte(0xF2802, 0x0E);
    machine.mem_store_byte(0xF2803, 0x97);
    machine.mem_store_byte(0x00000, 0xF9);
    machine.mem_store_byte(0x00001, 0x5F);
    machine.mem_store_byte(0x00002, 0xD5);
    machine.mem_store_byte(0x00003, 0x43);
    machine.mem_store_byte(0x49D48, 0xDE);
    machine.mem_store_byte(0x49D49, 0xF4);
    machine.mem_store_byte(0x49D4A, 0x5C);
    machine.mem_store_byte(0x49D4B, 0xF4);
    machine.mem_store_byte(0x49D4C, 0x23);
    machine.mem_store_byte(0x49D4D, 0xF4);
    machine.mem_store_byte(0x49D4E, 0x34);
    machine.mem_store_byte(0x49D4F, 0xF4);
    machine.mem_store_byte(0x49D50, 0xFE);
    machine.mem_store_byte(0x49D51, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0000592B);
    EXPECT_EQ(cpu.get_ebx(), 0xFC9218CF);
    EXPECT_EQ(cpu.get_ecx(), 0x055879FE);
    EXPECT_EQ(cpu.get_edx(), 0x59CAF95A);
    EXPECT_EQ(cpu.get_esi(), 0xCD44283E);
    EXPECT_EQ(cpu.get_edi(), 0x576CBAF3);
    EXPECT_EQ(cpu.get_ebp(), 0xC866FB77);
    EXPECT_EQ(cpu.get_esp(), 0x00007793);
    EXPECT_EQ(cpu.get_cs(), 0x000043D5);
    EXPECT_EQ(cpu.get_ds(), 0x0000B6AA);
    EXPECT_EQ(cpu.get_es(), 0x0000E5B1);
    EXPECT_EQ(cpu.get_fs(), 0x0000DBDB);
    EXPECT_EQ(cpu.get_gs(), 0x000005C0);
    EXPECT_EQ(cpu.get_ss(), 0x0000142F);
    EXPECT_EQ(cpu.get_eip(), 0x00005FFA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1BA88), 0x00);
    EXPECT_EQ(memory.load8(0x1BA87), 0x12);
    EXPECT_EQ(memory.load8(0x1BA85), 0xBF);
    EXPECT_EQ(memory.load8(0x1BA86), 0xE2);
    EXPECT_EQ(memory.load8(0x1BA84), 0xFC);
    EXPECT_EQ(memory.load8(0x1BA83), 0x00);
}

//
// idiv byte [ds:edx+26h]
//
TEST_F(Test386, idiv_byte_ds_edx_26h_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x95C855E7);
    cpu.set_ebx(0x496E1E33);
    cpu.set_ecx(0xB5948D84);
    cpu.set_edx(0x000003E6);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xFDD5448E);
    cpu.set_ebp(0xA1A2E6BD);
    cpu.set_esp(0x00000939);
    cpu.set_cs(0x00008666);
    cpu.set_ds(0x00005B64);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00003768);
    cpu.set_gs(0x000005B8);
    cpu.set_ss(0x0000C53B);
    cpu.set_eip(0x00003CB8);
    cpu.set_eflags(0xFFFC0083);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8A318, 0x67);
    machine.mem_store_byte(0x8A319, 0xF6);
    machine.mem_store_byte(0x8A31A, 0x7A);
    machine.mem_store_byte(0x8A31B, 0x26);
    machine.mem_store_byte(0x8A31C, 0xF4);
    machine.mem_store_byte(0x8A31D, 0x3F);
    machine.mem_store_byte(0x8A31E, 0xEE);
    machine.mem_store_byte(0x8A31F, 0x35);
    machine.mem_store_byte(0x8A320, 0x89);
    machine.mem_store_byte(0x8A321, 0xE3);
    machine.mem_store_byte(0x8A322, 0xA6);
    machine.mem_store_byte(0x8A323, 0xAC);
    machine.mem_store_byte(0x5BA4C, 0x45);
    machine.mem_store_byte(0x8A324, 0x96);
    machine.mem_store_byte(0x8A325, 0x3B);
    machine.mem_store_byte(0x8A326, 0xAF);
    machine.mem_store_byte(0x8A327, 0x3B);
    machine.mem_store_byte(0x00000, 0x30);
    machine.mem_store_byte(0x00001, 0xD2);
    machine.mem_store_byte(0x00002, 0xD8);
    machine.mem_store_byte(0x00003, 0xFA);
    machine.mem_store_byte(0x107FB0, 0xF4);
    machine.mem_store_byte(0x107FB1, 0x41);
    machine.mem_store_byte(0x107FB2, 0xF4);
    machine.mem_store_byte(0x107FB3, 0xDE);
    machine.mem_store_byte(0x107FB4, 0xF4);
    machine.mem_store_byte(0x107FB5, 0xC0);
    machine.mem_store_byte(0x107FB6, 0xF4);
    machine.mem_store_byte(0x107FB7, 0xE6);
    machine.mem_store_byte(0x107FB8, 0xF4);
    machine.mem_store_byte(0x107FB9, 0x09);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x95C855E7);
    EXPECT_EQ(cpu.get_ebx(), 0x496E1E33);
    EXPECT_EQ(cpu.get_ecx(), 0xB5948D84);
    EXPECT_EQ(cpu.get_edx(), 0x000003E6);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xFDD5448E);
    EXPECT_EQ(cpu.get_ebp(), 0xA1A2E6BD);
    EXPECT_EQ(cpu.get_esp(), 0x00000933);
    EXPECT_EQ(cpu.get_cs(), 0x0000FAD8);
    EXPECT_EQ(cpu.get_ds(), 0x00005B64);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00003768);
    EXPECT_EQ(cpu.get_gs(), 0x000005B8);
    EXPECT_EQ(cpu.get_ss(), 0x0000C53B);
    EXPECT_EQ(cpu.get_eip(), 0x0000D231);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0097);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC5CE8), 0x00);
    EXPECT_EQ(memory.load8(0xC5CE7), 0x97);
    EXPECT_EQ(memory.load8(0xC5CE5), 0x66);
    EXPECT_EQ(memory.load8(0xC5CE6), 0x86);
    EXPECT_EQ(memory.load8(0xC5CE4), 0x3C);
    EXPECT_EQ(memory.load8(0xC5CE3), 0xB8);
}

//
// idiv byte [gs:bx+si-5]
//
TEST_F(Test386, idiv_byte_gs_bx_si_5_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x95C855E7);
    cpu.set_ebx(0x496E1E33);
    cpu.set_ecx(0xB5948D84);
    cpu.set_edx(0x3F3103E6);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xFDD5448E);
    cpu.set_ebp(0xA1A2E6BD);
    cpu.set_esp(0x00000939);
    cpu.set_cs(0x00008666);
    cpu.set_ds(0x00005B64);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00003768);
    cpu.set_gs(0x000005B8);
    cpu.set_ss(0x0000C53B);
    cpu.set_eip(0x00003CB8);
    cpu.set_eflags(0xFFFC0083);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8A318, 0x65);
    machine.mem_store_byte(0x8A319, 0xF6);
    machine.mem_store_byte(0x8A31A, 0x78);
    machine.mem_store_byte(0x8A31B, 0xFB);
    machine.mem_store_byte(0x8A31C, 0xF4);
    machine.mem_store_byte(0x8A31D, 0x3F);
    machine.mem_store_byte(0x8A31E, 0xEE);
    machine.mem_store_byte(0x8A31F, 0x35);
    machine.mem_store_byte(0x8A320, 0x89);
    machine.mem_store_byte(0x8A321, 0xE3);
    machine.mem_store_byte(0x8A322, 0xA6);
    machine.mem_store_byte(0x8A323, 0xAC);
    machine.mem_store_byte(0x079AE, 0xAE);
    machine.mem_store_byte(0x8A324, 0x96);
    machine.mem_store_byte(0x8A325, 0x3B);
    machine.mem_store_byte(0x8A326, 0xAF);
    machine.mem_store_byte(0x8A327, 0x3B);
    machine.mem_store_byte(0x00000, 0x30);
    machine.mem_store_byte(0x00001, 0xD2);
    machine.mem_store_byte(0x00002, 0xD8);
    machine.mem_store_byte(0x00003, 0xFA);
    machine.mem_store_byte(0x107FB0, 0xF4);
    machine.mem_store_byte(0x107FB1, 0x41);
    machine.mem_store_byte(0x107FB2, 0xF4);
    machine.mem_store_byte(0x107FB3, 0xDE);
    machine.mem_store_byte(0x107FB4, 0xF4);
    machine.mem_store_byte(0x107FB5, 0xC0);
    machine.mem_store_byte(0x107FB6, 0xF4);
    machine.mem_store_byte(0x107FB7, 0xE6);
    machine.mem_store_byte(0x107FB8, 0xF4);
    machine.mem_store_byte(0x107FB9, 0x09);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x95C855E7);
    EXPECT_EQ(cpu.get_ebx(), 0x496E1E33);
    EXPECT_EQ(cpu.get_ecx(), 0xB5948D84);
    EXPECT_EQ(cpu.get_edx(), 0x3F3103E6);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xFDD5448E);
    EXPECT_EQ(cpu.get_ebp(), 0xA1A2E6BD);
    EXPECT_EQ(cpu.get_esp(), 0x00000933);
    EXPECT_EQ(cpu.get_cs(), 0x0000FAD8);
    EXPECT_EQ(cpu.get_ds(), 0x00005B64);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00003768);
    EXPECT_EQ(cpu.get_gs(), 0x000005B8);
    EXPECT_EQ(cpu.get_ss(), 0x0000C53B);
    EXPECT_EQ(cpu.get_eip(), 0x0000D231);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC5CE8), 0x00);
    EXPECT_EQ(memory.load8(0xC5CE7), 0x82);
    EXPECT_EQ(memory.load8(0xC5CE5), 0x66);
    EXPECT_EQ(memory.load8(0xC5CE6), 0x86);
    EXPECT_EQ(memory.load8(0xC5CE4), 0x3C);
    EXPECT_EQ(memory.load8(0xC5CE3), 0xB8);
}

//
// idiv dword [gs:bx+si-5]
//
TEST_F(Test386, idiv_dword_gs_bx_si_5_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x95C855E7);
    cpu.set_ebx(0x496E1E33);
    cpu.set_ecx(0xB5948D84);
    cpu.set_edx(0x3F3103E6);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xFDD5448E);
    cpu.set_ebp(0xA1A2E6BD);
    cpu.set_esp(0x00000939);
    cpu.set_cs(0x00008666);
    cpu.set_ds(0x00005B64);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00003768);
    cpu.set_gs(0x000005B8);
    cpu.set_ss(0x0000C53B);
    cpu.set_eip(0x00003CB8);
    cpu.set_eflags(0xFFFC0083);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8A318, 0x65);
    machine.mem_store_byte(0x8A319, 0x66);
    machine.mem_store_byte(0x8A31A, 0xF7);
    machine.mem_store_byte(0x8A31B, 0x78);
    machine.mem_store_byte(0x8A31C, 0xFB);
    machine.mem_store_byte(0x8A31D, 0xF4);
    machine.mem_store_byte(0x8A31E, 0x48);
    machine.mem_store_byte(0x8A31F, 0xDA);
    machine.mem_store_byte(0x8A320, 0x55);
    machine.mem_store_byte(0x8A321, 0x99);
    machine.mem_store_byte(0x8A322, 0x5F);
    machine.mem_store_byte(0x8A323, 0x8A);
    machine.mem_store_byte(0x079B0, 0x2E);
    machine.mem_store_byte(0x079B1, 0xBE);
    machine.mem_store_byte(0x079AE, 0x7B);
    machine.mem_store_byte(0x079AF, 0x20);
    machine.mem_store_byte(0x8A324, 0x08);
    machine.mem_store_byte(0x8A325, 0xE1);
    machine.mem_store_byte(0x8A326, 0xEF);
    machine.mem_store_byte(0x8A327, 0x6D);
    machine.mem_store_byte(0x00000, 0x66);
    machine.mem_store_byte(0x00001, 0x2A);
    machine.mem_store_byte(0x00002, 0x05);
    machine.mem_store_byte(0x00003, 0x3F);
    machine.mem_store_byte(0x41AB6, 0xF4);
    machine.mem_store_byte(0x41AB7, 0x82);
    machine.mem_store_byte(0x41AB8, 0xF4);
    machine.mem_store_byte(0x41AB9, 0x0D);
    machine.mem_store_byte(0x41ABA, 0xF4);
    machine.mem_store_byte(0x41ABB, 0x53);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x95C855E7);
    EXPECT_EQ(cpu.get_ebx(), 0x496E1E33);
    EXPECT_EQ(cpu.get_ecx(), 0xB5948D84);
    EXPECT_EQ(cpu.get_edx(), 0x3F3103E6);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xFDD5448E);
    EXPECT_EQ(cpu.get_ebp(), 0xA1A2E6BD);
    EXPECT_EQ(cpu.get_esp(), 0x00000933);
    EXPECT_EQ(cpu.get_cs(), 0x00003F05);
    EXPECT_EQ(cpu.get_ds(), 0x00005B64);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00003768);
    EXPECT_EQ(cpu.get_gs(), 0x000005B8);
    EXPECT_EQ(cpu.get_ss(), 0x0000C53B);
    EXPECT_EQ(cpu.get_eip(), 0x00002A67);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC5CE8), 0x00);
    EXPECT_EQ(memory.load8(0xC5CE7), 0x82);
    EXPECT_EQ(memory.load8(0xC5CE5), 0x66);
    EXPECT_EQ(memory.load8(0xC5CE6), 0x86);
    EXPECT_EQ(memory.load8(0xC5CE4), 0x3C);
    EXPECT_EQ(memory.load8(0xC5CE3), 0xB8);
}

//
// o32 enter 9FEDh,F9h
//
TEST_F(Test386, o32_enter_9FEDh_F9h_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF85BCC80);
    cpu.set_ebx(0x5843C464);
    cpu.set_ecx(0xC1B45CC9);
    cpu.set_edx(0xA936A901);
    cpu.set_esi(0x73D1F5B5);
    cpu.set_edi(0x974DD498);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x00000052);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000084F);
    cpu.set_es(0x0000985A);
    cpu.set_fs(0x00001DAF);
    cpu.set_gs(0x00005746);
    cpu.set_ss(0x0000170C);
    cpu.set_eip(0x0000D160);
    cpu.set_eflags(0xFFFC0016);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0D160, 0x64);
    machine.mem_store_byte(0x0D161, 0x64);
    machine.mem_store_byte(0x0D162, 0x66);
    machine.mem_store_byte(0x0D163, 0xC8);
    machine.mem_store_byte(0x0D164, 0xED);
    machine.mem_store_byte(0x0D165, 0x9F);
    machine.mem_store_byte(0x0D166, 0xF9);
    machine.mem_store_byte(0x0D167, 0xF4);
    machine.mem_store_byte(0x0D168, 0x63);
    machine.mem_store_byte(0x0D169, 0x2A);
    machine.mem_store_byte(0x0D16A, 0x26);
    machine.mem_store_byte(0x0D16B, 0x17);
    machine.mem_store_byte(0x0D16C, 0xA9);
    machine.mem_store_byte(0x0D16D, 0x1C);
    machine.mem_store_byte(0x0D16E, 0xFA);
    machine.mem_store_byte(0x0D16F, 0x38);
    machine.mem_store_byte(0x0D170, 0x30);
    machine.mem_store_byte(0x0D171, 0xF5);
    machine.mem_store_byte(0x1F0BC, 0x32);
    machine.mem_store_byte(0x1F0BD, 0x34);
    machine.mem_store_byte(0x1F0BE, 0xF2);
    machine.mem_store_byte(0x1F0BB, 0x55);
    machine.mem_store_byte(0x1F0B8, 0x81);
    machine.mem_store_byte(0x1F0B9, 0xF2);
    machine.mem_store_byte(0x1F0BA, 0xE9);
    machine.mem_store_byte(0x1F0B7, 0x19);
    machine.mem_store_byte(0x1F0B4, 0x39);
    machine.mem_store_byte(0x1F0B5, 0x53);
    machine.mem_store_byte(0x1F0B6, 0xA3);
    machine.mem_store_byte(0x1F0B3, 0x5B);
    machine.mem_store_byte(0x1F0B0, 0x63);
    machine.mem_store_byte(0x1F0B1, 0x18);
    machine.mem_store_byte(0x1F0B2, 0x8F);
    machine.mem_store_byte(0x1F0AF, 0x8A);
    machine.mem_store_byte(0x1F0AC, 0x04);
    machine.mem_store_byte(0x1F0AD, 0xFE);
    machine.mem_store_byte(0x1F0AE, 0xE6);
    machine.mem_store_byte(0x1F0AB, 0xB9);
    machine.mem_store_byte(0x1F0A8, 0x88);
    machine.mem_store_byte(0x1F0A9, 0xD1);
    machine.mem_store_byte(0x1F0AA, 0xA3);
    machine.mem_store_byte(0x1F0A7, 0xC6);
    machine.mem_store_byte(0x1F0A4, 0x42);
    machine.mem_store_byte(0x1F0A5, 0xC8);
    machine.mem_store_byte(0x1F0A6, 0xFF);
    machine.mem_store_byte(0x1F0A3, 0x1E);
    machine.mem_store_byte(0x1F0A0, 0x14);
    machine.mem_store_byte(0x1F0A1, 0xA1);
    machine.mem_store_byte(0x1F0A2, 0x1D);
    machine.mem_store_byte(0x1F09F, 0x8A);
    machine.mem_store_byte(0x1F09C, 0xA7);
    machine.mem_store_byte(0x1F09D, 0x97);
    machine.mem_store_byte(0x1F09E, 0x10);
    machine.mem_store_byte(0x1F09B, 0xB8);
    machine.mem_store_byte(0x1F098, 0xE7);
    machine.mem_store_byte(0x1F099, 0xBA);
    machine.mem_store_byte(0x1F09A, 0x72);
    machine.mem_store_byte(0x1F097, 0x0B);
    machine.mem_store_byte(0x1F094, 0x84);
    machine.mem_store_byte(0x1F095, 0x58);
    machine.mem_store_byte(0x1F096, 0x39);
    machine.mem_store_byte(0x1F093, 0x31);
    machine.mem_store_byte(0x1F090, 0xE2);
    machine.mem_store_byte(0x1F091, 0x70);
    machine.mem_store_byte(0x1F092, 0x54);
    machine.mem_store_byte(0x1F08F, 0xE6);
    machine.mem_store_byte(0x1F08C, 0xC7);
    machine.mem_store_byte(0x1F08D, 0xBF);
    machine.mem_store_byte(0x1F08E, 0x32);
    machine.mem_store_byte(0x1F08B, 0x00);
    machine.mem_store_byte(0x1F088, 0x3E);
    machine.mem_store_byte(0x1F089, 0x51);
    machine.mem_store_byte(0x1F08A, 0x8B);
    machine.mem_store_byte(0x1F087, 0x15);
    machine.mem_store_byte(0x1F084, 0xAA);
    machine.mem_store_byte(0x1F085, 0x3A);
    machine.mem_store_byte(0x1F086, 0x5E);
    machine.mem_store_byte(0x1F083, 0x21);
    machine.mem_store_byte(0x1F080, 0xE3);
    machine.mem_store_byte(0x1F081, 0x2A);
    machine.mem_store_byte(0x1F082, 0x31);
    machine.mem_store_byte(0x1F07F, 0xCD);
    machine.mem_store_byte(0x1F07C, 0x3F);
    machine.mem_store_byte(0x1F07D, 0xE9);
    machine.mem_store_byte(0x1F07E, 0xC9);
    machine.mem_store_byte(0x1F07B, 0x53);
    machine.mem_store_byte(0x1F078, 0x1C);
    machine.mem_store_byte(0x1F079, 0xE9);
    machine.mem_store_byte(0x1F07A, 0x66);
    machine.mem_store_byte(0x1F077, 0x7E);
    machine.mem_store_byte(0x1F074, 0x31);
    machine.mem_store_byte(0x1F075, 0x84);
    machine.mem_store_byte(0x1F076, 0xDC);
    machine.mem_store_byte(0x1F073, 0xF8);
    machine.mem_store_byte(0x1F070, 0x01);
    machine.mem_store_byte(0x1F071, 0x3A);
    machine.mem_store_byte(0x1F072, 0xF6);
    machine.mem_store_byte(0x1F06F, 0x22);
    machine.mem_store_byte(0x00030, 0xAB);
    machine.mem_store_byte(0x00031, 0xAA);
    machine.mem_store_byte(0x00032, 0x9D);
    machine.mem_store_byte(0x00033, 0xB6);
    machine.mem_store_byte(0xC147A, 0x87);
    machine.mem_store_byte(0xC147B, 0xF4);
    machine.mem_store_byte(0xC147C, 0xC4);
    machine.mem_store_byte(0xC147D, 0xF4);
    machine.mem_store_byte(0xC147E, 0xE4);
    machine.mem_store_byte(0xC147F, 0xF4);
    machine.mem_store_byte(0xC1480, 0x91);
    machine.mem_store_byte(0xC1481, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF85BCC80);
    EXPECT_EQ(cpu.get_ebx(), 0x5843C464);
    EXPECT_EQ(cpu.get_ecx(), 0xC1B45CC9);
    EXPECT_EQ(cpu.get_edx(), 0xA936A901);
    EXPECT_EQ(cpu.get_esi(), 0x73D1F5B5);
    EXPECT_EQ(cpu.get_edi(), 0x974DD498);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000004C);
    EXPECT_EQ(cpu.get_cs(), 0x0000B69D);
    EXPECT_EQ(cpu.get_ds(), 0x0000084F);
    EXPECT_EQ(cpu.get_es(), 0x0000985A);
    EXPECT_EQ(cpu.get_fs(), 0x00001DAF);
    EXPECT_EQ(cpu.get_gs(), 0x00005746);
    EXPECT_EQ(cpu.get_ss(), 0x0000170C);
    EXPECT_EQ(cpu.get_eip(), 0x0000AAAC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x17110), 0x16);
    EXPECT_EQ(memory.load8(0x17111), 0x00);
    EXPECT_EQ(memory.load8(0x1710E), 0x00);
    EXPECT_EQ(memory.load8(0x1710F), 0x00);
    EXPECT_EQ(memory.load8(0x1710C), 0x60);
    EXPECT_EQ(memory.load8(0x1710D), 0xD1);
    EXPECT_EQ(memory.load8(0x1710A), 0x55);
    EXPECT_EQ(memory.load8(0x1710B), 0x32);
    EXPECT_EQ(memory.load8(0x17108), 0xF2);
    EXPECT_EQ(memory.load8(0x17109), 0xE9);
    EXPECT_EQ(memory.load8(0x17106), 0x19);
    EXPECT_EQ(memory.load8(0x17107), 0x81);
    EXPECT_EQ(memory.load8(0x17104), 0x53);
    EXPECT_EQ(memory.load8(0x17105), 0xA3);
    EXPECT_EQ(memory.load8(0x17102), 0x5B);
    EXPECT_EQ(memory.load8(0x17103), 0x39);
    EXPECT_EQ(memory.load8(0x17100), 0x18);
    EXPECT_EQ(memory.load8(0x17101), 0x8F);
    EXPECT_EQ(memory.load8(0x170FE), 0x8A);
    EXPECT_EQ(memory.load8(0x170FF), 0x63);
    EXPECT_EQ(memory.load8(0x170FC), 0xFE);
    EXPECT_EQ(memory.load8(0x170FD), 0xE6);
    EXPECT_EQ(memory.load8(0x170FA), 0xB9);
    EXPECT_EQ(memory.load8(0x170FB), 0x04);
    EXPECT_EQ(memory.load8(0x170F8), 0xD1);
    EXPECT_EQ(memory.load8(0x170F9), 0xA3);
    EXPECT_EQ(memory.load8(0x170F6), 0xC6);
    EXPECT_EQ(memory.load8(0x170F7), 0x88);
    EXPECT_EQ(memory.load8(0x170F4), 0xC8);
    EXPECT_EQ(memory.load8(0x170F5), 0xFF);
    EXPECT_EQ(memory.load8(0x170F2), 0x1E);
    EXPECT_EQ(memory.load8(0x170F3), 0x42);
    EXPECT_EQ(memory.load8(0x170F0), 0xA1);
    EXPECT_EQ(memory.load8(0x170F1), 0x1D);
    EXPECT_EQ(memory.load8(0x170EE), 0x8A);
    EXPECT_EQ(memory.load8(0x170EF), 0x14);
    EXPECT_EQ(memory.load8(0x170EC), 0x97);
    EXPECT_EQ(memory.load8(0x170ED), 0x10);
    EXPECT_EQ(memory.load8(0x170EA), 0xB8);
    EXPECT_EQ(memory.load8(0x170EB), 0xA7);
    EXPECT_EQ(memory.load8(0x170E8), 0xBA);
    EXPECT_EQ(memory.load8(0x170E9), 0x72);
    EXPECT_EQ(memory.load8(0x170E6), 0x0B);
    EXPECT_EQ(memory.load8(0x170E7), 0xE7);
    EXPECT_EQ(memory.load8(0x170E4), 0x58);
    EXPECT_EQ(memory.load8(0x170E5), 0x39);
    EXPECT_EQ(memory.load8(0x170E2), 0x31);
    EXPECT_EQ(memory.load8(0x170E3), 0x84);
    EXPECT_EQ(memory.load8(0x170E0), 0x70);
    EXPECT_EQ(memory.load8(0x170E1), 0x54);
    EXPECT_EQ(memory.load8(0x170DE), 0xE6);
    EXPECT_EQ(memory.load8(0x170DF), 0xE2);
    EXPECT_EQ(memory.load8(0x170DC), 0xBF);
    EXPECT_EQ(memory.load8(0x170DD), 0x32);
    EXPECT_EQ(memory.load8(0x170DA), 0x00);
    EXPECT_EQ(memory.load8(0x170DB), 0xC7);
    EXPECT_EQ(memory.load8(0x170D8), 0x51);
    EXPECT_EQ(memory.load8(0x170D9), 0x8B);
    EXPECT_EQ(memory.load8(0x170D6), 0x15);
    EXPECT_EQ(memory.load8(0x170D7), 0x3E);
    EXPECT_EQ(memory.load8(0x170D4), 0x3A);
    EXPECT_EQ(memory.load8(0x170D5), 0x5E);
    EXPECT_EQ(memory.load8(0x170D2), 0x21);
    EXPECT_EQ(memory.load8(0x170D3), 0xAA);
    EXPECT_EQ(memory.load8(0x170D0), 0x2A);
    EXPECT_EQ(memory.load8(0x170D1), 0x31);
    EXPECT_EQ(memory.load8(0x170CE), 0xCD);
    EXPECT_EQ(memory.load8(0x170CF), 0xE3);
    EXPECT_EQ(memory.load8(0x170CC), 0xE9);
    EXPECT_EQ(memory.load8(0x170CD), 0xC9);
    EXPECT_EQ(memory.load8(0x170CA), 0x53);
    EXPECT_EQ(memory.load8(0x170CB), 0x3F);
    EXPECT_EQ(memory.load8(0x170C8), 0xE9);
    EXPECT_EQ(memory.load8(0x170C9), 0x66);
    EXPECT_EQ(memory.load8(0x170C6), 0x7E);
    EXPECT_EQ(memory.load8(0x170C7), 0x1C);
    EXPECT_EQ(memory.load8(0x170C4), 0x84);
    EXPECT_EQ(memory.load8(0x170C5), 0xDC);
    EXPECT_EQ(memory.load8(0x170C2), 0xF8);
    EXPECT_EQ(memory.load8(0x170C3), 0x31);
}

//
// pop bx
//
TEST_F(Test386, pop_bx_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x01FFFFFF);
    cpu.set_ebx(0x9744EEA7);
    cpu.set_ecx(0x66FA5289);
    cpu.set_edx(0xFE15141F);
    cpu.set_esi(0x9D2F23F0);
    cpu.set_edi(0x91E102D5);
    cpu.set_ebp(0x00000060);
    cpu.set_esp(0x0000FFFF);
    cpu.set_cs(0x0000E3F6);
    cpu.set_ds(0x00000CC4);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x0000DF09);
    cpu.set_gs(0x00000040);
    cpu.set_ss(0x00001EB4);
    cpu.set_eip(0x00005BA0);
    cpu.set_eflags(0xFFFC08D7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE9B00, 0x5B);
    machine.mem_store_byte(0xE9B01, 0xF4);
    machine.mem_store_byte(0xE9B02, 0xC6);
    machine.mem_store_byte(0xE9B03, 0xED);
    machine.mem_store_byte(0xE9B04, 0x40);
    machine.mem_store_byte(0xE9B05, 0x74);
    machine.mem_store_byte(0xE9B06, 0x2F);
    machine.mem_store_byte(0xE9B07, 0xFB);
    machine.mem_store_byte(0xE9B08, 0x0C);
    machine.mem_store_byte(0xE9B09, 0x20);
    machine.mem_store_byte(0xE9B0A, 0xEF);
    machine.mem_store_byte(0xE9B0B, 0x60);
    machine.mem_store_byte(0xE9B0C, 0x24);
    machine.mem_store_byte(0xE9B0D, 0x35);
    machine.mem_store_byte(0xE9B0E, 0x8D);
    machine.mem_store_byte(0xE9B0F, 0x36);
    machine.mem_store_byte(0xE9B10, 0x73);
    machine.mem_store_byte(0xE9B11, 0x07);
    machine.mem_store_byte(0xE9B12, 0x3A);
    machine.mem_store_byte(0xE9B13, 0x48);
    machine.mem_store_byte(0x00030, 0xC6);
    machine.mem_store_byte(0x00031, 0x1A);
    machine.mem_store_byte(0x00032, 0x2A);
    machine.mem_store_byte(0x00033, 0xE3);
    machine.mem_store_byte(0xE4D66, 0xF4);
    machine.mem_store_byte(0xE4D67, 0xFE);
    machine.mem_store_byte(0xE4D68, 0xF4);
    machine.mem_store_byte(0xE4D69, 0xB1);
    machine.mem_store_byte(0xE4D6A, 0xF4);
    machine.mem_store_byte(0xE4D6B, 0xF6);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x01FFFFFF);
    EXPECT_EQ(cpu.get_ebx(), 0x9744EEA7);
    EXPECT_EQ(cpu.get_ecx(), 0x66FA5289);
    EXPECT_EQ(cpu.get_edx(), 0xFE15141F);
    EXPECT_EQ(cpu.get_esi(), 0x9D2F23F0);
    EXPECT_EQ(cpu.get_edi(), 0x91E102D5);
    EXPECT_EQ(cpu.get_ebp(), 0x00000060);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF9);
    EXPECT_EQ(cpu.get_cs(), 0x0000E32A);
    EXPECT_EQ(cpu.get_ds(), 0x00000CC4);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x0000DF09);
    EXPECT_EQ(cpu.get_gs(), 0x00000040);
    EXPECT_EQ(cpu.get_ss(), 0x00001EB4);
    EXPECT_EQ(cpu.get_eip(), 0x00001AC7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D7);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x2EB3D, 0xD7);
    EXPECT_FLAGS_HI(0x2EB3E, 0x08);
    EXPECT_EQ(memory.load8(0x2EB3C), 0xE3);
    EXPECT_EQ(memory.load8(0x2EB3B), 0xF6);
    EXPECT_EQ(memory.load8(0x2EB39), 0xA0);
    EXPECT_EQ(memory.load8(0x2EB3A), 0x5B);
}

//
// pop cx
//
TEST_F(Test386, pop_cx_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000014);
    cpu.set_ebx(0x911E80FA);
    cpu.set_ecx(0xCC148059);
    cpu.set_edx(0x308EDE49);
    cpu.set_esi(0x6625DFDC);
    cpu.set_edi(0x05CB7DC5);
    cpu.set_ebp(0x4F0A1E61);
    cpu.set_esp(0x0000FFFF);
    cpu.set_cs(0x0000E55D);
    cpu.set_ds(0x00001A85);
    cpu.set_es(0x0000784C);
    cpu.set_fs(0x00004F5E);
    cpu.set_gs(0x0000AFFC);
    cpu.set_ss(0x000000AF);
    cpu.set_eip(0x0000DEA0);
    cpu.set_eflags(0xFFFC0416);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF3470, 0x59);
    machine.mem_store_byte(0xF3471, 0xF4);
    machine.mem_store_byte(0xF3472, 0x52);
    machine.mem_store_byte(0xF3473, 0x85);
    machine.mem_store_byte(0xF3474, 0x94);
    machine.mem_store_byte(0xF3475, 0x91);
    machine.mem_store_byte(0xF3476, 0x37);
    machine.mem_store_byte(0xF3477, 0x6E);
    machine.mem_store_byte(0xF3478, 0x26);
    machine.mem_store_byte(0xF3479, 0x80);
    machine.mem_store_byte(0xF347A, 0x9E);
    machine.mem_store_byte(0xF347B, 0xA2);
    machine.mem_store_byte(0xF347C, 0xE6);
    machine.mem_store_byte(0xF347D, 0x22);
    machine.mem_store_byte(0xF347E, 0x62);
    machine.mem_store_byte(0xF347F, 0xFD);
    machine.mem_store_byte(0xF3480, 0x97);
    machine.mem_store_byte(0xF3481, 0x38);
    machine.mem_store_byte(0xF3482, 0xD9);
    machine.mem_store_byte(0xF3483, 0xEE);
    machine.mem_store_byte(0x00030, 0x7F);
    machine.mem_store_byte(0x00031, 0x91);
    machine.mem_store_byte(0x00032, 0x2D);
    machine.mem_store_byte(0x00033, 0x46);
    machine.mem_store_byte(0x4F44E, 0xB9);
    machine.mem_store_byte(0x4F44F, 0xF4);
    machine.mem_store_byte(0x4F450, 0xAB);
    machine.mem_store_byte(0x4F451, 0xF4);
    machine.mem_store_byte(0x4F452, 0x35);
    machine.mem_store_byte(0x4F453, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000014);
    EXPECT_EQ(cpu.get_ebx(), 0x911E80FA);
    EXPECT_EQ(cpu.get_ecx(), 0xCC148059);
    EXPECT_EQ(cpu.get_edx(), 0x308EDE49);
    EXPECT_EQ(cpu.get_esi(), 0x6625DFDC);
    EXPECT_EQ(cpu.get_edi(), 0x05CB7DC5);
    EXPECT_EQ(cpu.get_ebp(), 0x4F0A1E61);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF9);
    EXPECT_EQ(cpu.get_cs(), 0x0000462D);
    EXPECT_EQ(cpu.get_ds(), 0x00001A85);
    EXPECT_EQ(cpu.get_es(), 0x0000784C);
    EXPECT_EQ(cpu.get_fs(), 0x00004F5E);
    EXPECT_EQ(cpu.get_gs(), 0x0000AFFC);
    EXPECT_EQ(cpu.get_ss(), 0x000000AF);
    EXPECT_EQ(cpu.get_eip(), 0x00009180);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0416);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x10AED, 0x16);
    EXPECT_FLAGS_HI(0x10AEE, 0x04);
    EXPECT_EQ(memory.load8(0x10AEC), 0xE5);
    EXPECT_EQ(memory.load8(0x10AEB), 0x5D);
    EXPECT_EQ(memory.load8(0x10AE9), 0xA0);
    EXPECT_EQ(memory.load8(0x10AEA), 0xDE);
}

//
// push sp
//
TEST_F(Test386, push_sp_batch70)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x5A5A5A5A);
    cpu.set_ebx(0xC3A6945D);
    cpu.set_ecx(0xF95ADC25);
    cpu.set_edx(0xFD29DC71);
    cpu.set_esi(0x57F2805E);
    cpu.set_edi(0xAB50A441);
    cpu.set_ebp(0xD1AACFD4);
    cpu.set_esp(0x00004492);
    cpu.set_cs(0x00005833);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x000000E6);
    cpu.set_fs(0x00003DFA);
    cpu.set_gs(0x00007446);
    cpu.set_ss(0x0000B412);
    cpu.set_eip(0x00005530);
    cpu.set_eflags(0xFFFC0847);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5D860, 0xFF);
    machine.mem_store_byte(0x5D861, 0xF4);
    machine.mem_store_byte(0x5D862, 0xF4);
    machine.mem_store_byte(0x5D863, 0x08);
    machine.mem_store_byte(0x5D864, 0x6E);
    machine.mem_store_byte(0x5D865, 0x35);
    machine.mem_store_byte(0x5D866, 0xAB);
    machine.mem_store_byte(0x5D867, 0xA6);
    machine.mem_store_byte(0x5D868, 0x20);
    machine.mem_store_byte(0x5D869, 0x8C);
    machine.mem_store_byte(0x5D86A, 0x9C);
    machine.mem_store_byte(0x5D86B, 0x15);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x5A5A5A5A);
    EXPECT_EQ(cpu.get_ebx(), 0xC3A6945D);
    EXPECT_EQ(cpu.get_ecx(), 0xF95ADC25);
    EXPECT_EQ(cpu.get_edx(), 0xFD29DC71);
    EXPECT_EQ(cpu.get_esi(), 0x57F2805E);
    EXPECT_EQ(cpu.get_edi(), 0xAB50A441);
    EXPECT_EQ(cpu.get_ebp(), 0xD1AACFD4);
    EXPECT_EQ(cpu.get_esp(), 0x00004490);
    EXPECT_EQ(cpu.get_cs(), 0x00005833);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x000000E6);
    EXPECT_EQ(cpu.get_fs(), 0x00003DFA);
    EXPECT_EQ(cpu.get_gs(), 0x00007446);
    EXPECT_EQ(cpu.get_ss(), 0x0000B412);
    EXPECT_EQ(cpu.get_eip(), 0x00005533);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0847);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB85B0), 0x92);
    EXPECT_EQ(memory.load8(0xB85B1), 0x44);
}
