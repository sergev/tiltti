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
#include <getopt.h>

#include <cstring>
#include <iostream>

#include "machine.h"

//
// CLI options.
//
static const struct option long_options[] = {
    // clang-format off
    { "help",           no_argument,        nullptr,    'h' },
    { "version",        no_argument,        nullptr,    'V' },
    { "verbose",        no_argument,        nullptr,    'v' },
    { "output",         required_argument,  nullptr,    'o' },
    { "regs",           required_argument,  nullptr,    'r' },
    { "ports",          required_argument,  nullptr,    'p' },
    { "syscalls",       required_argument,  nullptr,    's' },
    {},
    // clang-format on
};

//
// Print usage message.
//
static void print_usage(std::ostream &out, const char *prog_name)
{
    out << "PC i86 Simulator, Version " << VERSION_STRING << "\n";
    out << "Usage:" << std::endl;
    out << "    " << prog_name << " [options...] disk.img" << std::endl;
    out << "Input files:" << std::endl;
    out << "    disk.img                Image of bootable PC floppy or disk" << std::endl;
    out << "Options:" << std::endl;
    out << "    -v, --verbose           Verbose mode" << std::endl;
    out << "    -V, --version           Print the version number and exit" << std::endl;
    out << "    -h, --help              Display available options" << std::endl;
    out << "Trace modes:" << std::endl;
    out << "    -r, --regs              Trace registers and everything else" << std::endl;
    out << "    -s, --syscalls          Trace INT software interrupts" << std::endl;
    out << "    -p, --ports             Trace IN and OUT port access" << std::endl;
    out << "    -o, --output=FILE       Redirect trace to the file" << std::endl;
}

//
// Main routine of the simulator,
// when invoked from a command line.
//
int main(int argc, char *argv[])
{
    // Get the program name.
    const char *prog_name = strrchr(argv[0], '/');
    if (prog_name == nullptr) {
        prog_name = argv[0];
    } else {
        prog_name++;
    }

    Memory memory;
    bool verbose = false;
    std::string disk_file;

    // Parse command line options.
    for (;;) {
        switch (getopt_long(argc, argv, "-hVvrspo:", long_options, nullptr)) {
        case EOF:
            break;

        case 0:
            continue;

        case 1:
            // Regular argument.
            if (!disk_file.empty()) {
                std::cerr << "Too many arguments: " << optarg << std::endl;
                print_usage(std::cerr, prog_name);
                ::exit(EXIT_FAILURE);
            }
            disk_file = optarg;
            continue;

        case 'h':
            // Show usage message and exit.
            print_usage(std::cout, prog_name);
            exit(EXIT_SUCCESS);

        case 'v':
            verbose = true;
            continue;

        case 'V':
            // Show version and exit.
            std::cout << "Version " << VERSION_STRING << "\n";
            exit(EXIT_SUCCESS);

        case 'r':
            // Enable tracing of registers, instructions and everything else.
            Machine::enable_trace("r");
            continue;

        case 's':
            // Enable tracing of INT syscalls, to stdout by default.
            Machine::enable_trace("s");
            continue;

        case 'p':
            // Enable tracing of IN and OUT port access.
            Machine::enable_trace("p");
            continue;

        case 'o':
            // Redirect tracing to a file.
            Machine::redirect_trace(optarg, "s");
            Machine::get_trace_stream() << "PC i86 Simulator Version: " << VERSION_STRING << "\n";
            continue;

        default:
            print_usage(std::cerr, prog_name);
            exit(EXIT_FAILURE);
        }
        break;
    }

    // Must specify a file to run.
    if (disk_file.empty()) {
        print_usage(std::cerr, prog_name);
        exit(EXIT_FAILURE);
    }

    Machine machine{ memory };
    if (verbose)
        machine.set_verbose(true);

    try {
        // Boot from disk.
        if (disk_file == "-") {
            machine.start_basic();
        } else {
            machine.boot_disk(disk_file);
        }

        // Run simulation.
        machine.run();

        // Finish the trace output.
        Machine::close_trace();

    } catch (const std::exception &ex) {
        // Print exception message.
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch (...) {
        // Assuming the exception message already printed.
        exit(EXIT_FAILURE);
    }
}
