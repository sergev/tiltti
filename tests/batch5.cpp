#include "fixture.h"

//
// aaa
//
TEST_F(MachineTest, aaa_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x101A);
    cpu.set_bx(0xEFCD);
    cpu.set_cx(0x0DF8);
    cpu.set_dx(0x6BB9);
    cpu.set_cs(0x83BB);
    cpu.set_ss(0x2759);
    cpu.set_ds(0xDC48);
    cpu.set_es(0x26B5);
    cpu.set_sp(0xC059);
    cpu.set_bp(0x6D95);
    cpu.set_si(0x4149);
    cpu.set_di(0xE276);
    cpu.set_ip(0x31AB);
    cpu.set_flags(0xF006);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x86D5B, 0x37);
    machine.mem_store_byte(0x86D5C, 0x90);
    machine.mem_store_byte(0x86D5D, 0x90);
    machine.mem_store_byte(0x86D5E, 0x90);
    machine.mem_store_byte(0x86D5F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1100);
    EXPECT_EQ(cpu.get_ip(), 0x31AC);
    EXPECT_FLAGS(0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x86D5B), 0x37);
    EXPECT_EQ(memory.load8(0x86D5C), 0x90);
    EXPECT_EQ(memory.load8(0x86D5D), 0x90);
    EXPECT_EQ(memory.load8(0x86D5E), 0x90);
    EXPECT_EQ(memory.load8(0x86D5F), 0x90);
}

//
// idiv byte [es:bp+7Eh]
//
TEST_F(MachineTest, idiv_byte_es_bp_7Eh_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x0B9F);
    cpu.set_bx(0x0FF2);
    cpu.set_cx(0x35C4);
    cpu.set_dx(0x8F0F);
    cpu.set_cs(0x3B68);
    cpu.set_ss(0xE8D3);
    cpu.set_ds(0xBFA7);
    cpu.set_es(0xE5AD);
    cpu.set_sp(0x5F34);
    cpu.set_bp(0x386B);
    cpu.set_si(0x0585);
    cpu.set_di(0xEA10);
    cpu.set_ip(0x2556);
    cpu.set_flags(0xF8C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3DBD6, 0x26);
    machine.mem_store_byte(0x3DBD7, 0xF2);
    machine.mem_store_byte(0x3DBD8, 0xF6);
    machine.mem_store_byte(0x3DBD9, 0x7E);
    machine.mem_store_byte(0x3DBDA, 0x7E);
    machine.mem_store_byte(0x3DBDB, 0x90);
    machine.mem_store_byte(0xE93B9, 0xBE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x052D);
    EXPECT_EQ(cpu.get_ip(), 0x255B);
    EXPECT_FLAGS(0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3DBD6), 0x26);
    EXPECT_EQ(memory.load8(0x3DBD7), 0xF2);
    EXPECT_EQ(memory.load8(0x3DBD8), 0xF6);
    EXPECT_EQ(memory.load8(0x3DBD9), 0x7E);
    EXPECT_EQ(memory.load8(0x3DBDA), 0x7E);
    EXPECT_EQ(memory.load8(0x3DBDB), 0x90);
    EXPECT_EQ(memory.load8(0xE93B9), 0xBE);
}

//
// imul al
//
TEST_F(MachineTest, imul_al_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x9905);
    cpu.set_bx(0xBF57);
    cpu.set_cx(0x4E04);
    cpu.set_dx(0xB1E7);
    cpu.set_cs(0x63D0);
    cpu.set_ss(0xF4C4);
    cpu.set_ds(0x9E98);
    cpu.set_es(0x66B0);
    cpu.set_sp(0x324C);
    cpu.set_bp(0x3325);
    cpu.set_si(0x9A13);
    cpu.set_di(0x243B);
    cpu.set_ip(0x72A6);
    cpu.set_flags(0xF417);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6AFA6, 0xF6);
    machine.mem_store_byte(0x6AFA7, 0xE8);
    machine.mem_store_byte(0x6AFA8, 0x90);
    machine.mem_store_byte(0x6AFA9, 0x90);
    machine.mem_store_byte(0x6AFAA, 0x90);
    machine.mem_store_byte(0x6AFAB, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0019);
    EXPECT_EQ(cpu.get_ip(), 0x72A8);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6AFA6), 0xF6);
    EXPECT_EQ(memory.load8(0x6AFA7), 0xE8);
    EXPECT_EQ(memory.load8(0x6AFA8), 0x90);
    EXPECT_EQ(memory.load8(0x6AFA9), 0x90);
    EXPECT_EQ(memory.load8(0x6AFAA), 0x90);
    EXPECT_EQ(memory.load8(0x6AFAB), 0x90);
}

