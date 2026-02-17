//
// Int 14h: BIOS serial services.
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
// Process Int 14h request: Serial.
//
void Machine::handle_int14_serial()
{
    switch (cpu.get_ah()) {
    case 0x00:
        int14_initialize_serial_port();
        break;
    case 0x01:
        int14_write_char();
        break;
    case 0x02:
        int14_read_char();
        break;
    case 0x03:
        int14_get_port_status();
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

//
// AH=00h - Initialize serial port.
//
// Initialize the asynchronous communications port with the requested baud rate
// and line parameters (word length, stop bits, parity).
// Returns the current line and modem status.
// Inputs:
//      DX = port index (0–3).
//      AL = line and baud parameters:
//           - Bits 0–1: Word length — 00 = 5 bits, 01 = 6 bits, 10 = 7 bits, 11 = 8 bits.
//           - Bit 2:    Stop bits — 0 = 1 stop bit, 1 = 2 stop bits.
//           - Bits 3–4: Parity — 00 = none, 01 = odd, 10 = even, 11 = stick parity.
//           - Bits 5–7: Baud rate divisor index —
//              000 = default (110 baud, divisor 0x417);
//              001–111 = 150, 300, 600, 1200, 2400, 4800, 9600 baud
//              (divisor derived from `0x600 >> (bits 5–7)`).
// Outputs:
//      AH = LSR
//      AL = MSR
//      CF = 0.
// On invalid port, CF=1 and handler returns without updating AX.
//
void Machine::int14_initialize_serial_port()
{
    // Invalid port.
    cpu.set_cf(1);
}

void Machine::int14_write_char()
{
    throw std::runtime_error("Unimplemented: Write character");
}

void Machine::int14_read_char()
{
    throw std::runtime_error("Unimplemented: Read character");
}

void Machine::int14_get_port_status()
{
    throw std::runtime_error("Unimplemented: Get port status");
}
