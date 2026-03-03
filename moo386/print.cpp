// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include <iomanip>

#include "test_case.h"

//
// Lets users inspect a test's name and initial/final CPU state (32-bit registers and RAM) for
// debugging or comparison.
//
void TestCase::print(std::ostream &os) const
{
    os << "\n==== Test #" << index_ << " (" << chunk_len_ << " bytes) ====\n";
    os << "Name: \"" << name_ << "\"\n";

    os << "Initial CPU State:\n  Registers:\n";
    for (size_t i = 0; i < static_cast<size_t>(REG::COUNT); i++) {
        REG r  = static_cast<REG>(i);
        auto v = get_initial_reg(r);
        if (v) {
            os << "    " << std::left << std::setw(7) << std::setfill(' ') << get_register_name(r)
               << " = ";
            fmt_hex8(os, *v);
            os << " (" << *v << ")\n";
        }
    }
    os << "  RAM entries: " << initial_ram.size() << "\n";
    for (const auto &mb : initial_ram) {
        os << "    ";
        fmt_hex5(os, mb.first);
        os << " = ";
        fmt_hex2(os, static_cast<unsigned>(mb.second));
        os << " (" << static_cast<unsigned>(mb.second) << ")\n";
    }

    os << "Final CPU State:\n  Registers:\n";
    for (size_t i = 0; i < static_cast<size_t>(REG::COUNT); i++) {
        REG r  = static_cast<REG>(i);
        auto v = get_final_reg(r);
        if (v) {
            os << "    " << std::left << std::setw(7) << std::setfill(' ') << get_register_name(r)
               << " = ";
            fmt_hex8(os, *v);
            os << " (" << *v << ")\n";
        }
    }
    os << "  RAM entries: " << final_ram.size() << "\n";
    for (const auto &mb : final_ram) {
        os << "    ";
        fmt_hex5(os, mb.first);
        os << " = ";
        fmt_hex2(os, static_cast<unsigned>(mb.second));
        os << " (" << static_cast<unsigned>(mb.second) << ")\n";
    }
}
