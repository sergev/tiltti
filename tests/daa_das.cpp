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

//
// daa
//
TEST_F(MachineTest, daa_batch11)
{
    // Initial CPU State
    cpu.set_ax(0xA59C);
    cpu.set_bx(0x246A);
    cpu.set_cx(0xCAE0);
    cpu.set_dx(0x67CB);
    cpu.set_cs(0x3013);
    cpu.set_ss(0x2119);
    cpu.set_ds(0x15E8);
    cpu.set_es(0xED5D);
    cpu.set_sp(0xEACA);
    cpu.set_bp(0x60DF);
    cpu.set_si(0xF773);
    cpu.set_di(0xD53D);
    cpu.set_ip(0x52D5);
    cpu.set_flags(0xF402);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x35405, 0x27);
    machine.mem_store_byte(0x35406, 0x90);
    machine.mem_store_byte(0x35407, 0x90);
    machine.mem_store_byte(0x35408, 0x90);
    machine.mem_store_byte(0x35409, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xA502);
    EXPECT_EQ(cpu.get_ip(), 0x52D6);
    EXPECT_FLAGS(0xF413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x35405), 0x27);
    EXPECT_EQ(memory.load8(0x35406), 0x90);
    EXPECT_EQ(memory.load8(0x35407), 0x90);
    EXPECT_EQ(memory.load8(0x35408), 0x90);
    EXPECT_EQ(memory.load8(0x35409), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch11)
{
    // Initial CPU State
    cpu.set_ax(0x8C9F);
    cpu.set_bx(0xC588);
    cpu.set_cx(0x678C);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xAEEF);
    cpu.set_ss(0xBF66);
    cpu.set_ds(0xD6B8);
    cpu.set_es(0xBF0B);
    cpu.set_sp(0x37AF);
    cpu.set_bp(0x81B5);
    cpu.set_si(0x06CE);
    cpu.set_di(0x14AA);
    cpu.set_ip(0xA26E);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB915E, 0x2F);
    machine.mem_store_byte(0xB915F, 0x90);
    machine.mem_store_byte(0xB9160, 0x90);
    machine.mem_store_byte(0xB9161, 0x90);
    machine.mem_store_byte(0xB9162, 0x90);
    machine.mem_store_byte(0xB9163, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8C39);
    EXPECT_EQ(cpu.get_ip(), 0xA26F);
    EXPECT_FLAGS(0xFC17);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB915E), 0x2F);
    EXPECT_EQ(memory.load8(0xB915F), 0x90);
    EXPECT_EQ(memory.load8(0xB9160), 0x90);
    EXPECT_EQ(memory.load8(0xB9161), 0x90);
    EXPECT_EQ(memory.load8(0xB9162), 0x90);
    EXPECT_EQ(memory.load8(0xB9163), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch12)
{
    // Initial CPU State
    cpu.set_ax(0xE99C);
    cpu.set_bx(0x4D89);
    cpu.set_cx(0x3688);
    cpu.set_dx(0xF539);
    cpu.set_cs(0x11E9);
    cpu.set_ss(0x5964);
    cpu.set_ds(0xB09C);
    cpu.set_es(0xECCA);
    cpu.set_sp(0x43E1);
    cpu.set_bp(0x952D);
    cpu.set_si(0xBD7C);
    cpu.set_di(0x2421);
    cpu.set_ip(0x52B9);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x17149, 0x27);
    machine.mem_store_byte(0x1714A, 0x90);
    machine.mem_store_byte(0x1714B, 0x90);
    machine.mem_store_byte(0x1714C, 0x90);
    machine.mem_store_byte(0x1714D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xE9A2);
    EXPECT_EQ(cpu.get_ip(), 0x52BA);
    EXPECT_FLAGS(0xF092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x17149), 0x27);
    EXPECT_EQ(memory.load8(0x1714A), 0x90);
    EXPECT_EQ(memory.load8(0x1714B), 0x90);
    EXPECT_EQ(memory.load8(0x1714C), 0x90);
    EXPECT_EQ(memory.load8(0x1714D), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch12)
{
    // Initial CPU State
    cpu.set_ax(0xED9A);
    cpu.set_bx(0x9D70);
    cpu.set_cx(0x11F2);
    cpu.set_dx(0x6909);
    cpu.set_cs(0x3D9A);
    cpu.set_ss(0xD960);
    cpu.set_ds(0x30B8);
    cpu.set_es(0x8584);
    cpu.set_sp(0xB0C5);
    cpu.set_bp(0x4493);
    cpu.set_si(0xF886);
    cpu.set_di(0x20E5);
    cpu.set_ip(0xA5AC);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x47F4C, 0x2F);
    machine.mem_store_byte(0x47F4D, 0x90);
    machine.mem_store_byte(0x47F4E, 0x90);
    machine.mem_store_byte(0x47F4F, 0x90);
    machine.mem_store_byte(0x47F50, 0x90);
    machine.mem_store_byte(0x47F51, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xED34);
    EXPECT_EQ(cpu.get_ip(), 0xA5AD);
    EXPECT_FLAGS(0xFC13);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x47F4C), 0x2F);
    EXPECT_EQ(memory.load8(0x47F4D), 0x90);
    EXPECT_EQ(memory.load8(0x47F4E), 0x90);
    EXPECT_EQ(memory.load8(0x47F4F), 0x90);
    EXPECT_EQ(memory.load8(0x47F50), 0x90);
    EXPECT_EQ(memory.load8(0x47F51), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch13)
{
    // Initial CPU State
    cpu.set_ax(0x7B9D);
    cpu.set_bx(0xEF43);
    cpu.set_cx(0x8466);
    cpu.set_dx(0x69B2);
    cpu.set_cs(0x84FA);
    cpu.set_ss(0xD480);
    cpu.set_ds(0x4B33);
    cpu.set_es(0x1532);
    cpu.set_sp(0x22EB);
    cpu.set_bp(0xD23B);
    cpu.set_si(0x3C9E);
    cpu.set_di(0x5CE4);
    cpu.set_ip(0x19A9);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x86949, 0x27);
    machine.mem_store_byte(0x8694A, 0x90);
    machine.mem_store_byte(0x8694B, 0x90);
    machine.mem_store_byte(0x8694C, 0x90);
    machine.mem_store_byte(0x8694D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7BA3);
    EXPECT_EQ(cpu.get_ip(), 0x19AA);
    EXPECT_FLAGS(0xF096);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x86949), 0x27);
    EXPECT_EQ(memory.load8(0x8694A), 0x90);
    EXPECT_EQ(memory.load8(0x8694B), 0x90);
    EXPECT_EQ(memory.load8(0x8694C), 0x90);
    EXPECT_EQ(memory.load8(0x8694D), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch13)
{
    // Initial CPU State
    cpu.set_ax(0x819D);
    cpu.set_bx(0x0DE0);
    cpu.set_cx(0xB6D2);
    cpu.set_dx(0x5C1B);
    cpu.set_cs(0xE83E);
    cpu.set_ss(0x723A);
    cpu.set_ds(0x83B6);
    cpu.set_es(0xFA57);
    cpu.set_sp(0xF125);
    cpu.set_bp(0xE312);
    cpu.set_si(0x37BD);
    cpu.set_di(0x3BA4);
    cpu.set_ip(0x6E0C);
    cpu.set_flags(0xF486);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEF1EC, 0x2F);
    machine.mem_store_byte(0xEF1ED, 0x90);
    machine.mem_store_byte(0xEF1EE, 0x90);
    machine.mem_store_byte(0xEF1EF, 0x90);
    machine.mem_store_byte(0xEF1F0, 0x90);
    machine.mem_store_byte(0xEF1F1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8137);
    EXPECT_EQ(cpu.get_ip(), 0x6E0D);
    EXPECT_FLAGS(0xFC13);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEF1EC), 0x2F);
    EXPECT_EQ(memory.load8(0xEF1ED), 0x90);
    EXPECT_EQ(memory.load8(0xEF1EE), 0x90);
    EXPECT_EQ(memory.load8(0xEF1EF), 0x90);
    EXPECT_EQ(memory.load8(0xEF1F0), 0x90);
    EXPECT_EQ(memory.load8(0xEF1F1), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch14)
{
    // Initial CPU State
    cpu.set_ax(0x829F);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xE38C);
    cpu.set_dx(0xE06C);
    cpu.set_cs(0x31F0);
    cpu.set_ss(0xFAE0);
    cpu.set_ds(0x311B);
    cpu.set_es(0xDFFF);
    cpu.set_sp(0xB9B1);
    cpu.set_bp(0xD626);
    cpu.set_si(0x546C);
    cpu.set_di(0x7069);
    cpu.set_ip(0xB1EA);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3D0EA, 0x27);
    machine.mem_store_byte(0x3D0EB, 0x90);
    machine.mem_store_byte(0x3D0EC, 0x90);
    machine.mem_store_byte(0x3D0ED, 0x90);
    machine.mem_store_byte(0x3D0EE, 0x90);
    machine.mem_store_byte(0x3D0EF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8205);
    EXPECT_EQ(cpu.get_ip(), 0xB1EB);
    EXPECT_FLAGS(0xF017);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3D0EA), 0x27);
    EXPECT_EQ(memory.load8(0x3D0EB), 0x90);
    EXPECT_EQ(memory.load8(0x3D0EC), 0x90);
    EXPECT_EQ(memory.load8(0x3D0ED), 0x90);
    EXPECT_EQ(memory.load8(0x3D0EE), 0x90);
    EXPECT_EQ(memory.load8(0x3D0EF), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch14)
{
    // Initial CPU State
    cpu.set_ax(0x0C9D);
    cpu.set_bx(0xA472);
    cpu.set_cx(0x261E);
    cpu.set_dx(0xD531);
    cpu.set_cs(0xC249);
    cpu.set_ss(0x0473);
    cpu.set_ds(0x60F8);
    cpu.set_es(0xE6CD);
    cpu.set_sp(0xEFC6);
    cpu.set_bp(0xCF0A);
    cpu.set_si(0x6550);
    cpu.set_di(0xABAD);
    cpu.set_ip(0x12BA);
    cpu.set_flags(0xF002);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC374A, 0x2F);
    machine.mem_store_byte(0xC374B, 0x90);
    machine.mem_store_byte(0xC374C, 0x90);
    machine.mem_store_byte(0xC374D, 0x90);
    machine.mem_store_byte(0xC374E, 0x90);
    machine.mem_store_byte(0xC374F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0C37);
    EXPECT_EQ(cpu.get_ip(), 0x12BB);
    EXPECT_FLAGS(0xF813);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC374A), 0x2F);
    EXPECT_EQ(memory.load8(0xC374B), 0x90);
    EXPECT_EQ(memory.load8(0xC374C), 0x90);
    EXPECT_EQ(memory.load8(0xC374D), 0x90);
    EXPECT_EQ(memory.load8(0xC374E), 0x90);
    EXPECT_EQ(memory.load8(0xC374F), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch15)
{
    // Initial CPU State
    cpu.set_ax(0x459B);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xF87C);
    cpu.set_dx(0xFBBF);
    cpu.set_cs(0xC343);
    cpu.set_ss(0xE283);
    cpu.set_ds(0x3F55);
    cpu.set_es(0xFC77);
    cpu.set_sp(0x7CB2);
    cpu.set_bp(0x3DEC);
    cpu.set_si(0xF1FA);
    cpu.set_di(0x61B1);
    cpu.set_ip(0xC7B2);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCFBE2, 0x27);
    machine.mem_store_byte(0xCFBE3, 0x90);
    machine.mem_store_byte(0xCFBE4, 0x90);
    machine.mem_store_byte(0xCFBE5, 0x90);
    machine.mem_store_byte(0xCFBE6, 0x90);
    machine.mem_store_byte(0xCFBE7, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x45A1);
    EXPECT_EQ(cpu.get_ip(), 0xC7B3);
    EXPECT_FLAGS(0xF092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCFBE2), 0x27);
    EXPECT_EQ(memory.load8(0xCFBE3), 0x90);
    EXPECT_EQ(memory.load8(0xCFBE4), 0x90);
    EXPECT_EQ(memory.load8(0xCFBE5), 0x90);
    EXPECT_EQ(memory.load8(0xCFBE6), 0x90);
    EXPECT_EQ(memory.load8(0xCFBE7), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch15)
{
    // Initial CPU State
    cpu.set_ax(0x8F9D);
    cpu.set_bx(0xFE36);
    cpu.set_cx(0x0000);
    cpu.set_dx(0xC339);
    cpu.set_cs(0xC2CA);
    cpu.set_ss(0xAC27);
    cpu.set_ds(0x61CF);
    cpu.set_es(0x2FF2);
    cpu.set_sp(0xA977);
    cpu.set_bp(0xEE63);
    cpu.set_si(0x369A);
    cpu.set_di(0xF4C5);
    cpu.set_ip(0x7F78);
    cpu.set_flags(0xF892);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCAC18, 0x2F);
    machine.mem_store_byte(0xCAC19, 0x90);
    machine.mem_store_byte(0xCAC1A, 0x90);
    machine.mem_store_byte(0xCAC1B, 0x90);
    machine.mem_store_byte(0xCAC1C, 0x90);
    machine.mem_store_byte(0xCAC1D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8F97);
    EXPECT_EQ(cpu.get_ip(), 0x7F79);
    EXPECT_FLAGS(0xF092);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCAC18), 0x2F);
    EXPECT_EQ(memory.load8(0xCAC19), 0x90);
    EXPECT_EQ(memory.load8(0xCAC1A), 0x90);
    EXPECT_EQ(memory.load8(0xCAC1B), 0x90);
    EXPECT_EQ(memory.load8(0xCAC1C), 0x90);
    EXPECT_EQ(memory.load8(0xCAC1D), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch16)
{
    // Initial CPU State
    cpu.set_ax(0x1D9A);
    cpu.set_bx(0x8A6D);
    cpu.set_cx(0x0000);
    cpu.set_dx(0xDCFE);
    cpu.set_cs(0x9542);
    cpu.set_ss(0x3F03);
    cpu.set_ds(0x4342);
    cpu.set_es(0xD534);
    cpu.set_sp(0xDE29);
    cpu.set_bp(0x4915);
    cpu.set_si(0x706D);
    cpu.set_di(0x538B);
    cpu.set_ip(0xE18F);
    cpu.set_flags(0xF4D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA35AF, 0x27);
    machine.mem_store_byte(0xA35B0, 0x90);
    machine.mem_store_byte(0xA35B1, 0x90);
    machine.mem_store_byte(0xA35B2, 0x90);
    machine.mem_store_byte(0xA35B3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1DA0);
    EXPECT_EQ(cpu.get_ip(), 0xE190);
    EXPECT_FLAGS(0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA35AF), 0x27);
    EXPECT_EQ(memory.load8(0xA35B0), 0x90);
    EXPECT_EQ(memory.load8(0xA35B1), 0x90);
    EXPECT_EQ(memory.load8(0xA35B2), 0x90);
    EXPECT_EQ(memory.load8(0xA35B3), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch16)
{
    // Initial CPU State
    cpu.set_ax(0xD59E);
    cpu.set_bx(0x2DCE);
    cpu.set_cx(0xED64);
    cpu.set_dx(0x9A51);
    cpu.set_cs(0xA1F8);
    cpu.set_ss(0x0156);
    cpu.set_ds(0x6E26);
    cpu.set_es(0xA5E1);
    cpu.set_sp(0x12BA);
    cpu.set_bp(0x4572);
    cpu.set_si(0x2658);
    cpu.set_di(0xCDE7);
    cpu.set_ip(0xAB57);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xACAD7, 0x2F);
    machine.mem_store_byte(0xACAD8, 0x90);
    machine.mem_store_byte(0xACAD9, 0x90);
    machine.mem_store_byte(0xACADA, 0x90);
    machine.mem_store_byte(0xACADB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD538);
    EXPECT_EQ(cpu.get_ip(), 0xAB58);
    EXPECT_FLAGS(0xF813);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xACAD7), 0x2F);
    EXPECT_EQ(memory.load8(0xACAD8), 0x90);
    EXPECT_EQ(memory.load8(0xACAD9), 0x90);
    EXPECT_EQ(memory.load8(0xACADA), 0x90);
    EXPECT_EQ(memory.load8(0xACADB), 0x90);
}
