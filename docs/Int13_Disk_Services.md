# Disk Services (INT 13h)

This page documents the BIOS disk services implemented in SeaBIOS and invoked via **INT 13h** (and the relocated floppy handler **INT 40h**). It lists every supported function (AH code), its purpose, register and packet inputs, outputs, and how it relates to other disk services and to the block layer.

Implementation is in `src/disk.c` (handler and dispatch) and `src/block.c` (drive mapping, geometry translation, EDD fill, and actual I/O dispatch). Data structures are in `src/std/disk.h` and `src/block.h`.

## Overview

- **INT 13h** is the main entry for disk services. The handler `handle_13()` in `src/disk.c` runs for all drives; it may redirect to the El Torito emulated drive or to `handle_legacy_disk()`.
- **INT 40h** is the relocated floppy handler: it calls the same internal logic as INT 13h with `DL` as the drive number, so floppy drive 0/1 are accessed the same way via INT 13h or INT 40h.
- **Success/error convention**: On return, the **carry flag (CF)** is clear on success and set on error. **AH** holds the status code (0 = success; non-zero values are defined in `src/std/disk.h` as `DISK_RET_*`). The last operation’s status is also stored in the BDA: floppy uses `floppy_last_status` (0x41), hard disk uses `disk_last_status` (0x75). **AH=01h** (Read Disk Status) returns that stored value and sets CF accordingly.

## Drive numbering

Drive selection is by **DL** (drive number). Ranges are defined in `src/block.h`:

| DL range        | Type    | Constant      | Notes |
|-----------------|---------|---------------|-------|
| 0x00–0x7F       | Floppy  | &lt; EXTSTART_HD (0x80) | Floppy 0 = 0x00, floppy 1 = 0x01 |
| 0x80–0xDF       | Hard disk | EXTSTART_HD (0x80) .. &lt; EXTSTART_CD (0xE0) | First HD = 0x80, second = 0x81, … |
| 0xE0–0xFF       | CD-ROM  | ≥ EXTSTART_CD (0xE0)   | First CD = 0xE0, … |

When El Torito CD-ROM emulation is active, one logical drive (floppy or hard) is emulated; accesses to that drive number are handled by the CD emulation layer, and only classic INT 13h functions (AH ≤ 16h) are supported on the emulated drive. AH=4Bh is handled before drive lookup and is used to get emulation info or terminate emulation.

## Calling conventions

- **Register layout** matches `struct bregs` in `src/bregs.h` (DS, ES, EDI/DI, ESI/SI, EBP/BP, EBX/BX, EDX/DX, ECX/CX, EAX/AX, and flags). INT 13h uses the standard register semantics below; segment:offset pointers use the segment in DS or ES as documented per function.
- **Drive number** is always in **DL** at invocation (except AH=4Bh, which is handled without resolving a drive from DL).

## Status codes

Return codes in **AH** (and in BDA last-status) are defined in `src/std/disk.h`:

| Code | Name | Meaning |
|------|------|----------|
| 0x00 | DISK_RET_SUCCESS | Success |
| 0x01 | DISK_RET_EPARAM | Invalid parameter or invalid function |
| 0x02 | DISK_RET_EADDRNOTFOUND | Address mark not found |
| 0x03 | DISK_RET_EWRITEPROTECT | Write protected |
| 0x06 | DISK_RET_ECHANGED | Media changed |
| 0x09 | DISK_RET_EBOUNDARY | DMA boundary error (e.g. transfer &gt; 64 KiB) |
| 0x0C | DISK_RET_EBADTRACK | Bad track |
| 0x20 | DISK_RET_ECONTROLLER | Controller error |
| 0x80 | DISK_RET_ETIMEOUT | Timeout |
| 0xAA | DISK_RET_ENOTREADY | Drive not ready |
| 0xB0 | DISK_RET_ENOTLOCKED | Not locked (unlock when not locked) |
| 0xB1 | DISK_RET_ELOCKED | Locked (eject while locked) |
| 0xB2 | DISK_RET_ENOTREMOVABLE | Volume not removable |
| 0xB4 | DISK_RET_ETOOMANYLOCKS | Too many lock levels |
| 0xC0 | DISK_RET_EMEDIA | Media error |

