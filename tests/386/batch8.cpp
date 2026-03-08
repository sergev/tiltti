#include "test386.h"

//
// a32 scasd
//
TEST_F(Test386, a32_scasd_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00001CDB);
    cpu.set_ebx(0xA9BCC431);
    cpu.set_ecx(0xA2A8108F);
    cpu.set_edx(0x748B7A5F);
    cpu.set_esi(0x16D989B5);
    cpu.set_edi(0x0000FFFF);
    cpu.set_ebp(0xEA75A8BF);
    cpu.set_esp(0x000011FA);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000041F);
    cpu.set_es(0x00001E2D);
    cpu.set_fs(0x0000F0EE);
    cpu.set_gs(0x0000F372);
    cpu.set_ss(0x00008000);
    cpu.set_eip(0x0000CBA8);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10CB98, 0x67);
    machine.mem_store_byte(0x10CB99, 0x66);
    machine.mem_store_byte(0x10CB9A, 0xAF);
    machine.mem_store_byte(0x10CB9B, 0xF4);
    machine.mem_store_byte(0x10CB9C, 0x13);
    machine.mem_store_byte(0x10CB9D, 0x77);
    machine.mem_store_byte(0x10CB9E, 0x35);
    machine.mem_store_byte(0x10CB9F, 0x84);
    machine.mem_store_byte(0x10CBA0, 0x9B);
    machine.mem_store_byte(0x10CBA1, 0xEC);
    machine.mem_store_byte(0x10CBA2, 0xEA);
    machine.mem_store_byte(0x10CBA3, 0x7A);
    machine.mem_store_byte(0x10CBA4, 0x01);
    machine.mem_store_byte(0x10CBA5, 0x4D);
    machine.mem_store_byte(0x10CBA6, 0x6A);
    machine.mem_store_byte(0x10CBA7, 0x3A);
    machine.mem_store_byte(0x10CBA8, 0x2D);
    machine.mem_store_byte(0x10CBA9, 0x50);
    machine.mem_store_byte(0x10CBAA, 0x6A);
    machine.mem_store_byte(0x10CBAB, 0x67);
    machine.mem_store_byte(0x00034, 0x55);
    machine.mem_store_byte(0x00035, 0x34);
    machine.mem_store_byte(0x00036, 0x1A);
    machine.mem_store_byte(0x00037, 0x86);
    machine.mem_store_byte(0x895F4, 0x37);
    machine.mem_store_byte(0x895F5, 0xF4);
    machine.mem_store_byte(0x895F6, 0xB4);
    machine.mem_store_byte(0x895F7, 0xF4);
    machine.mem_store_byte(0x895F8, 0xF6);
    machine.mem_store_byte(0x895F9, 0xF4);
    machine.mem_store_byte(0x895FA, 0xFC);
    machine.mem_store_byte(0x895FB, 0xF4);
    machine.mem_store_byte(0x895FC, 0x2B);
    machine.mem_store_byte(0x895FD, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001CDB);
    EXPECT_EQ(cpu.get_ebx(), 0xA9BCC431);
    EXPECT_EQ(cpu.get_ecx(), 0xA2A8108F);
    EXPECT_EQ(cpu.get_edx(), 0x748B7A5F);
    EXPECT_EQ(cpu.get_esi(), 0x16D989B5);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xEA75A8BF);
    EXPECT_EQ(cpu.get_esp(), 0x000011F4);
    EXPECT_EQ(cpu.get_cs(), 0x0000861A);
    EXPECT_EQ(cpu.get_ds(), 0x0000041F);
    EXPECT_EQ(cpu.get_es(), 0x00001E2D);
    EXPECT_EQ(cpu.get_fs(), 0x0000F0EE);
    EXPECT_EQ(cpu.get_gs(), 0x0000F372);
    EXPECT_EQ(cpu.get_ss(), 0x00008000);
    EXPECT_EQ(cpu.get_eip(), 0x00003456);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x811F8), 0xD6);
    EXPECT_EQ(memory.load8(0x811F9), 0x0C);
    EXPECT_EQ(memory.load8(0x811F6), 0xFF);
    EXPECT_EQ(memory.load8(0x811F7), 0xFF);
    EXPECT_EQ(memory.load8(0x811F4), 0xA8);
    EXPECT_EQ(memory.load8(0x811F5), 0xCB);
}

