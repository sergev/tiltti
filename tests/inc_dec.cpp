#include "fixture.h"

// Tests: inc, dec

TEST_F(MachineTest, dec_ax)
{
    // Initial CPU State
    cpu.set_ax(0x31C6);
    cpu.set_bx(0x7D48);
    cpu.set_cx(0x4E92);
    cpu.set_dx(0x96DB);
    cpu.set_cs(0xC11A);
    cpu.set_ss(0xA850);
    cpu.set_ds(0xEFA1);
    cpu.set_es(0x37E3);
    cpu.set_sp(0xD007);
    cpu.set_bp(0x5E71);
    cpu.set_si(0x0000);
    cpu.set_di(0xD5C0);
    cpu.set_ip(0x8D9C);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC9F3C, 0x48);
    machine.mem_store_byte(0xC9F3D, 0x90);
    machine.mem_store_byte(0xC9F3E, 0x90);
    machine.mem_store_byte(0xC9F3F, 0x90);
    machine.mem_store_byte(0xC9F40, 0x90);
    machine.mem_store_byte(0xC9F41, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x31C5);
    EXPECT_EQ(cpu.get_ip(), 0x8D9D);
    EXPECT_EQ(cpu.get_flags(), 0xF407) << show_flags(0xF407);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC9F3C), 0x48);
    EXPECT_EQ(memory.load8(0xC9F3D), 0x90);
    EXPECT_EQ(memory.load8(0xC9F3E), 0x90);
    EXPECT_EQ(memory.load8(0xC9F3F), 0x90);
    EXPECT_EQ(memory.load8(0xC9F40), 0x90);
    EXPECT_EQ(memory.load8(0xC9F41), 0x90);
}

TEST_F(MachineTest, dec_bp)
{
    // Initial CPU State
    cpu.set_ax(0x0990);
    cpu.set_bx(0x7EC0);
    cpu.set_cx(0x6FFE);
    cpu.set_dx(0x6341);
    cpu.set_cs(0x398A);
    cpu.set_ss(0x731F);
    cpu.set_ds(0x476E);
    cpu.set_es(0x4986);
    cpu.set_sp(0xF7DF);
    cpu.set_bp(0x3EA7);
    cpu.set_si(0x3A67);
    cpu.set_di(0xDCF5);
    cpu.set_ip(0xF749);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x48FE9, 0x4D);
    machine.mem_store_byte(0x48FEA, 0x90);
    machine.mem_store_byte(0x48FEB, 0x90);
    machine.mem_store_byte(0x48FEC, 0x90);
    machine.mem_store_byte(0x48FED, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x3EA6);
    EXPECT_EQ(cpu.get_ip(), 0xF74A);
    EXPECT_EQ(cpu.get_flags(), 0xF007) << show_flags(0xF007);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x48FE9), 0x4D);
    EXPECT_EQ(memory.load8(0x48FEA), 0x90);
    EXPECT_EQ(memory.load8(0x48FEB), 0x90);
    EXPECT_EQ(memory.load8(0x48FEC), 0x90);
    EXPECT_EQ(memory.load8(0x48FED), 0x90);
}

TEST_F(MachineTest, dec_bx)
{
    // Initial CPU State
    cpu.set_ax(0xB794);
    cpu.set_bx(0x813D);
    cpu.set_cx(0x7236);
    cpu.set_dx(0xEC43);
    cpu.set_cs(0x1BA6);
    cpu.set_ss(0xD055);
    cpu.set_ds(0xCC87);
    cpu.set_es(0xBAE4);
    cpu.set_sp(0x5AED);
    cpu.set_bp(0x74BD);
    cpu.set_si(0xA658);
    cpu.set_di(0x47D0);
    cpu.set_ip(0xC7B2);
    cpu.set_flags(0xF002);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x28212, 0x4B);
    machine.mem_store_byte(0x28213, 0x90);
    machine.mem_store_byte(0x28214, 0x90);
    machine.mem_store_byte(0x28215, 0x90);
    machine.mem_store_byte(0x28216, 0x90);
    machine.mem_store_byte(0x28217, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x813C);
    EXPECT_EQ(cpu.get_ip(), 0xC7B3);
    EXPECT_EQ(cpu.get_flags(), 0xF086) << show_flags(0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x28212), 0x4B);
    EXPECT_EQ(memory.load8(0x28213), 0x90);
    EXPECT_EQ(memory.load8(0x28214), 0x90);
    EXPECT_EQ(memory.load8(0x28215), 0x90);
    EXPECT_EQ(memory.load8(0x28216), 0x90);
    EXPECT_EQ(memory.load8(0x28217), 0x90);
}

