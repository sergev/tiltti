//
// Map SDL2 (USB HID) scancodes to PC BIOS scancode set 1 and US ASCII.
// Copyright (c) 2026 Serge Vakulenko
//
// SDL scancodes: SDL_SCANCODE_A=4, B=5, ... Z=29, 1=30..0=39, Return=40, Escape=41, etc.
// PC BIOS set 1: A=0x1E, B=0x30, ... Escape=0x01, Enter=0x1C, etc.
//
#include "sdl_scancode_map.h"

namespace {

// SDL scancode (0..511) -> BIOS scancode set 1 (0 = unmapped).
constexpr unsigned MAP_SIZE     = 512;
uint8_t bios_scancode[MAP_SIZE] = {};

// Extended keys (E0 xx): second byte only; caller uses 0xE0 prefix for BIOS.
uint8_t bios_extended[MAP_SIZE] = {};

// Unshifted ASCII (US layout). 0 = no character.
uint8_t ascii_unshifted[MAP_SIZE] = {};

// Shifted ASCII (US layout). 0 = no character.
uint8_t ascii_shifted[MAP_SIZE] = {};

void init_tables()
{
    for (unsigned i = 0; i < MAP_SIZE; i++) {
        bios_scancode[i]   = 0;
        bios_extended[i]   = 0;
        ascii_unshifted[i] = 0;
        ascii_shifted[i]   = 0;
    }

    // Letters: SDL A=4..Z=29 -> BIOS A=0x1E, B=0x30, C=0x2E, D=0x20, E=0x12, F=0x21, G=0x22,
    // H=0x23, I=0x17, J=0x24, K=0x25, L=0x26, M=0x32, N=0x31, O=0x18, P=0x19, Q=0x10, R=0x13,
    // S=0x1F, T=0x14, U=0x16, V=0x2F, W=0x11, X=0x2D, Y=0x15, Z=0x2C
    const uint8_t letter_bios[] = { 0x1E, 0x30, 0x2E, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17,
                                    0x24, 0x25, 0x26, 0x32, 0x31, 0x18, 0x19, 0x10, 0x13,
                                    0x1F, 0x14, 0x16, 0x2F, 0x11, 0x2D, 0x15, 0x2C };
    for (int i = 0; i < 26; i++) {
        unsigned sdl         = 4 + i; // SDL_SCANCODE_A + i
        bios_scancode[sdl]   = letter_bios[i];
        ascii_unshifted[sdl] = static_cast<uint8_t>('a' + i);
        ascii_shifted[sdl]   = static_cast<uint8_t>('A' + i);
    }

    // Digits: SDL 1=30..0=39 -> BIOS 1=0x02..0=0x0B
    const uint8_t digit_bios[] = { 0x0B, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };
    const char digit_unch[]    = "0123456789";
    const char digit_shift[]   = ")!@#$%^&*(";
    for (int i = 0; i < 10; i++) {
        unsigned sdl         = 30 + i;       // SDL_SCANCODE_1 + i (1 is index 0, 0 is index 9)
        unsigned idx         = (i + 9) % 10; // SDL 30=1, 31=2, ... 39=0
        bios_scancode[sdl]   = digit_bios[idx];
        ascii_unshifted[sdl] = static_cast<uint8_t>(digit_unch[idx]);
        ascii_shifted[sdl]   = static_cast<uint8_t>(digit_shift[idx]);
    }

    // Return=40 -> 0x1C, Escape=41 -> 0x01, Backspace=42 -> 0x0E, Tab=43 -> 0x0F, Space=44 -> 0x39
    bios_scancode[40]   = 0x1C;
    ascii_unshifted[40] = '\r';
    bios_scancode[41]   = 0x01;
    ascii_unshifted[41] = 0x1B; // ESC
    bios_scancode[42]   = 0x0E;
    ascii_unshifted[42] = 0x08; // BS
    bios_scancode[43]   = 0x0F;
    ascii_unshifted[43] = '\t';
    bios_scancode[44]   = 0x39;
    ascii_unshifted[44] = ' ';

    // Minus=45, Equals=46, LeftBracket=47, RightBracket=48, Backslash=49, Semicolon=51,
    // Apostrophe=52, Grave=53, Comma=54, Period=55, Slash=56
    bios_scancode[45]   = 0x0C;
    ascii_unshifted[45] = '-';
    ascii_shifted[45]   = '_';
    bios_scancode[46]   = 0x0D;
    ascii_unshifted[46] = '=';
    ascii_shifted[46]   = '+';
    bios_scancode[47]   = 0x1A;
    ascii_unshifted[47] = '[';
    ascii_shifted[47]   = '{';
    bios_scancode[48]   = 0x1B;
    ascii_unshifted[48] = ']';
    ascii_shifted[48]   = '}';
    bios_scancode[49]   = 0x2B;
    ascii_unshifted[49] = '\\';
    ascii_shifted[49]   = '|';
    bios_scancode[51]   = 0x27;
    ascii_unshifted[51] = ';';
    ascii_shifted[51]   = ':';
    bios_scancode[52]   = 0x28;
    ascii_unshifted[52] = '\'';
    ascii_shifted[52]   = '"';
    bios_scancode[53]   = 0x29;
    ascii_unshifted[53] = '`';
    ascii_shifted[53]   = '~';
    bios_scancode[54]   = 0x33;
    ascii_unshifted[54] = ',';
    ascii_shifted[54]   = '<';
    bios_scancode[55]   = 0x34;
    ascii_unshifted[55] = '.';
    ascii_shifted[55]   = '>';
    bios_scancode[56]   = 0x35;
    ascii_unshifted[56] = '/';
    ascii_shifted[56]   = '?';

    // CapsLock=57, F1..F12=58..69
    bios_scancode[57] = 0x3A;
    for (int i = 0; i < 12; i++) {
        bios_scancode[58 + i] = static_cast<uint8_t>(0x3B + i);
        // F-keys: ASCII 0 for normal; some BIOS use 0x00, 0x3B+ for scan
    }

    // PrintScreen=70, ScrollLock=71, Pause=72, Insert=73, Home=74, PageUp=75, Delete=76, End=77,
    // PageDown=78, Right=79, Left=80, Down=81, Up=82 These are E0 extended in BIOS. Store second
    // byte in bios_extended.
    bios_extended[73] = 0x52; // Insert
    bios_extended[74] = 0x47; // Home
    bios_extended[75] = 0x49; // PageUp
    bios_extended[76] = 0x53; // Delete
    bios_extended[77] = 0x4F; // End
    bios_extended[78] = 0x51; // PageDown
    bios_extended[79] = 0x4D; // Right
    bios_extended[80] = 0x4B; // Left
    bios_extended[81] = 0x50; // Down
    bios_extended[82] = 0x48; // Up

    // NumLock=83, KP_Divide=84..KP_Period=99 - numpad with E0 prefix
    bios_scancode[83] = 0x45; // NumLock
    bios_extended[84] = 0x35; // KP_Divide
    bios_extended[85] = 0x37; // KP_Multiply
    bios_extended[86] = 0x4A; // KP_Minus
    bios_extended[87] = 0x4E; // KP_Plus
    bios_extended[88] = 0x1C; // KP_Enter (E0 1C)
    bios_extended[89] = 0x4F; // KP_1 End
    bios_extended[90] = 0x50; // KP_2 Down
    bios_extended[91] = 0x51; // KP_3 PageDn
    bios_extended[92] = 0x4B; // KP_4 Left
    bios_extended[93] = 0x4C; // KP_5
    bios_extended[94] = 0x4D; // KP_6 Right
    bios_extended[95] = 0x47; // KP_7 Home
    bios_extended[96] = 0x48; // KP_8 Up
    bios_extended[97] = 0x49; // KP_9 PageUp
    bios_extended[98] = 0x52; // KP_0 Insert
    bios_extended[99] = 0x53; // KP_Period Delete

    // Modifiers: LCtrl=224, LShift=225, LAlt=226, RCtrl=228, RShift=229, RAlt=230
    bios_scancode[224] = 0x1D; // LCtrl
    bios_scancode[225] = 0x2A; // LShift
    bios_scancode[226] = 0x38; // LAlt
    bios_extended[228] = 0x1D; // RCtrl (E0 1D)
    bios_extended[229] = 0x36; // RShift
    bios_extended[230] = 0x38; // RAlt (E0 38)
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
    return bios_scancode[sdl_scancode];
}

uint8_t sdl_to_bios_scancode_extended(uint32_t sdl_scancode)
{
    if (!tables_initialized) {
        init_tables();
        tables_initialized = true;
    }
    if (sdl_scancode >= MAP_SIZE)
        return 0;
    return bios_extended[sdl_scancode];
}

uint8_t sdl_scancode_to_ascii_unshifted(uint32_t sdl_scancode)
{
    if (!tables_initialized) {
        init_tables();
        tables_initialized = true;
    }
    if (sdl_scancode >= MAP_SIZE)
        return 0;
    return ascii_unshifted[sdl_scancode];
}

uint8_t sdl_scancode_to_ascii_shifted(uint32_t sdl_scancode)
{
    if (!tables_initialized) {
        init_tables();
        tables_initialized = true;
    }
    if (sdl_scancode >= MAP_SIZE)
        return 0;
    return ascii_shifted[sdl_scancode];
}