//
// imul byte [ds:bx+di]
//
TEST_F(MachineTest, imul_byte_ds_bx_di_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x88ED);
    cpu.set_bx(0x39CD);
    cpu.set_cx(0xEFBE);
    cpu.set_dx(0x01B7);
    cpu.set_cs(0xBA74);
    cpu.set_ss(0x14E0);
    cpu.set_ds(0x755B);
    cpu.set_es(0xDF1E);
    cpu.set_sp(0x6808);
    cpu.set_bp(0xFBC3);
    cpu.set_si(0x7E17);
    cpu.set_di(0x0000);
    cpu.set_ip(0x58B0);
    cpu.set_flags(0xFC42);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBFFF0, 0xF6);
    machine.mem_store_byte(0xBFFF1, 0x29);
    machine.mem_store_byte(0xBFFF2, 0x90);
    machine.mem_store_byte(0xBFFF3, 0x90);
    machine.mem_store_byte(0xBFFF4, 0x90);
    machine.mem_store_byte(0xBFFF5, 0x90);
    machine.mem_store_byte(0x78F7D, 0xFC);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x004C);
    EXPECT_EQ(cpu.get_ip(), 0x58B2);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBFFF0), 0xF6);
    EXPECT_EQ(memory.load8(0xBFFF1), 0x29);
    EXPECT_EQ(memory.load8(0xBFFF2), 0x90);
    EXPECT_EQ(memory.load8(0xBFFF3), 0x90);
    EXPECT_EQ(memory.load8(0xBFFF4), 0x90);
    EXPECT_EQ(memory.load8(0xBFFF5), 0x90);
    EXPECT_EQ(memory.load8(0x78F7D), 0xFC);
}

//
// imul byte [ss:bp+di+35h]
//
TEST_F(MachineTest, imul_byte_ss_bp_di_35h_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x53ED);
    cpu.set_bx(0xFE28);
    cpu.set_cx(0x90EE);
    cpu.set_dx(0x4A68);
    cpu.set_cs(0x6457);
    cpu.set_ss(0x747C);
    cpu.set_ds(0xABF4);
    cpu.set_es(0x91C4);
    cpu.set_sp(0x8EBC);
    cpu.set_bp(0xA6D3);
    cpu.set_si(0x9BE3);
    cpu.set_di(0x0A6C);
    cpu.set_ip(0x0BF9);
    cpu.set_flags(0xF093);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x65169, 0xF6);
    machine.mem_store_byte(0x6516A, 0x6B);
    machine.mem_store_byte(0x6516B, 0x35);
    machine.mem_store_byte(0x6516C, 0x90);
    machine.mem_store_byte(0x6516D, 0x90);
    machine.mem_store_byte(0x7F934, 0x01);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFFED);
    EXPECT_EQ(cpu.get_ip(), 0x0BFC);
    EXPECT_FLAGS(0xF056);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x65169), 0xF6);
    EXPECT_EQ(memory.load8(0x6516A), 0x6B);
    EXPECT_EQ(memory.load8(0x6516B), 0x35);
    EXPECT_EQ(memory.load8(0x6516C), 0x90);
    EXPECT_EQ(memory.load8(0x6516D), 0x90);
    EXPECT_EQ(memory.load8(0x7F934), 0x01);
}

//
// imul word [cs:bx+1Ah]
//
TEST_F(MachineTest, imul_word_cs_bx_1Ah_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xEE9C);
    cpu.set_bx(0xE45B);
    cpu.set_cx(0x556C);
    cpu.set_dx(0x4A40);
    cpu.set_cs(0x21E4);
    cpu.set_ss(0x080B);
    cpu.set_ds(0x52C2);
    cpu.set_es(0x22EA);
    cpu.set_sp(0x2DBC);
    cpu.set_bp(0x5741);
    cpu.set_si(0xD971);
    cpu.set_di(0x492D);
    cpu.set_ip(0x17A5);
    cpu.set_flags(0xF8D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x235E5, 0x2E);
    machine.mem_store_byte(0x235E6, 0xF7);
    machine.mem_store_byte(0x235E7, 0x6F);
    machine.mem_store_byte(0x235E8, 0x1A);
    machine.mem_store_byte(0x235E9, 0x90);
    machine.mem_store_byte(0x302B5, 0x21);
    machine.mem_store_byte(0x302B6, 0xF3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xD61C);
    EXPECT_EQ(cpu.get_dx(), 0x00DF);
    EXPECT_EQ(cpu.get_ip(), 0x17A9);
    EXPECT_FLAGS(0xF813);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x235E5), 0x2E);
    EXPECT_EQ(memory.load8(0x235E6), 0xF7);
    EXPECT_EQ(memory.load8(0x235E7), 0x6F);
    EXPECT_EQ(memory.load8(0x235E8), 0x1A);
    EXPECT_EQ(memory.load8(0x235E9), 0x90);
    EXPECT_EQ(memory.load8(0x302B5), 0x21);
    EXPECT_EQ(memory.load8(0x302B6), 0xF3);
}