//
// a32 scasw
//
TEST_F(Test386, a32_scasw_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00001CDB);
    cpu.set_ebx(0xA9BCC431);
    cpu.set_ecx(0xA2A8108F);
    cpu.set_edx(0x748B7A5F);
    cpu.set_esi(0x16D989B5);
    cpu.set_edi(0x0000FFFF);
    cpu.set_ebp(0xEA75A8BF);
    cpu.set_esp(0x000011FA);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000041F);
    cpu.set_es(0x00001E2D);
    cpu.set_fs(0x0000F0EE);
    cpu.set_gs(0x0000F372);
    cpu.set_ss(0x00008000);
    cpu.set_eip(0x0000CBA8);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10CB98, 0x67);
    machine.mem_store_byte(0x10CB99, 0xAF);
    machine.mem_store_byte(0x10CB9A, 0xF4);
    machine.mem_store_byte(0x10CB9B, 0xF4);
    machine.mem_store_byte(0x10CB9C, 0x13);
    machine.mem_store_byte(0x10CB9D, 0x77);
    machine.mem_store_byte(0x10CB9E, 0x35);
    machine.mem_store_byte(0x10CB9F, 0x84);
    machine.mem_store_byte(0x10CBA0, 0x9B);
    machine.mem_store_byte(0x10CBA1, 0xEC);
    machine.mem_store_byte(0x10CBA2, 0xEA);
    machine.mem_store_byte(0x10CBA3, 0x7A);
    machine.mem_store_byte(0x10CBA4, 0x01);
    machine.mem_store_byte(0x10CBA5, 0x4D);
    machine.mem_store_byte(0x10CBA6, 0x6A);
    machine.mem_store_byte(0x10CBA7, 0x3A);
    machine.mem_store_byte(0x00034, 0x55);
    machine.mem_store_byte(0x00035, 0x34);
    machine.mem_store_byte(0x00036, 0x1A);
    machine.mem_store_byte(0x00037, 0x86);
    machine.mem_store_byte(0x895F4, 0x37);
    machine.mem_store_byte(0x895F5, 0xF4);
    machine.mem_store_byte(0x895F6, 0xB4);
    machine.mem_store_byte(0x895F7, 0xF4);
    machine.mem_store_byte(0x895F8, 0xF6);
    machine.mem_store_byte(0x895F9, 0xF4);
    machine.mem_store_byte(0x895FA, 0xFC);
    machine.mem_store_byte(0x895FB, 0xF4);
    machine.mem_store_byte(0x895FC, 0x2B);
    machine.mem_store_byte(0x895FD, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001CDB);
    EXPECT_EQ(cpu.get_ebx(), 0xA9BCC431);
    EXPECT_EQ(cpu.get_ecx(), 0xA2A8108F);
    EXPECT_EQ(cpu.get_edx(), 0x748B7A5F);
    EXPECT_EQ(cpu.get_esi(), 0x16D989B5);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xEA75A8BF);
    EXPECT_EQ(cpu.get_esp(), 0x000011F4);
    EXPECT_EQ(cpu.get_cs(), 0x0000861A);
    EXPECT_EQ(cpu.get_ds(), 0x0000041F);
    EXPECT_EQ(cpu.get_es(), 0x00001E2D);
    EXPECT_EQ(cpu.get_fs(), 0x0000F0EE);
    EXPECT_EQ(cpu.get_gs(), 0x0000F372);
    EXPECT_EQ(cpu.get_ss(), 0x00008000);
    EXPECT_EQ(cpu.get_eip(), 0x00003456);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x811F8), 0xD6);
    EXPECT_EQ(memory.load8(0x811F9), 0x0C);
    EXPECT_EQ(memory.load8(0x811F6), 0xFF);
    EXPECT_EQ(memory.load8(0x811F7), 0xFF);
    EXPECT_EQ(memory.load8(0x811F4), 0xA8);
    EXPECT_EQ(memory.load8(0x811F5), 0xCB);
}

