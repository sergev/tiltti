//
// Processing of INT requests.
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

//
// Check whether instruction is syscall.
//
bool Machine::is_syscall(int type)
{
    if (!mode_640k) {
        // No syscalls in raw mode.
        return false;
    }

    switch (type) {
    case 0x00:
    case 0x01: // CPU exception
    case 0x02: // NMI
    case 0x03:
    case 0x04: // CPU exception
    case 0x05: // Print Screen
    case 0x06:
    case 0x07: // CPU exception
        return true;
    case 0x08: // IRQ0 Timer
    case 0x09: // IRQ1 Keyboard
    case 0x0E: // IRQ6 Floppy
        return false;
    case 0x10: // Video
    case 0x11: // Equipment List
    case 0x12: // Memory Size
    case 0x13: // Disk
    case 0x14: // Serial
    case 0x15: // System Services
    case 0x16: // Keyboard
    case 0x17: // Printer
    case 0x18: // ROM BASIC
    case 0x19: // Boot
    case 0x1A: // RTC/Timer
        return true;
    case 0x1E: // Floppy param table
    case 0x1F: // Font 8x8 ext
    case 0x40: // Floppy disk internal
    case 0x41: // HD0 FDPT
    case 0x46: // HD1 FDPT
        return false;
    case 0x70: // IRQ8 RTC
    case 0x74: // IRQ12 Mouse
    case 0x75: // IRQ13 FPU
    case 0x76: // IRQ14 IDE
    case 0x79: // Guardian Angel
        return false;
    default:
        // 0x0A-0x0D Unused IRQ
        // 0x0F Unused IRQ
        // 0x20-0x3F Unused
        // 0x1B-0x1D Unused
        // 0x42-0x45 Unused
        // 0x7A-0xFF Unused
        // 0x47-0x5F Unused
        // 0x60-0x66 User reserved
        // 0x67-0x78 Unused
        // 0x71-0x73 Unused IRQ
        // 0x77 Unused IRQ
        return false;
    }
}

//
// Print details about INT request.
//
void Processor::print_syscall(int type)
{
    switch (type) {
    case 0x00:
        machine.print_exception("Int 0h Divide Error");
        return;
    case 0x01:
        machine.print_exception("Int 1h Single Step");
        return;
    case 0x02:
        machine.print_exception("Int 2h NMI");
        return;
    case 0x03:
        machine.print_exception("Int 3h Breakpoint");
        return;
    case 0x04:
        machine.print_exception("Int 4h Overflow");
        return;
    case 0x05:
        machine.print_exception("Int 5h Print Screen Request");
        return;
    case 0x10:
        machine.print_exception("Int 10h Video Request");
        return;
    case 0x11:
        machine.print_exception("Int 11h Equipment List Request");
        return;
    case 0x12:
        machine.print_exception("Int 12h Memory Size Request");
        return;
    case 0x13:
        machine.print_exception("Int 13h Disk Request");
        return;
    case 0x14:
        machine.print_exception("Int 14h Serial Request");
        return;
    case 0x15:
        machine.print_exception("Int 15h System Services Request");
        return;
    case 0x16:
        machine.print_exception("Int 16h Keyboard Request");
        return;
    case 0x17:
        machine.print_exception("Int 17h Printer Request");
        return;
    case 0x18:
        machine.print_exception("Int 18h ROM BASIC Request");
        return;
    case 0x19:
        machine.print_exception("Int 19h Boot Request");
        return;
    case 0x1A:
        machine.print_exception("Int 1Ah RTC Timer Request");
        return;
    default:
        break;
    }
    std::string message = "CPU exception #" + std::to_string(type);
    machine.print_exception(message.c_str());
}

//
// Process INT request.
//
void Machine::process_syscall(int type)
{
    if (trace_enabled()) {
        cpu.print_syscall(type);
    }
    switch (type) {
    case 0x00:
        throw std::runtime_error("Divide Error");
    case 0x01:
        throw std::runtime_error("Single Step");
    case 0x02:
        throw std::runtime_error("NMI");
    case 0x03:
        throw std::runtime_error("Breakpoint");
    case 0x04:
        throw std::runtime_error("Overflow");
    case 0x05:
        // TODO: Print Screen
        throw std::runtime_error("Unimplemented Print Screen Request");
    case 0x10:
        // Video
        handle_int10_video();
        return;
    case 0x11:
        // Equipment List
        cpu.set_ax(bda.equipment_list_flags);
        return;
    case 0x12:
        // TODO: Memory Size
        throw std::runtime_error("Unimplemented Memory Size Request");
    case 0x13:
        // Disk
        handle_int13_disk();
        return;
    case 0x14:
        // Serial
        handle_int14_serial();
        return;
    case 0x15:
        // System Services
        handle_int15_system_services();
        return;
    case 0x16:
        // TODO: Keyboard
        throw std::runtime_error("Unimplemented Keyboard Request");
    case 0x17:
        // TODO: Printer
        throw std::runtime_error("Unimplemented Printer Request");
    case 0x18:
        throw std::runtime_error("ROM BASIC Request");
    case 0x19:
        throw std::runtime_error("Boot Request");
    case 0x1A:
        // TODO: RTC Timer
        throw std::runtime_error("Unimplemented RTC Timer Request");
    default:
        throw std::runtime_error("Unknown syscall 0x" + to_hex(type));
    }
}
