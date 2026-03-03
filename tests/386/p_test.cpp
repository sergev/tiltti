#include "test386.h"

//
// pop bx
//
TEST_F(Test386, pop_bx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x027B7E2A);
    cpu.set_ebx(0xB3B762E5);
    cpu.set_ecx(0xFB9C6577);
    cpu.set_edx(0xFFEFFFFF);
    cpu.set_esi(0x43E574BA);
    cpu.set_edi(0x00000050);
    cpu.set_ebp(0xD48BCE7A);
    cpu.set_esp(0x0000D7EA);
    cpu.set_cs(0x0000441C);
    cpu.set_ds(0x0000D5B9);
    cpu.set_es(0x0000AB49);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x0000191E);
    cpu.set_ss(0x0000F728);
    cpu.set_eip(0x0000B988);
    cpu.set_eflags(0xFFFC0886);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4FB48, 0x5B);
    machine.mem_store_byte(0x4FB49, 0xF4);
    machine.mem_store_byte(0x4FB4A, 0x9B);
    machine.mem_store_byte(0x4FB4B, 0xF9);
    machine.mem_store_byte(0x4FB4C, 0x1A);
    machine.mem_store_byte(0x4FB4D, 0xED);
    machine.mem_store_byte(0x4FB4E, 0xBB);
    machine.mem_store_byte(0x4FB4F, 0x52);
    machine.mem_store_byte(0x104A6A, 0xD2);
    machine.mem_store_byte(0x104A6B, 0xEA);
    machine.mem_store_byte(0x4FB50, 0x03);
    machine.mem_store_byte(0x4FB51, 0x51);
    machine.mem_store_byte(0x4FB52, 0xD8);
    machine.mem_store_byte(0x4FB53, 0x8E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x027B7E2A);
    EXPECT_EQ(cpu.get_ebx(), 0xB3B7EAD2);
    EXPECT_EQ(cpu.get_ecx(), 0xFB9C6577);
    EXPECT_EQ(cpu.get_edx(), 0xFFEFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0x43E574BA);
    EXPECT_EQ(cpu.get_edi(), 0x00000050);
    EXPECT_EQ(cpu.get_ebp(), 0xD48BCE7A);
    EXPECT_EQ(cpu.get_esp(), 0x0000D7EC);
    EXPECT_EQ(cpu.get_cs(), 0x0000441C);
    EXPECT_EQ(cpu.get_ds(), 0x0000D5B9);
    EXPECT_EQ(cpu.get_es(), 0x0000AB49);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x0000191E);
    EXPECT_EQ(cpu.get_ss(), 0x0000F728);
    EXPECT_EQ(cpu.get_eip(), 0x0000B98A);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0886);

    // Final RAM entries
}

//
// pop eax
//
TEST_F(Test386, pop_eax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDFC745B1);
    cpu.set_ebx(0xE8DD22C6);
    cpu.set_ecx(0xF3277557);
    cpu.set_edx(0xFFF9CABF);
    cpu.set_esi(0x00000101);
    cpu.set_edi(0x7F7F7F7F);
    cpu.set_ebp(0x16A8CB85);
    cpu.set_esp(0x00000800);
    cpu.set_cs(0x000000BF);
    cpu.set_ds(0x0000FBFA);
    cpu.set_es(0x00000010);
    cpu.set_fs(0x00000800);
    cpu.set_gs(0x00003060);
    cpu.set_ss(0x000019CB);
    cpu.set_eip(0x000073F8);
    cpu.set_eflags(0xFFFC08C3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x07FE8, 0x66);
    machine.mem_store_byte(0x07FE9, 0x58);
    machine.mem_store_byte(0x07FEA, 0xF4);
    machine.mem_store_byte(0x07FEB, 0x00);
    machine.mem_store_byte(0x07FEC, 0x00);
    machine.mem_store_byte(0x07FED, 0x00);
    machine.mem_store_byte(0x07FEE, 0x00);
    machine.mem_store_byte(0x07FEF, 0x00);
    machine.mem_store_byte(0x07FF0, 0x00);
    machine.mem_store_byte(0x07FF1, 0x00);
    machine.mem_store_byte(0x1A4B0, 0x00);
    machine.mem_store_byte(0x1A4B1, 0x00);
    machine.mem_store_byte(0x1A4B2, 0x00);
    machine.mem_store_byte(0x1A4B3, 0x00);
    machine.mem_store_byte(0x07FF2, 0x00);
    machine.mem_store_byte(0x07FF3, 0x00);
    machine.mem_store_byte(0x07FF4, 0x00);
    machine.mem_store_byte(0x07FF5, 0x00);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0xE8DD22C6);
    EXPECT_EQ(cpu.get_ecx(), 0xF3277557);
    EXPECT_EQ(cpu.get_edx(), 0xFFF9CABF);
    EXPECT_EQ(cpu.get_esi(), 0x00000101);
    EXPECT_EQ(cpu.get_edi(), 0x7F7F7F7F);
    EXPECT_EQ(cpu.get_ebp(), 0x16A8CB85);
    EXPECT_EQ(cpu.get_esp(), 0x00000804);
    EXPECT_EQ(cpu.get_cs(), 0x000000BF);
    EXPECT_EQ(cpu.get_ds(), 0x0000FBFA);
    EXPECT_EQ(cpu.get_es(), 0x00000010);
    EXPECT_EQ(cpu.get_fs(), 0x00000800);
    EXPECT_EQ(cpu.get_gs(), 0x00003060);
    EXPECT_EQ(cpu.get_ss(), 0x000019CB);
    EXPECT_EQ(cpu.get_eip(), 0x000073FB);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C3);

    // Final RAM entries
}

