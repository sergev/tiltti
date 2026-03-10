#include "test386.h"

//
// div bx
//
TEST_F(Test386, div_bx_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDE255FE5);
    cpu.set_ebx(0xD6202C0F);
    cpu.set_ecx(0x0E9BA616);
    cpu.set_edx(0x48C9D278);
    cpu.set_esi(0x00008000);
    cpu.set_edi(0xFF8E4CAD);
    cpu.set_ebp(0x4B47E83C);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00001AFA);
    cpu.set_es(0x0000578C);
    cpu.set_fs(0x0000F954);
    cpu.set_gs(0x00001E80);
    cpu.set_ss(0x00009FC4);
    cpu.set_eip(0x0000A298);
    cpu.set_eflags(0xFFFC0C82);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10A288, 0xF7);
    machine.mem_store_byte(0x10A289, 0xF3);
    machine.mem_store_byte(0x10A28A, 0xF4);
    machine.mem_store_byte(0x10A28B, 0x3C);
    machine.mem_store_byte(0x10A28C, 0x66);
    machine.mem_store_byte(0x10A28D, 0xED);
    machine.mem_store_byte(0x10A28E, 0xAD);
    machine.mem_store_byte(0x10A28F, 0x17);
    machine.mem_store_byte(0x10A290, 0x77);
    machine.mem_store_byte(0x10A291, 0xFA);
    machine.mem_store_byte(0x10A292, 0x7F);
    machine.mem_store_byte(0x10A293, 0x5C);
    machine.mem_store_byte(0x10A294, 0x98);
    machine.mem_store_byte(0x10A295, 0xE3);
    machine.mem_store_byte(0x10A296, 0xFA);
    machine.mem_store_byte(0x10A297, 0x5C);
    machine.mem_store_byte(0x00000, 0x05);
    machine.mem_store_byte(0x00001, 0xC1);
    machine.mem_store_byte(0x00002, 0x06);
    machine.mem_store_byte(0x00003, 0x64);
    machine.mem_store_byte(0x70164, 0xE5);
    machine.mem_store_byte(0x70165, 0xF4);
    machine.mem_store_byte(0x70166, 0x40);
    machine.mem_store_byte(0x70167, 0xF4);
    machine.mem_store_byte(0x70168, 0xB2);
    machine.mem_store_byte(0x70169, 0xF4);
    machine.mem_store_byte(0x7016A, 0xC8);
    machine.mem_store_byte(0x7016B, 0xF4);
    machine.mem_store_byte(0x7016C, 0x65);
    machine.mem_store_byte(0x7016D, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDE255FE5);
    EXPECT_EQ(cpu.get_ebx(), 0xD6202C0F);
    EXPECT_EQ(cpu.get_ecx(), 0x0E9BA616);
    EXPECT_EQ(cpu.get_edx(), 0x48C9D278);
    EXPECT_EQ(cpu.get_esi(), 0x00008000);
    EXPECT_EQ(cpu.get_edi(), 0xFF8E4CAD);
    EXPECT_EQ(cpu.get_ebp(), 0x4B47E83C);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x00006406);
    EXPECT_EQ(cpu.get_ds(), 0x00001AFA);
    EXPECT_EQ(cpu.get_es(), 0x0000578C);
    EXPECT_EQ(cpu.get_fs(), 0x0000F954);
    EXPECT_EQ(cpu.get_gs(), 0x00001E80);
    EXPECT_EQ(cpu.get_ss(), 0x00009FC4);
    EXPECT_EQ(cpu.get_eip(), 0x0000C106);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x9FC46, 0x93);
    EXPECT_FLAGS_HI(0x9FC47, 0x04);
    EXPECT_EQ(memory.load8(0x9FC44), 0xFF);
    EXPECT_EQ(memory.load8(0x9FC45), 0xFF);
    EXPECT_EQ(memory.load8(0x9FC42), 0x98);
    EXPECT_EQ(memory.load8(0x9FC43), 0xA2);
}

