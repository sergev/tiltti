#include "fixture.h"

// Tests: string (movsb, movsw, lods, stos, cmps, scas, rep)

TEST_F(MachineTest, cmpsw)
{
    // Initial CPU State
    cpu.set_ax(0x79B7);
    cpu.set_bx(0xC88E);
    cpu.set_cx(0x003A);
    cpu.set_dx(0x5151);
    cpu.set_cs(0xA9E5);
    cpu.set_ss(0xABB5);
    cpu.set_ds(0x2654);
    cpu.set_es(0x692A);
    cpu.set_sp(0x81AE);
    cpu.set_bp(0x5DEE);
    cpu.set_si(0x76F9);
    cpu.set_di(0xF8A4);
    cpu.set_ip(0x981B);
    cpu.set_flags(0xF0D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB366B, 0xA7);
    machine.mem_store_byte(0xB366C, 0x90);
    machine.mem_store_byte(0xB366D, 0x90);
    machine.mem_store_byte(0xB366E, 0x90);
    machine.mem_store_byte(0xB366F, 0x90);
    machine.mem_store_byte(0x2DC39, 0x42);
    machine.mem_store_byte(0x2DC3A, 0xA2);
    machine.mem_store_byte(0x78B44, 0xA8);
    machine.mem_store_byte(0x78B45, 0xBA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x76FB);
    EXPECT_EQ(cpu.get_di(), 0xF8A6);
    EXPECT_EQ(cpu.get_ip(), 0x981C);
    EXPECT_EQ(cpu.get_flags(), 0xF097);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB366B), 0xA7);
    EXPECT_EQ(memory.load8(0xB366C), 0x90);
    EXPECT_EQ(memory.load8(0xB366D), 0x90);
    EXPECT_EQ(memory.load8(0xB366E), 0x90);
    EXPECT_EQ(memory.load8(0xB366F), 0x90);
    EXPECT_EQ(memory.load8(0x2DC39), 0x42);
    EXPECT_EQ(memory.load8(0x2DC3A), 0xA2);
    EXPECT_EQ(memory.load8(0x78B44), 0xA8);
    EXPECT_EQ(memory.load8(0x78B45), 0xBA);
}

TEST_F(MachineTest, cs_movsb)
{
    // Initial CPU State
    cpu.set_ax(0x2A14);
    cpu.set_bx(0x7A2C);
    cpu.set_cx(0x0036);
    cpu.set_dx(0x2B97);
    cpu.set_cs(0x9415);
    cpu.set_ss(0x8145);
    cpu.set_ds(0x4575);
    cpu.set_es(0x2C46);
    cpu.set_sp(0x76DD);
    cpu.set_bp(0xD1D2);
    cpu.set_si(0x987E);
    cpu.set_di(0x35D1);
    cpu.set_ip(0xDE6F);
    cpu.set_flags(0xF8D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA1FBF, 0x2E);
    machine.mem_store_byte(0xA1FC0, 0xA4);
    machine.mem_store_byte(0xA1FC1, 0x90);
    machine.mem_store_byte(0xA1FC2, 0x90);
    machine.mem_store_byte(0xA1FC3, 0x90);
    machine.mem_store_byte(0x9D9CE, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x987F);
    EXPECT_EQ(cpu.get_di(), 0x35D2);
    EXPECT_EQ(cpu.get_ip(), 0xDE71);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA1FBF), 0x2E);
    EXPECT_EQ(memory.load8(0xA1FC0), 0xA4);
    EXPECT_EQ(memory.load8(0xA1FC1), 0x90);
    EXPECT_EQ(memory.load8(0xA1FC2), 0x90);
    EXPECT_EQ(memory.load8(0xA1FC3), 0x90);
    EXPECT_EQ(memory.load8(0x9D9CE), 0x90);
    EXPECT_EQ(memory.load8(0x2FA31), 0x90);
}

