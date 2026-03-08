#include "test386.h"

//
// a32 outsd
//
TEST_F(Test386, a32_outsd_batch13)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF6CB8A1F);
    cpu.set_ebx(0xE9A19794);
    cpu.set_ecx(0xC4239CAD);
    cpu.set_edx(0xFBF02782);
    cpu.set_esi(0x0000FFFF);
    cpu.set_edi(0xBBBE37A4);
    cpu.set_ebp(0x04E32E9A);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F58F);
    cpu.set_ds(0x00000283);
    cpu.set_es(0x00003C8B);
    cpu.set_fs(0x00000129);
    cpu.set_gs(0x0000B006);
    cpu.set_ss(0x00001824);
    cpu.set_eip(0x00004958);
    cpu.set_eflags(0xFFFC04C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFA248, 0x67);
    machine.mem_store_byte(0xFA249, 0x66);
    machine.mem_store_byte(0xFA24A, 0x6F);
    machine.mem_store_byte(0xFA24B, 0xF4);
    machine.mem_store_byte(0xFA24C, 0xFF);
    machine.mem_store_byte(0xFA24D, 0xFF);
    machine.mem_store_byte(0xFA24E, 0xFF);
    machine.mem_store_byte(0xFA24F, 0xFF);
    machine.mem_store_byte(0xFA250, 0xFF);
    machine.mem_store_byte(0xFA251, 0xFF);
    machine.mem_store_byte(0xFA252, 0xFF);
    machine.mem_store_byte(0xFA253, 0xFF);
    machine.mem_store_byte(0xFA254, 0xFF);
    machine.mem_store_byte(0xFA255, 0xFF);
    machine.mem_store_byte(0xFA256, 0xFF);
    machine.mem_store_byte(0xFA257, 0xFF);
    machine.mem_store_byte(0x00034, 0x58);
    machine.mem_store_byte(0x00035, 0xA1);
    machine.mem_store_byte(0x00036, 0x0E);
    machine.mem_store_byte(0x00037, 0x2C);
    machine.mem_store_byte(0x36238, 0xF4);
    machine.mem_store_byte(0x36239, 0xFF);
    machine.mem_store_byte(0x3623A, 0xF4);
    machine.mem_store_byte(0x3623B, 0xFF);
    machine.mem_store_byte(0x3623C, 0xF4);
    machine.mem_store_byte(0x3623D, 0xFF);
    machine.mem_store_byte(0x3623E, 0xF4);
    machine.mem_store_byte(0x3623F, 0xFF);
    machine.mem_store_byte(0x36240, 0xF4);
    machine.mem_store_byte(0x36241, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF6CB8A1F);
    EXPECT_EQ(cpu.get_ebx(), 0xE9A19794);
    EXPECT_EQ(cpu.get_ecx(), 0xC4239CAD);
    EXPECT_EQ(cpu.get_edx(), 0xFBF02782);
    EXPECT_EQ(cpu.get_esi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edi(), 0xBBBE37A4);
    EXPECT_EQ(cpu.get_ebp(), 0x04E32E9A);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x00002C0E);
    EXPECT_EQ(cpu.get_ds(), 0x00000283);
    EXPECT_EQ(cpu.get_es(), 0x00003C8B);
    EXPECT_EQ(cpu.get_fs(), 0x00000129);
    EXPECT_EQ(cpu.get_gs(), 0x0000B006);
    EXPECT_EQ(cpu.get_ss(), 0x00001824);
    EXPECT_EQ(cpu.get_eip(), 0x0000A159);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x18246), 0xC6);
    EXPECT_EQ(memory.load8(0x18247), 0x04);
    EXPECT_EQ(memory.load8(0x18244), 0x8F);
    EXPECT_EQ(memory.load8(0x18245), 0xF5);
    EXPECT_EQ(memory.load8(0x18242), 0x58);
    EXPECT_EQ(memory.load8(0x18243), 0x49);
}

