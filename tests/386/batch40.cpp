#include "test386.h"

//
// a32 rep insd
//
TEST_F(Test386, a32_rep_insd_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x01A0541B);
    cpu.set_ebx(0xA7874DBE);
    cpu.set_ecx(0x00000026);
    cpu.set_edx(0x523D6C9B);
    cpu.set_esi(0xCAFC2417);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x00008C9A);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000B273);
    cpu.set_es(0x00007BA0);
    cpu.set_fs(0x00002262);
    cpu.set_gs(0x0000B650);
    cpu.set_ss(0x00001A31);
    cpu.set_eip(0x0000BB40);
    cpu.set_eflags(0xFFFC0C42);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10BB30, 0xF3);
    machine.mem_store_byte(0x10BB31, 0x67);
    machine.mem_store_byte(0x10BB32, 0x66);
    machine.mem_store_byte(0x10BB33, 0x6D);
    machine.mem_store_byte(0x10BB34, 0xF4);
    machine.mem_store_byte(0x10BB35, 0x07);
    machine.mem_store_byte(0x10BB36, 0xAD);
    machine.mem_store_byte(0x10BB37, 0xC4);
    machine.mem_store_byte(0x10BB38, 0x2B);
    machine.mem_store_byte(0x10BB39, 0x95);
    machine.mem_store_byte(0x10BB3A, 0x57);
    machine.mem_store_byte(0x10BB3B, 0x08);
    machine.mem_store_byte(0x10BB3C, 0x2F);
    machine.mem_store_byte(0x10BB3D, 0x67);
    machine.mem_store_byte(0x10BB3E, 0xF4);
    machine.mem_store_byte(0x10BB3F, 0x42);
    machine.mem_store_byte(0x00034, 0x8B);
    machine.mem_store_byte(0x00035, 0x12);
    machine.mem_store_byte(0x00036, 0x35);
    machine.mem_store_byte(0x00037, 0x6B);
    machine.mem_store_byte(0x6C5DA, 0x56);
    machine.mem_store_byte(0x6C5DB, 0xF4);
    machine.mem_store_byte(0x6C5DC, 0x42);
    machine.mem_store_byte(0x6C5DD, 0xF4);
    machine.mem_store_byte(0x6C5DE, 0xD2);
    machine.mem_store_byte(0x6C5DF, 0xF4);
    machine.mem_store_byte(0x6C5E0, 0x71);
    machine.mem_store_byte(0x6C5E1, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x01A0541B);
    EXPECT_EQ(cpu.get_ebx(), 0xA7874DBE);
    EXPECT_EQ(cpu.get_ecx(), 0x00000025);
    EXPECT_EQ(cpu.get_edx(), 0x523D6C9B);
    EXPECT_EQ(cpu.get_esi(), 0xCAFC2417);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFC);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x00008C94);
    EXPECT_EQ(cpu.get_cs(), 0x00006B35);
    EXPECT_EQ(cpu.get_ds(), 0x0000B273);
    EXPECT_EQ(cpu.get_es(), 0x00007BA0);
    EXPECT_EQ(cpu.get_fs(), 0x00002262);
    EXPECT_EQ(cpu.get_gs(), 0x0000B650);
    EXPECT_EQ(cpu.get_ss(), 0x00001A31);
    EXPECT_EQ(cpu.get_eip(), 0x0000128C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C42);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7BA00), 0xFF);
    EXPECT_EQ(memory.load8(0x7BA01), 0xFF);
    EXPECT_EQ(memory.load8(0x7BA02), 0xFF);
    EXPECT_EQ(memory.load8(0x7BA03), 0xFF);
    EXPECT_EQ(memory.load8(0x22FA8), 0x42);
    EXPECT_EQ(memory.load8(0x22FA9), 0x0C);
    EXPECT_EQ(memory.load8(0x22FA6), 0xFF);
    EXPECT_EQ(memory.load8(0x22FA7), 0xFF);
    EXPECT_EQ(memory.load8(0x22FA4), 0x40);
    EXPECT_EQ(memory.load8(0x22FA5), 0xBB);
}

