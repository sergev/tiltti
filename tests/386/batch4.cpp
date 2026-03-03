#include "test386.h"

//
// aaa
//
TEST_F(Test386, aaa_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x430D607A);
    cpu.set_ebx(0x99CE0DB2);
    cpu.set_ecx(0x00080001);
    cpu.set_edx(0x00000021);
    cpu.set_esi(0x5A5A5A5A);
    cpu.set_edi(0x00008001);
    cpu.set_ebp(0xC1E605A1);
    cpu.set_esp(0x000000D0);
    cpu.set_cs(0x00000053);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x00006730);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x0000EEFE);
    cpu.set_ss(0x00000F1E);
    cpu.set_eip(0x0000C490);
    cpu.set_eflags(0xFFFC0083);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0C9C0, 0x37);
    machine.mem_store_byte(0x0C9C1, 0xF4);
    machine.mem_store_byte(0x0C9C2, 0xEB);
    machine.mem_store_byte(0x0C9C3, 0x1F);
    machine.mem_store_byte(0x0C9C4, 0x49);
    machine.mem_store_byte(0x0C9C5, 0xA7);
    machine.mem_store_byte(0x0C9C6, 0x0A);
    machine.mem_store_byte(0x0C9C7, 0x56);
    machine.mem_store_byte(0x0C9C8, 0xE0);
    machine.mem_store_byte(0x0C9C9, 0x22);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x430D6100);
    EXPECT_EQ(cpu.get_ebx(), 0x99CE0DB2);
    EXPECT_EQ(cpu.get_ecx(), 0x00080001);
    EXPECT_EQ(cpu.get_edx(), 0x00000021);
    EXPECT_EQ(cpu.get_esi(), 0x5A5A5A5A);
    EXPECT_EQ(cpu.get_edi(), 0x00008001);
    EXPECT_EQ(cpu.get_ebp(), 0xC1E605A1);
    EXPECT_EQ(cpu.get_esp(), 0x000000D0);
    EXPECT_EQ(cpu.get_cs(), 0x00000053);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x00006730);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x0000EEFE);
    EXPECT_EQ(cpu.get_ss(), 0x00000F1E);
    EXPECT_EQ(cpu.get_eip(), 0x0000C492);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0893);

    // Final RAM entries
}

//
// aas
//
TEST_F(Test386, aas_01_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00002001);
    cpu.set_ebx(0x1FFFFFFF);
    cpu.set_ecx(0xAF845F2D);
    cpu.set_edx(0xFE3974E4);
    cpu.set_esi(0x920C4CDE);
    cpu.set_edi(0xE6610047);
    cpu.set_ebp(0xF41974C2);
    cpu.set_esp(0x0000C4F6);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000F430);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00000091);
    cpu.set_gs(0x000000F9);
    cpu.set_ss(0x000032D0);
    cpu.set_eip(0x0000F030);
    cpu.set_eflags(0xFFFC0856);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10F020, 0x3F);
    machine.mem_store_byte(0x10F021, 0xF4);
    machine.mem_store_byte(0x10F022, 0x00);
    machine.mem_store_byte(0x10F023, 0x00);
    machine.mem_store_byte(0x10F024, 0x00);
    machine.mem_store_byte(0x10F025, 0x00);
    machine.mem_store_byte(0x10F026, 0x00);
    machine.mem_store_byte(0x10F027, 0x00);
    machine.mem_store_byte(0x10F028, 0x00);
    machine.mem_store_byte(0x10F029, 0x00);
    machine.mem_store_byte(0x10F02A, 0x00);
    machine.mem_store_byte(0x10F02B, 0x00);
    machine.mem_store_byte(0x10F02C, 0x00);
    machine.mem_store_byte(0x10F02D, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001E0B);
    EXPECT_EQ(cpu.get_ebx(), 0x1FFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0xAF845F2D);
    EXPECT_EQ(cpu.get_edx(), 0xFE3974E4);
    EXPECT_EQ(cpu.get_esi(), 0x920C4CDE);
    EXPECT_EQ(cpu.get_edi(), 0xE6610047);
    EXPECT_EQ(cpu.get_ebp(), 0xF41974C2);
    EXPECT_EQ(cpu.get_esp(), 0x0000C4F6);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000F430);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00000091);
    EXPECT_EQ(cpu.get_gs(), 0x000000F9);
    EXPECT_EQ(cpu.get_ss(), 0x000032D0);
    EXPECT_EQ(cpu.get_eip(), 0x0000F032);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0093);

    // Final RAM entries
}

//
// mov byte [ds:edx+2BCAh],98h
//
TEST_F(Test386, mov_byte_ds_edx_2BCAh_98h_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x6E7FB82A);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0x0000F39C);
    cpu.set_esi(0x00B14F55);
    cpu.set_edi(0x525048FF);
    cpu.set_ebp(0xBE490715);
    cpu.set_esp(0x00007AD0);
    cpu.set_cs(0x00003CEA);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x00004CEF);
    cpu.set_gs(0x000004AB);
    cpu.set_ss(0x0000F971);
    cpu.set_eip(0x0000F388);
    cpu.set_eflags(0xFFFC0843);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4C228, 0x3E);
    machine.mem_store_byte(0x4C229, 0x67);
    machine.mem_store_byte(0x4C22A, 0xC6);
    machine.mem_store_byte(0x4C22B, 0x82);
    machine.mem_store_byte(0x4C22C, 0xCA);
    machine.mem_store_byte(0x4C22D, 0x2B);
    machine.mem_store_byte(0x4C22E, 0x00);
    machine.mem_store_byte(0x4C22F, 0x00);
    machine.mem_store_byte(0x4C230, 0x98);
    machine.mem_store_byte(0x4C231, 0xF4);
    machine.mem_store_byte(0x4C232, 0x5A);
    machine.mem_store_byte(0x4C233, 0xB9);
    machine.mem_store_byte(0x4C234, 0x09);
    machine.mem_store_byte(0x4C235, 0xF8);
    machine.mem_store_byte(0x4C236, 0x58);
    machine.mem_store_byte(0x4C237, 0x09);
    machine.mem_store_byte(0x4C238, 0x97);
    machine.mem_store_byte(0x4C239, 0x88);
    machine.mem_store_byte(0x4C23A, 0x45);
    machine.mem_store_byte(0x4C23B, 0x56);
    machine.mem_store_byte(0x4C23C, 0x27);
    machine.mem_store_byte(0x4C23D, 0xF9);
    machine.mem_store_byte(0x4C23E, 0x33);
    machine.mem_store_byte(0x4C23F, 0x1F);
    machine.mem_store_byte(0x00034, 0x1B);
    machine.mem_store_byte(0x00035, 0xA8);
    machine.mem_store_byte(0x00036, 0x4C);
    machine.mem_store_byte(0x00037, 0x8F);
    machine.mem_store_byte(0x99CDA, 0x18);
    machine.mem_store_byte(0x99CDB, 0xF4);
    machine.mem_store_byte(0x99CDC, 0x49);
    machine.mem_store_byte(0x99CDD, 0xF4);
    machine.mem_store_byte(0x99CDE, 0xC7);
    machine.mem_store_byte(0x99CDF, 0xF4);
    machine.mem_store_byte(0x99CE0, 0xA7);
    machine.mem_store_byte(0x99CE1, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0x6E7FB82A);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x0000F39C);
    EXPECT_EQ(cpu.get_esi(), 0x00B14F55);
    EXPECT_EQ(cpu.get_edi(), 0x525048FF);
    EXPECT_EQ(cpu.get_ebp(), 0xBE490715);
    EXPECT_EQ(cpu.get_esp(), 0x00007ACA);
    EXPECT_EQ(cpu.get_cs(), 0x00008F4C);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x00004CEF);
    EXPECT_EQ(cpu.get_gs(), 0x000004AB);
    EXPECT_EQ(cpu.get_ss(), 0x0000F971);
    EXPECT_EQ(cpu.get_eip(), 0x0000A81C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0843);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1011DE), 0x43);
    EXPECT_EQ(memory.load8(0x1011DF), 0x08);
    EXPECT_EQ(memory.load8(0x1011DC), 0xEA);
    EXPECT_EQ(memory.load8(0x1011DD), 0x3C);
    EXPECT_EQ(memory.load8(0x1011DA), 0x88);
    EXPECT_EQ(memory.load8(0x1011DB), 0xF3);
}

