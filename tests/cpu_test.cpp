#include "util.h"

//
// add byte [ss:bp+di-64h], cl
//
TEST(CpuTest, add_byte_ss_bp_di_64h_cl)
{
    Memory memory;
    Machine machine(memory);
    Processor &cpu = machine.cpu;

    // Optionally enable trace.
    Machine::enable_trace("r");

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
    machine.mem_store_byte(0x32186, 0x00);
    machine.mem_store_byte(0x32187, 0x4B);
    machine.mem_store_byte(0x32188, 0x9C);
    machine.mem_store_byte(0x32189, 0x90);
    machine.mem_store_byte(0x21CFD, 0x14);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x02B9);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x21CFD), 0xDC);
}
