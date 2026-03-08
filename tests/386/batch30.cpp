#include "test386.h"

//
// (bad) mov invalid,esi
//
TEST_F(Test386, bad_mov_invalid_esi_batch30)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x30F13BA0);
    cpu.set_ebx(0x10377913);
    cpu.set_ecx(0xC5FF7A34);
    cpu.set_edx(0x08B05841);
    cpu.set_esi(0x00000011);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x49DABA3E);
    cpu.set_esp(0x0000A5A1);
    cpu.set_cs(0x0000FE3E);
    cpu.set_ds(0x0000F61D);
    cpu.set_es(0x0000BAF5);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00000979);
    cpu.set_ss(0x0000160D);
    cpu.set_eip(0x000043C8);
    cpu.set_eflags(0xFFFC00D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1027A8, 0x67);
    machine.mem_store_byte(0x1027A9, 0x66);
    machine.mem_store_byte(0x1027AA, 0x8E);
    machine.mem_store_byte(0x1027AB, 0xF6);
    machine.mem_store_byte(0x1027AC, 0xF4);
    machine.mem_store_byte(0x1027AD, 0xFF);
    machine.mem_store_byte(0x1027AE, 0xFF);
    machine.mem_store_byte(0x1027AF, 0xFF);
    machine.mem_store_byte(0x1027B0, 0xFF);
    machine.mem_store_byte(0x1027B1, 0xFF);
    machine.mem_store_byte(0x1027B2, 0xFF);
    machine.mem_store_byte(0x1027B3, 0xFF);
    machine.mem_store_byte(0x1027B4, 0xFF);
    machine.mem_store_byte(0x1027B5, 0xFF);
    machine.mem_store_byte(0x1027B6, 0xFF);
    machine.mem_store_byte(0x1027B7, 0xFF);
    machine.mem_store_byte(0x00018, 0x34);
    machine.mem_store_byte(0x00019, 0xA0);
    machine.mem_store_byte(0x0001A, 0x9A);
    machine.mem_store_byte(0x0001B, 0x87);
    machine.mem_store_byte(0x919D4, 0xF4);
    machine.mem_store_byte(0x919D5, 0xFF);
    machine.mem_store_byte(0x919D6, 0xF4);
    machine.mem_store_byte(0x919D7, 0xFF);
    machine.mem_store_byte(0x919D8, 0xF4);
    machine.mem_store_byte(0x919D9, 0xFF);
    machine.mem_store_byte(0x919DA, 0xF4);
    machine.mem_store_byte(0x919DB, 0xFF);
    machine.mem_store_byte(0x919DC, 0xF4);
    machine.mem_store_byte(0x919DD, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x30F13BA0);
    EXPECT_EQ(cpu.get_ebx(), 0x10377913);
    EXPECT_EQ(cpu.get_ecx(), 0xC5FF7A34);
    EXPECT_EQ(cpu.get_edx(), 0x08B05841);
    EXPECT_EQ(cpu.get_esi(), 0x00000011);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x49DABA3E);
    EXPECT_EQ(cpu.get_esp(), 0x0000A59B);
    EXPECT_EQ(cpu.get_cs(), 0x0000879A);
    EXPECT_EQ(cpu.get_ds(), 0x0000F61D);
    EXPECT_EQ(cpu.get_es(), 0x0000BAF5);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00000979);
    EXPECT_EQ(cpu.get_ss(), 0x0000160D);
    EXPECT_EQ(cpu.get_eip(), 0x0000A035);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00D6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x20670), 0x00);
    EXPECT_EQ(memory.load8(0x2066F), 0xD6);
    EXPECT_EQ(memory.load8(0x2066D), 0x3E);
    EXPECT_EQ(memory.load8(0x2066E), 0xFE);
    EXPECT_EQ(memory.load8(0x2066C), 0x43);
    EXPECT_EQ(memory.load8(0x2066B), 0xC8);
}

