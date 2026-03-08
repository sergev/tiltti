#include "test386.h"

//
// (bad) bound ax,bp
//
TEST_F(Test386, bad_bound_ax_bp_batch20)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x6C52DC55);
    cpu.set_ebx(0x859172DD);
    cpu.set_ecx(0x00000001);
    cpu.set_edx(0xB1D8A081);
    cpu.set_esi(0x7FFFFFFF);
    cpu.set_edi(0xCF8765F2);
    cpu.set_ebp(0xCD2D645A);
    cpu.set_esp(0x000081D8);
    cpu.set_cs(0x0000FC98);
    cpu.set_ds(0x00009993);
    cpu.set_es(0x000001BE);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00009C69);
    cpu.set_ss(0x000005ED);
    cpu.set_eip(0x0000DD18);
    cpu.set_eflags(0xFFFC0816);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10A698, 0x62);
    machine.mem_store_byte(0x10A699, 0xC5);
    machine.mem_store_byte(0x10A69A, 0xF4);
    machine.mem_store_byte(0x10A69B, 0x59);
    machine.mem_store_byte(0x10A69C, 0xF8);
    machine.mem_store_byte(0x10A69D, 0xC4);
    machine.mem_store_byte(0x10A69E, 0xB9);
    machine.mem_store_byte(0x10A69F, 0xB4);
    machine.mem_store_byte(0x10A6A0, 0x6A);
    machine.mem_store_byte(0x10A6A1, 0x19);
    machine.mem_store_byte(0x10A6A2, 0x32);
    machine.mem_store_byte(0x10A6A3, 0x64);
    machine.mem_store_byte(0x10A6A4, 0x23);
    machine.mem_store_byte(0x10A6A5, 0x96);
    machine.mem_store_byte(0x00018, 0xF2);
    machine.mem_store_byte(0x00019, 0x59);
    machine.mem_store_byte(0x0001A, 0x14);
    machine.mem_store_byte(0x0001B, 0x84);
    machine.mem_store_byte(0x89B32, 0xF4);
    machine.mem_store_byte(0x89B33, 0x63);
    machine.mem_store_byte(0x89B34, 0xF4);
    machine.mem_store_byte(0x89B35, 0x2F);
    machine.mem_store_byte(0x89B36, 0xF4);
    machine.mem_store_byte(0x89B37, 0x35);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x6C52DC55);
    EXPECT_EQ(cpu.get_ebx(), 0x859172DD);
    EXPECT_EQ(cpu.get_ecx(), 0x00000001);
    EXPECT_EQ(cpu.get_edx(), 0xB1D8A081);
    EXPECT_EQ(cpu.get_esi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0xCF8765F2);
    EXPECT_EQ(cpu.get_ebp(), 0xCD2D645A);
    EXPECT_EQ(cpu.get_esp(), 0x000081D2);
    EXPECT_EQ(cpu.get_cs(), 0x00008414);
    EXPECT_EQ(cpu.get_ds(), 0x00009993);
    EXPECT_EQ(cpu.get_es(), 0x000001BE);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00009C69);
    EXPECT_EQ(cpu.get_ss(), 0x000005ED);
    EXPECT_EQ(cpu.get_eip(), 0x000059F3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0816);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0E0A6), 0x16);
    EXPECT_EQ(memory.load8(0x0E0A7), 0x08);
    EXPECT_EQ(memory.load8(0x0E0A4), 0x98);
    EXPECT_EQ(memory.load8(0x0E0A5), 0xFC);
    EXPECT_EQ(memory.load8(0x0E0A2), 0x18);
    EXPECT_EQ(memory.load8(0x0E0A3), 0xDD);
}