TEST_F(MachineTest, cs_rep_lodsb)
{
    // Initial CPU State
    cpu.set_ax(0xBEE2);
    cpu.set_bx(0xA7F4);
    cpu.set_cx(0x005C);
    cpu.set_dx(0xE866);
    cpu.set_cs(0x824B);
    cpu.set_ss(0x2163);
    cpu.set_ds(0x2130);
    cpu.set_es(0x19A9);
    cpu.set_sp(0x55A7);
    cpu.set_bp(0x6C2F);
    cpu.set_si(0xE697);
    cpu.set_di(0xD09C);
    cpu.set_ip(0xFCD4);
    cpu.set_flags(0xF857);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x92184, 0x2E);
    machine.mem_store_byte(0x92185, 0xF2);
    machine.mem_store_byte(0x92186, 0xAC);
    machine.mem_store_byte(0x92187, 0x90);
    machine.mem_store_byte(0x92188, 0x90);
    machine.mem_store_byte(0x92189, 0x90);
    machine.mem_store_byte(0x90B47, 0xFF);
    machine.mem_store_byte(0x90B48, 0x09);
    machine.mem_store_byte(0x90B49, 0x1B);
    machine.mem_store_byte(0x90B4A, 0x4F);
    machine.mem_store_byte(0x90B4B, 0x66);
    machine.mem_store_byte(0x90B4C, 0xDB);
    machine.mem_store_byte(0x90B4D, 0xE2);
    machine.mem_store_byte(0x90B4E, 0xFD);
    machine.mem_store_byte(0x90B4F, 0xE9);
    machine.mem_store_byte(0x90B50, 0x7E);
    machine.mem_store_byte(0x90B51, 0x6E);
    machine.mem_store_byte(0x90B52, 0xCE);
    machine.mem_store_byte(0x90B53, 0xE6);
    machine.mem_store_byte(0x90B54, 0x1D);
    machine.mem_store_byte(0x90B55, 0x2B);
    machine.mem_store_byte(0x90B56, 0x85);
    machine.mem_store_byte(0x90B57, 0x00);
    machine.mem_store_byte(0x90B58, 0x64);
    machine.mem_store_byte(0x90B59, 0xFB);
    machine.mem_store_byte(0x90B5A, 0xF8);
    machine.mem_store_byte(0x90B5B, 0x1C);
    machine.mem_store_byte(0x90B5C, 0x4D);
    machine.mem_store_byte(0x90B5D, 0xB3);
    machine.mem_store_byte(0x90B5E, 0x96);
    machine.mem_store_byte(0x90B5F, 0x94);
    machine.mem_store_byte(0x90B60, 0x4B);
    machine.mem_store_byte(0x90B61, 0xFF);
    machine.mem_store_byte(0x90B62, 0xEB);
    machine.mem_store_byte(0x90B63, 0xE0);
    machine.mem_store_byte(0x90B64, 0x75);
    machine.mem_store_byte(0x90B65, 0xEF);
    machine.mem_store_byte(0x90B66, 0x35);
    machine.mem_store_byte(0x90B67, 0xE5);
    machine.mem_store_byte(0x90B68, 0xBC);
    machine.mem_store_byte(0x90B69, 0x1C);
    machine.mem_store_byte(0x90B6A, 0xF8);
    machine.mem_store_byte(0x90B6B, 0xBA);
    machine.mem_store_byte(0x90B6C, 0xA1);
    machine.mem_store_byte(0x90B6D, 0x1C);
    machine.mem_store_byte(0x90B6E, 0x94);
    machine.mem_store_byte(0x90B6F, 0x07);
    machine.mem_store_byte(0x90B70, 0x47);
    machine.mem_store_byte(0x90B71, 0x3A);
    machine.mem_store_byte(0x90B72, 0x19);
    machine.mem_store_byte(0x90B73, 0x48);
    machine.mem_store_byte(0x90B74, 0x52);
    machine.mem_store_byte(0x90B75, 0xCC);
    machine.mem_store_byte(0x90B76, 0x4A);
    machine.mem_store_byte(0x90B77, 0x09);
    machine.mem_store_byte(0x90B78, 0xBF);
    machine.mem_store_byte(0x90B79, 0xDC);
    machine.mem_store_byte(0x90B7A, 0x6E);
    machine.mem_store_byte(0x90B7B, 0x13);
    machine.mem_store_byte(0x90B7C, 0x6A);
    machine.mem_store_byte(0x90B7D, 0xDA);
    machine.mem_store_byte(0x90B7E, 0xB8);
    machine.mem_store_byte(0x90B7F, 0x53);
    machine.mem_store_byte(0x90B80, 0xD5);
    machine.mem_store_byte(0x90B81, 0xEA);
    machine.mem_store_byte(0x90B82, 0x94);
    machine.mem_store_byte(0x90B83, 0x15);
    machine.mem_store_byte(0x90B84, 0xDB);
    machine.mem_store_byte(0x90B85, 0x3A);
    machine.mem_store_byte(0x90B86, 0xAA);
    machine.mem_store_byte(0x90B87, 0xEF);
    machine.mem_store_byte(0x90B88, 0x2A);
    machine.mem_store_byte(0x90B89, 0xFA);
    machine.mem_store_byte(0x90B8A, 0x78);
    machine.mem_store_byte(0x90B8B, 0x2D);
    machine.mem_store_byte(0x90B8C, 0xDE);
    machine.mem_store_byte(0x90B8D, 0x9E);
    machine.mem_store_byte(0x90B8E, 0xF4);
    machine.mem_store_byte(0x90B8F, 0x36);
    machine.mem_store_byte(0x90B90, 0xD2);
    machine.mem_store_byte(0x90B91, 0x6E);
    machine.mem_store_byte(0x90B92, 0xF6);
    machine.mem_store_byte(0x90B93, 0xB5);
    machine.mem_store_byte(0x90B94, 0x66);
    machine.mem_store_byte(0x90B95, 0xFF);
    machine.mem_store_byte(0x90B96, 0x06);
    machine.mem_store_byte(0x90B97, 0xB9);
    machine.mem_store_byte(0x90B98, 0x5B);
    machine.mem_store_byte(0x90B99, 0x5E);
    machine.mem_store_byte(0x90B9A, 0xA7);
    machine.mem_store_byte(0x90B9B, 0xB2);
    machine.mem_store_byte(0x90B9C, 0x74);
    machine.mem_store_byte(0x90B9D, 0x8B);
    machine.mem_store_byte(0x90B9E, 0xC2);
    machine.mem_store_byte(0x90B9F, 0xE3);
    machine.mem_store_byte(0x90BA0, 0x95);
    machine.mem_store_byte(0x90BA1, 0xC4);
    machine.mem_store_byte(0x90BA2, 0x05);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xBE05);
    EXPECT_EQ(cpu.get_cx(), 0x0000);
    EXPECT_EQ(cpu.get_si(), 0xE6F3);
    EXPECT_EQ(cpu.get_ip(), 0xFCD7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x92184), 0x2E);
    EXPECT_EQ(memory.load8(0x92185), 0xF2);
    EXPECT_EQ(memory.load8(0x92186), 0xAC);
    EXPECT_EQ(memory.load8(0x92187), 0x90);
    EXPECT_EQ(memory.load8(0x92188), 0x90);
    EXPECT_EQ(memory.load8(0x92189), 0x90);
    EXPECT_EQ(memory.load8(0x90B47), 0xFF);
    EXPECT_EQ(memory.load8(0x90B48), 0x09);
    EXPECT_EQ(memory.load8(0x90B49), 0x1B);
    EXPECT_EQ(memory.load8(0x90B4A), 0x4F);
    EXPECT_EQ(memory.load8(0x90B4B), 0x66);
    EXPECT_EQ(memory.load8(0x90B4C), 0xDB);
    EXPECT_EQ(memory.load8(0x90B4D), 0xE2);
    EXPECT_EQ(memory.load8(0x90B4E), 0xFD);
    EXPECT_EQ(memory.load8(0x90B4F), 0xE9);
    EXPECT_EQ(memory.load8(0x90B50), 0x7E);
    EXPECT_EQ(memory.load8(0x90B51), 0x6E);
    EXPECT_EQ(memory.load8(0x90B52), 0xCE);
    EXPECT_EQ(memory.load8(0x90B53), 0xE6);
    EXPECT_EQ(memory.load8(0x90B54), 0x1D);
    EXPECT_EQ(memory.load8(0x90B55), 0x2B);
    EXPECT_EQ(memory.load8(0x90B56), 0x85);
    EXPECT_EQ(memory.load8(0x90B57), 0x00);
    EXPECT_EQ(memory.load8(0x90B58), 0x64);
    EXPECT_EQ(memory.load8(0x90B59), 0xFB);
    EXPECT_EQ(memory.load8(0x90B5A), 0xF8);
    EXPECT_EQ(memory.load8(0x90B5B), 0x1C);
    EXPECT_EQ(memory.load8(0x90B5C), 0x4D);
    EXPECT_EQ(memory.load8(0x90B5D), 0xB3);
    EXPECT_EQ(memory.load8(0x90B5E), 0x96);
    EXPECT_EQ(memory.load8(0x90B5F), 0x94);
    EXPECT_EQ(memory.load8(0x90B60), 0x4B);
    EXPECT_EQ(memory.load8(0x90B61), 0xFF);
    EXPECT_EQ(memory.load8(0x90B62), 0xEB);
    EXPECT_EQ(memory.load8(0x90B63), 0xE0);
    EXPECT_EQ(memory.load8(0x90B64), 0x75);
    EXPECT_EQ(memory.load8(0x90B65), 0xEF);
    EXPECT_EQ(memory.load8(0x90B66), 0x35);
    EXPECT_EQ(memory.load8(0x90B67), 0xE5);
    EXPECT_EQ(memory.load8(0x90B68), 0xBC);
    EXPECT_EQ(memory.load8(0x90B69), 0x1C);
    EXPECT_EQ(memory.load8(0x90B6A), 0xF8);
    EXPECT_EQ(memory.load8(0x90B6B), 0xBA);
    EXPECT_EQ(memory.load8(0x90B6C), 0xA1);
    EXPECT_EQ(memory.load8(0x90B6D), 0x1C);
    EXPECT_EQ(memory.load8(0x90B6E), 0x94);
    EXPECT_EQ(memory.load8(0x90B6F), 0x07);
    EXPECT_EQ(memory.load8(0x90B70), 0x47);
    EXPECT_EQ(memory.load8(0x90B71), 0x3A);
    EXPECT_EQ(memory.load8(0x90B72), 0x19);
    EXPECT_EQ(memory.load8(0x90B73), 0x48);
    EXPECT_EQ(memory.load8(0x90B74), 0x52);
    EXPECT_EQ(memory.load8(0x90B75), 0xCC);
    EXPECT_EQ(memory.load8(0x90B76), 0x4A);
    EXPECT_EQ(memory.load8(0x90B77), 0x09);
    EXPECT_EQ(memory.load8(0x90B78), 0xBF);
    EXPECT_EQ(memory.load8(0x90B79), 0xDC);
    EXPECT_EQ(memory.load8(0x90B7A), 0x6E);
    EXPECT_EQ(memory.load8(0x90B7B), 0x13);
    EXPECT_EQ(memory.load8(0x90B7C), 0x6A);
    EXPECT_EQ(memory.load8(0x90B7D), 0xDA);
    EXPECT_EQ(memory.load8(0x90B7E), 0xB8);
    EXPECT_EQ(memory.load8(0x90B7F), 0x53);
    EXPECT_EQ(memory.load8(0x90B80), 0xD5);
    EXPECT_EQ(memory.load8(0x90B81), 0xEA);
    EXPECT_EQ(memory.load8(0x90B82), 0x94);
    EXPECT_EQ(memory.load8(0x90B83), 0x15);
    EXPECT_EQ(memory.load8(0x90B84), 0xDB);
    EXPECT_EQ(memory.load8(0x90B85), 0x3A);
    EXPECT_EQ(memory.load8(0x90B86), 0xAA);
    EXPECT_EQ(memory.load8(0x90B87), 0xEF);
    EXPECT_EQ(memory.load8(0x90B88), 0x2A);
    EXPECT_EQ(memory.load8(0x90B89), 0xFA);
    EXPECT_EQ(memory.load8(0x90B8A), 0x78);
    EXPECT_EQ(memory.load8(0x90B8B), 0x2D);
    EXPECT_EQ(memory.load8(0x90B8C), 0xDE);
    EXPECT_EQ(memory.load8(0x90B8D), 0x9E);
    EXPECT_EQ(memory.load8(0x90B8E), 0xF4);
    EXPECT_EQ(memory.load8(0x90B8F), 0x36);
    EXPECT_EQ(memory.load8(0x90B90), 0xD2);
    EXPECT_EQ(memory.load8(0x90B91), 0x6E);
    EXPECT_EQ(memory.load8(0x90B92), 0xF6);
    EXPECT_EQ(memory.load8(0x90B93), 0xB5);
    EXPECT_EQ(memory.load8(0x90B94), 0x66);
    EXPECT_EQ(memory.load8(0x90B95), 0xFF);
    EXPECT_EQ(memory.load8(0x90B96), 0x06);
    EXPECT_EQ(memory.load8(0x90B97), 0xB9);
    EXPECT_EQ(memory.load8(0x90B98), 0x5B);
    EXPECT_EQ(memory.load8(0x90B99), 0x5E);
    EXPECT_EQ(memory.load8(0x90B9A), 0xA7);
    EXPECT_EQ(memory.load8(0x90B9B), 0xB2);
    EXPECT_EQ(memory.load8(0x90B9C), 0x74);
    EXPECT_EQ(memory.load8(0x90B9D), 0x8B);
    EXPECT_EQ(memory.load8(0x90B9E), 0xC2);
    EXPECT_EQ(memory.load8(0x90B9F), 0xE3);
    EXPECT_EQ(memory.load8(0x90BA0), 0x95);
    EXPECT_EQ(memory.load8(0x90BA1), 0xC4);
    EXPECT_EQ(memory.load8(0x90BA2), 0x05);
}

