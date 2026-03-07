#include "test386.h"

//
// a32 es lodsd
//
TEST_F(Test386, a32_es_lodsd_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x007F0000);
    cpu.set_ebx(0xE9C33506);
    cpu.set_ecx(0xFFFFFFFA);
    cpu.set_edx(0xB2438935);
    cpu.set_esi(0x0000FFFF);
    cpu.set_edi(0x066351C6);
    cpu.set_ebp(0x01C99132);
    cpu.set_esp(0x0000F86A);
    cpu.set_cs(0x0000FB96);
    cpu.set_ds(0x0000D776);
    cpu.set_es(0x0000349C);
    cpu.set_fs(0x00000101);
    cpu.set_gs(0x0000FDCD);
    cpu.set_ss(0x00001C43);
    cpu.set_eip(0x00001D60);
    cpu.set_eflags(0xFFFC0803);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD6C0, 0x3E);
    machine.mem_store_byte(0xFD6C1, 0x3E);
    machine.mem_store_byte(0xFD6C2, 0x64);
    machine.mem_store_byte(0xFD6C3, 0x64);
    machine.mem_store_byte(0xFD6C4, 0x26);
    machine.mem_store_byte(0xFD6C5, 0x67);
    machine.mem_store_byte(0xFD6C6, 0x66);
    machine.mem_store_byte(0xFD6C7, 0xAD);
    machine.mem_store_byte(0xFD6C8, 0xF4);
    machine.mem_store_byte(0xFD6C9, 0x04);
    machine.mem_store_byte(0xFD6CA, 0x7F);
    machine.mem_store_byte(0xFD6CB, 0x35);
    machine.mem_store_byte(0xFD6CC, 0xA0);
    machine.mem_store_byte(0xFD6CD, 0xF8);
    machine.mem_store_byte(0xFD6CE, 0x83);
    machine.mem_store_byte(0xFD6CF, 0x92);
    machine.mem_store_byte(0xFD6D0, 0xF8);
    machine.mem_store_byte(0xFD6D1, 0x47);
    machine.mem_store_byte(0xFD6D2, 0xF2);
    machine.mem_store_byte(0xFD6D3, 0xE9);
    machine.mem_store_byte(0xFD6D4, 0x5F);
    machine.mem_store_byte(0xFD6D5, 0x1E);
    machine.mem_store_byte(0xFD6D6, 0x13);
    machine.mem_store_byte(0xFD6D7, 0xF2);
    machine.mem_store_byte(0x00034, 0x85);
    machine.mem_store_byte(0x00035, 0x74);
    machine.mem_store_byte(0x00036, 0xD6);
    machine.mem_store_byte(0x00037, 0xDA);
    machine.mem_store_byte(0xE21E4, 0x8E);
    machine.mem_store_byte(0xE21E5, 0xF4);
    machine.mem_store_byte(0xE21E6, 0xCA);
    machine.mem_store_byte(0xE21E7, 0xF4);
    machine.mem_store_byte(0xE21E8, 0xCD);
    machine.mem_store_byte(0xE21E9, 0xF4);
    machine.mem_store_byte(0xE21EA, 0x1C);
    machine.mem_store_byte(0xE21EB, 0xF4);
    machine.mem_store_byte(0xE21EC, 0xB7);
    machine.mem_store_byte(0xE21ED, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x007F0000);
    EXPECT_EQ(cpu.get_ebx(), 0xE9C33506);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFA);
    EXPECT_EQ(cpu.get_edx(), 0xB2438935);
    EXPECT_EQ(cpu.get_esi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edi(), 0x066351C6);
    EXPECT_EQ(cpu.get_ebp(), 0x01C99132);
    EXPECT_EQ(cpu.get_esp(), 0x0000F864);
    EXPECT_EQ(cpu.get_cs(), 0x0000DAD6);
    EXPECT_EQ(cpu.get_ds(), 0x0000D776);
    EXPECT_EQ(cpu.get_es(), 0x0000349C);
    EXPECT_EQ(cpu.get_fs(), 0x00000101);
    EXPECT_EQ(cpu.get_gs(), 0x0000FDCD);
    EXPECT_EQ(cpu.get_ss(), 0x00001C43);
    EXPECT_EQ(cpu.get_eip(), 0x00007486);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2BC98), 0x03);
    EXPECT_EQ(memory.load8(0x2BC99), 0x08);
    EXPECT_EQ(memory.load8(0x2BC96), 0x96);
    EXPECT_EQ(memory.load8(0x2BC97), 0xFB);
    EXPECT_EQ(memory.load8(0x2BC94), 0x60);
    EXPECT_EQ(memory.load8(0x2BC95), 0x1D);
}

//
// a32 es lodsw
//
TEST_F(Test386, a32_es_lodsw_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x007F0000);
    cpu.set_ebx(0xE9C33506);
    cpu.set_ecx(0xFFFFFFFA);
    cpu.set_edx(0xB2438935);
    cpu.set_esi(0x0000FFFF);
    cpu.set_edi(0x066351C6);
    cpu.set_ebp(0x01C99132);
    cpu.set_esp(0x0000F86A);
    cpu.set_cs(0x0000FB96);
    cpu.set_ds(0x0000D776);
    cpu.set_es(0x0000349C);
    cpu.set_fs(0x00000101);
    cpu.set_gs(0x0000FDCD);
    cpu.set_ss(0x00001C43);
    cpu.set_eip(0x00001D60);
    cpu.set_eflags(0xFFFC0803);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD6C0, 0x3E);
    machine.mem_store_byte(0xFD6C1, 0x3E);
    machine.mem_store_byte(0xFD6C2, 0x64);
    machine.mem_store_byte(0xFD6C3, 0x64);
    machine.mem_store_byte(0xFD6C4, 0x26);
    machine.mem_store_byte(0xFD6C5, 0x67);
    machine.mem_store_byte(0xFD6C6, 0xAD);
    machine.mem_store_byte(0xFD6C7, 0xF4);
    machine.mem_store_byte(0xFD6C8, 0x17);
    machine.mem_store_byte(0xFD6C9, 0x04);
    machine.mem_store_byte(0xFD6CA, 0x7F);
    machine.mem_store_byte(0xFD6CB, 0x35);
    machine.mem_store_byte(0xFD6CC, 0xA0);
    machine.mem_store_byte(0xFD6CD, 0xF8);
    machine.mem_store_byte(0xFD6CE, 0x83);
    machine.mem_store_byte(0xFD6CF, 0x92);
    machine.mem_store_byte(0xFD6D0, 0xF8);
    machine.mem_store_byte(0xFD6D1, 0x47);
    machine.mem_store_byte(0xFD6D2, 0xF2);
    machine.mem_store_byte(0xFD6D3, 0xE9);
    machine.mem_store_byte(0x00034, 0x85);
    machine.mem_store_byte(0x00035, 0x74);
    machine.mem_store_byte(0x00036, 0xD6);
    machine.mem_store_byte(0x00037, 0xDA);
    machine.mem_store_byte(0xE21E4, 0x8E);
    machine.mem_store_byte(0xE21E5, 0xF4);
    machine.mem_store_byte(0xE21E6, 0xCA);
    machine.mem_store_byte(0xE21E7, 0xF4);
    machine.mem_store_byte(0xE21E8, 0xCD);
    machine.mem_store_byte(0xE21E9, 0xF4);
    machine.mem_store_byte(0xE21EA, 0x1C);
    machine.mem_store_byte(0xE21EB, 0xF4);
    machine.mem_store_byte(0xE21EC, 0xB7);
    machine.mem_store_byte(0xE21ED, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x007F0000);
    EXPECT_EQ(cpu.get_ebx(), 0xE9C33506);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFA);
    EXPECT_EQ(cpu.get_edx(), 0xB2438935);
    EXPECT_EQ(cpu.get_esi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edi(), 0x066351C6);
    EXPECT_EQ(cpu.get_ebp(), 0x01C99132);
    EXPECT_EQ(cpu.get_esp(), 0x0000F864);
    EXPECT_EQ(cpu.get_cs(), 0x0000DAD6);
    EXPECT_EQ(cpu.get_ds(), 0x0000D776);
    EXPECT_EQ(cpu.get_es(), 0x0000349C);
    EXPECT_EQ(cpu.get_fs(), 0x00000101);
    EXPECT_EQ(cpu.get_gs(), 0x0000FDCD);
    EXPECT_EQ(cpu.get_ss(), 0x00001C43);
    EXPECT_EQ(cpu.get_eip(), 0x00007486);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2BC98), 0x03);
    EXPECT_EQ(memory.load8(0x2BC99), 0x08);
    EXPECT_EQ(memory.load8(0x2BC96), 0x96);
    EXPECT_EQ(memory.load8(0x2BC97), 0xFB);
    EXPECT_EQ(memory.load8(0x2BC94), 0x60);
    EXPECT_EQ(memory.load8(0x2BC95), 0x1D);
}

//
// (bad) lea ax,si
//
TEST_F(Test386, bad_lea_ax_si_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x954E3C55);
    cpu.set_ebx(0xD13EC745);
    cpu.set_ecx(0x0003FFFF);
    cpu.set_edx(0x7FD683FB);
    cpu.set_esi(0xD879E88F);
    cpu.set_edi(0x000001FF);
    cpu.set_ebp(0x51477FA6);
    cpu.set_esp(0x0000A452);
    cpu.set_cs(0x00003D6E);
    cpu.set_ds(0x0000D22B);
    cpu.set_es(0x0000EBFF);
    cpu.set_fs(0x0000FF7F);
    cpu.set_gs(0x0000816D);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000AD30);
    cpu.set_eflags(0xFFFC0486);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x48410, 0x26);
    machine.mem_store_byte(0x48411, 0x65);
    machine.mem_store_byte(0x48412, 0x3E);
    machine.mem_store_byte(0x48413, 0x36);
    machine.mem_store_byte(0x48414, 0x8D);
    machine.mem_store_byte(0x48415, 0xC6);
    machine.mem_store_byte(0x48416, 0xF4);
    machine.mem_store_byte(0x48417, 0xD9);
    machine.mem_store_byte(0x48418, 0x28);
    machine.mem_store_byte(0x48419, 0x78);
    machine.mem_store_byte(0x4841A, 0x6F);
    machine.mem_store_byte(0x4841B, 0x8D);
    machine.mem_store_byte(0x4841C, 0x9C);
    machine.mem_store_byte(0x4841D, 0xEC);
    machine.mem_store_byte(0x4841E, 0x65);
    machine.mem_store_byte(0x4841F, 0x57);
    machine.mem_store_byte(0x48420, 0x95);
    machine.mem_store_byte(0x48421, 0xED);
    machine.mem_store_byte(0x00018, 0xD9);
    machine.mem_store_byte(0x00019, 0xB9);
    machine.mem_store_byte(0x0001A, 0x01);
    machine.mem_store_byte(0x0001B, 0xA0);
    machine.mem_store_byte(0xAB9E8, 0xD9);
    machine.mem_store_byte(0xAB9E9, 0xF4);
    machine.mem_store_byte(0xAB9EA, 0xC9);
    machine.mem_store_byte(0xAB9EB, 0xF4);
    machine.mem_store_byte(0xAB9EC, 0x0B);
    machine.mem_store_byte(0xAB9ED, 0xF4);
    machine.mem_store_byte(0xAB9EE, 0xBE);
    machine.mem_store_byte(0xAB9EF, 0xF4);
    machine.mem_store_byte(0xAB9F0, 0x43);
    machine.mem_store_byte(0xAB9F1, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x954E3C55);
    EXPECT_EQ(cpu.get_ebx(), 0xD13EC745);
    EXPECT_EQ(cpu.get_ecx(), 0x0003FFFF);
    EXPECT_EQ(cpu.get_edx(), 0x7FD683FB);
    EXPECT_EQ(cpu.get_esi(), 0xD879E88F);
    EXPECT_EQ(cpu.get_edi(), 0x000001FF);
    EXPECT_EQ(cpu.get_ebp(), 0x51477FA6);
    EXPECT_EQ(cpu.get_esp(), 0x0000A44C);
    EXPECT_EQ(cpu.get_cs(), 0x0000A001);
    EXPECT_EQ(cpu.get_ds(), 0x0000D22B);
    EXPECT_EQ(cpu.get_es(), 0x0000EBFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000FF7F);
    EXPECT_EQ(cpu.get_gs(), 0x0000816D);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000B9DA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0A450), 0x86);
    EXPECT_EQ(memory.load8(0x0A451), 0x04);
    EXPECT_EQ(memory.load8(0x0A44E), 0x6E);
    EXPECT_EQ(memory.load8(0x0A44F), 0x3D);
    EXPECT_EQ(memory.load8(0x0A44C), 0x30);
    EXPECT_EQ(memory.load8(0x0A44D), 0xAD);
}

