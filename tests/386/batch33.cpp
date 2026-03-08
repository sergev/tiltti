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
    EXPECT_EQ(memory.load8(0x9FC46), 0x93);
    EXPECT_EQ(memory.load8(0x9FC47), 0x04);
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
