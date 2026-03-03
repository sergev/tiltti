#include "test386.h"

//
// xchg bx,ax
//
TEST_F(Test386, xchg_bx_ax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0C3FD377);
    cpu.set_ebx(0x19C3CFDD);
    cpu.set_ecx(0x27714D07);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xF2A9E6B8);
    cpu.set_edi(0xF53B0D71);
    cpu.set_ebp(0x78E1645D);
    cpu.set_esp(0x00001A62);
    cpu.set_cs(0x00004A9A);
    cpu.set_ds(0x000000B9);
    cpu.set_es(0x0000DD16);
    cpu.set_fs(0x0000EC02);
    cpu.set_gs(0x0000FFFA);
    cpu.set_ss(0x00007C2A);
    cpu.set_eip(0x00005C80);
    cpu.set_eflags(0xFFFC0446);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x50620, 0x93);
    machine.mem_store_byte(0x50621, 0xF4);
    machine.mem_store_byte(0x50622, 0xB1);
    machine.mem_store_byte(0x50623, 0x27);
    machine.mem_store_byte(0x50624, 0x8A);
    machine.mem_store_byte(0x50625, 0x11);
    machine.mem_store_byte(0x50626, 0x19);
    machine.mem_store_byte(0x50627, 0xBA);
    machine.mem_store_byte(0x50628, 0xCD);
    machine.mem_store_byte(0x50629, 0x06);
    machine.mem_store_byte(0x5062A, 0x45);
    machine.mem_store_byte(0x5062B, 0x96);
    machine.mem_store_byte(0x5062C, 0x9B);
    machine.mem_store_byte(0x5062D, 0xAD);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0C3FCFDD);
    EXPECT_EQ(cpu.get_ebx(), 0x19C3D377);
    EXPECT_EQ(cpu.get_ecx(), 0x27714D07);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xF2A9E6B8);
    EXPECT_EQ(cpu.get_edi(), 0xF53B0D71);
    EXPECT_EQ(cpu.get_ebp(), 0x78E1645D);
    EXPECT_EQ(cpu.get_esp(), 0x00001A62);
    EXPECT_EQ(cpu.get_cs(), 0x00004A9A);
    EXPECT_EQ(cpu.get_ds(), 0x000000B9);
    EXPECT_EQ(cpu.get_es(), 0x0000DD16);
    EXPECT_EQ(cpu.get_fs(), 0x0000EC02);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFA);
    EXPECT_EQ(cpu.get_ss(), 0x00007C2A);
    EXPECT_EQ(cpu.get_eip(), 0x00005C82);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
}

//
// xchg ebx,eax
//
TEST_F(Test386, xchg_ebx_eax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0C3FD377);
    cpu.set_ebx(0x19C3CFDD);
    cpu.set_ecx(0x27714D07);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xF2A9E6B8);
    cpu.set_edi(0xF53B0D71);
    cpu.set_ebp(0x78E1645D);
    cpu.set_esp(0x00001A62);
    cpu.set_cs(0x00004A9A);
    cpu.set_ds(0x000000B9);
    cpu.set_es(0x0000DD16);
    cpu.set_fs(0x0000EC02);
    cpu.set_gs(0x0000FFFA);
    cpu.set_ss(0x00007C2A);
    cpu.set_eip(0x00005C80);
    cpu.set_eflags(0xFFFC0446);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x50620, 0x66);
    machine.mem_store_byte(0x50621, 0x93);
    machine.mem_store_byte(0x50622, 0xF4);
    machine.mem_store_byte(0x50623, 0x27);
    machine.mem_store_byte(0x50624, 0x8A);
    machine.mem_store_byte(0x50625, 0x11);
    machine.mem_store_byte(0x50626, 0x19);
    machine.mem_store_byte(0x50627, 0xBA);
    machine.mem_store_byte(0x50628, 0xCD);
    machine.mem_store_byte(0x50629, 0x06);
    machine.mem_store_byte(0x5062A, 0x45);
    machine.mem_store_byte(0x5062B, 0x96);
    machine.mem_store_byte(0x5062C, 0x9B);
    machine.mem_store_byte(0x5062D, 0xAD);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x19C3CFDD);
    EXPECT_EQ(cpu.get_ebx(), 0x0C3FD377);
    EXPECT_EQ(cpu.get_ecx(), 0x27714D07);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xF2A9E6B8);
    EXPECT_EQ(cpu.get_edi(), 0xF53B0D71);
    EXPECT_EQ(cpu.get_ebp(), 0x78E1645D);
    EXPECT_EQ(cpu.get_esp(), 0x00001A62);
    EXPECT_EQ(cpu.get_cs(), 0x00004A9A);
    EXPECT_EQ(cpu.get_ds(), 0x000000B9);
    EXPECT_EQ(cpu.get_es(), 0x0000DD16);
    EXPECT_EQ(cpu.get_fs(), 0x0000EC02);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFA);
    EXPECT_EQ(cpu.get_ss(), 0x00007C2A);
    EXPECT_EQ(cpu.get_eip(), 0x00005C83);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
}