//
// imul word [cs:bx+di-4Dh]
//
TEST_F(MachineTest, imul_word_cs_bx_di_4Dh_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x03DC);
    cpu.set_bx(0x1062);
    cpu.set_cx(0x38C8);
    cpu.set_dx(0x70BF);
    cpu.set_cs(0x3065);
    cpu.set_ss(0x5CF1);
    cpu.set_ds(0x548B);
    cpu.set_es(0x324B);
    cpu.set_sp(0xB294);
    cpu.set_bp(0xEA50);
    cpu.set_si(0x6B25);
    cpu.set_di(0x7B2A);
    cpu.set_ip(0xB908);
    cpu.set_flags(0xF083);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3BF58, 0x2E);
    machine.mem_store_byte(0x3BF59, 0xF7);
    machine.mem_store_byte(0x3BF5A, 0x69);
    machine.mem_store_byte(0x3BF5B, 0xB3);
    machine.mem_store_byte(0x3BF5C, 0x90);
    machine.mem_store_byte(0x3BF5D, 0x90);
    machine.mem_store_byte(0x3918F, 0x28);
    machine.mem_store_byte(0x39190, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9A60);
    EXPECT_EQ(cpu.get_dx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0xB90C);
    EXPECT_FLAGS(0xF803);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3BF58), 0x2E);
    EXPECT_EQ(memory.load8(0x3BF59), 0xF7);
    EXPECT_EQ(memory.load8(0x3BF5A), 0x69);
    EXPECT_EQ(memory.load8(0x3BF5B), 0xB3);
    EXPECT_EQ(memory.load8(0x3BF5C), 0x90);
    EXPECT_EQ(memory.load8(0x3BF5D), 0x90);
    EXPECT_EQ(memory.load8(0x3918F), 0x28);
    EXPECT_EQ(memory.load8(0x39190), 0x00);
}

//
// rcl bp, cl
//
TEST_F(MachineTest, rcl_bp_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xB1BD);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xC322);
    cpu.set_dx(0xCDE4);
    cpu.set_cs(0x260C);
    cpu.set_ss(0x4D81);
    cpu.set_ds(0x8F5B);
    cpu.set_es(0x5426);
    cpu.set_sp(0xC220);
    cpu.set_bp(0xB476);
    cpu.set_si(0xE835);
    cpu.set_di(0x80F0);
    cpu.set_ip(0xBDDD);
    cpu.set_flags(0xF012);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x31E9D, 0x26);
    machine.mem_store_byte(0x31E9E, 0xD3);
    machine.mem_store_byte(0x31E9F, 0xD5);
    machine.mem_store_byte(0x31EA0, 0x90);
    machine.mem_store_byte(0x31EA1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBDE0);
    EXPECT_FLAGS(0xF812);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x31E9D), 0x26);
    EXPECT_EQ(memory.load8(0x31E9E), 0xD3);
    EXPECT_EQ(memory.load8(0x31E9F), 0xD5);
    EXPECT_EQ(memory.load8(0x31EA0), 0x90);
    EXPECT_EQ(memory.load8(0x31EA1), 0x90);
}

//
// rcl word [es:bp+di+55h], cl
//
TEST_F(MachineTest, rcl_word_es_bp_di_55h_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x61E8);
    cpu.set_bx(0xEA3E);
    cpu.set_cx(0x6522);
    cpu.set_dx(0x4225);
    cpu.set_cs(0x57F0);
    cpu.set_ss(0x376D);
    cpu.set_ds(0x0919);
    cpu.set_es(0x6017);
    cpu.set_sp(0xB788);
    cpu.set_bp(0x0000);
    cpu.set_si(0x0EDD);
    cpu.set_di(0xC8AF);
    cpu.set_ip(0xE204);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x66104, 0x26);
    machine.mem_store_byte(0x66105, 0xD3);
    machine.mem_store_byte(0x66106, 0x53);
    machine.mem_store_byte(0x66107, 0x55);
    machine.mem_store_byte(0x66108, 0x90);
    machine.mem_store_byte(0x66109, 0x90);
    machine.mem_store_byte(0x6CA74, 0x67);
    machine.mem_store_byte(0x6CA75, 0x50);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE208);
    EXPECT_FLAGS(0xF4D6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x66104), 0x26);
    EXPECT_EQ(memory.load8(0x66105), 0xD3);
    EXPECT_EQ(memory.load8(0x66106), 0x53);
    EXPECT_EQ(memory.load8(0x66107), 0x55);
    EXPECT_EQ(memory.load8(0x66108), 0x90);
    EXPECT_EQ(memory.load8(0x66109), 0x90);
    EXPECT_EQ(memory.load8(0x6CA74), 0x67);
    EXPECT_EQ(memory.load8(0x6CA75), 0x50);
}

