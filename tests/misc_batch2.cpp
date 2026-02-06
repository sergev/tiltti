#include "fixture.h"

//
// aaa
//
TEST_F(MachineTest, aaa_batch2)
{
    // Initial CPU State
    cpu.set_ax(0x7B15);
    cpu.set_bx(0x1369);
    cpu.set_cx(0x84D0);
    cpu.set_dx(0x18DD);
    cpu.set_cs(0x2DCA);
    cpu.set_ss(0xC7B1);
    cpu.set_ds(0x085C);
    cpu.set_es(0xBD6B);
    cpu.set_sp(0xA25C);
    cpu.set_bp(0x5AB5);
    cpu.set_si(0xEC30);
    cpu.set_di(0xDDC9);
    cpu.set_ip(0xD158);
    cpu.set_flags(0xFC17);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3ADF8, 0x37);
    machine.mem_store_byte(0x3ADF9, 0x90);
    machine.mem_store_byte(0x3ADFA, 0x90);
    machine.mem_store_byte(0x3ADFB, 0x90);
    machine.mem_store_byte(0x3ADFC, 0x90);
    machine.mem_store_byte(0x3ADFD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x7C0B);
    EXPECT_EQ(cpu.get_ip(), 0xD159);
    EXPECT_EQ(cpu.get_flags(), 0xF417);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x3ADF8), 0x37);
    EXPECT_EQ(memory.load8(0x3ADF9), 0x90);
    EXPECT_EQ(memory.load8(0x3ADFA), 0x90);
    EXPECT_EQ(memory.load8(0x3ADFB), 0x90);
    EXPECT_EQ(memory.load8(0x3ADFC), 0x90);
    EXPECT_EQ(memory.load8(0x3ADFD), 0x90);
}

//
// aad 3Ah
//
TEST_F(MachineTest, aad_3Ah)
{
    // Initial CPU State
    cpu.set_ax(0xF416);
    cpu.set_bx(0xD0C7);
    cpu.set_cx(0x5614);
    cpu.set_dx(0xB130);
    cpu.set_cs(0x95B8);
    cpu.set_ss(0xABB1);
    cpu.set_ds(0x780D);
    cpu.set_es(0x2060);
    cpu.set_sp(0xBE88);
    cpu.set_bp(0x3C7B);
    cpu.set_si(0x1EB2);
    cpu.set_di(0xEC4C);
    cpu.set_ip(0xE73A);
    cpu.set_flags(0xFC57);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA42BA, 0xD5);
    machine.mem_store_byte(0xA42BB, 0x3A);
    machine.mem_store_byte(0xA42BC, 0x90);
    machine.mem_store_byte(0xA42BD, 0x90);
    machine.mem_store_byte(0xA42BE, 0x90);
    machine.mem_store_byte(0xA42BF, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x005E);
    EXPECT_EQ(cpu.get_ip(), 0xE73C);
    EXPECT_EQ(cpu.get_flags(), 0xF402);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA42BA), 0xD5);
    EXPECT_EQ(memory.load8(0xA42BB), 0x3A);
    EXPECT_EQ(memory.load8(0xA42BC), 0x90);
    EXPECT_EQ(memory.load8(0xA42BD), 0x90);
    EXPECT_EQ(memory.load8(0xA42BE), 0x90);
    EXPECT_EQ(memory.load8(0xA42BF), 0x90);
}

