#include "test386.h"

//
// (bad) mov esi,invalid
//
TEST_F(Test386, bad_mov_esi_invalid_batch50)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFE76D53);
    cpu.set_ebx(0x49AE7899);
    cpu.set_ecx(0x00000090);
    cpu.set_edx(0x0092B10B);
    cpu.set_esi(0x042A7ABA);
    cpu.set_edi(0x7CAE23C5);
    cpu.set_ebp(0x5EDF718D);
    cpu.set_esp(0x00000100);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000AC15);
    cpu.set_es(0x0000CC01);
    cpu.set_fs(0x00000099);
    cpu.set_gs(0x0000648B);
    cpu.set_ss(0x0000CABA);
    cpu.set_eip(0x00006B48);
    cpu.set_eflags(0xFFFC0813);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x06B48, 0x3E);
    machine.mem_store_byte(0x06B49, 0x67);
    machine.mem_store_byte(0x06B4A, 0x66);
    machine.mem_store_byte(0x06B4B, 0x8C);
    machine.mem_store_byte(0x06B4C, 0xFE);
    machine.mem_store_byte(0x06B4D, 0xF4);
    machine.mem_store_byte(0x06B4E, 0xFA);
    machine.mem_store_byte(0x06B4F, 0xE3);
    machine.mem_store_byte(0x06B50, 0x63);
    machine.mem_store_byte(0x06B51, 0xB5);
    machine.mem_store_byte(0x06B52, 0x9F);
    machine.mem_store_byte(0x06B53, 0x7B);
    machine.mem_store_byte(0x06B54, 0x1B);
    machine.mem_store_byte(0x06B55, 0xF5);
    machine.mem_store_byte(0x06B56, 0x80);
    machine.mem_store_byte(0x06B57, 0x93);
    machine.mem_store_byte(0x00018, 0x62);
    machine.mem_store_byte(0x00019, 0x4E);
    machine.mem_store_byte(0x0001A, 0x07);
    machine.mem_store_byte(0x0001B, 0xB5);
    machine.mem_store_byte(0xB9ED2, 0xF4);
    machine.mem_store_byte(0xB9ED3, 0x69);
    machine.mem_store_byte(0xB9ED4, 0xF4);
    machine.mem_store_byte(0xB9ED5, 0x2A);
    machine.mem_store_byte(0xB9ED6, 0xF4);
    machine.mem_store_byte(0xB9ED7, 0xC5);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFE76D53);
    EXPECT_EQ(cpu.get_ebx(), 0x49AE7899);
    EXPECT_EQ(cpu.get_ecx(), 0x00000090);
    EXPECT_EQ(cpu.get_edx(), 0x0092B10B);
    EXPECT_EQ(cpu.get_esi(), 0x042A7ABA);
    EXPECT_EQ(cpu.get_edi(), 0x7CAE23C5);
    EXPECT_EQ(cpu.get_ebp(), 0x5EDF718D);
    EXPECT_EQ(cpu.get_esp(), 0x000000FA);
    EXPECT_EQ(cpu.get_cs(), 0x0000B507);
    EXPECT_EQ(cpu.get_ds(), 0x0000AC15);
    EXPECT_EQ(cpu.get_es(), 0x0000CC01);
    EXPECT_EQ(cpu.get_fs(), 0x00000099);
    EXPECT_EQ(cpu.get_gs(), 0x0000648B);
    EXPECT_EQ(cpu.get_ss(), 0x0000CABA);
    EXPECT_EQ(cpu.get_eip(), 0x00004E63);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0813);

    // Final RAM entries
    EXPECT_FLAGS_LO(0xCAC9E, 0x13);
    EXPECT_FLAGS_HI(0xCAC9F, 0x08);
    EXPECT_EQ(memory.load8(0xCAC9C), 0x00);
    EXPECT_EQ(memory.load8(0xCAC9D), 0x00);
    EXPECT_EQ(memory.load8(0xCAC9A), 0x48);
    EXPECT_EQ(memory.load8(0xCAC9B), 0x6B);
}

