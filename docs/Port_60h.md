In IBM PC/AT and compatible computers, I/O port 0x60 (commonly referred to as port 60h) serves as the data register for the 8042 keyboard controller (or equivalent emulation in later chipsets). Introduced with the IBM PC/AT in 1984, this port is integral to the keyboard (and often auxiliary device like PS/2 mouse) interface, handling the transfer of scan codes, command responses, and configuration data. It complements port 0x64 (command/status register): typically, commands are written to 64h, and associated data or parameters are written to or read from 60h. In earlier PC/XT systems, port 60h directly provides keyboard scan codes without a full 8042, and port 64h may alias or be partially equivalent. Modern systems emulate port 60h via chipset firmware or USB legacy modes to support low-level code, even with USB input devices.

### Key Functions
- **Data Input/Output**: Reading from 60h retrieves keyboard scan codes (e.g., key press/release), acknowledgment bytes (e.g., 0xFA for ACK), self-test results (e.g., 0xAA for keyboard BAT success, 0x55 for controller self-test), or other responses from the keyboard or controller. Writing to 60h sends data such as keyboard commands (e.g., reset, LED control), configuration bytes (e.g., for the Keyboard Controller Command Byte, KCCB), or simulated input.
- **Command Parameter Handling**: After writing a command to 64h (e.g., 0x60 to write KCCB), the next write to 60h provides the parameter byte. Similarly, responses to commands issued via 64h are read from 60h.
- **Auxiliary Device Support**: In PS/2 systems, port 60h also handles mouse data when commands like 0xD4 (write to auxiliary) are used via 64h.
- **System Control Extensions**: Beyond input, it's used for tasks like enabling the A20 address line (for extended memory access) by writing to the output port via commands, or pulsing the CPU reset line for reboot.
- **Interrupt and Polling**: Scan codes trigger IRQ1 (INT 09h), but during POST or low-level ops, software polls status at 64h before accessing 60h to avoid errors.

The port is accessible via I/O instructions (IN/OUT in assembly) and requires ring 0 privileges in protected mode. No fixed bit definitions exist for the byte at 60h, as its meaning varies by context (e.g., scan code, command response, or parameter).

### Common Commands and Data (Via 60h)
While commands are primarily sent to 64h, 60h handles the data flow. Examples of values written to or read from 60h:

- **Keyboard Commands (Written to 60h after enabling interface)**:
  - 0xED: Set LEDs (followed by byte for Num/Caps/Scroll Lock bits).
  - 0xF3: Set typematic rate/delay.
  - 0xF4: Enable scanning.
  - 0xF5: Disable scanning (default settings).
  - 0xFF: Reset keyboard (expects 0xFA ACK, then 0xAA BAT success).
- **Controller Parameters (Written to 60h after command to 64h)**:
  - After 0x60 to 64h: Write KCCB byte (e.g., bit 0: IRQ1 enable; bit 1: IRQ12 enable; bit 6: scan code translation).
  - After 0xD1 to 64h: Write output port byte (e.g., bit 1 for A20 gate, bit 0 for reset).
- **Responses (Read from 60h)**:
  - 0xAA: Keyboard BAT complete/success.
  - 0xFA: ACK to command.
  - 0xFC: BAT failure.
  - Scan codes: Vary by set (e.g., set 2: 0x1C for 'A' make, 0xF0 0x1C for break).

For indirect access (e.g., to keyboard), poll status bit 1 at 64h (input buffer empty) before writing, and bit 0 (output buffer full) before reading.

### Usage Examples
- **Reading a Scan Code**: In INT 09h handler, read status from 64h (check bit 0), then read byte from 60h (e.g., 0x1C for 'A' press). Acknowledge by pulsing port 61h bit 7 (in XT) or via controller.
- **Keyboard Reset (During POST)**: Write 0xFF to 60h; read 0xFA (ACK) then 0xAA (success) from 60h after polling.
- **Enable A20 Line**: Write 0xD1 to 64h, then 0xDF (set bit 1) to 60h.
- **Simulate Keystroke (PS/2)**: Write 0xD2 to 64h, then scan code to 60h; controller presents it as input.
- **Controller Self-Test**: Write 0xAA to 64h, read 0x55 from 60h for success.

### Compatibility Notes
- In PC/XT: Port 60h is the primary keyboard data port; no separate command register at 64h (it may alias to 60h). Requires manual acknowledgment via port 61h.
- Undefined or reserved commands may cause hangs or no-ops on clones.
- In modern hardware/VMs: Emulated for legacy software, but USB keyboards use OS drivers bypassing direct I/O. Access may be trapped or virtualized.
- Aliasing: On some early hardware, ports 60h-63h decode across 60h-7Fh, but 60h is the standard address.
