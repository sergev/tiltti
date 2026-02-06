#include "fixture.h"

//
// div bp
//
TEST_F(MachineTest, div_bp)
{
    // Initial CPU State
    cpu.set_ax(0xACD5);
    cpu.set_bx(0x6B72);
    cpu.set_cx(0x4102);
    cpu.set_dx(0x0233);
    cpu.set_cs(0xE7AC);
    cpu.set_ss(0x995B);
    cpu.set_ds(0xB957);
    cpu.set_es(0x9416);
    cpu.set_sp(0xCF3C);
    cpu.set_bp(0x9BB9);
    cpu.set_si(0x0ADD);
    cpu.set_di(0x3EC7);
    cpu.set_ip(0x4CD6);
    cpu.set_flags(0xF4C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEC796, 0xF7);
    machine.mem_store_byte(0xEC797, 0xF5);
    machine.mem_store_byte(0xEC798, 0x90);
    machine.mem_store_byte(0xEC799, 0x90);
    machine.mem_store_byte(0xEC79A, 0x90);
    machine.mem_store_byte(0xEC79B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x039E);
    EXPECT_EQ(cpu.get_dx(), 0x65A7);
    EXPECT_EQ(cpu.get_ip(), 0x4CD8);
    EXPECT_EQ(cpu.get_flags(), 0xFC97);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xEC796), 0xF7);
    EXPECT_EQ(memory.load8(0xEC797), 0xF5);
    EXPECT_EQ(memory.load8(0xEC798), 0x90);
    EXPECT_EQ(memory.load8(0xEC799), 0x90);
    EXPECT_EQ(memory.load8(0xEC79A), 0x90);
    EXPECT_EQ(memory.load8(0xEC79B), 0x90);
}

//
// div byte [ds:bx+5Ch]
//
TEST_F(MachineTest, div_byte_ds_bx_5Ch)
{
    // Initial CPU State
    cpu.set_ax(0x702E);
    cpu.set_bx(0xD343);
    cpu.set_cx(0x89D6);
    cpu.set_dx(0x0DA6);
    cpu.set_cs(0xF3A3);
    cpu.set_ss(0x83E3);
    cpu.set_ds(0xFA8E);
    cpu.set_es(0x2C99);
    cpu.set_sp(0x21CD);
    cpu.set_bp(0x9500);
    cpu.set_si(0xA44A);
    cpu.set_di(0xB515);
    cpu.set_ip(0x95E1);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD011, 0xF6);
    machine.mem_store_byte(0xFD012, 0x77);
    machine.mem_store_byte(0xFD013, 0x5C);
    machine.mem_store_byte(0xFD014, 0x90);
    machine.mem_store_byte(0xFD015, 0x90);
    machine.mem_store_byte(0x07C7F, 0xD1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x5589);
    EXPECT_EQ(cpu.get_ip(), 0x95E4);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFD011), 0xF6);
    EXPECT_EQ(memory.load8(0xFD012), 0x77);
    EXPECT_EQ(memory.load8(0xFD013), 0x5C);
    EXPECT_EQ(memory.load8(0xFD014), 0x90);
    EXPECT_EQ(memory.load8(0xFD015), 0x90);
    EXPECT_EQ(memory.load8(0x07C7F), 0xD1);
}

