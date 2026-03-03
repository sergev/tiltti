#include "test386.h"

//
// o32 enter B328h,1Fh
//
TEST_F(Test386, o32_enter_B328h_1Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x37B67AD5);
    cpu.set_ebx(0x0053CCDF);
    cpu.set_ecx(0x6482E98F);
    cpu.set_edx(0x7FFFFFFF);
    cpu.set_esi(0xFFFFFFFF);
    cpu.set_edi(0x62CBBFF5);
    cpu.set_ebp(0x00000401);
    cpu.set_esp(0x0000D172);
    cpu.set_cs(0x0000A987);
    cpu.set_ds(0x0000DD63);
    cpu.set_es(0x0000EC29);
    cpu.set_fs(0x0000C997);
    cpu.set_gs(0x000009C0);
    cpu.set_ss(0x000002B1);
    cpu.set_eip(0x00008D10);
    cpu.set_eflags(0xFFFC0C87);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xB2580, 0x66);
    machine.mem_store_byte(0xB2581, 0xC8);
    machine.mem_store_byte(0xB2582, 0x28);
    machine.mem_store_byte(0xB2583, 0xB3);
    machine.mem_store_byte(0xB2584, 0x1F);
    machine.mem_store_byte(0xB2585, 0xF4);
    machine.mem_store_byte(0xB2586, 0xC8);
    machine.mem_store_byte(0xB2587, 0xA7);
    machine.mem_store_byte(0xB2588, 0x2D);
    machine.mem_store_byte(0xB2589, 0x6B);
    machine.mem_store_byte(0xB258A, 0x96);
    machine.mem_store_byte(0xB258B, 0x7F);
    machine.mem_store_byte(0xB258C, 0x2C);
    machine.mem_store_byte(0xB258D, 0xED);
    machine.mem_store_byte(0xB258E, 0xE3);
    machine.mem_store_byte(0xB258F, 0xDD);
    machine.mem_store_byte(0x02F10, 0xED);
    machine.mem_store_byte(0x02F0D, 0x64);
    machine.mem_store_byte(0x02F0E, 0x78);
    machine.mem_store_byte(0x02F0F, 0xC0);
    machine.mem_store_byte(0x02F0C, 0xF4);
    machine.mem_store_byte(0x02F09, 0xEA);
    machine.mem_store_byte(0x02F0A, 0x2F);
    machine.mem_store_byte(0x02F0B, 0xBA);
    machine.mem_store_byte(0x02F08, 0xC5);
    machine.mem_store_byte(0x02F05, 0x45);
    machine.mem_store_byte(0x02F06, 0x12);
    machine.mem_store_byte(0x02F07, 0x1C);
    machine.mem_store_byte(0x02F04, 0x9F);
    machine.mem_store_byte(0x02F01, 0x2D);
    machine.mem_store_byte(0x02F02, 0x90);
    machine.mem_store_byte(0x02F03, 0x19);
    machine.mem_store_byte(0x02F00, 0x87);
    machine.mem_store_byte(0x02EFD, 0x64);
    machine.mem_store_byte(0x02EFE, 0x61);
    machine.mem_store_byte(0x02EFF, 0x6D);
    machine.mem_store_byte(0x02EFC, 0x78);
    machine.mem_store_byte(0x02EF9, 0x16);
    machine.mem_store_byte(0x02EFA, 0x15);
    machine.mem_store_byte(0x02EFB, 0x7E);
    machine.mem_store_byte(0x02EF8, 0x84);
    machine.mem_store_byte(0x02EF5, 0x29);
    machine.mem_store_byte(0x02EF6, 0x59);
    machine.mem_store_byte(0x02EF7, 0x67);
    machine.mem_store_byte(0x02EF4, 0xB1);
    machine.mem_store_byte(0x02EF1, 0x41);
    machine.mem_store_byte(0x02EF2, 0x88);
    machine.mem_store_byte(0x02EF3, 0x47);
    machine.mem_store_byte(0x02EF0, 0xE6);
    machine.mem_store_byte(0x02EED, 0x46);
    machine.mem_store_byte(0x02EEE, 0x09);
    machine.mem_store_byte(0x02EEF, 0xAD);
    machine.mem_store_byte(0x02EEC, 0x09);
    machine.mem_store_byte(0x02EE9, 0x54);
    machine.mem_store_byte(0x02EEA, 0xD5);
    machine.mem_store_byte(0x02EEB, 0xE9);
    machine.mem_store_byte(0x02EE8, 0xFF);
    machine.mem_store_byte(0x02EE5, 0x36);
    machine.mem_store_byte(0x02EE6, 0x97);
    machine.mem_store_byte(0x02EE7, 0x17);
    machine.mem_store_byte(0x02EE4, 0x85);
    machine.mem_store_byte(0x02EE1, 0x47);
    machine.mem_store_byte(0x02EE2, 0x9E);
    machine.mem_store_byte(0x02EE3, 0x1A);
    machine.mem_store_byte(0x02EE0, 0x5A);
    machine.mem_store_byte(0x02EDD, 0x07);
    machine.mem_store_byte(0x02EDE, 0xAA);
    machine.mem_store_byte(0x02EDF, 0x1A);
    machine.mem_store_byte(0x02EDC, 0xF3);
    machine.mem_store_byte(0x02ED9, 0xAC);
    machine.mem_store_byte(0x02EDA, 0xB5);
    machine.mem_store_byte(0x02EDB, 0xB6);
    machine.mem_store_byte(0x02ED8, 0xCA);
    machine.mem_store_byte(0x02ED5, 0x3D);
    machine.mem_store_byte(0x02ED6, 0x35);
    machine.mem_store_byte(0x02ED7, 0x55);
    machine.mem_store_byte(0x02ED4, 0xF8);
    machine.mem_store_byte(0x02ED1, 0x39);
    machine.mem_store_byte(0x02ED2, 0x0A);
    machine.mem_store_byte(0x02ED3, 0xAA);
    machine.mem_store_byte(0x02ED0, 0x3C);
    machine.mem_store_byte(0x02ECD, 0x3E);
    machine.mem_store_byte(0x02ECE, 0x6C);
    machine.mem_store_byte(0x02ECF, 0x39);
    machine.mem_store_byte(0x02ECC, 0x17);
    machine.mem_store_byte(0x02EC9, 0x4F);
    machine.mem_store_byte(0x02ECA, 0x3B);
    machine.mem_store_byte(0x02ECB, 0xAF);
    machine.mem_store_byte(0x02EC8, 0x60);
    machine.mem_store_byte(0x02EC5, 0x44);
    machine.mem_store_byte(0x02EC6, 0xEF);
    machine.mem_store_byte(0x02EC7, 0x01);
    machine.mem_store_byte(0x02EC4, 0x31);
    machine.mem_store_byte(0x02EC1, 0xC1);
    machine.mem_store_byte(0x02EC2, 0x6A);
    machine.mem_store_byte(0x02EC3, 0x21);
    machine.mem_store_byte(0x02EC0, 0xCE);
    machine.mem_store_byte(0x02EBD, 0x22);
    machine.mem_store_byte(0x02EBE, 0xD3);
    machine.mem_store_byte(0x02EBF, 0xED);
    machine.mem_store_byte(0x02EBC, 0xC3);
    machine.mem_store_byte(0x02EB9, 0xC0);
    machine.mem_store_byte(0x02EBA, 0x46);
    machine.mem_store_byte(0x02EBB, 0x4B);
    machine.mem_store_byte(0x02EB8, 0xC8);
    machine.mem_store_byte(0x02EB5, 0x0D);
    machine.mem_store_byte(0x02EB6, 0xAA);
    machine.mem_store_byte(0x02EB7, 0x2B);
    machine.mem_store_byte(0x02EB4, 0xF5);
    machine.mem_store_byte(0x02EB1, 0xA3);
    machine.mem_store_byte(0x02EB2, 0x62);
    machine.mem_store_byte(0x02EB3, 0x56);
    machine.mem_store_byte(0x02EB0, 0x94);
    machine.mem_store_byte(0x02EAD, 0x4F);
    machine.mem_store_byte(0x02EAE, 0xC5);
    machine.mem_store_byte(0x02EAF, 0x33);
    machine.mem_store_byte(0x02EAC, 0xA6);
    machine.mem_store_byte(0x02EA9, 0x8E);
    machine.mem_store_byte(0x02EAA, 0xD3);
    machine.mem_store_byte(0x02EAB, 0x43);
    machine.mem_store_byte(0x02EA8, 0x16);
    machine.mem_store_byte(0x02EA5, 0x43);
    machine.mem_store_byte(0x02EA6, 0xE7);
    machine.mem_store_byte(0x02EA7, 0xA7);
    machine.mem_store_byte(0x02EA4, 0x79);
    machine.mem_store_byte(0x02EA1, 0x93);
    machine.mem_store_byte(0x02EA2, 0xF9);
    machine.mem_store_byte(0x02EA3, 0xFA);
    machine.mem_store_byte(0x02EA0, 0xCE);
    machine.mem_store_byte(0x02E9D, 0xFC);
    machine.mem_store_byte(0x02E9E, 0x33);
    machine.mem_store_byte(0x02E9F, 0x6A);
    machine.mem_store_byte(0x02E9C, 0x8A);
    machine.mem_store_byte(0x02E99, 0x7E);
    machine.mem_store_byte(0x02E9A, 0x36);
    machine.mem_store_byte(0x02E9B, 0x26);
    machine.mem_store_byte(0xB2590, 0x5C);
    machine.mem_store_byte(0xB2591, 0x09);
    machine.mem_store_byte(0xB2592, 0xE7);
    machine.mem_store_byte(0xB2593, 0xD7);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x37B67AD5);
    EXPECT_EQ(cpu.get_ebx(), 0x0053CCDF);
    EXPECT_EQ(cpu.get_ecx(), 0x6482E98F);
    EXPECT_EQ(cpu.get_edx(), 0x7FFFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x62CBBFF5);
    EXPECT_EQ(cpu.get_ebp(), 0x0000D16E);
    EXPECT_EQ(cpu.get_esp(), 0x00001DCA);
    EXPECT_EQ(cpu.get_cs(), 0x0000A987);
    EXPECT_EQ(cpu.get_ds(), 0x0000DD63);
    EXPECT_EQ(cpu.get_es(), 0x0000EC29);
    EXPECT_EQ(cpu.get_fs(), 0x0000C997);
    EXPECT_EQ(cpu.get_gs(), 0x000009C0);
    EXPECT_EQ(cpu.get_ss(), 0x000002B1);
    EXPECT_EQ(cpu.get_eip(), 0x00008D16);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0C87);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x0FC80), 0x00);
    EXPECT_EQ(memory.load8(0x0FC81), 0x00);
    EXPECT_EQ(memory.load8(0x0FC7E), 0x01);
    EXPECT_EQ(memory.load8(0x0FC7F), 0x04);
    EXPECT_EQ(memory.load8(0x0FC7C), 0xC0);
    EXPECT_EQ(memory.load8(0x0FC7D), 0xED);
    EXPECT_EQ(memory.load8(0x0FC7A), 0x64);
    EXPECT_EQ(memory.load8(0x0FC7B), 0x78);
    EXPECT_EQ(memory.load8(0x0FC78), 0xBA);
    EXPECT_EQ(memory.load8(0x0FC79), 0xF4);
    EXPECT_EQ(memory.load8(0x0FC76), 0xEA);
    EXPECT_EQ(memory.load8(0x0FC77), 0x2F);
    EXPECT_EQ(memory.load8(0x0FC74), 0x1C);
    EXPECT_EQ(memory.load8(0x0FC75), 0xC5);
    EXPECT_EQ(memory.load8(0x0FC72), 0x45);
    EXPECT_EQ(memory.load8(0x0FC73), 0x12);
    EXPECT_EQ(memory.load8(0x0FC70), 0x19);
    EXPECT_EQ(memory.load8(0x0FC71), 0x9F);
    EXPECT_EQ(memory.load8(0x0FC6E), 0x2D);
    EXPECT_EQ(memory.load8(0x0FC6F), 0x90);
    EXPECT_EQ(memory.load8(0x0FC6C), 0x6D);
    EXPECT_EQ(memory.load8(0x0FC6D), 0x87);
    EXPECT_EQ(memory.load8(0x0FC6A), 0x64);
    EXPECT_EQ(memory.load8(0x0FC6B), 0x61);
    EXPECT_EQ(memory.load8(0x0FC68), 0x7E);
    EXPECT_EQ(memory.load8(0x0FC69), 0x78);
    EXPECT_EQ(memory.load8(0x0FC66), 0x16);
    EXPECT_EQ(memory.load8(0x0FC67), 0x15);
    EXPECT_EQ(memory.load8(0x0FC64), 0x67);
    EXPECT_EQ(memory.load8(0x0FC65), 0x84);
    EXPECT_EQ(memory.load8(0x0FC62), 0x29);
    EXPECT_EQ(memory.load8(0x0FC63), 0x59);
    EXPECT_EQ(memory.load8(0x0FC60), 0x47);
    EXPECT_EQ(memory.load8(0x0FC61), 0xB1);
    EXPECT_EQ(memory.load8(0x0FC5E), 0x41);
    EXPECT_EQ(memory.load8(0x0FC5F), 0x88);
    EXPECT_EQ(memory.load8(0x0FC5C), 0xAD);
    EXPECT_EQ(memory.load8(0x0FC5D), 0xE6);
    EXPECT_EQ(memory.load8(0x0FC5A), 0x46);
    EXPECT_EQ(memory.load8(0x0FC5B), 0x09);
    EXPECT_EQ(memory.load8(0x0FC58), 0xE9);
    EXPECT_EQ(memory.load8(0x0FC59), 0x09);
    EXPECT_EQ(memory.load8(0x0FC56), 0x54);
    EXPECT_EQ(memory.load8(0x0FC57), 0xD5);
    EXPECT_EQ(memory.load8(0x0FC54), 0x17);
    EXPECT_EQ(memory.load8(0x0FC55), 0xFF);
    EXPECT_EQ(memory.load8(0x0FC52), 0x36);
    EXPECT_EQ(memory.load8(0x0FC53), 0x97);
    EXPECT_EQ(memory.load8(0x0FC50), 0x1A);
    EXPECT_EQ(memory.load8(0x0FC51), 0x85);
    EXPECT_EQ(memory.load8(0x0FC4E), 0x47);
    EXPECT_EQ(memory.load8(0x0FC4F), 0x9E);
    EXPECT_EQ(memory.load8(0x0FC4C), 0x1A);
    EXPECT_EQ(memory.load8(0x0FC4D), 0x5A);
    EXPECT_EQ(memory.load8(0x0FC4A), 0x07);
    EXPECT_EQ(memory.load8(0x0FC4B), 0xAA);
    EXPECT_EQ(memory.load8(0x0FC48), 0xB6);
    EXPECT_EQ(memory.load8(0x0FC49), 0xF3);
    EXPECT_EQ(memory.load8(0x0FC46), 0xAC);
    EXPECT_EQ(memory.load8(0x0FC47), 0xB5);
    EXPECT_EQ(memory.load8(0x0FC44), 0x55);
    EXPECT_EQ(memory.load8(0x0FC45), 0xCA);
    EXPECT_EQ(memory.load8(0x0FC42), 0x3D);
    EXPECT_EQ(memory.load8(0x0FC43), 0x35);
    EXPECT_EQ(memory.load8(0x0FC40), 0xAA);
    EXPECT_EQ(memory.load8(0x0FC41), 0xF8);
    EXPECT_EQ(memory.load8(0x0FC3E), 0x39);
    EXPECT_EQ(memory.load8(0x0FC3F), 0x0A);
    EXPECT_EQ(memory.load8(0x0FC3C), 0x39);
    EXPECT_EQ(memory.load8(0x0FC3D), 0x3C);
    EXPECT_EQ(memory.load8(0x0FC3A), 0x3E);
    EXPECT_EQ(memory.load8(0x0FC3B), 0x6C);
    EXPECT_EQ(memory.load8(0x0FC38), 0xAF);
    EXPECT_EQ(memory.load8(0x0FC39), 0x17);
    EXPECT_EQ(memory.load8(0x0FC36), 0x4F);
    EXPECT_EQ(memory.load8(0x0FC37), 0x3B);
    EXPECT_EQ(memory.load8(0x0FC34), 0x01);
    EXPECT_EQ(memory.load8(0x0FC35), 0x60);
    EXPECT_EQ(memory.load8(0x0FC32), 0x44);
    EXPECT_EQ(memory.load8(0x0FC33), 0xEF);
    EXPECT_EQ(memory.load8(0x0FC30), 0x21);
    EXPECT_EQ(memory.load8(0x0FC31), 0x31);
    EXPECT_EQ(memory.load8(0x0FC2E), 0xC1);
    EXPECT_EQ(memory.load8(0x0FC2F), 0x6A);
    EXPECT_EQ(memory.load8(0x0FC2C), 0xED);
    EXPECT_EQ(memory.load8(0x0FC2D), 0xCE);
    EXPECT_EQ(memory.load8(0x0FC2A), 0x22);
    EXPECT_EQ(memory.load8(0x0FC2B), 0xD3);
    EXPECT_EQ(memory.load8(0x0FC28), 0x4B);
    EXPECT_EQ(memory.load8(0x0FC29), 0xC3);
    EXPECT_EQ(memory.load8(0x0FC26), 0xC0);
    EXPECT_EQ(memory.load8(0x0FC27), 0x46);
    EXPECT_EQ(memory.load8(0x0FC24), 0x2B);
    EXPECT_EQ(memory.load8(0x0FC25), 0xC8);
    EXPECT_EQ(memory.load8(0x0FC22), 0x0D);
    EXPECT_EQ(memory.load8(0x0FC23), 0xAA);
    EXPECT_EQ(memory.load8(0x0FC20), 0x56);
    EXPECT_EQ(memory.load8(0x0FC21), 0xF5);
    EXPECT_EQ(memory.load8(0x0FC1E), 0xA3);
    EXPECT_EQ(memory.load8(0x0FC1F), 0x62);
    EXPECT_EQ(memory.load8(0x0FC1C), 0x33);
    EXPECT_EQ(memory.load8(0x0FC1D), 0x94);
    EXPECT_EQ(memory.load8(0x0FC1A), 0x4F);
    EXPECT_EQ(memory.load8(0x0FC1B), 0xC5);
    EXPECT_EQ(memory.load8(0x0FC18), 0x43);
    EXPECT_EQ(memory.load8(0x0FC19), 0xA6);
    EXPECT_EQ(memory.load8(0x0FC16), 0x8E);
    EXPECT_EQ(memory.load8(0x0FC17), 0xD3);
    EXPECT_EQ(memory.load8(0x0FC14), 0xA7);
    EXPECT_EQ(memory.load8(0x0FC15), 0x16);
    EXPECT_EQ(memory.load8(0x0FC12), 0x43);
    EXPECT_EQ(memory.load8(0x0FC13), 0xE7);
    EXPECT_EQ(memory.load8(0x0FC10), 0xFA);
    EXPECT_EQ(memory.load8(0x0FC11), 0x79);
    EXPECT_EQ(memory.load8(0x0FC0E), 0x93);
    EXPECT_EQ(memory.load8(0x0FC0F), 0xF9);
    EXPECT_EQ(memory.load8(0x0FC0C), 0x6A);
    EXPECT_EQ(memory.load8(0x0FC0D), 0xCE);
    EXPECT_EQ(memory.load8(0x0FC0A), 0xFC);
    EXPECT_EQ(memory.load8(0x0FC0B), 0x33);
    EXPECT_EQ(memory.load8(0x0FC08), 0x26);
    EXPECT_EQ(memory.load8(0x0FC09), 0x8A);
    EXPECT_EQ(memory.load8(0x0FC06), 0x7E);
    EXPECT_EQ(memory.load8(0x0FC07), 0x36);
    EXPECT_EQ(memory.load8(0x0FC04), 0x00);
    EXPECT_EQ(memory.load8(0x0FC05), 0x00);
    EXPECT_EQ(memory.load8(0x0FC02), 0x6E);
    EXPECT_EQ(memory.load8(0x0FC03), 0xD1);
}

