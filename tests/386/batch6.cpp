#include "test386.h"

//
// loope 40D4h
//
TEST_F(Test386, loope_40D4h_batch6)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF447E133);
    cpu.set_ebx(0xF59D3667);
    cpu.set_ecx(0x00000000);
    cpu.set_edx(0x9E77CFAA);
    cpu.set_esi(0x2B28DC20);
    cpu.set_edi(0xF807992E);
    cpu.set_ebp(0x0D646AEB);
    cpu.set_esp(0x000029F8);
    cpu.set_cs(0x0000EA97);
    cpu.set_ds(0x0000B5C7);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x00007EF7);
    cpu.set_gs(0x00007FFF);
    cpu.set_ss(0x00001806);
    cpu.set_eip(0x00004138);
    cpu.set_eflags(0xFFFC0C56);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEEAA8, 0xE1);
    machine.mem_store_byte(0xEEAA9, 0x9A);
    machine.mem_store_byte(0xEEAAA, 0xF4);
    machine.mem_store_byte(0xEEAAB, 0xCD);
    machine.mem_store_byte(0xEEAAC, 0x1F);
    machine.mem_store_byte(0xEEAAD, 0x87);
    machine.mem_store_byte(0xEEAAE, 0x6A);
    machine.mem_store_byte(0xEEAAF, 0x2A);
    machine.mem_store_byte(0xEEA44, 0xF4);
    machine.mem_store_byte(0xEEA45, 0x00);
    machine.mem_store_byte(0xEEA46, 0x90);
    machine.mem_store_byte(0xEEA47, 0x63);
    machine.mem_store_byte(0xEEA48, 0x5D);
    machine.mem_store_byte(0xEEA49, 0xC0);
    machine.mem_store_byte(0xEEA4A, 0xA1);
    machine.mem_store_byte(0xEEA4B, 0x2A);
    machine.mem_store_byte(0xEEA4C, 0x42);
    machine.mem_store_byte(0xEEA4D, 0x33);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF447E133);
    EXPECT_EQ(cpu.get_ebx(), 0xF59D3667);
    EXPECT_EQ(cpu.get_ecx(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edx(), 0x9E77CFAA);
    EXPECT_EQ(cpu.get_esi(), 0x2B28DC20);
    EXPECT_EQ(cpu.get_edi(), 0xF807992E);
    EXPECT_EQ(cpu.get_ebp(), 0x0D646AEB);
    EXPECT_EQ(cpu.get_esp(), 0x000029F8);
    EXPECT_EQ(cpu.get_cs(), 0x0000EA97);
    EXPECT_EQ(cpu.get_ds(), 0x0000B5C7);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x00007EF7);
    EXPECT_EQ(cpu.get_gs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ss(), 0x00001806);
    EXPECT_EQ(cpu.get_eip(), 0x000040D5);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C56);

    // Final RAM entries
}