//
// (bad) lea eax,esi
//
TEST_F(Test386, bad_lea_eax_esi_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x954E3C55);
    cpu.set_ebx(0xD13EC745);
    cpu.set_ecx(0x0003FFFF);
    cpu.set_edx(0x7FD683FB);
    cpu.set_esi(0xD879E88F);
    cpu.set_edi(0x000001FF);
    cpu.set_ebp(0x51477FA6);
    cpu.set_esp(0x0000A452);
    cpu.set_cs(0x00003D6E);
    cpu.set_ds(0x0000D22B);
    cpu.set_es(0x0000EBFF);
    cpu.set_fs(0x0000FF7F);
    cpu.set_gs(0x0000816D);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000AD30);
    cpu.set_eflags(0xFFFC0486);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x48410, 0x26);
    machine.mem_store_byte(0x48411, 0x65);
    machine.mem_store_byte(0x48412, 0x3E);
    machine.mem_store_byte(0x48413, 0x36);
    machine.mem_store_byte(0x48414, 0x67);
    machine.mem_store_byte(0x48415, 0x66);
    machine.mem_store_byte(0x48416, 0x8D);
    machine.mem_store_byte(0x48417, 0xC6);
    machine.mem_store_byte(0x48418, 0xF4);
    machine.mem_store_byte(0x48419, 0x78);
    machine.mem_store_byte(0x4841A, 0x6F);
    machine.mem_store_byte(0x4841B, 0x8D);
    machine.mem_store_byte(0x4841C, 0x9C);
    machine.mem_store_byte(0x4841D, 0xEC);
    machine.mem_store_byte(0x4841E, 0x65);
    machine.mem_store_byte(0x4841F, 0x57);
    machine.mem_store_byte(0x48420, 0x95);
    machine.mem_store_byte(0x48421, 0xED);
    machine.mem_store_byte(0x48422, 0xB7);
    machine.mem_store_byte(0x48423, 0x5C);
    machine.mem_store_byte(0x00018, 0xD9);
    machine.mem_store_byte(0x00019, 0xB9);
    machine.mem_store_byte(0x0001A, 0x01);
    machine.mem_store_byte(0x0001B, 0xA0);
    machine.mem_store_byte(0xAB9E8, 0xD9);
    machine.mem_store_byte(0xAB9E9, 0xF4);
    machine.mem_store_byte(0xAB9EA, 0xC9);
    machine.mem_store_byte(0xAB9EB, 0xF4);
    machine.mem_store_byte(0xAB9EC, 0x0B);
    machine.mem_store_byte(0xAB9ED, 0xF4);
    machine.mem_store_byte(0xAB9EE, 0xBE);
    machine.mem_store_byte(0xAB9EF, 0xF4);
    machine.mem_store_byte(0xAB9F0, 0x43);
    machine.mem_store_byte(0xAB9F1, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x954E3C55);
    EXPECT_EQ(cpu.get_ebx(), 0xD13EC745);
    EXPECT_EQ(cpu.get_ecx(), 0x0003FFFF);
    EXPECT_EQ(cpu.get_edx(), 0x7FD683FB);
    EXPECT_EQ(cpu.get_esi(), 0xD879E88F);
    EXPECT_EQ(cpu.get_edi(), 0x000001FF);
    EXPECT_EQ(cpu.get_ebp(), 0x51477FA6);
    EXPECT_EQ(cpu.get_esp(), 0x0000A44C);
    EXPECT_EQ(cpu.get_cs(), 0x0000A001);
    EXPECT_EQ(cpu.get_ds(), 0x0000D22B);
    EXPECT_EQ(cpu.get_es(), 0x0000EBFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000FF7F);
    EXPECT_EQ(cpu.get_gs(), 0x0000816D);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000B9DA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0A450), 0x86);
    EXPECT_EQ(memory.load8(0x0A451), 0x04);
    EXPECT_EQ(memory.load8(0x0A44E), 0x6E);
    EXPECT_EQ(memory.load8(0x0A44F), 0x3D);
    EXPECT_EQ(memory.load8(0x0A44C), 0x30);
    EXPECT_EQ(memory.load8(0x0A44D), 0xAD);
}

//
// btc [cs:ecx-B224h],cx
//
TEST_F(Test386, btc_cs_ecx_B224h_cx_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1FCB6B4B);
    cpu.set_ebx(0xF023BEE6);
    cpu.set_ecx(0x00001657);
    cpu.set_edx(0xC56E6BC5);
    cpu.set_esi(0x297B3AB1);
    cpu.set_edi(0xBB1F2856);
    cpu.set_ebp(0xF3836793);
    cpu.set_esp(0x00008400);
    cpu.set_cs(0x0000EA26);
    cpu.set_ds(0x0000FE39);
    cpu.set_es(0x0000782D);
    cpu.set_fs(0x0000C3AC);
    cpu.set_gs(0x0000D155);
    cpu.set_ss(0x0000A099);
    cpu.set_eip(0x00002E70);
    cpu.set_eflags(0xFFFC0092);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xED0D0, 0x2E);
    machine.mem_store_byte(0xED0D1, 0x67);
    machine.mem_store_byte(0xED0D2, 0x0F);
    machine.mem_store_byte(0xED0D3, 0xBB);
    machine.mem_store_byte(0xED0D4, 0x89);
    machine.mem_store_byte(0xED0D5, 0xDC);
    machine.mem_store_byte(0xED0D6, 0x4D);
    machine.mem_store_byte(0xED0D7, 0xFF);
    machine.mem_store_byte(0xED0D8, 0xFF);
    machine.mem_store_byte(0xED0D9, 0xF4);
    machine.mem_store_byte(0xED0DA, 0x00);
    machine.mem_store_byte(0xED0DB, 0x00);
    machine.mem_store_byte(0xED0DC, 0x00);
    machine.mem_store_byte(0xED0DD, 0x00);
    machine.mem_store_byte(0xED0DE, 0x00);
    machine.mem_store_byte(0xED0DF, 0x00);
    machine.mem_store_byte(0xED0E0, 0x00);
    machine.mem_store_byte(0xED0E1, 0x00);
    machine.mem_store_byte(0xED0E2, 0x00);
    machine.mem_store_byte(0xED0E3, 0x00);
    machine.mem_store_byte(0xED0E4, 0x00);
    machine.mem_store_byte(0xED0E5, 0x00);
    machine.mem_store_byte(0x00034, 0xB1);
    machine.mem_store_byte(0x00035, 0x4F);
    machine.mem_store_byte(0x00036, 0xF6);
    machine.mem_store_byte(0x00037, 0xB5);
    machine.mem_store_byte(0xBAF10, 0x00);
    machine.mem_store_byte(0xBAF11, 0xF4);
    machine.mem_store_byte(0xBAF12, 0x00);
    machine.mem_store_byte(0xBAF13, 0xF4);
    machine.mem_store_byte(0xBAF14, 0x00);
    machine.mem_store_byte(0xBAF15, 0xF4);
    machine.mem_store_byte(0xBAF16, 0x00);
    machine.mem_store_byte(0xBAF17, 0xF4);
    machine.mem_store_byte(0xBAF18, 0x00);
    machine.mem_store_byte(0xBAF19, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1FCB6B4B);
    EXPECT_EQ(cpu.get_ebx(), 0xF023BEE6);
    EXPECT_EQ(cpu.get_ecx(), 0x00001657);
    EXPECT_EQ(cpu.get_edx(), 0xC56E6BC5);
    EXPECT_EQ(cpu.get_esi(), 0x297B3AB1);
    EXPECT_EQ(cpu.get_edi(), 0xBB1F2856);
    EXPECT_EQ(cpu.get_ebp(), 0xF3836793);
    EXPECT_EQ(cpu.get_esp(), 0x000083FA);
    EXPECT_EQ(cpu.get_cs(), 0x0000B5F6);
    EXPECT_EQ(cpu.get_ds(), 0x0000FE39);
    EXPECT_EQ(cpu.get_es(), 0x0000782D);
    EXPECT_EQ(cpu.get_fs(), 0x0000C3AC);
    EXPECT_EQ(cpu.get_gs(), 0x0000D155);
    EXPECT_EQ(cpu.get_ss(), 0x0000A099);
    EXPECT_EQ(cpu.get_eip(), 0x00004FB2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA8D8E), 0x92);
    EXPECT_EQ(memory.load8(0xA8D8F), 0x00);
    EXPECT_EQ(memory.load8(0xA8D8C), 0x26);
    EXPECT_EQ(memory.load8(0xA8D8D), 0xEA);
    EXPECT_EQ(memory.load8(0xA8D8A), 0x70);
    EXPECT_EQ(memory.load8(0xA8D8B), 0x2E);
}

//
// btc [cs:ecx-B224h],ecx
//
TEST_F(Test386, btc_cs_ecx_B224h_ecx_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1FCB6B4B);
    cpu.set_ebx(0xF023BEE6);
    cpu.set_ecx(0x00001657);
    cpu.set_edx(0xC56E6BC5);
    cpu.set_esi(0x297B3AB1);
    cpu.set_edi(0xBB1F2856);
    cpu.set_ebp(0xF3836793);
    cpu.set_esp(0x00008400);
    cpu.set_cs(0x0000EA26);
    cpu.set_ds(0x0000FE39);
    cpu.set_es(0x0000782D);
    cpu.set_fs(0x0000C3AC);
    cpu.set_gs(0x0000D155);
    cpu.set_ss(0x0000A099);
    cpu.set_eip(0x00002E70);
    cpu.set_eflags(0xFFFC0092);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xED0D0, 0x2E);
    machine.mem_store_byte(0xED0D1, 0x66);
    machine.mem_store_byte(0xED0D2, 0x67);
    machine.mem_store_byte(0xED0D3, 0x0F);
    machine.mem_store_byte(0xED0D4, 0xBB);
    machine.mem_store_byte(0xED0D5, 0x89);
    machine.mem_store_byte(0xED0D6, 0xDC);
    machine.mem_store_byte(0xED0D7, 0x4D);
    machine.mem_store_byte(0xED0D8, 0xFF);
    machine.mem_store_byte(0xED0D9, 0xFF);
    machine.mem_store_byte(0xED0DA, 0xF4);
    machine.mem_store_byte(0xED0DB, 0x00);
    machine.mem_store_byte(0xED0DC, 0x00);
    machine.mem_store_byte(0xED0DD, 0x00);
    machine.mem_store_byte(0xED0DE, 0x00);
    machine.mem_store_byte(0xED0DF, 0x00);
    machine.mem_store_byte(0xED0E0, 0x00);
    machine.mem_store_byte(0xED0E1, 0x00);
    machine.mem_store_byte(0xED0E2, 0x00);
    machine.mem_store_byte(0xED0E3, 0x00);
    machine.mem_store_byte(0xED0E4, 0x00);
    machine.mem_store_byte(0xED0E5, 0x00);
    machine.mem_store_byte(0x00034, 0xB1);
    machine.mem_store_byte(0x00035, 0x4F);
    machine.mem_store_byte(0x00036, 0xF6);
    machine.mem_store_byte(0x00037, 0xB5);
    machine.mem_store_byte(0xBAF10, 0x00);
    machine.mem_store_byte(0xBAF11, 0xF4);
    machine.mem_store_byte(0xBAF12, 0x00);
    machine.mem_store_byte(0xBAF13, 0xF4);
    machine.mem_store_byte(0xBAF14, 0x00);
    machine.mem_store_byte(0xBAF15, 0xF4);
    machine.mem_store_byte(0xBAF16, 0x00);
    machine.mem_store_byte(0xBAF17, 0xF4);
    machine.mem_store_byte(0xBAF18, 0x00);
    machine.mem_store_byte(0xBAF19, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1FCB6B4B);
    EXPECT_EQ(cpu.get_ebx(), 0xF023BEE6);
    EXPECT_EQ(cpu.get_ecx(), 0x00001657);
    EXPECT_EQ(cpu.get_edx(), 0xC56E6BC5);
    EXPECT_EQ(cpu.get_esi(), 0x297B3AB1);
    EXPECT_EQ(cpu.get_edi(), 0xBB1F2856);
    EXPECT_EQ(cpu.get_ebp(), 0xF3836793);
    EXPECT_EQ(cpu.get_esp(), 0x000083FA);
    EXPECT_EQ(cpu.get_cs(), 0x0000B5F6);
    EXPECT_EQ(cpu.get_ds(), 0x0000FE39);
    EXPECT_EQ(cpu.get_es(), 0x0000782D);
    EXPECT_EQ(cpu.get_fs(), 0x0000C3AC);
    EXPECT_EQ(cpu.get_gs(), 0x0000D155);
    EXPECT_EQ(cpu.get_ss(), 0x0000A099);
    EXPECT_EQ(cpu.get_eip(), 0x00004FB2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA8D8E), 0x92);
    EXPECT_EQ(memory.load8(0xA8D8F), 0x00);
    EXPECT_EQ(memory.load8(0xA8D8C), 0x26);
    EXPECT_EQ(memory.load8(0xA8D8D), 0xEA);
    EXPECT_EQ(memory.load8(0xA8D8A), 0x70);
    EXPECT_EQ(memory.load8(0xA8D8B), 0x2E);
}