//
// rcr al, cl
//
TEST_F(MachineTest, rcr_al_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xB6B7);
    cpu.set_bx(0xE236);
    cpu.set_cx(0x5E36);
    cpu.set_dx(0xF378);
    cpu.set_cs(0xCA07);
    cpu.set_ss(0x6472);
    cpu.set_ds(0xD44E);
    cpu.set_es(0x1A5F);
    cpu.set_sp(0xE8EC);
    cpu.set_bp(0x78A2);
    cpu.set_si(0xE1A8);
    cpu.set_di(0x6D42);
    cpu.set_ip(0xCAB4);
    cpu.set_flags(0xF082);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD6B24, 0x36);
    machine.mem_store_byte(0xD6B25, 0xD2);
    machine.mem_store_byte(0xD6B26, 0xD8);
    machine.mem_store_byte(0xD6B27, 0x90);
    machine.mem_store_byte(0xD6B28, 0x90);
    machine.mem_store_byte(0xD6B29, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCAB7);
    EXPECT_FLAGS(0xF882);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD6B24), 0x36);
    EXPECT_EQ(memory.load8(0xD6B25), 0xD2);
    EXPECT_EQ(memory.load8(0xD6B26), 0xD8);
    EXPECT_EQ(memory.load8(0xD6B27), 0x90);
    EXPECT_EQ(memory.load8(0xD6B28), 0x90);
    EXPECT_EQ(memory.load8(0xD6B29), 0x90);
}

//
// rcr byte [es:bx+57h], cl
//
TEST_F(MachineTest, rcr_byte_es_bx_57h_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xD908);
    cpu.set_bx(0x01B9);
    cpu.set_cx(0xF424);
    cpu.set_dx(0x0C30);
    cpu.set_cs(0xFABD);
    cpu.set_ss(0x3CE4);
    cpu.set_ds(0x6AF4);
    cpu.set_es(0x38D0);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x08BA);
    cpu.set_si(0xECFD);
    cpu.set_di(0x3E69);
    cpu.set_ip(0x368C);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFE25C, 0x26);
    machine.mem_store_byte(0xFE25D, 0xD2);
    machine.mem_store_byte(0xFE25E, 0x5F);
    machine.mem_store_byte(0xFE25F, 0x57);
    machine.mem_store_byte(0xFE260, 0x90);
    machine.mem_store_byte(0xFE261, 0x90);
    machine.mem_store_byte(0x38F10, 0x5C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3690);
    EXPECT_FLAGS(0xF897);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFE25C), 0x26);
    EXPECT_EQ(memory.load8(0xFE25D), 0xD2);
    EXPECT_EQ(memory.load8(0xFE25E), 0x5F);
    EXPECT_EQ(memory.load8(0xFE25F), 0x57);
    EXPECT_EQ(memory.load8(0xFE260), 0x90);
    EXPECT_EQ(memory.load8(0xFE261), 0x90);
    EXPECT_EQ(memory.load8(0x38F10), 0x5C);
}

//
// rcr byte [ss:bp+si-Dh], cl
//
TEST_F(MachineTest, rcr_byte_ss_bp_si_Dh_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x0DB7);
    cpu.set_bx(0x851A);
    cpu.set_cx(0x2536);
    cpu.set_dx(0x90B2);
    cpu.set_cs(0xF411);
    cpu.set_ss(0x0A3E);
    cpu.set_ds(0xE896);
    cpu.set_es(0x92F9);
    cpu.set_sp(0xF370);
    cpu.set_bp(0x5AA3);
    cpu.set_si(0x7F96);
    cpu.set_di(0xB892);
    cpu.set_ip(0x4491);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF85A1, 0xD2);
    machine.mem_store_byte(0xF85A2, 0x5A);
    machine.mem_store_byte(0xF85A3, 0xF3);
    machine.mem_store_byte(0xF85A4, 0x90);
    machine.mem_store_byte(0xF85A5, 0x90);
    machine.mem_store_byte(0x17E0C, 0x22);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4494);
    EXPECT_FLAGS(0xF4D6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF85A1), 0xD2);
    EXPECT_EQ(memory.load8(0xF85A2), 0x5A);
    EXPECT_EQ(memory.load8(0xF85A3), 0xF3);
    EXPECT_EQ(memory.load8(0xF85A4), 0x90);
    EXPECT_EQ(memory.load8(0xF85A5), 0x90);
    EXPECT_EQ(memory.load8(0x17E0C), 0x22);
}

//
// setmoc byte [ss:bp+di], cl
//
TEST_F(MachineTest, setmoc_byte_ss_bp_di_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xECD3);
    cpu.set_bx(0xA319);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x4743);
    cpu.set_cs(0x23C7);
    cpu.set_ss(0xF22A);
    cpu.set_ds(0x7A8D);
    cpu.set_es(0xAA8E);
    cpu.set_sp(0xAE8D);
    cpu.set_bp(0xC1DC);
    cpu.set_si(0x3017);
    cpu.set_di(0x6234);
    cpu.set_ip(0x0637);
    cpu.set_flags(0xFC53);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x242A7, 0xD2);
    machine.mem_store_byte(0x242A8, 0x33);
    machine.mem_store_byte(0x242A9, 0x90);
    machine.mem_store_byte(0x242AA, 0x90);
    machine.mem_store_byte(0x242AB, 0x90);
    machine.mem_store_byte(0xF46B0, 0xC5);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0639);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x242A7), 0xD2);
    EXPECT_EQ(memory.load8(0x242A8), 0x33);
    EXPECT_EQ(memory.load8(0x242A9), 0x90);
    EXPECT_EQ(memory.load8(0x242AA), 0x90);
    EXPECT_EQ(memory.load8(0x242AB), 0x90);
    EXPECT_EQ(memory.load8(0xF46B0), 0xC5);
}

