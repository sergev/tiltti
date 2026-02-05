#include "fixture.h"

//
// rcl bh, cl
//
TEST_F(MachineTest, rcl_bh_cl)
{
    // Initial CPU State
    cpu.set_ax(0x405C);
    cpu.set_bx(0x5C40);
    cpu.set_cx(0xB80E);
    cpu.set_dx(0xC3E0);
    cpu.set_cs(0x93EF);
    cpu.set_ss(0x2D2C);
    cpu.set_ds(0x0B3B);
    cpu.set_es(0x30BD);
    cpu.set_sp(0x8CC0);
    cpu.set_bp(0xC794);
    cpu.set_si(0x6FD1);
    cpu.set_di(0xC264);
    cpu.set_ip(0xA2F5);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9E1E5, 0xD2);
    machine.mem_store_byte(0x9E1E6, 0xD7);
    machine.mem_store_byte(0x9E1E7, 0x90);
    machine.mem_store_byte(0x9E1E8, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x8540);
    EXPECT_EQ(cpu.get_ip(), 0xA2F7);
    EXPECT_EQ(cpu.get_flags(), 0xF013);

    // Final RAM entries
}

//
// rcl cl
//
TEST_F(MachineTest, rcl_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC461);
    cpu.set_bx(0xE772);
    cpu.set_cx(0x6606);
    cpu.set_dx(0x491D);
    cpu.set_cs(0xD91B);
    cpu.set_ss(0x20C8);
    cpu.set_ds(0x8EB4);
    cpu.set_es(0x88C5);
    cpu.set_sp(0x8483);
    cpu.set_bp(0xD2C3);
    cpu.set_si(0x65E6);
    cpu.set_di(0xE262);
    cpu.set_ip(0x51E5);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDE395, 0x2E);
    machine.mem_store_byte(0xDE396, 0xD0);
    machine.mem_store_byte(0xDE397, 0xD1);
    machine.mem_store_byte(0xDE398, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x660D);
    EXPECT_EQ(cpu.get_ip(), 0x51E8);
    EXPECT_EQ(cpu.get_flags(), 0xF096);

    // Final RAM entries
}

//
// rcl si, cl
//
TEST_F(MachineTest, rcl_si_cl)
{
    // Initial CPU State
    cpu.set_ax(0x3A72);
    cpu.set_bx(0xA094);
    cpu.set_cx(0x9402);
    cpu.set_dx(0x157D);
    cpu.set_cs(0x417C);
    cpu.set_ss(0x454F);
    cpu.set_ds(0x9397);
    cpu.set_es(0xAC0D);
    cpu.set_sp(0xCF73);
    cpu.set_bp(0xF4C5);
    cpu.set_si(0xC936);
    cpu.set_di(0xAAAF);
    cpu.set_ip(0x17AF);
    cpu.set_flags(0xFCC2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x42F6F, 0x36);
    machine.mem_store_byte(0x42F70, 0xD3);
    machine.mem_store_byte(0x42F71, 0xD6);
    machine.mem_store_byte(0x42F72, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x24D9);
    EXPECT_EQ(cpu.get_ip(), 0x17B2);
    EXPECT_EQ(cpu.get_flags(), 0xFCC3);

    // Final RAM entries
}

//
// rcl word [ds:si]
//
TEST_F(MachineTest, rcl_word_ds_si)
{
    // Initial CPU State
    cpu.set_ax(0x3FB1);
    cpu.set_bx(0x1CAF);
    cpu.set_cx(0x6E06);
    cpu.set_dx(0x6FDA);
    cpu.set_cs(0xC6BF);
    cpu.set_ss(0x459F);
    cpu.set_ds(0xDBF1);
    cpu.set_es(0xA835);
    cpu.set_sp(0x35BD);
    cpu.set_bp(0x04FD);
    cpu.set_si(0x637A);
    cpu.set_di(0x79B1);
    cpu.set_ip(0x189F);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC848F, 0xD1);
    machine.mem_store_byte(0xC8490, 0x14);
    machine.mem_store_byte(0xC8491, 0x90);
    machine.mem_store_byte(0xC8492, 0x90);
    machine.mem_store_byte(0xE228A, 0x51);
    machine.mem_store_byte(0xE228B, 0xAC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x18A1);
    EXPECT_EQ(cpu.get_flags(), 0xF813);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xE228A), 0xA2);
    EXPECT_EQ(memory.load8(0xE228B), 0x58);
}

