#include "test386.h"

//
// div byte [ds:eax+edx*8+517h]
//
TEST_F(Test386, div_byte_ds_eax_edx_8_517h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x000000D2);
    cpu.set_ebx(0x00000001);
    cpu.set_ecx(0xD935A22C);
    cpu.set_edx(0x00000ECB);
    cpu.set_esi(0xD47140A3);
    cpu.set_edi(0xFF5807F8);
    cpu.set_ebp(0x5E4394D1);
    cpu.set_esp(0x0000C72A);
    cpu.set_cs(0x0000D53F);
    cpu.set_ds(0x0000B65A);
    cpu.set_es(0x00000DC3);
    cpu.set_fs(0x00004B97);
    cpu.set_gs(0x00007940);
    cpu.set_ss(0x00000014);
    cpu.set_eip(0x0000C268);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE1658, 0x67);
    machine.mem_store_byte(0xE1659, 0xF6);
    machine.mem_store_byte(0xE165A, 0xB4);
    machine.mem_store_byte(0xE165B, 0xD0);
    machine.mem_store_byte(0xE165C, 0x17);
    machine.mem_store_byte(0xE165D, 0x05);
    machine.mem_store_byte(0xE165E, 0x00);
    machine.mem_store_byte(0xE165F, 0x00);
    machine.mem_store_byte(0xE1660, 0xF4);
    machine.mem_store_byte(0xE1661, 0x82);
    machine.mem_store_byte(0xE1662, 0x65);
    machine.mem_store_byte(0xE1663, 0x28);
    machine.mem_store_byte(0xBE1E1, 0x3F);
    machine.mem_store_byte(0xE1664, 0x32);
    machine.mem_store_byte(0xE1665, 0xEB);
    machine.mem_store_byte(0xE1666, 0x2A);
    machine.mem_store_byte(0xE1667, 0xE2);
    machine.mem_store_byte(0xE1668, 0x96);
    machine.mem_store_byte(0xE1669, 0x10);
    machine.mem_store_byte(0xE166A, 0x67);
    machine.mem_store_byte(0xE166B, 0xF0);
    machine.mem_store_byte(0xE166C, 0x71);
    machine.mem_store_byte(0xE166D, 0x25);
    machine.mem_store_byte(0xE166E, 0xE7);
    machine.mem_store_byte(0xE166F, 0x4E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00001503);
    EXPECT_EQ(cpu.get_ebx(), 0x00000001);
    EXPECT_EQ(cpu.get_ecx(), 0xD935A22C);
    EXPECT_EQ(cpu.get_edx(), 0x00000ECB);
    EXPECT_EQ(cpu.get_esi(), 0xD47140A3);
    EXPECT_EQ(cpu.get_edi(), 0xFF5807F8);
    EXPECT_EQ(cpu.get_ebp(), 0x5E4394D1);
    EXPECT_EQ(cpu.get_esp(), 0x0000C72A);
    EXPECT_EQ(cpu.get_cs(), 0x0000D53F);
    EXPECT_EQ(cpu.get_ds(), 0x0000B65A);
    EXPECT_EQ(cpu.get_es(), 0x00000DC3);
    EXPECT_EQ(cpu.get_fs(), 0x00004B97);
    EXPECT_EQ(cpu.get_gs(), 0x00007940);
    EXPECT_EQ(cpu.get_ss(), 0x00000014);
    EXPECT_EQ(cpu.get_eip(), 0x0000C271);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0412);

    // Final RAM entries
}