//
// mov [ss:esp+edx*4],es
//
TEST_F(Test386, mov_ss_esp_edx_4_es_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x3D265FE9);
    cpu.set_ebx(0xCEE68DE1);
    cpu.set_ecx(0xFFFFFF9F);
    cpu.set_edx(0x00000C11);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xC64467B3);
    cpu.set_ebp(0xAEC7F156);
    cpu.set_esp(0x000000A0);
    cpu.set_cs(0x00000006);
    cpu.set_ds(0x00001C66);
    cpu.set_es(0x00005163);
    cpu.set_fs(0x00005FAF);
    cpu.set_gs(0x000045AD);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000DF10);
    cpu.set_eflags(0xFFFC0C92);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0DF70, 0x67);
    machine.mem_store_byte(0x0DF71, 0x8C);
    machine.mem_store_byte(0x0DF72, 0x04);
    machine.mem_store_byte(0x0DF73, 0x94);
    machine.mem_store_byte(0x0DF74, 0xF4);
    machine.mem_store_byte(0x0DF75, 0xC1);
    machine.mem_store_byte(0x0DF76, 0xE8);
    machine.mem_store_byte(0x0DF77, 0xE7);
    machine.mem_store_byte(0x0DF78, 0x03);
    machine.mem_store_byte(0x0DF79, 0xC2);
    machine.mem_store_byte(0x0DF7A, 0xE3);
    machine.mem_store_byte(0x0DF7B, 0x70);
    machine.mem_store_byte(0x0DF7C, 0xC3);
    machine.mem_store_byte(0x0DF7D, 0x04);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x3D265FE9);
    EXPECT_EQ(cpu.get_ebx(), 0xCEE68DE1);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFF9F);
    EXPECT_EQ(cpu.get_edx(), 0x00000C11);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xC64467B3);
    EXPECT_EQ(cpu.get_ebp(), 0xAEC7F156);
    EXPECT_EQ(cpu.get_esp(), 0x000000A0);
    EXPECT_EQ(cpu.get_cs(), 0x00000006);
    EXPECT_EQ(cpu.get_ds(), 0x00001C66);
    EXPECT_EQ(cpu.get_es(), 0x00005163);
    EXPECT_EQ(cpu.get_fs(), 0x00005FAF);
    EXPECT_EQ(cpu.get_gs(), 0x000045AD);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000DF15);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C92);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x030E4), 0x63);
    EXPECT_EQ(memory.load8(0x030E5), 0x51);
}

//
// mul cl
//
TEST_F(Test386, mul_cl_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x950AE6DF);
    cpu.set_ebx(0x8D5D8656);
    cpu.set_ecx(0x00003FFF);
    cpu.set_edx(0xFFFFFFFF);
    cpu.set_esi(0xEA44138C);
    cpu.set_edi(0xA63A372E);
    cpu.set_ebp(0x3D5BAA25);
    cpu.set_esp(0x00005234);
    cpu.set_cs(0x0000332E);
    cpu.set_ds(0x0000628F);
    cpu.set_es(0x0000D169);
    cpu.set_fs(0x00000C4E);
    cpu.set_gs(0x0000564D);
    cpu.set_ss(0x0000357A);
    cpu.set_eip(0x00001240);
    cpu.set_eflags(0xFFFC0C83);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x34520, 0xF6);
    machine.mem_store_byte(0x34521, 0xE1);
    machine.mem_store_byte(0x34522, 0xF4);
    machine.mem_store_byte(0x34523, 0x94);
    machine.mem_store_byte(0x34524, 0x6C);
    machine.mem_store_byte(0x34525, 0x04);
    machine.mem_store_byte(0x34526, 0x59);
    machine.mem_store_byte(0x34527, 0x72);
    machine.mem_store_byte(0x34528, 0x46);
    machine.mem_store_byte(0x34529, 0xDF);
    machine.mem_store_byte(0x3452A, 0x2D);
    machine.mem_store_byte(0x3452B, 0x37);
    machine.mem_store_byte(0x3452C, 0x8C);
    machine.mem_store_byte(0x3452D, 0xAC);
    machine.mem_store_byte(0x3452E, 0xB0);
    machine.mem_store_byte(0x3452F, 0x77);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x950ADE21);
    EXPECT_EQ(cpu.get_ebx(), 0x8D5D8656);
    EXPECT_EQ(cpu.get_ecx(), 0x00003FFF);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0xEA44138C);
    EXPECT_EQ(cpu.get_edi(), 0xA63A372E);
    EXPECT_EQ(cpu.get_ebp(), 0x3D5BAA25);
    EXPECT_EQ(cpu.get_esp(), 0x00005234);
    EXPECT_EQ(cpu.get_cs(), 0x0000332E);
    EXPECT_EQ(cpu.get_ds(), 0x0000628F);
    EXPECT_EQ(cpu.get_es(), 0x0000D169);
    EXPECT_EQ(cpu.get_fs(), 0x00000C4E);
    EXPECT_EQ(cpu.get_gs(), 0x0000564D);
    EXPECT_EQ(cpu.get_ss(), 0x0000357A);
    EXPECT_EQ(cpu.get_eip(), 0x00001243);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C93);

    // Final RAM entries
}

