In IBM PC/AT and compatible computers, I/O port 0x64 (commonly referred to as port 64h) serves as the command and status register for the 8042 keyboard controller (or equivalent emulation in later chipsets). Introduced with the IBM PC/AT in 1984, the 8042 microcontroller manages keyboard (and often auxiliary device like mouse) communication, handling serial data reception, parity checks, scan code translation, and interrupt generation. Port 64h is bidirectional: reading it provides the controller's status, while writing to it issues commands. It works in tandem with port 0x60 (data port) for full interaction. In earlier PC/XT systems, port 64h is often an alias or partially decoded equivalent to port 60h, but full 8042 functionality is AT-specific. Modern systems emulate this port via chipset firmware for legacy compatibility, even with USB keyboards.

### Key Functions
- **Status Reporting**: Reading port 64h returns a byte indicating the controller's state, such as buffer readiness, error flags, and self-test results. This is polled during initialization or interrupt handling to check if data is available at port 60h.
- **Command Issuance**: Writing to port 64h sends control commands to the 8042, such as enabling/disabling interfaces, self-testing, or configuring translation modes.
- **Integration with Keyboard/Mouse**: Facilitates bidirectional communication; commands can reset the keyboard, read/write internal RAM, or manage auxiliary ports (e.g., PS/2 mouse).
- **Error and Interrupt Handling**: Status bits flag parity errors, timeouts, or buffer overflows, often triggering IRQ1 (keyboard) or IRQ12 (mouse).

The port is accessible in real mode or via I/O instructions in protected mode, but requires ring 0 privileges in modern OSes.

### Bit Definitions (Status Register - Read from 64h)
The status byte provides real-time controller information. Bits are as follows (based on standard 8042 implementation; some clones may vary slightly):

| Bit | Function |
|-----|----------|
| 0   | Output Buffer Full (OBF): 1 = Data is ready to read from port 60h (e.g., scan code or response); 0 = Buffer empty. Poll this before reading 60h. |
| 1   | Input Buffer Full (IBF): 1 = Buffer full (cannot write to 60h/64h); 0 = Buffer empty (safe to write). Poll this before writing. |
| 2   | System Flag (SYSF): 1 = Controller passed self-test (after power-on or command AAH); 0 = Pre-self-test or failure. |
| 3   | Command/Data Flag (C/D): 1 = Last write to 64h was a command; 0 = Last write to 60h was data. Helps distinguish in queue. |
| 4   | Keyboard Lock (Inhibit Switch): 1 = Keyboard unlocked; 0 = Locked (e.g., via physical switch or command). |
| 5   | Auxiliary Output Buffer Full (AOBF): 1 = Auxiliary data (e.g., mouse) ready at 60h; 0 = Empty. |
| 6   | Timeout Error: 1 = Timeout occurred (e.g., no response from keyboard); 0 = No timeout. |
| 7   | Parity Error: 1 = Parity error in received data (from keyboard); 0 = No error. |

### Commands (Write to 64h)
Writing a byte to 64h issues a command to the controller. Many commands expect follow-up data written to port 60h. A partial list of common commands (hex values) includes:

- **20h**: Read Keyboard Controller Command Byte (KCCB) from internal RAM and place it in output buffer (read from 60h).
- **60h**: Write KCCB; next byte to 60h sets configuration (e.g., bits for interrupt enable, translation).
- **AAh**: Self-test controller; returns 55h (success) or FCh (error) at 60h.
- **ABh**: Keyboard interface test; returns 00h (OK) or error code at 60h.
- **ADh**: Disable keyboard interface (stops scan code processing).
- **AEh**: Enable keyboard interface.
- **A7h**: Disable auxiliary (mouse) interface.
- **A8h**: Enable auxiliary interface.
- **A9h**: Auxiliary interface test; returns 00h (OK) or error.
- **C0h**: Read input port (P1 bits, e.g., system switches) to 60h.
- **D0h**: Read output port (P2 bits, e.g., gate A20, reset) to 60h.
- **D1h**: Write output port; next byte to 60h sets P2.
- **D2h**: Write to output buffer as if from keyboard (for simulating keystrokes).
- **D4h**: Write next byte (to 60h) to auxiliary device (mouse).
- **EDh**: Set LEDs; forwarded to keyboard (next byte to 60h controls Num/Caps/Scroll Lock).
- **F0h-FFh**: Pulse output lines (e.g., FEh pulses reset line to reboot system).

For a full list, including lesser-used or ignored commands (e.g., 00h-1Fh for RAM read), refer to detailed 8042 documentation. Responses to commands are read from 60h after polling status bit 0.

### Usage Examples
- **Polling for Data**: In a keyboard interrupt handler (INT 09h), read 64h and check bit 0; if set, read scan code from 60h. If bit 7 or 6 is set, handle error.
- **Controller Self-Test (During POST)**: Write AAh to 64h, poll bit 0, read 60h expecting 55h. This is part of BIOS initialization.
- **Enable Keyboard**: Write AEh to 64h after disabling (ADh) for maintenance.
- **Simulate Keystroke**: On PS/2 compatibles, write D2h to 64h, then scan code to 60h; controller presents it as real input.
- **Gate A20 Control**: Write D1h to 64h, then value with bit 1 set (e.g., DFh) to 60h to enable A20 line for extended memory access.
- **System Reset**: Write FEh to 64h to pulse CPU reset line.

### Compatibility Notes
- In PC/XT systems, port 64h may alias to 60h or be undecoded, lacking full 8042 commands.
- On some clones, undefined bits or commands may behave differently; always poll status before reads/writes to avoid hangs.
- In virtual machines or modern hardware, this port is emulated, but USB keyboards bypass it via OS drivers. Low-level access is still used in OS development or retro programming.
