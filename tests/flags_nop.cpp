#include "fixture.h"

// Tests: pushf, popf, lahf, sahf, cli, sti, clc, stc, cmc, cld, std, nop

TEST_F(MachineTest, clc)
{
    // Initial CPU State
    cpu.set_ax(0x658C);
    cpu.set_bx(0xD053);
    cpu.set_cx(0xDA20);
    cpu.set_dx(0x42CB);
    cpu.set_cs(0x33DE);
    cpu.set_ss(0xDC21);
    cpu.set_ds(0xF76A);
    cpu.set_es(0x26D2);
    cpu.set_sp(0x17DE);
    cpu.set_bp(0x70BC);
    cpu.set_si(0xEDF0);
    cpu.set_di(0x81D6);
    cpu.set_ip(0xF13E);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x42F1E, 0xF8);
    machine.mem_store_byte(0x42F1F, 0x90);
    machine.mem_store_byte(0x42F20, 0x90);
    machine.mem_store_byte(0x42F21, 0x90);
    machine.mem_store_byte(0x42F22, 0x90);
    machine.mem_store_byte(0x42F23, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF13F);
    EXPECT_EQ(cpu.get_flags(), 0xF816);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x42F1E), 0xF8);
    EXPECT_EQ(memory.load8(0x42F1F), 0x90);
    EXPECT_EQ(memory.load8(0x42F20), 0x90);
    EXPECT_EQ(memory.load8(0x42F21), 0x90);
    EXPECT_EQ(memory.load8(0x42F22), 0x90);
    EXPECT_EQ(memory.load8(0x42F23), 0x90);
}

TEST_F(MachineTest, cld)
{
    // Initial CPU State
    cpu.set_ax(0x0258);
    cpu.set_bx(0x9026);
    cpu.set_cx(0xA604);
    cpu.set_dx(0x95E4);
    cpu.set_cs(0x82C8);
    cpu.set_ss(0x8A98);
    cpu.set_ds(0xEF39);
    cpu.set_es(0xC214);
    cpu.set_sp(0x2EEC);
    cpu.set_bp(0xC3AA);
    cpu.set_si(0x7FCA);
    cpu.set_di(0x5BBF);
    cpu.set_ip(0xFB1E);
    cpu.set_flags(0xF406);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9279E, 0xFC);
    machine.mem_store_byte(0x9279F, 0x90);
    machine.mem_store_byte(0x927A0, 0x90);
    machine.mem_store_byte(0x927A1, 0x90);
    machine.mem_store_byte(0x927A2, 0x90);
    machine.mem_store_byte(0x927A3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xFB1F);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9279E), 0xFC);
    EXPECT_EQ(memory.load8(0x9279F), 0x90);
    EXPECT_EQ(memory.load8(0x927A0), 0x90);
    EXPECT_EQ(memory.load8(0x927A1), 0x90);
    EXPECT_EQ(memory.load8(0x927A2), 0x90);
    EXPECT_EQ(memory.load8(0x927A3), 0x90);
}

TEST_F(MachineTest, cli)
{
    // Initial CPU State
    cpu.set_ax(0x941E);
    cpu.set_bx(0xC4B9);
    cpu.set_cx(0x7206);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xE7A3);
    cpu.set_ss(0x73C4);
    cpu.set_ds(0x9456);
    cpu.set_es(0xD5E8);
    cpu.set_sp(0x6C26);
    cpu.set_bp(0xB31F);
    cpu.set_si(0x28FF);
    cpu.set_di(0xC29F);
    cpu.set_ip(0x01AC);
    cpu.set_flags(0xF8C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE7BDC, 0xFA);
    machine.mem_store_byte(0xE7BDD, 0x90);
    machine.mem_store_byte(0xE7BDE, 0x90);
    machine.mem_store_byte(0xE7BDF, 0x90);
    machine.mem_store_byte(0xE7BE0, 0x90);
    machine.mem_store_byte(0xE7BE1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x01AD);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE7BDC), 0xFA);
    EXPECT_EQ(memory.load8(0xE7BDD), 0x90);
    EXPECT_EQ(memory.load8(0xE7BDE), 0x90);
    EXPECT_EQ(memory.load8(0xE7BDF), 0x90);
    EXPECT_EQ(memory.load8(0xE7BE0), 0x90);
    EXPECT_EQ(memory.load8(0xE7BE1), 0x90);
}

