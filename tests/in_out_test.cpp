#include "fixture.h"

//
// in al, 1Bh
//
TEST_F(MachineTest, in_al_1Bh)
{
    // Initial CPU State
    cpu.set_ax(0x9960);
    cpu.set_bx(0x4576);
    cpu.set_cx(0xE6AA);
    cpu.set_dx(0xFC78);
    cpu.set_cs(0x4AB0);
    cpu.set_ss(0x30E6);
    cpu.set_ds(0xCB24);
    cpu.set_es(0x1499);
    cpu.set_sp(0xED88);
    cpu.set_bp(0x1EA7);
    cpu.set_si(0xCAFA);
    cpu.set_di(0xEFB2);
    cpu.set_ip(0x5B9C);
    cpu.set_flags(0xF097);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x5069C, 0xE4);
    machine.mem_store_byte(0x5069D, 0x1B);
    machine.mem_store_byte(0x5069E, 0x90);
    machine.mem_store_byte(0x5069F, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0x99FF);
    EXPECT_EQ(cpu.get_ip(), 0x5B9E);

    // Final RAM entries
}

//
// in al, dx
//
TEST_F(MachineTest, in_al_dx)
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
    machine.mem_store_byte(0x2EE0D, 0xEC);
    machine.mem_store_byte(0x2EE0E, 0x90);
    machine.mem_store_byte(0x2EE0F, 0x90);
    machine.mem_store_byte(0x2EE10, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xA3FF);
    EXPECT_EQ(cpu.get_ip(), 0x3FAE);

    // Final RAM entries
}

//
// in ax, 8Dh
//
TEST_F(MachineTest, in_ax_8Dh)
{
    // Initial CPU State
    cpu.set_ax(0x830B);
    cpu.set_bx(0x4F53);
    cpu.set_cx(0x93C4);
    cpu.set_dx(0x3AEB);
    cpu.set_cs(0x97E7);
    cpu.set_ss(0xE621);
    cpu.set_ds(0x8ED9);
    cpu.set_es(0x99CC);
    cpu.set_sp(0xD373);
    cpu.set_bp(0x4A31);
    cpu.set_si(0x31BA);
    cpu.set_di(0xF413);
    cpu.set_ip(0xBEC3);
    cpu.set_flags(0xF056);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xA3D33, 0xE5);
    machine.mem_store_byte(0xA3D34, 0x8D);
    machine.mem_store_byte(0xA3D35, 0x90);
    machine.mem_store_byte(0xA3D36, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0xBEC5);

    // Final RAM entries
}

//
// in ax, dx
//
TEST_F(MachineTest, in_ax_dx)
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
    machine.mem_store_byte(0xDB5E3, 0xED);
    machine.mem_store_byte(0xDB5E4, 0x90);
    machine.mem_store_byte(0xDB5E5, 0x90);
    machine.mem_store_byte(0xDB5E6, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ax(), 0xFFFF);
    EXPECT_EQ(cpu.get_ip(), 0x5D64);

    // Final RAM entries
}

//
// out 45h, al
//
TEST_F(MachineTest, out_45h_al)
{
    // Initial CPU State
    cpu.set_ax(0x8DB5);
    cpu.set_bx(0xDDC1);
    cpu.set_cx(0x495C);
    cpu.set_dx(0xA570);
    cpu.set_cs(0xE8AA);
    cpu.set_ss(0x3666);
    cpu.set_ds(0xACE9);
    cpu.set_es(0x017C);
    cpu.set_sp(0x9468);
    cpu.set_bp(0xDE03);
    cpu.set_si(0x3DE9);
    cpu.set_di(0x5EDD);
    cpu.set_ip(0x61F8);
    cpu.set_flags(0xFCD7);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEEC98, 0xE6);
    machine.mem_store_byte(0xEEC99, 0x45);
    machine.mem_store_byte(0xEEC9A, 0x90);
    machine.mem_store_byte(0xEEC9B, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x61FA);

    // Final RAM entries
}

//
// out ABh, ax
//
TEST_F(MachineTest, out_ABh_ax)
{
    // Initial CPU State
    cpu.set_ax(0xB861);
    cpu.set_bx(0xB3E9);
    cpu.set_cx(0x825A);
    cpu.set_dx(0x19EE);
    cpu.set_cs(0x5F51);
    cpu.set_ss(0xD1DB);
    cpu.set_ds(0x4E80);
    cpu.set_es(0x35F6);
    cpu.set_sp(0xDCE8);
    cpu.set_bp(0x5019);
    cpu.set_si(0xAC88);
    cpu.set_di(0xCF60);
    cpu.set_ip(0x0D96);
    cpu.set_flags(0xF817);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x602A6, 0xE7);
    machine.mem_store_byte(0x602A7, 0xAB);
    machine.mem_store_byte(0x602A8, 0x90);
    machine.mem_store_byte(0x602A9, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0D98);

    // Final RAM entries
}

//
// out dx, al
//
TEST_F(MachineTest, out_dx_al)
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
    machine.mem_store_byte(0x0308E, 0xEE);
    machine.mem_store_byte(0x0308F, 0x90);
    machine.mem_store_byte(0x03090, 0x90);
    machine.mem_store_byte(0x03091, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0xCC7F);

    // Final RAM entries
}

//
// out dx, ax
//
TEST_F(MachineTest, out_dx_ax)
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
    machine.mem_store_byte(0xE42A9, 0xEF);
    machine.mem_store_byte(0xE42AA, 0x90);
    machine.mem_store_byte(0xE42AB, 0x90);
    machine.mem_store_byte(0xE42AC, 0x90);

    // Single-step.
    cpu.step();

    // Final CPU State
    EXPECT_EQ(cpu.get_ip(), 0x0FEA);

    // Final RAM entries
}