//
// o32 enter FA47h,12h
//
TEST_F(Test386, o32_enter_FA47h_12h_batch6)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDB78CAC6);
    cpu.set_ebx(0x765ED85F);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0x13E55BF6);
    cpu.set_esi(0xDE0D5C00);
    cpu.set_edi(0x4DD5B612);
    cpu.set_ebp(0x28019A7F);
    cpu.set_esp(0x00000276);
    cpu.set_cs(0x0000A6F5);
    cpu.set_ds(0x00007C4F);
    cpu.set_es(0x0000F6A7);
    cpu.set_fs(0x00000D39);
    cpu.set_gs(0x0000E37E);
    cpu.set_ss(0x0000ADE0);
    cpu.set_eip(0x000092F0);
    cpu.set_eflags(0xFFFC0097);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB0240, 0x66);
    machine.mem_store_byte(0xB0241, 0xC8);
    machine.mem_store_byte(0xB0242, 0x47);
    machine.mem_store_byte(0xB0243, 0xFA);
    machine.mem_store_byte(0xB0244, 0x12);
    machine.mem_store_byte(0xB0245, 0xF4);
    machine.mem_store_byte(0xB0246, 0xDD);
    machine.mem_store_byte(0xB0247, 0x5F);
    machine.mem_store_byte(0xB0248, 0xA5);
    machine.mem_store_byte(0xB0249, 0xA6);
    machine.mem_store_byte(0xB024A, 0xE7);
    machine.mem_store_byte(0xB024B, 0xEC);
    machine.mem_store_byte(0xB024C, 0x62);
    machine.mem_store_byte(0xB024D, 0x95);
    machine.mem_store_byte(0xB024E, 0x79);
    machine.mem_store_byte(0xB024F, 0xC0);
    machine.mem_store_byte(0xB787C, 0xB4);
    machine.mem_store_byte(0xB787D, 0x1D);
    machine.mem_store_byte(0xB787E, 0x38);
    machine.mem_store_byte(0xB787B, 0x61);
    machine.mem_store_byte(0xB7878, 0xFA);
    machine.mem_store_byte(0xB7879, 0x6B);
    machine.mem_store_byte(0xB787A, 0x1F);
    machine.mem_store_byte(0xB7877, 0x96);
    machine.mem_store_byte(0xB7874, 0xB5);
    machine.mem_store_byte(0xB7875, 0xF6);
    machine.mem_store_byte(0xB7876, 0x3C);
    machine.mem_store_byte(0xB7873, 0x43);
    machine.mem_store_byte(0xB7870, 0x5E);
    machine.mem_store_byte(0xB7871, 0x75);
    machine.mem_store_byte(0xB7872, 0x33);
    machine.mem_store_byte(0xB786F, 0x88);
    machine.mem_store_byte(0xB786C, 0x5F);
    machine.mem_store_byte(0xB786D, 0x58);
    machine.mem_store_byte(0xB786E, 0xAD);
    machine.mem_store_byte(0xB786B, 0x02);
    machine.mem_store_byte(0xB7868, 0xD1);
    machine.mem_store_byte(0xB7869, 0xE0);
    machine.mem_store_byte(0xB786A, 0x3F);
    machine.mem_store_byte(0xB7867, 0x01);
    machine.mem_store_byte(0xB7864, 0xBB);
    machine.mem_store_byte(0xB7865, 0xA7);
    machine.mem_store_byte(0xB7866, 0xD3);
    machine.mem_store_byte(0xB7863, 0xB9);
    machine.mem_store_byte(0xB7860, 0xEA);
    machine.mem_store_byte(0xB7861, 0x34);
    machine.mem_store_byte(0xB7862, 0xE0);
    machine.mem_store_byte(0xB785F, 0x6E);
    machine.mem_store_byte(0xB785C, 0x0B);
    machine.mem_store_byte(0xB785D, 0x86);
    machine.mem_store_byte(0xB785E, 0xC0);
    machine.mem_store_byte(0xB785B, 0x12);
    machine.mem_store_byte(0xB7858, 0xEB);
    machine.mem_store_byte(0xB7859, 0x24);
    machine.mem_store_byte(0xB785A, 0xA4);
    machine.mem_store_byte(0xB7857, 0x3D);
    machine.mem_store_byte(0xB7854, 0xB9);
    machine.mem_store_byte(0xB7855, 0xC6);
    machine.mem_store_byte(0xB7856, 0xD4);
    machine.mem_store_byte(0xB7853, 0xB4);
    machine.mem_store_byte(0xB7850, 0x67);
    machine.mem_store_byte(0xB7851, 0xB6);
    machine.mem_store_byte(0xB7852, 0xA5);
    machine.mem_store_byte(0xB784F, 0xCC);
    machine.mem_store_byte(0xB784C, 0xF1);
    machine.mem_store_byte(0xB784D, 0x15);
    machine.mem_store_byte(0xB784E, 0x7A);
    machine.mem_store_byte(0xB784B, 0x6B);
    machine.mem_store_byte(0xB7848, 0x2B);
    machine.mem_store_byte(0xB7849, 0x99);
    machine.mem_store_byte(0xB784A, 0x7B);
    machine.mem_store_byte(0xB7847, 0x30);
    machine.mem_store_byte(0xB7844, 0x47);
    machine.mem_store_byte(0xB7845, 0x1B);
    machine.mem_store_byte(0xB7846, 0x79);
    machine.mem_store_byte(0xB7843, 0xCE);
    machine.mem_store_byte(0xB7840, 0xB5);
    machine.mem_store_byte(0xB7841, 0x73);
    machine.mem_store_byte(0xB7842, 0x80);
    machine.mem_store_byte(0xB783F, 0x09);
    machine.mem_store_byte(0xB783C, 0x88);
    machine.mem_store_byte(0xB783D, 0x63);
    machine.mem_store_byte(0xB783E, 0x3F);
    machine.mem_store_byte(0xB783B, 0x59);
    machine.mem_store_byte(0xB0250, 0xC4);
    machine.mem_store_byte(0xB0251, 0x0B);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDB78CAC6);
    EXPECT_EQ(cpu.get_ebx(), 0x765ED85F);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x13E55BF6);
    EXPECT_EQ(cpu.get_esi(), 0xDE0D5C00);
    EXPECT_EQ(cpu.get_edi(), 0x4DD5B612);
    EXPECT_EQ(cpu.get_ebp(), 0x00000272);
    EXPECT_EQ(cpu.get_esp(), 0x000007E3);
    EXPECT_EQ(cpu.get_cs(), 0x0000A6F5);
    EXPECT_EQ(cpu.get_ds(), 0x00007C4F);
    EXPECT_EQ(cpu.get_es(), 0x0000F6A7);
    EXPECT_EQ(cpu.get_fs(), 0x00000D39);
    EXPECT_EQ(cpu.get_gs(), 0x0000E37E);
    EXPECT_EQ(cpu.get_ss(), 0x0000ADE0);
    EXPECT_EQ(cpu.get_eip(), 0x000092F6);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0097);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAE074), 0x01);
    EXPECT_EQ(memory.load8(0xAE075), 0x28);
    EXPECT_EQ(memory.load8(0xAE072), 0x7F);
    EXPECT_EQ(memory.load8(0xAE073), 0x9A);
    EXPECT_EQ(memory.load8(0xAE070), 0x1D);
    EXPECT_EQ(memory.load8(0xAE071), 0x38);
    EXPECT_EQ(memory.load8(0xAE06E), 0x61);
    EXPECT_EQ(memory.load8(0xAE06F), 0xB4);
    EXPECT_EQ(memory.load8(0xAE06C), 0x6B);
    EXPECT_EQ(memory.load8(0xAE06D), 0x1F);
    EXPECT_EQ(memory.load8(0xAE06A), 0x96);
    EXPECT_EQ(memory.load8(0xAE06B), 0xFA);
    EXPECT_EQ(memory.load8(0xAE068), 0xF6);
    EXPECT_EQ(memory.load8(0xAE069), 0x3C);
    EXPECT_EQ(memory.load8(0xAE066), 0x43);
    EXPECT_EQ(memory.load8(0xAE067), 0xB5);
    EXPECT_EQ(memory.load8(0xAE064), 0x75);
    EXPECT_EQ(memory.load8(0xAE065), 0x33);
    EXPECT_EQ(memory.load8(0xAE062), 0x88);
    EXPECT_EQ(memory.load8(0xAE063), 0x5E);
    EXPECT_EQ(memory.load8(0xAE060), 0x58);
    EXPECT_EQ(memory.load8(0xAE061), 0xAD);
    EXPECT_EQ(memory.load8(0xAE05E), 0x02);
    EXPECT_EQ(memory.load8(0xAE05F), 0x5F);
    EXPECT_EQ(memory.load8(0xAE05C), 0xE0);
    EXPECT_EQ(memory.load8(0xAE05D), 0x3F);
    EXPECT_EQ(memory.load8(0xAE05A), 0x01);
    EXPECT_EQ(memory.load8(0xAE05B), 0xD1);
    EXPECT_EQ(memory.load8(0xAE058), 0xA7);
    EXPECT_EQ(memory.load8(0xAE059), 0xD3);
    EXPECT_EQ(memory.load8(0xAE056), 0xB9);
    EXPECT_EQ(memory.load8(0xAE057), 0xBB);
    EXPECT_EQ(memory.load8(0xAE054), 0x34);
    EXPECT_EQ(memory.load8(0xAE055), 0xE0);
    EXPECT_EQ(memory.load8(0xAE052), 0x6E);
    EXPECT_EQ(memory.load8(0xAE053), 0xEA);
    EXPECT_EQ(memory.load8(0xAE050), 0x86);
    EXPECT_EQ(memory.load8(0xAE051), 0xC0);
    EXPECT_EQ(memory.load8(0xAE04E), 0x12);
    EXPECT_EQ(memory.load8(0xAE04F), 0x0B);
    EXPECT_EQ(memory.load8(0xAE04C), 0x24);
    EXPECT_EQ(memory.load8(0xAE04D), 0xA4);
    EXPECT_EQ(memory.load8(0xAE04A), 0x3D);
    EXPECT_EQ(memory.load8(0xAE04B), 0xEB);
    EXPECT_EQ(memory.load8(0xAE048), 0xC6);
    EXPECT_EQ(memory.load8(0xAE049), 0xD4);
    EXPECT_EQ(memory.load8(0xAE046), 0xB4);
    EXPECT_EQ(memory.load8(0xAE047), 0xB9);
    EXPECT_EQ(memory.load8(0xAE044), 0xB6);
    EXPECT_EQ(memory.load8(0xAE045), 0xA5);
    EXPECT_EQ(memory.load8(0xAE042), 0xCC);
    EXPECT_EQ(memory.load8(0xAE043), 0x67);
    EXPECT_EQ(memory.load8(0xAE040), 0x15);
    EXPECT_EQ(memory.load8(0xAE041), 0x7A);
    EXPECT_EQ(memory.load8(0xAE03E), 0x6B);
    EXPECT_EQ(memory.load8(0xAE03F), 0xF1);
    EXPECT_EQ(memory.load8(0xAE03C), 0x99);
    EXPECT_EQ(memory.load8(0xAE03D), 0x7B);
    EXPECT_EQ(memory.load8(0xAE03A), 0x30);
    EXPECT_EQ(memory.load8(0xAE03B), 0x2B);
    EXPECT_EQ(memory.load8(0xAE038), 0x1B);
    EXPECT_EQ(memory.load8(0xAE039), 0x79);
    EXPECT_EQ(memory.load8(0xAE036), 0xCE);
    EXPECT_EQ(memory.load8(0xAE037), 0x47);
    EXPECT_EQ(memory.load8(0xAE034), 0x73);
    EXPECT_EQ(memory.load8(0xAE035), 0x80);
    EXPECT_EQ(memory.load8(0xAE032), 0x09);
    EXPECT_EQ(memory.load8(0xAE033), 0xB5);
    EXPECT_EQ(memory.load8(0xAE030), 0x63);
    EXPECT_EQ(memory.load8(0xAE031), 0x3F);
    EXPECT_EQ(memory.load8(0xAE02E), 0x59);
    EXPECT_EQ(memory.load8(0xAE02F), 0x88);
    EXPECT_EQ(memory.load8(0xAE02C), 0x00);
    EXPECT_EQ(memory.load8(0xAE02D), 0x00);
    EXPECT_EQ(memory.load8(0xAE02A), 0x72);
    EXPECT_EQ(memory.load8(0xAE02B), 0x02);
}