//
// dec ebx
//
TEST_F(Test386, dec_ebx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x20D6F139);
    cpu.set_ebx(0x4C6EC70E);
    cpu.set_ecx(0x0882C938);
    cpu.set_edx(0x080F1CEE);
    cpu.set_esi(0x50334B9D);
    cpu.set_edi(0xE34EE29F);
    cpu.set_ebp(0xBACE2D66);
    cpu.set_esp(0x000026B0);
    cpu.set_cs(0x000006CA);
    cpu.set_ds(0x000058A8);
    cpu.set_es(0x0000F5E0);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00000049);
    cpu.set_ss(0x00003FE1);
    cpu.set_eip(0x00006548);
    cpu.set_eflags(0xFFFC00D6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0D1E8, 0x66);
    machine.mem_store_byte(0x0D1E9, 0x4B);
    machine.mem_store_byte(0x0D1EA, 0xF4);
    machine.mem_store_byte(0x0D1EB, 0x13);
    machine.mem_store_byte(0x0D1EC, 0x02);
    machine.mem_store_byte(0x0D1ED, 0xD0);
    machine.mem_store_byte(0x0D1EE, 0x5F);
    machine.mem_store_byte(0x0D1EF, 0xBA);
    machine.mem_store_byte(0x0D1F0, 0xF7);
    machine.mem_store_byte(0x0D1F1, 0xAA);
    machine.mem_store_byte(0x0D1F2, 0x42);
    machine.mem_store_byte(0x0D1F3, 0x85);
    machine.mem_store_byte(0x0D1F4, 0x81);
    machine.mem_store_byte(0x0D1F5, 0x50);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x20D6F139);
    EXPECT_EQ(cpu.get_ebx(), 0x4C6EC70D);
    EXPECT_EQ(cpu.get_ecx(), 0x0882C938);
    EXPECT_EQ(cpu.get_edx(), 0x080F1CEE);
    EXPECT_EQ(cpu.get_esi(), 0x50334B9D);
    EXPECT_EQ(cpu.get_edi(), 0xE34EE29F);
    EXPECT_EQ(cpu.get_ebp(), 0xBACE2D66);
    EXPECT_EQ(cpu.get_esp(), 0x000026B0);
    EXPECT_EQ(cpu.get_cs(), 0x000006CA);
    EXPECT_EQ(cpu.get_ds(), 0x000058A8);
    EXPECT_EQ(cpu.get_es(), 0x0000F5E0);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00000049);
    EXPECT_EQ(cpu.get_ss(), 0x00003FE1);
    EXPECT_EQ(cpu.get_eip(), 0x0000654B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0002);

    // Final RAM entries
}

//
// div di
//
TEST_F(Test386, div_di)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x44846D20);
    cpu.set_ebx(0x00000001);
    cpu.set_ecx(0x75DCF65D);
    cpu.set_edx(0xDA458064);
    cpu.set_esi(0x06C38BF3);
    cpu.set_edi(0x7A8CC8BD);
    cpu.set_ebp(0x016EBFA7);
    cpu.set_esp(0x0000C679);
    cpu.set_cs(0x0000E7A8);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x000092C9);
    cpu.set_gs(0x0000D355);
    cpu.set_ss(0x0000FCA6);
    cpu.set_eip(0x00003F78);
    cpu.set_eflags(0xFFFC0487);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEB9F8, 0xF7);
    machine.mem_store_byte(0xEB9F9, 0xF7);
    machine.mem_store_byte(0xEB9FA, 0xF4);
    machine.mem_store_byte(0xEB9FB, 0x0F);
    machine.mem_store_byte(0xEB9FC, 0x7A);
    machine.mem_store_byte(0xEB9FD, 0x1C);
    machine.mem_store_byte(0xEB9FE, 0xAE);
    machine.mem_store_byte(0xEB9FF, 0xEC);
    machine.mem_store_byte(0xEBA00, 0x77);
    machine.mem_store_byte(0xEBA01, 0xD9);
    machine.mem_store_byte(0xEBA02, 0x15);
    machine.mem_store_byte(0xEBA03, 0xA7);
    machine.mem_store_byte(0xEBA04, 0x8A);
    machine.mem_store_byte(0xEBA05, 0x64);
    machine.mem_store_byte(0xEBA06, 0xD8);
    machine.mem_store_byte(0xEBA07, 0x44);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x4484A3BC);
    EXPECT_EQ(cpu.get_ebx(), 0x00000001);
    EXPECT_EQ(cpu.get_ecx(), 0x75DCF65D);
    EXPECT_EQ(cpu.get_edx(), 0xDA45AB54);
    EXPECT_EQ(cpu.get_esi(), 0x06C38BF3);
    EXPECT_EQ(cpu.get_edi(), 0x7A8CC8BD);
    EXPECT_EQ(cpu.get_ebp(), 0x016EBFA7);
    EXPECT_EQ(cpu.get_esp(), 0x0000C679);
    EXPECT_EQ(cpu.get_cs(), 0x0000E7A8);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x000092C9);
    EXPECT_EQ(cpu.get_gs(), 0x0000D355);
    EXPECT_EQ(cpu.get_ss(), 0x0000FCA6);
    EXPECT_EQ(cpu.get_eip(), 0x00003F7B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
}

