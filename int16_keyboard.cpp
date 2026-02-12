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
        int16_store_kkeystroke_in_buffer();
        break;
    case 0x09:
        int16_get_kkeyboard_functionality();
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

void Machine::int16_read_keyboard_input()
{
    throw std::runtime_error("Unimplemented: Read keyboard input");
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
    // Imitate empty buffer for now.
    //TODO
    cpu.set_zf(1);
}

void Machine::int16_get_shift_flag_status()
{
    throw std::runtime_error("Unimplemented: Get shift flag status");
}

void Machine::int16_store_kkeystroke_in_buffer()
{
    throw std::runtime_error("Unimplemented: Store keystroke in buffer");
}

void Machine::int16_get_kkeyboard_functionality()
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

void Machine::int16_keyboard_capability_dos_keyb()
{
    throw std::runtime_error("Unimplemented: Keyboard capability (DOS keyb)");
}
