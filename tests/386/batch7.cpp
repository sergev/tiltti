#include "test386.h"

//
// (bad) lgs bx,dx
//
TEST_F(Test386, bad_lgs_bx_dx_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x289327B2);
    cpu.set_ebx(0xFFFFDF94);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0xA5DE6444);
    cpu.set_esi(0xA5CF700A);
    cpu.set_edi(0x267D9E51);
    cpu.set_ebp(0x516F24CC);
    cpu.set_esp(0x00007360);
    cpu.set_cs(0x00006DC6);
    cpu.set_ds(0x00000456);
    cpu.set_es(0x0000687E);
    cpu.set_fs(0x000032C5);
    cpu.set_gs(0x00005129);
    cpu.set_ss(0x0000FDED);
    cpu.set_eip(0x00007F78);
    cpu.set_eflags(0xFFFC0C06);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x75BD8, 0x67);
    machine.mem_store_byte(0x75BD9, 0x0F);
    machine.mem_store_byte(0x75BDA, 0xB5);
    machine.mem_store_byte(0x75BDB, 0xDA);
    machine.mem_store_byte(0x75BDC, 0xF4);
    machine.mem_store_byte(0x75BDD, 0x1B);
    machine.mem_store_byte(0x75BDE, 0xAE);
    machine.mem_store_byte(0x75BDF, 0x65);
    machine.mem_store_byte(0x75BE0, 0x17);
    machine.mem_store_byte(0x75BE1, 0xD5);
    machine.mem_store_byte(0x75BE2, 0x66);
    machine.mem_store_byte(0x75BE3, 0xFF);
    machine.mem_store_byte(0x75BE4, 0x4A);
    machine.mem_store_byte(0x75BE5, 0x71);
    machine.mem_store_byte(0x75BE6, 0x7A);
    machine.mem_store_byte(0x75BE7, 0x08);
    machine.mem_store_byte(0x00018, 0xDC);
    machine.mem_store_byte(0x00019, 0xAF);
    machine.mem_store_byte(0x0001A, 0x22);
    machine.mem_store_byte(0x0001B, 0xB0);
    machine.mem_store_byte(0xBB1FC, 0xF4);
    machine.mem_store_byte(0xBB1FD, 0x51);
    machine.mem_store_byte(0xBB1FE, 0xF4);
    machine.mem_store_byte(0xBB1FF, 0xD2);
    machine.mem_store_byte(0xBB200, 0xF4);
    machine.mem_store_byte(0xBB201, 0xA1);
    machine.mem_store_byte(0xBB202, 0xF4);
    machine.mem_store_byte(0xBB203, 0x8D);
    machine.mem_store_byte(0xBB204, 0xF4);
    machine.mem_store_byte(0xBB205, 0x6E);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x289327B2);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFDF94);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xA5DE6444);
    EXPECT_EQ(cpu.get_esi(), 0xA5CF700A);
    EXPECT_EQ(cpu.get_edi(), 0x267D9E51);
    EXPECT_EQ(cpu.get_ebp(), 0x516F24CC);
    EXPECT_EQ(cpu.get_esp(), 0x0000735A);
    EXPECT_EQ(cpu.get_cs(), 0x0000B022);
    EXPECT_EQ(cpu.get_ds(), 0x00000456);
    EXPECT_EQ(cpu.get_es(), 0x0000687E);
    EXPECT_EQ(cpu.get_fs(), 0x000032C5);
    EXPECT_EQ(cpu.get_gs(), 0x00005129);
    EXPECT_EQ(cpu.get_ss(), 0x0000FDED);
    EXPECT_EQ(cpu.get_eip(), 0x0000AFDD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C06);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x10522E), 0x06);
    EXPECT_EQ(memory.load8(0x10522F), 0x0C);
    EXPECT_EQ(memory.load8(0x10522C), 0xC6);
    EXPECT_EQ(memory.load8(0x10522D), 0x6D);
    EXPECT_EQ(memory.load8(0x10522A), 0x78);
    EXPECT_EQ(memory.load8(0x10522B), 0x7F);
}

