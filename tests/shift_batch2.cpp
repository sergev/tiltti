#include "fixture.h"

//
// rcl byte [ss:bp+si+0h], cl
//
TEST_F(MachineTest, rcl_byte_ss_bp_si_0h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xB53E);
    cpu.set_bx(0xE0C7);
    cpu.set_cx(0x7F02);
    cpu.set_dx(0x0000);
    cpu.set_cs(0xFA8C);
    cpu.set_ss(0x26CC);
    cpu.set_ds(0x1102);
    cpu.set_es(0xCC44);
    cpu.set_sp(0xFFB9);
    cpu.set_bp(0xE99D);
    cpu.set_si(0x39A8);
    cpu.set_di(0x03AF);
    cpu.set_ip(0xC31A);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x06BDA, 0xD2);
    machine.mem_store_byte(0x06BDB, 0x52);
    machine.mem_store_byte(0x06BDC, 0x00);
    machine.mem_store_byte(0x06BDD, 0x90);
    machine.mem_store_byte(0x06BDE, 0x90);
    machine.mem_store_byte(0x06BDF, 0x90);
    machine.mem_store_byte(0x29005, 0x94);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC31D);
    EXPECT_EQ(cpu.get_flags(), 0xF456) << show_flags(0xF456);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x06BDA), 0xD2);
    EXPECT_EQ(memory.load8(0x06BDB), 0x52);
    EXPECT_EQ(memory.load8(0x06BDC), 0x00);
    EXPECT_EQ(memory.load8(0x06BDD), 0x90);
    EXPECT_EQ(memory.load8(0x06BDE), 0x90);
    EXPECT_EQ(memory.load8(0x06BDF), 0x90);
    EXPECT_EQ(memory.load8(0x29005), 0x53);
}

//
// rcr byte [cs:bx-32A8h], cl
//
TEST_F(MachineTest, rcr_byte_cs_bx_32A8h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC182);
    cpu.set_bx(0x19F8);
    cpu.set_cx(0x683A);
    cpu.set_dx(0xDE67);
    cpu.set_cs(0xB858);
    cpu.set_ss(0xD8AF);
    cpu.set_ds(0xB958);
    cpu.set_es(0x27C8);
    cpu.set_sp(0xCD40);
    cpu.set_bp(0x8F06);
    cpu.set_si(0xB55E);
    cpu.set_di(0x0000);
    cpu.set_ip(0xC31E);
    cpu.set_flags(0xF056);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC489E, 0x2E);
    machine.mem_store_byte(0xC489F, 0xD2);
    machine.mem_store_byte(0xC48A0, 0x9F);
    machine.mem_store_byte(0xC48A1, 0x58);
    machine.mem_store_byte(0xC48A2, 0xCD);
    machine.mem_store_byte(0xC48A3, 0x90);
    machine.mem_store_byte(0xC6CD0, 0x92);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC323);
    EXPECT_EQ(cpu.get_flags(), 0xF856) << show_flags(0xF856);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC489E), 0x2E);
    EXPECT_EQ(memory.load8(0xC489F), 0xD2);
    EXPECT_EQ(memory.load8(0xC48A0), 0x9F);
    EXPECT_EQ(memory.load8(0xC48A1), 0x58);
    EXPECT_EQ(memory.load8(0xC48A2), 0xCD);
    EXPECT_EQ(memory.load8(0xC48A3), 0x90);
    EXPECT_EQ(memory.load8(0xC6CD0), 0x49);
}

//
// rcr ch, cl
//
TEST_F(MachineTest, rcr_ch_cl)
{
    // Initial CPU State
    cpu.set_ax(0xC81D);
    cpu.set_bx(0xE26A);
    cpu.set_cx(0x5218);
    cpu.set_dx(0x2DAD);
    cpu.set_cs(0xBECC);
    cpu.set_ss(0x9AE5);
    cpu.set_ds(0xA511);
    cpu.set_es(0xE7D6);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x4CD8);
    cpu.set_si(0xD862);
    cpu.set_di(0x6EB2);
    cpu.set_ip(0x35D5);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xC2295, 0x26);
    machine.mem_store_byte(0xC2296, 0xD2);
    machine.mem_store_byte(0xC2297, 0xDD);
    machine.mem_store_byte(0xC2298, 0x90);
    machine.mem_store_byte(0xC2299, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x9518);
    EXPECT_EQ(cpu.get_ip(), 0x35D8);
    EXPECT_EQ(cpu.get_flags(), 0xF8C6) << show_flags(0xF8C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC2295), 0x26);
    EXPECT_EQ(memory.load8(0xC2296), 0xD2);
    EXPECT_EQ(memory.load8(0xC2297), 0xDD);
    EXPECT_EQ(memory.load8(0xC2298), 0x90);
    EXPECT_EQ(memory.load8(0xC2299), 0x90);
}

