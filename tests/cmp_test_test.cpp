#include "fixture.h"

//
// cmp al, FCh
//
TEST_F(MachineTest, cmp_al_FCh)
{
    // Initial CPU State
    cpu.set_ax(0xD2F3);
    cpu.set_bx(0x0FC9);
    cpu.set_cx(0x97FA);
    cpu.set_dx(0x7BF7);
    cpu.set_cs(0xEE70);
    cpu.set_ss(0xAD3E);
    cpu.set_ds(0x2B3A);
    cpu.set_es(0x0DF9);
    cpu.set_sp(0xF7A1);
    cpu.set_bp(0x75BD);
    cpu.set_si(0xD199);
    cpu.set_di(0xB77B);
    cpu.set_ip(0x3821);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF1F21, 0x3C);
    machine.mem_store_byte(0xF1F22, 0xFC);
    machine.mem_store_byte(0xF1F23, 0x90);
    machine.mem_store_byte(0xF1F24, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3823);
    EXPECT_EQ(cpu.get_flags(), 0xF493);

    // Final RAM entries
}

//
// cmp ax, 4B15h
//
TEST_F(MachineTest, cmp_ax_4B15h)
{
    // Initial CPU State
    cpu.set_ax(0xC8B7);
    cpu.set_bx(0x2DBE);
    cpu.set_cx(0x769C);
    cpu.set_dx(0xC5AA);
    cpu.set_cs(0x1716);
    cpu.set_ss(0x55EE);
    cpu.set_ds(0x163B);
    cpu.set_es(0xA59C);
    cpu.set_sp(0x7169);
    cpu.set_bp(0x7F4F);
    cpu.set_si(0xFA49);
    cpu.set_di(0x5137);
    cpu.set_ip(0xBCF2);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x22E52, 0x36);
    machine.mem_store_byte(0x22E53, 0x3D);
    machine.mem_store_byte(0x22E54, 0x15);
    machine.mem_store_byte(0x22E55, 0x4B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBCF6);
    EXPECT_EQ(cpu.get_flags(), 0xFC02);

    // Final RAM entries
}

//
// cmp bx, word [ds:di]
//
TEST_F(MachineTest, cmp_bx_word_ds_di)
{
    // Initial CPU State
    cpu.set_ax(0xA3C2);
    cpu.set_bx(0x7E8A);
    cpu.set_cx(0xFAAE);
    cpu.set_dx(0x8DE6);
    cpu.set_cs(0xBC5B);
    cpu.set_ss(0xE1FE);
    cpu.set_ds(0x06C6);
    cpu.set_es(0x481D);
    cpu.set_sp(0x9BAB);
    cpu.set_bp(0x1D8D);
    cpu.set_si(0xF0FD);
    cpu.set_di(0x68B8);
    cpu.set_ip(0x9D88);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC6338, 0x3E);
    machine.mem_store_byte(0xC6339, 0x3B);
    machine.mem_store_byte(0xC633A, 0x1D);
    machine.mem_store_byte(0xC633B, 0x90);
    machine.mem_store_byte(0x0D518, 0x09);
    machine.mem_store_byte(0x0D519, 0x9B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9D8B);
    EXPECT_EQ(cpu.get_flags(), 0xFC87);

    // Final RAM entries
}

//
// cmp byte [ds:bx+si], 20h
//
TEST_F(MachineTest, cmp_byte_ds_bx_si_20h)
{
    // Initial CPU State
    cpu.set_ax(0x4CA7);
    cpu.set_bx(0x47FF);
    cpu.set_cx(0xD328);
    cpu.set_dx(0xAA0F);
    cpu.set_cs(0x8D73);
    cpu.set_ss(0x8FC0);
    cpu.set_ds(0xCF7F);
    cpu.set_es(0xF3FF);
    cpu.set_sp(0x7244);
    cpu.set_bp(0xFB0C);
    cpu.set_si(0x4463);
    cpu.set_di(0xDEBF);
    cpu.set_ip(0x1F5A);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8F68A, 0x82);
    machine.mem_store_byte(0x8F68B, 0x38);
    machine.mem_store_byte(0x8F68C, 0x20);
    machine.mem_store_byte(0x8F68D, 0x90);
    machine.mem_store_byte(0xD8452, 0x7B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1F5D);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// cmp byte [ss:bp+di+709h], E0h