## Shared data structures

### Disk Address Packet (DAP) — `struct int13ext_s`

Used by extended read/write/verify/seek (AH=42h, 43h, 44h, 47h). Defined in `src/std/disk.h`.

| Offset | Field   | Type           | Description |
|--------|---------|----------------|-------------|
| 0      | size    | u8             | Packet size in bytes (typically 0x10) |
| 1      | reserved| u8             | Reserved (0) |
| 2      | count   | u16            | Sector count (input); updated to sectors transferred on return |
| 4      | data    | struct segoff_s| Buffer segment:offset for transfer |
| 8      | lba     | u64            | Starting LBA (64-bit) |

The handler reads the DAP from **DS:SI** and, for read/write/verify, updates the **count** field with the number of sectors actually transferred.

### EDD Get Drive Parameters buffer — `struct int13dpt_s`

Used by AH=48h. The caller provides a buffer at **DS:SI**; the BIOS fills it with EDD 3.0–style drive parameters (geometry, sector count, DPTE pointer, bus/interface type, etc.). Layout in `src/std/disk.h`: `size`, `infos`, `cylinders`, `heads`, `spt`, `sector_count`, `blksize`, `dpte`, `key`, device path fields, and optional checksum. Size and format depend on EDD version; `fill_edd()` in `src/block.c` fills this (ATA-specific or generic).

### El Torito packet — `struct eltorito_s`

Used by AH=4Bh. Defined in `src/std/disk.h`: `size`, `media`, `emulated_drive`, `controller_index`, `ilba`, `device_spec`, `buffer_segment`, `load_segment`, `sector_count`, `chs`. On call, the BIOS copies the current CD emulation state from internal `CDEmu` into the buffer at **DS:SI**. AL=0 requests termination of emulation.

---

## Classic functions (CHS-style)

These use cylinder/head/sector in registers (and optionally ES:BX for buffer). CHS is converted to LBA using the drive’s **logical geometry** from `getLCHS()` in `basic_access()`; see geometry translation in `src/block.c` (`setup_translation()`).

| AH | Function | Purpose | Applicability |
|----|----------|---------|---------------|
| 00h | Reset disk system | Reset controller/drive | Floppy, HD, CD |
| 01h | Read disk status | Return last operation status from BDA | Floppy, HD, CD |
| 02h | Read sectors | Read sectors (CHS) into ES:BX | Floppy, HD, CD, emulated |
| 03h | Write sectors | Write sectors from ES:BX (CHS) | Floppy, HD, CD (if writable), emulated |
| 04h | Verify sectors | Verify sectors (CHS) | Floppy, HD, CD, emulated |
| 05h | Format track | Format track (CHS) | Floppy, HD, CD (driver may no-op) |
| 08h | Get drive parameters | Return CHS geometry and drive count | Floppy, HD only (CD returns error) |
| 09h | Initialize drive parameters | Initialize drive parameters | Stub; all; returns success |
| 0Ch | Seek to cylinder | Seek to cylinder | Stub; all; returns success |
| 0Dh | Alternate disk reset | Alternate reset | Stub; all; returns success |
| 10h | Check drive ready | Test if drive is ready | Floppy, HD, CD |
| 11h | Recalibrate | Recalibrate drive | Stub; all; returns success |
| 14h | Controller diagnostic | Controller self-test | Stub; all; returns success |
| 15h | Read disk drive size | Return drive type and (for HD) sector count | Floppy, HD, CD |
| 16h | Detect disk change | Detect media change | Floppy only (HD returns error) |

**Floppy restriction**: When the target is a floppy (DL &lt; 0x80), only AH = 00h, 01h, 02h, 03h, 04h, 05h, 08h, 15h, 16h are accepted; any other AH returns unimplemented (EPARAM) without calling the full disk_13 dispatch.

