#include "fixture.h"

// Tests: and, or, xor

TEST_F(MachineTest, and_al_9Fh)
{
    // Initial CPU State
    cpu.set_ax(0x1422);
    cpu.set_bx(0x0A3F);
    cpu.set_cx(0xC882);
    cpu.set_dx(0xD1BD);
    cpu.set_cs(0x5CCF);
    cpu.set_ss(0xF741);
    cpu.set_ds(0xCFDD);
    cpu.set_es(0x91FE);
    cpu.set_sp(0xFD5C);
    cpu.set_bp(0x3FEF);
    cpu.set_si(0x4D8B);
    cpu.set_di(0x211D);
    cpu.set_ip(0x452A);
    cpu.set_flags(0xF4D7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6121A, 0x26);
    machine.mem_store_byte(0x6121B, 0x24);
    machine.mem_store_byte(0x6121C, 0x9F);
    machine.mem_store_byte(0x6121D, 0x90);
    machine.mem_store_byte(0x6121E, 0x90);
    machine.mem_store_byte(0x6121F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1402);
    EXPECT_EQ(cpu.get_ip(), 0x452D);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6121A), 0x26);
    EXPECT_EQ(memory.load8(0x6121B), 0x24);
    EXPECT_EQ(memory.load8(0x6121C), 0x9F);
    EXPECT_EQ(memory.load8(0x6121D), 0x90);
    EXPECT_EQ(memory.load8(0x6121E), 0x90);
    EXPECT_EQ(memory.load8(0x6121F), 0x90);
}

TEST_F(MachineTest, and_ax_5E8Eh)
{
    // Initial CPU State
    cpu.set_ax(0x8D1E);
    cpu.set_bx(0xAAE3);
    cpu.set_cx(0x171C);
    cpu.set_dx(0x11EA);
    cpu.set_cs(0x6000);
    cpu.set_ss(0xE5AF);
    cpu.set_ds(0x81E7);
    cpu.set_es(0x3AB8);
    cpu.set_sp(0xE16A);
    cpu.set_bp(0x5E12);
    cpu.set_si(0x1718);
    cpu.set_di(0xC791);
    cpu.set_ip(0xFE7C);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6FE7C, 0x3E);
    machine.mem_store_byte(0x6FE7D, 0x25);
    machine.mem_store_byte(0x6FE7E, 0x8E);
    machine.mem_store_byte(0x6FE7F, 0x5E);
    machine.mem_store_byte(0x6FE80, 0x90);
    machine.mem_store_byte(0x6FE81, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0C0E);
    EXPECT_EQ(cpu.get_ip(), 0xFE80);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6FE7C), 0x3E);
    EXPECT_EQ(memory.load8(0x6FE7D), 0x25);
    EXPECT_EQ(memory.load8(0x6FE7E), 0x8E);
    EXPECT_EQ(memory.load8(0x6FE7F), 0x5E);
    EXPECT_EQ(memory.load8(0x6FE80), 0x90);
    EXPECT_EQ(memory.load8(0x6FE81), 0x90);
}

TEST_F(MachineTest, and_byte_ds_bp_di_41E5h_6Ah)
{
    // Initial CPU State
    cpu.set_ax(0xE295);
    cpu.set_bx(0x8432);
    cpu.set_cx(0xA8F2);
    cpu.set_dx(0xFC73);
    cpu.set_cs(0x4DF1);
    cpu.set_ss(0x109B);
    cpu.set_ds(0xC609);
    cpu.set_es(0x3C88);
    cpu.set_sp(0xC896);
    cpu.set_bp(0x257E);
    cpu.set_si(0xE74D);
    cpu.set_di(0x492A);
    cpu.set_ip(0x7F3C);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x55E4C, 0x3E);
    machine.mem_store_byte(0x55E4D, 0x80);
    machine.mem_store_byte(0x55E4E, 0xA3);
    machine.mem_store_byte(0x55E4F, 0x1B);
    machine.mem_store_byte(0x55E50, 0xBE);
    machine.mem_store_byte(0x55E51, 0x6A);
    machine.mem_store_byte(0xC8D53, 0x23);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x7F42);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x55E4C), 0x3E);
    EXPECT_EQ(memory.load8(0x55E4D), 0x80);
    EXPECT_EQ(memory.load8(0x55E4E), 0xA3);
    EXPECT_EQ(memory.load8(0x55E4F), 0x1B);
    EXPECT_EQ(memory.load8(0x55E50), 0xBE);
    EXPECT_EQ(memory.load8(0x55E51), 0x6A);
    EXPECT_EQ(memory.load8(0xC8D53), 0x22);
}

TEST_F(MachineTest, and_byte_ss_bp_65h_90h)
{
    // Initial CPU State
    cpu.set_ax(0xAF67);
    cpu.set_bx(0x5072);
    cpu.set_cx(0xBAE0);
    cpu.set_dx(0x3D33);
    cpu.set_cs(0xA272);
    cpu.set_ss(0xCD0B);
    cpu.set_ds(0xD2B2);
    cpu.set_es(0x9CCA);
    cpu.set_sp(0x8F7E);
    cpu.set_bp(0x35B8);
    cpu.set_si(0x418A);
    cpu.set_di(0x2B62);
    cpu.set_ip(0x8812);
    cpu.set_flags(0xF492);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAAF32, 0x36);
    machine.mem_store_byte(0xAAF33, 0x82);
    machine.mem_store_byte(0xAAF34, 0x66);
    machine.mem_store_byte(0xAAF35, 0x65);
    machine.mem_store_byte(0xAAF36, 0x90);
    machine.mem_store_byte(0xAAF37, 0x90);
    machine.mem_store_byte(0xD06CD, 0xF0);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8817);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAAF32), 0x36);
    EXPECT_EQ(memory.load8(0xAAF33), 0x82);
    EXPECT_EQ(memory.load8(0xAAF34), 0x66);
    EXPECT_EQ(memory.load8(0xAAF35), 0x65);
    EXPECT_EQ(memory.load8(0xAAF36), 0x90);
    EXPECT_EQ(memory.load8(0xAAF37), 0x90);
    EXPECT_EQ(memory.load8(0xD06CD), 0x90);
}

