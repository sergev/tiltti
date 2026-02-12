# Memory Size (INT 12h)

This page documents the BIOS Memory Size service implemented in SeaBIOS and invoked via **INT 12h**. It describes the single function: return conventional memory size in kilobytes. There are no subfunctions (no AH dispatch).

Implementation is in [`src/misc.c`](src/misc.c) (handler `handle_12()`). The value is stored in the BIOS Data Area at 40:13h (`mem_size_kb` in [`src/std/bda.h`](src/std/bda.h)). The IVT vector 0x12 is set in [`src/post.c`](src/post.c); the entry point `entry_12` is at fixed address 0xf841 in [`src/romlayout.S`](src/romlayout.S).

## Overview

- **INT 12h** is the Memory Size interrupt. It has a single function: return conventional memory size in KB in AX.
- **Entry**: `entry_12` at 0xf841 (via `IRQ_ENTRY_ARG 12` in `src/romlayout.S`).
- **Handler**: `handle_12()` in `src/misc.c` — reads BDA `mem_size_kb` and returns it in the caller's AX.
- **Data source**: BDA at segment 0x40, offset 0x13 (MEM 0040:0013h).

## Calling convention

- **Inputs**: None. No register inputs are used.
- **Output**: **AX** = conventional memory size in kilobytes (16-bit). On 32-bit callers, the high word of EAX is not defined by the BIOS; callers that interpret the result as a 16-bit value should use only the low word.
- **Registers**: The handler uses `struct bregs` in `src/bregs.h`; on return, only AX is set; other registers are preserved by the entry/exit code.

## Implementation flow

```mermaid
flowchart LR
    INT12[INT 12h]
    INT12 --> Entry12[entry_12]
    Entry12 --> Handle12[handle_12]
    Handle12 --> BDA[mem_size_kb at 40:13h]
    BDA --> AX[AX = memory size KB]
```

## Data source

The returned value is the 16-bit word at BDA offset 0x13 (`mem_size_kb`). It represents the size of conventional (base) memory in kilobytes — i.e., the contiguous RAM below 1 MB that ends where the Extended BIOS Data Area (EBDA) begins.

### Initialization

`bda_init()` in [`src/post.c`](src/post.c) sets `mem_size_kb` during POST:

- Formula: `mem_size_kb = ebda_seg / (1024/16)` = `ebda_seg / 64`
- Rationale: In real mode, segment `ebda_seg` corresponds to physical address `ebda_seg * 16`; dividing that by 1024 yields the size in KB of memory from 0 up to (but not including) the EBDA.
- Default: `ebda_seg` is set to `EBDA_SEGMENT_START` = `(BUILD_LOWRAM_END - EBDA_SIZE_START*1024) / 16`. With `BUILD_LOWRAM_END` = 0xA0000 and a 1 KB EBDA, `ebda_seg` = 0x9FC0 and **mem_size_kb = 639** KB (typical PC value).

When `CONFIG_MALLOC_UPPERMEMORY` is disabled, `bda_init()` may place the EBDA lower in RAM; in that case `ebda_seg` and thus `mem_size_kb` are smaller.

### Runtime updates

When the low-memory allocator needs to grow and the EBDA is at the end of low RAM, [`src/malloc.c`](src/malloc.c) may call `relocate_ebda()` from `zonelow_expand()` to move the EBDA downward. That function updates both BDA `ebda_seg` and **mem_size_kb** (setting `mem_size_kb = newebda / 1024`). Subsequent INT 12h calls then return the new, reduced conventional memory size.

## Related documentation

- [BIOS_Data_Area.md](BIOS_Data_Area.md) — documents `mem_size_kb` at 40:13h and other BDA fields.
- [Extended_BIOS_Data_Area.md](Extended_BIOS_Data_Area.md) — describes EBDA placement and relocation, which determines the value returned by INT 12h.
- [Interrupt_Descriptor_Table.md](Interrupt_Descriptor_Table.md) — lists INT 12h entry and handler.