//
// xchg di,[ds:D3C6h]
//
TEST_F(Test386, xchg_di_ds_D3C6h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0D59B57B);
    cpu.set_ebx(0xFF800000);
    cpu.set_ecx(0x0B2FD496);
    cpu.set_edx(0x00000200);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xFB73C907);
    cpu.set_ebp(0x00000018);
    cpu.set_esp(0x0000ADC8);
    cpu.set_cs(0x0000929D);
    cpu.set_ds(0x00002377);
    cpu.set_es(0x0000001C);
    cpu.set_fs(0x000037AB);
    cpu.set_gs(0x00000401);
    cpu.set_ss(0x0000AB8B);
    cpu.set_eip(0x000048F0);
    cpu.set_eflags(0xFFFC0416);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x972C0, 0x67);
    machine.mem_store_byte(0x972C1, 0x87);
    machine.mem_store_byte(0x972C2, 0x3D);
    machine.mem_store_byte(0x972C3, 0xC6);
    machine.mem_store_byte(0x972C4, 0xD3);
    machine.mem_store_byte(0x972C5, 0x00);
    machine.mem_store_byte(0x972C6, 0x00);
    machine.mem_store_byte(0x972C7, 0xF4);
    machine.mem_store_byte(0x972C8, 0xC8);
    machine.mem_store_byte(0x972C9, 0x91);
    machine.mem_store_byte(0x972CA, 0xB4);
    machine.mem_store_byte(0x972CB, 0xAB);
    machine.mem_store_byte(0x30B36, 0x50);
    machine.mem_store_byte(0x30B37, 0x88);
    machine.mem_store_byte(0x972CC, 0xEC);
    machine.mem_store_byte(0x972CD, 0x45);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0D59B57B);
    EXPECT_EQ(cpu.get_ebx(), 0xFF800000);
    EXPECT_EQ(cpu.get_ecx(), 0x0B2FD496);
    EXPECT_EQ(cpu.get_edx(), 0x00000200);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xFB738850);
    EXPECT_EQ(cpu.get_ebp(), 0x00000018);
    EXPECT_EQ(cpu.get_esp(), 0x0000ADC8);
    EXPECT_EQ(cpu.get_cs(), 0x0000929D);
    EXPECT_EQ(cpu.get_ds(), 0x00002377);
    EXPECT_EQ(cpu.get_es(), 0x0000001C);
    EXPECT_EQ(cpu.get_fs(), 0x000037AB);
    EXPECT_EQ(cpu.get_gs(), 0x00000401);
    EXPECT_EQ(cpu.get_ss(), 0x0000AB8B);
    EXPECT_EQ(cpu.get_eip(), 0x000048F8);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30B36), 0x07);
    EXPECT_EQ(memory.load8(0x30B37), 0xC9);
}

