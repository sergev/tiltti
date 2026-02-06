// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include "test_case.h"
#include "machine.h"

//
// Run the test case on simulator.
// In case of failure, create a GTest C++ source file named after the test.
//
void TestCase::run() const
{
    Memory memory;
    Machine machine{ memory };
    Processor &cpu{ machine.cpu };

    // Set initial CPU State
    //TODO: cpu.set_ax(0xADEE);
    //TODO: ...
    //TODO: cpu.set_ip(0x8490);
    //TODO: cpu.set_flags(0xF4C3);

    // Set initial RAM contents
    //TODO: machine.mem_store_byte(0xDABA0, 0x3E);
    //TODO: ...

    // Single-step.
    cpu.step();

    // Check final CPU State
    //TODO: compare cpu.get_ax() with 0xAD34;
    //TODO: ...
    //TODO: compare cpu.get_ip() with 0x8493;
    //TODO: compare cpu.get_flags() with 0xF413;

    // Check final RAM contents
    //TODO: compare memory.load8(0xDABA0) with 0x3E;
    //TODO: ...
}