//
// or byte [ds:esi+14h],DAh
//
TEST_F(Test386, or_byte_ds_esi_14h_DAh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xFFFFFF4F);
    cpu.set_ebx(0xFAB4AE91);
    cpu.set_ecx(0x00000401);
    cpu.set_edx(0x9D301BEA);
    cpu.set_esi(0x0000EA9A);
    cpu.set_edi(0x00000000);
    cpu.set_ebp(0x8806DFE7);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000E9F3);
    cpu.set_ds(0x000093E2);
    cpu.set_es(0x000051F0);
    cpu.set_fs(0x0000B076);
    cpu.set_gs(0x00000F00);
    cpu.set_ss(0x000007D4);
    cpu.set_eip(0x00000680);
    cpu.set_eflags(0xFFFC0047);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xEA5B0, 0x67);
    machine.mem_store_byte(0xEA5B1, 0x80);
    machine.mem_store_byte(0xEA5B2, 0x4E);
    machine.mem_store_byte(0xEA5B3, 0x14);
    machine.mem_store_byte(0xEA5B4, 0xDA);
    machine.mem_store_byte(0xEA5B5, 0xF4);
    machine.mem_store_byte(0xEA5B6, 0xC4);
    machine.mem_store_byte(0xEA5B7, 0xB4);
    machine.mem_store_byte(0xEA5B8, 0xCA);
    machine.mem_store_byte(0xEA5B9, 0x13);
    machine.mem_store_byte(0xEA5BA, 0xC4);
    machine.mem_store_byte(0xEA5BB, 0xB7);
    machine.mem_store_byte(0xA28CE, 0xD1);
    machine.mem_store_byte(0xEA5BC, 0x66);
    machine.mem_store_byte(0xEA5BD, 0xBE);
    machine.mem_store_byte(0xEA5BE, 0xDF);
    machine.mem_store_byte(0xEA5BF, 0x36);
    machine.mem_store_byte(0xEA5C0, 0xA8);
    machine.mem_store_byte(0xEA5C1, 0xC6);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xFFFFFF4F);
    EXPECT_EQ(cpu.get_ebx(), 0xFAB4AE91);
    EXPECT_EQ(cpu.get_ecx(), 0x00000401);
    EXPECT_EQ(cpu.get_edx(), 0x9D301BEA);
    EXPECT_EQ(cpu.get_esi(), 0x0000EA9A);
    EXPECT_EQ(cpu.get_edi(), 0x00000000);
    EXPECT_EQ(cpu.get_ebp(), 0x8806DFE7);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x0000E9F3);
    EXPECT_EQ(cpu.get_ds(), 0x000093E2);
    EXPECT_EQ(cpu.get_es(), 0x000051F0);
    EXPECT_EQ(cpu.get_fs(), 0x0000B076);
    EXPECT_EQ(cpu.get_gs(), 0x00000F00);
    EXPECT_EQ(cpu.get_ss(), 0x000007D4);
    EXPECT_EQ(cpu.get_eip(), 0x00000686);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0086);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0xA28CE), 0xDB);
}

