#include "test386.h"

//
// cmpsb
//
TEST_F(Test386, cmpsb_string)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007FFF);
    cpu.set_ebx(0xFB2FE814);
    cpu.set_ecx(0x501174C1);
    cpu.set_edx(0xFFFFFFFA);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0x008EC25C);
    cpu.set_ebp(0x7900A601);
    cpu.set_esp(0x000000D1);
    cpu.set_cs(0x0000BFA5);
    cpu.set_ds(0x0000A679);
    cpu.set_es(0x00000D7A);
    cpu.set_fs(0x0000715A);
    cpu.set_gs(0x0000E5E0);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00008980);
    cpu.set_eflags(0xFFFC0443);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC83D0, 0xA6);
    machine.mem_store_byte(0xC83D1, 0xF4);
    machine.mem_store_byte(0xC83D2, 0xD6);
    machine.mem_store_byte(0xC83D3, 0x9F);
    machine.mem_store_byte(0xC83D4, 0x09);
    machine.mem_store_byte(0xC83D5, 0x05);
    machine.mem_store_byte(0xC83D6, 0xBB);
    machine.mem_store_byte(0xC83D7, 0x69);
    machine.mem_store_byte(0xC83D8, 0xDB);
    machine.mem_store_byte(0xC83D9, 0xF0);
    machine.mem_store_byte(0x199FC, 0x34);
    machine.mem_store_byte(0xA6790, 0x9E);
    machine.mem_store_byte(0xC83DA, 0x87);
    machine.mem_store_byte(0xC83DB, 0x7B);
    machine.mem_store_byte(0xC83DC, 0xB3);
    machine.mem_store_byte(0xC83DD, 0x64);
    machine.mem_store_byte(0xC83DE, 0x25);
    machine.mem_store_byte(0xC83DF, 0xE8);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebx(), 0xFB2FE814);
    EXPECT_EQ(cpu.get_ecx(), 0x501174C1);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFA);
    EXPECT_EQ(cpu.get_esi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edi(), 0x008EC25B);
    EXPECT_EQ(cpu.get_ebp(), 0x7900A601);
    EXPECT_EQ(cpu.get_esp(), 0x000000D1);
    EXPECT_EQ(cpu.get_cs(), 0x0000BFA5);
    EXPECT_EQ(cpu.get_ds(), 0x0000A679);
    EXPECT_EQ(cpu.get_es(), 0x00000D7A);
    EXPECT_EQ(cpu.get_fs(), 0x0000715A);
    EXPECT_EQ(cpu.get_gs(), 0x0000E5E0);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x00008982);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C06);

    // Final RAM entries
}

//
// insb
//
TEST_F(Test386, insb_string)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7E8FA0DB);
    cpu.set_ebx(0x5EE5FA57);
    cpu.set_ecx(0x08497F07);
    cpu.set_edx(0xFFFFFFFC);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0xFFFFFFFF);
    cpu.set_ebp(0xB7598C47);
    cpu.set_esp(0x0000E2B4);
    cpu.set_cs(0x0000922D);
    cpu.set_ds(0x00007CA0);
    cpu.set_es(0x0000D3E5);
    cpu.set_fs(0x0000F406);
    cpu.set_gs(0x0000966D);
    cpu.set_ss(0x000016FA);
    cpu.set_eip(0x00003DE0);
    cpu.set_eflags(0xFFFC0007);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x960B0, 0x6C);
    machine.mem_store_byte(0x960B1, 0xF4);
    machine.mem_store_byte(0x960B2, 0xAF);
    machine.mem_store_byte(0x960B3, 0x66);
    machine.mem_store_byte(0x960B4, 0x9D);
    machine.mem_store_byte(0x960B5, 0x66);
    machine.mem_store_byte(0x960B6, 0xF7);
    machine.mem_store_byte(0x960B7, 0x4A);
    machine.mem_store_byte(0x960B8, 0x54);
    machine.mem_store_byte(0x960B9, 0x36);
    machine.mem_store_byte(0x960BA, 0xB8);
    machine.mem_store_byte(0x960BB, 0xD1);
    machine.mem_store_byte(0x960BC, 0x82);
    machine.mem_store_byte(0x960BD, 0xBD);
    machine.mem_store_byte(0x960BE, 0xA8);
    machine.mem_store_byte(0x960BF, 0x80);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7E8FA0DB);
    EXPECT_EQ(cpu.get_ebx(), 0x5EE5FA57);
    EXPECT_EQ(cpu.get_ecx(), 0x08497F07);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFC);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0xFFFF0000);
    EXPECT_EQ(cpu.get_ebp(), 0xB7598C47);
    EXPECT_EQ(cpu.get_esp(), 0x0000E2B4);
    EXPECT_EQ(cpu.get_cs(), 0x0000922D);
    EXPECT_EQ(cpu.get_ds(), 0x00007CA0);
    EXPECT_EQ(cpu.get_es(), 0x0000D3E5);
    EXPECT_EQ(cpu.get_fs(), 0x0000F406);
    EXPECT_EQ(cpu.get_gs(), 0x0000966D);
    EXPECT_EQ(cpu.get_ss(), 0x000016FA);
    EXPECT_EQ(cpu.get_eip(), 0x00003DE2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0007);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE3E4F), 0xFF);
}

