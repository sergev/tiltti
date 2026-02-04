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
// Initialize the machine.
//
Machine::Machine(Memory &m) : memory(m), cpu(*this),
    ivt(*(Interrupt_Vector_Table*) memory.get_ptr(0x0)),
    bda(*(Bios_Data_Area*) memory.get_ptr(0x400)),
    ebda(*(Extended_Bios_Data_Area*) memory.get_ptr(0x9fc00)),
    bios(memory.get_ptr(0xf0000)),
    diskette_param_table2(*(Floppy_Extended_Disk_Base_Table*) bios)
{
    // Set pointer to EBDA.
    bda.ebda_seg = 0x9fc00 >> 4;
    ebda.size    = (sizeof(ebda) + 1023) / 1024; // round up

    floppy_setup();
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
// Run the machine until completion.
//
void Machine::run()
{
    trace_registers();
    for (;;) {
        after_call   = false;
        after_return = false;

        cpu.step();

        simulated_instructions++;
    }
}

//
// Fetch one byte of instruction from memory.
// No tracing.
//
Byte Machine::mem_fetch_byte(unsigned addr)
{
    if (addr >= 0xa0000) {
        throw std::runtime_error("Jump to Upper Memory Area");
    }
    Byte val = memory.load(addr);
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
    memory.store(addr, val);
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
    Byte val = memory.load(addr);
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
    if (addr + 1 >= MEMORY_NBYTES) {
        throw std::runtime_error("Store out of range");
    }
    memory.store(addr, val & 0xff);
    memory.store(addr + 1, val >> 8);
    if (debug_all) {
        print_word_access(addr, val, "Memory Write");
    }
}

//
// Read 16-bit word from memory (little-endian).
//
Word Machine::mem_load_word(unsigned addr)
{
    if (addr + 1 >= MEMORY_NBYTES) {
        throw std::runtime_error("Load out of range");
    }
    Word val = memory.load(addr) | (memory.load(addr + 1) << 8);
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
    //TODO: implement port_out
    if (debug_all) {
        print_byte_access(port, val, "Port Out");
    }
}

//
// Receive one byte from port.
//
Byte Machine::port_in_byte(unsigned port)
{
    //TODO: implement port_in
    Word val = 0;
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
    //TODO: implement port_out
    if (debug_all) {
        print_word_access(port, val, "Outport");
    }
}

//
// Receive 16-bit word from port.
//
Word Machine::port_in_word(unsigned port)
{
    //TODO: implement port_in
    Word val = 0;
    if (debug_all) {
        print_word_access(port, val, "Inport");
    }
    return val;
}

//
// Disk read/write.
//
void Machine::disk_io(char op, unsigned disk_unit, unsigned sector, unsigned addr, unsigned nbytes)
{
    Disk *disk;

    if (disk_unit >= NDISKS) {
        throw std::runtime_error("Invalid disk unit " + std::to_string(disk_unit));
    }
    if (!disks[disk_unit]) {
        // Disk must be previously configured using disk_mount().
        throw std::runtime_error("Disk unit " + std::to_string(disk_unit) + " is not mounted");
    }
    disk = disks[disk_unit].get();

    if (op == 'r') {
        disk->disk_to_memory(sector, addr, nbytes);

        // Debug: dump the data.
        if (dump_io_flag) {
            memory.dump(++dump_serial_num, disk_unit, sector, addr, nbytes);
        }
    } else {
        disk->memory_to_disk(sector, addr, nbytes);
    }
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
        std::cout << "Mount image '" << path << "' as disk " << disk_unit << std::endl;
    }
}

//
// Load binary program (overlay).
//
void Machine::boot_disk(const std::string &filename)
{
    // Attach image as floppy A.
    disk_mount(FLOPPY_A, filename, true);

    // TODO: Alternatively, attach image as disk C.

    // Start at address 07c0:0000.
    unsigned addr = 0x7c00;
    cpu.set_cs(addr >> 4);
    cpu.set_ip(0);

    // Load boot sector from disk.
    disk_io('r', FLOPPY_A, 0, addr, SECTOR_NBYTES);
}

//
// Initialize floppy BIOS.
//
void Machine::floppy_setup()
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
