#include "test386.h"

//
// bsr dx,[ss:bp+si+A3Dh]
//
TEST_F(Test386, bsr_dx_ss_bp_si_A3Dh_batch25)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0003F3CA);
    cpu.set_ebx(0x5AF4756B);
    cpu.set_ecx(0xC23007DF);
    cpu.set_edx(0x7960464D);
    cpu.set_esi(0x28BE0E8C);
    cpu.set_edi(0x691B46CF);
    cpu.set_ebp(0x3E7A72A8);
    cpu.set_esp(0x0000C14E);
    cpu.set_cs(0x0000F0B6);
    cpu.set_ds(0x0000A84D);
    cpu.set_es(0x0000FF13);
    cpu.set_fs(0x0000AFD4);
    cpu.set_gs(0x0000A99A);
    cpu.set_ss(0x00000132);
    cpu.set_eip(0x000032D0);
    cpu.set_eflags(0xFFFC0C92);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF3E30, 0x0F);
    machine.mem_store_byte(0xF3E31, 0xBD);
    machine.mem_store_byte(0xF3E32, 0x92);
    machine.mem_store_byte(0xF3E33, 0x3D);
    machine.mem_store_byte(0xF3E34, 0x0A);
    machine.mem_store_byte(0xF3E35, 0xF4);
    machine.mem_store_byte(0xF3E36, 0x00);
    machine.mem_store_byte(0xF3E37, 0x00);
    machine.mem_store_byte(0xF3E38, 0x00);
    machine.mem_store_byte(0xF3E39, 0x00);
    machine.mem_store_byte(0xF3E3A, 0x00);
    machine.mem_store_byte(0xF3E3B, 0x00);
    machine.mem_store_byte(0x09E91, 0x00);
    machine.mem_store_byte(0x09E92, 0x00);
    machine.mem_store_byte(0xF3E3C, 0x00);
    machine.mem_store_byte(0xF3E3D, 0x00);
    machine.mem_store_byte(0xF3E3E, 0x00);
    machine.mem_store_byte(0xF3E3F, 0x00);
    machine.mem_store_byte(0xF3E40, 0x00);
    machine.mem_store_byte(0xF3E41, 0x00);
    machine.mem_store_byte(0xF3E42, 0x00);
    machine.mem_store_byte(0xF3E43, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0003F3CA);
    EXPECT_EQ(cpu.get_ebx(), 0x5AF4756B);
    EXPECT_EQ(cpu.get_ecx(), 0xC23007DF);
    EXPECT_EQ(cpu.get_edx(), 0x7960464D);
    EXPECT_EQ(cpu.get_esi(), 0x28BE0E8C);
    EXPECT_EQ(cpu.get_edi(), 0x691B46CF);
    EXPECT_EQ(cpu.get_ebp(), 0x3E7A72A8);
    EXPECT_EQ(cpu.get_esp(), 0x0000C14E);
    EXPECT_EQ(cpu.get_cs(), 0x0000F0B6);
    EXPECT_EQ(cpu.get_ds(), 0x0000A84D);
    EXPECT_EQ(cpu.get_es(), 0x0000FF13);
    EXPECT_EQ(cpu.get_fs(), 0x0000AFD4);
    EXPECT_EQ(cpu.get_gs(), 0x0000A99A);
    EXPECT_EQ(cpu.get_ss(), 0x00000132);
    EXPECT_EQ(cpu.get_eip(), 0x000032D6);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
}