TEST_F(MachineTest, dec_byte_ss_bp_di_1Dh)
{
    // Initial CPU State
    cpu.set_ax(0xCBEC);
    cpu.set_bx(0x44F1);
    cpu.set_cx(0x0000);
    cpu.set_dx(0xD75F);
    cpu.set_cs(0xE429);
    cpu.set_ss(0x01EC);
    cpu.set_ds(0xED8E);
    cpu.set_es(0x0214);
    cpu.set_sp(0xF190);
    cpu.set_bp(0x94D6);
    cpu.set_si(0x8989);
    cpu.set_di(0x64AE);
    cpu.set_ip(0x3E97);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE8127, 0xFE);
    machine.mem_store_byte(0xE8128, 0x4B);
    machine.mem_store_byte(0xE8129, 0xE3);
    machine.mem_store_byte(0xE812A, 0x90);
    machine.mem_store_byte(0xE812B, 0x90);
    machine.mem_store_byte(0x11827, 0x7F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3E9A);
    EXPECT_EQ(cpu.get_flags(), 0xF406) << show_flags(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE8127), 0xFE);
    EXPECT_EQ(memory.load8(0xE8128), 0x4B);
    EXPECT_EQ(memory.load8(0xE8129), 0xE3);
    EXPECT_EQ(memory.load8(0xE812A), 0x90);
    EXPECT_EQ(memory.load8(0xE812B), 0x90);
    EXPECT_EQ(memory.load8(0x11827), 0x7E);
}

TEST_F(MachineTest, dec_cx)
{
    // Initial CPU State
    cpu.set_ax(0x65C1);
    cpu.set_bx(0xFF53);
    cpu.set_cx(0xBF5C);
    cpu.set_dx(0x3152);
    cpu.set_cs(0x7A7B);
    cpu.set_ss(0xD04D);
    cpu.set_ds(0xC8A2);
    cpu.set_es(0xFBE2);
    cpu.set_sp(0x9F88);
    cpu.set_bp(0x802C);
    cpu.set_si(0x64D0);
    cpu.set_di(0x0000);
    cpu.set_ip(0xB9A0);
    cpu.set_flags(0xF407);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x86150, 0x49);
    machine.mem_store_byte(0x86151, 0x90);
    machine.mem_store_byte(0x86152, 0x90);
    machine.mem_store_byte(0x86153, 0x90);
    machine.mem_store_byte(0x86154, 0x90);
    machine.mem_store_byte(0x86155, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xBF5B);
    EXPECT_EQ(cpu.get_ip(), 0xB9A1);
    EXPECT_EQ(cpu.get_flags(), 0xF483) << show_flags(0xF483);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x86150), 0x49);
    EXPECT_EQ(memory.load8(0x86151), 0x90);
    EXPECT_EQ(memory.load8(0x86152), 0x90);
    EXPECT_EQ(memory.load8(0x86153), 0x90);
    EXPECT_EQ(memory.load8(0x86154), 0x90);
    EXPECT_EQ(memory.load8(0x86155), 0x90);
}

TEST_F(MachineTest, dec_di)
{
    // Initial CPU State
    cpu.set_ax(0x84ED);
    cpu.set_bx(0x7A20);
    cpu.set_cx(0xBB7A);
    cpu.set_dx(0xBD8B);
    cpu.set_cs(0x9FAE);
    cpu.set_ss(0x0E19);
    cpu.set_ds(0x5BF5);
    cpu.set_es(0xDE28);
    cpu.set_sp(0xDF97);
    cpu.set_bp(0xDC43);
    cpu.set_si(0xE6F9);
    cpu.set_di(0x2B11);
    cpu.set_ip(0x2260);
    cpu.set_flags(0xFC43);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA1D40, 0x4F);
    machine.mem_store_byte(0xA1D41, 0x90);
    machine.mem_store_byte(0xA1D42, 0x90);
    machine.mem_store_byte(0xA1D43, 0x90);
    machine.mem_store_byte(0xA1D44, 0x90);
    machine.mem_store_byte(0xA1D45, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x2B10);
    EXPECT_EQ(cpu.get_ip(), 0x2261);
    EXPECT_EQ(cpu.get_flags(), 0xF403) << show_flags(0xF403);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA1D40), 0x4F);
    EXPECT_EQ(memory.load8(0xA1D41), 0x90);
    EXPECT_EQ(memory.load8(0xA1D42), 0x90);
    EXPECT_EQ(memory.load8(0xA1D43), 0x90);
    EXPECT_EQ(memory.load8(0xA1D44), 0x90);
    EXPECT_EQ(memory.load8(0xA1D45), 0x90);
}

