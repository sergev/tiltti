#include "fixture.h"

// Tests: jb, jbe, jl, jle, jnb, jnbe, jnl, jnle, jno, jnp, jns, jnz, jo, jp, js, jz

TEST_F(MachineTest, jb_0027h)
{
    // Initial CPU State
    cpu.set_ax(0xB213);
    cpu.set_bx(0x11FC);
    cpu.set_cx(0x6068);
    cpu.set_dx(0xFE6D);
    cpu.set_cs(0x717E);
    cpu.set_ss(0xEA91);
    cpu.set_ds(0x1E55);
    cpu.set_es(0x635F);
    cpu.set_sp(0xD748);
    cpu.set_bp(0xA68A);
    cpu.set_si(0x358D);
    cpu.set_di(0x1A94);
    cpu.set_ip(0xEFC8);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x807A8, 0x72);
    machine.mem_store_byte(0x807A9, 0x25);
    machine.mem_store_byte(0x807AA, 0x90);
    machine.mem_store_byte(0x807AB, 0x90);
    machine.mem_store_byte(0x807AC, 0x90);
    machine.mem_store_byte(0x807AD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEFEF);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x807A8), 0x72);
    EXPECT_EQ(memory.load8(0x807A9), 0x25);
    EXPECT_EQ(memory.load8(0x807AA), 0x90);
    EXPECT_EQ(memory.load8(0x807AB), 0x90);
    EXPECT_EQ(memory.load8(0x807AC), 0x90);
    EXPECT_EQ(memory.load8(0x807AD), 0x90);
}

TEST_F(MachineTest, jb_003Ch)
{
    // Initial CPU State
    cpu.set_ax(0xCFE1);
    cpu.set_bx(0xD70C);
    cpu.set_cx(0xCD76);
    cpu.set_dx(0xBB3D);
    cpu.set_cs(0x1921);
    cpu.set_ss(0xD63C);
    cpu.set_ds(0xB127);
    cpu.set_es(0xBB52);
    cpu.set_sp(0xF85D);
    cpu.set_bp(0xBFE3);
    cpu.set_si(0x3EDA);
    cpu.set_di(0x4319);
    cpu.set_ip(0xC16E);
    cpu.set_flags(0xFC12);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2537E, 0x62);
    machine.mem_store_byte(0x2537F, 0x3A);
    machine.mem_store_byte(0x25380, 0x90);
    machine.mem_store_byte(0x25381, 0x90);
    machine.mem_store_byte(0x25382, 0x90);
    machine.mem_store_byte(0x25383, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC170);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2537E), 0x62);
    EXPECT_EQ(memory.load8(0x2537F), 0x3A);
    EXPECT_EQ(memory.load8(0x25380), 0x90);
    EXPECT_EQ(memory.load8(0x25381), 0x90);
    EXPECT_EQ(memory.load8(0x25382), 0x90);
    EXPECT_EQ(memory.load8(0x25383), 0x90);
}

TEST_F(MachineTest, jbe_FFD7h)
{
    // Initial CPU State
    cpu.set_ax(0x6638);
    cpu.set_bx(0x27CF);
    cpu.set_cx(0x7646);
    cpu.set_dx(0xE2E9);
    cpu.set_cs(0xD6AB);
    cpu.set_ss(0xB3A6);
    cpu.set_ds(0x8A0B);
    cpu.set_es(0xE1B2);
    cpu.set_sp(0xC941);
    cpu.set_bp(0x1FCA);
    cpu.set_si(0xA45C);
    cpu.set_di(0x7DCA);
    cpu.set_ip(0x5E0B);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDC8BB, 0x76);
    machine.mem_store_byte(0xDC8BC, 0xD5);
    machine.mem_store_byte(0xDC8BD, 0x90);
    machine.mem_store_byte(0xDC8BE, 0x90);
    machine.mem_store_byte(0xDC8BF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5DE2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDC8BB), 0x76);
    EXPECT_EQ(memory.load8(0xDC8BC), 0xD5);
    EXPECT_EQ(memory.load8(0xDC8BD), 0x90);
    EXPECT_EQ(memory.load8(0xDC8BE), 0x90);
    EXPECT_EQ(memory.load8(0xDC8BF), 0x90);
}

TEST_F(MachineTest, jbe_FFEDh)
{
    // Initial CPU State
    cpu.set_ax(0xDA4A);
    cpu.set_bx(0x35FF);
    cpu.set_cx(0x3FEE);
    cpu.set_dx(0x4B8D);
    cpu.set_cs(0x254A);
    cpu.set_ss(0xA53D);
    cpu.set_ds(0x2E8C);
    cpu.set_es(0xF2E8);
    cpu.set_sp(0xC28B);
    cpu.set_bp(0x0000);
    cpu.set_si(0xFE86);
    cpu.set_di(0x0000);
    cpu.set_ip(0xF127);
    cpu.set_flags(0xF857);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x345C7, 0x66);
    machine.mem_store_byte(0x345C8, 0xEB);
    machine.mem_store_byte(0x345C9, 0x90);
    machine.mem_store_byte(0x345CA, 0x90);
    machine.mem_store_byte(0x345CB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF114);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x345C7), 0x66);
    EXPECT_EQ(memory.load8(0x345C8), 0xEB);
    EXPECT_EQ(memory.load8(0x345C9), 0x90);
    EXPECT_EQ(memory.load8(0x345CA), 0x90);
    EXPECT_EQ(memory.load8(0x345CB), 0x90);
}

