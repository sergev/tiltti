# Callbacks From ROM

This page documents all mechanisms where SeaBIOS ROM code invokes or transfers control to user-provided code. A *callback from ROM* is any case where the BIOS calls back into code or data that the user (or OS, driver, or option ROM) has installed or provided.

For the Interrupt Vector Table (IVT) layout and initialization, see [Interrupt_Descriptor_Table.md](Interrupt_Descriptor_Table.md). For BDA/EBDA layout, see [BIOS_Data_Area.md](BIOS_Data_Area.md).

---

## IVT Initialization at Startup

The IVT is initialized in a specific order during POST. Understanding this order clarifies which vectors the BIOS sets and which remain available for user handlers.

### Order of Operations

1. **`interface_init()`** ([`src/post.c`](src/post.c)) — called from `maininit()`:
   - **`ivt_init()`** ([`src/post.c`](src/post.c) lines 32–71):
     - Sets all 256 vectors to `entry_iret_official` (IRET stub).
     - Sets hardware IRQ vectors 0x08–0x0F and 0x70–0x77 to `entry_hwpic1` / `entry_hwpic2`.
     - Sets software handlers: 0x02, 0x05, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x40.
     - Sets 0x60–0x66 and 0x79 to `SEGOFF(0,0)` (reserved/zero).
   - **`bda_init()`** — initializes BDA and EBDA.

2. **`platform_hardware_setup()`**:
   - **`clock_setup()`** ([`src/clock.c`](src/clock.c)): `enable_hwirq(0, entry_08)` → IVT[0x08]; `enable_hwirq(8, entry_70)` → IVT[0x70].

3. **`device_hardware_setup()`**:
   - **`floppy_setup()`** ([`src/hw/floppy.c`](src/hw/floppy.c)): `SET_IVT(0x1E, diskette_param_table)`; `enable_hwirq(6, entry_0e)` → IVT[0x0E].
   - **`block_setup()`** ([`src/block.c`](src/block.c)): `SET_IVT(0x41, 0x46)` for fixed disk parameter tables (EBDA).
   - **`ps2port_setup()`** ([`src/hw/ps2port.c`](src/hw/ps2port.c)): `enable_hwirq(1, entry_09)`, `enable_hwirq(12, entry_74)`.
   - **`mathcp_setup()`** ([`src/misc.c`](src/misc.c)): `enable_hwirq(13, entry_75)`.
   - **ATA** ([`src/hw/ata.c`](src/hw/ata.c)): `enable_hwirq(14, entry_76)`.

4. **`vgarom_setup()`** ([`src/optionroms.c`](src/optionroms.c)): Runs VGA option ROM init.
   - VGA `vga_post()` ([`vgasrc/vgainit.c`](vgasrc/vgainit.c)): Replaces IVT[0x10] with VGA handler; hooks IVT[0x08] (saves old, installs VGA hook, chains via `Timer_Hook_Resume`).

5. **`sercon_setup()`** ([`src/sercon.c`](src/sercon.c)): May replace IVT[0x10] with serial console handler if enabled.

### Vectors Not Initialized by BIOS (User Must Install)

- **INT 1Ch** (timer tick): Default `entry_iret_official`; user installs for periodic work.
- **INT 4Ah** (RTC alarm): Default `entry_iret_official`; user installs and programs alarm via INT 1Ah AH=06.
- **INT 1Bh** (Ctrl-Break): Default `entry_iret_official`; user installs to handle Ctrl-Break.

---

## IVT-Based Callbacks

The BIOS uses `call16_int()` ([`src/stacks.c`](src/stacks.c)) which invokes `int $N` via `irq_trampoline_N` ([`src/romlayout.S`](src/romlayout.S) lines 166–184). Whatever the user has installed at IVT[N] receives control.

| Vector | Trigger | User Setup | Source |
|--------|---------|------------|--------|
| **INT 1Ch** | Every timer tick (~18.2 Hz) from INT 08h | User sets IVT[0x1C] | [`src/clock.c`](src/clock.c):312 |
| **INT 4Ah** | RTC alarm when alarm time matches | User sets IVT[0x4A], programs alarm via INT 1Ah AH=06 | [`src/clock.c`](src/clock.c):475 |
| **INT 1Bh** | Ctrl+Break key press | User sets IVT[0x1B] | [`src/kbd.c`](src/kbd.c):427 |
| **INT 05h** | Print Screen key press | User replaces IVT[0x05] (BIOS sets default stub) | [`src/kbd.c`](src/kbd.c):451, [`src/misc.c`](src/misc.c):49 |
| **INT 15h** (AH=85) | SysReq key press/release | User replaces IVT[0x15] or chains | [`src/kbd.c`](src/kbd.c):439 |
| **INT 15h** (AH=4F) | Every key before processing (if CONFIG_KBD_CALL_INT15_4F) | User hooks INT 15; returns CF clear to intercept | [`src/kbd.c`](src/kbd.c):587–594, [`src/system.c`](src/system.c):239 |
| **INT 02h** | NMI (e.g., from IRQ13 math coprocessor) | User replaces IVT[0x02] | [`src/misc.c`](src/misc.c):84 |
| **INT 18h** | Boot failure (no bootable device) | User/option ROM sets IVT[0x18] | [`src/boot.c`](src/boot.c):1024 |
| **INT 19h** | Boot load service entry | Option ROMs may replace; BIOS restores if misbehaving | [`src/post.c`](src/post.c):192, [`src/optionroms.c`](src/optionroms.c):314–323 |