//
// o32 loope 000040D5h
//
TEST_F(Test386, o32_loope_000040D5h_batch6)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF447E133);
    cpu.set_ebx(0xF59D3667);
    cpu.set_ecx(0x00000000);
    cpu.set_edx(0x9E77CFAA);
    cpu.set_esi(0x2B28DC20);
    cpu.set_edi(0xF807992E);
    cpu.set_ebp(0x0D646AEB);
    cpu.set_esp(0x000029F8);
    cpu.set_cs(0x0000EA97);
    cpu.set_ds(0x0000B5C7);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x00007EF7);
    cpu.set_gs(0x00007FFF);
    cpu.set_ss(0x00001806);
    cpu.set_eip(0x00004138);
    cpu.set_eflags(0xFFFC0C56);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEEAA8, 0x66);
    machine.mem_store_byte(0xEEAA9, 0xE1);
    machine.mem_store_byte(0xEEAAA, 0x9A);
    machine.mem_store_byte(0xEEAAB, 0xF4);
    machine.mem_store_byte(0xEEAAC, 0x1F);
    machine.mem_store_byte(0xEEAAD, 0x87);
    machine.mem_store_byte(0xEEAAE, 0x6A);
    machine.mem_store_byte(0xEEAAF, 0x2A);
    machine.mem_store_byte(0xEEAB0, 0xB4);
    machine.mem_store_byte(0xEEAB1, 0xDF);
    machine.mem_store_byte(0xEEA44, 0x89);
    machine.mem_store_byte(0xEEA45, 0xF4);
    machine.mem_store_byte(0xEEA46, 0x90);
    machine.mem_store_byte(0xEEA47, 0x63);
    machine.mem_store_byte(0xEEA48, 0x5D);
    machine.mem_store_byte(0xEEA49, 0xC0);
    machine.mem_store_byte(0xEEA4A, 0xA1);
    machine.mem_store_byte(0xEEA4B, 0x2A);
    machine.mem_store_byte(0xEEA4C, 0x42);
    machine.mem_store_byte(0xEEA4D, 0x33);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF447E133);
    EXPECT_EQ(cpu.get_ebx(), 0xF59D3667);
    EXPECT_EQ(cpu.get_ecx(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edx(), 0x9E77CFAA);
    EXPECT_EQ(cpu.get_esi(), 0x2B28DC20);
    EXPECT_EQ(cpu.get_edi(), 0xF807992E);
    EXPECT_EQ(cpu.get_ebp(), 0x0D646AEB);
    EXPECT_EQ(cpu.get_esp(), 0x000029F8);
    EXPECT_EQ(cpu.get_cs(), 0x0000EA97);
    EXPECT_EQ(cpu.get_ds(), 0x0000B5C7);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x00007EF7);
    EXPECT_EQ(cpu.get_gs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ss(), 0x00001806);
    EXPECT_EQ(cpu.get_eip(), 0x000040D6);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C56);

    // Final RAM entries
}