TEST_F(MachineTest, jl_001Fh)
{
    // Initial CPU State
    cpu.set_ax(0x4A0A);
    cpu.set_bx(0xF79F);
    cpu.set_cx(0xE35C);
    cpu.set_dx(0x09FD);
    cpu.set_cs(0xB3C2);
    cpu.set_ss(0xE0C4);
    cpu.set_ds(0x3BA9);
    cpu.set_es(0x7A7F);
    cpu.set_sp(0x7F4B);
    cpu.set_bp(0x6D8E);
    cpu.set_si(0x0000);
    cpu.set_di(0xF893);
    cpu.set_ip(0x71C5);
    cpu.set_flags(0xF842);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBADE5, 0x7C);
    machine.mem_store_byte(0xBADE6, 0x1D);
    machine.mem_store_byte(0xBADE7, 0x90);
    machine.mem_store_byte(0xBADE8, 0x90);
    machine.mem_store_byte(0xBADE9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x71E4);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBADE5), 0x7C);
    EXPECT_EQ(memory.load8(0xBADE6), 0x1D);
    EXPECT_EQ(memory.load8(0xBADE7), 0x90);
    EXPECT_EQ(memory.load8(0xBADE8), 0x90);
    EXPECT_EQ(memory.load8(0xBADE9), 0x90);
}

TEST_F(MachineTest, jl_FFE3h)
{
    // Initial CPU State
    cpu.set_ax(0x685E);
    cpu.set_bx(0xE01F);
    cpu.set_cx(0xF704);
    cpu.set_dx(0xCAD7);
    cpu.set_cs(0x2F10);
    cpu.set_ss(0x85C8);
    cpu.set_ds(0xFB9B);
    cpu.set_es(0x48FB);
    cpu.set_sp(0x0969);
    cpu.set_bp(0x11F6);
    cpu.set_si(0x9B3F);
    cpu.set_di(0x0EB8);
    cpu.set_ip(0xE869);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3D969, 0x3E);
    machine.mem_store_byte(0x3D96A, 0x6C);
    machine.mem_store_byte(0x3D96B, 0xE0);
    machine.mem_store_byte(0x3D96C, 0x90);
    machine.mem_store_byte(0x3D96D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE86C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3D969), 0x3E);
    EXPECT_EQ(memory.load8(0x3D96A), 0x6C);
    EXPECT_EQ(memory.load8(0x3D96B), 0xE0);
    EXPECT_EQ(memory.load8(0x3D96C), 0x90);
    EXPECT_EQ(memory.load8(0x3D96D), 0x90);
}

TEST_F(MachineTest, jle_005Ah)
{
    // Initial CPU State
    cpu.set_ax(0x6E77);
    cpu.set_bx(0xC382);
    cpu.set_cx(0x49FE);
    cpu.set_dx(0x84B7);
    cpu.set_cs(0xF2CC);
    cpu.set_ss(0xDE8B);
    cpu.set_ds(0xC1B8);
    cpu.set_es(0xA1C0);
    cpu.set_sp(0x30AE);
    cpu.set_bp(0xCF66);
    cpu.set_si(0x4B72);
    cpu.set_di(0xDB99);
    cpu.set_ip(0xF9B7);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02677, 0x7E);
    machine.mem_store_byte(0x02678, 0x58);
    machine.mem_store_byte(0x02679, 0x90);
    machine.mem_store_byte(0x0267A, 0x90);
    machine.mem_store_byte(0x0267B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF9B9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02677), 0x7E);
    EXPECT_EQ(memory.load8(0x02678), 0x58);
    EXPECT_EQ(memory.load8(0x02679), 0x90);
    EXPECT_EQ(memory.load8(0x0267A), 0x90);
    EXPECT_EQ(memory.load8(0x0267B), 0x90);
}

TEST_F(MachineTest, jle_FFF1h)
{
    // Initial CPU State
    cpu.set_ax(0x0718);
    cpu.set_bx(0x069C);
    cpu.set_cx(0xEA08);
    cpu.set_dx(0x7994);
    cpu.set_cs(0x0402);
    cpu.set_ss(0xA741);
    cpu.set_ds(0x8E16);
    cpu.set_es(0x1B6F);
    cpu.set_sp(0x86B7);
    cpu.set_bp(0x9A41);
    cpu.set_si(0x6AE5);
    cpu.set_di(0xA39D);
    cpu.set_ip(0x7B35);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0BB55, 0x6E);
    machine.mem_store_byte(0x0BB56, 0xEF);
    machine.mem_store_byte(0x0BB57, 0x90);
    machine.mem_store_byte(0x0BB58, 0x90);
    machine.mem_store_byte(0x0BB59, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x7B26);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0BB55), 0x6E);
    EXPECT_EQ(memory.load8(0x0BB56), 0xEF);
    EXPECT_EQ(memory.load8(0x0BB57), 0x90);
    EXPECT_EQ(memory.load8(0x0BB58), 0x90);
    EXPECT_EQ(memory.load8(0x0BB59), 0x90);
}

