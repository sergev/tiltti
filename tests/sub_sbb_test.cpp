#include "fixture.h"

//
// sbb al, E3h
//
TEST_F(MachineTest, sbb_al_E3h)
{
    // Initial CPU State
    cpu.set_ax(0x172D);
    cpu.set_bx(0x98D3);
    cpu.set_cx(0x38A8);
    cpu.set_dx(0xE64C);
    cpu.set_cs(0xE32C);
    cpu.set_ss(0x47C2);
    cpu.set_ds(0x4B98);
    cpu.set_es(0x74A1);
    cpu.set_sp(0x5D8C);
    cpu.set_bp(0x1DFE);
    cpu.set_si(0x0450);
    cpu.set_di(0x5FF3);
    cpu.set_ip(0x0FE9);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xE42A9, 0x1C);
    machine.mem_store_byte(0xE42AA, 0xE3);
    machine.mem_store_byte(0xE42AB, 0x90);
    machine.mem_store_byte(0xE42AC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1749);
    EXPECT_EQ(cpu.get_ip(), 0x0FEB);
    EXPECT_EQ(cpu.get_flags(), 0xF003);

    // Final RAM entries
}

//
// sbb ax, D3A9h
//
TEST_F(MachineTest, sbb_ax_D3A9h)
{
    // Initial CPU State
    cpu.set_ax(0xC6B7);
    cpu.set_bx(0x8D86);
    cpu.set_cx(0x864C);
    cpu.set_dx(0x7100);
    cpu.set_cs(0x4813);
    cpu.set_ss(0x6E0B);
    cpu.set_ds(0x1452);
    cpu.set_es(0x0E85);
    cpu.set_sp(0x8D8B);
    cpu.set_bp(0x2CCD);
    cpu.set_si(0xCB20);
    cpu.set_di(0x2B11);
    cpu.set_ip(0xEAB2);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x56BE2, 0x1D);
    machine.mem_store_byte(0x56BE3, 0xA9);
    machine.mem_store_byte(0x56BE4, 0xD3);
    machine.mem_store_byte(0x56BE5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xF30E);
    EXPECT_EQ(cpu.get_ip(), 0xEAB5);
    EXPECT_EQ(cpu.get_flags(), 0xF493);

    // Final RAM entries
}

//
// sbb bh, byte [ds:58C2h]
//
TEST_F(MachineTest, sbb_bh_byte_ds_58C2h)
{
    // Initial CPU State
    cpu.set_ax(0xF488);
    cpu.set_bx(0x01EC);
    cpu.set_cx(0xDD68);
    cpu.set_dx(0x8B70);
    cpu.set_cs(0xD588);
    cpu.set_ss(0x500F);
    cpu.set_ds(0x82CF);
    cpu.set_es(0x7A86);
    cpu.set_sp(0x38EA);
    cpu.set_bp(0x0A9B);
    cpu.set_si(0x6C3A);
    cpu.set_di(0x0504);
    cpu.set_ip(0x5D63);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDB5E3, 0x1A);
    machine.mem_store_byte(0xDB5E4, 0x3E);
    machine.mem_store_byte(0xDB5E5, 0xC2);
    machine.mem_store_byte(0xDB5E6, 0x58);
    machine.mem_store_byte(0x885B2, 0x24);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xDDEC);
    EXPECT_EQ(cpu.get_ip(), 0x5D67);
    EXPECT_EQ(cpu.get_flags(), 0xF097);

    // Final RAM entries
}

