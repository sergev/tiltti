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
#include <cstring>
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
        int10_save_restore_video_state();
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
// Fill video memory with spaces,
// Use attribute 0x07 (grey on black).
//
void Machine::clear_video_memory()
{
    unsigned video_base = (bda.video_mode == 7) ? 0xb0000 : 0xb8000;
    unsigned fill       = (bda.video_mode == 6) ? 0x0000 : 0x0720;

    for (unsigned i = 0; i < 32 * 1024; i += 2)
        memory.store16(video_base + i, fill);
}

//
// Set video mode: update BDA and optionally clear display memory.
// Does not touch CPU registers.
//
void Machine::set_video_mode(unsigned mode)
{
    // Mode-to-BDA mapping. Unsupported modes (4, 5, 8+) use mode 3 as fallback.
    unsigned cols, rows, pagesize;
    bool is_text;
    if (mode <= 1) {
        cols     = 40;
        rows     = 24;
        pagesize = 40 * 25 * 2;
        is_text  = true;
    } else if (mode <= 3 || mode == 7) {
        cols     = 80;
        rows     = 24;
        pagesize = 80 * 25 * 2;
        is_text  = true;
    } else if (mode == 6) {
        cols     = 80;
        rows     = 24;
        pagesize = 80 * 25 * 2;
        is_text  = false;
    } else {
        cols     = 80;
        rows     = 24;
        pagesize = 80 * 25 * 2;
        is_text  = true;
    }

    bda.video_mode      = (mode < 0x100) ? static_cast<uint8_t>(mode) : 0xff;
    bda.video_cols      = cols;
    bda.video_rows      = rows;
    bda.video_pagesize  = pagesize;
    bda.video_pagestart = 0x0000;
    bda.video_page      = 0x00;
    bda.cursor_type     = is_text ? 0x0607 : 0x0000;
    bda.video_ctl       = 0x60;
    bda.modeset_ctl &= 0x7f;
    for (int i = 0; i < 8; i++) {
        bda.cursor_pos[i] = 0x0000;
    }

    video_dirty = true;
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
    unsigned mode   = cpu.get_al() & 0x7f;
    bool clear_flag = (cpu.get_al() & 0x80) == 0;

    set_video_mode(mode);
    if (clear_flag) {
        clear_video_memory();
    } else {
        bda.video_ctl |= 0x80;
    }

    if (mode > 7)
        cpu.set_al(0x20);
    else if (mode == 6)
        cpu.set_al(0x3f);
    else if (mode <= 1)
        cpu.set_al(0x20);
    else
        cpu.set_al(0x30);
}

//
// AH=01h - Set cursor shape.
//
// Set the cursor shape or hide the cursor.
// Inputs:
//      CX = cursor type (CH = start scan line, CL = end scan line).
//           CX=0x0000 hides the cursor.
//
void Machine::int10_set_cursor_shape()
{
    bda.cursor_type = cpu.get_cx();
    video_dirty     = true;
    // TODO: update CRTC port (cursor shape registers 0x0a, 0x0b)
}

//
// AH=02h - Set cursor position.
//
// Set the cursor position on a given page.
// Inputs:
//      BH = page (0-7)
//      DH = row
//      DL = column
//
void Machine::int10_set_cursor_position()
{
    unsigned page = cpu.get_bh();
    if (page > 7)
        return;

    unsigned row         = cpu.get_dh();
    unsigned col         = cpu.get_dl();
    bda.cursor_pos[page] = (row << 8) | col;
    video_dirty          = true;
    // TODO: update CRTC port (cursor position 0x0e, 0x0f) when page == active page
}

//
// AH=03h - Get cursor position.
//
// Return cursor shape and position for the given page.
// Inputs:
//      BH = page (0-7)
// Outputs:
//      DH = row, DL = column, CX = cursor type (CH = start scan line, CL = end scan line).
//
void Machine::int10_get_cursor_position()
{
    unsigned page = cpu.get_bh();
    if (page > 7) {
        cpu.set_dh(0);
        cpu.set_dl(0);
        cpu.set_cx(0);
        return;
    }

    uint16_t pos = bda.cursor_pos[page];
    cpu.set_dx(pos);
    cpu.set_cx(bda.cursor_type);
}

//
// AH=04h - Read light pen position. No light pen; return zeros.
//
void Machine::int10_read_light_pen_position()
{
    cpu.set_ax(0);
    cpu.set_bx(0);
    cpu.set_cx(0);
    cpu.set_dx(0);
}

