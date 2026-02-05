// (C) 2025 Daniel Balsom

#ifndef MOO_TEST_CASE_H
#define MOO_TEST_CASE_H

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

using OptReg  = std::optional<uint16_t>;
using MemByte = std::pair<unsigned, uint8_t>;

class TestCase {
public:
    TestCase(uint32_t index, uint32_t chunk_len, const uint8_t *payload);

    void print(std::ostream &os) const;
    void emit_gtest() const;

private:
    static const char *const REG_LUT[];
    static constexpr size_t REG_COUNT    = 14;
    static constexpr size_t MAX_NAME_LEN = 256;

    static uint16_t read_u16_le(const uint8_t *p);
    static uint32_t read_u32_le(const uint8_t *p);
    static std::ostream &fmt_hex2(std::ostream &os, unsigned v);
    static std::ostream &fmt_hex4(std::ostream &os, unsigned v);
    static std::ostream &fmt_hex5(std::ostream &os, unsigned v);
    static void parse_regs_into(const uint8_t *data, uint32_t len, OptReg *regs);
    static void parse_ram_into(const uint8_t *data, uint32_t len, std::vector<MemByte> &out);
    static void parse_cpu_state(const uint8_t *data, uint32_t len, OptReg *regs,
                                std::vector<MemByte> &ram);

    uint32_t index_;
    uint32_t chunk_len_;
    std::string name_;
    OptReg initial_ax, initial_bx, initial_cx, initial_dx, initial_cs, initial_ss, initial_ds,
        initial_es, initial_sp, initial_bp, initial_si, initial_di, initial_ip, initial_flags;
    OptReg final_ax, final_bx, final_cx, final_dx, final_cs, final_ss, final_ds, final_es, final_sp,
        final_bp, final_si, final_di, final_ip, final_flags;
    std::vector<MemByte> initial_ram, final_ram;
};

#endif