//
// (bad) mov invalid,si
//
TEST_F(Test386, bad_mov_invalid_si_batch30)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x30F13BA0);
    cpu.set_ebx(0x10377913);
    cpu.set_ecx(0xC5FF7A34);
    cpu.set_edx(0x08B05841);
    cpu.set_esi(0x00000011);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x49DABA3E);
    cpu.set_esp(0x0000A5A1);
    cpu.set_cs(0x0000FE3E);
    cpu.set_ds(0x0000F61D);
    cpu.set_es(0x0000BAF5);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00000979);
    cpu.set_ss(0x0000160D);
    cpu.set_eip(0x000043C8);
    cpu.set_eflags(0xFFFC00D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1027A8, 0x8E);
    machine.mem_store_byte(0x1027A9, 0xF6);
    machine.mem_store_byte(0x1027AA, 0xF4);
    machine.mem_store_byte(0x1027AB, 0xFF);
    machine.mem_store_byte(0x1027AC, 0xFF);
    machine.mem_store_byte(0x1027AD, 0xFF);
    machine.mem_store_byte(0x1027AE, 0xFF);
    machine.mem_store_byte(0x1027AF, 0xFF);
    machine.mem_store_byte(0x1027B0, 0xFF);
    machine.mem_store_byte(0x1027B1, 0xFF);
    machine.mem_store_byte(0x1027B2, 0xFF);
    machine.mem_store_byte(0x1027B3, 0xFF);
    machine.mem_store_byte(0x1027B4, 0xFF);
    machine.mem_store_byte(0x1027B5, 0xFF);
    machine.mem_store_byte(0x00018, 0x34);
    machine.mem_store_byte(0x00019, 0xA0);
    machine.mem_store_byte(0x0001A, 0x9A);
    machine.mem_store_byte(0x0001B, 0x87);
    machine.mem_store_byte(0x919D4, 0xF4);
    machine.mem_store_byte(0x919D5, 0xFF);
    machine.mem_store_byte(0x919D6, 0xF4);
    machine.mem_store_byte(0x919D7, 0xFF);
    machine.mem_store_byte(0x919D8, 0xF4);
    machine.mem_store_byte(0x919D9, 0xFF);
    machine.mem_store_byte(0x919DA, 0xF4);
    machine.mem_store_byte(0x919DB, 0xFF);
    machine.mem_store_byte(0x919DC, 0xF4);
    machine.mem_store_byte(0x919DD, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x30F13BA0);
    EXPECT_EQ(cpu.get_ebx(), 0x10377913);
    EXPECT_EQ(cpu.get_ecx(), 0xC5FF7A34);
    EXPECT_EQ(cpu.get_edx(), 0x08B05841);
    EXPECT_EQ(cpu.get_esi(), 0x00000011);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x49DABA3E);
    EXPECT_EQ(cpu.get_esp(), 0x0000A59B);
    EXPECT_EQ(cpu.get_cs(), 0x0000879A);
    EXPECT_EQ(cpu.get_ds(), 0x0000F61D);
    EXPECT_EQ(cpu.get_es(), 0x0000BAF5);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00000979);
    EXPECT_EQ(cpu.get_ss(), 0x0000160D);
    EXPECT_EQ(cpu.get_eip(), 0x0000A035);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00D6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x20670), 0x00);
    EXPECT_EQ(memory.load8(0x2066F), 0xD6);
    EXPECT_EQ(memory.load8(0x2066D), 0x3E);
    EXPECT_EQ(memory.load8(0x2066E), 0xFE);
    EXPECT_EQ(memory.load8(0x2066C), 0x43);
    EXPECT_EQ(memory.load8(0x2066B), 0xC8);
}