//
// outsb
//
TEST_F(Test386, outsb_string)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xADCE9F84);
    cpu.set_ebx(0x30415BF1);
    cpu.set_ecx(0xFDCCC926);
    cpu.set_edx(0xC7CC2AED);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0xFFF16127);
    cpu.set_ebp(0x709C4333);
    cpu.set_esp(0x0000069C);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000BFD9);
    cpu.set_es(0x000002AF);
    cpu.set_fs(0x000084FD);
    cpu.set_gs(0x0000002B);
    cpu.set_ss(0x00008000);
    cpu.set_eip(0x0000AFF0);
    cpu.set_eflags(0xFFFC0802);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10AFE0, 0x26);
    machine.mem_store_byte(0x10AFE1, 0x36);
    machine.mem_store_byte(0x10AFE2, 0x3E);
    machine.mem_store_byte(0x10AFE3, 0x6E);
    machine.mem_store_byte(0x10AFE4, 0xF4);
    machine.mem_store_byte(0x10AFE5, 0xDF);
    machine.mem_store_byte(0x10AFE6, 0xA5);
    machine.mem_store_byte(0x10AFE7, 0x60);
    machine.mem_store_byte(0x10AFE8, 0x5E);
    machine.mem_store_byte(0x10AFE9, 0xEA);
    machine.mem_store_byte(0x10AFEA, 0x01);
    machine.mem_store_byte(0x10AFEB, 0x2F);
    machine.mem_store_byte(0x10AFEC, 0x1B);
    machine.mem_store_byte(0x10AFED, 0x5C);
    machine.mem_store_byte(0x10AFEE, 0xAB);
    machine.mem_store_byte(0x10AFEF, 0x65);
    machine.mem_store_byte(0x10AFF0, 0x88);
    machine.mem_store_byte(0x10AFF1, 0xFB);
    machine.mem_store_byte(0x10AFF2, 0xF4);
    machine.mem_store_byte(0x10AFF3, 0xD7);
    machine.mem_store_byte(0xCFD8F, 0xB9);
    machine.mem_store_byte(0x10AFF4, 0x2F);
    machine.mem_store_byte(0x10AFF5, 0xE4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xADCE9F84);
    EXPECT_EQ(cpu.get_ebx(), 0x30415BF1);
    EXPECT_EQ(cpu.get_ecx(), 0xFDCCC926);
    EXPECT_EQ(cpu.get_edx(), 0xC7CC2AED);
    EXPECT_EQ(cpu.get_esi(), 0xFFFF0000);
    EXPECT_EQ(cpu.get_edi(), 0xFFF16127);
    EXPECT_EQ(cpu.get_ebp(), 0x709C4333);
    EXPECT_EQ(cpu.get_esp(), 0x0000069C);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000BFD9);
    EXPECT_EQ(cpu.get_es(), 0x000002AF);
    EXPECT_EQ(cpu.get_fs(), 0x000084FD);
    EXPECT_EQ(cpu.get_gs(), 0x0000002B);
    EXPECT_EQ(cpu.get_ss(), 0x00008000);
    EXPECT_EQ(cpu.get_eip(), 0x0000AFF5);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0802);

    // Final RAM entries
}

