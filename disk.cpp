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
// Read big-endian 32-bit value.
//
static uint32_t read_be32(const uint8_t *p)
{
    return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3];
}

//
// Read big-endian 64-bit value.
//
static uint64_t read_be64(const uint8_t *p)
{
    return (uint64_t)read_be32(p) << 32 | read_be32(p + 4);
}

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

    // Set geometry. Hard disks always use IDE geometry; floppies use size-based lookup.
    const unsigned max_floppy_sectors = 80 * 2 * 36; // 2.88M
    if (is_hard_disk) {
        num_heads     = 16;
        num_sectors   = 63;
        num_cylinders = size_sectors / (num_heads * num_sectors);
        if (num_cylinders == 0 && size_sectors > 0)
            num_cylinders = 1;
        if (num_cylinders > 1024)
            num_cylinders = 1024;
    } else if (size_sectors <= max_floppy_sectors) {
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
            throw std::runtime_error("Unrecognized size of floppy image: " +
                                     std::to_string(size_sectors / 2) + " kbytes");
        }
    } else {
        num_heads     = 16;
        num_sectors   = 63;
        num_cylinders = size_sectors / (num_heads * num_sectors);
        if (num_cylinders > 1024)
            num_cylinders = 1024;
    }
}

//
// Attempt to detect and initialize dynamic VHD. Returns true if VHD was detected and initialized.
// Follows DiscUtils: read footer from end first, fallback to offset 0 if invalid.
//
bool Disk::vhd_try_init(off_t file_size)
{
    uint8_t footer[512];
    bool footer_valid = false;

    if (lseek(file_descriptor, file_size - 512, SEEK_SET) >= 0 &&
        read(file_descriptor, footer, sizeof(footer)) == (ssize_t)sizeof(footer) &&
        memcmp(footer, "conectix", 8) == 0) {
        footer_valid = true;
    }
    if (!footer_valid) {
        if (lseek(file_descriptor, 0, SEEK_SET) < 0 ||
            read(file_descriptor, footer, sizeof(footer)) != (ssize_t)sizeof(footer) ||
            memcmp(footer, "conectix", 8) != 0) {
            return false;
        }
    }

    // VHD footer found. Disk type at offset 0x3C (4 bytes BE).
    const uint32_t disk_type = read_be32(footer + 0x3C);
    if (disk_type != 3) {
        throw std::runtime_error("Fixed/differencing VHD not supported; only dynamic VHD");
    }
    is_vhd_dynamic     = true;
    size_sectors       = read_be64(footer + 0x28) / SECTOR_NBYTES;
    const uint64_t data_offset = read_be64(footer + 0x10);

    // Dynamic header at data_offset. Layout per spec: TableOffset@0x10, Version@0x18,
    // MaxTableEntries@0x1C, BlockSize@0x20.
    uint8_t dyn_header[1024];
    if (lseek(file_descriptor, data_offset, SEEK_SET) < 0 ||
        read(file_descriptor, dyn_header, sizeof(dyn_header)) != (ssize_t)sizeof(dyn_header) ||
        memcmp(dyn_header, "cxsparse", 8) != 0) {
        throw std::runtime_error("Invalid dynamic VHD header");
    }
    vhd_bat_file_offset   = read_be64(dyn_header + 0x10);
    vhd_block_size        = read_be32(dyn_header + 0x20);
    const uint32_t max_entries = read_be32(dyn_header + 0x1C);
    vhd_sectors_per_block = vhd_block_size / SECTOR_NBYTES;

    vhd_bat.resize(max_entries);
    if (lseek(file_descriptor, vhd_bat_file_offset, SEEK_SET) < 0) {
        throw std::runtime_error("Cannot seek to VHD BAT");
    }
    for (uint32_t i = 0; i < max_entries; ++i) {
        uint8_t entry[4];
        if (read(file_descriptor, entry, 4) != 4) {
            throw std::runtime_error("Cannot read VHD BAT");
        }
        vhd_bat[i] = read_be32(entry);
    }

    // DiscUtils: next block goes at (file_size - 512), overwriting the footer.
    vhd_next_block_start = file_size - 512;
    return true;
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
// VHD: read binary file to memory.
//
void Disk::vhd_file_to_memory(unsigned lba, unsigned addr, unsigned nbytes)
{
    Byte *dest = memory.get_ptr(addr);
    for (unsigned off = 0; off < nbytes; off += SECTOR_NBYTES) {
        uint64_t file_offset;
        if (vhd_lba_to_file_offset(lba + off / SECTOR_NBYTES, &file_offset)) {
            if (lseek(file_descriptor, file_offset, SEEK_SET) < 0)
                throw std::runtime_error("File seek error");
            if (read(file_descriptor, dest + off, SECTOR_NBYTES) != (ssize_t)SECTOR_NBYTES)
                throw std::runtime_error("File read error");
        } else {
            memset(dest + off, 0, SECTOR_NBYTES);
        }
    }
}

//
// VHD: write binary file from memory.
//
void Disk::vhd_memory_to_file(unsigned lba, unsigned addr, unsigned nbytes)
{
    const Byte *src = memory.get_ptr(addr);
    for (unsigned off = 0; off < nbytes; off += SECTOR_NBYTES) {
        const unsigned sector_lba = lba + off / SECTOR_NBYTES;
        const unsigned block_idx  = sector_lba / vhd_sectors_per_block;
        vhd_ensure_block_allocated(block_idx);
        uint64_t file_offset;
        if (!vhd_lba_to_file_offset(sector_lba, &file_offset))
            throw std::runtime_error("VHD block allocation failed");
        if (lseek(file_descriptor, file_offset, SEEK_SET) < 0)
            throw std::runtime_error("File seek error");
        if (write(file_descriptor, src + off, SECTOR_NBYTES) != (ssize_t)SECTOR_NBYTES)
            throw std::runtime_error("File write error");
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
// VHD: write sectors filled with a single byte. Skips unallocated blocks.
//
void Disk::vhd_write_sector_zeroes(unsigned lba, unsigned n_sectors)
{
    // Always write zeroes to VHD.
    uint8_t buf[SECTOR_NBYTES]{};

    for (unsigned i = 0; i < n_sectors; ++i) {
        const unsigned sector_lba = lba + i;
        uint64_t file_offset;

        if (!vhd_lba_to_file_offset(sector_lba, &file_offset))
            continue; // Skip unallocated block

        if (lseek(file_descriptor, file_offset, SEEK_SET) < 0)
            throw std::runtime_error("File seek error");

        if (write(file_descriptor, buf, SECTOR_NBYTES) != (ssize_t)SECTOR_NBYTES)
            throw std::runtime_error("File write error");
    }
}

//
// Map LBA to file offset for VHD. Returns true if block is allocated.
//
bool Disk::vhd_lba_to_file_offset(unsigned lba, uint64_t *file_offset) const
{
    const unsigned block_idx      = lba / vhd_sectors_per_block;
    const unsigned sector_in_block = lba % vhd_sectors_per_block;
    if (block_idx >= vhd_bat.size() || vhd_bat[block_idx] == 0xFFFFFFFF)
        return false;
    *file_offset = (uint64_t)vhd_bat[block_idx] * SECTOR_NBYTES + SECTOR_NBYTES + sector_in_block * SECTOR_NBYTES;
    return true;
}

//
// Write big-endian 32-bit value.
//
static void write_be32(uint8_t *p, uint32_t val)
{
    p[0] = (val >> 24) & 0xFF;
    p[1] = (val >> 16) & 0xFF;
    p[2] = (val >> 8) & 0xFF;
    p[3] = val & 0xFF;
}

//
// VHD: allocate a new block and update BAT.
// DiscUtils pattern: write block at vhd_next_block_start, then append footer.
//
void Disk::vhd_ensure_block_allocated(unsigned block_idx)
{
    if (block_idx >= vhd_bat.size() || vhd_bat[block_idx] != 0xFFFFFFFF)
        return;

    const uint64_t pos = vhd_next_block_start;

    // Write block: 512-byte bitmap (all 0xFF) + block_size zeros.
    uint8_t bitmap[SECTOR_NBYTES];
    memset(bitmap, 0xFF, sizeof(bitmap));
    if (lseek(file_descriptor, pos, SEEK_SET) < 0 ||
        write(file_descriptor, bitmap, sizeof(bitmap)) != (ssize_t)sizeof(bitmap))
        throw std::runtime_error("VHD block allocation failed");

    // Write block_size zeros in chunks.
    uint8_t zeros[4096];
    memset(zeros, 0, sizeof(zeros));
    for (uint32_t remain = vhd_block_size; remain > 0;) {
        size_t chunk = (remain < sizeof(zeros)) ? remain : sizeof(zeros);
        if (write(file_descriptor, zeros, chunk) != (ssize_t)chunk)
            throw std::runtime_error("VHD block allocation failed");
        remain -= chunk;
    }

    vhd_next_block_start = pos + SECTOR_NBYTES + vhd_block_size;
    vhd_blocks_allocated = true;

    const uint32_t new_sector_offset = pos / SECTOR_NBYTES;
    vhd_bat[block_idx]               = new_sector_offset;

    // Update BAT on disk.
    uint8_t entry[4];
    write_be32(entry, new_sector_offset);
    if (lseek(file_descriptor, vhd_bat_file_offset + block_idx * 4, SEEK_SET) < 0 ||
        write(file_descriptor, entry, 4) != 4)
        throw std::runtime_error("VHD BAT update failed");

    // Append footer at end (DiscUtils: seek to nextBlockStart, write footer).
    uint8_t footer[512];
    if (lseek(file_descriptor, 0, SEEK_SET) < 0 ||
        read(file_descriptor, footer, sizeof(footer)) != (ssize_t)sizeof(footer))
        throw std::runtime_error("VHD footer read failed");

    footer[0x40] = footer[0x41] = footer[0x42] = footer[0x43] = 0;
    uint32_t sum = 0;
    for (size_t i = 0; i < sizeof(footer); ++i)
        sum += footer[i];
    write_be32(footer + 0x40, 0xFFFFFFFF - sum);

    if (lseek(file_descriptor, vhd_next_block_start, SEEK_SET) < 0 ||
        write(file_descriptor, footer, sizeof(footer)) != (ssize_t)sizeof(footer))
        throw std::runtime_error("VHD footer write failed");

    // Update footer copy at offset 0 (spec: both copies must match).
    if (lseek(file_descriptor, 0, SEEK_SET) < 0 ||
        write(file_descriptor, footer, sizeof(footer)) != (ssize_t)sizeof(footer))
        throw std::runtime_error("VHD footer copy update failed");
}

//
// VHD: write footer at end before close. Called from destructor.
//
void Disk::vhd_update_footer()
{
    if (!vhd_blocks_allocated)
        return;

    uint8_t footer[512];
    if (lseek(file_descriptor, 0, SEEK_SET) < 0 ||
        read(file_descriptor, footer, sizeof(footer)) != (ssize_t)sizeof(footer))
        return;

    footer[0x40] = footer[0x41] = footer[0x42] = footer[0x43] = 0;
    uint32_t sum = 0;
    for (size_t i = 0; i < sizeof(footer); ++i)
        sum += footer[i];
    write_be32(footer + 0x40, 0xFFFFFFFF - sum);

    if (lseek(file_descriptor, vhd_next_block_start, SEEK_SET) >= 0 &&
        write(file_descriptor, footer, sizeof(footer)) == (ssize_t)sizeof(footer)) {
        lseek(file_descriptor, 0, SEEK_SET);
        write(file_descriptor, footer, sizeof(footer));
        fsync(file_descriptor);
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