//
// pop fs
//
TEST_F(Test386, pop_fs)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0052936A);
    cpu.set_ebx(0x26AB1150);
    cpu.set_ecx(0x2F444FD3);
    cpu.set_edx(0xFFFFFFFF);
    cpu.set_esi(0x0A7503A1);
    cpu.set_edi(0xA1897E64);
    cpu.set_ebp(0x07617D2D);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x000009CA);
    cpu.set_ds(0x000000AF);
    cpu.set_es(0x00004EB6);
    cpu.set_fs(0x00000006);
    cpu.set_gs(0x00005D89);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00000948);
    cpu.set_eflags(0xFFFC0086);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0A5E8, 0x0F);
    machine.mem_store_byte(0x0A5E9, 0xA1);
    machine.mem_store_byte(0x0A5EA, 0xF4);
    machine.mem_store_byte(0x0A5EB, 0x7A);
    machine.mem_store_byte(0x0A5EC, 0x4A);
    machine.mem_store_byte(0x0A5ED, 0xE3);
    machine.mem_store_byte(0x0A5EE, 0x55);
    machine.mem_store_byte(0x0A5EF, 0x70);
    machine.mem_store_byte(0x0A5F0, 0x65);
    machine.mem_store_byte(0x0A5F1, 0x1A);
    machine.mem_store_byte(0x0FFFE, 0x21);
    machine.mem_store_byte(0x0FFFF, 0x49);
    machine.mem_store_byte(0x0A5F2, 0x55);
    machine.mem_store_byte(0x0A5F3, 0x78);
    machine.mem_store_byte(0x0A5F4, 0x8E);
    machine.mem_store_byte(0x0A5F5, 0x81);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0052936A);
    EXPECT_EQ(cpu.get_ebx(), 0x26AB1150);
    EXPECT_EQ(cpu.get_ecx(), 0x2F444FD3);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0x0A7503A1);
    EXPECT_EQ(cpu.get_edi(), 0xA1897E64);
    EXPECT_EQ(cpu.get_ebp(), 0x07617D2D);
    EXPECT_EQ(cpu.get_esp(), 0x00000000);
    EXPECT_EQ(cpu.get_cs(), 0x000009CA);
    EXPECT_EQ(cpu.get_ds(), 0x000000AF);
    EXPECT_EQ(cpu.get_es(), 0x00004EB6);
    EXPECT_EQ(cpu.get_fs(), 0x00004921);
    EXPECT_EQ(cpu.get_gs(), 0x00005D89);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000094B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0086);

    // Final RAM entries
}

