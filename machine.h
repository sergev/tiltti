//
// Implement PC i86 machine.
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
#ifndef TILTTI_MACHINE_H
#define TILTTI_MACHINE_H

#include <array>
#include <chrono>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "disk.h"
#include "processor.h"

class Machine {
private:
    // Disks and floppies.
    std::array<std::unique_ptr<Disk>, NDISKS> disks;

    // Dump disk data for debug.
    bool dump_io_flag{}; // set to true to dump all disk reads
    unsigned dump_serial_num{};

    // Trace output.
    static std::ofstream trace_stream;

    // Trace modes.
    static bool debug_all;      // trace CPU registers, instructions, memory and everything else
    static bool debug_syscalls; // trace syscalls
    static bool debug_ports;    // trace i/o ports
    bool after_call{};          // right after JVM instruction
    bool after_return{};        // right after UJ(13) instruction

    // Static stuff.
    static bool verbose;                    // Verbose flag for tracing
    static uint64_t simulated_instructions; // Count of instructions

public:
    // 32K words of virtual memory.
    Memory &memory;

    // PC i86 processor.
    Processor cpu;

    Interrupt_Vector_Table &ivt;   // Interrupt vector table at 0x00000
    Bios_Data_Area &bda;           // Bios Data Area at 0x00400
    Extended_Bios_Data_Area &ebda; // Extended Bios Data Area at 0x9fc00
    Byte *bios;                    // Bios ROM at 0xf0000
    Floppy_Extended_Disk_Base_Table &diskette_param_table2;

    // Constructor.
    explicit Machine(Memory &memory);

    // Destructor.
    ~Machine();

    // Run simulation.
    void run();

    // Get instruction count.
    static uint64_t get_instr_count() { return simulated_instructions; }
    static void incr_simulated_instructions() { simulated_instructions++; }

    // Verbose flag for tracing.
    static void set_verbose(bool on) { verbose = on; }
    static bool get_verbose() { return verbose; }

    // Enable trace output to the given file,
    // or to std::cout when filename not present.
    static void enable_trace(const char *mode);
    static void enable_trace(unsigned bitmask);
    static void redirect_trace(const char *file_name, const char *default_mode);
    static void close_trace();
    static bool trace_enabled() { return debug_all | debug_syscalls | debug_ports; }
    void set_after_call() { after_call = true; };
    void set_after_return() { after_return = true; };

    // Emit trace to this stream.
    static std::ostream &get_trace_stream();

    // Memory access, byte-addressed.
    // Word ops use little-endian (low at addr, high at addr+1).
    Byte mem_fetch_byte(unsigned addr);
    Byte mem_load_byte(unsigned addr);
    void mem_store_byte(unsigned addr, Byte val);
    Word mem_load_word(unsigned addr);
    void mem_store_word(unsigned addr, Word val);

    // Port I/O.
    Byte port_in_byte(unsigned port);
    void port_out_byte(unsigned port, Byte val);
    Word port_in_word(unsigned port);
    void port_out_word(unsigned port, Word val);

    // Disk i/o.
    void disk_io(char op, unsigned disk_unit, unsigned sector, unsigned addr, unsigned nbytes);
    void disk_mount(unsigned disk_unit, const std::string &path, bool write_permit);

    // Boot from disk or floppy image.
    void boot_disk(const std::string &filename);

    //
    // Trace methods.
    //
    static void trace_exception(const char *message)
    {
        if (trace_enabled())
            print_exception(message);
    }

    void trace_instruction()
    {
        if (debug_all)
            cpu.print_instruction();
    }

    void trace_registers()
    {
        if (debug_all)
            cpu.print_registers();
    }

    static void print_exception(const char *message);
    static void print_byte_access(unsigned addr, Byte val, const char *opname);
    static void print_word_access(unsigned addr, Word val, const char *opname);

private:
    void floppy_setup();
};

#endif // TILTTI_MACHINE_H
