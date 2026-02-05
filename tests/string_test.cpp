#include "fixture.h"

//
// cs rep stosb
//
TEST_F(MachineTest, cs_rep_stosb)
{
    // Initial CPU State
    cpu.set_ax(0xAA28);
    cpu.set_bx(0x2127);
    cpu.set_cx(0x0076);
    cpu.set_dx(0x196D);
    cpu.set_cs(0xA1A9);
    cpu.set_ss(0x474B);
    cpu.set_ds(0xC5B7);
    cpu.set_es(0xA8E5);
    cpu.set_sp(0xD810);
    cpu.set_bp(0x56E1);
    cpu.set_si(0xC0A2);
    cpu.set_di(0xA75E);
    cpu.set_ip(0x3C1E);
    cpu.set_flags(0xF007);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA56AE, 0x2E);
    machine.mem_store_byte(0xA56AF, 0xF2);
    machine.mem_store_byte(0xA56B0, 0xAA);
    machine.mem_store_byte(0xA56B1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0000);
    EXPECT_EQ(cpu.get_di(), 0xA7D4);
    EXPECT_EQ(cpu.get_ip(), 0x3C21);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xB35AE), 0x28);
    EXPECT_EQ(memory.load8(0xB35AF), 0x28);
    EXPECT_EQ(memory.load8(0xB35B0), 0x28);
    EXPECT_EQ(memory.load8(0xB35B1), 0x28);
    EXPECT_EQ(memory.load8(0xB35B2), 0x28);
    EXPECT_EQ(memory.load8(0xB35B3), 0x28);
    EXPECT_EQ(memory.load8(0xB35B4), 0x28);
    EXPECT_EQ(memory.load8(0xB35B5), 0x28);
    EXPECT_EQ(memory.load8(0xB35B6), 0x28);
    EXPECT_EQ(memory.load8(0xB35B7), 0x28);
    EXPECT_EQ(memory.load8(0xB35B8), 0x28);
    EXPECT_EQ(memory.load8(0xB35B9), 0x28);
    EXPECT_EQ(memory.load8(0xB35BA), 0x28);
    EXPECT_EQ(memory.load8(0xB35BB), 0x28);
    EXPECT_EQ(memory.load8(0xB35BC), 0x28);
    EXPECT_EQ(memory.load8(0xB35BD), 0x28);
    EXPECT_EQ(memory.load8(0xB35BE), 0x28);
    EXPECT_EQ(memory.load8(0xB35BF), 0x28);
    EXPECT_EQ(memory.load8(0xB35C0), 0x28);
    EXPECT_EQ(memory.load8(0xB35C1), 0x28);
    EXPECT_EQ(memory.load8(0xB35C2), 0x28);
    EXPECT_EQ(memory.load8(0xB35C3), 0x28);
    EXPECT_EQ(memory.load8(0xB35C4), 0x28);
    EXPECT_EQ(memory.load8(0xB35C5), 0x28);
    EXPECT_EQ(memory.load8(0xB35C6), 0x28);
    EXPECT_EQ(memory.load8(0xB35C7), 0x28);
    EXPECT_EQ(memory.load8(0xB35C8), 0x28);
    EXPECT_EQ(memory.load8(0xB35C9), 0x28);
    EXPECT_EQ(memory.load8(0xB35CA), 0x28);
    EXPECT_EQ(memory.load8(0xB35CB), 0x28);
    EXPECT_EQ(memory.load8(0xB35CC), 0x28);
    EXPECT_EQ(memory.load8(0xB35CD), 0x28);
    EXPECT_EQ(memory.load8(0xB35CE), 0x28);
    EXPECT_EQ(memory.load8(0xB35CF), 0x28);
    EXPECT_EQ(memory.load8(0xB35D0), 0x28);
    EXPECT_EQ(memory.load8(0xB35D1), 0x28);
    EXPECT_EQ(memory.load8(0xB35D2), 0x28);
    EXPECT_EQ(memory.load8(0xB35D3), 0x28);
    EXPECT_EQ(memory.load8(0xB35D4), 0x28);
    EXPECT_EQ(memory.load8(0xB35D5), 0x28);
    EXPECT_EQ(memory.load8(0xB35D6), 0x28);
    EXPECT_EQ(memory.load8(0xB35D7), 0x28);
    EXPECT_EQ(memory.load8(0xB35D8), 0x28);
    EXPECT_EQ(memory.load8(0xB35D9), 0x28);
    EXPECT_EQ(memory.load8(0xB35DA), 0x28);
    EXPECT_EQ(memory.load8(0xB35DB), 0x28);
    EXPECT_EQ(memory.load8(0xB35DC), 0x28);
    EXPECT_EQ(memory.load8(0xB35DD), 0x28);
    EXPECT_EQ(memory.load8(0xB35DE), 0x28);
    EXPECT_EQ(memory.load8(0xB35DF), 0x28);
    EXPECT_EQ(memory.load8(0xB35E0), 0x28);
    EXPECT_EQ(memory.load8(0xB35E1), 0x28);
    EXPECT_EQ(memory.load8(0xB35E2), 0x28);
    EXPECT_EQ(memory.load8(0xB35E3), 0x28);
    EXPECT_EQ(memory.load8(0xB35E4), 0x28);
    EXPECT_EQ(memory.load8(0xB35E5), 0x28);
    EXPECT_EQ(memory.load8(0xB35E6), 0x28);
    EXPECT_EQ(memory.load8(0xB35E7), 0x28);
    EXPECT_EQ(memory.load8(0xB35E8), 0x28);
    EXPECT_EQ(memory.load8(0xB35E9), 0x28);
    EXPECT_EQ(memory.load8(0xB35EA), 0x28);
    EXPECT_EQ(memory.load8(0xB35EB), 0x28);
    EXPECT_EQ(memory.load8(0xB35EC), 0x28);
    EXPECT_EQ(memory.load8(0xB35ED), 0x28);
    EXPECT_EQ(memory.load8(0xB35EE), 0x28);
    EXPECT_EQ(memory.load8(0xB35EF), 0x28);
    EXPECT_EQ(memory.load8(0xB35F0), 0x28);
    EXPECT_EQ(memory.load8(0xB35F1), 0x28);
    EXPECT_EQ(memory.load8(0xB35F2), 0x28);
    EXPECT_EQ(memory.load8(0xB35F3), 0x28);
    EXPECT_EQ(memory.load8(0xB35F4), 0x28);
    EXPECT_EQ(memory.load8(0xB35F5), 0x28);
    EXPECT_EQ(memory.load8(0xB35F6), 0x28);
    EXPECT_EQ(memory.load8(0xB35F7), 0x28);
    EXPECT_EQ(memory.load8(0xB35F8), 0x28);
    EXPECT_EQ(memory.load8(0xB35F9), 0x28);
    EXPECT_EQ(memory.load8(0xB35FA), 0x28);
    EXPECT_EQ(memory.load8(0xB35FB), 0x28);
    EXPECT_EQ(memory.load8(0xB35FC), 0x28);
    EXPECT_EQ(memory.load8(0xB35FD), 0x28);
    EXPECT_EQ(memory.load8(0xB35FE), 0x28);
    EXPECT_EQ(memory.load8(0xB35FF), 0x28);
    EXPECT_EQ(memory.load8(0xB3600), 0x28);
    EXPECT_EQ(memory.load8(0xB3601), 0x28);
    EXPECT_EQ(memory.load8(0xB3602), 0x28);
    EXPECT_EQ(memory.load8(0xB3603), 0x28);
    EXPECT_EQ(memory.load8(0xB3604), 0x28);
    EXPECT_EQ(memory.load8(0xB3605), 0x28);
    EXPECT_EQ(memory.load8(0xB3606), 0x28);
    EXPECT_EQ(memory.load8(0xB3607), 0x28);
    EXPECT_EQ(memory.load8(0xB3608), 0x28);
    EXPECT_EQ(memory.load8(0xB3609), 0x28);
    EXPECT_EQ(memory.load8(0xB360A), 0x28);
    EXPECT_EQ(memory.load8(0xB360B), 0x28);
    EXPECT_EQ(memory.load8(0xB360C), 0x28);
    EXPECT_EQ(memory.load8(0xB360D), 0x28);
    EXPECT_EQ(memory.load8(0xB360E), 0x28);
    EXPECT_EQ(memory.load8(0xB360F), 0x28);
    EXPECT_EQ(memory.load8(0xB3610), 0x28);
    EXPECT_EQ(memory.load8(0xB3611), 0x28);
    EXPECT_EQ(memory.load8(0xB3612), 0x28);
    EXPECT_EQ(memory.load8(0xB3613), 0x28);
    EXPECT_EQ(memory.load8(0xB3614), 0x28);
    EXPECT_EQ(memory.load8(0xB3615), 0x28);
    EXPECT_EQ(memory.load8(0xB3616), 0x28);
    EXPECT_EQ(memory.load8(0xB3617), 0x28);
    EXPECT_EQ(memory.load8(0xB3618), 0x28);
    EXPECT_EQ(memory.load8(0xB3619), 0x28);
    EXPECT_EQ(memory.load8(0xB361A), 0x28);
    EXPECT_EQ(memory.load8(0xB361B), 0x28);
    EXPECT_EQ(memory.load8(0xB361C), 0x28);
    EXPECT_EQ(memory.load8(0xB361D), 0x28);
    EXPECT_EQ(memory.load8(0xB361E), 0x28);
    EXPECT_EQ(memory.load8(0xB361F), 0x28);
    EXPECT_EQ(memory.load8(0xB3620), 0x28);
    EXPECT_EQ(memory.load8(0xB3621), 0x28);
    EXPECT_EQ(memory.load8(0xB3622), 0x28);
    EXPECT_EQ(memory.load8(0xB3623), 0x28);
}

