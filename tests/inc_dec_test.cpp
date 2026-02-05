#include "fixture.h"

//
// dec ax
//
TEST_F(MachineTest, dec_ax)
{
    // Initial CPU State
    cpu.set_ax(0xF4A1);
    cpu.set_bx(0xF50D);
    cpu.set_cx(0x7DB0);
    cpu.set_dx(0xCAB8);
    cpu.set_cs(0x67AD);
    cpu.set_ss(0xE8A5);
    cpu.set_ds(0x1E5C);
    cpu.set_es(0xBF1F);
    cpu.set_sp(0xA0B4);
    cpu.set_bp(0x7981);
    cpu.set_si(0x26AB);
    cpu.set_di(0x94F0);
    cpu.set_ip(0xFDDB);
    cpu.set_flags(0xFC16);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x778AB, 0x48);
    machine.mem_store_byte(0x778AC, 0x90);
    machine.mem_store_byte(0x778AD, 0x90);
    machine.mem_store_byte(0x778AE, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xF4A0);
    EXPECT_EQ(cpu.get_ip(), 0xFDDC);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
}

//
// dec bp
//
TEST_F(MachineTest, dec_bp)
{
    // Initial CPU State
    cpu.set_ax(0xD9CC);
    cpu.set_bx(0x7593);
    cpu.set_cx(0x4BE0);
    cpu.set_dx(0x8F09);
    cpu.set_cs(0x5A85);
    cpu.set_ss(0xC548);
    cpu.set_ds(0xE990);
    cpu.set_es(0x3651);
    cpu.set_sp(0x62A8);
    cpu.set_bp(0x5495);
    cpu.set_si(0x09B5);
    cpu.set_di(0x64CC);
    cpu.set_ip(0x4983);
    cpu.set_flags(0xF446);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5F1D3, 0x4D);
    machine.mem_store_byte(0x5F1D4, 0x90);
    machine.mem_store_byte(0x5F1D5, 0x90);
    machine.mem_store_byte(0x5F1D6, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x5494);
    EXPECT_EQ(cpu.get_ip(), 0x4984);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// dec bx
//
TEST_F(MachineTest, dec_bx)
{
    // Initial CPU State
    cpu.set_ax(0x0C39);
    cpu.set_bx(0xD754);
    cpu.set_cx(0xAFC2);
    cpu.set_dx(0xA95A);
    cpu.set_cs(0xAF8F);
    cpu.set_ss(0x6BBE);
    cpu.set_ds(0x0053);
    cpu.set_es(0x3E0A);
    cpu.set_sp(0x3362);
    cpu.set_bp(0x5FAF);
    cpu.set_si(0x2A12);
    cpu.set_di(0x8B91);
    cpu.set_ip(0x641E);
    cpu.set_flags(0xF493);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB5D0E, 0x4B);
    machine.mem_store_byte(0xB5D0F, 0x90);
    machine.mem_store_byte(0xB5D10, 0x90);
    machine.mem_store_byte(0xB5D11, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xD753);
    EXPECT_EQ(cpu.get_ip(), 0x641F);
    EXPECT_EQ(cpu.get_flags(), 0xF487);

    // Final RAM entries
}

//
// dec byte [ss:bp+si+62h]
//
TEST_F(MachineTest, dec_byte_ss_bp_si_62h)
{
    // Initial CPU State
    cpu.set_ax(0x0EEE);
    cpu.set_bx(0x3DE7);
    cpu.set_cx(0xBF04);
    cpu.set_dx(0xF8F6);
    cpu.set_cs(0x35D1);
    cpu.set_ss(0x71E4);
    cpu.set_ds(0x2848);
    cpu.set_es(0xCB4E);
    cpu.set_sp(0x94F9);
    cpu.set_bp(0x9B27);
    cpu.set_si(0x609F);
    cpu.set_di(0xBC1D);
    cpu.set_ip(0x4ED2);
    cpu.set_flags(0xF412);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3ABE2, 0xFE);
    machine.mem_store_byte(0x3ABE3, 0x4A);
    machine.mem_store_byte(0x3ABE4, 0x62);
    machine.mem_store_byte(0x3ABE5, 0x90);
    machine.mem_store_byte(0x81A68, 0xB2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4ED5);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x81A68), 0xB1);
}

