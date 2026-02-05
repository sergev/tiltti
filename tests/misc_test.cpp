#include "fixture.h"

//
// aaa
//
TEST_F(MachineTest, aaa)
{
    // Initial CPU State
    cpu.set_ax(0x092B);
    cpu.set_bx(0xE2C5);
    cpu.set_cx(0xEED6);
    cpu.set_dx(0xFC7A);
    cpu.set_cs(0xE6A4);
    cpu.set_ss(0xFC9A);
    cpu.set_ds(0x4DDE);
    cpu.set_es(0x5FAB);
    cpu.set_sp(0x6E6C);
    cpu.set_bp(0xE7EB);
    cpu.set_si(0xA650);
    cpu.set_di(0x4D63);
    cpu.set_ip(0xF404);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF5E44, 0x37);
    machine.mem_store_byte(0xF5E45, 0x90);
    machine.mem_store_byte(0xF5E46, 0x90);
    machine.mem_store_byte(0xF5E47, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0A01);
    EXPECT_EQ(cpu.get_ip(), 0xF405);
    EXPECT_EQ(cpu.get_flags(), 0xF013);

    // Final RAM entries
}

//
// aad E2h
//
TEST_F(MachineTest, aad_E2h)
{
    // Initial CPU State
    cpu.set_ax(0x634C);
    cpu.set_bx(0xD4B7);
    cpu.set_cx(0x3A92);
    cpu.set_dx(0x9001);
    cpu.set_cs(0xA070);
    cpu.set_ss(0xFBF1);
    cpu.set_ds(0xBD4A);
    cpu.set_es(0xA238);
    cpu.set_sp(0xE657);
    cpu.set_bp(0xA49C);
    cpu.set_si(0x9BC4);
    cpu.set_di(0xB7E7);
    cpu.set_ip(0x94E2);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA9BE2, 0xD5);
    machine.mem_store_byte(0xA9BE3, 0xE2);
    machine.mem_store_byte(0xA9BE4, 0x90);
    machine.mem_store_byte(0xA9BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x00B2);
    EXPECT_EQ(cpu.get_ip(), 0x94E4);
    EXPECT_EQ(cpu.get_flags(), 0xFC96);

    // Final RAM entries
}

//
// aam 4Bh
//
TEST_F(MachineTest, aam_4Bh)
{
    // Initial CPU State
    cpu.set_ax(0x52A1);
    cpu.set_bx(0xE724);
    cpu.set_cx(0x81C8);
    cpu.set_dx(0xF0F7);
    cpu.set_cs(0x31ED);
    cpu.set_ss(0x1D03);
    cpu.set_ds(0x0258);
    cpu.set_es(0xCCC3);
    cpu.set_sp(0xBF76);
    cpu.set_bp(0x2608);
    cpu.set_si(0xCB21);
    cpu.set_di(0x2729);
    cpu.set_ip(0x02B6);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x32186, 0xD4);
    machine.mem_store_byte(0x32187, 0x4B);
    machine.mem_store_byte(0x32188, 0x90);
    machine.mem_store_byte(0x32189, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x020B);
    EXPECT_EQ(cpu.get_ip(), 0x02B8);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// aas
//
TEST_F(MachineTest, aas)
{
    // Initial CPU State
    cpu.set_ax(0x1249);
    cpu.set_bx(0x1F08);
    cpu.set_cx(0x2642);
    cpu.set_dx(0x3862);
    cpu.set_cs(0x36CB);
    cpu.set_ss(0x6805);
    cpu.set_ds(0x1116);
    cpu.set_es(0xFE53);
    cpu.set_sp(0x4642);
    cpu.set_bp(0xA265);
    cpu.set_si(0x4168);
    cpu.set_di(0xAF73);
    cpu.set_ip(0x90BC);
    cpu.set_flags(0xF087);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3FD6C, 0x3F);
    machine.mem_store_byte(0x3FD6D, 0x90);
    machine.mem_store_byte(0x3FD6E, 0x90);
    machine.mem_store_byte(0x3FD6F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1209);
    EXPECT_EQ(cpu.get_ip(), 0x90BD);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
}