//
// AH=05h - Select display page.
//
// Set the active display page (0-7). The display shows the region of video
// memory for the selected page.
// Inputs:
//      AL = page number (0-7)
// Outputs:
//      None.
//
void Machine::int10_select_display_page()
{
    unsigned page = cpu.get_al();
    if (page > 7)
        page = 0;

    bda.video_page      = static_cast<uint8_t>(page);
    bda.video_pagestart = static_cast<uint16_t>(bda.video_pagesize * page);
    video_dirty         = true;
    // TODO: update CRTC port (display start address 0x0C, 0x0D) when port I/O is implemented
}

//
// AH=06h - Scroll window up
// AH=07h - Scroll window down
//
// Scroll a rectangle up or down by a number of lines, or clear it (AL=0).
// Inputs:
//      AL = number of lines to scroll (0 = clear entire rectangle)
//      BH = attribute for new lines
//      CH, CL = upper-left row, column
//      DH, DL = lower-right row, column
//
void Machine::int10_scroll_window_up()
{
    scroll_window(1);
}

void Machine::int10_scroll_window_down()
{
    scroll_window(-1);
}

void Machine::scroll_window(int dir)
{
    unsigned ulx    = cpu.get_cl();
    unsigned uly    = cpu.get_ch();
    unsigned lrx    = cpu.get_dl();
    unsigned lry    = cpu.get_dh();
    unsigned nbrows = bda.video_rows + 1;
    unsigned nbcols = bda.video_cols;

    if (lry >= nbrows)
        lry = nbrows - 1;
    if (lrx >= nbcols)
        lrx = nbcols - 1;

    int wincols = static_cast<int>(lrx - ulx + 1);
    int winrows = static_cast<int>(lry - uly + 1);
    if (wincols <= 0 || winrows <= 0)
        return;

    int lines = cpu.get_al();
    if (lines >= winrows)
        lines = 0;
    lines *= dir;

    unsigned page_offset = bda.video_pagesize * bda.video_page;

    int stride    = bda.video_cols * 2;
    Byte *base    = memory.get_ptr(0xb8000) + page_offset;
    uint16_t fill = (cpu.get_bh() << 8) | 0x20; // space + attribute

    auto cell_addr = [&](int x, int y) {
        return base + static_cast<ptrdiff_t>(y) * stride + x * 2;
    };

    auto store_cell = [&](int x, int y) {
        memory.store16(0xb8000 + page_offset + (static_cast<unsigned>(y) * stride + x * 2), fill);
    };

    if (lines == 0) {
        // Clear entire window.
        for (int y = 0; y < winrows; y++) {
            for (int x = 0; x < wincols; x++) {
                store_cell(ulx + x, uly + y);
            }
        }
        video_dirty = true;
        return;
    }

    if (lines > 0) {
        // Scroll up: move block from (ulx, uly+lines) to (ulx, uly).
        int nlines     = winrows - lines;
        Byte *dest     = cell_addr(ulx, uly);
        Byte *src      = cell_addr(ulx, uly + lines);
        int line_bytes = wincols * 2;

        for (int i = 0; i < nlines; i++) {
            std::memcpy(dest + i * stride, src + i * stride, static_cast<size_t>(line_bytes));
        }

        // Clear bottom lines.
        for (int y = winrows - lines; y < winrows; y++) {
            for (int x = 0; x < wincols; x++) {
                store_cell(ulx + x, uly + y);
            }
        }
    } else {
        // Scroll down: move block from (ulx, uly) to (ulx, uly + abs(lines)).
        int abs_lines  = -lines;
        int nlines     = winrows - abs_lines;
        Byte *dest     = cell_addr(ulx, uly + abs_lines);
        Byte *src      = cell_addr(ulx, uly);
        int line_bytes = wincols * 2;

        for (int i = nlines - 1; i >= 0; i--) {
            std::memcpy(dest + i * stride, src + i * stride, static_cast<size_t>(line_bytes));
        }

        // Clear top lines.
        for (int y = 0; y < abs_lines; y++) {
            for (int x = 0; x < wincols; x++) {
                store_cell(ulx + x, uly + y);
            }
        }
    }
    video_dirty = true;
}