//
// a32 rep insw
//
TEST_F(Test386, a32_rep_insw_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x01A0541B);
    cpu.set_ebx(0xA7874DBE);
    cpu.set_ecx(0x00000026);
    cpu.set_edx(0x523D6C9B);
    cpu.set_esi(0xCAFC2417);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x00008C9A);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000B273);
    cpu.set_es(0x00007BA0);
    cpu.set_fs(0x00002262);
    cpu.set_gs(0x0000B650);
    cpu.set_ss(0x00001A31);
    cpu.set_eip(0x0000BB40);
    cpu.set_eflags(0xFFFC0C42);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10BB30, 0xF3);
    machine.mem_store_byte(0x10BB31, 0x67);
    machine.mem_store_byte(0x10BB32, 0x6D);
    machine.mem_store_byte(0x10BB33, 0xF4);
    machine.mem_store_byte(0x10BB34, 0xAB);
    machine.mem_store_byte(0x10BB35, 0x07);
    machine.mem_store_byte(0x10BB36, 0xAD);
    machine.mem_store_byte(0x10BB37, 0xC4);
    machine.mem_store_byte(0x10BB38, 0x2B);
    machine.mem_store_byte(0x10BB39, 0x95);
    machine.mem_store_byte(0x10BB3A, 0x57);
    machine.mem_store_byte(0x10BB3B, 0x08);
    machine.mem_store_byte(0x10BB3C, 0x2F);
    machine.mem_store_byte(0x10BB3D, 0x67);
    machine.mem_store_byte(0x10BB3E, 0xF4);
    machine.mem_store_byte(0x10BB3F, 0x42);
    machine.mem_store_byte(0x00034, 0x8B);
    machine.mem_store_byte(0x00035, 0x12);
    machine.mem_store_byte(0x00036, 0x35);
    machine.mem_store_byte(0x00037, 0x6B);
    machine.mem_store_byte(0x6C5DA, 0x56);
    machine.mem_store_byte(0x6C5DB, 0xF4);
    machine.mem_store_byte(0x6C5DC, 0x42);
    machine.mem_store_byte(0x6C5DD, 0xF4);
    machine.mem_store_byte(0x6C5DE, 0xD2);
    machine.mem_store_byte(0x6C5DF, 0xF4);
    machine.mem_store_byte(0x6C5E0, 0x71);
    machine.mem_store_byte(0x6C5E1, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x01A0541B);
    EXPECT_EQ(cpu.get_ebx(), 0xA7874DBE);
    EXPECT_EQ(cpu.get_ecx(), 0x00000025);
    EXPECT_EQ(cpu.get_edx(), 0x523D6C9B);
    EXPECT_EQ(cpu.get_esi(), 0xCAFC2417);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFFE);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x00008C94);
    EXPECT_EQ(cpu.get_cs(), 0x00006B35);
    EXPECT_EQ(cpu.get_ds(), 0x0000B273);
    EXPECT_EQ(cpu.get_es(), 0x00007BA0);
    EXPECT_EQ(cpu.get_fs(), 0x00002262);
    EXPECT_EQ(cpu.get_gs(), 0x0000B650);
    EXPECT_EQ(cpu.get_ss(), 0x00001A31);
    EXPECT_EQ(cpu.get_eip(), 0x0000128C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C42);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7BA00), 0xFF);
    EXPECT_EQ(memory.load8(0x7BA01), 0xFF);
    EXPECT_EQ(memory.load8(0x22FA8), 0x42);
    EXPECT_EQ(memory.load8(0x22FA9), 0x0C);
    EXPECT_EQ(memory.load8(0x22FA6), 0xFF);
    EXPECT_EQ(memory.load8(0x22FA7), 0xFF);
    EXPECT_EQ(memory.load8(0x22FA4), 0x40);
    EXPECT_EQ(memory.load8(0x22FA5), 0xBB);
}

