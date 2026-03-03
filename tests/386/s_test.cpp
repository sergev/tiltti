#include "test386.h"

//
// sal bl,B0h
//
TEST_F(Test386, sal_bl_B0h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA3D930DB);
    cpu.set_ebx(0xBECB81E3);
    cpu.set_ecx(0xABF4C072);
    cpu.set_edx(0xBF6773DC);
    cpu.set_esi(0xE4FB5473);
    cpu.set_edi(0xCB9E3607);
    cpu.set_ebp(0xC4F43722);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x000091E7);
    cpu.set_es(0x00007773);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x000079D6);
    cpu.set_ss(0x0000C4F3);
    cpu.set_eip(0x00009140);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x09140, 0xC0);
    machine.mem_store_byte(0x09141, 0xF3);
    machine.mem_store_byte(0x09142, 0xB0);
    machine.mem_store_byte(0x09143, 0xF4);
    machine.mem_store_byte(0x09144, 0x57);
    machine.mem_store_byte(0x09145, 0x26);
    machine.mem_store_byte(0x09146, 0x67);
    machine.mem_store_byte(0x09147, 0x6E);
    machine.mem_store_byte(0x09148, 0xB6);
    machine.mem_store_byte(0x09149, 0x77);
    machine.mem_store_byte(0x0914A, 0xBB);
    machine.mem_store_byte(0x0914B, 0x9B);
    machine.mem_store_byte(0x0914C, 0xD5);
    machine.mem_store_byte(0x0914D, 0x89);
    machine.mem_store_byte(0x0914E, 0xEF);
    machine.mem_store_byte(0x0914F, 0x02);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA3D930DB);
    EXPECT_EQ(cpu.get_ebx(), 0xBECB8100);
    EXPECT_EQ(cpu.get_ecx(), 0xABF4C072);
    EXPECT_EQ(cpu.get_edx(), 0xBF6773DC);
    EXPECT_EQ(cpu.get_esi(), 0xE4FB5473);
    EXPECT_EQ(cpu.get_edi(), 0xCB9E3607);
    EXPECT_EQ(cpu.get_ebp(), 0xC4F43722);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x000091E7);
    EXPECT_EQ(cpu.get_es(), 0x00007773);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x000079D6);
    EXPECT_EQ(cpu.get_ss(), 0x0000C4F3);
    EXPECT_EQ(cpu.get_eip(), 0x00009144);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C57);

    // Final RAM entries
}

//
// sal byte [ds:bx+di],cl
//
TEST_F(Test386, sal_byte_ds_bx_di_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x626E18E0);
    cpu.set_ebx(0x3D5AE300);
    cpu.set_ecx(0x5BC57131);
    cpu.set_edx(0xF8D644ED);
    cpu.set_esi(0x4D031716);
    cpu.set_edi(0x46F84088);
    cpu.set_ebp(0xF7864D9A);
    cpu.set_esp(0x0000FAA2);
    cpu.set_cs(0x0000AC70);
    cpu.set_ds(0x00000E1C);
    cpu.set_es(0x00004B83);
    cpu.set_fs(0x000066A1);
    cpu.set_gs(0x0000CCB0);
    cpu.set_ss(0x000026EB);
    cpu.set_eip(0x00005630);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB1D30, 0xD2);
    machine.mem_store_byte(0xB1D31, 0x31);
    machine.mem_store_byte(0xB1D32, 0xF4);
    machine.mem_store_byte(0xB1D33, 0x1B);
    machine.mem_store_byte(0xB1D34, 0x6D);
    machine.mem_store_byte(0xB1D35, 0xF3);
    machine.mem_store_byte(0xB1D36, 0xE0);
    machine.mem_store_byte(0xB1D37, 0x77);
    machine.mem_store_byte(0xB1D38, 0x25);
    machine.mem_store_byte(0xB1D39, 0xF2);
    machine.mem_store_byte(0x10548, 0x80);
    machine.mem_store_byte(0xB1D3A, 0x87);
    machine.mem_store_byte(0xB1D3B, 0xF0);
    machine.mem_store_byte(0xB1D3C, 0x4F);
    machine.mem_store_byte(0xB1D3D, 0x79);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x626E18E0);
    EXPECT_EQ(cpu.get_ebx(), 0x3D5AE300);
    EXPECT_EQ(cpu.get_ecx(), 0x5BC57131);
    EXPECT_EQ(cpu.get_edx(), 0xF8D644ED);
    EXPECT_EQ(cpu.get_esi(), 0x4D031716);
    EXPECT_EQ(cpu.get_edi(), 0x46F84088);
    EXPECT_EQ(cpu.get_ebp(), 0xF7864D9A);
    EXPECT_EQ(cpu.get_esp(), 0x0000FAA2);
    EXPECT_EQ(cpu.get_cs(), 0x0000AC70);
    EXPECT_EQ(cpu.get_ds(), 0x00000E1C);
    EXPECT_EQ(cpu.get_es(), 0x00004B83);
    EXPECT_EQ(cpu.get_fs(), 0x000066A1);
    EXPECT_EQ(cpu.get_gs(), 0x0000CCB0);
    EXPECT_EQ(cpu.get_ss(), 0x000026EB);
    EXPECT_EQ(cpu.get_eip(), 0x00005633);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0456);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x10548), 0x00);
}

//
// sal di,cl
//
TEST_F(Test386, sal_di_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x92175544);
    cpu.set_ebx(0x7FFFFFFF);
    cpu.set_ecx(0xA6D8809D);
    cpu.set_edx(0x7E9BA2E4);
    cpu.set_esi(0x79B725F6);
    cpu.set_edi(0x5FA6F2B1);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00008ED3);
    cpu.set_ds(0x0000469A);
    cpu.set_es(0x0000130C);
    cpu.set_fs(0x0000FE54);
    cpu.set_gs(0x0000D558);
    cpu.set_ss(0x00001064);
    cpu.set_eip(0x00009E90);
    cpu.set_eflags(0xFFFC04C2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x98BC0, 0x67);
    machine.mem_store_byte(0x98BC1, 0xD3);
    machine.mem_store_byte(0x98BC2, 0xF7);
    machine.mem_store_byte(0x98BC3, 0xF4);
    machine.mem_store_byte(0x98BC4, 0x35);
    machine.mem_store_byte(0x98BC5, 0x0C);
    machine.mem_store_byte(0x98BC6, 0xC7);
    machine.mem_store_byte(0x98BC7, 0x94);
    machine.mem_store_byte(0x98BC8, 0xBB);
    machine.mem_store_byte(0x98BC9, 0xC2);
    machine.mem_store_byte(0x98BCA, 0x08);
    machine.mem_store_byte(0x98BCB, 0x2B);
    machine.mem_store_byte(0x98BCC, 0xF4);
    machine.mem_store_byte(0x98BCD, 0x2B);
    machine.mem_store_byte(0x98BCE, 0x01);
    machine.mem_store_byte(0x98BCF, 0xF2);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x92175544);
    EXPECT_EQ(cpu.get_ebx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0xA6D8809D);
    EXPECT_EQ(cpu.get_edx(), 0x7E9BA2E4);
    EXPECT_EQ(cpu.get_esi(), 0x79B725F6);
    EXPECT_EQ(cpu.get_edi(), 0x5FA60000);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00008ED3);
    EXPECT_EQ(cpu.get_ds(), 0x0000469A);
    EXPECT_EQ(cpu.get_es(), 0x0000130C);
    EXPECT_EQ(cpu.get_fs(), 0x0000FE54);
    EXPECT_EQ(cpu.get_gs(), 0x0000D558);
    EXPECT_EQ(cpu.get_ss(), 0x00001064);
    EXPECT_EQ(cpu.get_eip(), 0x00009E94);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0456);

    // Final RAM entries
}

//
// sar bl,B0h
//
TEST_F(Test386, sar_bl_B0h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA3D930DB);
    cpu.set_ebx(0xBECB81E3);
    cpu.set_ecx(0xABF4C072);
    cpu.set_edx(0xBF6773DC);
    cpu.set_esi(0xE4FB5473);
    cpu.set_edi(0xCB9E3607);
    cpu.set_ebp(0xC4F43722);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x000091E7);
    cpu.set_es(0x00007773);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x000079D6);
    cpu.set_ss(0x0000C4F3);
    cpu.set_eip(0x00009140);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x09140, 0x67);
    machine.mem_store_byte(0x09141, 0xC0);
    machine.mem_store_byte(0x09142, 0xFB);
    machine.mem_store_byte(0x09143, 0xB0);
    machine.mem_store_byte(0x09144, 0xF4);
    machine.mem_store_byte(0x09145, 0x57);
    machine.mem_store_byte(0x09146, 0x0D);
    machine.mem_store_byte(0x09147, 0x44);
    machine.mem_store_byte(0x09148, 0xF0);
    machine.mem_store_byte(0x09149, 0xAA);
    machine.mem_store_byte(0x0914A, 0x16);
    machine.mem_store_byte(0x0914B, 0x76);
    machine.mem_store_byte(0x0914C, 0xF8);
    machine.mem_store_byte(0x0914D, 0xCD);
    machine.mem_store_byte(0x0914E, 0x5B);
    machine.mem_store_byte(0x0914F, 0x02);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA3D930DB);
    EXPECT_EQ(cpu.get_ebx(), 0xBECB81FF);
    EXPECT_EQ(cpu.get_ecx(), 0xABF4C072);
    EXPECT_EQ(cpu.get_edx(), 0xBF6773DC);
    EXPECT_EQ(cpu.get_esi(), 0xE4FB5473);
    EXPECT_EQ(cpu.get_edi(), 0xCB9E3607);
    EXPECT_EQ(cpu.get_ebp(), 0xC4F43722);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x000091E7);
    EXPECT_EQ(cpu.get_es(), 0x00007773);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x000079D6);
    EXPECT_EQ(cpu.get_ss(), 0x0000C4F3);
    EXPECT_EQ(cpu.get_eip(), 0x00009145);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0497);

    // Final RAM entries
}