//
// btr [es:esi+ACA2h],cx
//
TEST_F(Test386, btr_es_esi_ACA2h_cx_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x58948C3F);
    cpu.set_ebx(0xAFE9C79C);
    cpu.set_ecx(0x3222D288);
    cpu.set_edx(0xFCA49809);
    cpu.set_esi(0x0000E872);
    cpu.set_edi(0x30C68689);
    cpu.set_ebp(0x77C7DB49);
    cpu.set_esp(0x0000AA1C);
    cpu.set_cs(0x0000FEE8);
    cpu.set_ds(0x00005F49);
    cpu.set_es(0x0000D844);
    cpu.set_fs(0x000081D5);
    cpu.set_gs(0x00002952);
    cpu.set_ss(0x0000192A);
    cpu.set_eip(0x0000A1B8);
    cpu.set_eflags(0xFFFC0082);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x109038, 0x26);
    machine.mem_store_byte(0x109039, 0x67);
    machine.mem_store_byte(0x10903A, 0x0F);
    machine.mem_store_byte(0x10903B, 0xB3);
    machine.mem_store_byte(0x10903C, 0x8E);
    machine.mem_store_byte(0x10903D, 0xA2);
    machine.mem_store_byte(0x10903E, 0xAC);
    machine.mem_store_byte(0x10903F, 0x00);
    machine.mem_store_byte(0x109040, 0x00);
    machine.mem_store_byte(0x109041, 0xF4);
    machine.mem_store_byte(0x109042, 0x6B);
    machine.mem_store_byte(0x109043, 0x09);
    machine.mem_store_byte(0x109044, 0xF7);
    machine.mem_store_byte(0x109045, 0x62);
    machine.mem_store_byte(0x109046, 0xD7);
    machine.mem_store_byte(0x109047, 0xDB);
    machine.mem_store_byte(0x109048, 0x69);
    machine.mem_store_byte(0x109049, 0x39);
    machine.mem_store_byte(0x10904A, 0x04);
    machine.mem_store_byte(0x10904B, 0x92);
    machine.mem_store_byte(0x10904C, 0xFE);
    machine.mem_store_byte(0x10904D, 0x70);
    machine.mem_store_byte(0x00034, 0xE9);
    machine.mem_store_byte(0x00035, 0x5A);
    machine.mem_store_byte(0x00036, 0xC2);
    machine.mem_store_byte(0x00037, 0x47);
    machine.mem_store_byte(0x4D708, 0x42);
    machine.mem_store_byte(0x4D709, 0xF4);
    machine.mem_store_byte(0x4D70A, 0x48);
    machine.mem_store_byte(0x4D70B, 0xF4);
    machine.mem_store_byte(0x4D70C, 0x92);
    machine.mem_store_byte(0x4D70D, 0xF4);
    machine.mem_store_byte(0x4D70E, 0xCA);
    machine.mem_store_byte(0x4D70F, 0xF4);
    machine.mem_store_byte(0x4D710, 0xE3);
    machine.mem_store_byte(0x4D711, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x58948C3F);
    EXPECT_EQ(cpu.get_ebx(), 0xAFE9C79C);
    EXPECT_EQ(cpu.get_ecx(), 0x3222D288);
    EXPECT_EQ(cpu.get_edx(), 0xFCA49809);
    EXPECT_EQ(cpu.get_esi(), 0x0000E872);
    EXPECT_EQ(cpu.get_edi(), 0x30C68689);
    EXPECT_EQ(cpu.get_ebp(), 0x77C7DB49);
    EXPECT_EQ(cpu.get_esp(), 0x0000AA16);
    EXPECT_EQ(cpu.get_cs(), 0x000047C2);
    EXPECT_EQ(cpu.get_ds(), 0x00005F49);
    EXPECT_EQ(cpu.get_es(), 0x0000D844);
    EXPECT_EQ(cpu.get_fs(), 0x000081D5);
    EXPECT_EQ(cpu.get_gs(), 0x00002952);
    EXPECT_EQ(cpu.get_ss(), 0x0000192A);
    EXPECT_EQ(cpu.get_eip(), 0x00005AEA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x23CBA), 0x82);
    EXPECT_EQ(memory.load8(0x23CBB), 0x00);
    EXPECT_EQ(memory.load8(0x23CB8), 0xE8);
    EXPECT_EQ(memory.load8(0x23CB9), 0xFE);
    EXPECT_EQ(memory.load8(0x23CB6), 0xB8);
    EXPECT_EQ(memory.load8(0x23CB7), 0xA1);
}

//
// btr [es:esi+ACA2h],ecx
//
TEST_F(Test386, btr_es_esi_ACA2h_ecx_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x58948C3F);
    cpu.set_ebx(0xAFE9C79C);
    cpu.set_ecx(0x0000D288);
    cpu.set_edx(0xFCA49809);
    cpu.set_esi(0x0000E872);
    cpu.set_edi(0x30C68689);
    cpu.set_ebp(0x77C7DB49);
    cpu.set_esp(0x0000AA1C);
    cpu.set_cs(0x0000FEE8);
    cpu.set_ds(0x00005F49);
    cpu.set_es(0x0000D844);
    cpu.set_fs(0x000081D5);
    cpu.set_gs(0x00002952);
    cpu.set_ss(0x0000192A);
    cpu.set_eip(0x0000A1B8);
    cpu.set_eflags(0xFFFC0082);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x109038, 0x26);
    machine.mem_store_byte(0x109039, 0x66);
    machine.mem_store_byte(0x10903A, 0x67);
    machine.mem_store_byte(0x10903B, 0x0F);
    machine.mem_store_byte(0x10903C, 0xB3);
    machine.mem_store_byte(0x10903D, 0x8E);
    machine.mem_store_byte(0x10903E, 0xA2);
    machine.mem_store_byte(0x10903F, 0xAC);
    machine.mem_store_byte(0x109040, 0x00);
    machine.mem_store_byte(0x109041, 0x00);
    machine.mem_store_byte(0x109042, 0xF4);
    machine.mem_store_byte(0x109043, 0x09);
    machine.mem_store_byte(0x109044, 0xF7);
    machine.mem_store_byte(0x109045, 0x62);
    machine.mem_store_byte(0x109046, 0xD7);
    machine.mem_store_byte(0x109047, 0xDB);
    machine.mem_store_byte(0x109048, 0x69);
    machine.mem_store_byte(0x109049, 0x39);
    machine.mem_store_byte(0x10904A, 0x04);
    machine.mem_store_byte(0x10904B, 0x92);
    machine.mem_store_byte(0x10904C, 0xFE);
    machine.mem_store_byte(0x10904D, 0x70);
    machine.mem_store_byte(0x00034, 0xE9);
    machine.mem_store_byte(0x00035, 0x5A);
    machine.mem_store_byte(0x00036, 0xC2);
    machine.mem_store_byte(0x00037, 0x47);
    machine.mem_store_byte(0x4D708, 0x42);
    machine.mem_store_byte(0x4D709, 0xF4);
    machine.mem_store_byte(0x4D70A, 0x48);
    machine.mem_store_byte(0x4D70B, 0xF4);
    machine.mem_store_byte(0x4D70C, 0x92);
    machine.mem_store_byte(0x4D70D, 0xF4);
    machine.mem_store_byte(0x4D70E, 0xCA);
    machine.mem_store_byte(0x4D70F, 0xF4);
    machine.mem_store_byte(0x4D710, 0xE3);
    machine.mem_store_byte(0x4D711, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x58948C3F);
    EXPECT_EQ(cpu.get_ebx(), 0xAFE9C79C);
    EXPECT_EQ(cpu.get_ecx(), 0x0000D288);
    EXPECT_EQ(cpu.get_edx(), 0xFCA49809);
    EXPECT_EQ(cpu.get_esi(), 0x0000E872);
    EXPECT_EQ(cpu.get_edi(), 0x30C68689);
    EXPECT_EQ(cpu.get_ebp(), 0x77C7DB49);
    EXPECT_EQ(cpu.get_esp(), 0x0000AA16);
    EXPECT_EQ(cpu.get_cs(), 0x000047C2);
    EXPECT_EQ(cpu.get_ds(), 0x00005F49);
    EXPECT_EQ(cpu.get_es(), 0x0000D844);
    EXPECT_EQ(cpu.get_fs(), 0x000081D5);
    EXPECT_EQ(cpu.get_gs(), 0x00002952);
    EXPECT_EQ(cpu.get_ss(), 0x0000192A);
    EXPECT_EQ(cpu.get_eip(), 0x00005AEA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x23CBA), 0x82);
    EXPECT_EQ(memory.load8(0x23CBB), 0x00);
    EXPECT_EQ(memory.load8(0x23CB8), 0xE8);
    EXPECT_EQ(memory.load8(0x23CB9), 0xFE);
    EXPECT_EQ(memory.load8(0x23CB6), 0xB8);
    EXPECT_EQ(memory.load8(0x23CB7), 0xA1);
}

//
// idiv esp
//
TEST_F(Test386, idiv_esp_batch2)
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
    machine.mem_store_byte(0x5D860, 0x67);
    machine.mem_store_byte(0x5D861, 0x66);
    machine.mem_store_byte(0x5D862, 0xF7);
    machine.mem_store_byte(0x5D863, 0xFC);
    machine.mem_store_byte(0x5D864, 0xF4);
    machine.mem_store_byte(0x5D865, 0x48);
    machine.mem_store_byte(0x5D866, 0xFF);
    machine.mem_store_byte(0x5D867, 0xE2);
    machine.mem_store_byte(0x5D868, 0x48);
    machine.mem_store_byte(0x5D869, 0x56);
    machine.mem_store_byte(0x5D86A, 0x86);
    machine.mem_store_byte(0x5D86B, 0xAC);
    machine.mem_store_byte(0x5D86C, 0x26);
    machine.mem_store_byte(0x5D86D, 0x87);
    machine.mem_store_byte(0x5D86E, 0xE6);
    machine.mem_store_byte(0x5D86F, 0x58);
    machine.mem_store_byte(0x00000, 0x7E);
    machine.mem_store_byte(0x00001, 0xD6);
    machine.mem_store_byte(0x00002, 0x63);
    machine.mem_store_byte(0x00003, 0x2D);
    machine.mem_store_byte(0x3ACAE, 0xF4);
    machine.mem_store_byte(0x3ACAF, 0x3A);
    machine.mem_store_byte(0x3ACB0, 0xF4);
    machine.mem_store_byte(0x3ACB1, 0xA7);
    machine.mem_store_byte(0x3ACB2, 0xF4);
    machine.mem_store_byte(0x3ACB3, 0x57);

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
    EXPECT_EQ(cpu.get_esp(), 0x0000448C);
    EXPECT_EQ(cpu.get_cs(), 0x00002D63);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x000000E6);
    EXPECT_EQ(cpu.get_fs(), 0x00003DFA);
    EXPECT_EQ(cpu.get_gs(), 0x00007446);
    EXPECT_EQ(cpu.get_ss(), 0x0000B412);
    EXPECT_EQ(cpu.get_eip(), 0x0000D67F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB85B0), 0x06);
    EXPECT_EQ(memory.load8(0xB85B1), 0x00);
    EXPECT_EQ(memory.load8(0xB85AE), 0x33);
    EXPECT_EQ(memory.load8(0xB85AF), 0x58);
    EXPECT_EQ(memory.load8(0xB85AC), 0x30);
    EXPECT_EQ(memory.load8(0xB85AD), 0x55);
}