//
// (bad) lgs ebx,edx
//
TEST_F(Test386, bad_lgs_ebx_edx_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x289327B2);
    cpu.set_ebx(0xFFFFDF94);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0xA5DE6444);
    cpu.set_esi(0xA5CF700A);
    cpu.set_edi(0x267D9E51);
    cpu.set_ebp(0x516F24CC);
    cpu.set_esp(0x00007360);
    cpu.set_cs(0x00006DC6);
    cpu.set_ds(0x00000456);
    cpu.set_es(0x0000687E);
    cpu.set_fs(0x000032C5);
    cpu.set_gs(0x00005129);
    cpu.set_ss(0x0000FDED);
    cpu.set_eip(0x00007F78);
    cpu.set_eflags(0xFFFC0C06);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x75BD8, 0x67);
    machine.mem_store_byte(0x75BD9, 0x66);
    machine.mem_store_byte(0x75BDA, 0x0F);
    machine.mem_store_byte(0x75BDB, 0xB5);
    machine.mem_store_byte(0x75BDC, 0xDA);
    machine.mem_store_byte(0x75BDD, 0xF4);
    machine.mem_store_byte(0x75BDE, 0xAE);
    machine.mem_store_byte(0x75BDF, 0x65);
    machine.mem_store_byte(0x75BE0, 0x17);
    machine.mem_store_byte(0x75BE1, 0xD5);
    machine.mem_store_byte(0x75BE2, 0x66);
    machine.mem_store_byte(0x75BE3, 0xFF);
    machine.mem_store_byte(0x75BE4, 0x4A);
    machine.mem_store_byte(0x75BE5, 0x71);
    machine.mem_store_byte(0x75BE6, 0x7A);
    machine.mem_store_byte(0x75BE7, 0x08);
    machine.mem_store_byte(0x00018, 0xDC);
    machine.mem_store_byte(0x00019, 0xAF);
    machine.mem_store_byte(0x0001A, 0x22);
    machine.mem_store_byte(0x0001B, 0xB0);
    machine.mem_store_byte(0xBB1FC, 0xF4);
    machine.mem_store_byte(0xBB1FD, 0x51);
    machine.mem_store_byte(0xBB1FE, 0xF4);
    machine.mem_store_byte(0xBB1FF, 0xD2);
    machine.mem_store_byte(0xBB200, 0xF4);
    machine.mem_store_byte(0xBB201, 0xA1);
    machine.mem_store_byte(0xBB202, 0xF4);
    machine.mem_store_byte(0xBB203, 0x8D);
    machine.mem_store_byte(0xBB204, 0xF4);
    machine.mem_store_byte(0xBB205, 0x6E);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x289327B2);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFDF94);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xA5DE6444);
    EXPECT_EQ(cpu.get_esi(), 0xA5CF700A);
    EXPECT_EQ(cpu.get_edi(), 0x267D9E51);
    EXPECT_EQ(cpu.get_ebp(), 0x516F24CC);
    EXPECT_EQ(cpu.get_esp(), 0x0000735A);
    EXPECT_EQ(cpu.get_cs(), 0x0000B022);
    EXPECT_EQ(cpu.get_ds(), 0x00000456);
    EXPECT_EQ(cpu.get_es(), 0x0000687E);
    EXPECT_EQ(cpu.get_fs(), 0x000032C5);
    EXPECT_EQ(cpu.get_gs(), 0x00005129);
    EXPECT_EQ(cpu.get_ss(), 0x0000FDED);
    EXPECT_EQ(cpu.get_eip(), 0x0000AFDD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C06);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x10522E), 0x06);
    EXPECT_EQ(memory.load8(0x10522F), 0x0C);
    EXPECT_EQ(memory.load8(0x10522C), 0xC6);
    EXPECT_EQ(memory.load8(0x10522D), 0x6D);
    EXPECT_EQ(memory.load8(0x10522A), 0x78);
    EXPECT_EQ(memory.load8(0x10522B), 0x7F);
}