//
// o32 mov [ss:esp+edx*4],es
//
TEST_F(Test386, o32_mov_ss_esp_edx_4_es_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x3D265FE9);
    cpu.set_ebx(0xCEE68DE1);
    cpu.set_ecx(0xFFFFFF9F);
    cpu.set_edx(0x00000C11);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xC64467B3);
    cpu.set_ebp(0xAEC7F156);
    cpu.set_esp(0x000000A0);
    cpu.set_cs(0x00000006);
    cpu.set_ds(0x00001C66);
    cpu.set_es(0x00005163);
    cpu.set_fs(0x00005FAF);
    cpu.set_gs(0x000045AD);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000DF10);
    cpu.set_eflags(0xFFFC0C92);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0DF70, 0x67);
    machine.mem_store_byte(0x0DF71, 0x66);
    machine.mem_store_byte(0x0DF72, 0x8C);
    machine.mem_store_byte(0x0DF73, 0x04);
    machine.mem_store_byte(0x0DF74, 0x94);
    machine.mem_store_byte(0x0DF75, 0xF4);
    machine.mem_store_byte(0x0DF76, 0xE8);
    machine.mem_store_byte(0x0DF77, 0xE7);
    machine.mem_store_byte(0x0DF78, 0x03);
    machine.mem_store_byte(0x0DF79, 0xC2);
    machine.mem_store_byte(0x0DF7A, 0xE3);
    machine.mem_store_byte(0x0DF7B, 0x70);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x3D265FE9);
    EXPECT_EQ(cpu.get_ebx(), 0xCEE68DE1);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFF9F);
    EXPECT_EQ(cpu.get_edx(), 0x00000C11);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xC64467B3);
    EXPECT_EQ(cpu.get_ebp(), 0xAEC7F156);
    EXPECT_EQ(cpu.get_esp(), 0x000000A0);
    EXPECT_EQ(cpu.get_cs(), 0x00000006);
    EXPECT_EQ(cpu.get_ds(), 0x00001C66);
    EXPECT_EQ(cpu.get_es(), 0x00005163);
    EXPECT_EQ(cpu.get_fs(), 0x00005FAF);
    EXPECT_EQ(cpu.get_gs(), 0x000045AD);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000DF16);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C92);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x030E4), 0x63);
    EXPECT_EQ(memory.load8(0x030E5), 0x51);
}

//
// o32 pop ds
//
TEST_F(Test386, o32_pop_ds_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xBA6E11C0);
    cpu.set_ebx(0x0E12465D);
    cpu.set_ecx(0x007F0000);
    cpu.set_edx(0xFDF4D577);
    cpu.set_esi(0x98FE1C1B);
    cpu.set_edi(0x00020001);
    cpu.set_ebp(0x0000000E);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000CEE7);
    cpu.set_ds(0x00003E73);
    cpu.set_es(0x00004FF6);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x000074ED);
    cpu.set_ss(0x0000A93D);
    cpu.set_eip(0x000067C8);
    cpu.set_eflags(0xFFFC0857);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD5638, 0x66);
    machine.mem_store_byte(0xD5639, 0x1F);
    machine.mem_store_byte(0xD563A, 0xF4);
    machine.mem_store_byte(0xD563B, 0xA0);
    machine.mem_store_byte(0xD563C, 0x75);
    machine.mem_store_byte(0xD563D, 0x6C);
    machine.mem_store_byte(0xD563E, 0xA3);
    machine.mem_store_byte(0xD563F, 0x45);
    machine.mem_store_byte(0xD5640, 0xDD);
    machine.mem_store_byte(0xD5641, 0x01);
    machine.mem_store_byte(0xB93CE, 0x82);
    machine.mem_store_byte(0xB93CF, 0xDD);
    machine.mem_store_byte(0xD5642, 0x02);
    machine.mem_store_byte(0xD5643, 0x98);
    machine.mem_store_byte(0xD5644, 0x9C);
    machine.mem_store_byte(0xD5645, 0xC0);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xBA6E11C0);
    EXPECT_EQ(cpu.get_ebx(), 0x0E12465D);
    EXPECT_EQ(cpu.get_ecx(), 0x007F0000);
    EXPECT_EQ(cpu.get_edx(), 0xFDF4D577);
    EXPECT_EQ(cpu.get_esi(), 0x98FE1C1B);
    EXPECT_EQ(cpu.get_edi(), 0x00020001);
    EXPECT_EQ(cpu.get_ebp(), 0x0000000E);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x0000CEE7);
    EXPECT_EQ(cpu.get_ds(), 0x0000DD82);
    EXPECT_EQ(cpu.get_es(), 0x00004FF6);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x000074ED);
    EXPECT_EQ(cpu.get_ss(), 0x0000A93D);
    EXPECT_EQ(cpu.get_eip(), 0x000067CB);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0857);

    // Final RAM entries
}

//
// rcr dl,1
//
TEST_F(Test386, rcr_dl_1_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFE0DD818);
    cpu.set_ebx(0x53A9CF67);
    cpu.set_ecx(0xE4513017);
    cpu.set_edx(0x1ACB67DA);
    cpu.set_esi(0x00000001);
    cpu.set_edi(0x3B756133);
    cpu.set_ebp(0x7D0A0C40);
    cpu.set_esp(0x0000E218);
    cpu.set_cs(0x000006E1);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00003FCD);
    cpu.set_fs(0x00005A5A);
    cpu.set_gs(0x00009266);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00002A30);
    cpu.set_eflags(0xFFFC0886);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x09840, 0xD0);
    machine.mem_store_byte(0x09841, 0xDA);
    machine.mem_store_byte(0x09842, 0xF4);
    machine.mem_store_byte(0x09843, 0x83);
    machine.mem_store_byte(0x09844, 0x08);
    machine.mem_store_byte(0x09845, 0xDB);
    machine.mem_store_byte(0x09846, 0x67);
    machine.mem_store_byte(0x09847, 0x3A);
    machine.mem_store_byte(0x09848, 0x74);
    machine.mem_store_byte(0x09849, 0x08);
    machine.mem_store_byte(0x0984A, 0x63);
    machine.mem_store_byte(0x0984B, 0xE7);
    machine.mem_store_byte(0x0984C, 0xB7);
    machine.mem_store_byte(0x0984D, 0x07);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFE0DD818);
    EXPECT_EQ(cpu.get_ebx(), 0x53A9CF67);
    EXPECT_EQ(cpu.get_ecx(), 0xE4513017);
    EXPECT_EQ(cpu.get_edx(), 0x1ACB676D);
    EXPECT_EQ(cpu.get_esi(), 0x00000001);
    EXPECT_EQ(cpu.get_edi(), 0x3B756133);
    EXPECT_EQ(cpu.get_ebp(), 0x7D0A0C40);
    EXPECT_EQ(cpu.get_esp(), 0x0000E218);
    EXPECT_EQ(cpu.get_cs(), 0x000006E1);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00003FCD);
    EXPECT_EQ(cpu.get_fs(), 0x00005A5A);
    EXPECT_EQ(cpu.get_gs(), 0x00009266);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x00002A33);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0886);

    // Final RAM entries
}

//
// shr bl,B0h
//
TEST_F(Test386, shr_bl_B0h_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA3D930DB);
    cpu.set_ebx(0xBECB81E3);
    cpu.set_ecx(0xABF4C072);
    cpu.set_edx(0xBF6773DC);
    cpu.set_esi(0xE4FB5473);
    cpu.set_edi(0xCB9E3607);
    cpu.set_ebp(0xC4F43722);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x000091E7);
    cpu.set_es(0x00007773);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x000079D6);
    cpu.set_ss(0x0000C4F3);
    cpu.set_eip(0x00009140);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x09140, 0xC0);
    machine.mem_store_byte(0x09141, 0xEB);
    machine.mem_store_byte(0x09142, 0xB0);
    machine.mem_store_byte(0x09143, 0xF4);
    machine.mem_store_byte(0x09144, 0x00);
    machine.mem_store_byte(0x09145, 0x00);
    machine.mem_store_byte(0x09146, 0x00);
    machine.mem_store_byte(0x09147, 0x00);
    machine.mem_store_byte(0x09148, 0x00);
    machine.mem_store_byte(0x09149, 0x00);
    machine.mem_store_byte(0x0914A, 0x00);
    machine.mem_store_byte(0x0914B, 0x00);
    machine.mem_store_byte(0x0914C, 0x00);
    machine.mem_store_byte(0x0914D, 0x00);
    machine.mem_store_byte(0x0914E, 0x00);
    machine.mem_store_byte(0x0914F, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA3D930DB);
    EXPECT_EQ(cpu.get_ebx(), 0xBECB8100);
    EXPECT_EQ(cpu.get_ecx(), 0xABF4C072);
    EXPECT_EQ(cpu.get_edx(), 0xBF6773DC);
    EXPECT_EQ(cpu.get_esi(), 0xE4FB5473);
    EXPECT_EQ(cpu.get_edi(), 0xCB9E3607);
    EXPECT_EQ(cpu.get_ebp(), 0xC4F43722);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x000091E7);
    EXPECT_EQ(cpu.get_es(), 0x00007773);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x000079D6);
    EXPECT_EQ(cpu.get_ss(), 0x0000C4F3);
    EXPECT_EQ(cpu.get_eip(), 0x00009144);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0457);

    // Final RAM entries
}