### Per-Vector Details

#### INT 1Ch — Timer Tick

- **Trigger**: INT 08h handler (`handle_08`) calls `call16_int(0x1c, &br)` after updating the tick counter.
- **Calling convention**: Standard software interrupt; registers as passed to `call16_int` (typically zeroed `struct bregs` with `F_IF`).
- **Note**: Not initialized by BIOS; defaults to `entry_iret_official`. User must install a handler.

#### INT 4Ah — RTC Alarm

- **Trigger**: INT 70h handler (`handle_70`) calls `call16_int(0x4a, &br)` when the RTC alarm matches the programmed time (INT 1Ah AH=06).
- **Setup**: User programs alarm via INT 1Ah AH=06; enables alarm interrupt via INT 1Ah AH=07.
- **Note**: Not initialized by BIOS; defaults to `entry_iret_official`.

#### INT 1Bh — Ctrl-Break

- **Trigger**: Keyboard driver calls `call16_int(0x1b, &br)` when Ctrl+Break is pressed.
- **Note**: Not initialized by BIOS; defaults to `entry_iret_official`.

#### INT 05h — Print Screen

- **Trigger**: Keyboard driver calls `call16_int(0x05, &br)` when Print Screen is pressed.
- **Default**: BIOS installs `entry_05` (stub that only calls `debug_enter`). User can replace.

#### INT 15h AH=85 — SysReq

- **Trigger**: Keyboard driver calls `call16_int(0x15, &br)` with AH=85, AL=00/01 on SysReq press/release.
- **Default**: BIOS `handle_15` handles it; user can replace IVT[0x15] or chain.

#### INT 15h AH=4F — Keyboard Intercept

- **Trigger**: When `CONFIG_KBD_CALL_INT15_4F`, `process_key()` invokes INT 15h with AH=4F, AL=scancode before processing each key.
- **Behavior**: If user handler returns with CF clear, the key is intercepted (not processed). If CF set, BIOS processes the key; user can modify keycode in AX.
- **Setup**: User must hook INT 15h and handle AH=4F; chain to BIOS for other AH values.

#### INT 02h — NMI

- **Trigger**: Math coprocessor handler (`handle_75`) calls `call16_int(0x02, &br)` after clearing IRQ13.
- **Default**: BIOS installs `entry_02`; user can replace.

#### INT 18h — Boot Failure

- **Trigger**: `do_boot()` calls `call16_int(0x18, &br)` when boot fails (no bootable device).
- **Default**: BIOS installs `handle_18`; user/option ROM can replace for custom boot failure handling.

#### INT 19h — Boot Load Service

- **Trigger**: `startBoot()` calls `call16_int(0x19, &br)` to begin the boot process.
- **Note**: Option ROMs may replace; SeaBIOS restores its handler if a PnP option ROM misbehaves ([`src/optionroms.c`](src/optionroms.c) `boot_irq_restore`).

---

## Mouse Far Call Pointer

The mouse driver supports a user-installed event handler stored in the EBDA.

### Setup

- **INT 15h AH=C2h AL=07h** — Set Mouse Handler Address
  - **Input**: ES:BX = far pointer to handler (or 0:0 to remove).
  - **Output**: Success/failure in carry flag.
  - **Source**: [`src/mouse.c`](src/mouse.c) lines 226–244.

### Storage

- Stored in EBDA `far_call_pointer` ([`src/std/bda.h`](src/std/bda.h) line 145).
- `mouse_flag2` bit 0x80 indicates handler is installed; clearing the pointer also clears this bit and disables the mouse.

### Invocation

- **When**: On each complete mouse packet (when `mouse_flag2 & 0x80` and package count matches).
- **How**: `invoke_mouse_handler()` in [`src/mouse.c`](src/mouse.c) lines 275–314.
- **Calling convention**: Far call with four words pushed on stack (in order): status, X, Y, Z. Handler must return with `retf` and preserve registers.

```c
// Pseudo-code of invocation
pushw status
pushw X
pushw Y
pushw Z
lcallw *far_call_pointer
addl $12, %esp
```

---

## INT 15h AH=83h — Wait Interval (user_wait_complete_flag)

This is a completion-signal callback: the BIOS writes to a user-provided byte when a timer interval elapses. It is not a code callback.

### Setup