TEST_F(MachineTest, dec_dx)
{
    // Initial CPU State
    cpu.set_ax(0xBF45);
    cpu.set_bx(0x5093);
    cpu.set_cx(0x97A0);
    cpu.set_dx(0x05B9);
    cpu.set_cs(0xF281);
    cpu.set_ss(0x60C9);
    cpu.set_ds(0xF3DE);
    cpu.set_es(0x24D5);
    cpu.set_sp(0x0096);
    cpu.set_bp(0x2F21);
    cpu.set_si(0xE4D8);
    cpu.set_di(0x571C);
    cpu.set_ip(0x87A9);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFAFB9, 0x4A);
    machine.mem_store_byte(0xFAFBA, 0x90);
    machine.mem_store_byte(0xFAFBB, 0x90);
    machine.mem_store_byte(0xFAFBC, 0x90);
    machine.mem_store_byte(0xFAFBD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x05B8);
    EXPECT_EQ(cpu.get_ip(), 0x87AA);
    EXPECT_EQ(cpu.get_flags(), 0xF007) << show_flags(0xF007);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFAFB9), 0x4A);
    EXPECT_EQ(memory.load8(0xFAFBA), 0x90);
    EXPECT_EQ(memory.load8(0xFAFBB), 0x90);
    EXPECT_EQ(memory.load8(0xFAFBC), 0x90);
    EXPECT_EQ(memory.load8(0xFAFBD), 0x90);
}

TEST_F(MachineTest, dec_si)
{
    // Initial CPU State
    cpu.set_ax(0x1A77);
    cpu.set_bx(0x455E);
    cpu.set_cx(0x4CFA);
    cpu.set_dx(0xB981);
    cpu.set_cs(0x85B4);
    cpu.set_ss(0x1BDD);
    cpu.set_ds(0x4FAA);
    cpu.set_es(0x1065);
    cpu.set_sp(0x9055);
    cpu.set_bp(0x5414);
    cpu.set_si(0xE174);
    cpu.set_di(0x4EDD);
    cpu.set_ip(0xA870);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x903B0, 0x4E);
    machine.mem_store_byte(0x903B1, 0x90);
    machine.mem_store_byte(0x903B2, 0x90);
    machine.mem_store_byte(0x903B3, 0x90);
    machine.mem_store_byte(0x903B4, 0x90);
    machine.mem_store_byte(0x903B5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0xE173);
    EXPECT_EQ(cpu.get_ip(), 0xA871);
    EXPECT_EQ(cpu.get_flags(), 0xF482) << show_flags(0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x903B0), 0x4E);
    EXPECT_EQ(memory.load8(0x903B1), 0x90);
    EXPECT_EQ(memory.load8(0x903B2), 0x90);
    EXPECT_EQ(memory.load8(0x903B3), 0x90);
    EXPECT_EQ(memory.load8(0x903B4), 0x90);
    EXPECT_EQ(memory.load8(0x903B5), 0x90);
}