//
// aaa
//
TEST_F(Test386, aaa_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA8851FFF);
    cpu.set_ebx(0xC1F47E3A);
    cpu.set_ecx(0x04C01399);
    cpu.set_edx(0xE3310091);
    cpu.set_esi(0xB70FFEB6);
    cpu.set_edi(0xE4266DCF);
    cpu.set_ebp(0xF39EC47C);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000081);
    cpu.set_ds(0x00007C9B);
    cpu.set_es(0x00000001);
    cpu.set_fs(0x0000CAD0);
    cpu.set_gs(0x00000001);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x00005EE8);
    cpu.set_eflags(0xFFFC0002);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x066F8, 0x37);
    machine.mem_store_byte(0x066F9, 0xF4);
    machine.mem_store_byte(0x066FA, 0x7B);
    machine.mem_store_byte(0x066FB, 0x41);
    machine.mem_store_byte(0x066FC, 0x09);
    machine.mem_store_byte(0x066FD, 0x77);
    machine.mem_store_byte(0x066FE, 0x2C);
    machine.mem_store_byte(0x066FF, 0x60);
    machine.mem_store_byte(0x06700, 0x20);
    machine.mem_store_byte(0x06701, 0x90);
    machine.mem_store_byte(0x06702, 0x98);
    machine.mem_store_byte(0x06703, 0xDB);
    machine.mem_store_byte(0x06704, 0x0F);
    machine.mem_store_byte(0x06705, 0xBE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA8852105);
    EXPECT_EQ(cpu.get_ebx(), 0xC1F47E3A);
    EXPECT_EQ(cpu.get_ecx(), 0x04C01399);
    EXPECT_EQ(cpu.get_edx(), 0xE3310091);
    EXPECT_EQ(cpu.get_esi(), 0xB70FFEB6);
    EXPECT_EQ(cpu.get_edi(), 0xE4266DCF);
    EXPECT_EQ(cpu.get_ebp(), 0xF39EC47C);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00000081);
    EXPECT_EQ(cpu.get_ds(), 0x00007C9B);
    EXPECT_EQ(cpu.get_es(), 0x00000001);
    EXPECT_EQ(cpu.get_fs(), 0x0000CAD0);
    EXPECT_EQ(cpu.get_gs(), 0x00000001);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x00005EEA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0017);

    // Final RAM entries
}

//
// iretd
//
TEST_F(Test386, iretd_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xC8944437);
    cpu.set_ebx(0x77DBDEAF);
    cpu.set_ecx(0xC9D00E0B);
    cpu.set_edx(0x199A2AB3);
    cpu.set_esi(0x23D8BAF7);
    cpu.set_edi(0x27FE35CA);
    cpu.set_ebp(0xA7081651);
    cpu.set_esp(0x0000FFFC);
    cpu.set_cs(0x00002E60);
    cpu.set_ds(0x0000B32E);
    cpu.set_es(0x0000E5A2);
    cpu.set_fs(0x00002D67);
    cpu.set_gs(0x000000C0);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000DD08);
    cpu.set_eflags(0xFFFC04C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3C308, 0x66);
    machine.mem_store_byte(0x3C309, 0xCF);
    machine.mem_store_byte(0x3C30A, 0xF4);
    machine.mem_store_byte(0x3C30B, 0xFF);
    machine.mem_store_byte(0x3C30C, 0xFF);
    machine.mem_store_byte(0x3C30D, 0xFF);
    machine.mem_store_byte(0x3C30E, 0xFF);
    machine.mem_store_byte(0x3C30F, 0xFF);
    machine.mem_store_byte(0x0FFFC, 0xFF);
    machine.mem_store_byte(0x0FFFD, 0xFF);
    machine.mem_store_byte(0x0FFFE, 0xFF);
    machine.mem_store_byte(0x0FFFF, 0xFF);
    machine.mem_store_byte(0x00000, 0xB2);
    machine.mem_store_byte(0x00001, 0x17);
    machine.mem_store_byte(0x00002, 0x86);
    machine.mem_store_byte(0x00003, 0xAE);
    machine.mem_store_byte(0x00004, 0x86);
    machine.mem_store_byte(0x00005, 0x04);
    machine.mem_store_byte(0x00006, 0x00);
    machine.mem_store_byte(0x00007, 0x00);
    machine.mem_store_byte(0x00034, 0xCF);
    machine.mem_store_byte(0x00035, 0x63);
    machine.mem_store_byte(0x00036, 0x76);
    machine.mem_store_byte(0x00037, 0x96);
    machine.mem_store_byte(0x9CB2E, 0xF4);
    machine.mem_store_byte(0x9CB2F, 0xF4);
    machine.mem_store_byte(0x9CB30, 0xFF);
    machine.mem_store_byte(0x9CB31, 0xF4);
    machine.mem_store_byte(0x9CB32, 0xFF);
    machine.mem_store_byte(0x9CB33, 0xF4);
    machine.mem_store_byte(0x9CB34, 0xFF);
    machine.mem_store_byte(0x9CB35, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xC8944437);
    EXPECT_EQ(cpu.get_ebx(), 0x77DBDEAF);
    EXPECT_EQ(cpu.get_ecx(), 0xC9D00E0B);
    EXPECT_EQ(cpu.get_edx(), 0x199A2AB3);
    EXPECT_EQ(cpu.get_esi(), 0x23D8BAF7);
    EXPECT_EQ(cpu.get_edi(), 0x27FE35CA);
    EXPECT_EQ(cpu.get_ebp(), 0xA7081651);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF6);
    EXPECT_EQ(cpu.get_cs(), 0x00009676);
    EXPECT_EQ(cpu.get_ds(), 0x0000B32E);
    EXPECT_EQ(cpu.get_es(), 0x0000E5A2);
    EXPECT_EQ(cpu.get_fs(), 0x00002D67);
    EXPECT_EQ(cpu.get_gs(), 0x000000C0);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x000063D0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0FFFA), 0xC6);
    EXPECT_EQ(memory.load8(0x0FFFB), 0x04);
    EXPECT_EQ(memory.load8(0x0FFF8), 0x60);
    EXPECT_EQ(memory.load8(0x0FFF9), 0x2E);
    EXPECT_EQ(memory.load8(0x0FFF6), 0x08);
    EXPECT_EQ(memory.load8(0x0FFF7), 0xDD);
}

