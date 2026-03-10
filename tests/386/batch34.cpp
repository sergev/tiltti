#include "test386.h"

//
// a32 lock repne outsd
//
TEST_F(Test386, a32_lock_repne_outsd_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x000000B1);
    cpu.set_ebx(0x09958025);
    cpu.set_ecx(0x00000019);
    cpu.set_edx(0xFFFFFFFF);
    cpu.set_esi(0x00003019);
    cpu.set_edi(0xFF92951D);
    cpu.set_ebp(0xFF32545B);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x00001046);
    cpu.set_ds(0x000066A5);
    cpu.set_es(0x0000A2EE);
    cpu.set_fs(0x0000E28C);
    cpu.set_gs(0x00000D16);
    cpu.set_ss(0x0000BCC1);
    cpu.set_eip(0x0000D278);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1D6D8, 0xF2);
    machine.mem_store_byte(0x1D6D9, 0xF0);
    machine.mem_store_byte(0x1D6DA, 0x67);
    machine.mem_store_byte(0x1D6DB, 0x66);
    machine.mem_store_byte(0x1D6DC, 0x6F);
    machine.mem_store_byte(0x1D6DD, 0xF4);
    machine.mem_store_byte(0x1D6DE, 0x20);
    machine.mem_store_byte(0x1D6DF, 0x67);
    machine.mem_store_byte(0x1D6E0, 0x45);
    machine.mem_store_byte(0x1D6E1, 0x9F);
    machine.mem_store_byte(0x1D6E2, 0xCC);
    machine.mem_store_byte(0x1D6E3, 0x81);
    machine.mem_store_byte(0x00018, 0x40);
    machine.mem_store_byte(0x00019, 0xDC);
    machine.mem_store_byte(0x0001A, 0x08);
    machine.mem_store_byte(0x0001B, 0xF3);
    machine.mem_store_byte(0x100CC0, 0xF4);
    machine.mem_store_byte(0x100CC1, 0xF0);
    machine.mem_store_byte(0x100CC2, 0xF4);
    machine.mem_store_byte(0x100CC3, 0x1D);
    machine.mem_store_byte(0x100CC4, 0xF4);
    machine.mem_store_byte(0x100CC5, 0x3C);
    machine.mem_store_byte(0x100CC6, 0xF4);
    machine.mem_store_byte(0x100CC7, 0xEF);
    machine.mem_store_byte(0x100CC8, 0xF4);
    machine.mem_store_byte(0x100CC9, 0xFE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x000000B1);
    EXPECT_EQ(cpu.get_ebx(), 0x09958025);
    EXPECT_EQ(cpu.get_ecx(), 0x00000019);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0x00003019);
    EXPECT_EQ(cpu.get_edi(), 0xFF92951D);
    EXPECT_EQ(cpu.get_ebp(), 0xFF32545B);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x0000F308);
    EXPECT_EQ(cpu.get_ds(), 0x000066A5);
    EXPECT_EQ(cpu.get_es(), 0x0000A2EE);
    EXPECT_EQ(cpu.get_fs(), 0x0000E28C);
    EXPECT_EQ(cpu.get_gs(), 0x00000D16);
    EXPECT_EQ(cpu.get_ss(), 0x0000BCC1);
    EXPECT_EQ(cpu.get_eip(), 0x0000DC41);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCCC0C), 0x17);
    EXPECT_EQ(memory.load8(0xCCC0D), 0x04);
    EXPECT_EQ(memory.load8(0xCCC0A), 0x46);
    EXPECT_EQ(memory.load8(0xCCC0B), 0x10);
    EXPECT_EQ(memory.load8(0xCCC08), 0x78);
    EXPECT_EQ(memory.load8(0xCCC09), 0xD2);
}

//
// a32 lock repne outsw
//
TEST_F(Test386, a32_lock_repne_outsw_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x014E77C1);
    cpu.set_ebx(0x48806E61);
    cpu.set_ecx(0x00000002);
    cpu.set_edx(0x0BFF1890);
    cpu.set_esi(0x0000D091);
    cpu.set_edi(0x000FFFFF);
    cpu.set_ebp(0x94314270);
    cpu.set_esp(0x00004FE2);
    cpu.set_cs(0x0000D4DC);
    cpu.set_ds(0x0000CCA8);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x0000F129);
    cpu.set_gs(0x00000DF5);
    cpu.set_ss(0x0000DCB6);
    cpu.set_eip(0x0000BFF8);
    cpu.set_eflags(0xFFFC0887);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE0DB8, 0xF2);
    machine.mem_store_byte(0xE0DB9, 0xF0);
    machine.mem_store_byte(0xE0DBA, 0x67);
    machine.mem_store_byte(0xE0DBB, 0x6F);
    machine.mem_store_byte(0xE0DBC, 0xF4);
    machine.mem_store_byte(0xE0DBD, 0xDD);
    machine.mem_store_byte(0xE0DBE, 0x61);
    machine.mem_store_byte(0xE0DBF, 0xE0);
    machine.mem_store_byte(0xE0DC0, 0xB8);
    machine.mem_store_byte(0xE0DC1, 0x3A);
    machine.mem_store_byte(0xE0DC2, 0xD9);
    machine.mem_store_byte(0xE0DC3, 0x0C);
    machine.mem_store_byte(0x00018, 0x40);
    machine.mem_store_byte(0x00019, 0xDC);
    machine.mem_store_byte(0x0001A, 0x08);
    machine.mem_store_byte(0x0001B, 0xF3);
    machine.mem_store_byte(0x100CC0, 0xF4);
    machine.mem_store_byte(0x100CC1, 0xF0);
    machine.mem_store_byte(0x100CC2, 0xF4);
    machine.mem_store_byte(0x100CC3, 0x1D);
    machine.mem_store_byte(0x100CC4, 0xF4);
    machine.mem_store_byte(0x100CC5, 0x3C);
    machine.mem_store_byte(0x100CC6, 0xF4);
    machine.mem_store_byte(0x100CC7, 0xEF);
    machine.mem_store_byte(0x100CC8, 0xF4);
    machine.mem_store_byte(0x100CC9, 0xFE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x014E77C1);
    EXPECT_EQ(cpu.get_ebx(), 0x48806E61);
    EXPECT_EQ(cpu.get_ecx(), 0x00000002);
    EXPECT_EQ(cpu.get_edx(), 0x0BFF1890);
    EXPECT_EQ(cpu.get_esi(), 0x0000D091);
    EXPECT_EQ(cpu.get_edi(), 0x000FFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x94314270);
    EXPECT_EQ(cpu.get_esp(), 0x00004FDC);
    EXPECT_EQ(cpu.get_cs(), 0x0000F308);
    EXPECT_EQ(cpu.get_ds(), 0x0000CCA8);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000F129);
    EXPECT_EQ(cpu.get_gs(), 0x00000DF5);
    EXPECT_EQ(cpu.get_ss(), 0x0000DCB6);
    EXPECT_EQ(cpu.get_eip(), 0x0000DC41);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE1B40), 0x87);
    EXPECT_EQ(memory.load8(0xE1B41), 0x08);
    EXPECT_EQ(memory.load8(0xE1B3E), 0xDC);
    EXPECT_EQ(memory.load8(0xE1B3F), 0xD4);
    EXPECT_EQ(memory.load8(0xE1B3C), 0xF8);
    EXPECT_EQ(memory.load8(0xE1B3D), 0xBF);
}