//
// sbb byte [ds:bx+65h], cl
//
TEST_F(MachineTest, sbb_byte_ds_bx_65h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC70E);
    cpu.set_bx(0x8F8B);
    cpu.set_cx(0x4B9E);
    cpu.set_dx(0x657F);
    cpu.set_cs(0x2140);
    cpu.set_ss(0xC178);
    cpu.set_ds(0xF4F8);
    cpu.set_es(0x184D);
    cpu.set_sp(0x0114);
    cpu.set_bp(0xBFCD);
    cpu.set_si(0x169F);
    cpu.set_di(0x105A);
    cpu.set_ip(0xA1DE);
    cpu.set_flags(0xF892);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2B5DE, 0x18);
    machine.mem_store_byte(0x2B5DF, 0x4F);
    machine.mem_store_byte(0x2B5E0, 0x65);
    machine.mem_store_byte(0x2B5E1, 0x90);
    machine.mem_store_byte(0xFDF70, 0x14);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA1E1);
    EXPECT_EQ(cpu.get_flags(), 0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFDF70), 0x76);
}

//
// sbb byte [ss:si-53h], E1h
//
TEST_F(MachineTest, sbb_byte_ss_si_53h_E1h)
{
    // Initial CPU State
    cpu.set_ax(0xF6AF);
    cpu.set_bx(0x099C);
    cpu.set_cx(0x53EE);
    cpu.set_dx(0x242B);
    cpu.set_cs(0xCC14);
    cpu.set_ss(0xD1FD);
    cpu.set_ds(0xE841);
    cpu.set_es(0xB782);
    cpu.set_sp(0x037D);
    cpu.set_bp(0xC157);
    cpu.set_si(0xC7D0);
    cpu.set_di(0x0346);
    cpu.set_ip(0xEE41);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDAF81, 0x36);
    machine.mem_store_byte(0xDAF82, 0x82);
    machine.mem_store_byte(0xDAF83, 0x5C);
    machine.mem_store_byte(0xDAF84, 0xAD);
    machine.mem_store_byte(0xDAF85, 0xE1);
    machine.mem_store_byte(0xDE74D, 0xBE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEE46);
    EXPECT_EQ(cpu.get_flags(), 0xF087);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDE74D), 0xDD);
}

//
// sbb dh, ABh
//
TEST_F(MachineTest, sbb_dh_ABh)
{
    // Initial CPU State
    cpu.set_ax(0xA5D3);
    cpu.set_bx(0x0C03);
    cpu.set_cx(0xDA7A);
    cpu.set_dx(0xE2B8);
    cpu.set_cs(0x2279);
    cpu.set_ss(0x8774);
    cpu.set_ds(0x8F39);
    cpu.set_es(0x7972);
    cpu.set_sp(0xE526);
    cpu.set_bp(0x6DD7);
    cpu.set_si(0x67EA);
    cpu.set_di(0x1761);
    cpu.set_ip(0x1795);
    cpu.set_flags(0xF802);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x23F25, 0x80);
    machine.mem_store_byte(0x23F26, 0xDE);
    machine.mem_store_byte(0x23F27, 0xAB);
    machine.mem_store_byte(0x23F28, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x37B8);
    EXPECT_EQ(cpu.get_ip(), 0x1798);
    EXPECT_EQ(cpu.get_flags(), 0xF012);

    // Final RAM entries
}

//
// sbb dx, word [ds:bp+di-59h]
//
TEST_F(MachineTest, sbb_dx_word_ds_bp_di_59h)
{
    // Initial CPU State
    cpu.set_ax(0x1922);
    cpu.set_bx(0xA557);
    cpu.set_cx(0x10F2);
    cpu.set_dx(0x2C2F);
    cpu.set_cs(0xF641);
    cpu.set_ss(0xCA85);
    cpu.set_ds(0xC20D);
    cpu.set_es(0x3BA4);
    cpu.set_sp(0xD2CE);
    cpu.set_bp(0xD402);
    cpu.set_si(0x07AF);
    cpu.set_di(0xA546);
    cpu.set_ip(0xCC7E);
    cpu.set_flags(0xFC13);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0308E, 0x3E);
    machine.mem_store_byte(0x0308F, 0x1B);
    machine.mem_store_byte(0x03090, 0x53);
    machine.mem_store_byte(0x03091, 0xA7);
    machine.mem_store_byte(0xC99BF, 0xC7);
    machine.mem_store_byte(0xC99C0, 0x21);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0A67);
    EXPECT_EQ(cpu.get_ip(), 0xCC82);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// sbb word [ds:bx+6175h], si