//
// test [ss:bp+5Ah],esp
//
TEST_F(Test386, test_ss_bp_5Ah_esp_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0197984D);
    cpu.set_ebx(0x479C3A62);
    cpu.set_ecx(0x17CBA145);
    cpu.set_edx(0xFFDFFFFF);
    cpu.set_esi(0x409CEBF5);
    cpu.set_edi(0x645984A0);
    cpu.set_ebp(0x14D9F073);
    cpu.set_esp(0x0000B1BA);
    cpu.set_cs(0x0000E9ED);
    cpu.set_ds(0x00009296);
    cpu.set_es(0x00004245);
    cpu.set_fs(0x0000D717);
    cpu.set_gs(0x000016FF);
    cpu.set_ss(0x00000800);
    cpu.set_eip(0x0000F0D8);
    cpu.set_eflags(0xFFFC0057);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8FA8, 0x66);
    machine.mem_store_byte(0xF8FA9, 0x85);
    machine.mem_store_byte(0xF8FAA, 0x66);
    machine.mem_store_byte(0xF8FAB, 0x5A);
    machine.mem_store_byte(0xF8FAC, 0xF4);
    machine.mem_store_byte(0xF8FAD, 0xCA);
    machine.mem_store_byte(0xF8FAE, 0x7F);
    machine.mem_store_byte(0xF8FAF, 0x07);
    machine.mem_store_byte(0xF8FB0, 0x57);
    machine.mem_store_byte(0xF8FB1, 0x30);
    machine.mem_store_byte(0xF8FB2, 0x1B);
    machine.mem_store_byte(0xF8FB3, 0x67);
    machine.mem_store_byte(0x170D0, 0x21);
    machine.mem_store_byte(0x170CD, 0xD2);
    machine.mem_store_byte(0x170CE, 0xB7);
    machine.mem_store_byte(0x170CF, 0x32);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0197984D);
    EXPECT_EQ(cpu.get_ebx(), 0x479C3A62);
    EXPECT_EQ(cpu.get_ecx(), 0x17CBA145);
    EXPECT_EQ(cpu.get_edx(), 0xFFDFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0x409CEBF5);
    EXPECT_EQ(cpu.get_edi(), 0x645984A0);
    EXPECT_EQ(cpu.get_ebp(), 0x14D9F073);
    EXPECT_EQ(cpu.get_esp(), 0x0000B1BA);
    EXPECT_EQ(cpu.get_cs(), 0x0000E9ED);
    EXPECT_EQ(cpu.get_ds(), 0x00009296);
    EXPECT_EQ(cpu.get_es(), 0x00004245);
    EXPECT_EQ(cpu.get_fs(), 0x0000D717);
    EXPECT_EQ(cpu.get_gs(), 0x000016FF);
    EXPECT_EQ(cpu.get_ss(), 0x00000800);
    EXPECT_EQ(cpu.get_eip(), 0x0000F0DD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0002);

    // Final RAM entries
}

//
// aas
//
TEST_F(Test386, aas_F2_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFFFFFF2);
    cpu.set_ebx(0x3A0CB159);
    cpu.set_ecx(0xBCAB5A8D);
    cpu.set_edx(0x315E770A);
    cpu.set_esi(0x00000040);
    cpu.set_edi(0x3F77C288);
    cpu.set_ebp(0x5E709DE0);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000BCF5);
    cpu.set_ds(0x00000021);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x000079E2);
    cpu.set_gs(0x00000707);
    cpu.set_ss(0x000004D5);
    cpu.set_eip(0x0000FC10);
    cpu.set_eflags(0xFFFC00D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCCB60, 0x3F);
    machine.mem_store_byte(0xCCB61, 0xF4);
    machine.mem_store_byte(0xCCB62, 0x88);
    machine.mem_store_byte(0xCCB63, 0x9C);
    machine.mem_store_byte(0xCCB64, 0xBE);
    machine.mem_store_byte(0xCCB65, 0x05);
    machine.mem_store_byte(0xCCB66, 0x34);
    machine.mem_store_byte(0xCCB67, 0x9D);
    machine.mem_store_byte(0xCCB68, 0x4C);
    machine.mem_store_byte(0xCCB69, 0x07);
    machine.mem_store_byte(0xCCB6A, 0x62);
    machine.mem_store_byte(0xCCB6B, 0xF5);
    machine.mem_store_byte(0xCCB6C, 0xC3);
    machine.mem_store_byte(0xCCB6D, 0x4C);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFFFFE0C);
    EXPECT_EQ(cpu.get_ebx(), 0x3A0CB159);
    EXPECT_EQ(cpu.get_ecx(), 0xBCAB5A8D);
    EXPECT_EQ(cpu.get_edx(), 0x315E770A);
    EXPECT_EQ(cpu.get_esi(), 0x00000040);
    EXPECT_EQ(cpu.get_edi(), 0x3F77C288);
    EXPECT_EQ(cpu.get_ebp(), 0x5E709DE0);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000BCF5);
    EXPECT_EQ(cpu.get_ds(), 0x00000021);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x000079E2);
    EXPECT_EQ(cpu.get_gs(), 0x00000707);
    EXPECT_EQ(cpu.get_ss(), 0x000004D5);
    EXPECT_EQ(cpu.get_eip(), 0x0000FC12);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0093);

    // Final RAM entries
}