//
// a32 outsw
//
TEST_F(Test386, a32_outsw_batch13)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF6CB8A1F);
    cpu.set_ebx(0xE9A19794);
    cpu.set_ecx(0xC4239CAD);
    cpu.set_edx(0xFBF02782);
    cpu.set_esi(0x0000FFFF);
    cpu.set_edi(0xBBBE37A4);
    cpu.set_ebp(0x04E32E9A);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F58F);
    cpu.set_ds(0x00000283);
    cpu.set_es(0x00003C8B);
    cpu.set_fs(0x00000129);
    cpu.set_gs(0x0000B006);
    cpu.set_ss(0x00001824);
    cpu.set_eip(0x00004958);
    cpu.set_eflags(0xFFFC04C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFA248, 0x67);
    machine.mem_store_byte(0xFA249, 0x6F);
    machine.mem_store_byte(0xFA24A, 0xF4);
    machine.mem_store_byte(0xFA24B, 0xFF);
    machine.mem_store_byte(0xFA24C, 0xFF);
    machine.mem_store_byte(0xFA24D, 0xFF);
    machine.mem_store_byte(0xFA24E, 0xFF);
    machine.mem_store_byte(0xFA24F, 0xFF);
    machine.mem_store_byte(0xFA250, 0xFF);
    machine.mem_store_byte(0xFA251, 0xFF);
    machine.mem_store_byte(0xFA252, 0xFF);
    machine.mem_store_byte(0xFA253, 0xFF);
    machine.mem_store_byte(0xFA254, 0xFF);
    machine.mem_store_byte(0xFA255, 0xFF);
    machine.mem_store_byte(0xFA256, 0xFF);
    machine.mem_store_byte(0xFA257, 0xFF);
    machine.mem_store_byte(0x00034, 0x58);
    machine.mem_store_byte(0x00035, 0xA1);
    machine.mem_store_byte(0x00036, 0x0E);
    machine.mem_store_byte(0x00037, 0x2C);
    machine.mem_store_byte(0x36238, 0xF4);
    machine.mem_store_byte(0x36239, 0xFF);
    machine.mem_store_byte(0x3623A, 0xF4);
    machine.mem_store_byte(0x3623B, 0xFF);
    machine.mem_store_byte(0x3623C, 0xF4);
    machine.mem_store_byte(0x3623D, 0xFF);
    machine.mem_store_byte(0x3623E, 0xF4);
    machine.mem_store_byte(0x3623F, 0xFF);
    machine.mem_store_byte(0x36240, 0xF4);
    machine.mem_store_byte(0x36241, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF6CB8A1F);
    EXPECT_EQ(cpu.get_ebx(), 0xE9A19794);
    EXPECT_EQ(cpu.get_ecx(), 0xC4239CAD);
    EXPECT_EQ(cpu.get_edx(), 0xFBF02782);
    EXPECT_EQ(cpu.get_esi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edi(), 0xBBBE37A4);
    EXPECT_EQ(cpu.get_ebp(), 0x04E32E9A);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x00002C0E);
    EXPECT_EQ(cpu.get_ds(), 0x00000283);
    EXPECT_EQ(cpu.get_es(), 0x00003C8B);
    EXPECT_EQ(cpu.get_fs(), 0x00000129);
    EXPECT_EQ(cpu.get_gs(), 0x0000B006);
    EXPECT_EQ(cpu.get_ss(), 0x00001824);
    EXPECT_EQ(cpu.get_eip(), 0x0000A159);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x18246), 0xC6);
    EXPECT_EQ(memory.load8(0x18247), 0x04);
    EXPECT_EQ(memory.load8(0x18244), 0x8F);
    EXPECT_EQ(memory.load8(0x18245), 0xF5);
    EXPECT_EQ(memory.load8(0x18242), 0x58);
    EXPECT_EQ(memory.load8(0x18243), 0x49);
}