//
// (bad) mov byte [ds:edi+BC311D2h],1Bh
//
TEST_F(Test386, bad_mov_byte_ds_edi_BC311D2h_1Bh_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1245DE87);
    cpu.set_ebx(0x9557578C);
    cpu.set_ecx(0x0EFA7AF4);
    cpu.set_edx(0x00000010);
    cpu.set_esi(0x393D4369);
    cpu.set_edi(0x19B87FBD);
    cpu.set_ebp(0x41883E75);
    cpu.set_esp(0x00003776);
    cpu.set_cs(0x000082E7);
    cpu.set_ds(0x0000ECE6);
    cpu.set_es(0x00009F78);
    cpu.set_fs(0x0000F5C0);
    cpu.set_gs(0x00000001);
    cpu.set_ss(0x0000CED8);
    cpu.set_eip(0x00007C80);
    cpu.set_eflags(0xFFFC0013);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8AAF0, 0x67);
    machine.mem_store_byte(0x8AAF1, 0xC6);
    machine.mem_store_byte(0x8AAF2, 0x97);
    machine.mem_store_byte(0x8AAF3, 0xD2);
    machine.mem_store_byte(0x8AAF4, 0x11);
    machine.mem_store_byte(0x8AAF5, 0xC3);
    machine.mem_store_byte(0x8AAF6, 0x0B);
    machine.mem_store_byte(0x8AAF7, 0x1B);
    machine.mem_store_byte(0x8AAF8, 0xF4);
    machine.mem_store_byte(0x8AAF9, 0x23);
    machine.mem_store_byte(0x8AAFA, 0x2E);
    machine.mem_store_byte(0x8AAFB, 0x55);
    machine.mem_store_byte(0x8AAFC, 0x31);
    machine.mem_store_byte(0x8AAFD, 0xFF);
    machine.mem_store_byte(0x8AAFE, 0xDE);
    machine.mem_store_byte(0x8AAFF, 0x06);
    machine.mem_store_byte(0x8AB00, 0x54);
    machine.mem_store_byte(0x8AB01, 0xEB);
    machine.mem_store_byte(0x00018, 0xCE);
    machine.mem_store_byte(0x00019, 0x07);
    machine.mem_store_byte(0x0001A, 0x57);
    machine.mem_store_byte(0x0001B, 0x94);
    machine.mem_store_byte(0x94D3E, 0xF4);
    machine.mem_store_byte(0x94D3F, 0x05);
    machine.mem_store_byte(0x94D40, 0xF4);
    machine.mem_store_byte(0x94D41, 0xA9);
    machine.mem_store_byte(0x94D42, 0xF4);
    machine.mem_store_byte(0x94D43, 0xB0);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1245DE87);
    EXPECT_EQ(cpu.get_ebx(), 0x9557578C);
    EXPECT_EQ(cpu.get_ecx(), 0x0EFA7AF4);
    EXPECT_EQ(cpu.get_edx(), 0x00000010);
    EXPECT_EQ(cpu.get_esi(), 0x393D4369);
    EXPECT_EQ(cpu.get_edi(), 0x19B87FBD);
    EXPECT_EQ(cpu.get_ebp(), 0x41883E75);
    EXPECT_EQ(cpu.get_esp(), 0x00003770);
    EXPECT_EQ(cpu.get_cs(), 0x00009457);
    EXPECT_EQ(cpu.get_ds(), 0x0000ECE6);
    EXPECT_EQ(cpu.get_es(), 0x00009F78);
    EXPECT_EQ(cpu.get_fs(), 0x0000F5C0);
    EXPECT_EQ(cpu.get_gs(), 0x00000001);
    EXPECT_EQ(cpu.get_ss(), 0x0000CED8);
    EXPECT_EQ(cpu.get_eip(), 0x000007CF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD24F4), 0x13);
    EXPECT_EQ(memory.load8(0xD24F5), 0x00);
    EXPECT_EQ(memory.load8(0xD24F2), 0xE7);
    EXPECT_EQ(memory.load8(0xD24F3), 0x82);
    EXPECT_EQ(memory.load8(0xD24F0), 0x80);
    EXPECT_EQ(memory.load8(0xD24F1), 0x7C);
}

//
// (bad) mov byte [ss:bp-30C0h],D2h
//
TEST_F(Test386, bad_mov_byte_ss_bp_30C0h_D2h_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1245DE87);
    cpu.set_ebx(0x9557578C);
    cpu.set_ecx(0x0EFA7AF4);
    cpu.set_edx(0x00000010);
    cpu.set_esi(0x393D4369);
    cpu.set_edi(0x19B87FBD);
    cpu.set_ebp(0x41883E75);
    cpu.set_esp(0x00003776);
    cpu.set_cs(0x000082E7);
    cpu.set_ds(0x0000ECE6);
    cpu.set_es(0x00009F78);
    cpu.set_fs(0x0000F5C0);
    cpu.set_gs(0x00000001);
    cpu.set_ss(0x0000CED8);
    cpu.set_eip(0x00007C80);
    cpu.set_eflags(0xFFFC0013);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8AAF0, 0xC6);
    machine.mem_store_byte(0x8AAF1, 0x96);
    machine.mem_store_byte(0x8AAF2, 0x40);
    machine.mem_store_byte(0x8AAF3, 0xCF);
    machine.mem_store_byte(0x8AAF4, 0xD2);
    machine.mem_store_byte(0x8AAF5, 0xF4);
    machine.mem_store_byte(0x8AAF6, 0xDF);
    machine.mem_store_byte(0x8AAF7, 0xC7);
    machine.mem_store_byte(0x8AAF8, 0xE6);
    machine.mem_store_byte(0x8AAF9, 0x23);
    machine.mem_store_byte(0x8AAFA, 0x2E);
    machine.mem_store_byte(0x8AAFB, 0x55);
    machine.mem_store_byte(0x8AAFC, 0x31);
    machine.mem_store_byte(0x8AAFD, 0xFF);
    machine.mem_store_byte(0x8AAFE, 0xDE);
    machine.mem_store_byte(0x8AAFF, 0x06);
    machine.mem_store_byte(0x00018, 0xCE);
    machine.mem_store_byte(0x00019, 0x07);
    machine.mem_store_byte(0x0001A, 0x57);
    machine.mem_store_byte(0x0001B, 0x94);
    machine.mem_store_byte(0x94D3E, 0xF4);
    machine.mem_store_byte(0x94D3F, 0x05);
    machine.mem_store_byte(0x94D40, 0xF4);
    machine.mem_store_byte(0x94D41, 0xA9);
    machine.mem_store_byte(0x94D42, 0xF4);
    machine.mem_store_byte(0x94D43, 0xB0);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1245DE87);
    EXPECT_EQ(cpu.get_ebx(), 0x9557578C);
    EXPECT_EQ(cpu.get_ecx(), 0x0EFA7AF4);
    EXPECT_EQ(cpu.get_edx(), 0x00000010);
    EXPECT_EQ(cpu.get_esi(), 0x393D4369);
    EXPECT_EQ(cpu.get_edi(), 0x19B87FBD);
    EXPECT_EQ(cpu.get_ebp(), 0x41883E75);
    EXPECT_EQ(cpu.get_esp(), 0x00003770);
    EXPECT_EQ(cpu.get_cs(), 0x00009457);
    EXPECT_EQ(cpu.get_ds(), 0x0000ECE6);
    EXPECT_EQ(cpu.get_es(), 0x00009F78);
    EXPECT_EQ(cpu.get_fs(), 0x0000F5C0);
    EXPECT_EQ(cpu.get_gs(), 0x00000001);
    EXPECT_EQ(cpu.get_ss(), 0x0000CED8);
    EXPECT_EQ(cpu.get_eip(), 0x000007CF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD24F4), 0x13);
    EXPECT_EQ(memory.load8(0xD24F5), 0x00);
    EXPECT_EQ(memory.load8(0xD24F2), 0xE7);
    EXPECT_EQ(memory.load8(0xD24F3), 0x82);
    EXPECT_EQ(memory.load8(0xD24F0), 0x80);
    EXPECT_EQ(memory.load8(0xD24F1), 0x7C);
}