//
// AH=08h - Read character and attribute at cursor.
//
// Read the character and attribute at the current cursor position on the given page.
// Inputs:
//      BH = page (0-7)
// Outputs:
//      AL = character code
//      AH = attribute
//
void Machine::int10_read_char()
{
    unsigned page = cpu.get_bh();
    if (page > 7) {
        cpu.set_al(0);
        cpu.set_ah(0);
        return;
    }

    unsigned col = bda.cursor_pos[page] & 0xff;
    unsigned row = bda.cursor_pos[page] >> 8;

    unsigned page_offset = bda.video_pagesize * page;
    int stride           = bda.video_cols * 2;

    unsigned addr = 0xb8000 + page_offset + row * stride + col * 2;
    uint16_t v    = memory.load16(addr);

    cpu.set_al(v & 0xff);
    cpu.set_ah(v >> 8);
}

//
// Helper: write 'count' cells at cursor on 'page', advancing cursor.
// use_fixed_attr: true = store (fixed_attr<<8)|ch; false = preserve attribute (load word, keep high byte).
//
void Machine::write_cells_at_cursor(unsigned page, unsigned count, uint8_t ch,
    bool use_fixed_attr, uint8_t fixed_attr)
{
    if (page > 7)
        return;

    unsigned col         = bda.cursor_pos[page] & 0xff;
    unsigned row         = bda.cursor_pos[page] >> 8;
    unsigned page_offset = bda.video_pagesize * page;
    int stride           = bda.video_cols * 2;

    while (count--) {
        unsigned addr = 0xb8000 + page_offset + row * stride + col * 2;
        uint16_t word;
        if (use_fixed_attr)
            word = (static_cast<uint16_t>(fixed_attr) << 8) | ch;
        else
            word = (memory.load16(addr) & 0xff00) | ch;
        memory.store16(addr, word);

        col++;
        if (col >= bda.video_cols) {
            col = 0;
            row++;
        }
    }

    video_dirty          = true;
    bda.cursor_pos[page] = (row << 8) | col;
}

//
// AH=09h - Write character and attribute.
//
// Write a character with attribute at the cursor position, repeated CX times;
// cursor advances for each character.
// Inputs:
//      AL = character
//      BH = page (0-7)
//      BL = attribute
//      CX = count
//
void Machine::int10_write_char()
{
    write_cells_at_cursor(cpu.get_bh(), cpu.get_cx(), cpu.get_al(), true, cpu.get_bl());
}

//
// AH=0Ah - Write character only.
//
// Write a character at the cursor position, repeated CX times; attribute is preserved.
// Cursor advances for each character.
// Inputs:
//      AL = character
//      BH = page (0-7)
//      CX = count
//
void Machine::int10_write_char_only()
{
    write_cells_at_cursor(cpu.get_bh(), cpu.get_cx(), cpu.get_al(), false, 0);
}

