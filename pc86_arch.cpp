//
// i86 architecture details implementation.
//
// Copyright (c) 2026 Serge Vakulenko
//
#include "pc86_arch.h"

#include <sstream>

//
// Convert number to hex string.
//
std::string to_hex(unsigned val)
{
    std::ostringstream os;
    os << std::hex << val;
    return os.str();
}