//
// dec cx
//
TEST_F(MachineTest, dec_cx)
{
    // Initial CPU State
    cpu.set_ax(0xE445);
    cpu.set_bx(0x5E36);
    cpu.set_cx(0xA9A0);
    cpu.set_dx(0x1E5C);
    cpu.set_cs(0x4785);
    cpu.set_ss(0xE736);
    cpu.set_ds(0xB3C1);
    cpu.set_es(0xFFF1);
    cpu.set_sp(0xA079);
    cpu.set_bp(0x7A77);
    cpu.set_si(0xF856);
    cpu.set_di(0xAA03);
    cpu.set_ip(0xA37C);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x51BCC, 0x49);
    machine.mem_store_byte(0x51BCD, 0x90);
    machine.mem_store_byte(0x51BCE, 0x90);
    machine.mem_store_byte(0x51BCF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xA99F);
    EXPECT_EQ(cpu.get_ip(), 0xA37D);
    EXPECT_EQ(cpu.get_flags(), 0xF496);

    // Final RAM entries
}

//
// dec di
//
TEST_F(MachineTest, dec_di)
{
    // Initial CPU State
    cpu.set_ax(0xD70D);
    cpu.set_bx(0x0CD9);
    cpu.set_cx(0x0926);
    cpu.set_dx(0x0D7D);
    cpu.set_cs(0x4874);
    cpu.set_ss(0xE452);
    cpu.set_ds(0xB472);
    cpu.set_es(0xC63D);
    cpu.set_sp(0x0BF8);
    cpu.set_bp(0x5DD0);
    cpu.set_si(0x92E1);
    cpu.set_di(0x8C3B);
    cpu.set_ip(0xDD97);
    cpu.set_flags(0xF886);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x564D7, 0x4F);
    machine.mem_store_byte(0x564D8, 0x90);
    machine.mem_store_byte(0x564D9, 0x90);
    machine.mem_store_byte(0x564DA, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x8C3A);
    EXPECT_EQ(cpu.get_ip(), 0xDD98);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// dec dx
//
TEST_F(MachineTest, dec_dx)
{
    // Initial CPU State
    cpu.set_ax(0xEA61);
    cpu.set_bx(0xB7B6);
    cpu.set_cx(0x4C16);
    cpu.set_dx(0x153B);
    cpu.set_cs(0xBC7F);
    cpu.set_ss(0x35B3);
    cpu.set_ds(0x73DC);
    cpu.set_es(0x2075);
    cpu.set_sp(0x65AF);
    cpu.set_bp(0x2E72);
    cpu.set_si(0x5DB2);
    cpu.set_di(0x991F);
    cpu.set_ip(0xE5DC);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCADCC, 0x4A);
    machine.mem_store_byte(0xCADCD, 0x90);
    machine.mem_store_byte(0xCADCE, 0x90);
    machine.mem_store_byte(0xCADCF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x153A);
    EXPECT_EQ(cpu.get_ip(), 0xE5DD);
    EXPECT_EQ(cpu.get_flags(), 0xF407);

    // Final RAM entries
}

//
// dec si
//
TEST_F(MachineTest, dec_si)
{
    // Initial CPU State
    cpu.set_ax(0x4B02);
    cpu.set_bx(0x9EF0);
    cpu.set_cx(0x7554);
    cpu.set_dx(0x7497);
    cpu.set_cs(0x3823);
    cpu.set_ss(0x05B2);
    cpu.set_ds(0x9A0A);
    cpu.set_es(0x92E9);
    cpu.set_sp(0x607C);
    cpu.set_bp(0x2438);
    cpu.set_si(0x7139);
    cpu.set_di(0x4C2E);
    cpu.set_ip(0x5CEB);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3DF1B, 0x4E);
    machine.mem_store_byte(0x3DF1C, 0x90);
    machine.mem_store_byte(0x3DF1D, 0x90);
    machine.mem_store_byte(0x3DF1E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x7138);
    EXPECT_EQ(cpu.get_ip(), 0x5CEC);
    EXPECT_EQ(cpu.get_flags(), 0xF403);

    // Final RAM entries
}

