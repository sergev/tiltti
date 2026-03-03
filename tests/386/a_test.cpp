#include "test386.h"

//
// add [ss:bp+60h],bl
//
TEST_F(Test386, add_ss_bp_60h_bl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x02CBE622);
    cpu.set_ebx(0x682431A8);
    cpu.set_ecx(0xC18D0AD1);
    cpu.set_edx(0xFAB60DE4);
    cpu.set_esi(0x007F0000);
    cpu.set_edi(0xF1A67FE0);
    cpu.set_ebp(0x00080001);
    cpu.set_esp(0x0000DDEB);
    cpu.set_cs(0x00001F22);
    cpu.set_ds(0x00000329);
    cpu.set_es(0x00004533);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00000F0F);
    cpu.set_ss(0x0000F7EC);
    cpu.set_eip(0x000072A0);
    cpu.set_eflags(0xFFFC0893);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x264C0, 0x00);
    machine.mem_store_byte(0x264C1, 0x5E);
    machine.mem_store_byte(0x264C2, 0x60);
    machine.mem_store_byte(0x264C3, 0xF4);
    machine.mem_store_byte(0x264C4, 0x3F);
    machine.mem_store_byte(0x264C5, 0xD8);
    machine.mem_store_byte(0x264C6, 0x23);
    machine.mem_store_byte(0x264C7, 0xF3);
    machine.mem_store_byte(0x264C8, 0x30);
    machine.mem_store_byte(0x264C9, 0x28);
    machine.mem_store_byte(0xF7F21, 0x0B);
    machine.mem_store_byte(0x264CA, 0x0A);
    machine.mem_store_byte(0x264CB, 0xED);
    machine.mem_store_byte(0x264CC, 0x19);
    machine.mem_store_byte(0x264CD, 0xE7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x02CBE622);
    EXPECT_EQ(cpu.get_ebx(), 0x682431A8);
    EXPECT_EQ(cpu.get_ecx(), 0xC18D0AD1);
    EXPECT_EQ(cpu.get_edx(), 0xFAB60DE4);
    EXPECT_EQ(cpu.get_esi(), 0x007F0000);
    EXPECT_EQ(cpu.get_edi(), 0xF1A67FE0);
    EXPECT_EQ(cpu.get_ebp(), 0x00080001);
    EXPECT_EQ(cpu.get_esp(), 0x0000DDEB);
    EXPECT_EQ(cpu.get_cs(), 0x00001F22);
    EXPECT_EQ(cpu.get_ds(), 0x00000329);
    EXPECT_EQ(cpu.get_es(), 0x00004533);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00000F0F);
    EXPECT_EQ(cpu.get_ss(), 0x0000F7EC);
    EXPECT_EQ(cpu.get_eip(), 0x000072A4);
    EXPECT_FLAGS(0xFFFC0092);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF7F21), 0xB3);
}

//
// aaa
//
TEST_F(Test386, aaa)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x10000000);
    cpu.set_ebx(0x3FFD7821);
    cpu.set_ecx(0x00000081);
    cpu.set_edx(0xF46E3D0E);
    cpu.set_esi(0xF2DA9E35);
    cpu.set_edi(0x00000002);
    cpu.set_ebp(0x0CB164B2);
    cpu.set_esp(0x0000FF2E);
    cpu.set_cs(0x00003E82);
    cpu.set_ds(0x00004133);
    cpu.set_es(0x00006334);
    cpu.set_fs(0x000059A8);
    cpu.set_gs(0x0000F405);
    cpu.set_ss(0x00001F8D);
    cpu.set_eip(0x0000ECB8);
    cpu.set_eflags(0xFFFC08D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4D4D8, 0x37);
    machine.mem_store_byte(0x4D4D9, 0xF4);
    machine.mem_store_byte(0x4D4DA, 0xB4);
    machine.mem_store_byte(0x4D4DB, 0x0A);
    machine.mem_store_byte(0x4D4DC, 0x0E);
    machine.mem_store_byte(0x4D4DD, 0xF4);
    machine.mem_store_byte(0x4D4DE, 0x24);
    machine.mem_store_byte(0x4D4DF, 0xF4);
    machine.mem_store_byte(0x4D4E0, 0xA0);
    machine.mem_store_byte(0x4D4E1, 0x24);
    machine.mem_store_byte(0x4D4E2, 0x6B);
    machine.mem_store_byte(0x4D4E3, 0xEF);
    machine.mem_store_byte(0x4D4E4, 0x4C);
    machine.mem_store_byte(0x4D4E5, 0x67);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x10000106);
    EXPECT_EQ(cpu.get_ebx(), 0x3FFD7821);
    EXPECT_EQ(cpu.get_ecx(), 0x00000081);
    EXPECT_EQ(cpu.get_edx(), 0xF46E3D0E);
    EXPECT_EQ(cpu.get_esi(), 0xF2DA9E35);
    EXPECT_EQ(cpu.get_edi(), 0x00000002);
    EXPECT_EQ(cpu.get_ebp(), 0x0CB164B2);
    EXPECT_EQ(cpu.get_esp(), 0x0000FF2E);
    EXPECT_EQ(cpu.get_cs(), 0x00003E82);
    EXPECT_EQ(cpu.get_ds(), 0x00004133);
    EXPECT_EQ(cpu.get_es(), 0x00006334);
    EXPECT_EQ(cpu.get_fs(), 0x000059A8);
    EXPECT_EQ(cpu.get_gs(), 0x0000F405);
    EXPECT_EQ(cpu.get_ss(), 0x00001F8D);
    EXPECT_EQ(cpu.get_eip(), 0x0000ECBA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0017);

    // Final RAM entries
}