//
// idiv sp
//
TEST_F(Test386, idiv_sp_batch2)
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
    machine.mem_store_byte(0x5D860, 0xF7);
    machine.mem_store_byte(0x5D861, 0xFC);
    machine.mem_store_byte(0x5D862, 0xF4);
    machine.mem_store_byte(0x5D863, 0x88);
    machine.mem_store_byte(0x5D864, 0x4C);
    machine.mem_store_byte(0x5D865, 0x48);
    machine.mem_store_byte(0x5D866, 0xFF);
    machine.mem_store_byte(0x5D867, 0xE2);
    machine.mem_store_byte(0x5D868, 0x48);
    machine.mem_store_byte(0x5D869, 0x56);
    machine.mem_store_byte(0x5D86A, 0x86);
    machine.mem_store_byte(0x5D86B, 0xAC);
    machine.mem_store_byte(0x5D86C, 0x26);
    machine.mem_store_byte(0x5D86D, 0x87);
    machine.mem_store_byte(0x5D86E, 0xE6);
    machine.mem_store_byte(0x5D86F, 0x58);
    machine.mem_store_byte(0x00000, 0x7E);
    machine.mem_store_byte(0x00001, 0xD6);
    machine.mem_store_byte(0x00002, 0x63);
    machine.mem_store_byte(0x00003, 0x2D);
    machine.mem_store_byte(0x3ACAE, 0xF4);
    machine.mem_store_byte(0x3ACAF, 0x3A);
    machine.mem_store_byte(0x3ACB0, 0xF4);
    machine.mem_store_byte(0x3ACB1, 0xA7);
    machine.mem_store_byte(0x3ACB2, 0xF4);
    machine.mem_store_byte(0x3ACB3, 0x57);

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
    EXPECT_EQ(cpu.get_esp(), 0x0000448C);
    EXPECT_EQ(cpu.get_cs(), 0x00002D63);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x000000E6);
    EXPECT_EQ(cpu.get_fs(), 0x00003DFA);
    EXPECT_EQ(cpu.get_gs(), 0x00007446);
    EXPECT_EQ(cpu.get_ss(), 0x0000B412);
    EXPECT_EQ(cpu.get_eip(), 0x0000D67F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0003);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB85B0), 0x03);
    EXPECT_EQ(memory.load8(0xB85B1), 0x00);
    EXPECT_EQ(memory.load8(0xB85AE), 0x33);
    EXPECT_EQ(memory.load8(0xB85AF), 0x58);
    EXPECT_EQ(memory.load8(0xB85AC), 0x30);
    EXPECT_EQ(memory.load8(0xB85AD), 0x55);
}

//
// jle near dword 00001CF1h
//
TEST_F(Test386, jle_near_dword_00001CF1h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2924B94E);
    cpu.set_ebx(0xA68E2BD1);
    cpu.set_ecx(0x1E173B57);
    cpu.set_edx(0xCB36F80A);
    cpu.set_esi(0xA14D5949);
    cpu.set_edi(0x28CA2A6C);
    cpu.set_ebp(0x55118C6E);
    cpu.set_esp(0x000023F8);
    cpu.set_cs(0x00009283);
    cpu.set_ds(0x0000EC63);
    cpu.set_es(0x0000830C);
    cpu.set_fs(0x0000CCBB);
    cpu.set_gs(0x00002EC2);
    cpu.set_ss(0x00003977);
    cpu.set_eip(0x00001CF0);
    cpu.set_eflags(0xFFFC0CD7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x94520, 0x66);
    machine.mem_store_byte(0x94521, 0x0F);
    machine.mem_store_byte(0x94522, 0x8E);
    machine.mem_store_byte(0x94523, 0xFA);
    machine.mem_store_byte(0x94524, 0xFF);
    machine.mem_store_byte(0x94525, 0xFF);
    machine.mem_store_byte(0x94526, 0xFF);
    machine.mem_store_byte(0x94527, 0xF4);
    machine.mem_store_byte(0x94528, 0x13);
    machine.mem_store_byte(0x94529, 0x44);
    machine.mem_store_byte(0x9452A, 0x2B);
    machine.mem_store_byte(0x9452B, 0x21);
    machine.mem_store_byte(0x9452C, 0x46);
    machine.mem_store_byte(0x9452D, 0x78);
    machine.mem_store_byte(0x9451E, 0x52);
    machine.mem_store_byte(0x9451F, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x2924B94E);
    EXPECT_EQ(cpu.get_ebx(), 0xA68E2BD1);
    EXPECT_EQ(cpu.get_ecx(), 0x1E173B57);
    EXPECT_EQ(cpu.get_edx(), 0xCB36F80A);
    EXPECT_EQ(cpu.get_esi(), 0xA14D5949);
    EXPECT_EQ(cpu.get_edi(), 0x28CA2A6C);
    EXPECT_EQ(cpu.get_ebp(), 0x55118C6E);
    EXPECT_EQ(cpu.get_esp(), 0x000023F8);
    EXPECT_EQ(cpu.get_cs(), 0x00009283);
    EXPECT_EQ(cpu.get_ds(), 0x0000EC63);
    EXPECT_EQ(cpu.get_es(), 0x0000830C);
    EXPECT_EQ(cpu.get_fs(), 0x0000CCBB);
    EXPECT_EQ(cpu.get_gs(), 0x00002EC2);
    EXPECT_EQ(cpu.get_ss(), 0x00003977);
    EXPECT_EQ(cpu.get_eip(), 0x00001CF0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CD7);

    // Final RAM entries
}

//
// lds dx,[ds:ebx-6954h]
//
TEST_F(Test386, lds_dx_ds_ebx_6954h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x3E2EE8EB);
    cpu.set_ebx(0x00000000);
    cpu.set_ecx(0x0000000A);
    cpu.set_edx(0x20582AD0);
    cpu.set_esi(0x674EAF2D);
    cpu.set_edi(0x6E6EB068);
    cpu.set_ebp(0x07C5330E);
    cpu.set_esp(0x0000037A);
    cpu.set_cs(0x0000639A);
    cpu.set_ds(0x00008000);
    cpu.set_es(0x000081B7);
    cpu.set_fs(0x000016CF);
    cpu.set_gs(0x000041C3);
    cpu.set_ss(0x0000026E);
    cpu.set_eip(0x00008250);
    cpu.set_eflags(0xFFFC0843);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6BBF0, 0x67);
    machine.mem_store_byte(0x6BBF1, 0xC5);
    machine.mem_store_byte(0x6BBF2, 0x93);
    machine.mem_store_byte(0x6BBF3, 0xAC);
    machine.mem_store_byte(0x6BBF4, 0x96);
    machine.mem_store_byte(0x6BBF5, 0xFF);
    machine.mem_store_byte(0x6BBF6, 0xFF);
    machine.mem_store_byte(0x6BBF7, 0xF4);
    machine.mem_store_byte(0x6BBF8, 0x1B);
    machine.mem_store_byte(0x6BBF9, 0x25);
    machine.mem_store_byte(0x6BBFA, 0x3B);
    machine.mem_store_byte(0x6BBFB, 0xC3);
    machine.mem_store_byte(0x6BBFC, 0x5E);
    machine.mem_store_byte(0x6BBFD, 0x3A);
    machine.mem_store_byte(0x6BBFE, 0xA0);
    machine.mem_store_byte(0x6BBFF, 0xFD);
    machine.mem_store_byte(0x6BC00, 0x3A);
    machine.mem_store_byte(0x6BC01, 0x0C);
    machine.mem_store_byte(0x6BC02, 0x01);
    machine.mem_store_byte(0x6BC03, 0xFF);
    machine.mem_store_byte(0x00034, 0x7B);
    machine.mem_store_byte(0x00035, 0xE8);
    machine.mem_store_byte(0x00036, 0xB0);
    machine.mem_store_byte(0x00037, 0xF0);
    machine.mem_store_byte(0xFF37A, 0xF4);
    machine.mem_store_byte(0xFF37B, 0xF4);
    machine.mem_store_byte(0xFF37C, 0x9C);
    machine.mem_store_byte(0xFF37D, 0xF4);
    machine.mem_store_byte(0xFF37E, 0x63);
    machine.mem_store_byte(0xFF37F, 0xF4);
    machine.mem_store_byte(0xFF380, 0xCD);
    machine.mem_store_byte(0xFF381, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x3E2EE8EB);
    EXPECT_EQ(cpu.get_ebx(), 0x00000000);
    EXPECT_EQ(cpu.get_ecx(), 0x0000000A);
    EXPECT_EQ(cpu.get_edx(), 0x20582AD0);
    EXPECT_EQ(cpu.get_esi(), 0x674EAF2D);
    EXPECT_EQ(cpu.get_edi(), 0x6E6EB068);
    EXPECT_EQ(cpu.get_ebp(), 0x07C5330E);
    EXPECT_EQ(cpu.get_esp(), 0x00000374);
    EXPECT_EQ(cpu.get_cs(), 0x0000F0B0);
    EXPECT_EQ(cpu.get_ds(), 0x00008000);
    EXPECT_EQ(cpu.get_es(), 0x000081B7);
    EXPECT_EQ(cpu.get_fs(), 0x000016CF);
    EXPECT_EQ(cpu.get_gs(), 0x000041C3);
    EXPECT_EQ(cpu.get_ss(), 0x0000026E);
    EXPECT_EQ(cpu.get_eip(), 0x0000E87C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0843);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02A58), 0x43);
    EXPECT_EQ(memory.load8(0x02A59), 0x08);
    EXPECT_EQ(memory.load8(0x02A56), 0x9A);
    EXPECT_EQ(memory.load8(0x02A57), 0x63);
    EXPECT_EQ(memory.load8(0x02A54), 0x50);
    EXPECT_EQ(memory.load8(0x02A55), 0x82);
}

//
// lds edx,[ds:ebx-6954h]
//
TEST_F(Test386, lds_edx_ds_ebx_6954h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x3E2EE8EB);
    cpu.set_ebx(0x00000000);
    cpu.set_ecx(0x0000000A);
    cpu.set_edx(0x20582AD0);
    cpu.set_esi(0x674EAF2D);
    cpu.set_edi(0x6E6EB068);
    cpu.set_ebp(0x07C5330E);
    cpu.set_esp(0x0000037A);
    cpu.set_cs(0x0000639A);
    cpu.set_ds(0x00008000);
    cpu.set_es(0x000081B7);
    cpu.set_fs(0x000016CF);
    cpu.set_gs(0x000041C3);
    cpu.set_ss(0x0000026E);
    cpu.set_eip(0x00008250);
    cpu.set_eflags(0xFFFC0843);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6BBF0, 0x66);
    machine.mem_store_byte(0x6BBF1, 0x67);
    machine.mem_store_byte(0x6BBF2, 0xC5);
    machine.mem_store_byte(0x6BBF3, 0x93);
    machine.mem_store_byte(0x6BBF4, 0xAC);
    machine.mem_store_byte(0x6BBF5, 0x96);
    machine.mem_store_byte(0x6BBF6, 0xFF);
    machine.mem_store_byte(0x6BBF7, 0xFF);
    machine.mem_store_byte(0x6BBF8, 0xF4);
    machine.mem_store_byte(0x6BBF9, 0x25);
    machine.mem_store_byte(0x6BBFA, 0x3B);
    machine.mem_store_byte(0x6BBFB, 0xC3);
    machine.mem_store_byte(0x6BBFC, 0x5E);
    machine.mem_store_byte(0x6BBFD, 0x3A);
    machine.mem_store_byte(0x6BBFE, 0xA0);
    machine.mem_store_byte(0x6BBFF, 0xFD);
    machine.mem_store_byte(0x6BC00, 0x3A);
    machine.mem_store_byte(0x6BC01, 0x0C);
    machine.mem_store_byte(0x6BC02, 0x01);
    machine.mem_store_byte(0x6BC03, 0xFF);
    machine.mem_store_byte(0x6BC04, 0xC3);
    machine.mem_store_byte(0x6BC05, 0x68);
    machine.mem_store_byte(0x6BC06, 0x60);
    machine.mem_store_byte(0x6BC07, 0x09);
    machine.mem_store_byte(0x00034, 0x7B);
    machine.mem_store_byte(0x00035, 0xE8);
    machine.mem_store_byte(0x00036, 0xB0);
    machine.mem_store_byte(0x00037, 0xF0);
    machine.mem_store_byte(0xFF37A, 0xF4);
    machine.mem_store_byte(0xFF37B, 0xF4);
    machine.mem_store_byte(0xFF37C, 0x9C);
    machine.mem_store_byte(0xFF37D, 0xF4);
    machine.mem_store_byte(0xFF37E, 0x63);
    machine.mem_store_byte(0xFF37F, 0xF4);
    machine.mem_store_byte(0xFF380, 0xCD);
    machine.mem_store_byte(0xFF381, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x3E2EE8EB);
    EXPECT_EQ(cpu.get_ebx(), 0x00000000);
    EXPECT_EQ(cpu.get_ecx(), 0x0000000A);
    EXPECT_EQ(cpu.get_edx(), 0x20582AD0);
    EXPECT_EQ(cpu.get_esi(), 0x674EAF2D);
    EXPECT_EQ(cpu.get_edi(), 0x6E6EB068);
    EXPECT_EQ(cpu.get_ebp(), 0x07C5330E);
    EXPECT_EQ(cpu.get_esp(), 0x00000374);
    EXPECT_EQ(cpu.get_cs(), 0x0000F0B0);
    EXPECT_EQ(cpu.get_ds(), 0x00008000);
    EXPECT_EQ(cpu.get_es(), 0x000081B7);
    EXPECT_EQ(cpu.get_fs(), 0x000016CF);
    EXPECT_EQ(cpu.get_gs(), 0x000041C3);
    EXPECT_EQ(cpu.get_ss(), 0x0000026E);
    EXPECT_EQ(cpu.get_eip(), 0x0000E87C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0843);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02A58), 0x43);
    EXPECT_EQ(memory.load8(0x02A59), 0x08);
    EXPECT_EQ(memory.load8(0x02A56), 0x9A);
    EXPECT_EQ(memory.load8(0x02A57), 0x63);
    EXPECT_EQ(memory.load8(0x02A54), 0x50);
    EXPECT_EQ(memory.load8(0x02A55), 0x82);
}

