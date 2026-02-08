#include "fixture.h"

//
// mul byte [ds:bp-3Eh]
//
TEST_F(MachineTest, mul_byte_ds_bp_3Eh)
{
    // Initial CPU State
    cpu.set_ax(0x48CE);
    cpu.set_bx(0xEC0B);
    cpu.set_cx(0x2764);
    cpu.set_dx(0x2441);
    cpu.set_cs(0xE7EB);
    cpu.set_ss(0x1211);
    cpu.set_ds(0xAB96);
    cpu.set_es(0x2004);
    cpu.set_sp(0x9105);
    cpu.set_bp(0x310C);
    cpu.set_si(0xAED7);
    cpu.set_di(0xA80C);
    cpu.set_ip(0xA746);
    cpu.set_flags(0xFC43);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF25F6, 0x3E);
    machine.mem_store_byte(0xF25F7, 0xF6);
    machine.mem_store_byte(0xF25F8, 0x66);
    machine.mem_store_byte(0xF25F9, 0xC2);
    machine.mem_store_byte(0xF25FA, 0x90);
    machine.mem_store_byte(0xF25FB, 0x90);
    machine.mem_store_byte(0xAEA2E, 0x01);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x00CE);
    EXPECT_EQ(cpu.get_ip(), 0xA74A);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF25F6), 0x3E);
    EXPECT_EQ(memory.load8(0xF25F7), 0xF6);
    EXPECT_EQ(memory.load8(0xF25F8), 0x66);
    EXPECT_EQ(memory.load8(0xF25F9), 0xC2);
    EXPECT_EQ(memory.load8(0xF25FA), 0x90);
    EXPECT_EQ(memory.load8(0xF25FB), 0x90);
    EXPECT_EQ(memory.load8(0xAEA2E), 0x01);
}

//
// mul byte [ds:bx+di]
//
TEST_F(MachineTest, mul_byte_ds_bx_di)
{
    // Initial CPU State
    cpu.set_ax(0x8902);
    cpu.set_bx(0x0960);
    cpu.set_cx(0x13E0);
    cpu.set_dx(0x46AF);
    cpu.set_cs(0x3121);
    cpu.set_ss(0x8753);
    cpu.set_ds(0x1204);
    cpu.set_es(0x131E);
    cpu.set_sp(0x9111);
    cpu.set_bp(0x7F2E);
    cpu.set_si(0xBE0A);
    cpu.set_di(0x1E46);
    cpu.set_ip(0xF0A2);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x402B2, 0xF6);
    machine.mem_store_byte(0x402B3, 0x21);
    machine.mem_store_byte(0x402B4, 0x90);
    machine.mem_store_byte(0x402B5, 0x90);
    machine.mem_store_byte(0x402B6, 0x90);
    machine.mem_store_byte(0x402B7, 0x90);
    machine.mem_store_byte(0x147E6, 0x10);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0020);
    EXPECT_EQ(cpu.get_ip(), 0xF0A4);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x402B2), 0xF6);
    EXPECT_EQ(memory.load8(0x402B3), 0x21);
    EXPECT_EQ(memory.load8(0x402B4), 0x90);
    EXPECT_EQ(memory.load8(0x402B5), 0x90);
    EXPECT_EQ(memory.load8(0x402B6), 0x90);
    EXPECT_EQ(memory.load8(0x402B7), 0x90);
    EXPECT_EQ(memory.load8(0x147E6), 0x10);
}

//
// shl byte [ds:bp+si+69E0h], cl
//
TEST_F(MachineTest, shl_byte_ds_bp_si_69E0h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xD3DC);
    cpu.set_bx(0x0BEE);
    cpu.set_cx(0xD404);
    cpu.set_dx(0x0000);
    cpu.set_cs(0x57AD);
    cpu.set_ss(0x3A36);
    cpu.set_ds(0x06D0);
    cpu.set_es(0x610E);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x9C91);
    cpu.set_si(0x8FF5);
    cpu.set_di(0xC77E);
    cpu.set_ip(0x9363);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x60E33, 0x3E);
    machine.mem_store_byte(0x60E34, 0xD2);
    machine.mem_store_byte(0x60E35, 0xA2);
    machine.mem_store_byte(0x60E36, 0xE0);
    machine.mem_store_byte(0x60E37, 0x69);
    machine.mem_store_byte(0x10366, 0x37);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9368);
    EXPECT_FLAGS(0xF813);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x60E33), 0x3E);
    EXPECT_EQ(memory.load8(0x60E34), 0xD2);
    EXPECT_EQ(memory.load8(0x60E35), 0xA2);
    EXPECT_EQ(memory.load8(0x60E36), 0xE0);
    EXPECT_EQ(memory.load8(0x60E37), 0x69);
    EXPECT_EQ(memory.load8(0x10366), 0x70);
}

