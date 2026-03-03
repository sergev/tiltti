// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include "test_case.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#if 0
//
// As I can see in some tests CS is changed without any reason.
// Let's skip those for now.
//
bool TestCase::invalid() const
{
    return has_initial_reg(REG::CS) &&
           has_final_reg(REG::CS) &&
           *get_final_reg(REG::CS) != *get_initial_reg(REG::CS);
}
#endif

//
// MOO format is little-endian. Interprets 4 bytes at p as unsigned little-endian; no bounds
// check (caller ensures sufficient payload).
//
uint32_t TestCase::read_u32_le(const uint8_t *p)
{
    return p[0] | (static_cast<uint32_t>(p[1]) << 8) | (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

//
// Consistent hex formatting: 2 digits for bytes, 5 for addresses, 8 for 32-bit registers.
//
std::ostream &TestCase::fmt_hex2(std::ostream &os, unsigned v)
{
    std::ostringstream o;
    o << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << v;
    return os << o.str();
}

std::ostream &TestCase::fmt_hex5(std::ostream &os, unsigned v)
{
    std::ostringstream o;
    o << std::uppercase << std::hex << std::setw(5) << std::setfill('0') << v;
    return os << o.str();
}

std::ostream &TestCase::fmt_hex8(std::ostream &os, unsigned v)
{
    std::ostringstream o;
    o << std::uppercase << std::hex << std::setw(8) << std::setfill('0') << v;
    return os << o.str();
}

//
// RG32 subchunk: 4-byte bitmask (LE), then for each set bit 0..31 a 4-byte value (LE).
// REG order: CR0(0), CR3(1), EAX(2)..DR7(19).
//
void TestCase::parse_regs_32_into(const uint8_t *data, uint32_t len, OptReg32 *regs)
{
    if (len < 4)
        return;
    uint32_t bitmask   = read_u32_le(data);
    const uint8_t *p   = data + 4;
    uint32_t remaining = len - 4;
    for (size_t i = 0; i < 32 && i < static_cast<size_t>(REG::COUNT); i++) {
        if ((bitmask >> i) & 1) {
            if (remaining < 4)
                break;
            regs[i] = read_u32_le(p);
            p += 4;
            remaining -= 4;
        }
    }
}

//
// RM32 subchunk: same layout as RG32; stores masks for masked final-register comparison.
//
void TestCase::parse_masks_32_into(const uint8_t *data, uint32_t len, OptReg32 *masks)
{
    parse_regs_32_into(data, len, masks);
}

//
// RAM subchunk: 4-byte count (LE), then count entries of (4-byte addr, 1-byte value).
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
// INIT/FINA subchunks: RG32, RM32, RAM; skip EA32 and other unknown types.
//
void TestCase::parse_cpu_state(const uint8_t *data, uint32_t len, OptReg32 *regs, OptReg32 *masks,
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
        if (std::strcmp(chunk_type, "RG32") == 0) {
            parse_regs_32_into(p, chunk_len, regs);
        } else if (std::strcmp(chunk_type, "RM32") == 0) {
            parse_masks_32_into(p, chunk_len, masks);
        } else if (std::strcmp(chunk_type, "RAM ") == 0) {
            parse_ram_into(p, chunk_len, ram);
        }
        p += chunk_len;
    }
}

OptReg32 TestCase::get_initial_reg(REG r) const
{
    size_t i = static_cast<size_t>(r);
    if (i >= static_cast<size_t>(REG::COUNT))
        return std::nullopt;
    return initial_regs_[i];
}

OptReg32 TestCase::get_final_reg(REG r) const
{
    size_t i = static_cast<size_t>(r);
    if (i >= static_cast<size_t>(REG::COUNT))
        return std::nullopt;
    OptReg32 v = final_regs_[i];
    if (!v)
        return get_initial_reg(r);
    if (final_masks_[i]) {
        return *v & *final_masks_[i];
    }
    return v;
}

//
// Builds one test case from a TEST chunk payload. Subchunks: NAME, BYTS, INIT, FINA, etc.
// INIT/FINA use RG32, RM32, RAM (386 format). Skip GMET, EA32, BYTS, CYCL, HASH.
//
TestCase::TestCase(uint32_t index, uint32_t chunk_len, const uint8_t *payload)
    : index_(index), chunk_len_(chunk_len)
{
    const uint32_t payload_len = (chunk_len >= 4) ? (chunk_len - 4) : 0;
    const uint8_t *end         = payload + payload_len;
    const uint8_t *p           = payload;

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
            parse_cpu_state(p, subchunk_len, initial_regs_, initial_masks_, initial_ram);
        } else if (std::strcmp(subchunk_type, "FINA") == 0) {
            parse_cpu_state(p, subchunk_len, final_regs_, final_masks_, final_ram);
        }
        p += subchunk_len;
    }
}