//
// rol byte [ss:bp+di], cl
//
TEST_F(MachineTest, rol_byte_ss_bp_di_cl)
{
    // Initial CPU State
    cpu.set_ax(0xB52A);
    cpu.set_bx(0xCB73);
    cpu.set_cx(0xDF20);
    cpu.set_dx(0xA3B9);
    cpu.set_cs(0x8CE6);
    cpu.set_ss(0x527C);
    cpu.set_ds(0x9A8F);
    cpu.set_es(0x3193);
    cpu.set_sp(0xBFBF);
    cpu.set_bp(0xD698);
    cpu.set_si(0x5955);
    cpu.set_di(0x0000);
    cpu.set_ip(0xAAB4);
    cpu.set_flags(0xF843);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97914, 0xD2);
    machine.mem_store_byte(0x97915, 0x03);
    machine.mem_store_byte(0x97916, 0x90);
    machine.mem_store_byte(0x97917, 0x90);
    machine.mem_store_byte(0x97918, 0x90);
    machine.mem_store_byte(0x97919, 0x90);
    machine.mem_store_byte(0x5FE58, 0x42);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xAAB6);
    EXPECT_EQ(cpu.get_flags(), 0xF042) << show_flags(0xF042);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x97914), 0xD2);
    EXPECT_EQ(memory.load8(0x97915), 0x03);
    EXPECT_EQ(memory.load8(0x97916), 0x90);
    EXPECT_EQ(memory.load8(0x97917), 0x90);
    EXPECT_EQ(memory.load8(0x97918), 0x90);
    EXPECT_EQ(memory.load8(0x97919), 0x90);
    EXPECT_EQ(memory.load8(0x5FE58), 0x42);
}

//
// rol dh, cl
//
TEST_F(MachineTest, rol_dh_cl)
{
    // Initial CPU State
    cpu.set_ax(0x72E4);
    cpu.set_bx(0x0FF2);
    cpu.set_cx(0x331C);
    cpu.set_dx(0x6B70);
    cpu.set_cs(0xA2D4);
    cpu.set_ss(0x225F);
    cpu.set_ds(0x450F);
    cpu.set_es(0xA8E3);
    cpu.set_sp(0xE765);
    cpu.set_bp(0x5DD1);
    cpu.set_si(0x0ED8);
    cpu.set_di(0x6071);
    cpu.set_ip(0x1DD7);
    cpu.set_flags(0xF492);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA4B17, 0xD2);
    machine.mem_store_byte(0xA4B18, 0xC6);
    machine.mem_store_byte(0xA4B19, 0x90);
    machine.mem_store_byte(0xA4B1A, 0x90);
    machine.mem_store_byte(0xA4B1B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xB670);
    EXPECT_EQ(cpu.get_ip(), 0x1DD9);
    EXPECT_EQ(cpu.get_flags(), 0xFC92) << show_flags(0xFC92);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA4B17), 0xD2);
    EXPECT_EQ(memory.load8(0xA4B18), 0xC6);
    EXPECT_EQ(memory.load8(0xA4B19), 0x90);
    EXPECT_EQ(memory.load8(0xA4B1A), 0x90);
    EXPECT_EQ(memory.load8(0xA4B1B), 0x90);
}