//
// pop dword [ds:bx-44h]
//
TEST_F(Test386, pop_dword_ds_bx_44h_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000015);
    cpu.set_ebx(0x87ECF850);
    cpu.set_ecx(0x961D7F71);
    cpu.set_edx(0x37F0343A);
    cpu.set_esi(0xAAE638F7);
    cpu.set_edi(0x008D4187);
    cpu.set_ebp(0xA356995B);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000CF00);
    cpu.set_ds(0x000078EE);
    cpu.set_es(0x0000D65E);
    cpu.set_fs(0x0000C9AD);
    cpu.set_gs(0x0000FFDF);
    cpu.set_ss(0x0000F908);
    cpu.set_eip(0x0000BFF8);
    cpu.set_eflags(0xFFFC0093);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDAFF8, 0x66);
    machine.mem_store_byte(0xDAFF9, 0x8F);
    machine.mem_store_byte(0xDAFFA, 0x47);
    machine.mem_store_byte(0xDAFFB, 0xBC);
    machine.mem_store_byte(0xDAFFC, 0xF4);
    machine.mem_store_byte(0xDAFFD, 0x29);
    machine.mem_store_byte(0xDAFFE, 0x4E);
    machine.mem_store_byte(0xDAFFF, 0x66);
    machine.mem_store_byte(0xDB000, 0xCA);
    machine.mem_store_byte(0xDB001, 0x19);
    machine.mem_store_byte(0xDB002, 0xAA);
    machine.mem_store_byte(0xDB003, 0x01);
    machine.mem_store_byte(0xDB004, 0xEE);
    machine.mem_store_byte(0xDB005, 0x5F);
    machine.mem_store_byte(0xDB006, 0x4D);
    machine.mem_store_byte(0xDB007, 0xB5);
    machine.mem_store_byte(0xDB008, 0x25);
    machine.mem_store_byte(0xDB009, 0x55);
    machine.mem_store_byte(0xDB00A, 0xA4);
    machine.mem_store_byte(0xDB00B, 0xC8);
    machine.mem_store_byte(0x00030, 0x31);
    machine.mem_store_byte(0x00031, 0x99);
    machine.mem_store_byte(0x00032, 0x87);
    machine.mem_store_byte(0x00033, 0x83);
    machine.mem_store_byte(0x8D1A0, 0xF8);
    machine.mem_store_byte(0x8D1A1, 0xF4);
    machine.mem_store_byte(0x8D1A2, 0x42);
    machine.mem_store_byte(0x8D1A3, 0xF4);
    machine.mem_store_byte(0x8D1A4, 0x9F);
    machine.mem_store_byte(0x8D1A5, 0xF4);
    machine.mem_store_byte(0x8D1A6, 0xED);
    machine.mem_store_byte(0x8D1A7, 0xF4);
    machine.mem_store_byte(0x8D1A8, 0xD8);
    machine.mem_store_byte(0x8D1A9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000015);
    EXPECT_EQ(cpu.get_ebx(), 0x87ECF850);
    EXPECT_EQ(cpu.get_ecx(), 0x961D7F71);
    EXPECT_EQ(cpu.get_edx(), 0x37F0343A);
    EXPECT_EQ(cpu.get_esi(), 0xAAE638F7);
    EXPECT_EQ(cpu.get_edi(), 0x008D4187);
    EXPECT_EQ(cpu.get_ebp(), 0xA356995B);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x00008387);
    EXPECT_EQ(cpu.get_ds(), 0x000078EE);
    EXPECT_EQ(cpu.get_es(), 0x0000D65E);
    EXPECT_EQ(cpu.get_fs(), 0x0000C9AD);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFDF);
    EXPECT_EQ(cpu.get_ss(), 0x0000F908);
    EXPECT_EQ(cpu.get_eip(), 0x00009932);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0093);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x10907C), 0x93);
    EXPECT_EQ(memory.load8(0x10907D), 0x00);
    EXPECT_EQ(memory.load8(0x10907A), 0x00);
    EXPECT_EQ(memory.load8(0x10907B), 0xCF);
    EXPECT_EQ(memory.load8(0x109078), 0xF8);
    EXPECT_EQ(memory.load8(0x109079), 0xBF);
}

//
// pop dword [ds:ecx-30h]
//
TEST_F(Test386, pop_dword_ds_ecx_30h_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000015);
    cpu.set_ebx(0x87ECF850);
    cpu.set_ecx(0x00007F71);
    cpu.set_edx(0x37F0343A);
    cpu.set_esi(0xAAE638F7);
    cpu.set_edi(0x008D4187);
    cpu.set_ebp(0xA356995B);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000CF00);
    cpu.set_ds(0x000078EE);
    cpu.set_es(0x0000D65E);
    cpu.set_fs(0x0000C9AD);
    cpu.set_gs(0x0000FFDF);
    cpu.set_ss(0x0000F908);
    cpu.set_eip(0x0000BFF8);
    cpu.set_eflags(0xFFFC0093);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDAFF8, 0x67);
    machine.mem_store_byte(0xDAFF9, 0x66);
    machine.mem_store_byte(0xDAFFA, 0x8F);
    machine.mem_store_byte(0xDAFFB, 0x41);
    machine.mem_store_byte(0xDAFFC, 0xD0);
    machine.mem_store_byte(0xDAFFD, 0xF4);
    machine.mem_store_byte(0xDAFFE, 0x4E);
    machine.mem_store_byte(0xDAFFF, 0x66);
    machine.mem_store_byte(0xDB000, 0xCA);
    machine.mem_store_byte(0xDB001, 0x19);
    machine.mem_store_byte(0xDB002, 0xAA);
    machine.mem_store_byte(0xDB003, 0x01);
    machine.mem_store_byte(0xDB004, 0xEE);
    machine.mem_store_byte(0xDB005, 0x5F);
    machine.mem_store_byte(0xDB006, 0x4D);
    machine.mem_store_byte(0xDB007, 0xB5);
    machine.mem_store_byte(0xDB008, 0x25);
    machine.mem_store_byte(0xDB009, 0x55);
    machine.mem_store_byte(0xDB00A, 0xA4);
    machine.mem_store_byte(0xDB00B, 0xC8);
    machine.mem_store_byte(0x00030, 0x31);
    machine.mem_store_byte(0x00031, 0x99);
    machine.mem_store_byte(0x00032, 0x87);
    machine.mem_store_byte(0x00033, 0x83);
    machine.mem_store_byte(0x8D1A0, 0xF8);
    machine.mem_store_byte(0x8D1A1, 0xF4);
    machine.mem_store_byte(0x8D1A2, 0x42);
    machine.mem_store_byte(0x8D1A3, 0xF4);
    machine.mem_store_byte(0x8D1A4, 0x9F);
    machine.mem_store_byte(0x8D1A5, 0xF4);
    machine.mem_store_byte(0x8D1A6, 0xED);
    machine.mem_store_byte(0x8D1A7, 0xF4);
    machine.mem_store_byte(0x8D1A8, 0xD8);
    machine.mem_store_byte(0x8D1A9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000015);
    EXPECT_EQ(cpu.get_ebx(), 0x87ECF850);
    EXPECT_EQ(cpu.get_ecx(), 0x00007F71);
    EXPECT_EQ(cpu.get_edx(), 0x37F0343A);
    EXPECT_EQ(cpu.get_esi(), 0xAAE638F7);
    EXPECT_EQ(cpu.get_edi(), 0x008D4187);
    EXPECT_EQ(cpu.get_ebp(), 0xA356995B);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x00008387);
    EXPECT_EQ(cpu.get_ds(), 0x000078EE);
    EXPECT_EQ(cpu.get_es(), 0x0000D65E);
    EXPECT_EQ(cpu.get_fs(), 0x0000C9AD);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFDF);
    EXPECT_EQ(cpu.get_ss(), 0x0000F908);
    EXPECT_EQ(cpu.get_eip(), 0x00009932);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0093);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x10907C), 0x93);
    EXPECT_EQ(memory.load8(0x10907D), 0x00);
    EXPECT_EQ(memory.load8(0x10907A), 0x00);
    EXPECT_EQ(memory.load8(0x10907B), 0xCF);
    EXPECT_EQ(memory.load8(0x109078), 0xF8);
    EXPECT_EQ(memory.load8(0x109079), 0xBF);
}