//
// bound bp,[ds:edi]
//
TEST_F(Test386, bound_bp_ds_edi_batch13)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x15D5F859);
    cpu.set_ebx(0x9F986FFD);
    cpu.set_ecx(0x01405732);
    cpu.set_edx(0x41CE9C12);
    cpu.set_esi(0x7EDB467A);
    cpu.set_edi(0x0000FFFF);
    cpu.set_ebp(0xF08022B6);
    cpu.set_esp(0x0000BE48);
    cpu.set_cs(0x0000D0C1);
    cpu.set_ds(0x0000CD98);
    cpu.set_es(0x0000B46D);
    cpu.set_fs(0x0000EDB5);
    cpu.set_gs(0x00002D91);
    cpu.set_ss(0x0000156B);
    cpu.set_eip(0x0000F9D0);
    cpu.set_eflags(0xFFFC00C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE05E0, 0x67);
    machine.mem_store_byte(0xE05E1, 0x62);
    machine.mem_store_byte(0xE05E2, 0x2F);
    machine.mem_store_byte(0xE05E3, 0xF4);
    machine.mem_store_byte(0xE05E4, 0x00);
    machine.mem_store_byte(0xE05E5, 0x00);
    machine.mem_store_byte(0xE05E6, 0x00);
    machine.mem_store_byte(0xE05E7, 0x00);
    machine.mem_store_byte(0xE05E8, 0x00);
    machine.mem_store_byte(0xE05E9, 0x00);
    machine.mem_store_byte(0xE05EA, 0x00);
    machine.mem_store_byte(0xE05EB, 0x00);
    machine.mem_store_byte(0xE05EC, 0x00);
    machine.mem_store_byte(0xE05ED, 0x00);
    machine.mem_store_byte(0xE05EE, 0x00);
    machine.mem_store_byte(0xE05EF, 0x00);
    machine.mem_store_byte(0x00034, 0xAF);
    machine.mem_store_byte(0x00035, 0x2F);
    machine.mem_store_byte(0x00036, 0x1A);
    machine.mem_store_byte(0x00037, 0x8C);
    machine.mem_store_byte(0x8F14E, 0x00);
    machine.mem_store_byte(0x8F14F, 0xF4);
    machine.mem_store_byte(0x8F150, 0x00);
    machine.mem_store_byte(0x8F151, 0xF4);
    machine.mem_store_byte(0x8F152, 0x00);
    machine.mem_store_byte(0x8F153, 0xF4);
    machine.mem_store_byte(0x8F154, 0x00);
    machine.mem_store_byte(0x8F155, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x15D5F859);
    EXPECT_EQ(cpu.get_ebx(), 0x9F986FFD);
    EXPECT_EQ(cpu.get_ecx(), 0x01405732);
    EXPECT_EQ(cpu.get_edx(), 0x41CE9C12);
    EXPECT_EQ(cpu.get_esi(), 0x7EDB467A);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xF08022B6);
    EXPECT_EQ(cpu.get_esp(), 0x0000BE42);
    EXPECT_EQ(cpu.get_cs(), 0x00008C1A);
    EXPECT_EQ(cpu.get_ds(), 0x0000CD98);
    EXPECT_EQ(cpu.get_es(), 0x0000B46D);
    EXPECT_EQ(cpu.get_fs(), 0x0000EDB5);
    EXPECT_EQ(cpu.get_gs(), 0x00002D91);
    EXPECT_EQ(cpu.get_ss(), 0x0000156B);
    EXPECT_EQ(cpu.get_eip(), 0x00002FB0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x214F6), 0xC6);
    EXPECT_EQ(memory.load8(0x214F7), 0x00);
    EXPECT_EQ(memory.load8(0x214F4), 0xC1);
    EXPECT_EQ(memory.load8(0x214F5), 0xD0);
    EXPECT_EQ(memory.load8(0x214F2), 0xD0);
    EXPECT_EQ(memory.load8(0x214F3), 0xF9);
}

