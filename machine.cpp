//
// PC i86 computer.
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
#include "machine.h"

#include <SDL.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "sdl_scancode_map.h"
#include "video_adapter.h"

// Static fields.
bool Machine::verbose                    = false;
uint64_t Machine::simulated_instructions = 0;

//
// Initialize the machine.
// When use_sdl_display is true, create SDL window and use SDL for keyboard; otherwise termios.
//
Machine::Machine(Memory &m, bool use_sdl_display)
    : use_sdl_display_(use_sdl_display),
      memory(m), cpu(*this), ivt(*(Interrupt_Vector_Table *)memory.get_ptr(0x0)),
      bda(*(Bios_Data_Area *)memory.get_ptr(0x400)),
      ebda(*(Extended_Bios_Data_Area *)memory.get_ptr(0x9fc00)), bios(memory.get_ptr(0xf0000)),
      diskette_param_table2(*(Floppy_Extended_Disk_Base_Table *)bios)
{
    // Set pointer to EBDA.
    bda.ebda_seg = 0x9fc00 >> 4;
    ebda.size    = (sizeof(ebda) + 1023) / 1024; // round up

    setup_bios_config_table();

    // Memory size in kilobytes.
    bda.mem_size_kb = 640;

    // Set display combination code: VGA analog color.
    bda.dcc_index = 0x08;

    // Video mode 80×25 color.
    bda.equipment_list_flags = 0x0021;

    // Floppy disk installed.
    setup_floppy();

    if (use_sdl_display) {
        video_adapter_ = std::make_unique<Video_Adapter>(true, memory.get_ptr(0xb8000));
        if (!video_adapter_->has_window()) {
            video_adapter_.reset();
            use_sdl_display_ = false;
            setup_keyboard();
        }
    }
    if (!use_sdl_display_)
        setup_keyboard();

    // Setup video.
    bda.video_mode = 3; // Text mode: 80 columns, 25 rows, 16 colors
    bda.video_rows = 25;
    bda.video_cols = 80;
    bda.video_pagesize = 80 * 25 * 2;  // 4000 bytes per page
    bda.video_ctl  = 0x60;
}

//
// Deallocate the machine: disable tracing.
//
Machine::~Machine()
{
    redirect_trace(nullptr, "");
    enable_trace("");
    close_keyboard();
}

//
// Run the machine until completion.
// When SDL display is active: poll events, run a batch of steps, refresh video, ~60 fps.
//
void Machine::run()
{
    trace_registers();
    constexpr unsigned steps_per_frame = 5000;
    constexpr unsigned frame_ms        = 16;

    if (use_sdl_display_ && video_adapter_) {
        while (pump_sdl_events()) {
            for (unsigned i = 0; i < steps_per_frame && !sdl_quit_requested_; i++) {
                after_call   = false;
                after_return = false;
                cpu.step();
                simulated_instructions++;
            }
            refresh_video();
            if (sdl_quit_requested_)
                break;
            SDL_Delay(frame_ms);
        }
        return;
    }

    for (;;) {
        after_call   = false;
        after_return = false;

        cpu.step();

        simulated_instructions++;
    }
}

void Machine::push_keystroke(uint16_t ax)
{
    keyboard_queue_.push(ax);
}

bool Machine::has_keystroke() const
{
    return !keyboard_queue_.empty();
}

uint16_t Machine::peek_keystroke() const
{
    return keyboard_queue_.front();
}

uint16_t Machine::pop_keystroke()
{
    uint16_t ax = keyboard_queue_.front();
    keyboard_queue_.pop();
    return ax;
}

void Machine::refresh_video()
{
    if (!video_adapter_ || !video_adapter_->has_window())
        return;
    unsigned page = bda.video_page;
    if (page > 7)
        page = 0;
    unsigned pos = bda.cursor_pos[page];
    unsigned col = pos & 0xff;
    unsigned row = pos >> 8;
    unsigned page_offset = bda.video_pagesize * page;
    if (page_offset == 0)
        page_offset = bda.video_cols * (bda.video_rows + 1) * 2;
    const uint8_t *text_buf = memory.get_ptr(0xb8000) + page_offset;
    video_adapter_->refresh_from_memory(text_buf, col, row, bda.cursor_type);
}