TEST_F(MachineTest, cs_repne_cmpsb)
{
    // Initial CPU State
    cpu.set_ax(0x03C7);
    cpu.set_bx(0xB910);
    cpu.set_cx(0x0050);
    cpu.set_dx(0x553B);
    cpu.set_cs(0x3BA5);
    cpu.set_ss(0xEFCD);
    cpu.set_ds(0x199B);
    cpu.set_es(0xB881);
    cpu.set_sp(0xC0F5);
    cpu.set_bp(0x34DA);
    cpu.set_si(0x1B5D);
    cpu.set_di(0x0000);
    cpu.set_ip(0x97A0);
    cpu.set_flags(0xF406);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x451F0, 0x2E);
    machine.mem_store_byte(0x451F1, 0xF2);
    machine.mem_store_byte(0x451F2, 0xA6);
    machine.mem_store_byte(0x451F3, 0x90);
    machine.mem_store_byte(0x451F4, 0x90);
    machine.mem_store_byte(0x451F5, 0x90);
    machine.mem_store_byte(0x3D5AD, 0x9F);
    machine.mem_store_byte(0xB8810, 0xB9);
    machine.mem_store_byte(0x3D5AC, 0x2D);
    machine.mem_store_byte(0xC880F, 0xF2);
    machine.mem_store_byte(0x3D5AB, 0x4E);
    machine.mem_store_byte(0xC880E, 0xA2);
    machine.mem_store_byte(0x3D5AA, 0x84);
    machine.mem_store_byte(0xC880D, 0xD4);
    machine.mem_store_byte(0x3D5A9, 0x3D);
    machine.mem_store_byte(0xC880C, 0x5C);
    machine.mem_store_byte(0x3D5A8, 0x15);
    machine.mem_store_byte(0xC880B, 0xF8);
    machine.mem_store_byte(0x3D5A7, 0xFF);
    machine.mem_store_byte(0xC880A, 0x98);
    machine.mem_store_byte(0x3D5A6, 0xB8);
    machine.mem_store_byte(0xC8809, 0x87);
    machine.mem_store_byte(0x3D5A5, 0x8D);
    machine.mem_store_byte(0xC8808, 0x1C);
    machine.mem_store_byte(0x3D5A4, 0x8B);
    machine.mem_store_byte(0xC8807, 0xC7);
    machine.mem_store_byte(0x3D5A3, 0x80);
    machine.mem_store_byte(0xC8806, 0x2B);
    machine.mem_store_byte(0x3D5A2, 0xFF);
    machine.mem_store_byte(0xC8805, 0xCC);
    machine.mem_store_byte(0x3D5A1, 0x4A);
    machine.mem_store_byte(0xC8804, 0xA1);
    machine.mem_store_byte(0x3D5A0, 0x9A);
    machine.mem_store_byte(0xC8803, 0xF0);
    machine.mem_store_byte(0x3D59F, 0x3A);
    machine.mem_store_byte(0xC8802, 0x29);
    machine.mem_store_byte(0x3D59E, 0x01);
    machine.mem_store_byte(0xC8801, 0x26);
    machine.mem_store_byte(0x3D59D, 0x25);
    machine.mem_store_byte(0xC8800, 0x47);
    machine.mem_store_byte(0x3D59C, 0xBC);
    machine.mem_store_byte(0xC87FF, 0x48);
    machine.mem_store_byte(0x3D59B, 0x6E);
    machine.mem_store_byte(0xC87FE, 0xCE);
    machine.mem_store_byte(0x3D59A, 0x82);
    machine.mem_store_byte(0xC87FD, 0x1D);
    machine.mem_store_byte(0x3D599, 0x93);
    machine.mem_store_byte(0xC87FC, 0xBC);
    machine.mem_store_byte(0x3D598, 0x65);
    machine.mem_store_byte(0xC87FB, 0xB0);
    machine.mem_store_byte(0x3D597, 0xD8);
    machine.mem_store_byte(0xC87FA, 0x97);
    machine.mem_store_byte(0x3D596, 0x73);
    machine.mem_store_byte(0xC87F9, 0xCA);
    machine.mem_store_byte(0x3D595, 0xD9);
    machine.mem_store_byte(0xC87F8, 0xFF);
    machine.mem_store_byte(0x3D594, 0xB2);
    machine.mem_store_byte(0xC87F7, 0x06);
    machine.mem_store_byte(0x3D593, 0xD4);
    machine.mem_store_byte(0xC87F6, 0x39);
    machine.mem_store_byte(0x3D592, 0x4B);
    machine.mem_store_byte(0xC87F5, 0x5B);
    machine.mem_store_byte(0x3D591, 0xC0);
    machine.mem_store_byte(0xC87F4, 0x1C);
    machine.mem_store_byte(0x3D590, 0x9B);
    machine.mem_store_byte(0xC87F3, 0x6E);
    machine.mem_store_byte(0x3D58F, 0x41);
    machine.mem_store_byte(0xC87F2, 0x80);
    machine.mem_store_byte(0x3D58E, 0x53);
    machine.mem_store_byte(0xC87F1, 0x2A);
    machine.mem_store_byte(0x3D58D, 0x1E);
    machine.mem_store_byte(0xC87F0, 0xBF);
    machine.mem_store_byte(0x3D58C, 0xB2);
    machine.mem_store_byte(0xC87EF, 0x89);
    machine.mem_store_byte(0x3D58B, 0xD2);
    machine.mem_store_byte(0xC87EE, 0xE2);
    machine.mem_store_byte(0x3D58A, 0xB5);
    machine.mem_store_byte(0xC87ED, 0x15);
    machine.mem_store_byte(0x3D589, 0xB5);
    machine.mem_store_byte(0xC87EC, 0x47);
    machine.mem_store_byte(0x3D588, 0x55);
    machine.mem_store_byte(0xC87EB, 0x3D);
    machine.mem_store_byte(0x3D587, 0xF6);
    machine.mem_store_byte(0xC87EA, 0xF6);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0029);
    EXPECT_EQ(cpu.get_si(), 0x1B36);
    EXPECT_EQ(cpu.get_di(), 0xFFD9);
    EXPECT_EQ(cpu.get_ip(), 0x97A3);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x451F0), 0x2E);
    EXPECT_EQ(memory.load8(0x451F1), 0xF2);
    EXPECT_EQ(memory.load8(0x451F2), 0xA6);
    EXPECT_EQ(memory.load8(0x451F3), 0x90);
    EXPECT_EQ(memory.load8(0x451F4), 0x90);
    EXPECT_EQ(memory.load8(0x451F5), 0x90);
    EXPECT_EQ(memory.load8(0x3D5AD), 0x9F);
    EXPECT_EQ(memory.load8(0xB8810), 0xB9);
    EXPECT_EQ(memory.load8(0x3D5AC), 0x2D);
    EXPECT_EQ(memory.load8(0xC880F), 0xF2);
    EXPECT_EQ(memory.load8(0x3D5AB), 0x4E);
    EXPECT_EQ(memory.load8(0xC880E), 0xA2);
    EXPECT_EQ(memory.load8(0x3D5AA), 0x84);
    EXPECT_EQ(memory.load8(0xC880D), 0xD4);
    EXPECT_EQ(memory.load8(0x3D5A9), 0x3D);
    EXPECT_EQ(memory.load8(0xC880C), 0x5C);
    EXPECT_EQ(memory.load8(0x3D5A8), 0x15);
    EXPECT_EQ(memory.load8(0xC880B), 0xF8);
    EXPECT_EQ(memory.load8(0x3D5A7), 0xFF);
    EXPECT_EQ(memory.load8(0xC880A), 0x98);
    EXPECT_EQ(memory.load8(0x3D5A6), 0xB8);
    EXPECT_EQ(memory.load8(0xC8809), 0x87);
    EXPECT_EQ(memory.load8(0x3D5A5), 0x8D);
    EXPECT_EQ(memory.load8(0xC8808), 0x1C);
    EXPECT_EQ(memory.load8(0x3D5A4), 0x8B);
    EXPECT_EQ(memory.load8(0xC8807), 0xC7);
    EXPECT_EQ(memory.load8(0x3D5A3), 0x80);
    EXPECT_EQ(memory.load8(0xC8806), 0x2B);
    EXPECT_EQ(memory.load8(0x3D5A2), 0xFF);
    EXPECT_EQ(memory.load8(0xC8805), 0xCC);
    EXPECT_EQ(memory.load8(0x3D5A1), 0x4A);
    EXPECT_EQ(memory.load8(0xC8804), 0xA1);
    EXPECT_EQ(memory.load8(0x3D5A0), 0x9A);
    EXPECT_EQ(memory.load8(0xC8803), 0xF0);
    EXPECT_EQ(memory.load8(0x3D59F), 0x3A);
    EXPECT_EQ(memory.load8(0xC8802), 0x29);
    EXPECT_EQ(memory.load8(0x3D59E), 0x01);
    EXPECT_EQ(memory.load8(0xC8801), 0x26);
    EXPECT_EQ(memory.load8(0x3D59D), 0x25);
    EXPECT_EQ(memory.load8(0xC8800), 0x47);
    EXPECT_EQ(memory.load8(0x3D59C), 0xBC);
    EXPECT_EQ(memory.load8(0xC87FF), 0x48);
    EXPECT_EQ(memory.load8(0x3D59B), 0x6E);
    EXPECT_EQ(memory.load8(0xC87FE), 0xCE);
    EXPECT_EQ(memory.load8(0x3D59A), 0x82);
    EXPECT_EQ(memory.load8(0xC87FD), 0x1D);
    EXPECT_EQ(memory.load8(0x3D599), 0x93);
    EXPECT_EQ(memory.load8(0xC87FC), 0xBC);
    EXPECT_EQ(memory.load8(0x3D598), 0x65);
    EXPECT_EQ(memory.load8(0xC87FB), 0xB0);
    EXPECT_EQ(memory.load8(0x3D597), 0xD8);
    EXPECT_EQ(memory.load8(0xC87FA), 0x97);
    EXPECT_EQ(memory.load8(0x3D596), 0x73);
    EXPECT_EQ(memory.load8(0xC87F9), 0xCA);
    EXPECT_EQ(memory.load8(0x3D595), 0xD9);
    EXPECT_EQ(memory.load8(0xC87F8), 0xFF);
    EXPECT_EQ(memory.load8(0x3D594), 0xB2);
    EXPECT_EQ(memory.load8(0xC87F7), 0x06);
    EXPECT_EQ(memory.load8(0x3D593), 0xD4);
    EXPECT_EQ(memory.load8(0xC87F6), 0x39);
    EXPECT_EQ(memory.load8(0x3D592), 0x4B);
    EXPECT_EQ(memory.load8(0xC87F5), 0x5B);
    EXPECT_EQ(memory.load8(0x3D591), 0xC0);
    EXPECT_EQ(memory.load8(0xC87F4), 0x1C);
    EXPECT_EQ(memory.load8(0x3D590), 0x9B);
    EXPECT_EQ(memory.load8(0xC87F3), 0x6E);
    EXPECT_EQ(memory.load8(0x3D58F), 0x41);
    EXPECT_EQ(memory.load8(0xC87F2), 0x80);
    EXPECT_EQ(memory.load8(0x3D58E), 0x53);
    EXPECT_EQ(memory.load8(0xC87F1), 0x2A);
    EXPECT_EQ(memory.load8(0x3D58D), 0x1E);
    EXPECT_EQ(memory.load8(0xC87F0), 0xBF);
    EXPECT_EQ(memory.load8(0x3D58C), 0xB2);
    EXPECT_EQ(memory.load8(0xC87EF), 0x89);
    EXPECT_EQ(memory.load8(0x3D58B), 0xD2);
    EXPECT_EQ(memory.load8(0xC87EE), 0xE2);
    EXPECT_EQ(memory.load8(0x3D58A), 0xB5);
    EXPECT_EQ(memory.load8(0xC87ED), 0x15);
    EXPECT_EQ(memory.load8(0x3D589), 0xB5);
    EXPECT_EQ(memory.load8(0xC87EC), 0x47);
    EXPECT_EQ(memory.load8(0x3D588), 0x55);
    EXPECT_EQ(memory.load8(0xC87EB), 0x3D);
    EXPECT_EQ(memory.load8(0x3D587), 0xF6);
    EXPECT_EQ(memory.load8(0xC87EA), 0xF6);
}