//
// shl byte [ds:bx+di+21A7h], cl
//
TEST_F(MachineTest, shl_byte_ds_bx_di_21A7h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x5C7E);
    cpu.set_cx(0x5B04);
    cpu.set_dx(0x6ACD);
    cpu.set_cs(0x024C);
    cpu.set_ss(0xA931);
    cpu.set_ds(0xBC06);
    cpu.set_es(0xE8D1);
    cpu.set_sp(0xF646);
    cpu.set_bp(0x5EE2);
    cpu.set_si(0x970D);
    cpu.set_di(0xC9D3);
    cpu.set_ip(0x1CB3);
    cpu.set_flags(0xF416);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x04173, 0xD2);
    machine.mem_store_byte(0x04174, 0xA1);
    machine.mem_store_byte(0x04175, 0xA7);
    machine.mem_store_byte(0x04176, 0x21);
    machine.mem_store_byte(0x04177, 0x90);
    machine.mem_store_byte(0xC0858, 0x6D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1CB7);
    EXPECT_FLAGS(0xFC92);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x04173), 0xD2);
    EXPECT_EQ(memory.load8(0x04174), 0xA1);
    EXPECT_EQ(memory.load8(0x04175), 0xA7);
    EXPECT_EQ(memory.load8(0x04176), 0x21);
    EXPECT_EQ(memory.load8(0x04177), 0x90);
    EXPECT_EQ(memory.load8(0xC0858), 0xD0);
}

//
// shl byte [es:bp+si+51h], cl
//
TEST_F(MachineTest, shl_byte_es_bp_si_51h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xFEF7);
    cpu.set_bx(0x5F16);
    cpu.set_cx(0xA402);
    cpu.set_dx(0x7D0D);
    cpu.set_cs(0xFEA9);
    cpu.set_ss(0xD42A);
    cpu.set_ds(0xF938);
    cpu.set_es(0xBD28);
    cpu.set_sp(0x2A93);
    cpu.set_bp(0xDEFC);
    cpu.set_si(0xA940);
    cpu.set_di(0x1402);
    cpu.set_ip(0x1CD4);
    cpu.set_flags(0xF412);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x00764, 0x26);
    machine.mem_store_byte(0x00765, 0xD2);
    machine.mem_store_byte(0x00766, 0x62);
    machine.mem_store_byte(0x00767, 0x51);
    machine.mem_store_byte(0x00768, 0x90);
    machine.mem_store_byte(0x00769, 0x90);
    machine.mem_store_byte(0xC5B0D, 0xB5);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1CD8);
    EXPECT_FLAGS(0xFC96);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x00764), 0x26);
    EXPECT_EQ(memory.load8(0x00765), 0xD2);
    EXPECT_EQ(memory.load8(0x00766), 0x62);
    EXPECT_EQ(memory.load8(0x00767), 0x51);
    EXPECT_EQ(memory.load8(0x00768), 0x90);
    EXPECT_EQ(memory.load8(0x00769), 0x90);
    EXPECT_EQ(memory.load8(0xC5B0D), 0xD4);
}

//
// shl byte [ss:bx+di-7AAFh], cl
//
TEST_F(MachineTest, shl_byte_ss_bx_di_7AAFh_cl)
{
    // Initial CPU State
    cpu.set_ax(0xCE41);
    cpu.set_bx(0x9858);
    cpu.set_cx(0x4A08);
    cpu.set_dx(0xC4AE);
    cpu.set_cs(0x2C15);
    cpu.set_ss(0x28D2);
    cpu.set_ds(0x77D9);
    cpu.set_es(0x1166);
    cpu.set_sp(0xC72D);
    cpu.set_bp(0x83BF);
    cpu.set_si(0xC988);
    cpu.set_di(0xB20F);
    cpu.set_ip(0x9D40);
    cpu.set_flags(0xF416);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x35E90, 0x36);
    machine.mem_store_byte(0x35E91, 0xD2);
    machine.mem_store_byte(0x35E92, 0xA1);
    machine.mem_store_byte(0x35E93, 0x51);
    machine.mem_store_byte(0x35E94, 0x85);
    machine.mem_store_byte(0x35E95, 0x90);
    machine.mem_store_byte(0x35CD8, 0x73);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9D45);
    EXPECT_FLAGS(0xFC47);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x35E90), 0x36);
    EXPECT_EQ(memory.load8(0x35E91), 0xD2);
    EXPECT_EQ(memory.load8(0x35E92), 0xA1);
    EXPECT_EQ(memory.load8(0x35E93), 0x51);
    EXPECT_EQ(memory.load8(0x35E94), 0x85);
    EXPECT_EQ(memory.load8(0x35E95), 0x90);
    EXPECT_EQ(memory.load8(0x35CD8), 0x00);
}