TEST_F(MachineTest, jnb_FF8Bh)
{
    // Initial CPU State
    cpu.set_ax(0x02FE);
    cpu.set_bx(0xC089);
    cpu.set_cx(0x8830);
    cpu.set_dx(0x89C7);
    cpu.set_cs(0x07C6);
    cpu.set_ss(0xD1D0);
    cpu.set_ds(0x3108);
    cpu.set_es(0xB215);
    cpu.set_sp(0xDFEA);
    cpu.set_bp(0x816C);
    cpu.set_si(0x88A3);
    cpu.set_di(0x42D8);
    cpu.set_ip(0x80E8);
    cpu.set_flags(0xF0C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0FD48, 0x63);
    machine.mem_store_byte(0x0FD49, 0x89);
    machine.mem_store_byte(0x0FD4A, 0x90);
    machine.mem_store_byte(0x0FD4B, 0x90);
    machine.mem_store_byte(0x0FD4C, 0x90);
    machine.mem_store_byte(0x0FD4D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x80EA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0FD48), 0x63);
    EXPECT_EQ(memory.load8(0x0FD49), 0x89);
    EXPECT_EQ(memory.load8(0x0FD4A), 0x90);
    EXPECT_EQ(memory.load8(0x0FD4B), 0x90);
    EXPECT_EQ(memory.load8(0x0FD4C), 0x90);
    EXPECT_EQ(memory.load8(0x0FD4D), 0x90);
}

TEST_F(MachineTest, jnb_FFF4h)
{
    // Initial CPU State
    cpu.set_ax(0x8FCA);
    cpu.set_bx(0xA817);
    cpu.set_cx(0x0454);
    cpu.set_dx(0x9F4B);
    cpu.set_cs(0x893A);
    cpu.set_ss(0x08F8);
    cpu.set_ds(0x1C03);
    cpu.set_es(0xE8EF);
    cpu.set_sp(0x81FB);
    cpu.set_bp(0x0BD0);
    cpu.set_si(0x99D2);
    cpu.set_di(0xCA6F);
    cpu.set_ip(0xE951);
    cpu.set_flags(0xF802);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97CF1, 0x73);
    machine.mem_store_byte(0x97CF2, 0xF2);
    machine.mem_store_byte(0x97CF3, 0x90);
    machine.mem_store_byte(0x97CF4, 0x90);
    machine.mem_store_byte(0x97CF5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE945);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x97CF1), 0x73);
    EXPECT_EQ(memory.load8(0x97CF2), 0xF2);
    EXPECT_EQ(memory.load8(0x97CF3), 0x90);
    EXPECT_EQ(memory.load8(0x97CF4), 0x90);
    EXPECT_EQ(memory.load8(0x97CF5), 0x90);
}

TEST_F(MachineTest, jnbe_0025h)
{
    // Initial CPU State
    cpu.set_ax(0xCA34);
    cpu.set_bx(0x4524);
    cpu.set_cx(0xCAA2);
    cpu.set_dx(0x263B);
    cpu.set_cs(0x28F7);
    cpu.set_ss(0x0CD6);
    cpu.set_ds(0xABE1);
    cpu.set_es(0x8530);
    cpu.set_sp(0x5F04);
    cpu.set_bp(0x97B5);
    cpu.set_si(0x0FCC);
    cpu.set_di(0xA099);
    cpu.set_ip(0xAB0A);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x33A7A, 0x77);
    machine.mem_store_byte(0x33A7B, 0x23);
    machine.mem_store_byte(0x33A7C, 0x90);
    machine.mem_store_byte(0x33A7D, 0x90);
    machine.mem_store_byte(0x33A7E, 0x90);
    machine.mem_store_byte(0x33A7F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAB2F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x33A7A), 0x77);
    EXPECT_EQ(memory.load8(0x33A7B), 0x23);
    EXPECT_EQ(memory.load8(0x33A7C), 0x90);
    EXPECT_EQ(memory.load8(0x33A7D), 0x90);
    EXPECT_EQ(memory.load8(0x33A7E), 0x90);
    EXPECT_EQ(memory.load8(0x33A7F), 0x90);
}

TEST_F(MachineTest, jnbe_FFDBh)
{
    // Initial CPU State
    cpu.set_ax(0x2E2B);
    cpu.set_bx(0x0E18);
    cpu.set_cx(0x3202);
    cpu.set_dx(0xAAE9);
    cpu.set_cs(0xDD79);
    cpu.set_ss(0x98CC);
    cpu.set_ds(0xE3FC);
    cpu.set_es(0xAA30);
    cpu.set_sp(0xCA63);
    cpu.set_bp(0xD5AE);
    cpu.set_si(0x6F2C);
    cpu.set_di(0xDB6C);
    cpu.set_ip(0x36B3);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE0E43, 0x67);
    machine.mem_store_byte(0xE0E44, 0xD9);
    machine.mem_store_byte(0xE0E45, 0x90);
    machine.mem_store_byte(0xE0E46, 0x90);
    machine.mem_store_byte(0xE0E47, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x36B5);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE0E43), 0x67);
    EXPECT_EQ(memory.load8(0xE0E44), 0xD9);
    EXPECT_EQ(memory.load8(0xE0E45), 0x90);
    EXPECT_EQ(memory.load8(0xE0E46), 0x90);
    EXPECT_EQ(memory.load8(0xE0E47), 0x90);
}

