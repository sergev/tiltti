# Interrupt Descriptor Table (IVT)

The Interrupt Vector Table (IVT) occupies physical addresses 0x0000-0x0400 (1 KB). It contains 256 interrupt vectors; each is a 4-byte far pointer (segment:offset) defined as `struct segoff_s`. The structure is `struct rmode_IVT` in `src/std/bda.h` with field `ivec[256]`. Access uses `GET_IVT(vector)` and `SET_IVT(vector, segoff)` from `src/biosvar.h` via segment `SEG_IVT` (0x0000).

In real mode this table is typically called the Interrupt Vector Table (IVT); `Memory_Model.md` refers to it as the Interrupt descriptor table (IDT).

## IVT Layout

| Offset | Size | Vector | Content |
|--------|------|--------|---------|
| 0x000 | 4 | 0 | ivec[0] |
| 0x004 | 4 | 1 | ivec[1] |
| ... | ... | ... | ... |
| 0x3FC | 4 | 255 | ivec[255] |

Each entry is a `struct segoff_s` (offset and segment, 4 bytes total) forming a far pointer used by the CPU when an interrupt or exception occurs.

## Initialization Flow

The IVT is initialized in this order during POST:

1. **ivt_init()** (`src/post.c`): Base setup — all 256 vectors to `entry_iret_official`; 0x08-0x0F and 0x70-0x77 to `entry_hwpic1`/`entry_hwpic2`; software handlers for 0x02, 0x05, 0x10-0x1a, 0x40; 0x60-0x66 and 0x79 to null (SEGOFF(0,0))
2. **enable_hwirq()** (`src/hw/pic.c`): Overrides vectors for enabled hardware IRQs (called from clock.c, ps2port.c, floppy.c, ata.c, misc.c)
3. **floppy_setup()** (`src/hw/floppy.c`): Vector 0x1E → diskette parameter table
4. **fill_fdpt()** (`src/block.c`): Vectors 0x41, 0x46 → FDPT in EBDA
5. **vga_post()** / **vgabios** (`vgasrc/`): Vectors 0x1f, 0x43 (font pointers); may override 0x08 (timer hook), 0x10
6. **sercon_setup()** (`src/sercon.c`): May override 0x10 when using serial console

## Hardware IRQ Mapping

The 8259 PIC maps hardware interrupts to vectors:

- **PIC1 (IRQ 0-7)**: Vectors 0x08-0x0F (`BIOS_HWIRQ0_VECTOR` = 0x08)
- **PIC2 (IRQ 8-15)**: Vectors 0x70-0x77 (`BIOS_HWIRQ8_VECTOR` = 0x70)

## Vector Summary Table

