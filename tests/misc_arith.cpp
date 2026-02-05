#include "fixture.h"

// Tests: aaa, aad, aam, aas, cbw, cwd, xlat, salc, daa, das

TEST_F(MachineTest, aaa)
{
    // Initial CPU State
    cpu.set_ax(0x137F);
    cpu.set_bx(0x46C1);
    cpu.set_cx(0x5B46);
    cpu.set_dx(0x2A7D);
    cpu.set_cs(0x9415);
    cpu.set_ss(0xD7A9);
    cpu.set_ds(0xE1FA);
    cpu.set_es(0x7764);
    cpu.set_sp(0xE64F);
    cpu.set_bp(0x4A65);
    cpu.set_si(0xC51E);
    cpu.set_di(0x04BA);
    cpu.set_ip(0xDE6F);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA1FBF, 0x37);
    machine.mem_store_byte(0xA1FC0, 0x90);
    machine.mem_store_byte(0xA1FC1, 0x90);
    machine.mem_store_byte(0xA1FC2, 0x90);
    machine.mem_store_byte(0xA1FC3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1405);
    EXPECT_EQ(cpu.get_ip(), 0xDE70);
    EXPECT_EQ(cpu.get_flags(), 0xF893);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA1FBF), 0x37);
    EXPECT_EQ(memory.load8(0xA1FC0), 0x90);
    EXPECT_EQ(memory.load8(0xA1FC1), 0x90);
    EXPECT_EQ(memory.load8(0xA1FC2), 0x90);
    EXPECT_EQ(memory.load8(0xA1FC3), 0x90);
}


TEST_F(MachineTest, aad_68h)
{
    // Initial CPU State
    cpu.set_ax(0x2E73);
    cpu.set_bx(0x7E52);
    cpu.set_cx(0x353E);
    cpu.set_dx(0xD098);
    cpu.set_cs(0xD21A);
    cpu.set_ss(0xB781);
    cpu.set_ds(0xC589);
    cpu.set_es(0x24B3);
    cpu.set_sp(0x96DA);
    cpu.set_bp(0xE1C5);
    cpu.set_si(0xD404);
    cpu.set_di(0x3262);
    cpu.set_ip(0x88EC);
    cpu.set_flags(0xFC56);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDAA8C, 0xD5);
    machine.mem_store_byte(0xDAA8D, 0x68);
    machine.mem_store_byte(0xDAA8E, 0x90);
    machine.mem_store_byte(0xDAA8F, 0x90);
    machine.mem_store_byte(0xDAA90, 0x90);
    machine.mem_store_byte(0xDAA91, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0023);
    EXPECT_EQ(cpu.get_ip(), 0x88EE);
    EXPECT_EQ(cpu.get_flags(), 0xF403);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDAA8C), 0xD5);
    EXPECT_EQ(memory.load8(0xDAA8D), 0x68);
    EXPECT_EQ(memory.load8(0xDAA8E), 0x90);
    EXPECT_EQ(memory.load8(0xDAA8F), 0x90);
    EXPECT_EQ(memory.load8(0xDAA90), 0x90);
    EXPECT_EQ(memory.load8(0xDAA91), 0x90);
}


TEST_F(MachineTest, aam_10h)
{
    // Initial CPU State
    cpu.set_ax(0xBD0E);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x7D82);
    cpu.set_dx(0x1347);
    cpu.set_cs(0xA79D);
    cpu.set_ss(0x2CB4);
    cpu.set_ds(0x8AEC);
    cpu.set_es(0x39A9);
    cpu.set_sp(0xE5F5);
    cpu.set_bp(0xBBFE);
    cpu.set_si(0xA6AC);
    cpu.set_di(0xEFCD);
    cpu.set_ip(0x2043);
    cpu.set_flags(0xF402);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA9A13, 0xD4);
    machine.mem_store_byte(0xA9A14, 0x10);
    machine.mem_store_byte(0xA9A15, 0x90);
    machine.mem_store_byte(0xA9A16, 0x90);
    machine.mem_store_byte(0xA9A17, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x000E);
    EXPECT_EQ(cpu.get_ip(), 0x2045);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA9A13), 0xD4);
    EXPECT_EQ(memory.load8(0xA9A14), 0x10);
    EXPECT_EQ(memory.load8(0xA9A15), 0x90);
    EXPECT_EQ(memory.load8(0xA9A16), 0x90);
    EXPECT_EQ(memory.load8(0xA9A17), 0x90);
}