TEST_F(MachineTest, cs_repne_scasw)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x4286);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x6C5D);
    cpu.set_cs(0x9B1B);
    cpu.set_ss(0x9AD7);
    cpu.set_ds(0xB4A0);
    cpu.set_es(0xA759);
    cpu.set_sp(0x770D);
    cpu.set_bp(0x49AD);
    cpu.set_si(0xAAE2);
    cpu.set_di(0x0000);
    cpu.set_ip(0xADCE);
    cpu.set_flags(0xFC82);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA5F7E, 0x2E);
    machine.mem_store_byte(0xA5F7F, 0xF2);
    machine.mem_store_byte(0xA5F80, 0xAF);
    machine.mem_store_byte(0xA5F81, 0x90);
    machine.mem_store_byte(0xA5F82, 0x90);
    machine.mem_store_byte(0xA5F83, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xADD1);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA5F7E), 0x2E);
    EXPECT_EQ(memory.load8(0xA5F7F), 0xF2);
    EXPECT_EQ(memory.load8(0xA5F80), 0xAF);
    EXPECT_EQ(memory.load8(0xA5F81), 0x90);
    EXPECT_EQ(memory.load8(0xA5F82), 0x90);
    EXPECT_EQ(memory.load8(0xA5F83), 0x90);
}