//
// popad
//
TEST_F(Test386, popad)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x9192DBB2);
    cpu.set_ebx(0x99C59D4B);
    cpu.set_ecx(0x4A3B1694);
    cpu.set_edx(0x5E456BE5);
    cpu.set_esi(0xFEC2D97F);
    cpu.set_edi(0x176802DB);
    cpu.set_ebp(0x7839DC30);
    cpu.set_esp(0x00005E90);
    cpu.set_cs(0x0000F2AA);
    cpu.set_ds(0x0000FBD5);
    cpu.set_es(0x00004000);
    cpu.set_fs(0x0000CEDD);
    cpu.set_gs(0x0000005F);
    cpu.set_ss(0x000077BF);
    cpu.set_eip(0x0000A488);
    cpu.set_eflags(0xFFFC0C86);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFCF28, 0x66);
    machine.mem_store_byte(0xFCF29, 0x61);
    machine.mem_store_byte(0xFCF2A, 0xF4);
    machine.mem_store_byte(0xFCF2B, 0x82);
    machine.mem_store_byte(0xFCF2C, 0x0A);
    machine.mem_store_byte(0xFCF2D, 0xBE);
    machine.mem_store_byte(0xFCF2E, 0x51);
    machine.mem_store_byte(0xFCF2F, 0x9C);
    machine.mem_store_byte(0xFCF30, 0x37);
    machine.mem_store_byte(0xFCF31, 0x02);
    machine.mem_store_byte(0x7DA80, 0xEA);
    machine.mem_store_byte(0x7DA81, 0x49);
    machine.mem_store_byte(0x7DA82, 0x91);
    machine.mem_store_byte(0x7DA83, 0xFA);
    machine.mem_store_byte(0x7DA84, 0x81);
    machine.mem_store_byte(0x7DA85, 0xE1);
    machine.mem_store_byte(0x7DA86, 0xC6);
    machine.mem_store_byte(0x7DA87, 0xA5);
    machine.mem_store_byte(0x7DA88, 0xB6);
    machine.mem_store_byte(0x7DA89, 0xB7);
    machine.mem_store_byte(0x7DA8A, 0x86);
    machine.mem_store_byte(0x7DA8B, 0x02);
    machine.mem_store_byte(0x7DA8C, 0x18);
    machine.mem_store_byte(0x7DA8D, 0x6B);
    machine.mem_store_byte(0x7DA8E, 0x04);
    machine.mem_store_byte(0x7DA8F, 0x5A);
    machine.mem_store_byte(0x7DA90, 0xE4);
    machine.mem_store_byte(0x7DA91, 0x22);
    machine.mem_store_byte(0x7DA92, 0xBF);
    machine.mem_store_byte(0x7DA93, 0xA3);
    machine.mem_store_byte(0x7DA94, 0xBE);
    machine.mem_store_byte(0x7DA95, 0xBB);
    machine.mem_store_byte(0x7DA96, 0x88);
    machine.mem_store_byte(0x7DA97, 0x56);
    machine.mem_store_byte(0x7DA98, 0x41);
    machine.mem_store_byte(0x7DA99, 0xE0);
    machine.mem_store_byte(0x7DA9A, 0x10);
    machine.mem_store_byte(0x7DA9B, 0x37);
    machine.mem_store_byte(0x7DA9C, 0xF3);
    machine.mem_store_byte(0x7DA9D, 0xEB);
    machine.mem_store_byte(0x7DA9E, 0xB6);
    machine.mem_store_byte(0x7DA9F, 0x7C);
    machine.mem_store_byte(0xFCF32, 0xF9);
    machine.mem_store_byte(0xFCF33, 0x56);
    machine.mem_store_byte(0xFCF34, 0x5F);
    machine.mem_store_byte(0xFCF35, 0xB5);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7CB6EBF3);
    EXPECT_EQ(cpu.get_ebx(), 0xA3BF22E4);
    EXPECT_EQ(cpu.get_ecx(), 0x3710E041);
    EXPECT_EQ(cpu.get_edx(), 0x5688BBBE);
    EXPECT_EQ(cpu.get_esi(), 0xA5C6E181);
    EXPECT_EQ(cpu.get_edi(), 0xFA9149EA);
    EXPECT_EQ(cpu.get_ebp(), 0x0286B7B6);
    EXPECT_EQ(cpu.get_esp(), 0x5A045EB0);
    EXPECT_EQ(cpu.get_cs(), 0x0000F2AA);
    EXPECT_EQ(cpu.get_ds(), 0x0000FBD5);
    EXPECT_EQ(cpu.get_es(), 0x00004000);
    EXPECT_EQ(cpu.get_fs(), 0x0000CEDD);
    EXPECT_EQ(cpu.get_gs(), 0x0000005F);
    EXPECT_EQ(cpu.get_ss(), 0x000077BF);
    EXPECT_EQ(cpu.get_eip(), 0x0000A48B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C86);

    // Final RAM entries
}