TEST_F(MachineTest, aas)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x30D3);
    cpu.set_cx(0x243A);
    cpu.set_dx(0x1CED);
    cpu.set_cs(0x55D1);
    cpu.set_ss(0x9B98);
    cpu.set_ds(0x2FF1);
    cpu.set_es(0xACD7);
    cpu.set_sp(0x9EB5);
    cpu.set_bp(0x0000);
    cpu.set_si(0x900C);
    cpu.set_di(0x0000);
    cpu.set_ip(0xA09A);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5FDAA, 0x3F);
    machine.mem_store_byte(0x5FDAB, 0x90);
    machine.mem_store_byte(0x5FDAC, 0x90);
    machine.mem_store_byte(0x5FDAD, 0x90);
    machine.mem_store_byte(0x5FDAE, 0x90);
    machine.mem_store_byte(0x5FDAF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA09B);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5FDAA), 0x3F);
    EXPECT_EQ(memory.load8(0x5FDAB), 0x90);
    EXPECT_EQ(memory.load8(0x5FDAC), 0x90);
    EXPECT_EQ(memory.load8(0x5FDAD), 0x90);
    EXPECT_EQ(memory.load8(0x5FDAE), 0x90);
    EXPECT_EQ(memory.load8(0x5FDAF), 0x90);
}


TEST_F(MachineTest, cbw)
{
    // Initial CPU State
    cpu.set_ax(0xA612);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x0442);
    cpu.set_dx(0xEF59);
    cpu.set_cs(0xF79F);
    cpu.set_ss(0xD1E5);
    cpu.set_ds(0x25A7);
    cpu.set_es(0x0775);
    cpu.set_sp(0x21C3);
    cpu.set_bp(0xE9AE);
    cpu.set_si(0x7573);
    cpu.set_di(0xF0BD);
    cpu.set_ip(0x7111);
    cpu.set_flags(0xF453);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFEB01, 0x98);
    machine.mem_store_byte(0xFEB02, 0x90);
    machine.mem_store_byte(0xFEB03, 0x90);
    machine.mem_store_byte(0xFEB04, 0x90);
    machine.mem_store_byte(0xFEB05, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0012);
    EXPECT_EQ(cpu.get_ip(), 0x7112);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFEB01), 0x98);
    EXPECT_EQ(memory.load8(0xFEB02), 0x90);
    EXPECT_EQ(memory.load8(0xFEB03), 0x90);
    EXPECT_EQ(memory.load8(0xFEB04), 0x90);
    EXPECT_EQ(memory.load8(0xFEB05), 0x90);
}


TEST_F(MachineTest, cwd)
{
    // Initial CPU State
    cpu.set_ax(0x1044);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x03CA);
    cpu.set_dx(0x3F96);
    cpu.set_cs(0xFBB3);
    cpu.set_ss(0xB611);
    cpu.set_ds(0x78DD);
    cpu.set_es(0x0E8D);
    cpu.set_sp(0xD1D2);
    cpu.set_bp(0xBC1F);
    cpu.set_si(0xDF60);
    cpu.set_di(0x4138);
    cpu.set_ip(0xA38B);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05EBB, 0x99);
    machine.mem_store_byte(0x05EBC, 0x90);
    machine.mem_store_byte(0x05EBD, 0x90);
    machine.mem_store_byte(0x05EBE, 0x90);
    machine.mem_store_byte(0x05EBF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0xA38C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x05EBB), 0x99);
    EXPECT_EQ(memory.load8(0x05EBC), 0x90);
    EXPECT_EQ(memory.load8(0x05EBD), 0x90);
    EXPECT_EQ(memory.load8(0x05EBE), 0x90);
    EXPECT_EQ(memory.load8(0x05EBF), 0x90);
}


TEST_F(MachineTest, daa)
{
    // Initial CPU State
    cpu.set_ax(0xC8FA);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x7B9C);
    cpu.set_dx(0xFE2D);
    cpu.set_cs(0x8FE2);
    cpu.set_ss(0x4188);
    cpu.set_ds(0x6616);
    cpu.set_es(0x4F1C);
    cpu.set_sp(0x604B);
    cpu.set_bp(0xBC7A);
    cpu.set_si(0x8203);
    cpu.set_di(0xC301);
    cpu.set_ip(0x5BD7);
    cpu.set_flags(0xF802);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x959F7, 0x27);
    machine.mem_store_byte(0x959F8, 0x90);
    machine.mem_store_byte(0x959F9, 0x90);
    machine.mem_store_byte(0x959FA, 0x90);
    machine.mem_store_byte(0x959FB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xC860);
    EXPECT_EQ(cpu.get_ip(), 0x5BD8);
    EXPECT_EQ(cpu.get_flags(), 0xF017);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x959F7), 0x27);
    EXPECT_EQ(memory.load8(0x959F8), 0x90);
    EXPECT_EQ(memory.load8(0x959F9), 0x90);
    EXPECT_EQ(memory.load8(0x959FA), 0x90);
    EXPECT_EQ(memory.load8(0x959FB), 0x90);
}


