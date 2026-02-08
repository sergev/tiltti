#include "fixture.h"

//
// aam 0h
//
TEST_F(MachineTest, aam_0h_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x7DEC);
    cpu.set_bx(0x6EF8);
    cpu.set_cx(0x044E);
    cpu.set_dx(0xC0DE);
    cpu.set_cs(0x8887);
    cpu.set_ss(0x868D);
    cpu.set_ds(0x8D70);
    cpu.set_es(0x0559);
    cpu.set_sp(0x7B4F);
    cpu.set_bp(0xFB0D);
    cpu.set_si(0x4DD0);
    cpu.set_di(0x7393);
    cpu.set_ip(0xAC3A);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x934AA, 0xD4);
    machine.mem_store_byte(0x934AB, 0x00);
    machine.mem_store_byte(0x934AC, 0x90);
    machine.mem_store_byte(0x934AD, 0x90);
    machine.mem_store_byte(0x934AE, 0x90);
    machine.mem_store_byte(0x934AF, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x7B49);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x934AA), 0xD4);
    EXPECT_EQ(memory.load8(0x934AB), 0x00);
    EXPECT_EQ(memory.load8(0x934AC), 0x90);
    EXPECT_EQ(memory.load8(0x934AD), 0x90);
    EXPECT_EQ(memory.load8(0x934AE), 0x90);
    EXPECT_EQ(memory.load8(0x934AF), 0x90);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_FLAGS_LO(0x8E41D, 0x46);
    EXPECT_FLAGS_HI(0x8E41E, 0xF4);
    EXPECT_EQ(memory.load8(0x8E41B), 0x87);
    EXPECT_EQ(memory.load8(0x8E41C), 0x88);
    EXPECT_EQ(memory.load8(0x8E419), 0x3C);
    EXPECT_EQ(memory.load8(0x8E41A), 0xAC);
}

//
// call word [ds:di-1h]
//
TEST_F(MachineTest, call_word_ds_di_1h_batch7)
{
    // Initial CPU State
    cpu.set_ax(0xD840);
    cpu.set_bx(0x9429);
    cpu.set_cx(0x0DE0);
    cpu.set_dx(0x530D);
    cpu.set_cs(0xEF18);
    cpu.set_ss(0x2571);
    cpu.set_ds(0x8802);
    cpu.set_es(0xA8E3);
    cpu.set_sp(0xF6BE);
    cpu.set_bp(0xC06D);
    cpu.set_si(0xE335);
    cpu.set_di(0x0000);
    cpu.set_ip(0xF62E);
    cpu.set_flags(0xF886);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFE7AE, 0xFF);
    machine.mem_store_byte(0xFE7AF, 0x55);
    machine.mem_store_byte(0xFE7B0, 0xFF);
    machine.mem_store_byte(0xFE7B1, 0x90);
    machine.mem_store_byte(0xFE7B2, 0x90);
    machine.mem_store_byte(0xFE7B3, 0x90);
    machine.mem_store_byte(0x9801F, 0xFA);
    machine.mem_store_byte(0x88020, 0x97);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xF6BC);
    EXPECT_EQ(cpu.get_ip(), 0x97FA);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFE7AE), 0xFF);
    EXPECT_EQ(memory.load8(0xFE7AF), 0x55);
    EXPECT_EQ(memory.load8(0xFE7B0), 0xFF);
    EXPECT_EQ(memory.load8(0xFE7B1), 0x90);
    EXPECT_EQ(memory.load8(0xFE7B2), 0x90);
    EXPECT_EQ(memory.load8(0xFE7B3), 0x90);
    EXPECT_EQ(memory.load8(0x9801F), 0xFA);
    EXPECT_EQ(memory.load8(0x88020), 0x97);
    EXPECT_EQ(memory.load8(0x34DCC), 0x31);
    EXPECT_EQ(memory.load8(0x34DCD), 0xF6);
}