//
// div ah
//
TEST_F(Test386, div_ah_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xC95D511E);
    cpu.set_ebx(0x8341D392);
    cpu.set_ecx(0xE67BFAB1);
    cpu.set_edx(0x000FB93B);
    cpu.set_esi(0x955003D2);
    cpu.set_edi(0xB2408282);
    cpu.set_ebp(0x4BA0CA6B);
    cpu.set_esp(0x0000E510);
    cpu.set_cs(0x0000058A);
    cpu.set_ds(0x00001F21);
    cpu.set_es(0x0000EC85);
    cpu.set_fs(0x00000FD6);
    cpu.set_gs(0x0000FF06);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000FC38);
    cpu.set_eflags(0xFFFC00C7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x154D8, 0xF6);
    machine.mem_store_byte(0x154D9, 0xF4);
    machine.mem_store_byte(0x154DA, 0xF4);
    machine.mem_store_byte(0x154DB, 0x46);
    machine.mem_store_byte(0x154DC, 0x06);
    machine.mem_store_byte(0x154DD, 0xDB);
    machine.mem_store_byte(0x154DE, 0x94);
    machine.mem_store_byte(0x154DF, 0xBF);
    machine.mem_store_byte(0x154E0, 0x1C);
    machine.mem_store_byte(0x154E1, 0xB5);
    machine.mem_store_byte(0x154E2, 0xB2);
    machine.mem_store_byte(0x154E3, 0x31);
    machine.mem_store_byte(0x154E4, 0x61);
    machine.mem_store_byte(0x154E5, 0x2A);
    machine.mem_store_byte(0x154E6, 0x2E);
    machine.mem_store_byte(0x154E7, 0x00);
    machine.mem_store_byte(0x00000, 0x57);
    machine.mem_store_byte(0x00001, 0x58);
    machine.mem_store_byte(0x00002, 0x65);
    machine.mem_store_byte(0x00003, 0xD2);
    machine.mem_store_byte(0xD7EA6, 0x0C);
    machine.mem_store_byte(0xD7EA7, 0xF4);
    machine.mem_store_byte(0xD7EA8, 0x21);
    machine.mem_store_byte(0xD7EA9, 0xF4);
    machine.mem_store_byte(0xD7EAA, 0x69);
    machine.mem_store_byte(0xD7EAB, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xC95D511E);
    EXPECT_EQ(cpu.get_ebx(), 0x8341D392);
    EXPECT_EQ(cpu.get_ecx(), 0xE67BFAB1);
    EXPECT_EQ(cpu.get_edx(), 0x000FB93B);
    EXPECT_EQ(cpu.get_esi(), 0x955003D2);
    EXPECT_EQ(cpu.get_edi(), 0xB2408282);
    EXPECT_EQ(cpu.get_ebp(), 0x4BA0CA6B);
    EXPECT_EQ(cpu.get_esp(), 0x0000E50A);
    EXPECT_EQ(cpu.get_cs(), 0x0000D265);
    EXPECT_EQ(cpu.get_ds(), 0x00001F21);
    EXPECT_EQ(cpu.get_es(), 0x0000EC85);
    EXPECT_EQ(cpu.get_fs(), 0x00000FD6);
    EXPECT_EQ(cpu.get_gs(), 0x0000FF06);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x00005858);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0E50E), 0x87);
    EXPECT_EQ(memory.load8(0x0E50F), 0x00);
    EXPECT_EQ(memory.load8(0x0E50C), 0x8A);
    EXPECT_EQ(memory.load8(0x0E50D), 0x05);
    EXPECT_EQ(memory.load8(0x0E50A), 0x38);
    EXPECT_EQ(memory.load8(0x0E50B), 0xFC);
}