//
// (bad) mov si,invalid
//
TEST_F(Test386, bad_mov_si_invalid_batch50)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFE76D53);
    cpu.set_ebx(0x49AE7899);
    cpu.set_ecx(0x00000090);
    cpu.set_edx(0x0092B10B);
    cpu.set_esi(0x042A7ABA);
    cpu.set_edi(0x7CAE23C5);
    cpu.set_ebp(0x5EDF718D);
    cpu.set_esp(0x00000100);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000AC15);
    cpu.set_es(0x0000CC01);
    cpu.set_fs(0x00000099);
    cpu.set_gs(0x0000648B);
    cpu.set_ss(0x0000CABA);
    cpu.set_eip(0x00006B48);
    cpu.set_eflags(0xFFFC0813);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x06B48, 0x3E);
    machine.mem_store_byte(0x06B49, 0x8C);
    machine.mem_store_byte(0x06B4A, 0xFE);
    machine.mem_store_byte(0x06B4B, 0xF4);
    machine.mem_store_byte(0x06B4C, 0x1F);
    machine.mem_store_byte(0x06B4D, 0x91);
    machine.mem_store_byte(0x06B4E, 0xFA);
    machine.mem_store_byte(0x06B4F, 0xE3);
    machine.mem_store_byte(0x06B50, 0x63);
    machine.mem_store_byte(0x06B51, 0xB5);
    machine.mem_store_byte(0x06B52, 0x9F);
    machine.mem_store_byte(0x06B53, 0x7B);
    machine.mem_store_byte(0x06B54, 0x1B);
    machine.mem_store_byte(0x06B55, 0xF5);
    machine.mem_store_byte(0x00018, 0x62);
    machine.mem_store_byte(0x00019, 0x4E);
    machine.mem_store_byte(0x0001A, 0x07);
    machine.mem_store_byte(0x0001B, 0xB5);
    machine.mem_store_byte(0xB9ED2, 0xF4);
    machine.mem_store_byte(0xB9ED3, 0x69);
    machine.mem_store_byte(0xB9ED4, 0xF4);
    machine.mem_store_byte(0xB9ED5, 0x2A);
    machine.mem_store_byte(0xB9ED6, 0xF4);
    machine.mem_store_byte(0xB9ED7, 0xC5);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFE76D53);
    EXPECT_EQ(cpu.get_ebx(), 0x49AE7899);
    EXPECT_EQ(cpu.get_ecx(), 0x00000090);
    EXPECT_EQ(cpu.get_edx(), 0x0092B10B);
    EXPECT_EQ(cpu.get_esi(), 0x042A7ABA);
    EXPECT_EQ(cpu.get_edi(), 0x7CAE23C5);
    EXPECT_EQ(cpu.get_ebp(), 0x5EDF718D);
    EXPECT_EQ(cpu.get_esp(), 0x000000FA);
    EXPECT_EQ(cpu.get_cs(), 0x0000B507);
    EXPECT_EQ(cpu.get_ds(), 0x0000AC15);
    EXPECT_EQ(cpu.get_es(), 0x0000CC01);
    EXPECT_EQ(cpu.get_fs(), 0x00000099);
    EXPECT_EQ(cpu.get_gs(), 0x0000648B);
    EXPECT_EQ(cpu.get_ss(), 0x0000CABA);
    EXPECT_EQ(cpu.get_eip(), 0x00004E63);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0813);

    // Final RAM entries
    EXPECT_FLAGS_LO(0xCAC9E, 0x13);
    EXPECT_FLAGS_HI(0xCAC9F, 0x08);
    EXPECT_EQ(memory.load8(0xCAC9C), 0x00);
    EXPECT_EQ(memory.load8(0xCAC9D), 0x00);
    EXPECT_EQ(memory.load8(0xCAC9A), 0x48);
    EXPECT_EQ(memory.load8(0xCAC9B), 0x6B);
}