//
// shr byte [ds:di-53h],cl
//
TEST_F(Test386, shr_byte_ds_di_53h_cl_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xCD0DFE34);
    cpu.set_ebx(0x9E23E82E);
    cpu.set_ecx(0xD4F89B95);
    cpu.set_edx(0xBB47948F);
    cpu.set_esi(0xFFFFFFDF);
    cpu.set_edi(0x74E4FE7A);
    cpu.set_ebp(0x94627614);
    cpu.set_esp(0x00007A8C);
    cpu.set_cs(0x0000D574);
    cpu.set_ds(0x00000001);
    cpu.set_es(0x0000F6AB);
    cpu.set_fs(0x0000FDDB);
    cpu.set_gs(0x0000924C);
    cpu.set_ss(0x0000C202);
    cpu.set_eip(0x00007080);
    cpu.set_eflags(0xFFFC0897);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDC7C0, 0xD2);
    machine.mem_store_byte(0xDC7C1, 0x6D);
    machine.mem_store_byte(0xDC7C2, 0xAD);
    machine.mem_store_byte(0xDC7C3, 0xF4);
    machine.mem_store_byte(0xDC7C4, 0xFF);
    machine.mem_store_byte(0xDC7C5, 0xFF);
    machine.mem_store_byte(0xDC7C6, 0xFF);
    machine.mem_store_byte(0xDC7C7, 0xFF);
    machine.mem_store_byte(0xDC7C8, 0xFF);
    machine.mem_store_byte(0xDC7C9, 0xFF);
    machine.mem_store_byte(0x0FE37, 0xFF);
    machine.mem_store_byte(0xDC7CA, 0xFF);
    machine.mem_store_byte(0xDC7CB, 0xFF);
    machine.mem_store_byte(0xDC7CC, 0xFF);
    machine.mem_store_byte(0xDC7CD, 0xFF);
    machine.mem_store_byte(0xDC7CE, 0xFF);
    machine.mem_store_byte(0xDC7CF, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xCD0DFE34);
    EXPECT_EQ(cpu.get_ebx(), 0x9E23E82E);
    EXPECT_EQ(cpu.get_ecx(), 0xD4F89B95);
    EXPECT_EQ(cpu.get_edx(), 0xBB47948F);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFDF);
    EXPECT_EQ(cpu.get_edi(), 0x74E4FE7A);
    EXPECT_EQ(cpu.get_ebp(), 0x94627614);
    EXPECT_EQ(cpu.get_esp(), 0x00007A8C);
    EXPECT_EQ(cpu.get_cs(), 0x0000D574);
    EXPECT_EQ(cpu.get_ds(), 0x00000001);
    EXPECT_EQ(cpu.get_es(), 0x0000F6AB);
    EXPECT_EQ(cpu.get_fs(), 0x0000FDDB);
    EXPECT_EQ(cpu.get_gs(), 0x0000924C);
    EXPECT_EQ(cpu.get_ss(), 0x0000C202);
    EXPECT_EQ(cpu.get_eip(), 0x00007084);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0FE37), 0x00);
}

//
// shr byte [ds:ebx-6Bh],cl
//
TEST_F(Test386, shr_byte_ds_ebx_6Bh_cl_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xCD0DFE34);
    cpu.set_ebx(0x0000E82E);
    cpu.set_ecx(0xD4F89B95);
    cpu.set_edx(0xBB47948F);
    cpu.set_esi(0xFFFFFFDF);
    cpu.set_edi(0x74E4FE7A);
    cpu.set_ebp(0x94627614);
    cpu.set_esp(0x00007A8C);
    cpu.set_cs(0x0000D574);
    cpu.set_ds(0x00000001);
    cpu.set_es(0x0000F6AB);
    cpu.set_fs(0x0000FDDB);
    cpu.set_gs(0x0000924C);
    cpu.set_ss(0x0000C202);
    cpu.set_eip(0x00007080);
    cpu.set_eflags(0xFFFC0897);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDC7C0, 0x67);
    machine.mem_store_byte(0xDC7C1, 0xD2);
    machine.mem_store_byte(0xDC7C2, 0x6B);
    machine.mem_store_byte(0xDC7C3, 0x95);
    machine.mem_store_byte(0xDC7C4, 0xF4);
    machine.mem_store_byte(0xDC7C5, 0xFF);
    machine.mem_store_byte(0xDC7C6, 0xFF);
    machine.mem_store_byte(0xDC7C7, 0xFF);
    machine.mem_store_byte(0xDC7C8, 0xFF);
    machine.mem_store_byte(0xDC7C9, 0xFF);
    machine.mem_store_byte(0xDC7CA, 0xFF);
    machine.mem_store_byte(0xDC7CB, 0xFF);
    machine.mem_store_byte(0x0E7D3, 0xFF);
    machine.mem_store_byte(0xDC7CC, 0xFF);
    machine.mem_store_byte(0xDC7CD, 0xFF);
    machine.mem_store_byte(0xDC7CE, 0xFF);
    machine.mem_store_byte(0xDC7CF, 0xFF);
    machine.mem_store_byte(0xDC7D0, 0xFF);
    machine.mem_store_byte(0xDC7D1, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xCD0DFE34);
    EXPECT_EQ(cpu.get_ebx(), 0x0000E82E);
    EXPECT_EQ(cpu.get_ecx(), 0xD4F89B95);
    EXPECT_EQ(cpu.get_edx(), 0xBB47948F);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFDF);
    EXPECT_EQ(cpu.get_edi(), 0x74E4FE7A);
    EXPECT_EQ(cpu.get_ebp(), 0x94627614);
    EXPECT_EQ(cpu.get_esp(), 0x00007A8C);
    EXPECT_EQ(cpu.get_cs(), 0x0000D574);
    EXPECT_EQ(cpu.get_ds(), 0x00000001);
    EXPECT_EQ(cpu.get_es(), 0x0000F6AB);
    EXPECT_EQ(cpu.get_fs(), 0x0000FDDB);
    EXPECT_EQ(cpu.get_gs(), 0x0000924C);
    EXPECT_EQ(cpu.get_ss(), 0x0000C202);
    EXPECT_EQ(cpu.get_eip(), 0x00007085);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0E7D3), 0x00);
}

//
// shr byte [ss:bp+si],5Ah
//
TEST_F(Test386, shr_byte_ss_bp_si_5Ah_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA1328009);
    cpu.set_ebx(0x6D8DAA30);
    cpu.set_ecx(0xD1EC610C);
    cpu.set_edx(0xA330DFF4);
    cpu.set_esi(0x97BE3F4A);
    cpu.set_edi(0xD7F7C5C0);
    cpu.set_ebp(0xE6356605);
    cpu.set_esp(0x0000D970);
    cpu.set_cs(0x00001CD7);
    cpu.set_ds(0x0000FFC2);
    cpu.set_es(0x00000382);
    cpu.set_fs(0x000057A9);
    cpu.set_gs(0x00009CBE);
    cpu.set_ss(0x00006919);
    cpu.set_eip(0x00000208);
    cpu.set_eflags(0xFFFC08C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1CF78, 0xC0);
    machine.mem_store_byte(0x1CF79, 0x2A);
    machine.mem_store_byte(0x1CF7A, 0x5A);
    machine.mem_store_byte(0x1CF7B, 0xF4);
    machine.mem_store_byte(0x1CF7C, 0xE2);
    machine.mem_store_byte(0x1CF7D, 0x3F);
    machine.mem_store_byte(0x1CF7E, 0x5F);
    machine.mem_store_byte(0x1CF7F, 0xCA);
    machine.mem_store_byte(0x1CF80, 0xFF);
    machine.mem_store_byte(0x1CF81, 0x0C);
    machine.mem_store_byte(0x736DF, 0x9F);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA1328009);
    EXPECT_EQ(cpu.get_ebx(), 0x6D8DAA30);
    EXPECT_EQ(cpu.get_ecx(), 0xD1EC610C);
    EXPECT_EQ(cpu.get_edx(), 0xA330DFF4);
    EXPECT_EQ(cpu.get_esi(), 0x97BE3F4A);
    EXPECT_EQ(cpu.get_edi(), 0xD7F7C5C0);
    EXPECT_EQ(cpu.get_ebp(), 0xE6356605);
    EXPECT_EQ(cpu.get_esp(), 0x0000D970);
    EXPECT_EQ(cpu.get_cs(), 0x00001CD7);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFC2);
    EXPECT_EQ(cpu.get_es(), 0x00000382);
    EXPECT_EQ(cpu.get_fs(), 0x000057A9);
    EXPECT_EQ(cpu.get_gs(), 0x00009CBE);
    EXPECT_EQ(cpu.get_ss(), 0x00006919);
    EXPECT_EQ(cpu.get_eip(), 0x0000020C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x736DF), 0x00);
}

