#include "test386.h"

//
// rcl bh,73h
//
TEST_F(Test386, rcl_bh_73h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x38E0A083);
    cpu.set_ebx(0x17150ABA);
    cpu.set_ecx(0x62DA76DD);
    cpu.set_edx(0xB6EC360F);
    cpu.set_esi(0x400BE293);
    cpu.set_edi(0x5A1F52EB);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x0000AD68);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000F808);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x000032F6);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x00006DFE);
    cpu.set_eip(0x0000F150);
    cpu.set_eflags(0xFFFC0097);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0F150, 0xC0);
    machine.mem_store_byte(0x0F151, 0xD7);
    machine.mem_store_byte(0x0F152, 0x73);
    machine.mem_store_byte(0x0F153, 0xF4);
    machine.mem_store_byte(0x0F154, 0xB4);
    machine.mem_store_byte(0x0F155, 0xED);
    machine.mem_store_byte(0x0F156, 0x30);
    machine.mem_store_byte(0x0F157, 0x54);
    machine.mem_store_byte(0x0F158, 0x0D);
    machine.mem_store_byte(0x0F159, 0x27);
    machine.mem_store_byte(0x0F15A, 0xFC);
    machine.mem_store_byte(0x0F15B, 0x7F);
    machine.mem_store_byte(0x0F15C, 0x8B);
    machine.mem_store_byte(0x0F15D, 0xE5);
    machine.mem_store_byte(0x0F15E, 0xB3);
    machine.mem_store_byte(0x0F15F, 0x2F);
    machine.mem_store_byte(0x0F160, 0xA1);
    machine.mem_store_byte(0x0F161, 0xC9);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x38E0A083);
    EXPECT_EQ(cpu.get_ebx(), 0x171515BA);
    EXPECT_EQ(cpu.get_ecx(), 0x62DA76DD);
    EXPECT_EQ(cpu.get_edx(), 0xB6EC360F);
    EXPECT_EQ(cpu.get_esi(), 0x400BE293);
    EXPECT_EQ(cpu.get_edi(), 0x5A1F52EB);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x0000AD68);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000F808);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x000032F6);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x00006DFE);
    EXPECT_EQ(cpu.get_eip(), 0x0000F154);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0096);

    // Final RAM entries
}

//
// rcr byte [ds:esi],cl
//
TEST_F(Test386, rcr_byte_ds_esi_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x032A2187);
    cpu.set_ebx(0xFFB0D14C);
    cpu.set_ecx(0x0000FFFF);
    cpu.set_edx(0x8C5EA10A);
    cpu.set_esi(0x00009C37);
    cpu.set_edi(0xF1F8DA38);
    cpu.set_ebp(0xEF7BA78C);
    cpu.set_esp(0x000098A6);
    cpu.set_cs(0x00008BF6);
    cpu.set_ds(0x0000C878);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x00002CAD);
    cpu.set_gs(0x0000FCA3);
    cpu.set_ss(0x00005EF8);
    cpu.set_eip(0x00005DF0);
    cpu.set_eflags(0xFFFC0CC3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x91D50, 0x67);
    machine.mem_store_byte(0x91D51, 0xD2);
    machine.mem_store_byte(0x91D52, 0x1E);
    machine.mem_store_byte(0x91D53, 0xF4);
    machine.mem_store_byte(0x91D54, 0x69);
    machine.mem_store_byte(0x91D55, 0x95);
    machine.mem_store_byte(0x91D56, 0xFF);
    machine.mem_store_byte(0x91D57, 0xBF);
    machine.mem_store_byte(0x91D58, 0xEE);
    machine.mem_store_byte(0x91D59, 0xA1);
    machine.mem_store_byte(0xD23B7, 0x91);
    machine.mem_store_byte(0x91D5A, 0x50);
    machine.mem_store_byte(0x91D5B, 0x63);
    machine.mem_store_byte(0x91D5C, 0x9A);
    machine.mem_store_byte(0x91D5D, 0x2C);
    machine.mem_store_byte(0x91D5E, 0x0F);
    machine.mem_store_byte(0x91D5F, 0x4D);
    machine.mem_store_byte(0x91D60, 0xC6);
    machine.mem_store_byte(0x91D61, 0xEC);
    machine.mem_store_byte(0x91D62, 0x72);
    machine.mem_store_byte(0x91D63, 0x8E);
    machine.mem_store_byte(0x91D64, 0xC0);
    machine.mem_store_byte(0x91D65, 0x11);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x032A2187);
    EXPECT_EQ(cpu.get_ebx(), 0xFFB0D14C);
    EXPECT_EQ(cpu.get_ecx(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_edx(), 0x8C5EA10A);
    EXPECT_EQ(cpu.get_esi(), 0x00009C37);
    EXPECT_EQ(cpu.get_edi(), 0xF1F8DA38);
    EXPECT_EQ(cpu.get_ebp(), 0xEF7BA78C);
    EXPECT_EQ(cpu.get_esp(), 0x000098A6);
    EXPECT_EQ(cpu.get_cs(), 0x00008BF6);
    EXPECT_EQ(cpu.get_ds(), 0x0000C878);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x00002CAD);
    EXPECT_EQ(cpu.get_gs(), 0x0000FCA3);
    EXPECT_EQ(cpu.get_ss(), 0x00005EF8);
    EXPECT_EQ(cpu.get_eip(), 0x00005DF4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04C2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD23B7), 0x39);
}