//
// idiv bx
//
TEST_F(Test386, idiv_bx_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDE255FE5);
    cpu.set_ebx(0xD6202C0F);
    cpu.set_ecx(0x0E9BA616);
    cpu.set_edx(0x48C9D278);
    cpu.set_esi(0x00008000);
    cpu.set_edi(0xFF8E4CAD);
    cpu.set_ebp(0x4B47E83C);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00001AFA);
    cpu.set_es(0x0000578C);
    cpu.set_fs(0x0000F954);
    cpu.set_gs(0x00001E80);
    cpu.set_ss(0x00009FC4);
    cpu.set_eip(0x0000A298);
    cpu.set_eflags(0xFFFC0C82);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10A288, 0xF7);
    machine.mem_store_byte(0x10A289, 0xFB);
    machine.mem_store_byte(0x10A28A, 0xF4);
    machine.mem_store_byte(0x10A28B, 0xC5);
    machine.mem_store_byte(0x10A28C, 0x51);
    machine.mem_store_byte(0x10A28D, 0xFE);
    machine.mem_store_byte(0x10A28E, 0xCE);
    machine.mem_store_byte(0x10A28F, 0xA9);
    machine.mem_store_byte(0x10A290, 0xF6);
    machine.mem_store_byte(0x10A291, 0xAD);
    machine.mem_store_byte(0x10A292, 0x5E);
    machine.mem_store_byte(0x10A293, 0x38);
    machine.mem_store_byte(0x10A294, 0x53);
    machine.mem_store_byte(0x10A295, 0xC8);
    machine.mem_store_byte(0x10A296, 0xF4);
    machine.mem_store_byte(0x10A297, 0x25);
    machine.mem_store_byte(0x00000, 0x1A);
    machine.mem_store_byte(0x00001, 0x0E);
    machine.mem_store_byte(0x00002, 0xE6);
    machine.mem_store_byte(0x00003, 0xE2);
    machine.mem_store_byte(0xE3C7A, 0xF4);
    machine.mem_store_byte(0xE3C7B, 0x29);
    machine.mem_store_byte(0xE3C7C, 0xF4);
    machine.mem_store_byte(0xE3C7D, 0xCE);
    machine.mem_store_byte(0xE3C7E, 0xF4);
    machine.mem_store_byte(0xE3C7F, 0xAE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDE255FE5);
    EXPECT_EQ(cpu.get_ebx(), 0xD6202C0F);
    EXPECT_EQ(cpu.get_ecx(), 0x0E9BA616);
    EXPECT_EQ(cpu.get_edx(), 0x48C9D278);
    EXPECT_EQ(cpu.get_esi(), 0x00008000);
    EXPECT_EQ(cpu.get_edi(), 0xFF8E4CAD);
    EXPECT_EQ(cpu.get_ebp(), 0x4B47E83C);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x0000E2E6);
    EXPECT_EQ(cpu.get_ds(), 0x00001AFA);
    EXPECT_EQ(cpu.get_es(), 0x0000578C);
    EXPECT_EQ(cpu.get_fs(), 0x0000F954);
    EXPECT_EQ(cpu.get_gs(), 0x00001E80);
    EXPECT_EQ(cpu.get_ss(), 0x00009FC4);
    EXPECT_EQ(cpu.get_eip(), 0x00000E1B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9FC46), 0x17);
    EXPECT_EQ(memory.load8(0x9FC47), 0x04);
    EXPECT_EQ(memory.load8(0x9FC44), 0xFF);
    EXPECT_EQ(memory.load8(0x9FC45), 0xFF);
    EXPECT_EQ(memory.load8(0x9FC42), 0x98);
    EXPECT_EQ(memory.load8(0x9FC43), 0xA2);
}

//
// idiv ebx
//
TEST_F(Test386, idiv_ebx_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDE255FE5);
    cpu.set_ebx(0xD6202C0F);
    cpu.set_ecx(0x0E9BA616);
    cpu.set_edx(0x48C9D278);
    cpu.set_esi(0x00008000);
    cpu.set_edi(0xFF8E4CAD);
    cpu.set_ebp(0x4B47E83C);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x00001AFA);
    cpu.set_es(0x0000578C);
    cpu.set_fs(0x0000F954);
    cpu.set_gs(0x00001E80);
    cpu.set_ss(0x00009FC4);
    cpu.set_eip(0x0000A298);
    cpu.set_eflags(0xFFFC0C82);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10A288, 0x67);
    machine.mem_store_byte(0x10A289, 0x66);
    machine.mem_store_byte(0x10A28A, 0xF7);
    machine.mem_store_byte(0x10A28B, 0xFB);
    machine.mem_store_byte(0x10A28C, 0xF4);
    machine.mem_store_byte(0x10A28D, 0xFE);
    machine.mem_store_byte(0x10A28E, 0xCE);
    machine.mem_store_byte(0x10A28F, 0xA9);
    machine.mem_store_byte(0x10A290, 0xF6);
    machine.mem_store_byte(0x10A291, 0xAD);
    machine.mem_store_byte(0x10A292, 0x5E);
    machine.mem_store_byte(0x10A293, 0x38);
    machine.mem_store_byte(0x10A294, 0x53);
    machine.mem_store_byte(0x10A295, 0xC8);
    machine.mem_store_byte(0x10A296, 0xF4);
    machine.mem_store_byte(0x10A297, 0x25);
    machine.mem_store_byte(0x10A298, 0x67);
    machine.mem_store_byte(0x10A299, 0xC6);
    machine.mem_store_byte(0x10A29A, 0x6B);
    machine.mem_store_byte(0x10A29B, 0xF9);
    machine.mem_store_byte(0x00000, 0x1A);
    machine.mem_store_byte(0x00001, 0x0E);
    machine.mem_store_byte(0x00002, 0xE6);
    machine.mem_store_byte(0x00003, 0xE2);
    machine.mem_store_byte(0xE3C7A, 0xF4);
    machine.mem_store_byte(0xE3C7B, 0x29);
    machine.mem_store_byte(0xE3C7C, 0xF4);
    machine.mem_store_byte(0xE3C7D, 0xCE);
    machine.mem_store_byte(0xE3C7E, 0xF4);
    machine.mem_store_byte(0xE3C7F, 0xAE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDE255FE5);
    EXPECT_EQ(cpu.get_ebx(), 0xD6202C0F);
    EXPECT_EQ(cpu.get_ecx(), 0x0E9BA616);
    EXPECT_EQ(cpu.get_edx(), 0x48C9D278);
    EXPECT_EQ(cpu.get_esi(), 0x00008000);
    EXPECT_EQ(cpu.get_edi(), 0xFF8E4CAD);
    EXPECT_EQ(cpu.get_ebp(), 0x4B47E83C);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x0000E2E6);
    EXPECT_EQ(cpu.get_ds(), 0x00001AFA);
    EXPECT_EQ(cpu.get_es(), 0x0000578C);
    EXPECT_EQ(cpu.get_fs(), 0x0000F954);
    EXPECT_EQ(cpu.get_gs(), 0x00001E80);
    EXPECT_EQ(cpu.get_ss(), 0x00009FC4);
    EXPECT_EQ(cpu.get_eip(), 0x00000E1B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9FC46), 0x96);
    EXPECT_EQ(memory.load8(0x9FC47), 0x04);
    EXPECT_EQ(memory.load8(0x9FC44), 0xFF);
    EXPECT_EQ(memory.load8(0x9FC45), 0xFF);
    EXPECT_EQ(memory.load8(0x9FC42), 0x98);
    EXPECT_EQ(memory.load8(0x9FC43), 0xA2);
}