//
// o32 leave
//
TEST_F(Test386, o32_leave)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD2B5E066);
    cpu.set_ebx(0xA0D2DE29);
    cpu.set_ecx(0x06051307);
    cpu.set_edx(0x5E2B52BA);
    cpu.set_esi(0x0C901F1A);
    cpu.set_edi(0x7DFA2403);
    cpu.set_ebp(0x1ED617B6);
    cpu.set_esp(0x0000C0D3);
    cpu.set_cs(0x00004B4E);
    cpu.set_ds(0x0000396C);
    cpu.set_es(0x00003F92);
    cpu.set_fs(0x00004010);
    cpu.set_gs(0x00000190);
    cpu.set_ss(0x00007562);
    cpu.set_eip(0x00008A20);
    cpu.set_eflags(0xFFFC0847);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x53F00, 0x66);
    machine.mem_store_byte(0x53F01, 0xC9);
    machine.mem_store_byte(0x53F02, 0xF4);
    machine.mem_store_byte(0x53F03, 0x41);
    machine.mem_store_byte(0x53F04, 0x9E);
    machine.mem_store_byte(0x53F05, 0x48);
    machine.mem_store_byte(0x53F06, 0xCA);
    machine.mem_store_byte(0x53F07, 0x2F);
    machine.mem_store_byte(0x53F08, 0xDD);
    machine.mem_store_byte(0x53F09, 0x48);
    machine.mem_store_byte(0x76DD8, 0xA3);
    machine.mem_store_byte(0x76DD9, 0xF5);
    machine.mem_store_byte(0x76DD6, 0xDD);
    machine.mem_store_byte(0x76DD7, 0xD6);
    machine.mem_store_byte(0x53F0A, 0x64);
    machine.mem_store_byte(0x53F0B, 0x52);
    machine.mem_store_byte(0x53F0C, 0x70);
    machine.mem_store_byte(0x53F0D, 0x02);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD2B5E066);
    EXPECT_EQ(cpu.get_ebx(), 0xA0D2DE29);
    EXPECT_EQ(cpu.get_ecx(), 0x06051307);
    EXPECT_EQ(cpu.get_edx(), 0x5E2B52BA);
    EXPECT_EQ(cpu.get_esi(), 0x0C901F1A);
    EXPECT_EQ(cpu.get_edi(), 0x7DFA2403);
    EXPECT_EQ(cpu.get_ebp(), 0xF5A3D6DD);
    EXPECT_EQ(cpu.get_esp(), 0x000017BA);
    EXPECT_EQ(cpu.get_cs(), 0x00004B4E);
    EXPECT_EQ(cpu.get_ds(), 0x0000396C);
    EXPECT_EQ(cpu.get_es(), 0x00003F92);
    EXPECT_EQ(cpu.get_fs(), 0x00004010);
    EXPECT_EQ(cpu.get_gs(), 0x00000190);
    EXPECT_EQ(cpu.get_ss(), 0x00007562);
    EXPECT_EQ(cpu.get_eip(), 0x00008A23);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0847);

    // Final RAM entries
}