TEST_F(MachineTest, ds_rep_lodsw)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0xFEA8);
    cpu.set_cx(0x0036);
    cpu.set_dx(0xB03C);
    cpu.set_cs(0xAFE1);
    cpu.set_ss(0x35AF);
    cpu.set_ds(0x9408);
    cpu.set_es(0x9669);
    cpu.set_sp(0x9DD7);
    cpu.set_bp(0x3CDD);
    cpu.set_si(0x9D7D);
    cpu.set_di(0x0225);
    cpu.set_ip(0x328B);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB309B, 0x3E);
    machine.mem_store_byte(0xB309C, 0xF3);
    machine.mem_store_byte(0xB309D, 0xAD);
    machine.mem_store_byte(0xB309E, 0x90);
    machine.mem_store_byte(0xB309F, 0x90);
    machine.mem_store_byte(0x9DDFD, 0x34);
    machine.mem_store_byte(0x9DDFE, 0x7B);
    machine.mem_store_byte(0x9DDFB, 0x54);
    machine.mem_store_byte(0x9DDFC, 0xDD);
    machine.mem_store_byte(0x9DDF9, 0xDF);
    machine.mem_store_byte(0x9DDFA, 0x34);
    machine.mem_store_byte(0x9DDF7, 0x7E);
    machine.mem_store_byte(0x9DDF8, 0x8D);
    machine.mem_store_byte(0x9DDF5, 0xF3);
    machine.mem_store_byte(0x9DDF6, 0x6C);
    machine.mem_store_byte(0x9DDF3, 0x85);
    machine.mem_store_byte(0x9DDF4, 0x19);
    machine.mem_store_byte(0x9DDF1, 0xE3);
    machine.mem_store_byte(0x9DDF2, 0xDC);
    machine.mem_store_byte(0x9DDEF, 0x76);
    machine.mem_store_byte(0x9DDF0, 0xEA);
    machine.mem_store_byte(0x9DDED, 0x00);
    machine.mem_store_byte(0x9DDEE, 0xFB);
    machine.mem_store_byte(0x9DDEB, 0x82);
    machine.mem_store_byte(0x9DDEC, 0x0C);
    machine.mem_store_byte(0x9DDE9, 0xEE);
    machine.mem_store_byte(0x9DDEA, 0xEE);
    machine.mem_store_byte(0x9DDE7, 0x42);
    machine.mem_store_byte(0x9DDE8, 0x7B);
    machine.mem_store_byte(0x9DDE5, 0x7B);
    machine.mem_store_byte(0x9DDE6, 0x02);
    machine.mem_store_byte(0x9DDE3, 0x52);
    machine.mem_store_byte(0x9DDE4, 0xD3);
    machine.mem_store_byte(0x9DDE1, 0x61);
    machine.mem_store_byte(0x9DDE2, 0x80);
    machine.mem_store_byte(0x9DDDF, 0x84);
    machine.mem_store_byte(0x9DDE0, 0x63);
    machine.mem_store_byte(0x9DDDD, 0x4A);
    machine.mem_store_byte(0x9DDDE, 0x0B);
    machine.mem_store_byte(0x9DDDB, 0x6E);
    machine.mem_store_byte(0x9DDDC, 0x95);
    machine.mem_store_byte(0x9DDD9, 0x29);
    machine.mem_store_byte(0x9DDDA, 0xEE);
    machine.mem_store_byte(0x9DDD7, 0xD7);
    machine.mem_store_byte(0x9DDD8, 0xFC);
    machine.mem_store_byte(0x9DDD5, 0x9F);
    machine.mem_store_byte(0x9DDD6, 0x44);
    machine.mem_store_byte(0x9DDD3, 0x83);
    machine.mem_store_byte(0x9DDD4, 0x76);
    machine.mem_store_byte(0x9DDD1, 0x44);
    machine.mem_store_byte(0x9DDD2, 0x00);
    machine.mem_store_byte(0x9DDCF, 0x14);
    machine.mem_store_byte(0x9DDD0, 0xE8);
    machine.mem_store_byte(0x9DDCD, 0xFC);
    machine.mem_store_byte(0x9DDCE, 0x88);
    machine.mem_store_byte(0x9DDCB, 0x8C);
    machine.mem_store_byte(0x9DDCC, 0x78);
    machine.mem_store_byte(0x9DDC9, 0x3D);
    machine.mem_store_byte(0x9DDCA, 0xCC);
    machine.mem_store_byte(0x9DDC7, 0xF7);
    machine.mem_store_byte(0x9DDC8, 0x38);
    machine.mem_store_byte(0x9DDC5, 0xE4);
    machine.mem_store_byte(0x9DDC6, 0xE0);
    machine.mem_store_byte(0x9DDC3, 0x1A);
    machine.mem_store_byte(0x9DDC4, 0x6B);
    machine.mem_store_byte(0x9DDC1, 0x23);
    machine.mem_store_byte(0x9DDC2, 0x50);
    machine.mem_store_byte(0x9DDBF, 0x23);
    machine.mem_store_byte(0x9DDC0, 0xEC);
    machine.mem_store_byte(0x9DDBD, 0x62);
    machine.mem_store_byte(0x9DDBE, 0x70);
    machine.mem_store_byte(0x9DDBB, 0x87);
    machine.mem_store_byte(0x9DDBC, 0xA8);
    machine.mem_store_byte(0x9DDB9, 0xB7);
    machine.mem_store_byte(0x9DDBA, 0xB9);
    machine.mem_store_byte(0x9DDB7, 0x32);
    machine.mem_store_byte(0x9DDB8, 0x16);
    machine.mem_store_byte(0x9DDB5, 0xF1);
    machine.mem_store_byte(0x9DDB6, 0x6A);
    machine.mem_store_byte(0x9DDB3, 0x06);
    machine.mem_store_byte(0x9DDB4, 0xD7);
    machine.mem_store_byte(0x9DDB1, 0xCC);
    machine.mem_store_byte(0x9DDB2, 0xC6);
    machine.mem_store_byte(0x9DDAF, 0x0A);
    machine.mem_store_byte(0x9DDB0, 0xF9);
    machine.mem_store_byte(0x9DDAD, 0x35);
    machine.mem_store_byte(0x9DDAE, 0xB1);
    machine.mem_store_byte(0x9DDAB, 0x5B);
    machine.mem_store_byte(0x9DDAC, 0x95);
    machine.mem_store_byte(0x9DDA9, 0x21);
    machine.mem_store_byte(0x9DDAA, 0xC3);
    machine.mem_store_byte(0x9DDA7, 0xC4);
    machine.mem_store_byte(0x9DDA8, 0xBD);
    machine.mem_store_byte(0x9DDA5, 0x74);
    machine.mem_store_byte(0x9DDA6, 0xDF);
    machine.mem_store_byte(0x9DDA3, 0xC8);
    machine.mem_store_byte(0x9DDA4, 0x6C);
    machine.mem_store_byte(0x9DDA1, 0xBA);
    machine.mem_store_byte(0x9DDA2, 0x54);
    machine.mem_store_byte(0x9DD9F, 0x7F);
    machine.mem_store_byte(0x9DDA0, 0xEB);
    machine.mem_store_byte(0x9DD9D, 0xDA);
    machine.mem_store_byte(0x9DD9E, 0x3D);
    machine.mem_store_byte(0x9DD9B, 0xF0);
    machine.mem_store_byte(0x9DD9C, 0xFE);
    machine.mem_store_byte(0x9DD99, 0x02);
    machine.mem_store_byte(0x9DD9A, 0xFD);
    machine.mem_store_byte(0x9DD97, 0xFE);
    machine.mem_store_byte(0x9DD98, 0xA1);
    machine.mem_store_byte(0x9DD95, 0xF3);
    machine.mem_store_byte(0x9DD96, 0x8D);
    machine.mem_store_byte(0x9DD93, 0x55);
    machine.mem_store_byte(0x9DD94, 0x37);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x3755);
    EXPECT_EQ(cpu.get_cx(), 0x0000);
    EXPECT_EQ(cpu.get_si(), 0x9D11);
    EXPECT_EQ(cpu.get_ip(), 0x328E);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB309B), 0x3E);
    EXPECT_EQ(memory.load8(0xB309C), 0xF3);
    EXPECT_EQ(memory.load8(0xB309D), 0xAD);
    EXPECT_EQ(memory.load8(0xB309E), 0x90);
    EXPECT_EQ(memory.load8(0xB309F), 0x90);
    EXPECT_EQ(memory.load8(0x9DDFD), 0x34);
    EXPECT_EQ(memory.load8(0x9DDFE), 0x7B);
    EXPECT_EQ(memory.load8(0x9DDFB), 0x54);
    EXPECT_EQ(memory.load8(0x9DDFC), 0xDD);
    EXPECT_EQ(memory.load8(0x9DDF9), 0xDF);
    EXPECT_EQ(memory.load8(0x9DDFA), 0x34);
    EXPECT_EQ(memory.load8(0x9DDF7), 0x7E);
    EXPECT_EQ(memory.load8(0x9DDF8), 0x8D);
    EXPECT_EQ(memory.load8(0x9DDF5), 0xF3);
    EXPECT_EQ(memory.load8(0x9DDF6), 0x6C);
    EXPECT_EQ(memory.load8(0x9DDF3), 0x85);
    EXPECT_EQ(memory.load8(0x9DDF4), 0x19);
    EXPECT_EQ(memory.load8(0x9DDF1), 0xE3);
    EXPECT_EQ(memory.load8(0x9DDF2), 0xDC);
    EXPECT_EQ(memory.load8(0x9DDEF), 0x76);
    EXPECT_EQ(memory.load8(0x9DDF0), 0xEA);
    EXPECT_EQ(memory.load8(0x9DDED), 0x00);
    EXPECT_EQ(memory.load8(0x9DDEE), 0xFB);
    EXPECT_EQ(memory.load8(0x9DDEB), 0x82);
    EXPECT_EQ(memory.load8(0x9DDEC), 0x0C);
    EXPECT_EQ(memory.load8(0x9DDE9), 0xEE);
    EXPECT_EQ(memory.load8(0x9DDEA), 0xEE);
    EXPECT_EQ(memory.load8(0x9DDE7), 0x42);
    EXPECT_EQ(memory.load8(0x9DDE8), 0x7B);
    EXPECT_EQ(memory.load8(0x9DDE5), 0x7B);
    EXPECT_EQ(memory.load8(0x9DDE6), 0x02);
    EXPECT_EQ(memory.load8(0x9DDE3), 0x52);
    EXPECT_EQ(memory.load8(0x9DDE4), 0xD3);
    EXPECT_EQ(memory.load8(0x9DDE1), 0x61);
    EXPECT_EQ(memory.load8(0x9DDE2), 0x80);
    EXPECT_EQ(memory.load8(0x9DDDF), 0x84);
    EXPECT_EQ(memory.load8(0x9DDE0), 0x63);
    EXPECT_EQ(memory.load8(0x9DDDD), 0x4A);
    EXPECT_EQ(memory.load8(0x9DDDE), 0x0B);
    EXPECT_EQ(memory.load8(0x9DDDB), 0x6E);
    EXPECT_EQ(memory.load8(0x9DDDC), 0x95);
    EXPECT_EQ(memory.load8(0x9DDD9), 0x29);
    EXPECT_EQ(memory.load8(0x9DDDA), 0xEE);
    EXPECT_EQ(memory.load8(0x9DDD7), 0xD7);
    EXPECT_EQ(memory.load8(0x9DDD8), 0xFC);
    EXPECT_EQ(memory.load8(0x9DDD5), 0x9F);
    EXPECT_EQ(memory.load8(0x9DDD6), 0x44);
    EXPECT_EQ(memory.load8(0x9DDD3), 0x83);
    EXPECT_EQ(memory.load8(0x9DDD4), 0x76);
    EXPECT_EQ(memory.load8(0x9DDD1), 0x44);
    EXPECT_EQ(memory.load8(0x9DDD2), 0x00);
    EXPECT_EQ(memory.load8(0x9DDCF), 0x14);
    EXPECT_EQ(memory.load8(0x9DDD0), 0xE8);
    EXPECT_EQ(memory.load8(0x9DDCD), 0xFC);
    EXPECT_EQ(memory.load8(0x9DDCE), 0x88);
    EXPECT_EQ(memory.load8(0x9DDCB), 0x8C);
    EXPECT_EQ(memory.load8(0x9DDCC), 0x78);
    EXPECT_EQ(memory.load8(0x9DDC9), 0x3D);
    EXPECT_EQ(memory.load8(0x9DDCA), 0xCC);
    EXPECT_EQ(memory.load8(0x9DDC7), 0xF7);
    EXPECT_EQ(memory.load8(0x9DDC8), 0x38);
    EXPECT_EQ(memory.load8(0x9DDC5), 0xE4);
    EXPECT_EQ(memory.load8(0x9DDC6), 0xE0);
    EXPECT_EQ(memory.load8(0x9DDC3), 0x1A);
    EXPECT_EQ(memory.load8(0x9DDC4), 0x6B);
    EXPECT_EQ(memory.load8(0x9DDC1), 0x23);
    EXPECT_EQ(memory.load8(0x9DDC2), 0x50);
    EXPECT_EQ(memory.load8(0x9DDBF), 0x23);
    EXPECT_EQ(memory.load8(0x9DDC0), 0xEC);
    EXPECT_EQ(memory.load8(0x9DDBD), 0x62);
    EXPECT_EQ(memory.load8(0x9DDBE), 0x70);
    EXPECT_EQ(memory.load8(0x9DDBB), 0x87);
    EXPECT_EQ(memory.load8(0x9DDBC), 0xA8);
    EXPECT_EQ(memory.load8(0x9DDB9), 0xB7);
    EXPECT_EQ(memory.load8(0x9DDBA), 0xB9);
    EXPECT_EQ(memory.load8(0x9DDB7), 0x32);
    EXPECT_EQ(memory.load8(0x9DDB8), 0x16);
    EXPECT_EQ(memory.load8(0x9DDB5), 0xF1);
    EXPECT_EQ(memory.load8(0x9DDB6), 0x6A);
    EXPECT_EQ(memory.load8(0x9DDB3), 0x06);
    EXPECT_EQ(memory.load8(0x9DDB4), 0xD7);
    EXPECT_EQ(memory.load8(0x9DDB1), 0xCC);
    EXPECT_EQ(memory.load8(0x9DDB2), 0xC6);
    EXPECT_EQ(memory.load8(0x9DDAF), 0x0A);
    EXPECT_EQ(memory.load8(0x9DDB0), 0xF9);
    EXPECT_EQ(memory.load8(0x9DDAD), 0x35);
    EXPECT_EQ(memory.load8(0x9DDAE), 0xB1);
    EXPECT_EQ(memory.load8(0x9DDAB), 0x5B);
    EXPECT_EQ(memory.load8(0x9DDAC), 0x95);
    EXPECT_EQ(memory.load8(0x9DDA9), 0x21);
    EXPECT_EQ(memory.load8(0x9DDAA), 0xC3);
    EXPECT_EQ(memory.load8(0x9DDA7), 0xC4);
    EXPECT_EQ(memory.load8(0x9DDA8), 0xBD);
    EXPECT_EQ(memory.load8(0x9DDA5), 0x74);
    EXPECT_EQ(memory.load8(0x9DDA6), 0xDF);
    EXPECT_EQ(memory.load8(0x9DDA3), 0xC8);
    EXPECT_EQ(memory.load8(0x9DDA4), 0x6C);
    EXPECT_EQ(memory.load8(0x9DDA1), 0xBA);
    EXPECT_EQ(memory.load8(0x9DDA2), 0x54);
    EXPECT_EQ(memory.load8(0x9DD9F), 0x7F);
    EXPECT_EQ(memory.load8(0x9DDA0), 0xEB);
    EXPECT_EQ(memory.load8(0x9DD9D), 0xDA);
    EXPECT_EQ(memory.load8(0x9DD9E), 0x3D);
    EXPECT_EQ(memory.load8(0x9DD9B), 0xF0);
    EXPECT_EQ(memory.load8(0x9DD9C), 0xFE);
    EXPECT_EQ(memory.load8(0x9DD99), 0x02);
    EXPECT_EQ(memory.load8(0x9DD9A), 0xFD);
    EXPECT_EQ(memory.load8(0x9DD97), 0xFE);
    EXPECT_EQ(memory.load8(0x9DD98), 0xA1);
    EXPECT_EQ(memory.load8(0x9DD95), 0xF3);
    EXPECT_EQ(memory.load8(0x9DD96), 0x8D);
    EXPECT_EQ(memory.load8(0x9DD93), 0x55);
    EXPECT_EQ(memory.load8(0x9DD94), 0x37);
}