//
// lock repne outsd
//
TEST_F(Test386, lock_repne_outsd_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x014E77C1);
    cpu.set_ebx(0x48806E61);
    cpu.set_ecx(0x00000002);
    cpu.set_edx(0x0BFF1890);
    cpu.set_esi(0x0936D091);
    cpu.set_edi(0x000FFFFF);
    cpu.set_ebp(0x94314270);
    cpu.set_esp(0x00004FE2);
    cpu.set_cs(0x0000D4DC);
    cpu.set_ds(0x0000CCA8);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x0000F129);
    cpu.set_gs(0x00000DF5);
    cpu.set_ss(0x0000DCB6);
    cpu.set_eip(0x0000BFF8);
    cpu.set_eflags(0xFFFC0887);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE0DB8, 0xF2);
    machine.mem_store_byte(0xE0DB9, 0xF0);
    machine.mem_store_byte(0xE0DBA, 0x66);
    machine.mem_store_byte(0xE0DBB, 0x6F);
    machine.mem_store_byte(0xE0DBC, 0xF4);
    machine.mem_store_byte(0xE0DBD, 0xDD);
    machine.mem_store_byte(0xE0DBE, 0x61);
    machine.mem_store_byte(0xE0DBF, 0xE0);
    machine.mem_store_byte(0xE0DC0, 0xB8);
    machine.mem_store_byte(0xE0DC1, 0x3A);
    machine.mem_store_byte(0xE0DC2, 0xD9);
    machine.mem_store_byte(0xE0DC3, 0x0C);
    machine.mem_store_byte(0x00018, 0x40);
    machine.mem_store_byte(0x00019, 0xDC);
    machine.mem_store_byte(0x0001A, 0x08);
    machine.mem_store_byte(0x0001B, 0xF3);
    machine.mem_store_byte(0x100CC0, 0xF4);
    machine.mem_store_byte(0x100CC1, 0xF0);
    machine.mem_store_byte(0x100CC2, 0xF4);
    machine.mem_store_byte(0x100CC3, 0x1D);
    machine.mem_store_byte(0x100CC4, 0xF4);
    machine.mem_store_byte(0x100CC5, 0x3C);
    machine.mem_store_byte(0x100CC6, 0xF4);
    machine.mem_store_byte(0x100CC7, 0xEF);
    machine.mem_store_byte(0x100CC8, 0xF4);
    machine.mem_store_byte(0x100CC9, 0xFE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x014E77C1);
    EXPECT_EQ(cpu.get_ebx(), 0x48806E61);
    EXPECT_EQ(cpu.get_ecx(), 0x00000002);
    EXPECT_EQ(cpu.get_edx(), 0x0BFF1890);
    EXPECT_EQ(cpu.get_esi(), 0x0936D091);
    EXPECT_EQ(cpu.get_edi(), 0x000FFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x94314270);
    EXPECT_EQ(cpu.get_esp(), 0x00004FDC);
    EXPECT_EQ(cpu.get_cs(), 0x0000F308);
    EXPECT_EQ(cpu.get_ds(), 0x0000CCA8);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000F129);
    EXPECT_EQ(cpu.get_gs(), 0x00000DF5);
    EXPECT_EQ(cpu.get_ss(), 0x0000DCB6);
    EXPECT_EQ(cpu.get_eip(), 0x0000DC41);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE1B40), 0x87);
    EXPECT_EQ(memory.load8(0xE1B41), 0x08);
    EXPECT_EQ(memory.load8(0xE1B3E), 0xDC);
    EXPECT_EQ(memory.load8(0xE1B3F), 0xD4);
    EXPECT_EQ(memory.load8(0xE1B3C), 0xF8);
    EXPECT_EQ(memory.load8(0xE1B3D), 0xBF);
}