TEST_F(MachineTest, cmc)
{
    // Initial CPU State
    cpu.set_ax(0xE551);
    cpu.set_bx(0x4626);
    cpu.set_cx(0x0000);
    cpu.set_dx(0xD717);
    cpu.set_cs(0x050F);
    cpu.set_ss(0xFBF4);
    cpu.set_ds(0x70CD);
    cpu.set_es(0xE810);
    cpu.set_sp(0x7876);
    cpu.set_bp(0xF73B);
    cpu.set_si(0xD412);
    cpu.set_di(0x1AFF);
    cpu.set_ip(0xDD5B);
    cpu.set_flags(0xFC17);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x12E4B, 0xF5);
    machine.mem_store_byte(0x12E4C, 0x90);
    machine.mem_store_byte(0x12E4D, 0x90);
    machine.mem_store_byte(0x12E4E, 0x90);
    machine.mem_store_byte(0x12E4F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDD5C);
    EXPECT_EQ(cpu.get_flags(), 0xFC16);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x12E4B), 0xF5);
    EXPECT_EQ(memory.load8(0x12E4C), 0x90);
    EXPECT_EQ(memory.load8(0x12E4D), 0x90);
    EXPECT_EQ(memory.load8(0x12E4E), 0x90);
    EXPECT_EQ(memory.load8(0x12E4F), 0x90);
}

TEST_F(MachineTest, lahf)
{
    // Initial CPU State
    cpu.set_ax(0x12F1);
    cpu.set_bx(0x88AE);
    cpu.set_cx(0x51E4);
    cpu.set_dx(0x68E9);
    cpu.set_cs(0x387D);
    cpu.set_ss(0x07DE);
    cpu.set_ds(0xC217);
    cpu.set_es(0x1D98);
    cpu.set_sp(0xA8DA);
    cpu.set_bp(0x0000);
    cpu.set_si(0x4988);
    cpu.set_di(0x7554);
    cpu.set_ip(0x75D8);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3FDA8, 0x9F);
    machine.mem_store_byte(0x3FDA9, 0x90);
    machine.mem_store_byte(0x3FDAA, 0x90);
    machine.mem_store_byte(0x3FDAB, 0x90);
    machine.mem_store_byte(0x3FDAC, 0x90);
    machine.mem_store_byte(0x3FDAD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x13F1);
    EXPECT_EQ(cpu.get_ip(), 0x75D9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3FDA8), 0x9F);
    EXPECT_EQ(memory.load8(0x3FDA9), 0x90);
    EXPECT_EQ(memory.load8(0x3FDAA), 0x90);
    EXPECT_EQ(memory.load8(0x3FDAB), 0x90);
    EXPECT_EQ(memory.load8(0x3FDAC), 0x90);
    EXPECT_EQ(memory.load8(0x3FDAD), 0x90);
}

TEST_F(MachineTest, nop)
{
    // Initial CPU State
    cpu.set_ax(0x552F);
    cpu.set_bx(0xA257);
    cpu.set_cx(0x4E86);
    cpu.set_dx(0x3581);
    cpu.set_cs(0x9EAA);
    cpu.set_ss(0x1A63);
    cpu.set_ds(0xD6D8);
    cpu.set_es(0x5559);
    cpu.set_sp(0x3DA4);
    cpu.set_bp(0x1410);
    cpu.set_si(0x55A4);
    cpu.set_di(0x0000);
    cpu.set_ip(0xC7D5);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAB275, 0x90);
    machine.mem_store_byte(0xAB276, 0x90);
    machine.mem_store_byte(0xAB277, 0x90);
    machine.mem_store_byte(0xAB278, 0x90);
    machine.mem_store_byte(0xAB279, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC7D6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAB275), 0x90);
    EXPECT_EQ(memory.load8(0xAB276), 0x90);
    EXPECT_EQ(memory.load8(0xAB277), 0x90);
    EXPECT_EQ(memory.load8(0xAB278), 0x90);
    EXPECT_EQ(memory.load8(0xAB279), 0x90);
}

