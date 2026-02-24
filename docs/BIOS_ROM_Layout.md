# BIOS ROM Layout

The BIOS ROM occupies physical memory **0xF0000-0xFFFFF** (64 KB). In real mode this region is addressed as segment **F000** (SEG_BIOS). The layout satisfies IBM PC/AT compatibility: many entry points and data structures must reside at fixed addresses so that legacy software and the CPU reset vector can find them.

In this project the layout is implemented via constants in **pc86_arch.h** and ROM/IVT setup in **machine.cpp** (no romlayout.S or layoutrom.py).

Key constants: `BIOS_ROM_ADDR = 0xf0000`, segment **0xF000**, physical address = 0xF0000 + offset.

## Reference: IBM BIOS compatibility offsets

The following fixed addresses are required for IBM PC/AT compatibility. Sources: Ralf Brown's Interrupt List (RBIL), IBM PS/2 and PC BIOS Interface Technical Reference (May 1988), reconstructed IBM PC AT BIOS (e.g. pcjs.org, IBMPCBIOS).

| F000h:offset | Purpose |
|--------------|---------|
| E05Bh | POST entry point |
| E2C3h | INT 02h NMI handler entry point |
| E401h | Fixed disk parameter table (AT+) |
| E6F2h | INT 19h bootstrap service entry point |
| E6F5h | INT 15h function C0h configuration data table (ATv2+) |
| E729h | Baud rate initialization table |
| E739h | INT 14h serial port services entry point |
| E82Eh | INT 16h keyboard services entry point |
| E987h | INT 09h keyboard interrupt entry point |
| EC59h | INT 13h diskette services entry point |
| EF57h | INT 0Eh diskette interrupt entry point |
| EFC7h | Floppy drive parameter table (INT 1Eh) |
| EFD2h | INT 17h printer services entry point |
| F045h | INT 10h functions 00h-0Fh jump table |
| F065h | INT 10h video services entry point |
| F0A4h | MDA/CGA video parameter table (INT 1Dh) |
| F841h | INT 12h memory size service entry point |
| F84Dh | INT 11h equipment check service entry point |
| F859h | INT 15h system services entry point |
| FA6Eh | Character font for 320x200 and 640x200 graphics (lower 128) |
| FE6Eh | INT 1Ah time of day services entry point |
| FEA5h | INT 08h system timer interrupt entry point |
| FEF3h | Initial interrupt vector offsets (INT 08h-1Fh) |
| FF23h | Initial interrupt vector offsets (INT 70h-77h) (AT+) |
| FF53h | IRET instruction for dummy interrupt handler |
| FF54h | INT 05h print screen service entry point |
| FFF0h | Power-up entry point |
| FFF5h | ASCII date ROM was built |
| FFFEh | System model ID |

## Reserved area: 0xFF40–0xFF4D (keep clear)

On many PC-compatible systems (e.g. NEC Powermate 386 series, Versa Note laptops), segment offset **0xFF40–0xFF4D** (physical 0xFFF40–0xFFF4D) is used for:

- **0xFF40–0xFF41**: 2-byte machine ID / system ID
- **0xFF42–0xFF4D**: 12-byte ASCII BIOS version string (e.g. "jjjj-kkkk-llll": System BIOS + Video BIOS + PIC version)

Do not use this range for dummy vector stubs or other emulator data. Dummy stubs for INT 00, 01, 02, 03, 04, 06, 07, 18 are placed at **0xFF38–0xFF3F** instead.

## Fixed Address Entry Points

These addresses are required for IBM PC/AT compatibility.

