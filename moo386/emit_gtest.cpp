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
// working directory. Uses fixture.h, Test386, cpu, machine, memory. Emits 32-bit register
// get/set calls for 386.
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

    //ofs << "#include \"fixture.h\"\n";
    ofs << "\n";
    ofs << "//\n// " << name_ << "\n//\n";
    ofs << "TEST_F(Test386, DISABLED_" << base << ")\n";
    ofs << "{\n";
    ofs << "    // Initial CPU State\n";

    for (size_t i = 0; i < static_cast<size_t>(REG::COUNT); i++) {
        REG r  = static_cast<REG>(i);
        auto v = get_initial_reg(r);
        if (v) {
            ofs << "    cpu.set_" << get_register_name(r) << "(0x";
            fmt_hex8(ofs, *v);
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
    ofs << "    cpu.step();\n";
    ofs << "    if (!cpu.is_halted())\n";
    ofs << "        cpu.step(); // HLT\n\n";
    ofs << "    // Final CPU State\n";

    for (size_t i = 0; i < static_cast<size_t>(REG::COUNT); i++) {
        REG r  = static_cast<REG>(i);
        if (r == REG::EFLAGS)
            continue;
        auto v = get_final_reg(r);
        if (v) {
            ofs << "    EXPECT_EQ(cpu.get_" << get_register_name(r) << "(), 0x";
            fmt_hex8(ofs, *v);
            ofs << ");\n";
        }
    }
    auto v = get_final_reg(REG::EFLAGS);
    if (v) {
        ofs << "    EXPECT_FLAGS(0x";
        fmt_hex8(ofs, *v);
        ofs << ");\n";
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