TEST_F(MachineTest, dec_sp)
{
    // Initial CPU State
    cpu.set_ax(0x4E64);
    cpu.set_bx(0x6150);
    cpu.set_cx(0xA062);
    cpu.set_dx(0xF03E);
    cpu.set_cs(0x9D80);
    cpu.set_ss(0x59FB);
    cpu.set_ds(0xD3A4);
    cpu.set_es(0x6873);
    cpu.set_sp(0x1080);
    cpu.set_bp(0xE62D);
    cpu.set_si(0x804B);
    cpu.set_di(0xD7C9);
    cpu.set_ip(0xE732);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xABF32, 0x4C);
    machine.mem_store_byte(0xABF33, 0x90);
    machine.mem_store_byte(0xABF34, 0x90);
    machine.mem_store_byte(0xABF35, 0x90);
    machine.mem_store_byte(0xABF36, 0x90);
    machine.mem_store_byte(0xABF37, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x107F);
    EXPECT_EQ(cpu.get_ip(), 0xE733);
    EXPECT_EQ(cpu.get_flags(), 0xF413) << show_flags(0xF413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xABF32), 0x4C);
    EXPECT_EQ(memory.load8(0xABF33), 0x90);
    EXPECT_EQ(memory.load8(0xABF34), 0x90);
    EXPECT_EQ(memory.load8(0xABF35), 0x90);
    EXPECT_EQ(memory.load8(0xABF36), 0x90);
    EXPECT_EQ(memory.load8(0xABF37), 0x90);
}

TEST_F(MachineTest, dec_word_es_si_3AE9h)
{
    // Initial CPU State
    cpu.set_ax(0x6AF1);
    cpu.set_bx(0x8A14);
    cpu.set_cx(0xF8D6);
    cpu.set_dx(0x0BCC);
    cpu.set_cs(0xC1AE);
    cpu.set_ss(0x3FA2);
    cpu.set_ds(0x4DDB);
    cpu.set_es(0xB82D);
    cpu.set_sp(0x1626);
    cpu.set_bp(0x0000);
    cpu.set_si(0x0000);
    cpu.set_di(0xCCC2);
    cpu.set_ip(0x2FF2);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC4AD2, 0x26);
    machine.mem_store_byte(0xC4AD3, 0xFF);
    machine.mem_store_byte(0xC4AD4, 0x8C);
    machine.mem_store_byte(0xC4AD5, 0x17);
    machine.mem_store_byte(0xC4AD6, 0xC5);
    machine.mem_store_byte(0xC4AD7, 0x90);
    machine.mem_store_byte(0xC47E7, 0x5C);
    machine.mem_store_byte(0xC47E8, 0x2F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2FF7);
    EXPECT_EQ(cpu.get_flags(), 0xF002) << show_flags(0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC4AD2), 0x26);
    EXPECT_EQ(memory.load8(0xC4AD3), 0xFF);
    EXPECT_EQ(memory.load8(0xC4AD4), 0x8C);
    EXPECT_EQ(memory.load8(0xC4AD5), 0x17);
    EXPECT_EQ(memory.load8(0xC4AD6), 0xC5);
    EXPECT_EQ(memory.load8(0xC4AD7), 0x90);
    EXPECT_EQ(memory.load8(0xC47E7), 0x5B);
    EXPECT_EQ(memory.load8(0xC47E8), 0x2F);
}

TEST_F(MachineTest, inc_ax)
{
    // Initial CPU State
    cpu.set_ax(0x9AA8);
    cpu.set_bx(0x5CE7);
    cpu.set_cx(0x267C);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x3014);
    cpu.set_ss(0x7879);
    cpu.set_ds(0x6C7B);
    cpu.set_es(0xEC13);
    cpu.set_sp(0x19B2);
    cpu.set_bp(0xBEB0);
    cpu.set_si(0xE8CD);
    cpu.set_di(0x1D32);
    cpu.set_ip(0xD387);
    cpu.set_flags(0xFC47);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3D4C7, 0x40);
    machine.mem_store_byte(0x3D4C8, 0x90);
    machine.mem_store_byte(0x3D4C9, 0x90);
    machine.mem_store_byte(0x3D4CA, 0x90);
    machine.mem_store_byte(0x3D4CB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9AA9);
    EXPECT_EQ(cpu.get_ip(), 0xD388);
    EXPECT_EQ(cpu.get_flags(), 0xF487) << show_flags(0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3D4C7), 0x40);
    EXPECT_EQ(memory.load8(0x3D4C8), 0x90);
    EXPECT_EQ(memory.load8(0x3D4C9), 0x90);
    EXPECT_EQ(memory.load8(0x3D4CA), 0x90);
    EXPECT_EQ(memory.load8(0x3D4CB), 0x90);
}