//
// cbw
//
TEST_F(MachineTest, cbw)
{
    // Initial CPU State
    cpu.set_ax(0xB80E);
    cpu.set_bx(0xFDB5);
    cpu.set_cx(0x33EE);
    cpu.set_dx(0xE214);
    cpu.set_cs(0x7BD3);
    cpu.set_ss(0x42ED);
    cpu.set_ds(0xFE59);
    cpu.set_es(0xB313);
    cpu.set_sp(0xFF22);
    cpu.set_bp(0x7033);
    cpu.set_si(0xE35E);
    cpu.set_di(0x4592);
    cpu.set_ip(0xDCD0);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x89A00, 0x36);
    machine.mem_store_byte(0x89A01, 0x98);
    machine.mem_store_byte(0x89A02, 0x90);
    machine.mem_store_byte(0x89A03, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x000E);
    EXPECT_EQ(cpu.get_ip(), 0xDCD2);

    // Final RAM entries
}

//
// clc
//
TEST_F(MachineTest, clc)
{
    // Initial CPU State
    cpu.set_ax(0xBBF8);
    cpu.set_bx(0x6C23);
    cpu.set_cx(0x1A64);
    cpu.set_dx(0xD8FA);
    cpu.set_cs(0xEBD0);
    cpu.set_ss(0xA452);
    cpu.set_ds(0x3F01);
    cpu.set_es(0x7EAB);
    cpu.set_sp(0x5332);
    cpu.set_bp(0xE8E0);
    cpu.set_si(0xD658);
    cpu.set_di(0xF852);
    cpu.set_ip(0xD948);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF9648, 0xF8);
    machine.mem_store_byte(0xF9649, 0x90);
    machine.mem_store_byte(0xF964A, 0x90);
    machine.mem_store_byte(0xF964B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xD949);

    // Final RAM entries
}

//
// cld
//
TEST_F(MachineTest, cld)
{
    // Initial CPU State
    cpu.set_ax(0xB2BD);
    cpu.set_bx(0x536A);
    cpu.set_cx(0xF70E);
    cpu.set_dx(0xBDB9);
    cpu.set_cs(0xC817);
    cpu.set_ss(0x3687);
    cpu.set_ds(0xF2D4);
    cpu.set_es(0xB8D3);
    cpu.set_sp(0x6CF5);
    cpu.set_bp(0xFC36);
    cpu.set_si(0x8CF7);
    cpu.set_di(0x1727);
    cpu.set_ip(0x91E2);
    cpu.set_flags(0xF017);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD1352, 0xFC);
    machine.mem_store_byte(0xD1353, 0x90);
    machine.mem_store_byte(0xD1354, 0x90);
    machine.mem_store_byte(0xD1355, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x91E3);

    // Final RAM entries
}

//
// cli
//
TEST_F(MachineTest, cli)
{
    // Initial CPU State
    cpu.set_ax(0xC5A9);
    cpu.set_bx(0x0598);
    cpu.set_cx(0xE556);
    cpu.set_dx(0xC293);
    cpu.set_cs(0x662E);
    cpu.set_ss(0x63E9);
    cpu.set_ds(0x6A2F);
    cpu.set_es(0x5523);
    cpu.set_sp(0x805E);
    cpu.set_bp(0x901B);
    cpu.set_si(0x44F9);
    cpu.set_di(0xC41C);
    cpu.set_ip(0xBE5F);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7213F, 0xFA);
    machine.mem_store_byte(0x72140, 0x90);
    machine.mem_store_byte(0x72141, 0x90);
    machine.mem_store_byte(0x72142, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBE60);

    // Final RAM entries
}

//
// cmc
//
TEST_F(MachineTest, cmc)
{
    // Initial CPU State
    cpu.set_ax(0xC6B7);
    cpu.set_bx(0x8D86);
    cpu.set_cx(0x864C);
    cpu.set_dx(0x7100);
    cpu.set_cs(0x4813);
    cpu.set_ss(0x6E0B);
    cpu.set_ds(0x1452);
    cpu.set_es(0x0E85);
    cpu.set_sp(0x8D8B);
    cpu.set_bp(0x2CCD);
    cpu.set_si(0xCB20);
    cpu.set_di(0x2B11);
    cpu.set_ip(0xEAB2);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x56BE2, 0xF5);
    machine.mem_store_byte(0x56BE3, 0x90);
    machine.mem_store_byte(0x56BE4, 0x90);
    machine.mem_store_byte(0x56BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEAB3);
    EXPECT_EQ(cpu.get_flags(), 0xFCD3);

    // Final RAM entries
}