TEST_F(MachineTest, and_ch_dh)
{
    // Initial CPU State
    cpu.set_ax(0xA551);
    cpu.set_bx(0xBAC9);
    cpu.set_cx(0xB9EA);
    cpu.set_dx(0xDF00);
    cpu.set_cs(0x474F);
    cpu.set_ss(0x5B05);
    cpu.set_ds(0xFA2D);
    cpu.set_es(0xEF03);
    cpu.set_sp(0x398A);
    cpu.set_bp(0xF0EE);
    cpu.set_si(0x0CC3);
    cpu.set_di(0x5D8C);
    cpu.set_ip(0x029C);
    cpu.set_flags(0xF052);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x4778C, 0x20);
    machine.mem_store_byte(0x4778D, 0xF5);
    machine.mem_store_byte(0x4778E, 0x90);
    machine.mem_store_byte(0x4778F, 0x90);
    machine.mem_store_byte(0x47790, 0x90);
    machine.mem_store_byte(0x47791, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x99EA);
    EXPECT_EQ(cpu.get_ip(), 0x029E);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4778C), 0x20);
    EXPECT_EQ(memory.load8(0x4778D), 0xF5);
    EXPECT_EQ(memory.load8(0x4778E), 0x90);
    EXPECT_EQ(memory.load8(0x4778F), 0x90);
    EXPECT_EQ(memory.load8(0x47790), 0x90);
    EXPECT_EQ(memory.load8(0x47791), 0x90);
}

TEST_F(MachineTest, and_dl_dh)
{
    // Initial CPU State
    cpu.set_ax(0xF8E7);
    cpu.set_bx(0xF5B0);
    cpu.set_cx(0xB700);
    cpu.set_dx(0x26AB);
    cpu.set_cs(0xB60A);
    cpu.set_ss(0x90A5);
    cpu.set_ds(0xED9B);
    cpu.set_es(0x7612);
    cpu.set_sp(0xF871);
    cpu.set_bp(0x1183);
    cpu.set_si(0xF18F);
    cpu.set_di(0x2696);
    cpu.set_ip(0x287D);
    cpu.set_flags(0xFC96);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB891D, 0x36);
    machine.mem_store_byte(0xB891E, 0x22);
    machine.mem_store_byte(0xB891F, 0xD6);
    machine.mem_store_byte(0xB8920, 0x90);
    machine.mem_store_byte(0xB8921, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x2622);
    EXPECT_EQ(cpu.get_ip(), 0x2880);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB891D), 0x36);
    EXPECT_EQ(memory.load8(0xB891E), 0x22);
    EXPECT_EQ(memory.load8(0xB891F), 0xD6);
    EXPECT_EQ(memory.load8(0xB8920), 0x90);
    EXPECT_EQ(memory.load8(0xB8921), 0x90);
}

TEST_F(MachineTest, and_si_sp)
{
    // Initial CPU State
    cpu.set_ax(0x74BA);
    cpu.set_bx(0x2B84);
    cpu.set_cx(0x7B46);
    cpu.set_dx(0xAB5D);
    cpu.set_cs(0x9513);
    cpu.set_ss(0xAB0C);
    cpu.set_ds(0x2795);
    cpu.set_es(0x85C4);
    cpu.set_sp(0x95D2);
    cpu.set_bp(0x68D7);
    cpu.set_si(0x0000);
    cpu.set_di(0x76AB);
    cpu.set_ip(0xFBDD);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA4D0D, 0x26);
    machine.mem_store_byte(0xA4D0E, 0x23);
    machine.mem_store_byte(0xA4D0F, 0xF4);
    machine.mem_store_byte(0xA4D10, 0x90);
    machine.mem_store_byte(0xA4D11, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xFBE0);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA4D0D), 0x26);
    EXPECT_EQ(memory.load8(0xA4D0E), 0x23);
    EXPECT_EQ(memory.load8(0xA4D0F), 0xF4);
    EXPECT_EQ(memory.load8(0xA4D10), 0x90);
    EXPECT_EQ(memory.load8(0xA4D11), 0x90);
}

TEST_F(MachineTest, and_word_cs_bx_si_FFA4h)
{
    // Initial CPU State
    cpu.set_ax(0x0464);
    cpu.set_bx(0x002A);
    cpu.set_cx(0xFFAA);
    cpu.set_dx(0xE474);
    cpu.set_cs(0xA256);
    cpu.set_ss(0xF45D);
    cpu.set_ds(0x35CB);
    cpu.set_es(0x6342);
    cpu.set_sp(0xFCE8);
    cpu.set_bp(0xCE09);
    cpu.set_si(0xDB29);
    cpu.set_di(0x55D8);
    cpu.set_ip(0x08FC);
    cpu.set_flags(0xF0C2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA2E5C, 0x2E);
    machine.mem_store_byte(0xA2E5D, 0x83);
    machine.mem_store_byte(0xA2E5E, 0x20);
    machine.mem_store_byte(0xA2E5F, 0xA4);
    machine.mem_store_byte(0xA2E60, 0x90);
    machine.mem_store_byte(0xA2E61, 0x90);
    machine.mem_store_byte(0xB00B3, 0x41);
    machine.mem_store_byte(0xB00B4, 0x15);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0900);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA2E5C), 0x2E);
    EXPECT_EQ(memory.load8(0xA2E5D), 0x83);
    EXPECT_EQ(memory.load8(0xA2E5E), 0x20);
    EXPECT_EQ(memory.load8(0xA2E5F), 0xA4);
    EXPECT_EQ(memory.load8(0xA2E60), 0x90);
    EXPECT_EQ(memory.load8(0xA2E61), 0x90);
    EXPECT_EQ(memory.load8(0xB00B3), 0x00);
    EXPECT_EQ(memory.load8(0xB00B4), 0x15);
}

