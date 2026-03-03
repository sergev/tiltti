#include "test386.h"

//
// lds bp,[ds:bx+si]
//
TEST_F(Test386, lds_bp_ds_bx_si)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2276E9AE);
    cpu.set_ebx(0xD87E2014);
    cpu.set_ecx(0x091538F0);
    cpu.set_edx(0x7C90E7DB);
    cpu.set_esi(0xB8965052);
    cpu.set_edi(0xFAC831E0);
    cpu.set_ebp(0x0A9A48ED);
    cpu.set_esp(0x0000F6B6);
    cpu.set_cs(0x0000EC24);
    cpu.set_ds(0x0000F9B7);
    cpu.set_es(0x0000535E);
    cpu.set_fs(0x00008B1F);
    cpu.set_gs(0x00002A88);
    cpu.set_ss(0x000021E5);
    cpu.set_eip(0x0000BAF0);
    cpu.set_eflags(0xFFFC00D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF7D30, 0xC5);
    machine.mem_store_byte(0xF7D31, 0x28);
    machine.mem_store_byte(0xF7D32, 0xF4);
    machine.mem_store_byte(0xF7D33, 0xC3);
    machine.mem_store_byte(0xF7D34, 0x31);
    machine.mem_store_byte(0xF7D35, 0x89);
    machine.mem_store_byte(0xF7D36, 0x7C);
    machine.mem_store_byte(0xF7D37, 0x89);
    machine.mem_store_byte(0xF7D38, 0xED);
    machine.mem_store_byte(0xF7D39, 0x03);
    machine.mem_store_byte(0x100BD6, 0xC3);
    machine.mem_store_byte(0x100BD7, 0x5C);
    machine.mem_store_byte(0x100BD8, 0x39);
    machine.mem_store_byte(0x100BD9, 0x34);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x2276E9AE);
    EXPECT_EQ(cpu.get_ebx(), 0xD87E2014);
    EXPECT_EQ(cpu.get_ecx(), 0x091538F0);
    EXPECT_EQ(cpu.get_edx(), 0x7C90E7DB);
    EXPECT_EQ(cpu.get_esi(), 0xB8965052);
    EXPECT_EQ(cpu.get_edi(), 0xFAC831E0);
    EXPECT_EQ(cpu.get_ebp(), 0x0A9A5CC3);
    EXPECT_EQ(cpu.get_esp(), 0x0000F6B6);
    EXPECT_EQ(cpu.get_cs(), 0x0000EC24);
    EXPECT_EQ(cpu.get_ds(), 0x00003439);
    EXPECT_EQ(cpu.get_es(), 0x0000535E);
    EXPECT_EQ(cpu.get_fs(), 0x00008B1F);
    EXPECT_EQ(cpu.get_gs(), 0x00002A88);
    EXPECT_EQ(cpu.get_ss(), 0x000021E5);
    EXPECT_EQ(cpu.get_eip(), 0x0000BAF3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00D2);

    // Final RAM entries
}

//
// lea di,[ds:edi+24A8094h]
//
TEST_F(Test386, lea_di_ds_edi_24A8094h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDC353CB9);
    cpu.set_ebx(0x0C870C55);
    cpu.set_ecx(0x20000000);
    cpu.set_edx(0x0FFFE837);
    cpu.set_esi(0x7F000000);
    cpu.set_edi(0x01010101);
    cpu.set_ebp(0x00000007);
    cpu.set_esp(0x00000014);
    cpu.set_cs(0x00008081);
    cpu.set_ds(0x0000A51D);
    cpu.set_es(0x000000A1);
    cpu.set_fs(0x00006B75);
    cpu.set_gs(0x0000001B);
    cpu.set_ss(0x00000052);
    cpu.set_eip(0x0000FCE0);
    cpu.set_eflags(0xFFFC0803);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x904F0, 0x67);
    machine.mem_store_byte(0x904F1, 0x8D);
    machine.mem_store_byte(0x904F2, 0xBF);
    machine.mem_store_byte(0x904F3, 0x94);
    machine.mem_store_byte(0x904F4, 0x80);
    machine.mem_store_byte(0x904F5, 0x4A);
    machine.mem_store_byte(0x904F6, 0x02);
    machine.mem_store_byte(0x904F7, 0xF4);
    machine.mem_store_byte(0x904F8, 0x5A);
    machine.mem_store_byte(0x904F9, 0xA1);
    machine.mem_store_byte(0x904FA, 0xF2);
    machine.mem_store_byte(0x904FB, 0xB3);
    machine.mem_store_byte(0x904FC, 0xC6);
    machine.mem_store_byte(0x904FD, 0x96);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDC353CB9);
    EXPECT_EQ(cpu.get_ebx(), 0x0C870C55);
    EXPECT_EQ(cpu.get_ecx(), 0x20000000);
    EXPECT_EQ(cpu.get_edx(), 0x0FFFE837);
    EXPECT_EQ(cpu.get_esi(), 0x7F000000);
    EXPECT_EQ(cpu.get_edi(), 0x01018195);
    EXPECT_EQ(cpu.get_ebp(), 0x00000007);
    EXPECT_EQ(cpu.get_esp(), 0x00000014);
    EXPECT_EQ(cpu.get_cs(), 0x00008081);
    EXPECT_EQ(cpu.get_ds(), 0x0000A51D);
    EXPECT_EQ(cpu.get_es(), 0x000000A1);
    EXPECT_EQ(cpu.get_fs(), 0x00006B75);
    EXPECT_EQ(cpu.get_gs(), 0x0000001B);
    EXPECT_EQ(cpu.get_ss(), 0x00000052);
    EXPECT_EQ(cpu.get_eip(), 0x0000FCE8);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
}