//
// daa
//
TEST_F(MachineTest, daa_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x099F);
    cpu.set_bx(0x65C2);
    cpu.set_cx(0xF05C);
    cpu.set_dx(0x6337);
    cpu.set_cs(0x0E31);
    cpu.set_ss(0xA00A);
    cpu.set_ds(0x2696);
    cpu.set_es(0x5EC6);
    cpu.set_sp(0xD11D);
    cpu.set_bp(0x0C97);
    cpu.set_si(0x1C2A);
    cpu.set_di(0x1680);
    cpu.set_ip(0xC8F6);
    cpu.set_flags(0xF412);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1AC06, 0x27);
    machine.mem_store_byte(0x1AC07, 0x90);
    machine.mem_store_byte(0x1AC08, 0x90);
    machine.mem_store_byte(0x1AC09, 0x90);
    machine.mem_store_byte(0x1AC0A, 0x90);
    machine.mem_store_byte(0x1AC0B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x09A5);
    EXPECT_EQ(cpu.get_ip(), 0xC8F7);
    EXPECT_FLAGS(0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1AC06), 0x27);
    EXPECT_EQ(memory.load8(0x1AC07), 0x90);
    EXPECT_EQ(memory.load8(0x1AC08), 0x90);
    EXPECT_EQ(memory.load8(0x1AC09), 0x90);
    EXPECT_EQ(memory.load8(0x1AC0A), 0x90);
    EXPECT_EQ(memory.load8(0x1AC0B), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x8C9D);
    cpu.set_bx(0xAAFE);
    cpu.set_cx(0x0E0E);
    cpu.set_dx(0xF699);
    cpu.set_cs(0xFA48);
    cpu.set_ss(0xE878);
    cpu.set_ds(0xA6BB);
    cpu.set_es(0x6FF7);
    cpu.set_sp(0x5293);
    cpu.set_bp(0x620C);
    cpu.set_si(0x2353);
    cpu.set_di(0xC8A2);
    cpu.set_ip(0x5DBA);
    cpu.set_flags(0xFC52);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0023A, 0x2F);
    machine.mem_store_byte(0x0023B, 0x90);
    machine.mem_store_byte(0x0023C, 0x90);
    machine.mem_store_byte(0x0023D, 0x90);
    machine.mem_store_byte(0x0023E, 0x90);
    machine.mem_store_byte(0x0023F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8C97);
    EXPECT_EQ(cpu.get_ip(), 0x5DBB);
    EXPECT_FLAGS(0xF492);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0023A), 0x2F);
    EXPECT_EQ(memory.load8(0x0023B), 0x90);
    EXPECT_EQ(memory.load8(0x0023C), 0x90);
    EXPECT_EQ(memory.load8(0x0023D), 0x90);
    EXPECT_EQ(memory.load8(0x0023E), 0x90);
    EXPECT_EQ(memory.load8(0x0023F), 0x90);
}

//
// idiv byte [ss:bp-1FFEh]
//
TEST_F(MachineTest, idiv_byte_ss_bp_1FFEh_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x3354);
    cpu.set_bx(0x26D2);
    cpu.set_cx(0xB7CE);
    cpu.set_dx(0x810B);
    cpu.set_cs(0x5D70);
    cpu.set_ss(0xF1A3);
    cpu.set_ds(0x0C88);
    cpu.set_es(0x2BFA);
    cpu.set_sp(0x0B36);
    cpu.set_bp(0x2D55);
    cpu.set_si(0x8D4B);
    cpu.set_di(0xB13A);
    cpu.set_ip(0xD0CE);
    cpu.set_flags(0xF497);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6A7CE, 0xF6);
    machine.mem_store_byte(0x6A7CF, 0xBE);
    machine.mem_store_byte(0x6A7D0, 0x02);
    machine.mem_store_byte(0x6A7D1, 0xE0);
    machine.mem_store_byte(0x6A7D2, 0x90);
    machine.mem_store_byte(0x6A7D3, 0x90);
    machine.mem_store_byte(0xF2787, 0x9A);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x0B30);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF496);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6A7CE), 0xF6);
    EXPECT_EQ(memory.load8(0x6A7CF), 0xBE);
    EXPECT_EQ(memory.load8(0x6A7D0), 0x02);
    EXPECT_EQ(memory.load8(0x6A7D1), 0xE0);
    EXPECT_EQ(memory.load8(0x6A7D2), 0x90);
    EXPECT_EQ(memory.load8(0x6A7D3), 0x90);
    EXPECT_EQ(memory.load8(0xF2787), 0x9A);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_FLAGS_LO(0xF2564, 0x96);
    EXPECT_FLAGS_HI(0xF2565, 0xF4);
    EXPECT_EQ(memory.load8(0xF2562), 0x70);
    EXPECT_EQ(memory.load8(0xF2563), 0x5D);
    EXPECT_EQ(memory.load8(0xF2560), 0xD2);
    EXPECT_EQ(memory.load8(0xF2561), 0xD0);
}