//
// mov dword [ss:ebp-E2CEh],19C72495h
//
TEST_F(Test386, mov_dword_ss_ebp_E2CEh_19C72495h_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE9B611B5);
    cpu.set_ebx(0xD003158A);
    cpu.set_ecx(0x4121B409);
    cpu.set_edx(0xC2EE2F23);
    cpu.set_esi(0xFFFFFFF4);
    cpu.set_edi(0xE54A24BD);
    cpu.set_ebp(0x00008257);
    cpu.set_esp(0x00004B9A);
    cpu.set_cs(0x000064D9);
    cpu.set_ds(0x0000CDD8);
    cpu.set_es(0x00003F09);
    cpu.set_fs(0x00009230);
    cpu.set_gs(0x000023DE);
    cpu.set_ss(0x00003B35);
    cpu.set_eip(0x0000A3B0);
    cpu.set_eflags(0xFFFC0097);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6F140, 0x66);
    machine.mem_store_byte(0x6F141, 0x67);
    machine.mem_store_byte(0x6F142, 0xC7);
    machine.mem_store_byte(0x6F143, 0x85);
    machine.mem_store_byte(0x6F144, 0x32);
    machine.mem_store_byte(0x6F145, 0x1D);
    machine.mem_store_byte(0x6F146, 0xFF);
    machine.mem_store_byte(0x6F147, 0xFF);
    machine.mem_store_byte(0x6F148, 0x95);
    machine.mem_store_byte(0x6F149, 0x24);
    machine.mem_store_byte(0x6F14A, 0xC7);
    machine.mem_store_byte(0x6F14B, 0x19);
    machine.mem_store_byte(0x6F14C, 0xF4);
    machine.mem_store_byte(0x6F14D, 0xAA);
    machine.mem_store_byte(0x6F14E, 0x7F);
    machine.mem_store_byte(0x6F14F, 0x99);
    machine.mem_store_byte(0x6F150, 0xA3);
    machine.mem_store_byte(0x6F151, 0xD7);
    machine.mem_store_byte(0x6F152, 0xCB);
    machine.mem_store_byte(0x6F153, 0x66);
    machine.mem_store_byte(0x6F154, 0x27);
    machine.mem_store_byte(0x6F155, 0xD8);
    machine.mem_store_byte(0x6F156, 0xA0);
    machine.mem_store_byte(0x6F157, 0x2D);
    machine.mem_store_byte(0x6F158, 0xF2);
    machine.mem_store_byte(0x6F159, 0xCD);
    machine.mem_store_byte(0x6F15A, 0xD7);
    machine.mem_store_byte(0x6F15B, 0xEE);
    machine.mem_store_byte(0x00030, 0xFC);
    machine.mem_store_byte(0x00031, 0x10);
    machine.mem_store_byte(0x00032, 0x3C);
    machine.mem_store_byte(0x00033, 0x06);
    machine.mem_store_byte(0x074BC, 0xF4);
    machine.mem_store_byte(0x074BD, 0xB9);
    machine.mem_store_byte(0x074BE, 0xF4);
    machine.mem_store_byte(0x074BF, 0xEF);
    machine.mem_store_byte(0x074C0, 0xF4);
    machine.mem_store_byte(0x074C1, 0x73);
    machine.mem_store_byte(0x074C2, 0xF4);
    machine.mem_store_byte(0x074C3, 0x3A);
    machine.mem_store_byte(0x074C4, 0xF4);
    machine.mem_store_byte(0x074C5, 0x58);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE9B611B5);
    EXPECT_EQ(cpu.get_ebx(), 0xD003158A);
    EXPECT_EQ(cpu.get_ecx(), 0x4121B409);
    EXPECT_EQ(cpu.get_edx(), 0xC2EE2F23);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFF4);
    EXPECT_EQ(cpu.get_edi(), 0xE54A24BD);
    EXPECT_EQ(cpu.get_ebp(), 0x00008257);
    EXPECT_EQ(cpu.get_esp(), 0x00004B94);
    EXPECT_EQ(cpu.get_cs(), 0x0000063C);
    EXPECT_EQ(cpu.get_ds(), 0x0000CDD8);
    EXPECT_EQ(cpu.get_es(), 0x00003F09);
    EXPECT_EQ(cpu.get_fs(), 0x00009230);
    EXPECT_EQ(cpu.get_gs(), 0x000023DE);
    EXPECT_EQ(cpu.get_ss(), 0x00003B35);
    EXPECT_EQ(cpu.get_eip(), 0x000010FD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0097);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x3FEE8, 0x97);
    EXPECT_FLAGS_HI(0x3FEE9, 0x00);
    EXPECT_EQ(memory.load8(0x3FEE6), 0xD9);
    EXPECT_EQ(memory.load8(0x3FEE7), 0x64);
    EXPECT_EQ(memory.load8(0x3FEE4), 0xB0);
    EXPECT_EQ(memory.load8(0x3FEE5), 0xA3);
}

