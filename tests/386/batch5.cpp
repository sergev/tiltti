#include "test386.h"

//
// jcxz FD40h
//
TEST_F(Test386, jcxz_FD40h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFFFFF0F);
    cpu.set_ebx(0xF63172DC);
    cpu.set_ecx(0x80000000);
    cpu.set_edx(0xC461B8CD);
    cpu.set_esi(0x00446BB2);
    cpu.set_edi(0xAD5B8A02);
    cpu.set_ebp(0xFF067658);
    cpu.set_esp(0x00007FFE);
    cpu.set_cs(0x0000C3D6);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00005A5A);
    cpu.set_fs(0x0000AA55);
    cpu.set_gs(0x0000CB19);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000FCD0);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD3A30, 0xE3);
    machine.mem_store_byte(0xD3A31, 0x6E);
    machine.mem_store_byte(0xD3A32, 0xF4);
    machine.mem_store_byte(0xD3A33, 0x2D);
    machine.mem_store_byte(0xD3A34, 0x74);
    machine.mem_store_byte(0xD3A35, 0x30);
    machine.mem_store_byte(0xD3A36, 0x5F);
    machine.mem_store_byte(0xD3A37, 0x63);
    machine.mem_store_byte(0xD3A38, 0xBE);
    machine.mem_store_byte(0xD3A39, 0x44);
    machine.mem_store_byte(0xD3A3A, 0xD4);
    machine.mem_store_byte(0xD3A3B, 0xB8);
    machine.mem_store_byte(0xD3A3C, 0x34);
    machine.mem_store_byte(0xD3A3D, 0xF4);
    machine.mem_store_byte(0xD3AA0, 0xF4);
    machine.mem_store_byte(0xD3AA1, 0x66);
    machine.mem_store_byte(0xD3AA2, 0x0A);
    machine.mem_store_byte(0xD3AA3, 0xC2);
    machine.mem_store_byte(0xD3AA4, 0x05);
    machine.mem_store_byte(0xD3AA5, 0x16);
    machine.mem_store_byte(0xD3AA6, 0xA4);
    machine.mem_store_byte(0xD3AA7, 0xD3);
    machine.mem_store_byte(0xD3AA8, 0x39);
    machine.mem_store_byte(0xD3AA9, 0x2B);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFFFFF0F);
    EXPECT_EQ(cpu.get_ebx(), 0xF63172DC);
    EXPECT_EQ(cpu.get_ecx(), 0x80000000);
    EXPECT_EQ(cpu.get_edx(), 0xC461B8CD);
    EXPECT_EQ(cpu.get_esi(), 0x00446BB2);
    EXPECT_EQ(cpu.get_edi(), 0xAD5B8A02);
    EXPECT_EQ(cpu.get_ebp(), 0xFF067658);
    EXPECT_EQ(cpu.get_esp(), 0x00007FFE);
    EXPECT_EQ(cpu.get_cs(), 0x0000C3D6);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00005A5A);
    EXPECT_EQ(cpu.get_fs(), 0x0000AA55);
    EXPECT_EQ(cpu.get_gs(), 0x0000CB19);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000FD41);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
}

//
// jmp 0DB6h
//
TEST_F(Test386, jmp_0DB6h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA4902898);
    cpu.set_ebx(0x1CDA345C);
    cpu.set_ecx(0x4465A9A8);
    cpu.set_edx(0x7AA5CB23);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0x8CD7BBDF);
    cpu.set_ebp(0x0CE93E3E);
    cpu.set_esp(0x00005696);
    cpu.set_cs(0x00006FF7);
    cpu.set_ds(0x000012BC);
    cpu.set_es(0x0000592B);
    cpu.set_fs(0x00000B4D);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x00002793);
    cpu.set_eip(0x0000B3C8);
    cpu.set_eflags(0xFFFC0096);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7B338, 0xE9);
    machine.mem_store_byte(0x7B339, 0xEB);
    machine.mem_store_byte(0x7B33A, 0x59);
    machine.mem_store_byte(0x7B33B, 0xF4);
    machine.mem_store_byte(0x7B33C, 0x35);
    machine.mem_store_byte(0x7B33D, 0xE5);
    machine.mem_store_byte(0x7B33E, 0xBF);
    machine.mem_store_byte(0x7B33F, 0x1A);
    machine.mem_store_byte(0x70D26, 0xF4);
    machine.mem_store_byte(0x70D27, 0xA9);
    machine.mem_store_byte(0x70D28, 0x2F);
    machine.mem_store_byte(0x70D29, 0x4C);
    machine.mem_store_byte(0x70D2A, 0xC5);
    machine.mem_store_byte(0x70D2B, 0xD7);
    machine.mem_store_byte(0x70D2C, 0xEC);
    machine.mem_store_byte(0x70D2D, 0x3C);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA4902898);
    EXPECT_EQ(cpu.get_ebx(), 0x1CDA345C);
    EXPECT_EQ(cpu.get_ecx(), 0x4465A9A8);
    EXPECT_EQ(cpu.get_edx(), 0x7AA5CB23);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0x8CD7BBDF);
    EXPECT_EQ(cpu.get_ebp(), 0x0CE93E3E);
    EXPECT_EQ(cpu.get_esp(), 0x00005696);
    EXPECT_EQ(cpu.get_cs(), 0x00006FF7);
    EXPECT_EQ(cpu.get_ds(), 0x000012BC);
    EXPECT_EQ(cpu.get_es(), 0x0000592B);
    EXPECT_EQ(cpu.get_fs(), 0x00000B4D);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x00002793);
    EXPECT_EQ(cpu.get_eip(), 0x00000DB7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0096);

    // Final RAM entries
}