//
// div byte [es:bx+di-6188h]
//
TEST_F(MachineTest, div_byte_es_bx_di_6188h)
{
    // Initial CPU State
    cpu.set_ax(0xAFD4);
    cpu.set_bx(0x849C);
    cpu.set_cx(0xDD18);
    cpu.set_dx(0x2B75);
    cpu.set_cs(0x9455);
    cpu.set_ss(0x0F5B);
    cpu.set_ds(0xFC8E);
    cpu.set_es(0x5898);
    cpu.set_sp(0x2769);
    cpu.set_bp(0xE8E9);
    cpu.set_si(0xDAA5);
    cpu.set_di(0x3AA3);
    cpu.set_ip(0xC17E);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA06CE, 0x26);
    machine.mem_store_byte(0xA06CF, 0xF6);
    machine.mem_store_byte(0xA06D0, 0xB1);
    machine.mem_store_byte(0xA06D1, 0x78);
    machine.mem_store_byte(0xA06D2, 0x9E);
    machine.mem_store_byte(0xA06D3, 0x90);
    machine.mem_store_byte(0x5E737, 0x52);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x2763);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF802);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA06CE), 0x26);
    EXPECT_EQ(memory.load8(0xA06CF), 0xF6);
    EXPECT_EQ(memory.load8(0xA06D0), 0xB1);
    EXPECT_EQ(memory.load8(0xA06D1), 0x78);
    EXPECT_EQ(memory.load8(0xA06D2), 0x9E);
    EXPECT_EQ(memory.load8(0xA06D3), 0x90);
    EXPECT_EQ(memory.load8(0x5E737), 0x52);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x11D17), 0x02);
    EXPECT_EQ(memory.load8(0x11D18), 0xF8);
    EXPECT_EQ(memory.load8(0x11D15), 0x55);
    EXPECT_EQ(memory.load8(0x11D16), 0x94);
    EXPECT_EQ(memory.load8(0x11D13), 0x83);
    EXPECT_EQ(memory.load8(0x11D14), 0xC1);
}

//
// div byte [es:si-5Ch]
//
TEST_F(MachineTest, div_byte_es_si_5Ch)
{
    // Initial CPU State
    cpu.set_ax(0x8369);
    cpu.set_bx(0x89E6);
    cpu.set_cx(0xFE06);
    cpu.set_dx(0x11D9);
    cpu.set_cs(0xA916);
    cpu.set_ss(0x6304);
    cpu.set_ds(0x3769);
    cpu.set_es(0xD08A);
    cpu.set_sp(0xA83C);
    cpu.set_bp(0x085F);
    cpu.set_si(0x0000);
    cpu.set_di(0x3C21);
    cpu.set_ip(0x7326);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB0486, 0x26);
    machine.mem_store_byte(0xB0487, 0xF6);
    machine.mem_store_byte(0xB0488, 0x74);
    machine.mem_store_byte(0xB0489, 0xA4);
    machine.mem_store_byte(0xB048A, 0x90);
    machine.mem_store_byte(0xB048B, 0x90);
    machine.mem_store_byte(0xE0844, 0xB1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0BBE);
    EXPECT_EQ(cpu.get_ip(), 0x732A);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB0486), 0x26);
    EXPECT_EQ(memory.load8(0xB0487), 0xF6);
    EXPECT_EQ(memory.load8(0xB0488), 0x74);
    EXPECT_EQ(memory.load8(0xB0489), 0xA4);
    EXPECT_EQ(memory.load8(0xB048A), 0x90);
    EXPECT_EQ(memory.load8(0xB048B), 0x90);
    EXPECT_EQ(memory.load8(0xE0844), 0xB1);
}

//
// div dl
//
TEST_F(MachineTest, div_dl)
{
    // Initial CPU State
    cpu.set_ax(0x1ED2);
    cpu.set_bx(0x6576);
    cpu.set_cx(0xE49C);
    cpu.set_dx(0xA4E9);
    cpu.set_cs(0x8D84);
    cpu.set_ss(0xAF73);
    cpu.set_ds(0xDDFB);
    cpu.set_es(0x5895);
    cpu.set_sp(0x1AC1);
    cpu.set_bp(0x42D2);
    cpu.set_si(0x9D8B);
    cpu.set_di(0x13A0);
    cpu.set_ip(0xB6FB);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x98F3B, 0xF6);
    machine.mem_store_byte(0x98F3C, 0xF2);
    machine.mem_store_byte(0x98F3D, 0x90);
    machine.mem_store_byte(0x98F3E, 0x90);
    machine.mem_store_byte(0x98F3F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xC921);
    EXPECT_EQ(cpu.get_ip(), 0xB6FD);
    EXPECT_EQ(cpu.get_flags(), 0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x98F3B), 0xF6);
    EXPECT_EQ(memory.load8(0x98F3C), 0xF2);
    EXPECT_EQ(memory.load8(0x98F3D), 0x90);
    EXPECT_EQ(memory.load8(0x98F3E), 0x90);
    EXPECT_EQ(memory.load8(0x98F3F), 0x90);
}