//
// pop dword [ds:esi-55h]
//
TEST_F(Test386, pop_dword_ds_esi_55h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00002001);
    cpu.set_ebx(0xBC9365A9);
    cpu.set_ecx(0x3B00EB33);
    cpu.set_edx(0xFFFFFFF7);
    cpu.set_esi(0x00007D85);
    cpu.set_edi(0xF0D738EA);
    cpu.set_ebp(0x00000400);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000B81F);
    cpu.set_ds(0x000024CF);
    cpu.set_es(0x0000DDD0);
    cpu.set_fs(0x000069EC);
    cpu.set_gs(0x0000FF0D);
    cpu.set_ss(0x00004D11);
    cpu.set_eip(0x00002C60);
    cpu.set_eflags(0xFFFC0C97);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBAE50, 0x67);
    machine.mem_store_byte(0xBAE51, 0x66);
    machine.mem_store_byte(0xBAE52, 0x8F);
    machine.mem_store_byte(0xBAE53, 0x46);
    machine.mem_store_byte(0xBAE54, 0xAB);
    machine.mem_store_byte(0xBAE55, 0xF4);
    machine.mem_store_byte(0xBAE56, 0xA1);
    machine.mem_store_byte(0xBAE57, 0xBB);
    machine.mem_store_byte(0xBAE58, 0x8D);
    machine.mem_store_byte(0xBAE59, 0xE9);
    machine.mem_store_byte(0xBAE5A, 0xB6);
    machine.mem_store_byte(0xBAE5B, 0x77);
    machine.mem_store_byte(0x4D118, 0xDD);
    machine.mem_store_byte(0x4D119, 0x01);
    machine.mem_store_byte(0x4D11A, 0x80);
    machine.mem_store_byte(0x4D11B, 0xF5);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00002001);
    EXPECT_EQ(cpu.get_ebx(), 0xBC9365A9);
    EXPECT_EQ(cpu.get_ecx(), 0x3B00EB33);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFF7);
    EXPECT_EQ(cpu.get_esi(), 0x00007D85);
    EXPECT_EQ(cpu.get_edi(), 0xF0D738EA);
    EXPECT_EQ(cpu.get_ebp(), 0x00000400);
    EXPECT_EQ(cpu.get_esp(), 0x0000000C);
    EXPECT_EQ(cpu.get_cs(), 0x0000B81F);
    EXPECT_EQ(cpu.get_ds(), 0x000024CF);
    EXPECT_EQ(cpu.get_es(), 0x0000DDD0);
    EXPECT_EQ(cpu.get_fs(), 0x000069EC);
    EXPECT_EQ(cpu.get_gs(), 0x0000FF0D);
    EXPECT_EQ(cpu.get_ss(), 0x00004D11);
    EXPECT_EQ(cpu.get_eip(), 0x00002C66);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C97);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2CA20), 0xDD);
    EXPECT_EQ(memory.load8(0x2CA21), 0x01);
    EXPECT_EQ(memory.load8(0x2CA22), 0x80);
    EXPECT_EQ(memory.load8(0x2CA23), 0xF5);
}

//
// popfd
//
TEST_F(Test386, popfd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007FFF);
    cpu.set_ebx(0xAFB4C279);
    cpu.set_ecx(0x04AB076F);
    cpu.set_edx(0x091EE2A8);
    cpu.set_esi(0x05B5A01D);
    cpu.set_edi(0xCE167BB7);
    cpu.set_ebp(0xAC8E4376);
    cpu.set_esp(0x00007A48);
    cpu.set_cs(0x00006B44);
    cpu.set_ds(0x0000FC56);
    cpu.set_es(0x00000001);
    cpu.set_fs(0x0000FE36);
    cpu.set_gs(0x000003E9);
    cpu.set_ss(0x00004E66);
    cpu.set_eip(0x0000C388);
    cpu.set_eflags(0xFFFC0C43);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x777C8, 0x66);
    machine.mem_store_byte(0x777C9, 0x9D);
    machine.mem_store_byte(0x777CA, 0xF4);
    machine.mem_store_byte(0x777CB, 0x6A);
    machine.mem_store_byte(0x777CC, 0xE8);
    machine.mem_store_byte(0x777CD, 0x5B);
    machine.mem_store_byte(0x777CE, 0x46);
    machine.mem_store_byte(0x777CF, 0x6F);
    machine.mem_store_byte(0x777D0, 0x50);
    machine.mem_store_byte(0x777D1, 0x97);
    machine.mem_store_byte(0x777D2, 0xEE);
    machine.mem_store_byte(0x777D3, 0xB2);
    machine.mem_store_byte(0x560A8, 0x80);
    machine.mem_store_byte(0x560A9, 0x02);
    machine.mem_store_byte(0x560AA, 0x00);
    machine.mem_store_byte(0x560AB, 0x00);
    machine.mem_store_byte(0x777D4, 0xAA);
    machine.mem_store_byte(0x777D5, 0xA8);
    machine.mem_store_byte(0x777D6, 0x9B);
    machine.mem_store_byte(0x777D7, 0xAD);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebx(), 0xAFB4C279);
    EXPECT_EQ(cpu.get_ecx(), 0x04AB076F);
    EXPECT_EQ(cpu.get_edx(), 0x091EE2A8);
    EXPECT_EQ(cpu.get_esi(), 0x05B5A01D);
    EXPECT_EQ(cpu.get_edi(), 0xCE167BB7);
    EXPECT_EQ(cpu.get_ebp(), 0xAC8E4376);
    EXPECT_EQ(cpu.get_esp(), 0x00007A4C);
    EXPECT_EQ(cpu.get_cs(), 0x00006B44);
    EXPECT_EQ(cpu.get_ds(), 0x0000FC56);
    EXPECT_EQ(cpu.get_es(), 0x00000001);
    EXPECT_EQ(cpu.get_fs(), 0x0000FE36);
    EXPECT_EQ(cpu.get_gs(), 0x000003E9);
    EXPECT_EQ(cpu.get_ss(), 0x00004E66);
    EXPECT_EQ(cpu.get_eip(), 0x0000C38B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0282);

    // Final RAM entries
}