bool Machine::pump_sdl_events()
{
    if (!use_sdl_display_)
        return true;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            sdl_quit_requested_ = true;
            return false;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            uint32_t sdl_sc = event.key.keysym.scancode;
            bool down       = (event.type == SDL_KEYDOWN);

            // Update modifier flags in BDA (low byte of kbd_flag0).
            uint16_t mod = SDL_GetModState();
            uint16_t &f0 = bda.kbd_flag0;
            f0 &= static_cast<uint16_t>(~(KF0_RSHIFT | KF0_LSHIFT | KF0_CTRL | KF0_ALT));
            if (mod & KMOD_RSHIFT)
                f0 |= KF0_RSHIFT;
            if (mod & KMOD_LSHIFT)
                f0 |= KF0_LSHIFT;
            if (mod & KMOD_CTRL)
                f0 |= KF0_CTRL;
            if (mod & KMOD_ALT)
                f0 |= KF0_ALT;
            const Uint8 *state = SDL_GetKeyboardState(nullptr);
            if (state[SDL_SCANCODE_SCROLLLOCK])
                f0 |= KF0_SCROLL;
            if (state[SDL_SCANCODE_NUMLOCKCLEAR])
                f0 |= KF0_NUMLOCK;
            if (state[SDL_SCANCODE_CAPSLOCK])
                f0 |= KF0_CAPSLOCK;

            if (down) {
                uint8_t bios_sc = sdl_to_bios_scancode(sdl_sc);
                uint8_t bios_ext = sdl_to_bios_scancode_extended(sdl_sc);
                uint8_t ascii    = 0;
                if (mod & KMOD_SHIFT)
                    ascii = sdl_scancode_to_ascii_shifted(sdl_sc);
                if (ascii == 0)
                    ascii = sdl_scancode_to_ascii_unshifted(sdl_sc);
                if (bios_ext) {
                    // Extended key: BIOS expects 0xE0 in low byte, scan in high for some; or 0x00, 0xE0xx.
                    // INT 16h returns AX = (scancode << 8) | ASCII. Extended often: AL=0, AH=ext_scan.
                    push_keystroke((static_cast<uint16_t>(bios_ext) << 8) | 0x00);
                } else if (bios_sc) {
                    push_keystroke((static_cast<uint16_t>(bios_sc) << 8) | ascii);
                }
            }
        }
    }
    return true;
}

static bool basic_area(unsigned addr)
{
    return addr >= BASIC_ROM_ADDR && addr < BASIC_ROM_ADDR + BASIC_ROM_LEN;
}

//
// Fetch one byte of instruction from memory.
// No tracing.
//
Byte Machine::mem_fetch_byte(unsigned addr)
{
    if (mode_640k && addr >= 0xa0000 && !basic_area(addr)) {
        throw std::runtime_error("Jump to Upper Memory Area");
    }
    Byte val = memory.load8(addr);
    return val;
}

//
// Store one byte to memory (with optional trace).
//
void Machine::mem_store_byte(unsigned addr, Byte val)
{
    if (addr >= MEMORY_NBYTES) {
        throw std::runtime_error("Store out of range");
    }
    memory.store8(addr, val);
    if (debug_all) {
        print_byte_access(addr, val, "Memory Write");
    }
}

//
// Load one byte from memory (with optional trace).
//
Byte Machine::mem_load_byte(unsigned addr)
{
    if (addr >= MEMORY_NBYTES) {
        throw std::runtime_error("Load out of range");
    }
    Byte val = memory.load8(addr);
    if (debug_all) {
        print_byte_access(addr, val, "Memory Read");
    }
    return val;
}