//
// div word [cs:bx+46h]
//
TEST_F(MachineTest, div_word_cs_bx_46h)
{
    // Initial CPU State
    cpu.set_ax(0xB236);
    cpu.set_bx(0xCBA0);
    cpu.set_cx(0x2848);
    cpu.set_dx(0xF390);
    cpu.set_cs(0xBA16);
    cpu.set_ss(0x6EC7);
    cpu.set_ds(0x35CB);
    cpu.set_es(0x10D3);
    cpu.set_sp(0xF7A1);
    cpu.set_bp(0x8B20);
    cpu.set_si(0x1570);
    cpu.set_di(0x2067);
    cpu.set_ip(0x9B99);
    cpu.set_flags(0xFC03);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC3CF9, 0x2E);
    machine.mem_store_byte(0xC3CFA, 0xF7);
    machine.mem_store_byte(0xC3CFB, 0x77);
    machine.mem_store_byte(0xC3CFC, 0x46);
    machine.mem_store_byte(0xC3CFD, 0x90);
    machine.mem_store_byte(0xC6D46, 0x55);
    machine.mem_store_byte(0xC6D47, 0x0C);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0xF79B);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF492);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC3CF9), 0x2E);
    EXPECT_EQ(memory.load8(0xC3CFA), 0xF7);
    EXPECT_EQ(memory.load8(0xC3CFB), 0x77);
    EXPECT_EQ(memory.load8(0xC3CFC), 0x46);
    EXPECT_EQ(memory.load8(0xC3CFD), 0x90);
    EXPECT_EQ(memory.load8(0xC6D46), 0x55);
    EXPECT_EQ(memory.load8(0xC6D47), 0x0C);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x7E40F), 0x92);
    EXPECT_EQ(memory.load8(0x7E410), 0xF4);
    EXPECT_EQ(memory.load8(0x7E40D), 0x16);
    EXPECT_EQ(memory.load8(0x7E40E), 0xBA);
    EXPECT_EQ(memory.load8(0x7E40B), 0x9D);
    EXPECT_EQ(memory.load8(0x7E40C), 0x9B);
}

//
// div word [ss:bp+di]
//
TEST_F(MachineTest, div_word_ss_bp_di)
{
    // Initial CPU State
    cpu.set_ax(0xE575);
    cpu.set_bx(0x3175);
    cpu.set_cx(0x09BA);
    cpu.set_dx(0x3FA9);
    cpu.set_cs(0x65CC);
    cpu.set_ss(0x3AB0);
    cpu.set_ds(0x6DDB);
    cpu.set_es(0x3CAD);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xC82B);
    cpu.set_si(0x460C);
    cpu.set_di(0x1EE4);
    cpu.set_ip(0xCF88);
    cpu.set_flags(0xF493);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x72C48, 0xF7);
    machine.mem_store_byte(0x72C49, 0x33);
    machine.mem_store_byte(0x72C4A, 0x90);
    machine.mem_store_byte(0x72C4B, 0x90);
    machine.mem_store_byte(0x72C4C, 0x90);
    machine.mem_store_byte(0x72C4D, 0x90);
    machine.mem_store_byte(0x4920F, 0x14);
    machine.mem_store_byte(0x49210, 0x0B);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0xFFFA);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x72C48), 0xF7);
    EXPECT_EQ(memory.load8(0x72C49), 0x33);
    EXPECT_EQ(memory.load8(0x72C4A), 0x90);
    EXPECT_EQ(memory.load8(0x72C4B), 0x90);
    EXPECT_EQ(memory.load8(0x72C4C), 0x90);
    EXPECT_EQ(memory.load8(0x72C4D), 0x90);
    EXPECT_EQ(memory.load8(0x4920F), 0x14);
    EXPECT_EQ(memory.load8(0x49210), 0x0B);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x4AAFE), 0x06);
    EXPECT_EQ(memory.load8(0x4AAFF), 0xF4);
    EXPECT_EQ(memory.load8(0x4AAFC), 0xCC);
    EXPECT_EQ(memory.load8(0x4AAFD), 0x65);
    EXPECT_EQ(memory.load8(0x4AAFA), 0x8A);
    EXPECT_EQ(memory.load8(0x4AAFB), 0xCF);
}