//
// imul byte [ds:edx+eax*8+277h]
//
TEST_F(Test386, imul_byte_ds_edx_eax_8_277h_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x000001C3);
    cpu.set_ebx(0x65ACC794);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0x00000FFF);
    cpu.set_esi(0x700A2ADB);
    cpu.set_edi(0x00000001);
    cpu.set_ebp(0xD51C7A11);
    cpu.set_esp(0x0000FFF2);
    cpu.set_cs(0x0000C3C4);
    cpu.set_ds(0x0000257F);
    cpu.set_es(0x00005A5A);
    cpu.set_fs(0x00002001);
    cpu.set_gs(0x00009D1B);
    cpu.set_ss(0x00006204);
    cpu.set_eip(0x0000FFF8);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD3C38, 0x67);
    machine.mem_store_byte(0xD3C39, 0xF6);
    machine.mem_store_byte(0xD3C3A, 0xAC);
    machine.mem_store_byte(0xD3C3B, 0xC2);
    machine.mem_store_byte(0xD3C3C, 0x77);
    machine.mem_store_byte(0xD3C3D, 0x02);
    machine.mem_store_byte(0xD3C3E, 0x00);
    machine.mem_store_byte(0xD3C3F, 0x00);
    machine.mem_store_byte(0xD3C40, 0xF4);
    machine.mem_store_byte(0x2787E, 0x34);
    machine.mem_store_byte(0x00034, 0x86);
    machine.mem_store_byte(0x00035, 0x54);
    machine.mem_store_byte(0x00036, 0x28);
    machine.mem_store_byte(0x00037, 0xC1);
    machine.mem_store_byte(0xC6706, 0xF4);
    machine.mem_store_byte(0xC6707, 0x84);
    machine.mem_store_byte(0xC6708, 0xF4);
    machine.mem_store_byte(0xC6709, 0xAC);
    machine.mem_store_byte(0xC670A, 0xF4);
    machine.mem_store_byte(0xC670B, 0xF3);
    machine.mem_store_byte(0xC670C, 0xF4);
    machine.mem_store_byte(0xC670D, 0x7E);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0000F39C);
    EXPECT_EQ(cpu.get_ebx(), 0x65ACC794);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x00000FFF);
    EXPECT_EQ(cpu.get_esi(), 0x700A2ADB);
    EXPECT_EQ(cpu.get_edi(), 0x00000001);
    EXPECT_EQ(cpu.get_ebp(), 0xD51C7A11);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFEC);
    EXPECT_EQ(cpu.get_cs(), 0x0000C128);
    EXPECT_EQ(cpu.get_ds(), 0x0000257F);
    EXPECT_EQ(cpu.get_es(), 0x00005A5A);
    EXPECT_EQ(cpu.get_fs(), 0x00002001);
    EXPECT_EQ(cpu.get_gs(), 0x00009D1B);
    EXPECT_EQ(cpu.get_ss(), 0x00006204);
    EXPECT_EQ(cpu.get_eip(), 0x00005487);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C87);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x72030), 0x87);
    EXPECT_EQ(memory.load8(0x72031), 0x0C);
    EXPECT_EQ(memory.load8(0x7202E), 0xC4);
    EXPECT_EQ(memory.load8(0x7202F), 0xC3);
    EXPECT_EQ(memory.load8(0x7202C), 0x00);
    EXPECT_EQ(memory.load8(0x7202D), 0x00);
}

//
// not dword [ds:bp-3305h]
//
TEST_F(Test386, not_dword_ds_bp_3305h_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x80000000);
    cpu.set_ebx(0xFE43AFDA);
    cpu.set_ecx(0xD3275BE9);
    cpu.set_edx(0x5A4BC8E2);
    cpu.set_esi(0x6C870E00);
    cpu.set_edi(0xAD4EAF06);
    cpu.set_ebp(0x0CE84DDC);
    cpu.set_esp(0x000078EE);
    cpu.set_cs(0x00002652);
    cpu.set_ds(0x00000642);
    cpu.set_es(0x0000BC03);
    cpu.set_fs(0x0000DD65);
    cpu.set_gs(0x0000964B);
    cpu.set_ss(0x00002B95);
    cpu.set_eip(0x0000FFF8);
    cpu.set_eflags(0xFFFC0007);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x36518, 0x64);
    machine.mem_store_byte(0x36519, 0x65);
    machine.mem_store_byte(0x3651A, 0x64);
    machine.mem_store_byte(0x3651B, 0x3E);
    machine.mem_store_byte(0x3651C, 0x66);
    machine.mem_store_byte(0x3651D, 0xF7);
    machine.mem_store_byte(0x3651E, 0x96);
    machine.mem_store_byte(0x3651F, 0xFB);
    machine.mem_store_byte(0x36520, 0xCC);
    machine.mem_store_byte(0x36521, 0xF4);
    machine.mem_store_byte(0x00034, 0x75);
    machine.mem_store_byte(0x00035, 0x83);
    machine.mem_store_byte(0x00036, 0x09);
    machine.mem_store_byte(0x00037, 0x9F);
    machine.mem_store_byte(0xA7404, 0x9C);
    machine.mem_store_byte(0xA7405, 0xF4);
    machine.mem_store_byte(0xA7406, 0x55);
    machine.mem_store_byte(0xA7407, 0xF4);
    machine.mem_store_byte(0xA7408, 0x5D);
    machine.mem_store_byte(0xA7409, 0xF4);
    machine.mem_store_byte(0xA740A, 0x5B);
    machine.mem_store_byte(0xA740B, 0xF4);
    machine.mem_store_byte(0xA740C, 0xB2);
    machine.mem_store_byte(0xA740D, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x80000000);
    EXPECT_EQ(cpu.get_ebx(), 0xFE43AFDA);
    EXPECT_EQ(cpu.get_ecx(), 0xD3275BE9);
    EXPECT_EQ(cpu.get_edx(), 0x5A4BC8E2);
    EXPECT_EQ(cpu.get_esi(), 0x6C870E00);
    EXPECT_EQ(cpu.get_edi(), 0xAD4EAF06);
    EXPECT_EQ(cpu.get_ebp(), 0x0CE84DDC);
    EXPECT_EQ(cpu.get_esp(), 0x000078E8);
    EXPECT_EQ(cpu.get_cs(), 0x00009F09);
    EXPECT_EQ(cpu.get_ds(), 0x00000642);
    EXPECT_EQ(cpu.get_es(), 0x0000BC03);
    EXPECT_EQ(cpu.get_fs(), 0x0000DD65);
    EXPECT_EQ(cpu.get_gs(), 0x0000964B);
    EXPECT_EQ(cpu.get_ss(), 0x00002B95);
    EXPECT_EQ(cpu.get_eip(), 0x00008376);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0007);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3323C), 0x07);
    EXPECT_EQ(memory.load8(0x3323D), 0x00);
    EXPECT_EQ(memory.load8(0x3323A), 0x52);
    EXPECT_EQ(memory.load8(0x3323B), 0x26);
    EXPECT_EQ(memory.load8(0x33238), 0xF8);
    EXPECT_EQ(memory.load8(0x33239), 0xFF);
}