---

### AH=00h — Reset disk system

- **Purpose**: Reset the disk controller/drive.
- **Inputs**: DL = drive number.
- **Outputs**: CF=0, AH=0 on success; otherwise CF=1, AH = status. BDA last-status updated.
- **Implementation**: `disk_1300()`; builds a `disk_op_s` with `CMD_RESET`, calls `send_disk_op()`. Drivers may return success by default if they do not implement reset (`default_process_op()` in `src/block.c`).
- **Relation**: Often used before or after other INT 13h calls to recover from errors.

---

### AH=01h — Read disk status

- **Purpose**: Return the status of the last disk operation for the given drive.
- **Inputs**: DL = drive number.
- **Outputs**: AH = last status (from BDA `floppy_last_status` or `disk_last_status`); CF is set if AH ≠ 0. No BDA update.
- **Implementation**: `disk_1301()`; reads BDA and sets CF from the stored value. Does not perform any I/O.
- **Relation**: All other INT 13h functions that complete via `disk_ret()` set the BDA last-status and AH/CF; AH=01h simply reports that value.

---

### AH=02h — Read disk sectors (CHS)

- **Purpose**: Read one or more sectors from the disk using CHS addressing.
- **Inputs**: DL = drive; DH = head; CH = cylinder low 8 bits; CL = bits 6–7 = cylinder high 2 bits, bits 0–5 = sector number (1-based); AL = sector count; ES:BX = data buffer.
- **Outputs**: On success: CF=0, AH=0, AL = number of sectors read. On error: CF=1, AH = status. BDA last-status updated. Buffer filled with sector data.
- **Implementation**: `disk_1302()` → `basic_access(regs, drive_fl, CMD_READ)`. CHS is validated against logical geometry and converted to LBA; transfer is sent via `send_disk_op()`. Sector count &gt; 128 or 0, or sector 0, or CHS out of range yields EPARAM. Total transfer size is limited by `process_op()` (e.g. 64 KiB boundary).
- **Relation**: Same CHS→LBA and buffer rules as AH=03h, 04h. For LBA and large disks use AH=42h.

---

### AH=03h — Write disk sectors (CHS)

- **Purpose**: Write one or more sectors to the disk using CHS addressing.
- **Inputs**: Same as AH=02h (DL, DH, CH, CL, AL, ES:BX).
- **Outputs**: On success: CF=0, AH=0, AL = sectors written. On error: CF=1, AH = status. BDA updated.
- **Implementation**: `disk_1303()` → `basic_access(regs, drive_fl, CMD_WRITE)`. Same CHS and boundary rules as AH=02h. Read-only media (e.g. CD) may return an error from the driver.
- **Relation**: Mirror of AH=02h; same geometry and `basic_access()` path.

---

### AH=04h — Verify disk sectors (CHS)

- **Purpose**: Verify sectors at the given CHS range (no data transfer to/from buffer).
- **Inputs**: Same as AH=02h (DL, DH, CH, CL, AL); ES:BX may be ignored for verify.
- **Outputs**: CF=0, AH=0 on success; otherwise CF=1, AH = status. BDA updated.
- **Implementation**: `disk_1304()` → `basic_access(regs, drive_fl, CMD_VERIFY)`. Same CHS and LBA conversion; driver may implement verify or return success by default.
- **Relation**: Same CHS path as 02h/03h; extended verify is AH=44h.

---

### AH=05h — Format disk track

- **Purpose**: Format a track at the given cylinder and head.
- **Inputs**: DL = drive; DH = head; CH = cylinder (low 8 bits); AL = sector count per track; ES:BX = pointer to format parameter table (sector layout).
- **Outputs**: CF=0, AH=0 on success; otherwise CF=1, AH = status. BDA updated.
- **Implementation**: `disk_1305()`; converts CHS to LBA for start of track, builds `CMD_FORMAT`, calls `send_disk_op()`. Validates cylinder/head/count against logical geometry. Many drivers do not implement format and return success via `default_process_op()`.
- **Relation**: Uses same geometry as read/write; ES:BX format table format is drive-specific.

