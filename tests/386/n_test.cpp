#include "test386.h"

//
// neg dword [ds:bx-10h]
//
TEST_F(Test386, neg_dword_ds_bx_10h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7413F32D);
    cpu.set_ebx(0x9E9707D5);
    cpu.set_ecx(0xFE6A9ABA);
    cpu.set_edx(0x3F6A799A);
    cpu.set_esi(0x9CE5E38E);
    cpu.set_edi(0xD0EC98FD);
    cpu.set_ebp(0xEDE39401);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000BA3C);
    cpu.set_ds(0x00002A2E);
    cpu.set_es(0x0000055A);
    cpu.set_fs(0x0000DA04);
    cpu.set_gs(0x0000F94D);
    cpu.set_ss(0x0000F9A5);
    cpu.set_eip(0x00001BD8);
    cpu.set_eflags(0xFFFC0442);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBBF98, 0x66);
    machine.mem_store_byte(0xBBF99, 0xF7);
    machine.mem_store_byte(0xBBF9A, 0x5F);
    machine.mem_store_byte(0xBBF9B, 0xF0);
    machine.mem_store_byte(0xBBF9C, 0xF4);
    machine.mem_store_byte(0xBBF9D, 0xFF);
    machine.mem_store_byte(0xBBF9E, 0xFF);
    machine.mem_store_byte(0xBBF9F, 0xFF);
    machine.mem_store_byte(0xBBFA0, 0xFF);
    machine.mem_store_byte(0xBBFA1, 0xFF);
    machine.mem_store_byte(0xBBFA2, 0xFF);
    machine.mem_store_byte(0xBBFA3, 0xFF);
    machine.mem_store_byte(0x2AAA8, 0xFF);
    machine.mem_store_byte(0x2AAA5, 0xFF);
    machine.mem_store_byte(0x2AAA6, 0xFF);
    machine.mem_store_byte(0x2AAA7, 0xFF);
    machine.mem_store_byte(0xBBFA4, 0xFF);
    machine.mem_store_byte(0xBBFA5, 0xFF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7413F32D);
    EXPECT_EQ(cpu.get_ebx(), 0x9E9707D5);
    EXPECT_EQ(cpu.get_ecx(), 0xFE6A9ABA);
    EXPECT_EQ(cpu.get_edx(), 0x3F6A799A);
    EXPECT_EQ(cpu.get_esi(), 0x9CE5E38E);
    EXPECT_EQ(cpu.get_edi(), 0xD0EC98FD);
    EXPECT_EQ(cpu.get_ebp(), 0xEDE39401);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000BA3C);
    EXPECT_EQ(cpu.get_ds(), 0x00002A2E);
    EXPECT_EQ(cpu.get_es(), 0x0000055A);
    EXPECT_EQ(cpu.get_fs(), 0x0000DA04);
    EXPECT_EQ(cpu.get_gs(), 0x0000F94D);
    EXPECT_EQ(cpu.get_ss(), 0x0000F9A5);
    EXPECT_EQ(cpu.get_eip(), 0x00001BDD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2AAA8), 0x00);
    EXPECT_EQ(memory.load8(0x2AAA5), 0x01);
    EXPECT_EQ(memory.load8(0x2AAA6), 0x00);
    EXPECT_EQ(memory.load8(0x2AAA7), 0x00);
}

