//
// Unit test: verify Bios_Data_Area field offsets match the BDA specification
// (legacy/bios_data_area.txt, segment 40h). Uses offsetof() for each field.
//
#include <gtest/gtest.h>

#include <cstddef>

#include "bios.h"

//
// BDA offset checks vs specification (segment 40h = physical 0x400+).
// Each EXPECT asserts that the struct member lies at the specified byte offset.
//
TEST(BdaOffsetsTest, OffsetsMatchSpecification)
{
    // 40:00 - Serial and parallel port addresses
    EXPECT_EQ(offsetof(Bios_Data_Area, port_com), 0x00u);
    EXPECT_EQ(offsetof(Bios_Data_Area, port_lpt), 0x08u);
    EXPECT_EQ(offsetof(Bios_Data_Area, ebda_seg), 0x0Eu);

    // 40:10 - Equipment and memory
    EXPECT_EQ(offsetof(Bios_Data_Area, equipment_list_flags), 0x10u);
    EXPECT_EQ(offsetof(Bios_Data_Area, reserved_12h), 0x12u);
    EXPECT_EQ(offsetof(Bios_Data_Area, mem_size_kb), 0x13u);
    EXPECT_EQ(offsetof(Bios_Data_Area, reserved_15h), 0x15u);
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_flag0),
              0x17u); // 40:17 Keyboard flags 1, 40:18 Keyboard flags 2
    EXPECT_EQ(offsetof(Bios_Data_Area, alt_keypad), 0x19u);

    // 40:1A - Keyboard buffer pointers and buffer
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_buf_head), 0x1Au);
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_buf_tail), 0x1Cu);
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_buf), 0x1Eu);

    // 40:3E - Floppy
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_recalibration_status), 0x3Eu);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_motor_status), 0x3Fu);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_motor_counter), 0x40u);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_last_status), 0x41u);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_controller_status), 0x42u);

    // 40:49 - Video
    EXPECT_EQ(offsetof(Bios_Data_Area, video_mode), 0x49u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_cols), 0x4Au);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_pagesize), 0x4Cu);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_pagestart), 0x4Eu);
    EXPECT_EQ(offsetof(Bios_Data_Area, cursor_pos), 0x50u);

    // 40:60 - Cursor and CRT
    EXPECT_EQ(offsetof(Bios_Data_Area, cursor_type), 0x60u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_page), 0x62u);
    EXPECT_EQ(offsetof(Bios_Data_Area, crtc_address), 0x63u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_msr), 0x65u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_pal), 0x66u);

    // 40:67 - Block move save, POST reserved, timer
    EXPECT_EQ(offsetof(Bios_Data_Area, block_move_ss_sp), 0x67u);
    EXPECT_EQ(offsetof(Bios_Data_Area, reserved_post_6b), 0x6Bu);
    EXPECT_EQ(offsetof(Bios_Data_Area, timer_counter), 0x6Cu);

    // 40:70 - Timer overflow, break, reset, disk
    EXPECT_EQ(offsetof(Bios_Data_Area, timer_rollover), 0x70u);
    EXPECT_EQ(offsetof(Bios_Data_Area, break_flag), 0x71u);
    EXPECT_EQ(offsetof(Bios_Data_Area, soft_reset_flag), 0x72u);
    EXPECT_EQ(offsetof(Bios_Data_Area, disk_last_status), 0x74u);
    EXPECT_EQ(offsetof(Bios_Data_Area, hdcount), 0x75u);
    EXPECT_EQ(offsetof(Bios_Data_Area, disk_control_byte), 0x76u);
    EXPECT_EQ(offsetof(Bios_Data_Area, port_disk), 0x77u);

    // 40:78 - LPT/COM timeouts, INT 4Bh flags
    EXPECT_EQ(offsetof(Bios_Data_Area, lpt_timeout), 0x78u);
    EXPECT_EQ(offsetof(Bios_Data_Area, int4b_flags), 0x7Bu);
    EXPECT_EQ(offsetof(Bios_Data_Area, com_timeout), 0x7Cu);

    // 40:80 - Keyboard buffer bounds, video rows/height, flags
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_buf_start_offset), 0x80u);
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_buf_end_offset), 0x82u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_rows), 0x84u);
    EXPECT_EQ(offsetof(Bios_Data_Area, char_height), 0x85u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_ctl), 0x87u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_switches), 0x88u);
    EXPECT_EQ(offsetof(Bios_Data_Area, modeset_ctl), 0x89u);
    EXPECT_EQ(offsetof(Bios_Data_Area, dcc_index), 0x8Au);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_last_data_rate), 0x8Bu);
    EXPECT_EQ(offsetof(Bios_Data_Area, disk_status_controller), 0x8Cu);
    EXPECT_EQ(offsetof(Bios_Data_Area, disk_error_controller), 0x8Du);
    EXPECT_EQ(offsetof(Bios_Data_Area, disk_interrupt_flag), 0x8Eu);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_harddisk_info), 0x8Fu);

    // 40:90 - Floppy media, workarea, track; keyboard mode/LED; wait
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_media_state), 0x90u);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_workarea), 0x92u);
    EXPECT_EQ(offsetof(Bios_Data_Area, floppy_track), 0x94u);
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_flag1), 0x96u);
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_led), 0x97u);
    EXPECT_EQ(offsetof(Bios_Data_Area, user_wait_complete_flag), 0x98u);
    EXPECT_EQ(offsetof(Bios_Data_Area, user_wait_timeout), 0x9Cu);

    // 40:A0 - RTC wait, reserved, video savetable
    EXPECT_EQ(offsetof(Bios_Data_Area, rtc_wait_flag), 0xA0u);
    EXPECT_EQ(offsetof(Bios_Data_Area, other_a1), 0xA1u);
    EXPECT_EQ(offsetof(Bios_Data_Area, video_savetable), 0xA8u);

    // 40:AC - Reserved through 40:B3
    EXPECT_EQ(offsetof(Bios_Data_Area, reserved_ac), 0xACu);

    // 40:B4 - Keyboard NMI save, reserved, days since 1980, reserved to end
    EXPECT_EQ(offsetof(Bios_Data_Area, kbd_nmi_save), 0xB4u);
    EXPECT_EQ(offsetof(Bios_Data_Area, reserved_cc), 0xCCu);
    EXPECT_EQ(offsetof(Bios_Data_Area, days_since_1980), 0xCEu);
    EXPECT_EQ(offsetof(Bios_Data_Area, reserved_d0), 0xD0u);
}

TEST(BdaOffsetsTest, TotalSizeIs256Bytes)
{
    EXPECT_EQ(sizeof(Bios_Data_Area), 0x100u);
}