//
// sar byte [ds:bx],EDh
//
TEST_F(Test386, sar_byte_ds_bx_EDh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xE34E2563);
    cpu.set_ebx(0xA0313944);
    cpu.set_ecx(0xDB271BDE);
    cpu.set_edx(0x00F83E11);
    cpu.set_esi(0xA0E287F5);
    cpu.set_edi(0x2D505FEE);
    cpu.set_ebp(0x1B1DBA4F);
    cpu.set_esp(0x000018F6);
    cpu.set_cs(0x000000BD);
    cpu.set_ds(0x00002C61);
    cpu.set_es(0x00000AF3);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x00001205);
    cpu.set_ss(0x000014DC);
    cpu.set_eip(0x00001D70);
    cpu.set_eflags(0xFFFC0897);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02940, 0xC0);
    machine.mem_store_byte(0x02941, 0x3F);
    machine.mem_store_byte(0x02942, 0xED);
    machine.mem_store_byte(0x02943, 0xF4);
    machine.mem_store_byte(0x02944, 0x0E);
    machine.mem_store_byte(0x02945, 0x34);
    machine.mem_store_byte(0x02946, 0x27);
    machine.mem_store_byte(0x02947, 0xFC);
    machine.mem_store_byte(0x02948, 0xB2);
    machine.mem_store_byte(0x02949, 0xD8);
    machine.mem_store_byte(0x2FF54, 0x11);
    machine.mem_store_byte(0x0294A, 0xA5);
    machine.mem_store_byte(0x0294B, 0x77);
    machine.mem_store_byte(0x0294C, 0xC8);
    machine.mem_store_byte(0x0294D, 0x4E);
    machine.mem_store_byte(0x0294E, 0xDB);
    machine.mem_store_byte(0x0294F, 0xA7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xE34E2563);
    EXPECT_EQ(cpu.get_ebx(), 0xA0313944);
    EXPECT_EQ(cpu.get_ecx(), 0xDB271BDE);
    EXPECT_EQ(cpu.get_edx(), 0x00F83E11);
    EXPECT_EQ(cpu.get_esi(), 0xA0E287F5);
    EXPECT_EQ(cpu.get_edi(), 0x2D505FEE);
    EXPECT_EQ(cpu.get_ebp(), 0x1B1DBA4F);
    EXPECT_EQ(cpu.get_esp(), 0x000018F6);
    EXPECT_EQ(cpu.get_cs(), 0x000000BD);
    EXPECT_EQ(cpu.get_ds(), 0x00002C61);
    EXPECT_EQ(cpu.get_es(), 0x00000AF3);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x00001205);
    EXPECT_EQ(cpu.get_ss(), 0x000014DC);
    EXPECT_EQ(cpu.get_eip(), 0x00001D74);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2FF54), 0x00);
}

//
// sbb [ds:bx+si],ecx
//
TEST_F(Test386, sbb_ds_bx_si_ecx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x998A4B29);
    cpu.set_ebx(0x00001FFF);
    cpu.set_ecx(0xD30D16CF);
    cpu.set_edx(0xFE544D34);
    cpu.set_esi(0xFF5D39CE);
    cpu.set_edi(0xF0FF7EF4);
    cpu.set_ebp(0xE56159F0);
    cpu.set_esp(0x00007EA6);
    cpu.set_cs(0x00007FFF);
    cpu.set_ds(0x0000D0F6);
    cpu.set_es(0x000044DB);
    cpu.set_fs(0x000069C9);
    cpu.set_gs(0x00000B20);
    cpu.set_ss(0x0000FF1F);
    cpu.set_eip(0x000099F0);
    cpu.set_eflags(0xFFFC0483);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x899E0, 0x66);
    machine.mem_store_byte(0x899E1, 0x19);
    machine.mem_store_byte(0x899E2, 0x08);
    machine.mem_store_byte(0x899E3, 0xF4);
    machine.mem_store_byte(0x899E4, 0xA9);
    machine.mem_store_byte(0x899E5, 0x6A);
    machine.mem_store_byte(0x899E6, 0xD5);
    machine.mem_store_byte(0x899E7, 0x8B);
    machine.mem_store_byte(0x899E8, 0xAA);
    machine.mem_store_byte(0x899E9, 0x28);
    machine.mem_store_byte(0xD6930, 0xB7);
    machine.mem_store_byte(0xD692D, 0x67);
    machine.mem_store_byte(0xD692E, 0x22);
    machine.mem_store_byte(0xD692F, 0x3E);
    machine.mem_store_byte(0x899EA, 0xEA);
    machine.mem_store_byte(0x899EB, 0xCD);
    machine.mem_store_byte(0x899EC, 0xD8);
    machine.mem_store_byte(0x899ED, 0xFC);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x998A4B29);
    EXPECT_EQ(cpu.get_ebx(), 0x00001FFF);
    EXPECT_EQ(cpu.get_ecx(), 0xD30D16CF);
    EXPECT_EQ(cpu.get_edx(), 0xFE544D34);
    EXPECT_EQ(cpu.get_esi(), 0xFF5D39CE);
    EXPECT_EQ(cpu.get_edi(), 0xF0FF7EF4);
    EXPECT_EQ(cpu.get_ebp(), 0xE56159F0);
    EXPECT_EQ(cpu.get_esp(), 0x00007EA6);
    EXPECT_EQ(cpu.get_cs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000D0F6);
    EXPECT_EQ(cpu.get_es(), 0x000044DB);
    EXPECT_EQ(cpu.get_fs(), 0x000069C9);
    EXPECT_EQ(cpu.get_gs(), 0x00000B20);
    EXPECT_EQ(cpu.get_ss(), 0x0000FF1F);
    EXPECT_EQ(cpu.get_eip(), 0x000099F4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD6930), 0xE4);
    EXPECT_EQ(memory.load8(0xD692D), 0x97);
    EXPECT_EQ(memory.load8(0xD692E), 0x0B);
    EXPECT_EQ(memory.load8(0xD692F), 0x31);
}

//
// sbb [ds:eax+eax*8],ecx
//
TEST_F(Test386, sbb_ds_eax_eax_8_ecx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000B29);
    cpu.set_ebx(0x00001FFF);
    cpu.set_ecx(0xD30D16CF);
    cpu.set_edx(0xFE544D34);
    cpu.set_esi(0xFF5D39CE);
    cpu.set_edi(0xF0FF7EF4);
    cpu.set_ebp(0xE56159F0);
    cpu.set_esp(0x00007EA6);
    cpu.set_cs(0x00007FFF);
    cpu.set_ds(0x0000D0F6);
    cpu.set_es(0x000044DB);
    cpu.set_fs(0x000069C9);
    cpu.set_gs(0x00000B20);
    cpu.set_ss(0x0000FF1F);
    cpu.set_eip(0x000099F0);
    cpu.set_eflags(0xFFFC0483);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x899E0, 0x67);
    machine.mem_store_byte(0x899E1, 0x66);
    machine.mem_store_byte(0x899E2, 0x19);
    machine.mem_store_byte(0x899E3, 0x0C);
    machine.mem_store_byte(0x899E4, 0xC0);
    machine.mem_store_byte(0x899E5, 0xF4);
    machine.mem_store_byte(0x899E6, 0xD5);
    machine.mem_store_byte(0x899E7, 0x8B);
    machine.mem_store_byte(0x899E8, 0xAA);
    machine.mem_store_byte(0x899E9, 0x28);
    machine.mem_store_byte(0x899EA, 0xEA);
    machine.mem_store_byte(0x899EB, 0xCD);
    machine.mem_store_byte(0xD73D4, 0x3E);
    machine.mem_store_byte(0xD73D1, 0xB3);
    machine.mem_store_byte(0xD73D2, 0x5E);
    machine.mem_store_byte(0xD73D3, 0xC7);
    machine.mem_store_byte(0x899EC, 0xD8);
    machine.mem_store_byte(0x899ED, 0xFC);
    machine.mem_store_byte(0x899EE, 0x54);
    machine.mem_store_byte(0x899EF, 0x43);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000B29);
    EXPECT_EQ(cpu.get_ebx(), 0x00001FFF);
    EXPECT_EQ(cpu.get_ecx(), 0xD30D16CF);
    EXPECT_EQ(cpu.get_edx(), 0xFE544D34);
    EXPECT_EQ(cpu.get_esi(), 0xFF5D39CE);
    EXPECT_EQ(cpu.get_edi(), 0xF0FF7EF4);
    EXPECT_EQ(cpu.get_ebp(), 0xE56159F0);
    EXPECT_EQ(cpu.get_esp(), 0x00007EA6);
    EXPECT_EQ(cpu.get_cs(), 0x00007FFF);
    EXPECT_EQ(cpu.get_ds(), 0x0000D0F6);
    EXPECT_EQ(cpu.get_es(), 0x000044DB);
    EXPECT_EQ(cpu.get_fs(), 0x000069C9);
    EXPECT_EQ(cpu.get_gs(), 0x00000B20);
    EXPECT_EQ(cpu.get_ss(), 0x0000FF1F);
    EXPECT_EQ(cpu.get_eip(), 0x000099F6);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD73D4), 0x6B);
    EXPECT_EQ(memory.load8(0xD73D1), 0xE3);
    EXPECT_EQ(memory.load8(0xD73D2), 0x47);
    EXPECT_EQ(memory.load8(0xD73D3), 0xBA);
}