//
// bound ebp,[ds:edi]
//
TEST_F(Test386, bound_ebp_ds_edi_batch13)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x15D5F859);
    cpu.set_ebx(0x9F986FFD);
    cpu.set_ecx(0x01405732);
    cpu.set_edx(0x41CE9C12);
    cpu.set_esi(0x7EDB467A);
    cpu.set_edi(0x0000FFFF);
    cpu.set_ebp(0xF08022B6);
    cpu.set_esp(0x0000BE48);
    cpu.set_cs(0x0000D0C1);
    cpu.set_ds(0x0000CD98);
    cpu.set_es(0x0000B46D);
    cpu.set_fs(0x0000EDB5);
    cpu.set_gs(0x00002D91);
    cpu.set_ss(0x0000156B);
    cpu.set_eip(0x0000F9D0);
    cpu.set_eflags(0xFFFC00C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE05E0, 0x67);
    machine.mem_store_byte(0xE05E1, 0x66);
    machine.mem_store_byte(0xE05E2, 0x62);
    machine.mem_store_byte(0xE05E3, 0x2F);
    machine.mem_store_byte(0xE05E4, 0xF4);
    machine.mem_store_byte(0xE05E5, 0x00);
    machine.mem_store_byte(0xE05E6, 0x00);
    machine.mem_store_byte(0xE05E7, 0x00);
    machine.mem_store_byte(0xE05E8, 0x00);
    machine.mem_store_byte(0xE05E9, 0x00);
    machine.mem_store_byte(0xE05EA, 0x00);
    machine.mem_store_byte(0xE05EB, 0x00);
    machine.mem_store_byte(0xE05EC, 0x00);
    machine.mem_store_byte(0xE05ED, 0x00);
    machine.mem_store_byte(0xE05EE, 0x00);
    machine.mem_store_byte(0xE05EF, 0x00);
    machine.mem_store_byte(0xE05F0, 0x00);
    machine.mem_store_byte(0xE05F1, 0x00);
    machine.mem_store_byte(0xE05F2, 0x00);
    machine.mem_store_byte(0xE05F3, 0x00);
    machine.mem_store_byte(0x00034, 0xAF);
    machine.mem_store_byte(0x00035, 0x2F);
    machine.mem_store_byte(0x00036, 0x1A);
    machine.mem_store_byte(0x00037, 0x8C);
    machine.mem_store_byte(0x8F14E, 0x00);
    machine.mem_store_byte(0x8F14F, 0xF4);
    machine.mem_store_byte(0x8F150, 0x00);
    machine.mem_store_byte(0x8F151, 0xF4);
    machine.mem_store_byte(0x8F152, 0x00);
    machine.mem_store_byte(0x8F153, 0xF4);
    machine.mem_store_byte(0x8F154, 0x00);
    machine.mem_store_byte(0x8F155, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x15D5F859);
    EXPECT_EQ(cpu.get_ebx(), 0x9F986FFD);
    EXPECT_EQ(cpu.get_ecx(), 0x01405732);
    EXPECT_EQ(cpu.get_edx(), 0x41CE9C12);
    EXPECT_EQ(cpu.get_esi(), 0x7EDB467A);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xF08022B6);
    EXPECT_EQ(cpu.get_esp(), 0x0000BE42);
    EXPECT_EQ(cpu.get_cs(), 0x00008C1A);
    EXPECT_EQ(cpu.get_ds(), 0x0000CD98);
    EXPECT_EQ(cpu.get_es(), 0x0000B46D);
    EXPECT_EQ(cpu.get_fs(), 0x0000EDB5);
    EXPECT_EQ(cpu.get_gs(), 0x00002D91);
    EXPECT_EQ(cpu.get_ss(), 0x0000156B);
    EXPECT_EQ(cpu.get_eip(), 0x00002FB0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x214F6), 0xC6);
    EXPECT_EQ(memory.load8(0x214F7), 0x00);
    EXPECT_EQ(memory.load8(0x214F4), 0xC1);
    EXPECT_EQ(memory.load8(0x214F5), 0xD0);
    EXPECT_EQ(memory.load8(0x214F2), 0xD0);
    EXPECT_EQ(memory.load8(0x214F3), 0xF9);
}

