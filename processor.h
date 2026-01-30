//
// PC i86 processor unit.
//
// Copyright (c) 2026 Serge Vakulenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef TILTTI_PROCESSOR_H
#define TILTTI_PROCESSOR_H

#include <cstdint>
#include <string>

#include "i86_arch.h"

class Machine;
class Memory;

//
// Internal state of the processor.
//
struct CoreState {
    unsigned ip;           // instruction pointer

    //TODO: registers
};

//
// PC i86 processor.
//
class Processor {
private:
    Machine &machine;        // Reference to the machine
    Memory &memory;          // Physical memory
    struct CoreState core{}; // Current state
    struct CoreState prev{}; // Previous state, for tracing
    unsigned opcode{};       // Current instruction being executed

    // Intercept divzero/overflow.
    unsigned intercept_count{};     // intercept this many times
    unsigned intercept_addr{ 020 }; // jump to this address
    const std::string MSG_ARITH_OVERFLOW = "Arithmetic overflow";
    const std::string MSG_ARITH_DIVZERO  = "Division by zero";

public:
    // Exception for unexpected situations.
    class Exception : public std::exception {
    private:
        std::string message;

    public:
        explicit Exception(const std::string &m) : message(m) {}
        const char *what() const noexcept override { return message.c_str(); }
    };

    // Constructor.
    Processor(Machine &machine, Memory &memory);

    // Reset to initial state.
    void reset();

    // Simulate one instruction.
    void step();

    // Finalize the processor.
    void finish();

    // Set register value.
    void set_ip(unsigned val) { core.ip = val; }

    // Get register value.
    unsigned get_ip() const { return core.ip; }

    // Intercept ofvl/divzero exception, when enabled.
    bool intercept(const std::string &message);

    // Print trace info.
    void print_instruction();
    void print_registers();
};

#endif // TILTTI_PROCESSOR_H