//
// shl byte [ss:di+20DAh], cl
//
TEST_F(MachineTest, shl_byte_ss_di_20DAh_cl)
{
    // Initial CPU State
    cpu.set_ax(0xB30B);
    cpu.set_bx(0x3E92);
    cpu.set_cx(0xCB02);
    cpu.set_dx(0x3C2A);
    cpu.set_cs(0xFCF2);
    cpu.set_ss(0x0284);
    cpu.set_ds(0x4832);
    cpu.set_es(0x3EE6);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x6AC9);
    cpu.set_si(0x4DC4);
    cpu.set_di(0xED58);
    cpu.set_ip(0xF93D);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0C85D, 0x36);
    machine.mem_store_byte(0x0C85E, 0xD2);
    machine.mem_store_byte(0x0C85F, 0xA5);
    machine.mem_store_byte(0x0C860, 0xDA);
    machine.mem_store_byte(0x0C861, 0x20);
    machine.mem_store_byte(0x03672, 0xA7);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF942);
    EXPECT_FLAGS(0xF896);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0C85D), 0x36);
    EXPECT_EQ(memory.load8(0x0C85E), 0xD2);
    EXPECT_EQ(memory.load8(0x0C85F), 0xA5);
    EXPECT_EQ(memory.load8(0x0C860), 0xDA);
    EXPECT_EQ(memory.load8(0x0C861), 0x20);
    EXPECT_EQ(memory.load8(0x03672), 0x9C);
}

//
// shl sp, cl
//
TEST_F(MachineTest, shl_sp_cl)
{
    // Initial CPU State
    cpu.set_ax(0x1F4B);
    cpu.set_bx(0x5079);
    cpu.set_cx(0xFB10);
    cpu.set_dx(0xCEDC);
    cpu.set_cs(0x6049);
    cpu.set_ss(0xACD8);
    cpu.set_ds(0x2F07);
    cpu.set_es(0x0245);
    cpu.set_sp(0xC58D);
    cpu.set_bp(0x2EFB);
    cpu.set_si(0xC50A);
    cpu.set_di(0x6990);
    cpu.set_ip(0x2B8F);
    cpu.set_flags(0xFC12);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6301F, 0x36);
    machine.mem_store_byte(0x63020, 0xD3);
    machine.mem_store_byte(0x63021, 0xE4);
    machine.mem_store_byte(0x63022, 0x90);
    machine.mem_store_byte(0x63023, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0x2B92);
    EXPECT_FLAGS(0xFC47);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6301F), 0x36);
    EXPECT_EQ(memory.load8(0x63020), 0xD3);
    EXPECT_EQ(memory.load8(0x63021), 0xE4);
    EXPECT_EQ(memory.load8(0x63022), 0x90);
    EXPECT_EQ(memory.load8(0x63023), 0x90);
}

//
// shl word [ds:bx-78h], cl
//
TEST_F(MachineTest, shl_word_ds_bx_78h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x5F75);
    cpu.set_cx(0xB204);
    cpu.set_dx(0xDEDD);
    cpu.set_cs(0x0C15);
    cpu.set_ss(0x376C);
    cpu.set_ds(0x1BAD);
    cpu.set_es(0x022D);
    cpu.set_sp(0x5CCC);
    cpu.set_bp(0x31A4);
    cpu.set_si(0x1306);
    cpu.set_di(0x6653);
    cpu.set_ip(0x9B80);
    cpu.set_flags(0xFCC2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x15CD0, 0xD3);
    machine.mem_store_byte(0x15CD1, 0x67);
    machine.mem_store_byte(0x15CD2, 0x88);
    machine.mem_store_byte(0x15CD3, 0x90);
    machine.mem_store_byte(0x15CD4, 0x90);
    machine.mem_store_byte(0x15CD5, 0x90);
    machine.mem_store_byte(0x219CD, 0x7B);
    machine.mem_store_byte(0x219CE, 0x51);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9B83);
    EXPECT_FLAGS(0xFC13);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x15CD0), 0xD3);
    EXPECT_EQ(memory.load8(0x15CD1), 0x67);
    EXPECT_EQ(memory.load8(0x15CD2), 0x88);
    EXPECT_EQ(memory.load8(0x15CD3), 0x90);
    EXPECT_EQ(memory.load8(0x15CD4), 0x90);
    EXPECT_EQ(memory.load8(0x15CD5), 0x90);
    EXPECT_EQ(memory.load8(0x219CD), 0xB0);
    EXPECT_EQ(memory.load8(0x219CE), 0x17);
}

