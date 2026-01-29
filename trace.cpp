//
// Instruction and register tracing.
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
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "machine.h"

//
// Flag to enable tracing.
//
bool Machine::debug_instructions; // trace machine instuctions
bool Machine::debug_syscalls;     // trace INT syscalls
bool Machine::debug_registers;    // trace CPU registers
bool Machine::debug_memory;       // trace memory read/write
bool Machine::debug_fetch;        // trace instruction fetch

//
// Emit trace to this stream.
//
std::ofstream Machine::trace_stream;

//
// Enable trace with given modes.
//  i - trace instructions
//  e - trace INT syscalls
//  f - trace fetch
//  r - trace registers
//  m - trace memory read/write
//  x - trace exceptions
//
void Machine::enable_trace(const char *trace_mode)
{
    // Disable all trace options.
    debug_instructions = false;
    debug_syscalls     = false;
    debug_registers    = false;
    debug_memory       = false;
    debug_fetch        = false;

    if (trace_mode) {
        // Parse the mode string and enable all requested trace flags.
        for (unsigned i = 0; trace_mode[i]; i++) {
            char ch = trace_mode[i];
            switch (ch) {
            case 'e':
                debug_syscalls = true;
                break;
            case 'm':
                debug_memory = true;
                break;
            case 'i':
                debug_instructions = true;
                break;
            case 'r':
                debug_registers = true;
                break;
            case 'f':
                debug_fetch = true;
                break;
            default:
                throw std::runtime_error("Wrong trace option: " + std::string(1, ch));
            }
        }
    }
}

//
// Enable trace by bitmask,
// for example by VTM instruction with register 0.
//
void Machine::enable_trace(unsigned bitmask)
{
    debug_syscalls   = bitmask & 01;   // -d e
    debug_memory       = bitmask & 02;   // -d m
    debug_instructions = bitmask & 04;   // -d i
    debug_registers    = bitmask & 010;  // -d r
    debug_fetch        = bitmask & 020;  // -d f
}

//
// Redirect trace output to a given file.
//
void Machine::redirect_trace(const char *file_name, const char *default_mode)
{
    if (trace_stream.is_open()) {
        // Close previous file.
        trace_stream.close();
    }
    if (file_name && file_name[0]) {
        // Open new trace file.
        trace_stream.open(file_name);
        if (!trace_stream.is_open())
            throw std::runtime_error("Cannot write to " + std::string(file_name));
    }

    if (!trace_enabled()) {
        // Set default mode.
        enable_trace(default_mode);
    }
}

std::ostream &Machine::get_trace_stream()
{
    if (trace_stream.is_open()) {
        return trace_stream;
    }
    return std::cout;
}

void Machine::close_trace()
{
    if (trace_stream.is_open()) {
        // Close output.
        trace_stream.close();
    }

    // Disable trace options.
    enable_trace("");
}

//
// Trace output
//
void Machine::print_exception(const char *message)
{
    auto &out = Machine::get_trace_stream();
    out << "--- " << message << std::endl;
}

//
// Print instruction fetch.
//
void Machine::print_fetch(unsigned addr, Word val)
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    out << "      Fetch [" << std::hex << std::setfill('0') << std::setw(5) << addr << "] = ";
    out << val << std::endl;

    // Restore.
    out.flags(save_flags);
}

//
// Print memory read/write.
//
void Machine::print_memory_access(unsigned addr, Word val, const char *opname)
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    out << "      Memory " << opname << " [" << std::hex << std::setfill('0') << std::setw(5)
        << addr << "] = ";
    out << val << std::endl;

    // Restore.
    out.flags(save_flags);
}

//
// Print instruction address, opcode from RK and mnemonics.
//
void Processor::print_instruction()
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    out << std::hex << std::setfill('0') << std::setw(5) << core.PC << " : ";
    out << RK;
    //TODO: print_executive_address();
    out << std::endl;

    // Restore.
    out.flags(save_flags);
}

//
// Print changes in CPU registers.
//
void Processor::print_registers()
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    for (unsigned i = 0; i < 16; i++) {
        if (core.M[i] != prev.M[i]) {
            out << "      M" << std::hex << i << " = " << std::setfill('0') << std::setw(5)
                << core.M[i] << std::endl;
        }
    }

    // Update previous state.
    prev = core;

    // Restore output flags.
    out.flags(save_flags);
}