//
// ds repne cmpsb
//
TEST_F(MachineTest, ds_repne_cmpsb)
{
    // Initial CPU State
    cpu.set_ax(0xE976);
    cpu.set_bx(0x2C37);
    cpu.set_cx(0x0028);
    cpu.set_dx(0xC2C3);
    cpu.set_cs(0xE0B5);
    cpu.set_ss(0xABAE);
    cpu.set_ds(0x7013);
    cpu.set_es(0xBA5C);
    cpu.set_sp(0x526C);
    cpu.set_bp(0x7658);
    cpu.set_si(0xAD9C);
    cpu.set_di(0xD2EB);
    cpu.set_ip(0xE091);
    cpu.set_flags(0xF416);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEEBE1, 0x3E);
    machine.mem_store_byte(0xEEBE2, 0xF2);
    machine.mem_store_byte(0xEEBE3, 0xA6);
    machine.mem_store_byte(0xEEBE4, 0x90);
    machine.mem_store_byte(0x7AECC, 0xCD);
    machine.mem_store_byte(0xC78AB, 0xAA);
    machine.mem_store_byte(0x7AECB, 0x29);
    machine.mem_store_byte(0xC78AA, 0x24);
    machine.mem_store_byte(0x7AECA, 0x25);
    machine.mem_store_byte(0xC78A9, 0x8E);
    machine.mem_store_byte(0x7AEC9, 0xE0);
    machine.mem_store_byte(0xC78A8, 0xD6);
    machine.mem_store_byte(0x7AEC8, 0xDE);
    machine.mem_store_byte(0xC78A7, 0x02);
    machine.mem_store_byte(0x7AEC7, 0xC2);
    machine.mem_store_byte(0xC78A6, 0xB6);
    machine.mem_store_byte(0x7AEC6, 0x7E);
    machine.mem_store_byte(0xC78A5, 0xF1);
    machine.mem_store_byte(0x7AEC5, 0x3B);
    machine.mem_store_byte(0xC78A4, 0xBE);
    machine.mem_store_byte(0x7AEC4, 0xCD);
    machine.mem_store_byte(0xC78A3, 0x6F);
    machine.mem_store_byte(0x7AEC3, 0xF3);
    machine.mem_store_byte(0xC78A2, 0x43);
    machine.mem_store_byte(0x7AEC2, 0xC4);
    machine.mem_store_byte(0xC78A1, 0x92);
    machine.mem_store_byte(0x7AEC1, 0x72);
    machine.mem_store_byte(0xC78A0, 0xDC);
    machine.mem_store_byte(0x7AEC0, 0xD9);
    machine.mem_store_byte(0xC789F, 0x52);
    machine.mem_store_byte(0x7AEBF, 0x83);
    machine.mem_store_byte(0xC789E, 0xF2);
    machine.mem_store_byte(0x7AEBE, 0x8A);
    machine.mem_store_byte(0xC789D, 0x0F);
    machine.mem_store_byte(0x7AEBD, 0x02);
    machine.mem_store_byte(0xC789C, 0x7C);
    machine.mem_store_byte(0x7AEBC, 0x4A);
    machine.mem_store_byte(0xC789B, 0xD7);
    machine.mem_store_byte(0x7AEBB, 0xF4);
    machine.mem_store_byte(0xC789A, 0x72);
    machine.mem_store_byte(0x7AEBA, 0x69);
    machine.mem_store_byte(0xC7899, 0xF3);
    machine.mem_store_byte(0x7AEB9, 0x29);
    machine.mem_store_byte(0xC7898, 0x79);
    machine.mem_store_byte(0x7AEB8, 0xDE);
    machine.mem_store_byte(0xC7897, 0xCF);
    machine.mem_store_byte(0x7AEB7, 0xB7);
    machine.mem_store_byte(0xC7896, 0x8E);
    machine.mem_store_byte(0x7AEB6, 0x4A);
    machine.mem_store_byte(0xC7895, 0x5C);
    machine.mem_store_byte(0x7AEB5, 0xF9);
    machine.mem_store_byte(0xC7894, 0x79);
    machine.mem_store_byte(0x7AEB4, 0xA1);
    machine.mem_store_byte(0xC7893, 0x04);
    machine.mem_store_byte(0x7AEB3, 0xE5);
    machine.mem_store_byte(0xC7892, 0x3C);
    machine.mem_store_byte(0x7AEB2, 0x44);
    machine.mem_store_byte(0xC7891, 0x30);
    machine.mem_store_byte(0x7AEB1, 0x40);
    machine.mem_store_byte(0xC7890, 0x12);
    machine.mem_store_byte(0x7AEB0, 0x07);
    machine.mem_store_byte(0xC788F, 0x78);
    machine.mem_store_byte(0x7AEAF, 0x66);
    machine.mem_store_byte(0xC788E, 0x71);
    machine.mem_store_byte(0x7AEAE, 0x36);
    machine.mem_store_byte(0xC788D, 0x8F);
    machine.mem_store_byte(0x7AEAD, 0x05);
    machine.mem_store_byte(0xC788C, 0xB1);
    machine.mem_store_byte(0x7AEAC, 0xFF);
    machine.mem_store_byte(0xC788B, 0x32);
    machine.mem_store_byte(0x7AEAB, 0xD4);
    machine.mem_store_byte(0xC788A, 0xEC);
    machine.mem_store_byte(0x7AEAA, 0xA5);
    machine.mem_store_byte(0xC7889, 0x7A);
    machine.mem_store_byte(0x7AEA9, 0xE0);
    machine.mem_store_byte(0xC7888, 0x58);
    machine.mem_store_byte(0x7AEA8, 0x5A);
    machine.mem_store_byte(0xC7887, 0x5F);
    machine.mem_store_byte(0x7AEA7, 0xBF);
    machine.mem_store_byte(0xC7886, 0x67);
    machine.mem_store_byte(0x7AEA6, 0x97);
    machine.mem_store_byte(0xC7885, 0xC5);
    machine.mem_store_byte(0x7AEA5, 0x7C);
    machine.mem_store_byte(0xC7884, 0x05);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0000);
    EXPECT_EQ(cpu.get_si(), 0xAD74);
    EXPECT_EQ(cpu.get_di(), 0xD2C3);
    EXPECT_EQ(cpu.get_ip(), 0xE094);
    EXPECT_EQ(cpu.get_flags(), 0xF406);

    // Final RAM entries
}