//
// div word [ss:bp+si-18C6h]
//
TEST_F(MachineTest, div_word_ss_bp_si_18C6h)
{
    // Initial CPU State
    cpu.set_ax(0x249C);
    cpu.set_bx(0x0141);
    cpu.set_cx(0x4862);
    cpu.set_dx(0x03EA);
    cpu.set_cs(0x4A55);
    cpu.set_ss(0x1162);
    cpu.set_ds(0x5E7B);
    cpu.set_es(0x676D);
    cpu.set_sp(0x08D0);
    cpu.set_bp(0x4FF3);
    cpu.set_si(0x9F49);
    cpu.set_di(0x0000);
    cpu.set_ip(0x6612);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x50B62, 0xF7);
    machine.mem_store_byte(0x50B63, 0xB2);
    machine.mem_store_byte(0x50B64, 0x3A);
    machine.mem_store_byte(0x50B65, 0xE7);
    machine.mem_store_byte(0x50B66, 0x90);
    machine.mem_store_byte(0x50B67, 0x90);
    machine.mem_store_byte(0x1EC96, 0x41);
    machine.mem_store_byte(0x1EC97, 0xCA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x04F4);
    EXPECT_EQ(cpu.get_dx(), 0x5AA8);
    EXPECT_EQ(cpu.get_ip(), 0x6616);
    EXPECT_EQ(cpu.get_flags(), 0xF883);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x50B62), 0xF7);
    EXPECT_EQ(memory.load8(0x50B63), 0xB2);
    EXPECT_EQ(memory.load8(0x50B64), 0x3A);
    EXPECT_EQ(memory.load8(0x50B65), 0xE7);
    EXPECT_EQ(memory.load8(0x50B66), 0x90);
    EXPECT_EQ(memory.load8(0x50B67), 0x90);
    EXPECT_EQ(memory.load8(0x1EC96), 0x41);
    EXPECT_EQ(memory.load8(0x1EC97), 0xCA);
}

//
// idiv al
//
TEST_F(MachineTest, idiv_al)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x5F9D);
    cpu.set_cx(0xBCFC);
    cpu.set_dx(0x86D5);
    cpu.set_cs(0xB811);
    cpu.set_ss(0xA386);
    cpu.set_ds(0x979F);
    cpu.set_es(0x63E9);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x7251);
    cpu.set_si(0xFEAD);
    cpu.set_di(0xEC4D);
    cpu.set_ip(0x4599);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBC6A9, 0x36);
    machine.mem_store_byte(0xBC6AA, 0xF6);
    machine.mem_store_byte(0xBC6AB, 0xF8);
    machine.mem_store_byte(0xBC6AC, 0x90);
    machine.mem_store_byte(0xBC6AD, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0xFFFA);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBC6A9), 0x36);
    EXPECT_EQ(memory.load8(0xBC6AA), 0xF6);
    EXPECT_EQ(memory.load8(0xBC6AB), 0xF8);
    EXPECT_EQ(memory.load8(0xBC6AC), 0x90);
    EXPECT_EQ(memory.load8(0xBC6AD), 0x90);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0xB385E), 0x46);
    EXPECT_EQ(memory.load8(0xB385F), 0xF0);
    EXPECT_EQ(memory.load8(0xB385C), 0x11);
    EXPECT_EQ(memory.load8(0xB385D), 0xB8);
    EXPECT_EQ(memory.load8(0xB385A), 0x9C);
    EXPECT_EQ(memory.load8(0xB385B), 0x45);
}