//
// shl word [ss:bx+di-6098h], cl
//
TEST_F(MachineTest, shl_word_ss_bx_di_6098h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xDFCB);
    cpu.set_bx(0xCDC4);
    cpu.set_cx(0x6902);
    cpu.set_dx(0x7A2F);
    cpu.set_cs(0xDD57);
    cpu.set_ss(0x21F6);
    cpu.set_ds(0x23AF);
    cpu.set_es(0x4E0B);
    cpu.set_sp(0x55FB);
    cpu.set_bp(0x72AE);
    cpu.set_si(0x7809);
    cpu.set_di(0xE123);
    cpu.set_ip(0x85E1);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE5B51, 0x36);
    machine.mem_store_byte(0xE5B52, 0xD3);
    machine.mem_store_byte(0xE5B53, 0xA1);
    machine.mem_store_byte(0xE5B54, 0x68);
    machine.mem_store_byte(0xE5B55, 0x9F);
    machine.mem_store_byte(0x26DAF, 0xF5);
    machine.mem_store_byte(0x26DB0, 0x86);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x85E6);
    EXPECT_FLAGS(0xF016);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE5B51), 0x36);
    EXPECT_EQ(memory.load8(0xE5B52), 0xD3);
    EXPECT_EQ(memory.load8(0xE5B53), 0xA1);
    EXPECT_EQ(memory.load8(0xE5B54), 0x68);
    EXPECT_EQ(memory.load8(0xE5B55), 0x9F);
    EXPECT_EQ(memory.load8(0x26DAF), 0xD4);
    EXPECT_EQ(memory.load8(0x26DB0), 0x1B);
}

//
// shr byte [cs:bp+di-5628h], cl
//
TEST_F(MachineTest, shr_byte_cs_bp_di_5628h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x3DC5);
    cpu.set_bx(0x7B83);
    cpu.set_cx(0x1624);
    cpu.set_dx(0xE09E);
    cpu.set_cs(0x1365);
    cpu.set_ss(0xE772);
    cpu.set_ds(0xA70E);
    cpu.set_es(0x3323);
    cpu.set_sp(0x7F68);
    cpu.set_bp(0x8B1C);
    cpu.set_si(0x2FFC);
    cpu.set_di(0x1E81);
    cpu.set_ip(0x6EE2);
    cpu.set_flags(0xF042);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1A532, 0x2E);
    machine.mem_store_byte(0x1A533, 0xD2);
    machine.mem_store_byte(0x1A534, 0xAB);
    machine.mem_store_byte(0x1A535, 0xD8);
    machine.mem_store_byte(0x1A536, 0xA9);
    machine.mem_store_byte(0x1A537, 0x90);
    machine.mem_store_byte(0x189C5, 0xE9);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6EE7);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1A532), 0x2E);
    EXPECT_EQ(memory.load8(0x1A533), 0xD2);
    EXPECT_EQ(memory.load8(0x1A534), 0xAB);
    EXPECT_EQ(memory.load8(0x1A535), 0xD8);
    EXPECT_EQ(memory.load8(0x1A536), 0xA9);
    EXPECT_EQ(memory.load8(0x1A537), 0x90);
    EXPECT_EQ(memory.load8(0x189C5), 0x00);
}

