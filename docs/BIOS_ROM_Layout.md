# BIOS ROM Layout

The BIOS ROM occupies physical memory **0xF0000-0xFFFFF** (64 KB). In real mode this region is addressed as segment **F000** (SEG_BIOS). The layout satisfies IBM PC/AT compatibility: many entry points and data structures must reside at fixed addresses so that legacy software and the CPU reset vector can find them.

The layout is defined by:

- **src/romlayout.S**: Assembly entry points via the ORG macro (`.section .fixedaddr.0xNNNN`)
- **src/misc.c**, **src/font.c**: Fixed-address variables via the VARFSEGFIXED(addr) macro
- **scripts/layoutrom.py**: Build-time script that assigns addresses and packs relocatable code into gaps between fixed sections

Key constants are in **src/config.h**: `BUILD_BIOS_ADDR = 0xf0000`, `BUILD_BIOS_SIZE = 0x10000`, `SEG_BIOS = 0xf000`.

## Fixed Address Entry Points

These addresses are required for IBM PC/AT compatibility. They are defined in **src/romlayout.S** using the ORG macro.

| Address (segment offset) | Symbol | Purpose |
|--------------------------|--------|---------|
| 0xe05b | entry_post | POST entry point; jumped to from reset vector |
| 0xe2c3 | entry_02 | INT 02 NMI handler |
| 0xe3fe | entry_13_official | INT 13 disk services (jumps to entry_13) |
| 0xe6f2 | entry_19_official | INT 19 bootstrap (jumps to entry_19) |
| 0xe739 | entry_14 | INT 14 serial services |
| 0xe82e | entry_16 | INT 16 keyboard services |
| 0xe987 | entry_09 | IRQ1 keyboard |
| 0xec59 | entry_40 | INT 40 floppy disk |
| 0xef57 | entry_0e | IRQ6 floppy |
| 0xefd2 | entry_17 | INT 17 printer services |
| 0xf045 | entry_10_0x0f | INT 10h functions 0-F (stub: iretw) |
| 0xf065 | entry_10 | INT 10 video services (stub: iretw) |
| 0xf841 | entry_12 | INT 12 memory size |
| 0xf84d | entry_11 | INT 11 equipment list |
| 0xf859 | entry_15_official | INT 15 system services |
| 0xfe6e | entry_1a_official | INT 1A time services; dispatches to PCI BIOS if AH=B1h |
| 0xfea5 | entry_08 | IRQ0 timer tick |
| 0xff40 | entry_iret_official | Default interrupt vector (generic dummy IRET) |
| 0xff41 | BIOS_ENTRY_INT_00 | Dummy IRET for INT 00 |
| 0xff42 | BIOS_ENTRY_INT_01 | Dummy IRET for INT 01 |
| 0xff43 | BIOS_ENTRY_INT_02 | Dummy IRET for INT 02 |
| 0xff44 | BIOS_ENTRY_INT_03 | Dummy IRET for INT 03 |
| 0xff45 | BIOS_ENTRY_INT_04 | Dummy IRET for INT 04 |
| 0xff46 | BIOS_ENTRY_INT_05 | Dummy IRET for INT 05 |
| 0xff47 | BIOS_ENTRY_INT_06 | Dummy IRET for INT 06 |
| 0xff48 | BIOS_ENTRY_INT_07 | Dummy IRET for INT 07 |
| 0xff49 | BIOS_ENTRY_INT_10 | Dummy IRET for INT 10 |
| 0xff4a | BIOS_ENTRY_INT_11 | Dummy IRET for INT 11 |
| 0xff4b | BIOS_ENTRY_INT_12 | Dummy IRET for INT 12 |
| 0xff4c | BIOS_ENTRY_INT_13 | Dummy IRET for INT 13 |
| 0xff4d | BIOS_ENTRY_INT_14 | Dummy IRET for INT 14 |
| 0xff4e | BIOS_ENTRY_INT_15 | Dummy IRET for INT 15 |
| 0xff4f | BIOS_ENTRY_INT_16 | Dummy IRET for INT 16 |
| 0xff50 | BIOS_ENTRY_INT_17 | Dummy IRET for INT 17 |
| 0xff51 | BIOS_ENTRY_INT_18 | Dummy IRET for INT 18 |
| 0xff52 | BIOS_ENTRY_INT_19 | Dummy IRET for INT 19 |
| 0xff53 | BIOS_ENTRY_INT_1A | Dummy IRET for INT 1A |
| 0xff54 | entry_05 | INT 05 print screen |
| 0xfff0 | reset_vector | Power-up entry point; ljmpw to entry_post |

Physical address = segment base 0xF0000 + offset (e.g. reset_vector = 0xFFFF0).

## Fixed Address Data Structures

These variables are placed at fixed offsets using VARFSEGFIXED(addr) so that legacy software and interrupt vectors can reference them.