//
// scasb
//
TEST_F(Test386, scasb_string)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x4927C79C);
    cpu.set_ecx(0x24561098);
    cpu.set_edx(0x152D68BA);
    cpu.set_esi(0x003FFFFF);
    cpu.set_edi(0x0FFFFFFF);
    cpu.set_ebp(0xBA952D9F);
    cpu.set_esp(0x00006AE2);
    cpu.set_cs(0x0000E827);
    cpu.set_ds(0x00000721);
    cpu.set_es(0x0000E347);
    cpu.set_fs(0x00009E6D);
    cpu.set_gs(0x0000FCDA);
    cpu.set_ss(0x0000EF39);
    cpu.set_eip(0x000063C8);
    cpu.set_eflags(0xFFFC0097);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE638, 0xAE);
    machine.mem_store_byte(0xEE639, 0xF4);
    machine.mem_store_byte(0xEE63A, 0x00);
    machine.mem_store_byte(0xEE63B, 0x00);
    machine.mem_store_byte(0xEE63C, 0x00);
    machine.mem_store_byte(0xEE63D, 0x00);
    machine.mem_store_byte(0xEE63E, 0x00);
    machine.mem_store_byte(0xEE63F, 0x00);
    machine.mem_store_byte(0xEE640, 0x00);
    machine.mem_store_byte(0xEE641, 0x00);
    machine.mem_store_byte(0xF346F, 0x00);
    machine.mem_store_byte(0xEE642, 0x00);
    machine.mem_store_byte(0xEE643, 0x00);
    machine.mem_store_byte(0xEE644, 0x00);
    machine.mem_store_byte(0xEE645, 0x00);
    machine.mem_store_byte(0xEE646, 0x00);
    machine.mem_store_byte(0xEE647, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0x4927C79C);
    EXPECT_EQ(cpu.get_ecx(), 0x24561098);
    EXPECT_EQ(cpu.get_edx(), 0x152D68BA);
    EXPECT_EQ(cpu.get_esi(), 0x003FFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x0FFF0000);
    EXPECT_EQ(cpu.get_ebp(), 0xBA952D9F);
    EXPECT_EQ(cpu.get_esp(), 0x00006AE2);
    EXPECT_EQ(cpu.get_cs(), 0x0000E827);
    EXPECT_EQ(cpu.get_ds(), 0x00000721);
    EXPECT_EQ(cpu.get_es(), 0x0000E347);
    EXPECT_EQ(cpu.get_fs(), 0x00009E6D);
    EXPECT_EQ(cpu.get_gs(), 0x0000FCDA);
    EXPECT_EQ(cpu.get_ss(), 0x0000EF39);
    EXPECT_EQ(cpu.get_eip(), 0x000063CA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0046);

    // Final RAM entries
}