//
// retf
//
TEST_F(Test386, retf_batch30)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x63FD854C);
    cpu.set_ebx(0x566CCF84);
    cpu.set_ecx(0xD3DCCB0E);
    cpu.set_edx(0x288683DA);
    cpu.set_esi(0x0313CD3C);
    cpu.set_edi(0x00AF8A79);
    cpu.set_ebp(0x047A9246);
    cpu.set_esp(0x0000FFFF);
    cpu.set_cs(0x0000BC04);
    cpu.set_ds(0x00001AAC);
    cpu.set_es(0x000000D0);
    cpu.set_fs(0x00002570);
    cpu.set_gs(0x00005A61);
    cpu.set_ss(0x0000D61E);
    cpu.set_eip(0x0000A5A8);
    cpu.set_eflags(0xFFFC0C56);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC65E8, 0xCB);
    machine.mem_store_byte(0xC65E9, 0xF4);
    machine.mem_store_byte(0xC65EA, 0x34);
    machine.mem_store_byte(0xC65EB, 0x79);
    machine.mem_store_byte(0xC65EC, 0x16);
    machine.mem_store_byte(0xC65ED, 0xC8);
    machine.mem_store_byte(0xC65EE, 0x18);
    machine.mem_store_byte(0xC65EF, 0x63);
    machine.mem_store_byte(0x00030, 0xC2);
    machine.mem_store_byte(0x00031, 0x3F);
    machine.mem_store_byte(0x00032, 0xC3);
    machine.mem_store_byte(0x00033, 0x3B);
    machine.mem_store_byte(0x3FBF2, 0xF4);
    machine.mem_store_byte(0x3FBF3, 0xF4);
    machine.mem_store_byte(0x3FBF4, 0xF4);
    machine.mem_store_byte(0x3FBF5, 0xD9);
    machine.mem_store_byte(0x3FBF6, 0xF4);
    machine.mem_store_byte(0x3FBF7, 0x3D);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x63FD854C);
    EXPECT_EQ(cpu.get_ebx(), 0x566CCF84);
    EXPECT_EQ(cpu.get_ecx(), 0xD3DCCB0E);
    EXPECT_EQ(cpu.get_edx(), 0x288683DA);
    EXPECT_EQ(cpu.get_esi(), 0x0313CD3C);
    EXPECT_EQ(cpu.get_edi(), 0x00AF8A79);
    EXPECT_EQ(cpu.get_ebp(), 0x047A9246);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF9);
    EXPECT_EQ(cpu.get_cs(), 0x00003BC3);
    EXPECT_EQ(cpu.get_ds(), 0x00001AAC);
    EXPECT_EQ(cpu.get_es(), 0x000000D0);
    EXPECT_EQ(cpu.get_fs(), 0x00002570);
    EXPECT_EQ(cpu.get_gs(), 0x00005A61);
    EXPECT_EQ(cpu.get_ss(), 0x0000D61E);
    EXPECT_EQ(cpu.get_eip(), 0x00003FC3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C56);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE61DD), 0x56);
    EXPECT_EQ(memory.load8(0xE61DE), 0x0C);
    EXPECT_EQ(memory.load8(0xE61DC), 0xBC);
    EXPECT_EQ(memory.load8(0xE61DB), 0x04);
    EXPECT_EQ(memory.load8(0xE61D9), 0xA8);
    EXPECT_EQ(memory.load8(0xE61DA), 0xA5);
}

//
// rol byte [ds:bx+di],cl
//
TEST_F(Test386, rol_byte_ds_bx_di_cl_batch30)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDC64A0F4);
    cpu.set_ebx(0xB0BB45BB);
    cpu.set_ecx(0xA5D0AB68);
    cpu.set_edx(0x1399C05D);
    cpu.set_esi(0x30F006C9);
    cpu.set_edi(0x7FFFFFFF);
    cpu.set_ebp(0xF15AFE80);
    cpu.set_esp(0x00000984);
    cpu.set_cs(0x00002ECD);
    cpu.set_ds(0x00006974);
    cpu.set_es(0x0000BE58);
    cpu.set_fs(0x000011E3);
    cpu.set_gs(0x0000E057);
    cpu.set_ss(0x0000C2D9);
    cpu.set_eip(0x00005398);
    cpu.set_eflags(0xFFFC0807);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x34068, 0xD2);
    machine.mem_store_byte(0x34069, 0x01);
    machine.mem_store_byte(0x3406A, 0xF4);
    machine.mem_store_byte(0x3406B, 0xF3);
    machine.mem_store_byte(0x3406C, 0xA0);
    machine.mem_store_byte(0x3406D, 0x33);
    machine.mem_store_byte(0x3406E, 0xD4);
    machine.mem_store_byte(0x3406F, 0x76);
    machine.mem_store_byte(0x34070, 0xA6);
    machine.mem_store_byte(0x34071, 0xB2);
    machine.mem_store_byte(0x6DCFA, 0x41);
    machine.mem_store_byte(0x34072, 0x33);
    machine.mem_store_byte(0x34073, 0xE2);
    machine.mem_store_byte(0x34074, 0x15);
    machine.mem_store_byte(0x34075, 0x25);
    machine.mem_store_byte(0x34076, 0xA4);
    machine.mem_store_byte(0x34077, 0xAF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDC64A0F4);
    EXPECT_EQ(cpu.get_ebx(), 0xB0BB45BB);
    EXPECT_EQ(cpu.get_ecx(), 0xA5D0AB68);
    EXPECT_EQ(cpu.get_edx(), 0x1399C05D);
    EXPECT_EQ(cpu.get_esi(), 0x30F006C9);
    EXPECT_EQ(cpu.get_edi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xF15AFE80);
    EXPECT_EQ(cpu.get_esp(), 0x00000984);
    EXPECT_EQ(cpu.get_cs(), 0x00002ECD);
    EXPECT_EQ(cpu.get_ds(), 0x00006974);
    EXPECT_EQ(cpu.get_es(), 0x0000BE58);
    EXPECT_EQ(cpu.get_fs(), 0x000011E3);
    EXPECT_EQ(cpu.get_gs(), 0x0000E057);
    EXPECT_EQ(cpu.get_ss(), 0x0000C2D9);
    EXPECT_EQ(cpu.get_eip(), 0x0000539B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0807);

    // Final RAM entries
}

