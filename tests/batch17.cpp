#include "fixture.h"

//
// aad F8h
//
TEST_F(MachineTest, aad_F8h_batch17)
{
    // Initial CPU State
    cpu.set_ax(0xC681);
    cpu.set_bx(0x430A);
    cpu.set_cx(0xEF48);
    cpu.set_dx(0xE4B8);
    cpu.set_cs(0x92EA);
    cpu.set_ss(0x01BB);
    cpu.set_ds(0x1C7E);
    cpu.set_es(0xF9AB);
    cpu.set_sp(0x001C);
    cpu.set_bp(0x2CC0);
    cpu.set_si(0xF100);
    cpu.set_di(0xDD9A);
    cpu.set_ip(0xB542);
    cpu.set_flags(0xF4D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9E3E2, 0xD5);
    machine.mem_store_byte(0x9E3E3, 0xF8);
    machine.mem_store_byte(0x9E3E4, 0x90);
    machine.mem_store_byte(0x9E3E5, 0x90);
    machine.mem_store_byte(0x9E3E6, 0x90);
    machine.mem_store_byte(0x9E3E7, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0051);
    EXPECT_EQ(cpu.get_ip(), 0xB544);
    EXPECT_FLAGS(0xFC03);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x9E3E2, 0xD5);
    EXPECT_FLAGS_HI(0x9E3E3, 0xF8);
    EXPECT_EQ(memory.load8(0x9E3E4), 0x90);
    EXPECT_EQ(memory.load8(0x9E3E5), 0x90);
    EXPECT_EQ(memory.load8(0x9E3E6), 0x90);
    EXPECT_EQ(memory.load8(0x9E3E7), 0x90);
}

//
// aam F8h
//
TEST_F(MachineTest, aam_F8h_batch17)
{
    // Initial CPU State
    cpu.set_ax(0x957D);
    cpu.set_bx(0x09BA);
    cpu.set_cx(0xDBC8);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x12B5);
    cpu.set_ss(0x6420);
    cpu.set_ds(0xAF45);
    cpu.set_es(0xC7DE);
    cpu.set_sp(0x566C);
    cpu.set_bp(0xABD5);
    cpu.set_si(0xEF43);
    cpu.set_di(0x06E4);
    cpu.set_ip(0xE23C);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x20D8C, 0xD4);
    machine.mem_store_byte(0x20D8D, 0xF8);
    machine.mem_store_byte(0x20D8E, 0x90);
    machine.mem_store_byte(0x20D8F, 0x90);
    machine.mem_store_byte(0x20D90, 0x90);
    machine.mem_store_byte(0x20D91, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x007D);
    EXPECT_EQ(cpu.get_ip(), 0xE23E);
    EXPECT_FLAGS(0xF006);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x20D8C, 0xD4);
    EXPECT_FLAGS_HI(0x20D8D, 0xF8);
    EXPECT_EQ(memory.load8(0x20D8E), 0x90);
    EXPECT_EQ(memory.load8(0x20D8F), 0x90);
    EXPECT_EQ(memory.load8(0x20D90), 0x90);
    EXPECT_EQ(memory.load8(0x20D91), 0x90);
}

//
// div al
//
TEST_F(MachineTest, div_al_batch17)
{
    // Initial CPU State
    cpu.set_ax(0x246D);
    cpu.set_bx(0x5C13);
    cpu.set_cx(0x9AD4);
    cpu.set_dx(0xE4EC);
    cpu.set_cs(0x7A07);
    cpu.set_ss(0xA8B0);
    cpu.set_ds(0x6A86);
    cpu.set_es(0xF72B);
    cpu.set_sp(0x9EA6);
    cpu.set_bp(0x4610);
    cpu.set_si(0x51C8);
    cpu.set_di(0x1395);
    cpu.set_ip(0xF0A0);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x89110, 0x3E);
    machine.mem_store_byte(0x89111, 0xF6);
    machine.mem_store_byte(0x89112, 0xF0);
    machine.mem_store_byte(0x89113, 0x90);
    machine.mem_store_byte(0x89114, 0x90);
    machine.mem_store_byte(0x89115, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x3C55);
    EXPECT_EQ(cpu.get_ip(), 0xF0A3);
    EXPECT_FLAGS(0xF817);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x89110, 0x3E);
    EXPECT_FLAGS_HI(0x89111, 0xF6);
    EXPECT_EQ(memory.load8(0x89112), 0xF0);
    EXPECT_EQ(memory.load8(0x89113), 0x90);
    EXPECT_EQ(memory.load8(0x89114), 0x90);
    EXPECT_EQ(memory.load8(0x89115), 0x90);
}