//
// o32 jcxz 0000FD41h
//
TEST_F(Test386, o32_jcxz_0000FD41h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFFFFF0F);
    cpu.set_ebx(0xF63172DC);
    cpu.set_ecx(0x80000000);
    cpu.set_edx(0xC461B8CD);
    cpu.set_esi(0x00446BB2);
    cpu.set_edi(0xAD5B8A02);
    cpu.set_ebp(0xFF067658);
    cpu.set_esp(0x00007FFE);
    cpu.set_cs(0x0000C3D6);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00005A5A);
    cpu.set_fs(0x0000AA55);
    cpu.set_gs(0x0000CB19);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000FCD0);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD3A30, 0x66);
    machine.mem_store_byte(0xD3A31, 0xE3);
    machine.mem_store_byte(0xD3A32, 0x6E);
    machine.mem_store_byte(0xD3A33, 0xF4);
    machine.mem_store_byte(0xD3A34, 0x74);
    machine.mem_store_byte(0xD3A35, 0x30);
    machine.mem_store_byte(0xD3A36, 0x5F);
    machine.mem_store_byte(0xD3A37, 0x63);
    machine.mem_store_byte(0xD3A38, 0xBE);
    machine.mem_store_byte(0xD3A39, 0x44);
    machine.mem_store_byte(0xD3A3A, 0xD4);
    machine.mem_store_byte(0xD3A3B, 0xB8);
    machine.mem_store_byte(0xD3A3C, 0x34);
    machine.mem_store_byte(0xD3A3D, 0xF4);
    machine.mem_store_byte(0xD3AA0, 0x0A);
    machine.mem_store_byte(0xD3AA1, 0xF4);
    machine.mem_store_byte(0xD3AA2, 0x0A);
    machine.mem_store_byte(0xD3AA3, 0xC2);
    machine.mem_store_byte(0xD3AA4, 0x05);
    machine.mem_store_byte(0xD3AA5, 0x16);
    machine.mem_store_byte(0xD3AA6, 0xA4);
    machine.mem_store_byte(0xD3AA7, 0xD3);
    machine.mem_store_byte(0xD3AA8, 0x39);
    machine.mem_store_byte(0xD3AA9, 0x2B);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFFFFF0F);
    EXPECT_EQ(cpu.get_ebx(), 0xF63172DC);
    EXPECT_EQ(cpu.get_ecx(), 0x80000000);
    EXPECT_EQ(cpu.get_edx(), 0xC461B8CD);
    EXPECT_EQ(cpu.get_esi(), 0x00446BB2);
    EXPECT_EQ(cpu.get_edi(), 0xAD5B8A02);
    EXPECT_EQ(cpu.get_ebp(), 0xFF067658);
    EXPECT_EQ(cpu.get_esp(), 0x00007FFE);
    EXPECT_EQ(cpu.get_cs(), 0x0000C3D6);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00005A5A);
    EXPECT_EQ(cpu.get_fs(), 0x0000AA55);
    EXPECT_EQ(cpu.get_gs(), 0x0000CB19);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000FD42);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
}