| Vector | IRQ/Usage | Handler / Pointer | C Handler | Source |
|--------|-----------|-------------------|-----------|--------|
| 0x00-0x01 | CPU exception | entry_iret_official | — | post.c |
| 0x02 | NMI | entry_02 | handle_02 | misc.c |
| 0x03-0x04 | CPU exception | entry_iret_official | — | post.c |
| 0x05 | Print Screen | entry_05 | handle_05 | misc.c |
| 0x06-0x07 | CPU exception | entry_iret_official | — | post.c |
| 0x08 | IRQ0 Timer | entry_08 (or timer hook) | handle_08 | clock.c, vgainit.c |
| 0x09 | IRQ1 Keyboard | entry_09 | handle_09 | ps2port.c |
| 0x0A-0x0D | Unused IRQ | entry_hwpic1 | handle_hwpic1 | pic.c |
| 0x0E | IRQ6 Floppy | entry_0e | handle_0e | floppy.c |
| 0x0F | Unused IRQ | entry_hwpic1 | handle_hwpic1 | pic.c |
| 0x10 | Video | entry_10 / entry_sercon | handle_10 | vgabios.c, sercon.c |
| 0x11 | Equipment List | entry_11 | handle_11 | misc.c |
| 0x12 | Memory Size | entry_12 | handle_12 | misc.c |
| 0x13 | Disk | entry_13 | handle_13 | disk.c |
| 0x14 | Serial | entry_14 | handle_14 | serial.c |
| 0x15 | System Services | entry_15_official | handle_15 | system.c |
| 0x16 | Keyboard | entry_16 | handle_16 | kbd.c |
| 0x17 | Printer | entry_17 | handle_17 | serial.c |
| 0x18 | ROM BASIC | entry_18 | handle_18 | boot.c |
| 0x19 | Boot | entry_19 | handle_19 | boot.c |
| 0x1A | RTC/Timer | entry_1a_official | handle_1a | clock.c |
| 0x1B-0x1D | — | entry_iret_official | — | post.c |
| 0x1E | Floppy param table | Pointer to diskette_param_table | (data) | floppy.c |
| 0x1F | Font 8x8 ext | Pointer to font | (data) | vgabios.c |
| 0x20-0x3F | — | entry_iret_official | — | post.c |
| 0x40 | Floppy disk | entry_40 | handle_40 | disk.c |
| 0x41 | HD0 FDPT | Pointer to EBDA fdpt[0] | (data) | block.c |
| 0x42-0x45 | — | entry_iret_official | — | post.c |
| 0x46 | HD1 FDPT | Pointer to EBDA fdpt[1] | (data) | block.c |
| 0x47-0x5F | — | entry_iret_official | — | post.c |
| 0x60-0x66 | User reserved | SEGOFF(0,0) | — | post.c |
| 0x67-0x78 | — | entry_iret_official | — | post.c |
| 0x70 | IRQ8 RTC | entry_70 | handle_70 | clock.c |
| 0x71-0x73 | Unused IRQ | entry_hwpic2 | handle_hwpic2 | pic.c |
| 0x74 | IRQ12 Mouse | entry_74 | handle_74 | ps2port.c |
| 0x75 | IRQ13 FPU | entry_75 | handle_75 | misc.c |
| 0x76 | IRQ14 IDE | entry_76 | handle_76 | disk.c |
| 0x77 | Unused IRQ | entry_hwpic2 | handle_hwpic2 | pic.c |
| 0x79 | Guardian Angel | SEGOFF(0,0) | — | post.c |
| 0x7A-0xFF | — | entry_iret_official | — | post.c |

---

## Vector Reference

### Default Handler: entry_iret_official

Unhandled vectors point to `entry_iret_official` in `src/romlayout.S`, which simply executes `iretw` and returns. Used for CPU exceptions that the BIOS does not handle and for unused software interrupt numbers.

---

### 0x00-0x1F — CPU Exceptions and BIOS Vectors

#### 0x02 — NMI (Non-Maskable Interrupt)

- **Purpose**: CPU NMI; often used for parity/memory errors
- **Entry**: `entry_02` (`romlayout.S`) → `handle_02`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_02()` in `src/misc.c` — calls debug_isr, chains to legacy NMI (INT 02h)

#### 0x05 — Print Screen

- **Purpose**: INT 05h — Print Screen service
- **Entry**: `entry_05` (via IRQ_ENTRY_ARG) → `handle_05`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_05()` in `src/misc.c` — stub (calls debug_enter only)

#### 0x08 — IRQ0 System Timer

- **Purpose**: Hardware timer tick (~18.2 Hz)
- **Entry**: `entry_08` or `entry_timer_hook` when VGA text emulation; → `handle_08`
- **Initialization**: `ivt_init()` then `clock_setup()` via `enable_hwirq(0, ...)`; `vgainit.c` may replace with timer hook
- **C Handler**: `handle_08()` in `src/clock.c` — updates BDA timer, chains to INT 1Ch

#### 0x09 — IRQ1 Keyboard

- **Purpose**: Keyboard scan code interrupt
- **Entry**: `entry_09` → `handle_09`
- **Initialization**: `ivt_init()` then `ps2port_setup()` via `enable_hwirq(1, ...)`
- **C Handler**: `handle_09()` in `src/hw/ps2port.c` — processes keyboard data

#### 0x0A-0x0D, 0x0F — Unused PIC1 IRQs