//
// rol si, cl
//
TEST_F(MachineTest, rol_si_cl_batch2)
{
    // Initial CPU State
    cpu.set_ax(0x780F);
    cpu.set_bx(0x429B);
    cpu.set_cx(0x8D26);
    cpu.set_dx(0x30BA);
    cpu.set_cs(0x7CBA);
    cpu.set_ss(0x0BE0);
    cpu.set_ds(0x57A4);
    cpu.set_es(0x9003);
    cpu.set_sp(0x8FBC);
    cpu.set_bp(0x3693);
    cpu.set_si(0x23DE);
    cpu.set_di(0x21C7);
    cpu.set_ip(0x51E3);
    cpu.set_flags(0xF443);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x81D83, 0x2E);
    machine.mem_store_byte(0x81D84, 0xD3);
    machine.mem_store_byte(0x81D85, 0xC6);
    machine.mem_store_byte(0x81D86, 0x90);
    machine.mem_store_byte(0x81D87, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0xF788);
    EXPECT_EQ(cpu.get_ip(), 0x51E6);
    EXPECT_EQ(cpu.get_flags(), 0xFC42) << show_flags(0xFC42);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x81D83), 0x2E);
    EXPECT_EQ(memory.load8(0x81D84), 0xD3);
    EXPECT_EQ(memory.load8(0x81D85), 0xC6);
    EXPECT_EQ(memory.load8(0x81D86), 0x90);
    EXPECT_EQ(memory.load8(0x81D87), 0x90);
}

//
// rol word [ss:bp+41h], cl
//
TEST_F(MachineTest, rol_word_ss_bp_41h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x8332);
    cpu.set_bx(0x65EF);
    cpu.set_cx(0x1424);
    cpu.set_dx(0xF357);
    cpu.set_cs(0x4E46);
    cpu.set_ss(0x81A2);
    cpu.set_ds(0xD5E7);
    cpu.set_es(0x939D);
    cpu.set_sp(0x31E6);
    cpu.set_bp(0x3D02);
    cpu.set_si(0x98DF);
    cpu.set_di(0xADD7);
    cpu.set_ip(0x348D);
    cpu.set_flags(0xF882);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x518ED, 0xD3);
    machine.mem_store_byte(0x518EE, 0x46);
    machine.mem_store_byte(0x518EF, 0x41);
    machine.mem_store_byte(0x518F0, 0x90);
    machine.mem_store_byte(0x518F1, 0x90);
    machine.mem_store_byte(0x85763, 0xFF);
    machine.mem_store_byte(0x85764, 0x9C);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x3490);
    EXPECT_EQ(cpu.get_flags(), 0xF083) << show_flags(0xF083);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x518ED), 0xD3);
    EXPECT_EQ(memory.load8(0x518EE), 0x46);
    EXPECT_EQ(memory.load8(0x518EF), 0x41);
    EXPECT_EQ(memory.load8(0x518F0), 0x90);
    EXPECT_EQ(memory.load8(0x518F1), 0x90);
    EXPECT_EQ(memory.load8(0x85763), 0xF9);
    EXPECT_EQ(memory.load8(0x85764), 0xCF);
}

//
// ror dl, cl
//
TEST_F(MachineTest, ror_dl_cl)
{
    // Initial CPU State
    cpu.set_ax(0x251E);
    cpu.set_bx(0xD9DC);
    cpu.set_cx(0x172C);
    cpu.set_dx(0xC8F5);
    cpu.set_cs(0xA10B);
    cpu.set_ss(0xC338);
    cpu.set_ds(0xAC65);
    cpu.set_es(0xCF4A);
    cpu.set_sp(0x7B8C);
    cpu.set_bp(0x2522);
    cpu.set_si(0x0F58);
    cpu.set_di(0x0000);
    cpu.set_ip(0x2208);
    cpu.set_flags(0xF8C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA32B8, 0x3E);
    machine.mem_store_byte(0xA32B9, 0xD2);
    machine.mem_store_byte(0xA32BA, 0xCA);
    machine.mem_store_byte(0xA32BB, 0x90);
    machine.mem_store_byte(0xA32BC, 0x90);
    machine.mem_store_byte(0xA32BD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0xC85F);
    EXPECT_EQ(cpu.get_ip(), 0x220B);
    EXPECT_EQ(cpu.get_flags(), 0xF8C6) << show_flags(0xF8C6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA32B8), 0x3E);
    EXPECT_EQ(memory.load8(0xA32B9), 0xD2);
    EXPECT_EQ(memory.load8(0xA32BA), 0xCA);
    EXPECT_EQ(memory.load8(0xA32BB), 0x90);
    EXPECT_EQ(memory.load8(0xA32BC), 0x90);
    EXPECT_EQ(memory.load8(0xA32BD), 0x90);
}

