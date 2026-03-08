#include "test386.h"

//
// bt dword [ds:eax-F253h],31h
//
TEST_F(Test386, bt_dword_ds_eax_F253h_31h_batch9)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007567);
    cpu.set_ebx(0xDF11ED5E);
    cpu.set_ecx(0x0B1C35E7);
    cpu.set_edx(0xB44CFE46);
    cpu.set_esi(0x0C39B0F7);
    cpu.set_edi(0xFFDF3886);
    cpu.set_ebp(0x5DC41F3A);
    cpu.set_esp(0x0000AC28);
    cpu.set_cs(0x0000E834);
    cpu.set_ds(0x00007C4B);
    cpu.set_es(0x000074A8);
    cpu.set_fs(0x000097DB);
    cpu.set_gs(0x0000C226);
    cpu.set_ss(0x00000969);
    cpu.set_eip(0x000064E8);
    cpu.set_eflags(0xFFFC0096);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE828, 0x66);
    machine.mem_store_byte(0xEE829, 0x67);
    machine.mem_store_byte(0xEE82A, 0x0F);
    machine.mem_store_byte(0xEE82B, 0xBA);
    machine.mem_store_byte(0xEE82C, 0xA0);
    machine.mem_store_byte(0xEE82D, 0xAD);
    machine.mem_store_byte(0xEE82E, 0x0D);
    machine.mem_store_byte(0xEE82F, 0xFF);
    machine.mem_store_byte(0xEE830, 0xFF);
    machine.mem_store_byte(0xEE831, 0x31);
    machine.mem_store_byte(0xEE832, 0xF4);
    machine.mem_store_byte(0xEE833, 0xEF);
    machine.mem_store_byte(0xEE834, 0xF6);
    machine.mem_store_byte(0xEE835, 0xF3);
    machine.mem_store_byte(0xEE836, 0x9A);
    machine.mem_store_byte(0xEE837, 0x48);
    machine.mem_store_byte(0xEE838, 0x27);
    machine.mem_store_byte(0xEE839, 0xCA);
    machine.mem_store_byte(0xEE83A, 0xC7);
    machine.mem_store_byte(0xEE83B, 0x4E);
    machine.mem_store_byte(0xEE83C, 0x16);
    machine.mem_store_byte(0xEE83D, 0x0F);
    machine.mem_store_byte(0xEE83E, 0x92);
    machine.mem_store_byte(0xEE83F, 0x94);
    machine.mem_store_byte(0x00034, 0x50);
    machine.mem_store_byte(0x00035, 0xB9);
    machine.mem_store_byte(0x00036, 0x34);
    machine.mem_store_byte(0x00037, 0x51);
    machine.mem_store_byte(0x5CC90, 0xF4);
    machine.mem_store_byte(0x5CC91, 0x63);
    machine.mem_store_byte(0x5CC92, 0xF4);
    machine.mem_store_byte(0x5CC93, 0x68);
    machine.mem_store_byte(0x5CC94, 0xF4);
    machine.mem_store_byte(0x5CC95, 0x2E);
    machine.mem_store_byte(0x5CC96, 0xF4);
    machine.mem_store_byte(0x5CC97, 0x6B);
    machine.mem_store_byte(0x5CC98, 0xF4);
    machine.mem_store_byte(0x5CC99, 0x41);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007567);
    EXPECT_EQ(cpu.get_ebx(), 0xDF11ED5E);
    EXPECT_EQ(cpu.get_ecx(), 0x0B1C35E7);
    EXPECT_EQ(cpu.get_edx(), 0xB44CFE46);
    EXPECT_EQ(cpu.get_esi(), 0x0C39B0F7);
    EXPECT_EQ(cpu.get_edi(), 0xFFDF3886);
    EXPECT_EQ(cpu.get_ebp(), 0x5DC41F3A);
    EXPECT_EQ(cpu.get_esp(), 0x0000AC22);
    EXPECT_EQ(cpu.get_cs(), 0x00005134);
    EXPECT_EQ(cpu.get_ds(), 0x00007C4B);
    EXPECT_EQ(cpu.get_es(), 0x000074A8);
    EXPECT_EQ(cpu.get_fs(), 0x000097DB);
    EXPECT_EQ(cpu.get_gs(), 0x0000C226);
    EXPECT_EQ(cpu.get_ss(), 0x00000969);
    EXPECT_EQ(cpu.get_eip(), 0x0000B951);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0096);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x142B6), 0x96);
    EXPECT_EQ(memory.load8(0x142B7), 0x00);
    EXPECT_EQ(memory.load8(0x142B4), 0x34);
    EXPECT_EQ(memory.load8(0x142B5), 0xE8);
    EXPECT_EQ(memory.load8(0x142B2), 0xE8);
    EXPECT_EQ(memory.load8(0x142B3), 0x64);
}