TEST_F(MachineTest, popf)
{
    // Initial CPU State
    cpu.set_ax(0x74D0);
    cpu.set_bx(0xCAA0);
    cpu.set_cx(0x34E0);
    cpu.set_dx(0x058D);
    cpu.set_cs(0x262C);
    cpu.set_ss(0xAC8D);
    cpu.set_ds(0xFCD5);
    cpu.set_es(0x6A94);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x4721);
    cpu.set_si(0x5DA5);
    cpu.set_di(0x0000);
    cpu.set_ip(0x46A3);
    cpu.set_flags(0xF4C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2A963, 0x9D);
    machine.mem_store_byte(0x2A964, 0x90);
    machine.mem_store_byte(0x2A965, 0x90);
    machine.mem_store_byte(0x2A966, 0x90);
    machine.mem_store_byte(0x2A967, 0x90);
    machine.mem_store_byte(0xAC8D0, 0xAA);
    machine.mem_store_byte(0xAC8D1, 0xD4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x0002);
    EXPECT_EQ(cpu.get_ip(), 0x46A4);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2A963), 0x9D);
    EXPECT_EQ(memory.load8(0x2A964), 0x90);
    EXPECT_EQ(memory.load8(0x2A965), 0x90);
    EXPECT_EQ(memory.load8(0x2A966), 0x90);
    EXPECT_EQ(memory.load8(0x2A967), 0x90);
    EXPECT_EQ(memory.load8(0xAC8D0), 0xAA);
    EXPECT_EQ(memory.load8(0xAC8D1), 0xD4);
}

TEST_F(MachineTest, pushf)
{
    // Initial CPU State
    cpu.set_ax(0x88AE);
    cpu.set_bx(0x0C02);
    cpu.set_cx(0xF098);
    cpu.set_dx(0xA502);
    cpu.set_cs(0x7EBF);
    cpu.set_ss(0xC1D8);
    cpu.set_ds(0xDE8E);
    cpu.set_es(0xD723);
    cpu.set_sp(0x7000);
    cpu.set_bp(0x644E);
    cpu.set_si(0x9DDF);
    cpu.set_di(0x251A);
    cpu.set_ip(0x96E9);
    cpu.set_flags(0xF8D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x882D9, 0x9C);
    machine.mem_store_byte(0x882DA, 0x90);
    machine.mem_store_byte(0x882DB, 0x90);
    machine.mem_store_byte(0x882DC, 0x90);
    machine.mem_store_byte(0x882DD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x6FFE);
    EXPECT_EQ(cpu.get_ip(), 0x96EA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x882D9), 0x9C);
    EXPECT_EQ(memory.load8(0x882DA), 0x90);
    EXPECT_EQ(memory.load8(0x882DB), 0x90);
    EXPECT_EQ(memory.load8(0x882DC), 0x90);
    EXPECT_EQ(memory.load8(0x882DD), 0x90);
    EXPECT_EQ(memory.load8(0xC8D7E), 0xD6);
    EXPECT_EQ(memory.load8(0xC8D7F), 0xF8);
}

TEST_F(MachineTest, sahf)
{
    // Initial CPU State
    cpu.set_ax(0xAF7D);
    cpu.set_bx(0x8460);
    cpu.set_cx(0x7EAE);
    cpu.set_dx(0xDA9B);
    cpu.set_cs(0xF4F5);
    cpu.set_ss(0xB8DD);
    cpu.set_ds(0x92A2);
    cpu.set_es(0xC0D0);
    cpu.set_sp(0x3CE7);
    cpu.set_bp(0x4CA6);
    cpu.set_si(0x2F18);
    cpu.set_di(0x7EFA);
    cpu.set_ip(0x3E76);
    cpu.set_flags(0xFCD3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8DC6, 0x9E);
    machine.mem_store_byte(0xF8DC7, 0x90);
    machine.mem_store_byte(0xF8DC8, 0x90);
    machine.mem_store_byte(0xF8DC9, 0x90);
    machine.mem_store_byte(0xF8DCA, 0x90);
    machine.mem_store_byte(0xF8DCB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3E77);
    EXPECT_EQ(cpu.get_flags(), 0xFC87);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF8DC6), 0x9E);
    EXPECT_EQ(memory.load8(0xF8DC7), 0x90);
    EXPECT_EQ(memory.load8(0xF8DC8), 0x90);
    EXPECT_EQ(memory.load8(0xF8DC9), 0x90);
    EXPECT_EQ(memory.load8(0xF8DCA), 0x90);
    EXPECT_EQ(memory.load8(0xF8DCB), 0x90);
}