//
// adc byte [ds:esi],E4h
//
TEST_F(Test386, adc_byte_ds_esi_E4h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x03846B1F);
    cpu.set_ebx(0xA1F684F5);
    cpu.set_ecx(0x0000001D);
    cpu.set_edx(0x8691F9FB);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xB0D8A1D5);
    cpu.set_ebp(0x8A9DC63A);
    cpu.set_esp(0x000062D6);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x0000007F);
    cpu.set_es(0x00009AF3);
    cpu.set_fs(0x0000F64C);
    cpu.set_gs(0x00000091);
    cpu.set_ss(0x0000E37F);
    cpu.set_eip(0x0000D470);
    cpu.set_eflags(0xFFFC0487);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10D460, 0x67);
    machine.mem_store_byte(0x10D461, 0x82);
    machine.mem_store_byte(0x10D462, 0x16);
    machine.mem_store_byte(0x10D463, 0xE4);
    machine.mem_store_byte(0x10D464, 0xF4);
    machine.mem_store_byte(0x10D465, 0x41);
    machine.mem_store_byte(0x10D466, 0x30);
    machine.mem_store_byte(0x10D467, 0x28);
    machine.mem_store_byte(0x10D468, 0x94);
    machine.mem_store_byte(0x10D469, 0x70);
    machine.mem_store_byte(0x10D46A, 0xF1);
    machine.mem_store_byte(0x10D46B, 0x39);
    machine.mem_store_byte(0x007F0, 0x5D);
    machine.mem_store_byte(0x10D46C, 0x4E);
    machine.mem_store_byte(0x10D46D, 0x34);
    machine.mem_store_byte(0x10D46E, 0x84);
    machine.mem_store_byte(0x10D46F, 0x14);
    machine.mem_store_byte(0x10D470, 0x1F);
    machine.mem_store_byte(0x10D471, 0xB0);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x03846B1F);
    EXPECT_EQ(cpu.get_ebx(), 0xA1F684F5);
    EXPECT_EQ(cpu.get_ecx(), 0x0000001D);
    EXPECT_EQ(cpu.get_edx(), 0x8691F9FB);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xB0D8A1D5);
    EXPECT_EQ(cpu.get_ebp(), 0x8A9DC63A);
    EXPECT_EQ(cpu.get_esp(), 0x000062D6);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000007F);
    EXPECT_EQ(cpu.get_es(), 0x00009AF3);
    EXPECT_EQ(cpu.get_fs(), 0x0000F64C);
    EXPECT_EQ(cpu.get_gs(), 0x00000091);
    EXPECT_EQ(cpu.get_ss(), 0x0000E37F);
    EXPECT_EQ(cpu.get_eip(), 0x0000D475);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x007F0), 0x42);
}

//
// a32 cmpsd
//
TEST_F(Test386, a32_cmpsd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x75FA03EC);
    cpu.set_ebx(0x9BEDF158);
    cpu.set_ecx(0xD8E7F8BE);
    cpu.set_edx(0x4CAAEB2E);
    cpu.set_esi(0x000047E0);
    cpu.set_edi(0x00000C0A);
    cpu.set_ebp(0x5A41885F);
    cpu.set_esp(0x0000B7EC);
    cpu.set_cs(0x0000CFFB);
    cpu.set_ds(0x0000BF6D);
    cpu.set_es(0x0000CAB5);
    cpu.set_fs(0x000024E7);
    cpu.set_gs(0x0000EA7E);
    cpu.set_ss(0x00006AAE);
    cpu.set_eip(0x00002FF0);
    cpu.set_eflags(0xFFFC0C17);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD2FA0, 0x67);
    machine.mem_store_byte(0xD2FA1, 0x66);
    machine.mem_store_byte(0xD2FA2, 0xA7);
    machine.mem_store_byte(0xD2FA3, 0xF4);
    machine.mem_store_byte(0xD2FA4, 0x2E);
    machine.mem_store_byte(0xD2FA5, 0x73);
    machine.mem_store_byte(0xD2FA6, 0x38);
    machine.mem_store_byte(0xD2FA7, 0x8C);
    machine.mem_store_byte(0xD2FA8, 0x98);
    machine.mem_store_byte(0xD2FA9, 0xBB);
    machine.mem_store_byte(0xD2FAA, 0x00);
    machine.mem_store_byte(0xD2FAB, 0xFB);
    machine.mem_store_byte(0xCB75C, 0x1E);
    machine.mem_store_byte(0xCB75D, 0x61);
    machine.mem_store_byte(0xCB75A, 0x84);
    machine.mem_store_byte(0xCB75B, 0xC7);
    machine.mem_store_byte(0xC3EB0, 0x71);
    machine.mem_store_byte(0xC3EB1, 0xD0);
    machine.mem_store_byte(0xC3EB2, 0xD0);
    machine.mem_store_byte(0xC3EB3, 0x95);
    machine.mem_store_byte(0xD2FAC, 0x1C);
    machine.mem_store_byte(0xD2FAD, 0xF0);
    machine.mem_store_byte(0xD2FAE, 0x10);
    machine.mem_store_byte(0xD2FAF, 0x39);
    machine.mem_store_byte(0xD2FB0, 0xEA);
    machine.mem_store_byte(0xD2FB1, 0x64);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x75FA03EC);
    EXPECT_EQ(cpu.get_ebx(), 0x9BEDF158);
    EXPECT_EQ(cpu.get_ecx(), 0xD8E7F8BE);
    EXPECT_EQ(cpu.get_edx(), 0x4CAAEB2E);
    EXPECT_EQ(cpu.get_esi(), 0x000047DC);
    EXPECT_EQ(cpu.get_edi(), 0x00000C06);
    EXPECT_EQ(cpu.get_ebp(), 0x5A41885F);
    EXPECT_EQ(cpu.get_esp(), 0x0000B7EC);
    EXPECT_EQ(cpu.get_cs(), 0x0000CFFB);
    EXPECT_EQ(cpu.get_ds(), 0x0000BF6D);
    EXPECT_EQ(cpu.get_es(), 0x0000CAB5);
    EXPECT_EQ(cpu.get_fs(), 0x000024E7);
    EXPECT_EQ(cpu.get_gs(), 0x0000EA7E);
    EXPECT_EQ(cpu.get_ss(), 0x00006AAE);
    EXPECT_EQ(cpu.get_eip(), 0x00002FF4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C16);

    // Final RAM entries
}