//
// repne lodsb
//
TEST_F(Test386, repne_lodsb)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE2AC250F);
    cpu.set_ebx(0x0137CCB0);
    cpu.set_ecx(0x00000020);
    cpu.set_edx(0x00B92D61);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x00200001);
    cpu.set_esp(0x00000A7C);
    cpu.set_cs(0x000063B1);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x0000FBB1);
    cpu.set_fs(0x0000B2CB);
    cpu.set_gs(0x0000AFE8);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00008918);
    cpu.set_eflags(0xFFFC0847);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6C428, 0xF2);
    machine.mem_store_byte(0x6C429, 0xAC);
    machine.mem_store_byte(0x6C42A, 0xF4);
    machine.mem_store_byte(0x6C42B, 0xB2);
    machine.mem_store_byte(0x6C42C, 0x51);
    machine.mem_store_byte(0x6C42D, 0xF5);
    machine.mem_store_byte(0x6C42E, 0xF3);
    machine.mem_store_byte(0x6C42F, 0x68);
    machine.mem_store_byte(0x6C430, 0x67);
    machine.mem_store_byte(0x6C431, 0xD7);
    machine.mem_store_byte(0x6C432, 0x13);
    machine.mem_store_byte(0x6C433, 0xFA);
    machine.mem_store_byte(0x6C434, 0xE4);
    machine.mem_store_byte(0x6C435, 0xEA);
    machine.mem_store_byte(0x10FFEF, 0xB7);
    machine.mem_store_byte(0xFFFF0, 0x26);
    machine.mem_store_byte(0xFFFF1, 0x56);
    machine.mem_store_byte(0xFFFF2, 0x50);
    machine.mem_store_byte(0xFFFF3, 0x19);
    machine.mem_store_byte(0xFFFF4, 0xC4);
    machine.mem_store_byte(0xFFFF5, 0x93);
    machine.mem_store_byte(0xFFFF6, 0x75);
    machine.mem_store_byte(0xFFFF7, 0x45);
    machine.mem_store_byte(0xFFFF8, 0x3F);
    machine.mem_store_byte(0xFFFF9, 0x6E);
    machine.mem_store_byte(0xFFFFA, 0x38);
    machine.mem_store_byte(0xFFFFB, 0x42);
    machine.mem_store_byte(0xFFFFC, 0xDB);
    machine.mem_store_byte(0xFFFFD, 0x80);
    machine.mem_store_byte(0xFFFFE, 0xF8);
    machine.mem_store_byte(0xFFFFF, 0x1B);
    machine.mem_store_byte(0x100000, 0x98);
    machine.mem_store_byte(0x100001, 0x89);
    machine.mem_store_byte(0x100002, 0xC1);
    machine.mem_store_byte(0x100003, 0x0E);
    machine.mem_store_byte(0x100004, 0xA1);
    machine.mem_store_byte(0x100005, 0x1A);
    machine.mem_store_byte(0x100006, 0xA4);
    machine.mem_store_byte(0x100007, 0x7C);
    machine.mem_store_byte(0x100008, 0xF8);
    machine.mem_store_byte(0x100009, 0xE1);
    machine.mem_store_byte(0x10000A, 0xF4);
    machine.mem_store_byte(0x10000B, 0x60);
    machine.mem_store_byte(0x10000C, 0x86);
    machine.mem_store_byte(0x10000D, 0x37);
    machine.mem_store_byte(0x10000E, 0xFA);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE2AC25FA);
    EXPECT_EQ(cpu.get_ebx(), 0x0137CCB0);
    EXPECT_EQ(cpu.get_ecx(), 0x00000000);
    EXPECT_EQ(cpu.get_edx(), 0x00B92D61);
    EXPECT_EQ(cpu.get_esi(), 0xFFFF001F);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x00200001);
    EXPECT_EQ(cpu.get_esp(), 0x00000A7C);
    EXPECT_EQ(cpu.get_cs(), 0x000063B1);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x0000FBB1);
    EXPECT_EQ(cpu.get_fs(), 0x0000B2CB);
    EXPECT_EQ(cpu.get_gs(), 0x0000AFE8);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000891B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0847);

    // Final RAM entries
}