---

### AH=08h — Get drive parameters

- **Purpose**: Return logical CHS geometry and number of drives of this type.
- **Inputs**: DL = drive number.
- **Outputs**: On success: CF=0, AH=0; AL=0; CH = max cylinder (low 8 bits); CL = (max cylinder &gt;&gt; 2) in bits 6–7, sectors per track in bits 0–5; DH = max head; DL = count of drives (floppy or HD). For floppy: ES:DI = diskette parameter table (segment 0xF000, `diskette_param_table2`); BX = floppy type. For HD: last logical cylinder is reduced by one (reserved). On CD: returns EPARAM (not supported).
- **Implementation**: `disk_1308()`; uses `getLCHS(drive_fl)` for geometry. Floppy count from `FloppyCount`, HD count from BDA `hdcount`. El Torito emulation can add an extra drive to the count. CD-ROM drives explicitly return error.
- **Relation**: Geometry here is the same logical CHS used by AH=02h/03h/04h/05h and by the FDPT (see [Fixed_Disk_Parameter_Table.md](Fixed_Disk_Parameter_Table.md)). For EDD-style parameters use AH=48h.

---

### AH=09h — Initialize drive parameters

- **Purpose**: Initialize drive parameters (historical/AT interface).
- **Inputs**: DL = drive number.
- **Outputs**: Success (stub). CF=0, AH=0. BDA last-status set to success.
- **Implementation**: `disk_1309()`; stub only (`DISK_STUB`), no actual initialization.
- **Relation**: No effect on geometry or other functions.

---

### AH=0Ch — Seek to cylinder

- **Purpose**: Seek the head to the given cylinder.
- **Inputs**: DL = drive; CH = cylinder low 8 bits; CL = cylinder high 2 bits (bits 6–7).
- **Outputs**: Success (stub). CF=0, AH=0.
- **Implementation**: `disk_130c()`; stub only.
- **Relation**: Optional optimization; I/O via 02h/03h/42h/43h does not require an explicit seek.

---

### AH=0Dh — Alternate disk reset

- **Purpose**: Alternate disk reset (historical).
- **Inputs**: DL = drive number.
- **Outputs**: Success (stub). CF=0, AH=0.
- **Implementation**: `disk_130d()`; stub only.
- **Relation**: Same conceptual role as AH=00h but not implemented.

---

### AH=10h — Check drive ready

- **Purpose**: Check if the drive is ready for access.
- **Inputs**: DL = drive number.
- **Outputs**: CF=0, AH=0 if ready; otherwise CF=1, AH = status (e.g. NOTREADY, TIMEOUT). BDA updated.
- **Implementation**: `disk_1310()`; sends `CMD_ISREADY` via `send_disk_op()`. Drivers may return success by default.
- **Relation**: Can be used before read/write to avoid unnecessary errors.

---

### AH=11h — Recalibrate drive

- **Purpose**: Recalibrate the drive (seek to cylinder 0).
- **Inputs**: DL = drive number.
- **Outputs**: Success (stub). CF=0, AH=0.
- **Implementation**: `disk_1311()`; stub only.
- **Relation**: Historical; no effect in this implementation.

---

### AH=14h — Controller internal diagnostic

- **Purpose**: Run controller internal diagnostic.
- **Inputs**: DL = drive number.
- **Outputs**: Success (stub). CF=0, AH=0.
- **Implementation**: `disk_1314()`; stub only.
- **Relation**: No effect in this implementation.

---

### AH=15h — Read disk drive size

- **Purpose**: Return drive type and (for hard disks) total sector count in INT 13h geometry.
- **Inputs**: DL = drive number.
- **Outputs**: CF=0, AH=0. For floppy or CD: AH on return = 1 (drive present, type 1). For hard disk: AH = 3 (drive present, type 3); CX:DX = 32-bit sector count (CX = high word, DX = low word) for the logical CHS space (max cylinder minus one for HD, then cylinders×heads×sectors). BDA last-status set to success.
- **Implementation**: `disk_1315()`; for HD uses `getLCHS()` and computes sectors as `(nlc-1)*nlh*nls`; for floppy/CD returns AH=1 only.
- **Relation**: Sector count matches the geometry returned by AH=08h. For 64-bit sector count and EDD info use AH=48h.