//
// a32 outsd
//
TEST_F(Test386, a32_outsd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xC2F5150A);
    cpu.set_ebx(0x4F1AF76F);
    cpu.set_ecx(0x1A2D05FD);
    cpu.set_edx(0x08CED4E1);
    cpu.set_esi(0x0000B330);
    cpu.set_edi(0x18D6E1F1);
    cpu.set_ebp(0xA8B149E7);
    cpu.set_esp(0x0000AE42);
    cpu.set_cs(0x0000A67A);
    cpu.set_ds(0x0000A97B);
    cpu.set_es(0x00001D33);
    cpu.set_fs(0x0000000A);
    cpu.set_gs(0x0000AAAB);
    cpu.set_ss(0x00004C54);
    cpu.set_eip(0x00004B78);
    cpu.set_eflags(0xFFFC0846);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAB318, 0x67);
    machine.mem_store_byte(0xAB319, 0x66);
    machine.mem_store_byte(0xAB31A, 0x6F);
    machine.mem_store_byte(0xAB31B, 0xF4);
    machine.mem_store_byte(0xAB31C, 0x2E);
    machine.mem_store_byte(0xAB31D, 0x8B);
    machine.mem_store_byte(0xAB31E, 0x16);
    machine.mem_store_byte(0xAB31F, 0x6F);
    machine.mem_store_byte(0xAB320, 0xD5);
    machine.mem_store_byte(0xAB321, 0xD5);
    machine.mem_store_byte(0xAB322, 0x27);
    machine.mem_store_byte(0xAB323, 0xD2);
    machine.mem_store_byte(0xAB324, 0x57);
    machine.mem_store_byte(0xAB325, 0xED);
    machine.mem_store_byte(0xAB326, 0x16);
    machine.mem_store_byte(0xAB327, 0x58);
    machine.mem_store_byte(0xAB328, 0x0B);
    machine.mem_store_byte(0xAB329, 0x50);
    machine.mem_store_byte(0xB4AE0, 0x15);
    machine.mem_store_byte(0xB4AE1, 0xBB);
    machine.mem_store_byte(0xB4AE2, 0xEF);
    machine.mem_store_byte(0xB4AE3, 0x00);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xC2F5150A);
    EXPECT_EQ(cpu.get_ebx(), 0x4F1AF76F);
    EXPECT_EQ(cpu.get_ecx(), 0x1A2D05FD);
    EXPECT_EQ(cpu.get_edx(), 0x08CED4E1);
    EXPECT_EQ(cpu.get_esi(), 0x0000B334);
    EXPECT_EQ(cpu.get_edi(), 0x18D6E1F1);
    EXPECT_EQ(cpu.get_ebp(), 0xA8B149E7);
    EXPECT_EQ(cpu.get_esp(), 0x0000AE42);
    EXPECT_EQ(cpu.get_cs(), 0x0000A67A);
    EXPECT_EQ(cpu.get_ds(), 0x0000A97B);
    EXPECT_EQ(cpu.get_es(), 0x00001D33);
    EXPECT_EQ(cpu.get_fs(), 0x0000000A);
    EXPECT_EQ(cpu.get_gs(), 0x0000AAAB);
    EXPECT_EQ(cpu.get_ss(), 0x00004C54);
    EXPECT_EQ(cpu.get_eip(), 0x00004B7C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0846);

    // Final RAM entries
}

//
// a32 es rep outsb
//
TEST_F(Test386, a32_es_rep_outsb)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x03D90395);
    cpu.set_ebx(0x092A3F3A);
    cpu.set_ecx(0x00000026);
    cpu.set_edx(0x491B266B);
    cpu.set_esi(0x00005211);
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
    machine.mem_store_byte(0x101A28, 0x2E);
    machine.mem_store_byte(0x101A29, 0xF3);
    machine.mem_store_byte(0x101A2A, 0x26);
    machine.mem_store_byte(0x101A2B, 0x67);
    machine.mem_store_byte(0x101A2C, 0x6E);
    machine.mem_store_byte(0x101A2D, 0xF4);
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
    machine.mem_store_byte(0x101A38, 0x1D);
    machine.mem_store_byte(0x101A39, 0x5F);
    machine.mem_store_byte(0x101A3A, 0x95);
    machine.mem_store_byte(0x101A3B, 0xF6);
    machine.mem_store_byte(0x595C1, 0xEC);
    machine.mem_store_byte(0x595C2, 0x07);
    machine.mem_store_byte(0x595C3, 0x6F);
    machine.mem_store_byte(0x595C4, 0xE8);
    machine.mem_store_byte(0x595C5, 0xE0);
    machine.mem_store_byte(0x595C6, 0x93);
    machine.mem_store_byte(0x595C7, 0xA1);
    machine.mem_store_byte(0x595C8, 0x94);
    machine.mem_store_byte(0x595C9, 0x9F);
    machine.mem_store_byte(0x595CA, 0x4A);
    machine.mem_store_byte(0x595CB, 0xED);
    machine.mem_store_byte(0x595CC, 0xF2);
    machine.mem_store_byte(0x595CD, 0x27);
    machine.mem_store_byte(0x595CE, 0x61);
    machine.mem_store_byte(0x595CF, 0x0B);
    machine.mem_store_byte(0x595D0, 0xB7);
    machine.mem_store_byte(0x595D1, 0x88);
    machine.mem_store_byte(0x595D2, 0xED);
    machine.mem_store_byte(0x595D3, 0x18);
    machine.mem_store_byte(0x595D4, 0xBC);
    machine.mem_store_byte(0x595D5, 0x3E);
    machine.mem_store_byte(0x595D6, 0xB2);
    machine.mem_store_byte(0x595D7, 0xB2);
    machine.mem_store_byte(0x595D8, 0x91);
    machine.mem_store_byte(0x595D9, 0x76);
    machine.mem_store_byte(0x595DA, 0x3B);
    machine.mem_store_byte(0x595DB, 0x37);
    machine.mem_store_byte(0x595DC, 0xD8);
    machine.mem_store_byte(0x595DD, 0xB9);
    machine.mem_store_byte(0x595DE, 0xD6);
    machine.mem_store_byte(0x595DF, 0x60);
    machine.mem_store_byte(0x595E0, 0xB4);
    machine.mem_store_byte(0x595E1, 0xB1);
    machine.mem_store_byte(0x595E2, 0xD6);
    machine.mem_store_byte(0x595E3, 0x90);
    machine.mem_store_byte(0x595E4, 0x4E);
    machine.mem_store_byte(0x595E5, 0x0B);
    machine.mem_store_byte(0x595E6, 0xE6);

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
    EXPECT_EQ(cpu.get_esi(), 0x00005237);
    EXPECT_EQ(cpu.get_edi(), 0x912D8CB0);
    EXPECT_EQ(cpu.get_ebp(), 0x0995B712);
    EXPECT_EQ(cpu.get_esp(), 0x0000DAE2);
    EXPECT_EQ(cpu.get_cs(), 0x0000F84B);
    EXPECT_EQ(cpu.get_ds(), 0x0000FD49);
    EXPECT_EQ(cpu.get_es(), 0x0000543B);
    EXPECT_EQ(cpu.get_fs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_gs(), 0x00004A72);
    EXPECT_EQ(cpu.get_ss(), 0x00003928);
    EXPECT_EQ(cpu.get_eip(), 0x0000957E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C6);

    // Final RAM entries
}

