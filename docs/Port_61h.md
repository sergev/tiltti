The I/O port 0x61 (commonly referred to as port 61h) in IBM PC compatible computers is a multifunctional system control and status register. It originated as Port B of the 8255 Programmable Peripheral Interface (PPI) chip in the original IBM PC and XT models, where it handled various hardware control and status functions. In later models (such as the AT and beyond), this port's behavior is emulated by the keyboard controller or other chipset components for backward compatibility, but its functionality remains largely the same. It plays a key role in speaker control, error handling via Non-Maskable Interrupts (NMIs), timing loops, and keyboard interrupt acknowledgment.

### Key Functions
- **PC Speaker Control**: Port 61h directly interfaces with the built-in PC speaker (a simple piezoelectric buzzer). The speaker is driven by combining signals from the Programmable Interval Timer (PIT, specifically channel 2 at port 0x42) and bits in this port. To produce tones, PIT channel 2 is typically programmed to generate a square wave at a desired frequency, and then bits in port 61h enable the output to the speaker.
- **Error Status and NMI Control**: It manages detection and enabling of hardware errors, such as memory parity issues or I/O expansion card problems, which can trigger NMIs to the CPU.
- **Timing and Delays**: Certain read-only bits toggle based on system timers or memory refresh cycles, making this port useful for software-based delay loops in legacy code.
- **Keyboard Interface**: It is involved in acknowledging keyboard interrupts by pulsing a specific bit, which resets the keyboard controller's buffer status after reading a scancode from port 0x60.

The port is both readable and writable, with some bits behaving differently depending on whether you're reading or writing. Below is a breakdown of the standard bit definitions, based on the original IBM PC/XT design (variations may exist in clones or modern emulations, but compatibility is generally preserved).

### Bit Definitions
| Bit | Write Function | Read Function |
|-----|----------------|---------------|
| 0   | Speaker gate enable: 1 = Connect PIT channel 2 output to the speaker (allows timer-driven tones); 0 = Disconnect. | Reflects the last value written to bit 0. |
| 1   | Speaker data enable: 1 = Activate the speaker (drives it high if combined with PIT output or forces it on); 0 = Deactivate. | Reflects the last value written to bit 1. |
| 2   | Parity check NMI enable: 1 = Enable NMI on memory parity error; 0 = Disable. | Reflects the last value written to bit 2. |
| 3   | I/O channel check NMI enable: 1 = Enable NMI on expansion bus I/O error; 0 = Disable. | Reflects the last value written to bit 3. |
| 4   | Not used (latch may store value, but no hardware effect). | Memory refresh toggle: Flips state (0/1) with each DRAM refresh cycle (approximately every 15 μs, driven by PIT channel 1). Commonly used in old software for precise short delays by polling for changes. |
| 5   | Not used (latch may store value, but no hardware effect). | PIT channel 2 output state: Reflects the current high/low status of the timer's output pin (useful for speaker synchronization or polling). |
| 6   | Not used (latch may store value, but no hardware effect). | I/O channel check error: 1 = Error detected on expansion bus (e.g., bad RAM card); 0 = No error. Triggers NMI if bit 3 is enabled. |
| 7   | Keyboard acknowledge/clear: Pulse to 1 then back to 0 to reset keyboard buffer after reading from port 0x60 (acknowledges IRQ1 and allows next key). In some contexts, 1 = Disable keyboard. | Memory parity error: 1 = Parity error detected in system memory; 0 = No error. Triggers NMI if bit 2 is enabled. |

### Usage Examples
- **Generating a Beep**: Program PIT channel 2 (ports 0x43 and 0x42) for the frequency, read port 61h, OR the value with 0x03 (set bits 0 and 1), write it back to enable the speaker. To stop, AND with 0xFC (clear bits 0 and 1) and write back.
- **Handling Keyboard Input**: After an IRQ1 (keyboard interrupt), read scancode from port 0x60, then read port 61h, OR with 0x80 (set bit 7), write back, then AND with 0x7F (clear bit 7), and write back. This pulses bit 7 to acknowledge.
- **Error Handling**: If an NMI occurs, read port 61h to check bits 6 and 7 for the source. To clear a latched error, temporarily set the corresponding enable bit (2 or 3) to 0, then back to 1.
- **Software Delay**: Poll bit 4 until it changes state for a ~15 μs interval, often used in BIOS or DOS code for timing without relying on interrupts.

In modern systems, this port is mostly vestigial (e.g., emulated in virtual machines or chipset firmware), as PC speakers are rare, parity memory is uncommon, and keyboards use PS/2 or USB interfaces. However, it remains accessible for compatibility in low-level programming, such as in operating system development or retro computing.