//
// Write 16-bit word to memory (little-endian).
//
void Machine::mem_store_word(unsigned addr, Word val)
{
    if (addr >= MEMORY_NBYTES) {
        throw std::runtime_error("Store out of range");
    }
    if (addr + 1 >= MEMORY_NBYTES) {
        // Wrap around.
        memory.store8(addr, val);
        memory.store8(0, val >> 8);
    } else {
        memory.store16(addr, val);
    }
    if (debug_all) {
        print_word_access(addr, val, "Memory Write");
    }
}

//
// Read 16-bit word from memory (little-endian).
//
Word Machine::mem_load_word(unsigned addr)
{
    if (addr >= MEMORY_NBYTES) {
        throw std::runtime_error("Load out of range");
    }
    Word val;
    if (addr + 1 >= MEMORY_NBYTES) {
        // Wrap around.
        val = memory.load8(addr);
        val |= memory.load8(0) << 8;
    } else {
        val = memory.load16(addr);
    }
    if (debug_all) {
        print_word_access(addr, val, "Memory Read");
    }
    return val;
}

//
// Send one byte to port.
//
void Machine::port_out_byte(unsigned port, Byte val)
{
    // TODO: implement port_out
    if (debug_all) {
        print_byte_access(port, val, "Port Out");
    }
}

//
// Receive one byte from port.
//
Byte Machine::port_in_byte(unsigned port)
{
    // Unimplemented ports return 0xFF (floating bus / typical PC behavior).
    const Byte val = 0xff;
    if (debug_all) {
        print_byte_access(port, val, "Port In");
    }
    return val;
}

//
// Send 16-bit word to port.
//
void Machine::port_out_word(unsigned port, Word val)
{
    // TODO: implement port_out
    if (debug_all) {
        print_word_access(port, val, "Outport");
    }
}

//
// Receive 16-bit word from port.
//
Word Machine::port_in_word(unsigned port)
{
    // Unimplemented ports return 0xFFFF (floating bus / typical PC behavior).
    const Word val = 0xffff;
    if (debug_all) {
        print_word_access(port, val, "Inport");
    }
    return val;
}

//
// Disk read/write.
// Return disk status.
//
unsigned Machine::disk_io_chs(char op, unsigned disk_unit, unsigned cylinder, unsigned head, unsigned sector, unsigned addr, unsigned nbytes)
{
    if (disk_unit >= NDISKS || sector < 1) {
        // Invalid disk unit
        return DISK_RET_EPARAM;
    }
    if (!disks[disk_unit]) {
        // Disk must be previously configured using disk_mount().
        return DISK_RET_EPARAM;
    }
    auto &disk = *disks[disk_unit].get();

    if (cylinder >= disk.num_cylinders || head >= disk.num_heads || sector > disk.num_sectors) {
        // Too large cylinder or head or sector.
        return DISK_RET_EPARAM;
    }

    // Translate CHS to logical block address.
    unsigned lba = (((cylinder * disk.num_heads) + head) * disk.num_sectors) + sector - 1;

    if (op == 'r') {
        disk.disk_to_memory(lba, addr, nbytes);

        // Debug: dump the data.
        if (dump_io_flag) {
            memory.dump(++dump_serial_num, disk_unit, lba, addr, nbytes);
        }
    } else {
        disk.memory_to_disk(lba, addr, nbytes);
    }
    return DISK_RET_SUCCESS;
}

//
// Open binary image and assign it to the disk unit.
//
void Machine::disk_mount(unsigned disk_unit, const std::string &path, bool write_permit)
{
    if (disk_unit >= NDISKS) {
        throw std::runtime_error("Invalid disk unit " + std::to_string(disk_unit) +
                                 " in disk_mount()");
    }
    if (disks[disk_unit]) {
        throw std::runtime_error("Disk unit " + std::to_string(disk_unit) + " is already mounted");
    }

    // Open binary image as disk.
    disks[disk_unit] = std::make_unique<Disk>(path, memory, write_permit);

    if (trace_enabled()) {
        auto &disk = *disks[disk_unit].get();
        std::cout << "Mount image '" << path << "' as disk " << disk_unit
                  << ", CHS = " << disk.num_cylinders
                  << "/" << disk.num_heads
                  << "/" << disk.num_sectors
                  << std::endl;
    }
}

