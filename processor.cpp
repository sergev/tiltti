//
// i86 processor.
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
#include "machine.h"

//
// Initialize the processor.
//
Processor::Processor(Machine &mach, Memory &mem) : machine(mach), memory(mem)
{
    reset();
}

//
// Finish the processor
//
void Processor::finish()
{
    //TODO
}

//
// Reset routine
//
void Processor::reset()
{
    //TODO
    core    = {};
    core.PC = 1;

    machine.trace_exception("Reset");
}

//
// Intercept ofvl/divzero exception, when enabled.
// Return true when intercepted.
// Return false when interception is disabled.
//
bool Processor::intercept(const std::string &message)
{
    //TODO
    if (intercept_count > 0 &&            // interception enabled
        (message == MSG_ARITH_OVERFLOW || // arithmetic overflow
         message == MSG_ARITH_DIVZERO)) { // divide by zero

        intercept_count--;

        // Jump to dedicated address.
        core.PC = intercept_addr;
        return true;
    } else {
        return false;
    }
}

//
// Execute one instruction, placed at address PC.
// Increment PC.
// Emit exception in case of failure.
//
void Processor::step()
{
    //TODO
}