//
// rcr ah, cl
//
TEST_F(MachineTest, rcr_ah_cl)
{
    // Initial CPU State
    cpu.set_ax(0x9355);
    cpu.set_bx(0xF329);
    cpu.set_cx(0x7412);
    cpu.set_dx(0x4520);
    cpu.set_cs(0xB52A);
    cpu.set_ss(0x8467);
    cpu.set_ds(0xC8DD);
    cpu.set_es(0x2BCE);
    cpu.set_sp(0xBD9A);
    cpu.set_bp(0xD0D9);
    cpu.set_si(0x50A0);
    cpu.set_di(0xEA76);
    cpu.set_ip(0xDAC5);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC2D65, 0x26);
    machine.mem_store_byte(0xC2D66, 0xD2);
    machine.mem_store_byte(0xC2D67, 0xDC);
    machine.mem_store_byte(0xC2D68, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDAC8);
    EXPECT_EQ(cpu.get_flags(), 0xFC82);

    // Final RAM entries
}

//
// rcr byte [ss:bp-5603h]
//
TEST_F(MachineTest, rcr_byte_ss_bp_5603h)
{
    // Initial CPU State
    cpu.set_ax(0x8F4C);
    cpu.set_bx(0xEFD4);
    cpu.set_cx(0x7026);
    cpu.set_dx(0xA61D);
    cpu.set_cs(0x3D4B);
    cpu.set_ss(0xFB53);
    cpu.set_ds(0x07F4);
    cpu.set_es(0x1974);
    cpu.set_sp(0xAB37);
    cpu.set_bp(0x8877);
    cpu.set_si(0xA5AD);
    cpu.set_di(0xE323);
    cpu.set_ip(0x9FB7);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x47467, 0x36);
    machine.mem_store_byte(0x47468, 0xD0);
    machine.mem_store_byte(0x47469, 0x9E);
    machine.mem_store_byte(0x4746A, 0xFD);
    machine.mem_store_byte(0x4746B, 0xA9);
    machine.mem_store_byte(0xFE7A4, 0xD1);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9FBC);
    EXPECT_EQ(cpu.get_flags(), 0xFC83);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFE7A4), 0x68);
}

//
// rcr word [cs:bp+7E01h]
//
TEST_F(MachineTest, rcr_word_cs_bp_7E01h)
{
    // Initial CPU State
    cpu.set_ax(0x5971);
    cpu.set_bx(0x7EE0);
    cpu.set_cx(0x7034);
    cpu.set_dx(0xCAE1);
    cpu.set_cs(0x7B48);
    cpu.set_ss(0xF41D);
    cpu.set_ds(0x3AFD);
    cpu.set_es(0xA364);
    cpu.set_sp(0x60E7);
    cpu.set_bp(0x1903);
    cpu.set_si(0x16CE);
    cpu.set_di(0x5AB6);
    cpu.set_ip(0x32F3);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7E773, 0x2E);
    machine.mem_store_byte(0x7E774, 0xD1);
    machine.mem_store_byte(0x7E775, 0x9E);
    machine.mem_store_byte(0x7E776, 0x01);
    machine.mem_store_byte(0x7E777, 0x7E);
    machine.mem_store_byte(0x84B84, 0xAA);
    machine.mem_store_byte(0x84B85, 0x37);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x32F8);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x84B84), 0xD5);
    EXPECT_EQ(memory.load8(0x84B85), 0x1B);
}

//
// rcr word [ss:si-34h], cl
//
TEST_F(MachineTest, rcr_word_ss_si_34h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x51EC);
    cpu.set_bx(0x6BCD);
    cpu.set_cx(0x2D30);
    cpu.set_dx(0xB3B7);
    cpu.set_cs(0xA1BD);
    cpu.set_ss(0xEEB1);
    cpu.set_ds(0x6F62);
    cpu.set_es(0xEC6C);
    cpu.set_sp(0x2ABE);
    cpu.set_bp(0x1A33);
    cpu.set_si(0xE357);
    cpu.set_di(0x7783);
    cpu.set_ip(0xCD78);
    cpu.set_flags(0xF816);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAE948, 0x36);
    machine.mem_store_byte(0xAE949, 0xD3);
    machine.mem_store_byte(0xAE94A, 0x5C);
    machine.mem_store_byte(0xAE94B, 0xCC);
    machine.mem_store_byte(0xFCE33, 0x31);
    machine.mem_store_byte(0xFCE34, 0xA5);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCD7C);
    EXPECT_EQ(cpu.get_flags(), 0xF017);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFCE33), 0x8A);
    EXPECT_EQ(memory.load8(0xFCE34), 0x29);
}

