//
// i86 architecture details.
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
#ifndef TILTTI_I86_ARCH_H
#define TILTTI_I86_ARCH_H

#include <cstdint>
#include <ostream>
#include <vector>

//
// Size of disk sector.
//
static const unsigned SECTOR_NBYTES = 512;

//
// Memory size 1 Mbyte.
//
static const unsigned MEMORY_NBYTES = 1024 * 1024;

//
// Total 8 hard+floppy disks.
//
static const unsigned NDISKS = 8;

//
// 8-bit unsigned byte.
// 16-bit memory word.
//
using Byte = uint8_t;
using Word = uint16_t;

//
// Array of bytes.
// Array of words.
//
using Bytes = std::vector<Byte>;
using Words = std::vector<Word>;

//
// Convert numbers to strings.
//
std::string to_hex(unsigned val);

//
// Bits of memory word, from right to left, starting from 1.
//
#define ONEBIT(n)      (1U << (n))                   // single bit, from 0 до 31
#define BITS(n)        ((uint32_t)~0U >> (31 - (n))) // bit mask n..0
#define FIELD(x, n, w) (((x) >> (n)) & BITS(w))      // field of w bits, starting from bit n

#endif // TILTTI_I86_ARCH_H
