#include "fixture.h"

// Tests: push

TEST_F(MachineTest, push_ax)
{
    // Initial CPU State
    cpu.set_ax(0xADA0);
    cpu.set_bx(0x4659);
    cpu.set_cx(0x80B4);
    cpu.set_dx(0xCB2D);
    cpu.set_cs(0xC31E);
    cpu.set_ss(0x6708);
    cpu.set_ds(0xDB3E);
    cpu.set_es(0x5C87);
    cpu.set_sp(0xDD6B);
    cpu.set_bp(0xB973);
    cpu.set_si(0xF2CD);
    cpu.set_di(0x7509);
    cpu.set_ip(0x66DB);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC98BB, 0x50);
    machine.mem_store_byte(0xC98BC, 0x90);
    machine.mem_store_byte(0xC98BD, 0x90);
    machine.mem_store_byte(0xC98BE, 0x90);
    machine.mem_store_byte(0xC98BF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xDD69);
    EXPECT_EQ(cpu.get_ip(), 0x66DC);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC98BB), 0x50);
    EXPECT_EQ(memory.load8(0xC98BC), 0x90);
    EXPECT_EQ(memory.load8(0xC98BD), 0x90);
    EXPECT_EQ(memory.load8(0xC98BE), 0x90);
    EXPECT_EQ(memory.load8(0xC98BF), 0x90);
    EXPECT_EQ(memory.load8(0x74DE9), 0xA0);
    EXPECT_EQ(memory.load8(0x74DEA), 0xAD);
}


TEST_F(MachineTest, push_bp)
{
    // Initial CPU State
    cpu.set_ax(0xF451);
    cpu.set_bx(0xEB6B);
    cpu.set_cx(0xA414);
    cpu.set_dx(0x54C8);
    cpu.set_cs(0x00FE);
    cpu.set_ss(0x63DC);
    cpu.set_ds(0x8B23);
    cpu.set_es(0x0623);
    cpu.set_sp(0x7F9E);
    cpu.set_bp(0xC9A5);
    cpu.set_si(0x9605);
    cpu.set_di(0x1EF2);
    cpu.set_ip(0x1174);
    cpu.set_flags(0xF0D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02154, 0xFF);
    machine.mem_store_byte(0x02155, 0xF5);
    machine.mem_store_byte(0x02156, 0x90);
    machine.mem_store_byte(0x02157, 0x90);
    machine.mem_store_byte(0x02158, 0x90);
    machine.mem_store_byte(0x02159, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x7F9C);
    EXPECT_EQ(cpu.get_ip(), 0x1176);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02154), 0xFF);
    EXPECT_EQ(memory.load8(0x02155), 0xF5);
    EXPECT_EQ(memory.load8(0x02156), 0x90);
    EXPECT_EQ(memory.load8(0x02157), 0x90);
    EXPECT_EQ(memory.load8(0x02158), 0x90);
    EXPECT_EQ(memory.load8(0x02159), 0x90);
    EXPECT_EQ(memory.load8(0x6BD5C), 0xA5);
    EXPECT_EQ(memory.load8(0x6BD5D), 0xC9);
}


TEST_F(MachineTest, push_bx)
{
    // Initial CPU State
    cpu.set_ax(0xC483);
    cpu.set_bx(0x41EA);
    cpu.set_cx(0x4102);
    cpu.set_dx(0x6C4E);
    cpu.set_cs(0x63A9);
    cpu.set_ss(0x7B9A);
    cpu.set_ds(0x7573);
    cpu.set_es(0x9945);
    cpu.set_sp(0x7687);
    cpu.set_bp(0xD11F);
    cpu.set_si(0xADF1);
    cpu.set_di(0x475B);
    cpu.set_ip(0xD47C);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x70F0C, 0x53);
    machine.mem_store_byte(0x70F0D, 0x90);
    machine.mem_store_byte(0x70F0E, 0x90);
    machine.mem_store_byte(0x70F0F, 0x90);
    machine.mem_store_byte(0x70F10, 0x90);
    machine.mem_store_byte(0x70F11, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x7685);
    EXPECT_EQ(cpu.get_ip(), 0xD47D);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x70F0C), 0x53);
    EXPECT_EQ(memory.load8(0x70F0D), 0x90);
    EXPECT_EQ(memory.load8(0x70F0E), 0x90);
    EXPECT_EQ(memory.load8(0x70F0F), 0x90);
    EXPECT_EQ(memory.load8(0x70F10), 0x90);
    EXPECT_EQ(memory.load8(0x70F11), 0x90);
    EXPECT_EQ(memory.load8(0x83025), 0xEA);
    EXPECT_EQ(memory.load8(0x83026), 0x41);
}