//
// (bad) bound eax,ebp
//
TEST_F(Test386, bad_bound_eax_ebp_batch20)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x6C52DC55);
    cpu.set_ebx(0x859172DD);
    cpu.set_ecx(0x00000001);
    cpu.set_edx(0xB1D8A081);
    cpu.set_esi(0x7FFFFFFF);
    cpu.set_edi(0xCF8765F2);
    cpu.set_ebp(0xCD2D645A);
    cpu.set_esp(0x000081D8);
    cpu.set_cs(0x0000FC98);
    cpu.set_ds(0x00009993);
    cpu.set_es(0x000001BE);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00009C69);
    cpu.set_ss(0x000005ED);
    cpu.set_eip(0x0000DD18);
    cpu.set_eflags(0xFFFC0816);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10A698, 0x67);
    machine.mem_store_byte(0x10A699, 0x66);
    machine.mem_store_byte(0x10A69A, 0x62);
    machine.mem_store_byte(0x10A69B, 0xC5);
    machine.mem_store_byte(0x10A69C, 0xF4);
    machine.mem_store_byte(0x10A69D, 0xC4);
    machine.mem_store_byte(0x10A69E, 0xB9);
    machine.mem_store_byte(0x10A69F, 0xB4);
    machine.mem_store_byte(0x10A6A0, 0x6A);
    machine.mem_store_byte(0x10A6A1, 0x19);
    machine.mem_store_byte(0x10A6A2, 0x32);
    machine.mem_store_byte(0x10A6A3, 0x64);
    machine.mem_store_byte(0x10A6A4, 0x23);
    machine.mem_store_byte(0x10A6A5, 0x96);
    machine.mem_store_byte(0x10A6A6, 0x9E);
    machine.mem_store_byte(0x10A6A7, 0x9B);
    machine.mem_store_byte(0x00018, 0xF2);
    machine.mem_store_byte(0x00019, 0x59);
    machine.mem_store_byte(0x0001A, 0x14);
    machine.mem_store_byte(0x0001B, 0x84);
    machine.mem_store_byte(0x89B32, 0xF4);
    machine.mem_store_byte(0x89B33, 0x63);
    machine.mem_store_byte(0x89B34, 0xF4);
    machine.mem_store_byte(0x89B35, 0x2F);
    machine.mem_store_byte(0x89B36, 0xF4);
    machine.mem_store_byte(0x89B37, 0x35);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x6C52DC55);
    EXPECT_EQ(cpu.get_ebx(), 0x859172DD);
    EXPECT_EQ(cpu.get_ecx(), 0x00000001);
    EXPECT_EQ(cpu.get_edx(), 0xB1D8A081);
    EXPECT_EQ(cpu.get_esi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0xCF8765F2);
    EXPECT_EQ(cpu.get_ebp(), 0xCD2D645A);
    EXPECT_EQ(cpu.get_esp(), 0x000081D2);
    EXPECT_EQ(cpu.get_cs(), 0x00008414);
    EXPECT_EQ(cpu.get_ds(), 0x00009993);
    EXPECT_EQ(cpu.get_es(), 0x000001BE);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00009C69);
    EXPECT_EQ(cpu.get_ss(), 0x000005ED);
    EXPECT_EQ(cpu.get_eip(), 0x000059F3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0816);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0E0A6), 0x16);
    EXPECT_EQ(memory.load8(0x0E0A7), 0x08);
    EXPECT_EQ(memory.load8(0x0E0A4), 0x98);
    EXPECT_EQ(memory.load8(0x0E0A5), 0xFC);
    EXPECT_EQ(memory.load8(0x0E0A2), 0x18);
    EXPECT_EQ(memory.load8(0x0E0A3), 0xDD);
}

