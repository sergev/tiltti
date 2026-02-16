//
// Map SDL2 (USB HID) scancodes to PC BIOS scancode set 1 and US ASCII.
// Copyright (c) 2026 Serge Vakulenko
//
// SDL scancodes: SDL_SCANCODE_A=4, B=5, ... Z=29, 1=30..0=39, Return=40, Escape=41, etc.
// PC BIOS set 1: A=0x1E, B=0x30, ... Escape=0x01, Enter=0x1C, etc.
//
#include "sdl_scancode_map.h"

#include <SDL.h>

namespace {

// SDL scancode (0..511) -> BIOS scancode set 1 and US ASCII.
constexpr unsigned MAP_SIZE = 512;

struct Scancode_Map {
    uint8_t bios_scancode;
    uint8_t bios_extended;
    uint8_t ascii_unshifted;
    uint8_t ascii_shifted;
};

Scancode_Map keymap[MAP_SIZE] = {};

void init_tables()
{
    // Letters: A..Z
    keymap[SDL_SCANCODE_A] = { 0x1E, 0, 'a', 'A' };
    keymap[SDL_SCANCODE_B] = { 0x30, 0, 'b', 'B' };
    keymap[SDL_SCANCODE_C] = { 0x2E, 0, 'c', 'C' };
    keymap[SDL_SCANCODE_D] = { 0x20, 0, 'd', 'D' };
    keymap[SDL_SCANCODE_E] = { 0x12, 0, 'e', 'E' };
    keymap[SDL_SCANCODE_F] = { 0x21, 0, 'f', 'F' };
    keymap[SDL_SCANCODE_G] = { 0x22, 0, 'g', 'G' };
    keymap[SDL_SCANCODE_H] = { 0x23, 0, 'h', 'H' };
    keymap[SDL_SCANCODE_I] = { 0x17, 0, 'i', 'I' };
    keymap[SDL_SCANCODE_J] = { 0x24, 0, 'j', 'J' };
    keymap[SDL_SCANCODE_K] = { 0x25, 0, 'k', 'K' };
    keymap[SDL_SCANCODE_L] = { 0x26, 0, 'l', 'L' };
    keymap[SDL_SCANCODE_M] = { 0x32, 0, 'm', 'M' };
    keymap[SDL_SCANCODE_N] = { 0x31, 0, 'n', 'N' };
    keymap[SDL_SCANCODE_O] = { 0x18, 0, 'o', 'O' };
    keymap[SDL_SCANCODE_P] = { 0x19, 0, 'p', 'P' };
    keymap[SDL_SCANCODE_Q] = { 0x10, 0, 'q', 'Q' };
    keymap[SDL_SCANCODE_R] = { 0x13, 0, 'r', 'R' };
    keymap[SDL_SCANCODE_S] = { 0x1F, 0, 's', 'S' };
    keymap[SDL_SCANCODE_T] = { 0x14, 0, 't', 'T' };
    keymap[SDL_SCANCODE_U] = { 0x16, 0, 'u', 'U' };
    keymap[SDL_SCANCODE_V] = { 0x2F, 0, 'v', 'V' };
    keymap[SDL_SCANCODE_W] = { 0x11, 0, 'w', 'W' };
    keymap[SDL_SCANCODE_X] = { 0x2D, 0, 'x', 'X' };
    keymap[SDL_SCANCODE_Y] = { 0x15, 0, 'y', 'Y' };
    keymap[SDL_SCANCODE_Z] = { 0x2C, 0, 'z', 'Z' };

    // Digits:  1..0
    keymap[SDL_SCANCODE_1] = { 0x02, 0, '1', '!' };
    keymap[SDL_SCANCODE_2] = { 0x03, 0, '2', '@' };
    keymap[SDL_SCANCODE_3] = { 0x04, 0, '3', '#' };
    keymap[SDL_SCANCODE_4] = { 0x05, 0, '4', '$' };
    keymap[SDL_SCANCODE_5] = { 0x06, 0, '5', '%' };
    keymap[SDL_SCANCODE_6] = { 0x07, 0, '6', '^' };
    keymap[SDL_SCANCODE_7] = { 0x08, 0, '7', '&' };
    keymap[SDL_SCANCODE_8] = { 0x09, 0, '8', '*' };
    keymap[SDL_SCANCODE_9] = { 0x0A, 0, '9', '(' };
    keymap[SDL_SCANCODE_0] = { 0x0B, 0, '0', ')' };

    // Return, Escape, Backspace, Tab, Space
    keymap[SDL_SCANCODE_RETURN]    = { 0x1C, 0, '\r', 0 };
    keymap[SDL_SCANCODE_ESCAPE]    = { 0x01, 0, 0x1B, 0 };
    keymap[SDL_SCANCODE_BACKSPACE] = { 0x0E, 0, 0x08, 0 };
    keymap[SDL_SCANCODE_TAB]       = { 0x0F, 0, '\t', 0 };
    keymap[SDL_SCANCODE_SPACE]     = { 0x39, 0, ' ', 0 };

    // Punctuation
    keymap[SDL_SCANCODE_MINUS]          = { 0x0C, 0, '-', '_' };
    keymap[SDL_SCANCODE_EQUALS]         = { 0x0D, 0, '=', '+' };
    keymap[SDL_SCANCODE_LEFTBRACKET]    = { 0x1A, 0, '[', '{' };
    keymap[SDL_SCANCODE_RIGHTBRACKET]   = { 0x1B, 0, ']', '}' };
    keymap[SDL_SCANCODE_BACKSLASH]      = { 0x2B, 0, '\\', '|' };
    keymap[SDL_SCANCODE_SEMICOLON]      = { 0x27, 0, ';', ':' };
    keymap[SDL_SCANCODE_APOSTROPHE]     = { 0x28, 0, '\'', '"' };
    keymap[SDL_SCANCODE_GRAVE]          = { 0x29, 0, '`', '~' };
    keymap[SDL_SCANCODE_COMMA]          = { 0x33, 0, ',', '<' };
    keymap[SDL_SCANCODE_PERIOD]         = { 0x34, 0, '.', '>' };
    keymap[SDL_SCANCODE_SLASH]          = { 0x35, 0, '/', '?' };
    keymap[SDL_SCANCODE_NONUSBACKSLASH] = { 0x56, 0, '\\', '|' };

    // CapsLock, F1..F12
    keymap[SDL_SCANCODE_CAPSLOCK] = { 0x3A, 0, 0, 0 };
    keymap[SDL_SCANCODE_F1]       = { 0x3B, 0, 0, 0 };
    keymap[SDL_SCANCODE_F2]       = { 0x3C, 0, 0, 0 };
    keymap[SDL_SCANCODE_F3]       = { 0x3D, 0, 0, 0 };
    keymap[SDL_SCANCODE_F4]       = { 0x3E, 0, 0, 0 };
    keymap[SDL_SCANCODE_F5]       = { 0x3F, 0, 0, 0 };
    keymap[SDL_SCANCODE_F6]       = { 0x40, 0, 0, 0 };
    keymap[SDL_SCANCODE_F7]       = { 0x41, 0, 0, 0 };
    keymap[SDL_SCANCODE_F8]       = { 0x42, 0, 0, 0 };
    keymap[SDL_SCANCODE_F9]       = { 0x43, 0, 0, 0 };
    keymap[SDL_SCANCODE_F10]      = { 0x44, 0, 0, 0 };
    keymap[SDL_SCANCODE_F11]      = { 0x45, 0, 0, 0 };
    keymap[SDL_SCANCODE_F12]      = { 0x46, 0, 0, 0 };

    // Extended keys (E0 xx): Insert, Home, PageUp, Delete, End, PageDown
    keymap[SDL_SCANCODE_INSERT]   = { 0, 0x52, 0, 0 };
    keymap[SDL_SCANCODE_HOME]     = { 0, 0x47, 0, 0 };
    keymap[SDL_SCANCODE_PAGEUP]   = { 0, 0x49, 0, 0 };
    keymap[SDL_SCANCODE_DELETE]   = { 0, 0x53, 0, 0 };
    keymap[SDL_SCANCODE_END]      = { 0, 0x4F, 0, 0 };
    keymap[SDL_SCANCODE_PAGEDOWN] = { 0, 0x51, 0, 0 };

    // Arrow keys (E0 xx)
    keymap[SDL_SCANCODE_RIGHT] = { 0, 0x4D, 0, 0 };
    keymap[SDL_SCANCODE_LEFT]  = { 0, 0x4B, 0, 0 };
    keymap[SDL_SCANCODE_DOWN]  = { 0, 0x50, 0, 0 };
    keymap[SDL_SCANCODE_UP]    = { 0, 0x48, 0, 0 };

    // NumLock, numpad with E0 prefix
    keymap[SDL_SCANCODE_NUMLOCKCLEAR] = { 0x45, 0, 0, 0 };
    keymap[SDL_SCANCODE_KP_DIVIDE]    = { 0, 0x35, 0, 0 };
    keymap[SDL_SCANCODE_KP_MULTIPLY]  = { 0, 0x37, 0, 0 };
    keymap[SDL_SCANCODE_KP_MINUS]     = { 0, 0x4A, 0, 0 };
    keymap[SDL_SCANCODE_KP_PLUS]      = { 0, 0x4E, 0, 0 };
    keymap[SDL_SCANCODE_KP_ENTER]     = { 0, 0x1C, 0, 0 };
    keymap[SDL_SCANCODE_KP_1]         = { 0, 0x4F, 0, 0 };
    keymap[SDL_SCANCODE_KP_2]         = { 0, 0x50, 0, 0 };
    keymap[SDL_SCANCODE_KP_3]         = { 0, 0x51, 0, 0 };
    keymap[SDL_SCANCODE_KP_4]         = { 0, 0x4B, 0, 0 };
    keymap[SDL_SCANCODE_KP_5]         = { 0, 0x4C, 0, 0 };
    keymap[SDL_SCANCODE_KP_6]         = { 0, 0x4D, 0, 0 };
    keymap[SDL_SCANCODE_KP_7]         = { 0, 0x47, 0, 0 };
    keymap[SDL_SCANCODE_KP_8]         = { 0, 0x48, 0, 0 };
    keymap[SDL_SCANCODE_KP_9]         = { 0, 0x49, 0, 0 };
    keymap[SDL_SCANCODE_KP_0]         = { 0, 0x52, 0, 0 };
    keymap[SDL_SCANCODE_KP_PERIOD]    = { 0, 0x53, 0, 0 };

    // Modifiers
    keymap[SDL_SCANCODE_LCTRL]  = { 0x1D, 0, 0, 0 };
    keymap[SDL_SCANCODE_LSHIFT] = { 0x2A, 0, 0, 0 };
    keymap[SDL_SCANCODE_LALT]   = { 0x38, 0, 0, 0 };
    keymap[SDL_SCANCODE_RCTRL]  = { 0, 0x1D, 0, 0 };
    keymap[SDL_SCANCODE_RSHIFT] = { 0, 0x36, 0, 0 };
    keymap[SDL_SCANCODE_RALT]   = { 0, 0x38, 0, 0 };
}

bool tables_initialized = false;

} // namespace

uint8_t sdl_to_bios_scancode(uint32_t sdl_scancode)
{
    if (!tables_initialized) {
        init_tables();
        tables_initialized = true;
    }
    if (sdl_scancode >= MAP_SIZE)
        return 0;
    return keymap[sdl_scancode].bios_scancode;
}

uint8_t sdl_to_bios_scancode_extended(uint32_t sdl_scancode)
{
    if (!tables_initialized) {
        init_tables();
        tables_initialized = true;
    }
    if (sdl_scancode >= MAP_SIZE)
        return 0;
    return keymap[sdl_scancode].bios_extended;
}

uint8_t sdl_scancode_to_ascii_unshifted(uint32_t sdl_scancode)
{
    if (!tables_initialized) {
        init_tables();
        tables_initialized = true;
    }
    if (sdl_scancode >= MAP_SIZE)
        return 0;
    return keymap[sdl_scancode].ascii_unshifted;
}

uint8_t sdl_scancode_to_ascii_shifted(uint32_t sdl_scancode)
{
    if (!tables_initialized) {
        init_tables();
        tables_initialized = true;
    }
    if (sdl_scancode >= MAP_SIZE)
        return 0;
    return keymap[sdl_scancode].ascii_shifted;
}