//
// retd
//
TEST_F(Test386, retd_batch6)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x5202E0E9);
    cpu.set_ebx(0xADF66D10);
    cpu.set_ecx(0x7FFFFFFF);
    cpu.set_edx(0x33134B7D);
    cpu.set_esi(0x6AF350DB);
    cpu.set_edi(0x3B495E20);
    cpu.set_ebp(0x5535E2DB);
    cpu.set_esp(0x00000FFE);
    cpu.set_cs(0x00001628);
    cpu.set_ds(0x0000E9C0);
    cpu.set_es(0x00004E9F);
    cpu.set_fs(0x00006C78);
    cpu.set_gs(0x00000017);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x000067A0);
    cpu.set_eflags(0xFFFC0C82);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1CA20, 0x66);
    machine.mem_store_byte(0x1CA21, 0xC3);
    machine.mem_store_byte(0x1CA22, 0xF4);
    machine.mem_store_byte(0x1CA23, 0xFF);
    machine.mem_store_byte(0x1CA24, 0xFF);
    machine.mem_store_byte(0x1CA25, 0xFF);
    machine.mem_store_byte(0x1CA26, 0xFF);
    machine.mem_store_byte(0x1CA27, 0xFF);
    machine.mem_store_byte(0x100FF0, 0xFF);
    machine.mem_store_byte(0x100FF1, 0xFF);
    machine.mem_store_byte(0x100FEE, 0xFF);
    machine.mem_store_byte(0x100FEF, 0xFF);
    machine.mem_store_byte(0x00034, 0x99);
    machine.mem_store_byte(0x00035, 0xF8);
    machine.mem_store_byte(0x00036, 0xB3);
    machine.mem_store_byte(0x00037, 0x5B);
    machine.mem_store_byte(0x6B3C8, 0xF4);
    machine.mem_store_byte(0x6B3C9, 0xF4);
    machine.mem_store_byte(0x6B3CA, 0xFF);
    machine.mem_store_byte(0x6B3CB, 0xF4);
    machine.mem_store_byte(0x6B3CC, 0xFF);
    machine.mem_store_byte(0x6B3CD, 0xF4);
    machine.mem_store_byte(0x6B3CE, 0xFF);
    machine.mem_store_byte(0x6B3CF, 0xF4);
    machine.mem_store_byte(0x6B3D0, 0xFF);
    machine.mem_store_byte(0x6B3D1, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x5202E0E9);
    EXPECT_EQ(cpu.get_ebx(), 0xADF66D10);
    EXPECT_EQ(cpu.get_ecx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x33134B7D);
    EXPECT_EQ(cpu.get_esi(), 0x6AF350DB);
    EXPECT_EQ(cpu.get_edi(), 0x3B495E20);
    EXPECT_EQ(cpu.get_ebp(), 0x5535E2DB);
    EXPECT_EQ(cpu.get_esp(), 0x00000FF8);
    EXPECT_EQ(cpu.get_cs(), 0x00005BB3);
    EXPECT_EQ(cpu.get_ds(), 0x0000E9C0);
    EXPECT_EQ(cpu.get_es(), 0x00004E9F);
    EXPECT_EQ(cpu.get_fs(), 0x00006C78);
    EXPECT_EQ(cpu.get_gs(), 0x00000017);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x0000F89A);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C82);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x100FEC), 0x82);
    EXPECT_EQ(memory.load8(0x100FED), 0x0C);
    EXPECT_EQ(memory.load8(0x100FEA), 0x28);
    EXPECT_EQ(memory.load8(0x100FEB), 0x16);
    EXPECT_EQ(memory.load8(0x100FE8), 0xA0);
    EXPECT_EQ(memory.load8(0x100FE9), 0x67);
}

