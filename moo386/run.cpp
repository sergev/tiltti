// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include <iostream>
#include <string>

#include "machine.h"
#include "memory.h"
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

    //Machine::enable_trace("r");

    // Set initial CPU state
    if (has_initial_reg(REG::EAX))
        cpu.set_eax(*get_initial_reg(REG::EAX));
    if (has_initial_reg(REG::EBX))
        cpu.set_ebx(*get_initial_reg(REG::EBX));
    if (has_initial_reg(REG::ECX))
        cpu.set_ecx(*get_initial_reg(REG::ECX));
    if (has_initial_reg(REG::EDX))
        cpu.set_edx(*get_initial_reg(REG::EDX));
    if (has_initial_reg(REG::CS))
        cpu.set_cs(*get_initial_reg(REG::CS));
    if (has_initial_reg(REG::SS))
        cpu.set_ss(*get_initial_reg(REG::SS));
    if (has_initial_reg(REG::DS))
        cpu.set_ds(*get_initial_reg(REG::DS));
    if (has_initial_reg(REG::ES))
        cpu.set_es(*get_initial_reg(REG::ES));
    if (has_initial_reg(REG::FS))
        cpu.set_fs(*get_initial_reg(REG::FS));
    if (has_initial_reg(REG::GS))
        cpu.set_gs(*get_initial_reg(REG::GS));
    if (has_initial_reg(REG::ESP))
        cpu.set_esp(*get_initial_reg(REG::ESP));
    if (has_initial_reg(REG::EBP))
        cpu.set_ebp(*get_initial_reg(REG::EBP));
    if (has_initial_reg(REG::ESI))
        cpu.set_esi(*get_initial_reg(REG::ESI));
    if (has_initial_reg(REG::EDI))
        cpu.set_edi(*get_initial_reg(REG::EDI));
    if (has_initial_reg(REG::EIP))
        cpu.set_eip(*get_initial_reg(REG::EIP));
    if (has_initial_reg(REG::CR0))
        cpu.set_cr0(*get_initial_reg(REG::CR0));
    if (has_initial_reg(REG::CR3))
        cpu.set_cr3(*get_initial_reg(REG::CR3));
    if (has_initial_reg(REG::DR6))
        cpu.set_dr6(*get_initial_reg(REG::DR6));
    if (has_initial_reg(REG::DR7))
        cpu.set_dr7(*get_initial_reg(REG::DR7));
    if (has_initial_reg(REG::EFLAGS))
        cpu.set_flags(*get_initial_reg(REG::EFLAGS));

    //machine.trace_registers();

    // Set initial RAM contents
    for (const auto &mb : initial_ram)
        machine.mem_store_byte(mb.first, mb.second);

    bool failed = false;
    try {
        // Single-step.
        cpu.step();
        if (!cpu.is_halted())
            cpu.step(); // HLT
    } catch (...) {
        failed = true;
    }

    // Check final CPU state and RAM
    if (has_final_reg(REG::EAX))
        failed |= cpu.get_eax() != *get_final_reg(REG::EAX);
    if (has_final_reg(REG::EBX))
        failed |= cpu.get_ebx() != *get_final_reg(REG::EBX);
    if (has_final_reg(REG::ECX))
        failed |= cpu.get_ecx() != *get_final_reg(REG::ECX);
    if (has_final_reg(REG::EDX))
        failed |= cpu.get_edx() != *get_final_reg(REG::EDX);
    if (has_final_reg(REG::CS))
        failed |= cpu.get_cs() != *get_final_reg(REG::CS);
    if (has_final_reg(REG::SS))
        failed |= cpu.get_ss() != *get_final_reg(REG::SS);
    if (has_final_reg(REG::DS))
        failed |= cpu.get_ds() != *get_final_reg(REG::DS);
    if (has_final_reg(REG::ES))
        failed |= cpu.get_es() != *get_final_reg(REG::ES);
    if (has_final_reg(REG::FS))
        failed |= cpu.get_fs() != *get_final_reg(REG::FS);
    if (has_final_reg(REG::GS))
        failed |= cpu.get_gs() != *get_final_reg(REG::GS);
    if (has_final_reg(REG::ESP))
        failed |= cpu.get_esp() != *get_final_reg(REG::ESP);
    if (has_final_reg(REG::EBP))
        failed |= cpu.get_ebp() != *get_final_reg(REG::EBP);
    if (has_final_reg(REG::ESI))
        failed |= cpu.get_esi() != *get_final_reg(REG::ESI);
    if (has_final_reg(REG::EDI))
        failed |= cpu.get_edi() != *get_final_reg(REG::EDI);
    if (has_final_reg(REG::EIP))
        failed |= cpu.get_eip() != *get_final_reg(REG::EIP);
    if (has_final_reg(REG::CR0))
        failed |= cpu.get_cr0() != *get_final_reg(REG::CR0);
    if (has_final_reg(REG::CR3))
        failed |= cpu.get_cr3() != *get_final_reg(REG::CR3);
    if (has_final_reg(REG::DR6))
        failed |= cpu.get_dr6() != *get_final_reg(REG::DR6);
    if (has_final_reg(REG::DR7))
        failed |= cpu.get_dr7() != *get_final_reg(REG::DR7);
    if (has_final_reg(REG::EFLAGS)) {
        auto eflags  = cpu.get_eflags() & ~cpu.u_flags();
        auto expect = *get_final_reg(REG::EFLAGS) & ~cpu.u_flags();
        failed |= eflags != expect;
    }

    for (size_t i = 0; i < final_ram.size(); i++) {
        const auto &mb = final_ram[i];
        if (is_flags_in_mem(i)) {
            // Check two items as flags in memory.
            const auto &mc    = final_ram[i + 1];
            uint8_t expect_lo = mb.second & ~cpu.u_flags();
            uint8_t expect_hi = mc.second & ~(cpu.u_flags() >> 8);
            i++;
            failed |= (memory.load8(mb.first) & ~cpu.u_flags()) != expect_lo;
            failed |= (memory.load8(mc.first) & ~(cpu.u_flags() >> 8)) != expect_hi;
        } else {
            failed |= memory.load8(mb.first) != mb.second;
        }
    }

    if (failed) {
        std::cerr << "Failed: " << name_ << "\n";
        emit_gtest();
    }
}
