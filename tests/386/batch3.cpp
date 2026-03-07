#include "test386.h"

//
// call FFE0h
//
TEST_F(Test386, call_FFE0h_batch3)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDCFAD28A);
    cpu.set_ebx(0x7E5C7E9D);
    cpu.set_ecx(0x41D1F5B1);
    cpu.set_edx(0x00E61883);
    cpu.set_esi(0x3EA9567B);
    cpu.set_edi(0x193C0CA0);
    cpu.set_ebp(0x4E131032);
    cpu.set_esp(0x00009B9E);
    cpu.set_cs(0x00002393);
    cpu.set_ds(0x00000020);
    cpu.set_es(0x00007942);
    cpu.set_fs(0x0000CD9E);
    cpu.set_gs(0x0000410E);
    cpu.set_ss(0x00000994);
    cpu.set_eip(0x00007D98);
    cpu.set_eflags(0xFFFC0046);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2B6C8, 0xE8);
    machine.mem_store_byte(0x2B6C9, 0x45);
    machine.mem_store_byte(0x2B6CA, 0x82);
    machine.mem_store_byte(0x2B6CB, 0xF4);
    machine.mem_store_byte(0x2B6CC, 0xEB);
    machine.mem_store_byte(0x2B6CD, 0xC4);
    machine.mem_store_byte(0x2B6CE, 0x47);
    machine.mem_store_byte(0x2B6CF, 0xE8);
    machine.mem_store_byte(0x33910, 0xF4);
    machine.mem_store_byte(0x33911, 0x58);
    machine.mem_store_byte(0x33912, 0x5E);
    machine.mem_store_byte(0x33913, 0xE2);
    machine.mem_store_byte(0x33914, 0xD6);
    machine.mem_store_byte(0x33915, 0x8F);
    machine.mem_store_byte(0x33916, 0xAC);
    machine.mem_store_byte(0x33917, 0x79);
    machine.mem_store_byte(0x33918, 0x7C);
    machine.mem_store_byte(0x33919, 0x79);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDCFAD28A);
    EXPECT_EQ(cpu.get_ebx(), 0x7E5C7E9D);
    EXPECT_EQ(cpu.get_ecx(), 0x41D1F5B1);
    EXPECT_EQ(cpu.get_edx(), 0x00E61883);
    EXPECT_EQ(cpu.get_esi(), 0x3EA9567B);
    EXPECT_EQ(cpu.get_edi(), 0x193C0CA0);
    EXPECT_EQ(cpu.get_ebp(), 0x4E131032);
    EXPECT_EQ(cpu.get_esp(), 0x00009B9C);
    EXPECT_EQ(cpu.get_cs(), 0x00002393);
    EXPECT_EQ(cpu.get_ds(), 0x00000020);
    EXPECT_EQ(cpu.get_es(), 0x00007942);
    EXPECT_EQ(cpu.get_fs(), 0x0000CD9E);
    EXPECT_EQ(cpu.get_gs(), 0x0000410E);
    EXPECT_EQ(cpu.get_ss(), 0x00000994);
    EXPECT_EQ(cpu.get_eip(), 0x0000FFE1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x134DC), 0x9B);
    EXPECT_EQ(memory.load8(0x134DD), 0x7D);
}