//
// mov word [ss:ebp-E2CEh],2495h
//
TEST_F(Test386, mov_word_ss_ebp_E2CEh_2495h_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE9B611B5);
    cpu.set_ebx(0xD003158A);
    cpu.set_ecx(0x4121B409);
    cpu.set_edx(0xC2EE2F23);
    cpu.set_esi(0xFFFFFFF4);
    cpu.set_edi(0xE54A24BD);
    cpu.set_ebp(0x00008257);
    cpu.set_esp(0x00004B9A);
    cpu.set_cs(0x000064D9);
    cpu.set_ds(0x0000CDD8);
    cpu.set_es(0x00003F09);
    cpu.set_fs(0x00009230);
    cpu.set_gs(0x000023DE);
    cpu.set_ss(0x00003B35);
    cpu.set_eip(0x0000A3B0);
    cpu.set_eflags(0xFFFC0097);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6F140, 0x67);
    machine.mem_store_byte(0x6F141, 0xC7);
    machine.mem_store_byte(0x6F142, 0x85);
    machine.mem_store_byte(0x6F143, 0x32);
    machine.mem_store_byte(0x6F144, 0x1D);
    machine.mem_store_byte(0x6F145, 0xFF);
    machine.mem_store_byte(0x6F146, 0xFF);
    machine.mem_store_byte(0x6F147, 0x95);
    machine.mem_store_byte(0x6F148, 0x24);
    machine.mem_store_byte(0x6F149, 0xF4);
    machine.mem_store_byte(0x6F14A, 0x41);
    machine.mem_store_byte(0x6F14B, 0x77);
    machine.mem_store_byte(0x6F14C, 0xD0);
    machine.mem_store_byte(0x6F14D, 0xAA);
    machine.mem_store_byte(0x6F14E, 0x7F);
    machine.mem_store_byte(0x6F14F, 0x99);
    machine.mem_store_byte(0x6F150, 0xA3);
    machine.mem_store_byte(0x6F151, 0xD7);
    machine.mem_store_byte(0x6F152, 0xCB);
    machine.mem_store_byte(0x6F153, 0x66);
    machine.mem_store_byte(0x6F154, 0x27);
    machine.mem_store_byte(0x6F155, 0xD8);
    machine.mem_store_byte(0x6F156, 0xA0);
    machine.mem_store_byte(0x6F157, 0x2D);
    machine.mem_store_byte(0x00030, 0xFC);
    machine.mem_store_byte(0x00031, 0x10);
    machine.mem_store_byte(0x00032, 0x3C);
    machine.mem_store_byte(0x00033, 0x06);
    machine.mem_store_byte(0x074BC, 0xF4);
    machine.mem_store_byte(0x074BD, 0xB9);
    machine.mem_store_byte(0x074BE, 0xF4);
    machine.mem_store_byte(0x074BF, 0xEF);
    machine.mem_store_byte(0x074C0, 0xF4);
    machine.mem_store_byte(0x074C1, 0x73);
    machine.mem_store_byte(0x074C2, 0xF4);
    machine.mem_store_byte(0x074C3, 0x3A);
    machine.mem_store_byte(0x074C4, 0xF4);
    machine.mem_store_byte(0x074C5, 0x58);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE9B611B5);
    EXPECT_EQ(cpu.get_ebx(), 0xD003158A);
    EXPECT_EQ(cpu.get_ecx(), 0x4121B409);
    EXPECT_EQ(cpu.get_edx(), 0xC2EE2F23);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFF4);
    EXPECT_EQ(cpu.get_edi(), 0xE54A24BD);
    EXPECT_EQ(cpu.get_ebp(), 0x00008257);
    EXPECT_EQ(cpu.get_esp(), 0x00004B94);
    EXPECT_EQ(cpu.get_cs(), 0x0000063C);
    EXPECT_EQ(cpu.get_ds(), 0x0000CDD8);
    EXPECT_EQ(cpu.get_es(), 0x00003F09);
    EXPECT_EQ(cpu.get_fs(), 0x00009230);
    EXPECT_EQ(cpu.get_gs(), 0x000023DE);
    EXPECT_EQ(cpu.get_ss(), 0x00003B35);
    EXPECT_EQ(cpu.get_eip(), 0x000010FD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0097);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x3FEE8, 0x97);
    EXPECT_FLAGS_HI(0x3FEE9, 0x00);
    EXPECT_EQ(memory.load8(0x3FEE6), 0xD9);
    EXPECT_EQ(memory.load8(0x3FEE7), 0x64);
    EXPECT_EQ(memory.load8(0x3FEE4), 0xB0);
    EXPECT_EQ(memory.load8(0x3FEE5), 0xA3);
}