//
// bt word [ds:eax-F253h],31h
//
TEST_F(Test386, bt_word_ds_eax_F253h_31h_batch9)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007567);
    cpu.set_ebx(0xDF11ED5E);
    cpu.set_ecx(0x0B1C35E7);
    cpu.set_edx(0xB44CFE46);
    cpu.set_esi(0x0C39B0F7);
    cpu.set_edi(0xFFDF3886);
    cpu.set_ebp(0x5DC41F3A);
    cpu.set_esp(0x0000AC28);
    cpu.set_cs(0x0000E834);
    cpu.set_ds(0x00007C4B);
    cpu.set_es(0x000074A8);
    cpu.set_fs(0x000097DB);
    cpu.set_gs(0x0000C226);
    cpu.set_ss(0x00000969);
    cpu.set_eip(0x000064E8);
    cpu.set_eflags(0xFFFC0096);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE828, 0x67);
    machine.mem_store_byte(0xEE829, 0x0F);
    machine.mem_store_byte(0xEE82A, 0xBA);
    machine.mem_store_byte(0xEE82B, 0xA0);
    machine.mem_store_byte(0xEE82C, 0xAD);
    machine.mem_store_byte(0xEE82D, 0x0D);
    machine.mem_store_byte(0xEE82E, 0xFF);
    machine.mem_store_byte(0xEE82F, 0xFF);
    machine.mem_store_byte(0xEE830, 0x31);
    machine.mem_store_byte(0xEE831, 0xF4);
    machine.mem_store_byte(0xEE832, 0x4B);
    machine.mem_store_byte(0xEE833, 0xEF);
    machine.mem_store_byte(0xEE834, 0xF6);
    machine.mem_store_byte(0xEE835, 0xF3);
    machine.mem_store_byte(0xEE836, 0x9A);
    machine.mem_store_byte(0xEE837, 0x48);
    machine.mem_store_byte(0xEE838, 0x27);
    machine.mem_store_byte(0xEE839, 0xCA);
    machine.mem_store_byte(0xEE83A, 0xC7);
    machine.mem_store_byte(0xEE83B, 0x4E);
    machine.mem_store_byte(0xEE83C, 0x16);
    machine.mem_store_byte(0xEE83D, 0x0F);
    machine.mem_store_byte(0xEE83E, 0x92);
    machine.mem_store_byte(0xEE83F, 0x94);
    machine.mem_store_byte(0x00034, 0x50);
    machine.mem_store_byte(0x00035, 0xB9);
    machine.mem_store_byte(0x00036, 0x34);
    machine.mem_store_byte(0x00037, 0x51);
    machine.mem_store_byte(0x5CC90, 0xF4);
    machine.mem_store_byte(0x5CC91, 0x63);
    machine.mem_store_byte(0x5CC92, 0xF4);
    machine.mem_store_byte(0x5CC93, 0x68);
    machine.mem_store_byte(0x5CC94, 0xF4);
    machine.mem_store_byte(0x5CC95, 0x2E);
    machine.mem_store_byte(0x5CC96, 0xF4);
    machine.mem_store_byte(0x5CC97, 0x6B);
    machine.mem_store_byte(0x5CC98, 0xF4);
    machine.mem_store_byte(0x5CC99, 0x41);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007567);
    EXPECT_EQ(cpu.get_ebx(), 0xDF11ED5E);
    EXPECT_EQ(cpu.get_ecx(), 0x0B1C35E7);
    EXPECT_EQ(cpu.get_edx(), 0xB44CFE46);
    EXPECT_EQ(cpu.get_esi(), 0x0C39B0F7);
    EXPECT_EQ(cpu.get_edi(), 0xFFDF3886);
    EXPECT_EQ(cpu.get_ebp(), 0x5DC41F3A);
    EXPECT_EQ(cpu.get_esp(), 0x0000AC22);
    EXPECT_EQ(cpu.get_cs(), 0x00005134);
    EXPECT_EQ(cpu.get_ds(), 0x00007C4B);
    EXPECT_EQ(cpu.get_es(), 0x000074A8);
    EXPECT_EQ(cpu.get_fs(), 0x000097DB);
    EXPECT_EQ(cpu.get_gs(), 0x0000C226);
    EXPECT_EQ(cpu.get_ss(), 0x00000969);
    EXPECT_EQ(cpu.get_eip(), 0x0000B951);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0096);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x142B6), 0x96);
    EXPECT_EQ(memory.load8(0x142B7), 0x00);
    EXPECT_EQ(memory.load8(0x142B4), 0x34);
    EXPECT_EQ(memory.load8(0x142B5), 0xE8);
    EXPECT_EQ(memory.load8(0x142B2), 0xE8);
    EXPECT_EQ(memory.load8(0x142B3), 0x64);
}