//
// aad 9Eh
//
TEST_F(MachineTest, aad_9Eh)
{
    // Initial CPU State
    cpu.set_ax(0x8A3C);
    cpu.set_bx(0xAD76);
    cpu.set_cx(0xCEFE);
    cpu.set_dx(0x927C);
    cpu.set_cs(0x5ABC);
    cpu.set_ss(0xE425);
    cpu.set_ds(0x02AA);
    cpu.set_es(0xA146);
    cpu.set_sp(0x68A4);
    cpu.set_bp(0x0000);
    cpu.set_si(0xE08D);
    cpu.set_di(0xAE40);
    cpu.set_ip(0xE175);
    cpu.set_flags(0xF856);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x68D35, 0xD5);
    machine.mem_store_byte(0x68D36, 0x9E);
    machine.mem_store_byte(0x68D37, 0x90);
    machine.mem_store_byte(0x68D38, 0x90);
    machine.mem_store_byte(0x68D39, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0068);
    EXPECT_EQ(cpu.get_ip(), 0xE177);
    EXPECT_EQ(cpu.get_flags(), 0xF012);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x68D35), 0xD5);
    EXPECT_EQ(memory.load8(0x68D36), 0x9E);
    EXPECT_EQ(memory.load8(0x68D37), 0x90);
    EXPECT_EQ(memory.load8(0x68D38), 0x90);
    EXPECT_EQ(memory.load8(0x68D39), 0x90);
}

//
// aad B7h
//
TEST_F(MachineTest, aad_B7h)
{
    // Initial CPU State
    cpu.set_ax(0x4C88);
    cpu.set_bx(0xA722);
    cpu.set_cx(0x030C);
    cpu.set_dx(0x31BE);
    cpu.set_cs(0x5BE5);
    cpu.set_ss(0x10F2);
    cpu.set_ds(0x4F2E);
    cpu.set_es(0xE845);
    cpu.set_sp(0xEE14);
    cpu.set_bp(0xD351);
    cpu.set_si(0x3DC3);
    cpu.set_di(0xD51C);
    cpu.set_ip(0x0B68);
    cpu.set_flags(0xF492);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5C9B8, 0xD5);
    machine.mem_store_byte(0x5C9B9, 0xB7);
    machine.mem_store_byte(0x5C9BA, 0x90);
    machine.mem_store_byte(0x5C9BB, 0x90);
    machine.mem_store_byte(0x5C9BC, 0x90);
    machine.mem_store_byte(0x5C9BD, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x00DC);
    EXPECT_EQ(cpu.get_ip(), 0x0B6A);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5C9B8), 0xD5);
    EXPECT_EQ(memory.load8(0x5C9B9), 0xB7);
    EXPECT_EQ(memory.load8(0x5C9BA), 0x90);
    EXPECT_EQ(memory.load8(0x5C9BB), 0x90);
    EXPECT_EQ(memory.load8(0x5C9BC), 0x90);
    EXPECT_EQ(memory.load8(0x5C9BD), 0x90);
}

//
// aad EBh
//
TEST_F(MachineTest, aad_EBh)
{
    // Initial CPU State
    cpu.set_ax(0x7476);
    cpu.set_bx(0x909D);
    cpu.set_cx(0x8892);
    cpu.set_dx(0x585D);
    cpu.set_cs(0xA126);
    cpu.set_ss(0x6FC0);
    cpu.set_ds(0xEF3E);
    cpu.set_es(0x12AB);
    cpu.set_sp(0xED74);
    cpu.set_bp(0x7C0D);
    cpu.set_si(0x1215);
    cpu.set_di(0x3783);
    cpu.set_ip(0x47F6);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA5A56, 0xD5);
    machine.mem_store_byte(0xA5A57, 0xEB);
    machine.mem_store_byte(0xA5A58, 0x90);
    machine.mem_store_byte(0xA5A59, 0x90);
    machine.mem_store_byte(0xA5A5A, 0x90);
    machine.mem_store_byte(0xA5A5B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x00F2);
    EXPECT_EQ(cpu.get_ip(), 0x47F8);
    EXPECT_EQ(cpu.get_flags(), 0xF892);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA5A56), 0xD5);
    EXPECT_EQ(memory.load8(0xA5A57), 0xEB);
    EXPECT_EQ(memory.load8(0xA5A58), 0x90);
    EXPECT_EQ(memory.load8(0xA5A59), 0x90);
    EXPECT_EQ(memory.load8(0xA5A5A), 0x90);
    EXPECT_EQ(memory.load8(0xA5A5B), 0x90);
}

