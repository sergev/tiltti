//
// Disk unit for PC i86.
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
#ifndef TILTTI_DISK_H
#define TILTTI_DISK_H

#include <cstdint>

#include "memory.h"

class Disk {
private:
    // Reference to the main memory.
    Memory &memory;

    // File path.
    std::string path;
    bool write_permit{};
    bool remove_on_close{};
    int file_descriptor{};
    unsigned size_sectors;

    // Skip so many bytes at the beginning of the file.
    unsigned file_offset{};

    // Embedded disk image, read only.
    const unsigned char *embedded_data{};

public:
    // Disk geometry.
    unsigned num_cylinders;
    unsigned num_heads;
    unsigned num_sectors;

    // Constructor throws exception if the file cannot be opened.
    Disk(const std::string &path, Memory &memory, bool write_permit, unsigned offset = 0);
    Disk(const unsigned char data[], Memory &memory, unsigned size_sectors, unsigned ncyl,
         unsigned nhead, unsigned nsect);

    // Clone the disk.
    Disk(const Disk &other);

    // Close file in destructor.
    ~Disk();

    // Data transfer.
    void disk_to_memory(unsigned sector, unsigned addr, unsigned nwords);
    void memory_to_disk(unsigned sector, unsigned addr, unsigned nwords);
    void write_sector_fill(unsigned lba, unsigned n_sectors, uint8_t fill_byte);

    const std::string &get_path() { return path; }

    bool is_writable() const { return write_permit; }

    // Total sectors (for LBA range check in extended INT 13h).
    unsigned get_size_sectors() const { return size_sectors; }

    // Remove this file.bin image when simulation is done.
    void remove_when_finished() { remove_on_close = true; }

private:
    void simh_to_memory(unsigned sector, unsigned addr, unsigned nwords);
    void memory_to_simh(unsigned sector, unsigned addr, unsigned nwords);
    void file_to_memory(unsigned sector, unsigned addr, unsigned nwords);
    void memory_to_file(unsigned sector, unsigned addr, unsigned nwords);
    void embedded_to_memory(unsigned sector, unsigned addr, unsigned nwords);
};

#endif // TILTTI_DISK_H