---

### AH=16h — Detect disk change

- **Purpose**: Detect if floppy media has been changed.
- **Inputs**: DL = drive number.
- **Outputs**: For floppy: always reports “changed” (ECHANGED), CF=1, AH=0x06. For hard disk: returns EPARAM (invalid), CF=1, AH=0x01.
- **Implementation**: `disk_1316()`; floppy path always returns DISK_RET_ECHANGED; HD path returns DISK_RET_EPARAM.
- **Relation**: Floppy-only; CD media change is reported via AH=49h.

---

## Extended (EDD) functions

These use the Disk Address Packet (DAP) at DS:SI for LBA and buffer, and/or EDD parameter buffers. They are not available on floppy when invoked through the floppy path (floppy_13 allows only AH ≤ 16h and only specific values). They are available on hard disk and CD; on the El Torito emulated drive, AH &gt; 16h is rejected.

| AH | Function | Purpose | Applicability |
|----|----------|---------|---------------|
| 41h | Installation check | Check for EDD and return version/capabilities | All (HD, CD; not on floppy path) |
| 42h | Extended read | Read sectors (LBA) using DAP | HD, CD, emulated (emulated: no) |
| 43h | Extended write | Write sectors (LBA) using DAP | HD, CD (if writable) |
| 44h | Extended verify | Verify sectors (LBA) using DAP | HD, CD |
| 45h | Lock/unlock drive | Lock, unlock, or query lock (AL subfunction) | HD (always success), CD (real lock) |
| 46h | Eject media | Eject removable media | CD only |
| 47h | Extended seek | Seek to LBA (DAP) | HD, CD |
| 48h | Get drive parameters (EDD) | Fill EDD parameter buffer at DS:SI | HD, CD |
| 49h | Extended media change | Report media change | HD (success), CD (changed) |
| 4Eh | Set hardware configuration | Set hardware config (AL subfunction) | Stubs for AL=01,03,04,06 |

---

### AH=41h — Installation check (EDD)

- **Purpose**: Report whether IBM/MS EDD extensions are supported and return version and capability flags.
- **Inputs**: DL = drive number.
- **Outputs**: BX = 0xAA55 (signature); CX = 0x0007 (extended disk access + EDD + removable supported); AH = 0x30 (EDD version 3.0); CF=0. BDA last-status set to success.
- **Implementation**: `disk_1341()`; sets registers and returns success. No I/O. Unsupported on floppy path (floppy_13 does not allow 41h).
- **Relation**: Call before using AH=42h–49h; BX=0xAA55 and CX bits indicate support.

---

### AH=42h — Extended read (LBA)

- **Purpose**: Read sectors using 64-bit LBA and a DAP; no CHS limit.
- **Inputs**: DL = drive number; DS:SI = pointer to `struct int13ext_s` (size, count, data segment:offset, lba).
- **Outputs**: CF=0, AH=0 on success; AL unchanged. DAP `count` field updated to number of sectors transferred. On error: CF=1, AH = status. BDA updated. Total transfer limited (e.g. 64 KiB in `process_op()`).
- **Implementation**: `disk_1342()` → `extended_access(regs, drive_fl, CMD_READ)`. Reads LBA and count from DAP; validates LBA &lt; drive sector count; performs transfer and updates DAP count.
- **Relation**: LBA counterpart of AH=02h; same DAP used by AH=43h, 44h, 47h.

---

### AH=43h — Extended write (LBA)

- **Purpose**: Write sectors using 64-bit LBA and DAP.
- **Inputs**: Same as AH=42h (DL, DS:SI DAP).
- **Outputs**: Same as AH=42h (DAP count updated, CF, AH, BDA). Read-only media may return error.
- **Implementation**: `disk_1343()` → `extended_access(regs, drive_fl, CMD_WRITE)`.
- **Relation**: LBA counterpart of AH=03h; same DAP as 42h/44h/47h.