//
// aam 1h
//
TEST_F(MachineTest, aam_1h)
{
    // Initial CPU State
    cpu.set_ax(0x464E);
    cpu.set_bx(0xCD46);
    cpu.set_cx(0xB9DA);
    cpu.set_dx(0x3863);
    cpu.set_cs(0x674E);
    cpu.set_ss(0x0740);
    cpu.set_ds(0x9407);
    cpu.set_es(0xB08C);
    cpu.set_sp(0xCDB9);
    cpu.set_bp(0xD2F0);
    cpu.set_si(0x144D);
    cpu.set_di(0xB4FB);
    cpu.set_ip(0xE99E);
    cpu.set_flags(0xF453);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x75E7E, 0xD4);
    machine.mem_store_byte(0x75E7F, 0x01);
    machine.mem_store_byte(0x75E80, 0x90);
    machine.mem_store_byte(0x75E81, 0x90);
    machine.mem_store_byte(0x75E82, 0x90);
    machine.mem_store_byte(0x75E83, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x4E00);
    EXPECT_EQ(cpu.get_ip(), 0xE9A0);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x75E7E), 0xD4);
    EXPECT_EQ(memory.load8(0x75E7F), 0x01);
    EXPECT_EQ(memory.load8(0x75E80), 0x90);
    EXPECT_EQ(memory.load8(0x75E81), 0x90);
    EXPECT_EQ(memory.load8(0x75E82), 0x90);
    EXPECT_EQ(memory.load8(0x75E83), 0x90);
}

//
// aam 3Ch
//
TEST_F(MachineTest, aam_3Ch)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0xBE8A);
    cpu.set_cx(0xD38A);
    cpu.set_dx(0x3A15);
    cpu.set_cs(0x5155);
    cpu.set_ss(0xAFF3);
    cpu.set_ds(0x622F);
    cpu.set_es(0x9D6C);
    cpu.set_sp(0xF371);
    cpu.set_bp(0xBDA9);
    cpu.set_si(0x827C);
    cpu.set_di(0xB1DB);
    cpu.set_ip(0x7CE4);
    cpu.set_flags(0xFC42);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x59234, 0xD4);
    machine.mem_store_byte(0x59235, 0x3C);
    machine.mem_store_byte(0x59236, 0x90);
    machine.mem_store_byte(0x59237, 0x90);
    machine.mem_store_byte(0x59238, 0x90);
    machine.mem_store_byte(0x59239, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x7CE6);
    EXPECT_EQ(cpu.get_flags(), 0xF446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x59234), 0xD4);
    EXPECT_EQ(memory.load8(0x59235), 0x3C);
    EXPECT_EQ(memory.load8(0x59236), 0x90);
    EXPECT_EQ(memory.load8(0x59237), 0x90);
    EXPECT_EQ(memory.load8(0x59238), 0x90);
    EXPECT_EQ(memory.load8(0x59239), 0x90);
}

//
// aam 87h
//
TEST_F(MachineTest, aam_87h)
{
    // Initial CPU State
    cpu.set_ax(0x5064);
    cpu.set_bx(0x277F);
    cpu.set_cx(0x114C);
    cpu.set_dx(0x727F);
    cpu.set_cs(0x585D);
    cpu.set_ss(0xF166);
    cpu.set_ds(0xCE62);
    cpu.set_es(0xA857);
    cpu.set_sp(0x6FAF);
    cpu.set_bp(0x3EB6);
    cpu.set_si(0xDD6E);
    cpu.set_di(0x97CE);
    cpu.set_ip(0x9443);
    cpu.set_flags(0xF8C3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x61A13, 0xD4);
    machine.mem_store_byte(0x61A14, 0x87);
    machine.mem_store_byte(0x61A15, 0x90);
    machine.mem_store_byte(0x61A16, 0x90);
    machine.mem_store_byte(0x61A17, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0064);
    EXPECT_EQ(cpu.get_ip(), 0x9445);
    EXPECT_EQ(cpu.get_flags(), 0xF002);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x61A13), 0xD4);
    EXPECT_EQ(memory.load8(0x61A14), 0x87);
    EXPECT_EQ(memory.load8(0x61A15), 0x90);
    EXPECT_EQ(memory.load8(0x61A16), 0x90);
    EXPECT_EQ(memory.load8(0x61A17), 0x90);
}