//
// setmoc word [cs:si-7CCDh], cl
//
TEST_F(MachineTest, setmoc_word_cs_si_7CCDh_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x151A);
    cpu.set_bx(0xDC23);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x78D4);
    cpu.set_cs(0xC7C2);
    cpu.set_ss(0xB0B1);
    cpu.set_ds(0xE6AA);
    cpu.set_es(0x2C5D);
    cpu.set_sp(0x0E6D);
    cpu.set_bp(0xD26E);
    cpu.set_si(0x24C9);
    cpu.set_di(0xEFC7);
    cpu.set_ip(0xDEBB);
    cpu.set_flags(0xF056);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD5ADB, 0x2E);
    machine.mem_store_byte(0xD5ADC, 0xD3);
    machine.mem_store_byte(0xD5ADD, 0xB4);
    machine.mem_store_byte(0xD5ADE, 0x33);
    machine.mem_store_byte(0xD5ADF, 0x83);
    machine.mem_store_byte(0xD241C, 0x95);
    machine.mem_store_byte(0xD241D, 0x87);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDEC0);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD5ADB), 0x2E);
    EXPECT_EQ(memory.load8(0xD5ADC), 0xD3);
    EXPECT_EQ(memory.load8(0xD5ADD), 0xB4);
    EXPECT_EQ(memory.load8(0xD5ADE), 0x33);
    EXPECT_EQ(memory.load8(0xD5ADF), 0x83);
    EXPECT_EQ(memory.load8(0xD241C), 0x95);
    EXPECT_EQ(memory.load8(0xD241D), 0x87);
}

//
// setmoc word [ds:bp-1110h], cl
//
TEST_F(MachineTest, setmoc_word_ds_bp_1110h_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x1C1D);
    cpu.set_bx(0x0000);
    cpu.set_cx(0xB300);
    cpu.set_dx(0x5B4C);
    cpu.set_cs(0x97B8);
    cpu.set_ss(0xA9E0);
    cpu.set_ds(0xE1A9);
    cpu.set_es(0xF26E);
    cpu.set_sp(0x4E70);
    cpu.set_bp(0x0E32);
    cpu.set_si(0xD5D1);
    cpu.set_di(0x819D);
    cpu.set_ip(0xDB80);
    cpu.set_flags(0xF082);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA5700, 0x3E);
    machine.mem_store_byte(0xA5701, 0xD3);
    machine.mem_store_byte(0xA5702, 0xB6);
    machine.mem_store_byte(0xA5703, 0xF0);
    machine.mem_store_byte(0xA5704, 0xEE);
    machine.mem_store_byte(0xA5705, 0x90);
    machine.mem_store_byte(0xF17B2, 0xD7);
    machine.mem_store_byte(0xF17B3, 0x38);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDB85);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA5700), 0x3E);
    EXPECT_EQ(memory.load8(0xA5701), 0xD3);
    EXPECT_EQ(memory.load8(0xA5702), 0xB6);
    EXPECT_EQ(memory.load8(0xA5703), 0xF0);
    EXPECT_EQ(memory.load8(0xA5704), 0xEE);
    EXPECT_EQ(memory.load8(0xA5705), 0x90);
    EXPECT_EQ(memory.load8(0xF17B2), 0xD7);
    EXPECT_EQ(memory.load8(0xF17B3), 0x38);
}

//
// setmoc word [ds:bp+di], cl
//
TEST_F(MachineTest, setmoc_word_ds_bp_di_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x31E5);
    cpu.set_bx(0x6736);
    cpu.set_cx(0x9B00);
    cpu.set_dx(0x350E);
    cpu.set_cs(0x611D);
    cpu.set_ss(0x158F);
    cpu.set_ds(0xEE85);
    cpu.set_es(0xB709);
    cpu.set_sp(0x458B);
    cpu.set_bp(0x2993);
    cpu.set_si(0xBC0E);
    cpu.set_di(0x4BBE);
    cpu.set_ip(0x11F7);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x623C7, 0x3E);
    machine.mem_store_byte(0x623C8, 0xD3);
    machine.mem_store_byte(0x623C9, 0x33);
    machine.mem_store_byte(0x623CA, 0x90);
    machine.mem_store_byte(0x623CB, 0x90);
    machine.mem_store_byte(0xF5DA1, 0x77);
    machine.mem_store_byte(0xF5DA2, 0x5A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x11FA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x623C7), 0x3E);
    EXPECT_EQ(memory.load8(0x623C8), 0xD3);
    EXPECT_EQ(memory.load8(0x623C9), 0x33);
    EXPECT_EQ(memory.load8(0x623CA), 0x90);
    EXPECT_EQ(memory.load8(0x623CB), 0x90);
    EXPECT_EQ(memory.load8(0xF5DA1), 0x77);
    EXPECT_EQ(memory.load8(0xF5DA2), 0x5A);
}