---

### AH=44h — Extended verify (LBA)

- **Purpose**: Verify sectors at LBA specified in DAP.
- **Inputs**: Same as AH=42h (DL, DS:SI DAP).
- **Outputs**: CF=0, AH=0 on success; DAP count updated to sectors verified. On error: CF=1, AH = status. BDA updated.
- **Implementation**: `disk_1344()` → `extended_access(regs, drive_fl, CMD_VERIFY)`.
- **Relation**: LBA counterpart of AH=04h.

---

### AH=45h — Lock/unlock drive

- **Purpose**: Lock or unlock removable media (prevent eject), or query lock status.
- **Inputs**: DL = drive number; AL = subfunction: 0x00 = lock, 0x01 = unlock, 0x02 = lock status.
- **Outputs**: For hard disk: always success (CF=0, AH=0). For CD: lock (AL=0) increments lock count, returns AL=1 and success or ETOOMANYLOCKS; unlock (AL=1) decrements, returns AL=1 or 0 and success or ENOTLOCKED; status (AL=2) returns AL=1 if locked else 0 and success. On error: CF=1, AH = status. BDA updated.
- **Implementation**: `disk_1345()`; for DL &lt; EXTSTART_CD returns success; for CD uses `CDRom_locks[]` indexed by (DL - EXTSTART_CD). Other AL values → EPARAM.
- **Relation**: Eject (AH=46h) fails if lock count ≠ 0 (ELOCKED).

---

### AH=46h — Eject media

- **Purpose**: Eject removable media.
- **Inputs**: DL = drive number.
- **Outputs**: CF=0, AH=0 on success. If drive is not CD: ENOTREMOVABLE. If CD is locked: ELOCKED. Actual eject is performed via INT 15h AH=52h; if that fails, returns ELOCKED. BDA updated.
- **Implementation**: `disk_1346()`; only CD (DL ≥ EXTSTART_CD); checks `CDRom_locks[]`; calls `call16_int(0x15, ...)` with AH=0x52.
- **Relation**: Must unlock (AH=45h AL=01h) before eject if lock count &gt; 0.

---

### AH=47h — Extended seek (LBA)

- **Purpose**: Seek to the LBA given in the DAP (no data transfer).
- **Inputs**: DL = drive number; DS:SI = DAP (LBA and size/count; buffer not used for seek).
- **Outputs**: CF=0, AH=0 on success; otherwise CF=1, AH = status. BDA updated. DAP count may be updated (implementation uses same extended_access path).
- **Implementation**: `disk_1347()` → `extended_access(regs, drive_fl, CMD_SEEK)`. Drivers may return success by default.
- **Relation**: LBA counterpart of seek; optional for correctness of read/write.

---

### AH=48h — Get drive parameters (EDD)

- **Purpose**: Fill the caller’s buffer at DS:SI with EDD 3.0 drive parameters (geometry, sector count, block size, DPTE, bus/interface type, etc.).
- **Inputs**: DL = drive number; DS:SI = pointer to buffer (e.g. `struct int13dpt_s`).
- **Outputs**: CF=0, AH=0 on success; buffer filled. On error: CF=1, AH = status. BDA updated.
- **Implementation**: `disk_1348()` calls `fill_edd(SEGOFF(regs->ds, regs->si), drive_fl)`. `fill_edd()` in `src/block.c` dispatches to ATA-specific or generic filler; fills size, geometry, sector_count, blksize, dpte, key, host_bus, iface_type, iface_path, and optional checksum.
- **Relation**: EDD version of drive info; CHS geometry is in the buffer and matches logical geometry used by AH=08h. See also [Fixed_Disk_Parameter_Table.md](Fixed_Disk_Parameter_Table.md) for FDPT (IVT 0x41/0x46).

---

### AH=49h — Extended media change