//
// leave
//
TEST_F(Test386, leave)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD2B5E066);
    cpu.set_ebx(0xA0D2DE29);
    cpu.set_ecx(0x06051307);
    cpu.set_edx(0x5E2B52BA);
    cpu.set_esi(0x0C901F1A);
    cpu.set_edi(0x7DFA2403);
    cpu.set_ebp(0x1ED617B6);
    cpu.set_esp(0x0000C0D3);
    cpu.set_cs(0x00004B4E);
    cpu.set_ds(0x0000396C);
    cpu.set_es(0x00003F92);
    cpu.set_fs(0x00004010);
    cpu.set_gs(0x00000190);
    cpu.set_ss(0x00007562);
    cpu.set_eip(0x00008A20);
    cpu.set_eflags(0xFFFC0847);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x53F00, 0xC9);
    machine.mem_store_byte(0x53F01, 0xF4);
    machine.mem_store_byte(0x53F02, 0x38);
    machine.mem_store_byte(0x53F03, 0x41);
    machine.mem_store_byte(0x53F04, 0x9E);
    machine.mem_store_byte(0x53F05, 0x48);
    machine.mem_store_byte(0x53F06, 0xCA);
    machine.mem_store_byte(0x53F07, 0x2F);
    machine.mem_store_byte(0x53F08, 0xDD);
    machine.mem_store_byte(0x53F09, 0x48);
    machine.mem_store_byte(0x76DD6, 0xDD);
    machine.mem_store_byte(0x76DD7, 0xD6);
    machine.mem_store_byte(0x53F0A, 0x64);
    machine.mem_store_byte(0x53F0B, 0x52);
    machine.mem_store_byte(0x53F0C, 0x70);
    machine.mem_store_byte(0x53F0D, 0x02);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD2B5E066);
    EXPECT_EQ(cpu.get_ebx(), 0xA0D2DE29);
    EXPECT_EQ(cpu.get_ecx(), 0x06051307);
    EXPECT_EQ(cpu.get_edx(), 0x5E2B52BA);
    EXPECT_EQ(cpu.get_esi(), 0x0C901F1A);
    EXPECT_EQ(cpu.get_edi(), 0x7DFA2403);
    EXPECT_EQ(cpu.get_ebp(), 0x1ED6D6DD);
    EXPECT_EQ(cpu.get_esp(), 0x000017B8);
    EXPECT_EQ(cpu.get_cs(), 0x00004B4E);
    EXPECT_EQ(cpu.get_ds(), 0x0000396C);
    EXPECT_EQ(cpu.get_es(), 0x00003F92);
    EXPECT_EQ(cpu.get_fs(), 0x00004010);
    EXPECT_EQ(cpu.get_gs(), 0x00000190);
    EXPECT_EQ(cpu.get_ss(), 0x00007562);
    EXPECT_EQ(cpu.get_eip(), 0x00008A22);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0847);

    // Final RAM entries
}

//
// lea edi,[ds:edi+24A8094h]
//
TEST_F(Test386, lea_edi_ds_edi_24A8094h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDC353CB9);
    cpu.set_ebx(0x0C870C55);
    cpu.set_ecx(0x20000000);
    cpu.set_edx(0x0FFFE837);
    cpu.set_esi(0x7F000000);
    cpu.set_edi(0x01010101);
    cpu.set_ebp(0x00000007);
    cpu.set_esp(0x00000014);
    cpu.set_cs(0x00008081);
    cpu.set_ds(0x0000A51D);
    cpu.set_es(0x000000A1);
    cpu.set_fs(0x00006B75);
    cpu.set_gs(0x0000001B);
    cpu.set_ss(0x00000052);
    cpu.set_eip(0x0000FCE0);
    cpu.set_eflags(0xFFFC0803);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x904F0, 0x67);
    machine.mem_store_byte(0x904F1, 0x66);
    machine.mem_store_byte(0x904F2, 0x8D);
    machine.mem_store_byte(0x904F3, 0xBF);
    machine.mem_store_byte(0x904F4, 0x94);
    machine.mem_store_byte(0x904F5, 0x80);
    machine.mem_store_byte(0x904F6, 0x4A);
    machine.mem_store_byte(0x904F7, 0x02);
    machine.mem_store_byte(0x904F8, 0xF4);
    machine.mem_store_byte(0x904F9, 0xA1);
    machine.mem_store_byte(0x904FA, 0xF2);
    machine.mem_store_byte(0x904FB, 0xB3);
    machine.mem_store_byte(0x904FC, 0xC6);
    machine.mem_store_byte(0x904FD, 0x96);
    machine.mem_store_byte(0x904FE, 0xE6);
    machine.mem_store_byte(0x904FF, 0xE0);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDC353CB9);
    EXPECT_EQ(cpu.get_ebx(), 0x0C870C55);
    EXPECT_EQ(cpu.get_ecx(), 0x20000000);
    EXPECT_EQ(cpu.get_edx(), 0x0FFFE837);
    EXPECT_EQ(cpu.get_esi(), 0x7F000000);
    EXPECT_EQ(cpu.get_edi(), 0x034B8195);
    EXPECT_EQ(cpu.get_ebp(), 0x00000007);
    EXPECT_EQ(cpu.get_esp(), 0x00000014);
    EXPECT_EQ(cpu.get_cs(), 0x00008081);
    EXPECT_EQ(cpu.get_ds(), 0x0000A51D);
    EXPECT_EQ(cpu.get_es(), 0x000000A1);
    EXPECT_EQ(cpu.get_fs(), 0x00006B75);
    EXPECT_EQ(cpu.get_gs(), 0x0000001B);
    EXPECT_EQ(cpu.get_ss(), 0x00000052);
    EXPECT_EQ(cpu.get_eip(), 0x0000FCE9);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
}