TEST_F(MachineTest, jnl_0031h)
{
    // Initial CPU State
    cpu.set_ax(0x3DDD);
    cpu.set_bx(0x94EB);
    cpu.set_cx(0xDDA8);
    cpu.set_dx(0xB5BF);
    cpu.set_cs(0x4021);
    cpu.set_ss(0x1F75);
    cpu.set_ds(0x462A);
    cpu.set_es(0xE9E4);
    cpu.set_sp(0xB8A9);
    cpu.set_bp(0xCB07);
    cpu.set_si(0x5B84);
    cpu.set_di(0xB71F);
    cpu.set_ip(0x0133);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x40343, 0x2E);
    machine.mem_store_byte(0x40344, 0x6D);
    machine.mem_store_byte(0x40345, 0x2E);
    machine.mem_store_byte(0x40346, 0x90);
    machine.mem_store_byte(0x40347, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0164);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x40343), 0x2E);
    EXPECT_EQ(memory.load8(0x40344), 0x6D);
    EXPECT_EQ(memory.load8(0x40345), 0x2E);
    EXPECT_EQ(memory.load8(0x40346), 0x90);
    EXPECT_EQ(memory.load8(0x40347), 0x90);
}

TEST_F(MachineTest, jnl_FFEAh)
{
    // Initial CPU State
    cpu.set_ax(0x4DDD);
    cpu.set_bx(0x50BF);
    cpu.set_cx(0x9024);
    cpu.set_dx(0x32BB);
    cpu.set_cs(0x743D);
    cpu.set_ss(0x96DA);
    cpu.set_ds(0xD9F0);
    cpu.set_es(0xB039);
    cpu.set_sp(0x99E9);
    cpu.set_bp(0x9F5F);
    cpu.set_si(0x09E4);
    cpu.set_di(0x7D9B);
    cpu.set_ip(0xE4C0);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x82890, 0x7D);
    machine.mem_store_byte(0x82891, 0xE8);
    machine.mem_store_byte(0x82892, 0x90);
    machine.mem_store_byte(0x82893, 0x90);
    machine.mem_store_byte(0x82894, 0x90);
    machine.mem_store_byte(0x82895, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE4AA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x82890), 0x7D);
    EXPECT_EQ(memory.load8(0x82891), 0xE8);
    EXPECT_EQ(memory.load8(0x82892), 0x90);
    EXPECT_EQ(memory.load8(0x82893), 0x90);
    EXPECT_EQ(memory.load8(0x82894), 0x90);
    EXPECT_EQ(memory.load8(0x82895), 0x90);
}

TEST_F(MachineTest, jnle_0026h)
{
    // Initial CPU State
    cpu.set_ax(0xFA22);
    cpu.set_bx(0x63DD);
    cpu.set_cx(0x25F2);
    cpu.set_dx(0xC9B0);
    cpu.set_cs(0x6B84);
    cpu.set_ss(0x12CE);
    cpu.set_ds(0x13F3);
    cpu.set_es(0x8DE1);
    cpu.set_sp(0x4B20);
    cpu.set_bp(0x6BA3);
    cpu.set_si(0x741F);
    cpu.set_di(0xA2BF);
    cpu.set_ip(0x4102);
    cpu.set_flags(0xF0D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6F942, 0x7F);
    machine.mem_store_byte(0x6F943, 0x24);
    machine.mem_store_byte(0x6F944, 0x90);
    machine.mem_store_byte(0x6F945, 0x90);
    machine.mem_store_byte(0x6F946, 0x90);
    machine.mem_store_byte(0x6F947, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4104);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6F942), 0x7F);
    EXPECT_EQ(memory.load8(0x6F943), 0x24);
    EXPECT_EQ(memory.load8(0x6F944), 0x90);
    EXPECT_EQ(memory.load8(0x6F945), 0x90);
    EXPECT_EQ(memory.load8(0x6F946), 0x90);
    EXPECT_EQ(memory.load8(0x6F947), 0x90);
}

TEST_F(MachineTest, jnle_FFD1h)
{
    // Initial CPU State
    cpu.set_ax(0x5388);
    cpu.set_bx(0xA801);
    cpu.set_cx(0xE3E4);
    cpu.set_dx(0x2C0E);
    cpu.set_cs(0xBA4B);
    cpu.set_ss(0x1674);
    cpu.set_ds(0x270F);
    cpu.set_es(0xADE9);
    cpu.set_sp(0xBFD9);
    cpu.set_bp(0x73FB);
    cpu.set_si(0x843A);
    cpu.set_di(0xE564);
    cpu.set_ip(0xE4F0);
    cpu.set_flags(0xF8C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC89A0, 0x6F);
    machine.mem_store_byte(0xC89A1, 0xCF);
    machine.mem_store_byte(0xC89A2, 0x90);
    machine.mem_store_byte(0xC89A3, 0x90);
    machine.mem_store_byte(0xC89A4, 0x90);
    machine.mem_store_byte(0xC89A5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE4F2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC89A0), 0x6F);
    EXPECT_EQ(memory.load8(0xC89A1), 0xCF);
    EXPECT_EQ(memory.load8(0xC89A2), 0x90);
    EXPECT_EQ(memory.load8(0xC89A3), 0x90);
    EXPECT_EQ(memory.load8(0xC89A4), 0x90);
    EXPECT_EQ(memory.load8(0xC89A5), 0x90);
}