TEST_F(MachineTest, push_cs)
{
    // Initial CPU State
    cpu.set_ax(0x2418);
    cpu.set_bx(0x1F2A);
    cpu.set_cx(0xE0C0);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x299C);
    cpu.set_ss(0x1959);
    cpu.set_ds(0xBE30);
    cpu.set_es(0x33B1);
    cpu.set_sp(0x85F1);
    cpu.set_bp(0xEE52);
    cpu.set_si(0x9EA3);
    cpu.set_di(0x0FEF);
    cpu.set_ip(0x74A4);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x30E64, 0x0E);
    machine.mem_store_byte(0x30E65, 0x90);
    machine.mem_store_byte(0x30E66, 0x90);
    machine.mem_store_byte(0x30E67, 0x90);
    machine.mem_store_byte(0x30E68, 0x90);
    machine.mem_store_byte(0x30E69, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x85EF);
    EXPECT_EQ(cpu.get_ip(), 0x74A5);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x30E64), 0x0E);
    EXPECT_EQ(memory.load8(0x30E65), 0x90);
    EXPECT_EQ(memory.load8(0x30E66), 0x90);
    EXPECT_EQ(memory.load8(0x30E67), 0x90);
    EXPECT_EQ(memory.load8(0x30E68), 0x90);
    EXPECT_EQ(memory.load8(0x30E69), 0x90);
    EXPECT_EQ(memory.load8(0x21B7F), 0x9C);
    EXPECT_EQ(memory.load8(0x21B80), 0x29);
}


TEST_F(MachineTest, push_cx)
{
    // Initial CPU State
    cpu.set_ax(0x6877);
    cpu.set_bx(0x376C);
    cpu.set_cx(0xC78E);
    cpu.set_dx(0x0ACE);
    cpu.set_cs(0x3EBD);
    cpu.set_ss(0x972F);
    cpu.set_ds(0x34A5);
    cpu.set_es(0xDAD3);
    cpu.set_sp(0xA761);
    cpu.set_bp(0x34B9);
    cpu.set_si(0xE7B7);
    cpu.set_di(0x9337);
    cpu.set_ip(0xC86E);
    cpu.set_flags(0xFC56);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4B43E, 0x51);
    machine.mem_store_byte(0x4B43F, 0x90);
    machine.mem_store_byte(0x4B440, 0x90);
    machine.mem_store_byte(0x4B441, 0x90);
    machine.mem_store_byte(0x4B442, 0x90);
    machine.mem_store_byte(0x4B443, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xA75F);
    EXPECT_EQ(cpu.get_ip(), 0xC86F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4B43E), 0x51);
    EXPECT_EQ(memory.load8(0x4B43F), 0x90);
    EXPECT_EQ(memory.load8(0x4B440), 0x90);
    EXPECT_EQ(memory.load8(0x4B441), 0x90);
    EXPECT_EQ(memory.load8(0x4B442), 0x90);
    EXPECT_EQ(memory.load8(0x4B443), 0x90);
    EXPECT_EQ(memory.load8(0xA1A4F), 0x8E);
    EXPECT_EQ(memory.load8(0xA1A50), 0xC7);
}