//
// les eax,[gs:esi-704Eh]
//
TEST_F(Test386, les_eax_gs_esi_704Eh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x07EB572D);
    cpu.set_ebx(0x3ABE265B);
    cpu.set_ecx(0xC260A1F8);
    cpu.set_edx(0x0697DB83);
    cpu.set_esi(0x0000D059);
    cpu.set_edi(0xA05329D4);
    cpu.set_ebp(0x88C7E4E6);
    cpu.set_esp(0x00001428);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000B02B);
    cpu.set_es(0x0000D68C);
    cpu.set_fs(0x00000360);
    cpu.set_gs(0x000076DA);
    cpu.set_ss(0x0000BA92);
    cpu.set_eip(0x00000EE8);
    cpu.set_eflags(0xFFFC04D7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x100ED8, 0x65);
    machine.mem_store_byte(0x100ED9, 0x66);
    machine.mem_store_byte(0x100EDA, 0x67);
    machine.mem_store_byte(0x100EDB, 0xC4);
    machine.mem_store_byte(0x100EDC, 0x86);
    machine.mem_store_byte(0x100EDD, 0xB2);
    machine.mem_store_byte(0x100EDE, 0x8F);
    machine.mem_store_byte(0x100EDF, 0xFF);
    machine.mem_store_byte(0x100EE0, 0xFF);
    machine.mem_store_byte(0x100EE1, 0xF4);
    machine.mem_store_byte(0x100EE2, 0x50);
    machine.mem_store_byte(0x100EE3, 0xF8);
    machine.mem_store_byte(0x100EE4, 0x3C);
    machine.mem_store_byte(0x100EE5, 0x84);
    machine.mem_store_byte(0x100EE6, 0x0C);
    machine.mem_store_byte(0x100EE7, 0xFD);
    machine.mem_store_byte(0x7CDAC, 0xA0);
    machine.mem_store_byte(0x7CDAD, 0x03);
    machine.mem_store_byte(0x7CDAE, 0xDF);
    machine.mem_store_byte(0x7CDAB, 0x6C);
    machine.mem_store_byte(0x7CDB0, 0x42);
    machine.mem_store_byte(0x7CDAF, 0x5C);
    machine.mem_store_byte(0x100EE8, 0x08);
    machine.mem_store_byte(0x100EE9, 0x38);
    machine.mem_store_byte(0x100EEA, 0x9D);
    machine.mem_store_byte(0x100EEB, 0xBE);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDF03A06C);
    EXPECT_EQ(cpu.get_ebx(), 0x3ABE265B);
    EXPECT_EQ(cpu.get_ecx(), 0xC260A1F8);
    EXPECT_EQ(cpu.get_edx(), 0x0697DB83);
    EXPECT_EQ(cpu.get_esi(), 0x0000D059);
    EXPECT_EQ(cpu.get_edi(), 0xA05329D4);
    EXPECT_EQ(cpu.get_ebp(), 0x88C7E4E6);
    EXPECT_EQ(cpu.get_esp(), 0x00001428);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000B02B);
    EXPECT_EQ(cpu.get_es(), 0x0000425C);
    EXPECT_EQ(cpu.get_fs(), 0x00000360);
    EXPECT_EQ(cpu.get_gs(), 0x000076DA);
    EXPECT_EQ(cpu.get_ss(), 0x0000BA92);
    EXPECT_EQ(cpu.get_eip(), 0x00000EF2);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04D7);

    // Final RAM entries
}

//
// lfs cx,[ds:bx-5ACDh]
//
TEST_F(Test386, lfs_cx_ds_bx_5ACDh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xC998B243);
    cpu.set_ebx(0xFC496EE8);
    cpu.set_ecx(0xDF06047E);
    cpu.set_edx(0xFE0FD871);
    cpu.set_esi(0xE315656D);
    cpu.set_edi(0xFD5B2397);
    cpu.set_ebp(0xE02F776B);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x0000F46D);
    cpu.set_ds(0x00000D2A);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x0000F27F);
    cpu.set_gs(0x0000BB5F);
    cpu.set_ss(0x000028E0);
    cpu.set_eip(0x0000C4A0);
    cpu.set_eflags(0xFFFC0882);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x100B70, 0x0F);
    machine.mem_store_byte(0x100B71, 0xB4);
    machine.mem_store_byte(0x100B72, 0x8F);
    machine.mem_store_byte(0x100B73, 0x33);
    machine.mem_store_byte(0x100B74, 0xA5);
    machine.mem_store_byte(0x100B75, 0xF4);
    machine.mem_store_byte(0x100B76, 0x91);
    machine.mem_store_byte(0x100B77, 0x7B);
    machine.mem_store_byte(0x100B78, 0x56);
    machine.mem_store_byte(0x100B79, 0x39);
    machine.mem_store_byte(0x100B7A, 0x8D);
    machine.mem_store_byte(0x100B7B, 0x1F);
    machine.mem_store_byte(0x0E6BC, 0x31);
    machine.mem_store_byte(0x0E6BB, 0xBD);
    machine.mem_store_byte(0x0E6BD, 0xBD);
    machine.mem_store_byte(0x0E6BE, 0x93);
    machine.mem_store_byte(0x100B7C, 0xC0);
    machine.mem_store_byte(0x100B7D, 0x94);
    machine.mem_store_byte(0x100B7E, 0xC6);
    machine.mem_store_byte(0x100B7F, 0x9E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xC998B243);
    EXPECT_EQ(cpu.get_ebx(), 0xFC496EE8);
    EXPECT_EQ(cpu.get_ecx(), 0xDF0631BD);
    EXPECT_EQ(cpu.get_edx(), 0xFE0FD871);
    EXPECT_EQ(cpu.get_esi(), 0xE315656D);
    EXPECT_EQ(cpu.get_edi(), 0xFD5B2397);
    EXPECT_EQ(cpu.get_ebp(), 0xE02F776B);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_cs(), 0x0000F46D);
    EXPECT_EQ(cpu.get_ds(), 0x00000D2A);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x000093BD);
    EXPECT_EQ(cpu.get_gs(), 0x0000BB5F);
    EXPECT_EQ(cpu.get_ss(), 0x000028E0);
    EXPECT_EQ(cpu.get_eip(), 0x0000C4A6);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0882);

    // Final RAM entries
}