//
// lock repne outsw
//
TEST_F(Test386, lock_repne_outsw_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x014E77C1);
    cpu.set_ebx(0x48806E61);
    cpu.set_ecx(0x00000002);
    cpu.set_edx(0x0BFF1890);
    cpu.set_esi(0x0936D091);
    cpu.set_edi(0x000FFFFF);
    cpu.set_ebp(0x94314270);
    cpu.set_esp(0x00004FE2);
    cpu.set_cs(0x0000D4DC);
    cpu.set_ds(0x0000CCA8);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x0000F129);
    cpu.set_gs(0x00000DF5);
    cpu.set_ss(0x0000DCB6);
    cpu.set_eip(0x0000BFF8);
    cpu.set_eflags(0xFFFC0887);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE0DB8, 0xF2);
    machine.mem_store_byte(0xE0DB9, 0xF0);
    machine.mem_store_byte(0xE0DBA, 0x6F);
    machine.mem_store_byte(0xE0DBB, 0xF4);
    machine.mem_store_byte(0xE0DBC, 0x26);
    machine.mem_store_byte(0xE0DBD, 0xDD);
    machine.mem_store_byte(0xE0DBE, 0x61);
    machine.mem_store_byte(0xE0DBF, 0xE0);
    machine.mem_store_byte(0xE0DC0, 0xB8);
    machine.mem_store_byte(0xE0DC1, 0x3A);
    machine.mem_store_byte(0x00018, 0x40);
    machine.mem_store_byte(0x00019, 0xDC);
    machine.mem_store_byte(0x0001A, 0x08);
    machine.mem_store_byte(0x0001B, 0xF3);
    machine.mem_store_byte(0x100CC0, 0xF4);
    machine.mem_store_byte(0x100CC1, 0xF0);
    machine.mem_store_byte(0x100CC2, 0xF4);
    machine.mem_store_byte(0x100CC3, 0x1D);
    machine.mem_store_byte(0x100CC4, 0xF4);
    machine.mem_store_byte(0x100CC5, 0x3C);
    machine.mem_store_byte(0x100CC6, 0xF4);
    machine.mem_store_byte(0x100CC7, 0xEF);
    machine.mem_store_byte(0x100CC8, 0xF4);
    machine.mem_store_byte(0x100CC9, 0xFE);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x014E77C1);
    EXPECT_EQ(cpu.get_ebx(), 0x48806E61);
    EXPECT_EQ(cpu.get_ecx(), 0x00000002);
    EXPECT_EQ(cpu.get_edx(), 0x0BFF1890);
    EXPECT_EQ(cpu.get_esi(), 0x0936D091);
    EXPECT_EQ(cpu.get_edi(), 0x000FFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x94314270);
    EXPECT_EQ(cpu.get_esp(), 0x00004FDC);
    EXPECT_EQ(cpu.get_cs(), 0x0000F308);
    EXPECT_EQ(cpu.get_ds(), 0x0000CCA8);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000F129);
    EXPECT_EQ(cpu.get_gs(), 0x00000DF5);
    EXPECT_EQ(cpu.get_ss(), 0x0000DCB6);
    EXPECT_EQ(cpu.get_eip(), 0x0000DC41);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE1B40), 0x87);
    EXPECT_EQ(memory.load8(0xE1B41), 0x08);
    EXPECT_EQ(memory.load8(0xE1B3E), 0xDC);
    EXPECT_EQ(memory.load8(0xE1B3F), 0xD4);
    EXPECT_EQ(memory.load8(0xE1B3C), 0xF8);
    EXPECT_EQ(memory.load8(0xE1B3D), 0xBF);
}

//
// mul byte [ds:edx+eax*8+277h]
//
TEST_F(Test386, mul_byte_ds_edx_eax_8_277h_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x000001C3);
    cpu.set_ebx(0x65ACC794);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0x00000FFF);
    cpu.set_esi(0x700A2ADB);
    cpu.set_edi(0x00000001);
    cpu.set_ebp(0xD51C7A11);
    cpu.set_esp(0x0000FFF2);
    cpu.set_cs(0x0000C3C4);
    cpu.set_ds(0x0000257F);
    cpu.set_es(0x00005A5A);
    cpu.set_fs(0x00002001);
    cpu.set_gs(0x00009D1B);
    cpu.set_ss(0x00006204);
    cpu.set_eip(0x0000FFF8);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD3C38, 0x67);
    machine.mem_store_byte(0xD3C39, 0xF6);
    machine.mem_store_byte(0xD3C3A, 0xA4);
    machine.mem_store_byte(0xD3C3B, 0xC2);
    machine.mem_store_byte(0xD3C3C, 0x77);
    machine.mem_store_byte(0xD3C3D, 0x02);
    machine.mem_store_byte(0xD3C3E, 0x00);
    machine.mem_store_byte(0xD3C3F, 0x00);
    machine.mem_store_byte(0xD3C40, 0xF4);
    machine.mem_store_byte(0x2787E, 0xBE);
    machine.mem_store_byte(0x00034, 0x5C);
    machine.mem_store_byte(0x00035, 0x58);
    machine.mem_store_byte(0x00036, 0x28);
    machine.mem_store_byte(0x00037, 0xD9);
    machine.mem_store_byte(0xDEADC, 0xF4);
    machine.mem_store_byte(0xDEADD, 0x4B);
    machine.mem_store_byte(0xDEADE, 0xF4);
    machine.mem_store_byte(0xDEADF, 0x5A);
    machine.mem_store_byte(0xDEAE0, 0xF4);
    machine.mem_store_byte(0xDEAE1, 0xA6);
    machine.mem_store_byte(0xDEAE2, 0xF4);
    machine.mem_store_byte(0xDEAE3, 0x9B);
    machine.mem_store_byte(0xDEAE4, 0xF4);
    machine.mem_store_byte(0xDEAE5, 0xAC);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x000090BA);
    EXPECT_EQ(cpu.get_ebx(), 0x65ACC794);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x00000FFF);
    EXPECT_EQ(cpu.get_esi(), 0x700A2ADB);
    EXPECT_EQ(cpu.get_edi(), 0x00000001);
    EXPECT_EQ(cpu.get_ebp(), 0xD51C7A11);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFEC);
    EXPECT_EQ(cpu.get_cs(), 0x0000D928);
    EXPECT_EQ(cpu.get_ds(), 0x0000257F);
    EXPECT_EQ(cpu.get_es(), 0x00005A5A);
    EXPECT_EQ(cpu.get_fs(), 0x00002001);
    EXPECT_EQ(cpu.get_gs(), 0x00009D1B);
    EXPECT_EQ(cpu.get_ss(), 0x00006204);
    EXPECT_EQ(cpu.get_eip(), 0x0000585D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C17);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x72030, 0x17);
    EXPECT_FLAGS_HI(0x72031, 0x0C);
    EXPECT_EQ(memory.load8(0x7202E), 0xC4);
    EXPECT_EQ(memory.load8(0x7202F), 0xC3);
    EXPECT_EQ(memory.load8(0x7202C), 0x00);
    EXPECT_EQ(memory.load8(0x7202D), 0x00);
}

