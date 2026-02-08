#include "fixture.h"

//
// daa
//
TEST_F(MachineTest, daa_batch8)
{
    // Initial CPU State
    cpu.set_ax(0x299A);
    cpu.set_bx(0x8D6C);
    cpu.set_cx(0x8F9C);
    cpu.set_dx(0x85F2);
    cpu.set_cs(0xE755);
    cpu.set_ss(0x9870);
    cpu.set_ds(0x4619);
    cpu.set_es(0xD21B);
    cpu.set_sp(0xCC39);
    cpu.set_bp(0x4469);
    cpu.set_si(0x9135);
    cpu.set_di(0x9DB6);
    cpu.set_ip(0xBD0E);
    cpu.set_flags(0xF082);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF325E, 0x27);
    machine.mem_store_byte(0xF325F, 0x90);
    machine.mem_store_byte(0xF3260, 0x90);
    machine.mem_store_byte(0xF3261, 0x90);
    machine.mem_store_byte(0xF3262, 0x90);
    machine.mem_store_byte(0xF3263, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2900);
    EXPECT_EQ(cpu.get_ip(), 0xBD0F);
    EXPECT_FLAGS(0xF057);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF325E), 0x27);
    EXPECT_EQ(memory.load8(0xF325F), 0x90);
    EXPECT_EQ(memory.load8(0xF3260), 0x90);
    EXPECT_EQ(memory.load8(0xF3261), 0x90);
    EXPECT_EQ(memory.load8(0xF3262), 0x90);
    EXPECT_EQ(memory.load8(0xF3263), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch8)
{
    // Initial CPU State
    cpu.set_ax(0x5A9B);
    cpu.set_bx(0x1E86);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x4031);
    cpu.set_ss(0x366C);
    cpu.set_ds(0xBFE6);
    cpu.set_es(0xB59A);
    cpu.set_sp(0x9340);
    cpu.set_bp(0x0000);
    cpu.set_si(0x2949);
    cpu.set_di(0x6EF9);
    cpu.set_ip(0xF553);
    cpu.set_flags(0xF846);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4F863, 0x2F);
    machine.mem_store_byte(0x4F864, 0x90);
    machine.mem_store_byte(0x4F865, 0x90);
    machine.mem_store_byte(0x4F866, 0x90);
    machine.mem_store_byte(0x4F867, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x5A35);
    EXPECT_EQ(cpu.get_ip(), 0xF554);
    EXPECT_FLAGS(0xF817);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4F863), 0x2F);
    EXPECT_EQ(memory.load8(0x4F864), 0x90);
    EXPECT_EQ(memory.load8(0x4F865), 0x90);
    EXPECT_EQ(memory.load8(0x4F866), 0x90);
    EXPECT_EQ(memory.load8(0x4F867), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch9)
{
    // Initial CPU State
    cpu.set_ax(0x2BAF);
    cpu.set_bx(0x3EE1);
    cpu.set_cx(0xA66A);
    cpu.set_dx(0x45C2);
    cpu.set_cs(0xC512);
    cpu.set_ss(0xD705);
    cpu.set_ds(0x119B);
    cpu.set_es(0x1390);
    cpu.set_sp(0x0E05);
    cpu.set_bp(0x91AE);
    cpu.set_si(0xE516);
    cpu.set_di(0xE66D);
    cpu.set_ip(0x6BD5);
    cpu.set_flags(0xF4D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCBCF5, 0x27);
    machine.mem_store_byte(0xCBCF6, 0x90);
    machine.mem_store_byte(0xCBCF7, 0x90);
    machine.mem_store_byte(0xCBCF8, 0x90);
    machine.mem_store_byte(0xCBCF9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2B15);
    EXPECT_EQ(cpu.get_ip(), 0x6BD6);
    EXPECT_FLAGS(0xF413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCBCF5), 0x27);
    EXPECT_EQ(memory.load8(0xCBCF6), 0x90);
    EXPECT_EQ(memory.load8(0xCBCF7), 0x90);
    EXPECT_EQ(memory.load8(0xCBCF8), 0x90);
    EXPECT_EQ(memory.load8(0xCBCF9), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch9)
{
    // Initial CPU State
    cpu.set_ax(0x7B4F);
    cpu.set_bx(0xBE66);
    cpu.set_cx(0xE41C);
    cpu.set_dx(0x8119);
    cpu.set_cs(0x95E3);
    cpu.set_ss(0xCE10);
    cpu.set_ds(0xF305);
    cpu.set_es(0x5D7F);
    cpu.set_sp(0x5576);
    cpu.set_bp(0xC63C);
    cpu.set_si(0x7822);
    cpu.set_di(0xACB1);
    cpu.set_ip(0xC671);
    cpu.set_flags(0xFC03);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA24A1, 0x2F);
    machine.mem_store_byte(0xA24A2, 0x90);
    machine.mem_store_byte(0xA24A3, 0x90);
    machine.mem_store_byte(0xA24A4, 0x90);
    machine.mem_store_byte(0xA24A5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7BE9);
    EXPECT_EQ(cpu.get_ip(), 0xC672);
    EXPECT_FLAGS(0xF493);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA24A1), 0x2F);
    EXPECT_EQ(memory.load8(0xA24A2), 0x90);
    EXPECT_EQ(memory.load8(0xA24A3), 0x90);
    EXPECT_EQ(memory.load8(0xA24A4), 0x90);
    EXPECT_EQ(memory.load8(0xA24A5), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch10)
{
    // Initial CPU State
    cpu.set_ax(0x799C);
    cpu.set_bx(0x9C2F);
    cpu.set_cx(0xF0CE);
    cpu.set_dx(0x637A);
    cpu.set_cs(0xA736);
    cpu.set_ss(0x4B75);
    cpu.set_ds(0xCBE1);
    cpu.set_es(0xF64B);
    cpu.set_sp(0x746F);
    cpu.set_bp(0x650D);
    cpu.set_si(0xE457);
    cpu.set_di(0xE5E5);
    cpu.set_ip(0x8CF7);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB0057, 0x27);
    machine.mem_store_byte(0xB0058, 0x90);
    machine.mem_store_byte(0xB0059, 0x90);
    machine.mem_store_byte(0xB005A, 0x90);
    machine.mem_store_byte(0xB005B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x79A2);
    EXPECT_EQ(cpu.get_ip(), 0x8CF8);
    EXPECT_FLAGS(0xF492);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB0057), 0x27);
    EXPECT_EQ(memory.load8(0xB0058), 0x90);
    EXPECT_EQ(memory.load8(0xB0059), 0x90);
    EXPECT_EQ(memory.load8(0xB005A), 0x90);
    EXPECT_EQ(memory.load8(0xB005B), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch10)
{
    // Initial CPU State
    cpu.set_ax(0x909B);
    cpu.set_bx(0x2397);
    cpu.set_cx(0xFBF8);
    cpu.set_dx(0x4D3C);
    cpu.set_cs(0xBB6F);
    cpu.set_ss(0x0AB4);
    cpu.set_ds(0xA96A);
    cpu.set_es(0xA49D);
    cpu.set_sp(0x49FB);
    cpu.set_bp(0xDC00);
    cpu.set_si(0x901C);
    cpu.set_di(0x044D);
    cpu.set_ip(0x01A6);
    cpu.set_flags(0xFC92);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBB896, 0x2F);
    machine.mem_store_byte(0xBB897, 0x90);
    machine.mem_store_byte(0xBB898, 0x90);
    machine.mem_store_byte(0xBB899, 0x90);
    machine.mem_store_byte(0xBB89A, 0x90);
    machine.mem_store_byte(0xBB89B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9095);
    EXPECT_EQ(cpu.get_ip(), 0x01A7);
    EXPECT_FLAGS(0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBB896), 0x2F);
    EXPECT_EQ(memory.load8(0xBB897), 0x90);
    EXPECT_EQ(memory.load8(0xBB898), 0x90);
    EXPECT_EQ(memory.load8(0xBB899), 0x90);
    EXPECT_EQ(memory.load8(0xBB89A), 0x90);
    EXPECT_EQ(memory.load8(0xBB89B), 0x90);
}