//
// a32 insd
//
TEST_F(Test386, a32_insd)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x8E76CCCD);
    cpu.set_ebx(0x7FFFFFFF);
    cpu.set_ecx(0x15C81A9F);
    cpu.set_edx(0x33A4B02F);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0x0000D401);
    cpu.set_ebp(0x15684AE3);
    cpu.set_esp(0x0000537E);
    cpu.set_cs(0x0000AC89);
    cpu.set_ds(0x00008578);
    cpu.set_es(0x0000F408);
    cpu.set_fs(0x00003D9D);
    cpu.set_gs(0x00007FFF);
    cpu.set_ss(0x00000C92);
    cpu.set_eip(0x00009D30);
    cpu.set_eflags(0xFFFC0446);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB65C0, 0x26);
    machine.mem_store_byte(0xB65C1, 0x26);
    machine.mem_store_byte(0xB65C2, 0x67);
    machine.mem_store_byte(0xB65C3, 0x66);
    machine.mem_store_byte(0xB65C4, 0x6D);
    machine.mem_store_byte(0xB65C5, 0xF4);
    machine.mem_store_byte(0xB65C6, 0xCA);
    machine.mem_store_byte(0xB65C7, 0xD4);
    machine.mem_store_byte(0xB65C8, 0x3E);
    machine.mem_store_byte(0xB65C9, 0xD3);
    machine.mem_store_byte(0xB65CA, 0x89);
    machine.mem_store_byte(0xB65CB, 0x45);
    machine.mem_store_byte(0xB65CC, 0xD8);
    machine.mem_store_byte(0xB65CD, 0x1D);
    machine.mem_store_byte(0xB65CE, 0xAA);
    machine.mem_store_byte(0xB65CF, 0x45);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x8E76CCCD);
    EXPECT_EQ(cpu.get_ebx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x15C81A9F);
    EXPECT_EQ(cpu.get_edx(), 0x33A4B02F);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x0000D3FD);
    EXPECT_EQ(cpu.get_ebp(), 0x15684AE3);
    EXPECT_EQ(cpu.get_esp(), 0x0000537E);
    EXPECT_EQ(cpu.get_cs(), 0x0000AC89);
    EXPECT_EQ(cpu.get_ds(), 0x00008578);
    EXPECT_EQ(cpu.get_es(), 0x0000F408);
    EXPECT_EQ(cpu.get_fs(), 0x00003D9D);
    EXPECT_EQ(cpu.get_gs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ss(), 0x00000C92);
    EXPECT_EQ(cpu.get_eip(), 0x00009D36);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x101484), 0xFF);
    EXPECT_EQ(memory.load8(0x101481), 0xFF);
    EXPECT_EQ(memory.load8(0x101482), 0xFF);
    EXPECT_EQ(memory.load8(0x101483), 0xFF);
}