//
// setmoc word [ss:bx+si-7Ch], cl
//
TEST_F(MachineTest, setmoc_word_ss_bx_si_7Ch_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x568F);
    cpu.set_bx(0xCAB8);
    cpu.set_cx(0x0000);
    cpu.set_dx(0x1D56);
    cpu.set_cs(0x084F);
    cpu.set_ss(0x0E65);
    cpu.set_ds(0x5255);
    cpu.set_es(0x981B);
    cpu.set_sp(0x6F60);
    cpu.set_bp(0xF3E4);
    cpu.set_si(0x2B44);
    cpu.set_di(0x6792);
    cpu.set_ip(0x2F1B);
    cpu.set_flags(0xFC96);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0B40B, 0x36);
    machine.mem_store_byte(0x0B40C, 0xD3);
    machine.mem_store_byte(0x0B40D, 0x70);
    machine.mem_store_byte(0x0B40E, 0x84);
    machine.mem_store_byte(0x0B40F, 0x90);
    machine.mem_store_byte(0x1DBD0, 0xFF);
    machine.mem_store_byte(0x1DBD1, 0x1D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2F1F);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0B40B), 0x36);
    EXPECT_EQ(memory.load8(0x0B40C), 0xD3);
    EXPECT_EQ(memory.load8(0x0B40D), 0x70);
    EXPECT_EQ(memory.load8(0x0B40E), 0x84);
    EXPECT_EQ(memory.load8(0x0B40F), 0x90);
    EXPECT_EQ(memory.load8(0x1DBD0), 0xFF);
    EXPECT_EQ(memory.load8(0x1DBD1), 0x1D);
}

//
// shl byte [ss:bp-34Fh], cl
//
TEST_F(MachineTest, shl_byte_ss_bp_34Fh_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x8377);
    cpu.set_bx(0x80CC);
    cpu.set_cx(0x3506);
    cpu.set_dx(0xE87D);
    cpu.set_cs(0xFC4C);
    cpu.set_ss(0x157E);
    cpu.set_ds(0x4E4A);
    cpu.set_es(0xAFC8);
    cpu.set_sp(0x5495);
    cpu.set_bp(0x3AFF);
    cpu.set_si(0x0000);
    cpu.set_di(0x6B5D);
    cpu.set_ip(0xF8BA);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0BD7A, 0xD2);
    machine.mem_store_byte(0x0BD7B, 0xA6);
    machine.mem_store_byte(0x0BD7C, 0xB1);
    machine.mem_store_byte(0x0BD7D, 0xFC);
    machine.mem_store_byte(0x0BD7E, 0x90);
    machine.mem_store_byte(0x0BD7F, 0x90);
    machine.mem_store_byte(0x18F90, 0x33);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF8BE);
    EXPECT_FLAGS(0xFC86);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0BD7A), 0xD2);
    EXPECT_EQ(memory.load8(0x0BD7B), 0xA6);
    EXPECT_EQ(memory.load8(0x0BD7C), 0xB1);
    EXPECT_EQ(memory.load8(0x0BD7D), 0xFC);
    EXPECT_EQ(memory.load8(0x0BD7E), 0x90);
    EXPECT_EQ(memory.load8(0x0BD7F), 0x90);
    EXPECT_EQ(memory.load8(0x18F90), 0xC0);
}

//
// shl dh, cl
//
TEST_F(MachineTest, shl_dh_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xB448);
    cpu.set_bx(0x123D);
    cpu.set_cx(0xCE04);
    cpu.set_dx(0x8E21);
    cpu.set_cs(0xB525);
    cpu.set_ss(0x9E20);
    cpu.set_ds(0x6C2C);
    cpu.set_es(0x1723);
    cpu.set_sp(0xADAE);
    cpu.set_bp(0xD417);
    cpu.set_si(0xD2F6);
    cpu.set_di(0x0739);
    cpu.set_ip(0xBCF3);
    cpu.set_flags(0xF413);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC0F43, 0xD2);
    machine.mem_store_byte(0xC0F44, 0xE6);
    machine.mem_store_byte(0xC0F45, 0x90);
    machine.mem_store_byte(0xC0F46, 0x90);
    machine.mem_store_byte(0xC0F47, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xE021);
    EXPECT_EQ(cpu.get_ip(), 0xBCF5);
    EXPECT_FLAGS(0xFC82);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC0F43), 0xD2);
    EXPECT_EQ(memory.load8(0xC0F44), 0xE6);
    EXPECT_EQ(memory.load8(0xC0F45), 0x90);
    EXPECT_EQ(memory.load8(0xC0F46), 0x90);
    EXPECT_EQ(memory.load8(0xC0F47), 0x90);
}