//
// o32 pop ds
//
TEST_F(Test386, o32_pop_ds)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x995074CA);
    cpu.set_ebx(0x05E5FEBF);
    cpu.set_ecx(0xF083DA18);
    cpu.set_edx(0xA04D88A4);
    cpu.set_esi(0x014595EC);
    cpu.set_edi(0xD964BE7F);
    cpu.set_ebp(0x2DF2FE5B);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x0000249D);
    cpu.set_ds(0x00003474);
    cpu.set_es(0x00000000);
    cpu.set_fs(0x000008AE);
    cpu.set_gs(0x00007DDC);
    cpu.set_ss(0x000011A6);
    cpu.set_eip(0x0000CC50);
    cpu.set_eflags(0xFFFC0803);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x31620, 0x66);
    machine.mem_store_byte(0x31621, 0x1F);
    machine.mem_store_byte(0x31622, 0xF4);
    machine.mem_store_byte(0x31623, 0x06);
    machine.mem_store_byte(0x31624, 0x29);
    machine.mem_store_byte(0x31625, 0xFC);
    machine.mem_store_byte(0x31626, 0xE1);
    machine.mem_store_byte(0x31627, 0x90);
    machine.mem_store_byte(0x31628, 0x5C);
    machine.mem_store_byte(0x31629, 0xFB);
    machine.mem_store_byte(0x11A68, 0x64);
    machine.mem_store_byte(0x11A69, 0x0A);
    machine.mem_store_byte(0x3162A, 0xE4);
    machine.mem_store_byte(0x3162B, 0x05);
    machine.mem_store_byte(0x3162C, 0xDF);
    machine.mem_store_byte(0x3162D, 0x58);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x995074CA);
    EXPECT_EQ(cpu.get_ebx(), 0x05E5FEBF);
    EXPECT_EQ(cpu.get_ecx(), 0xF083DA18);
    EXPECT_EQ(cpu.get_edx(), 0xA04D88A4);
    EXPECT_EQ(cpu.get_esi(), 0x014595EC);
    EXPECT_EQ(cpu.get_edi(), 0xD964BE7F);
    EXPECT_EQ(cpu.get_ebp(), 0x2DF2FE5B);
    EXPECT_EQ(cpu.get_esp(), 0x0000000C);
    EXPECT_EQ(cpu.get_cs(), 0x0000249D);
    EXPECT_EQ(cpu.get_ds(), 0x00000A64);
    EXPECT_EQ(cpu.get_es(), 0x00000000);
    EXPECT_EQ(cpu.get_fs(), 0x000008AE);
    EXPECT_EQ(cpu.get_gs(), 0x00007DDC);
    EXPECT_EQ(cpu.get_ss(), 0x000011A6);
    EXPECT_EQ(cpu.get_eip(), 0x0000CC53);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0803);

    // Final RAM entries
}