//
// shr byte [cs:si], cl
//
TEST_F(MachineTest, shr_byte_cs_si_cl)
{
    // Initial CPU State
    cpu.set_ax(0x6CB0);
    cpu.set_bx(0x6EF5);
    cpu.set_cx(0x6326);
    cpu.set_dx(0x80D5);
    cpu.set_cs(0x4BCD);
    cpu.set_ss(0x3C4E);
    cpu.set_ds(0xA247);
    cpu.set_es(0x4585);
    cpu.set_sp(0xBA0A);
    cpu.set_bp(0x8198);
    cpu.set_si(0x47B3);
    cpu.set_di(0x2B6F);
    cpu.set_ip(0x0AAA);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4C77A, 0x2E);
    machine.mem_store_byte(0x4C77B, 0xD2);
    machine.mem_store_byte(0x4C77C, 0x2C);
    machine.mem_store_byte(0x4C77D, 0x90);
    machine.mem_store_byte(0x4C77E, 0x90);
    machine.mem_store_byte(0x4C77F, 0x90);
    machine.mem_store_byte(0x50483, 0x21);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0AAD);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4C77A), 0x2E);
    EXPECT_EQ(memory.load8(0x4C77B), 0xD2);
    EXPECT_EQ(memory.load8(0x4C77C), 0x2C);
    EXPECT_EQ(memory.load8(0x4C77D), 0x90);
    EXPECT_EQ(memory.load8(0x4C77E), 0x90);
    EXPECT_EQ(memory.load8(0x4C77F), 0x90);
    EXPECT_EQ(memory.load8(0x50483), 0x00);
}

//
// shr byte [ds:7EB4h], cl
//
TEST_F(MachineTest, shr_byte_ds_7EB4h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xB32C);
    cpu.set_bx(0x756D);
    cpu.set_cx(0xDD28);
    cpu.set_dx(0x10C5);
    cpu.set_cs(0xC7F0);
    cpu.set_ss(0x91F1);
    cpu.set_ds(0xFC1A);
    cpu.set_es(0x960B);
    cpu.set_sp(0xD71B);
    cpu.set_bp(0xD4DE);
    cpu.set_si(0xF6ED);
    cpu.set_di(0x822C);
    cpu.set_ip(0x22D4);
    cpu.set_flags(0xF412);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCA1D4, 0xD2);
    machine.mem_store_byte(0xCA1D5, 0x2E);
    machine.mem_store_byte(0xCA1D6, 0xB4);
    machine.mem_store_byte(0xCA1D7, 0x7E);
    machine.mem_store_byte(0xCA1D8, 0x90);
    machine.mem_store_byte(0xCA1D9, 0x90);
    machine.mem_store_byte(0x04054, 0xD1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x22D8);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCA1D4), 0xD2);
    EXPECT_EQ(memory.load8(0xCA1D5), 0x2E);
    EXPECT_EQ(memory.load8(0xCA1D6), 0xB4);
    EXPECT_EQ(memory.load8(0xCA1D7), 0x7E);
    EXPECT_EQ(memory.load8(0xCA1D8), 0x90);
    EXPECT_EQ(memory.load8(0xCA1D9), 0x90);
    EXPECT_EQ(memory.load8(0x04054), 0x00);
}

//
// shr byte [ss:bx+si-2607h], cl
//
TEST_F(MachineTest, shr_byte_ss_bx_si_2607h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x2DCD);
    cpu.set_cx(0x3222);
    cpu.set_dx(0x5F37);
    cpu.set_cs(0xB6C1);
    cpu.set_ss(0xDBF4);
    cpu.set_ds(0x036C);
    cpu.set_es(0xF80F);
    cpu.set_sp(0xFCB4);
    cpu.set_bp(0x87B1);
    cpu.set_si(0x54CA);
    cpu.set_di(0xFE64);
    cpu.set_ip(0x1BD1);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB87E1, 0x36);
    machine.mem_store_byte(0xB87E2, 0xD2);
    machine.mem_store_byte(0xB87E3, 0xA8);
    machine.mem_store_byte(0xB87E4, 0xF9);
    machine.mem_store_byte(0xB87E5, 0xD9);
    machine.mem_store_byte(0xE1BD0, 0x96);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1BD6);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB87E1), 0x36);
    EXPECT_EQ(memory.load8(0xB87E2), 0xD2);
    EXPECT_EQ(memory.load8(0xB87E3), 0xA8);
    EXPECT_EQ(memory.load8(0xB87E4), 0xF9);
    EXPECT_EQ(memory.load8(0xB87E5), 0xD9);
    EXPECT_EQ(memory.load8(0xE1BD0), 0x00);
}

