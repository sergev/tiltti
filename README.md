# PC i86 Emulator

Emulator of the i86 computer with PC BIOS.

## Running

```text
tiltti [options...] disk.img [disk_b.img] [hd_c.img] [hd_d.img]
```

The first image is the boot floppy (drive A:). An optional second image is mounted as drive B:. Optional third and fourth images are mounted as hard disks C: and D: (INT 13h drive numbers 0x80 and 0x81). With one image, INT 11h reports one floppy; with two images, it reports two floppies. Hard disk count is reported in BDA and via INT 13h AH=08h.

Verified using MOO test suites:
 * 646000 tests from [SingleStepTests/8086](https://github.com/SingleStepTests/8086/tree/main/v1_binary)
 * 3007000 tests from [SingleStepTests/8088](https://github.com/SingleStepTests/8088/tree/main/v2_binary)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Documentation

Description of BIOS data structures:
 * [Interrupt Descriptor Table](docs/Interrupt_Descriptor_Table.md) at 0x0
 * [BIOS Data Area](docs/BIOS_Data_Area.md) at 0x400
 * [Extended BIOS Data Area](docs/Extended_BIOS_Data_Area.md) at 0x9fc00
 * [BIOS ROM Layout](docs/BIOS_ROM_Layout.md) at 0xf0000
 * [Diskette Parameter Table](docs/Diskette_Parameter_Table.md) pointed by vector 0x1E
 * [Fixed Disk Parameter Table](docs/Fixed_Disk_Parameter_Table.md) pointed by vectors 0x41 and 0x46
