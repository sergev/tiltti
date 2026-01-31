# BIOS Data Area (BDA)

The BIOS Data Area (BDA) is a 256-byte memory region located at physical addresses 0x400-0x500. It contains system configuration and runtime state used by the BIOS and operating systems. The structure is defined in `src/std/bda.h` as `struct bios_data_area_s`. All BDA access in SeaBIOS uses the `GET_BDA(var)` and `SET_BDA(var, val)` macros from `src/biosvar.h`, which reference segment `SEG_BDA` (0x0040).

Note: `startBoot()` clears low memory from 0x7000 to 0x90000 but leaves the BDA (0x400-0x500) intact.

## BDA Layout Overview

| Offset | Size | Field |
|--------|------|-------|
| 0x00 | 8 | port_com[4] |
| 0x08 | 6 | port_lpt[3] |
| 0x0E | 2 | ebda_seg |
| 0x10 | 2 | equipment_list_flags |
| 0x12 | 1 | pad1 |
| 0x13 | 2 | mem_size_kb |
| 0x15 | 1 | pad2 |
| 0x16 | 1 | ps2_ctrl_flag |
| 0x17 | 2 | kbd_flag0 |
| 0x19 | 1 | alt_keypad |
| 0x1A | 2 | kbd_buf_head |
| 0x1C | 2 | kbd_buf_tail |
| 0x1E | 32 | kbd_buf[32] |
| 0x3E | 1 | floppy_recalibration_status |
| 0x3F | 1 | floppy_motor_status |
| 0x40 | 1 | floppy_motor_counter |
| 0x41 | 1 | floppy_last_status |
| 0x42 | 7 | floppy_return_status[7] |
| 0x49 | 1 | video_mode |
| 0x4A | 2 | video_cols |
| 0x4C | 2 | video_pagesize |
| 0x4E | 2 | video_pagestart |
| 0x50 | 16 | cursor_pos[8] |
| 0x60 | 2 | cursor_type |
| 0x62 | 1 | video_page |
| 0x63 | 2 | crtc_address |
| 0x65 | 1 | video_msr |
| 0x66 | 1 | video_pal |
| 0x67 | 4 | jump |
| 0x6B | 1 | other_6b |
| 0x6C | 4 | timer_counter |
| 0x70 | 1 | timer_rollover |
| 0x71 | 1 | break_flag |
| 0x72 | 2 | soft_reset_flag |
| 0x74 | 1 | disk_last_status |
| 0x75 | 1 | hdcount |
| 0x76 | 1 | disk_control_byte |
| 0x77 | 1 | port_disk |
| 0x78 | 4 | lpt_timeout[4] |
| 0x7C | 4 | com_timeout[4] |
| 0x80 | 2 | kbd_buf_start_offset |
| 0x82 | 2 | kbd_buf_end_offset |
| 0x84 | 1 | video_rows |
| 0x85 | 2 | char_height |
| 0x87 | 1 | video_ctl |
| 0x88 | 1 | video_switches |
| 0x89 | 1 | modeset_ctl |
| 0x8A | 1 | dcc_index |
| 0x8B | 1 | floppy_last_data_rate |
| 0x8C | 1 | disk_status_controller |
| 0x8D | 1 | disk_error_controller |
| 0x8E | 1 | disk_interrupt_flag |
| 0x8F | 1 | floppy_harddisk_info |
| 0x90 | 4 | floppy_media_state[4] |
| 0x94 | 2 | floppy_track[2] |
| 0x96 | 1 | kbd_flag1 |
| 0x97 | 1 | kbd_led |
| 0x98 | 4 | user_wait_complete_flag |
| 0x9C | 4 | user_wait_timeout |
| 0xA0 | 1 | rtc_wait_flag |
| 0xA1 | 7 | other_a1[7] |
| 0xA8 | 4 | video_savetable |
| 0xAC | 4 | other_ac[4] |
| 0xB0 | 80 | other_b0[80] |

## Initialization Flow

The BDA is initialized in this order during POST:

1. **bda_init()** (`src/post.c`): Zeroes entire BDA, sets `ebda_seg` and `mem_size_kb`
2. **kbd_init()** (`src/kbd.c`): Keyboard buffer pointers and flags
3. **mouse_init()** (`src/mouse.c`): Equipment list bit for mouse
4. **mathcp_setup()** (`src/misc.c`): Equipment list bit for FPU
5. **clock_setup()** (`src/clock.c`): `timer_counter` from RTC
6. **device_hardware_setup()**: Serial, LPT, block devices, ATA
7. **VGA/Sercon**: Video-related fields via `vga_post()`, `vga_set_mode()`, `sercon_setup()`

---

## Field Reference

### 40:00 - Serial and Parallel Ports

#### port_com[4] (u16 × 4)
I/O base addresses of COM1-COM4. Standard values: 0x3F8, 0x2F8, 0x3E8, 0x2E8. Zero if port not present.

- **Initialization**: `serial_setup()` in `src/serial.c` probes each port and writes addresses for detected ports
- **Usage**: INT 14h (Serial I/O) reads port via `GET_BDA(port_com[regs->dx])`

#### port_lpt[3] (u16 × 3)
I/O base addresses of LPT1-3. Standard values: 0x378, 0x278, 0x3BC. Zero if not present.

- **Initialization**: `lpt_setup()` in `src/serial.c` via `detect_parport()` writes addresses for detected ports
- **Usage**: INT 17h (Printer) reads port via `GET_BDA(port_lpt[regs->dx])`

#### ebda_seg (u16)
Segment address of the Extended BIOS Data Area (EBDA). The EBDA is allocated at the top of conventional RAM.

- **Initialization**: `bda_init()` in `src/post.c` sets to `EBDA_SEGMENT_START` (or adjusted when `CONFIG_MALLOC_UPPERMEMORY` is disabled)
- **Usage**: `malloc.c` may update when shrinking EBDA; `get_ebda_seg()` returns this value

---

### 40:10 - Equipment and Memory

#### equipment_list_flags (u16)
INT 11h equipment list. Bits indicate installed hardware. SeaBIOS sets: bit 1 (FPU), bit 2 (mouse), bits 4-5 (initial video: 80×25 color), bits 9-11 (serial port count), bits 14-15 (parallel port count), bits 0 and 6 (floppy count).

- **Initialization**: Zero at BDA init; bits set by:
  - `mathcp_setup()`: bit 1 (0x02) — 80x87 installed
  - `mouse_init()`: bit 2 (0x04) — pointing device
  - `init_bios_area()` in `vgasrc/vgainit.c`: bits 4-5 (0x30→0x20) — 80×25 color
  - `serial_setup()`: bits 9-11 (0xe00) — number of COM ports
  - `lpt_setup()`: bits 14-15 (0xc000) — number of LPT ports
  - `map_floppy_drive()`: bits 0 and 6 (0x41) — 1 or 2 floppies
  - `cdrom.c`: bits 0 and 6 (0x41) — floppy present
- **Usage**: INT 11h returns this word in AX

#### pad1, pad2 (u8 each)
Unused padding. Zero-initialized.

#### mem_size_kb (u16)
Conventional memory size in kilobytes (below 1 MB). Used by INT 12h.

- **Initialization**: `bda_init()` sets to `ebda_seg / 64` (equivalent to end-of-RAM in KB)
- **Usage**: INT 12h returns this value; `malloc_low()` may decrease it when shrinking EBDA

#### ps2_ctrl_flag (u8)
Legacy PS/2 controller flag. SeaBIOS does not use this field. Zero.

#### kbd_flag0 (u16)
Keyboard status flags. See `bda.h` for `KF0_*` bits (shift, ctrl, alt, caps, num, scroll, etc.).

- **Initialization**: Zero; updated by INT 09h keyboard interrupt
- **Usage**: INT 16h AH=02h returns low byte; INT 16h AH=12h returns full word

#### alt_keypad (u8)
Alternate keypad flag. SeaBIOS does not use. Zero.

---

### 40:1E - Keyboard Buffer

#### kbd_buf_head (u16), kbd_buf_tail (u16)
Head and tail pointers for the keyboard circular buffer. Offsets within BDA segment.