//
// cmpsd
//
TEST_F(Test386, cmpsd_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xEA5A03AA);
    cpu.set_ebx(0x41666144);
    cpu.set_ecx(0xE1586CB0);
    cpu.set_edx(0x1A384AF0);
    cpu.set_esi(0xEBF0787B);
    cpu.set_edi(0xFBFFFFFF);
    cpu.set_ebp(0x8C44663A);
    cpu.set_esp(0x0000B622);
    cpu.set_cs(0x0000054C);
    cpu.set_ds(0x0000F185);
    cpu.set_es(0x00001C63);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00006A17);
    cpu.set_ss(0x0000C029);
    cpu.set_eip(0x000066B0);
    cpu.set_eflags(0xFFFC0497);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0BB70, 0x66);
    machine.mem_store_byte(0x0BB71, 0xA7);
    machine.mem_store_byte(0x0BB72, 0xF4);
    machine.mem_store_byte(0x0BB73, 0x00);
    machine.mem_store_byte(0x0BB74, 0x00);
    machine.mem_store_byte(0x0BB75, 0x00);
    machine.mem_store_byte(0x0BB76, 0x00);
    machine.mem_store_byte(0x0BB77, 0x00);
    machine.mem_store_byte(0x0BB78, 0x00);
    machine.mem_store_byte(0x0BB79, 0x00);
    machine.mem_store_byte(0x0BB7A, 0x00);
    machine.mem_store_byte(0x0BB7B, 0x00);
    machine.mem_store_byte(0x0BB7C, 0x00);
    machine.mem_store_byte(0x0BB7D, 0x00);
    machine.mem_store_byte(0x0BB7E, 0x00);
    machine.mem_store_byte(0x0BB7F, 0x00);
    machine.mem_store_byte(0x00034, 0xB4);
    machine.mem_store_byte(0x00035, 0x61);
    machine.mem_store_byte(0x00036, 0x56);
    machine.mem_store_byte(0x00037, 0xA0);
    machine.mem_store_byte(0xA6714, 0xF4);
    machine.mem_store_byte(0xA6715, 0x00);
    machine.mem_store_byte(0xA6716, 0xF4);
    machine.mem_store_byte(0xA6717, 0x00);
    machine.mem_store_byte(0xA6718, 0xF4);
    machine.mem_store_byte(0xA6719, 0x00);
    machine.mem_store_byte(0xA671A, 0xF4);
    machine.mem_store_byte(0xA671B, 0x00);
    machine.mem_store_byte(0xA671C, 0xF4);
    machine.mem_store_byte(0xA671D, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xEA5A03AA);
    EXPECT_EQ(cpu.get_ebx(), 0x41666144);
    EXPECT_EQ(cpu.get_ecx(), 0xE1586CB0);
    EXPECT_EQ(cpu.get_edx(), 0x1A384AF0);
    EXPECT_EQ(cpu.get_esi(), 0xEBF0787B);
    EXPECT_EQ(cpu.get_edi(), 0xFBFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x8C44663A);
    EXPECT_EQ(cpu.get_esp(), 0x0000B61C);
    EXPECT_EQ(cpu.get_cs(), 0x0000A056);
    EXPECT_EQ(cpu.get_ds(), 0x0000F185);
    EXPECT_EQ(cpu.get_es(), 0x00001C63);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00006A17);
    EXPECT_EQ(cpu.get_ss(), 0x0000C029);
    EXPECT_EQ(cpu.get_eip(), 0x000061B5);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCB8B0), 0x97);
    EXPECT_EQ(memory.load8(0xCB8B1), 0x04);
    EXPECT_EQ(memory.load8(0xCB8AE), 0x4C);
    EXPECT_EQ(memory.load8(0xCB8AF), 0x05);
    EXPECT_EQ(memory.load8(0xCB8AC), 0xB0);
    EXPECT_EQ(memory.load8(0xCB8AD), 0x66);
}