//
// div dword [ds:ecx]
//
TEST_F(Test386, div_dword_ds_ecx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF0DBEC8C);
    cpu.set_ebx(0xDE487927);
    cpu.set_ecx(0x000083D9);
    cpu.set_edx(0x018A3FD6);
    cpu.set_esi(0xED2DAADF);
    cpu.set_edi(0x1C3F2A2F);
    cpu.set_ebp(0x59C70ABF);
    cpu.set_esp(0x0000B58E);
    cpu.set_cs(0x0000FEC4);
    cpu.set_ds(0x00000073);
    cpu.set_es(0x0000DBE7);
    cpu.set_fs(0x0000D163);
    cpu.set_gs(0x00002194);
    cpu.set_ss(0x0000BD27);
    cpu.set_eip(0x0000EBA0);
    cpu.set_eflags(0xFFFC0496);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10D7E0, 0x67);
    machine.mem_store_byte(0x10D7E1, 0x66);
    machine.mem_store_byte(0x10D7E2, 0xF7);
    machine.mem_store_byte(0x10D7E3, 0x31);
    machine.mem_store_byte(0x10D7E4, 0xF4);
    machine.mem_store_byte(0x10D7E5, 0xD6);
    machine.mem_store_byte(0x10D7E6, 0x17);
    machine.mem_store_byte(0x10D7E7, 0x7B);
    machine.mem_store_byte(0x10D7E8, 0xE0);
    machine.mem_store_byte(0x10D7E9, 0xBF);
    machine.mem_store_byte(0x10D7EA, 0x44);
    machine.mem_store_byte(0x10D7EB, 0x08);
    machine.mem_store_byte(0x08B0C, 0x1F);
    machine.mem_store_byte(0x08B09, 0x36);
    machine.mem_store_byte(0x08B0A, 0xC2);
    machine.mem_store_byte(0x08B0B, 0x80);
    machine.mem_store_byte(0x10D7EC, 0x10);
    machine.mem_store_byte(0x10D7ED, 0xEC);
    machine.mem_store_byte(0x10D7EE, 0x18);
    machine.mem_store_byte(0x10D7EF, 0x95);
    machine.mem_store_byte(0x10D7F0, 0xCD);
    machine.mem_store_byte(0x10D7F1, 0x41);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0C83C1CA);
    EXPECT_EQ(cpu.get_ebx(), 0xDE487927);
    EXPECT_EQ(cpu.get_ecx(), 0x000083D9);
    EXPECT_EQ(cpu.get_edx(), 0x1935F7F0);
    EXPECT_EQ(cpu.get_esi(), 0xED2DAADF);
    EXPECT_EQ(cpu.get_edi(), 0x1C3F2A2F);
    EXPECT_EQ(cpu.get_ebp(), 0x59C70ABF);
    EXPECT_EQ(cpu.get_esp(), 0x0000B58E);
    EXPECT_EQ(cpu.get_cs(), 0x0000FEC4);
    EXPECT_EQ(cpu.get_ds(), 0x00000073);
    EXPECT_EQ(cpu.get_es(), 0x0000DBE7);
    EXPECT_EQ(cpu.get_fs(), 0x0000D163);
    EXPECT_EQ(cpu.get_gs(), 0x00002194);
    EXPECT_EQ(cpu.get_ss(), 0x0000BD27);
    EXPECT_EQ(cpu.get_eip(), 0x0000EBA5);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
}