- **Initialization**: `kbd_init()` sets both to `offsetof(struct bios_data_area_s, kbd_buf)`
- **Usage**: INT 09h advances tail when enqueueing; INT 16h advances head when dequeueing

#### kbd_buf[32] (u8 × 32)
Circular buffer for scan codes (stored as u16, so 16 entries). Wraps via head/tail.

- **Initialization**: Not explicitly cleared; head==tail means empty
- **Usage**: `enqueue_key()` / `dequeue_key()` in `src/kbd.c`

#### kbd_buf_start_offset (u16), kbd_buf_end_offset (u16)
Buffer bounds (offsets in BDA segment).

- **Initialization**: `kbd_init()` sets start to `kbd_buf` offset, end to start + 32
- **Usage**: Used by keyboard buffer logic to wrap indices

#### kbd_flag1 (u8)
Extended keyboard flags. See `KF1_*` in `bda.h` (LAST_E1, LAST_E0, RCTRL, RALT, 101KBD).

- **Initialization**: `kbd_init()` sets `KF1_101KBD` (1<<4)
- **Usage**: INT 09h updates for extended key handling; INT 16h AH=12h merges with kbd_flag0

#### kbd_led (u8)
Keyboard LED state (caps, num, scroll lock). Bits 0–2.

- **Initialization**: Zero
- **Usage**: INT 16h AH=03h (get/set typematic) reads and updates

---

### 40:3E - Floppy Disk

#### floppy_recalibration_status (u8)
Bit 7 (`FRS_IRQ`): IRQ received. Bits 0–1: recalibration needed per drive.

- **Initialization**: Zero; `floppy_reset()` clears
- **Usage**: Floppy driver in `src/hw/floppy.c` sets/clears during operations

#### floppy_motor_status (u8)
Legacy motor-on status per drive. SeaBIOS does not use. Zero.

#### floppy_motor_counter (u8)
Countdown before turning off motors. Decremented by timer tick.

- **Initialization**: Set to 255 or `FLOPPY_MOTOR_TICKS` when motor is started
- **Usage**: `floppy_tick()` decrements; motor off when it reaches zero

#### floppy_last_status (u8)
Last status code from floppy INT 13h operations.

- **Initialization**: Zero
- **Usage**: `disk_ret()` in `src/disk.c` sets for floppy drives (DL < 0x80)

#### floppy_return_status[7] (u8 × 7)
Result bytes from last Floppy Disk Controller command.

- **Initialization**: Filled by floppy driver after FDC commands
- **Usage**: `floppy_dma_cmd()` in `src/hw/floppy.c` populates after read/write/format

#### floppy_last_data_rate (u8)
Encodes last data rate used (bits 6–7) and drive data rate (bits 2–3). See `FMS_DATA_RATE_MASK`.

- **Initialization**: Zero; `floppy_reset()` clears
- **Usage**: Set during `floppy_prep()` for media detection

#### floppy_media_state[4] (u8 × 4)
Per-drive media state. See `FMS_*` in `bda.h`: `FMS_DRIVE_STATE_MASK`, `FMS_MEDIA_DRIVE_ESTABLISHED`, `FMS_DOUBLE_STEPPING`, `FMS_DATA_RATE_MASK`.

- **Initialization**: Zero; `floppy_reset()` clears first two drives
- **Usage**: Updated in `floppy_prep()` during read/write

#### floppy_track[2] (u8 × 2)
Current track for floppy drives 0 and 1.

- **Initialization**: Zero; `floppy_reset()` clears
- **Usage**: Set in `floppy_prep()` when seeking; read for read/write

#### floppy_harddisk_info (u8)
Floppy/hard disk info: low nibble = drives 0–3 type, high nibble = drives 4–7 type. 0x07 = one 1.44M, 0x77 = two 1.44M.

- **Initialization**: `map_floppy_drive()` sets 0x07 (1 drive) or 0x77 (2 drives)
- **Usage**: INT 13h and boot code use for drive configuration

---

### 40:49 - Video (VGA)

#### video_mode (u8)
Current video mode. 0x00–0x13 for standard modes; 0xFF for VBE modes.