//
// adc eax,C76E2E17h
//
TEST_F(Test386, adc_eax_C76E2E17h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00010000);
    cpu.set_ebx(0xEDDF9FCA);
    cpu.set_ecx(0x8B9B2F25);
    cpu.set_edx(0x4C993710);
    cpu.set_esi(0x750F8C02);
    cpu.set_edi(0xE58CF697);
    cpu.set_ebp(0x341485AA);
    cpu.set_esp(0x00005BB8);
    cpu.set_cs(0x000038D9);
    cpu.set_ds(0x00002CD6);
    cpu.set_es(0x000000A0);
    cpu.set_fs(0x0000FA75);
    cpu.set_gs(0x00000010);
    cpu.set_ss(0x00004BB7);
    cpu.set_eip(0x00001590);
    cpu.set_eflags(0xFFFC0816);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3A320, 0x66);
    machine.mem_store_byte(0x3A321, 0x15);
    machine.mem_store_byte(0x3A322, 0x17);
    machine.mem_store_byte(0x3A323, 0x2E);
    machine.mem_store_byte(0x3A324, 0x6E);
    machine.mem_store_byte(0x3A325, 0xC7);
    machine.mem_store_byte(0x3A326, 0xF4);
    machine.mem_store_byte(0x3A327, 0xB3);
    machine.mem_store_byte(0x3A328, 0x96);
    machine.mem_store_byte(0x3A329, 0xC0);
    machine.mem_store_byte(0x3A32A, 0xA7);
    machine.mem_store_byte(0x3A32B, 0x4A);
    machine.mem_store_byte(0x3A32C, 0x83);
    machine.mem_store_byte(0x3A32D, 0x92);
    machine.mem_store_byte(0x3A32E, 0x3F);
    machine.mem_store_byte(0x3A32F, 0x07);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xC76F2E17);
    EXPECT_EQ(cpu.get_ebx(), 0xEDDF9FCA);
    EXPECT_EQ(cpu.get_ecx(), 0x8B9B2F25);
    EXPECT_EQ(cpu.get_edx(), 0x4C993710);
    EXPECT_EQ(cpu.get_esi(), 0x750F8C02);
    EXPECT_EQ(cpu.get_edi(), 0xE58CF697);
    EXPECT_EQ(cpu.get_ebp(), 0x341485AA);
    EXPECT_EQ(cpu.get_esp(), 0x00005BB8);
    EXPECT_EQ(cpu.get_cs(), 0x000038D9);
    EXPECT_EQ(cpu.get_ds(), 0x00002CD6);
    EXPECT_EQ(cpu.get_es(), 0x000000A0);
    EXPECT_EQ(cpu.get_fs(), 0x0000FA75);
    EXPECT_EQ(cpu.get_gs(), 0x00000010);
    EXPECT_EQ(cpu.get_ss(), 0x00004BB7);
    EXPECT_EQ(cpu.get_eip(), 0x00001597);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0086);

    // Final RAM entries
}

//
// adc ebp,esp
//
TEST_F(Test386, adc_ebp_esp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x224E551C);
    cpu.set_ebx(0xD4B521BD);
    cpu.set_ecx(0x0000009F);
    cpu.set_edx(0xE19C5A37);
    cpu.set_esi(0xFFFFFFF8);
    cpu.set_edi(0xB73DE53D);
    cpu.set_ebp(0xFF7FFFFF);
    cpu.set_esp(0x00009024);
    cpu.set_cs(0x00000091);
    cpu.set_ds(0x00000401);
    cpu.set_es(0x000040F2);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00004757);
    cpu.set_ss(0x00000020);
    cpu.set_eip(0x00004FB0);
    cpu.set_eflags(0xFFFC0C13);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x058C0, 0x67);
    machine.mem_store_byte(0x058C1, 0x66);
    machine.mem_store_byte(0x058C2, 0x11);
    machine.mem_store_byte(0x058C3, 0xE5);
    machine.mem_store_byte(0x058C4, 0xF4);
    machine.mem_store_byte(0x058C5, 0x78);
    machine.mem_store_byte(0x058C6, 0x70);
    machine.mem_store_byte(0x058C7, 0xB6);
    machine.mem_store_byte(0x058C8, 0xA2);
    machine.mem_store_byte(0x058C9, 0x9F);
    machine.mem_store_byte(0x058CA, 0xF6);
    machine.mem_store_byte(0x058CB, 0xAD);
    machine.mem_store_byte(0x058CC, 0xCA);
    machine.mem_store_byte(0x058CD, 0x6B);
    machine.mem_store_byte(0x058CE, 0x30);
    machine.mem_store_byte(0x058CF, 0xEF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x224E551C);
    EXPECT_EQ(cpu.get_ebx(), 0xD4B521BD);
    EXPECT_EQ(cpu.get_ecx(), 0x0000009F);
    EXPECT_EQ(cpu.get_edx(), 0xE19C5A37);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFF8);
    EXPECT_EQ(cpu.get_edi(), 0xB73DE53D);
    EXPECT_EQ(cpu.get_ebp(), 0xFF809024);
    EXPECT_EQ(cpu.get_esp(), 0x00009024);
    EXPECT_EQ(cpu.get_cs(), 0x00000091);
    EXPECT_EQ(cpu.get_ds(), 0x00000401);
    EXPECT_EQ(cpu.get_es(), 0x000040F2);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00004757);
    EXPECT_EQ(cpu.get_ss(), 0x00000020);
    EXPECT_EQ(cpu.get_eip(), 0x00004FB5);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0496);

    // Final RAM entries
}