//
// cmpsw
//
TEST_F(Test386, cmpsw_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xEA5A03AA);
    cpu.set_ebx(0x41666144);
    cpu.set_ecx(0xE1586CB0);
    cpu.set_edx(0x1A384AF0);
    cpu.set_esi(0xEBF0787B);
    cpu.set_edi(0xFBFFFFFF);
    cpu.set_ebp(0x8C44663A);
    cpu.set_esp(0x0000B622);
    cpu.set_cs(0x0000054C);
    cpu.set_ds(0x0000F185);
    cpu.set_es(0x00001C63);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00006A17);
    cpu.set_ss(0x0000C029);
    cpu.set_eip(0x000066B0);
    cpu.set_eflags(0xFFFC0497);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0BB70, 0xA7);
    machine.mem_store_byte(0x0BB71, 0xF4);
    machine.mem_store_byte(0x0BB72, 0x00);
    machine.mem_store_byte(0x0BB73, 0x00);
    machine.mem_store_byte(0x0BB74, 0x00);
    machine.mem_store_byte(0x0BB75, 0x00);
    machine.mem_store_byte(0x0BB76, 0x00);
    machine.mem_store_byte(0x0BB77, 0x00);
    machine.mem_store_byte(0x0BB78, 0x00);
    machine.mem_store_byte(0x0BB79, 0x00);
    machine.mem_store_byte(0x0BB7A, 0x00);
    machine.mem_store_byte(0x0BB7B, 0x00);
    machine.mem_store_byte(0x0BB7C, 0x00);
    machine.mem_store_byte(0x0BB7D, 0x00);
    machine.mem_store_byte(0x0BB7E, 0x00);
    machine.mem_store_byte(0x0BB7F, 0x00);
    machine.mem_store_byte(0x00034, 0xB4);
    machine.mem_store_byte(0x00035, 0x61);
    machine.mem_store_byte(0x00036, 0x56);
    machine.mem_store_byte(0x00037, 0xA0);
    machine.mem_store_byte(0xA6714, 0xF4);
    machine.mem_store_byte(0xA6715, 0x00);
    machine.mem_store_byte(0xA6716, 0xF4);
    machine.mem_store_byte(0xA6717, 0x00);
    machine.mem_store_byte(0xA6718, 0xF4);
    machine.mem_store_byte(0xA6719, 0x00);
    machine.mem_store_byte(0xA671A, 0xF4);
    machine.mem_store_byte(0xA671B, 0x00);
    machine.mem_store_byte(0xA671C, 0xF4);
    machine.mem_store_byte(0xA671D, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xEA5A03AA);
    EXPECT_EQ(cpu.get_ebx(), 0x41666144);
    EXPECT_EQ(cpu.get_ecx(), 0xE1586CB0);
    EXPECT_EQ(cpu.get_edx(), 0x1A384AF0);
    EXPECT_EQ(cpu.get_esi(), 0xEBF0787B);
    EXPECT_EQ(cpu.get_edi(), 0xFBFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x8C44663A);
    EXPECT_EQ(cpu.get_esp(), 0x0000B61C);
    EXPECT_EQ(cpu.get_cs(), 0x0000A056);
    EXPECT_EQ(cpu.get_ds(), 0x0000F185);
    EXPECT_EQ(cpu.get_es(), 0x00001C63);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00006A17);
    EXPECT_EQ(cpu.get_ss(), 0x0000C029);
    EXPECT_EQ(cpu.get_eip(), 0x000061B5);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCB8B0), 0x97);
    EXPECT_EQ(memory.load8(0xCB8B1), 0x04);
    EXPECT_EQ(memory.load8(0xCB8AE), 0x4C);
    EXPECT_EQ(memory.load8(0xCB8AF), 0x05);
    EXPECT_EQ(memory.load8(0xCB8AC), 0xB0);
    EXPECT_EQ(memory.load8(0xCB8AD), 0x66);
}