//
// Boot from floppy image.
//
void Machine::boot_disk(const std::string &filename)
{
    // Enable Upper Memory Area.
    mode_640k = true;

    // Attach image as floppy A.
    disk_mount(FLOPPY_A, filename, true);

    // TODO: Alternatively, attach image as disk C.

    // Start at address 07c0:0000.
    unsigned addr = 0x7c00;
    cpu.set_cs(addr >> 4);
    cpu.set_ip(0);

    // Load boot sector from disk.
    if (disk_io_chs('r', FLOPPY_A, 0, 0, 1, addr, SECTOR_NBYTES) != DISK_RET_SUCCESS) {
        throw std::runtime_error("Cannot read boot sector");
    }
}

//
// Start Basic from ROM.
//
void Machine::start_basic()
{
    // Enable Upper Memory Area.
    mode_640k = true;

    // Start at address 6d00:0000.
    cpu.set_cs(BASIC_ROM_ADDR >> 4);
    cpu.set_ip(0);
}

//
// Initialize floppy BIOS.
//
void Machine::setup_floppy()
{
    // Parameters for 1.44M floppy type.
    static const Floppy_Extended_Disk_Base_Table diskette_params = {
        .dbt = {
            .specify1       = 0xAF, // step rate 12ms, head unload 240ms
            .specify2       = 0x02, // head load time 4ms, DMA used
            .shutoff_ticks  = 37,   // ~2 seconds
            .bps_code       = 0x02, // 512 byte sectors
            .sectors        = 18,   // 1.44M media
            .interblock_len = 0x1B,
            .data_len       = 0xff, // Not used - because size code is 0x02
            .gap_len        = 0x6c,
            .fill_byte      = 0xf6,
            .settle_time    = 0x0F, // 15ms
            .startup_time   = 8,    // 1 second
        },
        .max_track  = 79, // maximum track
        .data_rate  = 0,  // data transfer rate
        .drive_type = 4,  // drive type in CMOS
    };

    // Initialize the floppy param table.
    memcpy(&diskette_param_table2, &diskette_params, sizeof(diskette_param_table2));
    memcpy(&bios[BIOS_DISKETTE_PARAM_TABLE], &diskette_params.dbt, sizeof(diskette_params.dbt));

    // Vector 0x1E points to the floppy param table.
    ivt.ivec[0x1e] = { .offset = BIOS_DISKETTE_PARAM_TABLE, .seg = 0xf000 };
}

//
// Initialize BIOS Config Table.
//
void Machine::setup_bios_config_table()
{
    enum {
        F1_DMA3USED = 1<<7,  // DMA channel 3 used by hard disk BIOS
        F1_2NDPIC   = 1<<6,  // 2nd interrupt controller (8259) installed
        F1_RTC      = 1<<5,  // Real-Time Clock installed
        F1_INT154F  = 1<<4,  // INT 15/AH=4Fh called upon INT 09h
        F1_WAITEXT  = 1<<3,  // wait for external event (INT 15/AH=41h) supported
        F1_EBDA     = 1<<2,  // extended BIOS area allocated (usually at top of RAM)
        F1_MCA      = 1<<1,  // bus is Micro Channel instead of ISA
        F1_MCAISA   = 1<<0,  // system has dual bus (Micro Channel + ISA)

        F2_INT1609  = 1<<6,  // INT 16/AH=09h (keyboard functionality) supported
    };

    static const Bios_Config_Table config_table = {
        .size     = sizeof(Bios_Config_Table) - 2,
        .model    = 0xFC,
        .submodel = 0x00,
        .biosrev  = 0x01,
        .feature1 = // F1_2NDPIC |
                    F1_RTC |
                    F1_EBDA |
                    // F1_INT154F |
                    0,
        .feature2 = // F2_INT1609 // INT 16/AH=09h (keyboard functionality) supported
                    0,
        .feature3 = 0,
        .feature4 = 0,
        .feature5 = 0,
    };
    memcpy(&bios[BIOS_CONFIG_TABLE], &config_table, sizeof(config_table));
}