//
// not word [ds:bp-3305h]
//
TEST_F(Test386, not_word_ds_bp_3305h_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x80000000);
    cpu.set_ebx(0xFE43AFDA);
    cpu.set_ecx(0xD3275BE9);
    cpu.set_edx(0x5A4BC8E2);
    cpu.set_esi(0x6C870E00);
    cpu.set_edi(0xAD4EAF06);
    cpu.set_ebp(0x0CE84DDC);
    cpu.set_esp(0x000078EE);
    cpu.set_cs(0x00002652);
    cpu.set_ds(0x00000642);
    cpu.set_es(0x0000BC03);
    cpu.set_fs(0x0000DD65);
    cpu.set_gs(0x0000964B);
    cpu.set_ss(0x00002B95);
    cpu.set_eip(0x0000FFF8);
    cpu.set_eflags(0xFFFC0007);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x36518, 0x64);
    machine.mem_store_byte(0x36519, 0x65);
    machine.mem_store_byte(0x3651A, 0x64);
    machine.mem_store_byte(0x3651B, 0x3E);
    machine.mem_store_byte(0x3651C, 0xF7);
    machine.mem_store_byte(0x3651D, 0x96);
    machine.mem_store_byte(0x3651E, 0xFB);
    machine.mem_store_byte(0x3651F, 0xCC);
    machine.mem_store_byte(0x36520, 0xF4);
    machine.mem_store_byte(0x07EF8, 0x2E);
    machine.mem_store_byte(0x07EF7, 0xF8);
    machine.mem_store_byte(0x00034, 0x75);
    machine.mem_store_byte(0x00035, 0x83);
    machine.mem_store_byte(0x00036, 0x09);
    machine.mem_store_byte(0x00037, 0x9F);
    machine.mem_store_byte(0xA7404, 0x9C);
    machine.mem_store_byte(0xA7405, 0xF4);
    machine.mem_store_byte(0xA7406, 0x55);
    machine.mem_store_byte(0xA7407, 0xF4);
    machine.mem_store_byte(0xA7408, 0x5D);
    machine.mem_store_byte(0xA7409, 0xF4);
    machine.mem_store_byte(0xA740A, 0x5B);
    machine.mem_store_byte(0xA740B, 0xF4);
    machine.mem_store_byte(0xA740C, 0xB2);
    machine.mem_store_byte(0xA740D, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x80000000);
    EXPECT_EQ(cpu.get_ebx(), 0xFE43AFDA);
    EXPECT_EQ(cpu.get_ecx(), 0xD3275BE9);
    EXPECT_EQ(cpu.get_edx(), 0x5A4BC8E2);
    EXPECT_EQ(cpu.get_esi(), 0x6C870E00);
    EXPECT_EQ(cpu.get_edi(), 0xAD4EAF06);
    EXPECT_EQ(cpu.get_ebp(), 0x0CE84DDC);
    EXPECT_EQ(cpu.get_esp(), 0x000078E8);
    EXPECT_EQ(cpu.get_cs(), 0x00009F09);
    EXPECT_EQ(cpu.get_ds(), 0x00000642);
    EXPECT_EQ(cpu.get_es(), 0x0000BC03);
    EXPECT_EQ(cpu.get_fs(), 0x0000DD65);
    EXPECT_EQ(cpu.get_gs(), 0x0000964B);
    EXPECT_EQ(cpu.get_ss(), 0x00002B95);
    EXPECT_EQ(cpu.get_eip(), 0x00008376);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0007);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x07EF8), 0xD1);
    EXPECT_EQ(memory.load8(0x07EF7), 0x07);
    EXPECT_EQ(memory.load8(0x3323C), 0x07);
    EXPECT_EQ(memory.load8(0x3323D), 0x00);
    EXPECT_EQ(memory.load8(0x3323A), 0x52);
    EXPECT_EQ(memory.load8(0x3323B), 0x26);
    EXPECT_EQ(memory.load8(0x33238), 0x00);
    EXPECT_EQ(memory.load8(0x33239), 0x00);
}