//
// retfd
//
TEST_F(Test386, retfd_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x2E45F8F7);
    cpu.set_ebx(0x58130922);
    cpu.set_ecx(0x00339E49);
    cpu.set_edx(0xA7ECD0FD);
    cpu.set_esi(0x9E5E6D42);
    cpu.set_edi(0x049469CE);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x00004D56);
    cpu.set_cs(0x0000F8B3);
    cpu.set_ds(0x0000D4D6);
    cpu.set_es(0x0000F506);
    cpu.set_fs(0x0000D32B);
    cpu.set_gs(0x000019F0);
    cpu.set_ss(0x00008A41);
    cpu.set_eip(0x0000E0E0);
    cpu.set_eflags(0xFFFC0C16);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x106C10, 0x66);
    machine.mem_store_byte(0x106C11, 0xCB);
    machine.mem_store_byte(0x106C12, 0xF4);
    machine.mem_store_byte(0x106C13, 0xFF);
    machine.mem_store_byte(0x106C14, 0xFF);
    machine.mem_store_byte(0x106C15, 0xFF);
    machine.mem_store_byte(0x106C16, 0xFF);
    machine.mem_store_byte(0x106C17, 0xFF);
    machine.mem_store_byte(0x8F168, 0xFF);
    machine.mem_store_byte(0x8F169, 0xFF);
    machine.mem_store_byte(0x8F166, 0xFF);
    machine.mem_store_byte(0x8F167, 0xFF);
    machine.mem_store_byte(0x8F16C, 0xFF);
    machine.mem_store_byte(0x8F16D, 0xFF);
    machine.mem_store_byte(0x8F16A, 0xFF);
    machine.mem_store_byte(0x8F16B, 0xFF);
    machine.mem_store_byte(0x00034, 0xE3);
    machine.mem_store_byte(0x00035, 0x95);
    machine.mem_store_byte(0x00036, 0x49);
    machine.mem_store_byte(0x00037, 0x55);
    machine.mem_store_byte(0x5EA72, 0xF4);
    machine.mem_store_byte(0x5EA73, 0xF4);
    machine.mem_store_byte(0x5EA74, 0xFF);
    machine.mem_store_byte(0x5EA75, 0xF4);
    machine.mem_store_byte(0x5EA76, 0xFF);
    machine.mem_store_byte(0x5EA77, 0xF4);
    machine.mem_store_byte(0x5EA78, 0xFF);
    machine.mem_store_byte(0x5EA79, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x2E45F8F7);
    EXPECT_EQ(cpu.get_ebx(), 0x58130922);
    EXPECT_EQ(cpu.get_ecx(), 0x00339E49);
    EXPECT_EQ(cpu.get_edx(), 0xA7ECD0FD);
    EXPECT_EQ(cpu.get_esi(), 0x9E5E6D42);
    EXPECT_EQ(cpu.get_edi(), 0x049469CE);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x00004D50);
    EXPECT_EQ(cpu.get_cs(), 0x00005549);
    EXPECT_EQ(cpu.get_ds(), 0x0000D4D6);
    EXPECT_EQ(cpu.get_es(), 0x0000F506);
    EXPECT_EQ(cpu.get_fs(), 0x0000D32B);
    EXPECT_EQ(cpu.get_gs(), 0x000019F0);
    EXPECT_EQ(cpu.get_ss(), 0x00008A41);
    EXPECT_EQ(cpu.get_eip(), 0x000095E4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C16);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8F164), 0x16);
    EXPECT_EQ(memory.load8(0x8F165), 0x0C);
    EXPECT_EQ(memory.load8(0x8F162), 0xB3);
    EXPECT_EQ(memory.load8(0x8F163), 0xF8);
    EXPECT_EQ(memory.load8(0x8F160), 0xE0);
    EXPECT_EQ(memory.load8(0x8F161), 0xE0);
}

//
// sbb edx,[ss:bp+1E3Dh]
//
TEST_F(Test386, sbb_edx_ss_bp_1E3Dh_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0x4AA50A7C);
    cpu.set_ecx(0x9C985275);
    cpu.set_edx(0x0000001B);
    cpu.set_esi(0x80000001);
    cpu.set_edi(0xFE526D41);
    cpu.set_ebp(0x4C2E6FD6);
    cpu.set_esp(0x0000028D);
    cpu.set_cs(0x0000E42B);
    cpu.set_ds(0x0000F6EB);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x00005B00);
    cpu.set_gs(0x0000FFC6);
    cpu.set_ss(0x00002879);
    cpu.set_eip(0x00009358);
    cpu.set_eflags(0xFFFC0C13);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xED608, 0x66);
    machine.mem_store_byte(0xED609, 0x1B);
    machine.mem_store_byte(0xED60A, 0x96);
    machine.mem_store_byte(0xED60B, 0x3D);
    machine.mem_store_byte(0xED60C, 0x1E);
    machine.mem_store_byte(0xED60D, 0xF4);
    machine.mem_store_byte(0xED60E, 0xFF);
    machine.mem_store_byte(0xED60F, 0xFF);
    machine.mem_store_byte(0xED610, 0xFF);
    machine.mem_store_byte(0xED611, 0xFF);
    machine.mem_store_byte(0xED612, 0xFF);
    machine.mem_store_byte(0xED613, 0xFF);
    machine.mem_store_byte(0x315A4, 0xFF);
    machine.mem_store_byte(0x315A5, 0xFF);
    machine.mem_store_byte(0x315A6, 0xFF);
    machine.mem_store_byte(0x315A3, 0xFF);
    machine.mem_store_byte(0xED614, 0xFF);
    machine.mem_store_byte(0xED615, 0xFF);
    machine.mem_store_byte(0xED616, 0xFF);
    machine.mem_store_byte(0xED617, 0xFF);
    machine.mem_store_byte(0xED618, 0xFF);
    machine.mem_store_byte(0xED619, 0xFF);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0x4AA50A7C);
    EXPECT_EQ(cpu.get_ecx(), 0x9C985275);
    EXPECT_EQ(cpu.get_edx(), 0x0000001B);
    EXPECT_EQ(cpu.get_esi(), 0x80000001);
    EXPECT_EQ(cpu.get_edi(), 0xFE526D41);
    EXPECT_EQ(cpu.get_ebp(), 0x4C2E6FD6);
    EXPECT_EQ(cpu.get_esp(), 0x0000028D);
    EXPECT_EQ(cpu.get_cs(), 0x0000E42B);
    EXPECT_EQ(cpu.get_ds(), 0x0000F6EB);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x00005B00);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFC6);
    EXPECT_EQ(cpu.get_ss(), 0x00002879);
    EXPECT_EQ(cpu.get_eip(), 0x0000935E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
}