//
// seta [ds:ecx+23h]
//
TEST_F(Test386, seta_ds_ecx_23h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x94AAEDE4);
    cpu.set_ebx(0x64256C0C);
    cpu.set_ecx(0x00005B28);
    cpu.set_edx(0x00001000);
    cpu.set_esi(0xF0D811BB);
    cpu.set_edi(0x0ACF6EB3);
    cpu.set_ebp(0xD81920F8);
    cpu.set_esp(0x000056D0);
    cpu.set_cs(0x00006340);
    cpu.set_ds(0x0000EA77);
    cpu.set_es(0x00007A1C);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x0000EE14);
    cpu.set_ss(0x00007CFD);
    cpu.set_eip(0x000043E0);
    cpu.set_eflags(0xFFFC0012);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x677E0, 0x67);
    machine.mem_store_byte(0x677E1, 0x0F);
    machine.mem_store_byte(0x677E2, 0x97);
    machine.mem_store_byte(0x677E3, 0x61);
    machine.mem_store_byte(0x677E4, 0x23);
    machine.mem_store_byte(0x677E5, 0xF4);
    machine.mem_store_byte(0x677E6, 0xC9);
    machine.mem_store_byte(0x677E7, 0xA9);
    machine.mem_store_byte(0x677E8, 0x9D);
    machine.mem_store_byte(0x677E9, 0xD9);
    machine.mem_store_byte(0x677EA, 0x57);
    machine.mem_store_byte(0x677EB, 0x43);
    machine.mem_store_byte(0x677EC, 0x9E);
    machine.mem_store_byte(0x677ED, 0x20);
    machine.mem_store_byte(0x677EE, 0x9A);
    machine.mem_store_byte(0x677EF, 0xCC);
    machine.mem_store_byte(0x677F0, 0x78);
    machine.mem_store_byte(0x677F1, 0xED);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x94AAEDE4);
    EXPECT_EQ(cpu.get_ebx(), 0x64256C0C);
    EXPECT_EQ(cpu.get_ecx(), 0x00005B28);
    EXPECT_EQ(cpu.get_edx(), 0x00001000);
    EXPECT_EQ(cpu.get_esi(), 0xF0D811BB);
    EXPECT_EQ(cpu.get_edi(), 0x0ACF6EB3);
    EXPECT_EQ(cpu.get_ebp(), 0xD81920F8);
    EXPECT_EQ(cpu.get_esp(), 0x000056D0);
    EXPECT_EQ(cpu.get_cs(), 0x00006340);
    EXPECT_EQ(cpu.get_ds(), 0x0000EA77);
    EXPECT_EQ(cpu.get_es(), 0x00007A1C);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x0000EE14);
    EXPECT_EQ(cpu.get_ss(), 0x00007CFD);
    EXPECT_EQ(cpu.get_eip(), 0x000043E6);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF02BB), 0x01);
}

//
// shld cx,bp,cl
//
TEST_F(Test386, shld_cx_bp_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xA12DDDAD);
    cpu.set_ebx(0xD68AB768);
    cpu.set_ecx(0x9539BB7A);
    cpu.set_edx(0x95E57AED);
    cpu.set_esi(0x34221AA4);
    cpu.set_edi(0x93E5971D);
    cpu.set_ebp(0x00004000);
    cpu.set_esp(0x000074CA);
    cpu.set_cs(0x00004440);
    cpu.set_ds(0x00002653);
    cpu.set_es(0x000045F3);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x0000FFFF);
    cpu.set_ss(0x0000FFE7);
    cpu.set_eip(0x000094D8);
    cpu.set_eflags(0xFFFC0CC2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4D8D8, 0x67);
    machine.mem_store_byte(0x4D8D9, 0x0F);
    machine.mem_store_byte(0x4D8DA, 0xA5);
    machine.mem_store_byte(0x4D8DB, 0xE9);
    machine.mem_store_byte(0x4D8DC, 0xF4);
    machine.mem_store_byte(0x4D8DD, 0x00);
    machine.mem_store_byte(0x4D8DE, 0x00);
    machine.mem_store_byte(0x4D8DF, 0x00);
    machine.mem_store_byte(0x4D8E0, 0x00);
    machine.mem_store_byte(0x4D8E1, 0x00);
    machine.mem_store_byte(0x4D8E2, 0x00);
    machine.mem_store_byte(0x4D8E3, 0x00);
    machine.mem_store_byte(0x4D8E4, 0x00);
    machine.mem_store_byte(0x4D8E5, 0x00);
    machine.mem_store_byte(0x4D8E6, 0x00);
    machine.mem_store_byte(0x4D8E7, 0x00);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xA12DDDAD);
    EXPECT_EQ(cpu.get_ebx(), 0xD68AB768);
    EXPECT_EQ(cpu.get_ecx(), 0x95390100);
    EXPECT_EQ(cpu.get_edx(), 0x95E57AED);
    EXPECT_EQ(cpu.get_esi(), 0x34221AA4);
    EXPECT_EQ(cpu.get_edi(), 0x93E5971D);
    EXPECT_EQ(cpu.get_ebp(), 0x00004000);
    EXPECT_EQ(cpu.get_esp(), 0x000074CA);
    EXPECT_EQ(cpu.get_cs(), 0x00004440);
    EXPECT_EQ(cpu.get_ds(), 0x00002653);
    EXPECT_EQ(cpu.get_es(), 0x000045F3);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ss(), 0x0000FFE7);
    EXPECT_EQ(cpu.get_eip(), 0x000094DD);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0416);

    // Final RAM entries
}

//
// shr byte [ds:bx+si-67h],1
//
TEST_F(Test386, shr_byte_ds_bx_si_67h_1)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFF89F127);
    cpu.set_ebx(0x093C1A9C);
    cpu.set_ecx(0x00000000);
    cpu.set_edx(0x94D82877);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xEE9950B5);
    cpu.set_ebp(0xD330C88E);
    cpu.set_esp(0x00007FAE);
    cpu.set_cs(0x000099DA);
    cpu.set_ds(0x0000C1D0);
    cpu.set_es(0x0000BE1B);
    cpu.set_fs(0x000061F4);
    cpu.set_gs(0x0000D8A8);
    cpu.set_ss(0x000024C6);
    cpu.set_eip(0x0000DD90);
    cpu.set_eflags(0xFFFC0C43);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA7B30, 0xD0);
    machine.mem_store_byte(0xA7B31, 0x68);
    machine.mem_store_byte(0xA7B32, 0x99);
    machine.mem_store_byte(0xA7B33, 0xF4);
    machine.mem_store_byte(0xA7B34, 0x17);
    machine.mem_store_byte(0xA7B35, 0x38);
    machine.mem_store_byte(0xA7B36, 0x59);
    machine.mem_store_byte(0xA7B37, 0x41);
    machine.mem_store_byte(0xA7B38, 0xEE);
    machine.mem_store_byte(0xA7B39, 0x5F);
    machine.mem_store_byte(0xC3735, 0x6B);
    machine.mem_store_byte(0xA7B3A, 0xD0);
    machine.mem_store_byte(0xA7B3B, 0x7F);
    machine.mem_store_byte(0xA7B3C, 0x67);
    machine.mem_store_byte(0xA7B3D, 0x7E);
    machine.mem_store_byte(0xA7B3E, 0x43);
    machine.mem_store_byte(0xA7B3F, 0x3E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFF89F127);
    EXPECT_EQ(cpu.get_ebx(), 0x093C1A9C);
    EXPECT_EQ(cpu.get_ecx(), 0x00000000);
    EXPECT_EQ(cpu.get_edx(), 0x94D82877);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xEE9950B5);
    EXPECT_EQ(cpu.get_ebp(), 0xD330C88E);
    EXPECT_EQ(cpu.get_esp(), 0x00007FAE);
    EXPECT_EQ(cpu.get_cs(), 0x000099DA);
    EXPECT_EQ(cpu.get_ds(), 0x0000C1D0);
    EXPECT_EQ(cpu.get_es(), 0x0000BE1B);
    EXPECT_EQ(cpu.get_fs(), 0x000061F4);
    EXPECT_EQ(cpu.get_gs(), 0x0000D8A8);
    EXPECT_EQ(cpu.get_ss(), 0x000024C6);
    EXPECT_EQ(cpu.get_eip(), 0x0000DD94);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC3735), 0x35);
}

//
// sub [ds:bx+si],eax
//
TEST_F(Test386, sub_ds_bx_si_eax)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xC731C4E3);
    cpu.set_ebx(0xF8319378);
    cpu.set_ecx(0x44A1D787);
    cpu.set_edx(0x0000000E);
    cpu.set_esi(0xE28DC4B5);
    cpu.set_edi(0xA96FF63B);
    cpu.set_ebp(0x00000019);
    cpu.set_esp(0x00000A56);
    cpu.set_cs(0x00007F69);
    cpu.set_ds(0x0000F70C);
    cpu.set_es(0x00004426);
    cpu.set_fs(0x00000090);
    cpu.set_gs(0x00000015);
    cpu.set_ss(0x000097A4);
    cpu.set_eip(0x00003EE8);
    cpu.set_eflags(0xFFFC00C3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x83578, 0x66);
    machine.mem_store_byte(0x83579, 0x29);
    machine.mem_store_byte(0x8357A, 0x00);
    machine.mem_store_byte(0x8357B, 0xF4);
    machine.mem_store_byte(0x8357C, 0x3D);
    machine.mem_store_byte(0x8357D, 0x1E);
    machine.mem_store_byte(0x8357E, 0x1F);
    machine.mem_store_byte(0x8357F, 0xB9);
    machine.mem_store_byte(0x83580, 0x46);
    machine.mem_store_byte(0x83581, 0x4C);
    machine.mem_store_byte(0xFC8F0, 0xE4);
    machine.mem_store_byte(0xFC8ED, 0xB8);
    machine.mem_store_byte(0xFC8EE, 0x66);
    machine.mem_store_byte(0xFC8EF, 0x7F);
    machine.mem_store_byte(0x83582, 0x3C);
    machine.mem_store_byte(0x83583, 0x6B);
    machine.mem_store_byte(0x83584, 0x23);
    machine.mem_store_byte(0x83585, 0x88);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xC731C4E3);
    EXPECT_EQ(cpu.get_ebx(), 0xF8319378);
    EXPECT_EQ(cpu.get_ecx(), 0x44A1D787);
    EXPECT_EQ(cpu.get_edx(), 0x0000000E);
    EXPECT_EQ(cpu.get_esi(), 0xE28DC4B5);
    EXPECT_EQ(cpu.get_edi(), 0xA96FF63B);
    EXPECT_EQ(cpu.get_ebp(), 0x00000019);
    EXPECT_EQ(cpu.get_esp(), 0x00000A56);
    EXPECT_EQ(cpu.get_cs(), 0x00007F69);
    EXPECT_EQ(cpu.get_ds(), 0x0000F70C);
    EXPECT_EQ(cpu.get_es(), 0x00004426);
    EXPECT_EQ(cpu.get_fs(), 0x00000090);
    EXPECT_EQ(cpu.get_gs(), 0x00000015);
    EXPECT_EQ(cpu.get_ss(), 0x000097A4);
    EXPECT_EQ(cpu.get_eip(), 0x00003EEC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFC8F0), 0x1D);
    EXPECT_EQ(memory.load8(0xFC8ED), 0xD5);
    EXPECT_EQ(memory.load8(0xFC8EE), 0xA1);
    EXPECT_EQ(memory.load8(0xFC8EF), 0x4D);
}