//
// lfs dx,[ds:eax-4E22h]
//
TEST_F(Test386, lfs_dx_ds_eax_4E22h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00002E1B);
    cpu.set_ebx(0xBDBB72B2);
    cpu.set_ecx(0x18814875);
    cpu.set_edx(0x46C99BBD);
    cpu.set_esi(0x6749869B);
    cpu.set_edi(0x7C21CC24);
    cpu.set_ebp(0xEB4F2CCB);
    cpu.set_esp(0x0000A324);
    cpu.set_cs(0x0000086E);
    cpu.set_ds(0x0000B60F);
    cpu.set_es(0x00002CD3);
    cpu.set_fs(0x0000473E);
    cpu.set_gs(0x0000FE47);
    cpu.set_ss(0x0000648A);
    cpu.set_eip(0x0000DDF0);
    cpu.set_eflags(0xFFFC0843);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x164D0, 0x67);
    machine.mem_store_byte(0x164D1, 0x0F);
    machine.mem_store_byte(0x164D2, 0xB4);
    machine.mem_store_byte(0x164D3, 0x90);
    machine.mem_store_byte(0x164D4, 0xDE);
    machine.mem_store_byte(0x164D5, 0xB1);
    machine.mem_store_byte(0x164D6, 0xFF);
    machine.mem_store_byte(0x164D7, 0xFF);
    machine.mem_store_byte(0x164D8, 0xF4);
    machine.mem_store_byte(0x164D9, 0x86);
    machine.mem_store_byte(0x164DA, 0x73);
    machine.mem_store_byte(0x164DB, 0x13);
    machine.mem_store_byte(0x164DC, 0x37);
    machine.mem_store_byte(0x164DD, 0x8C);
    machine.mem_store_byte(0x164DE, 0xBD);
    machine.mem_store_byte(0x164DF, 0xA6);
    machine.mem_store_byte(0x164E0, 0xAC);
    machine.mem_store_byte(0x164E1, 0x62);
    machine.mem_store_byte(0x164E2, 0x1F);
    machine.mem_store_byte(0x164E3, 0xA3);
    machine.mem_store_byte(0x164E4, 0xEF);
    machine.mem_store_byte(0x164E5, 0x92);
    machine.mem_store_byte(0x164E6, 0x11);
    machine.mem_store_byte(0x164E7, 0xE5);
    machine.mem_store_byte(0x00034, 0x01);
    machine.mem_store_byte(0x00035, 0x71);
    machine.mem_store_byte(0x00036, 0xBB);
    machine.mem_store_byte(0x00037, 0x7C);
    machine.mem_store_byte(0x83CB0, 0x92);
    machine.mem_store_byte(0x83CB1, 0xF4);
    machine.mem_store_byte(0x83CB2, 0x72);
    machine.mem_store_byte(0x83CB3, 0xF4);
    machine.mem_store_byte(0x83CB4, 0x14);
    machine.mem_store_byte(0x83CB5, 0xF4);
    machine.mem_store_byte(0x83CB6, 0x0A);
    machine.mem_store_byte(0x83CB7, 0xF4);
    machine.mem_store_byte(0x83CB8, 0x50);
    machine.mem_store_byte(0x83CB9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00002E1B);
    EXPECT_EQ(cpu.get_ebx(), 0xBDBB72B2);
    EXPECT_EQ(cpu.get_ecx(), 0x18814875);
    EXPECT_EQ(cpu.get_edx(), 0x46C99BBD);
    EXPECT_EQ(cpu.get_esi(), 0x6749869B);
    EXPECT_EQ(cpu.get_edi(), 0x7C21CC24);
    EXPECT_EQ(cpu.get_ebp(), 0xEB4F2CCB);
    EXPECT_EQ(cpu.get_esp(), 0x0000A31E);
    EXPECT_EQ(cpu.get_cs(), 0x00007CBB);
    EXPECT_EQ(cpu.get_ds(), 0x0000B60F);
    EXPECT_EQ(cpu.get_es(), 0x00002CD3);
    EXPECT_EQ(cpu.get_fs(), 0x0000473E);
    EXPECT_EQ(cpu.get_gs(), 0x0000FE47);
    EXPECT_EQ(cpu.get_ss(), 0x0000648A);
    EXPECT_EQ(cpu.get_eip(), 0x00007102);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0843);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6EBC2), 0x43);
    EXPECT_EQ(memory.load8(0x6EBC3), 0x08);
    EXPECT_EQ(memory.load8(0x6EBC0), 0x6E);
    EXPECT_EQ(memory.load8(0x6EBC1), 0x08);
    EXPECT_EQ(memory.load8(0x6EBBE), 0xF0);
    EXPECT_EQ(memory.load8(0x6EBBF), 0xDD);
}

//
// lfs edx,[ds:eax-4E22h]
//
TEST_F(Test386, lfs_edx_ds_eax_4E22h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00002E1B);
    cpu.set_ebx(0xBDBB72B2);
    cpu.set_ecx(0x18814875);
    cpu.set_edx(0x46C99BBD);
    cpu.set_esi(0x6749869B);
    cpu.set_edi(0x7C21CC24);
    cpu.set_ebp(0xEB4F2CCB);
    cpu.set_esp(0x0000A324);
    cpu.set_cs(0x0000086E);
    cpu.set_ds(0x0000B60F);
    cpu.set_es(0x00002CD3);
    cpu.set_fs(0x0000473E);
    cpu.set_gs(0x0000FE47);
    cpu.set_ss(0x0000648A);
    cpu.set_eip(0x0000DDF0);
    cpu.set_eflags(0xFFFC0843);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x164D0, 0x66);
    machine.mem_store_byte(0x164D1, 0x67);
    machine.mem_store_byte(0x164D2, 0x0F);
    machine.mem_store_byte(0x164D3, 0xB4);
    machine.mem_store_byte(0x164D4, 0x90);
    machine.mem_store_byte(0x164D5, 0xDE);
    machine.mem_store_byte(0x164D6, 0xB1);
    machine.mem_store_byte(0x164D7, 0xFF);
    machine.mem_store_byte(0x164D8, 0xFF);
    machine.mem_store_byte(0x164D9, 0xF4);
    machine.mem_store_byte(0x164DA, 0x73);
    machine.mem_store_byte(0x164DB, 0x13);
    machine.mem_store_byte(0x164DC, 0x37);
    machine.mem_store_byte(0x164DD, 0x8C);
    machine.mem_store_byte(0x164DE, 0xBD);
    machine.mem_store_byte(0x164DF, 0xA6);
    machine.mem_store_byte(0x164E0, 0xAC);
    machine.mem_store_byte(0x164E1, 0x62);
    machine.mem_store_byte(0x164E2, 0x1F);
    machine.mem_store_byte(0x164E3, 0xA3);
    machine.mem_store_byte(0x164E4, 0xEF);
    machine.mem_store_byte(0x164E5, 0x92);
    machine.mem_store_byte(0x164E6, 0x11);
    machine.mem_store_byte(0x164E7, 0xE5);
    machine.mem_store_byte(0x00034, 0x01);
    machine.mem_store_byte(0x00035, 0x71);
    machine.mem_store_byte(0x00036, 0xBB);
    machine.mem_store_byte(0x00037, 0x7C);
    machine.mem_store_byte(0x83CB0, 0x92);
    machine.mem_store_byte(0x83CB1, 0xF4);
    machine.mem_store_byte(0x83CB2, 0x72);
    machine.mem_store_byte(0x83CB3, 0xF4);
    machine.mem_store_byte(0x83CB4, 0x14);
    machine.mem_store_byte(0x83CB5, 0xF4);
    machine.mem_store_byte(0x83CB6, 0x0A);
    machine.mem_store_byte(0x83CB7, 0xF4);
    machine.mem_store_byte(0x83CB8, 0x50);
    machine.mem_store_byte(0x83CB9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00002E1B);
    EXPECT_EQ(cpu.get_ebx(), 0xBDBB72B2);
    EXPECT_EQ(cpu.get_ecx(), 0x18814875);
    EXPECT_EQ(cpu.get_edx(), 0x46C99BBD);
    EXPECT_EQ(cpu.get_esi(), 0x6749869B);
    EXPECT_EQ(cpu.get_edi(), 0x7C21CC24);
    EXPECT_EQ(cpu.get_ebp(), 0xEB4F2CCB);
    EXPECT_EQ(cpu.get_esp(), 0x0000A31E);
    EXPECT_EQ(cpu.get_cs(), 0x00007CBB);
    EXPECT_EQ(cpu.get_ds(), 0x0000B60F);
    EXPECT_EQ(cpu.get_es(), 0x00002CD3);
    EXPECT_EQ(cpu.get_fs(), 0x0000473E);
    EXPECT_EQ(cpu.get_gs(), 0x0000FE47);
    EXPECT_EQ(cpu.get_ss(), 0x0000648A);
    EXPECT_EQ(cpu.get_eip(), 0x00007102);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0843);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6EBC2), 0x43);
    EXPECT_EQ(memory.load8(0x6EBC3), 0x08);
    EXPECT_EQ(memory.load8(0x6EBC0), 0x6E);
    EXPECT_EQ(memory.load8(0x6EBC1), 0x08);
    EXPECT_EQ(memory.load8(0x6EBBE), 0xF0);
    EXPECT_EQ(memory.load8(0x6EBBF), 0xDD);
}