//
// aam C6h
//
TEST_F(MachineTest, aam_C6h)
{
    // Initial CPU State
    cpu.set_ax(0x6F98);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x7112);
    cpu.set_dx(0xE7D4);
    cpu.set_cs(0xFD32);
    cpu.set_ss(0xEE5E);
    cpu.set_ds(0xCB57);
    cpu.set_es(0x1EFD);
    cpu.set_sp(0xBD1C);
    cpu.set_bp(0xD6D8);
    cpu.set_si(0x4C7C);
    cpu.set_di(0x002C);
    cpu.set_ip(0x062E);
    cpu.set_flags(0xFC07);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xFD94E, 0xD4);
    machine.mem_store_byte(0xFD94F, 0xC6);
    machine.mem_store_byte(0xFD950, 0x90);
    machine.mem_store_byte(0xFD951, 0x90);
    machine.mem_store_byte(0xFD952, 0x90);
    machine.mem_store_byte(0xFD953, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x0098);
    EXPECT_EQ(cpu.get_ip(), 0x0630);
    EXPECT_EQ(cpu.get_flags(), 0xF482);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xFD94E), 0xD4);
    EXPECT_EQ(memory.load8(0xFD94F), 0xC6);
    EXPECT_EQ(memory.load8(0xFD950), 0x90);
    EXPECT_EQ(memory.load8(0xFD951), 0x90);
    EXPECT_EQ(memory.load8(0xFD952), 0x90);
    EXPECT_EQ(memory.load8(0xFD953), 0x90);
}

//
// aas
//
TEST_F(MachineTest, aas_batch2)
{
    // Initial CPU State
    cpu.set_ax(0xCB1C);
    cpu.set_bx(0x6F43);
    cpu.set_cx(0xFD6E);
    cpu.set_dx(0x54EF);
    cpu.set_cs(0xB9BA);
    cpu.set_ss(0x4846);
    cpu.set_ds(0x1E41);
    cpu.set_es(0xFD5C);
    cpu.set_sp(0x482F);
    cpu.set_bp(0xB567);
    cpu.set_si(0xEFF9);
    cpu.set_di(0xA378);
    cpu.set_ip(0x58DC);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBF47C, 0x3F);
    machine.mem_store_byte(0xBF47D, 0x90);
    machine.mem_store_byte(0xBF47E, 0x90);
    machine.mem_store_byte(0xBF47F, 0x90);
    machine.mem_store_byte(0xBF480, 0x90);
    machine.mem_store_byte(0xBF481, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xCA06);
    EXPECT_EQ(cpu.get_ip(), 0x58DD);
    EXPECT_EQ(cpu.get_flags(), 0xF013);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xBF47C), 0x3F);
    EXPECT_EQ(memory.load8(0xBF47D), 0x90);
    EXPECT_EQ(memory.load8(0xBF47E), 0x90);
    EXPECT_EQ(memory.load8(0xBF47F), 0x90);
    EXPECT_EQ(memory.load8(0xBF480), 0x90);
    EXPECT_EQ(memory.load8(0xBF481), 0x90);
}

