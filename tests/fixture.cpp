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