//
// lock bt di,3Fh
//
TEST_F(Test386, lock_bt_di_3Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF499C6D6);
    cpu.set_ebx(0xF9433D4D);
    cpu.set_ecx(0x634FADD4);
    cpu.set_edx(0x063693B4);
    cpu.set_esi(0x626E4A31);
    cpu.set_edi(0x3ADE9CA7);
    cpu.set_ebp(0x705049D8);
    cpu.set_esp(0x0000A654);
    cpu.set_cs(0x000028CC);
    cpu.set_ds(0x00003222);
    cpu.set_es(0x00008397);
    cpu.set_fs(0x0000A8E3);
    cpu.set_gs(0x000020AE);
    cpu.set_ss(0x000001AC);
    cpu.set_eip(0x00004940);
    cpu.set_eflags(0xFFFC0007);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2D600, 0x65);
    machine.mem_store_byte(0x2D601, 0x64);
    machine.mem_store_byte(0x2D602, 0x26);
    machine.mem_store_byte(0x2D603, 0x65);
    machine.mem_store_byte(0x2D604, 0x26);
    machine.mem_store_byte(0x2D605, 0xF0);
    machine.mem_store_byte(0x2D606, 0x26);
    machine.mem_store_byte(0x2D607, 0x67);
    machine.mem_store_byte(0x2D608, 0x0F);
    machine.mem_store_byte(0x2D609, 0xBA);
    machine.mem_store_byte(0x2D60A, 0xE7);
    machine.mem_store_byte(0x2D60B, 0x3F);
    machine.mem_store_byte(0x2D60C, 0xF4);
    machine.mem_store_byte(0x2D60D, 0x5B);
    machine.mem_store_byte(0x2D60E, 0xC6);
    machine.mem_store_byte(0x2D60F, 0x1E);
    machine.mem_store_byte(0x2D610, 0x04);
    machine.mem_store_byte(0x2D611, 0x18);
    machine.mem_store_byte(0x00018, 0xA6);
    machine.mem_store_byte(0x00019, 0x3A);
    machine.mem_store_byte(0x0001A, 0x40);
    machine.mem_store_byte(0x0001B, 0xA1);
    machine.mem_store_byte(0xA4EA6, 0xF4);
    machine.mem_store_byte(0xA4EA7, 0xD7);
    machine.mem_store_byte(0xA4EA8, 0xF4);
    machine.mem_store_byte(0xA4EA9, 0xDE);
    machine.mem_store_byte(0xA4EAA, 0xF4);
    machine.mem_store_byte(0xA4EAB, 0xA4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF499C6D6);
    EXPECT_EQ(cpu.get_ebx(), 0xF9433D4D);
    EXPECT_EQ(cpu.get_ecx(), 0x634FADD4);
    EXPECT_EQ(cpu.get_edx(), 0x063693B4);
    EXPECT_EQ(cpu.get_esi(), 0x626E4A31);
    EXPECT_EQ(cpu.get_edi(), 0x3ADE9CA7);
    EXPECT_EQ(cpu.get_ebp(), 0x705049D8);
    EXPECT_EQ(cpu.get_esp(), 0x0000A64E);
    EXPECT_EQ(cpu.get_cs(), 0x0000A140);
    EXPECT_EQ(cpu.get_ds(), 0x00003222);
    EXPECT_EQ(cpu.get_es(), 0x00008397);
    EXPECT_EQ(cpu.get_fs(), 0x0000A8E3);
    EXPECT_EQ(cpu.get_gs(), 0x000020AE);
    EXPECT_EQ(cpu.get_ss(), 0x000001AC);
    EXPECT_EQ(cpu.get_eip(), 0x00003AA7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0007);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0C112), 0x07);
    EXPECT_EQ(memory.load8(0x0C113), 0x00);
    EXPECT_EQ(memory.load8(0x0C110), 0xCC);
    EXPECT_EQ(memory.load8(0x0C111), 0x28);
    EXPECT_EQ(memory.load8(0x0C10E), 0x40);
    EXPECT_EQ(memory.load8(0x0C10F), 0x49);
}