TEST_F(MachineTest, push_di)
{
    // Initial CPU State
    cpu.set_ax(0xE835);
    cpu.set_bx(0x8C82);
    cpu.set_cx(0x3E9A);
    cpu.set_dx(0x5A9C);
    cpu.set_cs(0xB722);
    cpu.set_ss(0x46E2);
    cpu.set_ds(0x04F0);
    cpu.set_es(0x1761);
    cpu.set_sp(0x606E);
    cpu.set_bp(0x7BD2);
    cpu.set_si(0x0B7D);
    cpu.set_di(0xFB54);
    cpu.set_ip(0x1165);
    cpu.set_flags(0xFC43);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB8385, 0x57);
    machine.mem_store_byte(0xB8386, 0x90);
    machine.mem_store_byte(0xB8387, 0x90);
    machine.mem_store_byte(0xB8388, 0x90);
    machine.mem_store_byte(0xB8389, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x606C);
    EXPECT_EQ(cpu.get_ip(), 0x1166);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB8385), 0x57);
    EXPECT_EQ(memory.load8(0xB8386), 0x90);
    EXPECT_EQ(memory.load8(0xB8387), 0x90);
    EXPECT_EQ(memory.load8(0xB8388), 0x90);
    EXPECT_EQ(memory.load8(0xB8389), 0x90);
    EXPECT_EQ(memory.load8(0x4CE8C), 0x54);
    EXPECT_EQ(memory.load8(0x4CE8D), 0xFB);
}


TEST_F(MachineTest, push_ds)
{
    // Initial CPU State
    cpu.set_ax(0x9C90);
    cpu.set_bx(0x66F5);
    cpu.set_cx(0x0A54);
    cpu.set_dx(0x80D1);
    cpu.set_cs(0xEF9B);
    cpu.set_ss(0x2E1B);
    cpu.set_ds(0xB0D2);
    cpu.set_es(0xAA86);
    cpu.set_sp(0x4230);
    cpu.set_bp(0xFD03);
    cpu.set_si(0xA217);
    cpu.set_di(0x75D6);
    cpu.set_ip(0x8A65);
    cpu.set_flags(0xFC93);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8415, 0x1E);
    machine.mem_store_byte(0xF8416, 0x90);
    machine.mem_store_byte(0xF8417, 0x90);
    machine.mem_store_byte(0xF8418, 0x90);
    machine.mem_store_byte(0xF8419, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x422E);
    EXPECT_EQ(cpu.get_ip(), 0x8A66);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF8415), 0x1E);
    EXPECT_EQ(memory.load8(0xF8416), 0x90);
    EXPECT_EQ(memory.load8(0xF8417), 0x90);
    EXPECT_EQ(memory.load8(0xF8418), 0x90);
    EXPECT_EQ(memory.load8(0xF8419), 0x90);
    EXPECT_EQ(memory.load8(0x323DE), 0xD2);
    EXPECT_EQ(memory.load8(0x323DF), 0xB0);
}


TEST_F(MachineTest, push_dx)
{
    // Initial CPU State
    cpu.set_ax(0x8941);
    cpu.set_bx(0xCA62);
    cpu.set_cx(0x2558);
    cpu.set_dx(0xBD5C);
    cpu.set_cs(0xA2AF);
    cpu.set_ss(0x50D6);
    cpu.set_ds(0x4AEC);
    cpu.set_es(0x5F8B);
    cpu.set_sp(0x4A8C);
    cpu.set_bp(0x4FF7);
    cpu.set_si(0x9698);
    cpu.set_di(0x7577);
    cpu.set_ip(0x6BE5);
    cpu.set_flags(0xF416);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA96D5, 0x52);
    machine.mem_store_byte(0xA96D6, 0x90);
    machine.mem_store_byte(0xA96D7, 0x90);
    machine.mem_store_byte(0xA96D8, 0x90);
    machine.mem_store_byte(0xA96D9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x4A8A);
    EXPECT_EQ(cpu.get_ip(), 0x6BE6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA96D5), 0x52);
    EXPECT_EQ(memory.load8(0xA96D6), 0x90);
    EXPECT_EQ(memory.load8(0xA96D7), 0x90);
    EXPECT_EQ(memory.load8(0xA96D8), 0x90);
    EXPECT_EQ(memory.load8(0xA96D9), 0x90);
    EXPECT_EQ(memory.load8(0x557EA), 0x5C);
    EXPECT_EQ(memory.load8(0x557EB), 0xBD);
}