//
// rcl dword [ds:di],cl
//
TEST_F(Test386, rcl_dword_ds_di_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x5B9A9ADB);
    cpu.set_ebx(0x00C3B9AE);
    cpu.set_ecx(0xFFFFFFFF);
    cpu.set_edx(0x2035EFDC);
    cpu.set_esi(0x99A386E5);
    cpu.set_edi(0x34CE1505);
    cpu.set_ebp(0x086B2C11);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00009483);
    cpu.set_ds(0x0000FC56);
    cpu.set_es(0x00000B2E);
    cpu.set_fs(0x00008B75);
    cpu.set_gs(0x0000003F);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x0000FFF8);
    cpu.set_eflags(0xFFFC08C2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA4828, 0x66);
    machine.mem_store_byte(0xA4829, 0xD3);
    machine.mem_store_byte(0xA482A, 0x15);
    machine.mem_store_byte(0xA482B, 0xF4);
    machine.mem_store_byte(0xA482C, 0x76);
    machine.mem_store_byte(0xA482D, 0xEC);
    machine.mem_store_byte(0xA482E, 0x34);
    machine.mem_store_byte(0xA482F, 0x74);
    machine.mem_store_byte(0xFDA68, 0x43);
    machine.mem_store_byte(0xFDA65, 0x90);
    machine.mem_store_byte(0xFDA66, 0x31);
    machine.mem_store_byte(0xFDA67, 0xF7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x5B9A9ADB);
    EXPECT_EQ(cpu.get_ebx(), 0x00C3B9AE);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x2035EFDC);
    EXPECT_EQ(cpu.get_esi(), 0x99A386E5);
    EXPECT_EQ(cpu.get_edi(), 0x34CE1505);
    EXPECT_EQ(cpu.get_ebp(), 0x086B2C11);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00009483);
    EXPECT_EQ(cpu.get_ds(), 0x0000FC56);
    EXPECT_EQ(cpu.get_es(), 0x00000B2E);
    EXPECT_EQ(cpu.get_fs(), 0x00008B75);
    EXPECT_EQ(cpu.get_gs(), 0x0000003F);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000FFFC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00C2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFDA68), 0x10);
    EXPECT_EQ(memory.load8(0xFDA65), 0x64);
    EXPECT_EQ(memory.load8(0xFDA66), 0xCC);
    EXPECT_EQ(memory.load8(0xFDA67), 0xFD);
}

//
// rcr dword [ds:9B54h],1
//
TEST_F(Test386, rcr_dword_ds_9B54h_1)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xF8699D3F);
    cpu.set_ebx(0x0026291C);
    cpu.set_ecx(0xF4E0CAF3);
    cpu.set_edx(0xE4139637);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0x00008000);
    cpu.set_ebp(0xE545C027);
    cpu.set_esp(0x0000FAD8);
    cpu.set_cs(0x0000FFE3);
    cpu.set_ds(0x00006926);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00002A64);
    cpu.set_ss(0x00000001);
    cpu.set_eip(0x0000F688);
    cpu.set_eflags(0xFFFC0816);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10F4B8, 0x64);
    machine.mem_store_byte(0x10F4B9, 0x26);
    machine.mem_store_byte(0x10F4BA, 0x65);
    machine.mem_store_byte(0x10F4BB, 0x2E);
    machine.mem_store_byte(0x10F4BC, 0x65);
    machine.mem_store_byte(0x10F4BD, 0x3E);
    machine.mem_store_byte(0x10F4BE, 0x66);
    machine.mem_store_byte(0x10F4BF, 0xD1);
    machine.mem_store_byte(0x10F4C0, 0x1E);
    machine.mem_store_byte(0x10F4C1, 0x54);
    machine.mem_store_byte(0x10F4C2, 0x9B);
    machine.mem_store_byte(0x10F4C3, 0xF4);
    machine.mem_store_byte(0x10F4C4, 0x15);
    machine.mem_store_byte(0x10F4C5, 0x86);
    machine.mem_store_byte(0x10F4C6, 0xC8);
    machine.mem_store_byte(0x10F4C7, 0xE8);
    machine.mem_store_byte(0x10F4C8, 0x82);
    machine.mem_store_byte(0x10F4C9, 0x19);
    machine.mem_store_byte(0x72DB4, 0x00);
    machine.mem_store_byte(0x72DB5, 0x34);
    machine.mem_store_byte(0x72DB6, 0xCA);
    machine.mem_store_byte(0x72DB7, 0xE7);
    machine.mem_store_byte(0x10F4CA, 0x9E);
    machine.mem_store_byte(0x10F4CB, 0xD6);
    machine.mem_store_byte(0x10F4CC, 0xAE);
    machine.mem_store_byte(0x10F4CD, 0xD8);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xF8699D3F);
    EXPECT_EQ(cpu.get_ebx(), 0x0026291C);
    EXPECT_EQ(cpu.get_ecx(), 0xF4E0CAF3);
    EXPECT_EQ(cpu.get_edx(), 0xE4139637);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0x00008000);
    EXPECT_EQ(cpu.get_ebp(), 0xE545C027);
    EXPECT_EQ(cpu.get_esp(), 0x0000FAD8);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFE3);
    EXPECT_EQ(cpu.get_ds(), 0x00006926);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00002A64);
    EXPECT_EQ(cpu.get_ss(), 0x00000001);
    EXPECT_EQ(cpu.get_eip(), 0x0000F694);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0816);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x72DB5), 0x1A);
    EXPECT_EQ(memory.load8(0x72DB6), 0xE5);
    EXPECT_EQ(memory.load8(0x72DB7), 0x73);
}