//
// div byte [cs:B537h]
//
TEST_F(MachineTest, div_byte_cs_B537h_batch17)
{
    // Initial CPU State
    cpu.set_ax(0x3EB6);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xD6B6);
    cpu.set_dx(0x0BB3);
    cpu.set_cs(0x79D4);
    cpu.set_ss(0xA02B);
    cpu.set_ds(0x7C1B);
    cpu.set_es(0x2E1C);
    cpu.set_sp(0x692A);
    cpu.set_bp(0x5713);
    cpu.set_si(0xA875);
    cpu.set_di(0x3862);
    cpu.set_ip(0x2ABD);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7C7FD, 0x2E);
    machine.mem_store_byte(0x7C7FE, 0xF6);
    machine.mem_store_byte(0x7C7FF, 0x36);
    machine.mem_store_byte(0x7C800, 0x37);
    machine.mem_store_byte(0x7C801, 0xB5);
    machine.mem_store_byte(0x85277, 0xD2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x5E4C);
    EXPECT_EQ(cpu.get_ip(), 0x2AC2);
    EXPECT_FLAGS(0xFC83);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x7C7FD, 0x2E);
    EXPECT_FLAGS_HI(0x7C7FE, 0xF6);
    EXPECT_EQ(memory.load8(0x7C7FF), 0x36);
    EXPECT_EQ(memory.load8(0x7C800), 0x37);
    EXPECT_EQ(memory.load8(0x7C801), 0xB5);
    EXPECT_EQ(memory.load8(0x85277), 0xD2);
}

//
// idiv al
//
TEST_F(MachineTest, idiv_al_batch17)
{
    // Initial CPU State
    cpu.set_ax(0x134E);
    cpu.set_bx(0xE2C1);
    cpu.set_cx(0xFF1A);
    cpu.set_dx(0xB00F);
    cpu.set_cs(0x5AB3);
    cpu.set_ss(0x4D44);
    cpu.set_ds(0x9E91);
    cpu.set_es(0xA1D2);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xFFA0);
    cpu.set_si(0xFEDA);
    cpu.set_di(0x0000);
    cpu.set_ip(0x9F2C);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x64A5C, 0xF6);
    machine.mem_store_byte(0x64A5D, 0xF8);
    machine.mem_store_byte(0x64A5E, 0x90);
    machine.mem_store_byte(0x64A5F, 0x90);
    machine.mem_store_byte(0x64A60, 0x90);
    machine.mem_store_byte(0x64A61, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1C3F);
    EXPECT_EQ(cpu.get_ip(), 0x9F2E);
    EXPECT_FLAGS(0xF012);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x64A5C, 0xF6);
    EXPECT_FLAGS_HI(0x64A5D, 0xF8);
    EXPECT_EQ(memory.load8(0x64A5E), 0x90);
    EXPECT_EQ(memory.load8(0x64A5F), 0x90);
    EXPECT_EQ(memory.load8(0x64A60), 0x90);
    EXPECT_EQ(memory.load8(0x64A61), 0x90);
}

//
// idiv byte [cs:bp+di]
//
TEST_F(MachineTest, idiv_byte_cs_bp_di_batch17)
{
    // Initial CPU State
    cpu.set_ax(0xF2E3);
    cpu.set_bx(0xEC9D);
    cpu.set_cx(0x1696);
    cpu.set_dx(0x0920);
    cpu.set_cs(0xBF24);
    cpu.set_ss(0x1556);
    cpu.set_ds(0xE857);
    cpu.set_es(0x0C63);
    cpu.set_sp(0x12F6);
    cpu.set_bp(0xE561);
    cpu.set_si(0xA4E8);
    cpu.set_di(0x625E);
    cpu.set_ip(0xB0D7);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCA317, 0x2E);
    machine.mem_store_byte(0xCA318, 0xF6);
    machine.mem_store_byte(0xCA319, 0x3B);
    machine.mem_store_byte(0xCA31A, 0x90);
    machine.mem_store_byte(0xCA31B, 0x90);
    machine.mem_store_byte(0xC39FF, 0x79);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xA6E5);
    EXPECT_EQ(cpu.get_ip(), 0xB0DA);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_FLAGS_LO(0xCA317, 0x2E);
    EXPECT_FLAGS_HI(0xCA318, 0xF6);
    EXPECT_EQ(memory.load8(0xCA319), 0x3B);
    EXPECT_EQ(memory.load8(0xCA31A), 0x90);
    EXPECT_EQ(memory.load8(0xCA31B), 0x90);
    EXPECT_EQ(memory.load8(0xC39FF), 0x79);
}