//
// rcr word [ds:edx],cl
//
TEST_F(Test386, rcr_word_ds_edx_cl_batch3)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x6A95DFBB);
    cpu.set_ebx(0xD4BA12C0);
    cpu.set_ecx(0xFA53A011);
    cpu.set_edx(0x00000001);
    cpu.set_esi(0xFE264585);
    cpu.set_edi(0xFB30FFE5);
    cpu.set_ebp(0x08B99D3D);
    cpu.set_esp(0x00008CD4);
    cpu.set_cs(0x00005762);
    cpu.set_ds(0x000049BE);
    cpu.set_es(0x0000FFF4);
    cpu.set_fs(0x0000BD43);
    cpu.set_gs(0x000083D0);
    cpu.set_ss(0x0000777A);
    cpu.set_eip(0x0000DF70);
    cpu.set_eflags(0xFFFC04D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x65590, 0x67);
    machine.mem_store_byte(0x65591, 0xD3);
    machine.mem_store_byte(0x65592, 0x1A);
    machine.mem_store_byte(0x65593, 0xF4);
    machine.mem_store_byte(0x65594, 0xAE);
    machine.mem_store_byte(0x65595, 0x28);
    machine.mem_store_byte(0x65596, 0xE2);
    machine.mem_store_byte(0x65597, 0xF9);
    machine.mem_store_byte(0x65598, 0x6B);
    machine.mem_store_byte(0x65599, 0x43);
    machine.mem_store_byte(0x49BE1, 0x84);
    machine.mem_store_byte(0x49BE2, 0x62);
    machine.mem_store_byte(0x6559A, 0x55);
    machine.mem_store_byte(0x6559B, 0xD7);
    machine.mem_store_byte(0x6559C, 0xC8);
    machine.mem_store_byte(0x6559D, 0x48);
    machine.mem_store_byte(0x6559E, 0xB2);
    machine.mem_store_byte(0x6559F, 0x22);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x6A95DFBB);
    EXPECT_EQ(cpu.get_ebx(), 0xD4BA12C0);
    EXPECT_EQ(cpu.get_ecx(), 0xFA53A011);
    EXPECT_EQ(cpu.get_edx(), 0x00000001);
    EXPECT_EQ(cpu.get_esi(), 0xFE264585);
    EXPECT_EQ(cpu.get_edi(), 0xFB30FFE5);
    EXPECT_EQ(cpu.get_ebp(), 0x08B99D3D);
    EXPECT_EQ(cpu.get_esp(), 0x00008CD4);
    EXPECT_EQ(cpu.get_cs(), 0x00005762);
    EXPECT_EQ(cpu.get_ds(), 0x000049BE);
    EXPECT_EQ(cpu.get_es(), 0x0000FFF4);
    EXPECT_EQ(cpu.get_fs(), 0x0000BD43);
    EXPECT_EQ(cpu.get_gs(), 0x000083D0);
    EXPECT_EQ(cpu.get_ss(), 0x0000777A);
    EXPECT_EQ(cpu.get_eip(), 0x0000DF74);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
}

//
// shrd [ss:ebp+1DFDh],ax,cl
//
TEST_F(Test386, shrd_ss_ebp_1DFDh_ax_cl_batch3)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB3F00ACD);
    cpu.set_ebx(0x86378199);
    cpu.set_ecx(0xFF9452C7);
    cpu.set_edx(0x88EFC327);
    cpu.set_esi(0x3F23ADF1);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x000007AE);
    cpu.set_esp(0x0000B7D2);
    cpu.set_cs(0x00007F64);
    cpu.set_ds(0x0000D603);
    cpu.set_es(0x00002224);
    cpu.set_fs(0x00004001);
    cpu.set_gs(0x0000D1A7);
    cpu.set_ss(0x00005E05);
    cpu.set_eip(0x00008828);
    cpu.set_eflags(0xFFFC0496);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x87E68, 0x67);
    machine.mem_store_byte(0x87E69, 0x0F);
    machine.mem_store_byte(0x87E6A, 0xAD);
    machine.mem_store_byte(0x87E6B, 0x84);
    machine.mem_store_byte(0x87E6C, 0x65);
    machine.mem_store_byte(0x87E6D, 0xFD);
    machine.mem_store_byte(0x87E6E, 0x1D);
    machine.mem_store_byte(0x87E6F, 0x00);
    machine.mem_store_byte(0x87E70, 0x00);
    machine.mem_store_byte(0x87E71, 0xF4);
    machine.mem_store_byte(0x87E72, 0x32);
    machine.mem_store_byte(0x87E73, 0x24);
    machine.mem_store_byte(0x87E74, 0xA3);
    machine.mem_store_byte(0x87E75, 0x8C);
    machine.mem_store_byte(0x87E76, 0x6E);
    machine.mem_store_byte(0x87E77, 0x8C);
    machine.mem_store_byte(0x60DA9, 0x4D);
    machine.mem_store_byte(0x60DAA, 0x63);
    machine.mem_store_byte(0x87E78, 0x95);
    machine.mem_store_byte(0x87E79, 0xB1);
    machine.mem_store_byte(0x87E7A, 0x6D);
    machine.mem_store_byte(0x87E7B, 0xC8);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xB3F00ACD);
    EXPECT_EQ(cpu.get_ebx(), 0x86378199);
    EXPECT_EQ(cpu.get_ecx(), 0xFF9452C7);
    EXPECT_EQ(cpu.get_edx(), 0x88EFC327);
    EXPECT_EQ(cpu.get_esi(), 0x3F23ADF1);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x000007AE);
    EXPECT_EQ(cpu.get_esp(), 0x0000B7D2);
    EXPECT_EQ(cpu.get_cs(), 0x00007F64);
    EXPECT_EQ(cpu.get_ds(), 0x0000D603);
    EXPECT_EQ(cpu.get_es(), 0x00002224);
    EXPECT_EQ(cpu.get_fs(), 0x00004001);
    EXPECT_EQ(cpu.get_gs(), 0x0000D1A7);
    EXPECT_EQ(cpu.get_ss(), 0x00005E05);
    EXPECT_EQ(cpu.get_eip(), 0x00008832);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C97);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x60DA9), 0xC6);
    EXPECT_EQ(memory.load8(0x60DAA), 0x9A);
}