TEST_F(MachineTest, jno_0038h)
{
    // Initial CPU State
    cpu.set_ax(0xEEC8);
    cpu.set_bx(0x9F6F);
    cpu.set_cx(0x6BFE);
    cpu.set_dx(0x584C);
    cpu.set_cs(0x0661);
    cpu.set_ss(0x0E8E);
    cpu.set_ds(0xE04F);
    cpu.set_es(0x18CC);
    cpu.set_sp(0x0A88);
    cpu.set_bp(0xDA7D);
    cpu.set_si(0x463C);
    cpu.set_di(0x3807);
    cpu.set_ip(0x91DB);
    cpu.set_flags(0xF4D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0F7EB, 0x71);
    machine.mem_store_byte(0x0F7EC, 0x36);
    machine.mem_store_byte(0x0F7ED, 0x90);
    machine.mem_store_byte(0x0F7EE, 0x90);
    machine.mem_store_byte(0x0F7EF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9213);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0F7EB), 0x71);
    EXPECT_EQ(memory.load8(0x0F7EC), 0x36);
    EXPECT_EQ(memory.load8(0x0F7ED), 0x90);
    EXPECT_EQ(memory.load8(0x0F7EE), 0x90);
    EXPECT_EQ(memory.load8(0x0F7EF), 0x90);
}

TEST_F(MachineTest, jno_FFEEh)
{
    // Initial CPU State
    cpu.set_ax(0xC9C2);
    cpu.set_bx(0xFA2F);
    cpu.set_cx(0xD58A);
    cpu.set_dx(0xCA7F);
    cpu.set_cs(0xAB9E);
    cpu.set_ss(0x6793);
    cpu.set_ds(0x81DA);
    cpu.set_es(0xA3FD);
    cpu.set_sp(0x03AF);
    cpu.set_bp(0x4A66);
    cpu.set_si(0x8029);
    cpu.set_di(0x2522);
    cpu.set_ip(0xC685);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB8065, 0x61);
    machine.mem_store_byte(0xB8066, 0xEC);
    machine.mem_store_byte(0xB8067, 0x90);
    machine.mem_store_byte(0xB8068, 0x90);
    machine.mem_store_byte(0xB8069, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC687);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB8065), 0x61);
    EXPECT_EQ(memory.load8(0xB8066), 0xEC);
    EXPECT_EQ(memory.load8(0xB8067), 0x90);
    EXPECT_EQ(memory.load8(0xB8068), 0x90);
    EXPECT_EQ(memory.load8(0xB8069), 0x90);
}

TEST_F(MachineTest, jnp_0058h)
{
    // Initial CPU State
    cpu.set_ax(0x99A4);
    cpu.set_bx(0xEFD1);
    cpu.set_cx(0x920C);
    cpu.set_dx(0x0075);
    cpu.set_cs(0x4C9A);
    cpu.set_ss(0x5729);
    cpu.set_ds(0x1B96);
    cpu.set_es(0x7874);
    cpu.set_sp(0x8EE7);
    cpu.set_bp(0x7BB7);
    cpu.set_si(0xCD6B);
    cpu.set_di(0x1AD6);
    cpu.set_ip(0xCAB7);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x59457, 0x7B);
    machine.mem_store_byte(0x59458, 0x56);
    machine.mem_store_byte(0x59459, 0x90);
    machine.mem_store_byte(0x5945A, 0x90);
    machine.mem_store_byte(0x5945B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCAB9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x59457), 0x7B);
    EXPECT_EQ(memory.load8(0x59458), 0x56);
    EXPECT_EQ(memory.load8(0x59459), 0x90);
    EXPECT_EQ(memory.load8(0x5945A), 0x90);
    EXPECT_EQ(memory.load8(0x5945B), 0x90);
}

TEST_F(MachineTest, jnp_FF94h)
{
    // Initial CPU State
    cpu.set_ax(0xA2BA);
    cpu.set_bx(0x3EAC);
    cpu.set_cx(0x48B6);
    cpu.set_dx(0xD85F);
    cpu.set_cs(0x7E5A);
    cpu.set_ss(0x4427);
    cpu.set_ds(0x6449);
    cpu.set_es(0x8F1E);
    cpu.set_sp(0x05CD);
    cpu.set_bp(0x6634);
    cpu.set_si(0xF2E7);
    cpu.set_di(0xC570);
    cpu.set_ip(0x5F18);
    cpu.set_flags(0xF853);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x844B8, 0x6B);
    machine.mem_store_byte(0x844B9, 0x92);
    machine.mem_store_byte(0x844BA, 0x90);
    machine.mem_store_byte(0x844BB, 0x90);
    machine.mem_store_byte(0x844BC, 0x90);
    machine.mem_store_byte(0x844BD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5EAC);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x844B8), 0x6B);
    EXPECT_EQ(memory.load8(0x844B9), 0x92);
    EXPECT_EQ(memory.load8(0x844BA), 0x90);
    EXPECT_EQ(memory.load8(0x844BB), 0x90);
    EXPECT_EQ(memory.load8(0x844BC), 0x90);
    EXPECT_EQ(memory.load8(0x844BD), 0x90);
}

