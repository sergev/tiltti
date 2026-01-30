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

    // Path to disk images, semicolon separated.
    std::string disk_search_path;

    // List of all requested file names, for e57.
    std::vector<std::string> file_paths;

    // Enable system load list from the start.
    bool system_load_list_flag{};

    // Get name of a resident program by address.
    std::unordered_map<unsigned, std::string> resident_name;

    // Addresses of resident programs.
    std::multiset<unsigned> resident_addr;

    // Load the table of resident programs from this file.
    std::string map_filename;

    // Trace output.
    static std::ofstream trace_stream;

    // Trace modes.
    static bool debug_instructions; // trace machine instuctions
    static bool debug_syscalls;     // trace syscalls
    static bool debug_registers;    // trace CPU registers
    static bool debug_memory;       // trace memory read/write
    static bool debug_fetch;        // trace instruction fetch
    bool after_call{};              // right after JVM instruction
    bool after_return{};            // right after UJ(13) instruction

    // Static stuff.
    static bool verbose;                    // Verbose flag for tracing
    static uint64_t simulated_instructions; // Count of instructions

public:
    // 32K words of virtual memory.
    Memory &memory;

    // PC i86 processor.
    Processor cpu;

    // Constructor.
    explicit Machine(Memory &memory);

    // Destructor.
    ~Machine();

    // Load script into machine.
    void load_script(const std::string &filename);
    void load_script(std::istream &input);

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
    static bool trace_enabled()
    {
        return debug_instructions | debug_syscalls | debug_registers | debug_memory | debug_fetch;
    }
    void set_after_call() { after_call = true; };
    void set_after_return() { after_return = true; };

    // Emit trace to this stream.
    static std::ostream &get_trace_stream();

    // Memory access. Byte-addressed; word ops use little-endian (low at addr, high at addr+1).
    Byte mem_load_byte(unsigned addr);
    void mem_store_byte(unsigned addr, Byte val);
    Word mem_fetch(unsigned addr);
    Word mem_load(unsigned addr);
    void mem_store(unsigned addr, Word val);

    // Port I/O (stub: return 0 / no-op until implemented).
    Word port_in(int w, unsigned port);
    void port_out(int w, unsigned port, Word val);

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

    static void trace_fetch(unsigned addr, Word val)
    {
        if (debug_fetch)
            print_fetch(addr, val);
    }

    static void trace_memory_write(unsigned addr, Word val)
    {
        if (debug_memory)
            print_memory_access(addr, val, "Write");
    }

    static void trace_memory_read(unsigned addr, Word val)
    {
        if (debug_memory)
            print_memory_access(addr, val, "Read");
    }

    void trace_instruction(uint64_t opcode)
    {
        if (debug_instructions || (debug_syscalls && is_syscall(opcode)))
            cpu.print_instruction();
    }

    void trace_registers()
    {
        if (debug_registers)
            cpu.print_registers();
    }

    static void print_exception(const char *message);
    static void print_fetch(unsigned addr, Word val);
    static void print_memory_access(unsigned addr, Word val, const char *opname);
};

#endif // TILTTI_MACHINE_H
