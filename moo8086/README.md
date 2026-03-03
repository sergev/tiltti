## MOO Parser

A C++ parser for the **MOO** (Machine Opcode Operation) binary CPU test format. Daniel Balsom created these tests for the 8088, 8086, V20 and V30 CPUs. The test suite uses a chunked binary format, typically gzipped, with 10,000 tests per opcode.

For details on the binary format, see [MOO_File_Format_Specification.md](MOO_File_Format_Specification.md). For sample parser output, see [Example_Output.md](Example_Output.md).

### Build

Requires a C++17 compiler and zlib. Build from the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The executable is `build/moo_booth/moo-booth`. For a debug build use `-DCMAKE_BUILD_TYPE=Debug` when configuring.

### Usage

```
./moo-booth [-limit=N] [-index=N] [-gtest] <binary_test_file>
```

- `-limit=N` — Process at most N tests
- `-index=N` — Process only test at index N
- `-gtest` — Emit GTest C++ source files instead of human-readable output

Supports both plain and gzipped MOO files (detected via gzip magic).

### Text Example

When run as `./moo-booth -limit=1 00.MOO.gz`:

```
File MOO Chunk:
  Version: 1
  Test Count: 10000
  CPU type: 88

==== Test #0 (671 bytes) ====
Name: "add byte [ss:bp+di-64h], cl"
Initial CPU State:
  Registers:
    ax    = 52A1 (21153)
    bx    = E724 (59172)
    cx    = 81C8 (33224)
    dx    = F0F7 (61687)
    cs    = 31ED (12781)
    ss    = 1D03 (7427)
    ds    = 0258 (600)
    es    = CCC3 (52419)
    sp    = BF76 (49014)
    bp    = 2608 (9736)
    si    = CB21 (52001)
    di    = 2729 (10025)
    ip    = 02B6 (694)
    flags = F452 (62546)
  RAM entries: 5
    32186 = 00 (0)
    32187 = 4B (75)
    32188 = 9C (156)
    32189 = 90 (144)
    21CFD = 14 (20)
Final CPU State:
  Registers:
    ip    = 02B9 (697)
    flags = F482 (62594)
  RAM entries: 1
    21CFD = DC (220)
```

### C++ Example

```cpp
#include "moo_parser.h"

MooParser parser("00.MOO.gz");
while (auto rec = parser.next()) {
    rec->print(std::cout);   // Human-readable output
    // rec->emit_gtest();    // Or emit GTest C++ source
}
```

`MooParser::next()` returns `std::optional<TestCase>`. Each `TestCase` holds the instruction name, initial and final registers, and initial/final RAM entries. See [test_case.h](test_case.h) for the full structure.

### Test Data Notes

- All tests assume 1 MB of RAM mapped to the processor and writable.
- On the 8088, the address space wraps at FFFFF.
- No wait states; interrupt and trap flags are not exercised.
- The queue and cycle fields can be ignored for functional testing.