//
// rol bp, cl
//
TEST_F(MachineTest, rol_bp_cl)
{
    // Initial CPU State
    cpu.set_ax(0xB03F);
    cpu.set_bx(0x6E7F);
    cpu.set_cx(0x3E02);
    cpu.set_dx(0x55E7);
    cpu.set_cs(0xEE42);
    cpu.set_ss(0x81C3);
    cpu.set_ds(0xEE4B);
    cpu.set_es(0x2769);
    cpu.set_sp(0x96D4);
    cpu.set_bp(0x8324);
    cpu.set_si(0x283A);
    cpu.set_di(0x2654);
    cpu.set_ip(0x6D29);
    cpu.set_flags(0xFC46);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF5149, 0xD3);
    machine.mem_store_byte(0xF514A, 0xC5);
    machine.mem_store_byte(0xF514B, 0x90);
    machine.mem_store_byte(0xF514C, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0x0C92);
    EXPECT_EQ(cpu.get_ip(), 0x6D2B);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
}

//
// rol byte [ds:2321h], cl
//
TEST_F(MachineTest, rol_byte_ds_2321h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x2B0A);
    cpu.set_bx(0x7119);
    cpu.set_cx(0x7E2E);
    cpu.set_dx(0x29E6);
    cpu.set_cs(0x1642);
    cpu.set_ss(0xA843);
    cpu.set_ds(0xC061);
    cpu.set_es(0x7932);
    cpu.set_sp(0x8E4F);
    cpu.set_bp(0x8855);
    cpu.set_si(0x180A);
    cpu.set_di(0x508C);
    cpu.set_ip(0xCCA2);
    cpu.set_flags(0xFC52);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x230C2, 0xD2);
    machine.mem_store_byte(0x230C3, 0x06);
    machine.mem_store_byte(0x230C4, 0x21);
    machine.mem_store_byte(0x230C5, 0x23);
    machine.mem_store_byte(0xC2931, 0xF6);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCCA6);
    EXPECT_EQ(cpu.get_flags(), 0xF453);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC2931), 0xBD);
}

//
// rol byte [ds:bx+si-51BAh]
//
TEST_F(MachineTest, rol_byte_ds_bx_si_51BAh)
{
    // Initial CPU State
    cpu.set_ax(0x468E);
    cpu.set_bx(0x905C);
    cpu.set_cx(0xBB1A);
    cpu.set_dx(0x4E14);
    cpu.set_cs(0x620B);
    cpu.set_ss(0xE619);
    cpu.set_ds(0xEC07);
    cpu.set_es(0x1DB7);
    cpu.set_sp(0x05F6);
    cpu.set_bp(0x27E7);
    cpu.set_si(0x3EDA);
    cpu.set_di(0x7708);
    cpu.set_ip(0x0CE6);
    cpu.set_flags(0xFC02);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x62D96, 0xD0);
    machine.mem_store_byte(0x62D97, 0x80);
    machine.mem_store_byte(0x62D98, 0x46);
    machine.mem_store_byte(0x62D99, 0xAE);
    machine.mem_store_byte(0xF3DEC, 0x45);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0CEA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF3DEC), 0x8A);
}

//
// rol word [es:bx+di+5C39h]
//
TEST_F(MachineTest, rol_word_es_bx_di_5C39h)
{
    // Initial CPU State
    cpu.set_ax(0x7D3A);
    cpu.set_bx(0xD181);
    cpu.set_cx(0x5104);
    cpu.set_dx(0xD5EA);
    cpu.set_cs(0xD644);
    cpu.set_ss(0x7446);
    cpu.set_ds(0x3706);
    cpu.set_es(0xCE83);
    cpu.set_sp(0xB2F0);
    cpu.set_bp(0x887C);
    cpu.set_si(0x8CE8);
    cpu.set_di(0x80C2);
    cpu.set_ip(0x1A02);
    cpu.set_flags(0xF056);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD7E42, 0x26);
    machine.mem_store_byte(0xD7E43, 0xD1);
    machine.mem_store_byte(0xD7E44, 0x81);
    machine.mem_store_byte(0xD7E45, 0x39);
    machine.mem_store_byte(0xD7E46, 0x5C);
    machine.mem_store_byte(0xD96AC, 0xB6);
    machine.mem_store_byte(0xD96AD, 0x7D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1A07);
    EXPECT_EQ(cpu.get_flags(), 0xF856);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD96AC), 0x6C);
    EXPECT_EQ(memory.load8(0xD96AD), 0xFB);
}