//
// rol bh,cl
//
TEST_F(Test386, rol_bh_cl_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFCB58DD2);
    cpu.set_ebx(0x3DE7AAFB);
    cpu.set_ecx(0x9FE95810);
    cpu.set_edx(0x62D11F2A);
    cpu.set_esi(0x2098D72C);
    cpu.set_edi(0x60E6A472);
    cpu.set_ebp(0x92E736BF);
    cpu.set_esp(0x000006B2);
    cpu.set_cs(0x00009B9D);
    cpu.set_ds(0x0000ECC1);
    cpu.set_es(0x000085E0);
    cpu.set_fs(0x00000232);
    cpu.set_gs(0x0000399E);
    cpu.set_ss(0x0000ECBD);
    cpu.set_eip(0x00006DE8);
    cpu.set_eflags(0xFFFC0443);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA27B8, 0x3E);
    machine.mem_store_byte(0xA27B9, 0x2E);
    machine.mem_store_byte(0xA27BA, 0xD2);
    machine.mem_store_byte(0xA27BB, 0xC7);
    machine.mem_store_byte(0xA27BC, 0xF4);
    machine.mem_store_byte(0xA27BD, 0x28);
    machine.mem_store_byte(0xA27BE, 0x05);
    machine.mem_store_byte(0xA27BF, 0x75);
    machine.mem_store_byte(0xA27C0, 0x51);
    machine.mem_store_byte(0xA27C1, 0x7B);
    machine.mem_store_byte(0xA27C2, 0xAC);
    machine.mem_store_byte(0xA27C3, 0xF1);
    machine.mem_store_byte(0xA27C4, 0x81);
    machine.mem_store_byte(0xA27C5, 0x06);
    machine.mem_store_byte(0xA27C6, 0x3A);
    machine.mem_store_byte(0xA27C7, 0x3A);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFCB58DD2);
    EXPECT_EQ(cpu.get_ebx(), 0x3DE7AAFB);
    EXPECT_EQ(cpu.get_ecx(), 0x9FE95810);
    EXPECT_EQ(cpu.get_edx(), 0x62D11F2A);
    EXPECT_EQ(cpu.get_esi(), 0x2098D72C);
    EXPECT_EQ(cpu.get_edi(), 0x60E6A472);
    EXPECT_EQ(cpu.get_ebp(), 0x92E736BF);
    EXPECT_EQ(cpu.get_esp(), 0x000006B2);
    EXPECT_EQ(cpu.get_cs(), 0x00009B9D);
    EXPECT_EQ(cpu.get_ds(), 0x0000ECC1);
    EXPECT_EQ(cpu.get_es(), 0x000085E0);
    EXPECT_EQ(cpu.get_fs(), 0x00000232);
    EXPECT_EQ(cpu.get_gs(), 0x0000399E);
    EXPECT_EQ(cpu.get_ss(), 0x0000ECBD);
    EXPECT_EQ(cpu.get_eip(), 0x00006DED);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C42);

    // Final RAM entries
}