//
// lodsd
//
TEST_F(Test386, lodsd_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x007F0000);
    cpu.set_ebx(0xE9C33506);
    cpu.set_ecx(0xFFFFFFFA);
    cpu.set_edx(0xB2438935);
    cpu.set_esi(0xDFFFFFFF);
    cpu.set_edi(0x066351C6);
    cpu.set_ebp(0x01C99132);
    cpu.set_esp(0x0000F86A);
    cpu.set_cs(0x0000FB96);
    cpu.set_ds(0x0000D776);
    cpu.set_es(0x0000349C);
    cpu.set_fs(0x00000101);
    cpu.set_gs(0x0000FDCD);
    cpu.set_ss(0x00001C43);
    cpu.set_eip(0x00001D60);
    cpu.set_eflags(0xFFFC0803);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD6C0, 0x66);
    machine.mem_store_byte(0xFD6C1, 0xAD);
    machine.mem_store_byte(0xFD6C2, 0xF4);
    machine.mem_store_byte(0xFD6C3, 0x10);
    machine.mem_store_byte(0xFD6C4, 0xBC);
    machine.mem_store_byte(0xFD6C5, 0xCB);
    machine.mem_store_byte(0xFD6C6, 0x87);
    machine.mem_store_byte(0xFD6C7, 0xB1);
    machine.mem_store_byte(0xFD6C8, 0x17);
    machine.mem_store_byte(0xFD6C9, 0x04);
    machine.mem_store_byte(0xFD6CA, 0x7F);
    machine.mem_store_byte(0xFD6CB, 0x35);
    machine.mem_store_byte(0xFD6CC, 0xA0);
    machine.mem_store_byte(0xFD6CD, 0xF8);
    machine.mem_store_byte(0xFD6CE, 0x83);
    machine.mem_store_byte(0xFD6CF, 0x92);
    machine.mem_store_byte(0xFD6D0, 0xF8);
    machine.mem_store_byte(0xFD6D1, 0x47);
    machine.mem_store_byte(0xFD6D2, 0xF2);
    machine.mem_store_byte(0xFD6D3, 0xE9);
    machine.mem_store_byte(0x00034, 0x85);
    machine.mem_store_byte(0x00035, 0x74);
    machine.mem_store_byte(0x00036, 0xD6);
    machine.mem_store_byte(0x00037, 0xDA);
    machine.mem_store_byte(0xE21E4, 0x8E);
    machine.mem_store_byte(0xE21E5, 0xF4);
    machine.mem_store_byte(0xE21E6, 0xCA);
    machine.mem_store_byte(0xE21E7, 0xF4);
    machine.mem_store_byte(0xE21E8, 0xCD);
    machine.mem_store_byte(0xE21E9, 0xF4);
    machine.mem_store_byte(0xE21EA, 0x1C);
    machine.mem_store_byte(0xE21EB, 0xF4);
    machine.mem_store_byte(0xE21EC, 0xB7);
    machine.mem_store_byte(0xE21ED, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x007F0000);
    EXPECT_EQ(cpu.get_ebx(), 0xE9C33506);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFA);
    EXPECT_EQ(cpu.get_edx(), 0xB2438935);
    EXPECT_EQ(cpu.get_esi(), 0xDFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x066351C6);
    EXPECT_EQ(cpu.get_ebp(), 0x01C99132);
    EXPECT_EQ(cpu.get_esp(), 0x0000F864);
    EXPECT_EQ(cpu.get_cs(), 0x0000DAD6);
    EXPECT_EQ(cpu.get_ds(), 0x0000D776);
    EXPECT_EQ(cpu.get_es(), 0x0000349C);
    EXPECT_EQ(cpu.get_fs(), 0x00000101);
    EXPECT_EQ(cpu.get_gs(), 0x0000FDCD);
    EXPECT_EQ(cpu.get_ss(), 0x00001C43);
    EXPECT_EQ(cpu.get_eip(), 0x00007486);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2BC98), 0x03);
    EXPECT_EQ(memory.load8(0x2BC99), 0x08);
    EXPECT_EQ(memory.load8(0x2BC96), 0x96);
    EXPECT_EQ(memory.load8(0x2BC97), 0xFB);
    EXPECT_EQ(memory.load8(0x2BC94), 0x60);
    EXPECT_EQ(memory.load8(0x2BC95), 0x1D);
}

//
// lodsw
//
TEST_F(Test386, lodsw_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x007F0000);
    cpu.set_ebx(0xE9C33506);
    cpu.set_ecx(0xFFFFFFFA);
    cpu.set_edx(0xB2438935);
    cpu.set_esi(0xDFFFFFFF);
    cpu.set_edi(0x066351C6);
    cpu.set_ebp(0x01C99132);
    cpu.set_esp(0x0000F86A);
    cpu.set_cs(0x0000FB96);
    cpu.set_ds(0x0000D776);
    cpu.set_es(0x0000349C);
    cpu.set_fs(0x00000101);
    cpu.set_gs(0x0000FDCD);
    cpu.set_ss(0x00001C43);
    cpu.set_eip(0x00001D60);
    cpu.set_eflags(0xFFFC0803);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD6C0, 0xAD);
    machine.mem_store_byte(0xFD6C1, 0xF4);
    machine.mem_store_byte(0xFD6C2, 0xB3);
    machine.mem_store_byte(0xFD6C3, 0x10);
    machine.mem_store_byte(0xFD6C4, 0xBC);
    machine.mem_store_byte(0xFD6C5, 0xCB);
    machine.mem_store_byte(0xFD6C6, 0x87);
    machine.mem_store_byte(0xFD6C7, 0xB1);
    machine.mem_store_byte(0xFD6C8, 0x17);
    machine.mem_store_byte(0xFD6C9, 0x04);
    machine.mem_store_byte(0xFD6CA, 0x7F);
    machine.mem_store_byte(0xFD6CB, 0x35);
    machine.mem_store_byte(0xFD6CC, 0xA0);
    machine.mem_store_byte(0xFD6CD, 0xF8);
    machine.mem_store_byte(0xFD6CE, 0x83);
    machine.mem_store_byte(0xFD6CF, 0x92);
    machine.mem_store_byte(0x00034, 0x85);
    machine.mem_store_byte(0x00035, 0x74);
    machine.mem_store_byte(0x00036, 0xD6);
    machine.mem_store_byte(0x00037, 0xDA);
    machine.mem_store_byte(0xE21E4, 0x8E);
    machine.mem_store_byte(0xE21E5, 0xF4);
    machine.mem_store_byte(0xE21E6, 0xCA);
    machine.mem_store_byte(0xE21E7, 0xF4);
    machine.mem_store_byte(0xE21E8, 0xCD);
    machine.mem_store_byte(0xE21E9, 0xF4);
    machine.mem_store_byte(0xE21EA, 0x1C);
    machine.mem_store_byte(0xE21EB, 0xF4);
    machine.mem_store_byte(0xE21EC, 0xB7);
    machine.mem_store_byte(0xE21ED, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x007F0000);
    EXPECT_EQ(cpu.get_ebx(), 0xE9C33506);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFA);
    EXPECT_EQ(cpu.get_edx(), 0xB2438935);
    EXPECT_EQ(cpu.get_esi(), 0xDFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x066351C6);
    EXPECT_EQ(cpu.get_ebp(), 0x01C99132);
    EXPECT_EQ(cpu.get_esp(), 0x0000F864);
    EXPECT_EQ(cpu.get_cs(), 0x0000DAD6);
    EXPECT_EQ(cpu.get_ds(), 0x0000D776);
    EXPECT_EQ(cpu.get_es(), 0x0000349C);
    EXPECT_EQ(cpu.get_fs(), 0x00000101);
    EXPECT_EQ(cpu.get_gs(), 0x0000FDCD);
    EXPECT_EQ(cpu.get_ss(), 0x00001C43);
    EXPECT_EQ(cpu.get_eip(), 0x00007486);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2BC98), 0x03);
    EXPECT_EQ(memory.load8(0x2BC99), 0x08);
    EXPECT_EQ(memory.load8(0x2BC96), 0x96);
    EXPECT_EQ(memory.load8(0x2BC97), 0xFB);
    EXPECT_EQ(memory.load8(0x2BC94), 0x60);
    EXPECT_EQ(memory.load8(0x2BC95), 0x1D);
}

//
// mul byte [ds:bx+di+11h]
//
TEST_F(Test386, mul_byte_ds_bx_di_11h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE73E12D9);
    cpu.set_ebx(0xB35B03EF);
    cpu.set_ecx(0x130F92AC);
    cpu.set_edx(0xD5511D7E);
    cpu.set_esi(0x0080FFE6);
    cpu.set_edi(0x7FFFFFFF);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x0000000E);
    cpu.set_cs(0x0000FCB7);
    cpu.set_ds(0x00007FFF);
    cpu.set_es(0x0000D0A6);
    cpu.set_fs(0x0000C8AB);
    cpu.set_gs(0x000005B5);
    cpu.set_ss(0x00000FE9);
    cpu.set_eip(0x00000090);
    cpu.set_eflags(0xFFFC0C03);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFCC00, 0xF6);
    machine.mem_store_byte(0xFCC01, 0x61);
    machine.mem_store_byte(0xFCC02, 0x11);
    machine.mem_store_byte(0xFCC03, 0xF4);
    machine.mem_store_byte(0xFCC04, 0xCC);
    machine.mem_store_byte(0xFCC05, 0x39);
    machine.mem_store_byte(0xFCC06, 0xE0);
    machine.mem_store_byte(0xFCC07, 0x45);
    machine.mem_store_byte(0xFCC08, 0x4D);
    machine.mem_store_byte(0xFCC09, 0xF1);
    machine.mem_store_byte(0x803EF, 0x74);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE73E6254);
    EXPECT_EQ(cpu.get_ebx(), 0xB35B03EF);
    EXPECT_EQ(cpu.get_ecx(), 0x130F92AC);
    EXPECT_EQ(cpu.get_edx(), 0xD5511D7E);
    EXPECT_EQ(cpu.get_esi(), 0x0080FFE6);
    EXPECT_EQ(cpu.get_edi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000000E);
    EXPECT_EQ(cpu.get_cs(), 0x0000FCB7);
    EXPECT_EQ(cpu.get_ds(), 0x00007FFF);
    EXPECT_EQ(cpu.get_es(), 0x0000D0A6);
    EXPECT_EQ(cpu.get_fs(), 0x0000C8AB);
    EXPECT_EQ(cpu.get_gs(), 0x000005B5);
    EXPECT_EQ(cpu.get_ss(), 0x00000FE9);
    EXPECT_EQ(cpu.get_eip(), 0x00000094);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C83);

    // Final RAM entries
}

//
// mul dword [ds:ebx-1B8Fh]
//
TEST_F(Test386, mul_dword_ds_ebx_1B8Fh_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB8573002);
    cpu.set_ebx(0x0000FFFF);
    cpu.set_ecx(0x00008000);
    cpu.set_edx(0x790E02DC);
    cpu.set_esi(0xEF7BF5BA);
    cpu.set_edi(0x20A6C341);
    cpu.set_ebp(0x12015F8A);
    cpu.set_esp(0x0000A74C);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00002077);
    cpu.set_es(0x00000269);
    cpu.set_fs(0x000033A5);
    cpu.set_gs(0x0000F7F8);
    cpu.set_ss(0x00000081);
    cpu.set_eip(0x00004398);
    cpu.set_eflags(0xFFFC04D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x104388, 0x66);
    machine.mem_store_byte(0x104389, 0x67);
    machine.mem_store_byte(0x10438A, 0xF7);
    machine.mem_store_byte(0x10438B, 0xA3);
    machine.mem_store_byte(0x10438C, 0x71);
    machine.mem_store_byte(0x10438D, 0xE4);
    machine.mem_store_byte(0x10438E, 0xFF);
    machine.mem_store_byte(0x10438F, 0xFF);
    machine.mem_store_byte(0x104390, 0xF4);
    machine.mem_store_byte(0x104391, 0x1C);
    machine.mem_store_byte(0x104392, 0x83);
    machine.mem_store_byte(0x104393, 0x6E);
    machine.mem_store_byte(0x2EBE0, 0xA4);
    machine.mem_store_byte(0x2EBE1, 0xEE);
    machine.mem_store_byte(0x2EBE2, 0x4E);
    machine.mem_store_byte(0x2EBE3, 0x28);
    machine.mem_store_byte(0x104394, 0xB3);
    machine.mem_store_byte(0x104395, 0x05);
    machine.mem_store_byte(0x104396, 0xE8);
    machine.mem_store_byte(0x104397, 0x58);
    machine.mem_store_byte(0x104398, 0x18);
    machine.mem_store_byte(0x104399, 0x0F);
    machine.mem_store_byte(0x10439A, 0x79);
    machine.mem_store_byte(0x10439B, 0x3F);
    machine.mem_store_byte(0x10439C, 0xFA);
    machine.mem_store_byte(0x10439D, 0x4B);
    machine.mem_store_byte(0x10439E, 0x4B);
    machine.mem_store_byte(0x10439F, 0x2B);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x17189D48);
    EXPECT_EQ(cpu.get_ebx(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x00008000);
    EXPECT_EQ(cpu.get_edx(), 0x1D0675E8);
    EXPECT_EQ(cpu.get_esi(), 0xEF7BF5BA);
    EXPECT_EQ(cpu.get_edi(), 0x20A6C341);
    EXPECT_EQ(cpu.get_ebp(), 0x12015F8A);
    EXPECT_EQ(cpu.get_esp(), 0x0000A74C);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x00002077);
    EXPECT_EQ(cpu.get_es(), 0x00000269);
    EXPECT_EQ(cpu.get_fs(), 0x000033A5);
    EXPECT_EQ(cpu.get_gs(), 0x0000F7F8);
    EXPECT_EQ(cpu.get_ss(), 0x00000081);
    EXPECT_EQ(cpu.get_eip(), 0x000043A1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C93);

    // Final RAM entries
}