- **Initialization**: Set by `vga_set_mode()` or `sercon_setup()` when using serial console
- **Usage**: INT 10h AH=0Fh returns current mode

#### video_cols (u16)
Number of columns (character width in text modes).

- **Initialization**: Set in `vga_set_mode()` or `sercon_setup()`
- **Usage**: Cursor and screen logic throughout `vgasrc/`

#### video_rows (u8)
Number of rows minus 1. Actual rows = `video_rows + 1`.

- **Initialization**: Set in `vga_set_mode()` or `sercon_setup()`
- **Usage**: `GET_BDA(video_rows)+1` for row count

#### video_pagesize (u16)
Size of one video page in bytes.

- **Initialization**: `vga_set_mode()` via `calc_page_size()`
- **Usage**: Page offset = `video_pagesize * page_number`

#### video_pagestart (u16)
Start address (offset in video segment) of current page.

- **Initialization**: `vga_set_mode()` sets to 0
- **Usage**: INT 10h AH=05h (select page) updates

#### cursor_pos[8] (u16 × 8)
Cursor position per page. Format: (row << 8) | col.

- **Initialization**: Cleared to 0 in `vga_set_mode()`; `kbd_init()` leaves buffer pointers here, cursor positions set on mode set
- **Usage**: INT 10h AH=02h/03h get/set cursor position

#### cursor_type (u16)
Cursor shape. 0x0607 = normal underline; 0x0000 = hidden.

- **Initialization**: `vga_set_mode()` sets 0x0607 (text) or 0x0000 (graphics)
- **Usage**: INT 10h AH=01h sets; INT 10h AH=03h returns

#### video_page (u8)
Active display page (0–7).

- **Initialization**: `vga_set_mode()` sets to 0
- **Usage**: INT 10h AH=05h sets; cursor operations use this page

#### crtc_address (u16)
CRTC base I/O address (0x3D4 or 0x3B4). Zero if not standard VGA.

- **Initialization**: `vga_set_mode()` sets via `stdvga_get_crtc()` when `CONFIG_VGA_STDVGA_PORTS`
- **Usage**: INT 10h AH=1Bh (video BIOS functionality) returns

#### video_msr (u8), video_pal (u8)
Miscellaneous video register state. Unavailable on standard VGA.

- **Initialization**: `init_bios_area()` in `vgasrc/vgainit.c` sets both to 0
- **Usage**: Read by INT 10h AH=1Bh

#### video_ctl (u8)
Video control. Bit 0: cursor enable; bit 7: don't clear memory on mode set.

- **Initialization**: `vga_set_mode()` sets 0x60 or 0xE0 depending on flags
- **Usage**: INT 10h AH=10h AL=1Bh; cursor emulation

#### video_switches (u8)
Display adapter switches (DIP). Typically 0xF9.

- **Initialization**: `vga_set_mode()` sets 0xF9
- **Usage**: INT 10h AH=1Bh returns

#### modeset_ctl (u8)
Mode set control flags (e.g., no palette, grayscale).

- **Initialization**: `init_bios_area()` sets 0x51; `vga_set_mode()` clears bit 7
- **Usage**: INT 10h mode set and save/restore

#### dcc_index (u8)
Display combination code index. 0x08 for standard VGA; 0xFF if not applicable.

- **Initialization**: `init_bios_area()` sets 0x08 when `CONFIG_VGA_STDVGA_PORTS`, else 0xFF
- **Usage**: INT 10h AH=1Bh returns; INT 10h AH=1Ch can set

#### char_height (u16)
Character height in scan lines (8, 14, or 16).

- **Initialization**: `vga_set_mode()` from current font
- **Usage**: Cursor drawing and font-related INT 10h

#### video_savetable (struct segoff_s)
Far pointer to video parameter/save table.

- **Initialization**: `stdvga_build_video_param()` in `vgasrc/stdvgamodes.c` when `CONFIG_VGA_STDVGA_PORTS`
- **Usage**: INT 10h AH=1Ch (save/restore video state)

---

### 40:67 - System

#### jump (struct segoff_s)
Resume/warm-boot vector at 40h:67h. Used for Ctrl+Alt+Del and other soft resets.