//
TEST_F(MachineTest, sbb_word_ds_bx_6175h_si)
{
    // Initial CPU State
    cpu.set_ax(0xA30E);
    cpu.set_bx(0xF37B);
    cpu.set_cx(0x873A);
    cpu.set_dx(0x01E5);
    cpu.set_cs(0x2AE6);
    cpu.set_ss(0x252C);
    cpu.set_ds(0xCE3C);
    cpu.set_es(0x3023);
    cpu.set_sp(0xE7FF);
    cpu.set_bp(0xD849);
    cpu.set_si(0x599D);
    cpu.set_di(0x91BD);
    cpu.set_ip(0x3FAD);
    cpu.set_flags(0xF482);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2EE0D, 0x19);
    machine.mem_store_byte(0x2EE0E, 0xB7);
    machine.mem_store_byte(0x2EE0F, 0x75);
    machine.mem_store_byte(0x2EE10, 0x61);
    machine.mem_store_byte(0xD38B0, 0x1E);
    machine.mem_store_byte(0xD38B1, 0x32);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3FB1);
    EXPECT_EQ(cpu.get_flags(), 0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD38B0), 0x81);
    EXPECT_EQ(memory.load8(0xD38B1), 0xD8);
}

//
// sbb word [ds:bx+di], 42h
//
TEST_F(MachineTest, sbb_word_ds_bx_di_42h)
{
    // Initial CPU State
    cpu.set_ax(0x5940);
    cpu.set_bx(0x550C);
    cpu.set_cx(0x2E74);
    cpu.set_dx(0x66D6);
    cpu.set_cs(0xCD2F);
    cpu.set_ss(0x098E);
    cpu.set_ds(0x3A43);
    cpu.set_es(0x59DC);
    cpu.set_sp(0x742A);
    cpu.set_bp(0x0085);
    cpu.set_si(0xBDB1);
    cpu.set_di(0x1E33);
    cpu.set_ip(0x7B7C);
    cpu.set_flags(0xF847);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD4E6C, 0x3E);
    machine.mem_store_byte(0xD4E6D, 0x83);
    machine.mem_store_byte(0xD4E6E, 0x19);
    machine.mem_store_byte(0xD4E6F, 0x42);
    machine.mem_store_byte(0x4176F, 0x23);
    machine.mem_store_byte(0x41770, 0x94);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x7B80);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4176F), 0xE0);
    EXPECT_EQ(memory.load8(0x41770), 0x93);
}

//
// sbb word [ds:bx+di+52h], FCBEh
//
TEST_F(MachineTest, sbb_word_ds_bx_di_52h_FCBEh)
{
    // Initial CPU State
    cpu.set_ax(0x963E);
    cpu.set_bx(0x7281);
    cpu.set_cx(0xAF72);
    cpu.set_dx(0xDA98);
    cpu.set_cs(0x0911);
    cpu.set_ss(0x08FC);
    cpu.set_ds(0x6504);
    cpu.set_es(0x9A99);
    cpu.set_sp(0xADA6);
    cpu.set_bp(0xD113);
    cpu.set_si(0xF71C);
    cpu.set_di(0x8D5F);
    cpu.set_ip(0x804F);
    cpu.set_flags(0xF043);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x1115F, 0x81);
    machine.mem_store_byte(0x11160, 0x59);
    machine.mem_store_byte(0x11161, 0x52);
    machine.mem_store_byte(0x11162, 0xBE);
    machine.mem_store_byte(0x11163, 0xFC);
    machine.mem_store_byte(0x65072, 0x24);
    machine.mem_store_byte(0x65073, 0x97);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8054);
    EXPECT_EQ(cpu.get_flags(), 0xF097);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x65072), 0x65);
    EXPECT_EQ(memory.load8(0x65073), 0x9A);
}