//
// mul dword [ss:bp-4C06h]
//
TEST_F(Test386, mul_dword_ss_bp_4C06h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB8573002);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x00008000);
    cpu.set_edx(0x790E02DC);
    cpu.set_esi(0xEF7BF5BA);
    cpu.set_edi(0x20A6C341);
    cpu.set_ebp(0x12015F8A);
    cpu.set_esp(0x0000A74C);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00002077);
    cpu.set_es(0x00000269);
    cpu.set_fs(0x000033A5);
    cpu.set_gs(0x0000F7F8);
    cpu.set_ss(0x00000081);
    cpu.set_eip(0x00004398);
    cpu.set_eflags(0xFFFC04D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x104388, 0x36);
    machine.mem_store_byte(0x104389, 0x66);
    machine.mem_store_byte(0x10438A, 0xF7);
    machine.mem_store_byte(0x10438B, 0xA6);
    machine.mem_store_byte(0x10438C, 0xFA);
    machine.mem_store_byte(0x10438D, 0xB3);
    machine.mem_store_byte(0x10438E, 0xF4);
    machine.mem_store_byte(0x10438F, 0xB6);
    machine.mem_store_byte(0x104390, 0xB7);
    machine.mem_store_byte(0x104391, 0x1C);
    machine.mem_store_byte(0x104392, 0x83);
    machine.mem_store_byte(0x104393, 0x6E);
    machine.mem_store_byte(0x01B94, 0xFB);
    machine.mem_store_byte(0x01B95, 0xBC);
    machine.mem_store_byte(0x01B96, 0x25);
    machine.mem_store_byte(0x01B97, 0x83);
    machine.mem_store_byte(0x104394, 0xB3);
    machine.mem_store_byte(0x104395, 0x05);
    machine.mem_store_byte(0x104396, 0xE8);
    machine.mem_store_byte(0x104397, 0x58);
    machine.mem_store_byte(0x104398, 0x18);
    machine.mem_store_byte(0x104399, 0x0F);
    machine.mem_store_byte(0x10439A, 0x79);
    machine.mem_store_byte(0x10439B, 0x3F);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xBB0789F6);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x00008000);
    EXPECT_EQ(cpu.get_edx(), 0x5E6FCA3F);
    EXPECT_EQ(cpu.get_esi(), 0xEF7BF5BA);
    EXPECT_EQ(cpu.get_edi(), 0x20A6C341);
    EXPECT_EQ(cpu.get_ebp(), 0x12015F8A);
    EXPECT_EQ(cpu.get_esp(), 0x0000A74C);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x00002077);
    EXPECT_EQ(cpu.get_es(), 0x00000269);
    EXPECT_EQ(cpu.get_fs(), 0x000033A5);
    EXPECT_EQ(cpu.get_gs(), 0x0000F7F8);
    EXPECT_EQ(cpu.get_ss(), 0x00000081);
    EXPECT_EQ(cpu.get_eip(), 0x0000439F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C83);

    // Final RAM entries
}

//
// pop esp
//
TEST_F(Test386, pop_esp_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x169077A7);
    cpu.set_ebx(0x0000001A);
    cpu.set_ecx(0x0000FFFE);
    cpu.set_edx(0x8D9C8B5E);
    cpu.set_esi(0x0A049AD5);
    cpu.set_edi(0x28D327CF);
    cpu.set_ebp(0x06690EF3);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x000003FF);
    cpu.set_ds(0x0000D424);
    cpu.set_es(0x00009DC0);
    cpu.set_fs(0x0000BC17);
    cpu.set_gs(0x0000BB51);
    cpu.set_ss(0x0000DFFF);
    cpu.set_eip(0x0000FD08);
    cpu.set_eflags(0xFFFC00C7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x13CF8, 0x66);
    machine.mem_store_byte(0x13CF9, 0x5C);
    machine.mem_store_byte(0x13CFA, 0xF4);
    machine.mem_store_byte(0x13CFB, 0x2E);
    machine.mem_store_byte(0x13CFC, 0x3B);
    machine.mem_store_byte(0x13CFD, 0x6D);
    machine.mem_store_byte(0x13CFE, 0xD0);
    machine.mem_store_byte(0x13CFF, 0x23);
    machine.mem_store_byte(0x13D00, 0xBE);
    machine.mem_store_byte(0x13D01, 0x43);
    machine.mem_store_byte(0x13D02, 0xA4);
    machine.mem_store_byte(0x13D03, 0xB6);
    machine.mem_store_byte(0x13D04, 0xAC);
    machine.mem_store_byte(0x13D05, 0xFE);
    machine.mem_store_byte(0x13D06, 0x5B);
    machine.mem_store_byte(0x13D07, 0x1F);
    machine.mem_store_byte(0x13D08, 0x6F);
    machine.mem_store_byte(0x13D09, 0x0A);
    machine.mem_store_byte(0x13D0A, 0x9B);
    machine.mem_store_byte(0x13D0B, 0x1F);
    machine.mem_store_byte(0x13D0C, 0x52);
    machine.mem_store_byte(0x13D0D, 0x1A);
    machine.mem_store_byte(0x13D0E, 0x02);
    machine.mem_store_byte(0x13D0F, 0x18);
    machine.mem_store_byte(0x00030, 0xF6);
    machine.mem_store_byte(0x00031, 0x2A);
    machine.mem_store_byte(0x00032, 0x9D);
    machine.mem_store_byte(0x00033, 0xA9);
    machine.mem_store_byte(0xAC4C6, 0xF4);
    machine.mem_store_byte(0xAC4C7, 0x68);
    machine.mem_store_byte(0xAC4C8, 0xF4);
    machine.mem_store_byte(0xAC4C9, 0x88);
    machine.mem_store_byte(0xAC4CA, 0xF4);
    machine.mem_store_byte(0xAC4CB, 0x73);
    machine.mem_store_byte(0xAC4CC, 0xF4);
    machine.mem_store_byte(0xAC4CD, 0x10);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x169077A7);
    EXPECT_EQ(cpu.get_ebx(), 0x0000001A);
    EXPECT_EQ(cpu.get_ecx(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_edx(), 0x8D9C8B5E);
    EXPECT_EQ(cpu.get_esi(), 0x0A049AD5);
    EXPECT_EQ(cpu.get_edi(), 0x28D327CF);
    EXPECT_EQ(cpu.get_ebp(), 0x06690EF3);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x0000A99D);
    EXPECT_EQ(cpu.get_ds(), 0x0000D424);
    EXPECT_EQ(cpu.get_es(), 0x00009DC0);
    EXPECT_EQ(cpu.get_fs(), 0x0000BC17);
    EXPECT_EQ(cpu.get_gs(), 0x0000BB51);
    EXPECT_EQ(cpu.get_ss(), 0x0000DFFF);
    EXPECT_EQ(cpu.get_eip(), 0x00002AF7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEFFEC), 0xC7);
    EXPECT_EQ(memory.load8(0xEFFED), 0x00);
    EXPECT_EQ(memory.load8(0xEFFEA), 0xFF);
    EXPECT_EQ(memory.load8(0xEFFEB), 0x03);
    EXPECT_EQ(memory.load8(0xEFFE8), 0x08);
    EXPECT_EQ(memory.load8(0xEFFE9), 0xFD);
}

//
// rol byte [ds:bx+25h],80h
//
TEST_F(Test386, rol_byte_ds_bx_25h_80h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xBC48E7B3);
    cpu.set_ebx(0x5671A216);
    cpu.set_ecx(0x10E7928E);
    cpu.set_edx(0xFE3D9497);
    cpu.set_esi(0xC516597D);
    cpu.set_edi(0x7FFFFFFF);
    cpu.set_ebp(0xFFD83882);
    cpu.set_esp(0x000012DE);
    cpu.set_cs(0x00002E41);
    cpu.set_ds(0x0000DD5F);
    cpu.set_es(0x00001D19);
    cpu.set_fs(0x0000059B);
    cpu.set_gs(0x0000EDD5);
    cpu.set_ss(0x00000D8D);
    cpu.set_eip(0x00006F28);
    cpu.set_eflags(0xFFFC0496);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x35338, 0xC0);
    machine.mem_store_byte(0x35339, 0x47);
    machine.mem_store_byte(0x3533A, 0x25);
    machine.mem_store_byte(0x3533B, 0x80);
    machine.mem_store_byte(0x3533C, 0xF4);
    machine.mem_store_byte(0x3533D, 0xBC);
    machine.mem_store_byte(0x3533E, 0x2A);
    machine.mem_store_byte(0x3533F, 0x18);
    machine.mem_store_byte(0x35340, 0x01);
    machine.mem_store_byte(0x35341, 0xE3);
    machine.mem_store_byte(0x35342, 0x6F);
    machine.mem_store_byte(0x35343, 0xA8);
    machine.mem_store_byte(0xE782B, 0xD0);
    machine.mem_store_byte(0x35344, 0x44);
    machine.mem_store_byte(0x35345, 0x61);
    machine.mem_store_byte(0x35346, 0x07);
    machine.mem_store_byte(0x35347, 0x09);
    machine.mem_store_byte(0x35348, 0xE5);
    machine.mem_store_byte(0x35349, 0xE3);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xBC48E7B3);
    EXPECT_EQ(cpu.get_ebx(), 0x5671A216);
    EXPECT_EQ(cpu.get_ecx(), 0x10E7928E);
    EXPECT_EQ(cpu.get_edx(), 0xFE3D9497);
    EXPECT_EQ(cpu.get_esi(), 0xC516597D);
    EXPECT_EQ(cpu.get_edi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xFFD83882);
    EXPECT_EQ(cpu.get_esp(), 0x000012DE);
    EXPECT_EQ(cpu.get_cs(), 0x00002E41);
    EXPECT_EQ(cpu.get_ds(), 0x0000DD5F);
    EXPECT_EQ(cpu.get_es(), 0x00001D19);
    EXPECT_EQ(cpu.get_fs(), 0x0000059B);
    EXPECT_EQ(cpu.get_gs(), 0x0000EDD5);
    EXPECT_EQ(cpu.get_ss(), 0x00000D8D);
    EXPECT_EQ(cpu.get_eip(), 0x00006F2D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0496);

    // Final RAM entries
}

//
// shl ax,cl
//
TEST_F(Test386, shl_ax_cl_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE3777A2F);
    cpu.set_ebx(0x6B5BD173);
    cpu.set_ecx(0x00008000);
    cpu.set_edx(0x33D9DF28);
    cpu.set_esi(0x02CC6519);
    cpu.set_edi(0x66536C27);
    cpu.set_ebp(0x096A6414);
    cpu.set_esp(0x0000EA6E);
    cpu.set_cs(0x0000E1FA);
    cpu.set_ds(0x00003BE2);
    cpu.set_es(0x0000A44A);
    cpu.set_fs(0x0000EF8F);
    cpu.set_gs(0x0000C1C6);
    cpu.set_ss(0x0000DB58);
    cpu.set_eip(0x0000D0E8);
    cpu.set_eflags(0xFFFC04C3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEF088, 0x2E);
    machine.mem_store_byte(0xEF089, 0x36);
    machine.mem_store_byte(0xEF08A, 0x3E);
    machine.mem_store_byte(0xEF08B, 0xD3);
    machine.mem_store_byte(0xEF08C, 0xE0);
    machine.mem_store_byte(0xEF08D, 0xF4);
    machine.mem_store_byte(0xEF08E, 0xB3);
    machine.mem_store_byte(0xEF08F, 0x22);
    machine.mem_store_byte(0xEF090, 0x1B);
    machine.mem_store_byte(0xEF091, 0x3D);
    machine.mem_store_byte(0xEF092, 0x92);
    machine.mem_store_byte(0xEF093, 0xC7);
    machine.mem_store_byte(0xEF094, 0xB9);
    machine.mem_store_byte(0xEF095, 0xB6);
    machine.mem_store_byte(0xEF096, 0x1F);
    machine.mem_store_byte(0xEF097, 0x06);
    machine.mem_store_byte(0xEF098, 0x7A);
    machine.mem_store_byte(0xEF099, 0x01);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE3777A2F);
    EXPECT_EQ(cpu.get_ebx(), 0x6B5BD173);
    EXPECT_EQ(cpu.get_ecx(), 0x00008000);
    EXPECT_EQ(cpu.get_edx(), 0x33D9DF28);
    EXPECT_EQ(cpu.get_esi(), 0x02CC6519);
    EXPECT_EQ(cpu.get_edi(), 0x66536C27);
    EXPECT_EQ(cpu.get_ebp(), 0x096A6414);
    EXPECT_EQ(cpu.get_esp(), 0x0000EA6E);
    EXPECT_EQ(cpu.get_cs(), 0x0000E1FA);
    EXPECT_EQ(cpu.get_ds(), 0x00003BE2);
    EXPECT_EQ(cpu.get_es(), 0x0000A44A);
    EXPECT_EQ(cpu.get_fs(), 0x0000EF8F);
    EXPECT_EQ(cpu.get_gs(), 0x0000C1C6);
    EXPECT_EQ(cpu.get_ss(), 0x0000DB58);
    EXPECT_EQ(cpu.get_eip(), 0x0000D0EE);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C3);

    // Final RAM entries
}

