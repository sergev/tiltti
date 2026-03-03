#include "test386.h"

//
// test al,13h
//
TEST_F(Test386, test_al_13h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00007FFF);
    cpu.set_ebx(0x00000000);
    cpu.set_ecx(0x579D72FA);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x00000001);
    cpu.set_edi(0xEAD3F813);
    cpu.set_ebp(0x7AE3DE4B);
    cpu.set_esp(0x0000FFFF);
    cpu.set_cs(0x0000FF13);
    cpu.set_ds(0x00001D3C);
    cpu.set_es(0x00006D74);
    cpu.set_fs(0x0000A95E);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x000034DF);
    cpu.set_eip(0x00005AE0);
    cpu.set_eflags(0xFFFC00D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x104C10, 0xA8);
    machine.mem_store_byte(0x104C11, 0x13);
    machine.mem_store_byte(0x104C12, 0xF4);
    machine.mem_store_byte(0x104C13, 0x70);
    machine.mem_store_byte(0x104C14, 0x24);
    machine.mem_store_byte(0x104C15, 0x4D);
    machine.mem_store_byte(0x104C16, 0x57);
    machine.mem_store_byte(0x104C17, 0x47);
    machine.mem_store_byte(0x104C18, 0x30);
    machine.mem_store_byte(0x104C19, 0x8D);
    machine.mem_store_byte(0x104C1A, 0xB4);
    machine.mem_store_byte(0x104C1B, 0x12);
    machine.mem_store_byte(0x104C1C, 0x9D);
    machine.mem_store_byte(0x104C1D, 0x07);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebx(), 0x00000000);
    EXPECT_EQ(cpu.get_ecx(), 0x579D72FA);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x00000001);
    EXPECT_EQ(cpu.get_edi(), 0xEAD3F813);
    EXPECT_EQ(cpu.get_ebp(), 0x7AE3DE4B);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_cs(), 0x0000FF13);
    EXPECT_EQ(cpu.get_ds(), 0x00001D3C);
    EXPECT_EQ(cpu.get_es(), 0x00006D74);
    EXPECT_EQ(cpu.get_fs(), 0x0000A95E);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x000034DF);
    EXPECT_EQ(cpu.get_eip(), 0x00005AE3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0002);

    // Final RAM entries
}

//
// test byte [ds:esi-3819h],83h
//
TEST_F(Test386, test_byte_ds_esi_3819h_83h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x01DB4F99);
    cpu.set_ebx(0x0173DDE3);
    cpu.set_ecx(0x672F06CA);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x0000FFFF);
    cpu.set_edi(0x0B9A9AC6);
    cpu.set_ebp(0x35EE136E);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x000085F3);
    cpu.set_ds(0x000000FF);
    cpu.set_es(0x00006C36);
    cpu.set_fs(0x0000E237);
    cpu.set_gs(0x0000B357);
    cpu.set_ss(0x00007FFF);
    cpu.set_eip(0x0000DE68);
    cpu.set_eflags(0xFFFC0883);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x93D98, 0x67);
    machine.mem_store_byte(0x93D99, 0xF6);
    machine.mem_store_byte(0x93D9A, 0x86);
    machine.mem_store_byte(0x93D9B, 0xE7);
    machine.mem_store_byte(0x93D9C, 0xC7);
    machine.mem_store_byte(0x93D9D, 0xFF);
    machine.mem_store_byte(0x93D9E, 0xFF);
    machine.mem_store_byte(0x93D9F, 0x83);
    machine.mem_store_byte(0x93DA0, 0xF4);
    machine.mem_store_byte(0x93DA1, 0xD4);
    machine.mem_store_byte(0x93DA2, 0x92);
    machine.mem_store_byte(0x93DA3, 0x02);
    machine.mem_store_byte(0x93DA4, 0x37);
    machine.mem_store_byte(0x93DA5, 0x5E);
    machine.mem_store_byte(0x0D7D6, 0xCE);
    machine.mem_store_byte(0x93DA6, 0x56);
    machine.mem_store_byte(0x93DA7, 0x69);
    machine.mem_store_byte(0x93DA8, 0xF0);
    machine.mem_store_byte(0x93DA9, 0x44);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x01DB4F99);
    EXPECT_EQ(cpu.get_ebx(), 0x0173DDE3);
    EXPECT_EQ(cpu.get_ecx(), 0x672F06CA);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edi(), 0x0B9A9AC6);
    EXPECT_EQ(cpu.get_ebp(), 0x35EE136E);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_cs(), 0x000085F3);
    EXPECT_EQ(cpu.get_ds(), 0x000000FF);
    EXPECT_EQ(cpu.get_es(), 0x00006C36);
    EXPECT_EQ(cpu.get_fs(), 0x0000E237);
    EXPECT_EQ(cpu.get_gs(), 0x0000B357);
    EXPECT_EQ(cpu.get_ss(), 0x00007FFF);
    EXPECT_EQ(cpu.get_eip(), 0x0000DE71);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0086);

    // Final RAM entries
}

