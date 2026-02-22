//
// PC i86 architecture details.
//
// Copyright (c) 2026 Serge Vakulenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef TILTTI_I86_ARCH_H
#define TILTTI_I86_ARCH_H

#include <cstdint>
#include <ostream>
#include <vector>

//
// Size of disk sector.
//
static const unsigned SECTOR_NBYTES = 512;

//
// Memory size 1 Mbyte.
//
static const unsigned MEMORY_NBYTES = 1024 * 1024;

//
// Total 4 hard+floppy disks.
//
static const unsigned NDISKS = 4;
enum {
    FLOPPY_A = 0,
    FLOPPY_B = 1,
    DISK_C   = 2,
    DISK_D   = 3,
};

//
// 8-bit unsigned byte.
// 16-bit memory word.
//
using Byte = uint8_t;
using Word = uint16_t;

//
// Array of bytes.
// Array of words.
//
using Bytes = std::vector<Byte>;
using Words = std::vector<Word>;

//
// Real-mode linear address from segment:offset.
//
inline unsigned pc86_linear_addr(Word seg, Word off)
{
    return ((seg << 4) + off) & 0xFFFFFu;
}

//
// Convert numbers to strings.
//
std::string to_hex(unsigned val);

//
// Bits of memory word, from right to left, starting from 1.
//
#define ONEBIT(n)      (1U << (n))                   // single bit, from 0 до 31
#define BITS(n)        ((uint32_t)~0U >> (31 - (n))) // bit mask n..0
#define FIELD(x, n, w) (((x) >> (n)) & BITS(w))      // field of w bits, starting from bit n

//
// Definition for common 16bit segment/offset pointers.
//
struct Seg_Off {
    union {
        struct {
            uint16_t offset;
            uint16_t seg;
        };
        uint32_t segoff;
    };
};

//
// Interrupt vector table
//
struct Interrupt_Vector_Table {
    Seg_Off ivec[256];
};

//
// Bios Data Area (BDA)
//
struct Bios_Data_Area {
    // 40:00
    uint16_t port_com[4];
    uint16_t port_lpt[3];
    uint16_t ebda_seg;
    // 40:10
    uint16_t equipment_list_flags;
    uint8_t pad1;
    uint16_t mem_size_kb;
    uint8_t pad2;
    uint8_t ps2_ctrl_flag;
    uint16_t kbd_flag0;
    uint8_t alt_keypad;
    uint16_t kbd_buf_head;
    uint16_t kbd_buf_tail;
    // 40:1e
    uint8_t kbd_buf[32];
    uint8_t floppy_recalibration_status;
    uint8_t floppy_motor_status;
    // 40:40
    uint8_t floppy_motor_counter;
    uint8_t floppy_last_status;
    uint8_t floppy_return_status[7];
    uint8_t video_mode;
    uint16_t video_cols;
    uint16_t video_pagesize;
    uint16_t video_pagestart;
    // 40:50
    uint16_t cursor_pos[8];
    // 40:60
    uint16_t cursor_type;
    uint8_t video_page;
    uint16_t crtc_address;
    uint8_t video_msr;
    uint8_t video_pal;
    Seg_Off jump;
    uint8_t other_6b;
    uint32_t timer_counter;
    // 40:70
    uint8_t timer_rollover;
    uint8_t break_flag;
    uint16_t soft_reset_flag;
    uint8_t disk_last_status;
    uint8_t hdcount;
    uint8_t disk_control_byte;
    uint8_t port_disk;
    uint8_t lpt_timeout[4];
    uint8_t com_timeout[4];
    // 40:80
    uint16_t kbd_buf_start_offset;
    uint16_t kbd_buf_end_offset;
    uint8_t video_rows;
    uint16_t char_height;
    uint8_t video_ctl;
    uint8_t video_switches;
    uint8_t modeset_ctl;
    uint8_t dcc_index;
    uint8_t floppy_last_data_rate;
    uint8_t disk_status_controller;
    uint8_t disk_error_controller;
    uint8_t disk_interrupt_flag;
    uint8_t floppy_harddisk_info;
    // 40:90
    uint8_t floppy_media_state[4];
    uint8_t floppy_track[2];
    uint8_t kbd_flag1;
    uint8_t kbd_led;
    Seg_Off user_wait_complete_flag;
    uint32_t user_wait_timeout;
    // 40:A0
    uint8_t rtc_wait_flag;
    uint8_t other_a1[7];
    Seg_Off video_savetable;
    uint8_t other_ac[4];
    // 40:B0
    uint8_t other_b0[5 * 16];
} __attribute__((packed));