//
// xchg edi,[ds:D3C6h]
//
TEST_F(Test386, xchg_edi_ds_D3C6h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0D59B57B);
    cpu.set_ebx(0xFF800000);
    cpu.set_ecx(0x0B2FD496);
    cpu.set_edx(0x00000200);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xFB73C907);
    cpu.set_ebp(0x00000018);
    cpu.set_esp(0x0000ADC8);
    cpu.set_cs(0x0000929D);
    cpu.set_ds(0x00002377);
    cpu.set_es(0x0000001C);
    cpu.set_fs(0x000037AB);
    cpu.set_gs(0x00000401);
    cpu.set_ss(0x0000AB8B);
    cpu.set_eip(0x000048F0);
    cpu.set_eflags(0xFFFC0416);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x972C0, 0x66);
    machine.mem_store_byte(0x972C1, 0x67);
    machine.mem_store_byte(0x972C2, 0x87);
    machine.mem_store_byte(0x972C3, 0x3D);
    machine.mem_store_byte(0x972C4, 0xC6);
    machine.mem_store_byte(0x972C5, 0xD3);
    machine.mem_store_byte(0x972C6, 0x00);
    machine.mem_store_byte(0x972C7, 0x00);
    machine.mem_store_byte(0x972C8, 0xF4);
    machine.mem_store_byte(0x972C9, 0x91);
    machine.mem_store_byte(0x972CA, 0xB4);
    machine.mem_store_byte(0x972CB, 0xAB);
    machine.mem_store_byte(0x30B38, 0xE1);
    machine.mem_store_byte(0x30B39, 0x01);
    machine.mem_store_byte(0x30B36, 0x50);
    machine.mem_store_byte(0x30B37, 0x88);
    machine.mem_store_byte(0x972CC, 0xEC);
    machine.mem_store_byte(0x972CD, 0x45);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0D59B57B);
    EXPECT_EQ(cpu.get_ebx(), 0xFF800000);
    EXPECT_EQ(cpu.get_ecx(), 0x0B2FD496);
    EXPECT_EQ(cpu.get_edx(), 0x00000200);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0x01E18850);
    EXPECT_EQ(cpu.get_ebp(), 0x00000018);
    EXPECT_EQ(cpu.get_esp(), 0x0000ADC8);
    EXPECT_EQ(cpu.get_cs(), 0x0000929D);
    EXPECT_EQ(cpu.get_ds(), 0x00002377);
    EXPECT_EQ(cpu.get_es(), 0x0000001C);
    EXPECT_EQ(cpu.get_fs(), 0x000037AB);
    EXPECT_EQ(cpu.get_gs(), 0x00000401);
    EXPECT_EQ(cpu.get_ss(), 0x0000AB8B);
    EXPECT_EQ(cpu.get_eip(), 0x000048F9);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30B38), 0x73);
    EXPECT_EQ(memory.load8(0x30B39), 0xFB);
    EXPECT_EQ(memory.load8(0x30B36), 0x07);
    EXPECT_EQ(memory.load8(0x30B37), 0xC9);
}

