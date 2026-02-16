//
// Int 16h: BIOS keyboard request.
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
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "encoding.h"
#include "machine.h"
#include "pc86_arch.h"

//
// Process Int 16h request: Keyboard.
//
void Machine::handle_int16_keyboard()
{
    switch (cpu.get_ah()) {
    case 0x00:
        int16_read_keyboard_input();
        break;
    case 0x01:
        int16_check_keyboard_status();
        break;
    case 0x02:
        int16_get_shift_flag_status();
        break;
    case 0x05:
        int16_store_keystroke_in_buffer();
        break;
    case 0x09:
        int16_get_keyboard_functionality();
        break;
    case 0x0a:
        int16_get_keyboard_id();
        break;
    case 0x10:
        int16_read_mf2_keyboard_input();
        break;
    case 0x11:
        int16_check_mf2_keyboard_status();
        break;
    case 0x12:
        int16_get_extended_keyboard_status();
        break;
    case 0x6f:
        int16_keyboard_capability_check();
        break;
    case 0x92:
        int16_keyboard_capability_dos_keyb();
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
// AH=00h — Read keyboard input.
//
// Wait until a key is available in the keyboard buffer,
// then return its keycode in AX and remove it from the buffer.
// Outputs:
//      AX = keycode (AL = ASCII, AH = scancode).
// For extended keys, the BIOS may translate (e.g. extended Enter → 0x1c0d, extended '/' → 0x352f).
// If the low byte was 0xe0 and high byte non-zero, AH is left as the scancode and AL cleared.
// If 0xf0 in low byte with high byte set, only the high byte is returned.
// Other registers and flags (except as modified by entry/exit) are preserved.
//
void Machine::int16_read_keyboard_input()
{
    pump_events();
    if (!has_keystroke()) {
        do {
            // Pause waiting for input.
            delay_callback_();

            if (!pump_events()) {
                // Window closed.
                std::exit(0);
            }
        } while (!has_keystroke());
    }
    uint16_t ax = pop_keystroke();
    cpu.set_ax(ax);
}

//
// AH=01h — Check keyboard status.
//
// Check whether a key is available in the buffer without removing it.
// Returns immediately.
// Outputs:
//      ZF = 1 if buffer empty
//      ZF = 0 if a key is available
// When a key is available, AX holds that keycode (same format as AH=00h).
// The key remains in the buffer.
// If buffer empty, sets ZF and returns. Otherwise reads keycode (with translation),
// sets AX and clears ZF, and does not advance head.
//
void Machine::int16_check_keyboard_status()
{
    pump_events();
    if (has_keystroke()) {
        cpu.set_zf(0);
        cpu.set_ax(peek_keystroke());
    } else {
        cpu.set_zf(1);
    }
}

//
// AH=02h — Get shift flag status.
//
// Return the current keyboard shift/modifier and lock state (low byte of kbd_flag0).
// Outputs:
//      AL = value of BDA `kbd_flag0` (low byte).
//           Bit definitions in `src/std/bda.h`:
//           KF0_RSHIFT, KF0_LSHIFT, KF0_CTRLACTIVE, KF0_ALTACTIVE,
//           KF0_SCROLLACTIVE, KF0_NUMACTIVE, KF0_CAPSACTIVE.
// See also AH=12h: it returns the full extended status
// (kbd_flag0 with kbd_flag1 RALT/RCTRL merged into the high byte).
//
void Machine::int16_get_shift_flag_status()
{
    cpu.set_al(static_cast<uint8_t>(bda.kbd_flag0 & 0xff));
    cpu.set_ah(0);
}

void Machine::int16_store_keystroke_in_buffer()
{
    throw std::runtime_error("Unimplemented: Store keystroke in buffer");
}

void Machine::int16_get_keyboard_functionality()
{
    throw std::runtime_error("Unimplemented: Get keyboard functionality");
}

void Machine::int16_get_keyboard_id()
{
    throw std::runtime_error("Unimplemented: Get keyboard ID");
}

void Machine::int16_read_mf2_keyboard_input()
{
    throw std::runtime_error("Unimplemented: Read MF-II keyboard input");
}

void Machine::int16_check_mf2_keyboard_status()
{
    throw std::runtime_error("Unimplemented: Check MF-II keyboard status");
}

void Machine::int16_get_extended_keyboard_status()
{
    throw std::runtime_error("Unimplemented: Get extended keyboard status");
}

void Machine::int16_keyboard_capability_check()
{
    throw std::runtime_error("Unimplemented: Keyboard capability check");
}

//
// AH=92h — Keyboard capability (DOS keyb).
//
// Called by DOS 5.0+ KEYB to detect whether INT 16h AH=10h–12h (enhanced keyboard) is supported.
// Outputs:
//      AH = 0x80 (enhanced keyboard functions supported)
//
void Machine::int16_keyboard_capability_dos_keyb()
{
    cpu.set_ah(0x80);
}