//
// enter 92D2h,26h
//
TEST_F(Test386, enter_92D2h_26h_batch50)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF1C84553);
    cpu.set_ebx(0x5F0F9B9A);
    cpu.set_ecx(0x6A648E8A);
    cpu.set_edx(0x03AC3397);
    cpu.set_esi(0xF522B2B4);
    cpu.set_edi(0x1204D83C);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x00000FDC);
    cpu.set_cs(0x00008908);
    cpu.set_ds(0x000070C5);
    cpu.set_es(0x0000FDB3);
    cpu.set_fs(0x000057BC);
    cpu.set_gs(0x00004FF2);
    cpu.set_ss(0x00006768);
    cpu.set_eip(0x00002E60);
    cpu.set_eflags(0xFFFC0053);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8BEE0, 0x36);
    machine.mem_store_byte(0x8BEE1, 0xC8);
    machine.mem_store_byte(0x8BEE2, 0xD2);
    machine.mem_store_byte(0x8BEE3, 0x92);
    machine.mem_store_byte(0x8BEE4, 0x26);
    machine.mem_store_byte(0x8BEE5, 0xF4);
    machine.mem_store_byte(0x8BEE6, 0x28);
    machine.mem_store_byte(0x8BEE7, 0x97);
    machine.mem_store_byte(0x8BEE8, 0x33);
    machine.mem_store_byte(0x8BEE9, 0x1F);
    machine.mem_store_byte(0x8BEEA, 0x1D);
    machine.mem_store_byte(0x8BEEB, 0x45);
    machine.mem_store_byte(0x8BEEC, 0xFB);
    machine.mem_store_byte(0x8BEED, 0x20);
    machine.mem_store_byte(0x8BEEE, 0x73);
    machine.mem_store_byte(0x8BEEF, 0x1A);
    machine.mem_store_byte(0x8BEF0, 0x02);
    machine.mem_store_byte(0x8BEF1, 0x2D);
    machine.mem_store_byte(0x8BEF2, 0xBB);
    machine.mem_store_byte(0x8BEF3, 0x27);
    machine.mem_store_byte(0x00030, 0xA2);
    machine.mem_store_byte(0x00031, 0x1B);
    machine.mem_store_byte(0x00032, 0x49);
    machine.mem_store_byte(0x00033, 0xD5);
    machine.mem_store_byte(0xD7032, 0xF4);
    machine.mem_store_byte(0xD7033, 0x32);
    machine.mem_store_byte(0xD7034, 0xF4);
    machine.mem_store_byte(0xD7035, 0x7C);
    machine.mem_store_byte(0xD7036, 0xF4);
    machine.mem_store_byte(0xD7037, 0x96);
    machine.mem_store_byte(0xD7038, 0xF4);
    machine.mem_store_byte(0xD7039, 0x11);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF1C84553);
    EXPECT_EQ(cpu.get_ebx(), 0x5F0F9B9A);
    EXPECT_EQ(cpu.get_ecx(), 0x6A648E8A);
    EXPECT_EQ(cpu.get_edx(), 0x03AC3397);
    EXPECT_EQ(cpu.get_esi(), 0xF522B2B4);
    EXPECT_EQ(cpu.get_edi(), 0x1204D83C);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x00000FD6);
    EXPECT_EQ(cpu.get_cs(), 0x0000D549);
    EXPECT_EQ(cpu.get_ds(), 0x000070C5);
    EXPECT_EQ(cpu.get_es(), 0x0000FDB3);
    EXPECT_EQ(cpu.get_fs(), 0x000057BC);
    EXPECT_EQ(cpu.get_gs(), 0x00004FF2);
    EXPECT_EQ(cpu.get_ss(), 0x00006768);
    EXPECT_EQ(cpu.get_eip(), 0x00001BA3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0053);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x6865A, 0x53);
    EXPECT_FLAGS_HI(0x6865B, 0x00);
    EXPECT_EQ(memory.load8(0x68658), 0x08);
    EXPECT_EQ(memory.load8(0x68659), 0x89);
    EXPECT_EQ(memory.load8(0x68656), 0x60);
    EXPECT_EQ(memory.load8(0x68657), 0x2E);
}