//
// imul ah
//
TEST_F(MachineTest, imul_ah_batch17)
{
    // Initial CPU State
    cpu.set_ax(0xAFA9);
    cpu.set_bx(0xDCC0);
    cpu.set_cx(0x7226);
    cpu.set_dx(0x3804);
    cpu.set_cs(0x997D);
    cpu.set_ss(0x7E94);
    cpu.set_ds(0xED57);
    cpu.set_es(0x087A);
    cpu.set_sp(0xE0A9);
    cpu.set_bp(0x6FAA);
    cpu.set_si(0x0000);
    cpu.set_di(0xEDB4);
    cpu.set_ip(0x0FC2);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9A792, 0x3E);
    machine.mem_store_byte(0x9A793, 0xF6);
    machine.mem_store_byte(0x9A794, 0xEC);
    machine.mem_store_byte(0x9A795, 0x90);
    machine.mem_store_byte(0x9A796, 0x90);
    machine.mem_store_byte(0x9A797, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1B87);
    EXPECT_EQ(cpu.get_ip(), 0x0FC5);
    EXPECT_FLAGS(0xF803);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x9A792, 0x3E);
    EXPECT_FLAGS_HI(0x9A793, 0xF6);
    EXPECT_EQ(memory.load8(0x9A794), 0xEC);
    EXPECT_EQ(memory.load8(0x9A795), 0x90);
    EXPECT_EQ(memory.load8(0x9A796), 0x90);
    EXPECT_EQ(memory.load8(0x9A797), 0x90);
}

//
// imul byte [cs:8BBDh]
//
TEST_F(MachineTest, imul_byte_cs_8BBDh_batch17)
{
    // Initial CPU State
    cpu.set_ax(0x2ECC);
    cpu.set_bx(0x92CE);
    cpu.set_cx(0xF092);
    cpu.set_dx(0x0B11);
    cpu.set_cs(0x4FEC);
    cpu.set_ss(0xED69);
    cpu.set_ds(0x1020);
    cpu.set_es(0x0A31);
    cpu.set_sp(0x9A2B);
    cpu.set_bp(0xBC52);
    cpu.set_si(0x9ACB);
    cpu.set_di(0x197D);
    cpu.set_ip(0x6EC9);
    cpu.set_flags(0xF0C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x56D89, 0x2E);
    machine.mem_store_byte(0x56D8A, 0xF6);
    machine.mem_store_byte(0x56D8B, 0x2E);
    machine.mem_store_byte(0x56D8C, 0xBD);
    machine.mem_store_byte(0x56D8D, 0x8B);
    machine.mem_store_byte(0x58A7D, 0xD9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x07EC);
    EXPECT_EQ(cpu.get_ip(), 0x6ECE);
    EXPECT_FLAGS(0xF803);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x56D89, 0x2E);
    EXPECT_FLAGS_HI(0x56D8A, 0xF6);
    EXPECT_EQ(memory.load8(0x56D8B), 0x2E);
    EXPECT_EQ(memory.load8(0x56D8C), 0xBD);
    EXPECT_EQ(memory.load8(0x56D8D), 0x8B);
    EXPECT_EQ(memory.load8(0x58A7D), 0xD9);
}

//
// mul ax
//
TEST_F(MachineTest, mul_ax_batch17)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x348D);
    cpu.set_cx(0xC708);
    cpu.set_dx(0xEDDD);
    cpu.set_cs(0x2DEB);
    cpu.set_ss(0x89EE);
    cpu.set_ds(0xAABF);
    cpu.set_es(0x35FD);
    cpu.set_sp(0xE0D4);
    cpu.set_bp(0xE55A);
    cpu.set_si(0x3B46);
    cpu.set_di(0xB744);
    cpu.set_ip(0x9E6C);
    cpu.set_flags(0xF0D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x37D1C, 0x26);
    machine.mem_store_byte(0x37D1D, 0xF7);
    machine.mem_store_byte(0x37D1E, 0xE0);
    machine.mem_store_byte(0x37D1F, 0x90);
    machine.mem_store_byte(0x37D20, 0x90);
    machine.mem_store_byte(0x37D21, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0x9E6F);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_FLAGS_LO(0x37D1C, 0x26);
    EXPECT_FLAGS_HI(0x37D1D, 0xF7);
    EXPECT_EQ(memory.load8(0x37D1E), 0xE0);
    EXPECT_EQ(memory.load8(0x37D1F), 0x90);
    EXPECT_EQ(memory.load8(0x37D20), 0x90);
    EXPECT_EQ(memory.load8(0x37D21), 0x90);
}