//
// idiv ch
//
TEST_F(MachineTest, idiv_ch_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x3D4D);
    cpu.set_bx(0xEC40);
    cpu.set_cx(0x86D0);
    cpu.set_dx(0xE83B);
    cpu.set_cs(0xA973);
    cpu.set_ss(0x2EEC);
    cpu.set_ds(0xCB24);
    cpu.set_es(0xFC66);
    cpu.set_sp(0x8D6B);
    cpu.set_bp(0x8FE0);
    cpu.set_si(0x2E63);
    cpu.set_di(0xAD54);
    cpu.set_ip(0xA037);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB3767, 0xF6);
    machine.mem_store_byte(0xB3768, 0xFD);
    machine.mem_store_byte(0xB3769, 0x90);
    machine.mem_store_byte(0xB376A, 0x90);
    machine.mem_store_byte(0xB376B, 0x90);
    machine.mem_store_byte(0x00000, 0x00);
    machine.mem_store_byte(0x00001, 0x04);
    machine.mem_store_byte(0x00002, 0x00);
    machine.mem_store_byte(0x00003, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x0000);
    EXPECT_EQ(cpu.get_sp(), 0x8D65);
    EXPECT_EQ(cpu.get_ip(), 0x0400);
    EXPECT_FLAGS(0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB3767), 0xF6);
    EXPECT_EQ(memory.load8(0xB3768), 0xFD);
    EXPECT_EQ(memory.load8(0xB3769), 0x90);
    EXPECT_EQ(memory.load8(0xB376A), 0x90);
    EXPECT_EQ(memory.load8(0xB376B), 0x90);
    EXPECT_EQ(memory.load8(0x00000), 0x00);
    EXPECT_EQ(memory.load8(0x00001), 0x04);
    EXPECT_EQ(memory.load8(0x00002), 0x00);
    EXPECT_EQ(memory.load8(0x00003), 0x00);
    EXPECT_FLAGS_LO(0x37C29, 0x82);
    EXPECT_FLAGS_HI(0x37C2A, 0xF0);
    EXPECT_EQ(memory.load8(0x37C27), 0x73);
    EXPECT_EQ(memory.load8(0x37C28), 0xA9);
    EXPECT_EQ(memory.load8(0x37C25), 0x39);
    EXPECT_EQ(memory.load8(0x37C26), 0xA0);
}

//
// mov ax, word [ds:AF24h]
//
TEST_F(MachineTest, mov_ax_word_ds_AF24h_batch7)
{
    // Initial CPU State
    cpu.set_ax(0xB885);
    cpu.set_bx(0x5845);
    cpu.set_cx(0x4558);
    cpu.set_dx(0x45C9);
    cpu.set_cs(0xF8A3);
    cpu.set_ss(0xFC95);
    cpu.set_ds(0x00FA);
    cpu.set_es(0x366D);
    cpu.set_sp(0x4C8F);
    cpu.set_bp(0x7329);
    cpu.set_si(0x78A6);
    cpu.set_di(0x17A3);
    cpu.set_ip(0xFFFE);
    cpu.set_flags(0xF087);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x08A2E, 0xA1);
    machine.mem_store_byte(0x08A2F, 0x24);
    machine.mem_store_byte(0xF8A30, 0xAF);
    machine.mem_store_byte(0xF8A31, 0x90);
    machine.mem_store_byte(0xF8A32, 0x90);
    machine.mem_store_byte(0xF8A33, 0x90);
    machine.mem_store_byte(0x0BEC4, 0x5A);
    machine.mem_store_byte(0x0BEC5, 0xF2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xF25A);
    EXPECT_EQ(cpu.get_ip(), 0x0001);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x08A2E), 0xA1);
    EXPECT_EQ(memory.load8(0x08A2F), 0x24);
    EXPECT_EQ(memory.load8(0xF8A30), 0xAF);
    EXPECT_EQ(memory.load8(0xF8A31), 0x90);
    EXPECT_EQ(memory.load8(0xF8A32), 0x90);
    EXPECT_EQ(memory.load8(0xF8A33), 0x90);
    EXPECT_EQ(memory.load8(0x0BEC4), 0x5A);
    EXPECT_EQ(memory.load8(0x0BEC5), 0xF2);
}