//
// bt [ds:ebx-FCD7h],esp
//
TEST_F(Test386, bt_ds_ebx_FCD7h_esp_batch20)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2444B721);
    cpu.set_ebx(0x0000F58C);
    cpu.set_ecx(0x7FFFFFFF);
    cpu.set_edx(0xA2443DB5);
    cpu.set_esi(0x00001001);
    cpu.set_edi(0x21DE94FF);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x000070C0);
    cpu.set_cs(0x00000AEA);
    cpu.set_ds(0x00007A80);
    cpu.set_es(0x0000793D);
    cpu.set_fs(0x000069F6);
    cpu.set_gs(0x0000BCAD);
    cpu.set_ss(0x0000164C);
    cpu.set_eip(0x0000CED8);
    cpu.set_eflags(0xFFFC0083);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x17D78, 0x66);
    machine.mem_store_byte(0x17D79, 0x67);
    machine.mem_store_byte(0x17D7A, 0x0F);
    machine.mem_store_byte(0x17D7B, 0xA3);
    machine.mem_store_byte(0x17D7C, 0xA3);
    machine.mem_store_byte(0x17D7D, 0x29);
    machine.mem_store_byte(0x17D7E, 0x03);
    machine.mem_store_byte(0x17D7F, 0xFF);
    machine.mem_store_byte(0x17D80, 0xFF);
    machine.mem_store_byte(0x17D81, 0xF4);
    machine.mem_store_byte(0x17D82, 0x56);
    machine.mem_store_byte(0x17D83, 0xB3);
    machine.mem_store_byte(0x17D84, 0xBD);
    machine.mem_store_byte(0x17D85, 0x4E);
    machine.mem_store_byte(0x17D86, 0xAD);
    machine.mem_store_byte(0x17D87, 0x8F);
    machine.mem_store_byte(0x17D88, 0x2A);
    machine.mem_store_byte(0x17D89, 0x3F);
    machine.mem_store_byte(0x17D8A, 0xCB);
    machine.mem_store_byte(0x17D8B, 0xFA);
    machine.mem_store_byte(0x17D8C, 0x3A);
    machine.mem_store_byte(0x17D8D, 0x7A);
    machine.mem_store_byte(0x7AED0, 0x7B);
    machine.mem_store_byte(0x7AECD, 0x77);
    machine.mem_store_byte(0x7AECE, 0xF6);
    machine.mem_store_byte(0x7AECF, 0x32);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x2444B721);
    EXPECT_EQ(cpu.get_ebx(), 0x0000F58C);
    EXPECT_EQ(cpu.get_ecx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xA2443DB5);
    EXPECT_EQ(cpu.get_esi(), 0x00001001);
    EXPECT_EQ(cpu.get_edi(), 0x21DE94FF);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x000070C0);
    EXPECT_EQ(cpu.get_cs(), 0x00000AEA);
    EXPECT_EQ(cpu.get_ds(), 0x00007A80);
    EXPECT_EQ(cpu.get_es(), 0x0000793D);
    EXPECT_EQ(cpu.get_fs(), 0x000069F6);
    EXPECT_EQ(cpu.get_gs(), 0x0000BCAD);
    EXPECT_EQ(cpu.get_ss(), 0x0000164C);
    EXPECT_EQ(cpu.get_eip(), 0x0000CEE2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0883);

    // Final RAM entries
}