//
// ror word [ds:bx+di-2FC1h], cl
//
TEST_F(MachineTest, ror_word_ds_bx_di_2FC1h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x1EBD);
    cpu.set_cx(0x1B1A);
    cpu.set_dx(0xE390);
    cpu.set_cs(0xB11D);
    cpu.set_ss(0xDC0E);
    cpu.set_ds(0xBD0C);
    cpu.set_es(0xC77C);
    cpu.set_sp(0x1302);
    cpu.set_bp(0x518F);
    cpu.set_si(0x0000);
    cpu.set_di(0xD146);
    cpu.set_ip(0xA8EA);
    cpu.set_flags(0xF4C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBBABA, 0xD3);
    machine.mem_store_byte(0xBBABB, 0x89);
    machine.mem_store_byte(0xBBABC, 0x3F);
    machine.mem_store_byte(0xBBABD, 0xD0);
    machine.mem_store_byte(0xBBABE, 0x90);
    machine.mem_store_byte(0xBBABF, 0x90);
    machine.mem_store_byte(0xC9102, 0xF5);
    machine.mem_store_byte(0xC9103, 0x91);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA8EE);
    EXPECT_EQ(cpu.get_flags(), 0xFCC6) << show_flags(0xFCC6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBBABA), 0xD3);
    EXPECT_EQ(memory.load8(0xBBABB), 0x89);
    EXPECT_EQ(memory.load8(0xBBABC), 0x3F);
    EXPECT_EQ(memory.load8(0xBBABD), 0xD0);
    EXPECT_EQ(memory.load8(0xBBABE), 0x90);
    EXPECT_EQ(memory.load8(0xBBABF), 0x90);
    EXPECT_EQ(memory.load8(0xC9102), 0x64);
    EXPECT_EQ(memory.load8(0xC9103), 0x7D);
}

//
// sar byte [ss:bp-7486h], cl
//
TEST_F(MachineTest, sar_byte_ss_bp_7486h_cl)
{
    // Initial CPU State
    cpu.set_ax(0x46BE);
    cpu.set_bx(0xA99C);
    cpu.set_cx(0x8120);
    cpu.set_dx(0x0E54);
    cpu.set_cs(0x1E3C);
    cpu.set_ss(0xBDF8);
    cpu.set_ds(0x0B06);
    cpu.set_es(0x5E3A);
    cpu.set_sp(0x644A);
    cpu.set_bp(0x0C56);
    cpu.set_si(0xC9FD);
    cpu.set_di(0x823A);
    cpu.set_ip(0xE3C5);
    cpu.set_flags(0xFC12);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2C785, 0x36);
    machine.mem_store_byte(0x2C786, 0xD2);
    machine.mem_store_byte(0x2C787, 0xBE);
    machine.mem_store_byte(0x2C788, 0x7A);
    machine.mem_store_byte(0x2C789, 0x8B);
    machine.mem_store_byte(0xC7750, 0xF8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE3CA);
    EXPECT_EQ(cpu.get_flags(), 0xF487) << show_flags(0xF487);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x2C785), 0x36);
    EXPECT_EQ(memory.load8(0x2C786), 0xD2);
    EXPECT_EQ(memory.load8(0x2C787), 0xBE);
    EXPECT_EQ(memory.load8(0x2C788), 0x7A);
    EXPECT_EQ(memory.load8(0x2C789), 0x8B);
    EXPECT_EQ(memory.load8(0xC7750), 0xFF);
}

//
// sar cx, cl
//
TEST_F(MachineTest, sar_cx_cl)
{
    // Initial CPU State
    cpu.set_ax(0xD3F4);
    cpu.set_bx(0x3243);
    cpu.set_cx(0x2708);
    cpu.set_dx(0xEB78);
    cpu.set_cs(0xC99C);
    cpu.set_ss(0xEB0F);
    cpu.set_ds(0xBF7F);
    cpu.set_es(0x29FF);
    cpu.set_sp(0xF215);
    cpu.set_bp(0x5542);
    cpu.set_si(0x7F0E);
    cpu.set_di(0x8FDA);
    cpu.set_ip(0x4995);
    cpu.set_flags(0xF483);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCE355, 0x2E);
    machine.mem_store_byte(0xCE356, 0xD3);
    machine.mem_store_byte(0xCE357, 0xF9);
    machine.mem_store_byte(0xCE358, 0x90);
    machine.mem_store_byte(0xCE359, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0027);
    EXPECT_EQ(cpu.get_ip(), 0x4998);
    EXPECT_EQ(cpu.get_flags(), 0xF406) << show_flags(0xF406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCE355), 0x2E);
    EXPECT_EQ(memory.load8(0xCE356), 0xD3);
    EXPECT_EQ(memory.load8(0xCE357), 0xF9);
    EXPECT_EQ(memory.load8(0xCE358), 0x90);
    EXPECT_EQ(memory.load8(0xCE359), 0x90);
}