//
// mul byte [fs:ecx-9931h]
//
TEST_F(Test386, mul_byte_fs_ecx_9931h_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1315CCA8);
    cpu.set_ebx(0x405432E5);
    cpu.set_ecx(0x0000344C);
    cpu.set_edx(0xC6D986C0);
    cpu.set_esi(0x8F9BD574);
    cpu.set_edi(0x3E7CB4C5);
    cpu.set_ebp(0xFFFFFFFF);
    cpu.set_esp(0x0000DDBF);
    cpu.set_cs(0x0000DD08);
    cpu.set_ds(0x0000B9AC);
    cpu.set_es(0x0000CFF0);
    cpu.set_fs(0x000040C3);
    cpu.set_gs(0x000051E0);
    cpu.set_ss(0x000003A2);
    cpu.set_eip(0x00003F30);
    cpu.set_eflags(0xFFFC0886);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE0FB0, 0x64);
    machine.mem_store_byte(0xE0FB1, 0x67);
    machine.mem_store_byte(0xE0FB2, 0xF6);
    machine.mem_store_byte(0xE0FB3, 0xA1);
    machine.mem_store_byte(0xE0FB4, 0xCF);
    machine.mem_store_byte(0xE0FB5, 0x66);
    machine.mem_store_byte(0xE0FB6, 0xFF);
    machine.mem_store_byte(0xE0FB7, 0xFF);
    machine.mem_store_byte(0xE0FB8, 0xF4);
    machine.mem_store_byte(0xE0FB9, 0xD6);
    machine.mem_store_byte(0xE0FBA, 0x05);
    machine.mem_store_byte(0xE0FBB, 0x71);
    machine.mem_store_byte(0xE0FBC, 0x17);
    machine.mem_store_byte(0xE0FBD, 0xA8);
    machine.mem_store_byte(0xE0FBE, 0x7E);
    machine.mem_store_byte(0xE0FBF, 0xB8);
    machine.mem_store_byte(0xE0FC0, 0x31);
    machine.mem_store_byte(0xE0FC1, 0xD7);
    machine.mem_store_byte(0xE0FC2, 0x6B);
    machine.mem_store_byte(0xE0FC3, 0xC5);
    machine.mem_store_byte(0x00034, 0xAB);
    machine.mem_store_byte(0x00035, 0x10);
    machine.mem_store_byte(0x00036, 0xED);
    machine.mem_store_byte(0x00037, 0x3B);
    machine.mem_store_byte(0x3CF7A, 0x10);
    machine.mem_store_byte(0x3CF7B, 0xF4);
    machine.mem_store_byte(0x3CF7C, 0x11);
    machine.mem_store_byte(0x3CF7D, 0xF4);
    machine.mem_store_byte(0x3CF7E, 0x0E);
    machine.mem_store_byte(0x3CF7F, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1315CCA8);
    EXPECT_EQ(cpu.get_ebx(), 0x405432E5);
    EXPECT_EQ(cpu.get_ecx(), 0x0000344C);
    EXPECT_EQ(cpu.get_edx(), 0xC6D986C0);
    EXPECT_EQ(cpu.get_esi(), 0x8F9BD574);
    EXPECT_EQ(cpu.get_edi(), 0x3E7CB4C5);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000DDB9);
    EXPECT_EQ(cpu.get_cs(), 0x00003BED);
    EXPECT_EQ(cpu.get_ds(), 0x0000B9AC);
    EXPECT_EQ(cpu.get_es(), 0x0000CFF0);
    EXPECT_EQ(cpu.get_fs(), 0x000040C3);
    EXPECT_EQ(cpu.get_gs(), 0x000051E0);
    EXPECT_EQ(cpu.get_ss(), 0x000003A2);
    EXPECT_EQ(cpu.get_eip(), 0x000010AC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0886);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x117DD, 0x86);
    EXPECT_FLAGS_HI(0x117DE, 0x08);
    EXPECT_EQ(memory.load8(0x117DC), 0xDD);
    EXPECT_EQ(memory.load8(0x117DB), 0x08);
    EXPECT_EQ(memory.load8(0x117D9), 0x30);
    EXPECT_EQ(memory.load8(0x117DA), 0x3F);
}

