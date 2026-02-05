#include "fixture.h"

//
// pop ax
//
TEST_F(MachineTest, pop_ax)
{
    // Initial CPU State
    cpu.set_ax(0xCB3C);
    cpu.set_bx(0x8B84);
    cpu.set_cx(0x2E0C);
    cpu.set_dx(0x6483);
    cpu.set_cs(0x4F08);
    cpu.set_ss(0x4FB6);
    cpu.set_ds(0xC3AD);
    cpu.set_es(0xC3F3);
    cpu.set_sp(0x2214);
    cpu.set_bp(0x8D85);
    cpu.set_si(0x4A71);
    cpu.set_di(0xB56F);
    cpu.set_ip(0x193A);
    cpu.set_flags(0xFC42);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x509BA, 0x58);
    machine.mem_store_byte(0x509BB, 0x90);
    machine.mem_store_byte(0x509BC, 0x90);
    machine.mem_store_byte(0x509BD, 0x90);
    machine.mem_store_byte(0x51D74, 0x87);
    machine.mem_store_byte(0x51D75, 0xDF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xDF87);
    EXPECT_EQ(cpu.get_sp(), 0x2216);
    EXPECT_EQ(cpu.get_ip(), 0x193B);

    // Final RAM entries
}

//
// pop bp
//
TEST_F(MachineTest, pop_bp)
{
    // Initial CPU State
    cpu.set_ax(0x61D3);
    cpu.set_bx(0x4CD7);
    cpu.set_cx(0x66B0);
    cpu.set_dx(0x1B71);
    cpu.set_cs(0x14A6);
    cpu.set_ss(0xD27C);
    cpu.set_ds(0x6222);
    cpu.set_es(0x045B);
    cpu.set_sp(0xFD6F);
    cpu.set_bp(0xF1C5);
    cpu.set_si(0xEC7D);
    cpu.set_di(0x91A2);
    cpu.set_ip(0x91D9);
    cpu.set_flags(0xFC93);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1DC39, 0x5D);
    machine.mem_store_byte(0x1DC3A, 0x90);
    machine.mem_store_byte(0x1DC3B, 0x90);
    machine.mem_store_byte(0x1DC3C, 0x90);
    machine.mem_store_byte(0xE252F, 0xAB);
    machine.mem_store_byte(0xE2530, 0x14);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xFD71);
    EXPECT_EQ(cpu.get_bp(), 0x14AB);
    EXPECT_EQ(cpu.get_ip(), 0x91DA);

    // Final RAM entries
}

//
// pop bx
//
TEST_F(MachineTest, pop_bx)
{
    // Initial CPU State
    cpu.set_ax(0x1E05);
    cpu.set_bx(0x33CA);
    cpu.set_cx(0x947E);
    cpu.set_dx(0x9B5D);
    cpu.set_cs(0xD5B8);
    cpu.set_ss(0xC52D);
    cpu.set_ds(0x61CE);
    cpu.set_es(0xCDC4);
    cpu.set_sp(0x0880);
    cpu.set_bp(0xFDB5);
    cpu.set_si(0x3418);
    cpu.set_di(0xE2EF);
    cpu.set_ip(0x7B8B);
    cpu.set_flags(0xF013);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDD70B, 0x5B);
    machine.mem_store_byte(0xDD70C, 0x90);
    machine.mem_store_byte(0xDD70D, 0x90);
    machine.mem_store_byte(0xDD70E, 0x90);
    machine.mem_store_byte(0xC5B50, 0x07);
    machine.mem_store_byte(0xC5B51, 0x4E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x4E07);
    EXPECT_EQ(cpu.get_sp(), 0x0882);
    EXPECT_EQ(cpu.get_ip(), 0x7B8C);

    // Final RAM entries
}

//
// pop cx
//
TEST_F(MachineTest, pop_cx)
{
    // Initial CPU State
    cpu.set_ax(0xCE7E);
    cpu.set_bx(0x38C4);
    cpu.set_cx(0x72E8);
    cpu.set_dx(0x0B50);
    cpu.set_cs(0xE7BB);
    cpu.set_ss(0x7D87);
    cpu.set_ds(0x4EB5);
    cpu.set_es(0x88EF);
    cpu.set_sp(0x8823);
    cpu.set_bp(0xC951);
    cpu.set_si(0x28D3);
    cpu.set_di(0x53E6);
    cpu.set_ip(0xA601);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF21B1, 0x59);
    machine.mem_store_byte(0xF21B2, 0x90);
    machine.mem_store_byte(0xF21B3, 0x90);
    machine.mem_store_byte(0xF21B4, 0x90);
    machine.mem_store_byte(0x86093, 0xDE);
    machine.mem_store_byte(0x86094, 0xB6);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xB6DE);
    EXPECT_EQ(cpu.get_sp(), 0x8825);
    EXPECT_EQ(cpu.get_ip(), 0xA602);

    // Final RAM entries
}

