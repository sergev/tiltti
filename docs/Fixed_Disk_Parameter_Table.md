# Fixed Disk Parameter Table

The Fixed Disk Parameter Table (FDPT) is a 16-byte structure that defines hard disk geometry and controller parameters for ATA/IDE drives. Interrupt vectors **0x41** and **0x46** are **not interrupt handlers** but far pointers to the FDPT for hard disk 0 and hard disk 1 respectively.

The structure is defined in `src/std/disk.h` as `struct fdpt_s`. SeaBIOS stores FDPTs in the Extended BIOS Data Area (EBDA) at `fdpt[0]` and `fdpt[1]`, and sets IVT 0x41 and 0x46 to point there.

## Table Locations

| Drive | IVT Vector | Pointer Target | EBDA Offset |
|-------|------------|----------------|-------------|
| Hard disk 0 | 0x41 | fdpt[0] | 0x3d |
| Hard disk 1 | 0x46 | fdpt[1] | 0x5d |

- **EBDA**: `struct extended_bios_data_area_s` in `src/std/bda.h`; `fdpt[2]` at offset 0x3d
- **Legacy**: `OldFDPT` at F000:E401 (`src/misc.c`) — fixed ROM location for IBM PC/AT compatibility; SeaBIOS does not populate it (new tables are in EBDA)

## struct fdpt_s (16 bytes)

Layout and IBM PC/AT compatibility:

| Offset | Field | Type | IBM PC/AT | SeaBIOS Init | Purpose |
|--------|-------|------|-----------|--------------|---------|
| 0 | cylinders | u16 | 00h | nlc | Logical cylinders (INT 13h geometry) |
| 2 | heads | u8 | 02h | nlh | Logical heads |
| 3 | a0h_signature | u8 | (03h) | 0xa0 when translated | Phoenix extension: 0xa0 = translated FDPT present |
| 4 | phys_sectors | u8 | (04h) | nps when translated | Physical sectors per track |
| 5 | precompensation | u16 | 05h | 0xffff | Write precompensation cylinder; 0xffff = disable |
| 7 | reserved | u8 | 07h | 0 | Reserved; XT ECC burst (0 for AT) |
| 8 | drive_control_byte | u8 | 08h | 0xc0 \| (nph>8)<<3 | AT control: bit 3 = >8 heads |
| 9 | phys_cylinders | u16 | (09h) | npc when translated | Physical cylinders |
| 11 | phys_heads | u8 | (0Bh) | nph when translated | Physical heads |
| 12 | landing_zone | u16 | 0Ch | npc | Cylinder for head parking |
| 14 | sectors | u8 | 0Eh | nls | Sectors per track (logical) |
| 15 | checksum | u8 | 0Fh | computed when translated | Byte sum of table = 0 (Phoenix extension) |

### Field Details

**cylinders** — Logical cylinder count used by INT 13h. Populated from `drive->lchs.cylinder` (logical CHS after translation). Used by OS and BIOS for CHS addressing.

**heads** — Logical head count. Populated from `drive->lchs.head`.

**sectors** — Logical sectors per track. Populated from `drive->lchs.sector`.

**a0h_signature** — Phoenix extension. Set to 0xa0 when logical geometry differs from physical (translation present). Software can detect a translated FDPT by checking this byte. When no translation, remains 0 (EBDA zero-initialized).

**phys_sectors, phys_cylinders, phys_heads** — Physical disk geometry. Set only when translation is present (`nlc != npc || nlh != nph || nls != nps`). Used by operating systems that access the disk directly (e.g. Xenix, NetWare) without going through INT 13h.

**precompensation** — Starting cylinder for write precompensation. SeaBIOS always sets 0xffff (disabled). On older drives, lower cylinders required precompensation; 0xffff indicates none.

**reserved** — Reserved; corresponds to XT "maximum ECC burst length" (0 for AT). SeaBIOS leaves it at 0.

**drive_control_byte** — AT control byte. SeaBIOS sets base 0xc0 (bits 6–7: disable ECC retries, disable access retries); bit 3 is set if physical heads > 8.

**landing_zone** — Cylinder number for head parking. SeaBIOS sets to physical cylinder count `npc`.

**checksum** — When translation is present: `checksum -= checksum(fdpt, sizeof(*fdpt))` so the sum of all bytes in the table equals 0. Validates the Phoenix-style extended table.

## IBM PC/AT Compatibility

The base layout (cylinders, heads, precompensation, control, landing_zone, sectors) matches the IBM PC/AT FDPT. Bytes 3–4, 9–11, and 15 are repurposed for the Phoenix translated extension. When no translation is present, those bytes remain zero; standard software reading cylinders, heads, sectors, and landing_zone obtains correct values.

## Initialization

**fill_fdpt()** in `src/block.c`:

1. Called from `map_hd_drive()` when each hard drive is registered
2. Only runs for `hdid` 0 and 1 (first two drives)
3. Reads `drive->lchs` (logical CHS) and `drive->pchs` (physical CHS) after `setup_translation()` has been run
4. Sets base fields; if translation is present, sets phys_cylinders, phys_heads, phys_sectors, a0h_signature, and checksum
5. Sets IVT 0x41 (hdid=0) or 0x46 (hdid=1) to `SEGOFF(ebda_seg, offsetof(..., fdpt[hdid]))`

EBDA is zero-initialized in `bda_init()` before `block_setup()` runs.

## Usage in SeaBIOS

- **INT 13h**: Uses `getLCHS(drive)` for geometry; drive data comes from `struct drive_s`, not the FDPT. The FDPT is intended for software that reads it directly (e.g. OS without BIOS access).
- **IVT 41h/46h**: Data pointers; callers read the table via the far pointer to obtain geometry.
- **ATA/IDE only**: The FDPT applies to ATA disks; SCSI and other interfaces do not use it.

## Drive Control Byte (AT)

| Bit | Meaning |
|-----|---------|
| 0 | Unused |
| 1 | Reserved (0) |
| 2 | Reserved (0) |
| 3 | 1 if more than 8 heads |
| 4 | Always 0 |
| 5 | Manufacturer defect map on max cylinder+1 |
| 6 | Disable ECC retries |
| 7 | Disable access retries |

SeaBIOS sets 0xc0 (bits 6–7) and adds bit 3 when `nph > 8`.
