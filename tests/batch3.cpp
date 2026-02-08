#include "fixture.h"

//
// aaa
//
TEST_F(MachineTest, aaa_batch3)
{
    // Initial CPU State
    cpu.set_ax(0xF000);
    cpu.set_bx(0x6BB4);
    cpu.set_cx(0xEE54);
    cpu.set_dx(0x20B5);
    cpu.set_cs(0x6E03);
    cpu.set_ss(0x9DC0);
    cpu.set_ds(0xEF71);
    cpu.set_es(0x8638);
    cpu.set_sp(0x54AE);
    cpu.set_bp(0xDFEC);
    cpu.set_si(0xBEFE);
    cpu.set_di(0x2909);
    cpu.set_ip(0xAB35);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x78B65, 0x37);
    machine.mem_store_byte(0x78B66, 0x90);
    machine.mem_store_byte(0x78B67, 0x90);
    machine.mem_store_byte(0x78B68, 0x90);
    machine.mem_store_byte(0x78B69, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAB36);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x78B65), 0x37);
    EXPECT_EQ(memory.load8(0x78B66), 0x90);
    EXPECT_EQ(memory.load8(0x78B67), 0x90);
    EXPECT_EQ(memory.load8(0x78B68), 0x90);
    EXPECT_EQ(memory.load8(0x78B69), 0x90);
}

//
// aas
//
TEST_F(MachineTest, aas_batch3)
{
    // Initial CPU State
    cpu.set_ax(0xC8D8);
    cpu.set_bx(0x51CE);
    cpu.set_cx(0x1700);
    cpu.set_dx(0x7D29);
    cpu.set_cs(0xDBA1);
    cpu.set_ss(0x72FB);
    cpu.set_ds(0x255B);
    cpu.set_es(0x496A);
    cpu.set_sp(0xA962);
    cpu.set_bp(0x1D12);
    cpu.set_si(0x5080);
    cpu.set_di(0x78DA);
    cpu.set_ip(0x0375);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDBD85, 0x3F);
    machine.mem_store_byte(0xDBD86, 0x90);
    machine.mem_store_byte(0xDBD87, 0x90);
    machine.mem_store_byte(0xDBD88, 0x90);
    machine.mem_store_byte(0xDBD89, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xC702);
    EXPECT_EQ(cpu.get_ip(), 0x0376);
    EXPECT_FLAGS(0xF497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDBD85), 0x3F);
    EXPECT_EQ(memory.load8(0xDBD86), 0x90);
    EXPECT_EQ(memory.load8(0xDBD87), 0x90);
    EXPECT_EQ(memory.load8(0xDBD88), 0x90);
    EXPECT_EQ(memory.load8(0xDBD89), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch3)
{
    // Initial CPU State
    cpu.set_ax(0x6BE0);
    cpu.set_bx(0x00BA);
    cpu.set_cx(0x9C2E);
    cpu.set_dx(0x3C9D);
    cpu.set_cs(0x11B8);
    cpu.set_ss(0x1971);
    cpu.set_ds(0xCBCD);
    cpu.set_es(0x949E);
    cpu.set_sp(0xE120);
    cpu.set_bp(0x506E);
    cpu.set_si(0xE38E);
    cpu.set_di(0xE345);
    cpu.set_ip(0xBC71);
    cpu.set_flags(0xF8C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1D7F1, 0x27);
    machine.mem_store_byte(0x1D7F2, 0x90);
    machine.mem_store_byte(0x1D7F3, 0x90);
    machine.mem_store_byte(0x1D7F4, 0x90);
    machine.mem_store_byte(0x1D7F5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x6B40);
    EXPECT_EQ(cpu.get_ip(), 0xBC72);
    EXPECT_FLAGS(0xF003);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1D7F1), 0x27);
    EXPECT_EQ(memory.load8(0x1D7F2), 0x90);
    EXPECT_EQ(memory.load8(0x1D7F3), 0x90);
    EXPECT_EQ(memory.load8(0x1D7F4), 0x90);
    EXPECT_EQ(memory.load8(0x1D7F5), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch3)
{
    // Initial CPU State
    cpu.set_ax(0x2BC3);
    cpu.set_bx(0xA8FA);
    cpu.set_cx(0xC494);
    cpu.set_dx(0x12EC);
    cpu.set_cs(0xA115);
    cpu.set_ss(0x15FC);
    cpu.set_ds(0x4AA1);
    cpu.set_es(0x907E);
    cpu.set_sp(0x8748);
    cpu.set_bp(0xD782);
    cpu.set_si(0x691B);
    cpu.set_di(0xD2FB);
    cpu.set_ip(0x774E);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA889E, 0x2F);
    machine.mem_store_byte(0xA889F, 0x90);
    machine.mem_store_byte(0xA88A0, 0x90);
    machine.mem_store_byte(0xA88A1, 0x90);
    machine.mem_store_byte(0xA88A2, 0x90);
    machine.mem_store_byte(0xA88A3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2B63);
    EXPECT_EQ(cpu.get_ip(), 0x774F);
    EXPECT_FLAGS(0xF807);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA889E), 0x2F);
    EXPECT_EQ(memory.load8(0xA889F), 0x90);
    EXPECT_EQ(memory.load8(0xA88A0), 0x90);
    EXPECT_EQ(memory.load8(0xA88A1), 0x90);
    EXPECT_EQ(memory.load8(0xA88A2), 0x90);
    EXPECT_EQ(memory.load8(0xA88A3), 0x90);
}