//
// bsr edx,[ss:bp+si+A3Dh]
//
TEST_F(Test386, bsr_edx_ss_bp_si_A3Dh_batch25)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0003F3CA);
    cpu.set_ebx(0x5AF4756B);
    cpu.set_ecx(0xC23007DF);
    cpu.set_edx(0x7960464D);
    cpu.set_esi(0x28BE0E8C);
    cpu.set_edi(0x691B46CF);
    cpu.set_ebp(0x3E7A72A8);
    cpu.set_esp(0x0000C14E);
    cpu.set_cs(0x0000F0B6);
    cpu.set_ds(0x0000A84D);
    cpu.set_es(0x0000FF13);
    cpu.set_fs(0x0000AFD4);
    cpu.set_gs(0x0000A99A);
    cpu.set_ss(0x00000132);
    cpu.set_eip(0x000032D0);
    cpu.set_eflags(0xFFFC0C92);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF3E30, 0x66);
    machine.mem_store_byte(0xF3E31, 0x0F);
    machine.mem_store_byte(0xF3E32, 0xBD);
    machine.mem_store_byte(0xF3E33, 0x92);
    machine.mem_store_byte(0xF3E34, 0x3D);
    machine.mem_store_byte(0xF3E35, 0x0A);
    machine.mem_store_byte(0xF3E36, 0xF4);
    machine.mem_store_byte(0xF3E37, 0x00);
    machine.mem_store_byte(0xF3E38, 0x00);
    machine.mem_store_byte(0xF3E39, 0x00);
    machine.mem_store_byte(0xF3E3A, 0x00);
    machine.mem_store_byte(0xF3E3B, 0x00);
    machine.mem_store_byte(0x09E94, 0x00);
    machine.mem_store_byte(0x09E91, 0x00);
    machine.mem_store_byte(0x09E92, 0x00);
    machine.mem_store_byte(0x09E93, 0x00);
    machine.mem_store_byte(0xF3E3C, 0x00);
    machine.mem_store_byte(0xF3E3D, 0x00);
    machine.mem_store_byte(0xF3E3E, 0x00);
    machine.mem_store_byte(0xF3E3F, 0x00);
    machine.mem_store_byte(0xF3E40, 0x00);
    machine.mem_store_byte(0xF3E41, 0x00);
    machine.mem_store_byte(0xF3E42, 0x00);
    machine.mem_store_byte(0xF3E43, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0003F3CA);
    EXPECT_EQ(cpu.get_ebx(), 0x5AF4756B);
    EXPECT_EQ(cpu.get_ecx(), 0xC23007DF);
    EXPECT_EQ(cpu.get_edx(), 0x7960464D);
    EXPECT_EQ(cpu.get_esi(), 0x28BE0E8C);
    EXPECT_EQ(cpu.get_edi(), 0x691B46CF);
    EXPECT_EQ(cpu.get_ebp(), 0x3E7A72A8);
    EXPECT_EQ(cpu.get_esp(), 0x0000C14E);
    EXPECT_EQ(cpu.get_cs(), 0x0000F0B6);
    EXPECT_EQ(cpu.get_ds(), 0x0000A84D);
    EXPECT_EQ(cpu.get_es(), 0x0000FF13);
    EXPECT_EQ(cpu.get_fs(), 0x0000AFD4);
    EXPECT_EQ(cpu.get_gs(), 0x0000A99A);
    EXPECT_EQ(cpu.get_ss(), 0x00000132);
    EXPECT_EQ(cpu.get_eip(), 0x000032D7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
}