//
// retd 695h
//
TEST_F(Test386, retd_695h)
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
    machine.mem_store_byte(0x7D008, 0x66);
    machine.mem_store_byte(0x7D009, 0xC2);
    machine.mem_store_byte(0x7D00A, 0x95);
    machine.mem_store_byte(0x7D00B, 0x06);
    machine.mem_store_byte(0x7D00C, 0xF4);
    machine.mem_store_byte(0x7D00D, 0xFF);
    machine.mem_store_byte(0x7D00E, 0xFF);
    machine.mem_store_byte(0x7D00F, 0xFF);
    machine.mem_store_byte(0x7D010, 0xFF);
    machine.mem_store_byte(0x7D011, 0xFF);
    machine.mem_store_byte(0x8E954, 0xFF);
    machine.mem_store_byte(0x8E955, 0xFF);
    machine.mem_store_byte(0x8E956, 0xFF);
    machine.mem_store_byte(0x8E957, 0xFF);
    machine.mem_store_byte(0x00034, 0x13);
    machine.mem_store_byte(0x00035, 0x72);
    machine.mem_store_byte(0x00036, 0xD3);
    machine.mem_store_byte(0x00037, 0x14);
    machine.mem_store_byte(0x1BF42, 0xF4);
    machine.mem_store_byte(0x1BF43, 0xF4);
    machine.mem_store_byte(0x1BF44, 0xFF);
    machine.mem_store_byte(0x1BF45, 0xF4);
    machine.mem_store_byte(0x1BF46, 0xFF);
    machine.mem_store_byte(0x1BF47, 0xF4);
    machine.mem_store_byte(0x1BF48, 0xFF);
    machine.mem_store_byte(0x1BF49, 0xF4);

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
    EXPECT_EQ(cpu.get_esp(), 0x0000A22E);
    EXPECT_EQ(cpu.get_cs(), 0x000014D3);
    EXPECT_EQ(cpu.get_ds(), 0x0000FAB5);
    EXPECT_EQ(cpu.get_es(), 0x00004C5E);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000DDE2);
    EXPECT_EQ(cpu.get_ss(), 0x00008472);
    EXPECT_EQ(cpu.get_eip(), 0x00007214);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8E952), 0xC6);
    EXPECT_EQ(memory.load8(0x8E953), 0x08);
    EXPECT_EQ(memory.load8(0x8E950), 0x72);
    EXPECT_EQ(memory.load8(0x8E951), 0x72);
    EXPECT_EQ(memory.load8(0x8E94E), 0xE8);
    EXPECT_EQ(memory.load8(0x8E94F), 0xA8);
}

//
// retfd 5D59h
//
TEST_F(Test386, retfd_5D59h)
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
    machine.mem_store_byte(0xA0198, 0x66);
    machine.mem_store_byte(0xA0199, 0xCA);
    machine.mem_store_byte(0xA019A, 0x59);
    machine.mem_store_byte(0xA019B, 0x5D);
    machine.mem_store_byte(0xA019C, 0xF4);
    machine.mem_store_byte(0xA019D, 0x4B);
    machine.mem_store_byte(0xA019E, 0x35);
    machine.mem_store_byte(0xA019F, 0x9C);
    machine.mem_store_byte(0xA01A0, 0xCF);
    machine.mem_store_byte(0xA01A1, 0x8A);
    machine.mem_store_byte(0x00030, 0x5D);
    machine.mem_store_byte(0x00031, 0x64);
    machine.mem_store_byte(0x00032, 0x11);
    machine.mem_store_byte(0x00033, 0x43);
    machine.mem_store_byte(0x4956C, 0xF4);
    machine.mem_store_byte(0x4956D, 0xF4);
    machine.mem_store_byte(0x4956E, 0x9B);
    machine.mem_store_byte(0x4956F, 0xF4);
    machine.mem_store_byte(0x49570, 0x37);
    machine.mem_store_byte(0x49571, 0xF4);
    machine.mem_store_byte(0x49572, 0x89);
    machine.mem_store_byte(0x49573, 0xF4);
    machine.mem_store_byte(0x49574, 0x9B);
    machine.mem_store_byte(0x49575, 0xF4);

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
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x00004311);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x000087A2);
    EXPECT_EQ(cpu.get_fs(), 0x0000DAA2);
    EXPECT_EQ(cpu.get_gs(), 0x0000FAFB);
    EXPECT_EQ(cpu.get_ss(), 0x0000FE3A);
    EXPECT_EQ(cpu.get_eip(), 0x0000645E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0492);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x10E39C), 0x92);
    EXPECT_EQ(memory.load8(0x10E39D), 0x04);
    EXPECT_EQ(memory.load8(0x10E39A), 0xE7);
    EXPECT_EQ(memory.load8(0x10E39B), 0x9A);
    EXPECT_EQ(memory.load8(0x10E398), 0x28);
    EXPECT_EQ(memory.load8(0x10E399), 0x53);
}