//
// push 3048A49Eh
//
TEST_F(Test386, push_3048A49Eh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7BE8F380);
    cpu.set_ebx(0xB053727A);
    cpu.set_ecx(0xF5328B51);
    cpu.set_edx(0x0450CF7B);
    cpu.set_esi(0xA7BF1CF9);
    cpu.set_edi(0x856F5A3B);
    cpu.set_ebp(0x0ED28E21);
    cpu.set_esp(0x0000896E);
    cpu.set_cs(0x0000D46F);
    cpu.set_ds(0x00000001);
    cpu.set_es(0x00003542);
    cpu.set_fs(0x0000A437);
    cpu.set_gs(0x0000008F);
    cpu.set_ss(0x00004232);
    cpu.set_eip(0x00001CF8);
    cpu.set_eflags(0xFFFC04D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD63E8, 0x66);
    machine.mem_store_byte(0xD63E9, 0x68);
    machine.mem_store_byte(0xD63EA, 0x9E);
    machine.mem_store_byte(0xD63EB, 0xA4);
    machine.mem_store_byte(0xD63EC, 0x48);
    machine.mem_store_byte(0xD63ED, 0x30);
    machine.mem_store_byte(0xD63EE, 0xF4);
    machine.mem_store_byte(0xD63EF, 0x48);
    machine.mem_store_byte(0xD63F0, 0xB0);
    machine.mem_store_byte(0xD63F1, 0x3E);
    machine.mem_store_byte(0xD63F2, 0xFC);
    machine.mem_store_byte(0xD63F3, 0x58);
    machine.mem_store_byte(0xD63F4, 0xEA);
    machine.mem_store_byte(0xD63F5, 0x3E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7BE8F380);
    EXPECT_EQ(cpu.get_ebx(), 0xB053727A);
    EXPECT_EQ(cpu.get_ecx(), 0xF5328B51);
    EXPECT_EQ(cpu.get_edx(), 0x0450CF7B);
    EXPECT_EQ(cpu.get_esi(), 0xA7BF1CF9);
    EXPECT_EQ(cpu.get_edi(), 0x856F5A3B);
    EXPECT_EQ(cpu.get_ebp(), 0x0ED28E21);
    EXPECT_EQ(cpu.get_esp(), 0x0000896A);
    EXPECT_EQ(cpu.get_cs(), 0x0000D46F);
    EXPECT_EQ(cpu.get_ds(), 0x00000001);
    EXPECT_EQ(cpu.get_es(), 0x00003542);
    EXPECT_EQ(cpu.get_fs(), 0x0000A437);
    EXPECT_EQ(cpu.get_gs(), 0x0000008F);
    EXPECT_EQ(cpu.get_ss(), 0x00004232);
    EXPECT_EQ(cpu.get_eip(), 0x00001CFF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04D3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4AC8C), 0x48);
    EXPECT_EQ(memory.load8(0x4AC8D), 0x30);
    EXPECT_EQ(memory.load8(0x4AC8A), 0x9E);
    EXPECT_EQ(memory.load8(0x4AC8B), 0xA4);
}