//
// bt [gs:ecx],edi
//
TEST_F(Test386, bt_gs_ecx_edi_batch13)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x04FAD39B);
    cpu.set_ebx(0xB5C2C4FD);
    cpu.set_ecx(0x0000FD00);
    cpu.set_edx(0xBB560534);
    cpu.set_esi(0xFE3ABA2E);
    cpu.set_edi(0x0000836F);
    cpu.set_ebp(0xC8B2B5B3);
    cpu.set_esp(0x0000DCA4);
    cpu.set_cs(0x00003C3B);
    cpu.set_ds(0x00000EE0);
    cpu.set_es(0x000034FD);
    cpu.set_fs(0x0000136A);
    cpu.set_gs(0x00000250);
    cpu.set_ss(0x0000CD5D);
    cpu.set_eip(0x0000D020);
    cpu.set_eflags(0xFFFC0802);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x493D0, 0x36);
    machine.mem_store_byte(0x493D1, 0x64);
    machine.mem_store_byte(0x493D2, 0x64);
    machine.mem_store_byte(0x493D3, 0x65);
    machine.mem_store_byte(0x493D4, 0x67);
    machine.mem_store_byte(0x493D5, 0x66);
    machine.mem_store_byte(0x493D6, 0x0F);
    machine.mem_store_byte(0x493D7, 0xA3);
    machine.mem_store_byte(0x493D8, 0x39);
    machine.mem_store_byte(0x493D9, 0xF4);
    machine.mem_store_byte(0x493DA, 0xF7);
    machine.mem_store_byte(0x493DB, 0xA9);
    machine.mem_store_byte(0x493DC, 0x18);
    machine.mem_store_byte(0x493DD, 0xB3);
    machine.mem_store_byte(0x493DE, 0x5A);
    machine.mem_store_byte(0x493DF, 0x3B);
    machine.mem_store_byte(0x493E0, 0x03);
    machine.mem_store_byte(0x493E1, 0x2D);
    machine.mem_store_byte(0x493E2, 0x14);
    machine.mem_store_byte(0x493E3, 0xC8);
    machine.mem_store_byte(0x493E4, 0x4D);
    machine.mem_store_byte(0x493E5, 0xC6);
    machine.mem_store_byte(0x00034, 0xAA);
    machine.mem_store_byte(0x00035, 0x05);
    machine.mem_store_byte(0x00036, 0xDF);
    machine.mem_store_byte(0x00037, 0xFC);
    machine.mem_store_byte(0xFD39A, 0xF4);
    machine.mem_store_byte(0xFD39B, 0xD9);
    machine.mem_store_byte(0xFD39C, 0xF4);
    machine.mem_store_byte(0xFD39D, 0x85);
    machine.mem_store_byte(0xFD39E, 0xF4);
    machine.mem_store_byte(0xFD39F, 0x69);
    machine.mem_store_byte(0xFD3A0, 0xF4);
    machine.mem_store_byte(0xFD3A1, 0x12);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x04FAD39B);
    EXPECT_EQ(cpu.get_ebx(), 0xB5C2C4FD);
    EXPECT_EQ(cpu.get_ecx(), 0x0000FD00);
    EXPECT_EQ(cpu.get_edx(), 0xBB560534);
    EXPECT_EQ(cpu.get_esi(), 0xFE3ABA2E);
    EXPECT_EQ(cpu.get_edi(), 0x0000836F);
    EXPECT_EQ(cpu.get_ebp(), 0xC8B2B5B3);
    EXPECT_EQ(cpu.get_esp(), 0x0000DC9E);
    EXPECT_EQ(cpu.get_cs(), 0x0000FCDF);
    EXPECT_EQ(cpu.get_ds(), 0x00000EE0);
    EXPECT_EQ(cpu.get_es(), 0x000034FD);
    EXPECT_EQ(cpu.get_fs(), 0x0000136A);
    EXPECT_EQ(cpu.get_gs(), 0x00000250);
    EXPECT_EQ(cpu.get_ss(), 0x0000CD5D);
    EXPECT_EQ(cpu.get_eip(), 0x000005AB);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0802);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDB272), 0x02);
    EXPECT_EQ(memory.load8(0xDB273), 0x08);
    EXPECT_EQ(memory.load8(0xDB270), 0x3B);
    EXPECT_EQ(memory.load8(0xDB271), 0x3C);
    EXPECT_EQ(memory.load8(0xDB26E), 0x20);
    EXPECT_EQ(memory.load8(0xDB26F), 0xD0);
}