//
// bt [ds:ebx-FCD7h],sp
//
TEST_F(Test386, bt_ds_ebx_FCD7h_sp_batch20)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2444B721);
    cpu.set_ebx(0x0000F58C);
    cpu.set_ecx(0x7FFFFFFF);
    cpu.set_edx(0xA2443DB5);
    cpu.set_esi(0x00001001);
    cpu.set_edi(0x21DE94FF);
    cpu.set_ebp(0x00000001);
    cpu.set_esp(0x000070C0);
    cpu.set_cs(0x00000AEA);
    cpu.set_ds(0x00007A80);
    cpu.set_es(0x0000793D);
    cpu.set_fs(0x000069F6);
    cpu.set_gs(0x0000BCAD);
    cpu.set_ss(0x0000164C);
    cpu.set_eip(0x0000CED8);
    cpu.set_eflags(0xFFFC0083);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x17D78, 0x67);
    machine.mem_store_byte(0x17D79, 0x0F);
    machine.mem_store_byte(0x17D7A, 0xA3);
    machine.mem_store_byte(0x17D7B, 0xA3);
    machine.mem_store_byte(0x17D7C, 0x29);
    machine.mem_store_byte(0x17D7D, 0x03);
    machine.mem_store_byte(0x17D7E, 0xFF);
    machine.mem_store_byte(0x17D7F, 0xFF);
    machine.mem_store_byte(0x17D80, 0xF4);
    machine.mem_store_byte(0x17D81, 0x6F);
    machine.mem_store_byte(0x17D82, 0x56);
    machine.mem_store_byte(0x17D83, 0xB3);
    machine.mem_store_byte(0x17D84, 0xBD);
    machine.mem_store_byte(0x17D85, 0x4E);
    machine.mem_store_byte(0x17D86, 0xAD);
    machine.mem_store_byte(0x17D87, 0x8F);
    machine.mem_store_byte(0x17D88, 0x2A);
    machine.mem_store_byte(0x17D89, 0x3F);
    machine.mem_store_byte(0x7AECD, 0x77);
    machine.mem_store_byte(0x7AECE, 0xF6);
    machine.mem_store_byte(0x17D8A, 0xCB);
    machine.mem_store_byte(0x17D8B, 0xFA);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x2444B721);
    EXPECT_EQ(cpu.get_ebx(), 0x0000F58C);
    EXPECT_EQ(cpu.get_ecx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xA2443DB5);
    EXPECT_EQ(cpu.get_esi(), 0x00001001);
    EXPECT_EQ(cpu.get_edi(), 0x21DE94FF);
    EXPECT_EQ(cpu.get_ebp(), 0x00000001);
    EXPECT_EQ(cpu.get_esp(), 0x000070C0);
    EXPECT_EQ(cpu.get_cs(), 0x00000AEA);
    EXPECT_EQ(cpu.get_ds(), 0x00007A80);
    EXPECT_EQ(cpu.get_es(), 0x0000793D);
    EXPECT_EQ(cpu.get_fs(), 0x000069F6);
    EXPECT_EQ(cpu.get_gs(), 0x0000BCAD);
    EXPECT_EQ(cpu.get_ss(), 0x0000164C);
    EXPECT_EQ(cpu.get_eip(), 0x0000CEE1);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0083);

    // Final RAM entries
}

//
// das
//
TEST_F(Test386, das_batch20)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00040001);
    cpu.set_ebx(0x031918BB);
    cpu.set_ecx(0xFE32C344);
    cpu.set_edx(0x000000D0);
    cpu.set_esi(0x3F2FD13A);
    cpu.set_edi(0xB228358B);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x000028F8);
    cpu.set_cs(0x0000FF8C);
    cpu.set_ds(0x00000001);
    cpu.set_es(0x00008310);
    cpu.set_fs(0x0000DA87);
    cpu.set_gs(0x0000DF2F);
    cpu.set_ss(0x0000FE33);
    cpu.set_eip(0x0000DDD0);
    cpu.set_eflags(0xFFFC04D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10D690, 0x2F);
    machine.mem_store_byte(0x10D691, 0xF4);
    machine.mem_store_byte(0x10D692, 0xF1);
    machine.mem_store_byte(0x10D693, 0x96);
    machine.mem_store_byte(0x10D694, 0x3B);
    machine.mem_store_byte(0x10D695, 0x03);
    machine.mem_store_byte(0x10D696, 0xB6);
    machine.mem_store_byte(0x10D697, 0xA3);
    machine.mem_store_byte(0x10D698, 0x02);
    machine.mem_store_byte(0x10D699, 0x81);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x000400FB);
    EXPECT_EQ(cpu.get_ebx(), 0x031918BB);
    EXPECT_EQ(cpu.get_ecx(), 0xFE32C344);
    EXPECT_EQ(cpu.get_edx(), 0x000000D0);
    EXPECT_EQ(cpu.get_esi(), 0x3F2FD13A);
    EXPECT_EQ(cpu.get_edi(), 0xB228358B);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x000028F8);
    EXPECT_EQ(cpu.get_cs(), 0x0000FF8C);
    EXPECT_EQ(cpu.get_ds(), 0x00000001);
    EXPECT_EQ(cpu.get_es(), 0x00008310);
    EXPECT_EQ(cpu.get_fs(), 0x0000DA87);
    EXPECT_EQ(cpu.get_gs(), 0x0000DF2F);
    EXPECT_EQ(cpu.get_ss(), 0x0000FE33);
    EXPECT_EQ(cpu.get_eip(), 0x0000DDD2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
}

