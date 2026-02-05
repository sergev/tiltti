#include "fixture.h"

//
// jb 0011h
//
TEST_F(MachineTest, jb_0011h)
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
    machine.mem_store_byte(0x3F81B, 0x62);
    machine.mem_store_byte(0x3F81C, 0x0F);
    machine.mem_store_byte(0x3F81D, 0x90);
    machine.mem_store_byte(0x3F81E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x283D);

    // Final RAM entries
}

//
// jb 0047h
//
TEST_F(MachineTest, jb_0047h)
{
    // Initial CPU State
    cpu.set_ax(0x8DB5);
    cpu.set_bx(0xDDC1);
    cpu.set_cx(0x495C);
    cpu.set_dx(0xA570);
    cpu.set_cs(0xE8AA);
    cpu.set_ss(0x3666);
    cpu.set_ds(0xACE9);
    cpu.set_es(0x017C);
    cpu.set_sp(0x9468);
    cpu.set_bp(0xDE03);
    cpu.set_si(0x3DE9);
    cpu.set_di(0x5EDD);
    cpu.set_ip(0x61F8);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEEC98, 0x72);
    machine.mem_store_byte(0xEEC99, 0x45);
    machine.mem_store_byte(0xEEC9A, 0x90);
    machine.mem_store_byte(0xEEC9B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x623F);

    // Final RAM entries
}

//
// jbe 000Dh
//
TEST_F(MachineTest, jbe_000Dh)
{
    // Initial CPU State
    cpu.set_ax(0xB20F);
    cpu.set_bx(0x9004);
    cpu.set_cx(0xF438);
    cpu.set_dx(0x110B);
    cpu.set_cs(0xB5B6);
    cpu.set_ss(0x6ADD);
    cpu.set_ds(0xC31E);
    cpu.set_es(0xC1E4);
    cpu.set_sp(0x08FD);
    cpu.set_bp(0xB363);
    cpu.set_si(0x4C83);
    cpu.set_di(0xF915);
    cpu.set_ip(0xCF28);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC2A88, 0x66);
    machine.mem_store_byte(0xC2A89, 0x0B);
    machine.mem_store_byte(0xC2A8A, 0x90);
    machine.mem_store_byte(0xC2A8B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCF2A);

    // Final RAM entries
}

//
// jbe 001Ch
//
TEST_F(MachineTest, jbe_001Ch)
{
    // Initial CPU State
    cpu.set_ax(0x6F01);
    cpu.set_bx(0xF3CB);
    cpu.set_cx(0xBF0A);
    cpu.set_dx(0x96B3);
    cpu.set_cs(0x16D8);
    cpu.set_ss(0xDCD3);
    cpu.set_ds(0x1A48);
    cpu.set_es(0xF923);
    cpu.set_sp(0x9631);
    cpu.set_bp(0xD6C5);
    cpu.set_si(0x3F69);
    cpu.set_di(0x9B40);
    cpu.set_ip(0x9359);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x200D9, 0x76);
    machine.mem_store_byte(0x200DA, 0x1A);
    machine.mem_store_byte(0x200DB, 0x90);
    machine.mem_store_byte(0x200DC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9375);

    // Final RAM entries
}

//
// jl 0046h
//
TEST_F(MachineTest, jl_0046h)
{
    // Initial CPU State
    cpu.set_ax(0xD8B3);
    cpu.set_bx(0x3741);
    cpu.set_cx(0x894C);
    cpu.set_dx(0x3AA9);
    cpu.set_cs(0x8A49);
    cpu.set_ss(0xE4AE);
    cpu.set_ds(0x83DE);
    cpu.set_es(0xECBF);
    cpu.set_sp(0xA6D3);
    cpu.set_bp(0x85A2);
    cpu.set_si(0x0420);
    cpu.set_di(0x8CBF);
    cpu.set_ip(0xCBE0);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97070, 0x6C);
    machine.mem_store_byte(0x97071, 0x44);
    machine.mem_store_byte(0x97072, 0x90);
    machine.mem_store_byte(0x97073, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCBE2);

    // Final RAM entries
}

//
// jl FFABh
//
TEST_F(MachineTest, jl_FFABh)
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
    machine.mem_store_byte(0x56BE2, 0x7C);
    machine.mem_store_byte(0x56BE3, 0xA9);
    machine.mem_store_byte(0x56BE4, 0x90);
    machine.mem_store_byte(0x56BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEAB4);

    // Final RAM entries
}

