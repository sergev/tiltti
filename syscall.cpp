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

#include <iostream>

//
// Check whether instruction is syscall.
//
bool Machine::is_syscall(int type)
{
    if (!mode_640k) {
        // No syscalls in raw mode.
        return false;
    }

    // Check interrupt vector.
    Word offset = memory.load16(type * 4);
    Word seg    = memory.load16(type * 4 + 2);
    unsigned addr = pc86_linear_addr(seg, offset);
    if (addr >= 0x500 && addr < 0xa0000) {
        // Handler is located in user memory.
#if 0
        auto &out = Machine::get_trace_stream();
        out << "--- Vector 0x" << std::hex << type << " at 0x" << seg << ":0x" << offset
            << " = 0x" << addr << std::dec << '\n';
#endif
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
        machine.print_exception_ah("Int 10h Video Request");
        return;
    case 0x11:
        machine.print_exception("Int 11h Equipment List Request");
        return;
    case 0x12:
        machine.print_exception("Int 12h Memory Size Request");
        return;
    case 0x13:
        machine.print_exception_ah("Int 13h Disk Request");
        return;
    case 0x14:
        machine.print_exception_ah("Int 14h Serial Request");
        return;
    case 0x15:
        machine.print_exception_ah("Int 15h System Services Request");
        return;
    case 0x16:
        if (get_ah() == 0x01) {
            // Check keyboard status.
            Machine::get_trace_stream() << '.' << std::flush;
        } else {
            machine.print_exception_ah("Int 16h Keyboard Request");
        }
        return;
    case 0x17:
        machine.print_exception_ah("Int 17h Printer Request");
        return;
    case 0x18:
        machine.print_exception("Int 18h ROM BASIC Request");
        return;
    case 0x19:
        machine.print_exception("Int 19h Boot Request");
        return;
    case 0x1A:
        machine.print_exception_ah("Int 1Ah RTC Timer Request");
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
    if (debug_all || debug_syscalls) {
        cpu.print_syscall(type);
    }

    // Remember last syscall for tests.
    if (type != 0x1A) {
        last_syscall = type | (cpu.get_ah() << 8);
        if (last_syscall == 0x0116) {
            kbd_poll_count++;
        } else {
            kbd_poll_count = 0;
        }
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
        // Memory Size
        cpu.set_ax(bda.mem_size_kb);
        return;
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
        // Keyboard Request
        handle_int16_keyboard();
        return;
    case 0x17:
        // Printer
        handle_int17_printer();
        return;
    case 0x18:
        throw std::runtime_error("ROM BASIC Request");
    case 0x19:
        throw std::runtime_error("Boot Request");
    case 0x1A:
        // RTC and Timer
        handle_int1a_rtc_timer();
        return;
    default:
        throw std::runtime_error("Unknown syscall 0x" + to_hex(type));
    }
}

//
// Process call to ROM BIOS.
// Return true when processed.
// Return false when address is not a valid ROM BIOS call.
//
bool Machine::process_bios_call(unsigned seg, unsigned off)
{
    if (!mode_640k) {
        // No syscalls in raw mode.
        return false;
    }
    if (seg != BIOS_ROM_ADDR >> 4) {
        // Not a BIOS call.
        return false;
    }
#if 0
    auto &out = Machine::get_trace_stream();
    out << "--- Bios call 0x" << std::hex << seg << ":0x" << off << std::dec << '\n';
#endif
    switch (off) {
    case BIOS_ENTRY_INT_00: process_syscall(0x00); return true;
    case BIOS_ENTRY_INT_01: process_syscall(0x01); return true;
    case BIOS_ENTRY_INT_02: process_syscall(0x02); return true;
    case BIOS_ENTRY_INT_03: process_syscall(0x03); return true;
    case BIOS_ENTRY_INT_04: process_syscall(0x04); return true;
    case BIOS_ENTRY_INT_05: process_syscall(0x05); return true;
    case BIOS_ENTRY_INT_06: process_syscall(0x06); return true;
    case BIOS_ENTRY_INT_07: process_syscall(0x07); return true;
    case BIOS_ENTRY_INT_10: process_syscall(0x10); return true;
    case BIOS_ENTRY_INT_11: process_syscall(0x11); return true;
    case BIOS_ENTRY_INT_12: process_syscall(0x12); return true;
    case BIOS_ENTRY_INT_13: process_syscall(0x13); return true;
    case BIOS_ENTRY_INT_14: process_syscall(0x14); return true;
    case BIOS_ENTRY_INT_15: process_syscall(0x15); return true;
    case BIOS_ENTRY_INT_16: process_syscall(0x16); return true;
    case BIOS_ENTRY_INT_17: process_syscall(0x17); return true;
    case BIOS_ENTRY_INT_18: process_syscall(0x18); return true;
    case BIOS_ENTRY_INT_19: process_syscall(0x19); return true;
    case BIOS_ENTRY_INT_1A: process_syscall(0x1A); return true;
    default:
        // Invalid BIOS call.
        return false;
    }
}