//
// rep outsb
//
TEST_F(Test386, rep_outsb)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x03D90395);
    cpu.set_ebx(0x092A3F3A);
    cpu.set_ecx(0x00000026);
    cpu.set_edx(0x491B266B);
    cpu.set_esi(0x2BC15211);
    cpu.set_edi(0x912D8CB0);
    cpu.set_ebp(0x0995B712);
    cpu.set_esp(0x0000DAE2);
    cpu.set_cs(0x0000F84B);
    cpu.set_ds(0x0000FD49);
    cpu.set_es(0x0000543B);
    cpu.set_fs(0x00007FFF);
    cpu.set_gs(0x00004A72);
    cpu.set_ss(0x00003928);
    cpu.set_eip(0x00009578);
    cpu.set_eflags(0xFFFC08C6);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x101A28, 0xF3);
    machine.mem_store_byte(0x101A29, 0x6E);
    machine.mem_store_byte(0x101A2A, 0xF4);
    machine.mem_store_byte(0x101A2B, 0xB7);
    machine.mem_store_byte(0x101A2C, 0xFF);
    machine.mem_store_byte(0x101A2D, 0x4C);
    machine.mem_store_byte(0x101A2E, 0x7C);
    machine.mem_store_byte(0x101A2F, 0x66);
    machine.mem_store_byte(0x101A30, 0x6B);
    machine.mem_store_byte(0x101A31, 0x07);
    machine.mem_store_byte(0x101A32, 0x00);
    machine.mem_store_byte(0x101A33, 0x92);
    machine.mem_store_byte(0x101A34, 0x74);
    machine.mem_store_byte(0x101A35, 0xA5);
    machine.mem_store_byte(0x101A36, 0x44);
    machine.mem_store_byte(0x101A37, 0x60);
    machine.mem_store_byte(0x1026A1, 0x50);
    machine.mem_store_byte(0x1026A2, 0xB8);
    machine.mem_store_byte(0x1026A3, 0x10);
    machine.mem_store_byte(0x1026A4, 0x21);
    machine.mem_store_byte(0x1026A5, 0x14);
    machine.mem_store_byte(0x1026A6, 0x7D);
    machine.mem_store_byte(0x1026A7, 0x69);
    machine.mem_store_byte(0x1026A8, 0x46);
    machine.mem_store_byte(0x1026A9, 0x44);
    machine.mem_store_byte(0x1026AA, 0x0E);
    machine.mem_store_byte(0x1026AB, 0x39);
    machine.mem_store_byte(0x1026AC, 0x05);
    machine.mem_store_byte(0x1026AD, 0x53);
    machine.mem_store_byte(0x1026AE, 0x3F);
    machine.mem_store_byte(0x1026AF, 0xBA);
    machine.mem_store_byte(0x1026B0, 0xBD);
    machine.mem_store_byte(0x1026B1, 0x73);
    machine.mem_store_byte(0x1026B2, 0x60);
    machine.mem_store_byte(0x1026B3, 0x8B);
    machine.mem_store_byte(0x1026B4, 0xCD);
    machine.mem_store_byte(0x1026B5, 0x9E);
    machine.mem_store_byte(0x1026B6, 0xAF);
    machine.mem_store_byte(0x1026B7, 0xF6);
    machine.mem_store_byte(0x1026B8, 0xEF);
    machine.mem_store_byte(0x1026B9, 0xA4);
    machine.mem_store_byte(0x1026BA, 0x46);
    machine.mem_store_byte(0x1026BB, 0xFC);
    machine.mem_store_byte(0x1026BC, 0x50);
    machine.mem_store_byte(0x1026BD, 0xC7);
    machine.mem_store_byte(0x1026BE, 0xBF);
    machine.mem_store_byte(0x1026BF, 0xCA);
    machine.mem_store_byte(0x1026C0, 0x32);
    machine.mem_store_byte(0x1026C1, 0xD2);
    machine.mem_store_byte(0x1026C2, 0x18);
    machine.mem_store_byte(0x1026C3, 0xF1);
    machine.mem_store_byte(0x1026C4, 0xB6);
    machine.mem_store_byte(0x1026C5, 0x06);
    machine.mem_store_byte(0x1026C6, 0x27);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x03D90395);
    EXPECT_EQ(cpu.get_ebx(), 0x092A3F3A);
    EXPECT_EQ(cpu.get_ecx(), 0x00000000);
    EXPECT_EQ(cpu.get_edx(), 0x491B266B);
    EXPECT_EQ(cpu.get_esi(), 0x2BC15237);
    EXPECT_EQ(cpu.get_edi(), 0x912D8CB0);
    EXPECT_EQ(cpu.get_ebp(), 0x0995B712);
    EXPECT_EQ(cpu.get_esp(), 0x0000DAE2);
    EXPECT_EQ(cpu.get_cs(), 0x0000F84B);
    EXPECT_EQ(cpu.get_ds(), 0x0000FD49);
    EXPECT_EQ(cpu.get_es(), 0x0000543B);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x00004A72);
    EXPECT_EQ(cpu.get_ss(), 0x00003928);
    EXPECT_EQ(cpu.get_eip(), 0x0000957B);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C6);

    // Final RAM entries
}

