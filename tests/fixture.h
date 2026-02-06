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

    // Boot sector load address.
    static const unsigned BOOT_ADDR = 0x7c00;

    void SetUp() override
    {
        // Show trace.
        Machine::enable_trace("r");
    }

    std::string show_flags(unsigned expect);
};

//
// Get current test name, as specified in TEST() macro.
//
std::string get_test_name();

#endif // TILTTI_TESTS_UTIL_H
