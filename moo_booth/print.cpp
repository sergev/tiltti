// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include "test_case.h"
#include <iomanip>

//
// Lets users inspect a test's name and initial/final CPU state (registers and RAM) for
// debugging or comparison. Prints test index and chunk size, name, then "Initial CPU State"
// (registers from REG_LUT for each present OptReg, then RAM as addr = value), then "Final CPU
// State" in the same format. Uses fmt_hex2/4/5 for consistent hex and decimal.
//
void TestCase::print(std::ostream &os) const
{
    os << "\n==== Test #" << index_ << " (" << chunk_len_ << " bytes) ====\n";
    os << "Name: \"" << name_ << "\"\n";

    os << "Initial CPU State:\n  Registers:\n";
    const OptReg *initial_regs[] = { &initial_ax, &initial_bx,   &initial_cx, &initial_dx,
                                     &initial_cs, &initial_ss,   &initial_ds, &initial_es,
                                     &initial_sp, &initial_bp,   &initial_si, &initial_di,
                                     &initial_ip, &initial_flags };
    for (size_t i = 0; i < REG_COUNT; i++) {
        if (initial_regs[i]->has_value()) {
            os << "    " << std::left << std::setw(5) << std::setfill(' ') << REG_LUT[i] << " = ";
            fmt_hex4(os, initial_regs[i]->value());
            os << " (" << initial_regs[i]->value() << ")\n";
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
    const OptReg *final_regs[] = { &final_ax, &final_bx, &final_cx, &final_dx,   &final_cs,
                                   &final_ss, &final_ds, &final_es, &final_sp,   &final_bp,
                                   &final_si, &final_di, &final_ip, &final_flags };
    for (size_t i = 0; i < REG_COUNT; i++) {
        if (final_regs[i]->has_value()) {
            os << "    " << std::left << std::setw(5) << std::setfill(' ') << REG_LUT[i] << " = ";
            fmt_hex4(os, final_regs[i]->value());
            os << " (" << final_regs[i]->value() << ")\n";
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
