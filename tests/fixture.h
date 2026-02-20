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
#ifndef TILTTI_TESTS_UTIL_H
#define TILTTI_TESTS_UTIL_H

#include <gtest/gtest.h>

#include <string>

#include "machine.h"

//
// Fixture with preallocated machine.
//
// For details, see: https://github.com/google/googletest/blob/main/docs/primer.md
//
class MachineTest : public ::testing::Test {
protected:
    Memory memory;
    Machine machine{ memory };
    Processor &cpu{ machine.cpu };

    // To be typed on keyboard.
    std::string input_buf;
    unsigned input_index{};

    // Boot sector load address.
    static const unsigned BOOT_ADDR = 0x7c00;

    void SetUp() override
    {
        // Push keystrokes into the keyboard queue.
        // Throw exception when no more input.
        auto event_callback = [this](unsigned timeout) {
            if (timeout == 0)
                return;
            if (input_index < input_buf.size()) {
                machine.push_keystroke(input_buf[input_index++]);
                return;
            }
            throw std::runtime_error("Complete");
        };
        machine.set_event_callback(event_callback);

        // Show trace.
        //Machine::enable_trace("r");
    }

    // Run until all input is processed.
    void run(const std::string &input);

    // Compare FLAGS register to expected value and
    // return a list of names of changed flags.
    std::string show_flags(unsigned expect);

    // Get contents of one line from the screen.
    std::string get_line(unsigned row);

    // Get cursor row/column.
    unsigned cursor_row() { return machine.bda.cursor_pos[machine.bda.video_page & 7] >> 8; }
    unsigned cursor_col() { return machine.bda.cursor_pos[machine.bda.video_page & 7] & 0xff; }
};

//
// Compare flags, ignoring unpredictable bits.
//
#define EXPECT_FLAGS(val) \
    EXPECT_EQ(cpu.get_flags() & ~cpu.u_flags(), val & ~cpu.u_flags()) << show_flags(val)
#define EXPECT_FLAGS_LO(addr, val) \
    EXPECT_EQ(memory.load8(addr) & ~cpu.u_flags(), val & ~cpu.u_flags())
#define EXPECT_FLAGS_HI(addr, val) \
    EXPECT_EQ(memory.load8(addr) & ~(cpu.u_flags() >> 8), val & ~(cpu.u_flags() >> 8))

//
// Get current test name, as specified in TEST() macro.
//
std::string get_test_name();

#endif // TILTTI_TESTS_UTIL_H