//
// dec sp
//
TEST_F(MachineTest, dec_sp)
{
    // Initial CPU State
    cpu.set_ax(0x5A80);
    cpu.set_bx(0x3243);
    cpu.set_cx(0x9D5C);
    cpu.set_dx(0x0559);
    cpu.set_cs(0x7D12);
    cpu.set_ss(0x1851);
    cpu.set_ds(0xBA46);
    cpu.set_es(0x480F);
    cpu.set_sp(0xD50F);
    cpu.set_bp(0xCD2F);
    cpu.set_si(0xECA5);
    cpu.set_di(0x4B24);
    cpu.set_ip(0xA252);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x87372, 0x4C);
    machine.mem_store_byte(0x87373, 0x90);
    machine.mem_store_byte(0x87374, 0x90);
    machine.mem_store_byte(0x87375, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xD50E);
    EXPECT_EQ(cpu.get_ip(), 0xA253);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
}

//
// dec word [ss:bp+si-7628h]
//
TEST_F(MachineTest, dec_word_ss_bp_si_7628h)
{
    // Initial CPU State
    cpu.set_ax(0xF097);
    cpu.set_bx(0x3B7D);
    cpu.set_cx(0x5604);
    cpu.set_dx(0xC690);
    cpu.set_cs(0x9554);
    cpu.set_ss(0xBC22);
    cpu.set_ds(0x07A8);
    cpu.set_es(0xB603);
    cpu.set_sp(0xD4EE);
    cpu.set_bp(0xF732);
    cpu.set_si(0x2C46);
    cpu.set_di(0x097F);
    cpu.set_ip(0x1044);
    cpu.set_flags(0xF4C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x96584, 0x36);
    machine.mem_store_byte(0x96585, 0xFF);
    machine.mem_store_byte(0x96586, 0x8A);
    machine.mem_store_byte(0x96587, 0xD8);
    machine.mem_store_byte(0x96588, 0x89);
    machine.mem_store_byte(0xC6F70, 0x36);
    machine.mem_store_byte(0xC6F71, 0x7A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1049);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC6F70), 0x35);
}

//
// inc ax
//
TEST_F(MachineTest, inc_ax)
{
    // Initial CPU State
    cpu.set_ax(0x6FCC);
    cpu.set_bx(0xB583);
    cpu.set_cx(0x83BC);
    cpu.set_dx(0x8A6C);
    cpu.set_cs(0xB107);
    cpu.set_ss(0x5630);
    cpu.set_ds(0xB890);
    cpu.set_es(0xFBBF);
    cpu.set_sp(0xE828);
    cpu.set_bp(0xB7BD);
    cpu.set_si(0x85C5);
    cpu.set_di(0x6C60);
    cpu.set_ip(0x9BAA);
    cpu.set_flags(0xF413);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBAC1A, 0x40);
    machine.mem_store_byte(0xBAC1B, 0x90);
    machine.mem_store_byte(0xBAC1C, 0x90);
    machine.mem_store_byte(0xBAC1D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x6FCD);
    EXPECT_EQ(cpu.get_ip(), 0x9BAB);
    EXPECT_EQ(cpu.get_flags(), 0xF403);

    // Final RAM entries
}