TEST_F(MachineTest, and_word_ds_bx_si_634Ah)
{
    // Initial CPU State
    cpu.set_ax(0x7C8D);
    cpu.set_bx(0x5EF4);
    cpu.set_cx(0x87B0);
    cpu.set_dx(0xAB51);
    cpu.set_cs(0xFFC5);
    cpu.set_ss(0x476C);
    cpu.set_ds(0x52FA);
    cpu.set_es(0x8D4F);
    cpu.set_sp(0x413D);
    cpu.set_bp(0x87BF);
    cpu.set_si(0xE502);
    cpu.set_di(0xA371);
    cpu.set_ip(0xB55E);
    cpu.set_flags(0xF453);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0B1AE, 0x81);
    machine.mem_store_byte(0x0B1AF, 0x20);
    machine.mem_store_byte(0x0B1B0, 0x4A);
    machine.mem_store_byte(0x0B1B1, 0x63);
    machine.mem_store_byte(0x0B1B2, 0x90);
    machine.mem_store_byte(0x0B1B3, 0x90);
    machine.mem_store_byte(0x57396, 0x71);
    machine.mem_store_byte(0x57397, 0x2E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB562);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0B1AE), 0x81);
    EXPECT_EQ(memory.load8(0x0B1AF), 0x20);
    EXPECT_EQ(memory.load8(0x0B1B0), 0x4A);
    EXPECT_EQ(memory.load8(0x0B1B1), 0x63);
    EXPECT_EQ(memory.load8(0x0B1B2), 0x90);
    EXPECT_EQ(memory.load8(0x0B1B3), 0x90);
    EXPECT_EQ(memory.load8(0x57396), 0x40);
    EXPECT_EQ(memory.load8(0x57397), 0x22);
}

TEST_F(MachineTest, and_word_ss_di_41h_di)
{
    // Initial CPU State
    cpu.set_ax(0x9B62);
    cpu.set_bx(0xED5B);
    cpu.set_cx(0x6142);
    cpu.set_dx(0xA769);
    cpu.set_cs(0x9EAA);
    cpu.set_ss(0xE27E);
    cpu.set_ds(0x461F);
    cpu.set_es(0x0BA0);
    cpu.set_sp(0xD6B6);
    cpu.set_bp(0x3BEE);
    cpu.set_si(0x0000);
    cpu.set_di(0x044A);
    cpu.set_ip(0xC7D5);
    cpu.set_flags(0xF0C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAB275, 0x36);
    machine.mem_store_byte(0xAB276, 0x21);
    machine.mem_store_byte(0xAB277, 0x7D);
    machine.mem_store_byte(0xAB278, 0xBF);
    machine.mem_store_byte(0xAB279, 0x90);
    machine.mem_store_byte(0xE2BE9, 0xA3);
    machine.mem_store_byte(0xE2BEA, 0x8C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC7D9);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAB275), 0x36);
    EXPECT_EQ(memory.load8(0xAB276), 0x21);
    EXPECT_EQ(memory.load8(0xAB277), 0x7D);
    EXPECT_EQ(memory.load8(0xAB278), 0xBF);
    EXPECT_EQ(memory.load8(0xAB279), 0x90);
    EXPECT_EQ(memory.load8(0xE2BE9), 0x02);
    EXPECT_EQ(memory.load8(0xE2BEA), 0x04);
}

TEST_F(MachineTest, or_al_94h)
{
    // Initial CPU State
    cpu.set_ax(0x08A1);
    cpu.set_bx(0x16B7);
    cpu.set_cx(0xCD5E);
    cpu.set_dx(0x5DD8);
    cpu.set_cs(0xFB20);
    cpu.set_ss(0xFEF2);
    cpu.set_ds(0xBE00);
    cpu.set_es(0xFEAC);
    cpu.set_sp(0xCAB1);
    cpu.set_bp(0x858B);
    cpu.set_si(0xE775);
    cpu.set_di(0x6BC7);
    cpu.set_ip(0x3D06);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFEF06, 0x36);
    machine.mem_store_byte(0xFEF07, 0x0C);
    machine.mem_store_byte(0xFEF08, 0x94);
    machine.mem_store_byte(0xFEF09, 0x90);
    machine.mem_store_byte(0xFEF0A, 0x90);
    machine.mem_store_byte(0xFEF0B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x08B5);
    EXPECT_EQ(cpu.get_ip(), 0x3D09);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFEF06), 0x36);
    EXPECT_EQ(memory.load8(0xFEF07), 0x0C);
    EXPECT_EQ(memory.load8(0xFEF08), 0x94);
    EXPECT_EQ(memory.load8(0xFEF09), 0x90);
    EXPECT_EQ(memory.load8(0xFEF0A), 0x90);
    EXPECT_EQ(memory.load8(0xFEF0B), 0x90);
}

