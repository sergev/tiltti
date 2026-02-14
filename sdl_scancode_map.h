//
// Map SDL2 (USB HID) scancodes to PC BIOS scancode set 1 and US ASCII.
// Copyright (c) 2026 Serge Vakulenko
//
#ifndef SDL_SCANCODE_MAP_H
#define SDL_SCANCODE_MAP_H

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

// SDL2 uses USB HID usage page 0x07; we map to PC AT scancode set 1.
// Return 0 if unmapped.
uint8_t sdl_to_bios_scancode(uint32_t sdl_scancode);

// Extended key: second byte only (e.g. cursor 0x48); high byte 0xE0 for BIOS.
// Returns 0 for non-extended keys.
uint8_t sdl_to_bios_scancode_extended(uint32_t sdl_scancode);

// US layout: ASCII for key (unshifted). Returns 0 if no character.
uint8_t sdl_scancode_to_ascii_unshifted(uint32_t sdl_scancode);

// US layout: ASCII for key (shifted). Returns 0 if no character.
uint8_t sdl_scancode_to_ascii_shifted(uint32_t sdl_scancode);

#ifdef __cplusplus
}
#endif

#endif /* SDL_SCANCODE_MAP_H */