//
// div byte [ss:bp+si-2EAh]
//
TEST_F(Test386, div_byte_ss_bp_si_2EAh_batch25)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7FFFFFFF);
    cpu.set_ebx(0x62703489);
    cpu.set_ecx(0xDE2BB39F);
    cpu.set_edx(0x6F877F5E);
    cpu.set_esi(0xA4E7B044);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x01D7CF44);
    cpu.set_esp(0x00007A3A);
    cpu.set_cs(0x0000436F);
    cpu.set_ds(0x0000FFF4);
    cpu.set_es(0x00000AED);
    cpu.set_fs(0x0000B8BD);
    cpu.set_gs(0x00008784);
    cpu.set_ss(0x000012D7);
    cpu.set_eip(0x000080D0);
    cpu.set_eflags(0xFFFC0C57);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4B7C0, 0xF6);
    machine.mem_store_byte(0x4B7C1, 0xB2);
    machine.mem_store_byte(0x4B7C2, 0x16);
    machine.mem_store_byte(0x4B7C3, 0xFD);
    machine.mem_store_byte(0x4B7C4, 0xF4);
    machine.mem_store_byte(0x4B7C5, 0x26);
    machine.mem_store_byte(0x4B7C6, 0xAE);
    machine.mem_store_byte(0x4B7C7, 0x0D);
    machine.mem_store_byte(0x4B7C8, 0xD2);
    machine.mem_store_byte(0x4B7C9, 0x8E);
    machine.mem_store_byte(0x1AA0E, 0x7E);
    machine.mem_store_byte(0x4B7CA, 0x9C);
    machine.mem_store_byte(0x4B7CB, 0xC8);
    machine.mem_store_byte(0x4B7CC, 0x38);
    machine.mem_store_byte(0x4B7CD, 0x88);
    machine.mem_store_byte(0x4B7CE, 0x22);
    machine.mem_store_byte(0x4B7CF, 0xCF);
    machine.mem_store_byte(0x4B7D0, 0xB4);
    machine.mem_store_byte(0x4B7D1, 0x1F);
    machine.mem_store_byte(0x4B7D2, 0x1B);
    machine.mem_store_byte(0x4B7D3, 0x8A);
    machine.mem_store_byte(0x00000, 0x76);
    machine.mem_store_byte(0x00001, 0xD4);
    machine.mem_store_byte(0x00002, 0x13);
    machine.mem_store_byte(0x00003, 0xEE);
    machine.mem_store_byte(0xFB5A6, 0xF4);
    machine.mem_store_byte(0xFB5A7, 0x7F);
    machine.mem_store_byte(0xFB5A8, 0xF4);
    machine.mem_store_byte(0xFB5A9, 0x65);
    machine.mem_store_byte(0xFB5AA, 0xF4);
    machine.mem_store_byte(0xFB5AB, 0xAD);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebx(), 0x62703489);
    EXPECT_EQ(cpu.get_ecx(), 0xDE2BB39F);
    EXPECT_EQ(cpu.get_edx(), 0x6F877F5E);
    EXPECT_EQ(cpu.get_esi(), 0xA4E7B044);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x01D7CF44);
    EXPECT_EQ(cpu.get_esp(), 0x00007A34);
    EXPECT_EQ(cpu.get_cs(), 0x0000EE13);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFF4);
    EXPECT_EQ(cpu.get_es(), 0x00000AED);
    EXPECT_EQ(cpu.get_fs(), 0x0000B8BD);
    EXPECT_EQ(cpu.get_gs(), 0x00008784);
    EXPECT_EQ(cpu.get_ss(), 0x000012D7);
    EXPECT_EQ(cpu.get_eip(), 0x0000D477);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C16);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x1A7A8, 0x16);
    EXPECT_FLAGS_HI(0x1A7A9, 0x0C);
    EXPECT_EQ(memory.load8(0x1A7A6), 0x6F);
    EXPECT_EQ(memory.load8(0x1A7A7), 0x43);
    EXPECT_EQ(memory.load8(0x1A7A4), 0xD0);
    EXPECT_EQ(memory.load8(0x1A7A5), 0x80);
}

//
// lea dx,[ds:91724F65h]
//
TEST_F(Test386, lea_dx_ds_91724F65h_batch25)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xEFAE56B8);
    cpu.set_ebx(0x41089D1D);
    cpu.set_ecx(0xFF8319C6);
    cpu.set_edx(0xEE61B828);
    cpu.set_esi(0xE788A17D);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x000000C0);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x000003E3);
    cpu.set_ds(0x00006BAB);
    cpu.set_es(0x00009EB7);
    cpu.set_fs(0x00001EAF);
    cpu.set_gs(0x00000200);
    cpu.set_ss(0x0000E409);
    cpu.set_eip(0x00003178);
    cpu.set_eflags(0xFFFC08D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x06FA8, 0x67);
    machine.mem_store_byte(0x06FA9, 0x8D);
    machine.mem_store_byte(0x06FAA, 0x15);
    machine.mem_store_byte(0x06FAB, 0x65);
    machine.mem_store_byte(0x06FAC, 0x4F);
    machine.mem_store_byte(0x06FAD, 0x72);
    machine.mem_store_byte(0x06FAE, 0x91);
    machine.mem_store_byte(0x06FAF, 0xF4);
    machine.mem_store_byte(0x06FB0, 0xEB);
    machine.mem_store_byte(0x06FB1, 0x92);
    machine.mem_store_byte(0x06FB2, 0xEC);
    machine.mem_store_byte(0x06FB3, 0x89);
    machine.mem_store_byte(0x06FB4, 0x20);
    machine.mem_store_byte(0x06FB5, 0x8C);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xEFAE56B8);
    EXPECT_EQ(cpu.get_ebx(), 0x41089D1D);
    EXPECT_EQ(cpu.get_ecx(), 0xFF8319C6);
    EXPECT_EQ(cpu.get_edx(), 0xEE614F65);
    EXPECT_EQ(cpu.get_esi(), 0xE788A17D);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x000000C0);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x000003E3);
    EXPECT_EQ(cpu.get_ds(), 0x00006BAB);
    EXPECT_EQ(cpu.get_es(), 0x00009EB7);
    EXPECT_EQ(cpu.get_fs(), 0x00001EAF);
    EXPECT_EQ(cpu.get_gs(), 0x00000200);
    EXPECT_EQ(cpu.get_ss(), 0x0000E409);
    EXPECT_EQ(cpu.get_eip(), 0x00003180);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D2);

    // Final RAM entries
}