//
// ror bh,cl
//
TEST_F(Test386, ror_bh_cl_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFCB58DD2);
    cpu.set_ebx(0x3DE7AAFB);
    cpu.set_ecx(0x9FE95810);
    cpu.set_edx(0x62D11F2A);
    cpu.set_esi(0x2098D72C);
    cpu.set_edi(0x60E6A472);
    cpu.set_ebp(0x92E736BF);
    cpu.set_esp(0x000006B2);
    cpu.set_cs(0x00009B9D);
    cpu.set_ds(0x0000ECC1);
    cpu.set_es(0x000085E0);
    cpu.set_fs(0x00000232);
    cpu.set_gs(0x0000399E);
    cpu.set_ss(0x0000ECBD);
    cpu.set_eip(0x00006DE8);
    cpu.set_eflags(0xFFFC0443);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA27B8, 0x3E);
    machine.mem_store_byte(0xA27B9, 0x2E);
    machine.mem_store_byte(0xA27BA, 0xD2);
    machine.mem_store_byte(0xA27BB, 0xCF);
    machine.mem_store_byte(0xA27BC, 0xF4);
    machine.mem_store_byte(0xA27BD, 0xB6);
    machine.mem_store_byte(0xA27BE, 0x76);
    machine.mem_store_byte(0xA27BF, 0xB5);
    machine.mem_store_byte(0xA27C0, 0xC6);
    machine.mem_store_byte(0xA27C1, 0xF9);
    machine.mem_store_byte(0xA27C2, 0xB8);
    machine.mem_store_byte(0xA27C3, 0xB7);
    machine.mem_store_byte(0xA27C4, 0x7E);
    machine.mem_store_byte(0xA27C5, 0x68);
    machine.mem_store_byte(0xA27C6, 0x3A);
    machine.mem_store_byte(0xA27C7, 0x34);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFCB58DD2);
    EXPECT_EQ(cpu.get_ebx(), 0x3DE7AAFB);
    EXPECT_EQ(cpu.get_ecx(), 0x9FE95810);
    EXPECT_EQ(cpu.get_edx(), 0x62D11F2A);
    EXPECT_EQ(cpu.get_esi(), 0x2098D72C);
    EXPECT_EQ(cpu.get_edi(), 0x60E6A472);
    EXPECT_EQ(cpu.get_ebp(), 0x92E736BF);
    EXPECT_EQ(cpu.get_esp(), 0x000006B2);
    EXPECT_EQ(cpu.get_cs(), 0x00009B9D);
    EXPECT_EQ(cpu.get_ds(), 0x0000ECC1);
    EXPECT_EQ(cpu.get_es(), 0x000085E0);
    EXPECT_EQ(cpu.get_fs(), 0x00000232);
    EXPECT_EQ(cpu.get_gs(), 0x0000399E);
    EXPECT_EQ(cpu.get_ss(), 0x0000ECBD);
    EXPECT_EQ(cpu.get_eip(), 0x00006DED);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C43);

    // Final RAM entries
}