//
// btc dword [ss:ebp+C377h],4Ch
//
TEST_F(Test386, btc_dword_ss_ebp_C377h_4Ch_batch9)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFD8840EF);
    cpu.set_ebx(0xA3A05DE2);
    cpu.set_ecx(0x6CE52AFF);
    cpu.set_edx(0xC1EBB788);
    cpu.set_esi(0x23933AB1);
    cpu.set_edi(0x96F4E438);
    cpu.set_ebp(0x0000CEBC);
    cpu.set_esp(0x0000A27C);
    cpu.set_cs(0x0000D93A);
    cpu.set_ds(0x00006C5A);
    cpu.set_es(0x0000DCCA);
    cpu.set_fs(0x000060E0);
    cpu.set_gs(0x0000A82B);
    cpu.set_ss(0x0000E226);
    cpu.set_eip(0x0000C510);
    cpu.set_eflags(0xFFFC0C03);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE58B0, 0x66);
    machine.mem_store_byte(0xE58B1, 0x67);
    machine.mem_store_byte(0xE58B2, 0x0F);
    machine.mem_store_byte(0xE58B3, 0xBA);
    machine.mem_store_byte(0xE58B4, 0xBD);
    machine.mem_store_byte(0xE58B5, 0x77);
    machine.mem_store_byte(0xE58B6, 0xC3);
    machine.mem_store_byte(0xE58B7, 0x00);
    machine.mem_store_byte(0xE58B8, 0x00);
    machine.mem_store_byte(0xE58B9, 0x4C);
    machine.mem_store_byte(0xE58BA, 0xF4);
    machine.mem_store_byte(0xE58BB, 0xD3);
    machine.mem_store_byte(0xE58BC, 0x21);
    machine.mem_store_byte(0xE58BD, 0xD9);
    machine.mem_store_byte(0xE58BE, 0xCF);
    machine.mem_store_byte(0xE58BF, 0xD0);
    machine.mem_store_byte(0xE58C0, 0x6B);
    machine.mem_store_byte(0xE58C1, 0x06);
    machine.mem_store_byte(0xE58C2, 0xCD);
    machine.mem_store_byte(0xE58C3, 0xBA);
    machine.mem_store_byte(0xE58C4, 0x7F);
    machine.mem_store_byte(0xE58C5, 0x4F);
    machine.mem_store_byte(0xE58C6, 0xA2);
    machine.mem_store_byte(0xE58C7, 0x38);
    machine.mem_store_byte(0x00030, 0x4B);
    machine.mem_store_byte(0x00031, 0xC3);
    machine.mem_store_byte(0x00032, 0x14);
    machine.mem_store_byte(0x00033, 0xCF);
    machine.mem_store_byte(0xDB48A, 0xB1);
    machine.mem_store_byte(0xDB48B, 0xF4);
    machine.mem_store_byte(0xDB48C, 0x84);
    machine.mem_store_byte(0xDB48D, 0xF4);
    machine.mem_store_byte(0xDB48E, 0x4C);
    machine.mem_store_byte(0xDB48F, 0xF4);
    machine.mem_store_byte(0xDB490, 0x18);
    machine.mem_store_byte(0xDB491, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFD8840EF);
    EXPECT_EQ(cpu.get_ebx(), 0xA3A05DE2);
    EXPECT_EQ(cpu.get_ecx(), 0x6CE52AFF);
    EXPECT_EQ(cpu.get_edx(), 0xC1EBB788);
    EXPECT_EQ(cpu.get_esi(), 0x23933AB1);
    EXPECT_EQ(cpu.get_edi(), 0x96F4E438);
    EXPECT_EQ(cpu.get_ebp(), 0x0000CEBC);
    EXPECT_EQ(cpu.get_esp(), 0x0000A276);
    EXPECT_EQ(cpu.get_cs(), 0x0000CF14);
    EXPECT_EQ(cpu.get_ds(), 0x00006C5A);
    EXPECT_EQ(cpu.get_es(), 0x0000DCCA);
    EXPECT_EQ(cpu.get_fs(), 0x000060E0);
    EXPECT_EQ(cpu.get_gs(), 0x0000A82B);
    EXPECT_EQ(cpu.get_ss(), 0x0000E226);
    EXPECT_EQ(cpu.get_eip(), 0x0000C34C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C03);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEC4DA), 0x03);
    EXPECT_EQ(memory.load8(0xEC4DB), 0x0C);
    EXPECT_EQ(memory.load8(0xEC4D8), 0x3A);
    EXPECT_EQ(memory.load8(0xEC4D9), 0xD9);
    EXPECT_EQ(memory.load8(0xEC4D6), 0x10);
    EXPECT_EQ(memory.load8(0xEC4D7), 0xC5);
}

