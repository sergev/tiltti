#include "fixture.h"

//
// push ax
//
TEST_F(MachineTest, push_ax)
{
    // Initial CPU State
    cpu.set_ax(0x51BC);
    cpu.set_bx(0x80D8);
    cpu.set_cx(0xB7B2);
    cpu.set_dx(0xBA33);
    cpu.set_cs(0x7A01);
    cpu.set_ss(0x9273);
    cpu.set_ds(0x3A31);
    cpu.set_es(0x3EEC);
    cpu.set_sp(0x476B);
    cpu.set_bp(0xDEA6);
    cpu.set_si(0x45C6);
    cpu.set_di(0x64DE);
    cpu.set_ip(0x8730);
    cpu.set_flags(0xF4C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x82740, 0x50);
    machine.mem_store_byte(0x82741, 0x90);
    machine.mem_store_byte(0x82742, 0x90);
    machine.mem_store_byte(0x82743, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x4769);
    EXPECT_EQ(cpu.get_ip(), 0x8731);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x96E99), 0xBC);
    EXPECT_EQ(memory.load8(0x96E9A), 0x51);
}

//
// push bp
//
TEST_F(MachineTest, push_bp)
{
    // Initial CPU State
    cpu.set_ax(0xD71C);
    cpu.set_bx(0x925F);
    cpu.set_cx(0xE9CC);
    cpu.set_dx(0xBB0F);
    cpu.set_cs(0x2913);
    cpu.set_ss(0x59A2);
    cpu.set_ds(0x2D39);
    cpu.set_es(0x68AD);
    cpu.set_sp(0xC6B6);
    cpu.set_bp(0x41C7);
    cpu.set_si(0x6E3B);
    cpu.set_di(0x65BF);
    cpu.set_ip(0x3B8C);
    cpu.set_flags(0xF892);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2CCBC, 0x55);
    machine.mem_store_byte(0x2CCBD, 0x90);
    machine.mem_store_byte(0x2CCBE, 0x90);
    machine.mem_store_byte(0x2CCBF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xC6B4);
    EXPECT_EQ(cpu.get_ip(), 0x3B8D);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x660D4), 0xC7);
    EXPECT_EQ(memory.load8(0x660D5), 0x41);
}

//
// push bx
//
TEST_F(MachineTest, push_bx)
{
    // Initial CPU State
    cpu.set_ax(0xEBB4);
    cpu.set_bx(0x4503);
    cpu.set_cx(0xD3B2);
    cpu.set_dx(0xA958);
    cpu.set_cs(0x57EA);
    cpu.set_ss(0xF94D);
    cpu.set_ds(0x6909);
    cpu.set_es(0x41D5);
    cpu.set_sp(0x698D);
    cpu.set_bp(0xA3CA);
    cpu.set_si(0x9F98);
    cpu.set_di(0x09A5);
    cpu.set_ip(0x8D4E);
    cpu.set_flags(0xF413);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x60BEE, 0x53);
    machine.mem_store_byte(0x60BEF, 0x90);
    machine.mem_store_byte(0x60BF0, 0x90);
    machine.mem_store_byte(0x60BF1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x698B);
    EXPECT_EQ(cpu.get_ip(), 0x8D4F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFFE5B), 0x03);
    EXPECT_EQ(memory.load8(0xFFE5C), 0x45);
}

//
// push cs
//
TEST_F(MachineTest, push_cs)
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
    machine.mem_store_byte(0xCBBB0, 0x0E);
    machine.mem_store_byte(0xCBBB1, 0x90);
    machine.mem_store_byte(0xCBBB2, 0x90);
    machine.mem_store_byte(0xCBBB3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x0A17);
    EXPECT_EQ(cpu.get_ip(), 0x4E41);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3E817), 0xD7);
    EXPECT_EQ(memory.load8(0x3E818), 0xC6);
}

//
// push cx
//
TEST_F(MachineTest, push_cx)
{
    // Initial CPU State
    cpu.set_ax(0x1D79);
    cpu.set_bx(0x43AB);
    cpu.set_cx(0xE746);
    cpu.set_dx(0x478F);
    cpu.set_cs(0x88CE);
    cpu.set_ss(0x4BF4);
    cpu.set_ds(0x90A8);
    cpu.set_es(0x5EA2);
    cpu.set_sp(0x84D8);
    cpu.set_bp(0xDB0C);
    cpu.set_si(0x5EA0);
    cpu.set_di(0x4091);
    cpu.set_ip(0xD79B);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9647B, 0x51);
    machine.mem_store_byte(0x9647C, 0x90);
    machine.mem_store_byte(0x9647D, 0x90);
    machine.mem_store_byte(0x9647E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x84D6);
    EXPECT_EQ(cpu.get_ip(), 0xD79C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x54416), 0x46);
    EXPECT_EQ(memory.load8(0x54417), 0xE7);
}

