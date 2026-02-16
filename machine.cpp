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

// Static fields.
bool Machine::verbose                    = false;
uint64_t Machine::simulated_instructions = 0;

//
// Initialize the machine (SDL-free; main() owns display and input).
//
Machine::Machine(Memory &m, std::function<bool(bool)> pump_cb)
    : pump_callback_(std::move(pump_cb)),
      memory(m), cpu(*this),
      ivt(*(Interrupt_Vector_Table *)memory.get_ptr(0x0)),
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

    // Setup video, clear screen.
    set_video_mode(3);
    clear_video_memory();
}

//
// Deallocate the machine: disable tracing.
//
Machine::~Machine()
{
    redirect_trace(nullptr, "");
    enable_trace("");
}

//
// Run a batch of CPU steps (main() owns the loop, event pump, and display refresh).
//
void Machine::run_batch(unsigned n)
{
    trace_registers();
    for (unsigned i = 0; i < n; i++) {
        after_call   = false;
        after_return = false;
        cpu.step();
        simulated_instructions++;
    }
}

VideoRefreshParams Machine::get_video_refresh_params()
{
    VideoRefreshParams p{};

    unsigned page = bda.video_page;
    if (page > 7)
        page = 0;

    unsigned pos  = bda.cursor_pos[page];
    p.cursor_col  = pos & 0xff;
    p.cursor_row  = pos >> 8;
    p.cursor_type = bda.cursor_type;

    unsigned page_offset = bda.video_pagesize * page;

    p.text_buf = memory.get_ptr(0xb8000) + page_offset;

    p.need_refresh = video_dirty;
    video_dirty    = false;
    return p;
}

void Machine::set_kbd_modifiers(uint16_t flags)
{
    bda.kbd_flag0 &=
        ~(KF0_RSHIFT | KF0_LSHIFT | KF0_CTRL | KF0_ALT | KF0_SCROLL | KF0_NUMLOCK | KF0_CAPSLOCK);
    bda.kbd_flag0 |= flags & (KF0_RSHIFT | KF0_LSHIFT | KF0_CTRL | KF0_ALT | KF0_SCROLL |
                              KF0_NUMLOCK | KF0_CAPSLOCK);
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

void Machine::pump_events_blocking()
{
    // With delay.
    if (!pump_callback_(true)) {
        // Window closed.
        std::exit(0);
    }
}

void Machine::pump_events_nonblocking()
{
    // No delay.
    pump_callback_(false);
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
unsigned Machine::disk_io_chs(char op, unsigned disk_unit, unsigned cylinder, unsigned head,
                              unsigned sector, unsigned addr, unsigned nbytes)
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
                  << ", CHS = " << disk.num_cylinders << "/" << disk.num_heads << "/"
                  << disk.num_sectors << std::endl;
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
        F1_DMA3USED = 1 << 7, // DMA channel 3 used by hard disk BIOS
        F1_2NDPIC   = 1 << 6, // 2nd interrupt controller (8259) installed
        F1_RTC      = 1 << 5, // Real-Time Clock installed
        F1_INT154F  = 1 << 4, // INT 15/AH=4Fh called upon INT 09h
        F1_WAITEXT  = 1 << 3, // wait for external event (INT 15/AH=41h) supported
        F1_EBDA     = 1 << 2, // extended BIOS area allocated (usually at top of RAM)
        F1_MCA      = 1 << 1, // bus is Micro Channel instead of ISA
        F1_MCAISA   = 1 << 0, // system has dual bus (Micro Channel + ISA)

        F2_INT1609 = 1 << 6, // INT 16/AH=09h (keyboard functionality) supported
    };

    static const Bios_Config_Table config_table = {
        .size     = sizeof(Bios_Config_Table) - 2,
        .model    = 0xFC,
        .submodel = 0x00,
        .biosrev  = 0x01,
        .feature1 = // F1_2NDPIC |
        F1_RTC | F1_EBDA |
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