//
// ror bh, cl
//
TEST_F(MachineTest, ror_bh_cl)
{
    // Initial CPU State
    cpu.set_ax(0x642F);
    cpu.set_bx(0xF0D2);
    cpu.set_cx(0x6A2A);
    cpu.set_dx(0xFCD9);
    cpu.set_cs(0x4F69);
    cpu.set_ss(0xC57C);
    cpu.set_ds(0x1640);
    cpu.set_es(0x6FDA);
    cpu.set_sp(0xF565);
    cpu.set_bp(0x8666);
    cpu.set_si(0x9DD8);
    cpu.set_di(0xE5E3);
    cpu.set_ip(0xB0CD);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5A75D, 0x3E);
    machine.mem_store_byte(0x5A75E, 0xD2);
    machine.mem_store_byte(0x5A75F, 0xCF);
    machine.mem_store_byte(0x5A760, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x3CD2);
    EXPECT_EQ(cpu.get_ip(), 0xB0D0);
    EXPECT_EQ(cpu.get_flags(), 0xF012);

    // Final RAM entries
}

//
// ror byte [ss:bp+si]
//
TEST_F(MachineTest, ror_byte_ss_bp_si)
{
    // Initial CPU State
    cpu.set_ax(0x4FD2);
    cpu.set_bx(0x8E72);
    cpu.set_cx(0xDA30);
    cpu.set_dx(0x2A21);
    cpu.set_cs(0x8808);
    cpu.set_ss(0xABD7);
    cpu.set_ds(0xF594);
    cpu.set_es(0xCFA6);
    cpu.set_sp(0xC37F);
    cpu.set_bp(0xBF0E);
    cpu.set_si(0xEBD4);
    cpu.set_di(0x5022);
    cpu.set_ip(0x6ACB);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8EB4B, 0x36);
    machine.mem_store_byte(0x8EB4C, 0xD0);
    machine.mem_store_byte(0x8EB4D, 0x0A);
    machine.mem_store_byte(0x8EB4E, 0x90);
    machine.mem_store_byte(0xB6852, 0xAF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6ACE);
    EXPECT_EQ(cpu.get_flags(), 0xF413);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB6852), 0xD7);
}

//
// ror word [ds:bx+si-2Bh]
//
TEST_F(MachineTest, ror_word_ds_bx_si_2Bh)
{
    // Initial CPU State
    cpu.set_ax(0xB572);
    cpu.set_bx(0x71F5);
    cpu.set_cx(0xEB2C);
    cpu.set_dx(0x9AE5);
    cpu.set_cs(0x9360);
    cpu.set_ss(0x1CDB);
    cpu.set_ds(0xAC3E);
    cpu.set_es(0xB3EA);
    cpu.set_sp(0x2E9C);
    cpu.set_bp(0xD099);
    cpu.set_si(0x92E1);
    cpu.set_di(0xEBBD);
    cpu.set_ip(0x63EB);
    cpu.set_flags(0xF857);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x999EB, 0xD1);
    machine.mem_store_byte(0x999EC, 0x48);
    machine.mem_store_byte(0x999ED, 0xD5);
    machine.mem_store_byte(0x999EE, 0x90);
    machine.mem_store_byte(0xAC88B, 0xF4);
    machine.mem_store_byte(0xAC88C, 0x84);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x63EE);
    EXPECT_EQ(cpu.get_flags(), 0xF856);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAC88B), 0x7A);
    EXPECT_EQ(memory.load8(0xAC88C), 0x42);
}

//
// ror word [ss:bx], cl
//
TEST_F(MachineTest, ror_word_ss_bx_cl)
{
    // Initial CPU State
    cpu.set_ax(0x16F6);
    cpu.set_bx(0xCED2);
    cpu.set_cx(0x8326);
    cpu.set_dx(0x45E6);
    cpu.set_cs(0xBE32);
    cpu.set_ss(0xF42C);
    cpu.set_ds(0x718C);
    cpu.set_es(0x1463);
    cpu.set_sp(0xE0CC);
    cpu.set_bp(0x331B);
    cpu.set_si(0x496A);
    cpu.set_di(0x3ECE);
    cpu.set_ip(0xB0B7);
    cpu.set_flags(0xF8D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC93D7, 0x36);
    machine.mem_store_byte(0xC93D8, 0xD3);
    machine.mem_store_byte(0xC93D9, 0x0F);
    machine.mem_store_byte(0xC93DA, 0x90);
    machine.mem_store_byte(0x01192, 0x59);
    machine.mem_store_byte(0x01193, 0xFD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB0BA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x01192), 0xF5);
    EXPECT_EQ(memory.load8(0x01193), 0x67);
}

