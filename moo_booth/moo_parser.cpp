// Copyright (c) 2026 Serge Vakulenko
// Licensed under the MIT License.

#include "moo_parser.h"

#include <zlib.h>

#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

//
// Low-level read so we can parse variable-length chunks without copying payloads; advances
// stream position for sequential parsing. Reads exactly len bytes into buf if remaining
// stream size allows; returns false on overrun so callers can handle EOF/invalid format.
//
bool MooParser::MemStream::read(void *buf, size_t len)
{
    if (pos + len > size)
        return false;
    std::memcpy(buf, data + pos, len);
    pos += len;
    return true;
}

//
// MOO spec requires all multi-byte fields in little-endian; 4-byte length and count fields
// are common. Reads one uint32 in little-endian order; returns false if fewer than 4 bytes remain.
//
bool MooParser::MemStream::read_u32_le(uint32_t &out)
{
    uint8_t buf[4];
    if (!read(buf, 4))
        return false;
    out = static_cast<uint32_t>(buf[0]) | (static_cast<uint32_t>(buf[1]) << 8) |
          (static_cast<uint32_t>(buf[2]) << 16) | (static_cast<uint32_t>(buf[3]) << 24);
    return true;
}

//
// Top-level and nested chunks share the same layout (type + length + payload); this
// centralizes bounds checks and position advance. Reads 4-byte ASCII chunk type
// (null-terminated for C string use), 4-byte little-endian length, then sets out_data to a
// pointer into the stream (no copy). Advances past the full chunk. Returns false if
// the header or payload would exceed stream size.
//
bool MooParser::MemStream::read_chunk(char *out_type, uint32_t &out_len, const uint8_t *&out_data)
{
    if (pos + 8 > size)
        return false;
    std::memcpy(out_type, data + pos, 4);
    out_type[4] = '\0';
    pos += 4;
    if (!read_u32_le(out_len))
        return false;
    if (pos + out_len > size)
        return false;
    out_data = data + pos;
    pos += out_len;
    return true;
}

//
// MOO files are read fully into memory so we can iterate chunks via MemStream and pass
// payload pointers into TestCase without copying. Opens the given path in binary mode,
// reads entire file into buffer_, and initializes stream_ over that buffer.
// Throws on open/read errors.
//
MooParser::MooParser(const std::string &path)
{
    std::ifstream f(path, std::ios::binary);
    if (!f)
        throw std::runtime_error(std::string("Error opening file: ") + std::strerror(errno));
    f.seekg(0, std::ios::end);
    const std::streamsize filesize = f.tellg();
    f.seekg(0, std::ios::beg);
    if (filesize < 0)
        throw std::runtime_error("Error reading file");
    buffer_.resize(static_cast<size_t>(filesize));
    if (!f.read(reinterpret_cast<char *>(buffer_.data()), filesize) || f.gcount() != filesize)
        throw std::runtime_error("Error reading file");

    // If gzip magic (0x1f 0x8b), decompress into buffer_ before parsing.
    if (buffer_.size() >= 2 && buffer_[0] == 0x1f && buffer_[1] == 0x8b) {
        z_stream strm;
        strm.zalloc   = Z_NULL;
        strm.zfree    = Z_NULL;
        strm.opaque   = Z_NULL;
        strm.next_in  = Z_NULL;
        strm.avail_in = 0;
        if (inflateInit2(&strm, 15 + 16) != Z_OK) {
            throw std::runtime_error("Invalid or unsupported gzip data");
        }
        strm.next_in  = buffer_.data();
        strm.avail_in = static_cast<uInt>(buffer_.size());
        std::vector<uint8_t> decompressed;
        const size_t chunk = 65536;
        uint8_t tmp[65536];
        int ret;
        do {
            strm.next_out  = tmp;
            strm.avail_out = chunk;
            ret            = inflate(&strm, Z_NO_FLUSH);
            if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
                inflateEnd(&strm);
                throw std::runtime_error("Invalid or unsupported gzip data");
            }
            size_t have = chunk - strm.avail_out;
            decompressed.insert(decompressed.end(), tmp, tmp + have);
        } while (ret != Z_STREAM_END);
        inflateEnd(&strm);
        buffer_ = std::move(decompressed);
    }

    stream_ = MemStream{ buffer_.data(), buffer_.size(), 0 };
}

//
// Iterator-style API: each call returns the next test case or nullopt when no more data;
// handles file-level MOO header and unknown chunks so the caller only sees TEST chunks as
// TestCase objects. Loop: read next top-level chunk. If "MOO " (file header), print
// version/test count/CPU name once then skip. If "TEST", parse index and payload and return
// one TestCase. Otherwise log unknown chunk and skip (per spec: ignore unrecognized chunk
// types). Return nullopt when no chunk can be read (end of file).
//
std::optional<TestCase> MooParser::next()
{
    while (true) {
        char chunk_type[5];
        uint32_t chunk_len;
        const uint8_t *chunk_data;

        if (!stream_.read_chunk(chunk_type, chunk_len, chunk_data))
            return std::nullopt;

        if (std::strcmp(chunk_type, "MOO ") == 0) {
            if (!header_printed_) {
                if (chunk_len != 12) {
                    std::cout << "Invalid MOO chunk length: expected 12, got " << chunk_len << "\n";
                } else {
                    uint32_t version = chunk_data[0] | (static_cast<uint32_t>(chunk_data[1]) << 8) |
                                       (static_cast<uint32_t>(chunk_data[2]) << 16) |
                                       (static_cast<uint32_t>(chunk_data[3]) << 24);
                    uint32_t file_test_count = chunk_data[4] |
                                               (static_cast<uint32_t>(chunk_data[5]) << 8) |
                                               (static_cast<uint32_t>(chunk_data[6]) << 16) |
                                               (static_cast<uint32_t>(chunk_data[7]) << 24);
                    char cpu_name[5] = { 0 };
                    std::memcpy(cpu_name, chunk_data + 8, 4);
                    for (int i = 3; i >= 0; i--) {
                        if (cpu_name[i] == ' ')
                            cpu_name[i] = '\0';
                        else
                            break;
                    }
                    std::cout << "File MOO Chunk:\n  Version: " << version
                              << "\n  Test Count: " << file_test_count
                              << "\n  CPU type: " << cpu_name << "\n";
                }
                header_printed_ = true;
            }
            continue;
        }

        if (std::strcmp(chunk_type, "TEST") == 0) {
            uint32_t test_idx = chunk_data[0] | (static_cast<uint32_t>(chunk_data[1]) << 8) |
                                (static_cast<uint32_t>(chunk_data[2]) << 16) |
                                (static_cast<uint32_t>(chunk_data[3]) << 24);
            const uint8_t *payload = chunk_data + 4;
            return TestCase(test_idx, chunk_len, payload);
        }

        std::cout << "Unknown top-level chunk '" << chunk_type << "' (" << chunk_len
                  << " bytes), skipping\n";
    }
}