- **Purpose**: IRQ 2-5, 7 (cascade, COM2, COM1, LPT2, LPT1)
- **Entry**: `entry_hwpic1` → `handle_hwpic1`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_hwpic1()` in `src/hw/pic.c` — EOI only

#### 0x0E — IRQ6 Floppy

- **Purpose**: Floppy disk controller interrupt
- **Entry**: `entry_0e` → `handle_0e`
- **Initialization**: `ivt_init()` then `floppy_setup()` via `enable_hwirq(6, ...)`
- **C Handler**: `handle_0e()` in `src/hw/floppy.c` — floppy IRQ handling

#### 0x10 — Video (INT 10h)

- **Purpose**: Video BIOS services
- **Entry**: `entry_10` or `entry_10_extrastack` or `entry_sercon` when serial console
- **Initialization**: `ivt_init()` then `vga_post()` (may use extra stack); `sercon_setup()` overrides when CONFIG_SERCON
- **C Handler**: `handle_10()` in `vgasrc/vgabios.c` — video mode, cursor, etc.

#### 0x11 — Equipment List (INT 11h)

- **Purpose**: Return equipment word
- **Entry**: `entry_11` → `handle_11`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_11()` in `src/misc.c` — returns BDA equipment_list_flags

#### 0x12 — Memory Size (INT 12h)

- **Purpose**: Return conventional memory size in KB
- **Entry**: `entry_12` → `handle_12`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_12()` in `src/misc.c` — returns BDA mem_size_kb

#### 0x13 — Disk (INT 13h)

- **Purpose**: Disk I/O (floppy, hard disk, CD-ROM)
- **Entry**: `entry_13_official` → `entry_13` → `handle_13`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_13()` in `src/disk.c` — routes to floppy/hard disk handlers

#### 0x14 — Serial (INT 14h)

- **Purpose**: Serial port I/O
- **Entry**: `entry_14` → `handle_14`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_14()` in `src/serial.c` — init, read, write, status

#### 0x15 — System Services (INT 15h)

- **Purpose**: Extended BIOS services (memory, APM, etc.)
- **Entry**: `entry_15_official` → `handle_15` (or `entry_1589` for AH=89h)
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_15()` in `src/system.c` — many subfunctions

#### 0x16 — Keyboard (INT 16h)

- **Purpose**: Keyboard read, status, typematic
- **Entry**: `entry_16` → `handle_16`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_16()` in `src/kbd.c` — read key, check buffer

#### 0x17 — Printer (INT 17h)

- **Purpose**: Parallel port printing
- **Entry**: `entry_17` → `handle_17`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_17()` in `src/serial.c` — write, init, status

#### 0x18 — ROM BASIC

- **Purpose**: Invoked when boot fails; normally "Insert boot disk"
- **Entry**: `entry_18` → `handle_18`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_18()` in `src/boot.c` — transitions to 32-bit, shows boot menu

#### 0x19 — Boot (INT 19h)

- **Purpose**: Bootstrap loader — load boot sector and transfer control
- **Entry**: `entry_19_official` → `entry_19` → `handle_19`
- **Initialization**: `ivt_init()` in `src/post.c`; option ROMs may replace, `optionroms.c` restores
- **C Handler**: `handle_19()` in `src/boot.c` — boots from BEV/BCV devices

#### 0x1A — RTC/Timer (INT 1Ah)

- **Purpose**: Time-of-day, RTC, wait
- **Entry**: `entry_1a_official` → `handle_1a` (or `entry_pcibios16` for AH=B1h)
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_1a()` in `src/clock.c` — get/set tick, CMOS date/time

#### 0x1E — Floppy Disk Parameter Table (data)

- **Purpose**: Pointer to floppy disk base table; used by INT 13h
- **Content**: `SEGOFF(SEG_BIOS, diskette_param_table2)`
- **Initialization**: `floppy_setup()` in `src/hw/floppy.c`
- **Data**: `diskette_param_table2` / `diskette_param_table` in `src/hw/floppy.c`

#### 0x1F — Font 8x8 Extension (data)

- **Purpose**: Pointer to 8x8 character font (second 128 chars)
- **Content**: Pointer to `vgafont8[128*8]` or user-defined
- **Initialization**: `vga_set_mode()` in `vgasrc/vgabios.c`; INT 10h AH=11h AL=30h can change

---

### 0x40-0x46 — Disk Vectors

#### 0x40 — Floppy Disk (INT 40h)