TEST_F(MachineTest, or_ax_D6CDh)
{
    // Initial CPU State
    cpu.set_ax(0x289F);
    cpu.set_bx(0x64AE);
    cpu.set_cx(0x43A2);
    cpu.set_dx(0x2658);
    cpu.set_cs(0x9F2D);
    cpu.set_ss(0xB5BE);
    cpu.set_ds(0xB02D);
    cpu.set_es(0x5319);
    cpu.set_sp(0x36E5);
    cpu.set_bp(0x4555);
    cpu.set_si(0x7A98);
    cpu.set_di(0x5619);
    cpu.set_ip(0xBFE2);
    cpu.set_flags(0xF487);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAB2B2, 0x26);
    machine.mem_store_byte(0xAB2B3, 0x0D);
    machine.mem_store_byte(0xAB2B4, 0xCD);
    machine.mem_store_byte(0xAB2B5, 0xD6);
    machine.mem_store_byte(0xAB2B6, 0x90);
    machine.mem_store_byte(0xAB2B7, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFEDF);
    EXPECT_EQ(cpu.get_ip(), 0xBFE6);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAB2B2), 0x26);
    EXPECT_EQ(memory.load8(0xAB2B3), 0x0D);
    EXPECT_EQ(memory.load8(0xAB2B4), 0xCD);
    EXPECT_EQ(memory.load8(0xAB2B5), 0xD6);
    EXPECT_EQ(memory.load8(0xAB2B6), 0x90);
    EXPECT_EQ(memory.load8(0xAB2B7), 0x90);
}

TEST_F(MachineTest, or_bh_byte_cs_bp_78h)
{
    // Initial CPU State
    cpu.set_ax(0x3C00);
    cpu.set_bx(0xF821);
    cpu.set_cx(0xEB98);
    cpu.set_dx(0x3BAF);
    cpu.set_cs(0x296C);
    cpu.set_ss(0xFFB5);
    cpu.set_ds(0x5B52);
    cpu.set_es(0x82C6);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xD37F);
    cpu.set_si(0x96F9);
    cpu.set_di(0x2CDE);
    cpu.set_ip(0xF8A3);
    cpu.set_flags(0xF8C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x38F63, 0x2E);
    machine.mem_store_byte(0x38F64, 0x0A);
    machine.mem_store_byte(0x38F65, 0x7E);
    machine.mem_store_byte(0x38F66, 0x88);
    machine.mem_store_byte(0x38F67, 0x90);
    machine.mem_store_byte(0x369C7, 0x0E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xFE21);
    EXPECT_EQ(cpu.get_ip(), 0xF8A7);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x38F63), 0x2E);
    EXPECT_EQ(memory.load8(0x38F64), 0x0A);
    EXPECT_EQ(memory.load8(0x38F65), 0x7E);
    EXPECT_EQ(memory.load8(0x38F66), 0x88);
    EXPECT_EQ(memory.load8(0x38F67), 0x90);
    EXPECT_EQ(memory.load8(0x369C7), 0x0E);
}

TEST_F(MachineTest, or_byte_ds_bx_di_31B5h_Ah)
{
    // Initial CPU State
    cpu.set_ax(0xD430);
    cpu.set_bx(0x05AE);
    cpu.set_cx(0x54D8);
    cpu.set_dx(0x145C);
    cpu.set_cs(0x9913);
    cpu.set_ss(0x772A);
    cpu.set_ds(0xC292);
    cpu.set_es(0x4101);
    cpu.set_sp(0xE357);
    cpu.set_bp(0x3AEC);
    cpu.set_si(0x28C0);
    cpu.set_di(0x243B);
    cpu.set_ip(0xBCFE);
    cpu.set_flags(0xF0D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA4E2E, 0x80);
    machine.mem_store_byte(0xA4E2F, 0x89);
    machine.mem_store_byte(0xA4E30, 0xB5);
    machine.mem_store_byte(0xA4E31, 0x31);
    machine.mem_store_byte(0xA4E32, 0x0A);
    machine.mem_store_byte(0xA4E33, 0x90);
    machine.mem_store_byte(0xC84BE, 0xB8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBD03);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA4E2E), 0x80);
    EXPECT_EQ(memory.load8(0xA4E2F), 0x89);
    EXPECT_EQ(memory.load8(0xA4E30), 0xB5);
    EXPECT_EQ(memory.load8(0xA4E31), 0x31);
    EXPECT_EQ(memory.load8(0xA4E32), 0x0A);
    EXPECT_EQ(memory.load8(0xA4E33), 0x90);
    EXPECT_EQ(memory.load8(0xC84BE), 0xBA);
}

TEST_F(MachineTest, or_byte_ss_bp_65h_90h)
{
    // Initial CPU State
    cpu.set_ax(0xAF67);
    cpu.set_bx(0x5072);
    cpu.set_cx(0xBAE0);
    cpu.set_dx(0x3D33);
    cpu.set_cs(0xA272);
    cpu.set_ss(0xCD0B);
    cpu.set_ds(0xD2B2);
    cpu.set_es(0x9CCA);
    cpu.set_sp(0x8F7E);
    cpu.set_bp(0x35B8);
    cpu.set_si(0x418A);
    cpu.set_di(0x2B62);
    cpu.set_ip(0x8812);
    cpu.set_flags(0xF492);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAAF32, 0x36);
    machine.mem_store_byte(0xAAF33, 0x82);
    machine.mem_store_byte(0xAAF34, 0x4E);
    machine.mem_store_byte(0xAAF35, 0x65);
    machine.mem_store_byte(0xAAF36, 0x90);
    machine.mem_store_byte(0xAAF37, 0x90);
    machine.mem_store_byte(0xD06CD, 0xF0);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x8817);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAAF32), 0x36);
    EXPECT_EQ(memory.load8(0xAAF33), 0x82);
    EXPECT_EQ(memory.load8(0xAAF34), 0x4E);
    EXPECT_EQ(memory.load8(0xAAF35), 0x65);
    EXPECT_EQ(memory.load8(0xAAF36), 0x90);
    EXPECT_EQ(memory.load8(0xAAF37), 0x90);
    EXPECT_EQ(memory.load8(0xD06CD), 0xF0);
}