//
// ret 5901h
//
TEST_F(Test386, ret_5901h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x8865395C);
    cpu.set_ebx(0x5704D05F);
    cpu.set_ecx(0x8A883AA1);
    cpu.set_edx(0x6784015B);
    cpu.set_esi(0xFFFFFFF1);
    cpu.set_edi(0x000000C1);
    cpu.set_ebp(0xDFFFFFFF);
    cpu.set_esp(0x0000B594);
    cpu.set_cs(0x0000010B);
    cpu.set_ds(0x00005A6A);
    cpu.set_es(0x0000DD87);
    cpu.set_fs(0x00007FFF);
    cpu.set_gs(0x0000F5C6);
    cpu.set_ss(0x000081DB);
    cpu.set_eip(0x00009CF0);
    cpu.set_eflags(0xFFFC0053);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0ADA0, 0xC2);
    machine.mem_store_byte(0x0ADA1, 0x01);
    machine.mem_store_byte(0x0ADA2, 0x59);
    machine.mem_store_byte(0x0ADA3, 0xF4);
    machine.mem_store_byte(0x0ADA4, 0x41);
    machine.mem_store_byte(0x0ADA5, 0x14);
    machine.mem_store_byte(0x0ADA6, 0xCB);
    machine.mem_store_byte(0x0ADA7, 0xEA);
    machine.mem_store_byte(0x8D344, 0x65);
    machine.mem_store_byte(0x8D345, 0x7F);
    machine.mem_store_byte(0x09014, 0xF4);
    machine.mem_store_byte(0x09015, 0xF4);
    machine.mem_store_byte(0x09016, 0x49);
    machine.mem_store_byte(0x09017, 0x55);
    machine.mem_store_byte(0x09018, 0xE6);
    machine.mem_store_byte(0x09019, 0x85);
    machine.mem_store_byte(0x0901A, 0x11);
    machine.mem_store_byte(0x0901B, 0x8C);
    machine.mem_store_byte(0x0901C, 0x00);
    machine.mem_store_byte(0x0901D, 0x0B);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x8865395C);
    EXPECT_EQ(cpu.get_ebx(), 0x5704D05F);
    EXPECT_EQ(cpu.get_ecx(), 0x8A883AA1);
    EXPECT_EQ(cpu.get_edx(), 0x6784015B);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFF1);
    EXPECT_EQ(cpu.get_edi(), 0x000000C1);
    EXPECT_EQ(cpu.get_ebp(), 0xDFFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x00000E97);
    EXPECT_EQ(cpu.get_cs(), 0x0000010B);
    EXPECT_EQ(cpu.get_ds(), 0x00005A6A);
    EXPECT_EQ(cpu.get_es(), 0x0000DD87);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000F5C6);
    EXPECT_EQ(cpu.get_ss(), 0x000081DB);
    EXPECT_EQ(cpu.get_eip(), 0x00007F66);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0053);

    // Final RAM entries
}