//
// lock cmp dword [cs:ebp+BB58h],FFFFFFB1h
//
TEST_F(Test386, lock_cmp_dword_cs_ebp_BB58h_FFFFFFB1h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000400);
    cpu.set_ebx(0x000000F1);
    cpu.set_ecx(0x0FB4BF66);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xF8436EF7);
    cpu.set_edi(0x00007FFF);
    cpu.set_ebp(0x000095A1);
    cpu.set_esp(0x0000FBFE);
    cpu.set_cs(0x00001357);
    cpu.set_ds(0x00000201);
    cpu.set_es(0x000000CF);
    cpu.set_fs(0x0000D5B3);
    cpu.set_gs(0x0000B8C9);
    cpu.set_ss(0x000067DE);
    cpu.set_eip(0x0000BB20);
    cpu.set_eflags(0xFFFC0046);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1F090, 0x2E);
    machine.mem_store_byte(0x1F091, 0xF0);
    machine.mem_store_byte(0x1F092, 0x66);
    machine.mem_store_byte(0x1F093, 0x67);
    machine.mem_store_byte(0x1F094, 0x83);
    machine.mem_store_byte(0x1F095, 0xBD);
    machine.mem_store_byte(0x1F096, 0x58);
    machine.mem_store_byte(0x1F097, 0xBB);
    machine.mem_store_byte(0x1F098, 0x00);
    machine.mem_store_byte(0x1F099, 0x00);
    machine.mem_store_byte(0x1F09A, 0xB1);
    machine.mem_store_byte(0x1F09B, 0xF4);
    machine.mem_store_byte(0x1F09C, 0xFF);
    machine.mem_store_byte(0x1F09D, 0x39);
    machine.mem_store_byte(0x00018, 0x2E);
    machine.mem_store_byte(0x00019, 0x6E);
    machine.mem_store_byte(0x0001A, 0xB1);
    machine.mem_store_byte(0x0001B, 0x9D);
    machine.mem_store_byte(0xA493E, 0xF4);
    machine.mem_store_byte(0xA493F, 0xC9);
    machine.mem_store_byte(0xA4940, 0xF4);
    machine.mem_store_byte(0xA4941, 0x93);
    machine.mem_store_byte(0xA4942, 0xF4);
    machine.mem_store_byte(0xA4943, 0x6A);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000400);
    EXPECT_EQ(cpu.get_ebx(), 0x000000F1);
    EXPECT_EQ(cpu.get_ecx(), 0x0FB4BF66);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xF8436EF7);
    EXPECT_EQ(cpu.get_edi(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebp(), 0x000095A1);
    EXPECT_EQ(cpu.get_esp(), 0x0000FBF8);
    EXPECT_EQ(cpu.get_cs(), 0x00009DB1);
    EXPECT_EQ(cpu.get_ds(), 0x00000201);
    EXPECT_EQ(cpu.get_es(), 0x000000CF);
    EXPECT_EQ(cpu.get_fs(), 0x0000D5B3);
    EXPECT_EQ(cpu.get_gs(), 0x0000B8C9);
    EXPECT_EQ(cpu.get_ss(), 0x000067DE);
    EXPECT_EQ(cpu.get_eip(), 0x00006E2F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x779DC), 0x46);
    EXPECT_EQ(memory.load8(0x779DD), 0x00);
    EXPECT_EQ(memory.load8(0x779DA), 0x57);
    EXPECT_EQ(memory.load8(0x779DB), 0x13);
    EXPECT_EQ(memory.load8(0x779D8), 0x20);
    EXPECT_EQ(memory.load8(0x779D9), 0xBB);
}

//
// lock mov al,[ds:EE9Eh]
//
TEST_F(Test386, lock_mov_al_ds_EE9Eh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x23055590);
    cpu.set_ebx(0x2C80B36A);
    cpu.set_ecx(0xCFAAD080);
    cpu.set_edx(0x558DF363);
    cpu.set_esi(0x428CBD1C);
    cpu.set_edi(0x9FA3324A);
    cpu.set_ebp(0x00010001);
    cpu.set_esp(0x0000CA0A);
    cpu.set_cs(0x00005780);
    cpu.set_ds(0x00003DE7);
    cpu.set_es(0x0000362C);
    cpu.set_fs(0x0000FE05);
    cpu.set_gs(0x0000A4C9);
    cpu.set_ss(0x0000246B);
    cpu.set_eip(0x0000C4E8);
    cpu.set_eflags(0xFFFC0047);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x63CE8, 0xF0);
    machine.mem_store_byte(0x63CE9, 0xA0);
    machine.mem_store_byte(0x63CEA, 0x9E);
    machine.mem_store_byte(0x63CEB, 0xEE);
    machine.mem_store_byte(0x63CEC, 0xF4);
    machine.mem_store_byte(0x63CED, 0x19);
    machine.mem_store_byte(0x63CEE, 0xD8);
    machine.mem_store_byte(0x63CEF, 0xC9);
    machine.mem_store_byte(0x63CF0, 0x1E);
    machine.mem_store_byte(0x63CF1, 0xDC);
    machine.mem_store_byte(0x00018, 0xFB);
    machine.mem_store_byte(0x00019, 0x81);
    machine.mem_store_byte(0x0001A, 0x26);
    machine.mem_store_byte(0x0001B, 0x7D);
    machine.mem_store_byte(0x8545A, 0x4C);
    machine.mem_store_byte(0x8545B, 0xF4);
    machine.mem_store_byte(0x8545C, 0xF7);
    machine.mem_store_byte(0x8545D, 0xF4);
    machine.mem_store_byte(0x8545E, 0xAD);
    machine.mem_store_byte(0x8545F, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x23055590);
    EXPECT_EQ(cpu.get_ebx(), 0x2C80B36A);
    EXPECT_EQ(cpu.get_ecx(), 0xCFAAD080);
    EXPECT_EQ(cpu.get_edx(), 0x558DF363);
    EXPECT_EQ(cpu.get_esi(), 0x428CBD1C);
    EXPECT_EQ(cpu.get_edi(), 0x9FA3324A);
    EXPECT_EQ(cpu.get_ebp(), 0x00010001);
    EXPECT_EQ(cpu.get_esp(), 0x0000CA04);
    EXPECT_EQ(cpu.get_cs(), 0x00007D26);
    EXPECT_EQ(cpu.get_ds(), 0x00003DE7);
    EXPECT_EQ(cpu.get_es(), 0x0000362C);
    EXPECT_EQ(cpu.get_fs(), 0x0000FE05);
    EXPECT_EQ(cpu.get_gs(), 0x0000A4C9);
    EXPECT_EQ(cpu.get_ss(), 0x0000246B);
    EXPECT_EQ(cpu.get_eip(), 0x000081FC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0047);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x310B8), 0x47);
    EXPECT_EQ(memory.load8(0x310B9), 0x00);
    EXPECT_EQ(memory.load8(0x310B6), 0x80);
    EXPECT_EQ(memory.load8(0x310B7), 0x57);
    EXPECT_EQ(memory.load8(0x310B4), 0xE8);
    EXPECT_EQ(memory.load8(0x310B5), 0xC4);
}