//
// o32 mov gs,[ds:ecx]
//
TEST_F(Test386, o32_mov_gs_ds_ecx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x00040001);
    cpu.set_ebx(0xFC0555EA);
    cpu.set_ecx(0x00000014);
    cpu.set_edx(0xF7FFFFFF);
    cpu.set_esi(0xC47B745A);
    cpu.set_edi(0x10000001);
    cpu.set_ebp(0xFFFFFFF8);
    cpu.set_esp(0x0000B53C);
    cpu.set_cs(0x0000FFFF);
    cpu.set_ds(0x000025F7);
    cpu.set_es(0x0000E754);
    cpu.set_fs(0x0000A824);
    cpu.set_gs(0x00000000);
    cpu.set_ss(0x00002ECC);
    cpu.set_eip(0x00005250);
    cpu.set_eflags(0xFFFC0843);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x105240, 0x67);
    machine.mem_store_byte(0x105241, 0x66);
    machine.mem_store_byte(0x105242, 0x8E);
    machine.mem_store_byte(0x105243, 0x29);
    machine.mem_store_byte(0x105244, 0xF4);
    machine.mem_store_byte(0x105245, 0x17);
    machine.mem_store_byte(0x105246, 0x21);
    machine.mem_store_byte(0x105247, 0x39);
    machine.mem_store_byte(0x105248, 0x39);
    machine.mem_store_byte(0x105249, 0x3D);
    machine.mem_store_byte(0x10524A, 0x3A);
    machine.mem_store_byte(0x10524B, 0x3F);
    machine.mem_store_byte(0x25F84, 0xB2);
    machine.mem_store_byte(0x25F85, 0x6F);
    machine.mem_store_byte(0x10524C, 0xAB);
    machine.mem_store_byte(0x10524D, 0x53);
    machine.mem_store_byte(0x10524E, 0x72);
    machine.mem_store_byte(0x10524F, 0x36);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x00040001);
    EXPECT_EQ(cpu.get_ebx(), 0xFC0555EA);
    EXPECT_EQ(cpu.get_ecx(), 0x00000014);
    EXPECT_EQ(cpu.get_edx(), 0xF7FFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0xC47B745A);
    EXPECT_EQ(cpu.get_edi(), 0x10000001);
    EXPECT_EQ(cpu.get_ebp(), 0xFFFFFFF8);
    EXPECT_EQ(cpu.get_esp(), 0x0000B53C);
    EXPECT_EQ(cpu.get_cs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_ds(), 0x000025F7);
    EXPECT_EQ(cpu.get_es(), 0x0000E754);
    EXPECT_EQ(cpu.get_fs(), 0x0000A824);
    EXPECT_EQ(cpu.get_gs(), 0x00006FB2);
    EXPECT_EQ(cpu.get_ss(), 0x00002ECC);
    EXPECT_EQ(cpu.get_eip(), 0x00005255);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0843);

    // Final RAM entries
}