//
// shrd [ss:eax+edx*2-308Bh],esi,60h
//
TEST_F(Test386, shrd_ss_eax_edx_2_308Bh_esi_60h_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00001C61);
    cpu.set_ebx(0x51330207);
    cpu.set_ecx(0x18A72671);
    cpu.set_edx(0x00000007);
    cpu.set_esi(0xC0EDC393);
    cpu.set_edi(0x922DC279);
    cpu.set_ebp(0x72A470C5);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000BE35);
    cpu.set_ds(0x00002C11);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x0000FCEA);
    cpu.set_gs(0x000070A3);
    cpu.set_ss(0x00000F54);
    cpu.set_eip(0x000000A8);
    cpu.set_eflags(0xFFFC0802);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBE3F8, 0x36);
    machine.mem_store_byte(0xBE3F9, 0x66);
    machine.mem_store_byte(0xBE3FA, 0x67);
    machine.mem_store_byte(0xBE3FB, 0x0F);
    machine.mem_store_byte(0xBE3FC, 0xAC);
    machine.mem_store_byte(0xBE3FD, 0xB4);
    machine.mem_store_byte(0xBE3FE, 0x50);
    machine.mem_store_byte(0xBE3FF, 0x75);
    machine.mem_store_byte(0xBE400, 0xCF);
    machine.mem_store_byte(0xBE401, 0xFF);
    machine.mem_store_byte(0xBE402, 0xFF);
    machine.mem_store_byte(0xBE403, 0x60);
    machine.mem_store_byte(0xBE404, 0xF4);
    machine.mem_store_byte(0xBE405, 0x65);
    machine.mem_store_byte(0xBE406, 0xD5);
    machine.mem_store_byte(0xBE407, 0x7D);
    machine.mem_store_byte(0xBE408, 0xC1);
    machine.mem_store_byte(0xBE409, 0x8C);
    machine.mem_store_byte(0xBE40A, 0x33);
    machine.mem_store_byte(0xBE40B, 0x20);
    machine.mem_store_byte(0xBE40C, 0x5E);
    machine.mem_store_byte(0xBE40D, 0x45);
    machine.mem_store_byte(0xBE40E, 0x9D);
    machine.mem_store_byte(0xBE40F, 0xCA);
    machine.mem_store_byte(0xBE410, 0x91);
    machine.mem_store_byte(0xBE411, 0x33);
    machine.mem_store_byte(0xBE412, 0x4A);
    machine.mem_store_byte(0xBE413, 0xBF);
    machine.mem_store_byte(0x00030, 0x96);
    machine.mem_store_byte(0x00031, 0x61);
    machine.mem_store_byte(0x00032, 0xBB);
    machine.mem_store_byte(0x00033, 0x86);
    machine.mem_store_byte(0x8CD46, 0xF4);
    machine.mem_store_byte(0x8CD47, 0xB7);
    machine.mem_store_byte(0x8CD48, 0xF4);
    machine.mem_store_byte(0x8CD49, 0x2D);
    machine.mem_store_byte(0x8CD4A, 0xF4);
    machine.mem_store_byte(0x8CD4B, 0x82);
    machine.mem_store_byte(0x8CD4C, 0xF4);
    machine.mem_store_byte(0x8CD4D, 0xD2);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001C61);
    EXPECT_EQ(cpu.get_ebx(), 0x51330207);
    EXPECT_EQ(cpu.get_ecx(), 0x18A72671);
    EXPECT_EQ(cpu.get_edx(), 0x00000007);
    EXPECT_EQ(cpu.get_esi(), 0xC0EDC393);
    EXPECT_EQ(cpu.get_edi(), 0x922DC279);
    EXPECT_EQ(cpu.get_ebp(), 0x72A470C5);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x000086BB);
    EXPECT_EQ(cpu.get_ds(), 0x00002C11);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000FCEA);
    EXPECT_EQ(cpu.get_gs(), 0x000070A3);
    EXPECT_EQ(cpu.get_ss(), 0x00000F54);
    EXPECT_EQ(cpu.get_eip(), 0x00006197);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0802);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1F53C), 0x02);
    EXPECT_EQ(memory.load8(0x1F53D), 0x08);
    EXPECT_EQ(memory.load8(0x1F53A), 0x35);
    EXPECT_EQ(memory.load8(0x1F53B), 0xBE);
    EXPECT_EQ(memory.load8(0x1F538), 0xA8);
    EXPECT_EQ(memory.load8(0x1F539), 0x00);
}

//
// shrd [ss:eax+edx*2-308Bh],si,60h
//
TEST_F(Test386, shrd_ss_eax_edx_2_308Bh_si_60h_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00001C61);
    cpu.set_ebx(0x51330207);
    cpu.set_ecx(0x18A72671);
    cpu.set_edx(0x00000007);
    cpu.set_esi(0xC0EDC393);
    cpu.set_edi(0x922DC279);
    cpu.set_ebp(0x72A470C5);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000BE35);
    cpu.set_ds(0x00002C11);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x0000FCEA);
    cpu.set_gs(0x000070A3);
    cpu.set_ss(0x00000F54);
    cpu.set_eip(0x000000A8);
    cpu.set_eflags(0xFFFC0802);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBE3F8, 0x36);
    machine.mem_store_byte(0xBE3F9, 0x67);
    machine.mem_store_byte(0xBE3FA, 0x0F);
    machine.mem_store_byte(0xBE3FB, 0xAC);
    machine.mem_store_byte(0xBE3FC, 0xB4);
    machine.mem_store_byte(0xBE3FD, 0x50);
    machine.mem_store_byte(0xBE3FE, 0x75);
    machine.mem_store_byte(0xBE3FF, 0xCF);
    machine.mem_store_byte(0xBE400, 0xFF);
    machine.mem_store_byte(0xBE401, 0xFF);
    machine.mem_store_byte(0xBE402, 0x60);
    machine.mem_store_byte(0xBE403, 0xF4);
    machine.mem_store_byte(0xBE404, 0x42);
    machine.mem_store_byte(0xBE405, 0x65);
    machine.mem_store_byte(0xBE406, 0xD5);
    machine.mem_store_byte(0xBE407, 0x7D);
    machine.mem_store_byte(0xBE408, 0xC1);
    machine.mem_store_byte(0xBE409, 0x8C);
    machine.mem_store_byte(0xBE40A, 0x33);
    machine.mem_store_byte(0xBE40B, 0x20);
    machine.mem_store_byte(0xBE40C, 0x5E);
    machine.mem_store_byte(0xBE40D, 0x45);
    machine.mem_store_byte(0xBE40E, 0x9D);
    machine.mem_store_byte(0xBE40F, 0xCA);
    machine.mem_store_byte(0x00030, 0x96);
    machine.mem_store_byte(0x00031, 0x61);
    machine.mem_store_byte(0x00032, 0xBB);
    machine.mem_store_byte(0x00033, 0x86);
    machine.mem_store_byte(0x8CD46, 0xF4);
    machine.mem_store_byte(0x8CD47, 0xB7);
    machine.mem_store_byte(0x8CD48, 0xF4);
    machine.mem_store_byte(0x8CD49, 0x2D);
    machine.mem_store_byte(0x8CD4A, 0xF4);
    machine.mem_store_byte(0x8CD4B, 0x82);
    machine.mem_store_byte(0x8CD4C, 0xF4);
    machine.mem_store_byte(0x8CD4D, 0xD2);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001C61);
    EXPECT_EQ(cpu.get_ebx(), 0x51330207);
    EXPECT_EQ(cpu.get_ecx(), 0x18A72671);
    EXPECT_EQ(cpu.get_edx(), 0x00000007);
    EXPECT_EQ(cpu.get_esi(), 0xC0EDC393);
    EXPECT_EQ(cpu.get_edi(), 0x922DC279);
    EXPECT_EQ(cpu.get_ebp(), 0x72A470C5);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x000086BB);
    EXPECT_EQ(cpu.get_ds(), 0x00002C11);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000FCEA);
    EXPECT_EQ(cpu.get_gs(), 0x000070A3);
    EXPECT_EQ(cpu.get_ss(), 0x00000F54);
    EXPECT_EQ(cpu.get_eip(), 0x00006197);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0802);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1F53C), 0x02);
    EXPECT_EQ(memory.load8(0x1F53D), 0x08);
    EXPECT_EQ(memory.load8(0x1F53A), 0x35);
    EXPECT_EQ(memory.load8(0x1F53B), 0xBE);
    EXPECT_EQ(memory.load8(0x1F538), 0xA8);
    EXPECT_EQ(memory.load8(0x1F539), 0x00);
}

