//
// Int 15h: BIOS system services.
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
#include <unistd.h>

#include <cstdint>
#include <iomanip>
#include <sstream>

#include "encoding.h"
#include "machine.h"
#include "pc86_arch.h"

//
// Process Int 15h request: System Services.
//
void Machine::handle_int15_system_services()
{
    switch (cpu.get_ah()) {
    case 0x24:
        int15_a20_gate_control();
        break;
    case 0x41:
        // Wait on External Event.
        pump_callback(10);
        break;
    case 0x4F:
        int15_keyboard_intercept();
        break;
    case 0x52:
        int15_removable_media_eject();
        break;
    case 0x53:
        int15_apm_bios();
        break;
    case 0x5F:
        int15_vga_option_rom_intel();
        break;
    case 0x7F:
        int15_vga_option_rom_smi();
        break;
    case 0x83:
        int15_user_wait_interval();
        break;
    case 0x86:
        int15_wait_for_time();
        break;
    case 0x87:
        int15_copy_memory_block();
        break;
    case 0x88:
        int15_get_extended_memory_size();
        break;
    case 0x89:
        int15_switch_to_protected_mode();
        break;
    case 0x90:
        int15_device_busy();
        break;
    case 0x91:
        int15_interrupt_complete();
        break;
    case 0xC0:
        int15_get_system_configuration();
        break;
    case 0xC1:
        int15_get_ebda_segment();
        break;
    case 0xC2:
        int15_mouse_interface();
        break;
    case 0xE8:
        int15_extended_memory();
        break;
    default:
        if (Machine::trace_enabled()) {
            auto &out = Machine::get_trace_stream();
            auto save = out.flags();

            out << "\tAH=" << std::hex << std::setfill('0') << std::setw(2)
                << (unsigned)cpu.get_ah() << "h Unknown request" << std::endl;
            out.flags(save);
        }
    }
}

//
// AH=24h — A20 gate control.
//
// Control or query the A20 address line (real-mode access above 1 MB).
// Inputs: AL = subfunction (00h disable, 01h enable, 02h get status, 03h query support).
// Outputs: CF=0 on success; AL=02h returns AL=0/1; AL=03h returns BX=3. Unsupported AL: CF=1, AH=86h.
//
void Machine::int15_a20_gate_control()
{
    unsigned al = cpu.get_al();
    switch (al) {
    case 0x00:
        a20_enabled = false;
        cpu.set_ah(0);
        cpu.set_cf(0);
        break;
    case 0x01:
        a20_enabled = true;
        cpu.set_ah(0);
        cpu.set_cf(0);
        break;
    case 0x02:
        cpu.set_al(a20_enabled ? 1 : 0);
        cpu.set_ah(0);
        cpu.set_cf(0);
        break;
    case 0x03:
        cpu.set_bx(3);
        cpu.set_ah(0);
        cpu.set_cf(0);
        break;
    default:
        cpu.set_ah(0x86);
        cpu.set_cf(1);
        break;
    }
}

void Machine::int15_keyboard_intercept()
{
    throw std::runtime_error("Unimplemented: Keyboard intercept");
}

void Machine::int15_removable_media_eject()
{
    throw std::runtime_error("Unimplemented: Removable media eject");
}

void Machine::int15_apm_bios()
{
    throw std::runtime_error("Unimplemented: APM BIOS");
}

void Machine::int15_vga_option_rom_intel()
{
    throw std::runtime_error("Unimplemented: VGA option ROM Intel");
}

void Machine::int15_vga_option_rom_smi()
{
    throw std::runtime_error("Unimplemented: VGA option ROM SMI");
}

void Machine::int15_user_wait_interval()
{
    throw std::runtime_error("Unimplemented: User wait interval");
}

void Machine::int15_wait_for_time()
{
    throw std::runtime_error("Unimplemented: Wait for time");
}

void Machine::int15_copy_memory_block()
{
    throw std::runtime_error("Unimplemented: Copy memory block");
}

//
// AH=88h — Get extended memory size.
//
// Return the size of extended memory (above 1 MB) in kilobytes.
// Outputs:
//      CF = 0
//      AX = (LegacyRamSize - 1 MB) / 1024, capped at 63 MB (63*1024 = 64512)
//
void Machine::int15_get_extended_memory_size()
{
    // No extended memory.
    cpu.set_cf(0);
    cpu.set_ax(0);
}

void Machine::int15_switch_to_protected_mode()
{
    throw std::runtime_error("Unimplemented: Switch to protected mode");
}

void Machine::int15_device_busy()
{
    throw std::runtime_error("Unimplemented: Device busy");
}

void Machine::int15_interrupt_complete()
{
    throw std::runtime_error("Unimplemented: Interrupt complete");
}

//
// AH=C0h - Get system configuration.
//
// Return a pointer to the BIOS configuration table
// (model, submodel, revision, feature flags).
// Outputs:
//      CF = 0
//      ES:BX = pointer to `BIOS_CONFIG_TABLE` (fixed at segment 0xF000,
//              offset 0xe6f5 in typical builds).
//
void Machine::int15_get_system_configuration()
{
    cpu.set_cf(0);
    cpu.set_es(0xf000);
    cpu.set_bx(BIOS_CONFIG_TABLE);
}

//
// AH=C1h — Get EBDA segment.
//
// Return the segment of the Extended BIOS Data Area (EBDA).
// Outputs:
//      CF = 0
//      ES = EBDA segment (from BDA ebda_seg)
//
void Machine::int15_get_ebda_segment()
{
    cpu.set_cf(0);
    cpu.set_es(bda.ebda_seg);
}

void Machine::int15_mouse_interface()
{
    throw std::runtime_error("Unimplemented: Mouse interface");
}

void Machine::int15_extended_memory()
{
    throw std::runtime_error("Unimplemented: Extended memory");
}