//
// shr dh, cl
//
TEST_F(MachineTest, shr_dh_cl)
{
    // Initial CPU State
    cpu.set_ax(0x96E4);
    cpu.set_bx(0x3862);
    cpu.set_cx(0x7828);
    cpu.set_dx(0xF0BD);
    cpu.set_cs(0xB5AA);
    cpu.set_ss(0x7711);
    cpu.set_ds(0x3FD2);
    cpu.set_es(0x37CA);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xEA4F);
    cpu.set_si(0x9EA4);
    cpu.set_di(0x38E2);
    cpu.set_ip(0x05DE);
    cpu.set_flags(0xF0D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB607E, 0xD2);
    machine.mem_store_byte(0xB607F, 0xEE);
    machine.mem_store_byte(0xB6080, 0x90);
    machine.mem_store_byte(0xB6081, 0x90);
    machine.mem_store_byte(0xB6082, 0x90);
    machine.mem_store_byte(0xB6083, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x00BD);
    EXPECT_EQ(cpu.get_ip(), 0x05E0);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB607E), 0xD2);
    EXPECT_EQ(memory.load8(0xB607F), 0xEE);
    EXPECT_EQ(memory.load8(0xB6080), 0x90);
    EXPECT_EQ(memory.load8(0xB6081), 0x90);
    EXPECT_EQ(memory.load8(0xB6082), 0x90);
    EXPECT_EQ(memory.load8(0xB6083), 0x90);
}

//
// shr word [cs:bx], cl
//
TEST_F(MachineTest, shr_word_cs_bx_cl)
{
    // Initial CPU State
    cpu.set_ax(0x938D);
    cpu.set_bx(0x8ED3);
    cpu.set_cx(0x2D2E);
    cpu.set_dx(0x3D10);
    cpu.set_cs(0x58DE);
    cpu.set_ss(0x64C2);
    cpu.set_ds(0x73B0);
    cpu.set_es(0x75C3);
    cpu.set_sp(0x502D);
    cpu.set_bp(0x39CC);
    cpu.set_si(0x099C);
    cpu.set_di(0x9D74);
    cpu.set_ip(0x0147);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x58F27, 0x2E);
    machine.mem_store_byte(0x58F28, 0xD3);
    machine.mem_store_byte(0x58F29, 0x2F);
    machine.mem_store_byte(0x58F2A, 0x90);
    machine.mem_store_byte(0x58F2B, 0x90);
    machine.mem_store_byte(0x61CB3, 0x8C);
    machine.mem_store_byte(0x61CB4, 0x60);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x014A);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x58F27), 0x2E);
    EXPECT_EQ(memory.load8(0x58F28), 0xD3);
    EXPECT_EQ(memory.load8(0x58F29), 0x2F);
    EXPECT_EQ(memory.load8(0x58F2A), 0x90);
    EXPECT_EQ(memory.load8(0x58F2B), 0x90);
    EXPECT_EQ(memory.load8(0x61CB3), 0x00);
    EXPECT_EQ(memory.load8(0x61CB4), 0x00);
}

//
// shr word [cs:di], cl
//
TEST_F(MachineTest, shr_word_cs_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0x3694);
    cpu.set_bx(0x0802);
    cpu.set_cx(0xA72A);
    cpu.set_dx(0xA636);
    cpu.set_cs(0x3066);
    cpu.set_ss(0xA011);
    cpu.set_ds(0x3356);
    cpu.set_es(0xADEB);
    cpu.set_sp(0x934F);
    cpu.set_bp(0x59EF);
    cpu.set_si(0x9563);
    cpu.set_di(0x4CAF);
    cpu.set_ip(0x9856);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x39EB6, 0x2E);
    machine.mem_store_byte(0x39EB7, 0xD3);
    machine.mem_store_byte(0x39EB8, 0x2D);
    machine.mem_store_byte(0x39EB9, 0x90);
    machine.mem_store_byte(0x39EBA, 0x90);
    machine.mem_store_byte(0x39EBB, 0x90);
    machine.mem_store_byte(0x3530F, 0xF8);
    machine.mem_store_byte(0x35310, 0x6B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9859);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x39EB6), 0x2E);
    EXPECT_EQ(memory.load8(0x39EB7), 0xD3);
    EXPECT_EQ(memory.load8(0x39EB8), 0x2D);
    EXPECT_EQ(memory.load8(0x39EB9), 0x90);
    EXPECT_EQ(memory.load8(0x39EBA), 0x90);
    EXPECT_EQ(memory.load8(0x39EBB), 0x90);
    EXPECT_EQ(memory.load8(0x3530F), 0x00);
    EXPECT_EQ(memory.load8(0x35310), 0x00);
}