//
// shld [ds:FFFFC00Ch],esi,80h
//
TEST_F(Test386, shld_ds_FFFFC00Ch_esi_80h_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xCA2E2DAC);
    cpu.set_ebx(0x13C3AE6D);
    cpu.set_ecx(0x20372394);
    cpu.set_edx(0xF1B156CA);
    cpu.set_esi(0x0000001B);
    cpu.set_edi(0xD7FA7C93);
    cpu.set_ebp(0x5975F4FE);
    cpu.set_esp(0x00002786);
    cpu.set_cs(0x00003F44);
    cpu.set_ds(0x0000FF67);
    cpu.set_es(0x00009582);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x0000F1F5);
    cpu.set_ss(0x000000AC);
    cpu.set_eip(0x00006368);
    cpu.set_eflags(0xFFFC0812);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x457A8, 0x66);
    machine.mem_store_byte(0x457A9, 0x67);
    machine.mem_store_byte(0x457AA, 0x0F);
    machine.mem_store_byte(0x457AB, 0xA4);
    machine.mem_store_byte(0x457AC, 0x35);
    machine.mem_store_byte(0x457AD, 0x0C);
    machine.mem_store_byte(0x457AE, 0xC0);
    machine.mem_store_byte(0x457AF, 0xFF);
    machine.mem_store_byte(0x457B0, 0xFF);
    machine.mem_store_byte(0x457B1, 0x80);
    machine.mem_store_byte(0x457B2, 0xF4);
    machine.mem_store_byte(0x457B3, 0x25);
    machine.mem_store_byte(0x457B4, 0x3F);
    machine.mem_store_byte(0x457B5, 0x27);
    machine.mem_store_byte(0x457B6, 0x9F);
    machine.mem_store_byte(0x457B7, 0x03);
    machine.mem_store_byte(0x457B8, 0x8B);
    machine.mem_store_byte(0x457B9, 0x7D);
    machine.mem_store_byte(0x457BA, 0x8B);
    machine.mem_store_byte(0x457BB, 0x86);
    machine.mem_store_byte(0x457BC, 0x02);
    machine.mem_store_byte(0x457BD, 0xCB);
    machine.mem_store_byte(0x457BE, 0x65);
    machine.mem_store_byte(0x457BF, 0x7B);
    machine.mem_store_byte(0x00034, 0xE3);
    machine.mem_store_byte(0x00035, 0xF4);
    machine.mem_store_byte(0x00036, 0xE5);
    machine.mem_store_byte(0x00037, 0x62);
    machine.mem_store_byte(0x72332, 0xF1);
    machine.mem_store_byte(0x72333, 0xF4);
    machine.mem_store_byte(0x72334, 0xCF);
    machine.mem_store_byte(0x72335, 0xF4);
    machine.mem_store_byte(0x72336, 0xEC);
    machine.mem_store_byte(0x72337, 0xF4);
    machine.mem_store_byte(0x72338, 0x57);
    machine.mem_store_byte(0x72339, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xCA2E2DAC);
    EXPECT_EQ(cpu.get_ebx(), 0x13C3AE6D);
    EXPECT_EQ(cpu.get_ecx(), 0x20372394);
    EXPECT_EQ(cpu.get_edx(), 0xF1B156CA);
    EXPECT_EQ(cpu.get_esi(), 0x0000001B);
    EXPECT_EQ(cpu.get_edi(), 0xD7FA7C93);
    EXPECT_EQ(cpu.get_ebp(), 0x5975F4FE);
    EXPECT_EQ(cpu.get_esp(), 0x00002780);
    EXPECT_EQ(cpu.get_cs(), 0x000062E5);
    EXPECT_EQ(cpu.get_ds(), 0x0000FF67);
    EXPECT_EQ(cpu.get_es(), 0x00009582);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x0000F1F5);
    EXPECT_EQ(cpu.get_ss(), 0x000000AC);
    EXPECT_EQ(cpu.get_eip(), 0x0000F4E4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0812);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x03244), 0x12);
    EXPECT_EQ(memory.load8(0x03245), 0x08);
    EXPECT_EQ(memory.load8(0x03242), 0x44);
    EXPECT_EQ(memory.load8(0x03243), 0x3F);
    EXPECT_EQ(memory.load8(0x03240), 0x68);
    EXPECT_EQ(memory.load8(0x03241), 0x63);
}

