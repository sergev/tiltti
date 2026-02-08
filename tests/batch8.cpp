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