//
// mov ax, word [es:FFFFh]
//
TEST_F(MachineTest, mov_ax_word_es_FFFFh_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x53C5);
    cpu.set_bx(0x9102);
    cpu.set_cx(0xF7D2);
    cpu.set_dx(0xB304);
    cpu.set_cs(0x7BCF);
    cpu.set_ss(0xDE5F);
    cpu.set_ds(0x58A7);
    cpu.set_es(0x04EE);
    cpu.set_sp(0x835B);
    cpu.set_bp(0xA5AD);
    cpu.set_si(0xFD7A);
    cpu.set_di(0x63AC);
    cpu.set_ip(0xCEAF);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x88B9F, 0x26);
    machine.mem_store_byte(0x88BA0, 0xA1);
    machine.mem_store_byte(0x88BA1, 0xFF);
    machine.mem_store_byte(0x88BA2, 0xFF);
    machine.mem_store_byte(0x88BA3, 0x90);
    machine.mem_store_byte(0x14EDF, 0x74);
    machine.mem_store_byte(0x04EE0, 0x75);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7574);
    EXPECT_EQ(cpu.get_ip(), 0xCEB3);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x88B9F), 0x26);
    EXPECT_EQ(memory.load8(0x88BA0), 0xA1);
    EXPECT_EQ(memory.load8(0x88BA1), 0xFF);
    EXPECT_EQ(memory.load8(0x88BA2), 0xFF);
    EXPECT_EQ(memory.load8(0x88BA3), 0x90);
    EXPECT_EQ(memory.load8(0x14EDF), 0x74);
    EXPECT_EQ(memory.load8(0x04EE0), 0x75);
}

//
// rcr ah, cl
//
TEST_F(MachineTest, rcr_ah_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0xFD83);
    cpu.set_bx(0x6928);
    cpu.set_cx(0x0A36);
    cpu.set_dx(0xA2DB);
    cpu.set_cs(0xB8BC);
    cpu.set_ss(0xEBD6);
    cpu.set_ds(0x8F48);
    cpu.set_es(0xCDD0);
    cpu.set_sp(0x149B);
    cpu.set_bp(0x28E5);
    cpu.set_si(0x4948);
    cpu.set_di(0xE24B);
    cpu.set_ip(0x3361);
    cpu.set_flags(0xFC16);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBBF21, 0xD2);
    machine.mem_store_byte(0xBBF22, 0xDC);
    machine.mem_store_byte(0xBBF23, 0x90);
    machine.mem_store_byte(0xBBF24, 0x90);
    machine.mem_store_byte(0xBBF25, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3363);
    EXPECT_FLAGS(0xF416);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBBF21), 0xD2);
    EXPECT_EQ(memory.load8(0xBBF22), 0xDC);
    EXPECT_EQ(memory.load8(0xBBF23), 0x90);
    EXPECT_EQ(memory.load8(0xBBF24), 0x90);
    EXPECT_EQ(memory.load8(0xBBF25), 0x90);
}

//
// rcr bx, cl
//
TEST_F(MachineTest, rcr_bx_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0xBD8B);
    cpu.set_bx(0x78A5);
    cpu.set_cx(0x3C22);
    cpu.set_dx(0xE0BB);
    cpu.set_cs(0x033C);
    cpu.set_ss(0x3A46);
    cpu.set_ds(0xE5F3);
    cpu.set_es(0x6652);
    cpu.set_sp(0x5BB7);
    cpu.set_bp(0x658D);
    cpu.set_si(0x06B3);
    cpu.set_di(0xCD33);
    cpu.set_ip(0xD5E3);
    cpu.set_flags(0xF442);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x109A3, 0xD3);
    machine.mem_store_byte(0x109A4, 0xDB);
    machine.mem_store_byte(0x109A5, 0x90);
    machine.mem_store_byte(0x109A6, 0x90);
    machine.mem_store_byte(0x109A7, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xD5E5);
    EXPECT_FLAGS(0xFC42);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x109A3), 0xD3);
    EXPECT_EQ(memory.load8(0x109A4), 0xDB);
    EXPECT_EQ(memory.load8(0x109A5), 0x90);
    EXPECT_EQ(memory.load8(0x109A6), 0x90);
    EXPECT_EQ(memory.load8(0x109A7), 0x90);
}