//
TEST_F(MachineTest, cmp_byte_ss_bp_di_709h_E0h)
{
    // Initial CPU State
    cpu.set_ax(0x7641);
    cpu.set_bx(0x020F);
    cpu.set_cx(0x4BB6);
    cpu.set_dx(0x7AC0);
    cpu.set_cs(0x9BAB);
    cpu.set_ss(0xB363);
    cpu.set_ds(0x697C);
    cpu.set_es(0xC388);
    cpu.set_sp(0xE6B0);
    cpu.set_bp(0x2DC7);
    cpu.set_si(0x3E03);
    cpu.set_di(0x968B);
    cpu.set_ip(0x1597);
    cpu.set_flags(0xF4D6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9D047, 0x80);
    machine.mem_store_byte(0x9D048, 0xBB);
    machine.mem_store_byte(0x9D049, 0x09);
    machine.mem_store_byte(0x9D04A, 0x07);
    machine.mem_store_byte(0x9D04B, 0xE0);
    machine.mem_store_byte(0xC018B, 0xFE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x159C);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
}

//
// cmp byte [ss:bp+si], cl
//
TEST_F(MachineTest, cmp_byte_ss_bp_si_cl)
{
    // Initial CPU State
    cpu.set_ax(0x611E);
    cpu.set_bx(0x4C17);
    cpu.set_cx(0xB8D4);
    cpu.set_dx(0xE0E6);
    cpu.set_cs(0x1721);
    cpu.set_ss(0xFE8D);
    cpu.set_ds(0x5E40);
    cpu.set_es(0x065D);
    cpu.set_sp(0xD04B);
    cpu.set_bp(0x31CE);
    cpu.set_si(0x2C9F);
    cpu.set_di(0x5FA6);
    cpu.set_ip(0x105C);
    cpu.set_flags(0xFC87);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1826C, 0x38);
    machine.mem_store_byte(0x1826D, 0x0A);
    machine.mem_store_byte(0x1826E, 0x90);
    machine.mem_store_byte(0x1826F, 0x90);
    machine.mem_store_byte(0x0473D, 0x33);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x105E);
    EXPECT_EQ(cpu.get_flags(), 0xF417);

    // Final RAM entries
}

//
// cmp ch, byte [ds:bx+si]
//
TEST_F(MachineTest, cmp_ch_byte_ds_bx_si)
{
    // Initial CPU State
    cpu.set_ax(0x8D04);
    cpu.set_bx(0x8178);
    cpu.set_cx(0x6C06);
    cpu.set_dx(0x98A9);
    cpu.set_cs(0x5208);
    cpu.set_ss(0x849E);
    cpu.set_ds(0x5909);
    cpu.set_es(0x3005);
    cpu.set_sp(0xC0B6);
    cpu.set_bp(0xC225);
    cpu.set_si(0xFF7E);
    cpu.set_di(0x6EB3);
    cpu.set_ip(0x237D);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x543FD, 0x3A);
    machine.mem_store_byte(0x543FE, 0x28);
    machine.mem_store_byte(0x543FF, 0x90);
    machine.mem_store_byte(0x54400, 0x90);
    machine.mem_store_byte(0x61186, 0xC2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x237F);
    EXPECT_EQ(cpu.get_flags(), 0xF887);

    // Final RAM entries
}

