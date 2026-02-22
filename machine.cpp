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

#include <sys/time.h>
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
uint64_t Machine::simulated_instructions = 0;

//
// Initialize the machine (SDL-free; main() owns display and input).
//
Machine::Machine(Memory &m)
    : memory(m), cpu(*this), ivt(*reinterpret_cast<Interrupt_Vector_Table *>(memory.get_ptr(0x0))),
      bda(*reinterpret_cast<Bios_Data_Area *>(memory.get_ptr(0x400))),
      ebda(*reinterpret_cast<Extended_Bios_Data_Area *>(memory.get_ptr(0x9fc00))),
      bios(memory.get_ptr(0xf0000)),
      diskette_param_table2(*reinterpret_cast<Floppy_Extended_Disk_Base_Table *>(bios))
{
    // Set pointer to EBDA.
    bda.ebda_seg = 0x9fc00 >> 4;
    ebda.size    = (sizeof(ebda) + 1023) / 1024; // round up

    setup_bios_config_table();

    // Dummy IRET handlers (one byte each: 0xCF)
    for (unsigned o = BIOS_ENTRY_IRET_OFFICIAL; o < BIOS_ENTRY_05; o++)
        bios[o] = 0xCF;

    // Initialize IVT: vectors 00h-07h and 10h-1Ah to named dummies, rest to generic dummy
    const Seg_Off null_vec = { .offset = 0, .seg = 0 };
    const uint16_t dummy_00_07[] = { BIOS_ENTRY_INT_00, BIOS_ENTRY_INT_01, BIOS_ENTRY_INT_02,
                                     BIOS_ENTRY_INT_03, BIOS_ENTRY_INT_04, BIOS_ENTRY_INT_05,
                                     BIOS_ENTRY_INT_06, BIOS_ENTRY_INT_07 };
    const uint16_t dummy_10_1A[] = { BIOS_ENTRY_INT_10, BIOS_ENTRY_INT_11, BIOS_ENTRY_INT_12,
                                     BIOS_ENTRY_INT_13, BIOS_ENTRY_INT_14, BIOS_ENTRY_INT_15,
                                     BIOS_ENTRY_INT_16, BIOS_ENTRY_INT_17, BIOS_ENTRY_INT_18,
                                     BIOS_ENTRY_INT_19, BIOS_ENTRY_INT_1A };
    const Seg_Off iret_vec = { .offset = BIOS_ENTRY_IRET_OFFICIAL, .seg = 0xf000 };
    for (unsigned i = 0; i < 256; i++)
        ivt.ivec[i] = iret_vec;
    for (unsigned i = 0; i < 8; i++)
        ivt.ivec[i] = { .offset = dummy_00_07[i], .seg = 0xf000 };
    for (unsigned i = 0; i < 11; i++)
        ivt.ivec[0x10 + i] = { .offset = dummy_10_1A[i], .seg = 0xf000 };
    for (unsigned i = 0x60; i <= 0x66; i++)
        ivt.ivec[i] = null_vec;
    ivt.ivec[0x79] = null_vec;

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

    // INT 10h AH=1Bh: static functionality table at BIOS_VIDEO_FUNC_STATIC.
    const unsigned static_addr = BIOS_VIDEO_FUNC_STATIC;
    memory.store32(static_addr + 0, 0xCF); // modes: 0,1,2,3,6,7 supported
    memory.store8(static_addr + 4, 0);
    memory.store8(static_addr + 5, 0);
    memory.store8(static_addr + 6, 0);
    memory.store8(static_addr + 7, 0x07);     // scanlines: 200, 350, 400
    memory.store8(static_addr + 8, 0x02);     // cblocks
    memory.store8(static_addr + 9, 0x08);     // active_cblocks
    memory.store16(static_addr + 10, 0x0ce7); // misc_flags
    // bytes 12-15 reserved, leave zero
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
// Set font buffer for INT 10h AH=11h (character generator). Caller owns the storage.
//
void Machine::set_font_buffer(uint8_t *ptr, size_t size)
{
    font_buf_      = ptr;
    font_buf_size_ = size;
}

//
// Run a batch of CPU steps.
//
void Machine::run_batch(unsigned n)
{
    trace_registers();
    for (unsigned i = 0; i < n; i++) {
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
    // std::cout << "--- keystroke 0x" << std::hex << ax << std::dec << '\n';
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

static bool basic_area(unsigned addr)
{
    if (addr >= BIOS_ENTRY_IRET_OFFICIAL + 0xf0000 && addr < BIOS_ENTRY_05 + 0xf0000) {
        // Allow dummy IRET handlers (0xff40..0xff53).
        return true;
    }
    return addr >= BASIC_ROM_ADDR && addr < BASIC_ROM_ADDR + BASIC_ROM_LEN;
}

//
// Fetch one byte of instruction from memory.
// No tracing.
//
Byte Machine::mem_fetch_byte(unsigned addr)
{
    if (mode_640k && addr >= 0xa0000 && !basic_area(addr)) {
        throw std::runtime_error("Jump to Upper Memory Area " + to_hex(addr));
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
        print_byte_access(addr, val, "Byte Write");
    }
    if (addr >= 0xb0000 && addr <= 0xbffff) {
        video_dirty = true;
        //print_byte_access(addr, val, "Byte Write");
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
        print_byte_access(addr, val, "Byte Read");
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
        print_word_access(addr, val, "Word Write");
    }
    if (addr < 0x400 && (addr & 3) == 2 && trace_enabled()) {
        print_handler(addr);
    }
    if (addr >= 0xb0000 && addr <= 0xbffff) {
        video_dirty = true;
        //print_word_access(addr, val, "Word Write");
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
        print_word_access(addr, val, "Word Read");
    }
    return val;
}

//
// Send one byte to port.
//
void Machine::port_out_byte(unsigned port, Byte val)
{
    // TODO: implement port_out
    if (debug_all || debug_ports) {
        print_byte_access(port, val, "Byte Outport");
    }
}

//
// Receive one byte from port.
//
Byte Machine::port_in_byte(unsigned port)
{
    // Unimplemented ports return 0xFF (floating bus / typical PC behavior).
    Byte val = 0xff;

    switch (port) {
    case 0x61:
        // Bit 4 flips state (0/1) with each DRAM refresh cycle, approximately every 15 μs.
        // Commonly used in old software for precise short delays by polling for changes.
        val = simulated_instructions & 0x10;
        break;
    default:
        break;
    }

    if (debug_all || debug_ports) {
        print_byte_access(port, val, "Byte Inport");
    }
    return val;
}

//
// Send 16-bit word to port.
//
void Machine::port_out_word(unsigned port, Word val)
{
    // TODO: implement port_out
    if (debug_all || debug_ports) {
        print_word_access(port, val, "Word Outport");
    }
}

//
// Receive 16-bit word from port.
//
Word Machine::port_in_word(unsigned port)
{
    // Unimplemented ports return 0xFFFF (floating bus / typical PC behavior).
    const Word val = 0xffff;
    if (debug_all || debug_ports) {
        print_word_access(port, val, "Word Inport");
    }
    return val;
}

//
// Map BIOS drive number (DL) to internal disk unit index.
// DL 0,1 = floppy A,B; DL 0x80,0x81 = hard disk C,D.
// Returns true and sets disk_unit to 0..3 if valid; false if invalid.
//
bool Machine::dl_to_disk_unit(unsigned dl, unsigned &disk_unit)
{
    if (dl < EXTSTART_HD) {
        if (dl > 1)
            return false;
        disk_unit = dl;
        return true;
    }
    if (dl >= EXTSTART_HD + 2) // only 0x80 and 0x81
        return false;
    disk_unit = DISK_C + (dl - EXTSTART_HD);
    return true;
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
        // Floppy present but no media -> not ready; other units invalid.
        if (disk_unit < EXTSTART_HD) {
            return DISK_RET_ENOTREADY;
        }
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
        if (!disk.is_writable()) {
            return DISK_RET_EWRITEPROTECT;
        }
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
        auto const &disk = *disks[disk_unit].get();
        std::cout << "Mount image '" << path << "' as disk " << disk_unit
                  << ", CHS = " << disk.num_cylinders << "/" << disk.num_heads << "/"
                  << disk.num_sectors
                  << (disk.is_writable() ? "" : " (write-protected)") << std::endl;
    }
}

//
// Boot from floppy or hard disk image. Mount only non-empty paths.
// Default boot order: C then A then B. Override with boot_drive "a","b","c","d".
//
void Machine::boot_disk(const std::string &filename, const std::string &filename_b,
                        const std::string &filename_c, const std::string &filename_d,
                        const std::string &boot_drive)
{
    // Enable Upper Memory Area.
    mode_640k = true;

    if (!filename.empty()) {
        disk_mount(FLOPPY_A, filename, true);
    }
    if (!filename_b.empty()) {
        disk_mount(FLOPPY_B, filename_b, true);
    }
    if (!filename_c.empty()) {
        disk_mount(DISK_C, filename_c, true);
    }
    if (!filename_d.empty()) {
        disk_mount(DISK_D, filename_d, true);
    }

    // Set floppy count in equipment word: bits 7-6 = (number of floppies) - 1.
    const unsigned nfloppy = disks[FLOPPY_B] ? 2 : (disks[FLOPPY_A] ? 1 : 0);
    bda.equipment_list_flags = (bda.equipment_list_flags & ~0x41) | 0x01 |
                              (nfloppy ? ((nfloppy - 1) << 6) : 0);

    // Set hard disk count for INT 13h AH=08h and similar.
    bda.hdcount = (disks[DISK_D] ? 2 : 0) + (disks[DISK_C] ? 1 : 0);

    // Choose boot unit: override or default order C then A then B.
    unsigned boot_unit;
    if (!boot_drive.empty()) {
        switch (boot_drive[0]) {
        case 'a': boot_unit = FLOPPY_A; break;
        case 'b': boot_unit = FLOPPY_B; break;
        case 'c': boot_unit = DISK_C; break;
        case 'd': boot_unit = DISK_D; break;
        default: boot_unit = NDISKS; break;
        }
        if (boot_unit >= NDISKS || !disks[boot_unit]) {
            throw std::runtime_error("Boot drive " + boot_drive +
                                     " not present or not mounted");
        }
    } else {
        if (disks[DISK_C])
            boot_unit = DISK_C;
        else if (disks[FLOPPY_A])
            boot_unit = FLOPPY_A;
        else if (disks[FLOPPY_B])
            boot_unit = FLOPPY_B;
        else
            throw std::runtime_error("No bootable disk present");
    }

    // Start at address 0000:7c00.
    unsigned addr = 0x7c00;
    cpu.set_cs(0);
    cpu.set_ip(addr);

    // Load boot sector from chosen drive.
    if (disk_io_chs('r', boot_unit, 0, 0, 1, addr, SECTOR_NBYTES) != DISK_RET_SUCCESS) {
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
        .feature1 = F1_2NDPIC | F1_RTC | F1_EBDA | F1_INT154F,
        .feature2 = F2_INT1609, // INT 16/AH=09h (keyboard functionality) supported
        .feature3 = 0,
        .feature4 = 0,
        .feature5 = 0,
    };
    memcpy(&bios[BIOS_CONFIG_TABLE], &config_table, sizeof(config_table));
}

//
// Take Int 8 as if a timer interrupt is requested by hardware.
//
void Machine::invoke_vector(unsigned vector)
{
    // Check interrupt flag.
    bool interrupts_enabled = cpu.get_flags() >> 9 & 1;
    if (!interrupts_enabled) {
        return;
    }

    // Check interrupt handler.
    Word offset   = memory.load16(vector * 4);
    Word seg      = memory.load16(vector * 4 + 2);
    unsigned addr = pc86_linear_addr(seg, offset);
    if (addr < 0x500 || addr >= 0xa0000) {
        // Handler must be located in user memory.
        return;
    }

    // Debug.
    // auto &out = Machine::get_trace_stream();
    // out << "------- " << "Vector " << vector << std::endl;

    cpu.call_int(vector);
}

void Machine::unsupported(uint8_t op, const std::string &required_cpu)
{
    if (mode_640k) {
        throw std::runtime_error("Unsupported opcode " + to_hex(op) + ": need " + required_cpu +
                                 " processor");
    }
}

void Machine::update_timer_counter()
{
    struct timeval tv;
    gettimeofday(&tv, 0);

    const time_t now      = tv.tv_sec;
    const struct tm *info = localtime(&now);

    // Get date and time.
    local_year  = info->tm_year + 1900;
    local_month = info->tm_mon + 1;
    local_mday  = info->tm_mday;
    local_hour  = info->tm_hour;
    local_min   = info->tm_min;
    local_sec   = info->tm_sec;
    local_isdst = info->tm_isdst;

    // Get milliseconds since midnight.
    unsigned sec      = (((info->tm_hour * 60) + info->tm_min) * 60) + info->tm_sec;
    unsigned msec     = (sec * 1000) + (tv.tv_usec / 1000);
    bda.timer_counter = msec / 55;

    // Debug.
    // auto &out = Machine::get_trace_stream();
    // out << "------- " << "Timer counter " << bda.timer_counter << std::endl;
}