//
// shrd [ss:esp+C50h],di,cl
//
TEST_F(Test386, shrd_ss_esp_C50h_di_cl_batch6)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF0306ABE);
    cpu.set_ebx(0xD43378E0);
    cpu.set_ecx(0x0A8D4826);
    cpu.set_edx(0x0204CCC3);
    cpu.set_esi(0xFF6754B0);
    cpu.set_edi(0xDD1EF3D3);
    cpu.set_ebp(0x01412B07);
    cpu.set_esp(0x00001436);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000B0EF);
    cpu.set_es(0x00008002);
    cpu.set_fs(0x000001F1);
    cpu.set_gs(0x0000CC6D);
    cpu.set_ss(0x0000B603);
    cpu.set_eip(0x0000DE90);
    cpu.set_eflags(0xFFFC0882);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0DE90, 0x67);
    machine.mem_store_byte(0x0DE91, 0x0F);
    machine.mem_store_byte(0x0DE92, 0xAD);
    machine.mem_store_byte(0x0DE93, 0xBC);
    machine.mem_store_byte(0x0DE94, 0xE4);
    machine.mem_store_byte(0x0DE95, 0x50);
    machine.mem_store_byte(0x0DE96, 0x0C);
    machine.mem_store_byte(0x0DE97, 0x00);
    machine.mem_store_byte(0x0DE98, 0x00);
    machine.mem_store_byte(0x0DE99, 0xF4);
    machine.mem_store_byte(0x0DE9A, 0xCB);
    machine.mem_store_byte(0x0DE9B, 0x87);
    machine.mem_store_byte(0x0DE9C, 0x85);
    machine.mem_store_byte(0x0DE9D, 0x7A);
    machine.mem_store_byte(0x0DE9E, 0x7D);
    machine.mem_store_byte(0x0DE9F, 0xEF);
    machine.mem_store_byte(0xC0E30, 0x01);
    machine.mem_store_byte(0xC0E31, 0x18);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF0306ABE);
    EXPECT_EQ(cpu.get_ebx(), 0xD43378E0);
    EXPECT_EQ(cpu.get_ecx(), 0x0A8D4826);
    EXPECT_EQ(cpu.get_edx(), 0x0204CCC3);
    EXPECT_EQ(cpu.get_esi(), 0xFF6754B0);
    EXPECT_EQ(cpu.get_edi(), 0xDD1EF3D3);
    EXPECT_EQ(cpu.get_ebp(), 0x01412B07);
    EXPECT_EQ(cpu.get_esp(), 0x00001436);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000B0EF);
    EXPECT_EQ(cpu.get_es(), 0x00008002);
    EXPECT_EQ(cpu.get_fs(), 0x000001F1);
    EXPECT_EQ(cpu.get_gs(), 0x0000CC6D);
    EXPECT_EQ(cpu.get_ss(), 0x0000B603);
    EXPECT_EQ(cpu.get_eip(), 0x0000DE9A);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0816);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC0E30), 0x60);
    EXPECT_EQ(memory.load8(0xC0E31), 0x4C);
}

