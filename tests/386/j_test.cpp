#include "test386.h"

//
// ja near 5864h
//
TEST_F(Test386, ja_near_5864h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x91625DB1);
    cpu.set_ebx(0x1AD8A420);
    cpu.set_ecx(0xFB65337B);
    cpu.set_edx(0xF286C67D);
    cpu.set_esi(0xF132827F);
    cpu.set_edi(0x267FEA62);
    cpu.set_ebp(0xD8644864);
    cpu.set_esp(0x0000B3D6);
    cpu.set_cs(0x0000FCE7);
    cpu.set_ds(0x00004CB7);
    cpu.set_es(0x00009D4E);
    cpu.set_fs(0x00008015);
    cpu.set_gs(0x00009DEC);
    cpu.set_ss(0x000056E1);
    cpu.set_eip(0x00000AD8);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD948, 0x0F);
    machine.mem_store_byte(0xFD949, 0x87);
    machine.mem_store_byte(0xFD94A, 0x88);
    machine.mem_store_byte(0xFD94B, 0x4D);
    machine.mem_store_byte(0xFD94C, 0xF4);
    machine.mem_store_byte(0xFD94D, 0xDF);
    machine.mem_store_byte(0xFD94E, 0x01);
    machine.mem_store_byte(0xFD94F, 0x09);
    machine.mem_store_byte(0xFD950, 0x88);
    machine.mem_store_byte(0xFD951, 0x86);
    machine.mem_store_byte(0xFD952, 0xCB);
    machine.mem_store_byte(0xFD953, 0x3F);
    machine.mem_store_byte(0xFD954, 0x6F);
    machine.mem_store_byte(0xFD955, 0x33);
    machine.mem_store_byte(0xFD956, 0x6B);
    machine.mem_store_byte(0xFD957, 0xBA);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x91625DB1);
    EXPECT_EQ(cpu.get_ebx(), 0x1AD8A420);
    EXPECT_EQ(cpu.get_ecx(), 0xFB65337B);
    EXPECT_EQ(cpu.get_edx(), 0xF286C67D);
    EXPECT_EQ(cpu.get_esi(), 0xF132827F);
    EXPECT_EQ(cpu.get_edi(), 0x267FEA62);
    EXPECT_EQ(cpu.get_ebp(), 0xD8644864);
    EXPECT_EQ(cpu.get_esp(), 0x0000B3D6);
    EXPECT_EQ(cpu.get_cs(), 0x0000FCE7);
    EXPECT_EQ(cpu.get_ds(), 0x00004CB7);
    EXPECT_EQ(cpu.get_es(), 0x00009D4E);
    EXPECT_EQ(cpu.get_fs(), 0x00008015);
    EXPECT_EQ(cpu.get_gs(), 0x00009DEC);
    EXPECT_EQ(cpu.get_ss(), 0x000056E1);
    EXPECT_EQ(cpu.get_eip(), 0x00000ADD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
}