//
// inc bp
//
TEST_F(MachineTest, inc_bp)
{
    // Initial CPU State
    cpu.set_ax(0x3729);
    cpu.set_bx(0xCBC0);
    cpu.set_cx(0xD736);
    cpu.set_dx(0xADEB);
    cpu.set_cs(0xD21A);
    cpu.set_ss(0x8DE7);
    cpu.set_ds(0x3D62);
    cpu.set_es(0x845B);
    cpu.set_sp(0x0DF7);
    cpu.set_bp(0xE12E);
    cpu.set_si(0x1A9B);
    cpu.set_di(0x2247);
    cpu.set_ip(0x96EF);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDB88F, 0x45);
    machine.mem_store_byte(0xDB890, 0x90);
    machine.mem_store_byte(0xDB891, 0x90);
    machine.mem_store_byte(0xDB892, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0xE12F);
    EXPECT_EQ(cpu.get_ip(), 0x96F0);
    EXPECT_EQ(cpu.get_flags(), 0xF083);

    // Final RAM entries
}

//
// inc bx
//
TEST_F(MachineTest, inc_bx)
{
    // Initial CPU State
    cpu.set_ax(0x6CBE);
    cpu.set_bx(0xB3C8);
    cpu.set_cx(0xA2E2);
    cpu.set_dx(0x1688);
    cpu.set_cs(0xA6F0);
    cpu.set_ss(0xE28C);
    cpu.set_ds(0xB7F5);
    cpu.set_es(0x3610);
    cpu.set_sp(0xD8D1);
    cpu.set_bp(0x4818);
    cpu.set_si(0x87F1);
    cpu.set_di(0x253E);
    cpu.set_ip(0x42D2);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAB1D2, 0x43);
    machine.mem_store_byte(0xAB1D3, 0x90);
    machine.mem_store_byte(0xAB1D4, 0x90);
    machine.mem_store_byte(0xAB1D5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xB3C9);
    EXPECT_EQ(cpu.get_ip(), 0x42D3);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// inc byte [ss:bp+si+10h]
//
TEST_F(MachineTest, inc_byte_ss_bp_si_10h)
{
    // Initial CPU State
    cpu.set_ax(0xBD5D);
    cpu.set_bx(0x7D55);
    cpu.set_cx(0xCFB4);
    cpu.set_dx(0xCDCD);
    cpu.set_cs(0x50C0);
    cpu.set_ss(0x2A1B);
    cpu.set_ds(0x7BDF);
    cpu.set_es(0xDA47);
    cpu.set_sp(0x5618);
    cpu.set_bp(0x2D02);
    cpu.set_si(0x2F93);
    cpu.set_di(0xDBB1);
    cpu.set_ip(0x5FF4);
    cpu.set_flags(0xFCD3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x56BF4, 0xFE);
    machine.mem_store_byte(0x56BF5, 0x42);
    machine.mem_store_byte(0x56BF6, 0x10);
    machine.mem_store_byte(0x56BF7, 0x90);
    machine.mem_store_byte(0x2FE55, 0xBE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5FF7);
    EXPECT_EQ(cpu.get_flags(), 0xF483);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2FE55), 0xBF);
}

//
// inc cx
//
TEST_F(MachineTest, inc_cx)
{
    // Initial CPU State
    cpu.set_ax(0x4D2F);
    cpu.set_bx(0xAF7F);
    cpu.set_cx(0x8CCE);
    cpu.set_dx(0x622E);
    cpu.set_cs(0x0353);
    cpu.set_ss(0x0E7E);
    cpu.set_ds(0xB362);
    cpu.set_es(0x16EF);
    cpu.set_sp(0x7186);
    cpu.set_bp(0xE192);
    cpu.set_si(0x27B2);
    cpu.set_di(0x85E1);
    cpu.set_ip(0xADCA);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0E2FA, 0x41);
    machine.mem_store_byte(0x0E2FB, 0x90);
    machine.mem_store_byte(0x0E2FC, 0x90);
    machine.mem_store_byte(0x0E2FD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x8CCF);
    EXPECT_EQ(cpu.get_ip(), 0xADCB);
    EXPECT_EQ(cpu.get_flags(), 0xF487);

    // Final RAM entries
}