//
// sbb ax,FDDEh
//
TEST_F(Test386, sbb_ax_FDDEh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x7A3EBC15);
    cpu.set_ebx(0x3CFA5537);
    cpu.set_ecx(0xE23704B0);
    cpu.set_edx(0xCB3400B0);
    cpu.set_esi(0xEA7704DA);
    cpu.set_edi(0x00000015);
    cpu.set_ebp(0x1A3EBF75);
    cpu.set_esp(0x0000C218);
    cpu.set_cs(0x0000FE82);
    cpu.set_ds(0x0000EFFF);
    cpu.set_es(0x000067A5);
    cpu.set_fs(0x00000000);
    cpu.set_gs(0x000018CA);
    cpu.set_ss(0x0000C1C4);
    cpu.set_eip(0x000099C8);
    cpu.set_eflags(0xFFFC00D3);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1081E8, 0x1D);
    machine.mem_store_byte(0x1081E9, 0xDE);
    machine.mem_store_byte(0x1081EA, 0xFD);
    machine.mem_store_byte(0x1081EB, 0xF4);
    machine.mem_store_byte(0x1081EC, 0xEE);
    machine.mem_store_byte(0x1081ED, 0xF7);
    machine.mem_store_byte(0x1081EE, 0xC5);
    machine.mem_store_byte(0x1081EF, 0x64);
    machine.mem_store_byte(0x1081F0, 0x5A);
    machine.mem_store_byte(0x1081F1, 0x8F);
    machine.mem_store_byte(0x1081F2, 0x57);
    machine.mem_store_byte(0x1081F3, 0xBC);
    machine.mem_store_byte(0x1081F4, 0x30);
    machine.mem_store_byte(0x1081F5, 0x57);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x7A3EBE36);
    EXPECT_EQ(cpu.get_ebx(), 0x3CFA5537);
    EXPECT_EQ(cpu.get_ecx(), 0xE23704B0);
    EXPECT_EQ(cpu.get_edx(), 0xCB3400B0);
    EXPECT_EQ(cpu.get_esi(), 0xEA7704DA);
    EXPECT_EQ(cpu.get_edi(), 0x00000015);
    EXPECT_EQ(cpu.get_ebp(), 0x1A3EBF75);
    EXPECT_EQ(cpu.get_esp(), 0x0000C218);
    EXPECT_EQ(cpu.get_cs(), 0x0000FE82);
    EXPECT_EQ(cpu.get_ds(), 0x0000EFFF);
    EXPECT_EQ(cpu.get_es(), 0x000067A5);
    EXPECT_EQ(cpu.get_fs(), 0x00000000);
    EXPECT_EQ(cpu.get_gs(), 0x000018CA);
    EXPECT_EQ(cpu.get_ss(), 0x0000C1C4);
    EXPECT_EQ(cpu.get_eip(), 0x000099CC);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0097);

    // Final RAM entries
}

//
// setb ch
//
TEST_F(Test386, setb_ch)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD3C7E81E);
    cpu.set_ebx(0xEAC5F517);
    cpu.set_ecx(0xEBFF1A81);
    cpu.set_edx(0xB8931C31);
    cpu.set_esi(0x08BB0F22);
    cpu.set_edi(0xE7334461);
    cpu.set_ebp(0x00000800);
    cpu.set_esp(0x0000FEDA);
    cpu.set_cs(0x000050BA);
    cpu.set_ds(0x0000FF78);
    cpu.set_es(0x000077B5);
    cpu.set_fs(0x00005140);
    cpu.set_gs(0x00003234);
    cpu.set_ss(0x0000AACB);
    cpu.set_eip(0x00000740);
    cpu.set_eflags(0xFFFC0C87);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x512E0, 0x67);
    machine.mem_store_byte(0x512E1, 0x0F);
    machine.mem_store_byte(0x512E2, 0x92);
    machine.mem_store_byte(0x512E3, 0xFD);
    machine.mem_store_byte(0x512E4, 0xF4);
    machine.mem_store_byte(0x512E5, 0x61);
    machine.mem_store_byte(0x512E6, 0xC1);
    machine.mem_store_byte(0x512E7, 0xA4);
    machine.mem_store_byte(0x512E8, 0x6F);
    machine.mem_store_byte(0x512E9, 0xD2);
    machine.mem_store_byte(0x512EA, 0x06);
    machine.mem_store_byte(0x512EB, 0xE0);
    machine.mem_store_byte(0x512EC, 0xAD);
    machine.mem_store_byte(0x512ED, 0x51);
    machine.mem_store_byte(0x512EE, 0xCA);
    machine.mem_store_byte(0x512EF, 0xB0);
    machine.mem_store_byte(0x512F0, 0xD8);
    machine.mem_store_byte(0x512F1, 0x8E);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD3C7E81E);
    EXPECT_EQ(cpu.get_ebx(), 0xEAC5F517);
    EXPECT_EQ(cpu.get_ecx(), 0xEBFF0181);
    EXPECT_EQ(cpu.get_edx(), 0xB8931C31);
    EXPECT_EQ(cpu.get_esi(), 0x08BB0F22);
    EXPECT_EQ(cpu.get_edi(), 0xE7334461);
    EXPECT_EQ(cpu.get_ebp(), 0x00000800);
    EXPECT_EQ(cpu.get_esp(), 0x0000FEDA);
    EXPECT_EQ(cpu.get_cs(), 0x000050BA);
    EXPECT_EQ(cpu.get_ds(), 0x0000FF78);
    EXPECT_EQ(cpu.get_es(), 0x000077B5);
    EXPECT_EQ(cpu.get_fs(), 0x00005140);
    EXPECT_EQ(cpu.get_gs(), 0x00003234);
    EXPECT_EQ(cpu.get_ss(), 0x0000AACB);
    EXPECT_EQ(cpu.get_eip(), 0x00000745);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C87);

    // Final RAM entries
}

//
// shld [ds:ecx+41h],ax,98h
//
TEST_F(Test386, shld_ds_ecx_41h_ax_98h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD7E8EFCC);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x0000CF89);
    cpu.set_edx(0x83D05882);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xE625DC14);
    cpu.set_ebp(0x8CA2C04E);
    cpu.set_esp(0x0000C3CC);
    cpu.set_cs(0x0000FDF0);
    cpu.set_ds(0x0000009F);
    cpu.set_es(0x0000B63A);
    cpu.set_fs(0x0000906B);
    cpu.set_gs(0x0000A08F);
    cpu.set_ss(0x00002E66);
    cpu.set_eip(0x000059B8);
    cpu.set_eflags(0xFFFC0457);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1038B8, 0x67);
    machine.mem_store_byte(0x1038B9, 0x0F);
    machine.mem_store_byte(0x1038BA, 0xA4);
    machine.mem_store_byte(0x1038BB, 0x41);
    machine.mem_store_byte(0x1038BC, 0x41);
    machine.mem_store_byte(0x1038BD, 0x98);
    machine.mem_store_byte(0x1038BE, 0xF4);
    machine.mem_store_byte(0x1038BF, 0xD4);
    machine.mem_store_byte(0x1038C0, 0xED);
    machine.mem_store_byte(0x1038C1, 0x7E);
    machine.mem_store_byte(0x1038C2, 0x06);
    machine.mem_store_byte(0x1038C3, 0x39);
    machine.mem_store_byte(0x1038C4, 0x66);
    machine.mem_store_byte(0x1038C5, 0xBF);
    machine.mem_store_byte(0x0D9BA, 0x2C);
    machine.mem_store_byte(0x0D9BB, 0x64);
    machine.mem_store_byte(0x1038C6, 0x13);
    machine.mem_store_byte(0x1038C7, 0x76);
    machine.mem_store_byte(0x1038C8, 0x28);
    machine.mem_store_byte(0x1038C9, 0xC9);
    machine.mem_store_byte(0x1038CA, 0x97);
    machine.mem_store_byte(0x1038CB, 0xB1);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD7E8EFCC);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x0000CF89);
    EXPECT_EQ(cpu.get_edx(), 0x83D05882);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xE625DC14);
    EXPECT_EQ(cpu.get_ebp(), 0x8CA2C04E);
    EXPECT_EQ(cpu.get_esp(), 0x0000C3CC);
    EXPECT_EQ(cpu.get_cs(), 0x0000FDF0);
    EXPECT_EQ(cpu.get_ds(), 0x0000009F);
    EXPECT_EQ(cpu.get_es(), 0x0000B63A);
    EXPECT_EQ(cpu.get_fs(), 0x0000906B);
    EXPECT_EQ(cpu.get_gs(), 0x0000A08F);
    EXPECT_EQ(cpu.get_ss(), 0x00002E66);
    EXPECT_EQ(cpu.get_eip(), 0x000059BF);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0D9BA), 0xEF);
    EXPECT_EQ(memory.load8(0x0D9BB), 0xCC);
}