TEST_F(MachineTest, or_cl_ah)
{
    // Initial CPU State
    cpu.set_ax(0xABC4);
    cpu.set_bx(0xED8A);
    cpu.set_cx(0xA80E);
    cpu.set_dx(0x864F);
    cpu.set_cs(0xA272);
    cpu.set_ss(0xC6CC);
    cpu.set_ds(0x5AB4);
    cpu.set_es(0x76DF);
    cpu.set_sp(0x7CA4);
    cpu.set_bp(0xCA43);
    cpu.set_si(0xF8D3);
    cpu.set_di(0xD6EC);
    cpu.set_ip(0x8812);
    cpu.set_flags(0xF456);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAAF32, 0x08);
    machine.mem_store_byte(0xAAF33, 0xE1);
    machine.mem_store_byte(0xAAF34, 0x90);
    machine.mem_store_byte(0xAAF35, 0x90);
    machine.mem_store_byte(0xAAF36, 0x90);
    machine.mem_store_byte(0xAAF37, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0xA8AF);
    EXPECT_EQ(cpu.get_ip(), 0x8814);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAAF32), 0x08);
    EXPECT_EQ(memory.load8(0xAAF33), 0xE1);
    EXPECT_EQ(memory.load8(0xAAF34), 0x90);
    EXPECT_EQ(memory.load8(0xAAF35), 0x90);
    EXPECT_EQ(memory.load8(0xAAF36), 0x90);
    EXPECT_EQ(memory.load8(0xAAF37), 0x90);
}

TEST_F(MachineTest, or_di_bp)
{
    // Initial CPU State
    cpu.set_ax(0x18EA);
    cpu.set_bx(0x854A);
    cpu.set_cx(0x8F8E);
    cpu.set_dx(0x31E1);
    cpu.set_cs(0x00FE);
    cpu.set_ss(0x0E56);
    cpu.set_ds(0xFBDD);
    cpu.set_es(0xDA05);
    cpu.set_sp(0x77BE);
    cpu.set_bp(0xD3A2);
    cpu.set_si(0x237E);
    cpu.set_di(0x0000);
    cpu.set_ip(0x1174);
    cpu.set_flags(0xFC17);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x02154, 0x26);
    machine.mem_store_byte(0x02155, 0x09);
    machine.mem_store_byte(0x02156, 0xEF);
    machine.mem_store_byte(0x02157, 0x90);
    machine.mem_store_byte(0x02158, 0x90);
    machine.mem_store_byte(0x02159, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xD3A2);
    EXPECT_EQ(cpu.get_ip(), 0x1177);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x02154), 0x26);
    EXPECT_EQ(memory.load8(0x02155), 0x09);
    EXPECT_EQ(memory.load8(0x02156), 0xEF);
    EXPECT_EQ(memory.load8(0x02157), 0x90);
    EXPECT_EQ(memory.load8(0x02158), 0x90);
    EXPECT_EQ(memory.load8(0x02159), 0x90);
}

TEST_F(MachineTest, or_di_word_ds_si)
{
    // Initial CPU State
    cpu.set_ax(0xFA8D);
    cpu.set_bx(0xDE12);
    cpu.set_cx(0xCBBC);
    cpu.set_dx(0x89BB);
    cpu.set_cs(0x3C90);
    cpu.set_ss(0xCA15);
    cpu.set_ds(0x5194);
    cpu.set_es(0x91C1);
    cpu.set_sp(0xB37A);
    cpu.set_bp(0x82D8);
    cpu.set_si(0x10AB);
    cpu.set_di(0xEA36);
    cpu.set_ip(0x916F);
    cpu.set_flags(0xFC46);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x45A6F, 0x3E);
    machine.mem_store_byte(0x45A70, 0x0B);
    machine.mem_store_byte(0x45A71, 0x3C);
    machine.mem_store_byte(0x45A72, 0x90);
    machine.mem_store_byte(0x45A73, 0x90);
    machine.mem_store_byte(0x529EB, 0x8A);
    machine.mem_store_byte(0x529EC, 0xF4);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0xFEBE);
    EXPECT_EQ(cpu.get_ip(), 0x9172);
    EXPECT_EQ(cpu.get_flags(), 0xF486);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x45A6F), 0x3E);
    EXPECT_EQ(memory.load8(0x45A70), 0x0B);
    EXPECT_EQ(memory.load8(0x45A71), 0x3C);
    EXPECT_EQ(memory.load8(0x45A72), 0x90);
    EXPECT_EQ(memory.load8(0x45A73), 0x90);
    EXPECT_EQ(memory.load8(0x529EB), 0x8A);
    EXPECT_EQ(memory.load8(0x529EC), 0xF4);
}

TEST_F(MachineTest, or_word_ds_bx_si_47C4h_4h)
{
    // Initial CPU State
    cpu.set_ax(0x2982);
    cpu.set_bx(0x0CEC);
    cpu.set_cx(0x31A0);
    cpu.set_dx(0x0EC3);
    cpu.set_cs(0x9F2D);
    cpu.set_ss(0x179A);
    cpu.set_ds(0x2A26);
    cpu.set_es(0xF80B);
    cpu.set_sp(0x3AB1);
    cpu.set_bp(0x9A12);
    cpu.set_si(0x8FBC);
    cpu.set_di(0xDEF2);
    cpu.set_ip(0xBFE2);
    cpu.set_flags(0xF0D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAB2B2, 0x83);
    machine.mem_store_byte(0xAB2B3, 0x88);
    machine.mem_store_byte(0xAB2B4, 0x3C);
    machine.mem_store_byte(0xAB2B5, 0xB8);
    machine.mem_store_byte(0xAB2B6, 0x04);
    machine.mem_store_byte(0xAB2B7, 0x90);
    machine.mem_store_byte(0x2F744, 0x85);
    machine.mem_store_byte(0x2F745, 0x00);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xBFE7);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xAB2B2), 0x83);
    EXPECT_EQ(memory.load8(0xAB2B3), 0x88);
    EXPECT_EQ(memory.load8(0xAB2B4), 0x3C);
    EXPECT_EQ(memory.load8(0xAB2B5), 0xB8);
    EXPECT_EQ(memory.load8(0xAB2B6), 0x04);
    EXPECT_EQ(memory.load8(0xAB2B7), 0x90);
    EXPECT_EQ(memory.load8(0x2F744), 0x85);
    EXPECT_EQ(memory.load8(0x2F745), 0x00);
}