//
// jle 003Fh
//
TEST_F(MachineTest, jle_003Fh)
{
    // Initial CPU State
    cpu.set_ax(0x17BB);
    cpu.set_bx(0xA8EB);
    cpu.set_cx(0xE23C);
    cpu.set_dx(0xAAF5);
    cpu.set_cs(0x0D44);
    cpu.set_ss(0x6599);
    cpu.set_ds(0xDFE1);
    cpu.set_es(0x06E2);
    cpu.set_sp(0x2C95);
    cpu.set_bp(0x6559);
    cpu.set_si(0x4D17);
    cpu.set_di(0x265E);
    cpu.set_ip(0xBB85);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x18FC5, 0x7E);
    machine.mem_store_byte(0x18FC6, 0x3D);
    machine.mem_store_byte(0x18FC7, 0x90);
    machine.mem_store_byte(0x18FC8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBBC4);

    // Final RAM entries
}

//
// jle 0080h
//
TEST_F(MachineTest, jle_0080h)
{
    // Initial CPU State
    cpu.set_ax(0x2275);
    cpu.set_bx(0x79AA);
    cpu.set_cx(0x1CF6);
    cpu.set_dx(0x99B0);
    cpu.set_cs(0xC6D7);
    cpu.set_ss(0x3DE0);
    cpu.set_ds(0x9691);
    cpu.set_es(0xB2E3);
    cpu.set_sp(0x0A19);
    cpu.set_bp(0xCECF);
    cpu.set_si(0x395F);
    cpu.set_di(0x386D);
    cpu.set_ip(0x4E40);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCBBB0, 0x6E);
    machine.mem_store_byte(0xCBBB1, 0x7E);
    machine.mem_store_byte(0xCBBB2, 0x90);
    machine.mem_store_byte(0xCBBB3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4EC0);

    // Final RAM entries
}

//
// jnb FF93h
//
TEST_F(MachineTest, jnb_FF93h)
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
    machine.mem_store_byte(0xEB58F, 0x63);
    machine.mem_store_byte(0xEB590, 0x91);
    machine.mem_store_byte(0xEB591, 0x90);
    machine.mem_store_byte(0xEB592, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3321);

    // Final RAM entries
}

//
// jnb FFADh
//
TEST_F(MachineTest, jnb_FFADh)
{
    // Initial CPU State
    cpu.set_ax(0xB861);
    cpu.set_bx(0xB3E9);
    cpu.set_cx(0x825A);
    cpu.set_dx(0x19EE);
    cpu.set_cs(0x5F51);
    cpu.set_ss(0xD1DB);
    cpu.set_ds(0x4E80);
    cpu.set_es(0x35F6);
    cpu.set_sp(0xDCE8);
    cpu.set_bp(0x5019);
    cpu.set_si(0xAC88);
    cpu.set_di(0xCF60);
    cpu.set_ip(0x0D96);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x602A6, 0x73);
    machine.mem_store_byte(0x602A7, 0xAB);
    machine.mem_store_byte(0x602A8, 0x90);
    machine.mem_store_byte(0x602A9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0D98);

    // Final RAM entries
}

//
// jnbe 0051h
//
TEST_F(MachineTest, jnbe_0051h)
{
    // Initial CPU State
    cpu.set_ax(0xC70E);
    cpu.set_bx(0x8F8B);
    cpu.set_cx(0x4B9E);
    cpu.set_dx(0x657F);
    cpu.set_cs(0x2140);
    cpu.set_ss(0xC178);
    cpu.set_ds(0xF4F8);
    cpu.set_es(0x184D);
    cpu.set_sp(0x0114);
    cpu.set_bp(0xBFCD);
    cpu.set_si(0x169F);
    cpu.set_di(0x105A);
    cpu.set_ip(0xA1DE);
    cpu.set_flags(0xF892);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2B5DE, 0x77);
    machine.mem_store_byte(0x2B5DF, 0x4F);
    machine.mem_store_byte(0x2B5E0, 0x90);
    machine.mem_store_byte(0x2B5E1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA22F);

    // Final RAM entries
}