//
// lock push 2FA7h
//
TEST_F(Test386, lock_push_2FA7h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1A8C0C41);
    cpu.set_ebx(0x5D0A6DE4);
    cpu.set_ecx(0xB07CA7E2);
    cpu.set_edx(0x62FD7859);
    cpu.set_esi(0xE50C987C);
    cpu.set_edi(0x1FAF3451);
    cpu.set_ebp(0xFFFFFFCF);
    cpu.set_esp(0x0000E128);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000F9FE);
    cpu.set_es(0x0000FB0E);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00007FFF);
    cpu.set_ss(0x0000EB27);
    cpu.set_eip(0x00003DE8);
    cpu.set_eflags(0xFFFC0C92);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x03DE8, 0xF0);
    machine.mem_store_byte(0x03DE9, 0x68);
    machine.mem_store_byte(0x03DEA, 0xA7);
    machine.mem_store_byte(0x03DEB, 0x2F);
    machine.mem_store_byte(0x03DEC, 0xF4);
    machine.mem_store_byte(0x03DED, 0x48);
    machine.mem_store_byte(0x03DEE, 0xFC);
    machine.mem_store_byte(0x03DEF, 0xBB);
    machine.mem_store_byte(0x03DF0, 0x57);
    machine.mem_store_byte(0x03DF1, 0x10);
    machine.mem_store_byte(0x00018, 0x8A);
    machine.mem_store_byte(0x00019, 0xF8);
    machine.mem_store_byte(0x0001A, 0x82);
    machine.mem_store_byte(0x0001B, 0xB4);
    machine.mem_store_byte(0xC40AA, 0xF4);
    machine.mem_store_byte(0xC40AB, 0x5F);
    machine.mem_store_byte(0xC40AC, 0xF4);
    machine.mem_store_byte(0xC40AD, 0xDA);
    machine.mem_store_byte(0xC40AE, 0xF4);
    machine.mem_store_byte(0xC40AF, 0x1C);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1A8C0C41);
    EXPECT_EQ(cpu.get_ebx(), 0x5D0A6DE4);
    EXPECT_EQ(cpu.get_ecx(), 0xB07CA7E2);
    EXPECT_EQ(cpu.get_edx(), 0x62FD7859);
    EXPECT_EQ(cpu.get_esi(), 0xE50C987C);
    EXPECT_EQ(cpu.get_edi(), 0x1FAF3451);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFFFFCF);
    EXPECT_EQ(cpu.get_esp(), 0x0000E122);
    EXPECT_EQ(cpu.get_cs(), 0x0000B482);
    EXPECT_EQ(cpu.get_ds(), 0x0000F9FE);
    EXPECT_EQ(cpu.get_es(), 0x0000FB0E);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ss(), 0x0000EB27);
    EXPECT_EQ(cpu.get_eip(), 0x0000F88B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C92);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF9396), 0x92);
    EXPECT_EQ(memory.load8(0xF9397), 0x0C);
    EXPECT_EQ(memory.load8(0xF9394), 0x00);
    EXPECT_EQ(memory.load8(0xF9395), 0x00);
    EXPECT_EQ(memory.load8(0xF9392), 0xE8);
    EXPECT_EQ(memory.load8(0xF9393), 0x3D);
}

//
// lock rcl dword [ds:edx+82Bh],1
//
TEST_F(Test386, lock_rcl_dword_ds_edx_82Bh_1)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x6E2C0EB4);
    cpu.set_ebx(0xC1326C73);
    cpu.set_ecx(0x744D720B);
    cpu.set_edx(0x0000B935);
    cpu.set_esi(0xFDE25B6A);
    cpu.set_edi(0xD4902A94);
    cpu.set_ebp(0x8AD61098);
    cpu.set_esp(0x00003E20);
    cpu.set_cs(0x000032F5);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x0000AD78);
    cpu.set_fs(0x000007BC);
    cpu.set_gs(0x00001A08);
    cpu.set_ss(0x00001349);
    cpu.set_eip(0x000088A8);
    cpu.set_eflags(0xFFFC0C93);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3B7F8, 0xF0);
    machine.mem_store_byte(0x3B7F9, 0x66);
    machine.mem_store_byte(0x3B7FA, 0x67);
    machine.mem_store_byte(0x3B7FB, 0xD1);
    machine.mem_store_byte(0x3B7FC, 0x92);
    machine.mem_store_byte(0x3B7FD, 0x2B);
    machine.mem_store_byte(0x3B7FE, 0x08);
    machine.mem_store_byte(0x3B7FF, 0x00);
    machine.mem_store_byte(0x3B800, 0x00);
    machine.mem_store_byte(0x3B801, 0xF4);
    machine.mem_store_byte(0x3B802, 0x12);
    machine.mem_store_byte(0x3B803, 0x9F);
    machine.mem_store_byte(0x00018, 0x40);
    machine.mem_store_byte(0x00019, 0x46);
    machine.mem_store_byte(0x0001A, 0xAB);
    machine.mem_store_byte(0x0001B, 0xF0);
    machine.mem_store_byte(0xF50F0, 0xF4);
    machine.mem_store_byte(0xF50F1, 0xE3);
    machine.mem_store_byte(0xF50F2, 0xF4);
    machine.mem_store_byte(0xF50F3, 0xB8);
    machine.mem_store_byte(0xF50F4, 0xF4);
    machine.mem_store_byte(0xF50F5, 0x1F);
    machine.mem_store_byte(0xF50F6, 0xF4);
    machine.mem_store_byte(0xF50F7, 0x90);
    machine.mem_store_byte(0xF50F8, 0xF4);
    machine.mem_store_byte(0xF50F9, 0x6C);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x6E2C0EB4);
    EXPECT_EQ(cpu.get_ebx(), 0xC1326C73);
    EXPECT_EQ(cpu.get_ecx(), 0x744D720B);
    EXPECT_EQ(cpu.get_edx(), 0x0000B935);
    EXPECT_EQ(cpu.get_esi(), 0xFDE25B6A);
    EXPECT_EQ(cpu.get_edi(), 0xD4902A94);
    EXPECT_EQ(cpu.get_ebp(), 0x8AD61098);
    EXPECT_EQ(cpu.get_esp(), 0x00003E1A);
    EXPECT_EQ(cpu.get_cs(), 0x0000F0AB);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x0000AD78);
    EXPECT_EQ(cpu.get_fs(), 0x000007BC);
    EXPECT_EQ(cpu.get_gs(), 0x00001A08);
    EXPECT_EQ(cpu.get_ss(), 0x00001349);
    EXPECT_EQ(cpu.get_eip(), 0x00004641);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C93);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x172AE), 0x93);
    EXPECT_EQ(memory.load8(0x172AF), 0x0C);
    EXPECT_EQ(memory.load8(0x172AC), 0xF5);
    EXPECT_EQ(memory.load8(0x172AD), 0x32);
    EXPECT_EQ(memory.load8(0x172AA), 0xA8);
    EXPECT_EQ(memory.load8(0x172AB), 0x88);
}