//
// popfd
//
TEST_F(Test386, popfd_batch20)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x000000C0);
    cpu.set_ebx(0x3831DD27);
    cpu.set_ecx(0x8ACF3557);
    cpu.set_edx(0x9ADF871E);
    cpu.set_esi(0x5C3DF4E5);
    cpu.set_edi(0xF0FA5B62);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x000042C1);
    cpu.set_ds(0x00000863);
    cpu.set_es(0x0000F66B);
    cpu.set_fs(0x00003037);
    cpu.set_gs(0x00006B04);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00004830);
    cpu.set_eflags(0xFFFC0C53);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x47440, 0x66);
    machine.mem_store_byte(0x47441, 0x9D);
    machine.mem_store_byte(0x47442, 0xF4);
    machine.mem_store_byte(0x47443, 0x24);
    machine.mem_store_byte(0x47444, 0x20);
    machine.mem_store_byte(0x47445, 0xE0);
    machine.mem_store_byte(0x47446, 0x1C);
    machine.mem_store_byte(0x47447, 0x5B);
    machine.mem_store_byte(0x47448, 0xFF);
    machine.mem_store_byte(0x47449, 0x39);
    machine.mem_store_byte(0x4744A, 0xA8);
    machine.mem_store_byte(0x4744B, 0xD4);
    machine.mem_store_byte(0x4744C, 0x78);
    machine.mem_store_byte(0x4744D, 0xB5);
    machine.mem_store_byte(0x4744E, 0xF7);
    machine.mem_store_byte(0x4744F, 0x9B);
    machine.mem_store_byte(0x00030, 0x1A);
    machine.mem_store_byte(0x00031, 0x6B);
    machine.mem_store_byte(0x00032, 0xCF);
    machine.mem_store_byte(0x00033, 0x98);
    machine.mem_store_byte(0x9F80A, 0xF4);
    machine.mem_store_byte(0x9F80B, 0xF7);
    machine.mem_store_byte(0x9F80C, 0xF4);
    machine.mem_store_byte(0x9F80D, 0x76);
    machine.mem_store_byte(0x9F80E, 0xF4);
    machine.mem_store_byte(0x9F80F, 0x32);
    machine.mem_store_byte(0x9F810, 0xF4);
    machine.mem_store_byte(0x9F811, 0xCE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x000000C0);
    EXPECT_EQ(cpu.get_ebx(), 0x3831DD27);
    EXPECT_EQ(cpu.get_ecx(), 0x8ACF3557);
    EXPECT_EQ(cpu.get_edx(), 0x9ADF871E);
    EXPECT_EQ(cpu.get_esi(), 0x5C3DF4E5);
    EXPECT_EQ(cpu.get_edi(), 0xF0FA5B62);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x000098CF);
    EXPECT_EQ(cpu.get_ds(), 0x00000863);
    EXPECT_EQ(cpu.get_es(), 0x0000F66B);
    EXPECT_EQ(cpu.get_fs(), 0x00003037);
    EXPECT_EQ(cpu.get_gs(), 0x00006B04);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x00006B1B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C53);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0FFFC), 0x53);
    EXPECT_EQ(memory.load8(0x0FFFD), 0x0C);
    EXPECT_EQ(memory.load8(0x0FFFA), 0xC1);
    EXPECT_EQ(memory.load8(0x0FFFB), 0x42);
    EXPECT_EQ(memory.load8(0x0FFF8), 0x30);
    EXPECT_EQ(memory.load8(0x0FFF9), 0x48);
}

