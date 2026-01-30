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
    { "trace",          required_argument,  nullptr,    'T' },
    { "debug",          required_argument,  nullptr,    'd' },
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
    out << "    -h, --help              Display available options" << std::endl;
    out << "    -V, --version           Print the version number and exit" << std::endl;
    out << "    -v, --verbose           Verbose mode" << std::endl;
    out << "    --trace=FILE            Redirect trace to the file" << std::endl;
    out << "    -d MODE, --debug=MODE   Select debug mode, default irm" << std::endl;
    out << "Debug modes:" << std::endl;
    out << "    i       Trace instructions" << std::endl;
    out << "    e       Trace INT calls" << std::endl;
    out << "    f       Trace fetch" << std::endl;
    out << "    r       Trace registers" << std::endl;
    out << "    m       Trace memory read/write" << std::endl;
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

    // Instantiate the machine.
    Memory memory;
    Machine machine{ memory };

    // A name of disk file.
    std::string disk_file;

    // Parse command line options.
    for (;;) {
        switch (getopt_long(argc, argv, "-hVvl:tT:d:rs", long_options, nullptr)) {
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
            // Verbose.
            machine.set_verbose(true);
            continue;

        case 'V':
            // Show version and exit.
            std::cout << "Version " << VERSION_STRING << "\n";
            exit(EXIT_SUCCESS);

        case 't':
            // Enable tracing of INT calls, to stdout by default.
            Machine::enable_trace("e");
            continue;

        case 'T':
            // Redirect tracing to a file.
            Machine::redirect_trace(optarg, "irm");
            Machine::get_trace_stream() << "PC i86 Simulator Version: " << VERSION_STRING << "\n";
            continue;

        case 'd':
            // Set trace options.
            if (optarg && *optarg) {
                Machine::enable_trace(optarg);
            } else {
                Machine::close_trace();
            }
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

    try {
        // Boot from disk.
        machine.boot_disk(disk_file);

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