//
// lea edx,[ds:91724F65h]
//
TEST_F(Test386, lea_edx_ds_91724F65h_batch25)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xEFAE56B8);
    cpu.set_ebx(0x41089D1D);
    cpu.set_ecx(0xFF8319C6);
    cpu.set_edx(0xEE61B828);
    cpu.set_esi(0xE788A17D);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x000000C0);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x000003E3);
    cpu.set_ds(0x00006BAB);
    cpu.set_es(0x00009EB7);
    cpu.set_fs(0x00001EAF);
    cpu.set_gs(0x00000200);
    cpu.set_ss(0x0000E409);
    cpu.set_eip(0x00003178);
    cpu.set_eflags(0xFFFC08D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x06FA8, 0x67);
    machine.mem_store_byte(0x06FA9, 0x66);
    machine.mem_store_byte(0x06FAA, 0x8D);
    machine.mem_store_byte(0x06FAB, 0x15);
    machine.mem_store_byte(0x06FAC, 0x65);
    machine.mem_store_byte(0x06FAD, 0x4F);
    machine.mem_store_byte(0x06FAE, 0x72);
    machine.mem_store_byte(0x06FAF, 0x91);
    machine.mem_store_byte(0x06FB0, 0xF4);
    machine.mem_store_byte(0x06FB1, 0x92);
    machine.mem_store_byte(0x06FB2, 0xEC);
    machine.mem_store_byte(0x06FB3, 0x89);
    machine.mem_store_byte(0x06FB4, 0x20);
    machine.mem_store_byte(0x06FB5, 0x8C);
    machine.mem_store_byte(0x06FB6, 0x44);
    machine.mem_store_byte(0x06FB7, 0x04);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xEFAE56B8);
    EXPECT_EQ(cpu.get_ebx(), 0x41089D1D);
    EXPECT_EQ(cpu.get_ecx(), 0xFF8319C6);
    EXPECT_EQ(cpu.get_edx(), 0x91724F65);
    EXPECT_EQ(cpu.get_esi(), 0xE788A17D);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x000000C0);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x000003E3);
    EXPECT_EQ(cpu.get_ds(), 0x00006BAB);
    EXPECT_EQ(cpu.get_es(), 0x00009EB7);
    EXPECT_EQ(cpu.get_fs(), 0x00001EAF);
    EXPECT_EQ(cpu.get_gs(), 0x00000200);
    EXPECT_EQ(cpu.get_ss(), 0x0000E409);
    EXPECT_EQ(cpu.get_eip(), 0x00003181);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D2);

    // Final RAM entries
}

