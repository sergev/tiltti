#include "fixture.h"

//
// jcxz FF8Fh
//
TEST_F(MachineTest, jcxz_FF8Fh)
{
    // Initial CPU State
    cpu.set_ax(0x846C);
    cpu.set_bx(0x0302);
    cpu.set_cx(0xEC3A);
    cpu.set_dx(0xD57F);
    cpu.set_cs(0x3134);
    cpu.set_ss(0x20B4);
    cpu.set_ds(0x15F0);
    cpu.set_es(0x793F);
    cpu.set_sp(0xC331);
    cpu.set_bp(0xDD80);
    cpu.set_si(0x87EA);
    cpu.set_di(0x70FC);
    cpu.set_ip(0xB3F7);
    cpu.set_flags(0xFC06);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x3C737, 0xE3);
    machine.mem_store_byte(0x3C738, 0x8D);
    machine.mem_store_byte(0x3C739, 0x90);
    machine.mem_store_byte(0x3C73A, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xB3F9);

    // Final RAM entries
}

//
// jmp 0051h
//
TEST_F(MachineTest, jmp_0051h)
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
    machine.mem_store_byte(0x2B5DE, 0xEB);
    machine.mem_store_byte(0x2B5DF, 0x4F);
    machine.mem_store_byte(0x2B5E0, 0x90);
    machine.mem_store_byte(0x2B5E1, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xA22F);

    // Final RAM entries
}

//
// jmp 1A33h
//
TEST_F(MachineTest, jmp_1A33h)
{
    // Initial CPU State
    cpu.set_ax(0xE5F0);
    cpu.set_bx(0x8D68);
    cpu.set_cx(0x3508);
    cpu.set_dx(0x016D);
    cpu.set_cs(0x0BB8);
    cpu.set_ss(0x0D6C);
    cpu.set_ds(0x5824);
    cpu.set_es(0x02EC);
    cpu.set_sp(0x5BCF);
    cpu.set_bp(0xC40C);
    cpu.set_si(0xC29C);
    cpu.set_di(0xA8F5);
    cpu.set_ip(0xAC29);
    cpu.set_flags(0xF8D3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x167A9, 0x26);
    machine.mem_store_byte(0x167AA, 0xE9);
    machine.mem_store_byte(0x167AB, 0x2F);
    machine.mem_store_byte(0x167AC, 0x1A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xC65C);

    // Final RAM entries
}

//
// jmp sp
//
TEST_F(MachineTest, jmp_sp)
{
    // Initial CPU State
    cpu.set_ax(0xE7D2);
    cpu.set_bx(0xEF29);
    cpu.set_cx(0x6496);
    cpu.set_dx(0x0E6A);
    cpu.set_cs(0x87A6);
    cpu.set_ss(0x39ED);
    cpu.set_ds(0xE52C);
    cpu.set_es(0x3C7F);
    cpu.set_sp(0x727A);
    cpu.set_bp(0x83AF);
    cpu.set_si(0x2EA8);
    cpu.set_di(0x710E);
    cpu.set_ip(0x9572);
    cpu.set_flags(0xF0C6);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x90FD2, 0x2E);
    machine.mem_store_byte(0x90FD3, 0xFF);
    machine.mem_store_byte(0x90FD4, 0xE4);
    machine.mem_store_byte(0x90FD5, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x727A);

    // Final RAM entries
}

//
// jmpf 3AC7h:E01Ah
//
TEST_F(MachineTest, jmpf_3AC7h_E01Ah)
{
    // Initial CPU State
    cpu.set_ax(0x6F01);
    cpu.set_bx(0xF3CB);
    cpu.set_cx(0xBF0A);
    cpu.set_dx(0x96B3);
    cpu.set_cs(0x16D8);
    cpu.set_ss(0xDCD3);
    cpu.set_ds(0x1A48);
    cpu.set_es(0xF923);
    cpu.set_sp(0x9631);
    cpu.set_bp(0xD6C5);
    cpu.set_si(0x3F69);
    cpu.set_di(0x9B40);
    cpu.set_ip(0x9359);
    cpu.set_flags(0xF893);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x200D9, 0x2E);
    machine.mem_store_byte(0x200DA, 0xEA);
    machine.mem_store_byte(0x200DB, 0x1A);
    machine.mem_store_byte(0x200DC, 0xE0);
    machine.mem_store_byte(0x200DD, 0xC7);
    machine.mem_store_byte(0x200DE, 0x3A);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0x3AC7);
    EXPECT_EQ(cpu.get_ip(), 0xE01A);

    // Final RAM entries
}

