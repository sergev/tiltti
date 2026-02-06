// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include <fstream>

#include "test_case.h"

//
// Converts test name to a safe filename/base: replace every sequence of non-alphanumeric
// characters with a single underscore, then trim leading/trailing underscores. Returns empty
// if nothing remains.
//
static std::string name_to_filename(const std::string &name)
{
    std::string out;
    bool need_underscore = false;
    for (unsigned char c : name) {
        if (std::isalnum(c)) {
            if (need_underscore) {
                out += '_';
                need_underscore = false;
            }
            out += static_cast<char>(c);
        } else {
            need_underscore = !out.empty();
        }
    }
    auto start = out.find_first_not_of('_');
    if (start == std::string::npos)
        return {};
    auto end = out.find_last_not_of('_');
    return out.substr(start, end - start + 1);
}

//
// Writes a GTest C++ source file named after the test (sanitized name + .cpp) to the current
// working directory. Uses fixture.h, MachineTest, cpu, machine, memory. Throws if the file
// cannot be opened.
//
void TestCase::emit_gtest() const
{
    std::string base = name_to_filename(name_);
    if (base.empty())
        base = "test_" + std::to_string(index_);

    std::string path = base + ".cpp";
    std::ofstream ofs(path);
    if (!ofs)
        throw std::runtime_error("emit_gtest: cannot open " + path + " for writing");

    ofs << "#include \"fixture.h\"\n\n";
    ofs << "//\n// " << name_ << "\n//\n";
    ofs << "TEST_F(MachineTest, " << base << ")\n";
    ofs << "{\n";
    ofs << "    // Initial CPU State\n";

    const OptReg *initial_regs[] = { &initial_ax, &initial_bx,   &initial_cx, &initial_dx,
                                     &initial_cs, &initial_ss,   &initial_ds, &initial_es,
                                     &initial_sp, &initial_bp,   &initial_si, &initial_di,
                                     &initial_ip, &initial_flags };
    for (size_t i = 0; i < REG_COUNT; i++) {
        if (initial_regs[i]->has_value()) {
            ofs << "    cpu.set_" << REG_LUT[i] << "(0x";
            fmt_hex4(ofs, initial_regs[i]->value());
            ofs << ");\n";
        }
    }
    ofs << "    machine.trace_registers();\n\n";
    ofs << "    // Initial RAM entries\n";
    for (const auto &mb : initial_ram) {
        ofs << "    machine.mem_store_byte(0x";
        fmt_hex5(ofs, mb.first);
        ofs << ", 0x";
        fmt_hex2(ofs, static_cast<unsigned>(mb.second));
        ofs << ");\n";
    }
    ofs << "\n    // Single-step.\n";
    ofs << "    cpu.step();\n\n";
    ofs << "    // Final CPU State\n";

    const OptReg *final_regs[] = { &final_ax, &final_bx, &final_cx, &final_dx,   &final_cs,
                                   &final_ss, &final_ds, &final_es, &final_sp,   &final_bp,
                                   &final_si, &final_di, &final_ip, &final_flags };
    for (size_t i = 0; i < REG_COUNT; i++) {
        if (final_regs[i]->has_value()) {
            ofs << "    EXPECT_EQ(cpu.get_" << REG_LUT[i] << "(), 0x";
            fmt_hex4(ofs, final_regs[i]->value());
            ofs << ");\n";
        }
    }
    ofs << "\n    // Final RAM entries\n";
    for (const auto &mb : final_ram) {
        ofs << "    EXPECT_EQ(memory.load8(0x";
        fmt_hex5(ofs, mb.first);
        ofs << "), 0x";
        fmt_hex2(ofs, static_cast<unsigned>(mb.second));
        ofs << ");\n";
    }
    ofs << "}\n";
}