//
// sar bx
//
TEST_F(MachineTest, sar_bx)
{
    // Initial CPU State
    cpu.set_ax(0x2431);
    cpu.set_bx(0xF9DE);
    cpu.set_cx(0x5A10);
    cpu.set_dx(0xB5EC);
    cpu.set_cs(0x415D);
    cpu.set_ss(0x2B3D);
    cpu.set_ds(0x3269);
    cpu.set_es(0x46A9);
    cpu.set_sp(0x6D38);
    cpu.set_bp(0x0362);
    cpu.set_si(0xED9D);
    cpu.set_di(0xAC5E);
    cpu.set_ip(0xC2C2);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4D892, 0xD1);
    machine.mem_store_byte(0x4D893, 0xFB);
    machine.mem_store_byte(0x4D894, 0x90);
    machine.mem_store_byte(0x4D895, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xFCEF);
    EXPECT_EQ(cpu.get_ip(), 0xC2C4);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
}

//
// sar byte [cs:si]
//
TEST_F(MachineTest, sar_byte_cs_si)
{
    // Initial CPU State
    cpu.set_ax(0xF71E);
    cpu.set_bx(0x8297);
    cpu.set_cx(0xC822);
    cpu.set_dx(0xEFB2);
    cpu.set_cs(0xF112);
    cpu.set_ss(0x7FDD);
    cpu.set_ds(0x3B3D);
    cpu.set_es(0xA853);
    cpu.set_sp(0x5C12);
    cpu.set_bp(0x634C);
    cpu.set_si(0xA630);
    cpu.set_di(0x377B);
    cpu.set_ip(0xD42C);
    cpu.set_flags(0xF497);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFE54C, 0x2E);
    machine.mem_store_byte(0xFE54D, 0xD0);
    machine.mem_store_byte(0xFE54E, 0x3C);
    machine.mem_store_byte(0xFE54F, 0x90);
    machine.mem_store_byte(0xFB750, 0x67);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xD42F);
    EXPECT_EQ(cpu.get_flags(), 0xF407);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFB750), 0x33);
}

//
// sar byte [es:si], cl
//
TEST_F(MachineTest, sar_byte_es_si_cl)
{
    // Initial CPU State
    cpu.set_ax(0x898B);
    cpu.set_bx(0x9F6A);
    cpu.set_cx(0xF41C);
    cpu.set_dx(0xAF44);
    cpu.set_cs(0x4826);
    cpu.set_ss(0x108B);
    cpu.set_ds(0x4CF1);
    cpu.set_es(0x52F9);
    cpu.set_sp(0x1510);
    cpu.set_bp(0x8837);
    cpu.set_si(0x5766);
    cpu.set_di(0xADFF);
    cpu.set_ip(0xA953);
    cpu.set_flags(0xFC53);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x52BB3, 0x26);
    machine.mem_store_byte(0x52BB4, 0xD2);
    machine.mem_store_byte(0x52BB5, 0x3C);
    machine.mem_store_byte(0x52BB6, 0x90);
    machine.mem_store_byte(0x586F6, 0xB0);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA956);
    EXPECT_EQ(cpu.get_flags(), 0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x586F6), 0xFF);
}

//
// sar word [ss:bp+2106h], cl
//
TEST_F(MachineTest, sar_word_ss_bp_2106h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x9393);
    cpu.set_bx(0xA609);
    cpu.set_cx(0xA302);
    cpu.set_dx(0xBC95);
    cpu.set_cs(0xA8F5);
    cpu.set_ss(0x07A0);
    cpu.set_ds(0xD427);
    cpu.set_es(0xDFEB);
    cpu.set_sp(0x74AB);
    cpu.set_bp(0xB8B6);
    cpu.set_si(0x2669);
    cpu.set_di(0xC6C7);
    cpu.set_ip(0xDF44);
    cpu.set_flags(0xF807);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB6E94, 0x36);
    machine.mem_store_byte(0xB6E95, 0xD3);
    machine.mem_store_byte(0xB6E96, 0xBE);
    machine.mem_store_byte(0xB6E97, 0x06);
    machine.mem_store_byte(0xB6E98, 0x21);
    machine.mem_store_byte(0x153BC, 0xB7);
    machine.mem_store_byte(0x153BD, 0xCD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDF49);
    EXPECT_EQ(cpu.get_flags(), 0xF083);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x153BC), 0x6D);
    EXPECT_EQ(memory.load8(0x153BD), 0xF3);
}