//
// cmp si, FFA1h
//
TEST_F(MachineTest, cmp_si_FFA1h)
{
    // Initial CPU State
    cpu.set_ax(0xC30D);
    cpu.set_bx(0xE3AE);
    cpu.set_cx(0x827E);
    cpu.set_dx(0x093A);
    cpu.set_cs(0xC8C6);
    cpu.set_ss(0x29E2);
    cpu.set_ds(0x009C);
    cpu.set_es(0x0DDD);
    cpu.set_sp(0xAD31);
    cpu.set_bp(0x8548);
    cpu.set_si(0x63B5);
    cpu.set_di(0xF74D);
    cpu.set_ip(0xA0C8);
    cpu.set_flags(0xF803);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD2D28, 0x83);
    machine.mem_store_byte(0xD2D29, 0xFE);
    machine.mem_store_byte(0xD2D2A, 0xA1);
    machine.mem_store_byte(0xD2D2B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA0CB);
    EXPECT_EQ(cpu.get_flags(), 0xF007);

    // Final RAM entries
}

//
// cmp word [ds:di+6C25h], sp
//
TEST_F(MachineTest, cmp_word_ds_di_6C25h_sp)
{
    // Initial CPU State
    cpu.set_ax(0xC272);
    cpu.set_bx(0xC51B);
    cpu.set_cx(0x049C);
    cpu.set_dx(0xD5B1);
    cpu.set_cs(0xB8F7);
    cpu.set_ss(0xC6D6);
    cpu.set_ds(0x139C);
    cpu.set_es(0x8E95);
    cpu.set_sp(0xF39C);
    cpu.set_bp(0xF6D3);
    cpu.set_si(0x90FB);
    cpu.set_di(0xF131);
    cpu.set_ip(0x6F0B);
    cpu.set_flags(0xFCC7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBFE7B, 0x39);
    machine.mem_store_byte(0xBFE7C, 0xA5);
    machine.mem_store_byte(0xBFE7D, 0x25);
    machine.mem_store_byte(0xBFE7E, 0x6C);
    machine.mem_store_byte(0x19716, 0x7B);
    machine.mem_store_byte(0x19717, 0xAE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6F0F);
    EXPECT_EQ(cpu.get_flags(), 0xF493);

    // Final RAM entries
}

//
// cmp word [es:si-3322h], 41FBh
//
TEST_F(MachineTest, cmp_word_es_si_3322h_41FBh)
{
    // Initial CPU State
    cpu.set_ax(0xF8E5);
    cpu.set_bx(0x5BFD);
    cpu.set_cx(0x1B34);
    cpu.set_dx(0xD5EA);
    cpu.set_cs(0xDBF3);
    cpu.set_ss(0xE544);
    cpu.set_ds(0x2CA9);
    cpu.set_es(0xD1A2);
    cpu.set_sp(0xAE62);
    cpu.set_bp(0x0987);
    cpu.set_si(0xF05F);
    cpu.set_di(0x4300);
    cpu.set_ip(0xFCB1);
    cpu.set_flags(0xF096);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEBBE1, 0x26);
    machine.mem_store_byte(0xEBBE2, 0x81);
    machine.mem_store_byte(0xEBBE3, 0xBC);
    machine.mem_store_byte(0xEBBE4, 0xDE);
    machine.mem_store_byte(0xEBBE5, 0xCC);
    machine.mem_store_byte(0xEBBE6, 0xFB);
    machine.mem_store_byte(0xEBBE7, 0x41);
    machine.mem_store_byte(0xDD75D, 0x9B);
    machine.mem_store_byte(0xDD75E, 0xD2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xFCB8);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// test al, 4Bh
//
TEST_F(MachineTest, test_al_4Bh)
{
    // Initial CPU State
    cpu.set_ax(0x52A1);
    cpu.set_bx(0xE724);
    cpu.set_cx(0x81C8);
    cpu.set_dx(0xF0F7);
    cpu.set_cs(0x31ED);
    cpu.set_ss(0x1D03);
    cpu.set_ds(0x0258);
    cpu.set_es(0xCCC3);
    cpu.set_sp(0xBF76);
    cpu.set_bp(0x2608);
    cpu.set_si(0xCB21);
    cpu.set_di(0x2729);
    cpu.set_ip(0x02B6);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x32186, 0xA8);
    machine.mem_store_byte(0x32187, 0x4B);
    machine.mem_store_byte(0x32188, 0x90);
    machine.mem_store_byte(0x32189, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x02B8);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// test ax, 5FE2h
