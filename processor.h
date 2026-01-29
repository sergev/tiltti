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
    unsigned PC;           // program counter СчАС
    unsigned M[16];        // registers modifiers
};

//
// PC i86 processor.
//
class Processor {
private:
    // Reference to the machine.
    Machine &machine;

    // 32K words of virtual memory.
    Memory &memory;

    // Current state.
    struct CoreState core{};

    // Previous state, for tracing.
    struct CoreState prev{};

    unsigned RK{};    // регистр команд
    unsigned Aex{};   // executive address

    // Intercept divzero/overflow.
    unsigned intercept_count{};     // intercept this many times
    unsigned intercept_addr{ 020 }; // jump to this address
    const std::string MSG_ARITH_OVERFLOW = "Arithmetic overflow";
    const std::string MSG_ARITH_DIVZERO  = "Division by zero";

    // Get CPU time in 1/50 of second.
    unsigned get_cpu_time();

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
    void set_pc(unsigned val) { core.PC = val; }
    void set_m(unsigned index, unsigned val) { core.M[index] = val; }

    // Get register value.
    unsigned get_pc() const { return core.PC; }
    unsigned get_m(unsigned index) const { return core.M[index]; }

    // Intercept ofvl/divzero exception, when enabled.
    bool intercept(const std::string &message);

    // Print trace info.
    void print_instruction();
    void print_registers();
};

#endif // TILTTI_PROCESSOR_H