//
// shl byte [ds:bx+di]
//
TEST_F(MachineTest, shl_byte_ds_bx_di)
{
    // Initial CPU State
    cpu.set_ax(0xEFDD);
    cpu.set_bx(0x1EB2);
    cpu.set_cx(0xEC3E);
    cpu.set_dx(0x16D8);
    cpu.set_cs(0x2833);
    cpu.set_ss(0x8395);
    cpu.set_ds(0xD967);
    cpu.set_es(0xD3FE);
    cpu.set_sp(0x714E);
    cpu.set_bp(0xD3A5);
    cpu.set_si(0x9362);
    cpu.set_di(0x8F34);
    cpu.set_ip(0xCB65);
    cpu.set_flags(0xFC47);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x34E95, 0xD0);
    machine.mem_store_byte(0x34E96, 0x21);
    machine.mem_store_byte(0x34E97, 0x90);
    machine.mem_store_byte(0x34E98, 0x90);
    machine.mem_store_byte(0x34E99, 0x90);
    machine.mem_store_byte(0xE4456, 0xBE);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCB67);
    EXPECT_EQ(cpu.get_flags(), 0xFC13) << show_flags(0xFC13);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x34E95), 0xD0);
    EXPECT_EQ(memory.load8(0x34E96), 0x21);
    EXPECT_EQ(memory.load8(0x34E97), 0x90);
    EXPECT_EQ(memory.load8(0x34E98), 0x90);
    EXPECT_EQ(memory.load8(0x34E99), 0x90);
    EXPECT_EQ(memory.load8(0xE4456), 0x7C);
}

//
// shl cx, cl
//
TEST_F(MachineTest, shl_cx_cl)
{
    // Initial CPU State
    cpu.set_ax(0x5D70);
    cpu.set_bx(0x3070);
    cpu.set_cx(0x9826);
    cpu.set_dx(0x431B);
    cpu.set_cs(0xCA3C);
    cpu.set_ss(0x7F12);
    cpu.set_ds(0xFB27);
    cpu.set_es(0xB670);
    cpu.set_sp(0x46C3);
    cpu.set_bp(0x21B3);
    cpu.set_si(0xD487);
    cpu.set_di(0xF3EF);
    cpu.set_ip(0xFC83);
    cpu.set_flags(0xF0C7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDA043, 0xD3);
    machine.mem_store_byte(0xDA044, 0xE1);
    machine.mem_store_byte(0xDA045, 0x90);
    machine.mem_store_byte(0xDA046, 0x90);
    machine.mem_store_byte(0xDA047, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0xFC85);
    EXPECT_EQ(cpu.get_flags(), 0xF046) << show_flags(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDA043), 0xD3);
    EXPECT_EQ(memory.load8(0xDA044), 0xE1);
    EXPECT_EQ(memory.load8(0xDA045), 0x90);
    EXPECT_EQ(memory.load8(0xDA046), 0x90);
    EXPECT_EQ(memory.load8(0xDA047), 0x90);
}

//
// shl dx, cl
//
TEST_F(MachineTest, shl_dx_cl)
{
    // Initial CPU State
    cpu.set_ax(0xA5AF);
    cpu.set_bx(0x0CC4);
    cpu.set_cx(0xB32A);
    cpu.set_dx(0xE2F3);
    cpu.set_cs(0xD02C);
    cpu.set_ss(0xAED3);
    cpu.set_ds(0x46D2);
    cpu.set_es(0xE202);
    cpu.set_sp(0x8CCC);
    cpu.set_bp(0x2464);
    cpu.set_si(0x0000);
    cpu.set_di(0x1B04);
    cpu.set_ip(0x79C0);
    cpu.set_flags(0xF807);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD7C80, 0xD3);
    machine.mem_store_byte(0xD7C81, 0xE2);
    machine.mem_store_byte(0xD7C82, 0x90);
    machine.mem_store_byte(0xD7C83, 0x90);
    machine.mem_store_byte(0xD7C84, 0x90);
    machine.mem_store_byte(0xD7C85, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_dx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0x79C2);
    EXPECT_EQ(cpu.get_flags(), 0xF046) << show_flags(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD7C80), 0xD3);
    EXPECT_EQ(memory.load8(0xD7C81), 0xE2);
    EXPECT_EQ(memory.load8(0xD7C82), 0x90);
    EXPECT_EQ(memory.load8(0xD7C83), 0x90);
    EXPECT_EQ(memory.load8(0xD7C84), 0x90);
    EXPECT_EQ(memory.load8(0xD7C85), 0x90);
}