TEST_F(MachineTest, push_es)
{
    // Initial CPU State
    cpu.set_ax(0x339C);
    cpu.set_bx(0xB0E4);
    cpu.set_cx(0xBAA8);
    cpu.set_dx(0xAA04);
    cpu.set_cs(0xE899);
    cpu.set_ss(0xEF46);
    cpu.set_ds(0x0C72);
    cpu.set_es(0xDA66);
    cpu.set_sp(0xF9A1);
    cpu.set_bp(0x39A1);
    cpu.set_si(0xA73E);
    cpu.set_di(0x0000);
    cpu.set_ip(0x5891);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE221, 0x06);
    machine.mem_store_byte(0xEE222, 0x90);
    machine.mem_store_byte(0xEE223, 0x90);
    machine.mem_store_byte(0xEE224, 0x90);
    machine.mem_store_byte(0xEE225, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xF99F);
    EXPECT_EQ(cpu.get_ip(), 0x5892);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE221), 0x06);
    EXPECT_EQ(memory.load8(0xEE222), 0x90);
    EXPECT_EQ(memory.load8(0xEE223), 0x90);
    EXPECT_EQ(memory.load8(0xEE224), 0x90);
    EXPECT_EQ(memory.load8(0xEE225), 0x90);
    EXPECT_EQ(memory.load8(0xFEDFF), 0x66);
    EXPECT_EQ(memory.load8(0xFEE00), 0xDA);
}


TEST_F(MachineTest, push_si)
{
    // Initial CPU State
    cpu.set_ax(0x3416);
    cpu.set_bx(0xF97F);
    cpu.set_cx(0x641C);
    cpu.set_dx(0x28B1);
    cpu.set_cs(0xE71F);
    cpu.set_ss(0x1F77);
    cpu.set_ds(0x0C39);
    cpu.set_es(0x803E);
    cpu.set_sp(0xEC40);
    cpu.set_bp(0xC47F);
    cpu.set_si(0x8344);
    cpu.set_di(0xEA7C);
    cpu.set_ip(0x00CC);
    cpu.set_flags(0xF443);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE72BC, 0x56);
    machine.mem_store_byte(0xE72BD, 0x90);
    machine.mem_store_byte(0xE72BE, 0x90);
    machine.mem_store_byte(0xE72BF, 0x90);
    machine.mem_store_byte(0xE72C0, 0x90);
    machine.mem_store_byte(0xE72C1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xEC3E);
    EXPECT_EQ(cpu.get_ip(), 0x00CD);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE72BC), 0x56);
    EXPECT_EQ(memory.load8(0xE72BD), 0x90);
    EXPECT_EQ(memory.load8(0xE72BE), 0x90);
    EXPECT_EQ(memory.load8(0xE72BF), 0x90);
    EXPECT_EQ(memory.load8(0xE72C0), 0x90);
    EXPECT_EQ(memory.load8(0xE72C1), 0x90);
    EXPECT_EQ(memory.load8(0x2E3AE), 0x44);
    EXPECT_EQ(memory.load8(0x2E3AF), 0x83);
}


TEST_F(MachineTest, push_sp)
{
    // Initial CPU State
    cpu.set_ax(0x338E);
    cpu.set_bx(0xF234);
    cpu.set_cx(0xE4BC);
    cpu.set_dx(0x9298);
    cpu.set_cs(0x62E3);
    cpu.set_ss(0xA291);
    cpu.set_ds(0xFC8A);
    cpu.set_es(0xAB57);
    cpu.set_sp(0x6068);
    cpu.set_bp(0xFA28);
    cpu.set_si(0x9832);
    cpu.set_di(0x4DFD);
    cpu.set_ip(0x4F39);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x67D69, 0x54);
    machine.mem_store_byte(0x67D6A, 0x90);
    machine.mem_store_byte(0x67D6B, 0x90);
    machine.mem_store_byte(0x67D6C, 0x90);
    machine.mem_store_byte(0x67D6D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x6066);
    EXPECT_EQ(cpu.get_ip(), 0x4F3A);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x67D69), 0x54);
    EXPECT_EQ(memory.load8(0x67D6A), 0x90);
    EXPECT_EQ(memory.load8(0x67D6B), 0x90);
    EXPECT_EQ(memory.load8(0x67D6C), 0x90);
    EXPECT_EQ(memory.load8(0x67D6D), 0x90);
    EXPECT_EQ(memory.load8(0xA8976), 0x66);
    EXPECT_EQ(memory.load8(0xA8977), 0x60);
}