| Address (segment offset) | Symbol | Purpose |
|--------------------------|--------|---------|
| 0xe05b | entry_post | POST entry point; jumped to from reset vector |
| 0xe2c3 | entry_02 | INT 02 NMI handler |
| 0xe401 | OldFDPT | Fixed disk parameter table (AT+) — data |
| 0xe6f2 | entry_19_official | INT 19 bootstrap |
| 0xe6f5 | BIOS_CONFIG_TABLE | INT 15h AH=C0h configuration table — data |
| 0xe729 | BaudTable | Baud rate table — data |
| 0xe739 | entry_14 | INT 14 serial services |
| 0xe82e | entry_16 | INT 16 keyboard services |
| 0xe987 | entry_09 | IRQ1 keyboard |
| 0xec59 | entry_40 | INT 13h diskette services / INT 40 floppy |
| 0xef57 | entry_0e | IRQ6 floppy |
| 0xefc7 | diskette_param_table | Floppy parameter table (INT 1Eh) — data |
| 0xefd2 | entry_17 | INT 17 printer services |
| 0xf045 | entry_10_0x0f | INT 10h functions 00h-0Fh jump table |
| 0xf065 | entry_10 | INT 10 video services |
| 0xf0a4 | VideoParams | MDA/CGA video parameter table (INT 1Dh) — data |
| 0xf841 | entry_12 | INT 12 memory size |
| 0xf84d | entry_11 | INT 11 equipment list |
| 0xf859 | entry_15_official | INT 15 system services |
| 0xfa6e | vgafont8 | Character font (320x200, 640x200) — data |
| 0xfe6e | entry_1a_official | INT 1A time of day services |
| 0xfea5 | entry_08 | IRQ0 timer tick |
| 0xfef3 | InitVectors | Initial interrupt vector offsets (INT 08h-1Fh) — data |
| 0xff23 | InitVectors_70 | Initial interrupt vector offsets (INT 70h-77h) (AT+) — data |
| 0xff38 | BIOS_ENTRY_INT_00 | Dummy stub for INT 00 (1 byte IRET) |
| 0xff39 | BIOS_ENTRY_INT_01 | Dummy stub for INT 01 |
| 0xff3a | BIOS_ENTRY_INT_02 | Dummy stub for INT 02 |
| 0xff3b | BIOS_ENTRY_INT_03 | Dummy stub for INT 03 |
| 0xff3c | BIOS_ENTRY_INT_04 | Dummy stub for INT 04 |
| 0xff3d | BIOS_ENTRY_INT_06 | Dummy stub for INT 06 |
| 0xff3e | BIOS_ENTRY_INT_07 | Dummy stub for INT 07 |
| 0xff3f | BIOS_ENTRY_INT_18 | Dummy stub for INT 18 |
| 0xff53 | entry_iret_official | IRET for dummy interrupt handler (1 byte 0xCF) |
| 0xff54 | entry_05 | INT 05 print screen |
| 0xfff0 | reset_vector | Power-up entry point; ljmpw to entry_post |

Physical address = segment base 0xF0000 + offset (e.g. reset_vector = 0xFFFF0). Area **0xFF40–0xFF4D** is reserved (machine ID + BIOS version string on some systems).

## Fixed Address Data Structures

These variables are placed at fixed offsets so that legacy software and interrupt vectors can reference them. In this project they are represented by constants in **pc86_arch.h** and ROM/IVT setup in **machine.cpp**.

| Address (offset) | Symbol | Size | Purpose |
|------------------|--------|------|---------|
| 0xe401 | OldFDPT | 16 bytes | Old Fixed Disk Parameter Table (legacy; FDPT now in EBDA) |
| 0xe6f5 | BIOS_CONFIG_TABLE | 10 bytes | BIOS configuration table (INT 15h AH=C0h) |
| 0xe729 | BaudTable | 16 bytes | Baud rate generator table |
| 0xefc7 | diskette_param_table | 11 bytes | Floppy Disk Base Table (INT 1E points here or to extended table) |
| 0xf0a4 | VideoParams | 88 bytes | Video parameter tables (INT 1D pointer) |
| 0xfa6e | vgafont8 | 1024 bytes | 8x8 VGA font for lower 128 characters (INT 1F points to extension) |
| 0xfef3 | InitVectors | varies | Initial interrupt vector offsets (INT 08h-1Fh) loaded by POST |
| 0xff23 | InitVectors_70 | 16 bytes | Initial interrupt vector offsets (INT 70h-77h) (AT+) |
| 0xfff5 | BiosDate | 8 bytes | BIOS build date string "MM/DD/YY" |
| 0xfffe | BiosModelId | 1 byte | Model ID (e.g. 0xFC for AT) |
| 0xffff | BiosChecksum | 1 byte | ROM checksum (sum of all bytes in ROM = 0) |

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

## Reference: pc86_arch.h constants

| Constant | Value | Meaning |
|----------|-------|---------|
| BIOS_ROM_ADDR | 0xf0000 | Physical base of BIOS ROM |
| (segment 0xF000) | — | Real-mode segment for BIOS (base 0xF0000) |
| BIOS_ENTRY_* | various | Fixed entry point offsets (see tables above) |
| BIOS_INIT_VECTORS | 0xfef3 | Initial vector table (INT 08h-1Fh) |
| BIOS_INIT_VECTORS_70 | 0xff23 | Initial vector table (INT 70h-77h) (AT+) |