//
// imul ah
//
TEST_F(MachineTest, imul_ah_batch3)
{
    // Initial CPU State
    cpu.set_ax(0xEF33);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xECB4);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xF02B);
    cpu.set_ss(0x379B);
    cpu.set_ds(0x1A9C);
    cpu.set_es(0xA604);
    cpu.set_sp(0x4FE2);
    cpu.set_bp(0x4FAC);
    cpu.set_si(0xE602);
    cpu.set_di(0x181D);
    cpu.set_ip(0xBAB4);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFBD64, 0xF6);
    machine.mem_store_byte(0xFBD65, 0xEC);
    machine.mem_store_byte(0xFBD66, 0x90);
    machine.mem_store_byte(0xFBD67, 0x90);
    machine.mem_store_byte(0xFBD68, 0x90);
    machine.mem_store_byte(0xFBD69, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFC9D);
    EXPECT_EQ(cpu.get_ip(), 0xBAB6);
    EXPECT_FLAGS(0xFC83);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFBD64), 0xF6);
    EXPECT_EQ(memory.load8(0xFBD65), 0xEC);
    EXPECT_EQ(memory.load8(0xFBD66), 0x90);
    EXPECT_EQ(memory.load8(0xFBD67), 0x90);
    EXPECT_EQ(memory.load8(0xFBD68), 0x90);
    EXPECT_EQ(memory.load8(0xFBD69), 0x90);
}

//
// imul byte [ss:bp+si+51h]
//
TEST_F(MachineTest, imul_byte_ss_bp_si_51h_batch3)
{
    // Initial CPU State
    cpu.set_ax(0xA6F3);
    cpu.set_bx(0x3163);
    cpu.set_cx(0x7B0C);
    cpu.set_dx(0x4614);
    cpu.set_cs(0xFE4A);
    cpu.set_ss(0x8D6F);
    cpu.set_ds(0x73FD);
    cpu.set_es(0x107A);
    cpu.set_sp(0x57FD);
    cpu.set_bp(0x9C0F);
    cpu.set_si(0x8818);
    cpu.set_di(0xF666);
    cpu.set_ip(0x3E61);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02301, 0x36);
    machine.mem_store_byte(0x02302, 0xF6);
    machine.mem_store_byte(0x02303, 0x6A);
    machine.mem_store_byte(0x02304, 0x51);
    machine.mem_store_byte(0x02305, 0x90);
    machine.mem_store_byte(0x8FB68, 0x6A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFA9E);
    EXPECT_EQ(cpu.get_ip(), 0x3E65);
    EXPECT_FLAGS(0xF883);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02301), 0x36);
    EXPECT_EQ(memory.load8(0x02302), 0xF6);
    EXPECT_EQ(memory.load8(0x02303), 0x6A);
    EXPECT_EQ(memory.load8(0x02304), 0x51);
    EXPECT_EQ(memory.load8(0x02305), 0x90);
    EXPECT_EQ(memory.load8(0x8FB68), 0x6A);
}