TEST_F(MachineTest, or_word_ss_bp_si_629Ch_5531h)
{
    // Initial CPU State
    cpu.set_ax(0xE43E);
    cpu.set_bx(0x2DF6);
    cpu.set_cx(0x7266);
    cpu.set_dx(0x7E5D);
    cpu.set_cs(0xCF9F);
    cpu.set_ss(0xFFD7);
    cpu.set_ds(0x6F71);
    cpu.set_es(0xC953);
    cpu.set_sp(0xE113);
    cpu.set_bp(0x0000);
    cpu.set_si(0x956E);
    cpu.set_di(0x05D1);
    cpu.set_ip(0x9A38);
    cpu.set_flags(0xF086);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD9428, 0x81);
    machine.mem_store_byte(0xD9429, 0x8A);
    machine.mem_store_byte(0xD942A, 0x9C);
    machine.mem_store_byte(0xD942B, 0x62);
    machine.mem_store_byte(0xD942C, 0x31);
    machine.mem_store_byte(0xD942D, 0x55);
    machine.mem_store_byte(0x0F57A, 0xCD);
    machine.mem_store_byte(0x0F57B, 0x54);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9A3E);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD9428), 0x81);
    EXPECT_EQ(memory.load8(0xD9429), 0x8A);
    EXPECT_EQ(memory.load8(0xD942A), 0x9C);
    EXPECT_EQ(memory.load8(0xD942B), 0x62);
    EXPECT_EQ(memory.load8(0xD942C), 0x31);
    EXPECT_EQ(memory.load8(0xD942D), 0x55);
    EXPECT_EQ(memory.load8(0x0F57A), 0xFD);
    EXPECT_EQ(memory.load8(0x0F57B), 0x55);
}

TEST_F(MachineTest, xor_ah_20h)
{
    // Initial CPU State
    cpu.set_ax(0x0226);
    cpu.set_bx(0x797C);
    cpu.set_cx(0x056E);
    cpu.set_dx(0xA762);
    cpu.set_cs(0x296C);
    cpu.set_ss(0x2ECD);
    cpu.set_ds(0xFC6F);
    cpu.set_es(0x9FCA);
    cpu.set_sp(0xE098);
    cpu.set_bp(0x39C3);
    cpu.set_si(0xE316);
    cpu.set_di(0x7094);
    cpu.set_ip(0xF8A3);
    cpu.set_flags(0xF842);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x38F63, 0x82);
    machine.mem_store_byte(0x38F64, 0xF4);
    machine.mem_store_byte(0x38F65, 0x20);
    machine.mem_store_byte(0x38F66, 0x90);
    machine.mem_store_byte(0x38F67, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x2226);
    EXPECT_EQ(cpu.get_ip(), 0xF8A6);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x38F63), 0x82);
    EXPECT_EQ(memory.load8(0x38F64), 0xF4);
    EXPECT_EQ(memory.load8(0x38F65), 0x20);
    EXPECT_EQ(memory.load8(0x38F66), 0x90);
    EXPECT_EQ(memory.load8(0x38F67), 0x90);
}

TEST_F(MachineTest, xor_al_Ah)
{
    // Initial CPU State
    cpu.set_ax(0x1781);
    cpu.set_bx(0x1A4D);
    cpu.set_cx(0x0D08);
    cpu.set_dx(0xEA3E);
    cpu.set_cs(0xB127);
    cpu.set_ss(0xDFC6);
    cpu.set_ds(0xD67D);
    cpu.set_es(0x13BB);
    cpu.set_sp(0xEE96);
    cpu.set_bp(0x7C80);
    cpu.set_si(0xE9A4);
    cpu.set_di(0x5EAE);
    cpu.set_ip(0x5DF0);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB7060, 0x34);
    machine.mem_store_byte(0xB7061, 0x0A);
    machine.mem_store_byte(0xB7062, 0x90);
    machine.mem_store_byte(0xB7063, 0x90);
    machine.mem_store_byte(0xB7064, 0x90);
    machine.mem_store_byte(0xB7065, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x178B);
    EXPECT_EQ(cpu.get_ip(), 0x5DF2);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB7060), 0x34);
    EXPECT_EQ(memory.load8(0xB7061), 0x0A);
    EXPECT_EQ(memory.load8(0xB7062), 0x90);
    EXPECT_EQ(memory.load8(0xB7063), 0x90);
    EXPECT_EQ(memory.load8(0xB7064), 0x90);
    EXPECT_EQ(memory.load8(0xB7065), 0x90);
}

TEST_F(MachineTest, xor_ax_FF76h)
{
    // Initial CPU State
    cpu.set_ax(0x7BF2);
    cpu.set_bx(0x1E1F);
    cpu.set_cx(0xC046);
    cpu.set_dx(0xBAEC);
    cpu.set_cs(0xF2D4);
    cpu.set_ss(0x0FA0);
    cpu.set_ds(0xF8B7);
    cpu.set_es(0x945E);
    cpu.set_sp(0x9154);
    cpu.set_bp(0xE588);
    cpu.set_si(0x4A7B);
    cpu.set_di(0xCA2A);
    cpu.set_ip(0x16B8);
    cpu.set_flags(0xF853);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF43F8, 0x35);
    machine.mem_store_byte(0xF43F9, 0x76);
    machine.mem_store_byte(0xF43FA, 0xFF);
    machine.mem_store_byte(0xF43FB, 0x90);
    machine.mem_store_byte(0xF43FC, 0x90);
    machine.mem_store_byte(0xF43FD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8484);
    EXPECT_EQ(cpu.get_ip(), 0x16BB);
    EXPECT_EQ(cpu.get_flags(), 0xF086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF43F8), 0x35);
    EXPECT_EQ(memory.load8(0xF43F9), 0x76);
    EXPECT_EQ(memory.load8(0xF43FA), 0xFF);
    EXPECT_EQ(memory.load8(0xF43FB), 0x90);
    EXPECT_EQ(memory.load8(0xF43FC), 0x90);
    EXPECT_EQ(memory.load8(0xF43FD), 0x90);
}