TEST_F(MachineTest, jns_0052h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0xA7F8);
    cpu.set_cx(0xDFEC);
    cpu.set_dx(0xE547);
    cpu.set_cs(0x6FA1);
    cpu.set_ss(0xB006);
    cpu.set_ds(0xEF83);
    cpu.set_es(0x8B6D);
    cpu.set_sp(0x3869);
    cpu.set_bp(0xEF51);
    cpu.set_si(0x59FE);
    cpu.set_di(0x4117);
    cpu.set_ip(0xE450);
    cpu.set_flags(0xF846);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7DE60, 0x26);
    machine.mem_store_byte(0x7DE61, 0x69);
    machine.mem_store_byte(0x7DE62, 0x4F);
    machine.mem_store_byte(0x7DE63, 0x90);
    machine.mem_store_byte(0x7DE64, 0x90);
    machine.mem_store_byte(0x7DE65, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE4A2);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7DE60), 0x26);
    EXPECT_EQ(memory.load8(0x7DE61), 0x69);
    EXPECT_EQ(memory.load8(0x7DE62), 0x4F);
    EXPECT_EQ(memory.load8(0x7DE63), 0x90);
    EXPECT_EQ(memory.load8(0x7DE64), 0x90);
    EXPECT_EQ(memory.load8(0x7DE65), 0x90);
}

TEST_F(MachineTest, jns_FFFFh)
{
    // Initial CPU State
    cpu.set_ax(0xBDF1);
    cpu.set_bx(0xA920);
    cpu.set_cx(0x2820);
    cpu.set_dx(0xD933);
    cpu.set_cs(0xCE26);
    cpu.set_ss(0x152D);
    cpu.set_ds(0x2A83);
    cpu.set_es(0xEC8C);
    cpu.set_sp(0xC8D5);
    cpu.set_bp(0x0000);
    cpu.set_si(0x6FEE);
    cpu.set_di(0xC68B);
    cpu.set_ip(0x8EA9);
    cpu.set_flags(0xF8C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD7109, 0x79);
    machine.mem_store_byte(0xD710A, 0xFD);
    machine.mem_store_byte(0xD710B, 0x90);
    machine.mem_store_byte(0xD710C, 0x90);
    machine.mem_store_byte(0xD710D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8EAB);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD7109), 0x79);
    EXPECT_EQ(memory.load8(0xD710A), 0xFD);
    EXPECT_EQ(memory.load8(0xD710B), 0x90);
    EXPECT_EQ(memory.load8(0xD710C), 0x90);
    EXPECT_EQ(memory.load8(0xD710D), 0x90);
}

TEST_F(MachineTest, jnz_000Ah)
{
    // Initial CPU State
    cpu.set_ax(0x024B);
    cpu.set_bx(0xF547);
    cpu.set_cx(0xA486);
    cpu.set_dx(0xAB6D);
    cpu.set_cs(0x7FBC);
    cpu.set_ss(0xA79E);
    cpu.set_ds(0x9160);
    cpu.set_es(0x07CE);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x0000);
    cpu.set_si(0xA4CA);
    cpu.set_di(0x2996);
    cpu.set_ip(0xC81F);
    cpu.set_flags(0xF056);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8C3DF, 0x75);
    machine.mem_store_byte(0x8C3E0, 0x08);
    machine.mem_store_byte(0x8C3E1, 0x90);
    machine.mem_store_byte(0x8C3E2, 0x90);
    machine.mem_store_byte(0x8C3E3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC821);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8C3DF), 0x75);
    EXPECT_EQ(memory.load8(0x8C3E0), 0x08);
    EXPECT_EQ(memory.load8(0x8C3E1), 0x90);
    EXPECT_EQ(memory.load8(0x8C3E2), 0x90);
    EXPECT_EQ(memory.load8(0x8C3E3), 0x90);
}

TEST_F(MachineTest, jnz_004Fh)
{
    // Initial CPU State
    cpu.set_ax(0xAFBB);
    cpu.set_bx(0x1AE3);
    cpu.set_cx(0x6EF8);
    cpu.set_dx(0x1082);
    cpu.set_cs(0xC826);
    cpu.set_ss(0xE3F5);
    cpu.set_ds(0xEBBD);
    cpu.set_es(0x127E);
    cpu.set_sp(0x8DFD);
    cpu.set_bp(0xDD06);
    cpu.set_si(0x5BD6);
    cpu.set_di(0xFFD9);
    cpu.set_ip(0x53BC);
    cpu.set_flags(0xF8C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCD61C, 0x65);
    machine.mem_store_byte(0xCD61D, 0x4D);
    machine.mem_store_byte(0xCD61E, 0x90);
    machine.mem_store_byte(0xCD61F, 0x90);
    machine.mem_store_byte(0xCD620, 0x90);
    machine.mem_store_byte(0xCD621, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x53BE);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCD61C), 0x65);
    EXPECT_EQ(memory.load8(0xCD61D), 0x4D);
    EXPECT_EQ(memory.load8(0xCD61E), 0x90);
    EXPECT_EQ(memory.load8(0xCD61F), 0x90);
    EXPECT_EQ(memory.load8(0xCD620), 0x90);
    EXPECT_EQ(memory.load8(0xCD621), 0x90);
}