//
// jnbe FFFFh
//
TEST_F(MachineTest, jnbe_FFFFh)
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
    machine.mem_store_byte(0x89A00, 0x67);
    machine.mem_store_byte(0x89A01, 0xFD);
    machine.mem_store_byte(0x89A02, 0x90);
    machine.mem_store_byte(0x89A03, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDCD2);

    // Final RAM entries
}

//
// jnl 005Bh
//
TEST_F(MachineTest, jnl_005Bh)
{
    // Initial CPU State
    cpu.set_ax(0x0AB0);
    cpu.set_bx(0x0428);
    cpu.set_cx(0x81F8);
    cpu.set_dx(0x1C79);
    cpu.set_cs(0x89A4);
    cpu.set_ss(0x656C);
    cpu.set_ds(0x79C8);
    cpu.set_es(0xC984);
    cpu.set_sp(0xAF26);
    cpu.set_bp(0x5BF9);
    cpu.set_si(0x1EB5);
    cpu.set_di(0xD90D);
    cpu.set_ip(0x87ED);
    cpu.set_flags(0xF843);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9222D, 0x6D);
    machine.mem_store_byte(0x9222E, 0x59);
    machine.mem_store_byte(0x9222F, 0x90);
    machine.mem_store_byte(0x92230, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x87EF);

    // Final RAM entries
}

//
// jnl 0070h
//
TEST_F(MachineTest, jnl_0070h)
{
    // Initial CPU State
    cpu.set_ax(0x095E);
    cpu.set_bx(0xF020);
    cpu.set_cx(0x804C);
    cpu.set_dx(0x966F);
    cpu.set_cs(0xD7F5);
    cpu.set_ss(0x7D3A);
    cpu.set_ds(0xDAC1);
    cpu.set_es(0xF84F);
    cpu.set_sp(0xA6B7);
    cpu.set_bp(0x5B97);
    cpu.set_si(0xDCA1);
    cpu.set_di(0xD9BB);
    cpu.set_ip(0x1BCB);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD9B1B, 0x7D);
    machine.mem_store_byte(0xD9B1C, 0x6E);
    machine.mem_store_byte(0xD9B1D, 0x90);
    machine.mem_store_byte(0xD9B1E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1C3B);

    // Final RAM entries
}

//
// jnle FF8Fh
//
TEST_F(MachineTest, jnle_FF8Fh)
{
    // Initial CPU State
    cpu.set_ax(0x846C);
    cpu.set_bx(0x0302);
    cpu.set_cx(0xEC3A);
    cpu.set_dx(0xD57F);
    cpu.set_cs(0x3134);
    cpu.set_ss(0x20B4);
    cpu.set_ds(0x15F0);
    cpu.set_es(0x793F);
    cpu.set_sp(0xC331);
    cpu.set_bp(0xDD80);
    cpu.set_si(0x87EA);
    cpu.set_di(0x70FC);
    cpu.set_ip(0xB3F7);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3C737, 0x6F);
    machine.mem_store_byte(0x3C738, 0x8D);
    machine.mem_store_byte(0x3C739, 0x90);
    machine.mem_store_byte(0x3C73A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB3F9);

    // Final RAM entries
}

//
// jnle FFB9h
//
TEST_F(MachineTest, jnle_FFB9h)
{
    // Initial CPU State
    cpu.set_ax(0x016F);
    cpu.set_bx(0xB06D);
    cpu.set_cx(0xEA8E);
    cpu.set_dx(0xC177);
    cpu.set_cs(0x2D72);
    cpu.set_ss(0x1B88);
    cpu.set_ds(0xB420);
    cpu.set_es(0xA1A2);
    cpu.set_sp(0xD2C4);
    cpu.set_bp(0xE1B3);
    cpu.set_si(0xE094);
    cpu.set_di(0x3411);
    cpu.set_ip(0xDC03);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3B323, 0x7F);
    machine.mem_store_byte(0x3B324, 0xB7);
    machine.mem_store_byte(0x3B325, 0x90);
    machine.mem_store_byte(0x3B326, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDC05);

    // Final RAM entries
}