TEST_F(MachineTest, inc_bp)
{
    // Initial CPU State
    cpu.set_ax(0xF411);
    cpu.set_bx(0x07B3);
    cpu.set_cx(0xDF36);
    cpu.set_dx(0x1B99);
    cpu.set_cs(0x008C);
    cpu.set_ss(0x887C);
    cpu.set_ds(0x05E4);
    cpu.set_es(0xE5FE);
    cpu.set_sp(0xA3C9);
    cpu.set_bp(0x19F1);
    cpu.set_si(0xAE8E);
    cpu.set_di(0x9175);
    cpu.set_ip(0x17AC);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0206C, 0x45);
    machine.mem_store_byte(0x0206D, 0x90);
    machine.mem_store_byte(0x0206E, 0x90);
    machine.mem_store_byte(0x0206F, 0x90);
    machine.mem_store_byte(0x02070, 0x90);
    machine.mem_store_byte(0x02071, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x19F2);
    EXPECT_EQ(cpu.get_ip(), 0x17AD);
    EXPECT_EQ(cpu.get_flags(), 0xF002) << show_flags(0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0206C), 0x45);
    EXPECT_EQ(memory.load8(0x0206D), 0x90);
    EXPECT_EQ(memory.load8(0x0206E), 0x90);
    EXPECT_EQ(memory.load8(0x0206F), 0x90);
    EXPECT_EQ(memory.load8(0x02070), 0x90);
    EXPECT_EQ(memory.load8(0x02071), 0x90);
}

TEST_F(MachineTest, inc_bx)
{
    // Initial CPU State
    cpu.set_ax(0x07E9);
    cpu.set_bx(0xB4CA);
    cpu.set_cx(0x3474);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x0FAC);
    cpu.set_ss(0x315C);
    cpu.set_ds(0x8C62);
    cpu.set_es(0x7651);
    cpu.set_sp(0x43C3);
    cpu.set_bp(0x06FC);
    cpu.set_si(0xF8E5);
    cpu.set_di(0x4855);
    cpu.set_ip(0x634F);
    cpu.set_flags(0xF492);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x15E0F, 0x43);
    machine.mem_store_byte(0x15E10, 0x90);
    machine.mem_store_byte(0x15E11, 0x90);
    machine.mem_store_byte(0x15E12, 0x90);
    machine.mem_store_byte(0x15E13, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xB4CB);
    EXPECT_EQ(cpu.get_ip(), 0x6350);
    EXPECT_EQ(cpu.get_flags(), 0xF482) << show_flags(0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x15E0F), 0x43);
    EXPECT_EQ(memory.load8(0x15E10), 0x90);
    EXPECT_EQ(memory.load8(0x15E11), 0x90);
    EXPECT_EQ(memory.load8(0x15E12), 0x90);
    EXPECT_EQ(memory.load8(0x15E13), 0x90);
}

TEST_F(MachineTest, inc_byte_ss_bp_di)
{
    // Initial CPU State
    cpu.set_ax(0x76D3);
    cpu.set_bx(0xDD7A);
    cpu.set_cx(0xCEFA);
    cpu.set_dx(0xA4E9);
    cpu.set_cs(0xFBC5);
    cpu.set_ss(0x9048);
    cpu.set_ds(0xF0B8);
    cpu.set_es(0x5CAD);
    cpu.set_sp(0x42BB);
    cpu.set_bp(0x5C60);
    cpu.set_si(0x39F8);
    cpu.set_di(0x8667);
    cpu.set_ip(0xF81A);
    cpu.set_flags(0xF8C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0B46A, 0xFE);
    machine.mem_store_byte(0x0B46B, 0x03);
    machine.mem_store_byte(0x0B46C, 0x90);
    machine.mem_store_byte(0x0B46D, 0x90);
    machine.mem_store_byte(0x0B46E, 0x90);
    machine.mem_store_byte(0x0B46F, 0x90);
    machine.mem_store_byte(0x9E747, 0x1C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF81C);
    EXPECT_EQ(cpu.get_flags(), 0xF006) << show_flags(0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0B46A), 0xFE);
    EXPECT_EQ(memory.load8(0x0B46B), 0x03);
    EXPECT_EQ(memory.load8(0x0B46C), 0x90);
    EXPECT_EQ(memory.load8(0x0B46D), 0x90);
    EXPECT_EQ(memory.load8(0x0B46E), 0x90);
    EXPECT_EQ(memory.load8(0x0B46F), 0x90);
    EXPECT_EQ(memory.load8(0x9E747), 0x1D);
}

