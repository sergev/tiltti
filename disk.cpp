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

#include <cerrno>
#include <cstring>
#include <filesystem>
#include <iostream>

#include "machine.h"
#include "pc86_arch.h"

//
// Open binary image as disk.
//
Disk::Disk(const std::string &p, Memory &m, bool hard_disk) : memory(m), path(p), is_hard_disk(hard_disk)
{
    // Try to open for read/write.
    file_descriptor = open(path.c_str(), O_RDWR);
    if (file_descriptor >= 0) {
        write_permit = true;
    } else {
        write_permit    = false;
        file_descriptor = open(path.c_str(), O_RDONLY);
        if (file_descriptor < 0) {
            throw std::runtime_error("Cannot open " + path);
        }
    }

    struct stat st;
    fstat(file_descriptor, &st);
    const off_t file_size = st.st_size;

    if (!is_hard_disk) {
        // Floppy: always raw.
        size_sectors = file_size / SECTOR_NBYTES;
    } else {
        // Hard disk: attempt VHD detection.
        if (file_size < 512) {
            throw std::runtime_error("Bad size of disk image " + path);
        } else if (vhd_try_init(file_size)) {
            // VHD initialized; size_sectors and vhd_* set by vhd_try_init
        } else {
            size_sectors = file_size / SECTOR_NBYTES;
        }
    }

    set_geometry(size_sectors, true);
}

//
// Create fresh image from scratch. For unit tests.
//
Disk::Disk(const std::string &p, Memory &m, ImageFormat format, unsigned sz)
    : memory(m), path(p), write_permit(true), size_sectors(sz), is_hard_disk(format == ImageFormat::VhdDynamic)
{
    file_descriptor = open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0600);
    if (file_descriptor < 0) {
        throw std::runtime_error("Cannot create " + path);
    }

    if (format == ImageFormat::Raw) {
        if (ftruncate(file_descriptor, (off_t)sz * SECTOR_NBYTES) < 0) {
            close(file_descriptor);
            throw std::runtime_error("Cannot truncate " + path);
        }
        is_vhd_dynamic = false;
    } else {
        vhd_create_empty((off_t)sz * SECTOR_NBYTES);
    }

    set_geometry(sz, false);
}

//
// Open embedded image as disk.
//
Disk::Disk(const unsigned char data[], Memory &m, unsigned sz, unsigned ncyl, unsigned nhead,
           unsigned nsect)
    : memory(m), size_sectors(sz), num_cylinders(ncyl), num_heads(nhead), num_sectors(nsect)

{
    embedded_data = data;
}

//
// Set disk geometry from sector count.
// throw_on_unknown_floppy: true when opening existing file; false when creating (use IDE fallback).
//
void Disk::set_geometry(unsigned sz, bool throw_on_unknown_floppy)
{
    const unsigned max_floppy_sectors = 80 * 2 * 36; // 2.88M
    if (is_hard_disk) {
        num_heads     = 16;
        num_sectors   = 63;
        num_cylinders = sz / (num_heads * num_sectors);
        if (num_cylinders == 0 && sz > 0)
            num_cylinders = 1;
        if (num_cylinders > 1024)
            num_cylinders = 1024;
    } else if (sz <= max_floppy_sectors) {
        if (sz > 800) {
            num_cylinders = 80;
        } else {
            num_cylinders = 40;
        }
        if (sz > 400) {
            num_heads = 2;
        } else {
            num_heads = 1;
        }
        switch (sz) {
        case 80 * 2 * 18:
            num_sectors = 18;
            break;
        case 80 * 2 * 20:
            num_sectors = 20;
            break;
        case 80 * 2 * 9:
            num_sectors = 9;
            break;
        case 80 * 2 * 10:
            num_sectors = 10;
            break;
        case 80 * 2 * 36:
            num_sectors = 36;
            break;
        case 80 * 2 * 39:
            num_sectors = 39;
            break;
        case 80 * 2 * 15:
            num_sectors = 15;
            break;
        case 40 * 2 * 9:
            num_sectors = 9;
            break;
        case 40 * 2 * 8:
            num_sectors = 8;
            break;
        case 40 * 1 * 8:
            num_sectors = 8;
            break;
        case 40 * 1 * 9:
            num_sectors = 9;
            break;
        default:
            if (throw_on_unknown_floppy) {
                throw std::runtime_error("Unrecognized size of floppy image: " +
                                         std::to_string(sz / 2) + " kbytes");
            }
            num_heads     = 16;
            num_sectors   = 63;
            num_cylinders = sz / (num_heads * num_sectors);
            if (num_cylinders > 1024)
                num_cylinders = 1024;
        }
    } else {
        num_heads     = 16;
        num_sectors   = 63;
        num_cylinders = sz / (num_heads * num_sectors);
        if (num_cylinders > 1024)
            num_cylinders = 1024;
    }
}

// Close file in destructor.
Disk::~Disk()
{
    if (!embedded_data) {
        if (is_vhd_dynamic && write_permit) {
            vhd_update_footer();
        }
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

    if (is_vhd_dynamic) {
        vhd_file_to_memory(lba, addr, nbytes);
        return;
    }

    unsigned offset_bytes = lba * SECTOR_NBYTES;
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

    if (is_vhd_dynamic) {
        vhd_memory_to_file(lba, addr, nbytes);
        return;
    }

    unsigned offset_bytes = lba * SECTOR_NBYTES;
    if (lseek(file_descriptor, offset_bytes, SEEK_SET) < 0)
        throw std::runtime_error("File seek error");

    const Byte *source = memory.get_ptr(addr);
    int nwrite         = write(file_descriptor, source, nbytes);
    if (nwrite != (int)nbytes) {
        throw std::runtime_error("File write error");
    }
}

//
// Write sectors filled with a single byte (e.g. for format track).
// Floppies: write fill_byte. Hard disks: write zeros only to allocated blocks (VHD: skip unallocated).
//
void Disk::write_sector_fill(unsigned lba, unsigned n_sectors, uint8_t fill_byte)
{
    if (embedded_data) {
        throw std::runtime_error("Cannot write embedded image");
    }
    if (!write_permit) {
        throw std::runtime_error("Cannot write to read-only file");
    }
    if (lba + n_sectors > size_sectors) {
        throw std::runtime_error("Sector range exceeds disk");
    }

    if (is_vhd_dynamic) {
        // Always write zeroes to VHD.
        vhd_write_sector_zeroes(lba, n_sectors);
        return;
    }

    uint8_t buf[SECTOR_NBYTES]{};
    if (!is_hard_disk) {
        // Always write zeroes to hard disks.
        memset(buf, fill_byte, sizeof(buf));
    }

    for (unsigned i = 0; i < n_sectors; ++i) {
        const unsigned sector_lba = lba + i;
        unsigned offset_bytes     = sector_lba * SECTOR_NBYTES;

        if (lseek(file_descriptor, offset_bytes, SEEK_SET) < 0)
            throw std::runtime_error("File seek error");

        if (write(file_descriptor, buf, SECTOR_NBYTES) != (ssize_t)SECTOR_NBYTES)
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