- **Purpose**: Floppy disk I/O (relocated INT 13h for floppy when INT 13h is hooked)
- **Entry**: `entry_40` → `handle_40`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_40()` in `src/disk.c` — same as floppy part of INT 13h

#### 0x41 — Hard Disk 0 FDPT (data)

- **Purpose**: Pointer to Fixed Disk Parameter Table for drive 0
- **Content**: `SEGOFF(ebda_seg, offsetof(..., fdpt[0]))`
- **Initialization**: `fill_fdpt()` in `src/block.c` when mapping first hard drive

#### 0x46 — Hard Disk 1 FDPT (data)

- **Purpose**: Pointer to Fixed Disk Parameter Table for drive 1
- **Content**: `SEGOFF(ebda_seg, offsetof(..., fdpt[1]))`
- **Initialization**: `fill_fdpt()` in `src/block.c` when mapping second hard drive

---

### 0x43 — Font Pointer (data)

- **Purpose**: Pointer to current character font (8x8, 8x14, or 8x16)
- **Content**: Pointer to `vgafont8`, `vgafont14`, or `vgafont16`
- **Initialization**: `vga_set_mode()` in `vgasrc/vgabios.c`; INT 10h AH=11h can change

---

### 0x60-0x66, 0x79 — Reserved

#### 0x60-0x66 — User Interrupt Vectors

- **Purpose**: Reserved for user/application use
- **Content**: `SEGOFF(0, 0)` (null)
- **Initialization**: `ivt_init()` in `src/post.c`

#### 0x79 — Guardian Angel

- **Purpose**: Used by "Guardian Angel" protection system; zeroed by BIOS
- **Content**: `SEGOFF(0, 0)` (null)
- **Initialization**: `ivt_init()` in `src/post.c`

---

### 0x70-0x77 — Second PIC (IRQ 8-15)

#### 0x70 — IRQ8 RTC

- **Purpose**: Real-time clock / periodic interrupt
- **Entry**: `entry_70` → `handle_70`
- **Initialization**: `clock_setup()` via `enable_hwirq(8, ...)` when CONFIG_RTC_TIMER
- **C Handler**: `handle_70()` in `src/clock.c` — RTC tick, INT 15h AH=83h wait

#### 0x71-0x73 — Unused PIC2 IRQs

- **Purpose**: IRQ 9-11 (redirected cascade, etc.)
- **Entry**: `entry_hwpic2` → `handle_hwpic2`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_hwpic2()` in `src/hw/pic.c` — EOI only

#### 0x74 — IRQ12 PS/2 Mouse

- **Purpose**: PS/2 mouse data
- **Entry**: `entry_74` → `handle_74`
- **Initialization**: `ps2port_setup()` via `enable_hwirq(12, ...)`
- **C Handler**: `handle_74()` in `src/hw/ps2port.c` — mouse packet handling

#### 0x75 — IRQ13 Math Coprocessor

- **Purpose**: x87 FPU exception
- **Entry**: `entry_75` → `handle_75`
- **Initialization**: `mathcp_setup()` via `enable_hwirq(13, ...)`
- **C Handler**: `handle_75()` in `src/misc.c` — clears IRQ13, chains to NMI

#### 0x76 — IRQ14 Primary IDE

- **Purpose**: Primary IDE controller interrupt
- **Entry**: `entry_76` → `handle_76`
- **Initialization**: `ata_setup()` via `enable_hwirq(14, ...)`
- **C Handler**: `handle_76()` in `src/disk.c` — IDE completion

#### 0x77 — Unused PIC2 IRQ

- **Purpose**: IRQ15 (secondary IDE typically)
- **Entry**: `entry_hwpic2` → `handle_hwpic2`
- **Initialization**: `ivt_init()` in `src/post.c`
- **C Handler**: `handle_hwpic2()` in `src/hw/pic.c` — EOI only

---

## Entry Point Implementation

Entry points are defined in `src/romlayout.S` using macros:

- **ENTRY(handler)**: Software interrupt — switch stack, call handler, IRET
- **IRQ_ENTRY(num)**: Hardware interrupt — push handler address, use extra stack, call, EOI, IRET
- **IRQ_ENTRY_ARG(num)**: Software interrupt with args — push handler, call with `struct bregs` from stack

The C handlers receive a `struct bregs *` (register state) and implement the actual BIOS service or IRQ logic.