TEST_F(MachineTest, ds_rep_movsw)
{
    // Initial CPU State
    cpu.set_ax(0x271A);
    cpu.set_bx(0xCC15);
    cpu.set_cx(0x0020);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x8FDF);
    cpu.set_ss(0x925B);
    cpu.set_ds(0x4746);
    cpu.set_es(0xD01A);
    cpu.set_sp(0x50F3);
    cpu.set_bp(0xF3FD);
    cpu.set_si(0xCF7D);
    cpu.set_di(0x0511);
    cpu.set_ip(0x3000);
    cpu.set_flags(0xF0D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x92DF0, 0x3E);
    machine.mem_store_byte(0x92DF1, 0xF2);
    machine.mem_store_byte(0x92DF2, 0xA5);
    machine.mem_store_byte(0x92DF3, 0x90);
    machine.mem_store_byte(0x92DF4, 0x90);
    machine.mem_store_byte(0x92DF5, 0x90);
    machine.mem_store_byte(0x543DD, 0x87);
    machine.mem_store_byte(0x543DE, 0x5C);
    machine.mem_store_byte(0x543DF, 0xB9);
    machine.mem_store_byte(0x543E0, 0x90);
    machine.mem_store_byte(0x543E1, 0xCC);
    machine.mem_store_byte(0x543E2, 0xFF);
    machine.mem_store_byte(0x543E3, 0x00);
    machine.mem_store_byte(0x543E4, 0x81);
    machine.mem_store_byte(0x543E5, 0xFF);
    machine.mem_store_byte(0x543E6, 0x62);
    machine.mem_store_byte(0x543E7, 0x61);
    machine.mem_store_byte(0x543E8, 0x62);
    machine.mem_store_byte(0x543E9, 0x9B);
    machine.mem_store_byte(0x543EA, 0xC4);
    machine.mem_store_byte(0x543EB, 0xF8);
    machine.mem_store_byte(0x543EC, 0x60);
    machine.mem_store_byte(0x543ED, 0xBF);
    machine.mem_store_byte(0x543EE, 0x13);
    machine.mem_store_byte(0x543EF, 0x32);
    machine.mem_store_byte(0x543F0, 0x42);
    machine.mem_store_byte(0x543F1, 0x4E);
    machine.mem_store_byte(0x543F2, 0x63);
    machine.mem_store_byte(0x543F3, 0xB1);
    machine.mem_store_byte(0x543F4, 0x96);
    machine.mem_store_byte(0x543F5, 0x2D);
    machine.mem_store_byte(0x543F6, 0xB1);
    machine.mem_store_byte(0x543F7, 0x34);
    machine.mem_store_byte(0x543F8, 0x4D);
    machine.mem_store_byte(0x543F9, 0x02);
    machine.mem_store_byte(0x543FA, 0x53);
    machine.mem_store_byte(0x543FB, 0x45);
    machine.mem_store_byte(0x543FC, 0xA0);
    machine.mem_store_byte(0x543FD, 0x62);
    machine.mem_store_byte(0x543FE, 0x65);
    machine.mem_store_byte(0x543FF, 0x55);
    machine.mem_store_byte(0x54400, 0x21);
    machine.mem_store_byte(0x54401, 0x9A);
    machine.mem_store_byte(0x54402, 0x8A);
    machine.mem_store_byte(0x54403, 0x4C);
    machine.mem_store_byte(0x54404, 0x1B);
    machine.mem_store_byte(0x54405, 0xBB);
    machine.mem_store_byte(0x54406, 0x53);
    machine.mem_store_byte(0x54407, 0x2C);
    machine.mem_store_byte(0x54408, 0x79);
    machine.mem_store_byte(0x54409, 0x7A);
    machine.mem_store_byte(0x5440A, 0x0C);
    machine.mem_store_byte(0x5440B, 0xFC);
    machine.mem_store_byte(0x5440C, 0xC5);
    machine.mem_store_byte(0x5440D, 0xD6);
    machine.mem_store_byte(0x5440E, 0x9A);
    machine.mem_store_byte(0x5440F, 0x3D);
    machine.mem_store_byte(0x54410, 0x1C);
    machine.mem_store_byte(0x54411, 0xB4);
    machine.mem_store_byte(0x54412, 0x39);
    machine.mem_store_byte(0x54413, 0xA7);
    machine.mem_store_byte(0x54414, 0x1A);
    machine.mem_store_byte(0x54415, 0x2B);
    machine.mem_store_byte(0x54416, 0xFD);
    machine.mem_store_byte(0x54417, 0xA1);
    machine.mem_store_byte(0x54418, 0xE1);
    machine.mem_store_byte(0x54419, 0x21);
    machine.mem_store_byte(0x5441A, 0xC0);
    machine.mem_store_byte(0x5441B, 0x83);
    machine.mem_store_byte(0x5441C, 0x1F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0000);
    EXPECT_EQ(cpu.get_si(), 0xCFBD);
    EXPECT_EQ(cpu.get_di(), 0x0551);
    EXPECT_EQ(cpu.get_ip(), 0x3003);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x92DF0), 0x3E);
    EXPECT_EQ(memory.load8(0x92DF1), 0xF2);
    EXPECT_EQ(memory.load8(0x92DF2), 0xA5);
    EXPECT_EQ(memory.load8(0x92DF3), 0x90);
    EXPECT_EQ(memory.load8(0x92DF4), 0x90);
    EXPECT_EQ(memory.load8(0x92DF5), 0x90);
    EXPECT_EQ(memory.load8(0x543DD), 0x87);
    EXPECT_EQ(memory.load8(0x543DE), 0x5C);
    EXPECT_EQ(memory.load8(0x543DF), 0xB9);
    EXPECT_EQ(memory.load8(0x543E0), 0x90);
    EXPECT_EQ(memory.load8(0x543E1), 0xCC);
    EXPECT_EQ(memory.load8(0x543E2), 0xFF);
    EXPECT_EQ(memory.load8(0x543E3), 0x00);
    EXPECT_EQ(memory.load8(0x543E4), 0x81);
    EXPECT_EQ(memory.load8(0x543E5), 0xFF);
    EXPECT_EQ(memory.load8(0x543E6), 0x62);
    EXPECT_EQ(memory.load8(0x543E7), 0x61);
    EXPECT_EQ(memory.load8(0x543E8), 0x62);
    EXPECT_EQ(memory.load8(0x543E9), 0x9B);
    EXPECT_EQ(memory.load8(0x543EA), 0xC4);
    EXPECT_EQ(memory.load8(0x543EB), 0xF8);
    EXPECT_EQ(memory.load8(0x543EC), 0x60);
    EXPECT_EQ(memory.load8(0x543ED), 0xBF);
    EXPECT_EQ(memory.load8(0x543EE), 0x13);
    EXPECT_EQ(memory.load8(0x543EF), 0x32);
    EXPECT_EQ(memory.load8(0x543F0), 0x42);
    EXPECT_EQ(memory.load8(0x543F1), 0x4E);
    EXPECT_EQ(memory.load8(0x543F2), 0x63);
    EXPECT_EQ(memory.load8(0x543F3), 0xB1);
    EXPECT_EQ(memory.load8(0x543F4), 0x96);
    EXPECT_EQ(memory.load8(0x543F5), 0x2D);
    EXPECT_EQ(memory.load8(0x543F6), 0xB1);
    EXPECT_EQ(memory.load8(0x543F7), 0x34);
    EXPECT_EQ(memory.load8(0x543F8), 0x4D);
    EXPECT_EQ(memory.load8(0x543F9), 0x02);
    EXPECT_EQ(memory.load8(0x543FA), 0x53);
    EXPECT_EQ(memory.load8(0x543FB), 0x45);
    EXPECT_EQ(memory.load8(0x543FC), 0xA0);
    EXPECT_EQ(memory.load8(0x543FD), 0x62);
    EXPECT_EQ(memory.load8(0x543FE), 0x65);
    EXPECT_EQ(memory.load8(0x543FF), 0x55);
    EXPECT_EQ(memory.load8(0x54400), 0x21);
    EXPECT_EQ(memory.load8(0x54401), 0x9A);
    EXPECT_EQ(memory.load8(0x54402), 0x8A);
    EXPECT_EQ(memory.load8(0x54403), 0x4C);
    EXPECT_EQ(memory.load8(0x54404), 0x1B);
    EXPECT_EQ(memory.load8(0x54405), 0xBB);
    EXPECT_EQ(memory.load8(0x54406), 0x53);
    EXPECT_EQ(memory.load8(0x54407), 0x2C);
    EXPECT_EQ(memory.load8(0x54408), 0x79);
    EXPECT_EQ(memory.load8(0x54409), 0x7A);
    EXPECT_EQ(memory.load8(0x5440A), 0x0C);
    EXPECT_EQ(memory.load8(0x5440B), 0xFC);
    EXPECT_EQ(memory.load8(0x5440C), 0xC5);
    EXPECT_EQ(memory.load8(0x5440D), 0xD6);
    EXPECT_EQ(memory.load8(0x5440E), 0x9A);
    EXPECT_EQ(memory.load8(0x5440F), 0x3D);
    EXPECT_EQ(memory.load8(0x54410), 0x1C);
    EXPECT_EQ(memory.load8(0x54411), 0xB4);
    EXPECT_EQ(memory.load8(0x54412), 0x39);
    EXPECT_EQ(memory.load8(0x54413), 0xA7);
    EXPECT_EQ(memory.load8(0x54414), 0x1A);
    EXPECT_EQ(memory.load8(0x54415), 0x2B);
    EXPECT_EQ(memory.load8(0x54416), 0xFD);
    EXPECT_EQ(memory.load8(0x54417), 0xA1);
    EXPECT_EQ(memory.load8(0x54418), 0xE1);
    EXPECT_EQ(memory.load8(0x54419), 0x21);
    EXPECT_EQ(memory.load8(0x5441A), 0xC0);
    EXPECT_EQ(memory.load8(0x5441B), 0x83);
    EXPECT_EQ(memory.load8(0x5441C), 0x1F);
    EXPECT_EQ(memory.load8(0xD06B1), 0x87);
    EXPECT_EQ(memory.load8(0xD06B2), 0x5C);
    EXPECT_EQ(memory.load8(0xD06B3), 0xB9);
    EXPECT_EQ(memory.load8(0xD06B4), 0x90);
    EXPECT_EQ(memory.load8(0xD06B5), 0xCC);
    EXPECT_EQ(memory.load8(0xD06B6), 0xFF);
    EXPECT_EQ(memory.load8(0xD06B7), 0x00);
    EXPECT_EQ(memory.load8(0xD06B8), 0x81);
    EXPECT_EQ(memory.load8(0xD06B9), 0xFF);
    EXPECT_EQ(memory.load8(0xD06BA), 0x62);
    EXPECT_EQ(memory.load8(0xD06BB), 0x61);
    EXPECT_EQ(memory.load8(0xD06BC), 0x62);
    EXPECT_EQ(memory.load8(0xD06BD), 0x9B);
    EXPECT_EQ(memory.load8(0xD06BE), 0xC4);
    EXPECT_EQ(memory.load8(0xD06BF), 0xF8);
    EXPECT_EQ(memory.load8(0xD06C0), 0x60);
    EXPECT_EQ(memory.load8(0xD06C1), 0xBF);
    EXPECT_EQ(memory.load8(0xD06C2), 0x13);
    EXPECT_EQ(memory.load8(0xD06C3), 0x32);
    EXPECT_EQ(memory.load8(0xD06C4), 0x42);
    EXPECT_EQ(memory.load8(0xD06C5), 0x4E);
    EXPECT_EQ(memory.load8(0xD06C6), 0x63);
    EXPECT_EQ(memory.load8(0xD06C7), 0xB1);
    EXPECT_EQ(memory.load8(0xD06C8), 0x96);
    EXPECT_EQ(memory.load8(0xD06C9), 0x2D);
    EXPECT_EQ(memory.load8(0xD06CA), 0xB1);
    EXPECT_EQ(memory.load8(0xD06CB), 0x34);
    EXPECT_EQ(memory.load8(0xD06CC), 0x4D);
    EXPECT_EQ(memory.load8(0xD06CD), 0x02);
    EXPECT_EQ(memory.load8(0xD06CE), 0x53);
    EXPECT_EQ(memory.load8(0xD06CF), 0x45);
    EXPECT_EQ(memory.load8(0xD06D0), 0xA0);
    EXPECT_EQ(memory.load8(0xD06D1), 0x62);
    EXPECT_EQ(memory.load8(0xD06D2), 0x65);
    EXPECT_EQ(memory.load8(0xD06D3), 0x55);
    EXPECT_EQ(memory.load8(0xD06D4), 0x21);
    EXPECT_EQ(memory.load8(0xD06D5), 0x9A);
    EXPECT_EQ(memory.load8(0xD06D6), 0x8A);
    EXPECT_EQ(memory.load8(0xD06D7), 0x4C);
    EXPECT_EQ(memory.load8(0xD06D8), 0x1B);
    EXPECT_EQ(memory.load8(0xD06D9), 0xBB);
    EXPECT_EQ(memory.load8(0xD06DA), 0x53);
    EXPECT_EQ(memory.load8(0xD06DB), 0x2C);
    EXPECT_EQ(memory.load8(0xD06DC), 0x79);
    EXPECT_EQ(memory.load8(0xD06DD), 0x7A);
    EXPECT_EQ(memory.load8(0xD06DE), 0x0C);
    EXPECT_EQ(memory.load8(0xD06DF), 0xFC);
    EXPECT_EQ(memory.load8(0xD06E0), 0xC5);
    EXPECT_EQ(memory.load8(0xD06E1), 0xD6);
    EXPECT_EQ(memory.load8(0xD06E2), 0x9A);
    EXPECT_EQ(memory.load8(0xD06E3), 0x3D);
    EXPECT_EQ(memory.load8(0xD06E4), 0x1C);
    EXPECT_EQ(memory.load8(0xD06E5), 0xB4);
    EXPECT_EQ(memory.load8(0xD06E6), 0x39);
    EXPECT_EQ(memory.load8(0xD06E7), 0xA7);
    EXPECT_EQ(memory.load8(0xD06E8), 0x1A);
    EXPECT_EQ(memory.load8(0xD06E9), 0x2B);
    EXPECT_EQ(memory.load8(0xD06EA), 0xFD);
    EXPECT_EQ(memory.load8(0xD06EB), 0xA1);
    EXPECT_EQ(memory.load8(0xD06EC), 0xE1);
    EXPECT_EQ(memory.load8(0xD06ED), 0x21);
    EXPECT_EQ(memory.load8(0xD06EE), 0xC0);
    EXPECT_EQ(memory.load8(0xD06EF), 0x83);
    EXPECT_EQ(memory.load8(0xD06F0), 0x1F);
}

