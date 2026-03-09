# PC i86 Simulator

Emulator of a PC-compatible machine with BIOS support. Supports **8086** and **386** CPU variants; 386 support is real-mode only (protected-mode switching is not implemented).

## Features

- Disk boot from floppy (A:, B:) and hard disk images (C:, D:), including raw and VHD.
- BIOS interrupt handlers: video (INT 10h), disk (INT 13h), keyboard (INT 16h), serial (INT 14h), printer (INT 17h), RTC/timer (INT 1Ah), system services (INT 15h), equipment list (INT 11h), memory size (INT 12h).
- VGA text-mode display via SDL2.
- Unit tests (GoogleTest) for 8086 and 386 instruction behavior, plus DOS/CP/M boot tests using images in `images/`.
- MOO binary test runners: `moo8086` (8086/8088) and `moo386` (386 real-mode) for external test suites.
- Documentation in `docs/` for BIOS data structures, interrupt services, and disk formats.

## Build

Requirements: CMake 3.12+, C++17 compiler, **SDL2**, **capstone** (pkg-config). The build also uses **xxd** to generate `basic_rom.h` from `images/ibm-basic-1.10.rom`. The MOO utilities (`moo8086`, `moo386`) need **zlib**. Optional: **cppcheck** for static analysis.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build
```

Or use the top-level Makefile:

- `make` or `make all` — build everything (creates `build/` and builds tiltti, moo8086, moo386, unit_tests).
- `make test` — build and run unit tests (ctest in `build/tests`).
- `make install` — install the `tiltti` binary to the chosen prefix (e.g. `/usr/local`).
- `make clean` — remove `build/`.
- `make debug` — configure for Debug (then run `make`).

## Running

```text
tiltti [options...] [disk_a.img]
```

At least one disk image or option is required. Disks:

- `-a FILE` — Floppy drive A: image
- `-b FILE` — Floppy drive B: image
- `-c FILE` — Hard disk C: image
- `-d FILE` — Hard disk D: image
- `disk_a.img` — Single positional argument is treated as drive A: (same as `-a`).

Options:

- `--boot=a|b|c|d` — Boot from the given drive (default: C if present, else A, else B).
- `--386` — Use 386 processor variant.
- `--8086` — Use 8086 processor variant (default).
- `-V`, `--version` — Print version and exit.
- `-h`, `--help` — Show usage.

Trace modes:

- `-r`, `--regs` — Trace registers and execution.
- `-s`, `--syscalls` — Trace INT software interrupts.
- `-p`, `--ports` — Trace IN/OUT port access.
- `-o`, `--output=FILE` — Redirect trace to a file.

## Testing

- **Unit tests**: `make test` builds the `unit_tests` target and runs ctest. Tests cover 8086 and 386 instructions (including MOO-derived cases), BDA layout, and boot behavior with disk images under `images/`.
- **MOO regression**: With external MOO test data, use `make moo86` (8086, `MOO86` dir), `make moo88` (8088, `MOO88` dir), or `make moo386` (386 real-mode, `MOO386` dir). See the Makefile for default paths (e.g. SingleStepTests/8086, 8088, 80386).

## Limitations

- **386**: Only real-mode is supported; switch to protected mode (e.g. INT 15h AH=89h) is unimplemented.
- Several BIOS and peripheral functions are stubbed or unimplemented (e.g. some INT 10h/13h/15h/16h/17h subfunctions, serial/printer I/O, light pen, pixel read/write). See the docs and source for details.
- The project relies on the `images/` directory for ROM (`ibm-basic-1.10.rom`) and for disk images used by unit tests and example `make` targets (e.g. MS-DOS, PC-DOS, DR-DOS, CP/M).

## Documentation

Documents in `docs/` describe BIOS layout, interrupt services, hardware ports, boot process, and disk formats.

**BIOS data structures and memory layout**

- [Interrupt Descriptor Table](docs/Interrupt_Descriptor_Table.md) at 0x0
- [BIOS Data Area](docs/BIOS_Data_Area.md) at 0x400
- [Extended BIOS Data Area](docs/Extended_BIOS_Data_Area.md) at 0x9fc00
- [BIOS ROM Layout](docs/BIOS_ROM_Layout.md) at 0xf0000
- [Diskette Parameter Table](docs/Diskette_Parameter_Table.md) (vector 0x1E)
- [Fixed Disk Parameter Table](docs/Fixed_Disk_Parameter_Table.md) (vectors 0x41 and 0x46)

**BIOS interrupt and service reference**

- [INT 10h — Video Services](docs/Int10_Video_Services.md)
- [INT 11h — Equipment List](docs/Int11_Equipment_List.md)
- [INT 12h — Memory Size](docs/Int12_Memory_Size.md)
- [INT 13h — Disk Services](docs/Int13_Disk_Services.md)
- [INT 14h — Serial Services](docs/Int14_Serial_Services.md)
- [INT 15h — System Services](docs/Int15_System_Services.md)
- [INT 16h — Keyboard Services](docs/Int16_Keyboard_Services.md)
- [INT 17h — Printer Services](docs/Int17_Printer_Services.md)
- [INT 1Ah — RTC and Timer](docs/Int1A_RTC_Timer.md)

**Hardware ports and interrupts**

- [Port 60h](docs/Port_60h.md) — Keyboard data
- [Port 61h](docs/Port_61h.md) — System control
- [Port 64h](docs/Port_64h.md) — Keyboard controller
- [Port 66h](docs/Port_66h.md)
- [Keyboard Interrupt](docs/Keyboard_Interrupt.md)
- [Timer Interrupt](docs/Timer_Interrupt.md)

**Boot and system behavior**

- [Boot Sequence](docs/Boot_Sequence.md)
- [Callbacks From ROM](docs/Callbacks_From_ROM.md)
- [Evolution of DOS](docs/Evolution_of_DOS.md)

**Video**

- [Video Modes](docs/Video_Modes.md)

**Disk and image formats**

- [Virtual Hard Disk Format](docs/Virtual_Hard_Disk_Format.md)

**Test format**

- [MOO File Format Specification](docs/MOO_File_Format_Specification.md)

**Other**

- [Undefined Flags](docs/Undefined_Flags.md)

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.
