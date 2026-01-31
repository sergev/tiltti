# Extended BIOS Data Area (EBDA)

The Extended BIOS Data Area (EBDA) occupies physical addresses 0x9FC00-0xA0000 (1 KB) in the typical configuration. Its location can change when `CONFIG_MALLOC_UPPERMEMORY` is disabled or when option ROMs relocate it. The structure is defined in `src/std/bda.h` as `struct extended_bios_data_area_s`. EBDA access uses the `GET_EBDA(eseg, var)` and `SET_EBDA(eseg, var, val)` macros from `src/biosvar.h`, with the segment obtained from `get_ebda_seg()` (which reads BDA `ebda_seg`).

**INT 15h AH=C1h** returns the EBDA segment in ES for callers that need to locate it.

## Location and Size

- **Default address**: 0x9FC00-0xA0000 (segment = `(BUILD_LOWRAM_END - EBDA_SIZE_START*1024) / 16`)
- **EBDA_SIZE_START**: `DIV_ROUND_UP(sizeof(struct extended_bios_data_area_s), 1024)` = 1 KB
- **Relocation**: `malloc.c` can move the EBDA when expanding ZoneLow (via `relocate_ebda()`); BDA `ebda_seg` and `mem_size_kb` are updated accordingly

## EBDA Layout Overview

| Offset | Size | Field |
|--------|------|-------|
| 0x00 | 1 | size |
| 0x01 | 0x21 | reserved1[33] |
| 0x22 | 4 | far_call_pointer |
| 0x26 | 1 | mouse_flag1 |
| 0x27 | 1 | mouse_flag2 |
| 0x28 | 8 | mouse_data[8] |
| 0x30 | 0x0d | other1[13] |
| 0x3d | 32 | fdpt[2] |
| 0x5d | 0xC4 | other2[196] |
| 0x121 | (to 1KB) | Custom storage (beyond struct) |

## Initialization Flow

The EBDA is initialized in this order during POST:

1. **bda_init()** (`src/post.c`): Zeroes entire EBDA, sets `size` to `EBDA_SIZE_START`
2. **block_setup()** (`src/block.c`): `fill_fdpt()` populates `fdpt[0]` and `fdpt[1]` for each hard drive; INT 41h and 46h vectors point to fdpt
3. **Mouse INT 15h C2**: Mouse fields (`mouse_flag1`, `mouse_flag2`, `far_call_pointer`, `mouse_data`) are set at runtime by INT 15h C2 subfunctions

---

## Field Reference

### 0x00 - size (u8)

Size of the EBDA in kilobytes. Used when relocating the EBDA.

- **Initialization**: `bda_init()` in `src/post.c` sets to `EBDA_SIZE_START` (1)
- **Usage**: `malloc.c` reads via `GET_EBDA(ebda_seg, size)` in `zonelow_expand()` when relocating the EBDA

---

### 0x01 - reserved1[0x21] (u8 × 33)

Reserved. Zero-initialized. SeaBIOS does not use this region.

---

### 0x22 - far_call_pointer (struct segoff_s)

User-installed mouse callback. Far pointer to the routine invoked on mouse events (INT 15h C2/07 API).

- **Initialization**: Zero; set by INT 15h C2/07 (Set Mouse Handler Address)
- **Usage**: `mouse_15c207()` in `src/mouse.c` sets; `invoke_mouse_handler()` performs an lcall with (status, X, Y, Z)

---

### 0x26 - mouse_flag1 (u8)

Mouse packet index. Low 3 bits (0x07) = current byte index within the multi-byte mouse packet.

- **Initialization**: Zero; INT 15h C2/05 (Initialize Mouse) sets to 0
- **Usage**: `process_mouse()` in `src/mouse.c` increments until the packet is complete, then clears and invokes the user handler

---

### 0x27 - mouse_flag2 (u8)

Mouse configuration. Bit 7 (0x80) = user handler installed; low 3 bits = packet byte count (3 for standard PS/2 mouse).

- **Initialization**: INT 15h C2/05 sets to 3 (3-byte packets)
- **Usage**: `mouse_15c20001` checks bit 7 before enabling; `mouse_15c207` sets or clears bit 7 when installing/removing handler; `process_mouse` uses it for `package_count` and to check if the handler is installed

---

### 0x28 - mouse_data[8] (u8 × 8)

Mouse event data buffer. For standard 3-byte packets: [0] = status, [1] = X delta, [2] = Y delta.

- **Initialization**: Filled by `process_mouse()` as bytes arrive from the mouse hardware
- **Usage**: `invoke_mouse_handler()` reads `mouse_data[0]`, `mouse_data[1]`, `mouse_data[2]` as status, X, and Y; passes them to the user callback

---

### 0x30 - other1[0x0d] (u8 × 13)

Reserved. Zero-initialized. SeaBIOS does not use this region.

---

### 0x3d - fdpt[2] (struct fdpt_s × 2)

Fixed Disk Parameter Tables for hard drives 0 and 1. The format is defined in `src/std/disk.h` as `struct fdpt_s`: cylinders, heads, a0h_signature, phys_sectors, precompensation, reserved, drive_control_byte, phys_cylinders, phys_heads, landing_zone, sectors, checksum.

- **Initialization**: `fill_fdpt()` in `src/block.c` when `map_hd_drive()` runs for each hard drive. Sets cylinders, heads, sectors, precompensation (0xffff), drive_control_byte (0xc0 or 0xc8 for >8 heads), landing_zone. If logical-to-physical translation is present: phys_cylinders, phys_heads, phys_sectors, a0h_signature (0xa0), and checksum.
- **Usage**: INT 41h vector points to `fdpt[0]`; INT 46h vector points to `fdpt[1]`. INT 13h uses these for drive geometry.
- **Note**: Only the first two hard drives receive fdpt entries; drives with `hdid > 1` skip fdpt filling.

---

### 0x5d - other2[0xC4] (u8 × 196)

Reserved. Zero-initialized. SeaBIOS does not use this region.

---

### 0x121 - Custom Storage

Bytes from the end of `struct extended_bios_data_area_s` to the end of the 1 KB allocation. The comment in `bda.h` marks this as "Begin custom storage." SeaBIOS does not use this region in the current codebase; it is available for future use.

---

## Relocation

When `malloc_low()` needs to expand ZoneLow and the EBDA is at the end of low RAM, `zonelow_expand()` in `src/malloc.c` may call `relocate_ebda()` to move the EBDA downward. This updates BDA `ebda_seg` and `mem_size_kb`. EBDA contents are preserved via `memmove()`.