//
// div byte [ss:bp+di-2FC3h]
//
TEST_F(Test386, div_byte_ss_bp_di_2FC3h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x3D0EB0D2);
    cpu.set_ebx(0x00000001);
    cpu.set_ecx(0xD935A22C);
    cpu.set_edx(0xED8C1ECB);
    cpu.set_esi(0xD47140A3);
    cpu.set_edi(0xFF5807F8);
    cpu.set_ebp(0x5E4394D1);
    cpu.set_esp(0x0000C72A);
    cpu.set_cs(0x0000D53F);
    cpu.set_ds(0x0000B65A);
    cpu.set_es(0x00000DC3);
    cpu.set_fs(0x00004B97);
    cpu.set_gs(0x00007940);
    cpu.set_ss(0x00000014);
    cpu.set_eip(0x0000C268);
    cpu.set_eflags(0xFFFC0417);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE1658, 0xF6);
    machine.mem_store_byte(0xE1659, 0xB3);
    machine.mem_store_byte(0xE165A, 0x3D);
    machine.mem_store_byte(0xE165B, 0xD0);
    machine.mem_store_byte(0xE165C, 0xF4);
    machine.mem_store_byte(0xE165D, 0xCE);
    machine.mem_store_byte(0xE165E, 0xA0);
    machine.mem_store_byte(0xE165F, 0x1F);
    machine.mem_store_byte(0xE1660, 0x85);
    machine.mem_store_byte(0xE1661, 0x82);
    machine.mem_store_byte(0x06E46, 0xF0);
    machine.mem_store_byte(0xE1662, 0x65);
    machine.mem_store_byte(0xE1663, 0x28);
    machine.mem_store_byte(0xE1664, 0x32);
    machine.mem_store_byte(0xE1665, 0xEB);
    machine.mem_store_byte(0xE1666, 0x2A);
    machine.mem_store_byte(0xE1667, 0xE2);
    machine.mem_store_byte(0xE1668, 0x96);
    machine.mem_store_byte(0xE1669, 0x10);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x3D0E92BC);
    EXPECT_EQ(cpu.get_ebx(), 0x00000001);
    EXPECT_EQ(cpu.get_ecx(), 0xD935A22C);
    EXPECT_EQ(cpu.get_edx(), 0xED8C1ECB);
    EXPECT_EQ(cpu.get_esi(), 0xD47140A3);
    EXPECT_EQ(cpu.get_edi(), 0xFF5807F8);
    EXPECT_EQ(cpu.get_ebp(), 0x5E4394D1);
    EXPECT_EQ(cpu.get_esp(), 0x0000C72A);
    EXPECT_EQ(cpu.get_cs(), 0x0000D53F);
    EXPECT_EQ(cpu.get_ds(), 0x0000B65A);
    EXPECT_EQ(cpu.get_es(), 0x00000DC3);
    EXPECT_EQ(cpu.get_fs(), 0x00004B97);
    EXPECT_EQ(cpu.get_gs(), 0x00007940);
    EXPECT_EQ(cpu.get_ss(), 0x00000014);
    EXPECT_EQ(cpu.get_eip(), 0x0000C26D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0483);

    // Final RAM entries
}