//
// leave
//
TEST_F(Test386, leave_batch50)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007FFF);
    cpu.set_ebx(0xEF8E2911);
    cpu.set_ecx(0xDE63E34C);
    cpu.set_edx(0x26C23B7B);
    cpu.set_esi(0xFCAF1697);
    cpu.set_edi(0xFA5F7FF0);
    cpu.set_ebp(0xFFFFFFFF);
    cpu.set_esp(0x0000AB56);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000ADF2);
    cpu.set_es(0x00000651);
    cpu.set_fs(0x0000CA60);
    cpu.set_gs(0x00003F66);
    cpu.set_ss(0x0000FB08);
    cpu.set_eip(0x00009CB8);
    cpu.set_eflags(0xFFFC0882);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x109CA8, 0x65);
    machine.mem_store_byte(0x109CA9, 0x65);
    machine.mem_store_byte(0x109CAA, 0xC9);
    machine.mem_store_byte(0x109CAB, 0xF4);
    machine.mem_store_byte(0x109CAC, 0xFF);
    machine.mem_store_byte(0x109CAD, 0xFF);
    machine.mem_store_byte(0x109CAE, 0xFF);
    machine.mem_store_byte(0x109CAF, 0xFF);
    machine.mem_store_byte(0x109CB0, 0xFF);
    machine.mem_store_byte(0x109CB1, 0xFF);
    machine.mem_store_byte(0x109CB2, 0xFF);
    machine.mem_store_byte(0x109CB3, 0xFF);
    machine.mem_store_byte(0x109CB4, 0xFF);
    machine.mem_store_byte(0x109CB5, 0xFF);
    machine.mem_store_byte(0x109CB6, 0xFF);
    machine.mem_store_byte(0x109CB7, 0xFF);
    machine.mem_store_byte(0x109CB8, 0xFF);
    machine.mem_store_byte(0x109CB9, 0xFF);
    machine.mem_store_byte(0x109CBA, 0xFF);
    machine.mem_store_byte(0x109CBB, 0xFF);
    machine.mem_store_byte(0x00030, 0xB7);
    machine.mem_store_byte(0x00031, 0x3D);
    machine.mem_store_byte(0x00032, 0x54);
    machine.mem_store_byte(0x00033, 0x18);
    machine.mem_store_byte(0x1C2F6, 0xFF);
    machine.mem_store_byte(0x1C2F7, 0xF4);
    machine.mem_store_byte(0x1C2F8, 0xFF);
    machine.mem_store_byte(0x1C2F9, 0xF4);
    machine.mem_store_byte(0x1C2FA, 0xFF);
    machine.mem_store_byte(0x1C2FB, 0xF4);
    machine.mem_store_byte(0x1C2FC, 0xFF);
    machine.mem_store_byte(0x1C2FD, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebx(), 0xEF8E2911);
    EXPECT_EQ(cpu.get_ecx(), 0xDE63E34C);
    EXPECT_EQ(cpu.get_edx(), 0x26C23B7B);
    EXPECT_EQ(cpu.get_esi(), 0xFCAF1697);
    EXPECT_EQ(cpu.get_edi(), 0xFA5F7FF0);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000AB50);
    EXPECT_EQ(cpu.get_cs(), 0x00001854);
    EXPECT_EQ(cpu.get_ds(), 0x0000ADF2);
    EXPECT_EQ(cpu.get_es(), 0x00000651);
    EXPECT_EQ(cpu.get_fs(), 0x0000CA60);
    EXPECT_EQ(cpu.get_gs(), 0x00003F66);
    EXPECT_EQ(cpu.get_ss(), 0x0000FB08);
    EXPECT_EQ(cpu.get_eip(), 0x00003DB8);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0882);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x105BD4, 0x82);
    EXPECT_FLAGS_HI(0x105BD5, 0x08);
    EXPECT_EQ(memory.load8(0x105BD2), 0xFF);
    EXPECT_EQ(memory.load8(0x105BD3), 0xFF);
    EXPECT_EQ(memory.load8(0x105BD0), 0xB8);
    EXPECT_EQ(memory.load8(0x105BD1), 0x9C);
}