//
// stosd
//
TEST_F(Test386, stosd_batch30)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x48F02CFD);
    cpu.set_ebx(0x7A53159E);
    cpu.set_ecx(0x02441786);
    cpu.set_edx(0xF759890E);
    cpu.set_esi(0x499D0D58);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0xFFFDFFFF);
    cpu.set_esp(0x0000F066);
    cpu.set_cs(0x00000D65);
    cpu.set_ds(0x0000BEB2);
    cpu.set_es(0x00000860);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x0000FFFA);
    cpu.set_ss(0x0000445E);
    cpu.set_eip(0x000056F0);
    cpu.set_eflags(0xFFFC08C7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x12D40, 0x66);
    machine.mem_store_byte(0x12D41, 0xAB);
    machine.mem_store_byte(0x12D42, 0xF4);
    machine.mem_store_byte(0x12D43, 0xD2);
    machine.mem_store_byte(0x12D44, 0x2A);
    machine.mem_store_byte(0x12D45, 0xE8);
    machine.mem_store_byte(0x12D46, 0x33);
    machine.mem_store_byte(0x12D47, 0xF4);
    machine.mem_store_byte(0x12D48, 0x50);
    machine.mem_store_byte(0x12D49, 0xF7);
    machine.mem_store_byte(0x12D4A, 0x46);
    machine.mem_store_byte(0x12D4B, 0x4A);
    machine.mem_store_byte(0x12D4C, 0xB8);
    machine.mem_store_byte(0x12D4D, 0x65);
    machine.mem_store_byte(0x12D4E, 0xA3);
    machine.mem_store_byte(0x12D4F, 0xD1);
    machine.mem_store_byte(0x00034, 0xC3);
    machine.mem_store_byte(0x00035, 0xF0);
    machine.mem_store_byte(0x00036, 0x60);
    machine.mem_store_byte(0x00037, 0x7B);
    machine.mem_store_byte(0x8A6C2, 0xAD);
    machine.mem_store_byte(0x8A6C3, 0xF4);
    machine.mem_store_byte(0x8A6C4, 0xDF);
    machine.mem_store_byte(0x8A6C5, 0xF4);
    machine.mem_store_byte(0x8A6C6, 0xEA);
    machine.mem_store_byte(0x8A6C7, 0xF4);
    machine.mem_store_byte(0x8A6C8, 0x2A);
    machine.mem_store_byte(0x8A6C9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x48F02CFD);
    EXPECT_EQ(cpu.get_ebx(), 0x7A53159E);
    EXPECT_EQ(cpu.get_ecx(), 0x02441786);
    EXPECT_EQ(cpu.get_edx(), 0xF759890E);
    EXPECT_EQ(cpu.get_esi(), 0x499D0D58);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFDFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000F060);
    EXPECT_EQ(cpu.get_cs(), 0x00007B60);
    EXPECT_EQ(cpu.get_ds(), 0x0000BEB2);
    EXPECT_EQ(cpu.get_es(), 0x00000860);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFA);
    EXPECT_EQ(cpu.get_ss(), 0x0000445E);
    EXPECT_EQ(cpu.get_eip(), 0x0000F0C4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x53644), 0xC7);
    EXPECT_EQ(memory.load8(0x53645), 0x08);
    EXPECT_EQ(memory.load8(0x53642), 0x65);
    EXPECT_EQ(memory.load8(0x53643), 0x0D);
    EXPECT_EQ(memory.load8(0x53640), 0xF0);
    EXPECT_EQ(memory.load8(0x53641), 0x56);
}