//
// pop dword [ss:esp+edx*1-17h]
//
TEST_F(Test386, pop_dword_ss_esp_edx_1_17h_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000061);
    cpu.set_ebx(0xA7F0F36C);
    cpu.set_ecx(0x81D729F1);
    cpu.set_edx(0x00002951);
    cpu.set_esi(0xA16BC3ED);
    cpu.set_edi(0xFFFFFFF9);
    cpu.set_ebp(0x00008080);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000CD47);
    cpu.set_es(0x00007E03);
    cpu.set_fs(0x0000FC62);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x000038E7);
    cpu.set_eip(0x0000C178);
    cpu.set_eflags(0xFFFC0C06);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0C178, 0x67);
    machine.mem_store_byte(0x0C179, 0x66);
    machine.mem_store_byte(0x0C17A, 0x8F);
    machine.mem_store_byte(0x0C17B, 0x44);
    machine.mem_store_byte(0x0C17C, 0x14);
    machine.mem_store_byte(0x0C17D, 0xE9);
    machine.mem_store_byte(0x0C17E, 0xF4);
    machine.mem_store_byte(0x0C17F, 0x1E);
    machine.mem_store_byte(0x0C180, 0x5D);
    machine.mem_store_byte(0x0C181, 0x62);
    machine.mem_store_byte(0x0C182, 0x86);
    machine.mem_store_byte(0x0C183, 0x9C);
    machine.mem_store_byte(0x0C184, 0xB5);
    machine.mem_store_byte(0x0C185, 0xDE);
    machine.mem_store_byte(0x38E78, 0xDC);
    machine.mem_store_byte(0x38E79, 0x2A);
    machine.mem_store_byte(0x38E7A, 0x40);
    machine.mem_store_byte(0x38E7B, 0xF7);
    machine.mem_store_byte(0x0C186, 0x12);
    machine.mem_store_byte(0x0C187, 0x59);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000061);
    EXPECT_EQ(cpu.get_ebx(), 0xA7F0F36C);
    EXPECT_EQ(cpu.get_ecx(), 0x81D729F1);
    EXPECT_EQ(cpu.get_edx(), 0x00002951);
    EXPECT_EQ(cpu.get_esi(), 0xA16BC3ED);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFF9);
    EXPECT_EQ(cpu.get_ebp(), 0x00008080);
    EXPECT_EQ(cpu.get_esp(), 0x0000000C);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000CD47);
    EXPECT_EQ(cpu.get_es(), 0x00007E03);
    EXPECT_EQ(cpu.get_fs(), 0x0000FC62);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x000038E7);
    EXPECT_EQ(cpu.get_eip(), 0x0000C17F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C06);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3B7B8), 0x40);
    EXPECT_EQ(memory.load8(0x3B7B9), 0xF7);
    EXPECT_EQ(memory.load8(0x3B7B6), 0xDC);
    EXPECT_EQ(memory.load8(0x3B7B7), 0x2A);
}

//
// pop word [ss:esp+edx*1-17h]
//
TEST_F(Test386, pop_word_ss_esp_edx_1_17h_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000061);
    cpu.set_ebx(0xA7F0F36C);
    cpu.set_ecx(0x81D729F1);
    cpu.set_edx(0x00002951);
    cpu.set_esi(0xA16BC3ED);
    cpu.set_edi(0xFFFFFFF9);
    cpu.set_ebp(0x00008080);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000CD47);
    cpu.set_es(0x00007E03);
    cpu.set_fs(0x0000FC62);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x000038E7);
    cpu.set_eip(0x0000C178);
    cpu.set_eflags(0xFFFC0C06);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0C178, 0x67);
    machine.mem_store_byte(0x0C179, 0x8F);
    machine.mem_store_byte(0x0C17A, 0x44);
    machine.mem_store_byte(0x0C17B, 0x14);
    machine.mem_store_byte(0x0C17C, 0xE9);
    machine.mem_store_byte(0x0C17D, 0xF4);
    machine.mem_store_byte(0x0C17E, 0x25);
    machine.mem_store_byte(0x0C17F, 0x1E);
    machine.mem_store_byte(0x0C180, 0x5D);
    machine.mem_store_byte(0x0C181, 0x62);
    machine.mem_store_byte(0x0C182, 0x86);
    machine.mem_store_byte(0x0C183, 0x9C);
    machine.mem_store_byte(0x38E78, 0xDC);
    machine.mem_store_byte(0x38E79, 0x2A);
    machine.mem_store_byte(0x0C184, 0xB5);
    machine.mem_store_byte(0x0C185, 0xDE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000061);
    EXPECT_EQ(cpu.get_ebx(), 0xA7F0F36C);
    EXPECT_EQ(cpu.get_ecx(), 0x81D729F1);
    EXPECT_EQ(cpu.get_edx(), 0x00002951);
    EXPECT_EQ(cpu.get_esi(), 0xA16BC3ED);
    EXPECT_EQ(cpu.get_edi(), 0xFFFFFFF9);
    EXPECT_EQ(cpu.get_ebp(), 0x00008080);
    EXPECT_EQ(cpu.get_esp(), 0x0000000A);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000CD47);
    EXPECT_EQ(cpu.get_es(), 0x00007E03);
    EXPECT_EQ(cpu.get_fs(), 0x0000FC62);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x000038E7);
    EXPECT_EQ(cpu.get_eip(), 0x0000C17E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C06);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3B7B4), 0xDC);
    EXPECT_EQ(memory.load8(0x3B7B5), 0x2A);
}

