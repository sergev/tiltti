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
// INT 10h AH=05h: Select display page.
//
TEST_F(MachineTest, SelectDisplayPage)
{
    cpu.set_al(0x03);
    machine.int10_set_video_mode();
    EXPECT_EQ(machine.bda.video_page, 0);
    EXPECT_EQ(machine.bda.video_pagestart, 0);

    cpu.set_al(1);
    machine.int10_select_display_page();

    EXPECT_EQ(machine.bda.video_page, 1);
    EXPECT_EQ(machine.bda.video_pagestart, 80 * 25 * 2);

    cpu.set_ah(0x0f);
    machine.int10_get_current_video_mode();
    EXPECT_EQ(cpu.get_bh(), 1);
}

//
// INT 10h AH=03h: Get cursor position.
//
TEST_F(MachineTest, GetCursorPosition)
{
    cpu.set_al(0x03);
    machine.int10_set_video_mode();

    cpu.set_bh(0);
    cpu.set_dh(5);
    cpu.set_dl(10);
    machine.int10_set_cursor_position();

    cpu.set_bh(0);
    machine.int10_get_cursor_position();
    EXPECT_EQ(cpu.get_dh(), 5);
    EXPECT_EQ(cpu.get_dl(), 10);
    EXPECT_EQ(cpu.get_cx(), 0x0607);

    cpu.set_bh(8); // invalid page
    machine.int10_get_cursor_position();
    EXPECT_EQ(cpu.get_dh(), 0);
    EXPECT_EQ(cpu.get_dl(), 0);
    EXPECT_EQ(cpu.get_cx(), 0);
}

//
// INT 10h AH=0Ah: Write character only; attribute is preserved.
//
TEST_F(MachineTest, WriteCharOnlyPreservesAttribute)
{
    cpu.set_al(0x03);
    machine.int10_set_video_mode();

    cpu.set_bh(0);
    cpu.set_dh(0);
    cpu.set_dl(0);
    machine.int10_set_cursor_position();

    cpu.set_al('A');
    cpu.set_bh(0);
    cpu.set_bl(0x4e);
    cpu.set_cx(1);
    machine.int10_write_char();

    EXPECT_EQ(memory.load16(0xb8000), 0x4e41u); // 'A' with attr 0x4E

    cpu.set_bh(0);
    cpu.set_dh(0);
    cpu.set_dl(0);
    machine.int10_set_cursor_position();

    cpu.set_al('B');
    cpu.set_bh(0);
    cpu.set_cx(1);
    machine.int10_write_char_only();

    EXPECT_EQ(memory.load16(0xb8000), 0x4e42u); // 'B' with attr 0x4E unchanged
}

//
// Output one character via Int 10h syscall, and check result in video memory.
//
TEST_F(MachineTest, TeletypeOutput)
{
    const Byte *base = memory.get_ptr(0xb8000);
    const auto page  = machine.bda.video_page;

    // Initial contents: spaces.
    EXPECT_EQ(base[0], ' ');
    EXPECT_EQ(machine.bda.cursor_pos[page], 0x00'00);

    // Output a character.
    cpu.set_al('f');
    machine.int10_teletype_output();

    // Check result in video memory.
    EXPECT_EQ(base[0], 'f');
    EXPECT_EQ(machine.bda.cursor_pos[page], 0x00'01);

    // Another character.
    cpu.set_al('o');
    machine.int10_teletype_output();
    EXPECT_EQ(base[2], 'o');
    EXPECT_EQ(machine.bda.cursor_pos[page], 0x00'02);

    // Newline.
    cpu.set_al('\n');
    machine.int10_teletype_output();
    EXPECT_EQ(machine.bda.cursor_pos[page], 0x01'02);

    // Carriage return.
    cpu.set_al('\r');
    machine.int10_teletype_output();
    EXPECT_EQ(machine.bda.cursor_pos[page], 0x01'00);

    // Another character.
    cpu.set_al('b');
    machine.int10_teletype_output();
    EXPECT_EQ(base[2*80], 'b');
    EXPECT_EQ(machine.bda.cursor_pos[page], 0x01'01);

    // Backspace.
    cpu.set_al('\b');
    machine.int10_teletype_output();
    EXPECT_EQ(machine.bda.cursor_pos[page], 0x01'00);
}

//
// INT 10h AH=1Bh: Video BIOS functionality — fill video_func_info at ES:DI.
//
TEST_F(MachineTest, VideoBiosFunctionality)
{
    const unsigned buf_linear = 0x500;
    cpu.set_es(0x50);
    cpu.set_di(0);
    machine.int10_video_bios_functionality();

    EXPECT_EQ(cpu.get_al(), 0x1B);

    EXPECT_EQ(memory.load16(buf_linear + 0), 0x0000);
    EXPECT_EQ(memory.load16(buf_linear + 2), static_cast<uint16_t>(BIOS_VIDEO_FUNC_STATIC >> 4));

    EXPECT_EQ(memory.load16(buf_linear + 39), 16);  // colors
    EXPECT_EQ(memory.load8(buf_linear + 41), 8);   // pages
    EXPECT_EQ(memory.load8(buf_linear + 42), 2);   // scan_lines
    EXPECT_EQ(memory.load8(buf_linear + 49), 3);   // video_mem

    EXPECT_EQ(memory.load8(buf_linear + 37), machine.bda.dcc_index);

    for (unsigned i = 0; i < 30; i++)
        EXPECT_EQ(memory.load8(buf_linear + 4 + i), memory.load8(0x449 + i)) << "bda_0x49[" << i << "]";
    for (unsigned i = 0; i < 3; i++)
        EXPECT_EQ(memory.load8(buf_linear + 34 + i), memory.load8(0x484 + i)) << "bda_0x84[" << i << "]";
}
