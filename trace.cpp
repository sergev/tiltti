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
#include <capstone/capstone.h>

#include "machine.h"

//
// Flag to enable tracing.
//
bool Machine::debug_all;      // trace CPU registers, instructions, memory and everything else
bool Machine::debug_syscalls; // trace INT syscalls
bool Machine::debug_ports;    // trace i/o ports

//
// Emit trace to this stream.
//
std::ofstream Machine::trace_stream;

// Capstone handle.
static csh disasm;

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
    debug_all      = false;
    debug_syscalls = false;
    debug_ports    = false;

    if (trace_mode) {
        // Parse the mode string and enable all requested trace flags.
        for (unsigned i = 0; trace_mode[i]; i++) {
            char ch = trace_mode[i];
            switch (ch) {
            case 'p':
                debug_ports = true;
                break;
            case 'r':
                debug_all = true;
                break;
            case 's':
                debug_syscalls = true;
                break;
            default:
                throw std::runtime_error("Wrong trace option: " + std::string(1, ch));
            }
        }

        // Initialize Capstone for i86 16-bit mode.
        if (cs_open(CS_ARCH_X86, CS_MODE_16, &disasm) != CS_ERR_OK) {
            throw std::runtime_error("Failed to initialize Capstone");
        }
    }
}

//
// Enable trace by bitmask,
// for example by some magic instruction.
//
void Machine::enable_trace(unsigned bitmask)
{
    debug_all      = bitmask & 01; // -r
    debug_syscalls = bitmask & 02; // -s
    debug_ports    = bitmask & 04; // -p
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
    out << "----- " << message << std::endl;
}

//
// Print memory or port read/write.
//
void Machine::print_byte_access(unsigned addr, Byte val, const char *opname)
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    out << "      " << opname << " [" << std::hex << std::setw(5)
        << addr << "] = ";
    out << (unsigned)val << std::endl;

    // Restore.
    out.flags(save_flags);
}

void Machine::print_word_access(unsigned addr, Word val, const char *opname)
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    out << "      " << opname << " [" << std::hex << std::setw(5)
        << addr << "] = ";
    out << val << std::endl;

    // Restore.
    out.flags(save_flags);
}

//
// Print instruction address and opcode.
//
void Processor::print_instruction()
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();
    auto pc         = (core.cs << 4) + core.ip;

    out << std::hex << std::setfill('0') << std::setw(5) << pc << " :";

    // Disassemble one instruction.
    cs_insn *insn;
    size_t count = cs_disasm(disasm, opcode.data(), opcode.size(), 0x0, 1, &insn);
    if (count > 0) {
        size_t i;
        for (i = 0; i < insn->size; ++i) {
            out << ' ' << std::setw(2) << std::setfill('0') << (unsigned)insn->bytes[i];
        }
        for (; i < 5; ++i) {
            out << "   ";
        }
        out << "  " << insn[0].mnemonic << ' ' << insn[0].op_str;
        cs_free(insn, count);
    } else {
        // Cannot disassembler, just print bytes.
        for (size_t i = 0; i < opcode.size(); ++i) {
            out << ' ' << std::setw(2) << std::setfill('0') << (unsigned)opcode[i];
        }
    }
    out << std::endl;

    out.flags(save_flags);
}

//
// Print changed CPU registers (core vs prev), then update prev.
//
void Processor::print_registers()
{
    auto &out       = Machine::get_trace_stream();
    auto save_flags = out.flags();

    if (core.ax != prev.ax)
        out << "      AX = " << std::hex << std::setfill('0') << std::setw(4) << core.ax
            << std::endl;
    if (core.bx != prev.bx)
        out << "      BX = " << std::hex << std::setfill('0') << std::setw(4) << core.bx
            << std::endl;
    if (core.cx != prev.cx)
        out << "      CX = " << std::hex << std::setfill('0') << std::setw(4) << core.cx
            << std::endl;
    if (core.dx != prev.dx)
        out << "      DX = " << std::hex << std::setfill('0') << std::setw(4) << core.dx
            << std::endl;
    if (core.sp != prev.sp)
        out << "      SP = " << std::hex << std::setfill('0') << std::setw(4) << core.sp
            << std::endl;
    if (core.bp != prev.bp)
        out << "      BP = " << std::hex << std::setfill('0') << std::setw(4) << core.bp
            << std::endl;
    if (core.si != prev.si)
        out << "      SI = " << std::hex << std::setfill('0') << std::setw(4) << core.si
            << std::endl;
    if (core.di != prev.di)
        out << "      DI = " << std::hex << std::setfill('0') << std::setw(4) << core.di
            << std::endl;
    if (core.cs != prev.cs)
        out << "      CS = " << std::hex << std::setfill('0') << std::setw(4) << core.cs
            << std::endl;
    if (core.ds != prev.ds)
        out << "      DS = " << std::hex << std::setfill('0') << std::setw(4) << core.ds
            << std::endl;
    if (core.ss != prev.ss)
        out << "      SS = " << std::hex << std::setfill('0') << std::setw(4) << core.ss
            << std::endl;
    if (core.es != prev.es)
        out << "      ES = " << std::hex << std::setfill('0') << std::setw(4) << core.es
            << std::endl;
    if (core.flags != prev.flags)
        out << "      Flags = " << std::hex << std::setfill('0') << std::setw(4) << core.flags
            << std::endl;

    prev = core;
    out.flags(save_flags);
}
