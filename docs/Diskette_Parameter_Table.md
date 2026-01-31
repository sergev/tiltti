# Diskette Parameter Table

The Diskette Parameter Table is a BIOS data structure that holds initialization parameters for the floppy disk controller. It is pointed to by interrupt vector **0x1E**. INT 1E is **not an interrupt handler** but a far pointer to this table. The structure is used during formatting, reading, and writing to floppy disks.

The data structures are defined in `src/std/disk.h` as `struct floppy_dbt_s` (base table) and `struct floppy_ext_dbt_s` (extended table). This layout follows the IBM PC/AT design; the extended fields come from the IBM SurePath BIOS.

## Table Locations

SeaBIOS maintains two instances:

| Instance | Size | Location | Purpose |
|----------|------|----------|---------|
| `diskette_param_table` | 11 bytes | F000:EFC7 (fixed) | Legacy IBM PC location. Some software reads F000:EFC7 directly for compatibility. |
| `diskette_param_table2` | 14 bytes | f-segment (VARFSEG) | Primary table. IVT vector 0x1E points here. Used by INT 13h AH=08. |

The fixed table at F000:EFC7 is defined in `src/misc.c` with `VARFSEGFIXED(0xefc7)`. The extended table `diskette_param_table2` lives in the BIOS f-segment.

During initialization, `floppy_setup()` copies the base 11 bytes from `diskette_param_table2` into `diskette_param_table`, then sets IVT 0x1E to point at `diskette_param_table2`.

## struct floppy_dbt_s (11 bytes)

The base table contains 11 bytes:

| Offset | Field | Type | SeaBIOS Init | Purpose |
|--------|-------|------|--------------|---------|
| 0 | specify1 | u8 | 0xAF | FDC SPECIFY byte 1: step rate (bits 7–4), head unload time (bits 3–0) |
| 1 | specify2 | u8 | 0x02 | FDC SPECIFY byte 2: head load time (bits 7–1), DMA flag (bit 0: 0=DMA) |
| 2 | shutoff_ticks | u8 | 37 | Motor off delay in timer ticks (~2 s at 18.2 Hz) |
| 3 | bps_code | u8 | 0x02 | Log2(bytes/128): 0=128, 1=256, 2=512, 3=1024 |
| 4 | sectors | u8 | 18 | Sectors per track (1.44 MB = 18) |
| 5 | interblock_len | u8 | 0x1B | Gap between sectors for read/write (3.5" MFM) |
| 6 | data_len | u8 | 0xFF | Sector length when bps_code=0; ignored otherwise |
| 7 | gap_len | u8 | 0x6C | Gap length when formatting |
| 8 | fill_byte | u8 | 0xF6 | Format filler byte |
| 9 | settle_time | u8 | 0x0F | Head settle time in milliseconds (15 ms) |
| 10 | startup_time | u8 | 8 | Motor start delay in 1/8 s units (8 × 0.125 s = 1 s) |

### Field Details

**specify1** — First byte of the Floppy Disk Controller SPECIFY command:
- Bits 7–4: Step rate time (ms). Value 0x0A yields ~12 ms step rate.
- Bits 3–0: Head unload time. Value 0x0F = 240 ms (max).

**specify2** — Second byte of the SPECIFY command:
- Bits 7–1: Head load time. Value 0x01 = (1+1)×2 = 4 ms.
- Bit 0: Non-DMA flag. 0 = DMA mode (used by SeaBIOS); 1 = non-DMA.

`specify1` and `specify2` are sent to the FDC via the SPECIFY command in `floppy_drive_specify()` (`src/hw/floppy.c`).

**shutoff_ticks** — Countdown before turning off the drive motor. When the motor is started, this value is written to `floppy_motor_counter` in the BDA. The timer tick handler (`floppy_tick()`) decrements it each tick (~18.2 Hz); when it reaches zero, motors are turned off. SeaBIOS uses 37 ticks (~2 seconds).

**bps_code** — Bytes-per-sector encoding: Log2(bytes/128). 0=128, 1=256, 2=512, 3=1024. SeaBIOS uses 0x02 (512 bytes) for standard sectors.

**sectors** — Maximum number of sectors per track. 18 for 1.44 MB floppies.

**interblock_len** — Gap length between sectors during read/write. 0x1B for 3.5" MFM disks; 0x2A for 5.25" MFM.

**data_len** — Sector data length used when `bps_code` is 0 (variable-length sectors). Ignored when `bps_code` ≠ 0. SeaBIOS sets 0xFF (not used because `bps_code` = 0x02).

**gap_len** — Gap length when formatting a track. 0x6C for 3.5"; 0x50 for 5.25".

**fill_byte** — Byte pattern written to sectors during format. Default 0xF6.

**settle_time** — Head settle delay in milliseconds after a seek, before reading. SeaBIOS initializes to 15 ms for compatibility but does not use this field in its seek/read paths.

**startup_time** — Motor spin-up delay in 1/8 second units. SeaBIOS uses 8 (= 1 second). When the motor was off, `floppy_drive_pio()` waits `startup_time × 125` ms before accessing the drive.

## struct floppy_ext_dbt_s (14 bytes)

The extended table embeds the base table and adds three IBM SurePath fields:

```c
struct floppy_ext_dbt_s {
    struct floppy_dbt_s dbt;
    u8 max_track;
    u8 data_rate;
    u8 drive_type;
};
```

| Offset | Field | Type | SeaBIOS Init | Purpose |
|--------|-------|------|--------------|---------|
| 11 | max_track | u8 | 79 | Maximum track number (0–79 for 80-track drives) |
| 12 | data_rate | u8 | 0 | Transfer rate: 0=500K, 1=300K, 2=250K, 3=1M bps |
| 13 | drive_type | u8 | 4 | CMOS drive type (4 = 1.44 MB 3.5") |

**max_track** — Highest track index. 79 for standard 80-track drives.

**data_rate** — Data transfer rate code. Matches `FloppyInfo[].data_rate` in `src/hw/floppy.c`. Written to the Digital Input Register (port 0x3F7) in `floppy_drive_readid()` during media sense. Values: 0=500K (1.44 MB, 1.2 MB), 1=300K, 2=250K (720 KB), 3=1M (2.88 MB).

**drive_type** — Drive type index matching `FloppyInfo[]` (1=360K, 2=1.2M, 3=720K, 4=1.44M, 5=2.88M, etc.). Used for geometry and INT 13h AH=08.

## Initialization

Initialization happens in `floppy_setup()` (`src/hw/floppy.c`):

1. **Copy base table**: `memcpy(&diskette_param_table, &diskette_param_table2, sizeof(diskette_param_table))` — copies the 11-byte base table to the fixed F000:EFC7 location.

2. **Set IVT 0x1E**: `SET_IVT(0x1E, SEGOFF(SEG_BIOS, diskette_param_table2))` — points vector 0x1E at the extended table.

3. **Drive setup**: Floppy drives are enumerated from CMOS or romfile; each drive gets geometry from `FloppyInfo[]`. The table values are tuned for 1.44 MB (drive type 4).

The SPECIFY command (which programs `specify1` and `specify2` into the FDC) is sent from `floppy_drive_specify()` during `floppy_prep()`, before the first read/write after recalibration or media sense.

## Usage in SeaBIOS

- **Read/Write/Format**: `floppy_read()`, `floppy_write()`, and `floppy_format()` use hardcoded constants (`FLOPPY_SIZE_CODE`, `FLOPPY_GAPLEN`, `FLOPPY_DATALEN`, etc.) that match the table. The table values are for INT 13h compatibility and for software that reads them.

- **Motor timeout**: When a floppy operation starts, `floppy_motor_counter` in the BDA is set to `shutoff_ticks` (or 255 for an active transfer). `floppy_tick()` decrements it; when it reaches 0, motors are turned off.

- **INT 13h AH=08 (Get Drive Parameters)**: Returns ES:DI pointing at `diskette_param_table2` so callers can read the parameter table (see `disk_1308()` in `src/disk.c`).

If the table is modified by software, INT 13h AH=00h (Reset Disk) should be called to reprogram the floppy controller.

## Reference: Gap and Bytes-Per-Sector Values

Standard values for common formats (MFM):

| bps_code | Bytes/Sector | Sectors/Track | interblock_len (read/write) | gap_len (format) |
|----------|--------------|---------------|-----------------------------|------------------|
| 1 | 256 | 18 | 0x0A | 0x0C |
| 1 | 256 | 16 | 0x20 | 0x32 |
| 2 | 512 | 8 | 0x2A | 0x50 |
| 2 | 512 | 9 | 0x1B | 0x6C |
| 3 | 1024 | 4 | 0x80 | 0xF0 |
| 4 | 2048 | 2 | 0xC8 | 0xFF |
| 5 | 4096 | 1 | 0xC8 | 0xFF |

5.25" disks typically use read gap 0x2A, format gap 0x50. 3.5" 1.44 MB uses read gap 0x1B, format gap 0x6C.