//
// push di
//
TEST_F(MachineTest, push_di)
{
    // Initial CPU State
    cpu.set_ax(0x91D5);
    cpu.set_bx(0x5197);
    cpu.set_cx(0x0990);
    cpu.set_dx(0xF1A2);
    cpu.set_cs(0x1D04);
    cpu.set_ss(0xE6DE);
    cpu.set_ds(0xCC10);
    cpu.set_es(0x3701);
    cpu.set_sp(0x4ED2);
    cpu.set_bp(0x53EC);
    cpu.set_si(0xC013);
    cpu.set_di(0xDA21);
    cpu.set_ip(0x02A2);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1D2E2, 0x57);
    machine.mem_store_byte(0x1D2E3, 0x90);
    machine.mem_store_byte(0x1D2E4, 0x90);
    machine.mem_store_byte(0x1D2E5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x4ED0);
    EXPECT_EQ(cpu.get_ip(), 0x02A3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEBCB0), 0x21);
    EXPECT_EQ(memory.load8(0xEBCB1), 0xDA);
}

//
// push ds
//
TEST_F(MachineTest, push_ds)
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
    machine.mem_store_byte(0xD9B1B, 0x1E);
    machine.mem_store_byte(0xD9B1C, 0x90);
    machine.mem_store_byte(0xD9B1D, 0x90);
    machine.mem_store_byte(0xD9B1E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xA6B5);
    EXPECT_EQ(cpu.get_ip(), 0x1BCC);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x87A55), 0xC1);
    EXPECT_EQ(memory.load8(0x87A56), 0xDA);
}

//
// push dx
//
TEST_F(MachineTest, push_dx)
{
    // Initial CPU State
    cpu.set_ax(0xEE28);
    cpu.set_bx(0xD478);
    cpu.set_cx(0x81B0);
    cpu.set_dx(0xAFC7);
    cpu.set_cs(0x788B);
    cpu.set_ss(0xDBEF);
    cpu.set_ds(0xB506);
    cpu.set_es(0x12AA);
    cpu.set_sp(0xF966);
    cpu.set_bp(0xFE2F);
    cpu.set_si(0x2F8B);
    cpu.set_di(0x0345);
    cpu.set_ip(0x1A84);
    cpu.set_flags(0xF887);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7A334, 0x52);
    machine.mem_store_byte(0x7A335, 0x90);
    machine.mem_store_byte(0x7A336, 0x90);
    machine.mem_store_byte(0x7A337, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xF964);
    EXPECT_EQ(cpu.get_ip(), 0x1A85);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEB854), 0xC7);
    EXPECT_EQ(memory.load8(0xEB855), 0xAF);
}

//
// push es
//
TEST_F(MachineTest, push_es)
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
    machine.mem_store_byte(0xC2A88, 0x06);
    machine.mem_store_byte(0xC2A89, 0x90);
    machine.mem_store_byte(0xC2A8A, 0x90);
    machine.mem_store_byte(0xC2A8B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x08FB);
    EXPECT_EQ(cpu.get_ip(), 0xCF29);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6B6CB), 0xE4);
    EXPECT_EQ(memory.load8(0x6B6CC), 0xC1);
}

//
// push si
//
TEST_F(MachineTest, push_si)
{
    // Initial CPU State
    cpu.set_ax(0x7B30);
    cpu.set_bx(0x114E);
    cpu.set_cx(0x2AB0);
    cpu.set_dx(0x4820);
    cpu.set_cs(0x2D8C);
    cpu.set_ss(0x3499);
    cpu.set_ds(0x0F59);
    cpu.set_es(0xF4BD);
    cpu.set_sp(0xCCDF);
    cpu.set_bp(0xB86E);
    cpu.set_si(0x9D33);
    cpu.set_di(0xB25D);
    cpu.set_ip(0xE6AE);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3BF6E, 0x56);
    machine.mem_store_byte(0x3BF6F, 0x90);
    machine.mem_store_byte(0x3BF70, 0x90);
    machine.mem_store_byte(0x3BF71, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xCCDD);
    EXPECT_EQ(cpu.get_ip(), 0xE6AF);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4166D), 0x33);
    EXPECT_EQ(memory.load8(0x4166E), 0x9D);
}