//
// rcr byte [cs:bp+di+3865h], cl
//
TEST_F(MachineTest, rcr_byte_cs_bp_di_3865h_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0xF075);
    cpu.set_bx(0xCA4D);
    cpu.set_cx(0xB724);
    cpu.set_dx(0x67A8);
    cpu.set_cs(0xAD98);
    cpu.set_ss(0x5F40);
    cpu.set_ds(0x87AE);
    cpu.set_es(0xB6F0);
    cpu.set_sp(0x5F74);
    cpu.set_bp(0x0000);
    cpu.set_si(0x1083);
    cpu.set_di(0x1BE7);
    cpu.set_ip(0x374A);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB10CA, 0x2E);
    machine.mem_store_byte(0xB10CB, 0xD2);
    machine.mem_store_byte(0xB10CC, 0x9B);
    machine.mem_store_byte(0xB10CD, 0x65);
    machine.mem_store_byte(0xB10CE, 0x38);
    machine.mem_store_byte(0xB10CF, 0x90);
    machine.mem_store_byte(0xB2DCC, 0xFF);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x374F);
    EXPECT_FLAGS(0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB10CA), 0x2E);
    EXPECT_EQ(memory.load8(0xB10CB), 0xD2);
    EXPECT_EQ(memory.load8(0xB10CC), 0x9B);
    EXPECT_EQ(memory.load8(0xB10CD), 0x65);
    EXPECT_EQ(memory.load8(0xB10CE), 0x38);
    EXPECT_EQ(memory.load8(0xB10CF), 0x90);
    EXPECT_EQ(memory.load8(0xB2DCC), 0xFF);
}

//
// rcr byte [ds:bp+6Fh], cl
//
TEST_F(MachineTest, rcr_byte_ds_bp_6Fh_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x9A03);
    cpu.set_bx(0xF66C);
    cpu.set_cx(0xE712);
    cpu.set_dx(0x5605);
    cpu.set_cs(0x0A74);
    cpu.set_ss(0x4FC9);
    cpu.set_ds(0x6640);
    cpu.set_es(0x2B43);
    cpu.set_sp(0x995A);
    cpu.set_bp(0x79C2);
    cpu.set_si(0x704B);
    cpu.set_di(0x0000);
    cpu.set_ip(0x6FD5);
    cpu.set_flags(0xF806);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x11715, 0x3E);
    machine.mem_store_byte(0x11716, 0xD2);
    machine.mem_store_byte(0x11717, 0x5E);
    machine.mem_store_byte(0x11718, 0x6F);
    machine.mem_store_byte(0x11719, 0x90);
    machine.mem_store_byte(0x6DE31, 0xEA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6FD9);
    EXPECT_FLAGS(0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x11715), 0x3E);
    EXPECT_EQ(memory.load8(0x11716), 0xD2);
    EXPECT_EQ(memory.load8(0x11717), 0x5E);
    EXPECT_EQ(memory.load8(0x11718), 0x6F);
    EXPECT_EQ(memory.load8(0x11719), 0x90);
    EXPECT_EQ(memory.load8(0x6DE31), 0xEA);
}

//
// rcr byte [es:bx+si-630Fh], cl
//
TEST_F(MachineTest, rcr_byte_es_bx_si_630Fh_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0xBDAC);
    cpu.set_bx(0x9613);
    cpu.set_cx(0xF536);
    cpu.set_dx(0xCAF3);
    cpu.set_cs(0xF9D8);
    cpu.set_ss(0xC2CC);
    cpu.set_ds(0x7E2B);
    cpu.set_es(0xF68D);
    cpu.set_sp(0xE92C);
    cpu.set_bp(0x9507);
    cpu.set_si(0xA5DB);
    cpu.set_di(0x08BB);
    cpu.set_ip(0xE77D);
    cpu.set_flags(0xFC03);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x084FD, 0x26);
    machine.mem_store_byte(0x084FE, 0xD2);
    machine.mem_store_byte(0x084FF, 0x98);
    machine.mem_store_byte(0x08500, 0xF1);
    machine.mem_store_byte(0x08501, 0x9C);
    machine.mem_store_byte(0x041AF, 0x0D);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE782);
    EXPECT_FLAGS(0xF403);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x084FD), 0x26);
    EXPECT_EQ(memory.load8(0x084FE), 0xD2);
    EXPECT_EQ(memory.load8(0x084FF), 0x98);
    EXPECT_EQ(memory.load8(0x08500), 0xF1);
    EXPECT_EQ(memory.load8(0x08501), 0x9C);
    EXPECT_EQ(memory.load8(0x041AF), 0x0D);
}