//
// BIOS Fixed Addresses.
// These are required for IBM PC/AT compatibility.
// Physical address = segment base 0xF0000 + offset.
// For example, reset vector = 0xFFFF0.
//

// Fixed Entry Points
enum {
    BIOS_ENTRY_POST          = 0xe05b, // POST entry point; jumped to from reset vector
    BIOS_ENTRY_02            = 0xe2c3, // INT 02 NMI handler
    BIOS_ENTRY_13_OFFICIAL   = 0xe3fe, // INT 13 disk services (jumps to entry_13)
    BIOS_ENTRY_19_OFFICIAL   = 0xe6f2, // INT 19 bootstrap (jumps to entry_19)
    BIOS_ENTRY_14            = 0xe739, // INT 14 serial services
    BIOS_ENTRY_16            = 0xe82e, // INT 16 keyboard services
    BIOS_ENTRY_09            = 0xe987, // IRQ1 keyboard
    BIOS_ENTRY_40            = 0xec59, // INT 40 floppy disk
    BIOS_ENTRY_0E            = 0xef57, // IRQ6 floppy
    BIOS_ENTRY_17            = 0xefd2, // INT 17 printer services
    BIOS_ENTRY_10_0X0F       = 0xf045, // INT 10h functions 0-F (stub: iretw)
    BIOS_ENTRY_10            = 0xf065, // INT 10 video services (stub: iretw)
    BIOS_ENTRY_12            = 0xf841, // INT 12 memory size
    BIOS_ENTRY_11            = 0xf84d, // INT 11 equipment list
    BIOS_ENTRY_15_OFFICIAL   = 0xf859, // INT 15 system services
    BIOS_ENTRY_1A_OFFICIAL   = 0xfe6e, // INT 1A time services; dispatches to PCI BIOS if AH=B1h
    BIOS_ENTRY_08            = 0xfea5, // IRQ0 timer tick
    BIOS_ENTRY_IRET_OFFICIAL = 0xff40, // Default interrupt vector (iret only)
    BIOS_ENTRY_INT_00        = 0xff41, // Dummy IRET for INT 00
    BIOS_ENTRY_INT_01        = 0xff42, // Dummy IRET for INT 01
    BIOS_ENTRY_INT_02        = 0xff43, // Dummy IRET for INT 02
    BIOS_ENTRY_INT_03        = 0xff44, // Dummy IRET for INT 03
    BIOS_ENTRY_INT_04        = 0xff45, // Dummy IRET for INT 04
    BIOS_ENTRY_INT_05        = 0xff46, // Dummy IRET for INT 05
    BIOS_ENTRY_INT_06        = 0xff47, // Dummy IRET for INT 06
    BIOS_ENTRY_INT_07        = 0xff48, // Dummy IRET for INT 07
    BIOS_ENTRY_INT_10        = 0xff49, // Dummy IRET for INT 10
    BIOS_ENTRY_INT_11        = 0xff4a, // Dummy IRET for INT 11
    BIOS_ENTRY_INT_12        = 0xff4b, // Dummy IRET for INT 12
    BIOS_ENTRY_INT_13        = 0xff4c, // Dummy IRET for INT 13
    BIOS_ENTRY_INT_14        = 0xff4d, // Dummy IRET for INT 14
    BIOS_ENTRY_INT_15        = 0xff4e, // Dummy IRET for INT 15
    BIOS_ENTRY_INT_16        = 0xff4f, // Dummy IRET for INT 16
    BIOS_ENTRY_INT_17        = 0xff50, // Dummy IRET for INT 17
    BIOS_ENTRY_INT_18        = 0xff51, // Dummy IRET for INT 18
    BIOS_ENTRY_INT_19        = 0xff52, // Dummy IRET for INT 19
    BIOS_ENTRY_INT_1A        = 0xff53, // Dummy IRET for INT 1A
    BIOS_RESET_VECTOR        = 0xfff0, // Power-up entry point; ljmpw to entry_post
};

// Fixed Address Data Structures
enum {
    BIOS_OLD_FDPT             = 0xe401,  // 16 bytes - Old Fixed Disk Parameter Table
    BIOS_CONFIG_TABLE         = 0xe6f5,  // 10 bytes - BIOS configuration table (INT 15h AH=C0h)
    BIOS_BAUD_TABLE           = 0xe729,  // 16 bytes - Baud rate generator table
    BIOS_DISKETTE_PARAM_TABLE = 0xefc7,  // 11 bytes - Floppy Disk Base Table
    BIOS_VIDEO_PARAMS         = 0xf0a4,  // 88 bytes - Video parameter tables (INT 1D pointer)
    BIOS_VIDEO_FUNC_STATIC    = 0xf0100, // 16 bytes - INT 10h AH=1Bh static functionality table
    BIOS_VGA_FONT8            = 0xfa6e,  // 1024 bytes - 8x8 VGA font for lower 128 characters
    BIOS_INIT_VECTORS = 0xfef3, // 13 bytes - Initial interrupt vector offsets loaded by POST
    BIOS_DATE         = 0xfff5, // 8 bytes - BIOS build date string "MM/DD/YY"
    BIOS_MODEL_ID     = 0xfffe, // 1 byte - Model ID (e.g. 0xFC for AT)
    BIOS_CHECKSUM     = 0xffff, // 1 byte - ROM checksum (sum of all bytes in ROM = 0)
};