//
// shrd [ds:ebx-41h],esi,cl
//
TEST_F(Test386, shrd_ds_ebx_41h_esi_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x29501526);
    cpu.set_ebx(0x00002891);
    cpu.set_ecx(0xEF56C9F4);
    cpu.set_edx(0xFFC7B99E);
    cpu.set_esi(0xF4B5A384);
    cpu.set_edi(0x00000101);
    cpu.set_ebp(0x19ACF83A);
    cpu.set_esp(0x0000CD60);
    cpu.set_cs(0x00005DB4);
    cpu.set_ds(0x0000003F);
    cpu.set_es(0x00002586);
    cpu.set_fs(0x00000853);
    cpu.set_gs(0x0000F97B);
    cpu.set_ss(0x0000FDBD);
    cpu.set_eip(0x00002E50);
    cpu.set_eflags(0xFFFC0C16);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x60990, 0x67);
    machine.mem_store_byte(0x60991, 0x66);
    machine.mem_store_byte(0x60992, 0x0F);
    machine.mem_store_byte(0x60993, 0xAD);
    machine.mem_store_byte(0x60994, 0x73);
    machine.mem_store_byte(0x60995, 0xBF);
    machine.mem_store_byte(0x60996, 0xF4);
    machine.mem_store_byte(0x60997, 0x00);
    machine.mem_store_byte(0x60998, 0x00);
    machine.mem_store_byte(0x60999, 0x00);
    machine.mem_store_byte(0x6099A, 0x00);
    machine.mem_store_byte(0x6099B, 0x00);
    machine.mem_store_byte(0x6099C, 0x00);
    machine.mem_store_byte(0x6099D, 0x00);
    machine.mem_store_byte(0x02C40, 0x00);
    machine.mem_store_byte(0x02C41, 0x00);
    machine.mem_store_byte(0x02C42, 0x00);
    machine.mem_store_byte(0x02C43, 0x00);
    machine.mem_store_byte(0x6099E, 0x00);
    machine.mem_store_byte(0x6099F, 0x00);
    machine.mem_store_byte(0x609A0, 0x00);
    machine.mem_store_byte(0x609A1, 0x00);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x29501526);
    EXPECT_EQ(cpu.get_ebx(), 0x00002891);
    EXPECT_EQ(cpu.get_ecx(), 0xEF56C9F4);
    EXPECT_EQ(cpu.get_edx(), 0xFFC7B99E);
    EXPECT_EQ(cpu.get_esi(), 0xF4B5A384);
    EXPECT_EQ(cpu.get_edi(), 0x00000101);
    EXPECT_EQ(cpu.get_ebp(), 0x19ACF83A);
    EXPECT_EQ(cpu.get_esp(), 0x0000CD60);
    EXPECT_EQ(cpu.get_cs(), 0x00005DB4);
    EXPECT_EQ(cpu.get_ds(), 0x0000003F);
    EXPECT_EQ(cpu.get_es(), 0x00002586);
    EXPECT_EQ(cpu.get_fs(), 0x00000853);
    EXPECT_EQ(cpu.get_gs(), 0x0000F97B);
    EXPECT_EQ(cpu.get_ss(), 0x0000FDBD);
    EXPECT_EQ(cpu.get_eip(), 0x00002E57);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C16);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02C41), 0x40);
    EXPECT_EQ(memory.load8(0x02C42), 0x38);
    EXPECT_EQ(memory.load8(0x02C43), 0x5A);
}

//
// sub eax,BC21EA7Bh
//
TEST_F(Test386, sub_eax_BC21EA7Bh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFF7EE779);
    cpu.set_ebx(0x2369BB4F);
    cpu.set_ecx(0x00000012);
    cpu.set_edx(0x0B709A14);
    cpu.set_esi(0x8B53C079);
    cpu.set_edi(0x00000090);
    cpu.set_ebp(0xFFCF9C38);
    cpu.set_esp(0x0000FF7E);
    cpu.set_cs(0x00006DA0);
    cpu.set_ds(0x000002E3);
    cpu.set_es(0x000033E3);
    cpu.set_fs(0x000074C2);
    cpu.set_gs(0x00006BA9);
    cpu.set_ss(0x0000E184);
    cpu.set_eip(0x0000B5D0);
    cpu.set_eflags(0xFFFC0857);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x78FD0, 0x66);
    machine.mem_store_byte(0x78FD1, 0x2D);
    machine.mem_store_byte(0x78FD2, 0x7B);
    machine.mem_store_byte(0x78FD3, 0xEA);
    machine.mem_store_byte(0x78FD4, 0x21);
    machine.mem_store_byte(0x78FD5, 0xBC);
    machine.mem_store_byte(0x78FD6, 0xF4);
    machine.mem_store_byte(0x78FD7, 0xFF);
    machine.mem_store_byte(0x78FD8, 0xFF);
    machine.mem_store_byte(0x78FD9, 0xFF);
    machine.mem_store_byte(0x78FDA, 0xFF);
    machine.mem_store_byte(0x78FDB, 0xFF);
    machine.mem_store_byte(0x78FDC, 0xFF);
    machine.mem_store_byte(0x78FDD, 0xFF);
    machine.mem_store_byte(0x78FDE, 0xFF);
    machine.mem_store_byte(0x78FDF, 0xFF);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x435CFCFE);
    EXPECT_EQ(cpu.get_ebx(), 0x2369BB4F);
    EXPECT_EQ(cpu.get_ecx(), 0x00000012);
    EXPECT_EQ(cpu.get_edx(), 0x0B709A14);
    EXPECT_EQ(cpu.get_esi(), 0x8B53C079);
    EXPECT_EQ(cpu.get_edi(), 0x00000090);
    EXPECT_EQ(cpu.get_ebp(), 0xFFCF9C38);
    EXPECT_EQ(cpu.get_esp(), 0x0000FF7E);
    EXPECT_EQ(cpu.get_cs(), 0x00006DA0);
    EXPECT_EQ(cpu.get_ds(), 0x000002E3);
    EXPECT_EQ(cpu.get_es(), 0x000033E3);
    EXPECT_EQ(cpu.get_fs(), 0x000074C2);
    EXPECT_EQ(cpu.get_gs(), 0x00006BA9);
    EXPECT_EQ(cpu.get_ss(), 0x0000E184);
    EXPECT_EQ(cpu.get_eip(), 0x0000B5D7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0012);

    // Final RAM entries
}

//
// sbb dword [ds:esi+4Dh],2Ah
//
TEST_F(Test386, sbb_dword_ds_esi_4Dh_2Ah)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFFFF7FF);
    cpu.set_ebx(0xCDCEFB25);
    cpu.set_ecx(0xF352F03E);
    cpu.set_edx(0x00000017);
    cpu.set_esi(0x00000101);
    cpu.set_edi(0x00F00000);
    cpu.set_ebp(0x10000000);
    cpu.set_esp(0x000000FE);
    cpu.set_cs(0x0000091A);
    cpu.set_ds(0x00006943);
    cpu.set_es(0x000000BF);
    cpu.set_fs(0x0000490A);
    cpu.set_gs(0x0000E847);
    cpu.set_ss(0x00006B8C);
    cpu.set_eip(0x00004DF8);
    cpu.set_eflags(0xFFFC0C42);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0DF98, 0x67);
    machine.mem_store_byte(0x0DF99, 0x66);
    machine.mem_store_byte(0x0DF9A, 0x83);
    machine.mem_store_byte(0x0DF9B, 0x5C);
    machine.mem_store_byte(0x0DF9C, 0xE6);
    machine.mem_store_byte(0x0DF9D, 0x4D);
    machine.mem_store_byte(0x0DF9E, 0x2A);
    machine.mem_store_byte(0x0DF9F, 0xF4);
    machine.mem_store_byte(0x0DFA0, 0x00);
    machine.mem_store_byte(0x0DFA1, 0x00);
    machine.mem_store_byte(0x0DFA2, 0x00);
    machine.mem_store_byte(0x0DFA3, 0x00);
    machine.mem_store_byte(0x0DFA4, 0x00);
    machine.mem_store_byte(0x0DFA5, 0x00);
    machine.mem_store_byte(0x69C88, 0x00);
    machine.mem_store_byte(0x69C85, 0x00);
    machine.mem_store_byte(0x69C86, 0x00);
    machine.mem_store_byte(0x69C87, 0x00);
    machine.mem_store_byte(0x0DFA6, 0x00);
    machine.mem_store_byte(0x0DFA7, 0x00);
    machine.mem_store_byte(0x0DFA8, 0x00);
    machine.mem_store_byte(0x0DFA9, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFFFF7FF);
    EXPECT_EQ(cpu.get_ebx(), 0xCDCEFB25);
    EXPECT_EQ(cpu.get_ecx(), 0xF352F03E);
    EXPECT_EQ(cpu.get_edx(), 0x00000017);
    EXPECT_EQ(cpu.get_esi(), 0x00000101);
    EXPECT_EQ(cpu.get_edi(), 0x00F00000);
    EXPECT_EQ(cpu.get_ebp(), 0x10000000);
    EXPECT_EQ(cpu.get_esp(), 0x000000FE);
    EXPECT_EQ(cpu.get_cs(), 0x0000091A);
    EXPECT_EQ(cpu.get_ds(), 0x00006943);
    EXPECT_EQ(cpu.get_es(), 0x000000BF);
    EXPECT_EQ(cpu.get_fs(), 0x0000490A);
    EXPECT_EQ(cpu.get_gs(), 0x0000E847);
    EXPECT_EQ(cpu.get_ss(), 0x00006B8C);
    EXPECT_EQ(cpu.get_eip(), 0x00004E00);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0493);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x69C88), 0xFF);
    EXPECT_EQ(memory.load8(0x69C85), 0xD6);
    EXPECT_EQ(memory.load8(0x69C86), 0xFF);
    EXPECT_EQ(memory.load8(0x69C87), 0xFF);
}

//
// shld [ds:ecx+41h],eax,98h
//
TEST_F(Test386, shld_ds_ecx_41h_eax_98h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD7E8EFCC);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x0000CF89);
    cpu.set_edx(0x83D05882);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xE625DC14);
    cpu.set_ebp(0x8CA2C04E);
    cpu.set_esp(0x0000C3CC);
    cpu.set_cs(0x0000FDF0);
    cpu.set_ds(0x0000009F);
    cpu.set_es(0x0000B63A);
    cpu.set_fs(0x0000906B);
    cpu.set_gs(0x0000A08F);
    cpu.set_ss(0x00002E66);
    cpu.set_eip(0x000059B8);
    cpu.set_eflags(0xFFFC0457);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1038B8, 0x67);
    machine.mem_store_byte(0x1038B9, 0x66);
    machine.mem_store_byte(0x1038BA, 0x0F);
    machine.mem_store_byte(0x1038BB, 0xA4);
    machine.mem_store_byte(0x1038BC, 0x41);
    machine.mem_store_byte(0x1038BD, 0x41);
    machine.mem_store_byte(0x1038BE, 0x98);
    machine.mem_store_byte(0x1038BF, 0xF4);
    machine.mem_store_byte(0x1038C0, 0xED);
    machine.mem_store_byte(0x1038C1, 0x7E);
    machine.mem_store_byte(0x1038C2, 0x06);
    machine.mem_store_byte(0x1038C3, 0x39);
    machine.mem_store_byte(0x1038C4, 0x66);
    machine.mem_store_byte(0x1038C5, 0xBF);
    machine.mem_store_byte(0x0D9BC, 0x3A);
    machine.mem_store_byte(0x0D9BD, 0x68);
    machine.mem_store_byte(0x0D9BA, 0x2C);
    machine.mem_store_byte(0x0D9BB, 0x64);
    machine.mem_store_byte(0x1038C6, 0x13);
    machine.mem_store_byte(0x1038C7, 0x76);
    machine.mem_store_byte(0x1038C8, 0x28);
    machine.mem_store_byte(0x1038C9, 0xC9);
    machine.mem_store_byte(0x1038CA, 0x97);
    machine.mem_store_byte(0x1038CB, 0xB1);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD7E8EFCC);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x0000CF89);
    EXPECT_EQ(cpu.get_edx(), 0x83D05882);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xE625DC14);
    EXPECT_EQ(cpu.get_ebp(), 0x8CA2C04E);
    EXPECT_EQ(cpu.get_esp(), 0x0000C3CC);
    EXPECT_EQ(cpu.get_cs(), 0x0000FDF0);
    EXPECT_EQ(cpu.get_ds(), 0x0000009F);
    EXPECT_EQ(cpu.get_es(), 0x0000B63A);
    EXPECT_EQ(cpu.get_fs(), 0x0000906B);
    EXPECT_EQ(cpu.get_gs(), 0x0000A08F);
    EXPECT_EQ(cpu.get_ss(), 0x00002E66);
    EXPECT_EQ(cpu.get_eip(), 0x000059C0);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0412);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0D9BC), 0xD7);
    EXPECT_EQ(memory.load8(0x0D9BD), 0x2C);
    EXPECT_EQ(memory.load8(0x0D9BA), 0xEF);
    EXPECT_EQ(memory.load8(0x0D9BB), 0xE8);
}