//
// rcr byte [ss:si-66h], cl
//
TEST_F(MachineTest, rcr_byte_ss_si_66h_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x7C77);
    cpu.set_bx(0x43E7);
    cpu.set_cx(0x2236);
    cpu.set_dx(0x3671);
    cpu.set_cs(0x6BD5);
    cpu.set_ss(0x67F7);
    cpu.set_ds(0xDA8B);
    cpu.set_es(0xC537);
    cpu.set_sp(0x467E);
    cpu.set_bp(0xCF0A);
    cpu.set_si(0x011D);
    cpu.set_di(0x4845);
    cpu.set_ip(0x8A7F);
    cpu.set_flags(0xF046);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x747CF, 0x36);
    machine.mem_store_byte(0x747D0, 0xD2);
    machine.mem_store_byte(0x747D1, 0x5C);
    machine.mem_store_byte(0x747D2, 0x9A);
    machine.mem_store_byte(0x747D3, 0x90);
    machine.mem_store_byte(0x68027, 0x4B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8A83);
    EXPECT_FLAGS(0xF846);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x747CF), 0x36);
    EXPECT_EQ(memory.load8(0x747D0), 0xD2);
    EXPECT_EQ(memory.load8(0x747D1), 0x5C);
    EXPECT_EQ(memory.load8(0x747D2), 0x9A);
    EXPECT_EQ(memory.load8(0x747D3), 0x90);
    EXPECT_EQ(memory.load8(0x68027), 0x4B);
}

//
// rcr cl, cl
//
TEST_F(MachineTest, rcr_cl_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x49EE);
    cpu.set_bx(0x75B4);
    cpu.set_cx(0x2036);
    cpu.set_dx(0xDE91);
    cpu.set_cs(0x1208);
    cpu.set_ss(0x0AA9);
    cpu.set_ds(0xE496);
    cpu.set_es(0xB4D1);
    cpu.set_sp(0x6426);
    cpu.set_bp(0x2AF2);
    cpu.set_si(0xFCB5);
    cpu.set_di(0xFA3C);
    cpu.set_ip(0xA9E2);
    cpu.set_flags(0xF887);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1CA62, 0x36);
    machine.mem_store_byte(0x1CA63, 0xD2);
    machine.mem_store_byte(0x1CA64, 0xD9);
    machine.mem_store_byte(0x1CA65, 0x90);
    machine.mem_store_byte(0x1CA66, 0x90);
    machine.mem_store_byte(0x1CA67, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA9E5);
    EXPECT_FLAGS(0xF087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1CA62), 0x36);
    EXPECT_EQ(memory.load8(0x1CA63), 0xD2);
    EXPECT_EQ(memory.load8(0x1CA64), 0xD9);
    EXPECT_EQ(memory.load8(0x1CA65), 0x90);
    EXPECT_EQ(memory.load8(0x1CA66), 0x90);
    EXPECT_EQ(memory.load8(0x1CA67), 0x90);
}

