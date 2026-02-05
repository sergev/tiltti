// (C) 2025 Daniel Balsom

#include "test_case.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <sstream>

const char *const TestCase::REG_LUT[] = { "ax", "bx", "cx", "dx", "cs", "ss", "ds",
                                          "es", "sp", "bp", "si", "di", "ip", "flags" };

//
// MOO format is little-endian; subchunk payloads use 16- and 32-bit fields (bitmasks, lengths,
// counts, indices). Static helpers avoid duplicating decode logic. Interprets 2 bytes at p as
// unsigned little-endian value; no bounds check (caller ensures sufficient payload).
//
uint16_t TestCase::read_u16_le(const uint8_t *p)
{
    return static_cast<uint16_t>(p[0]) | (static_cast<uint16_t>(p[1]) << 8);
}

//
// Same rationale as read_u16_le; 4 bytes at p.
// Interprets as unsigned little-endian; no bounds check.
//
uint32_t TestCase::read_u32_le(const uint8_t *p)
{
    return p[0] | (static_cast<uint32_t>(p[1]) << 8) | (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

//
// Consistent hex formatting for human-readable output: 2 digits for bytes, 4 for 16-bit
// registers, 5 for 20-bit addresses. Formats v as zero-padded uppercase hex with the given
// width to the provided ostream; returns the stream for chaining.
//
std::ostream &TestCase::fmt_hex2(std::ostream &os, unsigned v)
{
    std::ostringstream o;
    o << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << v;
    return os << o.str();
}

//
// Same as fmt_hex2; 4-digit width for 16-bit register values.
//
std::ostream &TestCase::fmt_hex4(std::ostream &os, unsigned v)
{
    std::ostringstream o;
    o << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << v;
    return os << o.str();
}

//
// Same as fmt_hex2; 5-digit width for 20-bit addresses.
//
std::ostream &TestCase::fmt_hex5(std::ostream &os, unsigned v)
{
    std::ostringstream o;
    o << std::uppercase << std::hex << std::setw(5) << std::setfill('0') << v;
    return os << o.str();
}

//
// REGS subchunk (inside INIT/FINA) encodes which registers are present and their values; only
// set bits in the bitmask have following values (spec: "only registers that were modified" in
// final state). First 2 bytes = little-endian bitmask (bit 0 = ax ... bit 13 = flags). For each
// set bit in order, read one 16-bit little-endian value into the corresponding reg slot.
// Stops if payload is exhausted.
//
void TestCase::parse_regs_into(const uint8_t *data, uint32_t len, OptReg *regs)
{
    if (len < 2)
        return;
    uint16_t bitmask   = read_u16_le(data);
    const uint8_t *p   = data + 2;
    uint32_t remaining = len - 2;
    for (size_t i = 0; i < REG_COUNT; i++) {
        if ((bitmask >> i) & 1) {
            if (remaining < 2)
                break;
            regs[i] = read_u16_le(p);
            p += 2;
            remaining -= 2;
        }
    }
}

//
// RAM subchunk lists memory (address, value) pairs to set before/after the test (spec: "should
// be written at their indicated ... addresses"). First 4 bytes = entry count (little-endian).
// Each entry is 4-byte address (LE) + 1 byte value. Clears out and fills it with (addr, val)
// pairs; returns early if payload is too short.
//
void TestCase::parse_ram_into(const uint8_t *data, uint32_t len, std::vector<MemByte> &out)
{
    out.clear();
    if (len < 4)
        return;
    uint32_t count = read_u32_le(data);
    if (len < 4 + count * 5)
        return;
    const uint8_t *p = data + 4;
    for (uint32_t i = 0; i < count; i++) {
        unsigned addr = static_cast<unsigned>(read_u32_le(p));
        uint8_t val   = p[4];
        out.emplace_back(addr, val);
        p += 5;
    }
}

//
// INIT and FINA payloads are a sequence of subchunks (REGS, RAM); this walks that sequence and
// fills the given register array and RAM vector. Scan payload for subchunks (4-byte type +
// 4-byte length + data). On "REGS" call parse_regs_into; on "RAM " call parse_ram_into. Advance
// by chunk length so we do not assume chunks are back-to-back (per spec).
//
void TestCase::parse_cpu_state(const uint8_t *data, uint32_t len, OptReg *regs,
                               std::vector<MemByte> &ram)
{
    const uint8_t *end = data + len;
    const uint8_t *p   = data;
    while (p + 8 <= end) {
        char chunk_type[5];
        std::memcpy(chunk_type, p, 4);
        chunk_type[4] = '\0';
        p += 4;
        uint32_t chunk_len = read_u32_le(p);
        p += 4;
        if (p + chunk_len > end)
            break;
        if (std::strcmp(chunk_type, "REGS") == 0) {
            parse_regs_into(p, chunk_len, regs);
        } else if (std::strcmp(chunk_type, "RAM ") == 0) {
            parse_ram_into(p, chunk_len, ram);
        }
        p += chunk_len;
    }
}

//
// Builds one test case from a TEST chunk payload (index and length already read by MooParser);
// subchunks define name and initial/final CPU state. Payload is a concatenation of subchunks.
// Loop: read subchunk type and length. NAME: length-prefixed UTF-8 name (4-byte length then
// bytes), capped at MAX_NAME_LEN. INIT: parse_cpu_state into initial registers and initial_ram.
// FINA: parse_cpu_state into final registers and final_ram. Other subchunk types skipped (e.g.
// BYTS, CYCL, HASH) so the parser remains forward-compatible.
//
TestCase::TestCase(uint32_t index, uint32_t chunk_len, const uint8_t *payload)
    : index_(index), chunk_len_(chunk_len)
{
    const uint32_t payload_len = (chunk_len >= 4) ? (chunk_len - 4) : 0;
    const uint8_t *end         = payload + payload_len;
    const uint8_t *p           = payload;

    OptReg *initial_regs[] = { &initial_ax, &initial_bx, &initial_cx, &initial_dx,   &initial_cs,
                               &initial_ss, &initial_ds, &initial_es, &initial_sp,   &initial_bp,
                               &initial_si, &initial_di, &initial_ip, &initial_flags };
    OptReg *final_regs[]   = { &final_ax, &final_bx, &final_cx, &final_dx,   &final_cs,
                               &final_ss, &final_ds, &final_es, &final_sp,   &final_bp,
                               &final_si, &final_di, &final_ip, &final_flags };

    while (p + 8 <= end) {
        char subchunk_type[5];
        std::memcpy(subchunk_type, p, 4);
        subchunk_type[4] = '\0';
        p += 4;
        uint32_t subchunk_len = read_u32_le(p);
        p += 4;
        if (subchunk_len == 0 || p + subchunk_len > end)
            break;

        if (std::strcmp(subchunk_type, "NAME") == 0) {
            if (subchunk_len >= 4) {
                uint32_t slen = read_u32_le(p);
                size_t copy_len =
                    std::min(static_cast<size_t>(slen), static_cast<size_t>(subchunk_len - 4));
                if (copy_len > MAX_NAME_LEN)
                    copy_len = MAX_NAME_LEN;
                name_.assign(reinterpret_cast<const char *>(p + 4), copy_len);
            }
        } else if (std::strcmp(subchunk_type, "INIT") == 0) {
            parse_cpu_state(p, subchunk_len, initial_regs[0], initial_ram);
        } else if (std::strcmp(subchunk_type, "FINA") == 0) {
            parse_cpu_state(p, subchunk_len, final_regs[0], final_ram);
        }
        p += subchunk_len;
    }
}

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