//
// shr di,cl
//
TEST_F(Test386, shr_di_cl_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x92175544);
    cpu.set_ebx(0x7FFFFFFF);
    cpu.set_ecx(0xA6D8809D);
    cpu.set_edx(0x7E9BA2E4);
    cpu.set_esi(0x79B725F6);
    cpu.set_edi(0x5FA6F2B1);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00008ED3);
    cpu.set_ds(0x0000469A);
    cpu.set_es(0x0000130C);
    cpu.set_fs(0x0000FE54);
    cpu.set_gs(0x0000D558);
    cpu.set_ss(0x00001064);
    cpu.set_eip(0x00009E90);
    cpu.set_eflags(0xFFFC04C2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x98BC0, 0xD3);
    machine.mem_store_byte(0x98BC1, 0xEF);
    machine.mem_store_byte(0x98BC2, 0xF4);
    machine.mem_store_byte(0x98BC3, 0x91);
    machine.mem_store_byte(0x98BC4, 0xD1);
    machine.mem_store_byte(0x98BC5, 0xA2);
    machine.mem_store_byte(0x98BC6, 0xCB);
    machine.mem_store_byte(0x98BC7, 0xD2);
    machine.mem_store_byte(0x98BC8, 0xFF);
    machine.mem_store_byte(0x98BC9, 0xA0);
    machine.mem_store_byte(0x98BCA, 0x40);
    machine.mem_store_byte(0x98BCB, 0xEE);
    machine.mem_store_byte(0x98BCC, 0x12);
    machine.mem_store_byte(0x98BCD, 0x7E);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x92175544);
    EXPECT_EQ(cpu.get_ebx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0xA6D8809D);
    EXPECT_EQ(cpu.get_edx(), 0x7E9BA2E4);
    EXPECT_EQ(cpu.get_esi(), 0x79B725F6);
    EXPECT_EQ(cpu.get_edi(), 0x5FA60000);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00008ED3);
    EXPECT_EQ(cpu.get_ds(), 0x0000469A);
    EXPECT_EQ(cpu.get_es(), 0x0000130C);
    EXPECT_EQ(cpu.get_fs(), 0x0000FE54);
    EXPECT_EQ(cpu.get_gs(), 0x0000D558);
    EXPECT_EQ(cpu.get_ss(), 0x00001064);
    EXPECT_EQ(cpu.get_eip(), 0x00009E93);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0456);

    // Final RAM entries
}

//
// shr word [ds:bx+si+F71h],1Ah
//
TEST_F(Test386, shr_word_ds_bx_si_F71h_1Ah_batch4)
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
    machine.mem_store_byte(0xC0F68, 0xC1);
    machine.mem_store_byte(0xC0F69, 0xA8);
    machine.mem_store_byte(0xC0F6A, 0x71);
    machine.mem_store_byte(0xC0F6B, 0x0F);
    machine.mem_store_byte(0xC0F6C, 0x1A);
    machine.mem_store_byte(0xC0F6D, 0xF4);
    machine.mem_store_byte(0xC0F6E, 0xD1);
    machine.mem_store_byte(0xC0F6F, 0xF4);
    machine.mem_store_byte(0xC0F70, 0x2B);
    machine.mem_store_byte(0xC0F71, 0xDE);
    machine.mem_store_byte(0xC0F72, 0xC7);
    machine.mem_store_byte(0xC0F73, 0xF3);
    machine.mem_store_byte(0x10576C, 0xB2);
    machine.mem_store_byte(0x10576B, 0xEB);
    machine.mem_store_byte(0xC0F74, 0x6C);
    machine.mem_store_byte(0xC0F75, 0xF4);
    machine.mem_store_byte(0xC0F76, 0x4A);
    machine.mem_store_byte(0xC0F77, 0x37);
    machine.mem_store_byte(0xC0F78, 0xFB);
    machine.mem_store_byte(0xC0F79, 0x95);

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
    EXPECT_EQ(cpu.get_esp(), 0x00003424);
    EXPECT_EQ(cpu.get_cs(), 0x0000BDBC);
    EXPECT_EQ(cpu.get_ds(), 0x0000FD8A);
    EXPECT_EQ(cpu.get_es(), 0x00004508);
    EXPECT_EQ(cpu.get_fs(), 0x00006774);
    EXPECT_EQ(cpu.get_gs(), 0x0000C692);
    EXPECT_EQ(cpu.get_ss(), 0x0000D4E5);
    EXPECT_EQ(cpu.get_eip(), 0x000033AE);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x10576C), 0x00);
    EXPECT_EQ(memory.load8(0x10576B), 0x00);
}