//
// o32 enter 92D2h,26h
//
TEST_F(Test386, o32_enter_92D2h_26h_batch50)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF1C84553);
    cpu.set_ebx(0x5F0F9B9A);
    cpu.set_ecx(0x6A648E8A);
    cpu.set_edx(0x03AC3397);
    cpu.set_esi(0xF522B2B4);
    cpu.set_edi(0x1204D83C);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x00000FDC);
    cpu.set_cs(0x00008908);
    cpu.set_ds(0x000070C5);
    cpu.set_es(0x0000FDB3);
    cpu.set_fs(0x000057BC);
    cpu.set_gs(0x00004FF2);
    cpu.set_ss(0x00006768);
    cpu.set_eip(0x00002E60);
    cpu.set_eflags(0xFFFC0053);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8BEE0, 0x36);
    machine.mem_store_byte(0x8BEE1, 0x66);
    machine.mem_store_byte(0x8BEE2, 0xC8);
    machine.mem_store_byte(0x8BEE3, 0xD2);
    machine.mem_store_byte(0x8BEE4, 0x92);
    machine.mem_store_byte(0x8BEE5, 0x26);
    machine.mem_store_byte(0x8BEE6, 0xF4);
    machine.mem_store_byte(0x8BEE7, 0x97);
    machine.mem_store_byte(0x8BEE8, 0x33);
    machine.mem_store_byte(0x8BEE9, 0x1F);
    machine.mem_store_byte(0x8BEEA, 0x1D);
    machine.mem_store_byte(0x8BEEB, 0x45);
    machine.mem_store_byte(0x8BEEC, 0xFB);
    machine.mem_store_byte(0x8BEED, 0x20);
    machine.mem_store_byte(0x8BEEE, 0x73);
    machine.mem_store_byte(0x8BEEF, 0x1A);
    machine.mem_store_byte(0x8BEF0, 0x02);
    machine.mem_store_byte(0x8BEF1, 0x2D);
    machine.mem_store_byte(0x00030, 0xA2);
    machine.mem_store_byte(0x00031, 0x1B);
    machine.mem_store_byte(0x00032, 0x49);
    machine.mem_store_byte(0x00033, 0xD5);
    machine.mem_store_byte(0xD7032, 0xF4);
    machine.mem_store_byte(0xD7033, 0x32);
    machine.mem_store_byte(0xD7034, 0xF4);
    machine.mem_store_byte(0xD7035, 0x7C);
    machine.mem_store_byte(0xD7036, 0xF4);
    machine.mem_store_byte(0xD7037, 0x96);
    machine.mem_store_byte(0xD7038, 0xF4);
    machine.mem_store_byte(0xD7039, 0x11);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF1C84553);
    EXPECT_EQ(cpu.get_ebx(), 0x5F0F9B9A);
    EXPECT_EQ(cpu.get_ecx(), 0x6A648E8A);
    EXPECT_EQ(cpu.get_edx(), 0x03AC3397);
    EXPECT_EQ(cpu.get_esi(), 0xF522B2B4);
    EXPECT_EQ(cpu.get_edi(), 0x1204D83C);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x00000FD6);
    EXPECT_EQ(cpu.get_cs(), 0x0000D549);
    EXPECT_EQ(cpu.get_ds(), 0x000070C5);
    EXPECT_EQ(cpu.get_es(), 0x0000FDB3);
    EXPECT_EQ(cpu.get_fs(), 0x000057BC);
    EXPECT_EQ(cpu.get_gs(), 0x00004FF2);
    EXPECT_EQ(cpu.get_ss(), 0x00006768);
    EXPECT_EQ(cpu.get_eip(), 0x00001BA3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0053);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x68658, 0x08);
    EXPECT_FLAGS_HI(0x68659, 0x89);
    EXPECT_EQ(memory.load8(0x6865A), 0x53);
    EXPECT_EQ(memory.load8(0x6865B), 0x00);
    EXPECT_EQ(memory.load8(0x68656), 0x60);
    EXPECT_EQ(memory.load8(0x68657), 0x2E);
}