//
// setmo byte [ss:bp-3D75h]
//
TEST_F(MachineTest, setmo_byte_ss_bp_3D75h)
{
    // Initial CPU State
    cpu.set_ax(0x99D2);
    cpu.set_bx(0xBFDA);
    cpu.set_cx(0x4602);
    cpu.set_dx(0xD2C3);
    cpu.set_cs(0x9072);
    cpu.set_ss(0xA993);
    cpu.set_ds(0x5E79);
    cpu.set_es(0x2B8A);
    cpu.set_sp(0x7277);
    cpu.set_bp(0xA888);
    cpu.set_si(0xBA37);
    cpu.set_di(0xA798);
    cpu.set_ip(0x822C);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9894C, 0xD0);
    machine.mem_store_byte(0x9894D, 0xB6);
    machine.mem_store_byte(0x9894E, 0x8B);
    machine.mem_store_byte(0x9894F, 0xC2);
    machine.mem_store_byte(0xB0443, 0xAA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8230);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB0443), 0xFF);
}

//
// setmo dx
//
TEST_F(MachineTest, setmo_dx)
{
    // Initial CPU State
    cpu.set_ax(0x117D);
    cpu.set_bx(0x6EB1);
    cpu.set_cx(0xCD28);
    cpu.set_dx(0x6B8E);
    cpu.set_cs(0x076C);
    cpu.set_ss(0xB0E5);
    cpu.set_ds(0x69E7);
    cpu.set_es(0xCA5A);
    cpu.set_sp(0xCCDC);
    cpu.set_bp(0xF140);
    cpu.set_si(0x9264);
    cpu.set_di(0xBCDB);
    cpu.set_ip(0x5168);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0C828, 0x26);
    machine.mem_store_byte(0x0C829, 0xD1);
    machine.mem_store_byte(0x0C82A, 0xF2);
    machine.mem_store_byte(0x0C82B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0x516B);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
}

//
// setmoc byte [ss:bp+di+12h], cl
//
TEST_F(MachineTest, setmoc_byte_ss_bp_di_12h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x8C0A);
    cpu.set_bx(0x523D);
    cpu.set_cx(0x773E);
    cpu.set_dx(0xA4A7);
    cpu.set_cs(0x87DE);
    cpu.set_ss(0x07C0);
    cpu.set_ds(0x3281);
    cpu.set_es(0x320F);
    cpu.set_sp(0x8EC5);
    cpu.set_bp(0x3134);
    cpu.set_si(0x031F);
    cpu.set_di(0x4725);
    cpu.set_ip(0xAEB8);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x92C98, 0xD2);
    machine.mem_store_byte(0x92C99, 0x73);
    machine.mem_store_byte(0x92C9A, 0x12);
    machine.mem_store_byte(0x92C9B, 0x90);
    machine.mem_store_byte(0x0F46B, 0xE4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAEBB);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0F46B), 0xFF);
}

//
// setmoc cx, cl
//
TEST_F(MachineTest, setmoc_cx_cl)
{
    // Initial CPU State
    cpu.set_ax(0x6887);
    cpu.set_bx(0xDBAE);
    cpu.set_cx(0x3D28);
    cpu.set_dx(0xF7B5);
    cpu.set_cs(0xC828);
    cpu.set_ss(0x4616);
    cpu.set_ds(0x4174);
    cpu.set_es(0x3756);
    cpu.set_sp(0x900C);
    cpu.set_bp(0xA1F0);
    cpu.set_si(0x5D1F);
    cpu.set_di(0x22A4);
    cpu.set_ip(0xF1E0);
    cpu.set_flags(0xF843);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD7460, 0xD3);
    machine.mem_store_byte(0xD7461, 0xF1);
    machine.mem_store_byte(0xD7462, 0x90);
    machine.mem_store_byte(0xD7463, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0xF1E2);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// shl bh