//
// jmp dword 0000F0E0h
//
TEST_F(Test386, jmp_dword_0000F0E0h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x463B292A);
    cpu.set_ebx(0x0B05A1C5);
    cpu.set_ecx(0xA3403580);
    cpu.set_edx(0xBE99456A);
    cpu.set_esi(0x228411D6);
    cpu.set_edi(0x045C85BB);
    cpu.set_ebp(0x0000000D);
    cpu.set_esp(0x0000000C);
    cpu.set_cs(0x0000DFF8);
    cpu.set_ds(0x00002DD7);
    cpu.set_es(0x000000B3);
    cpu.set_fs(0x00000BFF);
    cpu.set_gs(0x0000FFE2);
    cpu.set_ss(0x00003D6A);
    cpu.set_eip(0x0000D750);
    cpu.set_eflags(0xFFFC0C96);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xED6D0, 0x66);
    machine.mem_store_byte(0xED6D1, 0xE9);
    machine.mem_store_byte(0xED6D2, 0x8A);
    machine.mem_store_byte(0xED6D3, 0x19);
    machine.mem_store_byte(0xED6D4, 0x00);
    machine.mem_store_byte(0xED6D5, 0x00);
    machine.mem_store_byte(0xED6D6, 0xF4);
    machine.mem_store_byte(0xED6D7, 0xDD);
    machine.mem_store_byte(0xED6D8, 0xC7);
    machine.mem_store_byte(0xED6D9, 0x5E);
    machine.mem_store_byte(0xED6DA, 0xE8);
    machine.mem_store_byte(0xED6DB, 0xF7);
    machine.mem_store_byte(0xEF060, 0xF4);
    machine.mem_store_byte(0xEF061, 0xE0);
    machine.mem_store_byte(0xEF062, 0x09);
    machine.mem_store_byte(0xEF063, 0xF8);
    machine.mem_store_byte(0xEF064, 0x14);
    machine.mem_store_byte(0xEF065, 0xBD);
    machine.mem_store_byte(0xEF066, 0x34);
    machine.mem_store_byte(0xEF067, 0x91);
    machine.mem_store_byte(0xEF068, 0x78);
    machine.mem_store_byte(0xEF069, 0xE7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x463B292A);
    EXPECT_EQ(cpu.get_ebx(), 0x0B05A1C5);
    EXPECT_EQ(cpu.get_ecx(), 0xA3403580);
    EXPECT_EQ(cpu.get_edx(), 0xBE99456A);
    EXPECT_EQ(cpu.get_esi(), 0x228411D6);
    EXPECT_EQ(cpu.get_edi(), 0x045C85BB);
    EXPECT_EQ(cpu.get_ebp(), 0x0000000D);
    EXPECT_EQ(cpu.get_esp(), 0x0000000C);
    EXPECT_EQ(cpu.get_cs(), 0x0000DFF8);
    EXPECT_EQ(cpu.get_ds(), 0x00002DD7);
    EXPECT_EQ(cpu.get_es(), 0x000000B3);
    EXPECT_EQ(cpu.get_fs(), 0x00000BFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFE2);
    EXPECT_EQ(cpu.get_ss(), 0x00003D6A);
    EXPECT_EQ(cpu.get_eip(), 0x0000F0E1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C96);

    // Final RAM entries
}

//
// jae near 91B8h
//
TEST_F(Test386, jae_near_91B8h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7461637A);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x036FB89E);
    cpu.set_edx(0xB6225BE6);
    cpu.set_esi(0x59B97863);
    cpu.set_edi(0xED27C367);
    cpu.set_ebp(0x8BE14C0E);
    cpu.set_esp(0x00009659);
    cpu.set_cs(0x000032A3);
    cpu.set_ds(0x000000EA);
    cpu.set_es(0x000003AE);
    cpu.set_fs(0x00003518);
    cpu.set_gs(0x0000BAF9);
    cpu.set_ss(0x00003AC4);
    cpu.set_eip(0x000009D8);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x33408, 0x0F);
    machine.mem_store_byte(0x33409, 0x83);
    machine.mem_store_byte(0x3340A, 0xDC);
    machine.mem_store_byte(0x3340B, 0x87);
    machine.mem_store_byte(0x3340C, 0xF4);
    machine.mem_store_byte(0x3340D, 0x10);
    machine.mem_store_byte(0x3340E, 0x9D);
    machine.mem_store_byte(0x3340F, 0x33);
    machine.mem_store_byte(0x33410, 0x7F);
    machine.mem_store_byte(0x33411, 0xEC);
    machine.mem_store_byte(0x33412, 0xB7);
    machine.mem_store_byte(0x33413, 0x2C);
    machine.mem_store_byte(0x3BBE8, 0xF4);
    machine.mem_store_byte(0x3BBE9, 0x45);
    machine.mem_store_byte(0x3BBEA, 0xB0);
    machine.mem_store_byte(0x3BBEB, 0x4B);
    machine.mem_store_byte(0x3BBEC, 0x67);
    machine.mem_store_byte(0x3BBED, 0xBA);
    machine.mem_store_byte(0x3BBEE, 0x9B);
    machine.mem_store_byte(0x3BBEF, 0x08);
    machine.mem_store_byte(0x3BBF0, 0x64);
    machine.mem_store_byte(0x3BBF1, 0x8B);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7461637A);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x036FB89E);
    EXPECT_EQ(cpu.get_edx(), 0xB6225BE6);
    EXPECT_EQ(cpu.get_esi(), 0x59B97863);
    EXPECT_EQ(cpu.get_edi(), 0xED27C367);
    EXPECT_EQ(cpu.get_ebp(), 0x8BE14C0E);
    EXPECT_EQ(cpu.get_esp(), 0x00009659);
    EXPECT_EQ(cpu.get_cs(), 0x000032A3);
    EXPECT_EQ(cpu.get_ds(), 0x000000EA);
    EXPECT_EQ(cpu.get_es(), 0x000003AE);
    EXPECT_EQ(cpu.get_fs(), 0x00003518);
    EXPECT_EQ(cpu.get_gs(), 0x0000BAF9);
    EXPECT_EQ(cpu.get_ss(), 0x00003AC4);
    EXPECT_EQ(cpu.get_eip(), 0x000091B9);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
}