//
// retd
//
TEST_F(Test386, retd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x07809709);
    cpu.set_ebx(0xAE75395A);
    cpu.set_ecx(0x2A3338AB);
    cpu.set_edx(0xFC19E0E1);
    cpu.set_esi(0x0DC52477);
    cpu.set_edi(0x00000001);
    cpu.set_ebp(0x1181DD48);
    cpu.set_esp(0x00006E4A);
    cpu.set_cs(0x0000FCB3);
    cpu.set_ds(0x0000013B);
    cpu.set_es(0x000090E4);
    cpu.set_fs(0x0000F97E);
    cpu.set_gs(0x00008A94);
    cpu.set_ss(0x000020C1);
    cpu.set_eip(0x0000A2E8);
    cpu.set_eflags(0xFFFC0046);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x106E18, 0x66);
    machine.mem_store_byte(0x106E19, 0xC3);
    machine.mem_store_byte(0x106E1A, 0xF4);
    machine.mem_store_byte(0x106E1B, 0x5D);
    machine.mem_store_byte(0x106E1C, 0x1A);
    machine.mem_store_byte(0x106E1D, 0x3C);
    machine.mem_store_byte(0x106E1E, 0xE8);
    machine.mem_store_byte(0x106E1F, 0x84);
    machine.mem_store_byte(0x27A5C, 0x00);
    machine.mem_store_byte(0x27A5D, 0x00);
    machine.mem_store_byte(0x27A5A, 0xAE);
    machine.mem_store_byte(0x27A5B, 0xC7);
    machine.mem_store_byte(0x1092DE, 0xF4);
    machine.mem_store_byte(0x1092DF, 0xF4);
    machine.mem_store_byte(0x1092E0, 0x96);
    machine.mem_store_byte(0x1092E1, 0xE8);
    machine.mem_store_byte(0x1092E2, 0x40);
    machine.mem_store_byte(0x1092E3, 0xDF);
    machine.mem_store_byte(0x1092E4, 0xFC);
    machine.mem_store_byte(0x1092E5, 0x80);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x07809709);
    EXPECT_EQ(cpu.get_ebx(), 0xAE75395A);
    EXPECT_EQ(cpu.get_ecx(), 0x2A3338AB);
    EXPECT_EQ(cpu.get_edx(), 0xFC19E0E1);
    EXPECT_EQ(cpu.get_esi(), 0x0DC52477);
    EXPECT_EQ(cpu.get_edi(), 0x00000001);
    EXPECT_EQ(cpu.get_ebp(), 0x1181DD48);
    EXPECT_EQ(cpu.get_esp(), 0x00006E4E);
    EXPECT_EQ(cpu.get_cs(), 0x0000FCB3);
    EXPECT_EQ(cpu.get_ds(), 0x0000013B);
    EXPECT_EQ(cpu.get_es(), 0x000090E4);
    EXPECT_EQ(cpu.get_fs(), 0x0000F97E);
    EXPECT_EQ(cpu.get_gs(), 0x00008A94);
    EXPECT_EQ(cpu.get_ss(), 0x000020C1);
    EXPECT_EQ(cpu.get_eip(), 0x0000C7AF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0046);

    // Final RAM entries
}

//
// retf 9DFDh
//
TEST_F(Test386, retf_9DFDh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00008081);
    cpu.set_ebx(0x89233A9A);
    cpu.set_ecx(0x7FFFFFFF);
    cpu.set_edx(0xE2572916);
    cpu.set_esi(0x0852281E);
    cpu.set_edi(0x69F8119B);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x00008000);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000E551);
    cpu.set_es(0x0000D3CC);
    cpu.set_fs(0x000047D7);
    cpu.set_gs(0x00000008);
    cpu.set_ss(0x0000215C);
    cpu.set_eip(0x0000D4E8);
    cpu.set_eflags(0xFFFC04D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0D4E8, 0xCA);
    machine.mem_store_byte(0x0D4E9, 0xFD);
    machine.mem_store_byte(0x0D4EA, 0x9D);
    machine.mem_store_byte(0x0D4EB, 0xF4);
    machine.mem_store_byte(0x0D4EC, 0x00);
    machine.mem_store_byte(0x0D4ED, 0x00);
    machine.mem_store_byte(0x0D4EE, 0x00);
    machine.mem_store_byte(0x0D4EF, 0x00);
    machine.mem_store_byte(0x295C0, 0x00);
    machine.mem_store_byte(0x295C1, 0x00);
    machine.mem_store_byte(0x295C2, 0x00);
    machine.mem_store_byte(0x295C3, 0x00);
    machine.mem_store_byte(0x00000, 0xF4);
    machine.mem_store_byte(0x00001, 0xF4);
    machine.mem_store_byte(0x00002, 0x50);
    machine.mem_store_byte(0x00003, 0xE6);
    machine.mem_store_byte(0x00004, 0x46);
    machine.mem_store_byte(0x00005, 0xF2);
    machine.mem_store_byte(0x00006, 0xD9);
    machine.mem_store_byte(0x00007, 0x66);
    machine.mem_store_byte(0x00008, 0x5F);
    machine.mem_store_byte(0x00009, 0xA6);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00008081);
    EXPECT_EQ(cpu.get_ebx(), 0x89233A9A);
    EXPECT_EQ(cpu.get_ecx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xE2572916);
    EXPECT_EQ(cpu.get_esi(), 0x0852281E);
    EXPECT_EQ(cpu.get_edi(), 0x69F8119B);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x00001E01);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000E551);
    EXPECT_EQ(cpu.get_es(), 0x0000D3CC);
    EXPECT_EQ(cpu.get_fs(), 0x000047D7);
    EXPECT_EQ(cpu.get_gs(), 0x00000008);
    EXPECT_EQ(cpu.get_ss(), 0x0000215C);
    EXPECT_EQ(cpu.get_eip(), 0x00000001);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04D2);

    // Final RAM entries
}