//
// shld [ds:FFFFC00Ch],si,80h
//
TEST_F(Test386, shld_ds_FFFFC00Ch_si_80h_batch7)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xCA2E2DAC);
    cpu.set_ebx(0x13C3AE6D);
    cpu.set_ecx(0x20372394);
    cpu.set_edx(0xF1B156CA);
    cpu.set_esi(0x0000001B);
    cpu.set_edi(0xD7FA7C93);
    cpu.set_ebp(0x5975F4FE);
    cpu.set_esp(0x00002786);
    cpu.set_cs(0x00003F44);
    cpu.set_ds(0x0000FF67);
    cpu.set_es(0x00009582);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x0000F1F5);
    cpu.set_ss(0x000000AC);
    cpu.set_eip(0x00006368);
    cpu.set_eflags(0xFFFC0812);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x457A8, 0x67);
    machine.mem_store_byte(0x457A9, 0x0F);
    machine.mem_store_byte(0x457AA, 0xA4);
    machine.mem_store_byte(0x457AB, 0x35);
    machine.mem_store_byte(0x457AC, 0x0C);
    machine.mem_store_byte(0x457AD, 0xC0);
    machine.mem_store_byte(0x457AE, 0xFF);
    machine.mem_store_byte(0x457AF, 0xFF);
    machine.mem_store_byte(0x457B0, 0x80);
    machine.mem_store_byte(0x457B1, 0xF4);
    machine.mem_store_byte(0x457B2, 0x12);
    machine.mem_store_byte(0x457B3, 0x25);
    machine.mem_store_byte(0x457B4, 0x3F);
    machine.mem_store_byte(0x457B5, 0x27);
    machine.mem_store_byte(0x457B6, 0x9F);
    machine.mem_store_byte(0x457B7, 0x03);
    machine.mem_store_byte(0x457B8, 0x8B);
    machine.mem_store_byte(0x457B9, 0x7D);
    machine.mem_store_byte(0x457BA, 0x8B);
    machine.mem_store_byte(0x457BB, 0x86);
    machine.mem_store_byte(0x457BC, 0x02);
    machine.mem_store_byte(0x457BD, 0xCB);
    machine.mem_store_byte(0x457BE, 0x65);
    machine.mem_store_byte(0x457BF, 0x7B);
    machine.mem_store_byte(0x00034, 0xE3);
    machine.mem_store_byte(0x00035, 0xF4);
    machine.mem_store_byte(0x00036, 0xE5);
    machine.mem_store_byte(0x00037, 0x62);
    machine.mem_store_byte(0x72332, 0xF1);
    machine.mem_store_byte(0x72333, 0xF4);
    machine.mem_store_byte(0x72334, 0xCF);
    machine.mem_store_byte(0x72335, 0xF4);
    machine.mem_store_byte(0x72336, 0xEC);
    machine.mem_store_byte(0x72337, 0xF4);
    machine.mem_store_byte(0x72338, 0x57);
    machine.mem_store_byte(0x72339, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xCA2E2DAC);
    EXPECT_EQ(cpu.get_ebx(), 0x13C3AE6D);
    EXPECT_EQ(cpu.get_ecx(), 0x20372394);
    EXPECT_EQ(cpu.get_edx(), 0xF1B156CA);
    EXPECT_EQ(cpu.get_esi(), 0x0000001B);
    EXPECT_EQ(cpu.get_edi(), 0xD7FA7C93);
    EXPECT_EQ(cpu.get_ebp(), 0x5975F4FE);
    EXPECT_EQ(cpu.get_esp(), 0x00002780);
    EXPECT_EQ(cpu.get_cs(), 0x000062E5);
    EXPECT_EQ(cpu.get_ds(), 0x0000FF67);
    EXPECT_EQ(cpu.get_es(), 0x00009582);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x0000F1F5);
    EXPECT_EQ(cpu.get_ss(), 0x000000AC);
    EXPECT_EQ(cpu.get_eip(), 0x0000F4E4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0812);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x03244), 0x12);
    EXPECT_EQ(memory.load8(0x03245), 0x08);
    EXPECT_EQ(memory.load8(0x03242), 0x44);
    EXPECT_EQ(memory.load8(0x03243), 0x3F);
    EXPECT_EQ(memory.load8(0x03240), 0x68);
    EXPECT_EQ(memory.load8(0x03241), 0x63);
}