//
// push eax
//
TEST_F(Test386, push_eax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0CD27BB4);
    cpu.set_ebx(0x00000800);
    cpu.set_ecx(0xE50E528A);
    cpu.set_edx(0xFFFFFFF0);
    cpu.set_esi(0x5164E896);
    cpu.set_edi(0x082C22DE);
    cpu.set_ebp(0x588B341D);
    cpu.set_esp(0x00001878);
    cpu.set_cs(0x00000014);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x00007C4F);
    cpu.set_fs(0x00000A2D);
    cpu.set_gs(0x0000C449);
    cpu.set_ss(0x0000FFFE);
    cpu.set_eip(0x00001020);
    cpu.set_eflags(0xFFFC0842);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x01160, 0x66);
    machine.mem_store_byte(0x01161, 0x50);
    machine.mem_store_byte(0x01162, 0xF4);
    machine.mem_store_byte(0x01163, 0x81);
    machine.mem_store_byte(0x01164, 0x9C);
    machine.mem_store_byte(0x01165, 0xC8);
    machine.mem_store_byte(0x01166, 0x3C);
    machine.mem_store_byte(0x01167, 0x0A);
    machine.mem_store_byte(0x01168, 0x5F);
    machine.mem_store_byte(0x01169, 0x9B);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0CD27BB4);
    EXPECT_EQ(cpu.get_ebx(), 0x00000800);
    EXPECT_EQ(cpu.get_ecx(), 0xE50E528A);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFF0);
    EXPECT_EQ(cpu.get_esi(), 0x5164E896);
    EXPECT_EQ(cpu.get_edi(), 0x082C22DE);
    EXPECT_EQ(cpu.get_ebp(), 0x588B341D);
    EXPECT_EQ(cpu.get_esp(), 0x00001874);
    EXPECT_EQ(cpu.get_cs(), 0x00000014);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x00007C4F);
    EXPECT_EQ(cpu.get_fs(), 0x00000A2D);
    EXPECT_EQ(cpu.get_gs(), 0x0000C449);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_eip(), 0x00001023);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0842);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x101854), 0xB4);
    EXPECT_EQ(memory.load8(0x101855), 0x7B);
    EXPECT_EQ(memory.load8(0x101856), 0xD2);
    EXPECT_EQ(memory.load8(0x101857), 0x0C);
}

//
// pushad
//
TEST_F(Test386, pushad)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x398A1180);
    cpu.set_ebx(0xB335C947);
    cpu.set_ecx(0x71A4D609);
    cpu.set_edx(0x71507D51);
    cpu.set_esi(0xABFC96AE);
    cpu.set_edi(0x3F8182A7);
    cpu.set_ebp(0x6BE9E0C7);
    cpu.set_esp(0x0000BF73);
    cpu.set_cs(0x0000BD3A);
    cpu.set_ds(0x00005BAF);
    cpu.set_es(0x0000B3CF);
    cpu.set_fs(0x00003360);
    cpu.set_gs(0x00002072);
    cpu.set_ss(0x0000F8FD);
    cpu.set_eip(0x0000CFB8);
    cpu.set_eflags(0xFFFC0446);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCA358, 0x66);
    machine.mem_store_byte(0xCA359, 0x60);
    machine.mem_store_byte(0xCA35A, 0xF4);
    machine.mem_store_byte(0xCA35B, 0x7C);
    machine.mem_store_byte(0xCA35C, 0x15);
    machine.mem_store_byte(0xCA35D, 0x70);
    machine.mem_store_byte(0xCA35E, 0x15);
    machine.mem_store_byte(0xCA35F, 0xAC);
    machine.mem_store_byte(0xCA360, 0xAD);
    machine.mem_store_byte(0xCA361, 0x36);
    machine.mem_store_byte(0xCA362, 0xF5);
    machine.mem_store_byte(0xCA363, 0x83);
    machine.mem_store_byte(0xCA364, 0x60);
    machine.mem_store_byte(0xCA365, 0x71);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x398A1180);
    EXPECT_EQ(cpu.get_ebx(), 0xB335C947);
    EXPECT_EQ(cpu.get_ecx(), 0x71A4D609);
    EXPECT_EQ(cpu.get_edx(), 0x71507D51);
    EXPECT_EQ(cpu.get_esi(), 0xABFC96AE);
    EXPECT_EQ(cpu.get_edi(), 0x3F8182A7);
    EXPECT_EQ(cpu.get_ebp(), 0x6BE9E0C7);
    EXPECT_EQ(cpu.get_esp(), 0x0000BF53);
    EXPECT_EQ(cpu.get_cs(), 0x0000BD3A);
    EXPECT_EQ(cpu.get_ds(), 0x00005BAF);
    EXPECT_EQ(cpu.get_es(), 0x0000B3CF);
    EXPECT_EQ(cpu.get_fs(), 0x00003360);
    EXPECT_EQ(cpu.get_gs(), 0x00002072);
    EXPECT_EQ(cpu.get_ss(), 0x0000F8FD);
    EXPECT_EQ(cpu.get_eip(), 0x0000CFBB);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x104F24), 0x82);
    EXPECT_EQ(memory.load8(0x104F25), 0x81);
    EXPECT_EQ(memory.load8(0x104F26), 0x3F);
    EXPECT_EQ(memory.load8(0x104F23), 0xA7);
    EXPECT_EQ(memory.load8(0x104F28), 0x96);
    EXPECT_EQ(memory.load8(0x104F29), 0xFC);
    EXPECT_EQ(memory.load8(0x104F2A), 0xAB);
    EXPECT_EQ(memory.load8(0x104F27), 0xAE);
    EXPECT_EQ(memory.load8(0x104F2C), 0xE0);
    EXPECT_EQ(memory.load8(0x104F2D), 0xE9);
    EXPECT_EQ(memory.load8(0x104F2E), 0x6B);
    EXPECT_EQ(memory.load8(0x104F2B), 0xC7);
    EXPECT_EQ(memory.load8(0x104F30), 0xBF);
    EXPECT_EQ(memory.load8(0x104F31), 0x00);
    EXPECT_EQ(memory.load8(0x104F32), 0x00);
    EXPECT_EQ(memory.load8(0x104F2F), 0x73);
    EXPECT_EQ(memory.load8(0x104F34), 0xC9);
    EXPECT_EQ(memory.load8(0x104F35), 0x35);
    EXPECT_EQ(memory.load8(0x104F36), 0xB3);
    EXPECT_EQ(memory.load8(0x104F33), 0x47);
    EXPECT_EQ(memory.load8(0x104F38), 0x7D);
    EXPECT_EQ(memory.load8(0x104F39), 0x50);
    EXPECT_EQ(memory.load8(0x104F3A), 0x71);
    EXPECT_EQ(memory.load8(0x104F37), 0x51);
    EXPECT_EQ(memory.load8(0x104F3C), 0xD6);
    EXPECT_EQ(memory.load8(0x104F3D), 0xA4);
    EXPECT_EQ(memory.load8(0x104F3E), 0x71);
    EXPECT_EQ(memory.load8(0x104F3B), 0x09);
    EXPECT_EQ(memory.load8(0x104F40), 0x11);
    EXPECT_EQ(memory.load8(0x104F41), 0x8A);
    EXPECT_EQ(memory.load8(0x104F42), 0x39);
    EXPECT_EQ(memory.load8(0x104F3F), 0x80);
}

