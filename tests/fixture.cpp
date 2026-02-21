//
// Utility routines for unit tests.
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
#include "fixture.h"

#include <cstring>
#include <fstream>

void MachineTest::SetUp()
{
    // Push keystrokes into the keyboard queue.
    // Throw exception when no more input.
    auto event_callback = [this](unsigned timeout) {
        if (machine.has_keystroke()) {
            return;
        }
        if (timeout == 0) {
            // Keyboard poll.
            if (machine.kbd_poll_count < 10) {
                return;
            }
            // Too many polls - send keystroke.
            machine.kbd_poll_count = 0;
        }
        if (input_index < input_buf.size()) {
            // Map ASCII to BIOS keystroke.
            auto keycode = to_bios(input_buf[input_index++]);
            machine.push_keystroke(keycode);
            return;
        }
        throw std::runtime_error("Complete");
    };
    machine.set_event_callback(event_callback);

    // Show trace.
    //Machine::enable_trace("s");
}

//
// Run until all input is processed.
//
void MachineTest::run(const std::string &input)
{
    input_buf = input;
    input_index = 0;

    try {
        for (;;) {
            machine.run_batch(50000);
        }
    } catch (const std::exception &ex) {
        ASSERT_STREQ(ex.what(), "Complete");
    }
}

//
// Compare FLAGS register to expected value and
// return a list of names of changed flags.
//
std::string MachineTest::show_flags(unsigned expect)
{
    unsigned changes = cpu.get_flags() ^ expect;
    if (!changes)
        return "";

    std::string result = "Mismatch:";
    if (changes & 0x800)
        result += " OF";
    if (changes & 0x400)
        result += " DF";
    if (changes & 0x200)
        result += " IF";
    if (changes & 0x100)
        result += " TF";
    if (changes & 0x80)
        result += " SF";
    if (changes & 0x40)
        result += " ZF";
    if (changes & 0x10)
        result += " AF";
    if (changes & 0x4)
        result += " PF";
    if (changes & 0x1)
        result += " CF";

    return result;
}

//
// Get current test name, as specified in TEST() macro.
//
std::string get_test_name()
{
    std::string name = ::testing::UnitTest::GetInstance()->current_test_info()->name();

    // Remove the '/1' suffix.
    auto pos = name.find_last_of('/');
    if (pos != std::string::npos)
        name.erase(pos);

    return name;
}

//
// Get contents of one line from the screen.
//
std::string MachineTest::get_line(unsigned row)
{
    std::string result;
    auto p = machine.get_video_refresh_params();
    auto *line = &p.text_buf[row * 160];

    for (int i = 0; i < 160; i += 2) {
        char ch = line[i];
        if (ch == 0) {
            // Stop on NUL.
            return result;
        }
        result += ch;
    }

    // Trim spaces.
    const auto pos = result.find_last_not_of(' ');
    if (pos == std::string::npos) {
        // All spaces.
        return "";
    }
    result.erase(pos + 1);
    return result;
}

//
// Map ASCII byte to BIOS keystroke.
//
unsigned MachineTest::to_bios(uint8_t ch)
{
    switch (ch) {
    case 0201: return 0x3B00; // F1
    case 0202: return 0x3C00; // F2
    case 0203: return 0x3D00; // F3
    case 0204: return 0x3E00; // F4
    case 0205: return 0x3F00; // F5
    case 0206: return 0x4000; // F6
    case 0207: return 0x4100; // F7
    case 0210: return 0x4200; // F8
    case 0211: return 0x4300; // F9
    case 0212: return 0x4400; // F10
    case 0213: return 0x4500; // F11
    case 0214: return 0x4600; // F12
    default:
        return ch;
    }
}