//
// call far [ds:bx-3908h]
//
TEST_F(Test386, call_far_ds_bx_3908h_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00008000);
    cpu.set_ebx(0x8A4A52E7);
    cpu.set_ecx(0x8DDE1FF7);
    cpu.set_edx(0x4ECE0790);
    cpu.set_esi(0x99FDBE8F);
    cpu.set_edi(0xBD77CF14);
    cpu.set_ebp(0x7FFFFFFF);
    cpu.set_esp(0x00009D40);
    cpu.set_cs(0x0000F1DB);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00005FE8);
    cpu.set_fs(0x0000CFD9);
    cpu.set_gs(0x0000A3E8);
    cpu.set_ss(0x0000575D);
    cpu.set_eip(0x00000DC0);
    cpu.set_eflags(0xFFFC0412);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF2B70, 0xFF);
    machine.mem_store_byte(0xF2B71, 0x9F);
    machine.mem_store_byte(0xF2B72, 0xF8);
    machine.mem_store_byte(0xF2B73, 0xC6);
    machine.mem_store_byte(0xF2B74, 0xF4);
    machine.mem_store_byte(0xF2B75, 0xFF);
    machine.mem_store_byte(0xF2B76, 0xFF);
    machine.mem_store_byte(0xF2B77, 0xFF);
    machine.mem_store_byte(0xF2B78, 0xFF);
    machine.mem_store_byte(0xF2B79, 0xFF);
    machine.mem_store_byte(0x1019D0, 0xFF);
    machine.mem_store_byte(0x1019CF, 0xFF);
    machine.mem_store_byte(0x1019D1, 0xFF);
    machine.mem_store_byte(0x1019D2, 0xFF);
    machine.mem_store_byte(0x10FFEE, 0xF4);
    machine.mem_store_byte(0x10FFEF, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00008000);
    EXPECT_EQ(cpu.get_ebx(), 0x8A4A52E7);
    EXPECT_EQ(cpu.get_ecx(), 0x8DDE1FF7);
    EXPECT_EQ(cpu.get_edx(), 0x4ECE0790);
    EXPECT_EQ(cpu.get_esi(), 0x99FDBE8F);
    EXPECT_EQ(cpu.get_edi(), 0xBD77CF14);
    EXPECT_EQ(cpu.get_ebp(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x00009D3C);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00005FE8);
    EXPECT_EQ(cpu.get_fs(), 0x0000CFD9);
    EXPECT_EQ(cpu.get_gs(), 0x0000A3E8);
    EXPECT_EQ(cpu.get_ss(), 0x0000575D);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0412);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6130E), 0xDB);
    EXPECT_EQ(memory.load8(0x6130F), 0xF1);
    EXPECT_EQ(memory.load8(0x6130C), 0xC4);
    EXPECT_EQ(memory.load8(0x6130D), 0x0D);
}

//
// call word [ds:bx+3Dh]
//
TEST_F(Test386, call_word_ds_bx_3Dh_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xCA2C831F);
    cpu.set_ebx(0x4B70EF5C);
    cpu.set_ecx(0x96C71E20);
    cpu.set_edx(0x0AADCEF5);
    cpu.set_esi(0x19C57742);
    cpu.set_edi(0xDEE285A1);
    cpu.set_ebp(0x8EEB2497);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x00000D4D);
    cpu.set_ds(0x00007821);
    cpu.set_es(0x0000F6F0);
    cpu.set_fs(0x0000F760);
    cpu.set_gs(0x00000D6C);
    cpu.set_ss(0x0000CABA);
    cpu.set_eip(0x0000EFC0);
    cpu.set_eflags(0xFFFC08D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1C490, 0xFF);
    machine.mem_store_byte(0x1C491, 0x57);
    machine.mem_store_byte(0x1C492, 0x3D);
    machine.mem_store_byte(0x1C493, 0xF4);
    machine.mem_store_byte(0x1C494, 0xFF);
    machine.mem_store_byte(0x1C495, 0xFF);
    machine.mem_store_byte(0x1C496, 0xFF);
    machine.mem_store_byte(0x1C497, 0xFF);
    machine.mem_store_byte(0x1C498, 0xFF);
    machine.mem_store_byte(0x1C499, 0xFF);
    machine.mem_store_byte(0x871A9, 0xFF);
    machine.mem_store_byte(0x871AA, 0xFF);
    machine.mem_store_byte(0x1D4CE, 0xF4);
    machine.mem_store_byte(0x1D4CF, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xCA2C831F);
    EXPECT_EQ(cpu.get_ebx(), 0x4B70EF5C);
    EXPECT_EQ(cpu.get_ecx(), 0x96C71E20);
    EXPECT_EQ(cpu.get_edx(), 0x0AADCEF5);
    EXPECT_EQ(cpu.get_esi(), 0x19C57742);
    EXPECT_EQ(cpu.get_edi(), 0xDEE285A1);
    EXPECT_EQ(cpu.get_ebp(), 0x8EEB2497);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFFC);
    EXPECT_EQ(cpu.get_cs(), 0x00000D4D);
    EXPECT_EQ(cpu.get_ds(), 0x00007821);
    EXPECT_EQ(cpu.get_es(), 0x0000F6F0);
    EXPECT_EQ(cpu.get_fs(), 0x0000F760);
    EXPECT_EQ(cpu.get_gs(), 0x00000D6C);
    EXPECT_EQ(cpu.get_ss(), 0x0000CABA);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDAB9C), 0xC3);
    EXPECT_EQ(memory.load8(0xDAB9D), 0xEF);
}