//
// o32 pop fs
//
TEST_F(Test386, o32_pop_fs)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x0052936A);
    cpu.set_ebx(0x26AB1150);
    cpu.set_ecx(0x2F444FD3);
    cpu.set_edx(0xFFFFFFFF);
    cpu.set_esi(0x0A7503A1);
    cpu.set_edi(0xA1897E64);
    cpu.set_ebp(0x07617D2D);
    cpu.set_esp(0x0000FFFE);
    cpu.set_cs(0x000009CA);
    cpu.set_ds(0x000000AF);
    cpu.set_es(0x00004EB6);
    cpu.set_fs(0x00000006);
    cpu.set_gs(0x00005D89);
    cpu.set_ss(0x00000000);
    cpu.set_eip(0x00000948);
    cpu.set_eflags(0xFFFC0086);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x0A5E8, 0x66);
    machine.mem_store_byte(0x0A5E9, 0x0F);
    machine.mem_store_byte(0x0A5EA, 0xA1);
    machine.mem_store_byte(0x0A5EB, 0xF4);
    machine.mem_store_byte(0x0A5EC, 0x4A);
    machine.mem_store_byte(0x0A5ED, 0xE3);
    machine.mem_store_byte(0x0A5EE, 0x55);
    machine.mem_store_byte(0x0A5EF, 0x70);
    machine.mem_store_byte(0x0A5F0, 0x65);
    machine.mem_store_byte(0x0A5F1, 0x1A);
    machine.mem_store_byte(0x0FFFE, 0x21);
    machine.mem_store_byte(0x0FFFF, 0x49);
    machine.mem_store_byte(0x0A5F2, 0x55);
    machine.mem_store_byte(0x0A5F3, 0x78);
    machine.mem_store_byte(0x0A5F4, 0x8E);
    machine.mem_store_byte(0x0A5F5, 0x81);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x0052936A);
    EXPECT_EQ(cpu.get_ebx(), 0x26AB1150);
    EXPECT_EQ(cpu.get_ecx(), 0x2F444FD3);
    EXPECT_EQ(cpu.get_edx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_esi(), 0x0A7503A1);
    EXPECT_EQ(cpu.get_edi(), 0xA1897E64);
    EXPECT_EQ(cpu.get_ebp(), 0x07617D2D);
    EXPECT_EQ(cpu.get_esp(), 0x00000002);
    EXPECT_EQ(cpu.get_cs(), 0x000009CA);
    EXPECT_EQ(cpu.get_ds(), 0x000000AF);
    EXPECT_EQ(cpu.get_es(), 0x00004EB6);
    EXPECT_EQ(cpu.get_fs(), 0x00004921);
    EXPECT_EQ(cpu.get_gs(), 0x00005D89);
    EXPECT_EQ(cpu.get_ss(), 0x00000000);
    EXPECT_EQ(cpu.get_eip(), 0x0000094C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0086);

    // Final RAM entries
}

//
// o32 push 39h
//
TEST_F(Test386, o32_push_39h)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xD7343A87);
    cpu.set_ebx(0xFFFFFFFF);
    cpu.set_ecx(0x28AEEC30);
    cpu.set_edx(0x47F0EBF3);
    cpu.set_esi(0x994F2A79);
    cpu.set_edi(0x07CDA020);
    cpu.set_ebp(0xF8638720);
    cpu.set_esp(0x0000647A);
    cpu.set_cs(0x00009590);
    cpu.set_ds(0x0000BA57);
    cpu.set_es(0x0000824A);
    cpu.set_fs(0x0000E38E);
    cpu.set_gs(0x00000022);
    cpu.set_ss(0x0000FDD7);
    cpu.set_eip(0x000060F0);
    cpu.set_eflags(0xFFFC0446);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x9B9F0, 0x66);
    machine.mem_store_byte(0x9B9F1, 0x6A);
    machine.mem_store_byte(0x9B9F2, 0x39);
    machine.mem_store_byte(0x9B9F3, 0xF4);
    machine.mem_store_byte(0x9B9F4, 0x19);
    machine.mem_store_byte(0x9B9F5, 0x86);
    machine.mem_store_byte(0x9B9F6, 0x8E);
    machine.mem_store_byte(0x9B9F7, 0xF2);
    machine.mem_store_byte(0x9B9F8, 0xA7);
    machine.mem_store_byte(0x9B9F9, 0xE5);
    machine.mem_store_byte(0x9B9FA, 0x38);
    machine.mem_store_byte(0x9B9FB, 0xFB);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xD7343A87);
    EXPECT_EQ(cpu.get_ebx(), 0xFFFFFFFF);
    EXPECT_EQ(cpu.get_ecx(), 0x28AEEC30);
    EXPECT_EQ(cpu.get_edx(), 0x47F0EBF3);
    EXPECT_EQ(cpu.get_esi(), 0x994F2A79);
    EXPECT_EQ(cpu.get_edi(), 0x07CDA020);
    EXPECT_EQ(cpu.get_ebp(), 0xF8638720);
    EXPECT_EQ(cpu.get_esp(), 0x00006476);
    EXPECT_EQ(cpu.get_cs(), 0x00009590);
    EXPECT_EQ(cpu.get_ds(), 0x0000BA57);
    EXPECT_EQ(cpu.get_es(), 0x0000824A);
    EXPECT_EQ(cpu.get_fs(), 0x0000E38E);
    EXPECT_EQ(cpu.get_gs(), 0x00000022);
    EXPECT_EQ(cpu.get_ss(), 0x0000FDD7);
    EXPECT_EQ(cpu.get_eip(), 0x000060F4);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0446);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x1041E8), 0x00);
    EXPECT_EQ(memory.load8(0x1041E9), 0x00);
    EXPECT_EQ(memory.load8(0x1041E6), 0x39);
    EXPECT_EQ(memory.load8(0x1041E7), 0x00);
}