//
TEST_F(MachineTest, shl_bh)
{
    // Initial CPU State
    cpu.set_ax(0xD13D);
    cpu.set_bx(0x92DF);
    cpu.set_cx(0x1112);
    cpu.set_dx(0xD8A1);
    cpu.set_cs(0x13C7);
    cpu.set_ss(0xDF96);
    cpu.set_ds(0x3770);
    cpu.set_es(0x90AC);
    cpu.set_sp(0x502F);
    cpu.set_bp(0xC3E9);
    cpu.set_si(0x504E);
    cpu.set_di(0xDE4D);
    cpu.set_ip(0xB1E3);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1EE53, 0x2E);
    machine.mem_store_byte(0x1EE54, 0xD0);
    machine.mem_store_byte(0x1EE55, 0xE7);
    machine.mem_store_byte(0x1EE56, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x24DF);
    EXPECT_EQ(cpu.get_ip(), 0xB1E6);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
}

//
// shl byte [ds:si+41h], cl
//
TEST_F(MachineTest, shl_byte_ds_si_41h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x69D4);
    cpu.set_bx(0xE468);
    cpu.set_cx(0xE52A);
    cpu.set_dx(0x2DED);
    cpu.set_cs(0xE73B);
    cpu.set_ss(0x401C);
    cpu.set_ds(0x0CC8);
    cpu.set_es(0x05BE);
    cpu.set_sp(0x6F03);
    cpu.set_bp(0xE67C);
    cpu.set_si(0xFBF8);
    cpu.set_di(0xAAC5);
    cpu.set_ip(0x6BC3);
    cpu.set_flags(0xFCD3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEDF73, 0xD2);
    machine.mem_store_byte(0xEDF74, 0x64);
    machine.mem_store_byte(0xEDF75, 0x41);
    machine.mem_store_byte(0xEDF76, 0x90);
    machine.mem_store_byte(0x1C8B9, 0x50);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6BC6);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1C8B9), 0x00);
}

//
// shl word [es:bp+si-31h], cl
//
TEST_F(MachineTest, shl_word_es_bp_si_31h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x1431);
    cpu.set_bx(0xCBA3);
    cpu.set_cx(0xD23A);
    cpu.set_dx(0x2BD4);
    cpu.set_cs(0xE05E);
    cpu.set_ss(0x6557);
    cpu.set_ds(0x0C39);
    cpu.set_es(0x8245);
    cpu.set_sp(0x7216);
    cpu.set_bp(0x7162);
    cpu.set_si(0xD155);
    cpu.set_di(0x9D8E);
    cpu.set_ip(0x9976);
    cpu.set_flags(0xF447);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE9F56, 0x26);
    machine.mem_store_byte(0xE9F57, 0xD3);
    machine.mem_store_byte(0xE9F58, 0x62);
    machine.mem_store_byte(0xE9F59, 0xCF);
    machine.mem_store_byte(0x866D6, 0x34);
    machine.mem_store_byte(0x866D7, 0x24);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x997A);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x866D6), 0x00);
    EXPECT_EQ(memory.load8(0x866D7), 0x00);
}

//
// shl word [ss:bp+di]
//
TEST_F(MachineTest, shl_word_ss_bp_di)
{
    // Initial CPU State
    cpu.set_ax(0x2616);
    cpu.set_bx(0x6DF1);
    cpu.set_cx(0x1A10);
    cpu.set_dx(0xC286);
    cpu.set_cs(0xE00A);
    cpu.set_ss(0x4F76);
    cpu.set_ds(0x018E);
    cpu.set_es(0xF9F1);
    cpu.set_sp(0x3B58);
    cpu.set_bp(0x9913);
    cpu.set_si(0x7379);
    cpu.set_di(0x828B);
    cpu.set_ip(0x1AEB);
    cpu.set_flags(0xF013);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE1B8B, 0xD1);
    machine.mem_store_byte(0xE1B8C, 0x23);
    machine.mem_store_byte(0xE1B8D, 0x90);
    machine.mem_store_byte(0xE1B8E, 0x90);
    machine.mem_store_byte(0x512FE, 0x26);
    machine.mem_store_byte(0x512FF, 0x31);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1AED);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x512FE), 0x4C);
    EXPECT_EQ(memory.load8(0x512FF), 0x62);
}