//
// outsd
//
TEST_F(Test386, outsd_batch13)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF6CB8A1F);
    cpu.set_ebx(0xE9A19794);
    cpu.set_ecx(0xC4239CAD);
    cpu.set_edx(0xFBF02782);
    cpu.set_esi(0xFFDFFFFF);
    cpu.set_edi(0xBBBE37A4);
    cpu.set_ebp(0x04E32E9A);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F58F);
    cpu.set_ds(0x00000283);
    cpu.set_es(0x00003C8B);
    cpu.set_fs(0x00000129);
    cpu.set_gs(0x0000B006);
    cpu.set_ss(0x00001824);
    cpu.set_eip(0x00004958);
    cpu.set_eflags(0xFFFC04C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFA248, 0x66);
    machine.mem_store_byte(0xFA249, 0x6F);
    machine.mem_store_byte(0xFA24A, 0xF4);
    machine.mem_store_byte(0xFA24B, 0xFF);
    machine.mem_store_byte(0xFA24C, 0xFF);
    machine.mem_store_byte(0xFA24D, 0xFF);
    machine.mem_store_byte(0xFA24E, 0xFF);
    machine.mem_store_byte(0xFA24F, 0xFF);
    machine.mem_store_byte(0xFA250, 0xFF);
    machine.mem_store_byte(0xFA251, 0xFF);
    machine.mem_store_byte(0xFA252, 0xFF);
    machine.mem_store_byte(0xFA253, 0xFF);
    machine.mem_store_byte(0xFA254, 0xFF);
    machine.mem_store_byte(0xFA255, 0xFF);
    machine.mem_store_byte(0xFA256, 0xFF);
    machine.mem_store_byte(0xFA257, 0xFF);
    machine.mem_store_byte(0x00034, 0x58);
    machine.mem_store_byte(0x00035, 0xA1);
    machine.mem_store_byte(0x00036, 0x0E);
    machine.mem_store_byte(0x00037, 0x2C);
    machine.mem_store_byte(0x36238, 0xF4);
    machine.mem_store_byte(0x36239, 0xFF);
    machine.mem_store_byte(0x3623A, 0xF4);
    machine.mem_store_byte(0x3623B, 0xFF);
    machine.mem_store_byte(0x3623C, 0xF4);
    machine.mem_store_byte(0x3623D, 0xFF);
    machine.mem_store_byte(0x3623E, 0xF4);
    machine.mem_store_byte(0x3623F, 0xFF);
    machine.mem_store_byte(0x36240, 0xF4);
    machine.mem_store_byte(0x36241, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF6CB8A1F);
    EXPECT_EQ(cpu.get_ebx(), 0xE9A19794);
    EXPECT_EQ(cpu.get_ecx(), 0xC4239CAD);
    EXPECT_EQ(cpu.get_edx(), 0xFBF02782);
    EXPECT_EQ(cpu.get_esi(), 0xFFDFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0xBBBE37A4);
    EXPECT_EQ(cpu.get_ebp(), 0x04E32E9A);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x00002C0E);
    EXPECT_EQ(cpu.get_ds(), 0x00000283);
    EXPECT_EQ(cpu.get_es(), 0x00003C8B);
    EXPECT_EQ(cpu.get_fs(), 0x00000129);
    EXPECT_EQ(cpu.get_gs(), 0x0000B006);
    EXPECT_EQ(cpu.get_ss(), 0x00001824);
    EXPECT_EQ(cpu.get_eip(), 0x0000A159);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x18246), 0xC6);
    EXPECT_EQ(memory.load8(0x18247), 0x04);
    EXPECT_EQ(memory.load8(0x18244), 0x8F);
    EXPECT_EQ(memory.load8(0x18245), 0xF5);
    EXPECT_EQ(memory.load8(0x18242), 0x58);
    EXPECT_EQ(memory.load8(0x18243), 0x49);
}