//
// shrd [ss:ebp+1DFDh],eax,cl
//
TEST_F(Test386, shrd_ss_ebp_1DFDh_eax_cl_batch3)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB3F00ACD);
    cpu.set_ebx(0x86378199);
    cpu.set_ecx(0xFF9452C7);
    cpu.set_edx(0x88EFC327);
    cpu.set_esi(0x3F23ADF1);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0x000007AE);
    cpu.set_esp(0x0000B7D2);
    cpu.set_cs(0x00007F64);
    cpu.set_ds(0x0000D603);
    cpu.set_es(0x00002224);
    cpu.set_fs(0x00004001);
    cpu.set_gs(0x0000D1A7);
    cpu.set_ss(0x00005E05);
    cpu.set_eip(0x00008828);
    cpu.set_eflags(0xFFFC0496);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x87E68, 0x66);
    machine.mem_store_byte(0x87E69, 0x67);
    machine.mem_store_byte(0x87E6A, 0x0F);
    machine.mem_store_byte(0x87E6B, 0xAD);
    machine.mem_store_byte(0x87E6C, 0x84);
    machine.mem_store_byte(0x87E6D, 0x65);
    machine.mem_store_byte(0x87E6E, 0xFD);
    machine.mem_store_byte(0x87E6F, 0x1D);
    machine.mem_store_byte(0x87E70, 0x00);
    machine.mem_store_byte(0x87E71, 0x00);
    machine.mem_store_byte(0x87E72, 0xF4);
    machine.mem_store_byte(0x87E73, 0x24);
    machine.mem_store_byte(0x87E74, 0xA3);
    machine.mem_store_byte(0x87E75, 0x8C);
    machine.mem_store_byte(0x87E76, 0x6E);
    machine.mem_store_byte(0x87E77, 0x8C);
    machine.mem_store_byte(0x60DAC, 0x03);
    machine.mem_store_byte(0x60DA9, 0x4D);
    machine.mem_store_byte(0x60DAA, 0x63);
    machine.mem_store_byte(0x60DAB, 0x6E);
    machine.mem_store_byte(0x87E78, 0x95);
    machine.mem_store_byte(0x87E79, 0xB1);
    machine.mem_store_byte(0x87E7A, 0x6D);
    machine.mem_store_byte(0x87E7B, 0xC8);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xB3F00ACD);
    EXPECT_EQ(cpu.get_ebx(), 0x86378199);
    EXPECT_EQ(cpu.get_ecx(), 0xFF9452C7);
    EXPECT_EQ(cpu.get_edx(), 0x88EFC327);
    EXPECT_EQ(cpu.get_esi(), 0x3F23ADF1);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x000007AE);
    EXPECT_EQ(cpu.get_esp(), 0x0000B7D2);
    EXPECT_EQ(cpu.get_cs(), 0x00007F64);
    EXPECT_EQ(cpu.get_ds(), 0x0000D603);
    EXPECT_EQ(cpu.get_es(), 0x00002224);
    EXPECT_EQ(cpu.get_fs(), 0x00004001);
    EXPECT_EQ(cpu.get_gs(), 0x0000D1A7);
    EXPECT_EQ(cpu.get_ss(), 0x00005E05);
    EXPECT_EQ(cpu.get_eip(), 0x00008833);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C97);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x60DAC), 0x9A);
    EXPECT_EQ(memory.load8(0x60DA9), 0xC6);
    EXPECT_EQ(memory.load8(0x60DAA), 0xDC);
    EXPECT_EQ(memory.load8(0x60DAB), 0x06);
}