//
// xlatb
//
TEST_F(Test386, xlatb)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD1BD936D);
    cpu.set_ebx(0x1A419DA1);
    cpu.set_ecx(0x00000000);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xE5FE36DF);
    cpu.set_edi(0xECF952D3);
    cpu.set_ebp(0x75777740);
    cpu.set_esp(0x00008EF6);
    cpu.set_cs(0x00000501);
    cpu.set_ds(0x0000B1AA);
    cpu.set_es(0x0000FFFE);
    cpu.set_fs(0x00003FFF);
    cpu.set_gs(0x00000040);
    cpu.set_ss(0x0000A3DD);
    cpu.set_eip(0x00008018);
    cpu.set_eflags(0xFFFC08C3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0D028, 0xD7);
    machine.mem_store_byte(0x0D029, 0xF4);
    machine.mem_store_byte(0x0D02A, 0x59);
    machine.mem_store_byte(0x0D02B, 0xAF);
    machine.mem_store_byte(0x0D02C, 0x54);
    machine.mem_store_byte(0x0D02D, 0x17);
    machine.mem_store_byte(0x0D02E, 0x49);
    machine.mem_store_byte(0x0D02F, 0xFD);
    machine.mem_store_byte(0x0D030, 0xBD);
    machine.mem_store_byte(0x0D031, 0x36);
    machine.mem_store_byte(0xBB8AE, 0x95);
    machine.mem_store_byte(0x0D032, 0x73);
    machine.mem_store_byte(0x0D033, 0xB9);
    machine.mem_store_byte(0x0D034, 0x4D);
    machine.mem_store_byte(0x0D035, 0x2A);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD1BD9395);
    EXPECT_EQ(cpu.get_ebx(), 0x1A419DA1);
    EXPECT_EQ(cpu.get_ecx(), 0x00000000);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xE5FE36DF);
    EXPECT_EQ(cpu.get_edi(), 0xECF952D3);
    EXPECT_EQ(cpu.get_ebp(), 0x75777740);
    EXPECT_EQ(cpu.get_esp(), 0x00008EF6);
    EXPECT_EQ(cpu.get_cs(), 0x00000501);
    EXPECT_EQ(cpu.get_ds(), 0x0000B1AA);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFE);
    EXPECT_EQ(cpu.get_fs(), 0x00003FFF);
    EXPECT_EQ(cpu.get_gs(), 0x00000040);
    EXPECT_EQ(cpu.get_ss(), 0x0000A3DD);
    EXPECT_EQ(cpu.get_eip(), 0x0000801A);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC08C3);

    // Final RAM entries
}

//
// xor [cs:bp+di],esi
//
TEST_F(Test386, xor_cs_bp_di_esi)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE959A3D2);
    cpu.set_ebx(0x0000000B);
    cpu.set_ecx(0x00000041);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x3C9E96AC);
    cpu.set_edi(0x00997819);
    cpu.set_ebp(0x453F3753);
    cpu.set_esp(0x0000C5DC);
    cpu.set_cs(0x000068E7);
    cpu.set_ds(0x0000FD98);
    cpu.set_es(0x0000FFEF);
    cpu.set_fs(0x00000001);
    cpu.set_gs(0x000058F3);
    cpu.set_ss(0x0000FF2F);
    cpu.set_eip(0x00005840);
    cpu.set_eflags(0xFFFC0817);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6E6B0, 0x2E);
    machine.mem_store_byte(0x6E6B1, 0x66);
    machine.mem_store_byte(0x6E6B2, 0x31);
    machine.mem_store_byte(0x6E6B3, 0x33);
    machine.mem_store_byte(0x6E6B4, 0xF4);
    machine.mem_store_byte(0x6E6B5, 0x62);
    machine.mem_store_byte(0x6E6B6, 0x11);
    machine.mem_store_byte(0x6E6B7, 0x5C);
    machine.mem_store_byte(0x6E6B8, 0x0C);
    machine.mem_store_byte(0x6E6B9, 0x56);
    machine.mem_store_byte(0x6E6BA, 0x5B);
    machine.mem_store_byte(0x6E6BB, 0x97);
    machine.mem_store_byte(0x73DDC, 0xE8);
    machine.mem_store_byte(0x73DDD, 0xAB);
    machine.mem_store_byte(0x73DDE, 0x21);
    machine.mem_store_byte(0x73DDF, 0x02);
    machine.mem_store_byte(0x6E6BC, 0x13);
    machine.mem_store_byte(0x6E6BD, 0x65);
    machine.mem_store_byte(0x6E6BE, 0x19);
    machine.mem_store_byte(0x6E6BF, 0x16);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE959A3D2);
    EXPECT_EQ(cpu.get_ebx(), 0x0000000B);
    EXPECT_EQ(cpu.get_ecx(), 0x00000041);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x3C9E96AC);
    EXPECT_EQ(cpu.get_edi(), 0x00997819);
    EXPECT_EQ(cpu.get_ebp(), 0x453F3753);
    EXPECT_EQ(cpu.get_esp(), 0x0000C5DC);
    EXPECT_EQ(cpu.get_cs(), 0x000068E7);
    EXPECT_EQ(cpu.get_ds(), 0x0000FD98);
    EXPECT_EQ(cpu.get_es(), 0x0000FFEF);
    EXPECT_EQ(cpu.get_fs(), 0x00000001);
    EXPECT_EQ(cpu.get_gs(), 0x000058F3);
    EXPECT_EQ(cpu.get_ss(), 0x0000FF2F);
    EXPECT_EQ(cpu.get_eip(), 0x00005845);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x73DDC), 0x44);
    EXPECT_EQ(memory.load8(0x73DDD), 0x3D);
    EXPECT_EQ(memory.load8(0x73DDE), 0xBF);
    EXPECT_EQ(memory.load8(0x73DDF), 0x3E);
}