//
// shr word [ds:di-34FAh],5Ch
//
TEST_F(Test386, shr_word_ds_di_34FAh_5Ch_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x62FECB75);
    cpu.set_ebx(0x30F6DCDE);
    cpu.set_ecx(0x0000FFFF);
    cpu.set_edx(0xE81EFB43);
    cpu.set_esi(0x1F77E7A2);
    cpu.set_edi(0x3B053288);
    cpu.set_ebp(0x0F182105);
    cpu.set_esp(0x0000F1CE);
    cpu.set_cs(0x00008000);
    cpu.set_ds(0x00009FBB);
    cpu.set_es(0x00003C11);
    cpu.set_fs(0x0000DBBC);
    cpu.set_gs(0x0000FC65);
    cpu.set_ss(0x00005D1A);
    cpu.set_eip(0x00001838);
    cpu.set_eflags(0xFFFC0C17);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x81838, 0xC1);
    machine.mem_store_byte(0x81839, 0xAD);
    machine.mem_store_byte(0x8183A, 0x06);
    machine.mem_store_byte(0x8183B, 0xCB);
    machine.mem_store_byte(0x8183C, 0x5C);
    machine.mem_store_byte(0x8183D, 0xF4);
    machine.mem_store_byte(0x8183E, 0xFF);
    machine.mem_store_byte(0x8183F, 0xFF);
    machine.mem_store_byte(0x81840, 0xFF);
    machine.mem_store_byte(0x81841, 0xFF);
    machine.mem_store_byte(0x81842, 0xFF);
    machine.mem_store_byte(0x81843, 0xFF);
    machine.mem_store_byte(0xAF93E, 0xFF);
    machine.mem_store_byte(0xAF93F, 0xFF);
    machine.mem_store_byte(0x81844, 0xFF);
    machine.mem_store_byte(0x81845, 0xFF);
    machine.mem_store_byte(0x81846, 0xFF);
    machine.mem_store_byte(0x81847, 0xFF);
    machine.mem_store_byte(0x81848, 0xFF);
    machine.mem_store_byte(0x81849, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x62FECB75);
    EXPECT_EQ(cpu.get_ebx(), 0x30F6DCDE);
    EXPECT_EQ(cpu.get_ecx(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edx(), 0xE81EFB43);
    EXPECT_EQ(cpu.get_esi(), 0x1F77E7A2);
    EXPECT_EQ(cpu.get_edi(), 0x3B053288);
    EXPECT_EQ(cpu.get_ebp(), 0x0F182105);
    EXPECT_EQ(cpu.get_esp(), 0x0000F1CE);
    EXPECT_EQ(cpu.get_cs(), 0x00008000);
    EXPECT_EQ(cpu.get_ds(), 0x00009FBB);
    EXPECT_EQ(cpu.get_es(), 0x00003C11);
    EXPECT_EQ(cpu.get_fs(), 0x0000DBBC);
    EXPECT_EQ(cpu.get_gs(), 0x0000FC65);
    EXPECT_EQ(cpu.get_ss(), 0x00005D1A);
    EXPECT_EQ(cpu.get_eip(), 0x0000183E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0456);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAF93E), 0x00);
    EXPECT_EQ(memory.load8(0xAF93F), 0x00);
}

//
// shr word [ds:ecx+15h],3Fh
//
TEST_F(Test386, shr_word_ds_ecx_15h_3Fh_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x28BD1CDC);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x00001D8F);
    cpu.set_edx(0xBFF05FFF);
    cpu.set_esi(0x185B0820);
    cpu.set_edi(0x3FEE57C5);
    cpu.set_ebp(0x7F293FA2);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F8F9);
    cpu.set_ds(0x0000A884);
    cpu.set_es(0x0000F542);
    cpu.set_fs(0x00005679);
    cpu.set_gs(0x000019CD);
    cpu.set_ss(0x0000D9D8);
    cpu.set_eip(0x00007028);
    cpu.set_eflags(0xFFFC0857);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFFFB8, 0x67);
    machine.mem_store_byte(0xFFFB9, 0xC1);
    machine.mem_store_byte(0xFFFBA, 0x69);
    machine.mem_store_byte(0xFFFBB, 0x15);
    machine.mem_store_byte(0xFFFBC, 0x3F);
    machine.mem_store_byte(0xFFFBD, 0xF4);
    machine.mem_store_byte(0xFFFBE, 0xA3);
    machine.mem_store_byte(0xFFFBF, 0x4F);
    machine.mem_store_byte(0xFFFC0, 0xE5);
    machine.mem_store_byte(0xFFFC1, 0xC3);
    machine.mem_store_byte(0xFFFC2, 0x38);
    machine.mem_store_byte(0xFFFC3, 0x16);
    machine.mem_store_byte(0xAA5E4, 0x3E);
    machine.mem_store_byte(0xAA5E5, 0xEC);
    machine.mem_store_byte(0xFFFC4, 0xFB);
    machine.mem_store_byte(0xFFFC5, 0x14);
    machine.mem_store_byte(0xFFFC6, 0xB7);
    machine.mem_store_byte(0xFFFC7, 0x9C);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x28BD1CDC);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x00001D8F);
    EXPECT_EQ(cpu.get_edx(), 0xBFF05FFF);
    EXPECT_EQ(cpu.get_esi(), 0x185B0820);
    EXPECT_EQ(cpu.get_edi(), 0x3FEE57C5);
    EXPECT_EQ(cpu.get_ebp(), 0x7F293FA2);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000F8F9);
    EXPECT_EQ(cpu.get_ds(), 0x0000A884);
    EXPECT_EQ(cpu.get_es(), 0x0000F542);
    EXPECT_EQ(cpu.get_fs(), 0x00005679);
    EXPECT_EQ(cpu.get_gs(), 0x000019CD);
    EXPECT_EQ(cpu.get_ss(), 0x0000D9D8);
    EXPECT_EQ(cpu.get_eip(), 0x0000702E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAA5E4), 0x00);
    EXPECT_EQ(memory.load8(0xAA5E5), 0x00);
}

//
// shr word [ss:bp+di+6],11h
//
TEST_F(Test386, shr_word_ss_bp_di_6_11h_batch4)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x28BD1CDC);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0xDB051D8F);
    cpu.set_edx(0xBFF05FFF);
    cpu.set_esi(0x185B0820);
    cpu.set_edi(0x3FEE57C5);
    cpu.set_ebp(0x7F293FA2);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000F8F9);
    cpu.set_ds(0x0000A884);
    cpu.set_es(0x0000F542);
    cpu.set_fs(0x00005679);
    cpu.set_gs(0x000019CD);
    cpu.set_ss(0x0000D9D8);
    cpu.set_eip(0x00007028);
    cpu.set_eflags(0xFFFC0857);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFFFB8, 0xC1);
    machine.mem_store_byte(0xFFFB9, 0x6B);
    machine.mem_store_byte(0xFFFBA, 0x06);
    machine.mem_store_byte(0xFFFBB, 0x11);
    machine.mem_store_byte(0xFFFBC, 0xF4);
    machine.mem_store_byte(0xFFFBD, 0xC8);
    machine.mem_store_byte(0xFFFBE, 0xA3);
    machine.mem_store_byte(0xFFFBF, 0x4F);
    machine.mem_store_byte(0xFFFC0, 0xE5);
    machine.mem_store_byte(0xFFFC1, 0xC3);
    machine.mem_store_byte(0xFFFC2, 0x38);
    machine.mem_store_byte(0xFFFC3, 0x16);
    machine.mem_store_byte(0xE34ED, 0x0C);
    machine.mem_store_byte(0xE34EE, 0x98);
    machine.mem_store_byte(0xFFFC4, 0xFB);
    machine.mem_store_byte(0xFFFC5, 0x14);
    machine.mem_store_byte(0xFFFC6, 0xB7);
    machine.mem_store_byte(0xFFFC7, 0x9C);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x28BD1CDC);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0xDB051D8F);
    EXPECT_EQ(cpu.get_edx(), 0xBFF05FFF);
    EXPECT_EQ(cpu.get_esi(), 0x185B0820);
    EXPECT_EQ(cpu.get_edi(), 0x3FEE57C5);
    EXPECT_EQ(cpu.get_ebp(), 0x7F293FA2);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000F8F9);
    EXPECT_EQ(cpu.get_ds(), 0x0000A884);
    EXPECT_EQ(cpu.get_es(), 0x0000F542);
    EXPECT_EQ(cpu.get_fs(), 0x00005679);
    EXPECT_EQ(cpu.get_gs(), 0x000019CD);
    EXPECT_EQ(cpu.get_ss(), 0x0000D9D8);
    EXPECT_EQ(cpu.get_eip(), 0x0000702D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE34ED), 0x00);
    EXPECT_EQ(memory.load8(0xE34EE), 0x00);
}
