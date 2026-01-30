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
#include <sstream>
#include <regex>

// Static fields.
bool Machine::verbose                    = false;
uint64_t Machine::simulated_instructions = 0;

//
// Initialize the machine.
//
Machine::Machine(Memory &m)
    : memory(m), cpu(*this, m)
{
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
again:
    // Show initial state.
    trace_registers();

    try {
        for (;;) {
            after_call = false;
            after_return = false;

            cpu.step();

            // Show changed registers.
            trace_registers();

            simulated_instructions++;
        }

    } catch (const Processor::Exception &ex) {
        // Unexpected situation in the machine.
        auto ip = cpu.get_ip();
        cpu.finish();

        auto const *message = ex.what();
        if (!message[0]) {
            // Empty message - legally halted by extracode e74.
            return;
        }
        std::cerr << "Error: " << message << " @" << std::oct << std::setfill('0') << std::setw(5)
                  << ip << std::endl;
        // trace_exception(message);

        if (cpu.intercept(message)) {
            goto again;
        }
        throw std::runtime_error(message);

    } catch (std::exception &ex) {
        // Something else.
        cpu.finish();
        // std::cerr << "Error: " << ex.what() << std::endl;
        throw std::runtime_error(ex.what());
    }
}

//
// Fetch instruction word.
//
Word Machine::mem_fetch(unsigned addr)
{
    if (addr >= 0xa0000) {
        throw Processor::Exception("Jump to Upper Memory Area");
    }

    Word val = memory.load(addr);
    trace_fetch(addr, val);
    return val;
}

//
// Write word to memory.
//
void Machine::mem_store(unsigned addr, Word val)
{
    memory.store(addr, val);
    trace_memory_write(addr, val);
}

//
// Read word from memory.
//
Word Machine::mem_load(unsigned addr)
{
    Word val = memory.load(addr);
    trace_memory_read(addr, val);
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
        throw std::runtime_error("Invalid disk unit " + std::to_string(disk_unit) + " in disk_mount()");
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
    //TODO: Attach image as disk or floppy.
    disk_mount(4, filename, true);

    // Start at this address.
    unsigned ip = 0x7c00;
    cpu.set_ip(ip);

    //TODO: load sector #0 from disk.
}