//
// ds stosw
//
TEST_F(MachineTest, ds_stosw)
{
    // Initial CPU State
    cpu.set_ax(0xEB61);
    cpu.set_bx(0x6772);
    cpu.set_cx(0x0020);
    cpu.set_dx(0xD8DF);
    cpu.set_cs(0x39FF);
    cpu.set_ss(0xAAD1);
    cpu.set_ds(0x2AE7);
    cpu.set_es(0xBE56);
    cpu.set_sp(0x5106);
    cpu.set_bp(0xE6FE);
    cpu.set_si(0x6CAA);
    cpu.set_di(0x36DF);
    cpu.set_ip(0x4029);
    cpu.set_flags(0xF816);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3E019, 0x3E);
    machine.mem_store_byte(0x3E01A, 0xAB);
    machine.mem_store_byte(0x3E01B, 0x90);
    machine.mem_store_byte(0x3E01C, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x36E1);
    EXPECT_EQ(cpu.get_ip(), 0x402B);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xC1C3F), 0x61);
    EXPECT_EQ(memory.load8(0xC1C40), 0xEB);
}

//
// es movsw
//
TEST_F(MachineTest, es_movsw)
{
    // Initial CPU State
    cpu.set_ax(0x4792);
    cpu.set_bx(0x24F1);
    cpu.set_cx(0x004E);
    cpu.set_dx(0x0489);
    cpu.set_cs(0x2B8F);
    cpu.set_ss(0xAFB4);
    cpu.set_ds(0x2290);
    cpu.set_es(0x3EB1);
    cpu.set_sp(0x0FB0);
    cpu.set_bp(0x068F);
    cpu.set_si(0x475C);
    cpu.set_di(0x17C7);
    cpu.set_ip(0xCBA4);
    cpu.set_flags(0xF403);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x38494, 0x26);
    machine.mem_store_byte(0x38495, 0xA5);
    machine.mem_store_byte(0x38496, 0x90);
    machine.mem_store_byte(0x38497, 0x90);
    machine.mem_store_byte(0x4326C, 0x64);
    machine.mem_store_byte(0x4326D, 0xDD);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0x475A);
    EXPECT_EQ(cpu.get_di(), 0x17C5);
    EXPECT_EQ(cpu.get_ip(), 0xCBA6);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x402D7), 0x64);
    EXPECT_EQ(memory.load8(0x402D8), 0xDD);
}