//
// jmp dword AD6Ah:000057D0h
//
TEST_F(Test386, jmp_dword_AD6Ah_000057D0h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x51EBB945);
    cpu.set_ebx(0xD90CC091);
    cpu.set_ecx(0x68109CB2);
    cpu.set_edx(0xD924D55B);
    cpu.set_esi(0xB8EF34E4);
    cpu.set_edi(0x00BC55DB);
    cpu.set_ebp(0x26DA0D04);
    cpu.set_esp(0x00007AF6);
    cpu.set_cs(0x000061F7);
    cpu.set_ds(0x0000857D);
    cpu.set_es(0x0000D06D);
    cpu.set_fs(0x0000F113);
    cpu.set_gs(0x00001106);
    cpu.set_ss(0x00000222);
    cpu.set_eip(0x000089D8);
    cpu.set_eflags(0xFFFC0C57);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6A948, 0x64);
    machine.mem_store_byte(0x6A949, 0x66);
    machine.mem_store_byte(0x6A94A, 0xEA);
    machine.mem_store_byte(0x6A94B, 0xD0);
    machine.mem_store_byte(0x6A94C, 0x57);
    machine.mem_store_byte(0x6A94D, 0x00);
    machine.mem_store_byte(0x6A94E, 0x00);
    machine.mem_store_byte(0x6A94F, 0x6A);
    machine.mem_store_byte(0x6A950, 0xAD);
    machine.mem_store_byte(0x6A951, 0xF4);
    machine.mem_store_byte(0x6A952, 0x00);
    machine.mem_store_byte(0x6A953, 0x00);
    machine.mem_store_byte(0x6A954, 0x00);
    machine.mem_store_byte(0x6A955, 0x00);
    machine.mem_store_byte(0x6A956, 0x00);
    machine.mem_store_byte(0x6A957, 0x00);
    machine.mem_store_byte(0xB2E70, 0xF4);
    machine.mem_store_byte(0xB2E71, 0xF4);
    machine.mem_store_byte(0xB2E72, 0x00);
    machine.mem_store_byte(0xB2E73, 0x00);
    machine.mem_store_byte(0xB2E74, 0x00);
    machine.mem_store_byte(0xB2E75, 0x00);
    machine.mem_store_byte(0xB2E76, 0x00);
    machine.mem_store_byte(0xB2E77, 0x00);
    machine.mem_store_byte(0xB2E78, 0x00);
    machine.mem_store_byte(0xB2E79, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x51EBB945);
    EXPECT_EQ(cpu.get_ebx(), 0xD90CC091);
    EXPECT_EQ(cpu.get_ecx(), 0x68109CB2);
    EXPECT_EQ(cpu.get_edx(), 0xD924D55B);
    EXPECT_EQ(cpu.get_esi(), 0xB8EF34E4);
    EXPECT_EQ(cpu.get_edi(), 0x00BC55DB);
    EXPECT_EQ(cpu.get_ebp(), 0x26DA0D04);
    EXPECT_EQ(cpu.get_esp(), 0x00007AF6);
    EXPECT_EQ(cpu.get_cs(), 0x0000AD6A);
    EXPECT_EQ(cpu.get_ds(), 0x0000857D);
    EXPECT_EQ(cpu.get_es(), 0x0000D06D);
    EXPECT_EQ(cpu.get_fs(), 0x0000F113);
    EXPECT_EQ(cpu.get_gs(), 0x00001106);
    EXPECT_EQ(cpu.get_ss(), 0x00000222);
    EXPECT_EQ(cpu.get_eip(), 0x000057D1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C57);

    // Final RAM entries
}