//
// shl word [ds:di-6h]
//
TEST_F(MachineTest, shl_word_ds_di_6h)
{
    // Initial CPU State
    cpu.set_ax(0xA4EE);
    cpu.set_bx(0xCB12);
    cpu.set_cx(0x0D28);
    cpu.set_dx(0x0233);
    cpu.set_cs(0xD100);
    cpu.set_ss(0x8A63);
    cpu.set_ds(0x7837);
    cpu.set_es(0x1ECB);
    cpu.set_sp(0x3568);
    cpu.set_bp(0x794E);
    cpu.set_si(0x7CBE);
    cpu.set_di(0xC8AF);
    cpu.set_ip(0x70BE);
    cpu.set_flags(0xF417);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xD80BE, 0xD1);
    machine.mem_store_byte(0xD80BF, 0x65);
    machine.mem_store_byte(0xD80C0, 0xFA);
    machine.mem_store_byte(0xD80C1, 0x90);
    machine.mem_store_byte(0xD80C2, 0x90);
    machine.mem_store_byte(0xD80C3, 0x90);
    machine.mem_store_byte(0x84C19, 0x1D);
    machine.mem_store_byte(0x84C1A, 0x5F);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x70C1);
    EXPECT_EQ(cpu.get_flags(), 0xFC96) << show_flags(0xFC96);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xD80BE), 0xD1);
    EXPECT_EQ(memory.load8(0xD80BF), 0x65);
    EXPECT_EQ(memory.load8(0xD80C0), 0xFA);
    EXPECT_EQ(memory.load8(0xD80C1), 0x90);
    EXPECT_EQ(memory.load8(0xD80C2), 0x90);
    EXPECT_EQ(memory.load8(0xD80C3), 0x90);
    EXPECT_EQ(memory.load8(0x84C19), 0x3A);
    EXPECT_EQ(memory.load8(0x84C1A), 0xBE);
}

//
// shl word [ss:bx-5Ch], cl
//
TEST_F(MachineTest, shl_word_ss_bx_5Ch_cl)
{
    // Initial CPU State
    cpu.set_ax(0xAE09);
    cpu.set_bx(0x7EFC);
    cpu.set_cx(0x0F20);
    cpu.set_dx(0x58E9);
    cpu.set_cs(0x879A);
    cpu.set_ss(0xED04);
    cpu.set_ds(0xD9F2);
    cpu.set_es(0xB40F);
    cpu.set_sp(0x7D79);
    cpu.set_bp(0x2F65);
    cpu.set_si(0xFE75);
    cpu.set_di(0x2560);
    cpu.set_ip(0x2910);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8A2B0, 0x36);
    machine.mem_store_byte(0x8A2B1, 0xD3);
    machine.mem_store_byte(0x8A2B2, 0x67);
    machine.mem_store_byte(0x8A2B3, 0xA4);
    machine.mem_store_byte(0x8A2B4, 0x90);
    machine.mem_store_byte(0x8A2B5, 0x90);
    machine.mem_store_byte(0xF4EE0, 0x20);
    machine.mem_store_byte(0xF4EE1, 0xCB);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x2914);
    EXPECT_EQ(cpu.get_flags(), 0xF446) << show_flags(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x8A2B0), 0x36);
    EXPECT_EQ(memory.load8(0x8A2B1), 0xD3);
    EXPECT_EQ(memory.load8(0x8A2B2), 0x67);
    EXPECT_EQ(memory.load8(0x8A2B3), 0xA4);
    EXPECT_EQ(memory.load8(0x8A2B4), 0x90);
    EXPECT_EQ(memory.load8(0x8A2B5), 0x90);
    EXPECT_EQ(memory.load8(0xF4EE0), 0x00);
    EXPECT_EQ(memory.load8(0xF4EE1), 0x00);
}

