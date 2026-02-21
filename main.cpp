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
#include <SDL.h>
#include <getopt.h>

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "machine.h"
#include "pc86_arch.h"
#include "video_adapter.h"

//
// CLI options.
//
static const struct option long_options[] = {
    // clang-format off
    { "help",           no_argument,        nullptr,    'h' },
    { "version",        no_argument,        nullptr,    'V' },
    { "output",         required_argument,  nullptr,    'o' },
    { "regs",           required_argument,  nullptr,    'r' },
    { "ports",          required_argument,  nullptr,    'p' },
    { "syscalls",       required_argument,  nullptr,    's' },
    { "boot",           required_argument,  nullptr,    'B' },
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
    out << "    " << prog_name << " [options...] [disk_a.img]" << std::endl;
    out << "Disks (any may be omitted; at least one disk or positional required):" << std::endl;
    out << "    -a FILE                 Floppy drive A: image" << std::endl;
    out << "    -b FILE                 Floppy drive B: image" << std::endl;
    out << "    -c FILE                 Hard disk C: image" << std::endl;
    out << "    -d FILE                 Hard disk D: image" << std::endl;
    out << "    disk_a.img              Optional positional argument = drive A: (same as -a)"
        << std::endl;
    out << "Options:" << std::endl;
    out << "    --boot=a|b|c|d          Boot from specified drive (default: C if present, else A, else B)"
        << std::endl;
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

    std::string disk_file;
    std::string disk_file_b;
    std::string disk_file_c;
    std::string disk_file_d;
    std::string boot_drive;

    // Parse command line options.
    for (;;) {
        switch (getopt_long(argc, argv, "-hVrspo:a:b:c:d:B:", long_options, nullptr)) {
        case EOF:
            break;

        case 0:
            continue;

        case 1:
            // Single optional positional argument = drive A: (same as -a).
            if (!disk_file.empty()) {
                std::cerr << "Only one positional argument allowed: " << optarg << std::endl;
                print_usage(std::cerr, prog_name);
                ::exit(EXIT_FAILURE);
            }
            disk_file = optarg;
            continue;

        case 'a':
            disk_file = optarg;
            continue;

        case 'b':
            disk_file_b = optarg;
            continue;

        case 'c':
            disk_file_c = optarg;
            continue;

        case 'd':
            disk_file_d = optarg;
            continue;

        case 'B': {
            std::string v = optarg;
            if (v.size() != 1 || (v[0] != 'a' && v[0] != 'b' && v[0] != 'c' && v[0] != 'd')) {
                std::cerr << "Invalid --boot drive: " << optarg << " (use a, b, c, or d)"
                          << std::endl;
                print_usage(std::cerr, prog_name);
                ::exit(EXIT_FAILURE);
            }
            boot_drive = v;
            continue;
        }

        case 'h':
            // Show usage message and exit.
            print_usage(std::cout, prog_name);
            exit(EXIT_SUCCESS);

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

    // When no disks given at all (no positional, no -a/-b/-c/-d), show usage.
    const bool has_any_disk =
        !disk_file.empty() || !disk_file_b.empty() || !disk_file_c.empty() || !disk_file_d.empty();
    if (!has_any_disk) {
        print_usage(std::cerr, prog_name);
        exit(EXIT_FAILURE);
    }

    // Create RAM.
    Memory memory;

    // Create video adapter, using SDL.
    Video_Adapter gui{ "Tiltti v" VERSION_STRING, memory.get_ptr(0xb8000) };
    if (!gui.has_window()) {
        std::cerr << "Cannot create VGA window\n";
        exit(EXIT_FAILURE);
    }

    // Create PC i86 machine.
    Machine machine{ memory };

    // Connect machine to video adapter.
    auto event_callback = [&gui, &machine](unsigned timeout) {
        gui.pump_events(machine, timeout);
        if (!gui.active()) {
            // Window closed.
            std::exit(0);
        }
    };
    machine.set_event_callback(event_callback);
    machine.set_font_buffer(gui.font_buffer(), gui.font_buffer_size());

    try {
        machine.boot_disk(disk_file, disk_file_b, disk_file_c, disk_file_d, boot_drive);

        while (gui.active()) {
            constexpr unsigned steps_per_frame = 50000;

            machine.update_timer_counter();
            machine.run_batch(steps_per_frame);
            gui.pump_events(machine, 10);
        }

    } catch (const std::exception &ex) {
        // Print exception message.
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch (...) {
        // Assuming the exception message already printed.
        exit(EXIT_FAILURE);
    }
}
