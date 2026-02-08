#include "fixture.h"

//
// callf word [ds:bx+si-2Fh]
//
TEST_F(MachineTest, DISABLED_callf_word_ds_bx_si_2Fh_am88)
{
    // Initial CPU State
    cpu.set_ax(0x1300);
    cpu.set_bx(0x6B0E);
    cpu.set_cx(0x0244);
    cpu.set_dx(0xA754);
    cpu.set_cs(0xADF3);
    cpu.set_ss(0x3406);
    cpu.set_ds(0x0367);
    cpu.set_es(0xF273);
    cpu.set_sp(0x33BE);
    cpu.set_bp(0x066F);
    cpu.set_si(0x951F);
    cpu.set_di(0x8FAB);
    cpu.set_ip(0x679F);
    cpu.set_flags(0xF053);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB46CF, 0x3E);
    machine.mem_store_byte(0xB46D0, 0xFF);
    machine.mem_store_byte(0xB46D1, 0x58);
    machine.mem_store_byte(0xB46D2, 0xD1);
    machine.mem_store_byte(0x1366E, 0x4B);
    machine.mem_store_byte(0x1366F, 0x69);
    machine.mem_store_byte(0x03670, 0x9D);
    machine.mem_store_byte(0x03671, 0xE3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0xE39D);
    EXPECT_EQ(cpu.get_sp(), 0x33BA);
    EXPECT_EQ(cpu.get_ip(), 0x694B);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3741C), 0xF3);
    EXPECT_EQ(memory.load8(0x3741D), 0xAD);
    EXPECT_EQ(memory.load8(0x3741A), 0xA3);
    EXPECT_EQ(memory.load8(0x3741B), 0x67);
}

//
// lds ax, dword [ds:bx+di+4Ah]
//
TEST_F(MachineTest, DISABLED_lds_ax_dword_ds_bx_di_4Ah_am88)
{
    // Initial CPU State
    cpu.set_ax(0xD342);
    cpu.set_bx(0x1E93);
    cpu.set_cx(0x0534);
    cpu.set_dx(0xB69A);
    cpu.set_cs(0x18C8);
    cpu.set_ss(0xEDC7);
    cpu.set_ds(0x6D06);
    cpu.set_es(0xBE64);
    cpu.set_sp(0x4412);
    cpu.set_bp(0x2E39);
    cpu.set_si(0x12A4);
    cpu.set_di(0xE122);
    cpu.set_ip(0x7948);
    cpu.set_flags(0xF887);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x205C8, 0xC5);
    machine.mem_store_byte(0x205C9, 0x41);
    machine.mem_store_byte(0x205CA, 0x4A);
    machine.mem_store_byte(0x7D05F, 0x5E);
    machine.mem_store_byte(0x6D060, 0xBA);
    machine.mem_store_byte(0x6D061, 0x27);
    machine.mem_store_byte(0x6D062, 0xC6);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xBA5E);
    EXPECT_EQ(cpu.get_ds(), 0xC627);
    EXPECT_EQ(cpu.get_ip(), 0x794B);

    // Final RAM entries
}

//
// mul ax
//
TEST_F(MachineTest, DISABLED_mul_ax_am88)
{
    // Initial CPU State
    cpu.set_ax(0x0011);
    cpu.set_bx(0x252F);
    cpu.set_cx(0x9C52);
    cpu.set_dx(0x15AB);
    cpu.set_cs(0xDF24);
    cpu.set_ss(0x0FED);
    cpu.set_ds(0xC34C);
    cpu.set_es(0x81CC);
    cpu.set_sp(0x2CB9);
    cpu.set_bp(0x7267);
    cpu.set_si(0x2BCF);
    cpu.set_di(0xDE9C);
    cpu.set_ip(0xC220);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEB460, 0x3E);
    machine.mem_store_byte(0xEB461, 0xF7);
    machine.mem_store_byte(0xEB462, 0xE0);
    machine.mem_store_byte(0xEB463, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0121);
    EXPECT_EQ(cpu.get_dx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0xC223);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
}

//
// mul word [es:bx+si]
//
TEST_F(MachineTest, DISABLED_mul_word_es_bx_si_am88)
{
    // Initial CPU State
    cpu.set_ax(0x0107);
    cpu.set_bx(0xAE45);
    cpu.set_cx(0x3E34);
    cpu.set_dx(0x2597);
    cpu.set_cs(0xFC91);
    cpu.set_ss(0x2AAA);
    cpu.set_ds(0xF001);
    cpu.set_es(0xDB46);
    cpu.set_sp(0x5466);
    cpu.set_bp(0x140E);
    cpu.set_si(0x678C);
    cpu.set_di(0x0C65);
    cpu.set_ip(0xF34F);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0BC5F, 0x26);
    machine.mem_store_byte(0x0BC60, 0xF7);
    machine.mem_store_byte(0x0BC61, 0x20);
    machine.mem_store_byte(0x0BC62, 0x90);
    machine.mem_store_byte(0xDCA31, 0x0F);
    machine.mem_store_byte(0xDCA32, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0F69);
    EXPECT_EQ(cpu.get_dx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0xF352);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
}
