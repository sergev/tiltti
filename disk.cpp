//
// Disk and floppy for PC i86.
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
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <filesystem>
#include <iostream>

#include "machine.h"

//
// Open binary image as disk.
//
Disk::Disk(const std::string &p, Memory &m, bool wp, unsigned offset)
    : memory(m), path(p), write_permit(wp), file_offset(offset)
{
    // Open file.
    int open_flag   = write_permit ? O_RDWR : O_RDONLY;
    file_descriptor = open(path.c_str(), open_flag);
    if (file_descriptor < 0)
        throw std::runtime_error("Cannot open " + path +
                                 (write_permit ? " for write" : " for read"));

    // Get file size.
    struct stat stat;
    fstat(file_descriptor, &stat);
    size_sectors = stat.st_size / SECTOR_NBYTES;

    // Set geometry.
    if (size_sectors > 800) {
        num_cylinders = 80;
    } else {
        num_cylinders = 40;
    }
    if (size_sectors > 400) {
        num_heads = 2;
    } else {
        num_heads = 1;
    }
    switch (size_sectors) {
    case 80 * 2 * 18: // 1.44M
        num_sectors = 18;
        break;
    case 80 * 2 * 20: // 1.6M
        num_sectors = 20;
        break;
    case 80 * 2 * 9: // 720K
        num_sectors = 9;
        break;
    case 80 * 2 * 10: // 800K
        num_sectors = 10;
        break;
    case 80 * 2 * 36: // 2.88M
        num_sectors = 36;
        break;
    case 80 * 2 * 39: // 3.12M
        num_sectors = 39;
        break;
    case 80 * 2 * 15: // 1.2M
        num_sectors = 15;
        break;
    case 40 * 2 * 9: // 360K
        num_sectors = 9;
        break;
    case 40 * 2 * 8: // 320K
        num_sectors = 8;
        break;
    case 40 * 1 * 8: // 160K single side
        num_sectors = 8;
        break;
    case 40 * 1 * 9: // 180K single side
        num_sectors = 9;
        break;
    default:
        throw std::runtime_error(
            "Unrecognized size of floppy image: " + std::to_string(size_sectors / 2) + " kbytes");
    }
}

//
// Open embedded image as disk.
//
Disk::Disk(const unsigned char data[], Memory &m, unsigned sz, unsigned ncyl, unsigned nhead, unsigned nsect)
    : memory(m), size_sectors(sz), num_cylinders(ncyl), num_heads(nhead), num_sectors(nsect)

{
    embedded_data = data;
}

// Close file in destructor.
Disk::~Disk()
{
    if (!embedded_data) {
        close(file_descriptor);
    }
}

//
// Disk read: transfer data to memory.
//
void Disk::disk_to_memory(unsigned lba, unsigned addr, unsigned nbytes)
{
    if (embedded_data) {
        embedded_to_memory(lba, addr, nbytes);
    } else {
        file_to_memory(lba, addr, nbytes);
    }
}

//
// Disk write: transfer data from memory.
//
void Disk::memory_to_disk(unsigned lba, unsigned addr, unsigned nbytes)
{
    if (embedded_data) {
        throw std::runtime_error("Cannot write embedded image");
    } else {
        memory_to_file(lba, addr, nbytes);
    }
}

//
// Read binary file: transfer data to memory.
//
void Disk::file_to_memory(unsigned lba, unsigned addr, unsigned nbytes)
{
    if (lba >= size_sectors)
        throw std::runtime_error("Sector number exceeds file size");

    unsigned offset_bytes = lba * SECTOR_NBYTES + file_offset;
    if (lseek(file_descriptor, offset_bytes, SEEK_SET) < 0)
        throw std::runtime_error("File seek error");

    Byte *destination = memory.get_ptr(addr);
    int nread         = read(file_descriptor, destination, nbytes);
    if (nread != (int)nbytes) {
        throw std::runtime_error("File read error");
    }
}

//
// Write binary file: transfer data from memory.
//
void Disk::memory_to_file(unsigned lba, unsigned addr, unsigned nbytes)
{
    if (!write_permit)
        throw std::runtime_error("Cannot write to read-only file");

    if (lba >= size_sectors)
        throw std::runtime_error("Sector number exceeds file size");

    unsigned offset_bytes = lba * SECTOR_NBYTES + file_offset;
    if (lseek(file_descriptor, offset_bytes, SEEK_SET) < 0)
        throw std::runtime_error("File seek error");

    const Byte *source = memory.get_ptr(addr);
    int nwrite         = write(file_descriptor, source, nbytes);
    if (nwrite != (int)nbytes) {
        throw std::runtime_error("File write error");
    }
}

//
// Read embedded data: transfer data to memory.
//
void Disk::embedded_to_memory(unsigned lba, unsigned addr, unsigned nbytes)
{
    if (lba >= size_sectors)
        throw std::runtime_error("Sector number exceeds embedded data size");

    unsigned offset_bytes = lba * SECTOR_NBYTES;
    const uint8_t *ptr    = &embedded_data[offset_bytes];
    Byte *destination     = memory.get_ptr(addr);

    memcpy(destination, ptr, nbytes);
}