//
// div esp
//
TEST_F(Test386, div_esp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x5A5A5A5A);
    cpu.set_ebx(0xC3A6945D);
    cpu.set_ecx(0xF95ADC25);
    cpu.set_edx(0xFD29DC71);
    cpu.set_esi(0x57F2805E);
    cpu.set_edi(0xAB50A441);
    cpu.set_ebp(0xD1AACFD4);
    cpu.set_esp(0x00004492);
    cpu.set_cs(0x00005833);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x000000E6);
    cpu.set_fs(0x00003DFA);
    cpu.set_gs(0x00007446);
    cpu.set_ss(0x0000B412);
    cpu.set_eip(0x00005530);
    cpu.set_eflags(0xFFFC0847);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5D860, 0x67);
    machine.mem_store_byte(0x5D861, 0x66);
    machine.mem_store_byte(0x5D862, 0xF7);
    machine.mem_store_byte(0x5D863, 0xF4);
    machine.mem_store_byte(0x5D864, 0xF4);
    machine.mem_store_byte(0x5D865, 0xFF);
    machine.mem_store_byte(0x5D866, 0xFF);
    machine.mem_store_byte(0x5D867, 0xFF);
    machine.mem_store_byte(0x5D868, 0xFF);
    machine.mem_store_byte(0x5D869, 0xFF);
    machine.mem_store_byte(0x5D86A, 0xFF);
    machine.mem_store_byte(0x5D86B, 0xFF);
    machine.mem_store_byte(0x5D86C, 0xFF);
    machine.mem_store_byte(0x5D86D, 0xFF);
    machine.mem_store_byte(0x5D86E, 0xFF);
    machine.mem_store_byte(0x5D86F, 0xFF);
    machine.mem_store_byte(0x5D870, 0xFF);
    machine.mem_store_byte(0x5D871, 0xFF);
    machine.mem_store_byte(0x5D872, 0xFF);
    machine.mem_store_byte(0x5D873, 0xFF);
    machine.mem_store_byte(0x00000, 0xA1);
    machine.mem_store_byte(0x00001, 0xD8);
    machine.mem_store_byte(0x00002, 0xA5);
    machine.mem_store_byte(0x00003, 0x30);
    machine.mem_store_byte(0x3E2F0, 0xFF);
    machine.mem_store_byte(0x3E2F1, 0xF4);
    machine.mem_store_byte(0x3E2F2, 0xFF);
    machine.mem_store_byte(0x3E2F3, 0xF4);
    machine.mem_store_byte(0x3E2F4, 0xFF);
    machine.mem_store_byte(0x3E2F5, 0xF4);
    machine.mem_store_byte(0x3E2F6, 0xFF);
    machine.mem_store_byte(0x3E2F7, 0xF4);
    machine.mem_store_byte(0x3E2F8, 0xFF);
    machine.mem_store_byte(0x3E2F9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x5A5A5A5A);
    EXPECT_EQ(cpu.get_ebx(), 0xC3A6945D);
    EXPECT_EQ(cpu.get_ecx(), 0xF95ADC25);
    EXPECT_EQ(cpu.get_edx(), 0xFD29DC71);
    EXPECT_EQ(cpu.get_esi(), 0x57F2805E);
    EXPECT_EQ(cpu.get_edi(), 0xAB50A441);
    EXPECT_EQ(cpu.get_ebp(), 0xD1AACFD4);
    EXPECT_EQ(cpu.get_esp(), 0x0000448C);
    EXPECT_EQ(cpu.get_cs(), 0x000030A5);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x000000E6);
    EXPECT_EQ(cpu.get_fs(), 0x00003DFA);
    EXPECT_EQ(cpu.get_gs(), 0x00007446);
    EXPECT_EQ(cpu.get_ss(), 0x0000B412);
    EXPECT_EQ(cpu.get_eip(), 0x0000D8A2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB85B0), 0x92);
    EXPECT_EQ(memory.load8(0xB85B1), 0x00);
    EXPECT_EQ(memory.load8(0xB85AE), 0x33);
    EXPECT_EQ(memory.load8(0xB85AF), 0x58);
    EXPECT_EQ(memory.load8(0xB85AC), 0x30);
    EXPECT_EQ(memory.load8(0xB85AD), 0x55);
}