//
// movsd
//
TEST_F(Test386, movsd_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00C4755F);
    cpu.set_ebx(0xAD1CF84F);
    cpu.set_ecx(0x294DC637);
    cpu.set_edx(0xB7FD1D82);
    cpu.set_esi(0xDAAF2713);
    cpu.set_edi(0xFFFFFFFD);
    cpu.set_ebp(0x8D66301A);
    cpu.set_esp(0x00002786);
    cpu.set_cs(0x0000F37C);
    cpu.set_ds(0x0000213E);
    cpu.set_es(0x00000001);
    cpu.set_fs(0x00000016);
    cpu.set_gs(0x00001808);
    cpu.set_ss(0x0000DCB1);
    cpu.set_eip(0x0000F358);
    cpu.set_eflags(0xFFFC04D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x102B18, 0x66);
    machine.mem_store_byte(0x102B19, 0xA5);
    machine.mem_store_byte(0x102B1A, 0xF4);
    machine.mem_store_byte(0x102B1B, 0xF8);
    machine.mem_store_byte(0x102B1C, 0xB9);
    machine.mem_store_byte(0x102B1D, 0xCA);
    machine.mem_store_byte(0x102B1E, 0xB4);
    machine.mem_store_byte(0x102B1F, 0x64);
    machine.mem_store_byte(0x102B20, 0x4B);
    machine.mem_store_byte(0x102B21, 0xEE);
    machine.mem_store_byte(0x23AF4, 0xB0);
    machine.mem_store_byte(0x23AF5, 0x2B);
    machine.mem_store_byte(0x23AF6, 0x10);
    machine.mem_store_byte(0x23AF3, 0x95);
    machine.mem_store_byte(0x102B22, 0xFC);
    machine.mem_store_byte(0x102B23, 0xB6);
    machine.mem_store_byte(0x102B24, 0x3D);
    machine.mem_store_byte(0x102B25, 0x5F);
    machine.mem_store_byte(0x102B26, 0xB3);
    machine.mem_store_byte(0x102B27, 0xAC);
    machine.mem_store_byte(0x00034, 0xA0);
    machine.mem_store_byte(0x00035, 0xC9);
    machine.mem_store_byte(0x00036, 0xB1);
    machine.mem_store_byte(0x00037, 0x90);
    machine.mem_store_byte(0x9D4B0, 0xF4);
    machine.mem_store_byte(0x9D4B1, 0xB5);
    machine.mem_store_byte(0x9D4B2, 0xF4);
    machine.mem_store_byte(0x9D4B3, 0xB3);
    machine.mem_store_byte(0x9D4B4, 0xF4);
    machine.mem_store_byte(0x9D4B5, 0xE5);
    machine.mem_store_byte(0x9D4B6, 0xF4);
    machine.mem_store_byte(0x9D4B7, 0x75);
    machine.mem_store_byte(0x9D4B8, 0xF4);
    machine.mem_store_byte(0x9D4B9, 0x48);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00C4755F);
    EXPECT_EQ(cpu.get_ebx(), 0xAD1CF84F);
    EXPECT_EQ(cpu.get_ecx(), 0x294DC637);
    EXPECT_EQ(cpu.get_edx(), 0xB7FD1D82);
    EXPECT_EQ(cpu.get_esi(), 0xDAAF2713);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFD);
    EXPECT_EQ(cpu.get_ebp(), 0x8D66301A);
    EXPECT_EQ(cpu.get_esp(), 0x00002780);
    EXPECT_EQ(cpu.get_cs(), 0x000090B1);
    EXPECT_EQ(cpu.get_ds(), 0x0000213E);
    EXPECT_EQ(cpu.get_es(), 0x00000001);
    EXPECT_EQ(cpu.get_fs(), 0x00000016);
    EXPECT_EQ(cpu.get_gs(), 0x00001808);
    EXPECT_EQ(cpu.get_ss(), 0x0000DCB1);
    EXPECT_EQ(cpu.get_eip(), 0x0000C9A1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04D2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDF294), 0xD2);
    EXPECT_EQ(memory.load8(0xDF295), 0x04);
    EXPECT_EQ(memory.load8(0xDF292), 0x7C);
    EXPECT_EQ(memory.load8(0xDF293), 0xF3);
    EXPECT_EQ(memory.load8(0xDF290), 0x58);
    EXPECT_EQ(memory.load8(0xDF291), 0xF3);
}