//
// shrd [ds:ebx-41h],si,cl
//
TEST_F(Test386, shrd_ds_ebx_41h_si_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x29501526);
    cpu.set_ebx(0x00002891);
    cpu.set_ecx(0xEF56C9F4);
    cpu.set_edx(0xFFC7B99E);
    cpu.set_esi(0xF4B5A384);
    cpu.set_edi(0x00000101);
    cpu.set_ebp(0x19ACF83A);
    cpu.set_esp(0x0000CD60);
    cpu.set_cs(0x00005DB4);
    cpu.set_ds(0x0000003F);
    cpu.set_es(0x00002586);
    cpu.set_fs(0x00000853);
    cpu.set_gs(0x0000F97B);
    cpu.set_ss(0x0000FDBD);
    cpu.set_eip(0x00002E50);
    cpu.set_eflags(0xFFFC0C16);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x60990, 0x67);
    machine.mem_store_byte(0x60991, 0x0F);
    machine.mem_store_byte(0x60992, 0xAD);
    machine.mem_store_byte(0x60993, 0x73);
    machine.mem_store_byte(0x60994, 0xBF);
    machine.mem_store_byte(0x60995, 0xF4);
    machine.mem_store_byte(0x60996, 0x00);
    machine.mem_store_byte(0x60997, 0x00);
    machine.mem_store_byte(0x60998, 0x00);
    machine.mem_store_byte(0x60999, 0x00);
    machine.mem_store_byte(0x6099A, 0x00);
    machine.mem_store_byte(0x6099B, 0x00);
    machine.mem_store_byte(0x02C40, 0x00);
    machine.mem_store_byte(0x02C41, 0x00);
    machine.mem_store_byte(0x6099C, 0x00);
    machine.mem_store_byte(0x6099D, 0x00);
    machine.mem_store_byte(0x6099E, 0x00);
    machine.mem_store_byte(0x6099F, 0x00);
    machine.mem_store_byte(0x609A0, 0x00);
    machine.mem_store_byte(0x609A1, 0x00);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x29501526);
    EXPECT_EQ(cpu.get_ebx(), 0x00002891);
    EXPECT_EQ(cpu.get_ecx(), 0xEF56C9F4);
    EXPECT_EQ(cpu.get_edx(), 0xFFC7B99E);
    EXPECT_EQ(cpu.get_esi(), 0xF4B5A384);
    EXPECT_EQ(cpu.get_edi(), 0x00000101);
    EXPECT_EQ(cpu.get_ebp(), 0x19ACF83A);
    EXPECT_EQ(cpu.get_esp(), 0x0000CD60);
    EXPECT_EQ(cpu.get_cs(), 0x00005DB4);
    EXPECT_EQ(cpu.get_ds(), 0x0000003F);
    EXPECT_EQ(cpu.get_es(), 0x00002586);
    EXPECT_EQ(cpu.get_fs(), 0x00000853);
    EXPECT_EQ(cpu.get_gs(), 0x0000F97B);
    EXPECT_EQ(cpu.get_ss(), 0x0000FDBD);
    EXPECT_EQ(cpu.get_eip(), 0x00002E56);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C12);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02C40), 0x38);
    EXPECT_EQ(memory.load8(0x02C41), 0x4A);
}

//
// sbb di,[ss:esp+edx*4+26CCh]
//
TEST_F(Test386, sbb_di_ss_esp_edx_4_26CCh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000013);
    cpu.set_ebx(0xE6404EFB);
    cpu.set_ecx(0x94AE2428);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xF001E6EE);
    cpu.set_edi(0x587F74FC);
    cpu.set_ebp(0xE5527159);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000FA86);
    cpu.set_es(0x0000102D);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00004AD4);
    cpu.set_ss(0x000007BE);
    cpu.set_eip(0x000072B0);
    cpu.set_eflags(0xFFFC04C2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x072B0, 0x67);
    machine.mem_store_byte(0x072B1, 0x1B);
    machine.mem_store_byte(0x072B2, 0xBC);
    machine.mem_store_byte(0x072B3, 0x94);
    machine.mem_store_byte(0x072B4, 0xCC);
    machine.mem_store_byte(0x072B5, 0x26);
    machine.mem_store_byte(0x072B6, 0x00);
    machine.mem_store_byte(0x072B7, 0x00);
    machine.mem_store_byte(0x072B8, 0xF4);
    machine.mem_store_byte(0x072B9, 0xE7);
    machine.mem_store_byte(0x072BA, 0xA6);
    machine.mem_store_byte(0x072BB, 0xCC);
    machine.mem_store_byte(0x0A2B4, 0xE9);
    machine.mem_store_byte(0x0A2B5, 0x55);
    machine.mem_store_byte(0x072BC, 0x76);
    machine.mem_store_byte(0x072BD, 0xD2);
    machine.mem_store_byte(0x072BE, 0x2E);
    machine.mem_store_byte(0x072BF, 0x52);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000013);
    EXPECT_EQ(cpu.get_ebx(), 0xE6404EFB);
    EXPECT_EQ(cpu.get_ecx(), 0x94AE2428);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xF001E6EE);
    EXPECT_EQ(cpu.get_edi(), 0x587F1F13);
    EXPECT_EQ(cpu.get_ebp(), 0xE5527159);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000FA86);
    EXPECT_EQ(cpu.get_es(), 0x0000102D);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00004AD4);
    EXPECT_EQ(cpu.get_ss(), 0x000007BE);
    EXPECT_EQ(cpu.get_eip(), 0x000072B9);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0402);

    // Final RAM entries
}

//
// sbb edi,[ss:esp+edx*4+26CCh]
//
TEST_F(Test386, sbb_edi_ss_esp_edx_4_26CCh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000013);
    cpu.set_ebx(0xE6404EFB);
    cpu.set_ecx(0x94AE2428);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0xF001E6EE);
    cpu.set_edi(0x587F74FC);
    cpu.set_ebp(0xE5527159);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00000000);
    cpu.set_ds(0x0000FA86);
    cpu.set_es(0x0000102D);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00004AD4);
    cpu.set_ss(0x000007BE);
    cpu.set_eip(0x000072B0);
    cpu.set_eflags(0xFFFC04C2);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x072B0, 0x66);
    machine.mem_store_byte(0x072B1, 0x67);
    machine.mem_store_byte(0x072B2, 0x1B);
    machine.mem_store_byte(0x072B3, 0xBC);
    machine.mem_store_byte(0x072B4, 0x94);
    machine.mem_store_byte(0x072B5, 0xCC);
    machine.mem_store_byte(0x072B6, 0x26);
    machine.mem_store_byte(0x072B7, 0x00);
    machine.mem_store_byte(0x072B8, 0x00);
    machine.mem_store_byte(0x072B9, 0xF4);
    machine.mem_store_byte(0x072BA, 0xA6);
    machine.mem_store_byte(0x072BB, 0xCC);
    machine.mem_store_byte(0x072BC, 0x76);
    machine.mem_store_byte(0x072BD, 0xD2);
    machine.mem_store_byte(0x072BE, 0x2E);
    machine.mem_store_byte(0x072BF, 0x52);
    machine.mem_store_byte(0x0A2B4, 0xE9);
    machine.mem_store_byte(0x0A2B5, 0x55);
    machine.mem_store_byte(0x0A2B6, 0x2B);
    machine.mem_store_byte(0x0A2B7, 0xF2);
    machine.mem_store_byte(0x072C0, 0x89);
    machine.mem_store_byte(0x072C1, 0x0F);
    machine.mem_store_byte(0x072C2, 0x12);
    machine.mem_store_byte(0x072C3, 0xFC);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000013);
    EXPECT_EQ(cpu.get_ebx(), 0xE6404EFB);
    EXPECT_EQ(cpu.get_ecx(), 0x94AE2428);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0xF001E6EE);
    EXPECT_EQ(cpu.get_edi(), 0x66541F13);
    EXPECT_EQ(cpu.get_ebp(), 0xE5527159);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00000000);
    EXPECT_EQ(cpu.get_ds(), 0x0000FA86);
    EXPECT_EQ(cpu.get_es(), 0x0000102D);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00004AD4);
    EXPECT_EQ(cpu.get_ss(), 0x000007BE);
    EXPECT_EQ(cpu.get_eip(), 0x000072BA);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0403);

    // Final RAM entries
}