//
// es rep lodsw
//
TEST_F(MachineTest, es_rep_lodsw)
{
    // Initial CPU State
    cpu.set_ax(0x94BE);
    cpu.set_bx(0x5E1B);
    cpu.set_cx(0x0004);
    cpu.set_dx(0x4CC5);
    cpu.set_cs(0xBC36);
    cpu.set_ss(0x0BD2);
    cpu.set_ds(0x40AE);
    cpu.set_es(0x9D25);
    cpu.set_sp(0x493E);
    cpu.set_bp(0x4124);
    cpu.set_si(0x1345);
    cpu.set_di(0x3552);
    cpu.set_ip(0x1092);
    cpu.set_flags(0xF016);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBD3F2, 0x26);
    machine.mem_store_byte(0xBD3F3, 0xF3);
    machine.mem_store_byte(0xBD3F4, 0xAD);
    machine.mem_store_byte(0xBD3F5, 0x90);
    machine.mem_store_byte(0x9E595, 0x59);
    machine.mem_store_byte(0x9E596, 0x01);
    machine.mem_store_byte(0x9E597, 0xF1);
    machine.mem_store_byte(0x9E598, 0xBC);
    machine.mem_store_byte(0x9E599, 0x1A);
    machine.mem_store_byte(0x9E59A, 0xE5);
    machine.mem_store_byte(0x9E59B, 0x5C);
    machine.mem_store_byte(0x9E59C, 0xC6);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xC65C);
    EXPECT_EQ(cpu.get_cx(), 0x0000);
    EXPECT_EQ(cpu.get_si(), 0x134D);
    EXPECT_EQ(cpu.get_ip(), 0x1095);

    // Final RAM entries
}