//
// o32 push cs
//
TEST_F(Test386, o32_push_cs)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x093E57AC);
    cpu.set_ebx(0x000000AF);
    cpu.set_ecx(0xB446BA9F);
    cpu.set_edx(0x33362A15);
    cpu.set_esi(0xFFFFFF0F);
    cpu.set_edi(0x5A5A5A5A);
    cpu.set_ebp(0x00000000);
    cpu.set_esp(0x0000BE82);
    cpu.set_cs(0x0000B296);
    cpu.set_ds(0x0000917F);
    cpu.set_es(0x0000FFDF);
    cpu.set_fs(0x0000FFFF);
    cpu.set_gs(0x00000015);
    cpu.set_ss(0x0000876C);
    cpu.set_eip(0x00007AD0);
    cpu.set_eflags(0xFFFC0893);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xBA430, 0x66);
    machine.mem_store_byte(0xBA431, 0x0E);
    machine.mem_store_byte(0xBA432, 0xF4);
    machine.mem_store_byte(0xBA433, 0x4A);
    machine.mem_store_byte(0xBA434, 0x7B);
    machine.mem_store_byte(0xBA435, 0x36);
    machine.mem_store_byte(0xBA436, 0x28);
    machine.mem_store_byte(0xBA437, 0xCD);
    machine.mem_store_byte(0xBA438, 0x61);
    machine.mem_store_byte(0xBA439, 0x21);
    machine.mem_store_byte(0xBA43A, 0x0F);
    machine.mem_store_byte(0xBA43B, 0x11);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x093E57AC);
    EXPECT_EQ(cpu.get_ebx(), 0x000000AF);
    EXPECT_EQ(cpu.get_ecx(), 0xB446BA9F);
    EXPECT_EQ(cpu.get_edx(), 0x33362A15);
    EXPECT_EQ(cpu.get_esi(), 0xFFFFFF0F);
    EXPECT_EQ(cpu.get_edi(), 0x5A5A5A5A);
    EXPECT_EQ(cpu.get_ebp(), 0x00000000);
    EXPECT_EQ(cpu.get_esp(), 0x0000BE7E);
    EXPECT_EQ(cpu.get_cs(), 0x0000B296);
    EXPECT_EQ(cpu.get_ds(), 0x0000917F);
    EXPECT_EQ(cpu.get_es(), 0x0000FFDF);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFF);
    EXPECT_EQ(cpu.get_gs(), 0x00000015);
    EXPECT_EQ(cpu.get_ss(), 0x0000876C);
    EXPECT_EQ(cpu.get_eip(), 0x00007AD3);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0893);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x9353E), 0x96);
    EXPECT_EQ(memory.load8(0x9353F), 0xB2);
}

//
// or [ds:bx-979h],edx
//
TEST_F(Test386, or_ds_bx_979h_edx)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x3FFFFFFF);
    cpu.set_ebx(0xA9C0FAF6);
    cpu.set_ecx(0xC0835758);
    cpu.set_edx(0x00000008);
    cpu.set_esi(0x07C16F22);
    cpu.set_edi(0x0000001D);
    cpu.set_ebp(0xF2EE8174);
    cpu.set_esp(0x00000008);
    cpu.set_cs(0x00002FA1);
    cpu.set_ds(0x00005863);
    cpu.set_es(0x0000001F);
    cpu.set_fs(0x0000FFFB);
    cpu.set_gs(0x00004907);
    cpu.set_ss(0x0000702E);
    cpu.set_eip(0x00000958);
    cpu.set_eflags(0xFFFC0413);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x30368, 0x66);
    machine.mem_store_byte(0x30369, 0x09);
    machine.mem_store_byte(0x3036A, 0x97);
    machine.mem_store_byte(0x3036B, 0x87);
    machine.mem_store_byte(0x3036C, 0xF6);
    machine.mem_store_byte(0x3036D, 0xF4);
    machine.mem_store_byte(0x3036E, 0x3B);
    machine.mem_store_byte(0x3036F, 0xA2);
    machine.mem_store_byte(0x30370, 0xBE);
    machine.mem_store_byte(0x30371, 0x7E);
    machine.mem_store_byte(0x30372, 0xF1);
    machine.mem_store_byte(0x30373, 0x3B);
    machine.mem_store_byte(0x677B0, 0x44);
    machine.mem_store_byte(0x677AD, 0xD0);
    machine.mem_store_byte(0x677AE, 0xEE);
    machine.mem_store_byte(0x677AF, 0x5D);
    machine.mem_store_byte(0x30374, 0xE4);
    machine.mem_store_byte(0x30375, 0x75);
    machine.mem_store_byte(0x30376, 0x77);
    machine.mem_store_byte(0x30377, 0x4F);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x3FFFFFFF);
    EXPECT_EQ(cpu.get_ebx(), 0xA9C0FAF6);
    EXPECT_EQ(cpu.get_ecx(), 0xC0835758);
    EXPECT_EQ(cpu.get_edx(), 0x00000008);
    EXPECT_EQ(cpu.get_esi(), 0x07C16F22);
    EXPECT_EQ(cpu.get_edi(), 0x0000001D);
    EXPECT_EQ(cpu.get_ebp(), 0xF2EE8174);
    EXPECT_EQ(cpu.get_esp(), 0x00000008);
    EXPECT_EQ(cpu.get_cs(), 0x00002FA1);
    EXPECT_EQ(cpu.get_ds(), 0x00005863);
    EXPECT_EQ(cpu.get_es(), 0x0000001F);
    EXPECT_EQ(cpu.get_fs(), 0x0000FFFB);
    EXPECT_EQ(cpu.get_gs(), 0x00004907);
    EXPECT_EQ(cpu.get_ss(), 0x0000702E);
    EXPECT_EQ(cpu.get_eip(), 0x0000095E);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0406);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x677AD), 0xD8);
}