TEST_F(MachineTest, push_ss)
{
    // Initial CPU State
    cpu.set_ax(0x335A);
    cpu.set_bx(0x2F2B);
    cpu.set_cx(0xD9E8);
    cpu.set_dx(0x3EB8);
    cpu.set_cs(0x6484);
    cpu.set_ss(0xCB15);
    cpu.set_ds(0xB20D);
    cpu.set_es(0xFB95);
    cpu.set_sp(0x85F5);
    cpu.set_bp(0x5E1C);
    cpu.set_si(0x6511);
    cpu.set_di(0x3B34);
    cpu.set_ip(0xAEA6);
    cpu.set_flags(0xF896);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6F6E6, 0x16);
    machine.mem_store_byte(0x6F6E7, 0x90);
    machine.mem_store_byte(0x6F6E8, 0x90);
    machine.mem_store_byte(0x6F6E9, 0x90);
    machine.mem_store_byte(0x6F6EA, 0x90);
    machine.mem_store_byte(0x6F6EB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x85F3);
    EXPECT_EQ(cpu.get_ip(), 0xAEA7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6F6E6), 0x16);
    EXPECT_EQ(memory.load8(0x6F6E7), 0x90);
    EXPECT_EQ(memory.load8(0x6F6E8), 0x90);
    EXPECT_EQ(memory.load8(0x6F6E9), 0x90);
    EXPECT_EQ(memory.load8(0x6F6EA), 0x90);
    EXPECT_EQ(memory.load8(0x6F6EB), 0x90);
    EXPECT_EQ(memory.load8(0xD3743), 0x15);
    EXPECT_EQ(memory.load8(0xD3744), 0xCB);
}


TEST_F(MachineTest, push_word_cs_bx)
{
    // Initial CPU State
    cpu.set_ax(0x81B0);
    cpu.set_bx(0x17FB);
    cpu.set_cx(0xD5A2);
    cpu.set_dx(0x97F9);
    cpu.set_cs(0x296C);
    cpu.set_ss(0xD56B);
    cpu.set_ds(0x6F71);
    cpu.set_es(0xCEB1);
    cpu.set_sp(0x4CA7);
    cpu.set_bp(0x8B27);
    cpu.set_si(0x489B);
    cpu.set_di(0x54FD);
    cpu.set_ip(0xF8A3);
    cpu.set_flags(0xFC87);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x38F63, 0x2E);
    machine.mem_store_byte(0x38F64, 0xFF);
    machine.mem_store_byte(0x38F65, 0x3F);
    machine.mem_store_byte(0x38F66, 0x90);
    machine.mem_store_byte(0x38F67, 0x90);
    machine.mem_store_byte(0x2AEBB, 0x53);
    machine.mem_store_byte(0x2AEBC, 0x44);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x4CA5);
    EXPECT_EQ(cpu.get_ip(), 0xF8A6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x38F63), 0x2E);
    EXPECT_EQ(memory.load8(0x38F64), 0xFF);
    EXPECT_EQ(memory.load8(0x38F65), 0x3F);
    EXPECT_EQ(memory.load8(0x38F66), 0x90);
    EXPECT_EQ(memory.load8(0x38F67), 0x90);
    EXPECT_EQ(memory.load8(0x2AEBB), 0x53);
    EXPECT_EQ(memory.load8(0x2AEBC), 0x44);
    EXPECT_EQ(memory.load8(0xDA355), 0x53);
    EXPECT_EQ(memory.load8(0xDA356), 0x44);
}
