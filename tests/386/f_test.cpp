#include "test386.h"

//
// fs cmpsb
//
TEST_F(Test386, fs_cmpsb)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xBAFF4F3F);
    cpu.set_ebx(0x146708DD);
    cpu.set_ecx(0x90BE799E);
    cpu.set_edx(0x1F1A4B25);
    cpu.set_esi(0x62F365C5);
    cpu.set_edi(0xEC4EF395);
    cpu.set_ebp(0xFCB7F594);
    cpu.set_esp(0x0000D5AA);
    cpu.set_cs(0x0000C54A);
    cpu.set_ds(0x000010C5);
    cpu.set_es(0x0000016D);
    cpu.set_fs(0x0000FF87);
    cpu.set_gs(0x0000AD52);
    cpu.set_ss(0x000045E0);
    cpu.set_eip(0x00007948);
    cpu.set_eflags(0xFFFC0887);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCCDE8, 0x64);
    machine.mem_store_byte(0xCCDE9, 0xA6);
    machine.mem_store_byte(0xCCDEA, 0xF4);
    machine.mem_store_byte(0xCCDEB, 0x3B);
    machine.mem_store_byte(0xCCDEC, 0x0B);
    machine.mem_store_byte(0xCCDED, 0xB8);
    machine.mem_store_byte(0xCCDEE, 0x86);
    machine.mem_store_byte(0xCCDEF, 0xB3);
    machine.mem_store_byte(0xCCDF0, 0x41);
    machine.mem_store_byte(0xCCDF1, 0x45);
    machine.mem_store_byte(0x10A65, 0xA0);
    machine.mem_store_byte(0x105E35, 0xC1);
    machine.mem_store_byte(0xCCDF2, 0xF0);
    machine.mem_store_byte(0xCCDF3, 0x9A);
    machine.mem_store_byte(0xCCDF4, 0xD1);
    machine.mem_store_byte(0xCCDF5, 0x5E);
    machine.mem_store_byte(0xCCDF6, 0x29);
    machine.mem_store_byte(0xCCDF7, 0x2F);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xBAFF4F3F);
    EXPECT_EQ(cpu.get_ebx(), 0x146708DD);
    EXPECT_EQ(cpu.get_ecx(), 0x90BE799E);
    EXPECT_EQ(cpu.get_edx(), 0x1F1A4B25);
    EXPECT_EQ(cpu.get_esi(), 0x62F365C6);
    EXPECT_EQ(cpu.get_edi(), 0xEC4EF396);
    EXPECT_EQ(cpu.get_ebp(), 0xFCB7F594);
    EXPECT_EQ(cpu.get_esp(), 0x0000D5AA);
    EXPECT_EQ(cpu.get_cs(), 0x0000C54A);
    EXPECT_EQ(cpu.get_ds(), 0x000010C5);
    EXPECT_EQ(cpu.get_es(), 0x0000016D);
    EXPECT_EQ(cpu.get_fs(), 0x0000FF87);
    EXPECT_EQ(cpu.get_gs(), 0x0000AD52);
    EXPECT_EQ(cpu.get_ss(), 0x000045E0);
    EXPECT_EQ(cpu.get_eip(), 0x0000794B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0006);

    // Final RAM entries
}