//
// cwd
//
TEST_F(MachineTest, cwd)
{
    // Initial CPU State
    cpu.set_ax(0xB2D9);
    cpu.set_bx(0x6367);
    cpu.set_cx(0x8BC2);
    cpu.set_dx(0x98BD);
    cpu.set_cs(0x75D3);
    cpu.set_ss(0x3A7C);
    cpu.set_ds(0xC899);
    cpu.set_es(0x08E2);
    cpu.set_sp(0x288A);
    cpu.set_bp(0xFB26);
    cpu.set_si(0xECDC);
    cpu.set_di(0xE773);
    cpu.set_ip(0x0F30);
    cpu.set_flags(0xFC42);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x76C60, 0x36);
    machine.mem_store_byte(0x76C61, 0x99);
    machine.mem_store_byte(0x76C62, 0x90);
    machine.mem_store_byte(0x76C63, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0x0F32);

    // Final RAM entries
}

//
// daa
//
TEST_F(MachineTest, daa)
{
    // Initial CPU State
    cpu.set_ax(0x162C);
    cpu.set_bx(0x1080);
    cpu.set_cx(0xA9C8);
    cpu.set_dx(0x17A3);
    cpu.set_cs(0x91DB);
    cpu.set_ss(0x66D0);
    cpu.set_ds(0x3424);
    cpu.set_es(0xAC50);
    cpu.set_sp(0x18E2);
    cpu.set_bp(0x2330);
    cpu.set_si(0x239F);
    cpu.set_di(0xBFDE);
    cpu.set_ip(0x07FB);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x925AB, 0x27);
    machine.mem_store_byte(0x925AC, 0x90);
    machine.mem_store_byte(0x925AD, 0x90);
    machine.mem_store_byte(0x925AE, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1692);
    EXPECT_EQ(cpu.get_ip(), 0x07FC);
    EXPECT_EQ(cpu.get_flags(), 0xFC93);

    // Final RAM entries
}

//
// das
//
TEST_F(MachineTest, das)
{
    // Initial CPU State
    cpu.set_ax(0xC7B2);
    cpu.set_bx(0x4317);
    cpu.set_cx(0x029A);
    cpu.set_dx(0x5AF6);
    cpu.set_cs(0x5208);
    cpu.set_ss(0x51D1);
    cpu.set_ds(0x19B9);
    cpu.set_es(0xDDC5);
    cpu.set_sp(0xF809);
    cpu.set_bp(0x617C);
    cpu.set_si(0xF0FF);
    cpu.set_di(0x9254);
    cpu.set_ip(0x2ECA);
    cpu.set_flags(0xF412);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x54F4A, 0x2F);
    machine.mem_store_byte(0x54F4B, 0x90);
    machine.mem_store_byte(0x54F4C, 0x90);
    machine.mem_store_byte(0x54F4D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xC74C);
    EXPECT_EQ(cpu.get_ip(), 0x2ECB);
    EXPECT_EQ(cpu.get_flags(), 0xFC13);

    // Final RAM entries
}

//
// lahf
//
TEST_F(MachineTest, lahf)
{
    // Initial CPU State
    cpu.set_ax(0xD833);
    cpu.set_bx(0x8529);
    cpu.set_cx(0xC4DE);
    cpu.set_dx(0x2D9F);
    cpu.set_cs(0xD1A5);
    cpu.set_ss(0x31F5);
    cpu.set_ds(0xE7E2);
    cpu.set_es(0x1F25);
    cpu.set_sp(0x6B7C);
    cpu.set_bp(0xC694);
    cpu.set_si(0x5F28);
    cpu.set_di(0x6CE2);
    cpu.set_ip(0x83EE);
    cpu.set_flags(0xF816);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD9E3E, 0x9F);
    machine.mem_store_byte(0xD9E3F, 0x90);
    machine.mem_store_byte(0xD9E40, 0x90);
    machine.mem_store_byte(0xD9E41, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1633);
    EXPECT_EQ(cpu.get_ip(), 0x83EF);

    // Final RAM entries
}

