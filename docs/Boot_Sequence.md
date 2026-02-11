# MS-DOS 3.30 Boot Sequence

This document describes how MS-DOS starts from a floppy boot sector through to the command prompt. It is based on [AG.DOC](https://github.com/AR1972/DOS3.3/blob/master/AG.DOC) (Chapters 4 and 6) and the boot sector source [MSBOOT.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BOOT/MSBOOT.ASM).

---

## 1. Overview

The boot process follows this high-level flow:

**ROM → Boot sector → IO.SYS (BIOS) → SYSINIT → MSDOS.SYS → COMMAND.COM**

- The **system ROM** loads the first sector of the boot drive into RAM and jumps to it.
- The **boot sector** verifies that IO.SYS and MSDOS.SYS are present, loads IO.SYS (and in this implementation the full BIOS including the leading portion that will be at 70:0), then transfers control to the BIOS entry point.
- **IO.SYS** contains the resident device drivers and initialization code; it eventually calls **SYSINIT**.
- **SYSINIT** relocates itself and MSDOS.SYS, initializes MS-DOS, processes CONFIG.SYS, and **executes COMMAND.COM**.
- **COMMAND.COM** loads its transient portion and displays the command prompt.

References: [AG.DOC](https://github.com/AR1972/DOS3.3/blob/master/AG.DOC) Chapter 4 (Disk Structure and Bootstrap Loading) and Chapter 6 (SYSINIT and MS-DOS Initialization).

---

## 2. ROM Bootstrap (Pre–Boot Sector)

Before the boot sector runs:

- The system ROM performs hardware initialization and device checks.
- It loads **one sector** from the boot drive: **track 0, head 0, sector 1**.
- That sector is placed at physical address **07C00h**.
- The CPU is left in this state:
  - **CS = DS = ES = SS = 0**
  - **IP = 7C00h**
  - **SP = 0400h**

Execution therefore starts at 0:7C00h (the first byte of the boot sector).

Source: [MSBOOT.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BOOT/MSBOOT.ASM) lines 26–30.

---

## 3. Boot Sector Actions (MSBOOT.ASM)

The code in the boot sector performs the following steps.

### 3.1 Stack Setup

- **CLI** — disable interrupts until the disk parameter table is set up.
- **SS = 0**, **SP = 7C00h** (ORIGIN), so the stack grows downward from just below the boot sector.
- **ES** is set to the same segment as the boot code (0) for the following steps.

Interrupts stay disabled to avoid using an invalid disk parameter table during a possible reboot.

### 3.2 Disk Parameter Table

- The ROM **INT 1Eh** vector (at offset **1Eh×4** in the Interrupt Vector Table) points to the ROM disk parameter table (11 bytes).
- The boot sector has a local 11-byte table **SEC9** (some fields pre-filled, e.g. DISK_EOT = 12h).
- The code copies the ROM table into SEC9, but for each byte: if the **boot sector template** has a **non-zero** value, that value is kept; otherwise the value from the ROM is used.
- The **INT 1Eh** vector is then updated so it points to **SEC9** (segment remains from the original vector; offset is SEC9).
- **STI** — interrupts are re-enabled.

This ensures the BIOS disk driver uses parameters appropriate for the boot media.

### 3.3 Disk Reset

- **INT 13h, AH = 0** — reset the disk system.
- If the call fails (carry set), the code jumps to **RERROR** and displays "Disk Boot failure" (see Error Handling below).

### 3.4 Directory and BIOS Sector Calculation

Using the BPB in the boot sector:

- **DIR$** = logical sector number of the first root directory sector:
  - `DIR$ = cFat × cSecFat + cSecRes + cSecHid`
- **BIOS$** = logical sector where **IO.SYS** starts (first sector of the “data” area after the root directory):
  - Directory size in sectors = `ceil(DirNum × 32 / ByteSec)` (32 bytes per directory entry).
  - `BIOS$ = DIR$ + directory size in sectors`

So the boot sector computes where the root directory begins and where the first file (IO.SYS) must begin.

### 3.5 Directory Verification

- The first **directory sector** is read into memory at **00500h** using **INT 13h, AH = 2** (read sectors), with the logical sector from **DIR$** converted to head/track/sector via **DODIV**.
- The first directory entry (11 bytes) is compared to the string **"IO      SYS"**.
- The second directory entry (11 bytes) is compared to **"MSDOS   SYS"** (at offset 20h in the sector).
- If either comparison fails, the code goes to **CKERR**: displays "Non-System disk or disk error" and "Replace and strike any key when ready", waits for a key (**INT 16h, AH = 0**), restores the original INT 1Eh vector, and invokes **INT 19h** to retry the bootstrap.

Only the first directory sector is checked; IO.SYS and MSDOS.SYS must be the first two files in the root directory.

### 3.6 Load IO.SYS

- The **file size** of IO.SYS is taken from the first directory entry at offset **1Ch** (labeled **BiosFS** in the source; it overlays the same offset in the directory buffer at 500h).
- Number of sectors to read = `(size / 512) + 1` (rounded up, plus one extra to be safe).
- IO.SYS is loaded at **0:700h** (same linear address as **70:0**). The boot sector sets the transfer address to ES:BX = 0:700h (BX = BioOff, ES = 0); the **BIOS** entry point is **70:0**, so the first sector of IO.SYS is placed at that address and the rest follows.
- Reading is done in a loop:
  - **DODIV** converts the current logical sector (**BIOS$**) into **track**, **head**, and **sector** (sector is 1-based).
  - The number of sectors to read in one INT 13h call is limited to what fits on the remainder of the current track (**SECLIM − CURSEC + 1**).
  - **Rev 3.31 fix:** The request size is capped by **COUNT** (remaining sectors to load). So the code uses `min(COUNT, sectors remaining on track)` to avoid reading too many sectors and overwriting the boot sector or stack.
  - **INT 13h, AH = 2** is used with: **DL** = PHYDRV (physical drive), **DH** = head, **CH/CL** = cylinder and sector (CL low 6 bits = sector, CH + CL high 2 bits = cylinder).
  - After each successful read, **COUNT** is decremented; when it reaches **0**, loading is done (**JZ DISKOK**).
  - **BIOS$** and the buffer pointer **BX** are advanced for the next chunk.

If any read fails, the code goes to **RERROR** (see Error Handling).

### 3.7 Transfer to BIOS

When all of IO.SYS has been loaded:

- **CH** = Media byte (from BPB).
- **DL** = **PhyDrv** (physical drive number for INT 13h).
- **BX** = **BIOSAV** (logical sector number of the first sector of IO.SYS on disk, 0-based “first data sector” for the driver).
- **JMP FAR 70:0** — control is transferred to the BIOS entry point at segment 70h, offset 0.

The BIOS (IO.SYS) entry point is **INIT** in [MSINIT.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BIOS/MSINIT.ASM); it expects these register conventions for MS-DOS initialization.

---

## 4. BIOS Interrupt Calls Used by the Boot Sector

| INT  | AH   | Purpose |
|------|------|--------|
| 13h  | 0    | Reset disk system |
| 13h  | 2    | Read disk sectors |
| 10h  | 0Eh  | Write character in teletype mode (error messages); BH = 0, BL = attribute (7) |
| 16h  | 0    | Read one character from keyboard (wait for key on error) |
| 19h  | —    | Bootstrap loader: reload boot sector and retry boot |

Source: [MSBOOT.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BOOT/MSBOOT.ASM) (e.g. lines 174, 207–208, 234, 239, 261, 329–331).

---

## 5. Boot Sector Layout (BPB / Media Descriptor)

The first sector contains both code and the **BIOS Parameter Block (BPB)** / media descriptor table so the boot code can compute directory and file positions without assuming a fixed disk format.

Approximate layout (from MSBOOT.ASM and AG.DOC 4.4):

- **Bytes 0–2:**  Jump to boot code (e.g. `JMP START`).
- **Bytes 3–10:** OEM name and version (e.g. `"MSDOS"` + `"3.3"`).
- **Media descriptor table / BPB:**
  ByteSec, sectors per allocation unit, cSecRes, cFat, DirNum, total sectors (and extended fields), MEDIA, cSecFat, SECLIM (sectors per track), HDLIM (heads), cSecHid, and optional extended BPB fields.
  The boot code uses these to compute DIR$ and BIOS$ and to convert logical sectors to head/track/sector.
- **Disk parameter table image (SEC9):** 11 bytes used to build the INT 1Eh table.
- **Byte 509 (0-based):** **PHYDRV** — physical drive number for INT 13h. FORMAT and SYS expect this at a fixed offset.
- **Bytes 510–511:** Boot signature **55h, 0AAh** so the ROM recognizes a valid boot sector.

The exact BPB layout is defined in the boot sector source; the media descriptor table is equivalent to the BPB with extra physical layout (heads, tracks, sectors).

---

## 6. IO.SYS Entry (INIT)

- **Entry point:** segment **70h**, offset **0** (BIOSEG:0), i.e. **INIT** in [MSINIT.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BIOS/MSINIT.ASM).
- **Registers** passed from the boot sector:
  - **DL** = INT 13h drive number we booted from.
  - **CH** = media byte.
  - **BX** = first data sector on disk (0-based), i.e. logical sector of the start of IO.SYS.

INIT then:

- Saves the original **INT 13h** and **INT 19h** vectors and installs new handlers (Block13, int19).
- Uses **INT 11h** (equipment list) and **INT 15h** (system configuration) as needed.
- Sets up a local stack (e.g. SS:SP = 0:700h).
- Performs hardware and device driver initialization and eventually calls **SYSINIT** (FAR call).

SYSINIT is part of IO.SYS (linked with the BIOS) and continues the MS-DOS bring-up.

---

## 7. SYSINIT Phase (AG.DOC 6.2)

After SYSINIT gains control from the IO.SYS initialization code, it performs the following steps (summarized from AG.DOC 6.2):

1. **Relocate SYSINIT** to high memory (using memory size from scan or MEMORY_SIZE, and the size of SYSINIT).
2. **Move MSDOS.SYS** from **CURRENT_DOS_LOCATION** to **FINAL_DOS_LOCATION** (both set by IO.SYS) to compact low memory and fix the final DOS location.
3. **FAR call to MS-DOS** initialization. MS-DOS walks the device driver list, issues **INIT** (command code 0) to each driver, builds drive parameter blocks for block devices, installs a sector buffer, and may print the copyright message. It then does a **FAR return** to SYSINIT.
4. **RE_INIT** is called (in IO.SYS) so the OEM can print headers or do other one-time init. No permanent memory changes should be made here.
5. **CONFIG.SYS** is opened (on the boot drive). If found, it is read, uppercased, and parsed for **DEVICE=**, **BUFFERS=**, **FILES=**, **SHELL=**, etc. **DEVICE=** drivers are loaded and installed (INIT called); character devices are added at the front of the list, block devices at the end.
6. **Memory allocation** for the block containing buffers, installable drivers, and IO.SYS is performed, and the “owner” is set so this block is not freed.
7. **All file handles** are closed; then **CON**, **AUX**, and **PRN** are reopened so any replacement CON/AUX/PRN drivers take effect.
8. **Buffers** are allocated according to CONFIG.SYS (or default).
9. **Hardware stacks** are allocated and **STACKINIT** is called (e.g. for DOS 3.2+ switchable stacks).
10. **COMMAND.COM** is executed (as the shell, or the program specified by **SHELL=** in CONFIG.SYS).
11. **COMMAND.COM** allocates memory for its transient portion, loads it, and displays the **command prompt**.

At that point MS-DOS is up and running.

---

## 8. Memory Map Diagram

The following diagrams summarize the four main phases (from AG.DOC 6.3).

### Phase 1: After ROM loads the boot sector

```
+-----------------------------+    High memory
|                             |
|     (free)                  |
|                             |
+-----------------------------+
|     Bootstrap loader        |    Loaded at 0:7C00h by ROM
+-----------------------------+
|   Interrupt Vector Table    |    0:0
+-----------------------------+
```

### Phase 2: After boot sector loads IO.SYS and MSDOS.SYS

```
+-----------------------------+    High memory
|   (spent bootstrap loader)  |
+-----------------------------+
|         MSDOS.SYS           |    Temporary location
+-----------------------------+
|          SYSINIT            |    Part of IO.SYS
+-----------------------------+
|           IO.SYS            |    Resident device drivers
+-----------------------------+
|   Interrupt Vector Table    |
+-----------------------------+
```

### Phase 3: During SYSINIT (relocation, drivers, buffers)

```
+-----------------------------+    High memory
|          SYSINIT            |    Relocated here
+-----------------------------+
|   (free / TPA)              |
+-----------------------------+
| MS-DOS structures, buffers,|
| hardware stack space,       |
| installable drivers         |
+-----------------------------+
| MSDOS.SYS (relocated)       |    At FINAL_DOS_LOCATION
+-----------------------------+
|           IO.SYS            |
+-----------------------------+
|   Interrupt Vector Table    |
+-----------------------------+
```

### Phase 4: Final layout (COMMAND.COM resident and transient, TPA)

```
+-----------------------------+    High memory
|     COMMAND.COM (transient) |
+-----------------------------+
|   Transient Program Area    |    Start varies with drivers/buffers
+-----------------------------+
|  COMMAND.COM (resident)     |
+-----------------------------+
| MS-DOS structures, buffers, |
| hardware stacks, drivers    |
+-----------------------------+
|         MSDOS.SYS           |
+-----------------------------+
|           IO.SYS            |
+-----------------------------+
|   Interrupt Vector Table    |
+-----------------------------+
```

---

## 9. Key Constants (from MSBOOT.ASM)

| Symbol   | Value   | Meaning |
|----------|---------|--------|
| ORIGIN   | 7C00h   | Load address and initial SP for boot sector |
| BIOSEG   | 70h     | Segment where BIOS (IO.SYS) is entered |
| BioOff   | 700h    | Offset within that segment where IO.SYS is loaded (image may extend from 70:0) |
| DirOff   | 500h    | Address (offset in segment 0) where first directory sector is read |
| cbSec    | 512     | Bytes per sector |
| cbDirEnt | 32      | Bytes per root directory entry |
| DSKADR   | 1Eh×4   | Offset in IVT of disk parameter table pointer |

---

## 10. Error Handling

- **RERROR** (disk read or reset failure):
  - Display **"Disk Boot failure"** (DMSSG) using INT 10h AH=0Eh.
  - Then fall through to the same wait-and-retry as CKERR.

- **CKERR** (IO.SYS or MSDOS.SYS not found or directory read error):
  - Display **"Non-System disk or disk error"** and **"Replace and strike any key when ready"** (SYSMSG).
  - **INT 16h, AH = 0** — wait for a keypress.
  - Restore the original **INT 1Eh** vector (segment and offset) from the stack.
  - **INT 19h** — invoke the ROM bootstrap loader again (load boot sector and retry).

In both cases the user can change the disk and press a key to retry without power cycling.

---

## Sources

- [AG.DOC](https://github.com/AR1972/DOS3.3/blob/master/AG.DOC) — Chapters 4 and 6; disk structure, boot sector role, SYSINIT steps
- [MSBOOT.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BOOT/MSBOOT.ASM) — Boot sector implementation
- [MSINIT.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BIOS/MSINIT.ASM) — INIT entry from boot sector
- [SYSINIT1.ASM](https://github.com/AR1972/DOS3.3/blob/master/SRC/BIOS/SYSINIT1.ASM) — SYSINIT module