//
// shl word [ds:bx+di], cl
//
TEST_F(MachineTest, shl_word_ds_bx_di_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xC212);
    cpu.set_bx(0x5326);
    cpu.set_cx(0xFA0A);
    cpu.set_dx(0x3E6B);
    cpu.set_cs(0x8226);
    cpu.set_ss(0x659D);
    cpu.set_ds(0x9120);
    cpu.set_es(0xAAB0);
    cpu.set_sp(0x5FA3);
    cpu.set_bp(0x8E07);
    cpu.set_si(0x9CD1);
    cpu.set_di(0xF119);
    cpu.set_ip(0xDF4A);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x901AA, 0x3E);
    machine.mem_store_byte(0x901AB, 0xD3);
    machine.mem_store_byte(0x901AC, 0x21);
    machine.mem_store_byte(0x901AD, 0x90);
    machine.mem_store_byte(0x901AE, 0x90);
    machine.mem_store_byte(0x901AF, 0x90);
    machine.mem_store_byte(0x9563F, 0xFA);
    machine.mem_store_byte(0x95640, 0x29);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xDF4D);
    EXPECT_FLAGS(0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x901AA), 0x3E);
    EXPECT_EQ(memory.load8(0x901AB), 0xD3);
    EXPECT_EQ(memory.load8(0x901AC), 0x21);
    EXPECT_EQ(memory.load8(0x901AD), 0x90);
    EXPECT_EQ(memory.load8(0x901AE), 0x90);
    EXPECT_EQ(memory.load8(0x901AF), 0x90);
    EXPECT_EQ(memory.load8(0x9563F), 0x00);
    EXPECT_EQ(memory.load8(0x95640), 0xE8);
}

//
// shl word [ds:bx+si], cl
//
TEST_F(MachineTest, shl_word_ds_bx_si_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x908D);
    cpu.set_bx(0xF7FB);
    cpu.set_cx(0xD30E);
    cpu.set_dx(0x8C7E);
    cpu.set_cs(0xCB1E);
    cpu.set_ss(0x0C51);
    cpu.set_ds(0xAF1B);
    cpu.set_es(0x1884);
    cpu.set_sp(0x3819);
    cpu.set_bp(0x7D77);
    cpu.set_si(0xC51A);
    cpu.set_di(0xE1EB);
    cpu.set_ip(0x4D28);
    cpu.set_flags(0xF846);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCFF08, 0xD3);
    machine.mem_store_byte(0xCFF09, 0x20);
    machine.mem_store_byte(0xCFF0A, 0x90);
    machine.mem_store_byte(0xCFF0B, 0x90);
    machine.mem_store_byte(0xCFF0C, 0x90);
    machine.mem_store_byte(0xCFF0D, 0x90);
    machine.mem_store_byte(0xBAEC5, 0x0D);
    machine.mem_store_byte(0xBAEC6, 0x2D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4D2A);
    EXPECT_FLAGS(0xF807);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCFF08), 0xD3);
    EXPECT_EQ(memory.load8(0xCFF09), 0x20);
    EXPECT_EQ(memory.load8(0xCFF0A), 0x90);
    EXPECT_EQ(memory.load8(0xCFF0B), 0x90);
    EXPECT_EQ(memory.load8(0xCFF0C), 0x90);
    EXPECT_EQ(memory.load8(0xCFF0D), 0x90);
    EXPECT_EQ(memory.load8(0xBAEC5), 0x00);
    EXPECT_EQ(memory.load8(0xBAEC6), 0x40);
}

//
// shl word [ds:si-3Ah], cl
//
TEST_F(MachineTest, shl_word_ds_si_3Ah_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xD649);
    cpu.set_bx(0x8E7C);
    cpu.set_cx(0xD502);
    cpu.set_dx(0xF225);
    cpu.set_cs(0x3FCB);
    cpu.set_ss(0x5E01);
    cpu.set_ds(0x19CA);
    cpu.set_es(0xE540);
    cpu.set_sp(0xDFDF);
    cpu.set_bp(0x0D4B);
    cpu.set_si(0x922D);
    cpu.set_di(0x8C92);
    cpu.set_ip(0x944B);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x490FB, 0xD3);
    machine.mem_store_byte(0x490FC, 0x64);
    machine.mem_store_byte(0x490FD, 0xC6);
    machine.mem_store_byte(0x490FE, 0x90);
    machine.mem_store_byte(0x490FF, 0x90);
    machine.mem_store_byte(0x22E93, 0x9F);
    machine.mem_store_byte(0x22E94, 0x44);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x944E);
    EXPECT_FLAGS(0xFC13);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x490FB), 0xD3);
    EXPECT_EQ(memory.load8(0x490FC), 0x64);
    EXPECT_EQ(memory.load8(0x490FD), 0xC6);
    EXPECT_EQ(memory.load8(0x490FE), 0x90);
    EXPECT_EQ(memory.load8(0x490FF), 0x90);
    EXPECT_EQ(memory.load8(0x22E93), 0x7C);
    EXPECT_EQ(memory.load8(0x22E94), 0x12);
}