TEST_F(MachineTest, xor_bl_25h)
{
    // Initial CPU State
    cpu.set_ax(0x8832);
    cpu.set_bx(0xE9A0);
    cpu.set_cx(0xCDEC);
    cpu.set_dx(0xB33E);
    cpu.set_cs(0xCCF2);
    cpu.set_ss(0x355B);
    cpu.set_ds(0x758C);
    cpu.set_es(0xAF1D);
    cpu.set_sp(0xE620);
    cpu.set_bp(0x3B75);
    cpu.set_si(0x8FE6);
    cpu.set_di(0xA2E7);
    cpu.set_ip(0x164A);
    cpu.set_flags(0xF4D2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCE56A, 0x2E);
    machine.mem_store_byte(0xCE56B, 0x80);
    machine.mem_store_byte(0xCE56C, 0xF3);
    machine.mem_store_byte(0xCE56D, 0x25);
    machine.mem_store_byte(0xCE56E, 0x90);
    machine.mem_store_byte(0xCE56F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0xE985);
    EXPECT_EQ(cpu.get_ip(), 0x164E);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCE56A), 0x2E);
    EXPECT_EQ(memory.load8(0xCE56B), 0x80);
    EXPECT_EQ(memory.load8(0xCE56C), 0xF3);
    EXPECT_EQ(memory.load8(0xCE56D), 0x25);
    EXPECT_EQ(memory.load8(0xCE56E), 0x90);
    EXPECT_EQ(memory.load8(0xCE56F), 0x90);
}

TEST_F(MachineTest, xor_bp_bx)
{
    // Initial CPU State
    cpu.set_ax(0xBCD2);
    cpu.set_bx(0xE910);
    cpu.set_cx(0x09FC);
    cpu.set_dx(0x4327);
    cpu.set_cs(0xA610);
    cpu.set_ss(0x8B5E);
    cpu.set_ds(0x5611);
    cpu.set_es(0xE3FB);
    cpu.set_sp(0x079F);
    cpu.set_bp(0x416C);
    cpu.set_si(0xE5E0);
    cpu.set_di(0xE3D2);
    cpu.set_ip(0xC687);
    cpu.set_flags(0xFC53);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB2787, 0x2E);
    machine.mem_store_byte(0xB2788, 0x33);
    machine.mem_store_byte(0xB2789, 0xEB);
    machine.mem_store_byte(0xB278A, 0x90);
    machine.mem_store_byte(0xB278B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bp(), 0xA87C);
    EXPECT_EQ(cpu.get_ip(), 0xC68A);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB2787), 0x2E);
    EXPECT_EQ(memory.load8(0xB2788), 0x33);
    EXPECT_EQ(memory.load8(0xB2789), 0xEB);
    EXPECT_EQ(memory.load8(0xB278A), 0x90);
    EXPECT_EQ(memory.load8(0xB278B), 0x90);
}

TEST_F(MachineTest, xor_byte_ss_bp_si_Fh_bh)
{
    // Initial CPU State
    cpu.set_ax(0x624C);
    cpu.set_bx(0xA6B7);
    cpu.set_cx(0x704C);
    cpu.set_dx(0x4834);
    cpu.set_cs(0xF4F5);
    cpu.set_ss(0x3FCD);
    cpu.set_ds(0x7771);
    cpu.set_es(0x8469);
    cpu.set_sp(0x6505);
    cpu.set_bp(0x5C9F);
    cpu.set_si(0x48F9);
    cpu.set_di(0x8CD4);
    cpu.set_ip(0x3E76);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF8DC6, 0x30);
    machine.mem_store_byte(0xF8DC7, 0x7A);
    machine.mem_store_byte(0xF8DC8, 0xF1);
    machine.mem_store_byte(0xF8DC9, 0x90);
    machine.mem_store_byte(0xF8DCA, 0x90);
    machine.mem_store_byte(0xF8DCB, 0x90);
    machine.mem_store_byte(0x4A259, 0x7F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3E79);
    EXPECT_EQ(cpu.get_flags(), 0xF082);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xF8DC6), 0x30);
    EXPECT_EQ(memory.load8(0xF8DC7), 0x7A);
    EXPECT_EQ(memory.load8(0xF8DC8), 0xF1);
    EXPECT_EQ(memory.load8(0xF8DC9), 0x90);
    EXPECT_EQ(memory.load8(0xF8DCA), 0x90);
    EXPECT_EQ(memory.load8(0xF8DCB), 0x90);
    EXPECT_EQ(memory.load8(0x4A259), 0xD9);
}

TEST_F(MachineTest, xor_dl_byte_ss_bp_si_1h)
{
    // Initial CPU State
    cpu.set_ax(0x9C47);
    cpu.set_bx(0xD94C);
    cpu.set_cx(0xBC54);
    cpu.set_dx(0x4F28);
    cpu.set_cs(0x350E);
    cpu.set_ss(0x501E);
    cpu.set_ds(0x4E89);
    cpu.set_es(0x572B);
    cpu.set_sp(0xD7FE);
    cpu.set_bp(0x097E);
    cpu.set_si(0x0B0B);
    cpu.set_di(0x2084);
    cpu.set_ip(0x224B);
    cpu.set_flags(0xF812);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3732B, 0x32);
    machine.mem_store_byte(0x3732C, 0x52);
    machine.mem_store_byte(0x3732D, 0xFF);
    machine.mem_store_byte(0x3732E, 0x90);
    machine.mem_store_byte(0x3732F, 0x90);
    machine.mem_store_byte(0x51668, 0x4B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x4F63);
    EXPECT_EQ(cpu.get_ip(), 0x224E);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3732B), 0x32);
    EXPECT_EQ(memory.load8(0x3732C), 0x52);
    EXPECT_EQ(memory.load8(0x3732D), 0xFF);
    EXPECT_EQ(memory.load8(0x3732E), 0x90);
    EXPECT_EQ(memory.load8(0x3732F), 0x90);
    EXPECT_EQ(memory.load8(0x51668), 0x4B);
}