//
// xor eax,0
//
TEST_F(Test386, xor_eax_0)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000000);
    cpu.set_ebx(0xA595D4CD);
    cpu.set_ecx(0xFAFBC76F);
    cpu.set_edx(0xA3A8F902);
    cpu.set_esi(0xD67177DA);
    cpu.set_edi(0x0000000F);
    cpu.set_ebp(0x0AB11549);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000FEB6);
    cpu.set_ds(0x00000436);
    cpu.set_es(0x00006E11);
    cpu.set_fs(0x0000A16B);
    cpu.set_gs(0x0000D98B);
    cpu.set_ss(0x0000996D);
    cpu.set_eip(0x0000BD38);
    cpu.set_eflags(0xFFFC0892);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x10A898, 0x66);
    machine.mem_store_byte(0x10A899, 0x35);
    machine.mem_store_byte(0x10A89A, 0x00);
    machine.mem_store_byte(0x10A89B, 0x00);
    machine.mem_store_byte(0x10A89C, 0x00);
    machine.mem_store_byte(0x10A89D, 0x00);
    machine.mem_store_byte(0x10A89E, 0xF4);
    machine.mem_store_byte(0x10A89F, 0x82);
    machine.mem_store_byte(0x10A8A0, 0x1A);
    machine.mem_store_byte(0x10A8A1, 0xAF);
    machine.mem_store_byte(0x10A8A2, 0x3C);
    machine.mem_store_byte(0x10A8A3, 0x1C);
    machine.mem_store_byte(0x10A8A4, 0xC1);
    machine.mem_store_byte(0x10A8A5, 0xA4);
    machine.mem_store_byte(0x10A8A6, 0x85);
    machine.mem_store_byte(0x10A8A7, 0xF1);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000000);
    EXPECT_EQ(cpu.get_ebx(), 0xA595D4CD);
    EXPECT_EQ(cpu.get_ecx(), 0xFAFBC76F);
    EXPECT_EQ(cpu.get_edx(), 0xA3A8F902);
    EXPECT_EQ(cpu.get_esi(), 0xD67177DA);
    EXPECT_EQ(cpu.get_edi(), 0x0000000F);
    EXPECT_EQ(cpu.get_ebp(), 0x0AB11549);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000FEB6);
    EXPECT_EQ(cpu.get_ds(), 0x00000436);
    EXPECT_EQ(cpu.get_es(), 0x00006E11);
    EXPECT_EQ(cpu.get_fs(), 0x0000A16B);
    EXPECT_EQ(cpu.get_gs(), 0x0000D98B);
    EXPECT_EQ(cpu.get_ss(), 0x0000996D);
    EXPECT_EQ(cpu.get_eip(), 0x0000BD3F);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0046);

    // Final RAM entries
}