//
// sub al, Eh
//
TEST_F(MachineTest, sub_al_Eh)
{
    // Initial CPU State
    cpu.set_ax(0x475D);
    cpu.set_bx(0x5B1E);
    cpu.set_cx(0xDAE2);
    cpu.set_dx(0x8E64);
    cpu.set_cs(0xBD12);
    cpu.set_ss(0x5FC9);
    cpu.set_ds(0xE309);
    cpu.set_es(0x09EF);
    cpu.set_sp(0xE132);
    cpu.set_bp(0x4FE9);
    cpu.set_si(0xD280);
    cpu.set_di(0x461D);
    cpu.set_ip(0x5457);
    cpu.set_flags(0xF0C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC2577, 0x2C);
    machine.mem_store_byte(0xC2578, 0x0E);
    machine.mem_store_byte(0xC2579, 0x90);
    machine.mem_store_byte(0xC257A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x474F);
    EXPECT_EQ(cpu.get_ip(), 0x5459);
    EXPECT_EQ(cpu.get_flags(), 0xF012);

    // Final RAM entries
}

//
// sub ax, D73Ch
//
TEST_F(MachineTest, sub_ax_D73Ch)
{
    // Initial CPU State
    cpu.set_ax(0x473C);
    cpu.set_bx(0x4D7F);
    cpu.set_cx(0x04AA);
    cpu.set_dx(0xF681);
    cpu.set_cs(0xA4EB);
    cpu.set_ss(0x36E7);
    cpu.set_ds(0xD09E);
    cpu.set_es(0x00C2);
    cpu.set_sp(0x9B36);
    cpu.set_bp(0x292F);
    cpu.set_si(0x1FFE);
    cpu.set_di(0x86A7);
    cpu.set_ip(0x98CF);
    cpu.set_flags(0xF842);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAE77F, 0x2D);
    machine.mem_store_byte(0xAE780, 0x3C);
    machine.mem_store_byte(0xAE781, 0xD7);
    machine.mem_store_byte(0xAE782, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7000);
    EXPECT_EQ(cpu.get_ip(), 0x98D2);
    EXPECT_EQ(cpu.get_flags(), 0xF007);

    // Final RAM entries
}

//
// sub bl, byte [es:bx+di-63AAh]
//
TEST_F(MachineTest, sub_bl_byte_es_bx_di_63AAh)
{
    // Initial CPU State
    cpu.set_ax(0xF658);
    cpu.set_bx(0x7265);
    cpu.set_cx(0x4084);
    cpu.set_dx(0xA6CE);
    cpu.set_cs(0xEA77);
    cpu.set_ss(0x3052);
    cpu.set_ds(0x5D4F);
    cpu.set_es(0xFE02);
    cpu.set_sp(0x3735);
    cpu.set_bp(0x6F8D);
    cpu.set_si(0xF27B);
    cpu.set_di(0xA612);
    cpu.set_ip(0x9015);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF3785, 0x26);
    machine.mem_store_byte(0xF3786, 0x2A);
    machine.mem_store_byte(0xF3787, 0x99);
    machine.mem_store_byte(0xF3788, 0x56);
    machine.mem_store_byte(0xF3789, 0x9C);
    machine.mem_store_byte(0x094ED, 0xF4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x7271);
    EXPECT_EQ(cpu.get_ip(), 0x901A);
    EXPECT_EQ(cpu.get_flags(), 0xF007);

    // Final RAM entries
}

