//
// i86 architecture details implementation.
//
// Copyright (c) 2026 Serge Vakulenko
//
#include "i86_arch.h"

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

//
// Check whether instruction is syscall (INT n, INT 3, INTO).
// Uses first byte of opcode (caller passes low byte or full uint64_t).
//
bool is_syscall(unsigned opcode)
{
    unsigned b = opcode & 0xff;
    return b == 0xcd || b == 0xcc || b == 0xce;
}