//
// o32 leave
//
TEST_F(Test386, o32_leave_batch50)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007FFF);
    cpu.set_ebx(0xEF8E2911);
    cpu.set_ecx(0xDE63E34C);
    cpu.set_edx(0x26C23B7B);
    cpu.set_esi(0xFCAF1697);
    cpu.set_edi(0xFA5F7FF0);
    cpu.set_ebp(0xFFFFFFFF);
    cpu.set_esp(0x0000AB56);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000ADF2);
    cpu.set_es(0x00000651);
    cpu.set_fs(0x0000CA60);
    cpu.set_gs(0x00003F66);
    cpu.set_ss(0x0000FB08);
    cpu.set_eip(0x00009CB8);
    cpu.set_eflags(0xFFFC0882);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x109CA8, 0x65);
    machine.mem_store_byte(0x109CA9, 0x65);
    machine.mem_store_byte(0x109CAA, 0x66);
    machine.mem_store_byte(0x109CAB, 0xC9);
    machine.mem_store_byte(0x109CAC, 0xF4);
    machine.mem_store_byte(0x109CAD, 0xFF);
    machine.mem_store_byte(0x109CAE, 0xFF);
    machine.mem_store_byte(0x109CAF, 0xFF);
    machine.mem_store_byte(0x109CB0, 0xFF);
    machine.mem_store_byte(0x109CB1, 0xFF);
    machine.mem_store_byte(0x109CB2, 0xFF);
    machine.mem_store_byte(0x109CB3, 0xFF);
    machine.mem_store_byte(0x109CB4, 0xFF);
    machine.mem_store_byte(0x109CB5, 0xFF);
    machine.mem_store_byte(0x109CB6, 0xFF);
    machine.mem_store_byte(0x109CB7, 0xFF);
    machine.mem_store_byte(0x109CB8, 0xFF);
    machine.mem_store_byte(0x109CB9, 0xFF);
    machine.mem_store_byte(0x109CBA, 0xFF);
    machine.mem_store_byte(0x109CBB, 0xFF);
    machine.mem_store_byte(0x00030, 0xB7);
    machine.mem_store_byte(0x00031, 0x3D);
    machine.mem_store_byte(0x00032, 0x54);
    machine.mem_store_byte(0x00033, 0x18);
    machine.mem_store_byte(0x1C2F6, 0xFF);
    machine.mem_store_byte(0x1C2F7, 0xF4);
    machine.mem_store_byte(0x1C2F8, 0xFF);
    machine.mem_store_byte(0x1C2F9, 0xF4);
    machine.mem_store_byte(0x1C2FA, 0xFF);
    machine.mem_store_byte(0x1C2FB, 0xF4);
    machine.mem_store_byte(0x1C2FC, 0xFF);
    machine.mem_store_byte(0x1C2FD, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebx(), 0xEF8E2911);
    EXPECT_EQ(cpu.get_ecx(), 0xDE63E34C);
    EXPECT_EQ(cpu.get_edx(), 0x26C23B7B);
    EXPECT_EQ(cpu.get_esi(), 0xFCAF1697);
    EXPECT_EQ(cpu.get_edi(), 0xFA5F7FF0);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000AB50);
    EXPECT_EQ(cpu.get_cs(), 0x00001854);
    EXPECT_EQ(cpu.get_ds(), 0x0000ADF2);
    EXPECT_EQ(cpu.get_es(), 0x00000651);
    EXPECT_EQ(cpu.get_fs(), 0x0000CA60);
    EXPECT_EQ(cpu.get_gs(), 0x00003F66);
    EXPECT_EQ(cpu.get_ss(), 0x0000FB08);
    EXPECT_EQ(cpu.get_eip(), 0x00003DB8);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0882);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x105BD4, 0x82);
    EXPECT_FLAGS_HI(0x105BD5, 0x08);
    EXPECT_EQ(memory.load8(0x105BD2), 0xFF);
    EXPECT_EQ(memory.load8(0x105BD3), 0xFF);
    EXPECT_EQ(memory.load8(0x105BD0), 0xB8);
    EXPECT_EQ(memory.load8(0x105BD1), 0x9C);
}