TEST_F(MachineTest, ds_repe_scasb)
{
    // Initial CPU State
    cpu.set_ax(0x69BE);
    cpu.set_bx(0x19D3);
    cpu.set_cx(0x0036);
    cpu.set_dx(0x6F7A);
    cpu.set_cs(0x5F1E);
    cpu.set_ss(0x54DD);
    cpu.set_ds(0xF935);
    cpu.set_es(0x8F19);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x661A);
    cpu.set_si(0x8E0D);
    cpu.set_di(0xFA20);
    cpu.set_ip(0x1ECC);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x610AC, 0x3E);
    machine.mem_store_byte(0x610AD, 0xF3);
    machine.mem_store_byte(0x610AE, 0xAE);
    machine.mem_store_byte(0x610AF, 0x90);
    machine.mem_store_byte(0x610B0, 0x90);
    machine.mem_store_byte(0x610B1, 0x90);
    machine.mem_store_byte(0x9EBB0, 0x99);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0035);
    EXPECT_EQ(cpu.get_di(), 0xFA21);
    EXPECT_EQ(cpu.get_ip(), 0x1ECF);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x610AC), 0x3E);
    EXPECT_EQ(memory.load8(0x610AD), 0xF3);
    EXPECT_EQ(memory.load8(0x610AE), 0xAE);
    EXPECT_EQ(memory.load8(0x610AF), 0x90);
    EXPECT_EQ(memory.load8(0x610B0), 0x90);
    EXPECT_EQ(memory.load8(0x610B1), 0x90);
    EXPECT_EQ(memory.load8(0x9EBB0), 0x99);
}