- **Initialization**: Zero; set by OS or firmware for resume
- **Usage**: `handle_resume()` in `src/resume.c` uses for status 0x05, 0x0a, 0x0b, 0x0c

#### other_6b (u8)
Unused. Zero.

#### timer_counter (u32)
BIOS tick count at ~18.2 Hz. Rolls over at `TICKS_PER_DAY` (1573040).

- **Initialization**: `clock_setup()` sets from RTC (hours, minutes, seconds)
- **Usage**: INT 08h increments; INT 1Ah AH=00h/01h get/set; `irqtimer_*` for timeouts

#### timer_rollover (u8)
Incremented at midnight when `timer_counter` rolls over.

- **Initialization**: Zero; INT 1Ah AH=01h clears
- **Usage**: INT 1Ah AH=00h returns and clears

#### break_flag (u8)
Set to 0x80 when Ctrl+Break is pressed.

- **Initialization**: Zero
- **Usage**: `kbd.c` sets on Ctrl+Break; INT 1Bh or INT 23h handlers may check

#### soft_reset_flag (u16)
Set to 0x1234 when Ctrl+Alt+Del is pressed. Triggers warm reboot.

- **Initialization**: Zero
- **Usage**: `kbd.c` sets; boot/reset code checks before invoking INT 19h

---

### 40:74 - Disk

#### disk_last_status (u8)
Last status from hard disk INT 13h (DL >= 0x80).

- **Initialization**: Zero
- **Usage**: `disk_ret()` in `src/disk.c` sets for hard disk ops

#### hdcount (u8)
Number of hard drives (0–2 in classic BIOS). SeaBIOS may support more.

- **Initialization**: Starts at 0; `map_hd_drive()` increments; `map_cd_drive()` may increment; `csm.c` zeroes in UEFI CSM path
- **Usage**: INT 13h uses for drive validation and geometry

#### disk_control_byte (u8)
Disk controller control byte. 0xC0 = disable IRQ.

- **Initialization**: `ata_setup()` in `src/hw/ata.c` sets 0xC0
- **Usage**: Written to disk controller during operations

#### port_disk (u8)
Legacy disk controller port. SeaBIOS does not set. Zero.

#### lpt_timeout[4] (u8 × 4)
Timeout in ticks for LPT ports. Indexed by port number.

- **Initialization**: `detect_parport()` sets (e.g., 0x14) with each port
- **Usage**: INT 17h uses for printer operations

#### com_timeout[4] (u8 × 4)
Timeout in ticks for COM ports. Indexed by port number.

- **Initialization**: `detect_serial()` sets (e.g., 0x0A) with each port
- **Usage**: INT 14h uses for serial I/O

#### disk_status_controller (u8), disk_error_controller (u8)
Legacy controller status/error. SeaBIOS does not use. Zero.

#### disk_interrupt_flag (u8)
Indicates disk interrupt completion. 0 = idle/done; 0xFF = operation in progress.

- **Initialization**: Set to 0 before and 0xFF during disk ops
- **Usage**: `src/disk.c` for polling during disk operations

---

### 40:98 - User Wait (INT 15h AH=83h)

#### user_wait_complete_flag (struct segoff_s)
Far pointer to byte that is set when RTC wait completes.

- **Initialization**: Set by INT 15h AH=83h when starting wait
- **Usage**: `clock.c` writes 0x80 to this byte when timeout elapses

#### user_wait_timeout (u32)
Remaining microseconds for RTC-based wait.

- **Initialization**: Set by INT 15h AH=83h
- **Usage**: Decremented in INT 70h (RTC) handler until zero

#### rtc_wait_flag (u8)
State of RTC wait. `RWS_WAIT_PENDING` (bit 0) = wait active; `RWS_WAIT_ELAPSED` (bit 7) = done.

- **Initialization**: Zero; set to `RWS_WAIT_PENDING` when wait starts; cleared when done
- **Usage**: `clock.c` in `set_usertimer()` and `clear_usertimer()`

---

### Reserved / Unused

#### other_a1[7], other_ac[4], other_b0[80]
Reserved/padding. Zero-initialized. SeaBIOS does not use.