//
// push sp
//
TEST_F(MachineTest, push_sp)
{
    // Initial CPU State
    cpu.set_ax(0x83BC);
    cpu.set_bx(0xCB57);
    cpu.set_cx(0xC360);
    cpu.set_dx(0x5911);
    cpu.set_cs(0xB262);
    cpu.set_ss(0xF778);
    cpu.set_ds(0x2857);
    cpu.set_es(0xF7DC);
    cpu.set_sp(0xDD10);
    cpu.set_bp(0xD6B3);
    cpu.set_si(0x7D44);
    cpu.set_di(0x703C);
    cpu.set_ip(0xB7D6);
    cpu.set_flags(0xF4D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBDDF6, 0x54);
    machine.mem_store_byte(0xBDDF7, 0x90);
    machine.mem_store_byte(0xBDDF8, 0x90);
    machine.mem_store_byte(0xBDDF9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xDD0E);
    EXPECT_EQ(cpu.get_ip(), 0xB7D7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0548E), 0x0E);
    EXPECT_EQ(memory.load8(0x0548F), 0xDD);
}

//
// push ss
//
TEST_F(MachineTest, push_ss)
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
    machine.mem_store_byte(0x167A9, 0x16);
    machine.mem_store_byte(0x167AA, 0x90);
    machine.mem_store_byte(0x167AB, 0x90);
    machine.mem_store_byte(0x167AC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x5BCD);
    EXPECT_EQ(cpu.get_ip(), 0xAC2A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1328D), 0x6C);
    EXPECT_EQ(memory.load8(0x1328E), 0x0D);
}

//
// push word [cs:bp+di-61CAh]
//
TEST_F(MachineTest, push_word_cs_bp_di_61CAh)
{
    // Initial CPU State
    cpu.set_ax(0x4B30);
    cpu.set_bx(0xCC08);
    cpu.set_cx(0x3B5A);
    cpu.set_dx(0x1113);
    cpu.set_cs(0x71CC);
    cpu.set_ss(0x3E5A);
    cpu.set_ds(0xF092);
    cpu.set_es(0x88EC);
    cpu.set_sp(0x0B0D);
    cpu.set_bp(0x13EB);
    cpu.set_si(0xA2C0);
    cpu.set_di(0x26A3);
    cpu.set_ip(0x21E4);
    cpu.set_flags(0xFC43);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x73EA4, 0x2E);
    machine.mem_store_byte(0x73EA5, 0xFF);
    machine.mem_store_byte(0x73EA6, 0xBB);
    machine.mem_store_byte(0x73EA7, 0x36);
    machine.mem_store_byte(0x73EA8, 0x9E);
    machine.mem_store_byte(0x7F584, 0x4E);
    machine.mem_store_byte(0x7F585, 0x3A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x0B0B);
    EXPECT_EQ(cpu.get_ip(), 0x21E9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3F0AB), 0x4E);
    EXPECT_EQ(memory.load8(0x3F0AC), 0x3A);
}

//
// push word [ss:bp+si]
//
TEST_F(MachineTest, push_word_ss_bp_si)
{
    // Initial CPU State
    cpu.set_ax(0xCA7E);
    cpu.set_bx(0xD08E);
    cpu.set_cx(0x6D66);
    cpu.set_dx(0x215C);
    cpu.set_cs(0xED4A);
    cpu.set_ss(0xCE11);
    cpu.set_ds(0x694E);
    cpu.set_es(0x6710);
    cpu.set_sp(0x441E);
    cpu.set_bp(0x9386);
    cpu.set_si(0xABC4);
    cpu.set_di(0x9D27);
    cpu.set_ip(0xA554);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF79F4, 0xFF);
    machine.mem_store_byte(0xF79F5, 0x32);
    machine.mem_store_byte(0xF79F6, 0x90);
    machine.mem_store_byte(0xF79F7, 0x90);
    machine.mem_store_byte(0xD205A, 0x55);
    machine.mem_store_byte(0xD205B, 0xE1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x441C);
    EXPECT_EQ(cpu.get_ip(), 0xA556);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD252C), 0x55);
    EXPECT_EQ(memory.load8(0xD252D), 0xE1);
}