//
// add [ds:bx-1855h],edx
//
TEST_F(Test386, add_ds_bx_1855h_edx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE0A86B6F);
    cpu.set_ebx(0x6547C212);
    cpu.set_ecx(0x00080001);
    cpu.set_edx(0x67F37054);
    cpu.set_esi(0x257C2E3F);
    cpu.set_edi(0x57BDBEBD);
    cpu.set_ebp(0x4BD33352);
    cpu.set_esp(0x00005794);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x00000000);
    cpu.set_es(0x00006D57);
    cpu.set_fs(0x0000DA9A);
    cpu.set_gs(0x00000AA6);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00005330);
    cpu.set_eflags(0xFFFC04C3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05330, 0x66);
    machine.mem_store_byte(0x05331, 0x01);
    machine.mem_store_byte(0x05332, 0x97);
    machine.mem_store_byte(0x05333, 0xAB);
    machine.mem_store_byte(0x05334, 0xE7);
    machine.mem_store_byte(0x05335, 0xF4);
    machine.mem_store_byte(0x05336, 0xDB);
    machine.mem_store_byte(0x05337, 0x17);
    machine.mem_store_byte(0x05338, 0x66);
    machine.mem_store_byte(0x05339, 0xC7);
    machine.mem_store_byte(0x0533A, 0xB1);
    machine.mem_store_byte(0x0533B, 0x09);
    machine.mem_store_byte(0x0A9C0, 0xE5);
    machine.mem_store_byte(0x0A9BD, 0xC5);
    machine.mem_store_byte(0x0A9BE, 0x30);
    machine.mem_store_byte(0x0A9BF, 0x53);
    machine.mem_store_byte(0x0533C, 0xD9);
    machine.mem_store_byte(0x0533D, 0x9C);
    machine.mem_store_byte(0x0533E, 0xED);
    machine.mem_store_byte(0x0533F, 0xD6);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE0A86B6F);
    EXPECT_EQ(cpu.get_ebx(), 0x6547C212);
    EXPECT_EQ(cpu.get_ecx(), 0x00080001);
    EXPECT_EQ(cpu.get_edx(), 0x67F37054);
    EXPECT_EQ(cpu.get_esi(), 0x257C2E3F);
    EXPECT_EQ(cpu.get_edi(), 0x57BDBEBD);
    EXPECT_EQ(cpu.get_ebp(), 0x4BD33352);
    EXPECT_EQ(cpu.get_esp(), 0x00005794);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x00000000);
    EXPECT_EQ(cpu.get_es(), 0x00006D57);
    EXPECT_EQ(cpu.get_fs(), 0x0000DA9A);
    EXPECT_EQ(cpu.get_gs(), 0x00000AA6);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x00005336);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0403);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0A9C0), 0x4D);
    EXPECT_EQ(memory.load8(0x0A9BD), 0x19);
    EXPECT_EQ(memory.load8(0x0A9BE), 0xA1);
    EXPECT_EQ(memory.load8(0x0A9BF), 0x46);
}

//
// and eax,1386608Eh
//
TEST_F(Test386, and_eax_1386608Eh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x46045051);
    cpu.set_ebx(0x01010101);
    cpu.set_ecx(0x9BDF54E7);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x00004001);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x41E1895B);
    cpu.set_esp(0x00003622);
    cpu.set_cs(0x0000A5D4);
    cpu.set_ds(0x00000069);
    cpu.set_es(0x0000FED5);
    cpu.set_fs(0x0000BC0D);
    cpu.set_gs(0x000030F7);
    cpu.set_ss(0x00002D54);
    cpu.set_eip(0x0000E2E0);
    cpu.set_eflags(0xFFFC0053);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB4020, 0x66);
    machine.mem_store_byte(0xB4021, 0x25);
    machine.mem_store_byte(0xB4022, 0x8E);
    machine.mem_store_byte(0xB4023, 0x60);
    machine.mem_store_byte(0xB4024, 0x86);
    machine.mem_store_byte(0xB4025, 0x13);
    machine.mem_store_byte(0xB4026, 0xF4);
    machine.mem_store_byte(0xB4027, 0x52);
    machine.mem_store_byte(0xB4028, 0xAE);
    machine.mem_store_byte(0xB4029, 0x13);
    machine.mem_store_byte(0xB402A, 0x44);
    machine.mem_store_byte(0xB402B, 0x27);
    machine.mem_store_byte(0xB402C, 0x37);
    machine.mem_store_byte(0xB402D, 0xD2);
    machine.mem_store_byte(0xB402E, 0xD7);
    machine.mem_store_byte(0xB402F, 0x17);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x02044000);
    EXPECT_EQ(cpu.get_ebx(), 0x01010101);
    EXPECT_EQ(cpu.get_ecx(), 0x9BDF54E7);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x00004001);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x41E1895B);
    EXPECT_EQ(cpu.get_esp(), 0x00003622);
    EXPECT_EQ(cpu.get_cs(), 0x0000A5D4);
    EXPECT_EQ(cpu.get_ds(), 0x00000069);
    EXPECT_EQ(cpu.get_es(), 0x0000FED5);
    EXPECT_EQ(cpu.get_fs(), 0x0000BC0D);
    EXPECT_EQ(cpu.get_gs(), 0x000030F7);
    EXPECT_EQ(cpu.get_ss(), 0x00002D54);
    EXPECT_EQ(cpu.get_eip(), 0x0000E2E7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0006);

    // Final RAM entries
}

//
// add eax,B5BA95C4h
//
TEST_F(Test386, add_eax_B5BA95C4h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA3802EAF);
    cpu.set_ebx(0x0000004F);
    cpu.set_ecx(0x53CEAF98);
    cpu.set_edx(0x6B98BD9C);
    cpu.set_esi(0xFD68A229);
    cpu.set_edi(0x04CED189);
    cpu.set_ebp(0xFF569EF0);
    cpu.set_esp(0x0000C640);
    cpu.set_cs(0x00007555);
    cpu.set_ds(0x00000801);
    cpu.set_es(0x00004000);
    cpu.set_fs(0x0000B38C);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x000090A0);
    cpu.set_eflags(0xFFFC04C7);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7E5F0, 0x66);
    machine.mem_store_byte(0x7E5F1, 0x05);
    machine.mem_store_byte(0x7E5F2, 0xC4);
    machine.mem_store_byte(0x7E5F3, 0x95);
    machine.mem_store_byte(0x7E5F4, 0xBA);
    machine.mem_store_byte(0x7E5F5, 0xB5);
    machine.mem_store_byte(0x7E5F6, 0xF4);
    machine.mem_store_byte(0x7E5F7, 0xC6);
    machine.mem_store_byte(0x7E5F8, 0xCF);
    machine.mem_store_byte(0x7E5F9, 0x8F);
    machine.mem_store_byte(0x7E5FA, 0xA0);
    machine.mem_store_byte(0x7E5FB, 0xA9);
    machine.mem_store_byte(0x7E5FC, 0x11);
    machine.mem_store_byte(0x7E5FD, 0x9D);
    machine.mem_store_byte(0x7E5FE, 0x14);
    machine.mem_store_byte(0x7E5FF, 0x22);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x593AC473);
    EXPECT_EQ(cpu.get_ebx(), 0x0000004F);
    EXPECT_EQ(cpu.get_ecx(), 0x53CEAF98);
    EXPECT_EQ(cpu.get_edx(), 0x6B98BD9C);
    EXPECT_EQ(cpu.get_esi(), 0xFD68A229);
    EXPECT_EQ(cpu.get_edi(), 0x04CED189);
    EXPECT_EQ(cpu.get_ebp(), 0xFF569EF0);
    EXPECT_EQ(cpu.get_esp(), 0x0000C640);
    EXPECT_EQ(cpu.get_cs(), 0x00007555);
    EXPECT_EQ(cpu.get_ds(), 0x00000801);
    EXPECT_EQ(cpu.get_es(), 0x00004000);
    EXPECT_EQ(cpu.get_fs(), 0x0000B38C);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x000090A7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C13);

    // Final RAM entries
}

