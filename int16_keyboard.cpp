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
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

#include "encoding.h"
#include "machine.h"
#include "pc86_arch.h"

static struct termios tios_org;

void Machine::setup_keyboard()
{
    struct termios tios;

    if (tcgetattr(1, &tios) < 0) {
        throw std::runtime_error("Cannot get stdout mode");
    }
    tios_org = tios;
    tios.c_iflag &= ~(ISTRIP | INLCR | ICRNL | IXON | IXOFF);
    //tios.c_oflag &= ~OPOST;
    tios.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
    tios.c_cc[VMIN] = 1;
    tios.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &tios) < 0) {
        throw std::runtime_error("Cannot set stdout mode");
    }

    //init = 1;
    //atexit((void (*)(void))conio_close);
}

void Machine::close_keyboard()
{
    if (tcsetattr(0, TCSANOW, &tios_org) < 0) {
        std::cerr << "Error: Cannot restore stdout mode\n";
    }
}

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
    char c;

    for (;;) {
        switch (read(0, &c, 1)) {
        case 0:
            // No input - wait.
            continue;
        case 1:
            // Valid input.
            cpu.set_al(c);
            cpu.set_ah(c); // TODO: scancode
            return;
        default:
            // EOF
            exit(-1);
        }
    }
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
    fd_set rfds;
    struct timeval tout{};

    // Check input on stdin.
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    if (select(1, &rfds, NULL, NULL, &tout) == 1) {
        cpu.set_zf(0);
    } else {
        cpu.set_zf(1);
    }
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