//
// popad
//
TEST_F(Test386, popad_batch25)
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
    machine.mem_store_byte(0xE9590, 0x66);
    machine.mem_store_byte(0xE9591, 0x61);
    machine.mem_store_byte(0xE9592, 0xF4);
    machine.mem_store_byte(0xE9593, 0xFE);
    machine.mem_store_byte(0xE9594, 0x4B);
    machine.mem_store_byte(0xE9595, 0x77);
    machine.mem_store_byte(0xE9596, 0x51);
    machine.mem_store_byte(0xE9597, 0xDF);
    machine.mem_store_byte(0xE9598, 0x24);
    machine.mem_store_byte(0xE9599, 0x6B);
    machine.mem_store_byte(0xE959A, 0x15);
    machine.mem_store_byte(0xE959B, 0xF3);
    machine.mem_store_byte(0xE959C, 0x2F);
    machine.mem_store_byte(0xE959D, 0x8E);
    machine.mem_store_byte(0xE959E, 0xF6);
    machine.mem_store_byte(0xE959F, 0x0A);
    machine.mem_store_byte(0x00030, 0x23);
    machine.mem_store_byte(0x00031, 0xF0);
    machine.mem_store_byte(0x00032, 0x87);
    machine.mem_store_byte(0x00033, 0xF1);
    machine.mem_store_byte(0x100892, 0x69);
    machine.mem_store_byte(0x100893, 0xF4);
    machine.mem_store_byte(0x100894, 0x52);
    machine.mem_store_byte(0x100895, 0xF4);
    machine.mem_store_byte(0x100896, 0x40);
    machine.mem_store_byte(0x100897, 0xF4);
    machine.mem_store_byte(0x100898, 0xFF);
    machine.mem_store_byte(0x100899, 0xF4);

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
    EXPECT_EQ(cpu.get_edx(), 0xD3E7B32D);
    EXPECT_EQ(cpu.get_esi(), 0xF7AA0FB6);
    EXPECT_EQ(cpu.get_edi(), 0x1637BB67);
    EXPECT_EQ(cpu.get_ebp(), 0xDED841D2);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x0000F187);
    EXPECT_EQ(cpu.get_ds(), 0x00005740);
    EXPECT_EQ(cpu.get_es(), 0x00006CDE);
    EXPECT_EQ(cpu.get_fs(), 0x000000F6);
    EXPECT_EQ(cpu.get_gs(), 0x00009999);
    EXPECT_EQ(cpu.get_ss(), 0x0000AEA8);
    EXPECT_EQ(cpu.get_eip(), 0x0000F024);
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
// retf 5D59h
//
TEST_F(Test386, retf_5D59h_batch25)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFA766AD6);
    cpu.set_ebx(0x467676A7);
    cpu.set_ecx(0x2EBCE4B7);
    cpu.set_edx(0x00007FFF);
    cpu.set_esi(0x47ADA82F);
    cpu.set_edi(0x14C25D14);
    cpu.set_ebp(0x21648D77);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x00009AE7);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x000087A2);
    cpu.set_fs(0x0000DAA2);
    cpu.set_gs(0x0000FAFB);
    cpu.set_ss(0x0000FE3A);
    cpu.set_eip(0x00005328);
    cpu.set_eflags(0xFFFC0492);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA0198, 0xCA);
    machine.mem_store_byte(0xA0199, 0x59);
    machine.mem_store_byte(0xA019A, 0x5D);
    machine.mem_store_byte(0xA019B, 0xF4);
    machine.mem_store_byte(0xA019C, 0x2D);
    machine.mem_store_byte(0xA019D, 0x4B);
    machine.mem_store_byte(0xA019E, 0x35);
    machine.mem_store_byte(0xA019F, 0x9C);
    machine.mem_store_byte(0x10E39E, 0xB4);
    machine.mem_store_byte(0x10E39F, 0xA2);
    machine.mem_store_byte(0xFE3A0, 0xC4);
    machine.mem_store_byte(0xFE3A1, 0xDD);
    machine.mem_store_byte(0xE7EF4, 0xF4);
    machine.mem_store_byte(0xE7EF5, 0xF4);
    machine.mem_store_byte(0xE7EF6, 0x5A);
    machine.mem_store_byte(0xE7EF7, 0xB1);
    machine.mem_store_byte(0xE7EF8, 0x20);
    machine.mem_store_byte(0xE7EF9, 0xBF);
    machine.mem_store_byte(0xE7EFA, 0x2B);
    machine.mem_store_byte(0xE7EFB, 0xE2);
    machine.mem_store_byte(0xE7EFC, 0x00);
    machine.mem_store_byte(0xE7EFD, 0x7E);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFA766AD6);
    EXPECT_EQ(cpu.get_ebx(), 0x467676A7);
    EXPECT_EQ(cpu.get_ecx(), 0x2EBCE4B7);
    EXPECT_EQ(cpu.get_edx(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esi(), 0x47ADA82F);
    EXPECT_EQ(cpu.get_edi(), 0x14C25D14);
    EXPECT_EQ(cpu.get_ebp(), 0x21648D77);
    EXPECT_EQ(cpu.get_esp(), 0x00005D5B);
    EXPECT_EQ(cpu.get_cs(), 0x0000DDC4);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x000087A2);
    EXPECT_EQ(cpu.get_fs(), 0x0000DAA2);
    EXPECT_EQ(cpu.get_gs(), 0x0000FAFB);
    EXPECT_EQ(cpu.get_ss(), 0x0000FE3A);
    EXPECT_EQ(cpu.get_eip(), 0x0000A2B5);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0492);

    // Final RAM entries
}