//
// pop dword [ds:ecx-58EFh]
//
TEST_F(Test386, pop_dword_ds_ecx_58EFh_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF12BEA6E);
    cpu.set_ebx(0x00FF00FF);
    cpu.set_ecx(0x0000204E);
    cpu.set_edx(0x9D27D664);
    cpu.set_esi(0x95EA9D5E);
    cpu.set_edi(0x2A57F998);
    cpu.set_ebp(0x000003FF);
    cpu.set_esp(0x0000FBCD);
    cpu.set_cs(0x00000A76);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x0000E74C);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00003DDD);
    cpu.set_ss(0x000000D1);
    cpu.set_eip(0x0000E840);
    cpu.set_eflags(0xFFFC0493);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x18FA0, 0x66);
    machine.mem_store_byte(0x18FA1, 0x67);
    machine.mem_store_byte(0x18FA2, 0x8F);
    machine.mem_store_byte(0x18FA3, 0x81);
    machine.mem_store_byte(0x18FA4, 0x11);
    machine.mem_store_byte(0x18FA5, 0xA7);
    machine.mem_store_byte(0x18FA6, 0xFF);
    machine.mem_store_byte(0x18FA7, 0xFF);
    machine.mem_store_byte(0x18FA8, 0xF4);
    machine.mem_store_byte(0x18FA9, 0xA1);
    machine.mem_store_byte(0x18FAA, 0x29);
    machine.mem_store_byte(0x18FAB, 0xEF);
    machine.mem_store_byte(0x108E0, 0x2D);
    machine.mem_store_byte(0x108DD, 0x9F);
    machine.mem_store_byte(0x108DE, 0xBB);
    machine.mem_store_byte(0x108DF, 0x51);
    machine.mem_store_byte(0x18FAC, 0x4A);
    machine.mem_store_byte(0x18FAD, 0x2A);
    machine.mem_store_byte(0x18FAE, 0xFF);
    machine.mem_store_byte(0x18FAF, 0x7B);
    machine.mem_store_byte(0x18FB0, 0x2A);
    machine.mem_store_byte(0x18FB1, 0x8A);
    machine.mem_store_byte(0x18FB2, 0x76);
    machine.mem_store_byte(0x18FB3, 0xFF);
    machine.mem_store_byte(0x18FB4, 0x8D);
    machine.mem_store_byte(0x18FB5, 0x41);
    machine.mem_store_byte(0x18FB6, 0xD5);
    machine.mem_store_byte(0x18FB7, 0x50);
    machine.mem_store_byte(0x00034, 0x73);
    machine.mem_store_byte(0x00035, 0x6B);
    machine.mem_store_byte(0x00036, 0xE8);
    machine.mem_store_byte(0x00037, 0xC3);
    machine.mem_store_byte(0xCA9F2, 0x96);
    machine.mem_store_byte(0xCA9F3, 0xF4);
    machine.mem_store_byte(0xCA9F4, 0x40);
    machine.mem_store_byte(0xCA9F5, 0xF4);
    machine.mem_store_byte(0xCA9F6, 0x08);
    machine.mem_store_byte(0xCA9F7, 0xF4);
    machine.mem_store_byte(0xCA9F8, 0x36);
    machine.mem_store_byte(0xCA9F9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF12BEA6E);
    EXPECT_EQ(cpu.get_ebx(), 0x00FF00FF);
    EXPECT_EQ(cpu.get_ecx(), 0x0000204E);
    EXPECT_EQ(cpu.get_edx(), 0x9D27D664);
    EXPECT_EQ(cpu.get_esi(), 0x95EA9D5E);
    EXPECT_EQ(cpu.get_edi(), 0x2A57F998);
    EXPECT_EQ(cpu.get_ebp(), 0x000003FF);
    EXPECT_EQ(cpu.get_esp(), 0x0000FBC7);
    EXPECT_EQ(cpu.get_cs(), 0x0000C3E8);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x0000E74C);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00003DDD);
    EXPECT_EQ(cpu.get_ss(), 0x000000D1);
    EXPECT_EQ(cpu.get_eip(), 0x00006B74);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x108DC), 0x04);
    EXPECT_EQ(memory.load8(0x108DB), 0x93);
    EXPECT_EQ(memory.load8(0x108D9), 0x76);
    EXPECT_EQ(memory.load8(0x108DA), 0x0A);
    EXPECT_EQ(memory.load8(0x108D8), 0xE8);
    EXPECT_EQ(memory.load8(0x108D7), 0x40);
}