| Address (offset) | Symbol | Size | Purpose |
|------------------|--------|------|---------|
| 0xe401 | OldFDPT | 16 bytes | Old Fixed Disk Parameter Table (legacy; FDPT now in EBDA) |
| 0xe6f5 | BIOS_CONFIG_TABLE | 10 bytes | BIOS configuration table (INT 15h AH=C0h) |
| 0xe729 | BaudTable | 16 bytes | Baud rate generator table |
| 0xefc7 | diskette_param_table | 11 bytes | Floppy Disk Base Table (INT 1E points here or to extended table) |
| 0xf0a4 | VideoParams | 88 bytes | Video parameter tables (INT 1D pointer) |
| 0xfa6e | vgafont8 | 1024 bytes | 8x8 VGA font for lower 128 characters (INT 1F points to extension) |
| 0xfef3 | InitVectors | 13 bytes | Initial interrupt vector offsets loaded by POST |
| 0xfff5 | BiosDate | 8 bytes | BIOS build date string "MM/DD/YY" |
| 0xfffe | BiosModelId | 1 byte | Model ID (e.g. 0xFC for AT) |
| 0xffff | BiosChecksum | 1 byte | ROM checksum (sum of all bytes in ROM = 0) |

Defined in **src/misc.c** except vgafont8, which is in **src/font.c**.

## Dynamic Sections

The remainder of the F-segment is filled at build time by **scripts/layoutrom.py**. Section categories (from lowest to highest address in the layout algorithm) are:

1. **32init** — Init-only code; executed during POST and then relocated or discarded. Not present at fixed addresses at runtime.
2. **32flat** — Runtime 32-bit flat code and data (POST, boot, and internal C code).
3. **32fseg** — F-segment variables (VARFSEG); accessible in 16-bit and 32-bit segmented mode.
4. **32textfseg** — 32-bit code that must be callable with F-segment addressing.
5. **32seg** — 32-bit segmented mode code (e.g. PCI BIOS, APM).
6. **16bit** — 16-bit code (`.text16`) and data (`.data16`) from code16gcc and related objects.

Fixed-address sections (entry points and VARFSEGFIXED data) are assigned first. **fitSections()** in layoutrom.py then packs non-fixed 16-bit sections into the gaps between fixed sections to use the F-segment efficiently.

## Build Process

1. **layoutrom.py** reads section and symbol information (from objdump) for the 16-bit, 32seg, and 32flat objects.
2. Sections whose names start with `.fixedaddr.0x` get the corresponding segment offset (e.g. `.fixedaddr.0xe05b` → 0xe05b).
3. **fitSections()** sorts fixed sections by offset, computes free space between them, and assigns relocatable 16-bit sections to fill the gaps.
4. Remaining sections are placed below the first fixed address: 32init at the bottom, then 32flat, 32fseg, 32textfseg, 32seg, and 16bit, each contiguous block ending where the next starts.
5. The script emits linker scripts so the final link of **rom.o** places each section at the chosen address.

See **docs/Linking_overview.md** for the overall link process and fixed-address support.

## ZoneFSeg

ZoneFSeg is the runtime malloc region inside the F-segment (used by **malloc_fseg()**). Its bounds are **zonefseg_start** and **zonefseg_end**, computed by layoutrom.py so that:

- It lies within the F-segment and does not overlap static sections.
- At least **BUILD_MIN_BIOSTABLE** bytes are reserved: 2048 by default, or 8192 when CONFIG_ROM_SIZE >= 256.

This space holds dynamically allocated tables and buffers that must remain in the F-segment for 16-bit or segmented-mode access.

## Memory Map (typical)

Addresses are physical; segment F000 has base 0xF0000.

```
0xf0000 +-----------------+
        | 32init code     |  (relocated at runtime)
        | 32flat code     |
        | 32fseg vars     |
        | 32textfseg      |
        | 32seg code      |
        | 16bit code/data |  (packed with fixed sections)
        |                 |
0xe05b  +-----------------+  entry_post (first fixed entry)
        | Fixed entries   |
        | and data        |
        | (see tables)    |
0xfff0  +-----------------+  reset_vector
        | BiosDate        |
        | BiosModelId     |
        | BiosChecksum    |
0x100000+-----------------+
```

Exact boundaries depend on the build; the fixed locations in the tables above do not change.

## Reference: config.h constants

| Constant | Value | Meaning |
|----------|-------|---------|
| BUILD_BIOS_ADDR | 0xf0000 | Physical base of BIOS ROM |
| BUILD_BIOS_SIZE | 0x10000 | Size of BIOS ROM (64 KB) |
| SEG_BIOS | 0xf000 | Real-mode segment for BIOS |
| BUILD_MIN_BIOSTABLE | 2048 (or 8192) | Minimum ZoneFSeg size |