//
// sub byte [cs:bp+di-147Ah], dh
//
TEST_F(MachineTest, sub_byte_cs_bp_di_147Ah_dh)
{
    // Initial CPU State
    cpu.set_ax(0x2F39);
    cpu.set_bx(0xC475);
    cpu.set_cx(0x3E72);
    cpu.set_dx(0x425D);
    cpu.set_cs(0x5A55);
    cpu.set_ss(0x68C0);
    cpu.set_ds(0x7E85);
    cpu.set_es(0x7FDE);
    cpu.set_sp(0xF39C);
    cpu.set_bp(0x913F);
    cpu.set_si(0x8953);
    cpu.set_di(0x7395);
    cpu.set_ip(0x6DC9);
    cpu.set_flags(0xF4C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x61319, 0x2E);
    machine.mem_store_byte(0x6131A, 0x28);
    machine.mem_store_byte(0x6131B, 0xB3);
    machine.mem_store_byte(0x6131C, 0x86);
    machine.mem_store_byte(0x6131D, 0xEB);
    machine.mem_store_byte(0x695AA, 0x35);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x6DCE);
    EXPECT_EQ(cpu.get_flags(), 0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x695AA), 0xF3);
}

//
// sub byte [cs:bx+si-32h], 30h
//
TEST_F(MachineTest, sub_byte_cs_bx_si_32h_30h)
{
    // Initial CPU State
    cpu.set_ax(0x53AF);
    cpu.set_bx(0x1379);
    cpu.set_cx(0x7678);
    cpu.set_dx(0xD56B);
    cpu.set_cs(0x44D7);
    cpu.set_ss(0x3C4C);
    cpu.set_ds(0x0D04);
    cpu.set_es(0xF5AC);
    cpu.set_sp(0xE456);
    cpu.set_bp(0x7AE9);
    cpu.set_si(0x65B6);
    cpu.set_di(0x8B5F);
    cpu.set_ip(0x9AD7);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4E847, 0x2E);
    machine.mem_store_byte(0x4E848, 0x80);
    machine.mem_store_byte(0x4E849, 0x68);
    machine.mem_store_byte(0x4E84A, 0xCE);
    machine.mem_store_byte(0x4E84B, 0x30);
    machine.mem_store_byte(0x4C66D, 0x45);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9ADC);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4C66D), 0x15);
}

//
// sub ch, D4h
//
TEST_F(MachineTest, sub_ch_D4h)
{
    // Initial CPU State
    cpu.set_ax(0x7E7A);
    cpu.set_bx(0xCF0F);
    cpu.set_cx(0xED36);
    cpu.set_dx(0x5229);
    cpu.set_cs(0xFDBA);
    cpu.set_ss(0xC735);
    cpu.set_ds(0x00FE);
    cpu.set_es(0x98E3);
    cpu.set_sp(0x2B60);
    cpu.set_bp(0x1437);
    cpu.set_si(0xDC43);
    cpu.set_di(0xA554);
    cpu.set_ip(0xCC2F);
    cpu.set_flags(0xFC43);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0A7CF, 0x3E);
    machine.mem_store_byte(0x0A7D0, 0x82);
    machine.mem_store_byte(0x0A7D1, 0xED);
    machine.mem_store_byte(0x0A7D2, 0xD4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x1936);
    EXPECT_EQ(cpu.get_ip(), 0xCC33);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
}

//
// sub sp, word [ds:bx+di]
//
TEST_F(MachineTest, sub_sp_word_ds_bx_di)
{
    // Initial CPU State
    cpu.set_ax(0x800F);
    cpu.set_bx(0x3A07);
    cpu.set_cx(0x117E);
    cpu.set_dx(0xF5DF);
    cpu.set_cs(0xB377);
    cpu.set_ss(0x4F79);
    cpu.set_ds(0x8452);
    cpu.set_es(0xBBD3);
    cpu.set_sp(0x9A0F);
    cpu.set_bp(0x6BF0);
    cpu.set_si(0x23C9);
    cpu.set_di(0x93D7);
    cpu.set_ip(0x2076);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB57E6, 0x2B);
    machine.mem_store_byte(0xB57E7, 0x21);
    machine.mem_store_byte(0xB57E8, 0x90);
    machine.mem_store_byte(0xB57E9, 0x90);
    machine.mem_store_byte(0x912FE, 0xD4);
    machine.mem_store_byte(0x912FF, 0x9C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_sp(), 0xFD3B);
    EXPECT_EQ(cpu.get_ip(), 0x2078);
    EXPECT_EQ(cpu.get_flags(), 0xF483);

    // Final RAM entries
}

