#include "fixture.h"

//
// INT 10h AH=00h: Set video mode 3, clear screen, verify BDA and video memory.
//
TEST_F(MachineTest, SetVideoModeClearsScreen)
{
    cpu.set_al(0x03);
    machine.int10_set_video_mode();

    EXPECT_EQ(cpu.get_al(), 0x30); // 80-column indicator

    EXPECT_EQ(machine.bda.video_mode, 3);
    EXPECT_EQ(machine.bda.video_cols, 80);
    EXPECT_EQ(machine.bda.video_rows, 24);
    EXPECT_EQ(machine.bda.video_pagesize, 80 * 25 * 2);
    EXPECT_EQ(machine.bda.cursor_type, 0x0607);
    EXPECT_EQ(machine.bda.video_page, 0);
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(machine.bda.cursor_pos[i], 0x0000);

    EXPECT_EQ(memory.load16(0xb8000), 0x0720); // space + attr 0x07
    EXPECT_EQ(memory.load16(0xb8002), 0x0720);
}

//
// INT 10h AH=00h AL=0x83: Set mode 3 without clearing; video memory unchanged.
//
TEST_F(MachineTest, SetVideoModeNoClear)
{
    memory.store16(0xb8000, 0x1234); // arbitrary content
    cpu.set_al(0x83);                // mode 3, bit 7 = do not clear
    machine.int10_set_video_mode();

    EXPECT_EQ(memory.load16(0xb8000), 0x1234); // unchanged
}

//
// Output one character via Int 10h syscall, and check result in video memory.
//
TEST_F(MachineTest, TeletypeOutput)
{
    Byte const ch = 'Q';
    Byte *base    = memory.get_ptr(0xb8000);

    EXPECT_NE(base[0], ch);

    // Output a character.
    cpu.set_al(ch);
    machine.int10_teletype_output();

    // Check result in video memory.
    EXPECT_EQ(base[0], ch);
}
