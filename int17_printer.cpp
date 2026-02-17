//
// Int 17h: BIOS printer services.
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
#include <cstdint>
#include <iomanip>
#include <sstream>

#include "encoding.h"
#include "machine.h"
#include "pc86_arch.h"

//
// Process Int 17h request: Printer.
//
void Machine::handle_int17_printer()
{
    switch (cpu.get_ah()) {
    case 0x00:
        int17_write_char();
        break;
    case 0x01:
        int17_initialize_port();
        break;
    case 0x02:
        int17_get_status();
        break;
    default:
        if (debug_all | debug_syscalls) {
            auto &out = Machine::get_trace_stream();
            auto save = out.flags();

            out << "\tAH=" << std::hex << std::setfill('0') << std::setw(2)
                << (unsigned)cpu.get_ah() << "h Unknown request" << std::endl;
            out.flags(save);
        }
    }
}

void Machine::int17_write_char()
{
    throw std::runtime_error("Unimplemented: Write character to printer");
}

//
// AH=01h — Initialize printer port.
//
// Send an initialization pulse to the printer.
// Returns the current printer status.
// Inputs:
//      DX = port index (0–2).
// Outputs:
//      AH = printer status (status register XOR 0x48)
//      CF = 0
// On invalid port, CF=1.
//
void Machine::int17_initialize_port()
{
    // Invalid port.
    cpu.set_cf(1);
}

void Machine::int17_get_status()
{
    throw std::runtime_error("Unimplemented: Get printer status");
}