//
// and ecx,ebp
//
TEST_F(Test386, and_ecx_ebp)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1A4819B5);
    cpu.set_ebx(0x0101B489);
    cpu.set_ecx(0x11519CB2);
    cpu.set_edx(0x543EA0C5);
    cpu.set_esi(0x6162D3B3);
    cpu.set_edi(0x04AC015D);
    cpu.set_ebp(0x11F4DF86);
    cpu.set_esp(0x00002E20);
    cpu.set_cs(0x00000002);
    cpu.set_ds(0x0000024F);
    cpu.set_es(0x00000201);
    cpu.set_fs(0x0000EE25);
    cpu.set_gs(0x00008B89);
    cpu.set_ss(0x0000FFFF);
    cpu.set_eip(0x00007590);
    cpu.set_eflags(0xFFFC0C13);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x075B0, 0x67);
    machine.mem_store_byte(0x075B1, 0x66);
    machine.mem_store_byte(0x075B2, 0x21);
    machine.mem_store_byte(0x075B3, 0xE9);
    machine.mem_store_byte(0x075B4, 0xF4);
    machine.mem_store_byte(0x075B5, 0x00);
    machine.mem_store_byte(0x075B6, 0x00);
    machine.mem_store_byte(0x075B7, 0x00);
    machine.mem_store_byte(0x075B8, 0x00);
    machine.mem_store_byte(0x075B9, 0x00);
    machine.mem_store_byte(0x075BA, 0x00);
    machine.mem_store_byte(0x075BB, 0x00);
    machine.mem_store_byte(0x075BC, 0x00);
    machine.mem_store_byte(0x075BD, 0x00);
    machine.mem_store_byte(0x075BE, 0x00);
    machine.mem_store_byte(0x075BF, 0x00);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1A4819B5);
    EXPECT_EQ(cpu.get_ebx(), 0x0101B489);
    EXPECT_EQ(cpu.get_ecx(), 0x11509C82);
    EXPECT_EQ(cpu.get_edx(), 0x543EA0C5);
    EXPECT_EQ(cpu.get_esi(), 0x6162D3B3);
    EXPECT_EQ(cpu.get_edi(), 0x04AC015D);
    EXPECT_EQ(cpu.get_ebp(), 0x11F4DF86);
    EXPECT_EQ(cpu.get_esp(), 0x00002E20);
    EXPECT_EQ(cpu.get_cs(), 0x00000002);
    EXPECT_EQ(cpu.get_ds(), 0x0000024F);
    EXPECT_EQ(cpu.get_es(), 0x00000201);
    EXPECT_EQ(cpu.get_fs(), 0x0000EE25);
    EXPECT_EQ(cpu.get_gs(), 0x00008B89);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_eip(), 0x00007595);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0406);

    // Final RAM entries
}

//
// adc cl,[ss:ebp-37CCh]
//
TEST_F(Test386, adc_cl_ss_ebp_37CCh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xAD3EC2E5);
    cpu.set_ebx(0x00000101);
    cpu.set_ecx(0xDDD52345);
    cpu.set_edx(0x23A97A83);
    cpu.set_esi(0xCB17D46F);
    cpu.set_edi(0x00200001);
    cpu.set_ebp(0x000000A1);
    cpu.set_esp(0x0000FAC8);
    cpu.set_cs(0x00000050);
    cpu.set_ds(0x00000938);
    cpu.set_es(0x000006A5);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x000042D0);
    cpu.set_ss(0x0000199F);
    cpu.set_eip(0x00001478);
    cpu.set_eflags(0xFFFC0806);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x01978, 0x67);
    machine.mem_store_byte(0x01979, 0x12);
    machine.mem_store_byte(0x0197A, 0x8D);
    machine.mem_store_byte(0x0197B, 0x34);
    machine.mem_store_byte(0x0197C, 0xC8);
    machine.mem_store_byte(0x0197D, 0xFF);
    machine.mem_store_byte(0x0197E, 0xFF);
    machine.mem_store_byte(0x0197F, 0xF4);
    machine.mem_store_byte(0x01980, 0x3C);
    machine.mem_store_byte(0x01981, 0x34);
    machine.mem_store_byte(0x01982, 0xE3);
    machine.mem_store_byte(0x01983, 0x59);
    machine.mem_store_byte(0x01984, 0x9F);
    machine.mem_store_byte(0x01985, 0x2A);
    machine.mem_store_byte(0x01986, 0x0C);
    machine.mem_store_byte(0x01987, 0xAC);
    machine.mem_store_byte(0x01988, 0xA3);
    machine.mem_store_byte(0x01989, 0x04);
    machine.mem_store_byte(0x0198A, 0xF9);
    machine.mem_store_byte(0x0198B, 0x6B);
    machine.mem_store_byte(0x00030, 0xF7);
    machine.mem_store_byte(0x00031, 0x4B);
    machine.mem_store_byte(0x00032, 0x50);
    machine.mem_store_byte(0x00033, 0x01);
    machine.mem_store_byte(0x060F6, 0x08);
    machine.mem_store_byte(0x060F7, 0xF4);
    machine.mem_store_byte(0x060F8, 0x98);
    machine.mem_store_byte(0x060F9, 0xF4);
    machine.mem_store_byte(0x060FA, 0xB2);
    machine.mem_store_byte(0x060FB, 0xF4);
    machine.mem_store_byte(0x060FC, 0x59);
    machine.mem_store_byte(0x060FD, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xAD3EC2E5);
    EXPECT_EQ(cpu.get_ebx(), 0x00000101);
    EXPECT_EQ(cpu.get_ecx(), 0xDDD52345);
    EXPECT_EQ(cpu.get_edx(), 0x23A97A83);
    EXPECT_EQ(cpu.get_esi(), 0xCB17D46F);
    EXPECT_EQ(cpu.get_edi(), 0x00200001);
    EXPECT_EQ(cpu.get_ebp(), 0x000000A1);
    EXPECT_EQ(cpu.get_esp(), 0x0000FAC2);
    EXPECT_EQ(cpu.get_cs(), 0x00000150);
    EXPECT_EQ(cpu.get_ds(), 0x00000938);
    EXPECT_EQ(cpu.get_es(), 0x000006A5);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x000042D0);
    EXPECT_EQ(cpu.get_ss(), 0x0000199F);
    EXPECT_EQ(cpu.get_eip(), 0x00004BF8);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0806);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x294B6), 0x06);
    EXPECT_EQ(memory.load8(0x294B7), 0x08);
    EXPECT_EQ(memory.load8(0x294B4), 0x50);
    EXPECT_EQ(memory.load8(0x294B5), 0x00);
    EXPECT_EQ(memory.load8(0x294B2), 0x78);
    EXPECT_EQ(memory.load8(0x294B3), 0x14);
}

