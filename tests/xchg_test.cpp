#include "fixture.h"

//
// xchg bp, ax
//
TEST_F(MachineTest, xchg_bp_ax)
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
    machine.mem_store_byte(0x76C78, 0x95);
    machine.mem_store_byte(0x76C79, 0x90);
    machine.mem_store_byte(0x76C7A, 0x90);
    machine.mem_store_byte(0x76C7B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1B2A);
    EXPECT_EQ(cpu.get_bp(), 0xBE84);
    EXPECT_EQ(cpu.get_ip(), 0x01C9);

    // Final RAM entries
}

//
// xchg bx, ax
//
TEST_F(MachineTest, xchg_bx_ax)
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
    machine.mem_store_byte(0x3F81C, 0x93);
    machine.mem_store_byte(0x3F81D, 0x90);
    machine.mem_store_byte(0x3F81E, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xCEEC);
    EXPECT_EQ(cpu.get_bx(), 0x4568);
    EXPECT_EQ(cpu.get_ip(), 0x283D);

    // Final RAM entries
}

//
// xchg cl, byte [es:bx+di]
//
TEST_F(MachineTest, xchg_cl_byte_es_bx_di)
{
    // Initial CPU State
    cpu.set_ax(0x660C);
    cpu.set_bx(0xEB0B);
    cpu.set_cx(0x4D00);
    cpu.set_dx(0x47AE);
    cpu.set_cs(0x1206);
    cpu.set_ss(0xB683);
    cpu.set_ds(0x3EF5);
    cpu.set_es(0xAE57);
    cpu.set_sp(0x8AAA);
    cpu.set_bp(0xB1EE);
    cpu.set_si(0xEADF);
    cpu.set_di(0x8A69);
    cpu.set_ip(0xA7F7);
    cpu.set_flags(0xF842);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1C857, 0x26);
    machine.mem_store_byte(0x1C858, 0x86);
    machine.mem_store_byte(0x1C859, 0x09);
    machine.mem_store_byte(0x1C85A, 0x90);
    machine.mem_store_byte(0xB5AE4, 0x33);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x4D33);
    EXPECT_EQ(cpu.get_ip(), 0xA7FA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB5AE4), 0x00);
}

//
// xchg cx, ax
//
TEST_F(MachineTest, xchg_cx_ax)
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
    machine.mem_store_byte(0x32186, 0x91);
    machine.mem_store_byte(0x32187, 0x90);
    machine.mem_store_byte(0x32188, 0x90);
    machine.mem_store_byte(0x32189, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x81C8);
    EXPECT_EQ(cpu.get_cx(), 0x52A1);
    EXPECT_EQ(cpu.get_ip(), 0x02B7);

    // Final RAM entries
}

//
// xchg di, ax
//
TEST_F(MachineTest, xchg_di_ax)
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
    machine.mem_store_byte(0xC2A88, 0x3E);
    machine.mem_store_byte(0xC2A89, 0x97);
    machine.mem_store_byte(0xC2A8A, 0x90);
    machine.mem_store_byte(0xC2A8B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xF915);
    EXPECT_EQ(cpu.get_di(), 0xB20F);
    EXPECT_EQ(cpu.get_ip(), 0xCF2A);

    // Final RAM entries
}

//
// xchg dx, ax
//
TEST_F(MachineTest, xchg_dx_ax)
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
    machine.mem_store_byte(0xA9BE2, 0x92);
    machine.mem_store_byte(0xA9BE3, 0x90);
    machine.mem_store_byte(0xA9BE4, 0x90);
    machine.mem_store_byte(0xA9BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9001);
    EXPECT_EQ(cpu.get_dx(), 0x634C);
    EXPECT_EQ(cpu.get_ip(), 0x94E3);

    // Final RAM entries
}

//
// xchg si, ax
//
TEST_F(MachineTest, xchg_si_ax)
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
    machine.mem_store_byte(0x6D5D5, 0x96);
    machine.mem_store_byte(0x6D5D6, 0x90);
    machine.mem_store_byte(0x6D5D7, 0x90);
    machine.mem_store_byte(0x6D5D8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD4A8);
    EXPECT_EQ(cpu.get_si(), 0x5165);
    EXPECT_EQ(cpu.get_ip(), 0xBD16);

    // Final RAM entries
}

//
// xchg sp, ax
//
TEST_F(MachineTest, xchg_sp_ax)
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
    machine.mem_store_byte(0xEB58F, 0x94);
    machine.mem_store_byte(0xEB590, 0x90);
    machine.mem_store_byte(0xEB591, 0x90);
    machine.mem_store_byte(0xEB592, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x978F);
    EXPECT_EQ(cpu.get_sp(), 0x5EE5);
    EXPECT_EQ(cpu.get_ip(), 0x3320);

    // Final RAM entries
}

//
// xchg sp, word [ss:bp+si-51DCh]
//
TEST_F(MachineTest, xchg_sp_word_ss_bp_si_51DCh)
{
    // Initial CPU State
    cpu.set_ax(0xC01D);
    cpu.set_bx(0x3203);
    cpu.set_cx(0xEEA4);
    cpu.set_dx(0x5071);
    cpu.set_cs(0x8445);
    cpu.set_ss(0x2E08);
    cpu.set_ds(0x37A1);
    cpu.set_es(0x1887);
    cpu.set_sp(0x8D79);
    cpu.set_bp(0xC5A7);
    cpu.set_si(0x3043);
    cpu.set_di(0xED80);
    cpu.set_ip(0x8FD8);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8D428, 0x87);
    machine.mem_store_byte(0x8D429, 0xA2);
    machine.mem_store_byte(0x8D42A, 0x24);
    machine.mem_store_byte(0x8D42B, 0xAE);
    machine.mem_store_byte(0x3848E, 0x72);
    machine.mem_store_byte(0x3848F, 0xE1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xE172);
    EXPECT_EQ(cpu.get_ip(), 0x8FDC);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3848E), 0x79);
    EXPECT_EQ(memory.load8(0x3848F), 0x8D);
}
