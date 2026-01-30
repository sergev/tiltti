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
    num_sectors = stat.st_size / SECTOR_NBYTES;
}

//
// Open embedded image as disk.
//
Disk::Disk(const unsigned char data[], Memory &m, unsigned ns) : memory(m), num_sectors(ns)
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
void Disk::disk_to_memory(unsigned sector, unsigned addr, unsigned nbytes)
{
    if (embedded_data) {
        embedded_to_memory(sector, addr, nbytes);
    } else {
        file_to_memory(sector, addr, nbytes);
    }
}

//
// Disk write: transfer data from memory.
//
void Disk::memory_to_disk(unsigned sector, unsigned addr, unsigned nbytes)
{
    if (embedded_data) {
        throw std::runtime_error("Cannot write embedded image");
    } else {
        memory_to_file(sector, addr, nbytes);
    }
}

//
// Read binary file: transfer data to memory.
//
void Disk::file_to_memory(unsigned sector, unsigned addr, unsigned nbytes)
{
    if (sector >= num_sectors)
        throw std::runtime_error("Sector number exceeds file size");

    unsigned offset_bytes = sector * SECTOR_NBYTES + file_offset;
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
void Disk::memory_to_file(unsigned sector, unsigned addr, unsigned nbytes)
{
    if (!write_permit)
        throw std::runtime_error("Cannot write to read-only file");

    if (sector >= num_sectors)
        throw std::runtime_error("Sector number exceeds file size");

    unsigned offset_bytes = sector * SECTOR_NBYTES + file_offset;
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
void Disk::embedded_to_memory(unsigned sector, unsigned addr, unsigned nbytes)
{
    if (sector >= num_sectors)
        throw std::runtime_error("Sector number exceeds embedded data size");

    unsigned offset_bytes = sector * SECTOR_NBYTES;
    const uint8_t *ptr    = &embedded_data[offset_bytes];
    Byte *destination     = memory.get_ptr(addr);

    memcpy(destination, ptr, nbytes);
}
