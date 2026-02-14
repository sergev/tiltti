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
#include "sdl_scancode_map.h"
#include "video_adapter.h"

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
// Pump SDL events: keyboard -> machine queue, modifiers -> BDA, set quit on SDL_QUIT.
// Return false when no events were processed.
//
static bool pump_sdl_events(Machine &machine, bool &quit)
{
    SDL_Event event;
    unsigned count = 0;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
            return true;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            uint32_t sdl_sc = event.key.keysym.scancode;
            bool down       = (event.type == SDL_KEYDOWN);
            uint16_t mod    = SDL_GetModState();
            uint16_t f0     = 0;

            count++;
            if (mod & KMOD_RSHIFT)
                f0 |= KF0_RSHIFT;
            if (mod & KMOD_LSHIFT)
                f0 |= KF0_LSHIFT;
            if (mod & KMOD_CTRL)
                f0 |= KF0_CTRL;
            if (mod & KMOD_ALT)
                f0 |= KF0_ALT;
            const Uint8 *state = SDL_GetKeyboardState(nullptr);
            if (state[SDL_SCANCODE_SCROLLLOCK])
                f0 |= KF0_SCROLL;
            if (state[SDL_SCANCODE_NUMLOCKCLEAR])
                f0 |= KF0_NUMLOCK;
            if (state[SDL_SCANCODE_CAPSLOCK])
                f0 |= KF0_CAPSLOCK;
            machine.set_kbd_modifiers(f0);

            if (down) {
                uint8_t bios_sc  = sdl_to_bios_scancode(sdl_sc);
                uint8_t bios_ext = sdl_to_bios_scancode_extended(sdl_sc);
                uint8_t ascii    = 0;
                if (mod & KMOD_SHIFT)
                    ascii = sdl_scancode_to_ascii_shifted(sdl_sc);
                if (ascii == 0)
                    ascii = sdl_scancode_to_ascii_unshifted(sdl_sc);
                if (bios_ext) {
                    machine.push_keystroke((static_cast<uint16_t>(bios_ext) << 8) | 0x00);
                } else if (bios_sc) {
                    machine.push_keystroke((static_cast<uint16_t>(bios_sc) << 8) | ascii);
                }
            }
        }
    }
    return (count > 0);
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

    Video_Adapter video_adapter("Tiltti v" VERSION_STRING, memory.get_ptr(0xb8000));
    if (!video_adapter.has_window()) {
        throw std::runtime_error("SDL: cannot create display window");
    }

    try {
        // Boot from disk.
        if (disk_file == "-") {
            machine.start_basic();
        } else {
            machine.boot_disk(disk_file);
        }

        bool quit = false;
        machine.set_pump_callback([&machine, &quit]() {
            pump_sdl_events(machine, quit);
            return !quit;
        });

        while (!quit) {
            bool active = pump_sdl_events(machine, quit);
            if (quit)
                break;

            constexpr unsigned steps_per_frame = 5000;
            machine.run_batch(steps_per_frame);

            // Refresh SDL window from machine memory and BDA.
            VideoRefreshParams p = machine.get_video_refresh_params();
            if (p.need_refresh) {
                video_adapter.refresh_from_memory(p.text_buf, p.cursor_col, p.cursor_row, p.cursor_type);
            } else if (!active) {
                constexpr unsigned msec = 20;
                SDL_Delay(msec);
            }
        }

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