//
// push esp
//
TEST_F(Test386, push_esp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x566AF113);
    cpu.set_ebx(0x40478BFD);
    cpu.set_ecx(0xFC7B4F7E);
    cpu.set_edx(0xFFFFFF8F);
    cpu.set_esi(0x025F59A1);
    cpu.set_edi(0x4B88A292);
    cpu.set_ebp(0x2FF45484);
    cpu.set_esp(0x0000BCE8);
    cpu.set_cs(0x0000FDB5);
    cpu.set_ds(0x0000007F);
    cpu.set_es(0x000003A6);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x000065FB);
    cpu.set_ss(0x00007914);
    cpu.set_eip(0x00000D38);
    cpu.set_eflags(0xFFFC0CC7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFE888, 0x66);
    machine.mem_store_byte(0xFE889, 0x54);
    machine.mem_store_byte(0xFE88A, 0xF4);
    machine.mem_store_byte(0xFE88B, 0x21);
    machine.mem_store_byte(0xFE88C, 0x0A);
    machine.mem_store_byte(0xFE88D, 0x19);
    machine.mem_store_byte(0xFE88E, 0x92);
    machine.mem_store_byte(0xFE88F, 0xA5);
    machine.mem_store_byte(0xFE890, 0xF9);
    machine.mem_store_byte(0xFE891, 0x76);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x566AF113);
    EXPECT_EQ(cpu.get_ebx(), 0x40478BFD);
    EXPECT_EQ(cpu.get_ecx(), 0xFC7B4F7E);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFF8F);
    EXPECT_EQ(cpu.get_esi(), 0x025F59A1);
    EXPECT_EQ(cpu.get_edi(), 0x4B88A292);
    EXPECT_EQ(cpu.get_ebp(), 0x2FF45484);
    EXPECT_EQ(cpu.get_esp(), 0x0000BCE4);
    EXPECT_EQ(cpu.get_cs(), 0x0000FDB5);
    EXPECT_EQ(cpu.get_ds(), 0x0000007F);
    EXPECT_EQ(cpu.get_es(), 0x000003A6);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x000065FB);
    EXPECT_EQ(cpu.get_ss(), 0x00007914);
    EXPECT_EQ(cpu.get_eip(), 0x00000D3B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CC7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x84E24), 0xE8);
    EXPECT_EQ(memory.load8(0x84E25), 0xBC);
    EXPECT_EQ(memory.load8(0x84E26), 0x00);
    EXPECT_EQ(memory.load8(0x84E27), 0x00);
}