//
// iret
//
TEST_F(Test386, iret_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7FFFFFFF);
    cpu.set_ebx(0x575516FB);
    cpu.set_ecx(0x5D17F20F);
    cpu.set_edx(0xA8201098);
    cpu.set_esi(0xCCFF64CE);
    cpu.set_edi(0x0451E5C8);
    cpu.set_ebp(0xCD3AD6F9);
    cpu.set_esp(0x0000FFFC);
    cpu.set_cs(0x0000CCC3);
    cpu.set_ds(0x00009AF8);
    cpu.set_es(0x00001894);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00005142);
    cpu.set_ss(0x0000BB4F);
    cpu.set_eip(0x00004D38);
    cpu.set_eflags(0xFFFC0C03);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD1968, 0xCF);
    machine.mem_store_byte(0xD1969, 0xF4);
    machine.mem_store_byte(0xD196A, 0xFF);
    machine.mem_store_byte(0xD196B, 0xFF);
    machine.mem_store_byte(0xD196C, 0xFF);
    machine.mem_store_byte(0xD196D, 0xFF);
    machine.mem_store_byte(0xD196E, 0xFF);
    machine.mem_store_byte(0xD196F, 0xFF);
    machine.mem_store_byte(0xCB4EC, 0xFF);
    machine.mem_store_byte(0xCB4ED, 0xFF);
    machine.mem_store_byte(0xCB4EE, 0xFF);
    machine.mem_store_byte(0xCB4EF, 0xFF);
    machine.mem_store_byte(0xBB4F0, 0x84);
    machine.mem_store_byte(0xBB4F1, 0x04);
    machine.mem_store_byte(0x10FFEE, 0xF4);
    machine.mem_store_byte(0x10FFEF, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebx(), 0x575516FB);
    EXPECT_EQ(cpu.get_ecx(), 0x5D17F20F);
    EXPECT_EQ(cpu.get_edx(), 0xA8201098);
    EXPECT_EQ(cpu.get_esi(), 0xCCFF64CE);
    EXPECT_EQ(cpu.get_edi(), 0x0451E5C8);
    EXPECT_EQ(cpu.get_ebp(), 0xCD3AD6F9);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x00009AF8);
    EXPECT_EQ(cpu.get_es(), 0x00001894);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00005142);
    EXPECT_EQ(cpu.get_ss(), 0x0000BB4F);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0486);

    // Final RAM entries
}

//
// jmp far [ss:bp+di+6103h]
//
TEST_F(Test386, jmp_far_ss_bp_di_6103h_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x22A15415);
    cpu.set_ebx(0xF0868A8F);
    cpu.set_ecx(0x60BE8753);
    cpu.set_edx(0x33F24D5E);
    cpu.set_esi(0x0E94F5AF);
    cpu.set_edi(0xF79BF7F2);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00007DEC);
    cpu.set_ds(0x00005AC2);
    cpu.set_es(0x0000C11D);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x0000305C);
    cpu.set_ss(0x00003A8B);
    cpu.set_eip(0x0000E5B0);
    cpu.set_eflags(0xFFFC0C46);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8C470, 0xFF);
    machine.mem_store_byte(0x8C471, 0xAB);
    machine.mem_store_byte(0x8C472, 0x03);
    machine.mem_store_byte(0x8C473, 0x61);
    machine.mem_store_byte(0x8C474, 0xF4);
    machine.mem_store_byte(0x8C475, 0xFF);
    machine.mem_store_byte(0x8C476, 0xFF);
    machine.mem_store_byte(0x8C477, 0xFF);
    machine.mem_store_byte(0x8C478, 0xFF);
    machine.mem_store_byte(0x8C479, 0xFF);
    machine.mem_store_byte(0x401A6, 0xFF);
    machine.mem_store_byte(0x401A7, 0xFF);
    machine.mem_store_byte(0x401A8, 0xFF);
    machine.mem_store_byte(0x401A9, 0xFF);
    machine.mem_store_byte(0x10FFEE, 0xF4);
    machine.mem_store_byte(0x10FFEF, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x22A15415);
    EXPECT_EQ(cpu.get_ebx(), 0xF0868A8F);
    EXPECT_EQ(cpu.get_ecx(), 0x60BE8753);
    EXPECT_EQ(cpu.get_edx(), 0x33F24D5E);
    EXPECT_EQ(cpu.get_esi(), 0x0E94F5AF);
    EXPECT_EQ(cpu.get_edi(), 0xF79BF7F2);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x00005AC2);
    EXPECT_EQ(cpu.get_es(), 0x0000C11D);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x0000305C);
    EXPECT_EQ(cpu.get_ss(), 0x00003A8B);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C46);

    // Final RAM entries
}

