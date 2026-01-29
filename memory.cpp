//
// PC i86 main memory.
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
#include "memory.h"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//
// Backdoor read from memory.
// No tracing.
//
void Memory::read_bytes(Bytes &output, unsigned nbytes, unsigned addr)
{
    output.resize(nbytes);
    memcpy(output.data(), &mem[addr], nbytes * sizeof(Byte));
}

void Memory::read_bytes(Byte output[], unsigned nbytes, unsigned addr)
{
    memcpy(output, &mem[addr], nbytes * sizeof(Byte));
}

void Memory::read_words(Words &output, unsigned nwords, unsigned addr)
{
    output.resize(nwords);
    memcpy(output.data(), &mem[addr], nwords * sizeof(Word));
}

void Memory::read_words(Word output[], unsigned nwords, unsigned addr)
{
    memcpy(output, &mem[addr], nwords * sizeof(Word));
}

//
// Backdoor write to memory.
// No tracing.
//
void Memory::write_bytes(const Bytes &input, unsigned addr)
{
    unsigned nbytes = input.size();
    memcpy(&mem[addr], input.data(), nbytes * sizeof(Byte));
}

void Memory::write_bytes(const Byte input[], unsigned nbytes, unsigned addr)
{
    memcpy(&mem[addr], input, nbytes * sizeof(Byte));
}

void Memory::write_words(const Words &input, unsigned addr)
{
    unsigned nwords = input.size();
    memcpy(&mem[addr], input.data(), nwords * sizeof(Word));
}

void Memory::write_words(const Word input[], unsigned nwords, unsigned addr)
{
    memcpy(&mem[addr], input, nwords * sizeof(Word));
}

//
// Dump block of memory to file.
//
void Memory::dump(unsigned serial_num, unsigned disk_unit, unsigned sector, unsigned addr, unsigned nbytes)
{
    // Create unique filename.
    std::ostringstream buf;
    buf << serial_num << "-";
    buf << "disk" << disk_unit;
    buf << "-sector" << sector;
    buf << ".dump";

    // Open file.
    std::string filename = buf.str();
    std::ofstream out(filename);
    if (!out.is_open())
        throw std::runtime_error("Cannot create " + filename);

    out << "; " << filename << std::endl;
    for (; nbytes >= 16; nbytes -= 16, addr += 16) {
        out << std::hex << std::setfill('0') << std::setw(4) << addr << ' ';
        for (int i = 0; i < 16; i++) {
            out << ' ' << std::setw(2) << (unsigned)mem[i];
        }
        out << std::endl;
    }
}