//
// shr bx, cl
//
TEST_F(MachineTest, shr_bx_cl)
{
    // Initial CPU State
    cpu.set_ax(0x1F34);
    cpu.set_bx(0xF800);
    cpu.set_cx(0x0718);
    cpu.set_dx(0x2E19);
    cpu.set_cs(0x5234);
    cpu.set_ss(0x224E);
    cpu.set_ds(0xA3BB);
    cpu.set_es(0x941B);
    cpu.set_sp(0x0000);
    cpu.set_bp(0x2D68);
    cpu.set_si(0x970B);
    cpu.set_di(0x6403);
    cpu.set_ip(0x2DE8);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x55128, 0x2E);
    machine.mem_store_byte(0x55129, 0xD3);
    machine.mem_store_byte(0x5512A, 0xEB);
    machine.mem_store_byte(0x5512B, 0x90);
    machine.mem_store_byte(0x5512C, 0x90);
    machine.mem_store_byte(0x5512D, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x0000);
    EXPECT_EQ(cpu.get_ip(), 0x2DEB);
    EXPECT_EQ(cpu.get_flags(), 0xF446) << show_flags(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x55128), 0x2E);
    EXPECT_EQ(memory.load8(0x55129), 0xD3);
    EXPECT_EQ(memory.load8(0x5512A), 0xEB);
    EXPECT_EQ(memory.load8(0x5512B), 0x90);
    EXPECT_EQ(memory.load8(0x5512C), 0x90);
    EXPECT_EQ(memory.load8(0x5512D), 0x90);
}

//
// shr byte [ss:bp+di+6Eh], cl
//
TEST_F(MachineTest, shr_byte_ss_bp_di_6Eh_cl)
{
    // Initial CPU State
    cpu.set_ax(0x23A2);
    cpu.set_bx(0xFC05);
    cpu.set_cx(0xC222);
    cpu.set_dx(0xCE1A);
    cpu.set_cs(0x96A9);
    cpu.set_ss(0xCE1D);
    cpu.set_ds(0x0663);
    cpu.set_es(0xC6F1);
    cpu.set_sp(0x66AA);
    cpu.set_bp(0xC4CC);
    cpu.set_si(0xAA79);
    cpu.set_di(0xCB28);
    cpu.set_ip(0x05A7);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97037, 0xD2);
    machine.mem_store_byte(0x97038, 0x6B);
    machine.mem_store_byte(0x97039, 0x6E);
    machine.mem_store_byte(0x9703A, 0x90);
    machine.mem_store_byte(0x9703B, 0x90);
    machine.mem_store_byte(0xD7232, 0xB5);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x05AA);
    EXPECT_EQ(cpu.get_flags(), 0xF046) << show_flags(0xF046);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x97037), 0xD2);
    EXPECT_EQ(memory.load8(0x97038), 0x6B);
    EXPECT_EQ(memory.load8(0x97039), 0x6E);
    EXPECT_EQ(memory.load8(0x9703A), 0x90);
    EXPECT_EQ(memory.load8(0x9703B), 0x90);
    EXPECT_EQ(memory.load8(0xD7232), 0x00);
}

//
// shr word [ds:bx-3BF8h], cl
//
TEST_F(MachineTest, shr_word_ds_bx_3BF8h_cl)
{
    // Initial CPU State
    cpu.set_ax(0xACD4);
    cpu.set_bx(0x030B);
    cpu.set_cx(0xE404);
    cpu.set_dx(0xD539);
    cpu.set_cs(0x0DB1);
    cpu.set_ss(0x8CC9);
    cpu.set_ds(0x2880);
    cpu.set_es(0x26B8);
    cpu.set_sp(0x836E);
    cpu.set_bp(0x0138);
    cpu.set_si(0xFD7E);
    cpu.set_di(0xD713);
    cpu.set_ip(0x9B56);
    cpu.set_flags(0xFCD2);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x17666, 0xD3);
    machine.mem_store_byte(0x17667, 0xAF);
    machine.mem_store_byte(0x17668, 0x08);
    machine.mem_store_byte(0x17669, 0xC4);
    machine.mem_store_byte(0x1766A, 0x90);
    machine.mem_store_byte(0x1766B, 0x90);
    machine.mem_store_byte(0x34F13, 0x43);
    machine.mem_store_byte(0x34F14, 0x55);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x9B5A);
    EXPECT_EQ(cpu.get_flags(), 0xF402) << show_flags(0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x17666), 0xD3);
    EXPECT_EQ(memory.load8(0x17667), 0xAF);
    EXPECT_EQ(memory.load8(0x17668), 0x08);
    EXPECT_EQ(memory.load8(0x17669), 0xC4);
    EXPECT_EQ(memory.load8(0x1766A), 0x90);
    EXPECT_EQ(memory.load8(0x1766B), 0x90);
    EXPECT_EQ(memory.load8(0x34F13), 0x54);
    EXPECT_EQ(memory.load8(0x34F14), 0x05);
}