//
// rcr sp, cl
//
TEST_F(MachineTest, rcr_sp_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0xFF55);
    cpu.set_bx(0xEFF7);
    cpu.set_cx(0xDB22);
    cpu.set_dx(0x92CC);
    cpu.set_cs(0x2F23);
    cpu.set_ss(0x44EA);
    cpu.set_ds(0x029B);
    cpu.set_es(0xCF64);
    cpu.set_sp(0xAA24);
    cpu.set_bp(0x5738);
    cpu.set_si(0x634F);
    cpu.set_di(0x0000);
    cpu.set_ip(0xCB43);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3BD73, 0xD3);
    machine.mem_store_byte(0x3BD74, 0xDC);
    machine.mem_store_byte(0x3BD75, 0x90);
    machine.mem_store_byte(0x3BD76, 0x90);
    machine.mem_store_byte(0x3BD77, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCB45);
    EXPECT_FLAGS(0xF857);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3BD73), 0xD3);
    EXPECT_EQ(memory.load8(0x3BD74), 0xDC);
    EXPECT_EQ(memory.load8(0x3BD75), 0x90);
    EXPECT_EQ(memory.load8(0x3BD76), 0x90);
    EXPECT_EQ(memory.load8(0x3BD77), 0x90);
}

//
// rcr word [cs:bp+9h], cl
//
TEST_F(MachineTest, rcr_word_cs_bp_9h_cl_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x961D);
    cpu.set_bx(0xADFA);
    cpu.set_cx(0xF022);
    cpu.set_dx(0xBA0C);
    cpu.set_cs(0x54F9);
    cpu.set_ss(0x2BE7);
    cpu.set_ds(0x2961);
    cpu.set_es(0x5D86);
    cpu.set_sp(0x65EB);
    cpu.set_bp(0xBAB2);
    cpu.set_si(0x436A);
    cpu.set_di(0xF5E9);
    cpu.set_ip(0x93F2);
    cpu.set_flags(0xFCD6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5E382, 0x2E);
    machine.mem_store_byte(0x5E383, 0xD3);
    machine.mem_store_byte(0x5E384, 0x5E);
    machine.mem_store_byte(0x5E385, 0x09);
    machine.mem_store_byte(0x5E386, 0x90);
    machine.mem_store_byte(0x5E387, 0x90);
    machine.mem_store_byte(0x60A4B, 0x6E);
    machine.mem_store_byte(0x60A4C, 0xCB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x93F6);
    EXPECT_FLAGS(0xF4D6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5E382), 0x2E);
    EXPECT_EQ(memory.load8(0x5E383), 0xD3);
    EXPECT_EQ(memory.load8(0x5E384), 0x5E);
    EXPECT_EQ(memory.load8(0x5E385), 0x09);
    EXPECT_EQ(memory.load8(0x5E386), 0x90);
    EXPECT_EQ(memory.load8(0x5E387), 0x90);
    EXPECT_EQ(memory.load8(0x60A4B), 0x6E);
    EXPECT_EQ(memory.load8(0x60A4C), 0xCB);
}

//
// retn 97EDh
//
TEST_F(MachineTest, retn_97EDh_batch7)
{
    // Initial CPU State
    cpu.set_ax(0x61FB);
    cpu.set_bx(0x9C12);
    cpu.set_cx(0xD252);
    cpu.set_dx(0x9ED0);
    cpu.set_cs(0x0006);
    cpu.set_ss(0x594B);
    cpu.set_ds(0x65B5);
    cpu.set_es(0x3AFF);
    cpu.set_sp(0xEFEA);
    cpu.set_bp(0x1D9C);
    cpu.set_si(0x342A);
    cpu.set_di(0x6C98);
    cpu.set_ip(0xFFFE);
    cpu.set_flags(0xF496);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1005E, 0xC2);
    machine.mem_store_byte(0x1005F, 0xED);
    machine.mem_store_byte(0x00060, 0x97);
    machine.mem_store_byte(0x00061, 0x90);
    machine.mem_store_byte(0x00062, 0x90);
    machine.mem_store_byte(0x00063, 0x90);
    machine.mem_store_byte(0x6849A, 0x3C);
    machine.mem_store_byte(0x6849B, 0x4C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0x87D9);
    EXPECT_EQ(cpu.get_ip(), 0x4C3C);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1005E), 0xC2);
    EXPECT_EQ(memory.load8(0x1005F), 0xED);
    EXPECT_EQ(memory.load8(0x00060), 0x97);
    EXPECT_EQ(memory.load8(0x00061), 0x90);
    EXPECT_EQ(memory.load8(0x00062), 0x90);
    EXPECT_EQ(memory.load8(0x00063), 0x90);
    EXPECT_EQ(memory.load8(0x6849A), 0x3C);
    EXPECT_EQ(memory.load8(0x6849B), 0x4C);
}