TEST_F(MachineTest, stc)
{
    // Initial CPU State
    cpu.set_ax(0x2D02);
    cpu.set_bx(0x8A55);
    cpu.set_cx(0x885C);
    cpu.set_dx(0xE808);
    cpu.set_cs(0xD3B9);
    cpu.set_ss(0xC5FF);
    cpu.set_ds(0x0D9D);
    cpu.set_es(0x72D9);
    cpu.set_sp(0xE933);
    cpu.set_bp(0xDC2D);
    cpu.set_si(0x4978);
    cpu.set_di(0xE70B);
    cpu.set_ip(0x5332);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD8EC2, 0xF9);
    machine.mem_store_byte(0xD8EC3, 0x90);
    machine.mem_store_byte(0xD8EC4, 0x90);
    machine.mem_store_byte(0xD8EC5, 0x90);
    machine.mem_store_byte(0xD8EC6, 0x90);
    machine.mem_store_byte(0xD8EC7, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5333);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD8EC2), 0xF9);
    EXPECT_EQ(memory.load8(0xD8EC3), 0x90);
    EXPECT_EQ(memory.load8(0xD8EC4), 0x90);
    EXPECT_EQ(memory.load8(0xD8EC5), 0x90);
    EXPECT_EQ(memory.load8(0xD8EC6), 0x90);
    EXPECT_EQ(memory.load8(0xD8EC7), 0x90);
}

TEST_F(MachineTest, std)
{
    // Initial CPU State
    cpu.set_ax(0xAE6C);
    cpu.set_bx(0xB8FE);
    cpu.set_cx(0x2F18);
    cpu.set_dx(0x649E);
    cpu.set_cs(0x8D7D);
    cpu.set_ss(0xA386);
    cpu.set_ds(0x53E1);
    cpu.set_es(0x5C02);
    cpu.set_sp(0xDF3D);
    cpu.set_bp(0x5A11);
    cpu.set_si(0x21C6);
    cpu.set_di(0x0F46);
    cpu.set_ip(0x93FE);
    cpu.set_flags(0xF053);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x96BCE, 0xFD);
    machine.mem_store_byte(0x96BCF, 0x90);
    machine.mem_store_byte(0x96BD0, 0x90);
    machine.mem_store_byte(0x96BD1, 0x90);
    machine.mem_store_byte(0x96BD2, 0x90);
    machine.mem_store_byte(0x96BD3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x93FF);
    EXPECT_EQ(cpu.get_flags(), 0xF453);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x96BCE), 0xFD);
    EXPECT_EQ(memory.load8(0x96BCF), 0x90);
    EXPECT_EQ(memory.load8(0x96BD0), 0x90);
    EXPECT_EQ(memory.load8(0x96BD1), 0x90);
    EXPECT_EQ(memory.load8(0x96BD2), 0x90);
    EXPECT_EQ(memory.load8(0x96BD3), 0x90);
}

TEST_F(MachineTest, sti)
{
    // Initial CPU State
    cpu.set_ax(0xC3FF);
    cpu.set_bx(0x4947);
    cpu.set_cx(0xA548);
    cpu.set_dx(0x7F43);
    cpu.set_cs(0xB0C3);
    cpu.set_ss(0x4D20);
    cpu.set_ds(0x5580);
    cpu.set_es(0x7CEC);
    cpu.set_sp(0xE5CE);
    cpu.set_bp(0xD2BF);
    cpu.set_si(0x9DA5);
    cpu.set_di(0x9BFD);
    cpu.set_ip(0x19D3);
    cpu.set_flags(0xFC03);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB2603, 0xFB);
    machine.mem_store_byte(0xB2604, 0x90);
    machine.mem_store_byte(0xB2605, 0x90);
    machine.mem_store_byte(0xB2606, 0x90);
    machine.mem_store_byte(0xB2607, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x19D4);
    EXPECT_EQ(cpu.get_flags(), 0xFE03);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB2603), 0xFB);
    EXPECT_EQ(memory.load8(0xB2604), 0x90);
    EXPECT_EQ(memory.load8(0xB2605), 0x90);
    EXPECT_EQ(memory.load8(0xB2606), 0x90);
    EXPECT_EQ(memory.load8(0xB2607), 0x90);
}
