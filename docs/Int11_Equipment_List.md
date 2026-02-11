# Equipment List (INT 11h)

This page documents the BIOS Equipment List service implemented in SeaBIOS and invoked via **INT 11h**. It describes the single function (get equipment list), the equipment word bit layout, and how each bit is initialized during POST.

Implementation is in `src/misc.c` (handler `handle_11()`). The equipment word is stored in the BIOS Data Area at 40:10h (`equipment_list_flags` in `src/std/bda.h`) and is updated by various initialization routines using `set_equipment_flags()` in `src/biosvar.h`. The IVT vector 0x11 is set in `src/post.c`; the entry point `entry_11` is at fixed address 0xf84d in `src/romlayout.S`.

## Overview

- **INT 11h** is the Equipment List interrupt. It has a single function: return the equipment word in AX.
- **Entry**: `entry_11` at 0xf84d (via `IRQ_ENTRY_ARG 11` in `src/romlayout.S`).
- **Handler**: `handle_11()` in `src/misc.c` — reads BDA `equipment_list_flags` and returns it in the caller's AX.
- **Data source**: BDA at segment 0x40, offset 0x10 (same location as MEM 0040:0010h in RBIL).

## Calling convention

- **Inputs**: None. No register inputs are used.
- **Output**: **AX** = equipment list word (16-bit). On 32-bit callers, the high word of EAX is not defined by the BIOS; callers that test high bits should clear the high word before the call.
- **Registers**: The handler uses `struct bregs` in `src/bregs.h`; on return, only AX is set; other registers are preserved by the entry/exit code.

## Implementation flow

```mermaid
flowchart LR
    INT11[INT 11h]
    INT11 --> Entry11[entry_11]
    Entry11 --> Handle11[handle_11]
    Handle11 --> BDA[equipment_list_flags at 40:10h]
    BDA --> AX[AX = equipment word]
```

---

## Equipment word bit reference

The returned word follows the IBM PC BIOS equipment list format. Bits are set during POST by the listed code; bits that SeaBIOS does not set remain zero after BDA init.

| Bits | Mask | Description | SeaBIOS initialization |
|------|------|-------------|-------------------------|
| 0 | 0x0001 | Floppy disk(s) installed | Set by `map_floppy_drive()` in `src/block.c`; also by El Torito floppy emulation in `src/cdrom.c` |
| 1 | 0x0002 | 80x87 coprocessor installed | Set by `mathcp_setup()` in `src/misc.c` |
| 2 | 0x0004 | Pointing device installed (PS/2) | Set by `mouse_init()` in `src/mouse.c` when `CONFIG_MOUSE` |
| 3–2 | 0x000C | RAM on motherboard (PC/XT: 16K or 64K banks) | Not set by SeaBIOS |
| 5–4 | 0x0030 | Initial video mode | Set by `init_bios_area()` in `vgasrc/vgainit.c`: mask 0x30, value 0x20 (80×25 color) |
| 7–6 | 0x00C0 | Number of floppies minus 1 (if bit 0 set) | 0x00 = 1 drive, 0x40 = 2 drives; set with bit 0 by `map_floppy_drive()` or CD emulation |
| 8 | 0x0100 | DMA support (machine-specific) | Not set by SeaBIOS |
| 11–9 | 0x0E00 | Number of serial ports (0–4) | Set by `serial_setup()` in `src/serial.c`: `count &lt;&lt; 9` |
| 12 | 0x1000 | Game port installed | Not set by SeaBIOS |
| 13 | 0x2000 | Serial printer (PCjr) / internal modem (PC/Convertible) | Not set by SeaBIOS |
| 15–14 | 0xC000 | Number of parallel ports (0–2) | Set by `lpt_setup()` in `src/serial.c`: `count &lt;&lt; 14` |

### Initial video mode (bits 5–4)

| Value | Bits | Meaning |
|-------|------|---------|
| 00b | 0x00 | EGA, VGA, or PGA |
| 01b | 0x10 | 40×25 color |
| 10b | 0x20 | 80×25 color (SeaBIOS default) |
| 11b | 0x30 | 80×25 monochrome |

### Floppy count (bits 7–6, with bit 0)

When bit 0 is set: bits 7–6 = (number of floppy drives) − 1. So 0x01 = one drive, 0x41 = two drives.

---

## Where each bit is set

| Source | Function / context | Bits cleared | Bits set | Notes |
|--------|--------------------|--------------|----------|-------|
| `src/misc.c` | `mathcp_setup()` | 0x02 | 0x02 | 80x87 present |
| `src/mouse.c` | `mouse_init()` | 0x04 | 0x04 | If `CONFIG_MOUSE` |
| `vgasrc/vgainit.c` | `init_bios_area()` | 0x30 | 0x20 | 80×25 color |
| `src/serial.c` | `serial_setup()` | 0x0E00 | count &lt;&lt; 9 | 0–4 COM ports |
| `src/serial.c` | `lpt_setup()` | 0xC000 | count &lt;&lt; 14 | 0–2 LPT ports |
| `src/block.c` | `map_floppy_drive()` | 0x41 | 0x01 or 0x41 | 1 or 2 floppies |
| `src/cdrom.c` | El Torito floppy emulation | 0x41 | 0x41 | Emulated floppy present |

Updates use `set_equipment_flags(clear, set)` in `src/biosvar.h`: the BDA word is set to `(current & ~clear) | set`, so each caller specifies the mask it affects and the new value for those bits.

---

## Related documentation

- [BIOS_Data_Area.md](BIOS_Data_Area.md) — documents `equipment_list_flags` at 40:10h and other BDA fields.
- [Interrupt_Descriptor_Table.md](Interrupt_Descriptor_Table.md) — lists INT 11h entry and handler.