//
// ret 695h
//
TEST_F(Test386, ret_695h_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB1E84357);
    cpu.set_ebx(0x59429438);
    cpu.set_ecx(0x6153F17C);
    cpu.set_edx(0x7CFCEA92);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0x80000000);
    cpu.set_ebp(0xB0475D1A);
    cpu.set_esp(0x0000A234);
    cpu.set_cs(0x00007272);
    cpu.set_ds(0x0000FAB5);
    cpu.set_es(0x00004C5E);
    cpu.set_fs(0x00007FFF);
    cpu.set_gs(0x0000DDE2);
    cpu.set_ss(0x00008472);
    cpu.set_eip(0x0000A8E8);
    cpu.set_eflags(0xFFFC08C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7D008, 0xC2);
    machine.mem_store_byte(0x7D009, 0x95);
    machine.mem_store_byte(0x7D00A, 0x06);
    machine.mem_store_byte(0x7D00B, 0xF4);
    machine.mem_store_byte(0x7D00C, 0xFF);
    machine.mem_store_byte(0x7D00D, 0xFF);
    machine.mem_store_byte(0x7D00E, 0xFF);
    machine.mem_store_byte(0x7D00F, 0xFF);
    machine.mem_store_byte(0x8E954, 0xFF);
    machine.mem_store_byte(0x8E955, 0xFF);
    machine.mem_store_byte(0x8271E, 0xF4);
    machine.mem_store_byte(0x8271F, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xB1E84357);
    EXPECT_EQ(cpu.get_ebx(), 0x59429438);
    EXPECT_EQ(cpu.get_ecx(), 0x6153F17C);
    EXPECT_EQ(cpu.get_edx(), 0x7CFCEA92);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0x80000000);
    EXPECT_EQ(cpu.get_ebp(), 0xB0475D1A);
    EXPECT_EQ(cpu.get_esp(), 0x0000A8CB);
    EXPECT_EQ(cpu.get_cs(), 0x00007272);
    EXPECT_EQ(cpu.get_ds(), 0x0000FAB5);
    EXPECT_EQ(cpu.get_es(), 0x00004C5E);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000DDE2);
    EXPECT_EQ(cpu.get_ss(), 0x00008472);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C6);

    // Final RAM entries
}

//
// ret
//
TEST_F(Test386, ret_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x04C72895);
    cpu.set_ebx(0x13DB7430);
    cpu.set_ecx(0xC7FD6C73);
    cpu.set_edx(0x0C0DA812);
    cpu.set_esi(0x44C4FB2A);
    cpu.set_edi(0x00000001);
    cpu.set_ebp(0x1CB0582B);
    cpu.set_esp(0x00003424);
    cpu.set_cs(0x0000BDBC);
    cpu.set_ds(0x0000FD8A);
    cpu.set_es(0x00004508);
    cpu.set_fs(0x00006774);
    cpu.set_gs(0x0000C692);
    cpu.set_ss(0x0000D4E5);
    cpu.set_eip(0x000033A8);
    cpu.set_eflags(0xFFFC0813);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC0F68, 0xC3);
    machine.mem_store_byte(0xC0F69, 0xF4);
    machine.mem_store_byte(0xC0F6A, 0xFF);
    machine.mem_store_byte(0xC0F6B, 0xFF);
    machine.mem_store_byte(0xC0F6C, 0xFF);
    machine.mem_store_byte(0xC0F6D, 0xFF);
    machine.mem_store_byte(0xC0F6E, 0xFF);
    machine.mem_store_byte(0xC0F6F, 0xFF);
    machine.mem_store_byte(0xD8274, 0xFF);
    machine.mem_store_byte(0xD8275, 0xFF);
    machine.mem_store_byte(0xCDBBE, 0xF4);
    machine.mem_store_byte(0xCDBBF, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x04C72895);
    EXPECT_EQ(cpu.get_ebx(), 0x13DB7430);
    EXPECT_EQ(cpu.get_ecx(), 0xC7FD6C73);
    EXPECT_EQ(cpu.get_edx(), 0x0C0DA812);
    EXPECT_EQ(cpu.get_esi(), 0x44C4FB2A);
    EXPECT_EQ(cpu.get_edi(), 0x00000001);
    EXPECT_EQ(cpu.get_ebp(), 0x1CB0582B);
    EXPECT_EQ(cpu.get_esp(), 0x00003426);
    EXPECT_EQ(cpu.get_cs(), 0x0000BDBC);
    EXPECT_EQ(cpu.get_ds(), 0x0000FD8A);
    EXPECT_EQ(cpu.get_es(), 0x00004508);
    EXPECT_EQ(cpu.get_fs(), 0x00006774);
    EXPECT_EQ(cpu.get_gs(), 0x0000C692);
    EXPECT_EQ(cpu.get_ss(), 0x0000D4E5);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0813);

    // Final RAM entries
}