//
// pop word [ds:ecx-58EFh]
//
TEST_F(Test386, pop_word_ds_ecx_58EFh_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF12BEA6E);
    cpu.set_ebx(0x00FF00FF);
    cpu.set_ecx(0x0000204E);
    cpu.set_edx(0x9D27D664);
    cpu.set_esi(0x95EA9D5E);
    cpu.set_edi(0x2A57F998);
    cpu.set_ebp(0x000003FF);
    cpu.set_esp(0x0000FBCD);
    cpu.set_cs(0x00000A76);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x0000E74C);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00003DDD);
    cpu.set_ss(0x000000D1);
    cpu.set_eip(0x0000E840);
    cpu.set_eflags(0xFFFC0493);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x18FA0, 0x67);
    machine.mem_store_byte(0x18FA1, 0x8F);
    machine.mem_store_byte(0x18FA2, 0x81);
    machine.mem_store_byte(0x18FA3, 0x11);
    machine.mem_store_byte(0x18FA4, 0xA7);
    machine.mem_store_byte(0x18FA5, 0xFF);
    machine.mem_store_byte(0x18FA6, 0xFF);
    machine.mem_store_byte(0x18FA7, 0xF4);
    machine.mem_store_byte(0x18FA8, 0x03);
    machine.mem_store_byte(0x18FA9, 0xA1);
    machine.mem_store_byte(0x18FAA, 0x29);
    machine.mem_store_byte(0x18FAB, 0xEF);
    machine.mem_store_byte(0x108DD, 0x9F);
    machine.mem_store_byte(0x108DE, 0xBB);
    machine.mem_store_byte(0x18FAC, 0x4A);
    machine.mem_store_byte(0x18FAD, 0x2A);
    machine.mem_store_byte(0x18FAE, 0xFF);
    machine.mem_store_byte(0x18FAF, 0x7B);
    machine.mem_store_byte(0x18FB0, 0x2A);
    machine.mem_store_byte(0x18FB1, 0x8A);
    machine.mem_store_byte(0x18FB2, 0x76);
    machine.mem_store_byte(0x18FB3, 0xFF);
    machine.mem_store_byte(0x18FB4, 0x8D);
    machine.mem_store_byte(0x18FB5, 0x41);
    machine.mem_store_byte(0x18FB6, 0xD5);
    machine.mem_store_byte(0x18FB7, 0x50);
    machine.mem_store_byte(0x00034, 0x73);
    machine.mem_store_byte(0x00035, 0x6B);
    machine.mem_store_byte(0x00036, 0xE8);
    machine.mem_store_byte(0x00037, 0xC3);
    machine.mem_store_byte(0xCA9F2, 0x96);
    machine.mem_store_byte(0xCA9F3, 0xF4);
    machine.mem_store_byte(0xCA9F4, 0x40);
    machine.mem_store_byte(0xCA9F5, 0xF4);
    machine.mem_store_byte(0xCA9F6, 0x08);
    machine.mem_store_byte(0xCA9F7, 0xF4);
    machine.mem_store_byte(0xCA9F8, 0x36);
    machine.mem_store_byte(0xCA9F9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF12BEA6E);
    EXPECT_EQ(cpu.get_ebx(), 0x00FF00FF);
    EXPECT_EQ(cpu.get_ecx(), 0x0000204E);
    EXPECT_EQ(cpu.get_edx(), 0x9D27D664);
    EXPECT_EQ(cpu.get_esi(), 0x95EA9D5E);
    EXPECT_EQ(cpu.get_edi(), 0x2A57F998);
    EXPECT_EQ(cpu.get_ebp(), 0x000003FF);
    EXPECT_EQ(cpu.get_esp(), 0x0000FBC7);
    EXPECT_EQ(cpu.get_cs(), 0x0000C3E8);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x0000E74C);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00003DDD);
    EXPECT_EQ(cpu.get_ss(), 0x000000D1);
    EXPECT_EQ(cpu.get_eip(), 0x00006B74);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x108DC), 0x04);
    EXPECT_EQ(memory.load8(0x108DB), 0x93);
    EXPECT_EQ(memory.load8(0x108D9), 0x76);
    EXPECT_EQ(memory.load8(0x108DA), 0x0A);
    EXPECT_EQ(memory.load8(0x108D8), 0xE8);
    EXPECT_EQ(memory.load8(0x108D7), 0x40);
}