//
// stosb
//
TEST_F(Test386, stosb_string)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE8D4B0FE);
    cpu.set_ebx(0x0D632983);
    cpu.set_ecx(0x6D5C5015);
    cpu.set_edx(0x5480A946);
    cpu.set_esi(0x14D7FE20);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x46F6610A);
    cpu.set_esp(0x0000DD1C);
    cpu.set_cs(0x000047B5);
    cpu.set_ds(0x0000B7C6);
    cpu.set_es(0x0000B66C);
    cpu.set_fs(0x0000D139);
    cpu.set_gs(0x0000A296);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x0000F0E8);
    cpu.set_eflags(0xFFFC04C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x56C38, 0xAA);
    machine.mem_store_byte(0x56C39, 0xF4);
    machine.mem_store_byte(0x56C3A, 0x9A);
    machine.mem_store_byte(0x56C3B, 0xDA);
    machine.mem_store_byte(0x56C3C, 0xB8);
    machine.mem_store_byte(0x56C3D, 0x2D);
    machine.mem_store_byte(0x56C3E, 0x76);
    machine.mem_store_byte(0x56C3F, 0x42);
    machine.mem_store_byte(0x56C40, 0xCF);
    machine.mem_store_byte(0x56C41, 0x5E);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE8D4B0FE);
    EXPECT_EQ(cpu.get_ebx(), 0x0D632983);
    EXPECT_EQ(cpu.get_ecx(), 0x6D5C5015);
    EXPECT_EQ(cpu.get_edx(), 0x5480A946);
    EXPECT_EQ(cpu.get_esi(), 0x14D7FE20);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x46F6610A);
    EXPECT_EQ(cpu.get_esp(), 0x0000DD1C);
    EXPECT_EQ(cpu.get_cs(), 0x000047B5);
    EXPECT_EQ(cpu.get_ds(), 0x0000B7C6);
    EXPECT_EQ(cpu.get_es(), 0x0000B66C);
    EXPECT_EQ(cpu.get_fs(), 0x0000D139);
    EXPECT_EQ(cpu.get_gs(), 0x0000A296);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x0000F0EA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB66C0), 0xFE);
}

//
// stosw
//
TEST_F(Test386, stosw_string)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x728B37BE);
    cpu.set_ebx(0x857EF094);
    cpu.set_ecx(0x85D26BBB);
    cpu.set_edx(0xF5C15FB6);
    cpu.set_esi(0x9E7ED4EC);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0xB275DE81);
    cpu.set_esp(0x0000BA68);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000A575);
    cpu.set_es(0x0000C18F);
    cpu.set_fs(0x0000DE60);
    cpu.set_gs(0x000000CF);
    cpu.set_ss(0x00003DAE);
    cpu.set_eip(0x000017E8);
    cpu.set_eflags(0xFFFC0456);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1017D8, 0xAB);
    machine.mem_store_byte(0x1017D9, 0xF4);
    machine.mem_store_byte(0x1017DA, 0x2B);
    machine.mem_store_byte(0x1017DB, 0x30);
    machine.mem_store_byte(0x1017DC, 0xE7);
    machine.mem_store_byte(0x1017DD, 0xBD);
    machine.mem_store_byte(0x1017DE, 0x9F);
    machine.mem_store_byte(0x1017DF, 0x5A);
    machine.mem_store_byte(0x1017E0, 0x30);
    machine.mem_store_byte(0x1017E1, 0x10);
    machine.mem_store_byte(0x1017E2, 0x0E);
    machine.mem_store_byte(0x1017E3, 0xEC);
    machine.mem_store_byte(0x1017E4, 0x53);
    machine.mem_store_byte(0x1017E5, 0x76);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x728B37BE);
    EXPECT_EQ(cpu.get_ebx(), 0x857EF094);
    EXPECT_EQ(cpu.get_ecx(), 0x85D26BBB);
    EXPECT_EQ(cpu.get_edx(), 0xF5C15FB6);
    EXPECT_EQ(cpu.get_esi(), 0x9E7ED4EC);
    EXPECT_EQ(cpu.get_edi(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_ebp(), 0xB275DE81);
    EXPECT_EQ(cpu.get_esp(), 0x0000BA68);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000A575);
    EXPECT_EQ(cpu.get_es(), 0x0000C18F);
    EXPECT_EQ(cpu.get_fs(), 0x0000DE60);
    EXPECT_EQ(cpu.get_gs(), 0x000000CF);
    EXPECT_EQ(cpu.get_ss(), 0x00003DAE);
    EXPECT_EQ(cpu.get_eip(), 0x000017EA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0456);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC18F0), 0xBE);
    EXPECT_EQ(memory.load8(0xC18F1), 0x37);
}