//
// add byte [ds:ebx+72C6h],5Dh
//
TEST_F(Test386, add_byte_ds_ebx_72C6h_5Dh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1E6F9E6D);
    cpu.set_ebx(0x0000FFFE);
    cpu.set_ecx(0x744BA710);
    cpu.set_edx(0x00000090);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xC4AEF73B);
    cpu.set_ebp(0x2681C61A);
    cpu.set_esp(0x000033B0);
    cpu.set_cs(0x00000800);
    cpu.set_ds(0x000068A4);
    cpu.set_es(0x00000021);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x0000B25B);
    cpu.set_ss(0x0000A19E);
    cpu.set_eip(0x00006A58);
    cpu.set_eflags(0xFFFC0C52);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0EA58, 0x67);
    machine.mem_store_byte(0x0EA59, 0x80);
    machine.mem_store_byte(0x0EA5A, 0x83);
    machine.mem_store_byte(0x0EA5B, 0xC6);
    machine.mem_store_byte(0x0EA5C, 0x72);
    machine.mem_store_byte(0x0EA5D, 0x00);
    machine.mem_store_byte(0x0EA5E, 0x00);
    machine.mem_store_byte(0x0EA5F, 0x5D);
    machine.mem_store_byte(0x0EA60, 0xF4);
    machine.mem_store_byte(0x0EA61, 0x7F);
    machine.mem_store_byte(0x0EA62, 0x5E);
    machine.mem_store_byte(0x0EA63, 0x4D);
    machine.mem_store_byte(0x0EA64, 0xC9);
    machine.mem_store_byte(0x0EA65, 0xD5);
    machine.mem_store_byte(0x0EA66, 0x6C);
    machine.mem_store_byte(0x0EA67, 0xC0);
    machine.mem_store_byte(0x0EA68, 0x1D);
    machine.mem_store_byte(0x0EA69, 0x24);
    machine.mem_store_byte(0x0EA6A, 0xAE);
    machine.mem_store_byte(0x0EA6B, 0x03);
    machine.mem_store_byte(0x0EA6C, 0x90);
    machine.mem_store_byte(0x0EA6D, 0x12);
    machine.mem_store_byte(0x0EA6E, 0xAD);
    machine.mem_store_byte(0x0EA6F, 0xF4);
    machine.mem_store_byte(0x00034, 0xC7);
    machine.mem_store_byte(0x00035, 0x07);
    machine.mem_store_byte(0x00036, 0x1C);
    machine.mem_store_byte(0x00037, 0x63);
    machine.mem_store_byte(0x63986, 0x3A);
    machine.mem_store_byte(0x63987, 0xF4);
    machine.mem_store_byte(0x63988, 0x6C);
    machine.mem_store_byte(0x63989, 0xF4);
    machine.mem_store_byte(0x6398A, 0x36);
    machine.mem_store_byte(0x6398B, 0xF4);
    machine.mem_store_byte(0x6398C, 0x06);
    machine.mem_store_byte(0x6398D, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1E6F9E6D);
    EXPECT_EQ(cpu.get_ebx(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_ecx(), 0x744BA710);
    EXPECT_EQ(cpu.get_edx(), 0x00000090);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xC4AEF73B);
    EXPECT_EQ(cpu.get_ebp(), 0x2681C61A);
    EXPECT_EQ(cpu.get_esp(), 0x000033AA);
    EXPECT_EQ(cpu.get_cs(), 0x0000631C);
    EXPECT_EQ(cpu.get_ds(), 0x000068A4);
    EXPECT_EQ(cpu.get_es(), 0x00000021);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x0000B25B);
    EXPECT_EQ(cpu.get_ss(), 0x0000A19E);
    EXPECT_EQ(cpu.get_eip(), 0x000007C8);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C52);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA4D8E), 0x52);
    EXPECT_EQ(memory.load8(0xA4D8F), 0x0C);
    EXPECT_EQ(memory.load8(0xA4D8C), 0x00);
    EXPECT_EQ(memory.load8(0xA4D8D), 0x08);
    EXPECT_EQ(memory.load8(0xA4D8A), 0x58);
    EXPECT_EQ(memory.load8(0xA4D8B), 0x6A);
}