//
// daa
//
TEST_F(MachineTest, daa_batch2)
{
    // Initial CPU State
    cpu.set_ax(0x8B2E);
    cpu.set_bx(0xDA45);
    cpu.set_cx(0xDDE2);
    cpu.set_dx(0x4DF7);
    cpu.set_cs(0x554A);
    cpu.set_ss(0xEF7D);
    cpu.set_ds(0x140A);
    cpu.set_es(0xA4CE);
    cpu.set_sp(0xADC2);
    cpu.set_bp(0x4DAB);
    cpu.set_si(0x82EF);
    cpu.set_di(0xECDF);
    cpu.set_ip(0x8A80);
    cpu.set_flags(0xF417);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5DF20, 0x27);
    machine.mem_store_byte(0x5DF21, 0x90);
    machine.mem_store_byte(0x5DF22, 0x90);
    machine.mem_store_byte(0x5DF23, 0x90);
    machine.mem_store_byte(0x5DF24, 0x90);
    machine.mem_store_byte(0x5DF25, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x8B94);
    EXPECT_EQ(cpu.get_ip(), 0x8A81);
    EXPECT_EQ(cpu.get_flags(), 0xFC93);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x5DF20), 0x27);
    EXPECT_EQ(memory.load8(0x5DF21), 0x90);
    EXPECT_EQ(memory.load8(0x5DF22), 0x90);
    EXPECT_EQ(memory.load8(0x5DF23), 0x90);
    EXPECT_EQ(memory.load8(0x5DF24), 0x90);
    EXPECT_EQ(memory.load8(0x5DF25), 0x90);
}

//
// das
//
TEST_F(MachineTest, das_batch2)
{
    // Initial CPU State
    cpu.set_ax(0x19CB);
    cpu.set_bx(0x0000);
    cpu.set_cx(0x41F2);
    cpu.set_dx(0xE7CC);
    cpu.set_cs(0x0642);
    cpu.set_ss(0x05F8);
    cpu.set_ds(0x7DEE);
    cpu.set_es(0x9B36);
    cpu.set_sp(0xBA59);
    cpu.set_bp(0x9E05);
    cpu.set_si(0xCDA1);
    cpu.set_di(0xEAD2);
    cpu.set_ip(0x53C1);
    cpu.set_flags(0xF046);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0B7E1, 0x2F);
    machine.mem_store_byte(0x0B7E2, 0x90);
    machine.mem_store_byte(0x0B7E3, 0x90);
    machine.mem_store_byte(0x0B7E4, 0x90);
    machine.mem_store_byte(0x0B7E5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x1965);
    EXPECT_EQ(cpu.get_ip(), 0x53C2);
    EXPECT_EQ(cpu.get_flags(), 0xF817);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0B7E1), 0x2F);
    EXPECT_EQ(memory.load8(0x0B7E2), 0x90);
    EXPECT_EQ(memory.load8(0x0B7E3), 0x90);
    EXPECT_EQ(memory.load8(0x0B7E4), 0x90);
    EXPECT_EQ(memory.load8(0x0B7E5), 0x90);
}

//
// xchg bh, byte [ss:bx+di+79h]
//
TEST_F(MachineTest, xchg_bh_byte_ss_bx_di_79h)
{
    // Initial CPU State
    cpu.set_ax(0x0000);
    cpu.set_bx(0x22DA);
    cpu.set_cx(0x1F26);
    cpu.set_dx(0xD1DB);
    cpu.set_cs(0xAD46);
    cpu.set_ss(0xCBA2);
    cpu.set_ds(0xAFC0);
    cpu.set_es(0xE774);
    cpu.set_sp(0x5A5F);
    cpu.set_bp(0x2DBA);
    cpu.set_si(0xA77B);
    cpu.set_di(0x6C3F);
    cpu.set_ip(0x83B0);
    cpu.set_flags(0xF053);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB5810, 0x36);
    machine.mem_store_byte(0xB5811, 0x86);
    machine.mem_store_byte(0xB5812, 0x79);
    machine.mem_store_byte(0xB5813, 0x79);
    machine.mem_store_byte(0xB5814, 0x90);
    machine.mem_store_byte(0xB5815, 0x90);
    machine.mem_store_byte(0xD49B2, 0x58);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_bx(), 0x58DA);
    EXPECT_EQ(cpu.get_ip(), 0x83B4);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB5810), 0x36);
    EXPECT_EQ(memory.load8(0xB5811), 0x86);
    EXPECT_EQ(memory.load8(0xB5812), 0x79);
    EXPECT_EQ(memory.load8(0xB5813), 0x79);
    EXPECT_EQ(memory.load8(0xB5814), 0x90);
    EXPECT_EQ(memory.load8(0xB5815), 0x90);
    EXPECT_EQ(memory.load8(0xD49B2), 0x22);
}