//
// pushfd
//
TEST_F(Test386, pushfd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xB225FB42);
    cpu.set_ebx(0x5400272E);
    cpu.set_ecx(0x00DD864D);
    cpu.set_edx(0x099EA9BD);
    cpu.set_esi(0x96BB7BA0);
    cpu.set_edi(0xA0AC6D2C);
    cpu.set_ebp(0x8EB93E3F);
    cpu.set_esp(0x0000B4E7);
    cpu.set_cs(0x00000001);
    cpu.set_ds(0x0000C294);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00000100);
    cpu.set_gs(0x0000FF88);
    cpu.set_ss(0x0000B836);
    cpu.set_eip(0x0000D970);
    cpu.set_eflags(0xFFFC0493);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0D980, 0x66);
    machine.mem_store_byte(0x0D981, 0x9C);
    machine.mem_store_byte(0x0D982, 0xF4);
    machine.mem_store_byte(0x0D983, 0xC6);
    machine.mem_store_byte(0x0D984, 0xB1);
    machine.mem_store_byte(0x0D985, 0xE1);
    machine.mem_store_byte(0x0D986, 0x1D);
    machine.mem_store_byte(0x0D987, 0xAE);
    machine.mem_store_byte(0x0D988, 0xFE);
    machine.mem_store_byte(0x0D989, 0x54);
    machine.mem_store_byte(0x0D98A, 0x96);
    machine.mem_store_byte(0x0D98B, 0xB8);
    machine.mem_store_byte(0x0D98C, 0xC8);
    machine.mem_store_byte(0x0D98D, 0x60);
    machine.mem_store_byte(0x0D98E, 0x7E);
    machine.mem_store_byte(0x0D98F, 0x05);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xB225FB42);
    EXPECT_EQ(cpu.get_ebx(), 0x5400272E);
    EXPECT_EQ(cpu.get_ecx(), 0x00DD864D);
    EXPECT_EQ(cpu.get_edx(), 0x099EA9BD);
    EXPECT_EQ(cpu.get_esi(), 0x96BB7BA0);
    EXPECT_EQ(cpu.get_edi(), 0xA0AC6D2C);
    EXPECT_EQ(cpu.get_ebp(), 0x8EB93E3F);
    EXPECT_EQ(cpu.get_esp(), 0x0000B4E3);
    EXPECT_EQ(cpu.get_cs(), 0x00000001);
    EXPECT_EQ(cpu.get_ds(), 0x0000C294);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00000100);
    EXPECT_EQ(cpu.get_gs(), 0x0000FF88);
    EXPECT_EQ(cpu.get_ss(), 0x0000B836);
    EXPECT_EQ(cpu.get_eip(), 0x0000D973);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC3844), 0x04);
    EXPECT_EQ(memory.load8(0xC3845), 0x00);
    EXPECT_EQ(memory.load8(0xC3846), 0x00);
    EXPECT_EQ(memory.load8(0xC3843), 0x93);
}

//
// push sp
//
TEST_F(Test386, push_sp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x566AF113);
    cpu.set_ebx(0x40478BFD);
    cpu.set_ecx(0xFC7B4F7E);
    cpu.set_edx(0xFFFFFF8F);
    cpu.set_esi(0x025F59A1);
    cpu.set_edi(0x4B88A292);
    cpu.set_ebp(0x2FF45484);
    cpu.set_esp(0x0000BCE8);
    cpu.set_cs(0x0000FDB5);
    cpu.set_ds(0x0000007F);
    cpu.set_es(0x000003A6);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x000065FB);
    cpu.set_ss(0x00007914);
    cpu.set_eip(0x00000D38);
    cpu.set_eflags(0xFFFC0CC7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFE888, 0x54);
    machine.mem_store_byte(0xFE889, 0xF4);
    machine.mem_store_byte(0xFE88A, 0xF6);
    machine.mem_store_byte(0xFE88B, 0x21);
    machine.mem_store_byte(0xFE88C, 0x0A);
    machine.mem_store_byte(0xFE88D, 0x19);
    machine.mem_store_byte(0xFE88E, 0x92);
    machine.mem_store_byte(0xFE88F, 0xA5);
    machine.mem_store_byte(0xFE890, 0xF9);
    machine.mem_store_byte(0xFE891, 0x76);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x566AF113);
    EXPECT_EQ(cpu.get_ebx(), 0x40478BFD);
    EXPECT_EQ(cpu.get_ecx(), 0xFC7B4F7E);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFF8F);
    EXPECT_EQ(cpu.get_esi(), 0x025F59A1);
    EXPECT_EQ(cpu.get_edi(), 0x4B88A292);
    EXPECT_EQ(cpu.get_ebp(), 0x2FF45484);
    EXPECT_EQ(cpu.get_esp(), 0x0000BCE6);
    EXPECT_EQ(cpu.get_cs(), 0x0000FDB5);
    EXPECT_EQ(cpu.get_ds(), 0x0000007F);
    EXPECT_EQ(cpu.get_es(), 0x000003A6);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x000065FB);
    EXPECT_EQ(cpu.get_ss(), 0x00007914);
    EXPECT_EQ(cpu.get_eip(), 0x00000D3A);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0CC7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x84E26), 0xE8);
    EXPECT_EQ(memory.load8(0x84E27), 0xBC);
}