//
// lodsb
//
TEST_F(MachineTest, lodsb)
{
    // Initial CPU State
    cpu.set_ax(0x9DF0);
    cpu.set_bx(0x5E9E);
    cpu.set_cx(0x0056);
    cpu.set_dx(0x30ED);
    cpu.set_cs(0xC1B6);
    cpu.set_ss(0x2321);
    cpu.set_ds(0xD1E4);
    cpu.set_es(0x8590);
    cpu.set_sp(0x12E1);
    cpu.set_bp(0xDCDA);
    cpu.set_si(0x8D99);
    cpu.set_di(0x8036);
    cpu.set_ip(0x9EF1);
    cpu.set_flags(0xFC46);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCBA51, 0xAC);
    machine.mem_store_byte(0xCBA52, 0x90);
    machine.mem_store_byte(0xCBA53, 0x90);
    machine.mem_store_byte(0xCBA54, 0x90);
    machine.mem_store_byte(0xDABD9, 0x6E);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x9D6E);
    EXPECT_EQ(cpu.get_si(), 0x8D98);
    EXPECT_EQ(cpu.get_ip(), 0x9EF2);

    // Final RAM entries
}

//
// movsb
//
TEST_F(MachineTest, movsb)
{
    // Initial CPU State
    cpu.set_ax(0x52A1);
    cpu.set_bx(0xE724);
    cpu.set_cx(0x0048);
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
    machine.mem_store_byte(0x32186, 0xA4);
    machine.mem_store_byte(0x32187, 0x90);
    machine.mem_store_byte(0x32188, 0x90);
    machine.mem_store_byte(0x32189, 0x90);
    machine.mem_store_byte(0x0F0A1, 0x6B);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_si(), 0xCB20);
    EXPECT_EQ(cpu.get_di(), 0x2728);
    EXPECT_EQ(cpu.get_ip(), 0x02B7);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xCF359), 0x6B);
}