//
// btc word [ss:ebp+C377h],4Ch
//
TEST_F(Test386, btc_word_ss_ebp_C377h_4Ch_batch9)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFD8840EF);
    cpu.set_ebx(0xA3A05DE2);
    cpu.set_ecx(0x6CE52AFF);
    cpu.set_edx(0xC1EBB788);
    cpu.set_esi(0x23933AB1);
    cpu.set_edi(0x96F4E438);
    cpu.set_ebp(0x0000CEBC);
    cpu.set_esp(0x0000A27C);
    cpu.set_cs(0x0000D93A);
    cpu.set_ds(0x00006C5A);
    cpu.set_es(0x0000DCCA);
    cpu.set_fs(0x000060E0);
    cpu.set_gs(0x0000A82B);
    cpu.set_ss(0x0000E226);
    cpu.set_eip(0x0000C510);
    cpu.set_eflags(0xFFFC0C03);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE58B0, 0x67);
    machine.mem_store_byte(0xE58B1, 0x0F);
    machine.mem_store_byte(0xE58B2, 0xBA);
    machine.mem_store_byte(0xE58B3, 0xBD);
    machine.mem_store_byte(0xE58B4, 0x77);
    machine.mem_store_byte(0xE58B5, 0xC3);
    machine.mem_store_byte(0xE58B6, 0x00);
    machine.mem_store_byte(0xE58B7, 0x00);
    machine.mem_store_byte(0xE58B8, 0x4C);
    machine.mem_store_byte(0xE58B9, 0xF4);
    machine.mem_store_byte(0xE58BA, 0x78);
    machine.mem_store_byte(0xE58BB, 0xD3);
    machine.mem_store_byte(0xE58BC, 0x21);
    machine.mem_store_byte(0xE58BD, 0xD9);
    machine.mem_store_byte(0xE58BE, 0xCF);
    machine.mem_store_byte(0xE58BF, 0xD0);
    machine.mem_store_byte(0xE58C0, 0x6B);
    machine.mem_store_byte(0xE58C1, 0x06);
    machine.mem_store_byte(0xE58C2, 0xCD);
    machine.mem_store_byte(0xE58C3, 0xBA);
    machine.mem_store_byte(0xE58C4, 0x7F);
    machine.mem_store_byte(0xE58C5, 0x4F);
    machine.mem_store_byte(0xE58C6, 0xA2);
    machine.mem_store_byte(0xE58C7, 0x38);
    machine.mem_store_byte(0x00030, 0x4B);
    machine.mem_store_byte(0x00031, 0xC3);
    machine.mem_store_byte(0x00032, 0x14);
    machine.mem_store_byte(0x00033, 0xCF);
    machine.mem_store_byte(0xDB48A, 0xB1);
    machine.mem_store_byte(0xDB48B, 0xF4);
    machine.mem_store_byte(0xDB48C, 0x84);
    machine.mem_store_byte(0xDB48D, 0xF4);
    machine.mem_store_byte(0xDB48E, 0x4C);
    machine.mem_store_byte(0xDB48F, 0xF4);
    machine.mem_store_byte(0xDB490, 0x18);
    machine.mem_store_byte(0xDB491, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFD8840EF);
    EXPECT_EQ(cpu.get_ebx(), 0xA3A05DE2);
    EXPECT_EQ(cpu.get_ecx(), 0x6CE52AFF);
    EXPECT_EQ(cpu.get_edx(), 0xC1EBB788);
    EXPECT_EQ(cpu.get_esi(), 0x23933AB1);
    EXPECT_EQ(cpu.get_edi(), 0x96F4E438);
    EXPECT_EQ(cpu.get_ebp(), 0x0000CEBC);
    EXPECT_EQ(cpu.get_esp(), 0x0000A276);
    EXPECT_EQ(cpu.get_cs(), 0x0000CF14);
    EXPECT_EQ(cpu.get_ds(), 0x00006C5A);
    EXPECT_EQ(cpu.get_es(), 0x0000DCCA);
    EXPECT_EQ(cpu.get_fs(), 0x000060E0);
    EXPECT_EQ(cpu.get_gs(), 0x0000A82B);
    EXPECT_EQ(cpu.get_ss(), 0x0000E226);
    EXPECT_EQ(cpu.get_eip(), 0x0000C34C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C03);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEC4DA), 0x03);
    EXPECT_EQ(memory.load8(0xEC4DB), 0x0C);
    EXPECT_EQ(memory.load8(0xEC4D8), 0x3A);
    EXPECT_EQ(memory.load8(0xEC4D9), 0xD9);
    EXPECT_EQ(memory.load8(0xEC4D6), 0x10);
    EXPECT_EQ(memory.load8(0xEC4D7), 0xC5);
}