//
// Basic Addresses.
//
enum {
    BIOS_ROM_ADDR  = 0xf0000, // Start of BIOS ROM in memory
    BASIC_ROM_ADDR = 0xd6000, // Start of Basic ROM in memory
    BASIC_ROM_LEN  = 0x8000,  // Size in bytes
};

//
// Bios Config Table.
//
struct Bios_Config_Table {
    uint16_t size;
    uint8_t model;
    uint8_t submodel;
    uint8_t biosrev;
    uint8_t feature1, feature2, feature3, feature4, feature5;
} __attribute__((packed));

//
// Fixed Disk Parameter Table.
//
struct Fixed_Disk_Param_Table {
    uint16_t cylinders;
    uint8_t heads;
    uint8_t a0h_signature;
    uint8_t phys_sectors;
    uint16_t precompensation;
    uint8_t reserved;
    uint8_t drive_control_byte;
    uint16_t phys_cylinders;
    uint8_t phys_heads;
    uint16_t landing_zone;
    uint8_t sectors;
    uint8_t checksum;
} __attribute__((packed));

//
// Floppy Disk Base Table.
//
struct Floppy_Disk_Base_Table {
    uint8_t specify1;
    uint8_t specify2;
    uint8_t shutoff_ticks;
    uint8_t bps_code;
    uint8_t sectors;
    uint8_t interblock_len;
    uint8_t data_len;
    uint8_t gap_len;
    uint8_t fill_byte;
    uint8_t settle_time;
    uint8_t startup_time;
} __attribute__((packed));

struct Floppy_Extended_Disk_Base_Table {
    struct Floppy_Disk_Base_Table dbt;

    // Extra fields
    uint8_t max_track;
    uint8_t data_rate;
    uint8_t drive_type;
} __attribute__((packed));

//
// Extended Bios Data Area (EBDA)
//
struct Extended_Bios_Data_Area {
    uint8_t size;
    uint8_t reserved1[0x21];
    struct Seg_Off far_call_pointer;
    uint8_t mouse_flag1;
    uint8_t mouse_flag2;
    uint8_t mouse_data[0x08];
    // 0x30
    uint8_t other1[0x0d];

    // 0x3d
    Fixed_Disk_Param_Table fdpt[2];

    // 0x5d
    uint8_t other2[0xC4];

    // 0x121 - Begin custom storage.
} __attribute__((packed));

//
// Error codes for int13 calls.
//
#define DISK_RET_SUCCESS       0x00
#define DISK_RET_EPARAM        0x01
#define DISK_RET_EADDRNOTFOUND 0x02
#define DISK_RET_EWRITEPROTECT 0x03
#define DISK_RET_ECHANGED      0x06
#define DISK_RET_EBOUNDARY     0x09
#define DISK_RET_EBADTRACK     0x0c
#define DISK_RET_ECONTROLLER   0x20
#define DISK_RET_ETIMEOUT      0x80
#define DISK_RET_ENOTLOCKED    0xb0
#define DISK_RET_ELOCKED       0xb1
#define DISK_RET_ENOTREMOVABLE 0xb2
#define DISK_RET_ETOOMANYLOCKS 0xb4
#define DISK_RET_EMEDIA        0xC0
#define DISK_RET_ENOTREADY     0xAA

//
// Drive selection by DL.
//
#define EXTSTART_FD 0x00 // Floppy
#define EXTSTART_HD 0x80 // Hard disk
#define EXTSTART_CD 0xE0 // CD-ROM

//
// BDA kbd_flag0 bits (low byte).
//
enum {
    KF0_RSHIFT   = 0x01,
    KF0_LSHIFT   = 0x02,
    KF0_CTRL     = 0x04,
    KF0_ALT      = 0x08,
    KF0_SCROLL   = 0x10,
    KF0_NUMLOCK  = 0x20,
    KF0_CAPSLOCK = 0x40,
};

#endif // TILTTI_I86_ARCH_H