//
// jno FF8Fh
//
TEST_F(MachineTest, jno_FF8Fh)
{
    // Initial CPU State
    cpu.set_ax(0x830B);
    cpu.set_bx(0x4F53);
    cpu.set_cx(0x93C4);
    cpu.set_dx(0x3AEB);
    cpu.set_cs(0x97E7);
    cpu.set_ss(0xE621);
    cpu.set_ds(0x8ED9);
    cpu.set_es(0x99CC);
    cpu.set_sp(0xD373);
    cpu.set_bp(0x4A31);
    cpu.set_si(0x31BA);
    cpu.set_di(0xF413);
    cpu.set_ip(0xBEC3);
    cpu.set_flags(0xF056);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA3D33, 0x71);
    machine.mem_store_byte(0xA3D34, 0x8D);
    machine.mem_store_byte(0xA3D35, 0x90);
    machine.mem_store_byte(0xA3D36, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBE52);

    // Final RAM entries
}

//
// jno FFE4h
//
TEST_F(MachineTest, jno_FFE4h)
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
    machine.mem_store_byte(0xA9BE2, 0x61);
    machine.mem_store_byte(0xA9BE3, 0xE2);
    machine.mem_store_byte(0xA9BE4, 0x90);
    machine.mem_store_byte(0xA9BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x94C6);

    // Final RAM entries
}

//
// jnp FFE5h
//
TEST_F(MachineTest, jnp_FFE5h)
{
    // Initial CPU State
    cpu.set_ax(0x172D);
    cpu.set_bx(0x98D3);
    cpu.set_cx(0x38A8);
    cpu.set_dx(0xE64C);
    cpu.set_cs(0xE32C);
    cpu.set_ss(0x47C2);
    cpu.set_ds(0x4B98);
    cpu.set_es(0x74A1);
    cpu.set_sp(0x5D8C);
    cpu.set_bp(0x1DFE);
    cpu.set_si(0x0450);
    cpu.set_di(0x5FF3);
    cpu.set_ip(0x0FE9);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE42A9, 0x7B);
    machine.mem_store_byte(0xE42AA, 0xE3);
    machine.mem_store_byte(0xE42AB, 0x90);
    machine.mem_store_byte(0xE42AC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0FEB);

    // Final RAM entries
}

//
// jnp FFEAh
//
TEST_F(MachineTest, jnp_FFEAh)
{
    // Initial CPU State
    cpu.set_ax(0xAD7C);
    cpu.set_bx(0x6C11);
    cpu.set_cx(0x088C);
    cpu.set_dx(0x3275);
    cpu.set_cs(0xE906);
    cpu.set_ss(0x313F);
    cpu.set_ds(0x13CC);
    cpu.set_es(0x668B);
    cpu.set_sp(0x988C);
    cpu.set_bp(0xB2E4);
    cpu.set_si(0xF749);
    cpu.set_di(0x1F2F);
    cpu.set_ip(0x16BC);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEA71C, 0x36);
    machine.mem_store_byte(0xEA71D, 0x6B);
    machine.mem_store_byte(0xEA71E, 0xE7);
    machine.mem_store_byte(0xEA71F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x16A6);

    // Final RAM entries
}

//
// jns 0040h
//
TEST_F(MachineTest, jns_0040h)
{
    // Initial CPU State
    cpu.set_ax(0xF488);
    cpu.set_bx(0x01EC);
    cpu.set_cx(0xDD68);
    cpu.set_dx(0x8B70);
    cpu.set_cs(0xD588);
    cpu.set_ss(0x500F);
    cpu.set_ds(0x82CF);
    cpu.set_es(0x7A86);
    cpu.set_sp(0x38EA);
    cpu.set_bp(0x0A9B);
    cpu.set_si(0x6C3A);
    cpu.set_di(0x0504);
    cpu.set_ip(0x5D63);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDB5E3, 0x79);
    machine.mem_store_byte(0xDB5E4, 0x3E);
    machine.mem_store_byte(0xDB5E5, 0x90);
    machine.mem_store_byte(0xDB5E6, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5D65);

    // Final RAM entries
}