//
// retf 1DB5h
//
TEST_F(Test386, retf_1DB5h_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFB8E5AC);
    cpu.set_ebx(0x00000000);
    cpu.set_ecx(0x39A45AE6);
    cpu.set_edx(0x45308B71);
    cpu.set_esi(0x00664F53);
    cpu.set_edi(0x251831CB);
    cpu.set_ebp(0x00FF0000);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000CE78);
    cpu.set_ds(0x000002B3);
    cpu.set_es(0x0000DBB7);
    cpu.set_fs(0x0000DABD);
    cpu.set_gs(0x0000283B);
    cpu.set_ss(0x000072DE);
    cpu.set_eip(0x00006170);
    cpu.set_eflags(0xFFFC00C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD48F0, 0xCA);
    machine.mem_store_byte(0xD48F1, 0xB5);
    machine.mem_store_byte(0xD48F2, 0x1D);
    machine.mem_store_byte(0xD48F3, 0xF4);
    machine.mem_store_byte(0xD48F4, 0xFF);
    machine.mem_store_byte(0xD48F5, 0xFF);
    machine.mem_store_byte(0xD48F6, 0xFF);
    machine.mem_store_byte(0xD48F7, 0xFF);
    machine.mem_store_byte(0x72DE8, 0xFF);
    machine.mem_store_byte(0x72DE9, 0xFF);
    machine.mem_store_byte(0x72DEA, 0xFF);
    machine.mem_store_byte(0x72DEB, 0xFF);
    machine.mem_store_byte(0x10FFEE, 0xF4);
    machine.mem_store_byte(0x10FFEF, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFB8E5AC);
    EXPECT_EQ(cpu.get_ebx(), 0x00000000);
    EXPECT_EQ(cpu.get_ecx(), 0x39A45AE6);
    EXPECT_EQ(cpu.get_edx(), 0x45308B71);
    EXPECT_EQ(cpu.get_esi(), 0x00664F53);
    EXPECT_EQ(cpu.get_edi(), 0x251831CB);
    EXPECT_EQ(cpu.get_ebp(), 0x00FF0000);
    EXPECT_EQ(cpu.get_esp(), 0x00001DC1);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x000002B3);
    EXPECT_EQ(cpu.get_es(), 0x0000DBB7);
    EXPECT_EQ(cpu.get_fs(), 0x0000DABD);
    EXPECT_EQ(cpu.get_gs(), 0x0000283B);
    EXPECT_EQ(cpu.get_ss(), 0x000072DE);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C6);

    // Final RAM entries
}

//
// retf
//
TEST_F(Test386, retf_batch33)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD2B5E066);
    cpu.set_ebx(0xA0D2DE29);
    cpu.set_ecx(0x06051307);
    cpu.set_edx(0x5E2B52BA);
    cpu.set_esi(0x0C901F1A);
    cpu.set_edi(0x7DFA2403);
    cpu.set_ebp(0x1ED617B6);
    cpu.set_esp(0x0000C0D3);
    cpu.set_cs(0x00004B4E);
    cpu.set_ds(0x0000396C);
    cpu.set_es(0x00003F92);
    cpu.set_fs(0x00004010);
    cpu.set_gs(0x00000190);
    cpu.set_ss(0x00007562);
    cpu.set_eip(0x00008A20);
    cpu.set_eflags(0xFFFC0847);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x53F00, 0xCB);
    machine.mem_store_byte(0x53F01, 0xF4);
    machine.mem_store_byte(0x53F02, 0xFF);
    machine.mem_store_byte(0x53F03, 0xFF);
    machine.mem_store_byte(0x53F04, 0xFF);
    machine.mem_store_byte(0x53F05, 0xFF);
    machine.mem_store_byte(0x53F06, 0xFF);
    machine.mem_store_byte(0x53F07, 0xFF);
    machine.mem_store_byte(0x816F4, 0xFF);
    machine.mem_store_byte(0x816F3, 0xFF);
    machine.mem_store_byte(0x816F5, 0xFF);
    machine.mem_store_byte(0x816F6, 0xFF);
    machine.mem_store_byte(0x10FFEE, 0xF4);
    machine.mem_store_byte(0x10FFEF, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD2B5E066);
    EXPECT_EQ(cpu.get_ebx(), 0xA0D2DE29);
    EXPECT_EQ(cpu.get_ecx(), 0x06051307);
    EXPECT_EQ(cpu.get_edx(), 0x5E2B52BA);
    EXPECT_EQ(cpu.get_esi(), 0x0C901F1A);
    EXPECT_EQ(cpu.get_edi(), 0x7DFA2403);
    EXPECT_EQ(cpu.get_ebp(), 0x1ED617B6);
    EXPECT_EQ(cpu.get_esp(), 0x0000C0D7);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000396C);
    EXPECT_EQ(cpu.get_es(), 0x00003F92);
    EXPECT_EQ(cpu.get_fs(), 0x00004010);
    EXPECT_EQ(cpu.get_gs(), 0x00000190);
    EXPECT_EQ(cpu.get_ss(), 0x00007562);
    EXPECT_EQ(cpu.get_eip(), 0x00010000);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0847);

    // Final RAM entries
}