//
// shl dword [ss:esp+ecx*8+1BFEh],cl
//
TEST_F(Test386, shl_dword_ss_esp_ecx_8_1BFEh_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00576DB3);
    cpu.set_ebx(0x20000001);
    cpu.set_ecx(0x00000027);
    cpu.set_edx(0x33357743);
    cpu.set_esi(0x318256D6);
    cpu.set_edi(0xDFE4BC20);
    cpu.set_ebp(0x7FFFFFFF);
    cpu.set_esp(0x000009CD);
    cpu.set_cs(0x0000426B);
    cpu.set_ds(0x0000F644);
    cpu.set_es(0x000065C9);
    cpu.set_fs(0x00005BEB);
    cpu.set_gs(0x00000001);
    cpu.set_ss(0x00003CB1);
    cpu.set_eip(0x00007A40);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4A0F0, 0x66);
    machine.mem_store_byte(0x4A0F1, 0x67);
    machine.mem_store_byte(0x4A0F2, 0xD3);
    machine.mem_store_byte(0x4A0F3, 0xA4);
    machine.mem_store_byte(0x4A0F4, 0xCC);
    machine.mem_store_byte(0x4A0F5, 0xFE);
    machine.mem_store_byte(0x4A0F6, 0x1B);
    machine.mem_store_byte(0x4A0F7, 0x00);
    machine.mem_store_byte(0x4A0F8, 0x00);
    machine.mem_store_byte(0x4A0F9, 0xF4);
    machine.mem_store_byte(0x4A0FA, 0xE2);
    machine.mem_store_byte(0x4A0FB, 0x17);
    machine.mem_store_byte(0x4A0FC, 0x42);
    machine.mem_store_byte(0x4A0FD, 0x66);
    machine.mem_store_byte(0x4A0FE, 0x15);
    machine.mem_store_byte(0x4A0FF, 0xD5);
    machine.mem_store_byte(0x3F214, 0xCD);
    machine.mem_store_byte(0x3F215, 0x4D);
    machine.mem_store_byte(0x3F216, 0x8B);
    machine.mem_store_byte(0x3F213, 0x92);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00576DB3);
    EXPECT_EQ(cpu.get_ebx(), 0x20000001);
    EXPECT_EQ(cpu.get_ecx(), 0x00000027);
    EXPECT_EQ(cpu.get_edx(), 0x33357743);
    EXPECT_EQ(cpu.get_esi(), 0x318256D6);
    EXPECT_EQ(cpu.get_edi(), 0xDFE4BC20);
    EXPECT_EQ(cpu.get_ebp(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x000009CD);
    EXPECT_EQ(cpu.get_cs(), 0x0000426B);
    EXPECT_EQ(cpu.get_ds(), 0x0000F644);
    EXPECT_EQ(cpu.get_es(), 0x000065C9);
    EXPECT_EQ(cpu.get_fs(), 0x00005BEB);
    EXPECT_EQ(cpu.get_gs(), 0x00000001);
    EXPECT_EQ(cpu.get_ss(), 0x00003CB1);
    EXPECT_EQ(cpu.get_eip(), 0x00007A4A);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3F214), 0xC9);
    EXPECT_EQ(memory.load8(0x3F215), 0xE6);
    EXPECT_EQ(memory.load8(0x3F216), 0xA6);
    EXPECT_EQ(memory.load8(0x3F213), 0x00);
}

//
// shl word [ss:esp+ecx*8+1BFEh],cl
//
TEST_F(Test386, shl_word_ss_esp_ecx_8_1BFEh_cl)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00576DB3);
    cpu.set_ebx(0x20000001);
    cpu.set_ecx(0x00000027);
    cpu.set_edx(0x33357743);
    cpu.set_esi(0x318256D6);
    cpu.set_edi(0xDFE4BC20);
    cpu.set_ebp(0x7FFFFFFF);
    cpu.set_esp(0x000009CD);
    cpu.set_cs(0x0000426B);
    cpu.set_ds(0x0000F644);
    cpu.set_es(0x000065C9);
    cpu.set_fs(0x00005BEB);
    cpu.set_gs(0x00000001);
    cpu.set_ss(0x00003CB1);
    cpu.set_eip(0x00007A40);
    cpu.set_eflags(0xFFFC0452);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4A0F0, 0x67);
    machine.mem_store_byte(0x4A0F1, 0xD3);
    machine.mem_store_byte(0x4A0F2, 0xA4);
    machine.mem_store_byte(0x4A0F3, 0xCC);
    machine.mem_store_byte(0x4A0F4, 0xFE);
    machine.mem_store_byte(0x4A0F5, 0x1B);
    machine.mem_store_byte(0x4A0F6, 0x00);
    machine.mem_store_byte(0x4A0F7, 0x00);
    machine.mem_store_byte(0x4A0F8, 0xF4);
    machine.mem_store_byte(0x4A0F9, 0xAA);
    machine.mem_store_byte(0x4A0FA, 0xE2);
    machine.mem_store_byte(0x4A0FB, 0x17);
    machine.mem_store_byte(0x3F214, 0xCD);
    machine.mem_store_byte(0x3F213, 0x92);
    machine.mem_store_byte(0x4A0FC, 0x42);
    machine.mem_store_byte(0x4A0FD, 0x66);
    machine.mem_store_byte(0x4A0FE, 0x15);
    machine.mem_store_byte(0x4A0FF, 0xD5);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00576DB3);
    EXPECT_EQ(cpu.get_ebx(), 0x20000001);
    EXPECT_EQ(cpu.get_ecx(), 0x00000027);
    EXPECT_EQ(cpu.get_edx(), 0x33357743);
    EXPECT_EQ(cpu.get_esi(), 0x318256D6);
    EXPECT_EQ(cpu.get_edi(), 0xDFE4BC20);
    EXPECT_EQ(cpu.get_ebp(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_esp(), 0x000009CD);
    EXPECT_EQ(cpu.get_cs(), 0x0000426B);
    EXPECT_EQ(cpu.get_ds(), 0x0000F644);
    EXPECT_EQ(cpu.get_es(), 0x000065C9);
    EXPECT_EQ(cpu.get_fs(), 0x00005BEB);
    EXPECT_EQ(cpu.get_gs(), 0x00000001);
    EXPECT_EQ(cpu.get_ss(), 0x00003CB1);
    EXPECT_EQ(cpu.get_eip(), 0x00007A49);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C96);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3F214), 0xC9);
    EXPECT_EQ(memory.load8(0x3F213), 0x00);
}

//
// shld [ss:bp+si+1Bh],ax,A4h
//
TEST_F(Test386, shld_ss_bp_si_1Bh_ax_A4h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD7E8EFCC);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0xB7AACF89);
    cpu.set_edx(0x83D05882);
    cpu.set_esi(0x00000000);
    cpu.set_edi(0xE625DC14);
    cpu.set_ebp(0x8CA2C04E);
    cpu.set_esp(0x0000C3CC);
    cpu.set_cs(0x0000FDF0);
    cpu.set_ds(0x0000009F);
    cpu.set_es(0x0000B63A);
    cpu.set_fs(0x0000906B);
    cpu.set_gs(0x0000A08F);
    cpu.set_ss(0x00002E66);
    cpu.set_eip(0x000059B8);
    cpu.set_eflags(0xFFFC0457);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1038B8, 0x0F);
    machine.mem_store_byte(0x1038B9, 0xA4);
    machine.mem_store_byte(0x1038BA, 0x42);
    machine.mem_store_byte(0x1038BB, 0x1B);
    machine.mem_store_byte(0x1038BC, 0xA4);
    machine.mem_store_byte(0x1038BD, 0xF4);
    machine.mem_store_byte(0x1038BE, 0xA3);
    machine.mem_store_byte(0x1038BF, 0xD4);
    machine.mem_store_byte(0x1038C0, 0xED);
    machine.mem_store_byte(0x1038C1, 0x7E);
    machine.mem_store_byte(0x1038C2, 0x06);
    machine.mem_store_byte(0x1038C3, 0x39);
    machine.mem_store_byte(0x3A6C9, 0x27);
    machine.mem_store_byte(0x3A6CA, 0x2B);
    machine.mem_store_byte(0x1038C4, 0x66);
    machine.mem_store_byte(0x1038C5, 0xBF);
    machine.mem_store_byte(0x1038C6, 0x13);
    machine.mem_store_byte(0x1038C7, 0x76);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD7E8EFCC);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0xB7AACF89);
    EXPECT_EQ(cpu.get_edx(), 0x83D05882);
    EXPECT_EQ(cpu.get_esi(), 0x00000000);
    EXPECT_EQ(cpu.get_edi(), 0xE625DC14);
    EXPECT_EQ(cpu.get_ebp(), 0x8CA2C04E);
    EXPECT_EQ(cpu.get_esp(), 0x0000C3CC);
    EXPECT_EQ(cpu.get_cs(), 0x0000FDF0);
    EXPECT_EQ(cpu.get_ds(), 0x0000009F);
    EXPECT_EQ(cpu.get_es(), 0x0000B63A);
    EXPECT_EQ(cpu.get_fs(), 0x0000906B);
    EXPECT_EQ(cpu.get_gs(), 0x0000A08F);
    EXPECT_EQ(cpu.get_ss(), 0x00002E66);
    EXPECT_EQ(cpu.get_eip(), 0x000059BE);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C96);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3A6C9), 0x7E);
    EXPECT_EQ(memory.load8(0x3A6CA), 0xB2);
}

