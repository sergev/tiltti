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

#include <sys/types.h>

#include <cstdint>
#include <vector>

#include "memory.h"

enum class ImageFormat { Raw, VhdDynamic };

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

    // Embedded disk image, read only.
    const unsigned char *embedded_data{};

    // VHD dynamic disk support (hard disks only).
    bool is_hard_disk{};
    bool is_vhd_dynamic{};
    std::vector<uint32_t> vhd_bat;
    uint32_t vhd_block_size{};
    uint32_t vhd_sectors_per_block{};
    uint64_t vhd_bat_file_offset{};
    uint64_t vhd_next_block_start{}; // File offset where next block will be written
    bool vhd_blocks_allocated{};     // True if we allocated blocks (need footer on close)

public:
    // Disk geometry.
    unsigned num_cylinders;
    unsigned num_heads;
    unsigned num_sectors;

    // Constructor throws exception if the file cannot be opened.
    Disk(const std::string &path, Memory &memory, bool is_hard_disk = false);
    Disk(const std::string &path, Memory &memory, ImageFormat format, unsigned size_sectors);
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

    // VHD dynamic disk methods.
    bool vhd_try_init(off_t file_size);
    void vhd_file_to_memory(unsigned lba, unsigned addr, unsigned nbytes);
    void vhd_memory_to_file(unsigned lba, unsigned addr, unsigned nbytes);
    void vhd_write_sector_zeroes(unsigned lba, unsigned n_sectors);
    bool vhd_lba_to_file_offset(unsigned lba, uint64_t *file_offset) const;
    void vhd_ensure_block_allocated(unsigned block_idx);
    void vhd_update_footer();
    void vhd_create_empty(off_t total_size_bytes);

    // Set disk geometry from sector count. throw_on_unknown_floppy: true for open, false for
    // create.
    void set_geometry(unsigned size_sectors, bool throw_on_unknown_floppy = true);
};

#endif // TILTTI_DISK_H
