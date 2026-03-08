//
// PC i86 architecture details.
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
// Memory size 16 Mbytes.
//
static const unsigned MEMORY_NBYTES = 16 * 1024 * 1024;

//
// Total 4 hard+floppy disks.
//
static const unsigned NDISKS = 4;
enum {
    FLOPPY_A = 0,
    FLOPPY_B = 1,
    DISK_C   = 2,
    DISK_D   = 3,
};

//
// 8-bit unsigned byte.
// 16-bit memory word.
// 32-bit doubleword.
// 64-bit quadword.
//
using Byte  = uint8_t;
using Word  = uint16_t;
using Dword = uint32_t;
using Qword = uint64_t;

//
// Array of bytes.
// Array of words.
//
using Bytes = std::vector<Byte>;
using Words = std::vector<Word>;

//
// Real-mode linear address from segment:offset.
//
inline unsigned linear_addr20(Word seg, Word off)
{
    return ((seg << 4) + off) & 0xFFFFFu;
}

inline unsigned linear_addr21(Word seg, Word off)
{
    return (seg << 4) + off;
}

inline unsigned linear_addr32(Word seg, Dword off)
{
    return (seg << 4) + off;
}

//
// Convert numbers to strings.
//
std::string to_hex(unsigned val);

//
// Definition for common 16bit segment/offset pointers.
//
struct Seg_Off {
    union {
        struct {
            uint16_t offset;
            uint16_t seg;
        };
        uint32_t segoff;
    };
};

//
// Interrupt vector table
//
struct Interrupt_Vector_Table {
    Seg_Off ivec[256];
};

#endif // TILTTI_I86_ARCH_H