//
// sbb bx,[ds:edx-6Eh]
//
TEST_F(Test386, sbb_bx_ds_edx_6Eh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x1A9425B0);
    cpu.set_ebx(0x5450354E);
    cpu.set_ecx(0x7EE734EF);
    cpu.set_edx(0x00000000);
    cpu.set_esi(0x89480C45);
    cpu.set_edi(0x94A40B1A);
    cpu.set_ebp(0xCB742831);
    cpu.set_esp(0x000065FF);
    cpu.set_cs(0x000000E1);
    cpu.set_ds(0x00002C87);
    cpu.set_es(0x000035AA);
    cpu.set_fs(0x00003FFF);
    cpu.set_gs(0x00008BF6);
    cpu.set_ss(0x0000214B);
    cpu.set_eip(0x0000ECF8);
    cpu.set_eflags(0xFFFC0047);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0FB08, 0x67);
    machine.mem_store_byte(0x0FB09, 0x1B);
    machine.mem_store_byte(0x0FB0A, 0x5A);
    machine.mem_store_byte(0x0FB0B, 0x92);
    machine.mem_store_byte(0x0FB0C, 0xF4);
    machine.mem_store_byte(0x0FB0D, 0x80);
    machine.mem_store_byte(0x0FB0E, 0xD0);
    machine.mem_store_byte(0x0FB0F, 0x31);
    machine.mem_store_byte(0x0FB10, 0x58);
    machine.mem_store_byte(0x0FB11, 0x8B);
    machine.mem_store_byte(0x0FB12, 0xAC);
    machine.mem_store_byte(0x0FB13, 0x96);
    machine.mem_store_byte(0x0FB14, 0xAF);
    machine.mem_store_byte(0x0FB15, 0x34);
    machine.mem_store_byte(0x0FB16, 0x8C);
    machine.mem_store_byte(0x0FB17, 0x25);
    machine.mem_store_byte(0x0FB18, 0x94);
    machine.mem_store_byte(0x0FB19, 0x39);
    machine.mem_store_byte(0x0FB1A, 0x93);
    machine.mem_store_byte(0x0FB1B, 0xE9);
    machine.mem_store_byte(0x00034, 0x61);
    machine.mem_store_byte(0x00035, 0xD9);
    machine.mem_store_byte(0x00036, 0xC7);
    machine.mem_store_byte(0x00037, 0x1F);
    machine.mem_store_byte(0x2D5D0, 0x2D);
    machine.mem_store_byte(0x2D5D1, 0xF4);
    machine.mem_store_byte(0x2D5D2, 0xAF);
    machine.mem_store_byte(0x2D5D3, 0xF4);
    machine.mem_store_byte(0x2D5D4, 0x6F);
    machine.mem_store_byte(0x2D5D5, 0xF4);
    machine.mem_store_byte(0x2D5D6, 0xD6);
    machine.mem_store_byte(0x2D5D7, 0xF4);
    machine.mem_store_byte(0x2D5D8, 0x23);
    machine.mem_store_byte(0x2D5D9, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x1A9425B0);
    EXPECT_EQ(cpu.get_ebx(), 0x5450354E);
    EXPECT_EQ(cpu.get_ecx(), 0x7EE734EF);
    EXPECT_EQ(cpu.get_edx(), 0x00000000);
    EXPECT_EQ(cpu.get_esi(), 0x89480C45);
    EXPECT_EQ(cpu.get_edi(), 0x94A40B1A);
    EXPECT_EQ(cpu.get_ebp(), 0xCB742831);
    EXPECT_EQ(cpu.get_esp(), 0x000065F9);
    EXPECT_EQ(cpu.get_cs(), 0x00001FC7);
    EXPECT_EQ(cpu.get_ds(), 0x00002C87);
    EXPECT_EQ(cpu.get_es(), 0x000035AA);
    EXPECT_EQ(cpu.get_fs(), 0x00003FFF);
    EXPECT_EQ(cpu.get_gs(), 0x00008BF6);
    EXPECT_EQ(cpu.get_ss(), 0x0000214B);
    EXPECT_EQ(cpu.get_eip(), 0x0000D962);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0047);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x27AAD), 0x47);
    EXPECT_EQ(memory.load8(0x27AAE), 0x00);
    EXPECT_EQ(memory.load8(0x27AAC), 0x00);
    EXPECT_EQ(memory.load8(0x27AAB), 0xE1);
    EXPECT_EQ(memory.load8(0x27AA9), 0xF8);
    EXPECT_EQ(memory.load8(0x27AAA), 0xEC);
}

//
// sub dword [fs:eax],7Dh
//
TEST_F(Test386, sub_dword_fs_eax_7Dh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0000FFFF);
    cpu.set_ebx(0x5CF3ED4A);
    cpu.set_ecx(0x03FFFFFF);
    cpu.set_edx(0x32037997);
    cpu.set_esi(0x00800000);
    cpu.set_edi(0x004E8CCB);
    cpu.set_ebp(0x97918549);
    cpu.set_esp(0x00009E84);
    cpu.set_cs(0x00000148);
    cpu.set_ds(0x000000CF);
    cpu.set_es(0x0000FFFF);
    cpu.set_fs(0x000041CB);
    cpu.set_gs(0x00002036);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00000A20);
    cpu.set_eflags(0xFFFC0016);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x01EA0, 0x3E);
    machine.mem_store_byte(0x01EA1, 0x64);
    machine.mem_store_byte(0x01EA2, 0x67);
    machine.mem_store_byte(0x01EA3, 0x66);
    machine.mem_store_byte(0x01EA4, 0x83);
    machine.mem_store_byte(0x01EA5, 0x28);
    machine.mem_store_byte(0x01EA6, 0x7D);
    machine.mem_store_byte(0x01EA7, 0xF4);
    machine.mem_store_byte(0x01EA8, 0xE0);
    machine.mem_store_byte(0x01EA9, 0x63);
    machine.mem_store_byte(0x01EAA, 0x1E);
    machine.mem_store_byte(0x01EAB, 0x4E);
    machine.mem_store_byte(0x01EAC, 0xC1);
    machine.mem_store_byte(0x01EAD, 0xBD);
    machine.mem_store_byte(0x00034, 0xE6);
    machine.mem_store_byte(0x00035, 0x42);
    machine.mem_store_byte(0x00036, 0x9C);
    machine.mem_store_byte(0x00037, 0xF9);
    machine.mem_store_byte(0xFDCA6, 0xF4);
    machine.mem_store_byte(0xFDCA7, 0xE3);
    machine.mem_store_byte(0xFDCA8, 0xF4);
    machine.mem_store_byte(0xFDCA9, 0x5E);
    machine.mem_store_byte(0xFDCAA, 0xF4);
    machine.mem_store_byte(0xFDCAB, 0x55);
    machine.mem_store_byte(0xFDCAC, 0xF4);
    machine.mem_store_byte(0xFDCAD, 0xA0);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ebx(), 0x5CF3ED4A);
    EXPECT_EQ(cpu.get_ecx(), 0x03FFFFFF);
    EXPECT_EQ(cpu.get_edx(), 0x32037997);
    EXPECT_EQ(cpu.get_esi(), 0x00800000);
    EXPECT_EQ(cpu.get_edi(), 0x004E8CCB);
    EXPECT_EQ(cpu.get_ebp(), 0x97918549);
    EXPECT_EQ(cpu.get_esp(), 0x00009E7E);
    EXPECT_EQ(cpu.get_cs(), 0x0000F99C);
    EXPECT_EQ(cpu.get_ds(), 0x000000CF);
    EXPECT_EQ(cpu.get_es(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_fs(), 0x000041CB);
    EXPECT_EQ(cpu.get_gs(), 0x00002036);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x000042E7);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x09E82), 0x16);
    EXPECT_EQ(memory.load8(0x09E83), 0x00);
    EXPECT_EQ(memory.load8(0x09E80), 0x48);
    EXPECT_EQ(memory.load8(0x09E81), 0x01);
    EXPECT_EQ(memory.load8(0x09E7E), 0x20);
    EXPECT_EQ(memory.load8(0x09E7F), 0x0A);
}

//
// sbb [es:ebp+edx*1+CCF8h],ah
//
TEST_F(Test386, sbb_es_ebp_edx_1_CCF8h_ah)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00000060);
    cpu.set_ebx(0xF0505492);
    cpu.set_ecx(0xFFFF7FFF);
    cpu.set_edx(0x000043D3);
    cpu.set_esi(0x1BE4CC0C);
    cpu.set_edi(0xA75AE2B4);
    cpu.set_ebp(0x0000195A);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000FFF9);
    cpu.set_ds(0x0000B758);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x00007CA0);
    cpu.set_gs(0x000000DF);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00000130);
    cpu.set_eflags(0xFFFC0007);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1000C0, 0x26);
    machine.mem_store_byte(0x1000C1, 0x67);
    machine.mem_store_byte(0x1000C2, 0x18);
    machine.mem_store_byte(0x1000C3, 0xA4);
    machine.mem_store_byte(0x1000C4, 0x15);
    machine.mem_store_byte(0x1000C5, 0xF8);
    machine.mem_store_byte(0x1000C6, 0xCC);
    machine.mem_store_byte(0x1000C7, 0x00);
    machine.mem_store_byte(0x1000C8, 0x00);
    machine.mem_store_byte(0x1000C9, 0xF4);
    machine.mem_store_byte(0x1000CA, 0x00);
    machine.mem_store_byte(0x1000CB, 0x00);
    machine.mem_store_byte(0x1000CC, 0x00);
    machine.mem_store_byte(0x1000CD, 0x00);
    machine.mem_store_byte(0x1000CE, 0x00);
    machine.mem_store_byte(0x1000CF, 0x00);
    machine.mem_store_byte(0x1000D0, 0x00);
    machine.mem_store_byte(0x1000D1, 0x00);
    machine.mem_store_byte(0x1000D2, 0x00);
    machine.mem_store_byte(0x1000D3, 0x00);
    machine.mem_store_byte(0x1000D4, 0x00);
    machine.mem_store_byte(0x1000D5, 0x00);
    machine.mem_store_byte(0x1000D6, 0x00);
    machine.mem_store_byte(0x1000D7, 0x00);
    machine.mem_store_byte(0x00034, 0x07);
    machine.mem_store_byte(0x00035, 0xF0);
    machine.mem_store_byte(0x00036, 0x58);
    machine.mem_store_byte(0x00037, 0x7C);
    machine.mem_store_byte(0x8B586, 0x00);
    machine.mem_store_byte(0x8B587, 0xF4);
    machine.mem_store_byte(0x8B588, 0x00);
    machine.mem_store_byte(0x8B589, 0xF4);
    machine.mem_store_byte(0x8B58A, 0x00);
    machine.mem_store_byte(0x8B58B, 0xF4);
    machine.mem_store_byte(0x8B58C, 0x00);
    machine.mem_store_byte(0x8B58D, 0xF4);

    // Single-step.
    cpu.step();
    if (!cpu.is_halted())
        cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00000060);
    EXPECT_EQ(cpu.get_ebx(), 0xF0505492);
    EXPECT_EQ(cpu.get_ecx(), 0xFFFF7FFF);
    EXPECT_EQ(cpu.get_edx(), 0x000043D3);
    EXPECT_EQ(cpu.get_esi(), 0x1BE4CC0C);
    EXPECT_EQ(cpu.get_edi(), 0xA75AE2B4);
    EXPECT_EQ(cpu.get_ebp(), 0x0000195A);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x00007C58);
    EXPECT_EQ(cpu.get_ds(), 0x0000B758);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x00007CA0);
    EXPECT_EQ(cpu.get_gs(), 0x000000DF);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000F008);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0007);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x00006), 0x07);
    EXPECT_EQ(memory.load8(0x00007), 0x00);
    EXPECT_EQ(memory.load8(0x00004), 0xF9);
    EXPECT_EQ(memory.load8(0x00005), 0xFF);
    EXPECT_EQ(memory.load8(0x00002), 0x30);
    EXPECT_EQ(memory.load8(0x00003), 0x01);
}
