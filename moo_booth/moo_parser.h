// (C) 2025 Daniel Balsom

#ifndef MOO_PARSER_H
#define MOO_PARSER_H

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "test_case.h"

class MooParser {
public:
    struct MemStream {
        const uint8_t *data = nullptr;
        size_t size         = 0;
        size_t pos          = 0;

        bool read(void *buf, size_t len);
        bool read_u32_le(uint32_t &out);
        bool read_chunk(char *out_type, uint32_t &out_len, const uint8_t *&out_data);
    };

    explicit MooParser(const std::string &path);

    std::optional<TestCase> next();

private:
    std::vector<uint8_t> buffer_;
    MemStream stream_{ nullptr, 0, 0 };
    bool header_printed_ = false;
};

#endif