//
// stosw
//
TEST_F(Test386, stosw_batch30)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x48F02CFD);
    cpu.set_ebx(0x7A53159E);
    cpu.set_ecx(0x02441786);
    cpu.set_edx(0xF759890E);
    cpu.set_esi(0x499D0D58);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0xFFFDFFFF);
    cpu.set_esp(0x0000F066);
    cpu.set_cs(0x00000D65);
    cpu.set_ds(0x0000BEB2);
    cpu.set_es(0x00000860);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x0000FFFA);
    cpu.set_ss(0x0000445E);
    cpu.set_eip(0x000056F0);
    cpu.set_eflags(0xFFFC08C7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x12D40, 0xAB);
    machine.mem_store_byte(0x12D41, 0xF4);
    machine.mem_store_byte(0x12D42, 0x55);
    machine.mem_store_byte(0x12D43, 0xD2);
    machine.mem_store_byte(0x12D44, 0x2A);
    machine.mem_store_byte(0x12D45, 0xE8);
    machine.mem_store_byte(0x12D46, 0x33);
    machine.mem_store_byte(0x12D47, 0xF4);
    machine.mem_store_byte(0x12D48, 0x50);
    machine.mem_store_byte(0x12D49, 0xF7);
    machine.mem_store_byte(0x12D4A, 0x46);
    machine.mem_store_byte(0x12D4B, 0x4A);
    machine.mem_store_byte(0x12D4C, 0xB8);
    machine.mem_store_byte(0x12D4D, 0x65);
    machine.mem_store_byte(0x12D4E, 0xA3);
    machine.mem_store_byte(0x12D4F, 0xD1);
    machine.mem_store_byte(0x00034, 0xC3);
    machine.mem_store_byte(0x00035, 0xF0);
    machine.mem_store_byte(0x00036, 0x60);
    machine.mem_store_byte(0x00037, 0x7B);
    machine.mem_store_byte(0x8A6C2, 0xAD);
    machine.mem_store_byte(0x8A6C3, 0xF4);
    machine.mem_store_byte(0x8A6C4, 0xDF);
    machine.mem_store_byte(0x8A6C5, 0xF4);
    machine.mem_store_byte(0x8A6C6, 0xEA);
    machine.mem_store_byte(0x8A6C7, 0xF4);
    machine.mem_store_byte(0x8A6C8, 0x2A);
    machine.mem_store_byte(0x8A6C9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x48F02CFD);
    EXPECT_EQ(cpu.get_ebx(), 0x7A53159E);
    EXPECT_EQ(cpu.get_ecx(), 0x02441786);
    EXPECT_EQ(cpu.get_edx(), 0xF759890E);
    EXPECT_EQ(cpu.get_esi(), 0x499D0D58);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFDFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000F060);
    EXPECT_EQ(cpu.get_cs(), 0x00007B60);
    EXPECT_EQ(cpu.get_ds(), 0x0000BEB2);
    EXPECT_EQ(cpu.get_es(), 0x00000860);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFA);
    EXPECT_EQ(cpu.get_ss(), 0x0000445E);
    EXPECT_EQ(cpu.get_eip(), 0x0000F0C4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x53644), 0xC7);
    EXPECT_EQ(memory.load8(0x53645), 0x08);
    EXPECT_EQ(memory.load8(0x53642), 0x65);
    EXPECT_EQ(memory.load8(0x53643), 0x0D);
    EXPECT_EQ(memory.load8(0x53640), 0xF0);
    EXPECT_EQ(memory.load8(0x53641), 0x56);
}