//
// shr word [ds:bp+2Ch], cl
//
TEST_F(MachineTest, shr_word_ds_bp_2Ch_cl)
{
    // Initial CPU State
    cpu.set_ax(0xF513);
    cpu.set_bx(0xDCB1);
    cpu.set_cx(0xC62E);
    cpu.set_dx(0x182B);
    cpu.set_cs(0x443B);
    cpu.set_ss(0x1776);
    cpu.set_ds(0x86D5);
    cpu.set_es(0xFD07);
    cpu.set_sp(0x5A93);
    cpu.set_bp(0x2E1C);
    cpu.set_si(0x07E0);
    cpu.set_di(0x32D6);
    cpu.set_ip(0x0864);
    cpu.set_flags(0xF447);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x44C14, 0x3E);
    machine.mem_store_byte(0x44C15, 0xD3);
    machine.mem_store_byte(0x44C16, 0x6E);
    machine.mem_store_byte(0x44C17, 0x2C);
    machine.mem_store_byte(0x44C18, 0x90);
    machine.mem_store_byte(0x44C19, 0x90);
    machine.mem_store_byte(0x89B98, 0x07);
    machine.mem_store_byte(0x89B99, 0xE3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0868);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x44C14), 0x3E);
    EXPECT_EQ(memory.load8(0x44C15), 0xD3);
    EXPECT_EQ(memory.load8(0x44C16), 0x6E);
    EXPECT_EQ(memory.load8(0x44C17), 0x2C);
    EXPECT_EQ(memory.load8(0x44C18), 0x90);
    EXPECT_EQ(memory.load8(0x44C19), 0x90);
    EXPECT_EQ(memory.load8(0x89B98), 0x00);
    EXPECT_EQ(memory.load8(0x89B99), 0x00);
}

//
// shr word [ds:bx+di+7Fh], cl
//
TEST_F(MachineTest, shr_word_ds_bx_di_7Fh_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC470);
    cpu.set_bx(0x3528);
    cpu.set_cx(0xA92C);
    cpu.set_dx(0x9DCA);
    cpu.set_cs(0xA37F);
    cpu.set_ss(0xB6A0);
    cpu.set_ds(0x492D);
    cpu.set_es(0x25E7);
    cpu.set_sp(0xDEE9);
    cpu.set_bp(0xE223);
    cpu.set_si(0x49AD);
    cpu.set_di(0xD40A);
    cpu.set_ip(0x802C);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAB81C, 0xD3);
    machine.mem_store_byte(0xAB81D, 0x69);
    machine.mem_store_byte(0xAB81E, 0x7F);
    machine.mem_store_byte(0xAB81F, 0x90);
    machine.mem_store_byte(0xAB820, 0x90);
    machine.mem_store_byte(0xAB821, 0x90);
    machine.mem_store_byte(0x49C81, 0xF5);
    machine.mem_store_byte(0x49C82, 0xDC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x802F);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAB81C), 0xD3);
    EXPECT_EQ(memory.load8(0xAB81D), 0x69);
    EXPECT_EQ(memory.load8(0xAB81E), 0x7F);
    EXPECT_EQ(memory.load8(0xAB81F), 0x90);
    EXPECT_EQ(memory.load8(0xAB820), 0x90);
    EXPECT_EQ(memory.load8(0xAB821), 0x90);
    EXPECT_EQ(memory.load8(0x49C81), 0x00);
    EXPECT_EQ(memory.load8(0x49C82), 0x00);
}