TEST_F(MachineTest, jo_006Fh)
{
    // Initial CPU State
    cpu.set_ax(0x2D39);
    cpu.set_bx(0x87EE);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x14B0);
    cpu.set_cs(0x3C90);
    cpu.set_ss(0xCD08);
    cpu.set_ds(0xCD00);
    cpu.set_es(0xAC1D);
    cpu.set_sp(0xB231);
    cpu.set_bp(0x1E71);
    cpu.set_si(0x76EC);
    cpu.set_di(0x2960);
    cpu.set_ip(0xF82A);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4C12A, 0x70);
    machine.mem_store_byte(0x4C12B, 0x6D);
    machine.mem_store_byte(0x4C12C, 0x90);
    machine.mem_store_byte(0x4C12D, 0x90);
    machine.mem_store_byte(0x4C12E, 0x90);
    machine.mem_store_byte(0x4C12F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF82C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4C12A), 0x70);
    EXPECT_EQ(memory.load8(0x4C12B), 0x6D);
    EXPECT_EQ(memory.load8(0x4C12C), 0x90);
    EXPECT_EQ(memory.load8(0x4C12D), 0x90);
    EXPECT_EQ(memory.load8(0x4C12E), 0x90);
    EXPECT_EQ(memory.load8(0x4C12F), 0x90);
}

TEST_F(MachineTest, jo_007Ah)
{
    // Initial CPU State
    cpu.set_ax(0x1544);
    cpu.set_bx(0x0089);
    cpu.set_cx(0x4124);
    cpu.set_dx(0x624F);
    cpu.set_cs(0x0D23);
    cpu.set_ss(0x8B23);
    cpu.set_ds(0x9925);
    cpu.set_es(0xD684);
    cpu.set_sp(0xC6E8);
    cpu.set_bp(0xF29B);
    cpu.set_si(0xFC60);
    cpu.set_di(0x47B7);
    cpu.set_ip(0xAD90);
    cpu.set_flags(0xF887);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x17FC0, 0x60);
    machine.mem_store_byte(0x17FC1, 0x78);
    machine.mem_store_byte(0x17FC2, 0x90);
    machine.mem_store_byte(0x17FC3, 0x90);
    machine.mem_store_byte(0x17FC4, 0x90);
    machine.mem_store_byte(0x17FC5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAE0A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x17FC0), 0x60);
    EXPECT_EQ(memory.load8(0x17FC1), 0x78);
    EXPECT_EQ(memory.load8(0x17FC2), 0x90);
    EXPECT_EQ(memory.load8(0x17FC3), 0x90);
    EXPECT_EQ(memory.load8(0x17FC4), 0x90);
    EXPECT_EQ(memory.load8(0x17FC5), 0x90);
}

TEST_F(MachineTest, jp_FF8Fh)
{
    // Initial CPU State
    cpu.set_ax(0x923F);
    cpu.set_bx(0x78AC);
    cpu.set_cx(0xCC32);
    cpu.set_dx(0x5214);
    cpu.set_cs(0x1708);
    cpu.set_ss(0x3AD7);
    cpu.set_ds(0xED1F);
    cpu.set_es(0x3264);
    cpu.set_sp(0x7E20);
    cpu.set_bp(0xCC57);
    cpu.set_si(0x68AC);
    cpu.set_di(0x68BF);
    cpu.set_ip(0xE7B1);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x25831, 0x7A);
    machine.mem_store_byte(0x25832, 0x8D);
    machine.mem_store_byte(0x25833, 0x90);
    machine.mem_store_byte(0x25834, 0x90);
    machine.mem_store_byte(0x25835, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE7B3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x25831), 0x7A);
    EXPECT_EQ(memory.load8(0x25832), 0x8D);
    EXPECT_EQ(memory.load8(0x25833), 0x90);
    EXPECT_EQ(memory.load8(0x25834), 0x90);
    EXPECT_EQ(memory.load8(0x25835), 0x90);
}

TEST_F(MachineTest, jp_FFBFh)
{
    // Initial CPU State
    cpu.set_ax(0x02F3);
    cpu.set_bx(0xF8CC);
    cpu.set_cx(0x8B4A);
    cpu.set_dx(0x9DB8);
    cpu.set_cs(0x57CB);
    cpu.set_ss(0x0B10);
    cpu.set_ds(0x2BB8);
    cpu.set_es(0x0777);
    cpu.set_sp(0xDA54);
    cpu.set_bp(0x4352);
    cpu.set_si(0xFC09);
    cpu.set_di(0x0AE8);
    cpu.set_ip(0x64AE);
    cpu.set_flags(0xF053);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5E15E, 0x6A);
    machine.mem_store_byte(0x5E15F, 0xBD);
    machine.mem_store_byte(0x5E160, 0x90);
    machine.mem_store_byte(0x5E161, 0x90);
    machine.mem_store_byte(0x5E162, 0x90);
    machine.mem_store_byte(0x5E163, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x64B0);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5E15E), 0x6A);
    EXPECT_EQ(memory.load8(0x5E15F), 0xBD);
    EXPECT_EQ(memory.load8(0x5E160), 0x90);
    EXPECT_EQ(memory.load8(0x5E161), 0x90);
    EXPECT_EQ(memory.load8(0x5E162), 0x90);
    EXPECT_EQ(memory.load8(0x5E163), 0x90);
}