//
// lds bp, dword [cs:bx+di+5D90h]
//
TEST_F(MachineTest, lds_bp_dword_cs_bx_di_5D90h)
{
    // Initial CPU State
    cpu.set_ax(0x3A38);
    cpu.set_bx(0xCBDF);
    cpu.set_cx(0xA536);
    cpu.set_dx(0xDA58);
    cpu.set_cs(0xC90A);
    cpu.set_ss(0x52FB);
    cpu.set_ds(0x7867);
    cpu.set_es(0x8A54);
    cpu.set_sp(0x45FD);
    cpu.set_bp(0x3BD7);
    cpu.set_si(0x88BF);
    cpu.set_di(0x74B9);
    cpu.set_ip(0x4153);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCD1F3, 0x2E);
    machine.mem_store_byte(0xCD1F4, 0xC5);
    machine.mem_store_byte(0xCD1F5, 0xA9);
    machine.mem_store_byte(0xCD1F6, 0x90);
    machine.mem_store_byte(0xCD1F7, 0x5D);
    machine.mem_store_byte(0xD2EC8, 0x72);
    machine.mem_store_byte(0xD2EC9, 0x0F);
    machine.mem_store_byte(0xD2ECA, 0xAE);
    machine.mem_store_byte(0xD2ECB, 0xBD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ds(), 0xBDAE);
    EXPECT_EQ(cpu.get_bp(), 0x0F72);
    EXPECT_EQ(cpu.get_ip(), 0x4158);

    // Final RAM entries
}

//
// lea dx, [ds:bx+di-46FDh]
//
TEST_F(MachineTest, lea_dx_ds_bx_di_46FDh)
{
    // Initial CPU State
    cpu.set_ax(0x5EE5);
    cpu.set_bx(0x7DAD);
    cpu.set_cx(0x5500);
    cpu.set_dx(0xBDEF);
    cpu.set_cs(0xE827);
    cpu.set_ss(0x33BD);
    cpu.set_ds(0x4C52);
    cpu.set_es(0x1809);
    cpu.set_sp(0x978F);
    cpu.set_bp(0xB925);
    cpu.set_si(0xE87B);
    cpu.set_di(0xCFA4);
    cpu.set_ip(0x331F);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEB58F, 0x8D);
    machine.mem_store_byte(0xEB590, 0x91);
    machine.mem_store_byte(0xEB591, 0x03);
    machine.mem_store_byte(0xEB592, 0xB9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0654);
    EXPECT_EQ(cpu.get_ip(), 0x3323);

    // Final RAM entries
}

//
// les cx, dword [ds:di]
//
TEST_F(MachineTest, les_cx_dword_ds_di)
{
    // Initial CPU State
    cpu.set_ax(0x508B);
    cpu.set_bx(0x5907);
    cpu.set_cx(0xAEFE);
    cpu.set_dx(0x7955);
    cpu.set_cs(0x0161);
    cpu.set_ss(0x8DD6);
    cpu.set_ds(0xCFF4);
    cpu.set_es(0xB952);
    cpu.set_sp(0x6F6A);
    cpu.set_bp(0xEC1B);
    cpu.set_si(0xB9F0);
    cpu.set_di(0x942C);
    cpu.set_ip(0x8AA2);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0A0B2, 0xC4);
    machine.mem_store_byte(0x0A0B3, 0x0D);
    machine.mem_store_byte(0x0A0B4, 0x90);
    machine.mem_store_byte(0x0A0B5, 0x90);
    machine.mem_store_byte(0xD936C, 0x4D);
    machine.mem_store_byte(0xD936D, 0x64);
    machine.mem_store_byte(0xD936E, 0x56);
    machine.mem_store_byte(0xD936F, 0x65);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x644D);
    EXPECT_EQ(cpu.get_es(), 0x6556);
    EXPECT_EQ(cpu.get_ip(), 0x8AA4);

    // Final RAM entries
}

//
// nop
//
TEST_F(MachineTest, nop)
{
    // Initial CPU State
    cpu.set_ax(0x574C);
    cpu.set_bx(0x5202);
    cpu.set_cx(0xD700);
    cpu.set_dx(0x8B8F);
    cpu.set_cs(0x77CD);
    cpu.set_ss(0x1D2E);
    cpu.set_ds(0xDB7B);
    cpu.set_es(0x4239);
    cpu.set_sp(0x7482);
    cpu.set_bp(0x5823);
    cpu.set_si(0x564C);
    cpu.set_di(0x37DC);
    cpu.set_ip(0x93E9);
    cpu.set_flags(0xFC86);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x810B9, 0x2E);
    machine.mem_store_byte(0x810BA, 0x90);
    machine.mem_store_byte(0x810BB, 0x90);
    machine.mem_store_byte(0x810BC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x93EB);

    // Final RAM entries
}