//
// idiv byte [ds:AD0Eh]
//
TEST_F(MachineTest, idiv_byte_ds_AD0Eh)
{
    // Initial CPU State
    cpu.set_ax(0x73F4);
    cpu.set_bx(0xC55E);
    cpu.set_cx(0x27A0);
    cpu.set_dx(0xF8DD);
    cpu.set_cs(0xC5A2);
    cpu.set_ss(0xF978);
    cpu.set_ds(0x2BA4);
    cpu.set_es(0x3704);
    cpu.set_sp(0x0326);
    cpu.set_bp(0x93B9);
    cpu.set_si(0xA10F);
    cpu.set_di(0x235E);
    cpu.set_ip(0xED7F);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD479F, 0xF6);
    machine.mem_store_byte(0xD47A0, 0x3E);
    machine.mem_store_byte(0xD47A1, 0x0E);
    machine.mem_store_byte(0xD47A2, 0xAD);
    machine.mem_store_byte(0xD47A3, 0x90);
    machine.mem_store_byte(0x3674E, 0x49);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x0320);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD479F), 0xF6);
    EXPECT_EQ(memory.load8(0xD47A0), 0x3E);
    EXPECT_EQ(memory.load8(0xD47A1), 0x0E);
    EXPECT_EQ(memory.load8(0xD47A2), 0xAD);
    EXPECT_EQ(memory.load8(0xD47A3), 0x90);
    EXPECT_EQ(memory.load8(0x3674E), 0x49);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0xF9AA4), 0x12);
    EXPECT_EQ(memory.load8(0xF9AA5), 0xF0);
    EXPECT_EQ(memory.load8(0xF9AA2), 0xA2);
    EXPECT_EQ(memory.load8(0xF9AA3), 0xC5);
    EXPECT_EQ(memory.load8(0xF9AA0), 0x83);
    EXPECT_EQ(memory.load8(0xF9AA1), 0xED);
}

//
// idiv byte [ss:bx+di+510Ah]
//
TEST_F(MachineTest, idiv_byte_ss_bx_di_510Ah)
{
    // Initial CPU State
    cpu.set_ax(0x3CE0);
    cpu.set_bx(0x3C8B);
    cpu.set_cx(0x9FB0);
    cpu.set_dx(0xC365);
    cpu.set_cs(0xC520);
    cpu.set_ss(0x0CE3);
    cpu.set_ds(0x96AD);
    cpu.set_es(0xB42D);
    cpu.set_sp(0xD277);
    cpu.set_bp(0xAF84);
    cpu.set_si(0x3547);
    cpu.set_di(0xCDAE);
    cpu.set_ip(0x39DE);
    cpu.set_flags(0xF486);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC8BDE, 0x36);
    machine.mem_store_byte(0xC8BDF, 0xF6);
    machine.mem_store_byte(0xC8BE0, 0xB9);
    machine.mem_store_byte(0xC8BE1, 0x0A);
    machine.mem_store_byte(0xC8BE2, 0x51);
    machine.mem_store_byte(0xC8BE3, 0x90);
    machine.mem_store_byte(0x12973, 0x92);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0xD271);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xFC12);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC8BDE), 0x36);
    EXPECT_EQ(memory.load8(0xC8BDF), 0xF6);
    EXPECT_EQ(memory.load8(0xC8BE0), 0xB9);
    EXPECT_EQ(memory.load8(0xC8BE1), 0x0A);
    EXPECT_EQ(memory.load8(0xC8BE2), 0x51);
    EXPECT_EQ(memory.load8(0xC8BE3), 0x90);
    EXPECT_EQ(memory.load8(0x12973), 0x92);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0x1A0A5), 0x12);
    EXPECT_EQ(memory.load8(0x1A0A6), 0xFC);
    EXPECT_EQ(memory.load8(0x1A0A3), 0x20);
    EXPECT_EQ(memory.load8(0x1A0A4), 0xC5);
    EXPECT_EQ(memory.load8(0x1A0A1), 0xE3);
    EXPECT_EQ(memory.load8(0x1A0A2), 0x39);
}

//
// idiv ch
//
TEST_F(MachineTest, idiv_ch)
{
    // Initial CPU State
    cpu.set_ax(0x0EE6);
    cpu.set_bx(0x470F);
    cpu.set_cx(0xDC0C);
    cpu.set_dx(0x7B49);
    cpu.set_cs(0x287F);
    cpu.set_ss(0x1F1B);
    cpu.set_ds(0x9174);
    cpu.set_es(0x2C2F);
    cpu.set_sp(0xB0FD);
    cpu.set_bp(0xC952);
    cpu.set_si(0x82DD);
    cpu.set_di(0x4C3F);
    cpu.set_ip(0xBFD6);
    cpu.set_flags(0xF486);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x347C6, 0x2E);
    machine.mem_store_byte(0x347C7, 0xF6);
    machine.mem_store_byte(0x347C8, 0xFD);
    machine.mem_store_byte(0x347C9, 0x90);
    machine.mem_store_byte(0x347CA, 0x90);
    machine.mem_store_byte(0x347CB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2297);
    EXPECT_EQ(cpu.get_ip(), 0xBFD9);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x347C6), 0x2E);
    EXPECT_EQ(memory.load8(0x347C7), 0xF6);
    EXPECT_EQ(memory.load8(0x347C8), 0xFD);
    EXPECT_EQ(memory.load8(0x347C9), 0x90);
    EXPECT_EQ(memory.load8(0x347CA), 0x90);
    EXPECT_EQ(memory.load8(0x347CB), 0x90);
}