//
// ja near dword 00002E75h
//
TEST_F(Test386, ja_near_dword_00002E75h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF38453E2);
    cpu.set_ebx(0x80000000);
    cpu.set_ecx(0xFB239264);
    cpu.set_edx(0x9FD1C9CF);
    cpu.set_esi(0x0199F9FC);
    cpu.set_edi(0xB73A9F7E);
    cpu.set_ebp(0xC75A3D27);
    cpu.set_esp(0x0000E03A);
    cpu.set_cs(0x00009CAD);
    cpu.set_ds(0x000036A1);
    cpu.set_es(0x0000006F);
    cpu.set_fs(0x00000C35);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x00006178);
    cpu.set_eip(0x00008748);
    cpu.set_eflags(0xFFFC08C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA5218, 0x66);
    machine.mem_store_byte(0xA5219, 0x0F);
    machine.mem_store_byte(0xA521A, 0x87);
    machine.mem_store_byte(0xA521B, 0x26);
    machine.mem_store_byte(0xA521C, 0xA7);
    machine.mem_store_byte(0xA521D, 0xFF);
    machine.mem_store_byte(0xA521E, 0xFF);
    machine.mem_store_byte(0xA521F, 0xF4);
    machine.mem_store_byte(0xA5220, 0xFF);
    machine.mem_store_byte(0xA5221, 0xFF);
    machine.mem_store_byte(0xA5222, 0xFF);
    machine.mem_store_byte(0xA5223, 0xFF);
    machine.mem_store_byte(0xA5224, 0xFF);
    machine.mem_store_byte(0xA5225, 0xFF);
    machine.mem_store_byte(0xA5226, 0xFF);
    machine.mem_store_byte(0xA5227, 0xFF);
    machine.mem_store_byte(0xA5228, 0xFF);
    machine.mem_store_byte(0xA5229, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF38453E2);
    EXPECT_EQ(cpu.get_ebx(), 0x80000000);
    EXPECT_EQ(cpu.get_ecx(), 0xFB239264);
    EXPECT_EQ(cpu.get_edx(), 0x9FD1C9CF);
    EXPECT_EQ(cpu.get_esi(), 0x0199F9FC);
    EXPECT_EQ(cpu.get_edi(), 0xB73A9F7E);
    EXPECT_EQ(cpu.get_ebp(), 0xC75A3D27);
    EXPECT_EQ(cpu.get_esp(), 0x0000E03A);
    EXPECT_EQ(cpu.get_cs(), 0x00009CAD);
    EXPECT_EQ(cpu.get_ds(), 0x000036A1);
    EXPECT_EQ(cpu.get_es(), 0x0000006F);
    EXPECT_EQ(cpu.get_fs(), 0x00000C35);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x00006178);
    EXPECT_EQ(cpu.get_eip(), 0x00008750);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C6);

    // Final RAM entries
}

//
// jae near dword 000015CCh
//
TEST_F(Test386, jae_near_dword_000015CCh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7461637A);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x036FB89E);
    cpu.set_edx(0xB6225BE6);
    cpu.set_esi(0x59B97863);
    cpu.set_edi(0xED27C367);
    cpu.set_ebp(0x8BE14C0E);
    cpu.set_esp(0x00009659);
    cpu.set_cs(0x000032A3);
    cpu.set_ds(0x000000EA);
    cpu.set_es(0x000003AE);
    cpu.set_fs(0x00003518);
    cpu.set_gs(0x0000BAF9);
    cpu.set_ss(0x00003AC4);
    cpu.set_eip(0x000009D8);
    cpu.set_eflags(0xFFFC0CD6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x33408, 0x66);
    machine.mem_store_byte(0x33409, 0x0F);
    machine.mem_store_byte(0x3340A, 0x83);
    machine.mem_store_byte(0x3340B, 0xED);
    machine.mem_store_byte(0x3340C, 0x0B);
    machine.mem_store_byte(0x3340D, 0x00);
    machine.mem_store_byte(0x3340E, 0x00);
    machine.mem_store_byte(0x3340F, 0xF4);
    machine.mem_store_byte(0x33410, 0x7F);
    machine.mem_store_byte(0x33411, 0xEC);
    machine.mem_store_byte(0x33412, 0xB7);
    machine.mem_store_byte(0x33413, 0x2C);
    machine.mem_store_byte(0x33414, 0xAA);
    machine.mem_store_byte(0x33415, 0x56);
    machine.mem_store_byte(0x33FFC, 0xF4);
    machine.mem_store_byte(0x33FFD, 0x38);
    machine.mem_store_byte(0x33FFE, 0x6C);
    machine.mem_store_byte(0x33FFF, 0x21);
    machine.mem_store_byte(0x34000, 0x97);
    machine.mem_store_byte(0x34001, 0x03);
    machine.mem_store_byte(0x34002, 0x0E);
    machine.mem_store_byte(0x34003, 0x9A);
    machine.mem_store_byte(0x34004, 0x69);
    machine.mem_store_byte(0x34005, 0x1B);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7461637A);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x036FB89E);
    EXPECT_EQ(cpu.get_edx(), 0xB6225BE6);
    EXPECT_EQ(cpu.get_esi(), 0x59B97863);
    EXPECT_EQ(cpu.get_edi(), 0xED27C367);
    EXPECT_EQ(cpu.get_ebp(), 0x8BE14C0E);
    EXPECT_EQ(cpu.get_esp(), 0x00009659);
    EXPECT_EQ(cpu.get_cs(), 0x000032A3);
    EXPECT_EQ(cpu.get_ds(), 0x000000EA);
    EXPECT_EQ(cpu.get_es(), 0x000003AE);
    EXPECT_EQ(cpu.get_fs(), 0x00003518);
    EXPECT_EQ(cpu.get_gs(), 0x0000BAF9);
    EXPECT_EQ(cpu.get_ss(), 0x00003AC4);
    EXPECT_EQ(cpu.get_eip(), 0x000015CD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD6);

    // Final RAM entries
}

