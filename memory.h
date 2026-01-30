//
// Main memory for PC i86.
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
#ifndef TILTTI_MEMORY_H
#define TILTTI_MEMORY_H

#include <array>

#include "i86_arch.h"

class Memory {
private:
    // Memory contents.
    std::array<Byte, MEMORY_NBYTES> mem{};

public:
    explicit Memory() = default;
    virtual ~Memory() = default;

    // Store data to memory.
    void store(unsigned addr, Byte val) { mem[addr] = val; }

    // Load data from memory.
    Byte load(unsigned addr) { return mem[addr]; }

    Byte *get_ptr(unsigned addr) { return &mem[addr]; }

    // Dump disk data for debug.
    void dump(unsigned serial_num, unsigned disk_unit, unsigned sector, unsigned addr,
              unsigned nbytes);

    // Cannot copy the Memory object.
    Memory(const Memory &)            = delete;
    Memory &operator=(const Memory &) = delete;
};

#endif // TILTTI_MEMORY_H
