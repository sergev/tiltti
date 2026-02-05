// Example parser for the MOO CPU test format.
// Supports both plain and gzipped MOO files.

// (C) 2025 Daniel Balsom

#include <iostream>
#include <stdexcept>
#include <string>

#include "moo_parser.h"

namespace {

bool parse_uint_arg(const std::string &arg, const std::string &prefix, int &out_val)
{
    if (arg.size() < prefix.size() || arg.compare(0, prefix.size(), prefix) != 0)
        return false;
    try {
        size_t pos;
        long val = std::stol(arg.substr(prefix.size()), &pos);
        if (pos == arg.size() - prefix.size() && val >= 0) {
            out_val = static_cast<int>(val);
            return true;
        }
    } catch (...) {
    }
    return false;
}

} // namespace

int main(int argc, char **argv)
{
    int limit            = -1;
    int index            = -1;
    bool use_gtest       = false;
    const char *filename = nullptr;

    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        if (parse_uint_arg(arg, "-limit=", limit))
            continue;
        if (parse_uint_arg(arg, "-index=", index))
            continue;
        if (arg == "-gtest") {
            use_gtest = true;
            continue;
        }
        if (filename == nullptr) {
            filename = argv[i];
        } else {
            std::cerr << "Unexpected argument: " << argv[i] << "\n";
            return 1;
        }
    }

    if (filename == nullptr) {
        std::cerr << "Usage: " << argv[0] << " [-limit=N] [-index=N] [-gtest] <binary_test_file>\n";
        return 1;
    }

    try {
        MooParser parser(filename);
        int count = 0;
        while (auto rec = parser.next()) {
            if (index >= 0 && count != index) {
                count++;
                continue;
            }
            if (use_gtest)
                rec->emit_gtest();
            else
                rec->print(std::cout);
            count++;
            if (limit >= 0 && count >= limit)
                break;
            if (index >= 0 && count > index)
                break;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