//
// o32 push fs
//
TEST_F(Test386, o32_push_fs)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0x80B2DE9C);
    cpu.set_ebx(0xD5CD58FF);
    cpu.set_ecx(0x00000001);
    cpu.set_edx(0xCC3FCBA1);
    cpu.set_esi(0x5919DAC1);
    cpu.set_edi(0x2BC3064A);
    cpu.set_ebp(0x676A8115);
    cpu.set_esp(0x0000039E);
    cpu.set_cs(0x0000E8AF);
    cpu.set_ds(0x0000FFBD);
    cpu.set_es(0x0000E357);
    cpu.set_fs(0x000021F9);
    cpu.set_gs(0x0000A2B2);
    cpu.set_ss(0x00004239);
    cpu.set_eip(0x0000A198);
    cpu.set_eflags(0xFFFC0412);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0xF2C88, 0x66);
    machine.mem_store_byte(0xF2C89, 0x0F);
    machine.mem_store_byte(0xF2C8A, 0xA0);
    machine.mem_store_byte(0xF2C8B, 0xF4);
    machine.mem_store_byte(0xF2C8C, 0xD2);
    machine.mem_store_byte(0xF2C8D, 0x5F);
    machine.mem_store_byte(0xF2C8E, 0x2B);
    machine.mem_store_byte(0xF2C8F, 0x93);
    machine.mem_store_byte(0xF2C90, 0x51);
    machine.mem_store_byte(0xF2C91, 0x15);
    machine.mem_store_byte(0xF2C92, 0xC2);
    machine.mem_store_byte(0xF2C93, 0x61);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0x80B2DE9C);
    EXPECT_EQ(cpu.get_ebx(), 0xD5CD58FF);
    EXPECT_EQ(cpu.get_ecx(), 0x00000001);
    EXPECT_EQ(cpu.get_edx(), 0xCC3FCBA1);
    EXPECT_EQ(cpu.get_esi(), 0x5919DAC1);
    EXPECT_EQ(cpu.get_edi(), 0x2BC3064A);
    EXPECT_EQ(cpu.get_ebp(), 0x676A8115);
    EXPECT_EQ(cpu.get_esp(), 0x0000039A);
    EXPECT_EQ(cpu.get_cs(), 0x0000E8AF);
    EXPECT_EQ(cpu.get_ds(), 0x0000FFBD);
    EXPECT_EQ(cpu.get_es(), 0x0000E357);
    EXPECT_EQ(cpu.get_fs(), 0x000021F9);
    EXPECT_EQ(cpu.get_gs(), 0x0000A2B2);
    EXPECT_EQ(cpu.get_ss(), 0x00004239);
    EXPECT_EQ(cpu.get_eip(), 0x0000A19C);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0412);

    // Final RAM entries
    EXPECT_EQ(memory.load8(0x4272A), 0xF9);
    EXPECT_EQ(memory.load8(0x4272B), 0x21);
}

//
// or eax,5ECF765Fh
//
TEST_F(Test386, or_eax_5ECF765Fh)
{
    // Initial CPU State
    cpu.set_cr0(0x7FFEFFF0);
    cpu.set_cr3(0x00000000);
    cpu.set_eax(0xDDDE7E10);
    cpu.set_ebx(0x00000000);
    cpu.set_ecx(0x4A575308);
    cpu.set_edx(0x32BF1418);
    cpu.set_esi(0xFEFFFFFF);
    cpu.set_edi(0x89185FAD);
    cpu.set_ebp(0xBAEBC643);
    cpu.set_esp(0x000000E0);
    cpu.set_cs(0x00006308);
    cpu.set_ds(0x00007D56);
    cpu.set_es(0x00004A22);
    cpu.set_fs(0x00004701);
    cpu.set_gs(0x0000FFF6);
    cpu.set_ss(0x00000801);
    cpu.set_eip(0x00005840);
    cpu.set_eflags(0xFFFC0C07);
    cpu.set_dr6(0xFFFF0FF0);
    cpu.set_dr7(0x00000000);
    machine.trace_registers();

    // Initial RAM entries
    machine.mem_store_byte(0x688C0, 0x66);
    machine.mem_store_byte(0x688C1, 0x0D);
    machine.mem_store_byte(0x688C2, 0x5F);
    machine.mem_store_byte(0x688C3, 0x76);
    machine.mem_store_byte(0x688C4, 0xCF);
    machine.mem_store_byte(0x688C5, 0x5E);
    machine.mem_store_byte(0x688C6, 0xF4);
    machine.mem_store_byte(0x688C7, 0x5E);
    machine.mem_store_byte(0x688C8, 0x38);
    machine.mem_store_byte(0x688C9, 0x7E);
    machine.mem_store_byte(0x688CA, 0x1E);
    machine.mem_store_byte(0x688CB, 0xF6);
    machine.mem_store_byte(0x688CC, 0x7B);
    machine.mem_store_byte(0x688CD, 0xC6);
    machine.mem_store_byte(0x688CE, 0xBA);
    machine.mem_store_byte(0x688CF, 0x93);

    // Single-step.
    cpu.step();
    cpu.step(); // HLT

    // Final CPU State
    EXPECT_EQ(cpu.get_cr0(), 0x7FFEFFF0);
    EXPECT_EQ(cpu.get_cr3(), 0x00000000);
    EXPECT_EQ(cpu.get_eax(), 0xDFDF7E5F);
    EXPECT_EQ(cpu.get_ebx(), 0x00000000);
    EXPECT_EQ(cpu.get_ecx(), 0x4A575308);
    EXPECT_EQ(cpu.get_edx(), 0x32BF1418);
    EXPECT_EQ(cpu.get_esi(), 0xFEFFFFFF);
    EXPECT_EQ(cpu.get_edi(), 0x89185FAD);
    EXPECT_EQ(cpu.get_ebp(), 0xBAEBC643);
    EXPECT_EQ(cpu.get_esp(), 0x000000E0);
    EXPECT_EQ(cpu.get_cs(), 0x00006308);
    EXPECT_EQ(cpu.get_ds(), 0x00007D56);
    EXPECT_EQ(cpu.get_es(), 0x00004A22);
    EXPECT_EQ(cpu.get_fs(), 0x00004701);
    EXPECT_EQ(cpu.get_gs(), 0x0000FFF6);
    EXPECT_EQ(cpu.get_ss(), 0x00000801);
    EXPECT_EQ(cpu.get_eip(), 0x00005847);
    EXPECT_EQ(cpu.get_dr6(), 0xFFFF0FF0);
    EXPECT_EQ(cpu.get_dr7(), 0x00000000);
    EXPECT_FLAGS(0xFFFC0486);

    // Final RAM entries
}