//
// test byte [ss:esp+esi*1-38h],FAh
//
TEST_F(Test386, test_byte_ss_esp_esi_1_38h_FAh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFE964786);
    cpu.set_ebx(0xAFA182B0);
    cpu.set_ecx(0x28369878);
    cpu.set_edx(0xF8991E3C);
    cpu.set_esi(0x0000158E);
    cpu.set_edi(0x8468B5ED);
    cpu.set_ebp(0xDBB6B2C4);
    cpu.set_esp(0x0000638E);
    cpu.set_cs(0x0000009E);
    cpu.set_ds(0x00006B10);
    cpu.set_es(0x0000F44A);
    cpu.set_fs(0x000021B3);
    cpu.set_gs(0x0000033A);
    cpu.set_ss(0x0000147A);
    cpu.set_eip(0x00002BD8);
    cpu.set_eflags(0xFFFC0043);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x035B8, 0x67);
    machine.mem_store_byte(0x035B9, 0xF6);
    machine.mem_store_byte(0x035BA, 0x4C);
    machine.mem_store_byte(0x035BB, 0x34);
    machine.mem_store_byte(0x035BC, 0xC8);
    machine.mem_store_byte(0x035BD, 0xFA);
    machine.mem_store_byte(0x035BE, 0xF4);
    machine.mem_store_byte(0x035BF, 0x5F);
    machine.mem_store_byte(0x035C0, 0x23);
    machine.mem_store_byte(0x035C1, 0xBA);
    machine.mem_store_byte(0x035C2, 0x1E);
    machine.mem_store_byte(0x035C3, 0x92);
    machine.mem_store_byte(0x035C4, 0xD2);
    machine.mem_store_byte(0x035C5, 0xF0);
    machine.mem_store_byte(0x1C084, 0x4D);
    machine.mem_store_byte(0x035C6, 0x83);
    machine.mem_store_byte(0x035C7, 0x28);
    machine.mem_store_byte(0x035C8, 0xE5);
    machine.mem_store_byte(0x035C9, 0x12);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFE964786);
    EXPECT_EQ(cpu.get_ebx(), 0xAFA182B0);
    EXPECT_EQ(cpu.get_ecx(), 0x28369878);
    EXPECT_EQ(cpu.get_edx(), 0xF8991E3C);
    EXPECT_EQ(cpu.get_esi(), 0x0000158E);
    EXPECT_EQ(cpu.get_edi(), 0x8468B5ED);
    EXPECT_EQ(cpu.get_ebp(), 0xDBB6B2C4);
    EXPECT_EQ(cpu.get_esp(), 0x0000638E);
    EXPECT_EQ(cpu.get_cs(), 0x0000009E);
    EXPECT_EQ(cpu.get_ds(), 0x00006B10);
    EXPECT_EQ(cpu.get_es(), 0x0000F44A);
    EXPECT_EQ(cpu.get_fs(), 0x000021B3);
    EXPECT_EQ(cpu.get_gs(), 0x0000033A);
    EXPECT_EQ(cpu.get_ss(), 0x0000147A);
    EXPECT_EQ(cpu.get_eip(), 0x00002BDF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0006);

    // Final RAM entries
}