- **Purpose**: Report whether media in the drive has changed.
- **Inputs**: DL = drive number.
- **Outputs**: For hard disk: always success (CF=0, AH=0). For CD: returns “changed”: CF=1, AH=0x06 (ECHANGED). BDA not set for CD path (uses `set_invalid()`).
- **Implementation**: `disk_1349()`; HD path returns success; CD path sets CF and AH to DISK_RET_ECHANGED.
- **Relation**: CD analogue of AH=16h (floppy); used by OS to detect CD swap.

---

### AH=4Eh — Set hardware configuration

- **Purpose**: Set hardware configuration (subfunction in AL).
- **Inputs**: DL = drive number; AL = subfunction (0x01, 0x03, 0x04, 0x06 supported as stubs).
- **Outputs**: For AL=01, 03, 04, 06: success (CF=0, AH=0). For any other AL: EPARAM (CF=1, AH=0x01). BDA updated.
- **Implementation**: `disk_134e()` switches on AL; `disk_134e01`, `disk_134e03`, `disk_134e04`, `disk_134e06` are stubs that return success; default is `disk_134eXX` → EPARAM.
- **Relation**: Stub only; no configuration change.

---

## El Torito — AH=4Bh

- **Purpose**: Get CD-ROM emulation state and optionally terminate emulation. Handled in `handle_13()` before drive lookup; DL is not used to select a drive for this call.
- **Inputs**: AH = 0x4B; AL = 0x00 to terminate emulation (other values reserved); DS:SI = pointer to buffer for `struct eltorito_s`.
- **Outputs**: BIOS copies internal `CDEmu` state into the buffer at DS:SI. If AL=0x00, emulation is terminated (`CDEmu.media` set to 0). CF=0, AH=0. BDA updated.
- **Implementation**: `cdemu_134b()`; `memcpy_far()` from internal CDEmu to DS:SI; if AL==0 clears media. Only present when CONFIG_CDROM_EMU.
- **Relation**: When emulation is active, the emulated drive accepts only AH ≤ 16h; AH=4Bh is the way to stop emulation and get emulation parameters.

---

## Unsupported / unimplemented functions

Any AH not listed above (e.g. AH=06h, 07h, 0Ah, 0Bh, 0Eh, 0Fh, 12h, 13h, 17h–40h, 4Ah, 4Ch–4Dh, 4Fh and above) falls through to `disk_13XX()` in the main dispatch (or to the same from `floppy_13()` for disallowed AH on floppy). The handler calls `disk_ret_unimplemented(regs, DISK_RET_EPARAM)`: CF=1, AH=0x01, and the BDA last-status is set. No other action is performed.

---

## Internal flow summary

- **Entry**: INT 13h → `handle_13()`; INT 40h → `handle_40()` → `handle_legacy_disk(regs, regs->dl)`.
- **Routing**: By DL: floppy (DL &lt; 0x80) → `getDrive(EXTTYPE_FLOPPY, …)` → `floppy_13()`; HD (0x80–0xDF) → `getDrive(EXTTYPE_HD, …)` → `disk_13()`; CD (≥ 0xE0) → `getDrive(EXTTYPE_CD, …)` → `disk_13()`. If CD emulation is active, AH=4Bh is handled first; accesses to the emulated drive number go to the CD emulation drive with AH ≤ 16h only.
- **I/O path**: Read/write/verify/format/seek/ready/reset are mapped to `disk_op_s` and sent via `send_disk_op()` → `process_op()` in `src/block.c`. `process_op()` enforces the 64 KiB transfer limit (DISK_RET_EBOUNDARY) and dispatches to the appropriate driver (floppy, ATA, AHCI, USB, virtio, SCSI, NVMe, etc.). Geometry comes from `drive->lchs` (set by `setup_translation()` in block.c).

For BDA layout and disk-related fields (e.g. `floppy_last_status`, `disk_last_status`, `hdcount`, `disk_interrupt_flag`), see [BIOS_Data_Area.md](BIOS_Data_Area.md).