- **INT 15h AH=83h AL=00h** — Set Event Wait Interval
  - **Input**: ES:BX = far pointer to a byte; CX:DX = interval in microseconds.
  - **Output**: Success/failure in carry flag.
  - **Source**: [`src/clock.c`](src/clock.c) lines 367–377, 415–423.

### Behavior

- BDA fields: `user_wait_complete_flag` (seg:off of byte), `user_wait_timeout` (remaining usecs), `rtc_wait_flag` (RWS_WAIT_PENDING when active).
- When the RTC periodic interrupt (INT 70h) decrements the timeout to zero, the BIOS ORs 0x80 into the user's byte: `*ptr |= 0x80`.
- **Source**: [`src/clock.c`](src/clock.c) lines 491–496.

---

## Resume Vectors

The BIOS transfers control to OS-provided vectors on resume from certain power states.

### BDA Jump (40:67)

- **Location**: BDA offset 0x67, `struct segoff_s jump` ([`src/std/bda.h`](src/std/bda.h)).
- **Setup**: OS or firmware sets this before requesting a resume.
- **Invocation**: `handle_resume()` in [`src/resume.c`](src/resume.c) lines 38–70 uses it for CMOS reset status 0x05, 0x0a, 0x0b, 0x0c.
- **Transfer**: `ljmpw *jump` (status 0x05, 0x0a) or `lssw` + `iretw`/`lretw` (0x0b, 0x0c).

### ACPI FACS firmware_waking_vector

- **Location**: FACS table, pointed to by FADT `firmware_ctrl`.
- **Setup**: OS sets `firmware_waking_vector` in the FACS before S3 sleep.
- **Invocation**: `s3_resume()` in [`src/resume.c`](src/resume.c) lines 93–118 calls `find_resume_vector()` ([`src/fw/biostables.c`](src/fw/biostables.c) lines 180–193) and far-calls the vector.
- **Transfer**: `farcall16big(&br)` with `br.code` = resume vector.

---

## Boot Vectors (INT 18h/19h)

- **INT 19h**: Invoked by `startBoot()` to begin the boot process. The BIOS chains to whatever is in IVT[0x19] (default: SeaBIOS boot handler).
- **INT 18h**: Invoked by `do_boot()` when boot fails. User/option ROM can install a custom handler.
- **Boot entry**: `call_boot_entry()` uses `farcall16()` to transfer to the boot sector or option ROM; the boot target is not a callback in the strict sense.

---

## Video BIOS (vgasrc) Callbacks

### Timer Hook (INT 08h) — VGA Chains to Previous Handler

When the VGA option ROM initializes (`vga_post` in [`vgasrc/vgainit.c`](vgasrc/vgainit.c)), it hooks the timer IRQ:

- **`hook_timer_irq()`** ([`vgasrc/vgainit.c`](vgasrc/vgainit.c) lines 115–129): Saves `GET_IVT(0x08)` into `Timer_Hook_Resume`, then `SET_IVT(0x08, entry_timer_hook)`.
- **`entry_timer_hook`** ([`vgasrc/vgaentry.S`](vgasrc/vgaentry.S) lines 137–164): Calls `handle_timer_hook()` (swcursor_check_event), then `ljmpw *Timer_Hook_Resume` to chain to the previous handler (SeaBIOS `handle_08`).

**Effect**: VGA inserts itself into the INT 08 chain. The user's INT 1Ch is still invoked by SeaBIOS `handle_08` after the chain returns. No new user callback; VGA runs before SeaBIOS in the timer chain.

### Font Pointers (IVT 0x1F, 0x43) — User-Provided Data

The VGA BIOS uses IVT[0x1F] and IVT[0x43] as font table pointers:

- **Setup**: User sets via INT 10h AH=11h AL=20h (ES:BP for 8×8 font) or AL=21h/22h/23h/24h (load font).
- **Usage**: VGA reads font data from these addresses when rendering text in graphics mode.
- **Source**: [`vgasrc/vgafb.c`](vgasrc/vgafb.c) `get_font_data()`, [`vgasrc/vgabios.c`](vgasrc/vgabios.c) lines 730–738, 787–793.

**Note**: This is user-provided *data* (font bitmaps), not code execution. The VGA BIOS reads from the address; it does not execute user code.

### INT 10h AX=1012h BL=A0h — BIOS-Provided Callback (Not ROM→User)

The Cirrus Logic extension (when present) returns BX=offset of `a0h_callback` ([`vgasrc/clext.c`](vgasrc/clext.c) lines 511–526). The caller (user/driver) invokes it; the BIOS does not call the user. Documented here for completeness.

---

## References

- [BIOS_Data_Area.md](BIOS_Data_Area.md) — BDA and EBDA layout
- [Interrupt_Descriptor_Table.md](Interrupt_Descriptor_Table.md) — IVT layout and vector summary
- [Int10_Video_Services.md](Int10_Video_Services.md) — INT 10h video services
- [Int1A_RTC_Timer.md](Int1A_RTC_Timer.md) — INT 1Ah RTC and timer services