//
// sub [ss:ecx+2514h],dl
//
TEST_F(Test386, sub_ss_ecx_2514h_dl_batch34)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA90BC8D2);
    cpu.set_ebx(0xE30BA7FD);
    cpu.set_ecx(0x0000E8A8);
    cpu.set_edx(0x00000080);
    cpu.set_esi(0x0000001C);
    cpu.set_edi(0x3CBF50AC);
    cpu.set_ebp(0x572BEADF);
    cpu.set_esp(0x00001A7A);
    cpu.set_cs(0x000001C9);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x0000144F);
    cpu.set_fs(0x00003DC8);
    cpu.set_gs(0x00000011);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x000096C8);
    cpu.set_eflags(0xFFFC0053);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0B358, 0x36);
    machine.mem_store_byte(0x0B359, 0x67);
    machine.mem_store_byte(0x0B35A, 0x28);
    machine.mem_store_byte(0x0B35B, 0x91);
    machine.mem_store_byte(0x0B35C, 0x14);
    machine.mem_store_byte(0x0B35D, 0x25);
    machine.mem_store_byte(0x0B35E, 0x00);
    machine.mem_store_byte(0x0B35F, 0x00);
    machine.mem_store_byte(0x0B360, 0xF4);
    machine.mem_store_byte(0x0B361, 0x95);
    machine.mem_store_byte(0x0B362, 0x78);
    machine.mem_store_byte(0x0B363, 0x77);
    machine.mem_store_byte(0x0B364, 0xC5);
    machine.mem_store_byte(0x0B365, 0x12);
    machine.mem_store_byte(0x0B366, 0xB0);
    machine.mem_store_byte(0x0B367, 0x4B);
    machine.mem_store_byte(0x0B368, 0x96);
    machine.mem_store_byte(0x0B369, 0x67);
    machine.mem_store_byte(0x0B36A, 0x71);
    machine.mem_store_byte(0x0B36B, 0xE6);
    machine.mem_store_byte(0x00030, 0xAE);
    machine.mem_store_byte(0x00031, 0xA8);
    machine.mem_store_byte(0x00032, 0x19);
    machine.mem_store_byte(0x00033, 0x56);
    machine.mem_store_byte(0x60A3E, 0xF4);
    machine.mem_store_byte(0x60A3F, 0xB3);
    machine.mem_store_byte(0x60A40, 0xF4);
    machine.mem_store_byte(0x60A41, 0x5F);
    machine.mem_store_byte(0x60A42, 0xF4);
    machine.mem_store_byte(0x60A43, 0x4A);
    machine.mem_store_byte(0x60A44, 0xF4);
    machine.mem_store_byte(0x60A45, 0xE2);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA90BC8D2);
    EXPECT_EQ(cpu.get_ebx(), 0xE30BA7FD);
    EXPECT_EQ(cpu.get_ecx(), 0x0000E8A8);
    EXPECT_EQ(cpu.get_edx(), 0x00000080);
    EXPECT_EQ(cpu.get_esi(), 0x0000001C);
    EXPECT_EQ(cpu.get_edi(), 0x3CBF50AC);
    EXPECT_EQ(cpu.get_ebp(), 0x572BEADF);
    EXPECT_EQ(cpu.get_esp(), 0x00001A74);
    EXPECT_EQ(cpu.get_cs(), 0x00005619);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x0000144F);
    EXPECT_EQ(cpu.get_fs(), 0x00003DC8);
    EXPECT_EQ(cpu.get_gs(), 0x00000011);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000A8AF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0053);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x01A78), 0x53);
    EXPECT_EQ(memory.load8(0x01A79), 0x00);
    EXPECT_EQ(memory.load8(0x01A76), 0xC9);
    EXPECT_EQ(memory.load8(0x01A77), 0x01);
    EXPECT_EQ(memory.load8(0x01A74), 0xC8);
    EXPECT_EQ(memory.load8(0x01A75), 0x96);
}
