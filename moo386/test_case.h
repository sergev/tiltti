// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#ifndef MOO_TEST_CASE_H
#define MOO_TEST_CASE_H

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

using OptReg32 = std::optional<uint32_t>;
using MemByte  = std::pair<unsigned, uint8_t>;

// 386 register set (order matches MOO RG32/RM32 chunk bitmask).
enum class REG : uint8_t {
    CR0 = 0,
    CR3,
    EAX,
    EBX,
    ECX,
    EDX,
    ESI,
    EDI,
    EBP,
    ESP,
    CS,
    DS,
    ES,
    FS,
    GS,
    SS,
    EIP,
    EFLAGS,
    DR6,
    DR7,
    COUNT = 20
};

inline const char *get_register_name(REG r)
{
    static const char *const names[] = { "cr0", "cr3", "eax", "ebx",    "ecx", "edx", "esi",
                                         "edi", "ebp", "esp", "cs",     "ds",  "es",  "fs",
                                         "gs",  "ss",  "eip", "eflags", "dr6", "dr7" };
    return names[static_cast<size_t>(r)];
}

class TestCase {
public:
    TestCase(uint32_t index, uint32_t chunk_len, const uint8_t *payload);

    uint32_t index() const { return index_; }
    const std::string &name() const { return name_; }
    OptReg32 get_initial_reg(REG r) const;
    OptReg32 get_final_reg(REG r) const;

    bool has_initial_reg(REG r) const { return get_initial_reg(r).has_value(); }
    bool has_final_reg(REG r) const { return get_final_reg(r).has_value(); }

    // TODO: Is this index in final_ram correspond to FLAGS register, saved in memory?
    static bool is_flags_in_mem(size_t index) { return false; }

    // Is this test bad and should be skipped?
    static bool invalid() { return false; }

    void print(std::ostream &os) const;
    void emit_gtest() const;
    void run() const;

private:
    static constexpr size_t MAX_NAME_LEN = 256;

    static uint32_t read_u32_le(const uint8_t *p);
    static std::ostream &fmt_hex2(std::ostream &os, unsigned v);
    static std::ostream &fmt_hex5(std::ostream &os, unsigned v);
    static std::ostream &fmt_hex8(std::ostream &os, unsigned v);
    static void parse_regs_32_into(const uint8_t *data, uint32_t len, OptReg32 *regs);
    static void parse_masks_32_into(const uint8_t *data, uint32_t len, OptReg32 *masks);
    static void parse_ram_into(const uint8_t *data, uint32_t len, std::vector<MemByte> &out);
    static void parse_cpu_state(const uint8_t *data, uint32_t len, OptReg32 *regs, OptReg32 *masks,
                                std::vector<MemByte> &ram);

    uint32_t index_;
    uint32_t chunk_len_;
    std::string name_;
    OptReg32 initial_regs_[static_cast<size_t>(REG::COUNT)];
    OptReg32 initial_masks_[static_cast<size_t>(REG::COUNT)];
    OptReg32 final_regs_[static_cast<size_t>(REG::COUNT)];
    OptReg32 final_masks_[static_cast<size_t>(REG::COUNT)];
    std::vector<MemByte> initial_ram, final_ram;
};

#endif