//
// inc di
//
TEST_F(MachineTest, inc_di)
{
    // Initial CPU State
    cpu.set_ax(0x4C27);
    cpu.set_bx(0x8727);
    cpu.set_cx(0x7D90);
    cpu.set_dx(0x114D);
    cpu.set_cs(0xAF6C);
    cpu.set_ss(0x86AF);
    cpu.set_ds(0xC181);
    cpu.set_es(0x1EE0);
    cpu.set_sp(0xFB56);
    cpu.set_bp(0x2B53);
    cpu.set_si(0xE7CE);
    cpu.set_di(0xD9A9);
    cpu.set_ip(0xF726);
    cpu.set_flags(0xF443);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBEDE6, 0x47);
    machine.mem_store_byte(0xBEDE7, 0x90);
    machine.mem_store_byte(0xBEDE8, 0x90);
    machine.mem_store_byte(0xBEDE9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xD9AA);
    EXPECT_EQ(cpu.get_ip(), 0xF727);
    EXPECT_EQ(cpu.get_flags(), 0xF487);

    // Final RAM entries
}

//
// inc dx
//
TEST_F(MachineTest, inc_dx)
{
    // Initial CPU State
    cpu.set_ax(0xD690);
    cpu.set_bx(0x2F99);
    cpu.set_cx(0xA650);
    cpu.set_dx(0x7CC3);
    cpu.set_cs(0xB036);
    cpu.set_ss(0xBBAB);
    cpu.set_ds(0x642A);
    cpu.set_es(0x9904);
    cpu.set_sp(0xB7E2);
    cpu.set_bp(0x98E6);
    cpu.set_si(0x3F90);
    cpu.set_di(0x78A2);
    cpu.set_ip(0x12EF);
    cpu.set_flags(0xF4D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB164F, 0x42);
    machine.mem_store_byte(0xB1650, 0x90);
    machine.mem_store_byte(0xB1651, 0x90);
    machine.mem_store_byte(0xB1652, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x7CC4);
    EXPECT_EQ(cpu.get_ip(), 0x12F0);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// inc si
//
TEST_F(MachineTest, inc_si)
{
    // Initial CPU State
    cpu.set_ax(0x5866);
    cpu.set_bx(0x113B);
    cpu.set_cx(0x55B2);
    cpu.set_dx(0x2C78);
    cpu.set_cs(0x57B4);
    cpu.set_ss(0x2038);
    cpu.set_ds(0xEB7C);
    cpu.set_es(0xC396);
    cpu.set_sp(0x3B1A);
    cpu.set_bp(0x8F53);
    cpu.set_si(0x4371);
    cpu.set_di(0x9F6A);
    cpu.set_ip(0x1FC7);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x59B07, 0x46);
    machine.mem_store_byte(0x59B08, 0x90);
    machine.mem_store_byte(0x59B09, 0x90);
    machine.mem_store_byte(0x59B0A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x4372);
    EXPECT_EQ(cpu.get_ip(), 0x1FC8);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
}

//
// inc sp
//
TEST_F(MachineTest, inc_sp)
{
    // Initial CPU State
    cpu.set_ax(0x2311);
    cpu.set_bx(0x63B7);
    cpu.set_cx(0x8A1A);
    cpu.set_dx(0xF4E2);
    cpu.set_cs(0x76FE);
    cpu.set_ss(0x695D);
    cpu.set_ds(0xD841);
    cpu.set_es(0x59F5);
    cpu.set_sp(0x8E47);
    cpu.set_bp(0x7AD7);
    cpu.set_si(0x0847);
    cpu.set_di(0x5AFC);
    cpu.set_ip(0xDD2F);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x84D0F, 0xFF);
    machine.mem_store_byte(0x84D10, 0xC4);
    machine.mem_store_byte(0x84D11, 0x90);
    machine.mem_store_byte(0x84D12, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x8E48);
    EXPECT_EQ(cpu.get_ip(), 0xDD31);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
}