//
// imul word [cs:bp+4Ah]
//
TEST_F(MachineTest, imul_word_cs_bp_4Ah_batch3)
{
    // Initial CPU State
    cpu.set_ax(0x0876);
    cpu.set_bx(0x1508);
    cpu.set_cx(0xCE48);
    cpu.set_dx(0xBCB9);
    cpu.set_cs(0x82A9);
    cpu.set_ss(0xC85C);
    cpu.set_ds(0x62A4);
    cpu.set_es(0x2AE2);
    cpu.set_sp(0xA0F4);
    cpu.set_bp(0xF43C);
    cpu.set_si(0x8FC3);
    cpu.set_di(0x9800);
    cpu.set_ip(0xBC29);
    cpu.set_flags(0xFC53);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8E6B9, 0x2E);
    machine.mem_store_byte(0x8E6BA, 0xF7);
    machine.mem_store_byte(0x8E6BB, 0x6E);
    machine.mem_store_byte(0x8E6BC, 0x4A);
    machine.mem_store_byte(0x8E6BD, 0x90);
    machine.mem_store_byte(0x91F16, 0x7C);
    machine.mem_store_byte(0x91F17, 0xDC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8128);
    EXPECT_EQ(cpu.get_dx(), 0xFED3);
    EXPECT_EQ(cpu.get_ip(), 0xBC2D);
    EXPECT_FLAGS(0xFC87);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8E6B9), 0x2E);
    EXPECT_EQ(memory.load8(0x8E6BA), 0xF7);
    EXPECT_EQ(memory.load8(0x8E6BB), 0x6E);
    EXPECT_EQ(memory.load8(0x8E6BC), 0x4A);
    EXPECT_EQ(memory.load8(0x8E6BD), 0x90);
    EXPECT_EQ(memory.load8(0x91F16), 0x7C);
    EXPECT_EQ(memory.load8(0x91F17), 0xDC);
}

//
// imul word [ds:di]
//
TEST_F(MachineTest, imul_word_ds_di_batch3)
{
    // Initial CPU State
    cpu.set_ax(0xCE14);
    cpu.set_bx(0xBBF1);
    cpu.set_cx(0xDE9E);
    cpu.set_dx(0xF054);
    cpu.set_cs(0x5765);
    cpu.set_ss(0x103B);
    cpu.set_ds(0xC17B);
    cpu.set_es(0xB5F8);
    cpu.set_sp(0x9621);
    cpu.set_bp(0x0D6E);
    cpu.set_si(0x4DFA);
    cpu.set_di(0x38D7);
    cpu.set_ip(0x67DC);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5DE2C, 0xF7);
    machine.mem_store_byte(0x5DE2D, 0x2D);
    machine.mem_store_byte(0x5DE2E, 0x90);
    machine.mem_store_byte(0x5DE2F, 0x90);
    machine.mem_store_byte(0x5DE30, 0x90);
    machine.mem_store_byte(0x5DE31, 0x90);
    machine.mem_store_byte(0xC5087, 0x73);
    machine.mem_store_byte(0xC5088, 0x04);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xE2FC);
    EXPECT_EQ(cpu.get_dx(), 0xFF21);
    EXPECT_EQ(cpu.get_ip(), 0x67DE);
    EXPECT_FLAGS(0xF887);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5DE2C), 0xF7);
    EXPECT_EQ(memory.load8(0x5DE2D), 0x2D);
    EXPECT_EQ(memory.load8(0x5DE2E), 0x90);
    EXPECT_EQ(memory.load8(0x5DE2F), 0x90);
    EXPECT_EQ(memory.load8(0x5DE30), 0x90);
    EXPECT_EQ(memory.load8(0x5DE31), 0x90);
    EXPECT_EQ(memory.load8(0xC5087), 0x73);
    EXPECT_EQ(memory.load8(0xC5088), 0x04);
}