//
// popf
//
TEST_F(MachineTest, popf)
{
    // Initial CPU State
    cpu.set_ax(0xD0D6);
    cpu.set_bx(0x9CD5);
    cpu.set_cx(0x7CFE);
    cpu.set_dx(0x46F0);
    cpu.set_cs(0xFCF5);
    cpu.set_ss(0x3909);
    cpu.set_ds(0x575A);
    cpu.set_es(0xD33C);
    cpu.set_sp(0xA344);
    cpu.set_bp(0x6E7B);
    cpu.set_si(0xB4C8);
    cpu.set_di(0x8324);
    cpu.set_ip(0x8111);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05061, 0x36);
    machine.mem_store_byte(0x05062, 0x9D);
    machine.mem_store_byte(0x05063, 0x90);
    machine.mem_store_byte(0x05064, 0x90);
    machine.mem_store_byte(0x433D4, 0x9A);
    machine.mem_store_byte(0x433D5, 0x5C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xA346);
    EXPECT_EQ(cpu.get_ip(), 0x8113);
    EXPECT_EQ(cpu.get_flags(), 0xFC92);

    // Final RAM entries
}

//
// pushf
//
TEST_F(MachineTest, pushf)
{
    // Initial CPU State
    cpu.set_ax(0xFA8D);
    cpu.set_bx(0xE91F);
    cpu.set_cx(0xB1CE);
    cpu.set_dx(0x060B);
    cpu.set_cs(0xFA25);
    cpu.set_ss(0xF177);
    cpu.set_ds(0x75E0);
    cpu.set_es(0x1975);
    cpu.set_sp(0xE52B);
    cpu.set_bp(0x27D6);
    cpu.set_si(0xE378);
    cpu.set_di(0x88F8);
    cpu.set_ip(0x59CF);
    cpu.set_flags(0xF886);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFFC1F, 0x26);
    machine.mem_store_byte(0xFFC20, 0x9C);
    machine.mem_store_byte(0xFFC21, 0x90);
    machine.mem_store_byte(0xFFC22, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xE529);
    EXPECT_EQ(cpu.get_ip(), 0x59D1);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFFC99), 0x86);
    EXPECT_EQ(memory.load8(0xFFC9A), 0xF8);
}

//
// sahf
//
TEST_F(MachineTest, sahf)
{
    // Initial CPU State
    cpu.set_ax(0xFFA0);
    cpu.set_bx(0xD8E3);
    cpu.set_cx(0x1910);
    cpu.set_dx(0xD194);
    cpu.set_cs(0x7AA7);
    cpu.set_ss(0x5AD8);
    cpu.set_ds(0x8E7C);
    cpu.set_es(0xECB6);
    cpu.set_sp(0x2B12);
    cpu.set_bp(0x770A);
    cpu.set_si(0x0D3C);
    cpu.set_di(0x466B);
    cpu.set_ip(0x3DA0);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7E810, 0x9E);
    machine.mem_store_byte(0x7E811, 0x90);
    machine.mem_store_byte(0x7E812, 0x90);
    machine.mem_store_byte(0x7E813, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3DA1);
    EXPECT_EQ(cpu.get_flags(), 0xFCD7);

    // Final RAM entries
}

//
// salc
//
TEST_F(MachineTest, salc)
{
    // Initial CPU State
    cpu.set_ax(0x4568);
    cpu.set_bx(0xCEEC);
    cpu.set_cx(0x6D72);
    cpu.set_dx(0xD1B6);
    cpu.set_cs(0x3CFE);
    cpu.set_ss(0x74B5);
    cpu.set_ds(0x0894);
    cpu.set_es(0xD1F6);
    cpu.set_sp(0x60D6);
    cpu.set_bp(0x6EDE);
    cpu.set_si(0x6A6B);
    cpu.set_di(0x1F09);
    cpu.set_ip(0x283B);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3F81B, 0x36);
    machine.mem_store_byte(0x3F81C, 0xD6);
    machine.mem_store_byte(0x3F81D, 0x90);
    machine.mem_store_byte(0x3F81E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x4500);
    EXPECT_EQ(cpu.get_ip(), 0x283D);

    // Final RAM entries
}