//
// scasd
//
TEST_F(Test386, scasd_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00001CDB);
    cpu.set_ebx(0xA9BCC431);
    cpu.set_ecx(0xA2A8108F);
    cpu.set_edx(0x748B7A5F);
    cpu.set_esi(0x16D989B5);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0xEA75A8BF);
    cpu.set_esp(0x000011FA);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000041F);
    cpu.set_es(0x00001E2D);
    cpu.set_fs(0x0000F0EE);
    cpu.set_gs(0x0000F372);
    cpu.set_ss(0x00008000);
    cpu.set_eip(0x0000CBA8);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10CB98, 0x66);
    machine.mem_store_byte(0x10CB99, 0xAF);
    machine.mem_store_byte(0x10CB9A, 0xF4);
    machine.mem_store_byte(0x10CB9B, 0xF4);
    machine.mem_store_byte(0x10CB9C, 0x13);
    machine.mem_store_byte(0x10CB9D, 0x77);
    machine.mem_store_byte(0x10CB9E, 0x35);
    machine.mem_store_byte(0x10CB9F, 0x84);
    machine.mem_store_byte(0x10CBA0, 0x9B);
    machine.mem_store_byte(0x10CBA1, 0xEC);
    machine.mem_store_byte(0x10CBA2, 0xEA);
    machine.mem_store_byte(0x10CBA3, 0x7A);
    machine.mem_store_byte(0x10CBA4, 0x01);
    machine.mem_store_byte(0x10CBA5, 0x4D);
    machine.mem_store_byte(0x10CBA6, 0x6A);
    machine.mem_store_byte(0x10CBA7, 0x3A);
    machine.mem_store_byte(0x00034, 0x55);
    machine.mem_store_byte(0x00035, 0x34);
    machine.mem_store_byte(0x00036, 0x1A);
    machine.mem_store_byte(0x00037, 0x86);
    machine.mem_store_byte(0x895F4, 0x37);
    machine.mem_store_byte(0x895F5, 0xF4);
    machine.mem_store_byte(0x895F6, 0xB4);
    machine.mem_store_byte(0x895F7, 0xF4);
    machine.mem_store_byte(0x895F8, 0xF6);
    machine.mem_store_byte(0x895F9, 0xF4);
    machine.mem_store_byte(0x895FA, 0xFC);
    machine.mem_store_byte(0x895FB, 0xF4);
    machine.mem_store_byte(0x895FC, 0x2B);
    machine.mem_store_byte(0x895FD, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001CDB);
    EXPECT_EQ(cpu.get_ebx(), 0xA9BCC431);
    EXPECT_EQ(cpu.get_ecx(), 0xA2A8108F);
    EXPECT_EQ(cpu.get_edx(), 0x748B7A5F);
    EXPECT_EQ(cpu.get_esi(), 0x16D989B5);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xEA75A8BF);
    EXPECT_EQ(cpu.get_esp(), 0x000011F4);
    EXPECT_EQ(cpu.get_cs(), 0x0000861A);
    EXPECT_EQ(cpu.get_ds(), 0x0000041F);
    EXPECT_EQ(cpu.get_es(), 0x00001E2D);
    EXPECT_EQ(cpu.get_fs(), 0x0000F0EE);
    EXPECT_EQ(cpu.get_gs(), 0x0000F372);
    EXPECT_EQ(cpu.get_ss(), 0x00008000);
    EXPECT_EQ(cpu.get_eip(), 0x00003456);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x811F8), 0xD6);
    EXPECT_EQ(memory.load8(0x811F9), 0x0C);
    EXPECT_EQ(memory.load8(0x811F6), 0xFF);
    EXPECT_EQ(memory.load8(0x811F7), 0xFF);
    EXPECT_EQ(memory.load8(0x811F4), 0xA8);
    EXPECT_EQ(memory.load8(0x811F5), 0xCB);
}