//
TEST_F(MachineTest, test_ax_5FE2h)
{
    // Initial CPU State
    cpu.set_ax(0x634C);
    cpu.set_bx(0xD4B7);
    cpu.set_cx(0x3A92);
    cpu.set_dx(0x9001);
    cpu.set_cs(0xA070);
    cpu.set_ss(0xFBF1);
    cpu.set_ds(0xBD4A);
    cpu.set_es(0xA238);
    cpu.set_sp(0xE657);
    cpu.set_bp(0xA49C);
    cpu.set_si(0x9BC4);
    cpu.set_di(0xB7E7);
    cpu.set_ip(0x94E2);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA9BE2, 0xA9);
    machine.mem_store_byte(0xA9BE3, 0xE2);
    machine.mem_store_byte(0xA9BE4, 0x5F);
    machine.mem_store_byte(0xA9BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x94E5);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// test byte [es:bp+57E0h], 7h
//
TEST_F(MachineTest, test_byte_es_bp_57E0h_7h)
{
    // Initial CPU State
    cpu.set_ax(0x095E);
    cpu.set_bx(0xF020);
    cpu.set_cx(0x804C);
    cpu.set_dx(0x966F);
    cpu.set_cs(0xD7F5);
    cpu.set_ss(0x7D3A);
    cpu.set_ds(0xDAC1);
    cpu.set_es(0xF84F);
    cpu.set_sp(0xA6B7);
    cpu.set_bp(0x5B97);
    cpu.set_si(0xDCA1);
    cpu.set_di(0xD9BB);
    cpu.set_ip(0x1BCB);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD9B1B, 0x26);
    machine.mem_store_byte(0xD9B1C, 0xF6);
    machine.mem_store_byte(0xD9B1D, 0x86);
    machine.mem_store_byte(0xD9B1E, 0xE0);
    machine.mem_store_byte(0xD9B1F, 0x57);
    machine.mem_store_byte(0xD9B20, 0x07);
    machine.mem_store_byte(0x03867, 0x59);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x1BD1);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
}

//
// test byte [ss:bx+si-27h], 96h
//
TEST_F(MachineTest, test_byte_ss_bx_si_27h_96h)
{
    // Initial CPU State
    cpu.set_ax(0xCEA7);
    cpu.set_bx(0xA980);
    cpu.set_cx(0xF5E4);
    cpu.set_dx(0x1181);
    cpu.set_cs(0x8C32);
    cpu.set_ss(0x3B31);
    cpu.set_ds(0x1176);
    cpu.set_es(0x2EAE);
    cpu.set_sp(0x7785);
    cpu.set_bp(0x2699);
    cpu.set_si(0x426A);
    cpu.set_di(0x9D96);
    cpu.set_ip(0xB504);
    cpu.set_flags(0xF087);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97824, 0x36);
    machine.mem_store_byte(0x97825, 0xF6);
    machine.mem_store_byte(0x97826, 0x48);
    machine.mem_store_byte(0x97827, 0xD9);
    machine.mem_store_byte(0x97828, 0x96);
    machine.mem_store_byte(0x49ED3, 0x82);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB509);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// test dl, dh
//
TEST_F(MachineTest, test_dl_dh)
{
    // Initial CPU State
    cpu.set_ax(0x0767);
    cpu.set_bx(0x553E);
    cpu.set_cx(0xA332);
    cpu.set_dx(0xE757);
    cpu.set_cs(0xA4AD);
    cpu.set_ss(0xD5B2);
    cpu.set_ds(0xD79C);
    cpu.set_es(0x2C23);
    cpu.set_sp(0x5C7A);
    cpu.set_bp(0x8BE8);
    cpu.set_si(0x8550);
    cpu.set_di(0xF10E);
    cpu.set_ip(0x6F8D);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xABA5D, 0x84);
    machine.mem_store_byte(0xABA5E, 0xF2);
    machine.mem_store_byte(0xABA5F, 0x90);
    machine.mem_store_byte(0xABA60, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6F8F);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
}