TEST_F(MachineTest, stosb)
{
    // Initial CPU State
    cpu.set_ax(0x08E8);
    cpu.set_bx(0xF7F2);
    cpu.set_cx(0x0008);
    cpu.set_dx(0x4E06);
    cpu.set_cs(0x7357);
    cpu.set_ss(0xF8DC);
    cpu.set_ds(0xC5CF);
    cpu.set_es(0xD790);
    cpu.set_sp(0xC8BA);
    cpu.set_bp(0x3A7C);
    cpu.set_si(0x95A7);
    cpu.set_di(0xCC2E);
    cpu.set_ip(0x17DE);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x74D4E, 0xAA);
    machine.mem_store_byte(0x74D4F, 0x90);
    machine.mem_store_byte(0x74D50, 0x90);
    machine.mem_store_byte(0x74D51, 0x90);
    machine.mem_store_byte(0x74D52, 0x90);
    machine.mem_store_byte(0x74D53, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xCC2D);
    EXPECT_EQ(cpu.get_ip(), 0x17DF);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x74D4E), 0xAA);
    EXPECT_EQ(memory.load8(0x74D4F), 0x90);
    EXPECT_EQ(memory.load8(0x74D50), 0x90);
    EXPECT_EQ(memory.load8(0x74D51), 0x90);
    EXPECT_EQ(memory.load8(0x74D52), 0x90);
    EXPECT_EQ(memory.load8(0x74D53), 0x90);
    EXPECT_EQ(memory.load8(0xE452E), 0xE8);
}

TEST_F(MachineTest, stosw)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x39B2);
    cpu.set_cx(0x0054);
    cpu.set_dx(0xF59E);
    cpu.set_cs(0xECB6);
    cpu.set_ss(0xA175);
    cpu.set_ds(0x1094);
    cpu.set_es(0xB254);
    cpu.set_sp(0x4CAE);
    cpu.set_bp(0x5FE2);
    cpu.set_si(0xEE32);
    cpu.set_di(0xDC0C);
    cpu.set_ip(0x8ACD);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF562D, 0xAB);
    machine.mem_store_byte(0xF562E, 0x90);
    machine.mem_store_byte(0xF562F, 0x90);
    machine.mem_store_byte(0xF5630, 0x90);
    machine.mem_store_byte(0xF5631, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xDC0A);
    EXPECT_EQ(cpu.get_ip(), 0x8ACE);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF562D), 0xAB);
    EXPECT_EQ(memory.load8(0xF562E), 0x90);
    EXPECT_EQ(memory.load8(0xF562F), 0x90);
    EXPECT_EQ(memory.load8(0xF5630), 0x90);
    EXPECT_EQ(memory.load8(0xF5631), 0x90);
    EXPECT_EQ(memory.load8(0xC014C), 0x00);
    EXPECT_EQ(memory.load8(0xC014D), 0x00);
}