//
// shl word [es:bx-7Ch], cl
//
TEST_F(MachineTest, shl_word_es_bx_7Ch_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xBF57);
    cpu.set_bx(0x63A3);
    cpu.set_cx(0xBF02);
    cpu.set_dx(0xFAC5);
    cpu.set_cs(0x07AD);
    cpu.set_ss(0x0FC0);
    cpu.set_ds(0xC265);
    cpu.set_es(0x36A1);
    cpu.set_sp(0x23AA);
    cpu.set_bp(0xE73D);
    cpu.set_si(0x0000);
    cpu.set_di(0xEB12);
    cpu.set_ip(0x71CB);
    cpu.set_flags(0xFCC2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0EC9B, 0x26);
    machine.mem_store_byte(0x0EC9C, 0xD3);
    machine.mem_store_byte(0x0EC9D, 0x67);
    machine.mem_store_byte(0x0EC9E, 0x84);
    machine.mem_store_byte(0x0EC9F, 0x90);
    machine.mem_store_byte(0x3CD37, 0x5C);
    machine.mem_store_byte(0x3CD38, 0x52);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x71CF);
    EXPECT_FLAGS(0xFC13);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0EC9B), 0x26);
    EXPECT_EQ(memory.load8(0x0EC9C), 0xD3);
    EXPECT_EQ(memory.load8(0x0EC9D), 0x67);
    EXPECT_EQ(memory.load8(0x0EC9E), 0x84);
    EXPECT_EQ(memory.load8(0x0EC9F), 0x90);
    EXPECT_EQ(memory.load8(0x3CD37), 0x70);
    EXPECT_EQ(memory.load8(0x3CD38), 0x49);
}

//
// shl word [ss:bp+872h], cl
//
TEST_F(MachineTest, shl_word_ss_bp_872h_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0x6AAF);
    cpu.set_bx(0x9B90);
    cpu.set_cx(0xD50E);
    cpu.set_dx(0x4193);
    cpu.set_cs(0x0909);
    cpu.set_ss(0x3A9B);
    cpu.set_ds(0xEBE7);
    cpu.set_es(0x9898);
    cpu.set_sp(0x3B96);
    cpu.set_bp(0xEFFE);
    cpu.set_si(0x0913);
    cpu.set_di(0x029E);
    cpu.set_ip(0xEC83);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x17D13, 0xD3);
    machine.mem_store_byte(0x17D14, 0xA6);
    machine.mem_store_byte(0x17D15, 0x72);
    machine.mem_store_byte(0x17D16, 0x08);
    machine.mem_store_byte(0x17D17, 0x90);
    machine.mem_store_byte(0x4A220, 0xBF);
    machine.mem_store_byte(0x4A221, 0x45);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEC87);
    EXPECT_FLAGS(0xF087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x17D13), 0xD3);
    EXPECT_EQ(memory.load8(0x17D14), 0xA6);
    EXPECT_EQ(memory.load8(0x17D15), 0x72);
    EXPECT_EQ(memory.load8(0x17D16), 0x08);
    EXPECT_EQ(memory.load8(0x17D17), 0x90);
    EXPECT_EQ(memory.load8(0x4A220), 0x00);
    EXPECT_EQ(memory.load8(0x4A221), 0xC0);
}

//
// shr byte [ds:bx], cl
//
TEST_F(MachineTest, shr_byte_ds_bx_cl_batch5)
{
    // Initial CPU State
    cpu.set_ax(0xDD6F);
    cpu.set_bx(0xDF62);
    cpu.set_cx(0x4A08);
    cpu.set_dx(0x4351);
    cpu.set_cs(0x90A0);
    cpu.set_ss(0x6412);
    cpu.set_ds(0x6521);
    cpu.set_es(0x34A7);
    cpu.set_sp(0xB0AE);
    cpu.set_bp(0x47BB);
    cpu.set_si(0xBE5C);
    cpu.set_di(0xB334);
    cpu.set_ip(0xF006);
    cpu.set_flags(0xF886);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9FA06, 0xD2);
    machine.mem_store_byte(0x9FA07, 0x2F);
    machine.mem_store_byte(0x9FA08, 0x90);
    machine.mem_store_byte(0x9FA09, 0x90);
    machine.mem_store_byte(0x9FA0A, 0x90);
    machine.mem_store_byte(0x9FA0B, 0x90);
    machine.mem_store_byte(0x73172, 0x80);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xF008);
    EXPECT_FLAGS(0xF047);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9FA06), 0xD2);
    EXPECT_EQ(memory.load8(0x9FA07), 0x2F);
    EXPECT_EQ(memory.load8(0x9FA08), 0x90);
    EXPECT_EQ(memory.load8(0x9FA09), 0x90);
    EXPECT_EQ(memory.load8(0x9FA0A), 0x90);
    EXPECT_EQ(memory.load8(0x9FA0B), 0x90);
    EXPECT_EQ(memory.load8(0x73172), 0x00);
}