//
// jns FFC9h
//
TEST_F(MachineTest, jns_FFC9h)
{
    // Initial CPU State
    cpu.set_ax(0x1096);
    cpu.set_bx(0x96CC);
    cpu.set_cx(0xE564);
    cpu.set_dx(0x0D03);
    cpu.set_cs(0xF380);
    cpu.set_ss(0x230A);
    cpu.set_ds(0x1C7B);
    cpu.set_es(0xF82F);
    cpu.set_sp(0xA925);
    cpu.set_bp(0x35AD);
    cpu.set_si(0xEAF1);
    cpu.set_di(0xD515);
    cpu.set_ip(0x4C77);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8477, 0x3E);
    machine.mem_store_byte(0xF8478, 0x69);
    machine.mem_store_byte(0xF8479, 0xC6);
    machine.mem_store_byte(0xF847A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4C7A);

    // Final RAM entries
}

//
// jnz 0031h
//
TEST_F(MachineTest, jnz_0031h)
{
    // Initial CPU State
    cpu.set_ax(0xE5F0);
    cpu.set_bx(0x8D68);
    cpu.set_cx(0x3508);
    cpu.set_dx(0x016D);
    cpu.set_cs(0x0BB8);
    cpu.set_ss(0x0D6C);
    cpu.set_ds(0x5824);
    cpu.set_es(0x02EC);
    cpu.set_sp(0x5BCF);
    cpu.set_bp(0xC40C);
    cpu.set_si(0xC29C);
    cpu.set_di(0xA8F5);
    cpu.set_ip(0xAC29);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x167A9, 0x75);
    machine.mem_store_byte(0x167AA, 0x2F);
    machine.mem_store_byte(0x167AB, 0x90);
    machine.mem_store_byte(0x167AC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAC2B);

    // Final RAM entries
}

//
// jnz FFF1h
//
TEST_F(MachineTest, jnz_FFF1h)
{
    // Initial CPU State
    cpu.set_ax(0x5165);
    cpu.set_bx(0xE748);
    cpu.set_cx(0x13C4);
    cpu.set_dx(0xDDE0);
    cpu.set_cs(0x618C);
    cpu.set_ss(0x3D1E);
    cpu.set_ds(0x6E09);
    cpu.set_es(0x04E7);
    cpu.set_sp(0xF958);
    cpu.set_bp(0xD5E6);
    cpu.set_si(0xD4A8);
    cpu.set_di(0xD855);
    cpu.set_ip(0xBD15);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6D5D5, 0x65);
    machine.mem_store_byte(0x6D5D6, 0xEF);
    machine.mem_store_byte(0x6D5D7, 0x90);
    machine.mem_store_byte(0x6D5D8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBD06);

    // Final RAM entries
}

//
// jo 001Dh
//
TEST_F(MachineTest, jo_001Dh)
{
    // Initial CPU State
    cpu.set_ax(0x9960);
    cpu.set_bx(0x4576);
    cpu.set_cx(0xE6AA);
    cpu.set_dx(0xFC78);
    cpu.set_cs(0x4AB0);
    cpu.set_ss(0x30E6);
    cpu.set_ds(0xCB24);
    cpu.set_es(0x1499);
    cpu.set_sp(0xED88);
    cpu.set_bp(0x1EA7);
    cpu.set_si(0xCAFA);
    cpu.set_di(0xEFB2);
    cpu.set_ip(0x5B9C);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5069C, 0x70);
    machine.mem_store_byte(0x5069D, 0x1B);
    machine.mem_store_byte(0x5069E, 0x90);
    machine.mem_store_byte(0x5069F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5B9E);

    // Final RAM entries
}

//
// jo 004Dh
//
TEST_F(MachineTest, jo_004Dh)
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
    machine.mem_store_byte(0x32186, 0x60);
    machine.mem_store_byte(0x32187, 0x4B);
    machine.mem_store_byte(0x32188, 0x90);
    machine.mem_store_byte(0x32189, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x02B8);

    // Final RAM entries
}

//
// jp 0030h
//
TEST_F(MachineTest, jp_0030h)
{
    // Initial CPU State
    cpu.set_ax(0x86FA);
    cpu.set_bx(0xCADB);
    cpu.set_cx(0xF602);
    cpu.set_dx(0x176F);
    cpu.set_cs(0xCA8E);
    cpu.set_ss(0x5CAC);
    cpu.set_ds(0x009A);
    cpu.set_es(0x2C26);
    cpu.set_sp(0x9FAD);
    cpu.set_bp(0x64D2);
    cpu.set_si(0x6E77);
    cpu.set_di(0x5DF8);
    cpu.set_ip(0x3EEA);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCE7CA, 0x6A);
    machine.mem_store_byte(0xCE7CB, 0x2E);
    machine.mem_store_byte(0xCE7CC, 0x90);
    machine.mem_store_byte(0xCE7CD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3F1A);

    // Final RAM entries
}