TEST_F(MachineTest, inc_cx)
{
    // Initial CPU State
    cpu.set_ax(0xDF64);
    cpu.set_bx(0x4A93);
    cpu.set_cx(0x4C7C);
    cpu.set_dx(0xD95D);
    cpu.set_cs(0x5AA1);
    cpu.set_ss(0x23D4);
    cpu.set_ds(0xC0FB);
    cpu.set_es(0x6109);
    cpu.set_sp(0x430F);
    cpu.set_bp(0x2561);
    cpu.set_si(0x0D94);
    cpu.set_di(0xECA0);
    cpu.set_ip(0xA5E8);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x64FF8, 0x41);
    machine.mem_store_byte(0x64FF9, 0x90);
    machine.mem_store_byte(0x64FFA, 0x90);
    machine.mem_store_byte(0x64FFB, 0x90);
    machine.mem_store_byte(0x64FFC, 0x90);
    machine.mem_store_byte(0x64FFD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x4C7D);
    EXPECT_EQ(cpu.get_ip(), 0xA5E9);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x64FF8), 0x41);
    EXPECT_EQ(memory.load8(0x64FF9), 0x90);
    EXPECT_EQ(memory.load8(0x64FFA), 0x90);
    EXPECT_EQ(memory.load8(0x64FFB), 0x90);
    EXPECT_EQ(memory.load8(0x64FFC), 0x90);
    EXPECT_EQ(memory.load8(0x64FFD), 0x90);
}

TEST_F(MachineTest, inc_di)
{
    // Initial CPU State
    cpu.set_ax(0xBA92);
    cpu.set_bx(0x691D);
    cpu.set_cx(0x186E);
    cpu.set_dx(0xFE5F);
    cpu.set_cs(0x5D85);
    cpu.set_ss(0x60D1);
    cpu.set_ds(0xC82B);
    cpu.set_es(0x8F69);
    cpu.set_sp(0xA811);
    cpu.set_bp(0x5671);
    cpu.set_si(0x47C9);
    cpu.set_di(0xAAFF);
    cpu.set_ip(0xFA7B);
    cpu.set_flags(0xF457);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6D2CB, 0x47);
    machine.mem_store_byte(0x6D2CC, 0x90);
    machine.mem_store_byte(0x6D2CD, 0x90);
    machine.mem_store_byte(0x6D2CE, 0x90);
    machine.mem_store_byte(0x6D2CF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xAB00);
    EXPECT_EQ(cpu.get_ip(), 0xFA7C);
    EXPECT_EQ(cpu.get_flags(), 0xF497) << show_flags(0xF497);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6D2CB), 0x47);
    EXPECT_EQ(memory.load8(0x6D2CC), 0x90);
    EXPECT_EQ(memory.load8(0x6D2CD), 0x90);
    EXPECT_EQ(memory.load8(0x6D2CE), 0x90);
    EXPECT_EQ(memory.load8(0x6D2CF), 0x90);
}

TEST_F(MachineTest, inc_dx)
{
    // Initial CPU State
    cpu.set_ax(0x6A31);
    cpu.set_bx(0xC483);
    cpu.set_cx(0xA0F6);
    cpu.set_dx(0xEEFC);
    cpu.set_cs(0xC6E9);
    cpu.set_ss(0x321F);
    cpu.set_ds(0x0888);
    cpu.set_es(0x37BC);
    cpu.set_sp(0x0608);
    cpu.set_bp(0xF43F);
    cpu.set_si(0xE82B);
    cpu.set_di(0x8007);
    cpu.set_ip(0x0B2F);
    cpu.set_flags(0xF483);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC79BF, 0x42);
    machine.mem_store_byte(0xC79C0, 0x90);
    machine.mem_store_byte(0xC79C1, 0x90);
    machine.mem_store_byte(0xC79C2, 0x90);
    machine.mem_store_byte(0xC79C3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xEEFD);
    EXPECT_EQ(cpu.get_ip(), 0x0B30);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC79BF), 0x42);
    EXPECT_EQ(memory.load8(0xC79C0), 0x90);
    EXPECT_EQ(memory.load8(0xC79C1), 0x90);
    EXPECT_EQ(memory.load8(0xC79C2), 0x90);
    EXPECT_EQ(memory.load8(0xC79C3), 0x90);
}