//
// test word [ds:bx+1Ah], bx
//
TEST_F(MachineTest, test_word_ds_bx_1Ah_bx)
{
    // Initial CPU State
    cpu.set_ax(0x536E);
    cpu.set_bx(0xA5C4);
    cpu.set_cx(0xD716);
    cpu.set_dx(0xE524);
    cpu.set_cs(0x89C2);
    cpu.set_ss(0x13EC);
    cpu.set_ds(0x0F64);
    cpu.set_es(0x1CCF);
    cpu.set_sp(0x81A6);
    cpu.set_bp(0xDE14);
    cpu.set_si(0x2C73);
    cpu.set_di(0xA840);
    cpu.set_ip(0x4494);
    cpu.set_flags(0xF002);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8E0B4, 0x85);
    machine.mem_store_byte(0x8E0B5, 0x5F);
    machine.mem_store_byte(0x8E0B6, 0x1A);
    machine.mem_store_byte(0x8E0B7, 0x90);
    machine.mem_store_byte(0x19C1E, 0x5D);
    machine.mem_store_byte(0x19C1F, 0xDB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4497);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
}

//
// test word [ds:bx+38h], FDEAh
//
TEST_F(MachineTest, test_word_ds_bx_38h_FDEAh)
{
    // Initial CPU State
    cpu.set_ax(0x388F);
    cpu.set_bx(0x48C7);
    cpu.set_cx(0xCE3C);
    cpu.set_dx(0x0778);
    cpu.set_cs(0x1B74);
    cpu.set_ss(0xF429);
    cpu.set_ds(0xC61B);
    cpu.set_es(0x2D13);
    cpu.set_sp(0x645E);
    cpu.set_bp(0x38DF);
    cpu.set_si(0x7B80);
    cpu.set_di(0x3295);
    cpu.set_ip(0xC594);
    cpu.set_flags(0xFC96);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x27CD4, 0x3E);
    machine.mem_store_byte(0x27CD5, 0xF7);
    machine.mem_store_byte(0x27CD6, 0x47);
    machine.mem_store_byte(0x27CD7, 0x38);
    machine.mem_store_byte(0x27CD8, 0xEA);
    machine.mem_store_byte(0x27CD9, 0xFD);
    machine.mem_store_byte(0xCAAAF, 0xD6);
    machine.mem_store_byte(0xCAAB0, 0x17);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC59A);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// test word [es:bp+si+35h], FE07h
//
TEST_F(MachineTest, test_word_es_bp_si_35h_FE07h)
{
    // Initial CPU State
    cpu.set_ax(0x05B2);
    cpu.set_bx(0x4C75);
    cpu.set_cx(0xBA84);
    cpu.set_dx(0xDA92);
    cpu.set_cs(0xB14A);
    cpu.set_ss(0x80AF);
    cpu.set_ds(0x8AFD);
    cpu.set_es(0x60B4);
    cpu.set_sp(0x3F64);
    cpu.set_bp(0x5479);
    cpu.set_si(0x8A92);
    cpu.set_di(0x0FCD);
    cpu.set_ip(0x3073);
    cpu.set_flags(0xF413);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB4513, 0x26);
    machine.mem_store_byte(0xB4514, 0xF7);
    machine.mem_store_byte(0xB4515, 0x4A);
    machine.mem_store_byte(0xB4516, 0x35);
    machine.mem_store_byte(0xB4517, 0x07);
    machine.mem_store_byte(0xB4518, 0xFE);
    machine.mem_store_byte(0x6EA80, 0x11);
    machine.mem_store_byte(0x6EA81, 0xD8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3079);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
}