//
// scasw
//
TEST_F(Test386, scasw_batch8)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00001CDB);
    cpu.set_ebx(0xA9BCC431);
    cpu.set_ecx(0xA2A8108F);
    cpu.set_edx(0x748B7A5F);
    cpu.set_esi(0x16D989B5);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0xEA75A8BF);
    cpu.set_esp(0x000011FA);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000041F);
    cpu.set_es(0x00001E2D);
    cpu.set_fs(0x0000F0EE);
    cpu.set_gs(0x0000F372);
    cpu.set_ss(0x00008000);
    cpu.set_eip(0x0000CBA8);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10CB98, 0xAF);
    machine.mem_store_byte(0x10CB99, 0xF4);
    machine.mem_store_byte(0x10CB9A, 0xEB);
    machine.mem_store_byte(0x10CB9B, 0xF4);
    machine.mem_store_byte(0x10CB9C, 0x13);
    machine.mem_store_byte(0x10CB9D, 0x77);
    machine.mem_store_byte(0x10CB9E, 0x35);
    machine.mem_store_byte(0x10CB9F, 0x84);
    machine.mem_store_byte(0x10CBA0, 0x9B);
    machine.mem_store_byte(0x10CBA1, 0xEC);
    machine.mem_store_byte(0x00034, 0x55);
    machine.mem_store_byte(0x00035, 0x34);
    machine.mem_store_byte(0x00036, 0x1A);
    machine.mem_store_byte(0x00037, 0x86);
    machine.mem_store_byte(0x895F4, 0x37);
    machine.mem_store_byte(0x895F5, 0xF4);
    machine.mem_store_byte(0x895F6, 0xB4);
    machine.mem_store_byte(0x895F7, 0xF4);
    machine.mem_store_byte(0x895F8, 0xF6);
    machine.mem_store_byte(0x895F9, 0xF4);
    machine.mem_store_byte(0x895FA, 0xFC);
    machine.mem_store_byte(0x895FB, 0xF4);
    machine.mem_store_byte(0x895FC, 0x2B);
    machine.mem_store_byte(0x895FD, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001CDB);
    EXPECT_EQ(cpu.get_ebx(), 0xA9BCC431);
    EXPECT_EQ(cpu.get_ecx(), 0xA2A8108F);
    EXPECT_EQ(cpu.get_edx(), 0x748B7A5F);
    EXPECT_EQ(cpu.get_esi(), 0x16D989B5);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xEA75A8BF);
    EXPECT_EQ(cpu.get_esp(), 0x000011F4);
    EXPECT_EQ(cpu.get_cs(), 0x0000861A);
    EXPECT_EQ(cpu.get_ds(), 0x0000041F);
    EXPECT_EQ(cpu.get_es(), 0x00001E2D);
    EXPECT_EQ(cpu.get_fs(), 0x0000F0EE);
    EXPECT_EQ(cpu.get_gs(), 0x0000F372);
    EXPECT_EQ(cpu.get_ss(), 0x00008000);
    EXPECT_EQ(cpu.get_eip(), 0x00003456);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x811F8), 0xD6);
    EXPECT_EQ(memory.load8(0x811F9), 0x0C);
    EXPECT_EQ(memory.load8(0x811F6), 0xFF);
    EXPECT_EQ(memory.load8(0x811F7), 0xFF);
    EXPECT_EQ(memory.load8(0x811F4), 0xA8);
    EXPECT_EQ(memory.load8(0x811F5), 0xCB);
}