TEST_F(MachineTest, inc_si)
{
    // Initial CPU State
    cpu.set_ax(0x4EDC);
    cpu.set_bx(0x558B);
    cpu.set_cx(0x383A);
    cpu.set_dx(0x35FB);
    cpu.set_cs(0xD635);
    cpu.set_ss(0xAB92);
    cpu.set_ds(0x0011);
    cpu.set_es(0x9AD7);
    cpu.set_sp(0xF9CC);
    cpu.set_bp(0x1252);
    cpu.set_si(0xE917);
    cpu.set_di(0x8104);
    cpu.set_ip(0xE24F);
    cpu.set_flags(0xF412);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE459F, 0x46);
    machine.mem_store_byte(0xE45A0, 0x90);
    machine.mem_store_byte(0xE45A1, 0x90);
    machine.mem_store_byte(0xE45A2, 0x90);
    machine.mem_store_byte(0xE45A3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0xE918);
    EXPECT_EQ(cpu.get_ip(), 0xE250);
    EXPECT_EQ(cpu.get_flags(), 0xF486) << show_flags(0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE459F), 0x46);
    EXPECT_EQ(memory.load8(0xE45A0), 0x90);
    EXPECT_EQ(memory.load8(0xE45A1), 0x90);
    EXPECT_EQ(memory.load8(0xE45A2), 0x90);
    EXPECT_EQ(memory.load8(0xE45A3), 0x90);
}

TEST_F(MachineTest, inc_sp)
{
    // Initial CPU State
    cpu.set_ax(0x7837);
    cpu.set_bx(0x71CD);
    cpu.set_cx(0x3610);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xC97B);
    cpu.set_ss(0xAEAE);
    cpu.set_ds(0x4E20);
    cpu.set_es(0x1BF4);
    cpu.set_sp(0x0235);
    cpu.set_bp(0x6910);
    cpu.set_si(0x8B55);
    cpu.set_di(0x891A);
    cpu.set_ip(0xEF7D);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD872D, 0x44);
    machine.mem_store_byte(0xD872E, 0x90);
    machine.mem_store_byte(0xD872F, 0x90);
    machine.mem_store_byte(0xD8730, 0x90);
    machine.mem_store_byte(0xD8731, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x0236);
    EXPECT_EQ(cpu.get_ip(), 0xEF7E);
    EXPECT_EQ(cpu.get_flags(), 0xF406) << show_flags(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD872D), 0x44);
    EXPECT_EQ(memory.load8(0xD872E), 0x90);
    EXPECT_EQ(memory.load8(0xD872F), 0x90);
    EXPECT_EQ(memory.load8(0xD8730), 0x90);
    EXPECT_EQ(memory.load8(0xD8731), 0x90);
}

TEST_F(MachineTest, inc_word_ss_bp_4Ch)
{
    // Initial CPU State
    cpu.set_ax(0x0E1F);
    cpu.set_bx(0xEE2D);
    cpu.set_cx(0xF48E);
    cpu.set_dx(0x3AD8);
    cpu.set_cs(0xE899);
    cpu.set_ss(0x3C95);
    cpu.set_ds(0xDA66);
    cpu.set_es(0xA074);
    cpu.set_sp(0x81CF);
    cpu.set_bp(0x6D06);
    cpu.set_si(0xB1ED);
    cpu.set_di(0xEF46);
    cpu.set_ip(0x5891);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEE221, 0xFF);
    machine.mem_store_byte(0xEE222, 0x46);
    machine.mem_store_byte(0xEE223, 0x4C);
    machine.mem_store_byte(0xEE224, 0x90);
    machine.mem_store_byte(0xEE225, 0x90);
    machine.mem_store_byte(0x436A2, 0x10);
    machine.mem_store_byte(0x436A3, 0x48);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x5894);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEE221), 0xFF);
    EXPECT_EQ(memory.load8(0xEE222), 0x46);
    EXPECT_EQ(memory.load8(0xEE223), 0x4C);
    EXPECT_EQ(memory.load8(0xEE224), 0x90);
    EXPECT_EQ(memory.load8(0xEE225), 0x90);
    EXPECT_EQ(memory.load8(0x436A2), 0x11);
    EXPECT_EQ(memory.load8(0x436A3), 0x48);
}