//
// mul byte [es:bx+di+33h]
//
TEST_F(MachineTest, mul_byte_es_bx_di_33h_batch3)
{
    // Initial CPU State
    cpu.set_ax(0x9EC7);
    cpu.set_bx(0xF4BE);
    cpu.set_cx(0x2E32);
    cpu.set_dx(0xCF66);
    cpu.set_cs(0xE9E5);
    cpu.set_ss(0xDCB7);
    cpu.set_ds(0xF35C);
    cpu.set_es(0x2555);
    cpu.set_sp(0x0553);
    cpu.set_bp(0x2234);
    cpu.set_si(0x14C0);
    cpu.set_di(0xF390);
    cpu.set_ip(0xA30F);
    cpu.set_flags(0xF4D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF415F, 0x26);
    machine.mem_store_byte(0xF4160, 0xF6);
    machine.mem_store_byte(0xF4161, 0x61);
    machine.mem_store_byte(0xF4162, 0x33);
    machine.mem_store_byte(0xF4163, 0x90);
    machine.mem_store_byte(0x33DD1, 0xCB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9DCD);
    EXPECT_EQ(cpu.get_ip(), 0xA313);
    EXPECT_FLAGS(0xFC83);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF415F), 0x26);
    EXPECT_EQ(memory.load8(0xF4160), 0xF6);
    EXPECT_EQ(memory.load8(0xF4161), 0x61);
    EXPECT_EQ(memory.load8(0xF4162), 0x33);
    EXPECT_EQ(memory.load8(0xF4163), 0x90);
    EXPECT_EQ(memory.load8(0x33DD1), 0xCB);
}

//
// mul si
//
TEST_F(MachineTest, mul_si_batch3)
{
    // Initial CPU State
    cpu.set_ax(0x2A40);
    cpu.set_bx(0x9D10);
    cpu.set_cx(0xE606);
    cpu.set_dx(0x217E);
    cpu.set_cs(0xD07E);
    cpu.set_ss(0x7A60);
    cpu.set_ds(0x374A);
    cpu.set_es(0xF21F);
    cpu.set_sp(0xB638);
    cpu.set_bp(0x1E92);
    cpu.set_si(0x1DBB);
    cpu.set_di(0xD75F);
    cpu.set_ip(0xA310);
    cpu.set_flags(0xF0C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDAAF0, 0x36);
    machine.mem_store_byte(0xDAAF1, 0xF7);
    machine.mem_store_byte(0xDAAF2, 0xE6);
    machine.mem_store_byte(0xDAAF3, 0x90);
    machine.mem_store_byte(0xDAAF4, 0x90);
    machine.mem_store_byte(0xDAAF5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1CC0);
    EXPECT_EQ(cpu.get_dx(), 0x04E8);
    EXPECT_EQ(cpu.get_ip(), 0xA313);
    EXPECT_FLAGS(0xF807);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDAAF0), 0x36);
    EXPECT_EQ(memory.load8(0xDAAF1), 0xF7);
    EXPECT_EQ(memory.load8(0xDAAF2), 0xE6);
    EXPECT_EQ(memory.load8(0xDAAF3), 0x90);
    EXPECT_EQ(memory.load8(0xDAAF4), 0x90);
    EXPECT_EQ(memory.load8(0xDAAF5), 0x90);
}

//
// rcl byte [ss:bx+di+526Dh], cl
//
TEST_F(MachineTest, rcl_byte_ss_bx_di_526Dh_cl_batch3)
{
    // Initial CPU State
    cpu.set_ax(0x646C);
    cpu.set_bx(0xA7C9);
    cpu.set_cx(0x7F1A);
    cpu.set_dx(0x7EE2);
    cpu.set_cs(0x5D8F);
    cpu.set_ss(0x8797);
    cpu.set_ds(0x4B78);
    cpu.set_es(0xB778);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xBB72);
    cpu.set_si(0x1BC6);
    cpu.set_di(0x76EA);
    cpu.set_ip(0x142A);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5ED1A, 0x36);
    machine.mem_store_byte(0x5ED1B, 0xD2);
    machine.mem_store_byte(0x5ED1C, 0x91);
    machine.mem_store_byte(0x5ED1D, 0x6D);
    machine.mem_store_byte(0x5ED1E, 0x52);
    machine.mem_store_byte(0x5ED1F, 0x90);
    machine.mem_store_byte(0x8EA90, 0xAC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x142F);
    EXPECT_FLAGS(0xFC96);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5ED1A), 0x36);
    EXPECT_EQ(memory.load8(0x5ED1B), 0xD2);
    EXPECT_EQ(memory.load8(0x5ED1C), 0x91);
    EXPECT_EQ(memory.load8(0x5ED1D), 0x6D);
    EXPECT_EQ(memory.load8(0x5ED1E), 0x52);
    EXPECT_EQ(memory.load8(0x5ED1F), 0x90);
    EXPECT_EQ(memory.load8(0x8EA90), 0xD6);
}