//
// jb near dword 000067CAh
//
TEST_F(Test386, jb_near_dword_000067CAh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0B73A391);
    cpu.set_ebx(0x8E864B48);
    cpu.set_ecx(0x8953F9AC);
    cpu.set_edx(0x25FBD055);
    cpu.set_esi(0x6EF71A45);
    cpu.set_edi(0x663F1F48);
    cpu.set_ebp(0x0586A010);
    cpu.set_esp(0x0000B906);
    cpu.set_cs(0x0000E707);
    cpu.set_ds(0x0000B818);
    cpu.set_es(0x000099DB);
    cpu.set_fs(0x0000AE1E);
    cpu.set_gs(0x00008000);
    cpu.set_ss(0x00004E1E);
    cpu.set_eip(0x000081C8);
    cpu.set_eflags(0xFFFC0857);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEF238, 0x66);
    machine.mem_store_byte(0xEF239, 0x0F);
    machine.mem_store_byte(0xEF23A, 0x82);
    machine.mem_store_byte(0xEF23B, 0xFB);
    machine.mem_store_byte(0xEF23C, 0xE5);
    machine.mem_store_byte(0xEF23D, 0xFF);
    machine.mem_store_byte(0xEF23E, 0xFF);
    machine.mem_store_byte(0xEF23F, 0xF4);
    machine.mem_store_byte(0xEF240, 0x9F);
    machine.mem_store_byte(0xEF241, 0xFE);
    machine.mem_store_byte(0xEF242, 0x5D);
    machine.mem_store_byte(0xEF243, 0x8F);
    machine.mem_store_byte(0xEF244, 0xC2);
    machine.mem_store_byte(0xEF245, 0xCB);
    machine.mem_store_byte(0xED83A, 0xF4);
    machine.mem_store_byte(0xED83B, 0xA6);
    machine.mem_store_byte(0xED83C, 0xEC);
    machine.mem_store_byte(0xED83D, 0x03);
    machine.mem_store_byte(0xED83E, 0x2A);
    machine.mem_store_byte(0xED83F, 0xCF);
    machine.mem_store_byte(0xED840, 0x90);
    machine.mem_store_byte(0xED841, 0xDE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0B73A391);
    EXPECT_EQ(cpu.get_ebx(), 0x8E864B48);
    EXPECT_EQ(cpu.get_ecx(), 0x8953F9AC);
    EXPECT_EQ(cpu.get_edx(), 0x25FBD055);
    EXPECT_EQ(cpu.get_esi(), 0x6EF71A45);
    EXPECT_EQ(cpu.get_edi(), 0x663F1F48);
    EXPECT_EQ(cpu.get_ebp(), 0x0586A010);
    EXPECT_EQ(cpu.get_esp(), 0x0000B906);
    EXPECT_EQ(cpu.get_cs(), 0x0000E707);
    EXPECT_EQ(cpu.get_ds(), 0x0000B818);
    EXPECT_EQ(cpu.get_es(), 0x000099DB);
    EXPECT_EQ(cpu.get_fs(), 0x0000AE1E);
    EXPECT_EQ(cpu.get_gs(), 0x00008000);
    EXPECT_EQ(cpu.get_ss(), 0x00004E1E);
    EXPECT_EQ(cpu.get_eip(), 0x000067CB);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0857);

    // Final RAM entries
}