//
// ror byte [ds:bx+25h],80h
//
TEST_F(Test386, ror_byte_ds_bx_25h_80h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xBC48E7B3);
    cpu.set_ebx(0x5671A216);
    cpu.set_ecx(0x10E7928E);
    cpu.set_edx(0xFE3D9497);
    cpu.set_esi(0xC516597D);
    cpu.set_edi(0x7FFFFFFF);
    cpu.set_ebp(0xFFD83882);
    cpu.set_esp(0x000012DE);
    cpu.set_cs(0x00002E41);
    cpu.set_ds(0x0000DD5F);
    cpu.set_es(0x00001D19);
    cpu.set_fs(0x0000059B);
    cpu.set_gs(0x0000EDD5);
    cpu.set_ss(0x00000D8D);
    cpu.set_eip(0x00006F28);
    cpu.set_eflags(0xFFFC0496);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x35338, 0xC0);
    machine.mem_store_byte(0x35339, 0x4F);
    machine.mem_store_byte(0x3533A, 0x25);
    machine.mem_store_byte(0x3533B, 0x80);
    machine.mem_store_byte(0x3533C, 0xF4);
    machine.mem_store_byte(0x3533D, 0x53);
    machine.mem_store_byte(0x3533E, 0x34);
    machine.mem_store_byte(0x3533F, 0x4C);
    machine.mem_store_byte(0x35340, 0xCD);
    machine.mem_store_byte(0x35341, 0x6E);
    machine.mem_store_byte(0x35342, 0xD1);
    machine.mem_store_byte(0x35343, 0x47);
    machine.mem_store_byte(0xE782B, 0x4C);
    machine.mem_store_byte(0x35344, 0x6A);
    machine.mem_store_byte(0x35345, 0x19);
    machine.mem_store_byte(0x35346, 0xC8);
    machine.mem_store_byte(0x35347, 0xF6);
    machine.mem_store_byte(0x35348, 0xAF);
    machine.mem_store_byte(0x35349, 0x3B);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xBC48E7B3);
    EXPECT_EQ(cpu.get_ebx(), 0x5671A216);
    EXPECT_EQ(cpu.get_ecx(), 0x10E7928E);
    EXPECT_EQ(cpu.get_edx(), 0xFE3D9497);
    EXPECT_EQ(cpu.get_esi(), 0xC516597D);
    EXPECT_EQ(cpu.get_edi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0xFFD83882);
    EXPECT_EQ(cpu.get_esp(), 0x000012DE);
    EXPECT_EQ(cpu.get_cs(), 0x00002E41);
    EXPECT_EQ(cpu.get_ds(), 0x0000DD5F);
    EXPECT_EQ(cpu.get_es(), 0x00001D19);
    EXPECT_EQ(cpu.get_fs(), 0x0000059B);
    EXPECT_EQ(cpu.get_gs(), 0x0000EDD5);
    EXPECT_EQ(cpu.get_ss(), 0x00000D8D);
    EXPECT_EQ(cpu.get_eip(), 0x00006F2D);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0496);

    // Final RAM entries
}

//
// retfd
//
TEST_F(Test386, retfd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x38E0A083);
    cpu.set_ebx(0x17150ABA);
    cpu.set_ecx(0x62DA76DD);
    cpu.set_edx(0xB6EC360F);
    cpu.set_esi(0x400BE293);
    cpu.set_edi(0x5A1F52EB);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x0000AD68);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000F808);
    cpu.set_es(0x00007FFF);
    cpu.set_fs(0x000032F6);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x00006DFE);
    cpu.set_eip(0x0000F150);
    cpu.set_eflags(0xFFFC0097);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0F150, 0x66);
    machine.mem_store_byte(0x0F151, 0xCB);
    machine.mem_store_byte(0x0F152, 0xF4);
    machine.mem_store_byte(0x0F153, 0x00);
    machine.mem_store_byte(0x0F154, 0x00);
    machine.mem_store_byte(0x0F155, 0x00);
    machine.mem_store_byte(0x0F156, 0x00);
    machine.mem_store_byte(0x0F157, 0x00);
    machine.mem_store_byte(0x78D48, 0x00);
    machine.mem_store_byte(0x78D49, 0x00);
    machine.mem_store_byte(0x78D4A, 0x00);
    machine.mem_store_byte(0x78D4B, 0x00);
    machine.mem_store_byte(0x78D4C, 0x00);
    machine.mem_store_byte(0x78D4D, 0x00);
    machine.mem_store_byte(0x78D4E, 0x00);
    machine.mem_store_byte(0x78D4F, 0x00);
    machine.mem_store_byte(0x00000, 0xF4);
    machine.mem_store_byte(0x00001, 0xF4);
    machine.mem_store_byte(0x00002, 0x56);
    machine.mem_store_byte(0x00003, 0x13);
    machine.mem_store_byte(0x00004, 0x06);
    machine.mem_store_byte(0x00005, 0xBC);
    machine.mem_store_byte(0x00006, 0x11);
    machine.mem_store_byte(0x00007, 0x54);
    machine.mem_store_byte(0x00008, 0x0F);
    machine.mem_store_byte(0x00009, 0xFB);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x38E0A083);
    EXPECT_EQ(cpu.get_ebx(), 0x17150ABA);
    EXPECT_EQ(cpu.get_ecx(), 0x62DA76DD);
    EXPECT_EQ(cpu.get_edx(), 0xB6EC360F);
    EXPECT_EQ(cpu.get_esi(), 0x400BE293);
    EXPECT_EQ(cpu.get_edi(), 0x5A1F52EB);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x0000AD70);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000F808);
    EXPECT_EQ(cpu.get_es(), 0x00007FFF);
    EXPECT_EQ(cpu.get_fs(), 0x000032F6);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x00006DFE);
    EXPECT_EQ(cpu.get_eip(), 0x00000001);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0097);

    // Final RAM entries
}