//
// sub word [ss:bp+di+5Eh], 2Bh
//
TEST_F(MachineTest, sub_word_ss_bp_di_5Eh_2Bh)
{
    // Initial CPU State
    cpu.set_ax(0xCB3D);
    cpu.set_bx(0xB757);
    cpu.set_cx(0x386E);
    cpu.set_dx(0xE7AE);
    cpu.set_cs(0xF1B4);
    cpu.set_ss(0x537A);
    cpu.set_ds(0xAD8E);
    cpu.set_es(0x6887);
    cpu.set_sp(0x8271);
    cpu.set_bp(0x0FC3);
    cpu.set_si(0x0B4C);
    cpu.set_di(0x7378);
    cpu.set_ip(0x72E6);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8E26, 0x83);
    machine.mem_store_byte(0xF8E27, 0x6B);
    machine.mem_store_byte(0xF8E28, 0x5E);
    machine.mem_store_byte(0xF8E29, 0x2B);
    machine.mem_store_byte(0x5BB39, 0x98);
    machine.mem_store_byte(0x5BB3A, 0x11);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x72EA);
    EXPECT_EQ(cpu.get_flags(), 0xF012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5BB39), 0x6D);
}

//
// sub word [ss:bp+di], dx
//
TEST_F(MachineTest, sub_word_ss_bp_di_dx)
{
    // Initial CPU State
    cpu.set_ax(0x045F);
    cpu.set_bx(0x7489);
    cpu.set_cx(0x4F58);
    cpu.set_dx(0x5F9E);
    cpu.set_cs(0xDBDE);
    cpu.set_ss(0x1456);
    cpu.set_ds(0xEFD2);
    cpu.set_es(0xD836);
    cpu.set_sp(0x9596);
    cpu.set_bp(0x5F9B);
    cpu.set_si(0x49B4);
    cpu.set_di(0xEB3A);
    cpu.set_ip(0xEE2A);
    cpu.set_flags(0xF852);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEAC0A, 0x29);
    machine.mem_store_byte(0xEAC0B, 0x13);
    machine.mem_store_byte(0xEAC0C, 0x90);
    machine.mem_store_byte(0xEAC0D, 0x90);
    machine.mem_store_byte(0x19035, 0x3E);
    machine.mem_store_byte(0x19036, 0xEA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEE2C);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x19035), 0xA0);
    EXPECT_EQ(memory.load8(0x19036), 0x8A);
}

//
// sub word [ss:bx+di], A80Fh
//
TEST_F(MachineTest, sub_word_ss_bx_di_A80Fh)
{
    // Initial CPU State
    cpu.set_ax(0x75E5);
    cpu.set_bx(0x442C);
    cpu.set_cx(0x54DA);
    cpu.set_dx(0xD786);
    cpu.set_cs(0x7ED9);
    cpu.set_ss(0xA1BA);
    cpu.set_ds(0x4F39);
    cpu.set_es(0xAB28);
    cpu.set_sp(0x7FEC);
    cpu.set_bp(0xFD76);
    cpu.set_si(0xB632);
    cpu.set_di(0xB049);
    cpu.set_ip(0x1838);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x805C8, 0x36);
    machine.mem_store_byte(0x805C9, 0x81);
    machine.mem_store_byte(0x805CA, 0x29);
    machine.mem_store_byte(0x805CB, 0x0F);
    machine.mem_store_byte(0x805CC, 0xA8);
    machine.mem_store_byte(0xB1015, 0x59);
    machine.mem_store_byte(0xB1016, 0x62);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x183D);
    EXPECT_EQ(cpu.get_flags(), 0xF893);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB1015), 0x4A);
    EXPECT_EQ(memory.load8(0xB1016), 0xBA);
}