//
// ror byte [ds:eax],50h
//
TEST_F(Test386, ror_byte_ds_eax_50h_batch9)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00009B7D);
    cpu.set_ebx(0xDA835818);
    cpu.set_ecx(0x34D46BAB);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x21619C47);
    cpu.set_edi(0x0E744C03);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x0000DCF0);
    cpu.set_cs(0x000018C9);
    cpu.set_ds(0x0000FA98);
    cpu.set_es(0x0000AACD);
    cpu.set_fs(0x00008367);
    cpu.set_gs(0x00002C0C);
    cpu.set_ss(0x00000990);
    cpu.set_eip(0x00006970);
    cpu.set_eflags(0xFFFC00D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1F600, 0x67);
    machine.mem_store_byte(0x1F601, 0xC0);
    machine.mem_store_byte(0x1F602, 0x08);
    machine.mem_store_byte(0x1F603, 0x50);
    machine.mem_store_byte(0x1F604, 0xF4);
    machine.mem_store_byte(0x1F605, 0x53);
    machine.mem_store_byte(0x1F606, 0x88);
    machine.mem_store_byte(0x1F607, 0x5E);
    machine.mem_store_byte(0x1F608, 0x0E);
    machine.mem_store_byte(0x1F609, 0xBC);
    machine.mem_store_byte(0x1F60A, 0xD2);
    machine.mem_store_byte(0x1F60B, 0x41);
    machine.mem_store_byte(0x1044FD, 0xA8);
    machine.mem_store_byte(0x1F60C, 0x89);
    machine.mem_store_byte(0x1F60D, 0x74);
    machine.mem_store_byte(0x1F60E, 0x65);
    machine.mem_store_byte(0x1F60F, 0x30);
    machine.mem_store_byte(0x1F610, 0xDD);
    machine.mem_store_byte(0x1F611, 0x92);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00009B7D);
    EXPECT_EQ(cpu.get_ebx(), 0xDA835818);
    EXPECT_EQ(cpu.get_ecx(), 0x34D46BAB);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x21619C47);
    EXPECT_EQ(cpu.get_edi(), 0x0E744C03);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000DCF0);
    EXPECT_EQ(cpu.get_cs(), 0x000018C9);
    EXPECT_EQ(cpu.get_ds(), 0x0000FA98);
    EXPECT_EQ(cpu.get_es(), 0x0000AACD);
    EXPECT_EQ(cpu.get_fs(), 0x00008367);
    EXPECT_EQ(cpu.get_gs(), 0x00002C0C);
    EXPECT_EQ(cpu.get_ss(), 0x00000990);
    EXPECT_EQ(cpu.get_eip(), 0x00006975);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08D3);

    // Final RAM entries
}