//
// lock rcr byte [ds:esi+eax*4-4Bh],78h
//
TEST_F(Test386, lock_rcr_byte_ds_esi_eax_4_4Bh_78h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0000054D);
    cpu.set_ebx(0x0594559A);
    cpu.set_ecx(0x9C12F69B);
    cpu.set_edx(0xE4992478);
    cpu.set_esi(0x00001A82);
    cpu.set_edi(0x7145897E);
    cpu.set_ebp(0x50845508);
    cpu.set_esp(0x00007FFE);
    cpu.set_cs(0x0000FFFB);
    cpu.set_ds(0x00001BAA);
    cpu.set_es(0x0000FE86);
    cpu.set_fs(0x00001D20);
    cpu.set_gs(0x0000BA0A);
    cpu.set_ss(0x0000A850);
    cpu.set_eip(0x0000CBD0);
    cpu.set_eflags(0xFFFC08C2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10CB80, 0xF0);
    machine.mem_store_byte(0x10CB81, 0x67);
    machine.mem_store_byte(0x10CB82, 0xC0);
    machine.mem_store_byte(0x10CB83, 0x5C);
    machine.mem_store_byte(0x10CB84, 0x86);
    machine.mem_store_byte(0x10CB85, 0xB5);
    machine.mem_store_byte(0x10CB86, 0x78);
    machine.mem_store_byte(0x10CB87, 0xF4);
    machine.mem_store_byte(0x10CB88, 0x97);
    machine.mem_store_byte(0x10CB89, 0xB8);
    machine.mem_store_byte(0x10CB8A, 0xB3);
    machine.mem_store_byte(0x10CB8B, 0xC1);
    machine.mem_store_byte(0x00018, 0x51);
    machine.mem_store_byte(0x00019, 0x1F);
    machine.mem_store_byte(0x0001A, 0x9D);
    machine.mem_store_byte(0x0001B, 0xBD);
    machine.mem_store_byte(0xBF920, 0xC6);
    machine.mem_store_byte(0xBF921, 0xF4);
    machine.mem_store_byte(0xBF922, 0x87);
    machine.mem_store_byte(0xBF923, 0xF4);
    machine.mem_store_byte(0xBF924, 0x3A);
    machine.mem_store_byte(0xBF925, 0xF4);
    machine.mem_store_byte(0xBF926, 0x7A);
    machine.mem_store_byte(0xBF927, 0xF4);
    machine.mem_store_byte(0xBF928, 0x74);
    machine.mem_store_byte(0xBF929, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0000054D);
    EXPECT_EQ(cpu.get_ebx(), 0x0594559A);
    EXPECT_EQ(cpu.get_ecx(), 0x9C12F69B);
    EXPECT_EQ(cpu.get_edx(), 0xE4992478);
    EXPECT_EQ(cpu.get_esi(), 0x00001A82);
    EXPECT_EQ(cpu.get_edi(), 0x7145897E);
    EXPECT_EQ(cpu.get_ebp(), 0x50845508);
    EXPECT_EQ(cpu.get_esp(), 0x00007FF8);
    EXPECT_EQ(cpu.get_cs(), 0x0000BD9D);
    EXPECT_EQ(cpu.get_ds(), 0x00001BAA);
    EXPECT_EQ(cpu.get_es(), 0x0000FE86);
    EXPECT_EQ(cpu.get_fs(), 0x00001D20);
    EXPECT_EQ(cpu.get_gs(), 0x0000BA0A);
    EXPECT_EQ(cpu.get_ss(), 0x0000A850);
    EXPECT_EQ(cpu.get_eip(), 0x00001F52);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB04FC), 0xC2);
    EXPECT_EQ(memory.load8(0xB04FD), 0x08);
    EXPECT_EQ(memory.load8(0xB04FA), 0xFB);
    EXPECT_EQ(memory.load8(0xB04FB), 0xFF);
    EXPECT_EQ(memory.load8(0xB04F8), 0xD0);
    EXPECT_EQ(memory.load8(0xB04F9), 0xCB);
}

