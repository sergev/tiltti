// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include <iostream>
#include <string>

#include "machine.h"
#include "test_case.h"

//
// Run the test case on simulator.
// In case of failure, create a GTest C++ source file named after the test.
//
void TestCase::run() const
{
    Memory memory;
    Machine machine{ memory };
    Processor &cpu{ machine.cpu };

    // Set initial CPU state
    if (initial_ax.has_value())
        cpu.set_ax(*initial_ax);
    if (initial_bx.has_value())
        cpu.set_bx(*initial_bx);
    if (initial_cx.has_value())
        cpu.set_cx(*initial_cx);
    if (initial_dx.has_value())
        cpu.set_dx(*initial_dx);
    if (initial_cs.has_value())
        cpu.set_cs(*initial_cs);
    if (initial_ss.has_value())
        cpu.set_ss(*initial_ss);
    if (initial_ds.has_value())
        cpu.set_ds(*initial_ds);
    if (initial_es.has_value())
        cpu.set_es(*initial_es);
    if (initial_sp.has_value())
        cpu.set_sp(*initial_sp);
    if (initial_bp.has_value())
        cpu.set_bp(*initial_bp);
    if (initial_si.has_value())
        cpu.set_si(*initial_si);
    if (initial_di.has_value())
        cpu.set_di(*initial_di);
    if (initial_ip.has_value())
        cpu.set_ip(*initial_ip);
    if (initial_flags.has_value())
        cpu.set_flags(*initial_flags);

    // Set initial RAM contents
    for (const auto &mb : initial_ram)
        machine.mem_store_byte(mb.first, mb.second);

    // Single-step.
    cpu.step();

    // Check final CPU state and RAM
    bool failed = false;
    if (final_ax.has_value())
        failed |= cpu.get_ax() != *final_ax;
    if (final_bx.has_value())
        failed |= cpu.get_bx() != *final_bx;
    if (final_cx.has_value())
        failed |= cpu.get_cx() != *final_cx;
    if (final_dx.has_value())
        failed |= cpu.get_dx() != *final_dx;
    if (final_cs.has_value())
        failed |= cpu.get_cs() != *final_cs;
    if (final_ss.has_value())
        failed |= cpu.get_ss() != *final_ss;
    if (final_ds.has_value())
        failed |= cpu.get_ds() != *final_ds;
    if (final_es.has_value())
        failed |= cpu.get_es() != *final_es;
    if (final_sp.has_value())
        failed |= cpu.get_sp() != *final_sp;
    if (final_bp.has_value())
        failed |= cpu.get_bp() != *final_bp;
    if (final_si.has_value())
        failed |= cpu.get_si() != *final_si;
    if (final_di.has_value())
        failed |= cpu.get_di() != *final_di;
    if (final_ip.has_value())
        failed |= cpu.get_ip() != *final_ip;
    if (final_flags.has_value()) {
        auto flags  = cpu.get_flags() & ~cpu.u_flags();
        auto expect = *final_flags & ~cpu.u_flags();
        failed |= flags != expect;
    }
    for (const auto &mb : final_ram) {
        failed |= memory.load8(mb.first) != mb.second;
    }

    if (failed) {
        std::cerr << "Failed: " << name_ << "\n";
        emit_gtest();
    }
}