//
// pop di
//
TEST_F(MachineTest, pop_di)
{
    // Initial CPU State
    cpu.set_ax(0xD820);
    cpu.set_bx(0x7A75);
    cpu.set_cx(0xC77E);
    cpu.set_dx(0xBA35);
    cpu.set_cs(0x6DB5);
    cpu.set_ss(0x0F0C);
    cpu.set_ds(0x0CBA);
    cpu.set_es(0xD3BA);
    cpu.set_sp(0x156A);
    cpu.set_bp(0x4F94);
    cpu.set_si(0x0644);
    cpu.set_di(0x7FC8);
    cpu.set_ip(0xE591);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7C0E1, 0x5F);
    machine.mem_store_byte(0x7C0E2, 0x90);
    machine.mem_store_byte(0x7C0E3, 0x90);
    machine.mem_store_byte(0x7C0E4, 0x90);
    machine.mem_store_byte(0x1062A, 0x14);
    machine.mem_store_byte(0x1062B, 0x1B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x156C);
    EXPECT_EQ(cpu.get_di(), 0x1B14);
    EXPECT_EQ(cpu.get_ip(), 0xE592);

    // Final RAM entries
}

//
// pop ds
//
TEST_F(MachineTest, pop_ds)
{
    // Initial CPU State
    cpu.set_ax(0x17BB);
    cpu.set_bx(0xA8EB);
    cpu.set_cx(0xE23C);
    cpu.set_dx(0xAAF5);
    cpu.set_cs(0x0D44);
    cpu.set_ss(0x6599);
    cpu.set_ds(0xDFE1);
    cpu.set_es(0x06E2);
    cpu.set_sp(0x2C95);
    cpu.set_bp(0x6559);
    cpu.set_si(0x4D17);
    cpu.set_di(0x265E);
    cpu.set_ip(0xBB85);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x18FC5, 0x1F);
    machine.mem_store_byte(0x18FC6, 0x90);
    machine.mem_store_byte(0x18FC7, 0x90);
    machine.mem_store_byte(0x18FC8, 0x90);
    machine.mem_store_byte(0x68625, 0xF1);
    machine.mem_store_byte(0x68626, 0xD7);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ds(), 0xD7F1);
    EXPECT_EQ(cpu.get_sp(), 0x2C97);
    EXPECT_EQ(cpu.get_ip(), 0xBB86);

    // Final RAM entries
}

//
// pop dx
//
TEST_F(MachineTest, pop_dx)
{
    // Initial CPU State
    cpu.set_ax(0xB3D6);
    cpu.set_bx(0xDD0C);
    cpu.set_cx(0x5764);
    cpu.set_dx(0x8F32);
    cpu.set_cs(0x0F6E);
    cpu.set_ss(0x09AF);
    cpu.set_ds(0x17CD);
    cpu.set_es(0x1782);
    cpu.set_sp(0xAF8C);
    cpu.set_bp(0x79A1);
    cpu.set_si(0xB48D);
    cpu.set_di(0x7FD7);
    cpu.set_ip(0xB5BB);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1AC9B, 0x5A);
    machine.mem_store_byte(0x1AC9C, 0x90);
    machine.mem_store_byte(0x1AC9D, 0x90);
    machine.mem_store_byte(0x1AC9E, 0x90);
    machine.mem_store_byte(0x14A7C, 0x72);
    machine.mem_store_byte(0x14A7D, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0072);
    EXPECT_EQ(cpu.get_sp(), 0xAF8E);
    EXPECT_EQ(cpu.get_ip(), 0xB5BC);

    // Final RAM entries
}

//
// pop es
//
TEST_F(MachineTest, pop_es)
{
    // Initial CPU State
    cpu.set_ax(0xB80E);
    cpu.set_bx(0xFDB5);
    cpu.set_cx(0x33EE);
    cpu.set_dx(0xE214);
    cpu.set_cs(0x7BD3);
    cpu.set_ss(0x42ED);
    cpu.set_ds(0xFE59);
    cpu.set_es(0xB313);
    cpu.set_sp(0xFF22);
    cpu.set_bp(0x7033);
    cpu.set_si(0xE35E);
    cpu.set_di(0x4592);
    cpu.set_ip(0xDCD0);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x89A00, 0x07);
    machine.mem_store_byte(0x89A01, 0x90);
    machine.mem_store_byte(0x89A02, 0x90);
    machine.mem_store_byte(0x89A03, 0x90);
    machine.mem_store_byte(0x52DF2, 0x23);
    machine.mem_store_byte(0x52DF3, 0x8C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_es(), 0x8C23);
    EXPECT_EQ(cpu.get_sp(), 0xFF24);
    EXPECT_EQ(cpu.get_ip(), 0xDCD1);

    // Final RAM entries
}

