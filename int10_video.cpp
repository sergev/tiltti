//
// Int 10h: BIOS video services.
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
// Process Int 10h request: VGA display.
//
void Machine::handle_int10_video()
{
    switch (cpu.get_ah()) {
    case 0x00:
        int10_set_video_mode();
        break;
    case 0x01:
        int10_set_cursor_shape();
        break;
    case 0x02:
        int10_set_cursor_position();
        break;
    case 0x03:
        int10_get_cursor_position();
        break;
    case 0x04:
        int10_read_light_pen_position();
        break;
    case 0x05:
        int10_select_display_page();
        break;
    case 0x06:
        int10_scroll_window_up();
        break;
    case 0x07:
        int10_scroll_window_down();
        break;
    case 0x08:
        int10_read_char();
        break;
    case 0x09:
        int10_write_char();
        break;
    case 0x0A:
        int10_write_char_only();
        break;
    case 0x0B:
        int10_set_cga_palette();
        break;
    case 0x0C:
        int10_write_pixel();
        break;
    case 0x0D:
        int10_read_pixel();
        break;
    case 0x0E:
        int10_teletype_output();
        break;
    case 0x0F:
        int10_get_current_video_mode();
        break;
    case 0x10:
        int10_palette_control();
        break;
    case 0x11:
        int10_char_generator();
        break;
    case 0x12:
        int10_alternate_select();
        break;
    case 0x13:
        int10_write_string();
        break;
    case 0x1A:
        int10_display_combination_code();
        break;
    case 0x1B:
        int10_video_bios_functionality();
        break;
    case 0x1C:
        int10_save_rrestore_video_state();
        break;
    case 0x4F:
        int10_vbe();
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
// AH=00h - Set video mode
//
// Set the video mode and optionally clear display memory.
// Inputs:
//      AL = mode (0x00–0x13 and driver-specific modes).
//           Bit 7 of AL: 1 = do not clear display memory.
// Outputs:
//      AL is set to a column indicator: 0x20 for 40-column,
//      0x3f for 80-column (mode 6), 0x30 for other 80-column.
//      Registers otherwise unchanged.
//
void Machine::int10_set_video_mode()
{
    throw std::runtime_error("Unimplemented: Set video mode");
}

void Machine::int10_set_cursor_shape()
{
    throw std::runtime_error("Unimplemented: Set cursor shape");
}

void Machine::int10_set_cursor_position()
{
    throw std::runtime_error("Unimplemented: Set cursor position");
}

void Machine::int10_get_cursor_position()
{
    throw std::runtime_error("Unimplemented: Get cursor position");
}

void Machine::int10_read_light_pen_position()
{
    throw std::runtime_error("Unimplemented: Read light pen");
}

void Machine::int10_select_display_page()
{
    throw std::runtime_error("Unimplemented: Select display page");
}

void Machine::int10_scroll_window_up()
{
    throw std::runtime_error("Unimplemented: Scroll window up");
}

void Machine::int10_scroll_window_down()
{
    throw std::runtime_error("Unimplemented: Scroll window down");
}

void Machine::int10_read_char()
{
    throw std::runtime_error("Unimplemented: Read character and attribute");
}

void Machine::int10_write_char()
{
    throw std::runtime_error("Unimplemented: Write character and attribute");
}

void Machine::int10_write_char_only()
{
    throw std::runtime_error("Unimplemented: Write character only");
}

void Machine::int10_set_cga_palette()
{
    throw std::runtime_error("Unimplemented: Set color palette");
}

void Machine::int10_write_pixel()
{
    throw std::runtime_error("Unimplemented: Write pixel");
}

void Machine::int10_read_pixel()
{
    throw std::runtime_error("Unimplemented: Read pixel");
}

//
// AH=0Eh - Teletype output.
//
// Output a character with interpretation: BEL (7), BS (8), CR, LF.
// Other characters are written at the current cursor on the active page
// and cursor advances. Screen scrolls when past bottom.
// Inputs:
//      AL = character
//      BL = attribute
//
void Machine::int10_teletype_output()
{
    // For now, print on stdout.
    // Ignore attribute.
    unsigned ch = cpu.get_al();

    utf8_putc(cp437_to_unicode_table[ch]);
    std::cout << std::flush;
}

void Machine::int10_get_current_video_mode()
{
    throw std::runtime_error("Unimplemented: Get video mode");
}

void Machine::int10_palette_control()
{
    throw std::runtime_error("Unimplemented: Palette and DAC functions");
}

void Machine::int10_char_generator()
{
    throw std::runtime_error("Unimplemented: Character generator");
}

void Machine::int10_alternate_select()
{
    throw std::runtime_error("Unimplemented: Alternate select");
}

void Machine::int10_write_string()
{
    throw std::runtime_error("Unimplemented: Write string");
}

//
// AH=1Ah - Display combination code.
//
// When AL=00h - Get display combination code.
// Outputs:
//      BX = DCC index
//      AL = 0x1A
//
// When AL=01h - Set display combination code.
// Inputs:
//      BL = DCC index
// Outputs:
//      AL = 0x1A
//
void Machine::int10_display_combination_code()
{
    switch (cpu.get_al()) {
    case 0:
        // Get display combination code.
        cpu.set_bx(bda.dcc_index);
        cpu.set_al(0x1a);
        break;
    case 1:
        // Set display combination code.
        bda.dcc_index = cpu.get_bl();
        cpu.set_al(0x1a);
        break;
    default:
        break;
    }
}

//
// AH=1Bh - Video BIOS functionality
//
// Return a table describing video BIOS capabilities and current state.
// Inputs:
//      ES:DI = pointer to `struct video_func_info`
// Outputs:
//      Buffer filled with:
//          pointer to static functionality table
//          copy of BDA 0x49–0x66 and 0x84–0x86
//          DCC index
//          colors (16)
//          pages (8)
//          scan lines (2)
//          video memory (3)
//      AL = 0x1B
//
void Machine::int10_video_bios_functionality()
{
    throw std::runtime_error("Unimplemented: Video BIOS functionality");
}

void Machine::int10_save_rrestore_video_state()
{
    throw std::runtime_error("Unimplemented: Save/restore video state");
}

void Machine::int10_vbe()
{
    throw std::runtime_error("Unimplemented: VBE");
}
