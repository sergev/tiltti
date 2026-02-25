# Virtual Hard Disk (VHD) Format

This document describes the **VHD (Virtual Hard Disk)** format, also known as **VPC** (Virtual PC). The format was created by Connectix for Microsoft Virtual PC and acquired by Microsoft in 2003. It is the native format for Hyper-V and is supported by QEMU, VirtualBox, and other virtualization platforms.

The specification is available under the [Microsoft Open Specification Promise](https://www.microsoft.com/en-us/legal/intellectualproperty/protection/overview) since June 2005. The successor format **VHDX** (introduced in Windows 8 Server 2012) supports larger capacities and is not covered here.

## Overview

VHD files use the `.vhd` extension. There are three disk types:

| Type | Value | Description |
|------|-------|-------------|
| Fixed | 2 | Pre-allocated raw image + footer at end |
| Dynamic | 3 | Sparse allocation; grows as data is written |
| Differencing | 4 | Child image storing only modified blocks |

**This implementation supports only dynamic VHD** (type 3). Fixed and differencing are not supported.

All multi-byte values in VHD are **big-endian**.

## Disk Types

### Fixed

- Raw disk image at the start of the file
- 512-byte footer at the end of the file
- File size = virtual disk size + 512

### Dynamic

- File grows as blocks are allocated
- Layout: footer copy → dynamic header → BAT → Block 0 → Block 1 → … → footer
- Unallocated sectors read as zeros

### Differencing

- References a parent image
- Stores only modified blocks
- Not implemented in this codebase

## File Layout (Dynamic VHD)

```
Offset 0        : Footer (512 bytes) — copy at start
Offset 512      : Dynamic header (1024 bytes)
Offset 1536     : Block Allocation Table (BAT)
Offset 1536+N   : BAT padding to 512-byte boundary
Offset 1536+pad : Block 0 (bitmap + data)
                 Block 1 (bitmap + data)
                 ...
Offset EOF-512  : Footer (512 bytes) — canonical copy at end
```

The **footer at the end** is the canonical copy. When the file grows (new blocks allocated), the old footer is overwritten and a new one is written at the new end. The footer at offset 0 is updated to match.

## Hard Disk Footer (512 bytes)

The footer appears at the start (dynamic VHD) and at the end of the file. All values big-endian.

| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0x00 | 8 | Cookie | "conectix" (magic) |
| 0x08 | 4 | Features | 0x02 = no temp file |
| 0x0C | 4 | File format version | 0x00010000 |
| 0x10 | 8 | Data offset | Offset of next header; 512 for dynamic (points to dynamic header) |
| 0x18 | 4 | Timestamp | Seconds since Jan 1, 2000 00:00:00 UTC |
| 0x1C | 4 | Creator application | "vpc " or "qemu" |
| 0x20 | 2 | Creator version (major) | e.g. 0x0005 |
| 0x22 | 2 | Creator version (minor) | e.g. 0x0003 |
| 0x24 | 4 | Creator host OS | "Wi2k" (Windows 2000) |
| 0x28 | 8 | Original size | Virtual disk size in bytes |
| 0x30 | 8 | Current size | Same as original for dynamic |
| 0x38 | 2 | Cylinders | CHS geometry |
| 0x3A | 1 | Heads | CHS geometry |
| 0x3B | 1 | Sectors per track | CHS geometry |
| 0x3C | 4 | Disk type | 2=fixed, 3=dynamic, 4=differencing |
| 0x40 | 4 | Checksum | One's complement of sum of all bytes (checksum field zeroed) |
| 0x44 | 16 | Unique ID | UUID |
| 0x54 | 1 | Saved state | 0 = not saved |
| 0x55 | 427 | Reserved | Padding to 512 bytes |

### Checksum

Zero the checksum field (bytes 0x40–0x43), then sum all 512 bytes. The checksum value is `0xFFFFFFFF - sum` (one's complement).

## Dynamic Disk Header (1024 bytes)

Located at `data_offset` from the footer (typically 512). Magic: `"cxsparse"`.

| Offset | Size | Field | Description |
|--------|------|-------|-------------|
| 0x00 | 8 | Cookie | "cxsparse" |
| 0x08 | 8 | Data offset | 0xFFFFFFFFFFFFFFFF (no next header) |
| 0x10 | 8 | Table offset | File offset of BAT (typically 1536) |
| 0x18 | 4 | Header version | 0x00010000 |
| 0x1C | 4 | Max table entries | Number of BAT entries |
| 0x20 | 4 | Block size | 0x200000 (2 MB) typical |
| 0x24 | 4 | Checksum | One's complement of sum of 1024 bytes |
| 0x28 | 16 | Parent UUID | For differencing; unused for dynamic |
| 0x38 | 4 | Parent timestamp | For differencing |
| 0x3C | 4 | Reserved | 0 |
| 0x40 | 256 | Parent locators | 8 × 32 bytes; for differencing |
| 0x140 | 512 | Parent name | UTF-16; for differencing |

### Block size

Must be a power of two. QEMU and this implementation use **2 MB (0x200000)**. Block size determines:

- Sectors per block: `block_size / 512`
- BAT entries: `ceil(disk_size / block_size)`

## Block Allocation Table (BAT)

- **Location**: `table_offset` from dynamic header (typically 1536)
- **Entry size**: 4 bytes (big-endian)
- **Padding**: BAT size rounded up to 512-byte boundary: `(num_entries * 4 + 511) & ~511`
- **Unallocated**: 0xFFFFFFFF

Each BAT entry is the **sector offset** (in 512-byte sectors) where the block starts in the file. Sector 0 = file offset 0.

## Block layout

Each allocated block:

1. **Bitmap** (512 bytes): One bit per sector. 1 = sector present. For simplicity, implementations often set all bits to 1 when allocating.
2. **Data** (`block_size` bytes): Sector data.

For a 2 MB block:

- Bitmap size: `ceil(block_size / (8 * 512))` rounded to 512 = 512 bytes
- Data: 2 MB

Sector offset within block = `BAT_entry * 512 + 512 + sector_in_block * 512` (bitmap is first sector).

## Next block position

When allocating a new block:

1. **Initial** (empty image): `next_block_start = table_offset + bat_size`
2. **After allocation**: `next_block_start += 512 + block_size`
3. The footer at EOF is overwritten; a new footer is written at `next_block_start` after the new block.

This follows the **DiscUtils** pattern: new blocks are written at the end, overwriting the footer; the footer is then written at the new end.

## QEMU implementation notes

From `block/vpc.c`:

- **Table offset**: 1536 (3 × 512)
- **Block size**: 0x200000 (2 MB)
- **BAT size**: `(num_bat_entries * 4 + 511) & ~511`
- **free_data_block_offset**: `(bat_offset + max_table_entries * 4 + 511) & ~511` initially
- **Geometry**: QEMU uses `calculate_geometry()` for CHS; common values: 16 heads, 63 sectors
- **Create order**: QEMU writes footer at 0, seeks to BAT end, writes footer copy, then BAT, then dynamic header at 512

## Detection

To detect a VHD file:

1. Read last 512 bytes; check for "conectix" cookie
2. If invalid, try first 512 bytes (fallback for truncated or dynamic)
3. Verify checksum
4. Check disk type = 3 for dynamic

## Limitations

- **Capacity**: ~2 TB (2040 GB) due to 32-bit sector offset in BAT
- **CHS**: C×H×S formula allows up to 65535×16×255 sectors
- **Fixed/differencing**: Not supported in this implementation

## References

- [Virtual Hard Disk Image Format Specification](https://go.microsoft.com/fwlink/p/?linkid=137171) (Microsoft)
- [VHD (file format) - Wikipedia](https://en.wikipedia.org/wiki/VHD_(file_format))
- [QEMU block/vpc.c](https://github.com/qemu/qemu/blob/master/block/vpc.c)
- [DiscUtils](https://github.com/DiscUtils/DiscUtils) — .NET implementation