//
// outsw
//
TEST_F(Test386, outsw_batch13)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF6CB8A1F);
    cpu.set_ebx(0xE9A19794);
    cpu.set_ecx(0xC4239CAD);
    cpu.set_edx(0xFBF02782);
    cpu.set_esi(0xFFDFFFFF);
    cpu.set_edi(0xBBBE37A4);
    cpu.set_ebp(0x04E32E9A);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F58F);
    cpu.set_ds(0x00000283);
    cpu.set_es(0x00003C8B);
    cpu.set_fs(0x00000129);
    cpu.set_gs(0x0000B006);
    cpu.set_ss(0x00001824);
    cpu.set_eip(0x00004958);
    cpu.set_eflags(0xFFFC04C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFA248, 0x6F);
    machine.mem_store_byte(0xFA249, 0xF4);
    machine.mem_store_byte(0xFA24A, 0xFF);
    machine.mem_store_byte(0xFA24B, 0xFF);
    machine.mem_store_byte(0xFA24C, 0xFF);
    machine.mem_store_byte(0xFA24D, 0xFF);
    machine.mem_store_byte(0xFA24E, 0xFF);
    machine.mem_store_byte(0xFA24F, 0xFF);
    machine.mem_store_byte(0xFA250, 0xFF);
    machine.mem_store_byte(0xFA251, 0xFF);
    machine.mem_store_byte(0xFA252, 0xFF);
    machine.mem_store_byte(0xFA253, 0xFF);
    machine.mem_store_byte(0xFA254, 0xFF);
    machine.mem_store_byte(0xFA255, 0xFF);
    machine.mem_store_byte(0xFA256, 0xFF);
    machine.mem_store_byte(0xFA257, 0xFF);
    machine.mem_store_byte(0x00034, 0x58);
    machine.mem_store_byte(0x00035, 0xA1);
    machine.mem_store_byte(0x00036, 0x0E);
    machine.mem_store_byte(0x00037, 0x2C);
    machine.mem_store_byte(0x36238, 0xF4);
    machine.mem_store_byte(0x36239, 0xFF);
    machine.mem_store_byte(0x3623A, 0xF4);
    machine.mem_store_byte(0x3623B, 0xFF);
    machine.mem_store_byte(0x3623C, 0xF4);
    machine.mem_store_byte(0x3623D, 0xFF);
    machine.mem_store_byte(0x3623E, 0xF4);
    machine.mem_store_byte(0x3623F, 0xFF);
    machine.mem_store_byte(0x36240, 0xF4);
    machine.mem_store_byte(0x36241, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF6CB8A1F);
    EXPECT_EQ(cpu.get_ebx(), 0xE9A19794);
    EXPECT_EQ(cpu.get_ecx(), 0xC4239CAD);
    EXPECT_EQ(cpu.get_edx(), 0xFBF02782);
    EXPECT_EQ(cpu.get_esi(), 0xFFDFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0xBBBE37A4);
    EXPECT_EQ(cpu.get_ebp(), 0x04E32E9A);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x00002C0E);
    EXPECT_EQ(cpu.get_ds(), 0x00000283);
    EXPECT_EQ(cpu.get_es(), 0x00003C8B);
    EXPECT_EQ(cpu.get_fs(), 0x00000129);
    EXPECT_EQ(cpu.get_gs(), 0x0000B006);
    EXPECT_EQ(cpu.get_ss(), 0x00001824);
    EXPECT_EQ(cpu.get_eip(), 0x0000A159);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x18246), 0xC6);
    EXPECT_EQ(memory.load8(0x18247), 0x04);
    EXPECT_EQ(memory.load8(0x18244), 0x8F);
    EXPECT_EQ(memory.load8(0x18245), 0xF5);
    EXPECT_EQ(memory.load8(0x18242), 0x58);
    EXPECT_EQ(memory.load8(0x18243), 0x49);
}