//
// shrd [ss:esp+C50h],edi,cl
//
TEST_F(Test386, shrd_ss_esp_C50h_edi_cl_batch6)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF0306ABE);
    cpu.set_ebx(0xD43378E0);
    cpu.set_ecx(0x0A8D4826);
    cpu.set_edx(0x0204CCC3);
    cpu.set_esi(0xFF6754B0);
    cpu.set_edi(0xDD1EF3D3);
    cpu.set_ebp(0x01412B07);
    cpu.set_esp(0x00001436);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000B0EF);
    cpu.set_es(0x00008002);
    cpu.set_fs(0x000001F1);
    cpu.set_gs(0x0000CC6D);
    cpu.set_ss(0x0000B603);
    cpu.set_eip(0x0000DE90);
    cpu.set_eflags(0xFFFC0882);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0DE90, 0x66);
    machine.mem_store_byte(0x0DE91, 0x67);
    machine.mem_store_byte(0x0DE92, 0x0F);
    machine.mem_store_byte(0x0DE93, 0xAD);
    machine.mem_store_byte(0x0DE94, 0xBC);
    machine.mem_store_byte(0x0DE95, 0xE4);
    machine.mem_store_byte(0x0DE96, 0x50);
    machine.mem_store_byte(0x0DE97, 0x0C);
    machine.mem_store_byte(0x0DE98, 0x00);
    machine.mem_store_byte(0x0DE99, 0x00);
    machine.mem_store_byte(0x0DE9A, 0xF4);
    machine.mem_store_byte(0x0DE9B, 0x87);
    machine.mem_store_byte(0x0DE9C, 0x85);
    machine.mem_store_byte(0x0DE9D, 0x7A);
    machine.mem_store_byte(0x0DE9E, 0x7D);
    machine.mem_store_byte(0x0DE9F, 0xEF);
    machine.mem_store_byte(0xC0E30, 0x01);
    machine.mem_store_byte(0xC0E31, 0x18);
    machine.mem_store_byte(0xC0E32, 0xAE);
    machine.mem_store_byte(0xC0E33, 0x7E);
    machine.mem_store_byte(0x0DEA0, 0x74);
    machine.mem_store_byte(0x0DEA1, 0xF6);
    machine.mem_store_byte(0x0DEA2, 0x15);
    machine.mem_store_byte(0x0DEA3, 0x4A);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF0306ABE);
    EXPECT_EQ(cpu.get_ebx(), 0xD43378E0);
    EXPECT_EQ(cpu.get_ecx(), 0x0A8D4826);
    EXPECT_EQ(cpu.get_edx(), 0x0204CCC3);
    EXPECT_EQ(cpu.get_esi(), 0xFF6754B0);
    EXPECT_EQ(cpu.get_edi(), 0xDD1EF3D3);
    EXPECT_EQ(cpu.get_ebp(), 0x01412B07);
    EXPECT_EQ(cpu.get_esp(), 0x00001436);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000B0EF);
    EXPECT_EQ(cpu.get_es(), 0x00008002);
    EXPECT_EQ(cpu.get_fs(), 0x000001F1);
    EXPECT_EQ(cpu.get_gs(), 0x0000CC6D);
    EXPECT_EQ(cpu.get_ss(), 0x0000B603);
    EXPECT_EQ(cpu.get_eip(), 0x0000DE9B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0816);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC0E30), 0x60);
    EXPECT_EQ(memory.load8(0xC0E31), 0xB8);
    EXPECT_EQ(memory.load8(0xC0E32), 0xFA);
    EXPECT_EQ(memory.load8(0xC0E33), 0x4D);
}