//
// jmpf word [ds:di-Ah]
//
TEST_F(MachineTest, jmpf_word_ds_di_Ah)
{
    // Initial CPU State
    cpu.set_ax(0xB1E2);
    cpu.set_bx(0xB38F);
    cpu.set_cx(0x64E4);
    cpu.set_dx(0x27BB);
    cpu.set_cs(0x298A);
    cpu.set_ss(0x68E5);
    cpu.set_ds(0xBB86);
    cpu.set_es(0x4663);
    cpu.set_sp(0xB821);
    cpu.set_bp(0xAA3B);
    cpu.set_si(0x42BD);
    cpu.set_di(0x13BF);
    cpu.set_ip(0x49B0);
    cpu.set_flags(0xF813);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x2E250, 0xFF);
    machine.mem_store_byte(0x2E251, 0x6D);
    machine.mem_store_byte(0x2E252, 0xF6);
    machine.mem_store_byte(0x2E253, 0x90);
    machine.mem_store_byte(0xBCC15, 0x78);
    machine.mem_store_byte(0xBCC16, 0x75);
    machine.mem_store_byte(0xBCC17, 0xDE);
    machine.mem_store_byte(0xBCC18, 0xE8);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cs(), 0xE8DE);
    EXPECT_EQ(cpu.get_ip(), 0x7578);

    // Final RAM entries
}

//
// loop 0080h
//
TEST_F(MachineTest, loop_0080h)
{
    // Initial CPU State
    cpu.set_ax(0x2275);
    cpu.set_bx(0x79AA);
    cpu.set_cx(0x1CF6);
    cpu.set_dx(0x99B0);
    cpu.set_cs(0xC6D7);
    cpu.set_ss(0x3DE0);
    cpu.set_ds(0x9691);
    cpu.set_es(0xB2E3);
    cpu.set_sp(0x0A19);
    cpu.set_bp(0xCECF);
    cpu.set_si(0x395F);
    cpu.set_di(0x386D);
    cpu.set_ip(0x4E40);
    cpu.set_flags(0xFCC3);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xCBBB0, 0xE2);
    machine.mem_store_byte(0xCBBB1, 0x7E);
    machine.mem_store_byte(0xCBBB2, 0x90);
    machine.mem_store_byte(0xCBBB3, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x1CF5);
    EXPECT_EQ(cpu.get_ip(), 0x4EC0);

    // Final RAM entries
}

//
// loope 005Bh
//
TEST_F(MachineTest, loope_005Bh)
{
    // Initial CPU State
    cpu.set_ax(0x0AB0);
    cpu.set_bx(0x0428);
    cpu.set_cx(0x81F8);
    cpu.set_dx(0x1C79);
    cpu.set_cs(0x89A4);
    cpu.set_ss(0x656C);
    cpu.set_ds(0x79C8);
    cpu.set_es(0xC984);
    cpu.set_sp(0xAF26);
    cpu.set_bp(0x5BF9);
    cpu.set_si(0x1EB5);
    cpu.set_di(0xD90D);
    cpu.set_ip(0x87ED);
    cpu.set_flags(0xF843);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9222D, 0xE1);
    machine.mem_store_byte(0x9222E, 0x59);
    machine.mem_store_byte(0x9222F, 0x90);
    machine.mem_store_byte(0x92230, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x81F7);
    EXPECT_EQ(cpu.get_ip(), 0x8848);

    // Final RAM entries
}

//
// loopne 0046h
//
TEST_F(MachineTest, loopne_0046h)
{
    // Initial CPU State
    cpu.set_ax(0xD8B3);
    cpu.set_bx(0x3741);
    cpu.set_cx(0x894C);
    cpu.set_dx(0x3AA9);
    cpu.set_cs(0x8A49);
    cpu.set_ss(0xE4AE);
    cpu.set_ds(0x83DE);
    cpu.set_es(0xECBF);
    cpu.set_sp(0xA6D3);
    cpu.set_bp(0x85A2);
    cpu.set_si(0x0420);
    cpu.set_di(0x8CBF);
    cpu.set_ip(0xCBE0);
    cpu.set_flags(0xF057);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x97070, 0xE0);
    machine.mem_store_byte(0x97071, 0x44);
    machine.mem_store_byte(0x97072, 0x90);
    machine.mem_store_byte(0x97073, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_cx(), 0x894B);
    EXPECT_EQ(cpu.get_ip(), 0xCBE2);

    // Final RAM entries
}