//
// retf 6EEh
//
TEST_F(Test386, retf_6EEh_batch25)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1144AD36);
    cpu.set_ebx(0x31AF39C3);
    cpu.set_ecx(0x063D4067);
    cpu.set_edx(0xA2BE97FB);
    cpu.set_esi(0xF7280C77);
    cpu.set_edi(0xAB717755);
    cpu.set_ebp(0xFF55F4FC);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000F161);
    cpu.set_ds(0x00009590);
    cpu.set_es(0x0000A142);
    cpu.set_fs(0x00002BC7);
    cpu.set_gs(0x0000573A);
    cpu.set_ss(0x00007B6B);
    cpu.set_eip(0x00002AC8);
    cpu.set_eflags(0xFFFC00D7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF40D8, 0xCA);
    machine.mem_store_byte(0xF40D9, 0xEE);
    machine.mem_store_byte(0xF40DA, 0x06);
    machine.mem_store_byte(0xF40DB, 0xF4);
    machine.mem_store_byte(0xF40DC, 0x26);
    machine.mem_store_byte(0xF40DD, 0x7D);
    machine.mem_store_byte(0xF40DE, 0x72);
    machine.mem_store_byte(0xF40DF, 0xC7);
    machine.mem_store_byte(0x8B6AE, 0x3B);
    machine.mem_store_byte(0x8B6AF, 0xC4);
    machine.mem_store_byte(0x7B6B0, 0xD7);
    machine.mem_store_byte(0x7B6B1, 0xC9);
    machine.mem_store_byte(0xD61AA, 0xF4);
    machine.mem_store_byte(0xD61AB, 0xF4);
    machine.mem_store_byte(0xD61AC, 0xDA);
    machine.mem_store_byte(0xD61AD, 0x11);
    machine.mem_store_byte(0xD61AE, 0xAC);
    machine.mem_store_byte(0xD61AF, 0x6E);
    machine.mem_store_byte(0xD61B0, 0x66);
    machine.mem_store_byte(0xD61B1, 0xFA);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1144AD36);
    EXPECT_EQ(cpu.get_ebx(), 0x31AF39C3);
    EXPECT_EQ(cpu.get_ecx(), 0x063D4067);
    EXPECT_EQ(cpu.get_edx(), 0xA2BE97FB);
    EXPECT_EQ(cpu.get_esi(), 0xF7280C77);
    EXPECT_EQ(cpu.get_edi(), 0xAB717755);
    EXPECT_EQ(cpu.get_ebp(), 0xFF55F4FC);
    EXPECT_EQ(cpu.get_esp(), 0x000006F0);
    EXPECT_EQ(cpu.get_cs(), 0x0000C9D7);
    EXPECT_EQ(cpu.get_ds(), 0x00009590);
    EXPECT_EQ(cpu.get_es(), 0x0000A142);
    EXPECT_EQ(cpu.get_fs(), 0x00002BC7);
    EXPECT_EQ(cpu.get_gs(), 0x0000573A);
    EXPECT_EQ(cpu.get_ss(), 0x00007B6B);
    EXPECT_EQ(cpu.get_eip(), 0x0000C43C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00D7);

    // Final RAM entries
}
