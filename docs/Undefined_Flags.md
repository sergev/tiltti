# Unpredictable FLAGS

The processor models 8086 FLAGS and marks certain bits as unpredictable when an instruction's flag behavior cannot be accurately modeled—either per Intel 8086 documentation or due to hardware variation. These bits are recorded in the `unpredictable_flags` bitmask.

## Instructions with Unpredictable Flags

| Instruction | Opcode(s) | Unpredictable Flags | Explanation |
|-------------|-----------|---------------------|-------------|
| AAA | 0x37 | OF, PF, SF, ZF | Overflow, parity, sign and zero undefined per Intel |
| DAA | 0x27 | OF | Overflow undefined per Intel |
| AAS | 0x3f | OF, PF, SF, ZF | Overflow, parity, sign and zero undefined per Intel |
| DAS | 0x2f | OF | Overflow undefined per Intel |
| AAM | 0xd4 | OF | Overflow undefined per Intel |
| AAD | 0xd5 | OF | Overflow undefined per Intel |
| RCR (count != 1) | D0-D3 reg=3 | OF | OF defined only for single-rotate (count=1); undefined when count != 1 |
| SAL / SHL | D0-D3 reg=4 | AF | AF undefined per Intel; batch5/batch6 expect different values |
| MUL (word) | F7 reg=4 (w=W) | PF, ZF | PF and ZF undefined per Intel for word MUL |
| IMUL | F7 reg=5 | PF, AF, ZF, SF | AF, SF, ZF, PF undefined; only CF and OF defined per Intel |
| DIV | F7 reg=6 | CF, OF, SF, ZF, PF, AF | All arithmetic flags undefined per 8086 documentation |
| IDIV | F7 reg=7 | CF, OF, SF, ZF, PF, AF | Arithmetic flags in undefined state per 8086 manual |

## Flag Abbreviations

- OF: Overflow
- PF: Parity
- SF: Sign
- ZF: Zero
- CF: Carry
- AF: Auxiliary Carry

## Usage in the Processor

The `unpredictable_flags` bitmask is cleared at the start of each instruction step. When an instruction executes, it may set `unpredictable_flags` to designate which flag bits it leaves undefined. These bits are then masked out when comparing FLAGS for testing (e.g., `core.flags.w &= ~unpredictable_flags`), so tests do not fail on values that the simulator computes but real hardware may set differently.