TEST_F(MachineTest, xor_word_ds_bx_di_63h_bp)
{
    // Initial CPU State
    cpu.set_ax(0xCE14);
    cpu.set_bx(0xCB19);
    cpu.set_cx(0xEAE6);
    cpu.set_dx(0x8DD8);
    cpu.set_cs(0x387D);
    cpu.set_ss(0xC790);
    cpu.set_ds(0x40C3);
    cpu.set_es(0x58C8);
    cpu.set_sp(0xF177);
    cpu.set_bp(0xC816);
    cpu.set_si(0x5BD6);
    cpu.set_di(0x0996);
    cpu.set_ip(0x75D8);
    cpu.set_flags(0xF883);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3FDA8, 0x3E);
    machine.mem_store_byte(0x3FDA9, 0x31);
    machine.mem_store_byte(0x3FDAA, 0x69);
    machine.mem_store_byte(0x3FDAB, 0x9D);
    machine.mem_store_byte(0x3FDAC, 0x90);
    machine.mem_store_byte(0x3FDAD, 0x90);
    machine.mem_store_byte(0x4E07C, 0xF5);
    machine.mem_store_byte(0x4E07D, 0xBA);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x75DC);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3FDA8), 0x3E);
    EXPECT_EQ(memory.load8(0x3FDA9), 0x31);
    EXPECT_EQ(memory.load8(0x3FDAA), 0x69);
    EXPECT_EQ(memory.load8(0x3FDAB), 0x9D);
    EXPECT_EQ(memory.load8(0x3FDAC), 0x90);
    EXPECT_EQ(memory.load8(0x3FDAD), 0x90);
    EXPECT_EQ(memory.load8(0x4E07C), 0xE3);
    EXPECT_EQ(memory.load8(0x4E07D), 0x72);
}

TEST_F(MachineTest, xor_word_ds_si_6C5Eh_7645h)
{
    // Initial CPU State
    cpu.set_ax(0x5270);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x6FA4);
    cpu.set_dx(0xEFD0);
    cpu.set_cs(0x028D);
    cpu.set_ss(0x4F01);
    cpu.set_ds(0x5053);
    cpu.set_es(0xBD7C);
    cpu.set_sp(0x0000);
    cpu.set_bp(0xCDCC);
    cpu.set_si(0x3A25);
    cpu.set_di(0xD40C);
    cpu.set_ip(0x2F47);
    cpu.set_flags(0xF047);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x05817, 0x81);
    machine.mem_store_byte(0x05818, 0xB4);
    machine.mem_store_byte(0x05819, 0x5E);
    machine.mem_store_byte(0x0581A, 0x6C);
    machine.mem_store_byte(0x0581B, 0x45);
    machine.mem_store_byte(0x0581C, 0x76);
    machine.mem_store_byte(0x5ABB3, 0x3D);
    machine.mem_store_byte(0x5ABB4, 0x5C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2F4D);
    EXPECT_EQ(cpu.get_flags(), 0xF006);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x05817), 0x81);
    EXPECT_EQ(memory.load8(0x05818), 0xB4);
    EXPECT_EQ(memory.load8(0x05819), 0x5E);
    EXPECT_EQ(memory.load8(0x0581A), 0x6C);
    EXPECT_EQ(memory.load8(0x0581B), 0x45);
    EXPECT_EQ(memory.load8(0x0581C), 0x76);
    EXPECT_EQ(memory.load8(0x5ABB3), 0x78);
    EXPECT_EQ(memory.load8(0x5ABB4), 0x2A);
}

TEST_F(MachineTest, xor_word_ss_bp_F0Eh_FFD8h)
{
    // Initial CPU State
    cpu.set_ax(0xDCAF);
    cpu.set_bx(0x2CAE);
    cpu.set_cx(0xF4B4);
    cpu.set_dx(0x99AF);
    cpu.set_cs(0x6EE3);
    cpu.set_ss(0xEFDC);
    cpu.set_ds(0x415F);
    cpu.set_es(0xDECE);
    cpu.set_sp(0xAA36);
    cpu.set_bp(0x625D);
    cpu.set_si(0x0090);
    cpu.set_di(0x8366);
    cpu.set_ip(0xEC9A);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x7DACA, 0x83);
    machine.mem_store_byte(0x7DACB, 0xB6);
    machine.mem_store_byte(0x7DACC, 0xF2);
    machine.mem_store_byte(0x7DACD, 0xF0);
    machine.mem_store_byte(0x7DACE, 0xD8);
    machine.mem_store_byte(0x7DACF, 0x90);
    machine.mem_store_byte(0xF510F, 0xDC);
    machine.mem_store_byte(0xF5110, 0xED);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xEC9F);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x7DACA), 0x83);
    EXPECT_EQ(memory.load8(0x7DACB), 0xB6);
    EXPECT_EQ(memory.load8(0x7DACC), 0xF2);
    EXPECT_EQ(memory.load8(0x7DACD), 0xF0);
    EXPECT_EQ(memory.load8(0x7DACE), 0xD8);
    EXPECT_EQ(memory.load8(0x7DACF), 0x90);
    EXPECT_EQ(memory.load8(0xF510F), 0x04);
    EXPECT_EQ(memory.load8(0xF5110), 0x12);
}