//
// xchg ch,[es:esi-1Dh]
//
TEST_F(Test386, xchg_ch_es_esi_1Dh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x80808080);
    cpu.set_ebx(0x664E5F27);
    cpu.set_ecx(0xA27669C1);
    cpu.set_edx(0x00000101);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0x7FFFFFFF);
    cpu.set_ebp(0x79A0CEA7);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x00005E36);
    cpu.set_ds(0x000000FE);
    cpu.set_es(0x000094F0);
    cpu.set_fs(0x00002A74);
    cpu.set_gs(0x00007F7F);
    cpu.set_ss(0x0000EDA3);
    cpu.set_eip(0x00003C78);
    cpu.set_eflags(0xFFFC0442);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x61FD8, 0x26);
    machine.mem_store_byte(0x61FD9, 0x26);
    machine.mem_store_byte(0x61FDA, 0x67);
    machine.mem_store_byte(0x61FDB, 0x86);
    machine.mem_store_byte(0x61FDC, 0x6E);
    machine.mem_store_byte(0x61FDD, 0xE3);
    machine.mem_store_byte(0x61FDE, 0xF4);
    machine.mem_store_byte(0x61FDF, 0xB6);
    machine.mem_store_byte(0x61FE0, 0x34);
    machine.mem_store_byte(0x61FE1, 0xD4);
    machine.mem_store_byte(0x61FE2, 0x91);
    machine.mem_store_byte(0x61FE3, 0xE8);
    machine.mem_store_byte(0x61FE4, 0x28);
    machine.mem_store_byte(0x61FE5, 0x78);
    machine.mem_store_byte(0x00034, 0xAA);
    machine.mem_store_byte(0x00035, 0x20);
    machine.mem_store_byte(0x00036, 0xE1);
    machine.mem_store_byte(0x00037, 0xC3);
    machine.mem_store_byte(0xC5EBA, 0xF4);
    machine.mem_store_byte(0xC5EBB, 0x5B);
    machine.mem_store_byte(0xC5EBC, 0xF4);
    machine.mem_store_byte(0xC5EBD, 0x6E);
    machine.mem_store_byte(0xC5EBE, 0xF4);
    machine.mem_store_byte(0xC5EBF, 0xAC);
    machine.mem_store_byte(0xC5EC0, 0xF4);
    machine.mem_store_byte(0xC5EC1, 0x81);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x80808080);
    EXPECT_EQ(cpu.get_ebx(), 0x664E5F27);
    EXPECT_EQ(cpu.get_ecx(), 0xA27669C1);
    EXPECT_EQ(cpu.get_edx(), 0x00000101);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ebp(), 0x79A0CEA7);
    EXPECT_EQ(cpu.get_esp(), 0x0000FFF8);
    EXPECT_EQ(cpu.get_cs(), 0x0000C3E1);
    EXPECT_EQ(cpu.get_ds(), 0x000000FE);
    EXPECT_EQ(cpu.get_es(), 0x000094F0);
    EXPECT_EQ(cpu.get_fs(), 0x00002A74);
    EXPECT_EQ(cpu.get_gs(), 0x00007F7F);
    EXPECT_EQ(cpu.get_ss(), 0x0000EDA3);
    EXPECT_EQ(cpu.get_eip(), 0x000020AB);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0442);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFDA2C), 0x42);
    EXPECT_EQ(memory.load8(0xFDA2D), 0x04);
    EXPECT_EQ(memory.load8(0xFDA2A), 0x36);
    EXPECT_EQ(memory.load8(0xFDA2B), 0x5E);
    EXPECT_EQ(memory.load8(0xFDA28), 0x78);
    EXPECT_EQ(memory.load8(0xFDA29), 0x3C);
}