//
// ror dl,1
//
TEST_F(Test386, ror_dl_1)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFE0DD818);
    cpu.set_ebx(0x53A9CF67);
    cpu.set_ecx(0xE4513017);
    cpu.set_edx(0x1ACB67DA);
    cpu.set_esi(0x00000001);
    cpu.set_edi(0x3B756133);
    cpu.set_ebp(0x7D0A0C40);
    cpu.set_esp(0x0000E218);
    cpu.set_cs(0x000006E1);
    cpu.set_ds(0x0000FFFF);
    cpu.set_es(0x00003FCD);
    cpu.set_fs(0x00005A5A);
    cpu.set_gs(0x00009266);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00002A30);
    cpu.set_eflags(0xFFFC0886);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x09840, 0x67);
    machine.mem_store_byte(0x09841, 0xD0);
    machine.mem_store_byte(0x09842, 0xCA);
    machine.mem_store_byte(0x09843, 0xF4);
    machine.mem_store_byte(0x09844, 0x73);
    machine.mem_store_byte(0x09845, 0x2C);
    machine.mem_store_byte(0x09846, 0x90);
    machine.mem_store_byte(0x09847, 0x92);
    machine.mem_store_byte(0x09848, 0xE7);
    machine.mem_store_byte(0x09849, 0x17);
    machine.mem_store_byte(0x0984A, 0xB7);
    machine.mem_store_byte(0x0984B, 0xAA);
    machine.mem_store_byte(0x0984C, 0xC1);
    machine.mem_store_byte(0x0984D, 0xDD);
    machine.mem_store_byte(0x0984E, 0xB6);
    machine.mem_store_byte(0x0984F, 0x9D);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFE0DD818);
    EXPECT_EQ(cpu.get_ebx(), 0x53A9CF67);
    EXPECT_EQ(cpu.get_ecx(), 0xE4513017);
    EXPECT_EQ(cpu.get_edx(), 0x1ACB676D);
    EXPECT_EQ(cpu.get_esi(), 0x00000001);
    EXPECT_EQ(cpu.get_edi(), 0x3B756133);
    EXPECT_EQ(cpu.get_ebp(), 0x7D0A0C40);
    EXPECT_EQ(cpu.get_esp(), 0x0000E218);
    EXPECT_EQ(cpu.get_cs(), 0x000006E1);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_es(), 0x00003FCD);
    EXPECT_EQ(cpu.get_fs(), 0x00005A5A);
    EXPECT_EQ(cpu.get_gs(), 0x00009266);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x00002A34);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0886);

    // Final RAM entries
}