//
// idiv si
//
TEST_F(MachineTest, idiv_si)
{
    // Initial CPU State
    cpu.set_ax(0x30F9);
    cpu.set_bx(0x9588);
    cpu.set_cx(0x948E);
    cpu.set_dx(0x9E80);
    cpu.set_cs(0x3FA6);
    cpu.set_ss(0xDADB);
    cpu.set_ds(0x894A);
    cpu.set_es(0xE2F1);
    cpu.set_sp(0x746D);
    cpu.set_bp(0xE82E);
    cpu.set_si(0xAD76);
    cpu.set_di(0x0000);
    cpu.set_ip(0x99C3);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x49423, 0x26);
    machine.mem_store_byte(0x49424, 0xF7);
    machine.mem_store_byte(0x49425, 0xFE);
    machine.mem_store_byte(0x49426, 0x90);
    machine.mem_store_byte(0x49427, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x7467);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x49423), 0x26);
    EXPECT_EQ(memory.load8(0x49424), 0xF7);
    EXPECT_EQ(memory.load8(0x49425), 0xFE);
    EXPECT_EQ(memory.load8(0x49426), 0x90);
    EXPECT_EQ(memory.load8(0x49427), 0x90);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0xE221B), 0x06);
    EXPECT_EQ(memory.load8(0xE221C), 0xF4);
    EXPECT_EQ(memory.load8(0xE2219), 0xA6);
    EXPECT_EQ(memory.load8(0xE221A), 0x3F);
    EXPECT_EQ(memory.load8(0xE2217), 0xC6);
    EXPECT_EQ(memory.load8(0xE2218), 0x99);
}

//
// idiv word [cs:bp+di-28CEh]
//
TEST_F(MachineTest, idiv_word_cs_bp_di_28CEh)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x7060);
    cpu.set_cx(0x3330);
    cpu.set_dx(0xFEF3);
    cpu.set_cs(0x051A);
    cpu.set_ss(0x8BE1);
    cpu.set_ds(0x3918);
    cpu.set_es(0x01F7);
    cpu.set_sp(0xF54A);
    cpu.set_bp(0x0000);
    cpu.set_si(0xCE9B);
    cpu.set_di(0x8388);
    cpu.set_ip(0x0168);
    cpu.set_flags(0xFC93);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05308, 0x2E);
    machine.mem_store_byte(0x05309, 0xF7);
    machine.mem_store_byte(0x0530A, 0xBB);
    machine.mem_store_byte(0x0530B, 0x32);
    machine.mem_store_byte(0x0530C, 0xD7);
    machine.mem_store_byte(0x0530D, 0x90);
    machine.mem_store_byte(0x0AC5A, 0xF6);
    machine.mem_store_byte(0x0AC5B, 0x68);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFD70);
    EXPECT_EQ(cpu.get_dx(), 0xF660);
    EXPECT_EQ(cpu.get_ip(), 0x016D);
    EXPECT_EQ(cpu.get_flags(), 0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x05308), 0x2E);
    EXPECT_EQ(memory.load8(0x05309), 0xF7);
    EXPECT_EQ(memory.load8(0x0530A), 0xBB);
    EXPECT_EQ(memory.load8(0x0530B), 0x32);
    EXPECT_EQ(memory.load8(0x0530C), 0xD7);
    EXPECT_EQ(memory.load8(0x0530D), 0x90);
    EXPECT_EQ(memory.load8(0x0AC5A), 0xF6);
    EXPECT_EQ(memory.load8(0x0AC5B), 0x68);
}