TEST_F(MachineTest, das)
{
    // Initial CPU State
    cpu.set_ax(0x466B);
    cpu.set_bx(0x2229);
    cpu.set_cx(0xB412);
    cpu.set_dx(0xE33F);
    cpu.set_cs(0x262C);
    cpu.set_ss(0x7617);
    cpu.set_ds(0x6E2C);
    cpu.set_es(0xE8F1);
    cpu.set_sp(0xD316);
    cpu.set_bp(0xB2F0);
    cpu.set_si(0xED31);
    cpu.set_di(0x1166);
    cpu.set_ip(0x46A3);
    cpu.set_flags(0xF887);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2A963, 0x2F);
    machine.mem_store_byte(0x2A964, 0x90);
    machine.mem_store_byte(0x2A965, 0x90);
    machine.mem_store_byte(0x2A966, 0x90);
    machine.mem_store_byte(0x2A967, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x4605);
    EXPECT_EQ(cpu.get_ip(), 0x46A4);
    EXPECT_EQ(cpu.get_flags(), 0xF017);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2A963), 0x2F);
    EXPECT_EQ(memory.load8(0x2A964), 0x90);
    EXPECT_EQ(memory.load8(0x2A965), 0x90);
    EXPECT_EQ(memory.load8(0x2A966), 0x90);
    EXPECT_EQ(memory.load8(0x2A967), 0x90);
}


TEST_F(MachineTest, salc)
{
    // Initial CPU State
    cpu.set_ax(0x8147);
    cpu.set_bx(0xE9A4);
    cpu.set_cx(0xCF26);
    cpu.set_dx(0x0CCF);
    cpu.set_cs(0x6ACC);
    cpu.set_ss(0x374E);
    cpu.set_ds(0x1734);
    cpu.set_es(0x4784);
    cpu.set_sp(0xC55E);
    cpu.set_bp(0xBA16);
    cpu.set_si(0xF6FD);
    cpu.set_di(0x331B);
    cpu.set_ip(0x715D);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x71E1D, 0x2E);
    machine.mem_store_byte(0x71E1E, 0xD6);
    machine.mem_store_byte(0x71E1F, 0x90);
    machine.mem_store_byte(0x71E20, 0x90);
    machine.mem_store_byte(0x71E21, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x81FF);
    EXPECT_EQ(cpu.get_ip(), 0x715F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x71E1D), 0x2E);
    EXPECT_EQ(memory.load8(0x71E1E), 0xD6);
    EXPECT_EQ(memory.load8(0x71E1F), 0x90);
    EXPECT_EQ(memory.load8(0x71E20), 0x90);
    EXPECT_EQ(memory.load8(0x71E21), 0x90);
}


TEST_F(MachineTest, xlat)
{
    // Initial CPU State
    cpu.set_ax(0x22EA);
    cpu.set_bx(0xD7AD);
    cpu.set_cx(0x2436);
    cpu.set_dx(0x1703);
    cpu.set_cs(0x0EF2);
    cpu.set_ss(0x2C3D);
    cpu.set_ds(0xD389);
    cpu.set_es(0x63C0);
    cpu.set_sp(0x3746);
    cpu.set_bp(0xCE17);
    cpu.set_si(0x0000);
    cpu.set_di(0x0000);
    cpu.set_ip(0x0364);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0F284, 0xD7);
    machine.mem_store_byte(0x0F285, 0x90);
    machine.mem_store_byte(0x0F286, 0x90);
    machine.mem_store_byte(0x0F287, 0x90);
    machine.mem_store_byte(0x0F288, 0x90);
    machine.mem_store_byte(0x0F289, 0x90);
    machine.mem_store_byte(0xE1127, 0x5B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x225B);
    EXPECT_EQ(cpu.get_ip(), 0x0365);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0F284), 0xD7);
    EXPECT_EQ(memory.load8(0x0F285), 0x90);
    EXPECT_EQ(memory.load8(0x0F286), 0x90);
    EXPECT_EQ(memory.load8(0x0F287), 0x90);
    EXPECT_EQ(memory.load8(0x0F288), 0x90);
    EXPECT_EQ(memory.load8(0x0F289), 0x90);
    EXPECT_EQ(memory.load8(0xE1127), 0x5B);
}