//
// shr byte [es:di], cl
//
TEST_F(MachineTest, shr_byte_es_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0x76B9);
    cpu.set_bx(0x097F);
    cpu.set_cx(0x4C32);
    cpu.set_dx(0x1FDC);
    cpu.set_cs(0x06BF);
    cpu.set_ss(0x982C);
    cpu.set_ds(0xA551);
    cpu.set_es(0x48DF);
    cpu.set_sp(0xE3CE);
    cpu.set_bp(0xE69D);
    cpu.set_si(0xC799);
    cpu.set_di(0xD98A);
    cpu.set_ip(0x850B);
    cpu.set_flags(0xF096);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0F0FB, 0x26);
    machine.mem_store_byte(0x0F0FC, 0xD2);
    machine.mem_store_byte(0x0F0FD, 0x2D);
    machine.mem_store_byte(0x0F0FE, 0x90);
    machine.mem_store_byte(0x5677A, 0xCE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x850E);
    EXPECT_EQ(cpu.get_flags(), 0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5677A), 0x00);
}

//
// shr byte [ss:di-4056h]
//
TEST_F(MachineTest, shr_byte_ss_di_4056h)
{
    // Initial CPU State
    cpu.set_ax(0x9336);
    cpu.set_bx(0xDBD6);
    cpu.set_cx(0xB73E);
    cpu.set_dx(0x1EA0);
    cpu.set_cs(0x6B6D);
    cpu.set_ss(0x970F);
    cpu.set_ds(0x06FF);
    cpu.set_es(0x094C);
    cpu.set_sp(0x19D4);
    cpu.set_bp(0x49B0);
    cpu.set_si(0xBF2B);
    cpu.set_di(0xB12B);
    cpu.set_ip(0x486E);
    cpu.set_flags(0xF846);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6FF3E, 0x36);
    machine.mem_store_byte(0x6FF3F, 0xD0);
    machine.mem_store_byte(0x6FF40, 0xAD);
    machine.mem_store_byte(0x6FF41, 0xAA);
    machine.mem_store_byte(0x6FF42, 0xBF);
    machine.mem_store_byte(0x9E1C5, 0x87);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4873);
    EXPECT_EQ(cpu.get_flags(), 0xF803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9E1C5), 0x43);
}

//
// shr word [ds:bx+di-630h]
//
TEST_F(MachineTest, shr_word_ds_bx_di_630h)
{
    // Initial CPU State
    cpu.set_ax(0x94CA);
    cpu.set_bx(0x9FDE);
    cpu.set_cx(0xEF3C);
    cpu.set_dx(0xC27C);
    cpu.set_cs(0xA76F);
    cpu.set_ss(0x1C4B);
    cpu.set_ds(0x9CA8);
    cpu.set_es(0xE3AF);
    cpu.set_sp(0x0F8C);
    cpu.set_bp(0xDC93);
    cpu.set_si(0x2D62);
    cpu.set_di(0xB8DF);
    cpu.set_ip(0x44FA);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xABBEA, 0xD1);
    machine.mem_store_byte(0xABBEB, 0xA9);
    machine.mem_store_byte(0xABBEC, 0xD0);
    machine.mem_store_byte(0xABBED, 0xF9);
    machine.mem_store_byte(0xA1D0D, 0xD9);
    machine.mem_store_byte(0xA1D0E, 0xC2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x44FE);
    EXPECT_EQ(cpu.get_flags(), 0xFC07);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA1D0D), 0x6C);
    EXPECT_EQ(memory.load8(0xA1D0E), 0x61);
}

//
// shr word [ss:di], cl
//
TEST_F(MachineTest, shr_word_ss_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC85C);
    cpu.set_bx(0x4D95);
    cpu.set_cx(0x9A0C);
    cpu.set_dx(0x2217);
    cpu.set_cs(0x0F45);
    cpu.set_ss(0xB7D2);
    cpu.set_ds(0x4147);
    cpu.set_es(0xC5F1);
    cpu.set_sp(0x8D48);
    cpu.set_bp(0xDFA8);
    cpu.set_si(0x77BA);
    cpu.set_di(0xAA07);
    cpu.set_ip(0x1C96);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x110E6, 0x36);
    machine.mem_store_byte(0x110E7, 0xD3);
    machine.mem_store_byte(0x110E8, 0x2D);
    machine.mem_store_byte(0x110E9, 0x90);
    machine.mem_store_byte(0xC2727, 0xB5);
    machine.mem_store_byte(0xC2728, 0x77);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1C99);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC2727), 0x07);
    EXPECT_EQ(memory.load8(0xC2728), 0x00);
}