//
// repne lodsd
//
TEST_F(Test386, repne_lodsd_batch13)
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
    machine.mem_store_byte(0x6C429, 0x66);
    machine.mem_store_byte(0x6C42A, 0xAD);
    machine.mem_store_byte(0x6C42B, 0xF4);
    machine.mem_store_byte(0x6C42C, 0x14);
    machine.mem_store_byte(0x6C42D, 0xD8);
    machine.mem_store_byte(0x6C42E, 0x45);
    machine.mem_store_byte(0x6C42F, 0x1D);
    machine.mem_store_byte(0x6C430, 0xB0);
    machine.mem_store_byte(0x6C431, 0x55);
    machine.mem_store_byte(0x6C432, 0x4B);
    machine.mem_store_byte(0x6C433, 0x86);
    machine.mem_store_byte(0x6C434, 0xCA);
    machine.mem_store_byte(0x6C435, 0x12);
    machine.mem_store_byte(0x00034, 0xFB);
    machine.mem_store_byte(0x00035, 0x26);
    machine.mem_store_byte(0x00036, 0x67);
    machine.mem_store_byte(0x00037, 0x6C);
    machine.mem_store_byte(0x6ED6A, 0x76);
    machine.mem_store_byte(0x6ED6B, 0xF4);
    machine.mem_store_byte(0x6ED6C, 0x7A);
    machine.mem_store_byte(0x6ED6D, 0xF4);
    machine.mem_store_byte(0x6ED6E, 0x7C);
    machine.mem_store_byte(0x6ED6F, 0xF4);
    machine.mem_store_byte(0x6ED70, 0x2C);
    machine.mem_store_byte(0x6ED71, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE2AC250F);
    EXPECT_EQ(cpu.get_ebx(), 0x0137CCB0);
    EXPECT_EQ(cpu.get_ecx(), 0x00000020);
    EXPECT_EQ(cpu.get_edx(), 0x00B92D61);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x00200001);
    EXPECT_EQ(cpu.get_esp(), 0x00000A76);
    EXPECT_EQ(cpu.get_cs(), 0x00006C67);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x0000FBB1);
    EXPECT_EQ(cpu.get_fs(), 0x0000B2CB);
    EXPECT_EQ(cpu.get_gs(), 0x0000AFE8);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x000026FC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0847);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x00A7A), 0x47);
    EXPECT_EQ(memory.load8(0x00A7B), 0x08);
    EXPECT_EQ(memory.load8(0x00A78), 0xB1);
    EXPECT_EQ(memory.load8(0x00A79), 0x63);
    EXPECT_EQ(memory.load8(0x00A76), 0x18);
    EXPECT_EQ(memory.load8(0x00A77), 0x89);
}

//
// repne lodsw
//
TEST_F(Test386, repne_lodsw_batch13)
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
    machine.mem_store_byte(0x6C429, 0xAD);
    machine.mem_store_byte(0x6C42A, 0xF4);
    machine.mem_store_byte(0x6C42B, 0x9C);
    machine.mem_store_byte(0x6C42C, 0x14);
    machine.mem_store_byte(0x6C42D, 0xD8);
    machine.mem_store_byte(0x6C42E, 0x45);
    machine.mem_store_byte(0x6C42F, 0x1D);
    machine.mem_store_byte(0x6C430, 0xB0);
    machine.mem_store_byte(0x6C431, 0x55);
    machine.mem_store_byte(0x6C432, 0x4B);
    machine.mem_store_byte(0x6C433, 0x86);
    machine.mem_store_byte(0x6C434, 0xCA);
    machine.mem_store_byte(0x6C435, 0x12);
    machine.mem_store_byte(0x00034, 0xFB);
    machine.mem_store_byte(0x00035, 0x26);
    machine.mem_store_byte(0x00036, 0x67);
    machine.mem_store_byte(0x00037, 0x6C);
    machine.mem_store_byte(0x6ED6A, 0x76);
    machine.mem_store_byte(0x6ED6B, 0xF4);
    machine.mem_store_byte(0x6ED6C, 0x7A);
    machine.mem_store_byte(0x6ED6D, 0xF4);
    machine.mem_store_byte(0x6ED6E, 0x7C);
    machine.mem_store_byte(0x6ED6F, 0xF4);
    machine.mem_store_byte(0x6ED70, 0x2C);
    machine.mem_store_byte(0x6ED71, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE2AC250F);
    EXPECT_EQ(cpu.get_ebx(), 0x0137CCB0);
    EXPECT_EQ(cpu.get_ecx(), 0x00000020);
    EXPECT_EQ(cpu.get_edx(), 0x00B92D61);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x00200001);
    EXPECT_EQ(cpu.get_esp(), 0x00000A76);
    EXPECT_EQ(cpu.get_cs(), 0x00006C67);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x0000FBB1);
    EXPECT_EQ(cpu.get_fs(), 0x0000B2CB);
    EXPECT_EQ(cpu.get_gs(), 0x0000AFE8);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x000026FC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0847);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x00A7A), 0x47);
    EXPECT_EQ(memory.load8(0x00A7B), 0x08);
    EXPECT_EQ(memory.load8(0x00A78), 0xB1);
    EXPECT_EQ(memory.load8(0x00A79), 0x63);
    EXPECT_EQ(memory.load8(0x00A76), 0x18);
    EXPECT_EQ(memory.load8(0x00A77), 0x89);
}