//
// ret C15Ah
//
TEST_F(Test386, ret_C15Ah_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x03793884);
    cpu.set_ebx(0x7C50FDF0);
    cpu.set_ecx(0xB748ABC7);
    cpu.set_edx(0x0DC8E895);
    cpu.set_esi(0x00008000);
    cpu.set_edi(0x9D805199);
    cpu.set_ebp(0xFA9B5502);
    cpu.set_esp(0x0000FFFF);
    cpu.set_cs(0x00003083);
    cpu.set_ds(0x0000643C);
    cpu.set_es(0x0000046E);
    cpu.set_fs(0x00008733);
    cpu.set_gs(0x000005EB);
    cpu.set_ss(0x00001291);
    cpu.set_eip(0x00002790);
    cpu.set_eflags(0xFFFC0807);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x32FC0, 0xC2);
    machine.mem_store_byte(0x32FC1, 0x5A);
    machine.mem_store_byte(0x32FC2, 0xC1);
    machine.mem_store_byte(0x32FC3, 0xF4);
    machine.mem_store_byte(0x32FC4, 0xFF);
    machine.mem_store_byte(0x32FC5, 0xF9);
    machine.mem_store_byte(0x32FC6, 0x84);
    machine.mem_store_byte(0x32FC7, 0x84);
    machine.mem_store_byte(0x00030, 0x2C);
    machine.mem_store_byte(0x00031, 0x14);
    machine.mem_store_byte(0x00032, 0x3A);
    machine.mem_store_byte(0x00033, 0xCC);
    machine.mem_store_byte(0xCD7CC, 0xF4);
    machine.mem_store_byte(0xCD7CD, 0xF4);
    machine.mem_store_byte(0xCD7CE, 0xF4);
    machine.mem_store_byte(0xCD7CF, 0xF4);
    machine.mem_store_byte(0xCD7D0, 0xF4);
    machine.mem_store_byte(0xCD7D1, 0x96);
    machine.mem_store_byte(0xCD7D2, 0xF4);
    machine.mem_store_byte(0xCD7D3, 0x7A);
    machine.mem_store_byte(0xCD7D4, 0xF4);
    machine.mem_store_byte(0xCD7D5, 0xC3);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x03793884);
    EXPECT_EQ(cpu.get_ebx(), 0x7C50FDF0);
    EXPECT_EQ(cpu.get_ecx(), 0xB748ABC7);
    EXPECT_EQ(cpu.get_edx(), 0x0DC8E895);
    EXPECT_EQ(cpu.get_esi(), 0x00008000);
    EXPECT_EQ(cpu.get_edi(), 0x9D805199);
    EXPECT_EQ(cpu.get_ebp(), 0xFA9B5502);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF9);
    EXPECT_EQ(cpu.get_cs(), 0x0000CC3A);
    EXPECT_EQ(cpu.get_ds(), 0x0000643C);
    EXPECT_EQ(cpu.get_es(), 0x0000046E);
    EXPECT_EQ(cpu.get_fs(), 0x00008733);
    EXPECT_EQ(cpu.get_gs(), 0x000005EB);
    EXPECT_EQ(cpu.get_ss(), 0x00001291);
    EXPECT_EQ(cpu.get_eip(), 0x0000142D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0807);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x2290D, 0x07);
    EXPECT_FLAGS_HI(0x2290E, 0x08);
    EXPECT_EQ(memory.load8(0x2290C), 0x30);
    EXPECT_EQ(memory.load8(0x2290B), 0x83);
    EXPECT_EQ(memory.load8(0x22909), 0x90);
    EXPECT_EQ(memory.load8(0x2290A), 0x27);
}

