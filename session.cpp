//
// Class Session: collect parameters for simulation and run the Machine instance.
// Hide all internals from user.
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
#include "session.h"

#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "machine.h"

//
// Internal implementation of the simulation session, hidden from user.
//
class Session::Hidden {
private:
    Memory memory;
    Machine machine{ memory };

    // A name of input file for overlay.
    std::string disk_file;

    // Status of the simulation.
    int exit_status{ EXIT_SUCCESS };

public:
    //
    // Get status of simulation: either EXIT_SUCCESS (0) or
    // EXIT_FAILURE in case of errors.
    //
    int get_exit_status() const { return exit_status; }

    //
    // Set name of input file.
    //
    void set_disk_file(const char *filename)
    {
        if (!disk_file.empty()) {
            std::cerr << "Too many input files: " << filename << std::endl;
            ::exit(EXIT_FAILURE);
        }
        disk_file = filename;
    }

    const std::string &get_disk_file() const { return disk_file; }

    //
    // Run simulation session with given parameters.
    //
    void run()
    {
        try {
            // Boot from disk.
            machine.boot_disk(disk_file);

            // Run simulation.
            machine.run();

        } catch (const std::exception &ex) {
            // Print exception message.
            std::cerr << "Error: " << ex.what() << std::endl;
            exit_status = EXIT_FAILURE;
        } catch (...) {
            // Assuming the exception message already printed.
            exit_status = EXIT_FAILURE;
        }
    }

    //
    // Finish simulation.
    // Close trace files.
    //
    void finish()
    {
        // Finish the trace output.
        Machine::close_trace();
    }

    //
    // Enable verbose mode.
    // Print more details to the trace log.
    //
    void set_verbose(bool on) { machine.set_verbose(on); }

    //
    // Enable trace log to stdout.
    //
    void enable_trace(const char *mode)
    {
        if (mode && *mode) {
            Machine::enable_trace(mode);
        } else {
            Machine::close_trace();
        }
    }

    //
    // Enable trace log to the specified file.
    //
    void set_trace_file(const char *filename, const char *default_mode)
    {
        Machine::redirect_trace(filename, default_mode);
        Machine::get_trace_stream() << "PC i86 Simulator Version: " << VERSION_STRING << "\n";
    }

    //
    // Backdoor access to DRAM memory.
    // No tracing.
    //
    void mem_write(const Bytes &input, unsigned addr) { memory.write_bytes(input, addr); }

    void mem_read(Bytes &output, unsigned nbytes, unsigned addr)
    {
        memory.read_bytes(output, nbytes, addr);
    }

};

//
// Instaltiate the Session object.
// Allocate the internal implementation.
//
Session::Session() : internal(std::make_unique<Session::Hidden>())
{
}

//
// Destructor: implicitly delete the hidden object.
//
Session::~Session() = default;

//
// Set name of input file.
//
void Session::set_disk_file(const char *filename)
{
    internal->set_disk_file(filename);
}

const std::string &Session::get_disk_file()
{
    return internal->get_disk_file();
}

//
// Get status of simulation: either EXIT_SUCCESS (0) or
// EXIT_FAILURE in case of errors.
//
int Session::get_exit_status()
{
    return internal->get_exit_status();
}

//
// Run simulation session with given parameters.
//
void Session::run()
{
    internal->run();
}

//
// Finish simulation.
//
void Session::finish()
{
    internal->finish();
}

//
// Enable a trace log to stdout or to the specified file.
//
void Session::enable_trace(const char *mode)
{
    internal->enable_trace(mode);
}

void Session::set_trace_file(const char *filename, const char *default_mode)
{
    internal->set_trace_file(filename, default_mode);
}

//
// Enable verbose mode.
//
void Session::set_verbose(bool on)
{
    internal->set_verbose(on);
}

//
// Get the number of simulated instructions.
//
uint64_t Session::get_instr_count()
{
    return Machine::get_instr_count();
}

//
// Get version of the simulator.
//
const char *Session::get_version()
{
    // Return string, obtained from CMakeLists.txt.
    return VERSION_STRING;
}

//
// Access to DRAM memory.
//
void Session::mem_write(const Bytes &input, unsigned addr)
{
    internal->mem_write(input, addr);
}

void Session::mem_read(Bytes &output, unsigned nbytes, unsigned addr)
{
    internal->mem_read(output, nbytes, addr);
}