//
// retf 6548h
//
TEST_F(Test386, retf_6548h_batch20)
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
    machine.mem_store_byte(0xC65E8, 0xCA);
    machine.mem_store_byte(0xC65E9, 0x48);
    machine.mem_store_byte(0xC65EA, 0x65);
    machine.mem_store_byte(0xC65EB, 0xF4);
    machine.mem_store_byte(0xC65EC, 0x61);
    machine.mem_store_byte(0xC65ED, 0xBC);
    machine.mem_store_byte(0xC65EE, 0xD6);
    machine.mem_store_byte(0xC65EF, 0x67);
    machine.mem_store_byte(0x00030, 0xD5);
    machine.mem_store_byte(0x00031, 0xE3);
    machine.mem_store_byte(0x00032, 0x8B);
    machine.mem_store_byte(0x00033, 0xB0);
    machine.mem_store_byte(0xBEC84, 0xF4);
    machine.mem_store_byte(0xBEC85, 0xF4);
    machine.mem_store_byte(0xBEC86, 0xB5);
    machine.mem_store_byte(0xBEC87, 0xF4);
    machine.mem_store_byte(0xBEC88, 0x75);
    machine.mem_store_byte(0xBEC89, 0xF4);
    machine.mem_store_byte(0xBEC8A, 0xA3);
    machine.mem_store_byte(0xBEC8B, 0xF4);
    machine.mem_store_byte(0xBEC8C, 0x60);
    machine.mem_store_byte(0xBEC8D, 0xF4);

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
    EXPECT_EQ(cpu.get_cs(), 0x0000B08B);
    EXPECT_EQ(cpu.get_ds(), 0x00001AAC);
    EXPECT_EQ(cpu.get_es(), 0x000000D0);
    EXPECT_EQ(cpu.get_fs(), 0x00002570);
    EXPECT_EQ(cpu.get_gs(), 0x00005A61);
    EXPECT_EQ(cpu.get_ss(), 0x0000D61E);
    EXPECT_EQ(cpu.get_eip(), 0x0000E3D6);
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
// rol byte [ss:bp+di+408Dh],cl
//
TEST_F(Test386, rol_byte_ss_bp_di_408Dh_cl_batch20)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x8C63545C);
    cpu.set_ebx(0x00000000);
    cpu.set_ecx(0x2F965E38);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xD95F5C07);
    cpu.set_edi(0x0FF614FC);
    cpu.set_ebp(0x434D07F1);
    cpu.set_esp(0x00008C22);
    cpu.set_cs(0x000013E0);
    cpu.set_ds(0x00000357);
    cpu.set_es(0x00000C12);
    cpu.set_fs(0x0000D142);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x00006549);
    cpu.set_eip(0x0000DC88);
    cpu.set_eflags(0xFFFC0406);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x21A88, 0xD2);
    machine.mem_store_byte(0x21A89, 0x83);
    machine.mem_store_byte(0x21A8A, 0x8D);
    machine.mem_store_byte(0x21A8B, 0x40);
    machine.mem_store_byte(0x21A8C, 0xF4);
    machine.mem_store_byte(0x21A8D, 0x79);
    machine.mem_store_byte(0x21A8E, 0x0C);
    machine.mem_store_byte(0x21A8F, 0xC4);
    machine.mem_store_byte(0x21A90, 0xD2);
    machine.mem_store_byte(0x21A91, 0x34);
    machine.mem_store_byte(0x6B20A, 0x81);
    machine.mem_store_byte(0x21A92, 0x32);
    machine.mem_store_byte(0x21A93, 0xE0);
    machine.mem_store_byte(0x21A94, 0x67);
    machine.mem_store_byte(0x21A95, 0x71);
    machine.mem_store_byte(0x21A96, 0x2E);
    machine.mem_store_byte(0x21A97, 0x93);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x8C63545C);
    EXPECT_EQ(cpu.get_ebx(), 0x00000000);
    EXPECT_EQ(cpu.get_ecx(), 0x2F965E38);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xD95F5C07);
    EXPECT_EQ(cpu.get_edi(), 0x0FF614FC);
    EXPECT_EQ(cpu.get_ebp(), 0x434D07F1);
    EXPECT_EQ(cpu.get_esp(), 0x00008C22);
    EXPECT_EQ(cpu.get_cs(), 0x000013E0);
    EXPECT_EQ(cpu.get_ds(), 0x00000357);
    EXPECT_EQ(cpu.get_es(), 0x00000C12);
    EXPECT_EQ(cpu.get_fs(), 0x0000D142);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x00006549);
    EXPECT_EQ(cpu.get_eip(), 0x0000DC8D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0407);

    // Final RAM entries
}