//
// pop si
//
TEST_F(MachineTest, pop_si)
{
    // Initial CPU State
    cpu.set_ax(0xD0DC);
    cpu.set_bx(0x5A36);
    cpu.set_cx(0xB2CA);
    cpu.set_dx(0xA8D6);
    cpu.set_cs(0x1A02);
    cpu.set_ss(0x3F40);
    cpu.set_ds(0xF062);
    cpu.set_es(0xD5FD);
    cpu.set_sp(0x297A);
    cpu.set_bp(0xE7B1);
    cpu.set_si(0xD725);
    cpu.set_di(0x5693);
    cpu.set_ip(0xFDAB);
    cpu.set_flags(0xF457);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x29DCB, 0x5E);
    machine.mem_store_byte(0x29DCC, 0x90);
    machine.mem_store_byte(0x29DCD, 0x90);
    machine.mem_store_byte(0x29DCE, 0x90);
    machine.mem_store_byte(0x41D7A, 0x41);
    machine.mem_store_byte(0x41D7B, 0x9A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x297C);
    EXPECT_EQ(cpu.get_si(), 0x9A41);
    EXPECT_EQ(cpu.get_ip(), 0xFDAC);

    // Final RAM entries
}

//
// pop sp
//
TEST_F(MachineTest, pop_sp)
{
    // Initial CPU State
    cpu.set_ax(0xF709);
    cpu.set_bx(0xC182);
    cpu.set_cx(0xFB6A);
    cpu.set_dx(0x7D51);
    cpu.set_cs(0x4506);
    cpu.set_ss(0x0561);
    cpu.set_ds(0x0BE6);
    cpu.set_es(0x7BFF);
    cpu.set_sp(0xE9AC);
    cpu.set_bp(0x6A9B);
    cpu.set_si(0xBB82);
    cpu.set_di(0xC583);
    cpu.set_ip(0x06A2);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x45702, 0x5C);
    machine.mem_store_byte(0x45703, 0x90);
    machine.mem_store_byte(0x45704, 0x90);
    machine.mem_store_byte(0x45705, 0x90);
    machine.mem_store_byte(0x13FBC, 0xDC);
    machine.mem_store_byte(0x13FBD, 0x82);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x82DC);
    EXPECT_EQ(cpu.get_ip(), 0x06A3);

    // Final RAM entries
}

//
// pop ss
//
TEST_F(MachineTest, pop_ss)
{
    // Initial CPU State
    cpu.set_ax(0x6F01);
    cpu.set_bx(0xF3CB);
    cpu.set_cx(0xBF0A);
    cpu.set_dx(0x96B3);
    cpu.set_cs(0x16D8);
    cpu.set_ss(0xDCD3);
    cpu.set_ds(0x1A48);
    cpu.set_es(0xF923);
    cpu.set_sp(0x9631);
    cpu.set_bp(0xD6C5);
    cpu.set_si(0x3F69);
    cpu.set_di(0x9B40);
    cpu.set_ip(0x9359);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x200D9, 0x17);
    machine.mem_store_byte(0x200DA, 0x90);
    machine.mem_store_byte(0x200DB, 0x90);
    machine.mem_store_byte(0x200DC, 0x90);
    machine.mem_store_byte(0xE6361, 0x55);
    machine.mem_store_byte(0xE6362, 0x0B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ss(), 0x0B55);
    EXPECT_EQ(cpu.get_sp(), 0x9633);
    EXPECT_EQ(cpu.get_ip(), 0x935A);

    // Final RAM entries
}

//
// pop word [ds:si+6BC0h]
//
TEST_F(MachineTest, pop_word_ds_si_6BC0h)
{
    // Initial CPU State
    cpu.set_ax(0xAD2E);
    cpu.set_bx(0xB2BE);
    cpu.set_cx(0x5920);
    cpu.set_dx(0x20A1);
    cpu.set_cs(0x39E8);
    cpu.set_ss(0x19DE);
    cpu.set_ds(0x76F4);
    cpu.set_es(0x7326);
    cpu.set_sp(0xA732);
    cpu.set_bp(0x8350);
    cpu.set_si(0xCE22);
    cpu.set_di(0x816C);
    cpu.set_ip(0x5AD2);
    cpu.set_flags(0xF493);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3F952, 0x8F);
    machine.mem_store_byte(0x3F953, 0x84);
    machine.mem_store_byte(0x3F954, 0xC0);
    machine.mem_store_byte(0x3F955, 0x6B);
    machine.mem_store_byte(0x24512, 0xF0);
    machine.mem_store_byte(0x24513, 0xA3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xA734);
    EXPECT_EQ(cpu.get_ip(), 0x5AD6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7A922), 0xF0);
    EXPECT_EQ(memory.load8(0x7A923), 0xA3);
}