//
// shld [ds:esi+esi*1+2A94h],bp,1Dh
//
TEST_F(Test386, shld_ds_esi_esi_1_2A94h_bp_1Dh_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x200F0D1D);
    cpu.set_ebx(0x00008000);
    cpu.set_ecx(0x00008000);
    cpu.set_edx(0xF542F3EE);
    cpu.set_esi(0x0000631D);
    cpu.set_edi(0x57A11F8B);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x00008000);
    cpu.set_cs(0x0000ECCC);
    cpu.set_ds(0x0000395E);
    cpu.set_es(0x0000300D);
    cpu.set_fs(0x00001188);
    cpu.set_gs(0x00005641);
    cpu.set_ss(0x00002297);
    cpu.set_eip(0x00006C28);
    cpu.set_eflags(0xFFFC08D7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF38E8, 0x67);
    machine.mem_store_byte(0xF38E9, 0x0F);
    machine.mem_store_byte(0xF38EA, 0xA4);
    machine.mem_store_byte(0xF38EB, 0xAC);
    machine.mem_store_byte(0xF38EC, 0x36);
    machine.mem_store_byte(0xF38ED, 0x94);
    machine.mem_store_byte(0xF38EE, 0x2A);
    machine.mem_store_byte(0xF38EF, 0x00);
    machine.mem_store_byte(0xF38F0, 0x00);
    machine.mem_store_byte(0xF38F1, 0x1D);
    machine.mem_store_byte(0xF38F2, 0xF4);
    machine.mem_store_byte(0xF38F3, 0xB0);
    machine.mem_store_byte(0xF38F4, 0x71);
    machine.mem_store_byte(0xF38F5, 0x64);
    machine.mem_store_byte(0xF38F6, 0xDA);
    machine.mem_store_byte(0xF38F7, 0x72);
    machine.mem_store_byte(0xF38F8, 0x53);
    machine.mem_store_byte(0xF38F9, 0x39);
    machine.mem_store_byte(0x486AE, 0xE9);
    machine.mem_store_byte(0x486AF, 0xA7);
    machine.mem_store_byte(0xF38FA, 0x53);
    machine.mem_store_byte(0xF38FB, 0xC7);
    machine.mem_store_byte(0xF38FC, 0xF9);
    machine.mem_store_byte(0xF38FD, 0x92);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x200F0D1D);
    EXPECT_EQ(cpu.get_ebx(), 0x00008000);
    EXPECT_EQ(cpu.get_ecx(), 0x00008000);
    EXPECT_EQ(cpu.get_edx(), 0xF542F3EE);
    EXPECT_EQ(cpu.get_esi(), 0x0000631D);
    EXPECT_EQ(cpu.get_edi(), 0x57A11F8B);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x00008000);
    EXPECT_EQ(cpu.get_cs(), 0x0000ECCC);
    EXPECT_EQ(cpu.get_ds(), 0x0000395E);
    EXPECT_EQ(cpu.get_es(), 0x0000300D);
    EXPECT_EQ(cpu.get_fs(), 0x00001188);
    EXPECT_EQ(cpu.get_gs(), 0x00005641);
    EXPECT_EQ(cpu.get_ss(), 0x00002297);
    EXPECT_EQ(cpu.get_eip(), 0x00006C33);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x486AE), 0x00);
    EXPECT_EQ(memory.load8(0x486AF), 0x20);
}

//
// shld [ss:bp+36DCh],bp,94h
//
TEST_F(Test386, shld_ss_bp_36DCh_bp_94h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x200F0D1D);
    cpu.set_ebx(0x00008000);
    cpu.set_ecx(0x00008000);
    cpu.set_edx(0xF542F3EE);
    cpu.set_esi(0x87C1631D);
    cpu.set_edi(0x57A11F8B);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x00008000);
    cpu.set_cs(0x0000ECCC);
    cpu.set_ds(0x0000395E);
    cpu.set_es(0x0000300D);
    cpu.set_fs(0x00001188);
    cpu.set_gs(0x00005641);
    cpu.set_ss(0x00002297);
    cpu.set_eip(0x00006C28);
    cpu.set_eflags(0xFFFC08D7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF38E8, 0x0F);
    machine.mem_store_byte(0xF38E9, 0xA4);
    machine.mem_store_byte(0xF38EA, 0xAE);
    machine.mem_store_byte(0xF38EB, 0xDC);
    machine.mem_store_byte(0xF38EC, 0x36);
    machine.mem_store_byte(0xF38ED, 0x94);
    machine.mem_store_byte(0xF38EE, 0xF4);
    machine.mem_store_byte(0xF38EF, 0xE3);
    machine.mem_store_byte(0xF38F0, 0xBC);
    machine.mem_store_byte(0xF38F1, 0xF6);
    machine.mem_store_byte(0xF38F2, 0x92);
    machine.mem_store_byte(0xF38F3, 0xB0);
    machine.mem_store_byte(0xF38F4, 0x71);
    machine.mem_store_byte(0xF38F5, 0x64);
    machine.mem_store_byte(0x2604D, 0x0A);
    machine.mem_store_byte(0x2604E, 0x95);
    machine.mem_store_byte(0xF38F6, 0xDA);
    machine.mem_store_byte(0xF38F7, 0x72);
    machine.mem_store_byte(0xF38F8, 0x53);
    machine.mem_store_byte(0xF38F9, 0x39);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x200F0D1D);
    EXPECT_EQ(cpu.get_ebx(), 0x00008000);
    EXPECT_EQ(cpu.get_ecx(), 0x00008000);
    EXPECT_EQ(cpu.get_edx(), 0xF542F3EE);
    EXPECT_EQ(cpu.get_esi(), 0x87C1631D);
    EXPECT_EQ(cpu.get_edi(), 0x57A11F8B);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x00008000);
    EXPECT_EQ(cpu.get_cs(), 0x0000ECCC);
    EXPECT_EQ(cpu.get_ds(), 0x0000395E);
    EXPECT_EQ(cpu.get_es(), 0x0000300D);
    EXPECT_EQ(cpu.get_fs(), 0x00001188);
    EXPECT_EQ(cpu.get_gs(), 0x00005641);
    EXPECT_EQ(cpu.get_ss(), 0x00002297);
    EXPECT_EQ(cpu.get_eip(), 0x00006C2F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2604D), 0x10);
    EXPECT_EQ(memory.load8(0x2604E), 0x00);
}

//
// shrd di,cx,81h
//
TEST_F(Test386, shrd_di_cx_81h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x874F3E1B);
    cpu.set_ebx(0x8CBBBACC);
    cpu.set_ecx(0x9A7CE529);
    cpu.set_edx(0xFFFFFFFF);
    cpu.set_esi(0x2524F029);
    cpu.set_edi(0xF214A594);
    cpu.set_ebp(0x9108A417);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x000046F4);
    cpu.set_ds(0x0000000B);
    cpu.set_es(0x0000D1D8);
    cpu.set_fs(0x0000DEEA);
    cpu.set_gs(0x00004798);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x000059F8);
    cpu.set_eflags(0xFFFC08D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4C938, 0x67);
    machine.mem_store_byte(0x4C939, 0x0F);
    machine.mem_store_byte(0x4C93A, 0xAC);
    machine.mem_store_byte(0x4C93B, 0xCF);
    machine.mem_store_byte(0x4C93C, 0x81);
    machine.mem_store_byte(0x4C93D, 0xF4);
    machine.mem_store_byte(0x4C93E, 0x95);
    machine.mem_store_byte(0x4C93F, 0xF7);
    machine.mem_store_byte(0x4C940, 0x0E);
    machine.mem_store_byte(0x4C941, 0xBF);
    machine.mem_store_byte(0x4C942, 0x6C);
    machine.mem_store_byte(0x4C943, 0x68);
    machine.mem_store_byte(0x4C944, 0xE6);
    machine.mem_store_byte(0x4C945, 0x01);
    machine.mem_store_byte(0x4C946, 0x92);
    machine.mem_store_byte(0x4C947, 0xD9);
    machine.mem_store_byte(0x4C948, 0x50);
    machine.mem_store_byte(0x4C949, 0xA5);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x874F3E1B);
    EXPECT_EQ(cpu.get_ebx(), 0x8CBBBACC);
    EXPECT_EQ(cpu.get_ecx(), 0x9A7CE529);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0x2524F029);
    EXPECT_EQ(cpu.get_edi(), 0xF214D2CA);
    EXPECT_EQ(cpu.get_ebp(), 0x9108A417);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x000046F4);
    EXPECT_EQ(cpu.get_ds(), 0x0000000B);
    EXPECT_EQ(cpu.get_es(), 0x0000D1D8);
    EXPECT_EQ(cpu.get_fs(), 0x0000DEEA);
    EXPECT_EQ(cpu.get_gs(), 0x00004798);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x000059FE);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0096);

    // Final RAM entries
}

//
// shrd edi,ecx,81h
//
TEST_F(Test386, shrd_edi_ecx_81h_batch2)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x874F3E1B);
    cpu.set_ebx(0x8CBBBACC);
    cpu.set_ecx(0x9A7CE529);
    cpu.set_edx(0xFFFFFFFF);
    cpu.set_esi(0x2524F029);
    cpu.set_edi(0xF214A594);
    cpu.set_ebp(0x9108A417);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x000046F4);
    cpu.set_ds(0x0000000B);
    cpu.set_es(0x0000D1D8);
    cpu.set_fs(0x0000DEEA);
    cpu.set_gs(0x00004798);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x000059F8);
    cpu.set_eflags(0xFFFC08D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4C938, 0x67);
    machine.mem_store_byte(0x4C939, 0x66);
    machine.mem_store_byte(0x4C93A, 0x0F);
    machine.mem_store_byte(0x4C93B, 0xAC);
    machine.mem_store_byte(0x4C93C, 0xCF);
    machine.mem_store_byte(0x4C93D, 0x81);
    machine.mem_store_byte(0x4C93E, 0xF4);
    machine.mem_store_byte(0x4C93F, 0xF7);
    machine.mem_store_byte(0x4C940, 0x0E);
    machine.mem_store_byte(0x4C941, 0xBF);
    machine.mem_store_byte(0x4C942, 0x6C);
    machine.mem_store_byte(0x4C943, 0x68);
    machine.mem_store_byte(0x4C944, 0xE6);
    machine.mem_store_byte(0x4C945, 0x01);
    machine.mem_store_byte(0x4C946, 0x92);
    machine.mem_store_byte(0x4C947, 0xD9);
    machine.mem_store_byte(0x4C948, 0x50);
    machine.mem_store_byte(0x4C949, 0xA5);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x874F3E1B);
    EXPECT_EQ(cpu.get_ebx(), 0x8CBBBACC);
    EXPECT_EQ(cpu.get_ecx(), 0x9A7CE529);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0x2524F029);
    EXPECT_EQ(cpu.get_edi(), 0xF90A52CA);
    EXPECT_EQ(cpu.get_ebp(), 0x9108A417);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x000046F4);
    EXPECT_EQ(cpu.get_ds(), 0x0000000B);
    EXPECT_EQ(cpu.get_es(), 0x0000D1D8);
    EXPECT_EQ(cpu.get_fs(), 0x0000DEEA);
    EXPECT_EQ(cpu.get_gs(), 0x00004798);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x000059FF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0096);

    // Final RAM entries
}