//
// stc
//
TEST_F(MachineTest, stc)
{
    // Initial CPU State
    cpu.set_ax(0xA5F5);
    cpu.set_bx(0x3081);
    cpu.set_cx(0xE8F2);
    cpu.set_dx(0x8653);
    cpu.set_cs(0x9B6B);
    cpu.set_ss(0x261F);
    cpu.set_ds(0x629A);
    cpu.set_es(0xE374);
    cpu.set_sp(0x76D6);
    cpu.set_bp(0xFC2F);
    cpu.set_si(0x6985);
    cpu.set_di(0x73B6);
    cpu.set_ip(0x4A78);
    cpu.set_flags(0xF846);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA0128, 0xF9);
    machine.mem_store_byte(0xA0129, 0x90);
    machine.mem_store_byte(0xA012A, 0x90);
    machine.mem_store_byte(0xA012B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4A79);
    EXPECT_EQ(cpu.get_flags(), 0xF847);

    // Final RAM entries
}

//
// std
//
TEST_F(MachineTest, std)
{
    // Initial CPU State
    cpu.set_ax(0xE059);
    cpu.set_bx(0x93C1);
    cpu.set_cx(0xE4C2);
    cpu.set_dx(0x193D);
    cpu.set_cs(0xD27B);
    cpu.set_ss(0xC2E2);
    cpu.set_ds(0x5994);
    cpu.set_es(0xD939);
    cpu.set_sp(0x7936);
    cpu.set_bp(0xF037);
    cpu.set_si(0x9BF8);
    cpu.set_di(0x4A14);
    cpu.set_ip(0xCD49);
    cpu.set_flags(0xF8D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDF4F9, 0xFD);
    machine.mem_store_byte(0xDF4FA, 0x90);
    machine.mem_store_byte(0xDF4FB, 0x90);
    machine.mem_store_byte(0xDF4FC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCD4A);
    EXPECT_EQ(cpu.get_flags(), 0xFCD6);

    // Final RAM entries
}

//
// sti
//
TEST_F(MachineTest, sti)
{
    // Initial CPU State
    cpu.set_ax(0x0142);
    cpu.set_bx(0xB13E);
    cpu.set_cx(0xB346);
    cpu.set_dx(0x0E8D);
    cpu.set_cs(0xD207);
    cpu.set_ss(0xF392);
    cpu.set_ds(0x866E);
    cpu.set_es(0xA0A1);
    cpu.set_sp(0x2754);
    cpu.set_bp(0xB11F);
    cpu.set_si(0x3BF0);
    cpu.set_di(0x7A41);
    cpu.set_ip(0x3416);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD5486, 0xFB);
    machine.mem_store_byte(0xD5487, 0x90);
    machine.mem_store_byte(0xD5488, 0x90);
    machine.mem_store_byte(0xD5489, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3417);
    EXPECT_EQ(cpu.get_flags(), 0xFEC7);

    // Final RAM entries
}

//
// xlat
//
TEST_F(MachineTest, xlat)
{
    // Initial CPU State
    cpu.set_ax(0x5EE5);
    cpu.set_bx(0x7DAD);
    cpu.set_cx(0x5500);
    cpu.set_dx(0xBDEF);
    cpu.set_cs(0xE827);
    cpu.set_ss(0x33BD);
    cpu.set_ds(0x4C52);
    cpu.set_es(0x1809);
    cpu.set_sp(0x978F);
    cpu.set_bp(0xB925);
    cpu.set_si(0xE87B);
    cpu.set_di(0xCFA4);
    cpu.set_ip(0x331F);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEB58F, 0xD7);
    machine.mem_store_byte(0xEB590, 0x90);
    machine.mem_store_byte(0xEB591, 0x90);
    machine.mem_store_byte(0xEB592, 0x90);
    machine.mem_store_byte(0x543B2, 0x62);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x5E62);
    EXPECT_EQ(cpu.get_ip(), 0x3320);

    // Final RAM entries
}