//
// shr word [es:bp+si], cl
//
TEST_F(MachineTest, shr_word_es_bp_si_cl)
{
    // Initial CPU State
    cpu.set_ax(0xE993);
    cpu.set_bx(0x2DE5);
    cpu.set_cx(0x3816);
    cpu.set_dx(0x231D);
    cpu.set_cs(0xD6C5);
    cpu.set_ss(0xD66B);
    cpu.set_ds(0x4709);
    cpu.set_es(0x6005);
    cpu.set_sp(0xDEAD);
    cpu.set_bp(0x4D9D);
    cpu.set_si(0x0000);
    cpu.set_di(0x7347);
    cpu.set_ip(0x4662);
    cpu.set_flags(0xFC16);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xDB2B2, 0x26);
    machine.mem_store_byte(0xDB2B3, 0xD3);
    machine.mem_store_byte(0xDB2B4, 0x2A);
    machine.mem_store_byte(0xDB2B5, 0x90);
    machine.mem_store_byte(0xDB2B6, 0x90);
    machine.mem_store_byte(0xDB2B7, 0x90);
    machine.mem_store_byte(0x64DED, 0x22);
    machine.mem_store_byte(0x64DEE, 0x55);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x4665);
    EXPECT_EQ(cpu.get_flags(), 0xF446) << show_flags(0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xDB2B2), 0x26);
    EXPECT_EQ(memory.load8(0xDB2B3), 0xD3);
    EXPECT_EQ(memory.load8(0xDB2B4), 0x2A);
    EXPECT_EQ(memory.load8(0xDB2B5), 0x90);
    EXPECT_EQ(memory.load8(0xDB2B6), 0x90);
    EXPECT_EQ(memory.load8(0xDB2B7), 0x90);
    EXPECT_EQ(memory.load8(0x64DED), 0x00);
    EXPECT_EQ(memory.load8(0x64DEE), 0x00);
}

//
// shr word [ss:bp+si-6Dh], cl
//
TEST_F(MachineTest, shr_word_ss_bp_si_6Dh_cl)
{
    // Initial CPU State
    cpu.set_ax(0xDEA2);
    cpu.set_bx(0xB038);
    cpu.set_cx(0x3F08);
    cpu.set_dx(0x603D);
    cpu.set_cs(0x5EA1);
    cpu.set_ss(0xAE75);
    cpu.set_ds(0x69D0);
    cpu.set_es(0x69EC);
    cpu.set_sp(0x82B2);
    cpu.set_bp(0xAF83);
    cpu.set_si(0xD4BD);
    cpu.set_di(0x2B7D);
    cpu.set_ip(0xE227);
    cpu.set_flags(0xFC97);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x6CC37, 0xD3);
    machine.mem_store_byte(0x6CC38, 0x6A);
    machine.mem_store_byte(0x6CC39, 0x93);
    machine.mem_store_byte(0x6CC3A, 0x90);
    machine.mem_store_byte(0x6CC3B, 0x90);
    machine.mem_store_byte(0xB6B23, 0x83);
    machine.mem_store_byte(0xB6B24, 0xC3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xE22A);
    EXPECT_EQ(cpu.get_flags(), 0xF407) << show_flags(0xF407);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x6CC37), 0xD3);
    EXPECT_EQ(memory.load8(0x6CC38), 0x6A);
    EXPECT_EQ(memory.load8(0x6CC39), 0x93);
    EXPECT_EQ(memory.load8(0x6CC3A), 0x90);
    EXPECT_EQ(memory.load8(0x6CC3B), 0x90);
    EXPECT_EQ(memory.load8(0xB6B23), 0xC3);
    EXPECT_EQ(memory.load8(0xB6B24), 0x00);
}