//
// div sp
//
TEST_F(Test386, div_sp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x5A5A5A5A);
    cpu.set_ebx(0xC3A6945D);
    cpu.set_ecx(0xF95ADC25);
    cpu.set_edx(0xFD29DC71);
    cpu.set_esi(0x57F2805E);
    cpu.set_edi(0xAB50A441);
    cpu.set_ebp(0xD1AACFD4);
    cpu.set_esp(0x00004492);
    cpu.set_cs(0x00005833);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x000000E6);
    cpu.set_fs(0x00003DFA);
    cpu.set_gs(0x00007446);
    cpu.set_ss(0x0000B412);
    cpu.set_eip(0x00005530);
    cpu.set_eflags(0xFFFC0847);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5D860, 0xF7);
    machine.mem_store_byte(0x5D861, 0xF4);
    machine.mem_store_byte(0x5D862, 0xF4);
    machine.mem_store_byte(0x5D863, 0xFF);
    machine.mem_store_byte(0x5D864, 0xFF);
    machine.mem_store_byte(0x5D865, 0xFF);
    machine.mem_store_byte(0x5D866, 0xFF);
    machine.mem_store_byte(0x5D867, 0xFF);
    machine.mem_store_byte(0x5D868, 0xFF);
    machine.mem_store_byte(0x5D869, 0xFF);
    machine.mem_store_byte(0x5D86A, 0xFF);
    machine.mem_store_byte(0x5D86B, 0xFF);
    machine.mem_store_byte(0x5D86C, 0xFF);
    machine.mem_store_byte(0x5D86D, 0xFF);
    machine.mem_store_byte(0x5D86E, 0xFF);
    machine.mem_store_byte(0x5D86F, 0xFF);
    machine.mem_store_byte(0x00000, 0xA1);
    machine.mem_store_byte(0x00001, 0xD8);
    machine.mem_store_byte(0x00002, 0xA5);
    machine.mem_store_byte(0x00003, 0x30);
    machine.mem_store_byte(0x3E2F0, 0xFF);
    machine.mem_store_byte(0x3E2F1, 0xF4);
    machine.mem_store_byte(0x3E2F2, 0xFF);
    machine.mem_store_byte(0x3E2F3, 0xF4);
    machine.mem_store_byte(0x3E2F4, 0xFF);
    machine.mem_store_byte(0x3E2F5, 0xF4);
    machine.mem_store_byte(0x3E2F6, 0xFF);
    machine.mem_store_byte(0x3E2F7, 0xF4);
    machine.mem_store_byte(0x3E2F8, 0xFF);
    machine.mem_store_byte(0x3E2F9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x5A5A5A5A);
    EXPECT_EQ(cpu.get_ebx(), 0xC3A6945D);
    EXPECT_EQ(cpu.get_ecx(), 0xF95ADC25);
    EXPECT_EQ(cpu.get_edx(), 0xFD29DC71);
    EXPECT_EQ(cpu.get_esi(), 0x57F2805E);
    EXPECT_EQ(cpu.get_edi(), 0xAB50A441);
    EXPECT_EQ(cpu.get_ebp(), 0xD1AACFD4);
    EXPECT_EQ(cpu.get_esp(), 0x0000448C);
    EXPECT_EQ(cpu.get_cs(), 0x000030A5);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x000000E6);
    EXPECT_EQ(cpu.get_fs(), 0x00003DFA);
    EXPECT_EQ(cpu.get_gs(), 0x00007446);
    EXPECT_EQ(cpu.get_ss(), 0x0000B412);
    EXPECT_EQ(cpu.get_eip(), 0x0000D8A2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB85B0), 0x87);
    EXPECT_EQ(memory.load8(0xB85B1), 0x00);
    EXPECT_EQ(memory.load8(0xB85AE), 0x33);
    EXPECT_EQ(memory.load8(0xB85AF), 0x58);
    EXPECT_EQ(memory.load8(0xB85AC), 0x30);
    EXPECT_EQ(memory.load8(0xB85AD), 0x55);
}