//
// AH=0Bh - Set color palette (CGA).
//
// BH=0: BL = background/border color (0-15).
// BH=1: BL = palette (0 or 1) for 320x200 4-color graphics.
// State is stored in BDA; no CRTC or display update yet.
//
void Machine::int10_set_cga_palette()
{
    unsigned bh = cpu.get_bh();
    uint8_t bl  = cpu.get_bl();

    if (bh == 0) {
        bda.video_pal = bl & 0x0f;
    } else if (bh == 1) {
        bda.video_msr = (bda.video_msr & 0xfe) | (bl & 1);
    }
    // TODO: update CRTC port (CGA palette/background) when port I/O is implemented
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
// Output a character with interpretation: BEL (7), BS (8), CR (13), LF (10).
// Other characters are written at the current cursor on the active page
// (character only, attribute preserved); cursor advances. Screen scrolls when past bottom.
// Inputs:
//      AL = character
//      BL = attribute (unused; teletype preserves existing attribute)
//
void Machine::int10_teletype_output()
{
    unsigned page = bda.video_page;
    unsigned col  = bda.cursor_pos[page] & 0xff;
    unsigned row  = bda.cursor_pos[page] >> 8;
    uint8_t ch    = cpu.get_al();

    unsigned page_offset = bda.video_pagesize * page;
    int stride           = bda.video_cols * 2;
    unsigned nbrows      = bda.video_rows;
#if 0
    utf8_putc(cp437_to_unicode_table[ch]); // debug
    std::cout << std::flush; // debug
#endif
    switch (ch) {
    case 7: // BEL - beep
        std::cout << '\a' << std::flush;
        break;
    case 8: // BS - backspace
        if (col > 0)
            col--;
        break;
    case '\r': // CR - carriage return
        col = 0;
        break;
    case '\n': // LF - line feed
        row++;
        break;
    default: {
        // Write character only, preserve attribute.
        unsigned addr = 0xb8000 + page_offset + row * stride + col * 2;
        memory.store8(addr, ch);
        col++;
        if (col >= bda.video_cols) {
            col = 0;
            row++;
        }
        break;
    }
    }

    // Scroll if past bottom.
    if (row > nbrows) {
        row = nbrows;

        // Scroll full screen up by one line.
        Byte *base  = memory.get_ptr(0xb8000) + page_offset;
        int wincols = bda.video_cols;
        int winrows = nbrows + 1;

        Byte *dest     = base;
        Byte *src      = base + stride;
        int line_bytes = wincols * 2;
        for (int i = 0; i < winrows - 1; i++) {
            std::memcpy(dest + i * stride, src + i * stride, static_cast<size_t>(line_bytes));
        }
        for (int x = 0; x < wincols; x++) {
            memory.store16(
                0xb8000 + page_offset + (static_cast<unsigned>(winrows - 1) * stride + x * 2),
                (0x07 << 8) | 0x20); // space, default attribute
        }
    }

    video_dirty          = true;
    bda.cursor_pos[page] = (row << 8) | col;
    // TODO: update CRTC port (cursor position) when writing to video RAM
}

//
// AH=0Fh — Get current video mode.
//
// Return current mode, number of columns, and active page.
// Outputs:
//      AL = current video mode (or 0xFF for VBE mode)
//      AH = number of columns
//      BH = active display page.
//
void Machine::int10_get_current_video_mode()
{
    cpu.set_bh(bda.video_page);
    cpu.set_al(bda.video_mode | (bda.video_ctl & 0x80));
    cpu.set_ah(bda.video_cols);
}

void Machine::int10_palette_control()
{
    // TODO: update CRTC port (attribute controller, DAC)
    throw std::runtime_error("Unimplemented: Palette and DAC functions");
}

void Machine::int10_char_generator()
{
    // TODO: update CRTC port (font loading, character height)
    throw std::runtime_error("Unimplemented: Character generator");
}

//
// AH=12h - Alternate select (EGA/VGA).
//
// BL=10h: Get video subsystem config. Returns BX (config), CX (switch settings).
// BL=30h--36h: Set options (vertical resolution, palette, etc.); no-op, return AL=0x12.
//
void Machine::int10_alternate_select()
{
    unsigned bl = cpu.get_bl();

    if (bl == 0x10) {
        // Get video subsystem config. BX: BH=0 color/1 mono, BL=memory (0=64K..3=256K). CX: switch settings.
        cpu.set_bx(0x0003); // color, 256K
        cpu.set_cx(bda.video_switches);
    } else if (bl >= 0x30 && bl <= 0x36) {
        // Select vertical resolution, palette, addressing, gray-scale, cursor emulation, or reserved; no-op.
        cpu.set_al(0x12);
    }
}

//
// AH=13h - Write string.
//
// Write a string at (DH,DL) on page BH. AL bit 0: update cursor after; bit 1: string is char,attr pairs.
// ES:BP = string; CX = character count; BL = attribute (when AL bit 1 = 0).
//
void Machine::int10_write_string()
{
    unsigned page = cpu.get_bh();
    if (page > 7)
        return;

    unsigned row  = cpu.get_dh();
    unsigned col  = cpu.get_dl();
    unsigned count = cpu.get_cx();
    uint8_t al     = cpu.get_al();
    uint8_t attr   = cpu.get_bl();
    bool attr_in_string = (al & 2) != 0;
    bool update_cursor  = (al & 1) != 0;

    unsigned page_offset = bda.video_pagesize * page;
    int stride           = bda.video_cols * 2;
    unsigned str_addr    = pc86_linear_addr(cpu.get_es(), cpu.get_bp());

    for (unsigned i = 0; i < count; i++) {
        uint8_t ch;
        if (attr_in_string) {
            ch   = memory.load8(str_addr);
            attr = memory.load8(str_addr + 1);
            str_addr += 2;
        } else {
            ch = memory.load8(str_addr);
            str_addr += 1;
        }

        unsigned cell_addr = 0xb8000 + page_offset + row * stride + col * 2;
        memory.store16(cell_addr, (static_cast<uint16_t>(attr) << 8) | ch);

        col++;
        if (col >= bda.video_cols) {
            col = 0;
            row++;
        }
    }

    video_dirty = true;
    if (update_cursor)
        bda.cursor_pos[page] = (row << 8) | col;
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

void Machine::int10_save_restore_video_state()
{
    throw std::runtime_error("Unimplemented: Save/restore video state");
}

void Machine::int10_vbe()
{
    throw std::runtime_error("Unimplemented: VBE");
}