//
// idiv word [ds:si+3E03h]
//
TEST_F(MachineTest, idiv_word_ds_si_3E03h)
{
    // Initial CPU State
    cpu.set_ax(0x569F);
    cpu.set_bx(0x5D79);
    cpu.set_cx(0xD5E4);
    cpu.set_dx(0xD92B);
    cpu.set_cs(0xF8BA);
    cpu.set_ss(0x08C1);
    cpu.set_ds(0x6128);
    cpu.set_es(0x42C5);
    cpu.set_sp(0x561B);
    cpu.set_bp(0x5A0C);
    cpu.set_si(0x0000);
    cpu.set_di(0xF5BD);
    cpu.set_ip(0x3285);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFBE25, 0xF7);
    machine.mem_store_byte(0xFBE26, 0xBC);
    machine.mem_store_byte(0xFBE27, 0x03);
    machine.mem_store_byte(0xFBE28, 0x3E);
    machine.mem_store_byte(0xFBE29, 0x90);
    machine.mem_store_byte(0x65083, 0x28);
    machine.mem_store_byte(0x65084, 0xA9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7277);
    EXPECT_EQ(cpu.get_dx(), 0xE507);
    EXPECT_EQ(cpu.get_ip(), 0x3289);
    EXPECT_EQ(cpu.get_flags(), 0xF016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFBE25), 0xF7);
    EXPECT_EQ(memory.load8(0xFBE26), 0xBC);
    EXPECT_EQ(memory.load8(0xFBE27), 0x03);
    EXPECT_EQ(memory.load8(0xFBE28), 0x3E);
    EXPECT_EQ(memory.load8(0xFBE29), 0x90);
    EXPECT_EQ(memory.load8(0x65083), 0x28);
    EXPECT_EQ(memory.load8(0x65084), 0xA9);
}

//
// idiv word [es:si-5522h]
//
TEST_F(MachineTest, idiv_word_es_si_5522h)
{
    // Initial CPU State
    cpu.set_ax(0xC52A);
    cpu.set_bx(0x5C32);
    cpu.set_cx(0x4C40);
    cpu.set_dx(0xC2BC);
    cpu.set_cs(0x03B1);
    cpu.set_ss(0xB134);
    cpu.set_ds(0x4A59);
    cpu.set_es(0x6DB8);
    cpu.set_sp(0xE371);
    cpu.set_bp(0x3E89);
    cpu.set_si(0x0001);
    cpu.set_di(0xD251);
    cpu.set_ip(0xD52A);
    cpu.set_flags(0xFCC6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1103A, 0x26);
    machine.mem_store_byte(0x1103B, 0xF7);
    machine.mem_store_byte(0x1103C, 0xBC);
    machine.mem_store_byte(0x1103D, 0xDE);
    machine.mem_store_byte(0x1103E, 0xAA);
    machine.mem_store_byte(0x1103F, 0x90);
    machine.mem_store_byte(0x7865F, 0x78);
    machine.mem_store_byte(0x78660, 0x79);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0xE36B);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_EQ(cpu.get_flags(), 0xF412);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1103A), 0x26);
    EXPECT_EQ(memory.load8(0x1103B), 0xF7);
    EXPECT_EQ(memory.load8(0x1103C), 0xBC);
    EXPECT_EQ(memory.load8(0x1103D), 0xDE);
    EXPECT_EQ(memory.load8(0x1103E), 0xAA);
    EXPECT_EQ(memory.load8(0x1103F), 0x90);
    EXPECT_EQ(memory.load8(0x7865F), 0x78);
    EXPECT_EQ(memory.load8(0x78660), 0x79);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_EQ(memory.load8(0xBF6AF), 0x12);
    EXPECT_EQ(memory.load8(0xBF6B0), 0xF4);
    EXPECT_EQ(memory.load8(0xBF6AD), 0xB1);
    EXPECT_EQ(memory.load8(0xBF6AE), 0x03);
    EXPECT_EQ(memory.load8(0xBF6AB), 0x2F);
    EXPECT_EQ(memory.load8(0xBF6AC), 0xD5);
}