//
// repe cmpsw
//
TEST_F(MachineTest, repe_cmpsw)
{
    // Initial CPU State
    cpu.set_ax(0xB915);
    cpu.set_bx(0x4AC3);
    cpu.set_cx(0x0036);
    cpu.set_dx(0xF347);
    cpu.set_cs(0xA151);
    cpu.set_ss(0xF52F);
    cpu.set_ds(0xA66B);
    cpu.set_es(0xFCC8);
    cpu.set_sp(0x8B35);
    cpu.set_bp(0x22B2);
    cpu.set_si(0xE385);
    cpu.set_di(0xA571);
    cpu.set_ip(0xD7AF);
    cpu.set_flags(0xF447);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xAECBF, 0xF3);
    machine.mem_store_byte(0xAECC0, 0xA7);
    machine.mem_store_byte(0xAECC1, 0x90);
    machine.mem_store_byte(0xAECC2, 0x90);
    machine.mem_store_byte(0xB4A35, 0x3E);
    machine.mem_store_byte(0xB4A36, 0x12);
    machine.mem_store_byte(0x071F1, 0x78);
    machine.mem_store_byte(0x071F2, 0xC2);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0035);
    EXPECT_EQ(cpu.get_si(), 0xE383);
    EXPECT_EQ(cpu.get_di(), 0xA56F);
    EXPECT_EQ(cpu.get_ip(), 0xD7B1);
    EXPECT_EQ(cpu.get_flags(), 0xF407);

    // Final RAM entries
}

//
// ss repe scasw
//
TEST_F(MachineTest, ss_repe_scasw)
{
    // Initial CPU State
    cpu.set_ax(0xA91B);
    cpu.set_bx(0xB03F);
    cpu.set_cx(0x0008);
    cpu.set_dx(0xDA8B);
    cpu.set_cs(0x873B);
    cpu.set_ss(0x03E5);
    cpu.set_ds(0x4926);
    cpu.set_es(0x36BC);
    cpu.set_sp(0xE2DD);
    cpu.set_bp(0x372E);
    cpu.set_si(0x90A6);
    cpu.set_di(0x74C1);
    cpu.set_ip(0x33F6);
    cpu.set_flags(0xF883);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x8A7A6, 0x36);
    machine.mem_store_byte(0x8A7A7, 0xF3);
    machine.mem_store_byte(0x8A7A8, 0xAF);
    machine.mem_store_byte(0x8A7A9, 0x90);
    machine.mem_store_byte(0x3E081, 0x17);
    machine.mem_store_byte(0x3E082, 0xD3);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x0007);
    EXPECT_EQ(cpu.get_di(), 0x74C3);
    EXPECT_EQ(cpu.get_ip(), 0x33F9);
    EXPECT_EQ(cpu.get_flags(), 0xF083);

    // Final RAM entries
}

//
// ss scasb
//
TEST_F(MachineTest, ss_scasb)
{
    // Initial CPU State
    cpu.set_ax(0x4568);
    cpu.set_bx(0xCEEC);
    cpu.set_cx(0x0072);
    cpu.set_dx(0xD1B6);
    cpu.set_cs(0x3CFE);
    cpu.set_ss(0x74B5);
    cpu.set_ds(0x0894);
    cpu.set_es(0xD1F6);
    cpu.set_sp(0x60D6);
    cpu.set_bp(0x6EDE);
    cpu.set_si(0x6A6B);
    cpu.set_di(0x1F09);
    cpu.set_ip(0x283B);
    cpu.set_flags(0xF452);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3F81B, 0x36);
    machine.mem_store_byte(0x3F81C, 0xAE);
    machine.mem_store_byte(0x3F81D, 0x90);
    machine.mem_store_byte(0x3F81E, 0x90);
    machine.mem_store_byte(0xD3E69, 0xD8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_di(), 0x1F08);
    EXPECT_EQ(cpu.get_ip(), 0x283D);
    EXPECT_EQ(cpu.get_flags(), 0xFC87);

    // Final RAM entries
}