//
// jp 0055h
//
TEST_F(MachineTest, jp_0055h)
{
    // Initial CPU State
    cpu.set_ax(0x1922);
    cpu.set_bx(0xA557);
    cpu.set_cx(0x10F2);
    cpu.set_dx(0x2C2F);
    cpu.set_cs(0xF641);
    cpu.set_ss(0xCA85);
    cpu.set_ds(0xC20D);
    cpu.set_es(0x3BA4);
    cpu.set_sp(0xD2CE);
    cpu.set_bp(0xD402);
    cpu.set_si(0x07AF);
    cpu.set_di(0xA546);
    cpu.set_ip(0xCC7E);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0308E, 0x7A);
    machine.mem_store_byte(0x0308F, 0x53);
    machine.mem_store_byte(0x03090, 0x90);
    machine.mem_store_byte(0x03091, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCC80);

    // Final RAM entries
}

//
// js FFACh
//
TEST_F(MachineTest, js_FFACh)
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
    machine.mem_store_byte(0x76C60, 0x68);
    machine.mem_store_byte(0x76C61, 0xAA);
    machine.mem_store_byte(0x76C62, 0x90);
    machine.mem_store_byte(0x76C63, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0F32);

    // Final RAM entries
}

//
// js FFB9h
//
TEST_F(MachineTest, js_FFB9h)
{
    // Initial CPU State
    cpu.set_ax(0xA30E);
    cpu.set_bx(0xF37B);
    cpu.set_cx(0x873A);
    cpu.set_dx(0x01E5);
    cpu.set_cs(0x2AE6);
    cpu.set_ss(0x252C);
    cpu.set_ds(0xCE3C);
    cpu.set_es(0x3023);
    cpu.set_sp(0xE7FF);
    cpu.set_bp(0xD849);
    cpu.set_si(0x599D);
    cpu.set_di(0x91BD);
    cpu.set_ip(0x3FAD);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2EE0D, 0x78);
    machine.mem_store_byte(0x2EE0E, 0xB7);
    machine.mem_store_byte(0x2EE0F, 0x90);
    machine.mem_store_byte(0x2EE10, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3F66);

    // Final RAM entries
}

//
// jz 002Fh
//
TEST_F(MachineTest, jz_002Fh)
{
    // Initial CPU State
    cpu.set_ax(0xBE84);
    cpu.set_bx(0xACEF);
    cpu.set_cx(0x1296);
    cpu.set_dx(0x9A86);
    cpu.set_cs(0x76AB);
    cpu.set_ss(0xCBB3);
    cpu.set_ds(0x2445);
    cpu.set_es(0x02C4);
    cpu.set_sp(0xE67D);
    cpu.set_bp(0x1B2A);
    cpu.set_si(0x9BCA);
    cpu.set_di(0xFA0A);
    cpu.set_ip(0x01C8);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x76C78, 0x64);
    machine.mem_store_byte(0x76C79, 0x2D);
    machine.mem_store_byte(0x76C7A, 0x90);
    machine.mem_store_byte(0x76C7B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x01F7);

    // Final RAM entries
}

//
// jz 0073h
//
TEST_F(MachineTest, jz_0073h)
{
    // Initial CPU State
    cpu.set_ax(0x7163);
    cpu.set_bx(0xADC4);
    cpu.set_cx(0xACA8);
    cpu.set_dx(0xDEF2);
    cpu.set_cs(0x9E2C);
    cpu.set_ss(0x2310);
    cpu.set_ds(0xE675);
    cpu.set_es(0x4AD9);
    cpu.set_sp(0x5F97);
    cpu.set_bp(0xBAA2);
    cpu.set_si(0x747D);
    cpu.set_di(0xE4CF);
    cpu.set_ip(0xE7BA);
    cpu.set_flags(0xF013);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xACA7A, 0x74);
    machine.mem_store_byte(0xACA7B, 0x71);
    machine.mem_store_byte(0xACA7C, 0x90);
    machine.mem_store_byte(0xACA7D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE7BC);

    // Final RAM entries
}