//
// retfd 9DFDh
//
TEST_F(Test386, retfd_9DFDh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00008081);
    cpu.set_ebx(0x89233A9A);
    cpu.set_ecx(0x7FFFFFFF);
    cpu.set_edx(0xE2572916);
    cpu.set_esi(0x0852281E);
    cpu.set_edi(0x69F8119B);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x00008000);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000E551);
    cpu.set_es(0x0000D3CC);
    cpu.set_fs(0x000047D7);
    cpu.set_gs(0x00000008);
    cpu.set_ss(0x0000215C);
    cpu.set_eip(0x0000D4E8);
    cpu.set_eflags(0xFFFC04D2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0D4E8, 0x66);
    machine.mem_store_byte(0x0D4E9, 0xCA);
    machine.mem_store_byte(0x0D4EA, 0xFD);
    machine.mem_store_byte(0x0D4EB, 0x9D);
    machine.mem_store_byte(0x0D4EC, 0xF4);
    machine.mem_store_byte(0x0D4ED, 0x00);
    machine.mem_store_byte(0x0D4EE, 0x00);
    machine.mem_store_byte(0x0D4EF, 0x00);
    machine.mem_store_byte(0x0D4F0, 0x00);
    machine.mem_store_byte(0x0D4F1, 0x00);
    machine.mem_store_byte(0x295C0, 0x00);
    machine.mem_store_byte(0x295C1, 0x00);
    machine.mem_store_byte(0x295C2, 0x00);
    machine.mem_store_byte(0x295C3, 0x00);
    machine.mem_store_byte(0x295C4, 0x00);
    machine.mem_store_byte(0x295C5, 0x00);
    machine.mem_store_byte(0x295C6, 0x00);
    machine.mem_store_byte(0x295C7, 0x00);
    machine.mem_store_byte(0x00000, 0xF4);
    machine.mem_store_byte(0x00001, 0xF4);
    machine.mem_store_byte(0x00002, 0x50);
    machine.mem_store_byte(0x00003, 0xE6);
    machine.mem_store_byte(0x00004, 0x46);
    machine.mem_store_byte(0x00005, 0xF2);
    machine.mem_store_byte(0x00006, 0xD9);
    machine.mem_store_byte(0x00007, 0x66);
    machine.mem_store_byte(0x00008, 0x5F);
    machine.mem_store_byte(0x00009, 0xA6);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00008081);
    EXPECT_EQ(cpu.get_ebx(), 0x89233A9A);
    EXPECT_EQ(cpu.get_ecx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0xE2572916);
    EXPECT_EQ(cpu.get_esi(), 0x0852281E);
    EXPECT_EQ(cpu.get_edi(), 0x69F8119B);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x00001E05);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000E551);
    EXPECT_EQ(cpu.get_es(), 0x0000D3CC);
    EXPECT_EQ(cpu.get_fs(), 0x000047D7);
    EXPECT_EQ(cpu.get_gs(), 0x00000008);
    EXPECT_EQ(cpu.get_ss(), 0x0000215C);
    EXPECT_EQ(cpu.get_eip(), 0x00000001);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC04D2);

    // Final RAM entries
}

//
// ror word [ds:eax],50h
//
TEST_F(Test386, ror_word_ds_eax_50h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00009B7D);
    cpu.set_ebx(0xDA835818);
    cpu.set_ecx(0x34D46BAB);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x21619C47);
    cpu.set_edi(0x0E744C03);
    cpu.set_ebp(0x00007FFF);
    cpu.set_esp(0x0000DCF0);
    cpu.set_cs(0x000018C9);
    cpu.set_ds(0x0000FA98);
    cpu.set_es(0x0000AACD);
    cpu.set_fs(0x00008367);
    cpu.set_gs(0x00002C0C);
    cpu.set_ss(0x00000990);
    cpu.set_eip(0x00006970);
    cpu.set_eflags(0xFFFC00D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1F600, 0x67);
    machine.mem_store_byte(0x1F601, 0xC1);
    machine.mem_store_byte(0x1F602, 0x08);
    machine.mem_store_byte(0x1F603, 0x50);
    machine.mem_store_byte(0x1F604, 0xF4);
    machine.mem_store_byte(0x1F605, 0xD5);
    machine.mem_store_byte(0x1F606, 0xAC);
    machine.mem_store_byte(0x1F607, 0x50);
    machine.mem_store_byte(0x1F608, 0x98);
    machine.mem_store_byte(0x1F609, 0x36);
    machine.mem_store_byte(0x1F60A, 0xA6);
    machine.mem_store_byte(0x1F60B, 0x45);
    machine.mem_store_byte(0x1044FD, 0x30);
    machine.mem_store_byte(0x1044FE, 0x18);
    machine.mem_store_byte(0x1F60C, 0x1F);
    machine.mem_store_byte(0x1F60D, 0x12);
    machine.mem_store_byte(0x1F60E, 0xFF);
    machine.mem_store_byte(0x1F60F, 0xC3);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00009B7D);
    EXPECT_EQ(cpu.get_ebx(), 0xDA835818);
    EXPECT_EQ(cpu.get_ecx(), 0x34D46BAB);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x21619C47);
    EXPECT_EQ(cpu.get_edi(), 0x0E744C03);
    EXPECT_EQ(cpu.get_ebp(), 0x00007FFF);
    EXPECT_EQ(cpu.get_esp(), 0x0000DCF0);
    EXPECT_EQ(cpu.get_cs(), 0x000018C9);
    EXPECT_EQ(cpu.get_ds(), 0x0000FA98);
    EXPECT_EQ(cpu.get_es(), 0x0000AACD);
    EXPECT_EQ(cpu.get_fs(), 0x00008367);
    EXPECT_EQ(cpu.get_gs(), 0x00002C0C);
    EXPECT_EQ(cpu.get_ss(), 0x00000990);
    EXPECT_EQ(cpu.get_eip(), 0x00006975);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC00D2);

    // Final RAM entries
}