//
// lock rol dword [ss:bp+di-5941h],1
//
TEST_F(Test386, lock_rol_dword_ss_bp_di_5941h_1)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE33BE6F4);
    cpu.set_ebx(0x03292325);
    cpu.set_ecx(0xBB9070A0);
    cpu.set_edx(0x30B59A47);
    cpu.set_esi(0x04793F50);
    cpu.set_edi(0x094CA000);
    cpu.set_ebp(0xD9A91878);
    cpu.set_esp(0x00005584);
    cpu.set_cs(0x000000F0);
    cpu.set_ds(0x00004ACF);
    cpu.set_es(0x00000190);
    cpu.set_fs(0x0000FD6A);
    cpu.set_gs(0x0000D419);
    cpu.set_ss(0x0000FFF2);
    cpu.set_eip(0x000074C8);
    cpu.set_eflags(0xFFFC0843);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x083C8, 0xF0);
    machine.mem_store_byte(0x083C9, 0x66);
    machine.mem_store_byte(0x083CA, 0xD1);
    machine.mem_store_byte(0x083CB, 0x83);
    machine.mem_store_byte(0x083CC, 0xBF);
    machine.mem_store_byte(0x083CD, 0xA6);
    machine.mem_store_byte(0x083CE, 0xF4);
    machine.mem_store_byte(0x083CF, 0x1A);
    machine.mem_store_byte(0x083D0, 0xF8);
    machine.mem_store_byte(0x083D1, 0x97);
    machine.mem_store_byte(0x083D2, 0x9B);
    machine.mem_store_byte(0x083D3, 0x40);
    machine.mem_store_byte(0x00018, 0x0F);
    machine.mem_store_byte(0x00019, 0xF1);
    machine.mem_store_byte(0x0001A, 0xC9);
    machine.mem_store_byte(0x0001B, 0xED);
    machine.mem_store_byte(0xFCD9E, 0x6A);
    machine.mem_store_byte(0xFCD9F, 0xF4);
    machine.mem_store_byte(0xFCDA0, 0x82);
    machine.mem_store_byte(0xFCDA1, 0xF4);
    machine.mem_store_byte(0xFCDA2, 0x62);
    machine.mem_store_byte(0xFCDA3, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE33BE6F4);
    EXPECT_EQ(cpu.get_ebx(), 0x03292325);
    EXPECT_EQ(cpu.get_ecx(), 0xBB9070A0);
    EXPECT_EQ(cpu.get_edx(), 0x30B59A47);
    EXPECT_EQ(cpu.get_esi(), 0x04793F50);
    EXPECT_EQ(cpu.get_edi(), 0x094CA000);
    EXPECT_EQ(cpu.get_ebp(), 0xD9A91878);
    EXPECT_EQ(cpu.get_esp(), 0x0000557E);
    EXPECT_EQ(cpu.get_cs(), 0x0000EDC9);
    EXPECT_EQ(cpu.get_ds(), 0x00004ACF);
    EXPECT_EQ(cpu.get_es(), 0x00000190);
    EXPECT_EQ(cpu.get_fs(), 0x0000FD6A);
    EXPECT_EQ(cpu.get_gs(), 0x0000D419);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFF2);
    EXPECT_EQ(cpu.get_eip(), 0x0000F110);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0843);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1054A2), 0x43);
    EXPECT_EQ(memory.load8(0x1054A3), 0x08);
    EXPECT_EQ(memory.load8(0x1054A0), 0xF0);
    EXPECT_EQ(memory.load8(0x1054A1), 0x00);
    EXPECT_EQ(memory.load8(0x10549E), 0xC8);
    EXPECT_EQ(memory.load8(0x10549F), 0x74);
}

//
// lock setge al
//
TEST_F(Test386, lock_setge_al)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x35CDE86B);
    cpu.set_ebx(0xB1FF79C7);
    cpu.set_ecx(0x351DD917);
    cpu.set_edx(0xFF5977C5);
    cpu.set_esi(0x04A36244);
    cpu.set_edi(0x00007FFF);
    cpu.set_ebp(0xE038A20E);
    cpu.set_esp(0x0000BEDE);
    cpu.set_cs(0x0000991D);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x0000D592);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x0000C1DB);
    cpu.set_eip(0x0000F3D0);
    cpu.set_eflags(0xFFFC04C7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA85A0, 0xF0);
    machine.mem_store_byte(0xA85A1, 0x67);
    machine.mem_store_byte(0xA85A2, 0x0F);
    machine.mem_store_byte(0xA85A3, 0x9D);
    machine.mem_store_byte(0xA85A4, 0xD0);
    machine.mem_store_byte(0xA85A5, 0xF4);
    machine.mem_store_byte(0xA85A6, 0x92);
    machine.mem_store_byte(0xA85A7, 0xE8);
    machine.mem_store_byte(0xA85A8, 0x9C);
    machine.mem_store_byte(0xA85A9, 0xF4);
    machine.mem_store_byte(0xA85AA, 0x56);
    machine.mem_store_byte(0xA85AB, 0x00);
    machine.mem_store_byte(0x00018, 0x66);
    machine.mem_store_byte(0x00019, 0x54);
    machine.mem_store_byte(0x0001A, 0x37);
    machine.mem_store_byte(0x0001B, 0xB1);
    machine.mem_store_byte(0xB67D6, 0xF4);
    machine.mem_store_byte(0xB67D7, 0xFB);
    machine.mem_store_byte(0xB67D8, 0xF4);
    machine.mem_store_byte(0xB67D9, 0xE7);
    machine.mem_store_byte(0xB67DA, 0xF4);
    machine.mem_store_byte(0xB67DB, 0x30);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x35CDE86B);
    EXPECT_EQ(cpu.get_ebx(), 0xB1FF79C7);
    EXPECT_EQ(cpu.get_ecx(), 0x351DD917);
    EXPECT_EQ(cpu.get_edx(), 0xFF5977C5);
    EXPECT_EQ(cpu.get_esi(), 0x04A36244);
    EXPECT_EQ(cpu.get_edi(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ebp(), 0xE038A20E);
    EXPECT_EQ(cpu.get_esp(), 0x0000BED8);
    EXPECT_EQ(cpu.get_cs(), 0x0000B137);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x0000D592);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x0000C1DB);
    EXPECT_EQ(cpu.get_eip(), 0x00005467);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCDC8C), 0xC7);
    EXPECT_EQ(memory.load8(0xCDC8D), 0x04);
    EXPECT_EQ(memory.load8(0xCDC8A), 0x1D);
    EXPECT_EQ(memory.load8(0xCDC8B), 0x99);
    EXPECT_EQ(memory.load8(0xCDC88), 0xD0);
    EXPECT_EQ(memory.load8(0xCDC89), 0xF3);
}