//
// shr word [ds:bx+si+43A9h], cl
//
TEST_F(MachineTest, shr_word_ds_bx_si_43A9h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x0983);
    cpu.set_bx(0x16BB);
    cpu.set_cx(0xDF24);
    cpu.set_dx(0x408F);
    cpu.set_cs(0xB5BE);
    cpu.set_ss(0xED1A);
    cpu.set_ds(0x8FBF);
    cpu.set_es(0xBF0D);
    cpu.set_sp(0x2877);
    cpu.set_bp(0xB397);
    cpu.set_si(0x5071);
    cpu.set_di(0x0000);
    cpu.set_ip(0xF77C);
    cpu.set_flags(0xF883);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC535C, 0xD3);
    machine.mem_store_byte(0xC535D, 0xA8);
    machine.mem_store_byte(0xC535E, 0xA9);
    machine.mem_store_byte(0xC535F, 0x43);
    machine.mem_store_byte(0xC5360, 0x90);
    machine.mem_store_byte(0xC5361, 0x90);
    machine.mem_store_byte(0x9A6C5, 0x5A);
    machine.mem_store_byte(0x9A6C6, 0x8F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF780);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC535C), 0xD3);
    EXPECT_EQ(memory.load8(0xC535D), 0xA8);
    EXPECT_EQ(memory.load8(0xC535E), 0xA9);
    EXPECT_EQ(memory.load8(0xC535F), 0x43);
    EXPECT_EQ(memory.load8(0xC5360), 0x90);
    EXPECT_EQ(memory.load8(0xC5361), 0x90);
    EXPECT_EQ(memory.load8(0x9A6C5), 0x00);
    EXPECT_EQ(memory.load8(0x9A6C6), 0x00);
}

//
// shr word [ss:bp+di], cl
//
TEST_F(MachineTest, shr_word_ss_bp_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0x1986);
    cpu.set_bx(0xC5A9);
    cpu.set_cx(0x1228);
    cpu.set_dx(0x4EF1);
    cpu.set_cs(0xA2F3);
    cpu.set_ss(0x431E);
    cpu.set_ds(0x871B);
    cpu.set_es(0xA453);
    cpu.set_sp(0xD4CA);
    cpu.set_bp(0x1353);
    cpu.set_si(0x7C7A);
    cpu.set_di(0x0000);
    cpu.set_ip(0x8050);
    cpu.set_flags(0xF453);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAAF80, 0xD3);
    machine.mem_store_byte(0xAAF81, 0x2B);
    machine.mem_store_byte(0xAAF82, 0x90);
    machine.mem_store_byte(0xAAF83, 0x90);
    machine.mem_store_byte(0xAAF84, 0x90);
    machine.mem_store_byte(0xAAF85, 0x90);
    machine.mem_store_byte(0x44533, 0xC9);
    machine.mem_store_byte(0x44534, 0xE3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8052);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAAF80), 0xD3);
    EXPECT_EQ(memory.load8(0xAAF81), 0x2B);
    EXPECT_EQ(memory.load8(0xAAF82), 0x90);
    EXPECT_EQ(memory.load8(0xAAF83), 0x90);
    EXPECT_EQ(memory.load8(0xAAF84), 0x90);
    EXPECT_EQ(memory.load8(0xAAF85), 0x90);
    EXPECT_EQ(memory.load8(0x44533), 0x00);
    EXPECT_EQ(memory.load8(0x44534), 0x00);
}

//
// shr word [ss:di], cl
//
TEST_F(MachineTest, shr_word_ss_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0x0DAA);
    cpu.set_bx(0xB3D0);
    cpu.set_cx(0x6630);
    cpu.set_dx(0x0A25);
    cpu.set_cs(0xBA36);
    cpu.set_ss(0x0000);
    cpu.set_ds(0x9DD6);
    cpu.set_es(0x70B0);
    cpu.set_sp(0xE522);
    cpu.set_bp(0x2DCC);
    cpu.set_si(0xC826);
    cpu.set_di(0x28CD);
    cpu.set_ip(0x8B50);
    cpu.set_flags(0xF093);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC2EB0, 0x36);
    machine.mem_store_byte(0xC2EB1, 0xD3);
    machine.mem_store_byte(0xC2EB2, 0x2D);
    machine.mem_store_byte(0xC2EB3, 0x90);
    machine.mem_store_byte(0xC2EB4, 0x90);
    machine.mem_store_byte(0xC2EB5, 0x90);
    machine.mem_store_byte(0x028CD, 0x44);
    machine.mem_store_byte(0x028CE, 0x97);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8B53);
    EXPECT_FLAGS(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC2EB0), 0x36);
    EXPECT_EQ(memory.load8(0xC2EB1), 0xD3);
    EXPECT_EQ(memory.load8(0xC2EB2), 0x2D);
    EXPECT_EQ(memory.load8(0xC2EB3), 0x90);
    EXPECT_EQ(memory.load8(0xC2EB4), 0x90);
    EXPECT_EQ(memory.load8(0xC2EB5), 0x90);
    EXPECT_EQ(memory.load8(0x028CD), 0x00);
    EXPECT_EQ(memory.load8(0x028CE), 0x00);
}