TEST_F(MachineTest, js_FFCDh)
{
    // Initial CPU State
    cpu.set_ax(0xBE95);
    cpu.set_bx(0xA6E1);
    cpu.set_cx(0x7088);
    cpu.set_dx(0x3431);
    cpu.set_cs(0x2B26);
    cpu.set_ss(0xF943);
    cpu.set_ds(0x631D);
    cpu.set_es(0x99E1);
    cpu.set_sp(0xFF28);
    cpu.set_bp(0x0BDC);
    cpu.set_si(0x3FCA);
    cpu.set_di(0xD73E);
    cpu.set_ip(0x44D3);
    cpu.set_flags(0xF092);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2F733, 0x78);
    machine.mem_store_byte(0x2F734, 0xCB);
    machine.mem_store_byte(0x2F735, 0x90);
    machine.mem_store_byte(0x2F736, 0x90);
    machine.mem_store_byte(0x2F737, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x44A0);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2F733), 0x78);
    EXPECT_EQ(memory.load8(0x2F734), 0xCB);
    EXPECT_EQ(memory.load8(0x2F735), 0x90);
    EXPECT_EQ(memory.load8(0x2F736), 0x90);
    EXPECT_EQ(memory.load8(0x2F737), 0x90);
}

TEST_F(MachineTest, js_FFE8h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x9EDB);
    cpu.set_cx(0xFA5A);
    cpu.set_dx(0x452B);
    cpu.set_cs(0xAD8F);
    cpu.set_ss(0xBABA);
    cpu.set_ds(0xC6F3);
    cpu.set_es(0xBBB5);
    cpu.set_sp(0x9011);
    cpu.set_bp(0xAC3F);
    cpu.set_si(0xE2D8);
    cpu.set_di(0x8229);
    cpu.set_ip(0x8B3C);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB642C, 0x68);
    machine.mem_store_byte(0xB642D, 0xE6);
    machine.mem_store_byte(0xB642E, 0x90);
    machine.mem_store_byte(0xB642F, 0x90);
    machine.mem_store_byte(0xB6430, 0x90);
    machine.mem_store_byte(0xB6431, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8B24);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB642C), 0x68);
    EXPECT_EQ(memory.load8(0xB642D), 0xE6);
    EXPECT_EQ(memory.load8(0xB642E), 0x90);
    EXPECT_EQ(memory.load8(0xB642F), 0x90);
    EXPECT_EQ(memory.load8(0xB6430), 0x90);
    EXPECT_EQ(memory.load8(0xB6431), 0x90);
}

TEST_F(MachineTest, jz_001Eh)
{
    // Initial CPU State
    cpu.set_ax(0x3B72);
    cpu.set_bx(0xEA50);
    cpu.set_cx(0xFDCA);
    cpu.set_dx(0x822D);
    cpu.set_cs(0xD670);
    cpu.set_ss(0xB904);
    cpu.set_ds(0xE635);
    cpu.set_es(0xC8CE);
    cpu.set_sp(0xDCE6);
    cpu.set_bp(0xF9B0);
    cpu.set_si(0x4141);
    cpu.set_di(0x382C);
    cpu.set_ip(0x59CD);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDC0CD, 0x64);
    machine.mem_store_byte(0xDC0CE, 0x1C);
    machine.mem_store_byte(0xDC0CF, 0x90);
    machine.mem_store_byte(0xDC0D0, 0x90);
    machine.mem_store_byte(0xDC0D1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x59CF);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDC0CD), 0x64);
    EXPECT_EQ(memory.load8(0xDC0CE), 0x1C);
    EXPECT_EQ(memory.load8(0xDC0CF), 0x90);
    EXPECT_EQ(memory.load8(0xDC0D0), 0x90);
    EXPECT_EQ(memory.load8(0xDC0D1), 0x90);
}

TEST_F(MachineTest, jz_FF8Ah)
{
    // Initial CPU State
    cpu.set_ax(0xE671);
    cpu.set_bx(0x8838);
    cpu.set_cx(0x2F58);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x68D8);
    cpu.set_ss(0x34BA);
    cpu.set_ds(0x8526);
    cpu.set_es(0x2DD8);
    cpu.set_sp(0x44A3);
    cpu.set_bp(0x9453);
    cpu.set_si(0xA600);
    cpu.set_di(0x9EA0);
    cpu.set_ip(0xA017);
    cpu.set_flags(0xF802);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x72D97, 0x74);
    machine.mem_store_byte(0x72D98, 0x88);
    machine.mem_store_byte(0x72D99, 0x90);
    machine.mem_store_byte(0x72D9A, 0x90);
    machine.mem_store_byte(0x72D9B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA019);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x72D97), 0x74);
    EXPECT_EQ(memory.load8(0x72D98), 0x88);
    EXPECT_EQ(memory.load8(0x72D99), 0x90);
    EXPECT_EQ(memory.load8(0x72D9A), 0x90);
    EXPECT_EQ(memory.load8(0x72D9B), 0x90);
}