//
// retd C15Ah
//
TEST_F(Test386, retd_C15Ah_batch40)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x03793884);
    cpu.set_ebx(0x7C50FDF0);
    cpu.set_ecx(0xB748ABC7);
    cpu.set_edx(0x0DC8E895);
    cpu.set_esi(0x00008000);
    cpu.set_edi(0x9D805199);
    cpu.set_ebp(0xFA9B5502);
    cpu.set_esp(0x0000FFFF);
    cpu.set_cs(0x00003083);
    cpu.set_ds(0x0000643C);
    cpu.set_es(0x0000046E);
    cpu.set_fs(0x00008733);
    cpu.set_gs(0x000005EB);
    cpu.set_ss(0x00001291);
    cpu.set_eip(0x00002790);
    cpu.set_eflags(0xFFFC0807);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x32FC0, 0x66);
    machine.mem_store_byte(0x32FC1, 0xC2);
    machine.mem_store_byte(0x32FC2, 0x5A);
    machine.mem_store_byte(0x32FC3, 0xC1);
    machine.mem_store_byte(0x32FC4, 0xF4);
    machine.mem_store_byte(0x32FC5, 0xF9);
    machine.mem_store_byte(0x32FC6, 0x84);
    machine.mem_store_byte(0x32FC7, 0x84);
    machine.mem_store_byte(0x32FC8, 0xDD);
    machine.mem_store_byte(0x32FC9, 0xB9);
    machine.mem_store_byte(0x00030, 0x2C);
    machine.mem_store_byte(0x00031, 0x14);
    machine.mem_store_byte(0x00032, 0x3A);
    machine.mem_store_byte(0x00033, 0xCC);
    machine.mem_store_byte(0xCD7CC, 0xF4);
    machine.mem_store_byte(0xCD7CD, 0xF4);
    machine.mem_store_byte(0xCD7CE, 0xF4);
    machine.mem_store_byte(0xCD7CF, 0xF4);
    machine.mem_store_byte(0xCD7D0, 0xF4);
    machine.mem_store_byte(0xCD7D1, 0x96);
    machine.mem_store_byte(0xCD7D2, 0xF4);
    machine.mem_store_byte(0xCD7D3, 0x7A);
    machine.mem_store_byte(0xCD7D4, 0xF4);
    machine.mem_store_byte(0xCD7D5, 0xC3);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x03793884);
    EXPECT_EQ(cpu.get_ebx(), 0x7C50FDF0);
    EXPECT_EQ(cpu.get_ecx(), 0xB748ABC7);
    EXPECT_EQ(cpu.get_edx(), 0x0DC8E895);
    EXPECT_EQ(cpu.get_esi(), 0x00008000);
    EXPECT_EQ(cpu.get_edi(), 0x9D805199);
    EXPECT_EQ(cpu.get_ebp(), 0xFA9B5502);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF9);
    EXPECT_EQ(cpu.get_cs(), 0x0000CC3A);
    EXPECT_EQ(cpu.get_ds(), 0x0000643C);
    EXPECT_EQ(cpu.get_es(), 0x0000046E);
    EXPECT_EQ(cpu.get_fs(), 0x00008733);
    EXPECT_EQ(cpu.get_gs(), 0x000005EB);
    EXPECT_EQ(cpu.get_ss(), 0x00001291);
    EXPECT_EQ(cpu.get_eip(), 0x0000142D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0807);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x2290D, 0x07);
    EXPECT_FLAGS_HI(0x2290E, 0x08);
    EXPECT_EQ(memory.load8(0x2290C), 0x30);
    EXPECT_EQ(memory.load8(0x2290B), 0x83);
    EXPECT_EQ(memory.load8(0x22909), 0x90);
    EXPECT_EQ(memory.load8(0x2290A), 0x27);
}

//
// xlatb
//
TEST_F(Test386, xlatb_batch40)
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
    machine.mem_store_byte(0x98BC0, 0xD7);
    machine.mem_store_byte(0x98BC1, 0xF4);
    machine.mem_store_byte(0x98BC2, 0xFC);
    machine.mem_store_byte(0x98BC3, 0xF5);
    machine.mem_store_byte(0x98BC4, 0x79);
    machine.mem_store_byte(0x98BC5, 0x98);
    machine.mem_store_byte(0x98BC6, 0x11);
    machine.mem_store_byte(0x98BC7, 0x3F);
    machine.mem_store_byte(0x98BC8, 0xBA);
    machine.mem_store_byte(0x98BC9, 0x39);
    machine.mem_store_byte(0x469E3, 0x76);
    machine.mem_store_byte(0x98BCA, 0xF5);
    machine.mem_store_byte(0x98BCB, 0x87);
    machine.mem_store_byte(0x98BCC, 0x13);
    machine.mem_store_byte(0x98BCD, 0xB3);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x92175576);
    EXPECT_EQ(cpu.get_ebx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0xA6D8809D);
    EXPECT_EQ(cpu.get_edx(), 0x7E9BA2E4);
    EXPECT_EQ(cpu.get_esi(), 0x79B725F6);
    EXPECT_EQ(cpu.get_edi(), 0x5FA6F2B1);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00008ED3);
    EXPECT_EQ(cpu.get_ds(), 0x0000469A);
    EXPECT_EQ(cpu.get_es(), 0x0000130C);
    EXPECT_EQ(cpu.get_fs(), 0x0000FE54);
    EXPECT_EQ(cpu.get_gs(), 0x0000D558);
    EXPECT_EQ(cpu.get_ss(), 0x00001064);
    EXPECT_EQ(cpu.get_eip(), 0x00009E92);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C2);

    // Final RAM entries
}