//
// not byte [ds:esi+ebx*4-4Ch]
//
TEST_F(Test386, not_byte_ds_esi_ebx_4_4Ch)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x85096F16);
    cpu.set_ebx(0x00000888);
    cpu.set_ecx(0x780D5F62);
    cpu.set_edx(0xCBBF8886);
    cpu.set_esi(0x0000161A);
    cpu.set_edi(0x45379E82);
    cpu.set_ebp(0x030FC2B1);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00002B6C);
    cpu.set_ds(0x0000347D);
    cpu.set_es(0x00000698);
    cpu.set_fs(0x00001020);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x00000425);
    cpu.set_eip(0x000021D8);
    cpu.set_eflags(0xFFFC0017);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2D898, 0x67);
    machine.mem_store_byte(0x2D899, 0xF6);
    machine.mem_store_byte(0x2D89A, 0x54);
    machine.mem_store_byte(0x2D89B, 0x9E);
    machine.mem_store_byte(0x2D89C, 0xB4);
    machine.mem_store_byte(0x2D89D, 0xF4);
    machine.mem_store_byte(0x2D89E, 0x5A);
    machine.mem_store_byte(0x2D89F, 0x55);
    machine.mem_store_byte(0x2D8A0, 0xF2);
    machine.mem_store_byte(0x2D8A1, 0xED);
    machine.mem_store_byte(0x2D8A2, 0x9A);
    machine.mem_store_byte(0x2D8A3, 0x4A);
    machine.mem_store_byte(0x37FBE, 0xC8);
    machine.mem_store_byte(0x2D8A4, 0xBE);
    machine.mem_store_byte(0x2D8A5, 0x82);
    machine.mem_store_byte(0x2D8A6, 0xB5);
    machine.mem_store_byte(0x2D8A7, 0xA8);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x85096F16);
    EXPECT_EQ(cpu.get_ebx(), 0x00000888);
    EXPECT_EQ(cpu.get_ecx(), 0x780D5F62);
    EXPECT_EQ(cpu.get_edx(), 0xCBBF8886);
    EXPECT_EQ(cpu.get_esi(), 0x0000161A);
    EXPECT_EQ(cpu.get_edi(), 0x45379E82);
    EXPECT_EQ(cpu.get_ebp(), 0x030FC2B1);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00002B6C);
    EXPECT_EQ(cpu.get_ds(), 0x0000347D);
    EXPECT_EQ(cpu.get_es(), 0x00000698);
    EXPECT_EQ(cpu.get_fs(), 0x00001020);
    EXPECT_EQ(cpu.get_gs(), 0x00000000);
    EXPECT_EQ(cpu.get_ss(), 0x00000425);
    EXPECT_EQ(cpu.get_eip(), 0x000021DE);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0017);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x37FBE), 0x37);
}

//
// not dword [gs:di-48h]
//
TEST_F(Test386, not_dword_gs_di_48h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xED632CAD);
    cpu.set_ebx(0xC89622CB);
    cpu.set_ecx(0x910C1F9D);
    cpu.set_edx(0x0D18C1E5);
    cpu.set_esi(0x5F8EAFB9);
    cpu.set_edi(0x911D24EA);
    cpu.set_ebp(0x010CC20C);
    cpu.set_esp(0x000094EE);
    cpu.set_cs(0x0000695D);
    cpu.set_ds(0x0000DB5B);
    cpu.set_es(0x0000A82D);
    cpu.set_fs(0x00002992);
    cpu.set_gs(0x0000F280);
    cpu.set_ss(0x0000EA5F);
    cpu.set_eip(0x00002C50);
    cpu.set_eflags(0xFFFC04D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6C220, 0x65);
    machine.mem_store_byte(0x6C221, 0x66);
    machine.mem_store_byte(0x6C222, 0xF7);
    machine.mem_store_byte(0x6C223, 0x55);
    machine.mem_store_byte(0x6C224, 0xB8);
    machine.mem_store_byte(0x6C225, 0xF4);
    machine.mem_store_byte(0x6C226, 0xC2);
    machine.mem_store_byte(0x6C227, 0xC3);
    machine.mem_store_byte(0x6C228, 0xAC);
    machine.mem_store_byte(0x6C229, 0xAD);
    machine.mem_store_byte(0x6C22A, 0x9F);
    machine.mem_store_byte(0x6C22B, 0x9A);
    machine.mem_store_byte(0xF4CA4, 0xA7);
    machine.mem_store_byte(0xF4CA5, 0x6B);
    machine.mem_store_byte(0xF4CA2, 0x2A);
    machine.mem_store_byte(0xF4CA3, 0xE6);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xED632CAD);
    EXPECT_EQ(cpu.get_ebx(), 0xC89622CB);
    EXPECT_EQ(cpu.get_ecx(), 0x910C1F9D);
    EXPECT_EQ(cpu.get_edx(), 0x0D18C1E5);
    EXPECT_EQ(cpu.get_esi(), 0x5F8EAFB9);
    EXPECT_EQ(cpu.get_edi(), 0x911D24EA);
    EXPECT_EQ(cpu.get_ebp(), 0x010CC20C);
    EXPECT_EQ(cpu.get_esp(), 0x000094EE);
    EXPECT_EQ(cpu.get_cs(), 0x0000695D);
    EXPECT_EQ(cpu.get_ds(), 0x0000DB5B);
    EXPECT_EQ(cpu.get_es(), 0x0000A82D);
    EXPECT_EQ(cpu.get_fs(), 0x00002992);
    EXPECT_EQ(cpu.get_gs(), 0x0000F280);
    EXPECT_EQ(cpu.get_ss(), 0x0000EA5F);
    EXPECT_EQ(cpu.get_eip(), 0x00002C56);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04D3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF4CA4), 0x58);
    EXPECT_EQ(memory.load8(0xF4CA5), 0x94);
    EXPECT_EQ(memory.load8(0xF4CA2), 0xD5);
    EXPECT_EQ(memory.load8(0xF4CA3), 0x19);
}
