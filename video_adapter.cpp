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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "video_adapter.h"

#include <SDL.h>

#include <cstring>

#include "sdl_scancode_map.h"
#include "vga_font_9x16.h"

namespace {

// EGA/VGA 16-color palette (RGB, 0-255).
constexpr unsigned PALETTE[16][3] = {
    { 0, 0, 0 },       // 0 black
    { 0, 0, 170 },     // 1 blue
    { 0, 170, 0 },     // 2 green
    { 0, 170, 170 },   // 3 cyan
    { 170, 0, 0 },     // 4 red
    { 170, 0, 170 },   // 5 magenta
    { 170, 85, 0 },    // 6 brown
    { 170, 170, 170 }, // 7 light gray
    { 85, 85, 85 },    // 8 dark gray
    { 85, 85, 255 },   // 9 bright blue
    { 85, 255, 85 },   // 10 bright green
    { 85, 255, 255 },  // 11 bright cyan
    { 255, 85, 85 },   // 12 bright red
    { 255, 85, 255 },  // 13 bright magenta
    { 255, 255, 85 },  // 14 bright yellow
    { 255, 255, 255 }  // 15 white
};

} // namespace

//
// Construct the adapter; optionally create an SDL window for display.
// When text_buffer != nullptr, read from it (e.g. memory at 0xb8000); else use internal buffer.
//
Video_Adapter::Video_Adapter(const char *title, uint8_t *text_buffer)
    : text_buf_ptr_(text_buffer ? text_buffer : text_buf_.data())
{
    font_buf_.fill(0);
    init_font();
    if (!text_buffer) {
        text_buf_.fill(0);
        text_snapshot_.fill(0);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return;

    SDL_Window *win =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                         SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if (!win) {
        SDL_Quit();
        return;
    }

    SDL_Renderer *ren =
        SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                         SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!tex) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    window_   = win;
    renderer_ = ren;
    texture_  = tex;
}

//
// Destroy the adapter and release SDL resources if a window was created.
//
Video_Adapter::~Video_Adapter()
{
    if (window_) {
        SDL_DestroyTexture(static_cast<SDL_Texture *>(texture_));
        SDL_DestroyRenderer(static_cast<SDL_Renderer *>(renderer_));
        SDL_DestroyWindow(static_cast<SDL_Window *>(window_));
        SDL_Quit();
        window_   = nullptr;
        renderer_ = nullptr;
        texture_  = nullptr;
    }
}

//
// Copy the embedded 9x16 font from the header into the font buffer.
//
void Video_Adapter::init_font()
{
    for (unsigned c = 0; c < 256; c++) {
        for (unsigned row = 0; row < 16; row++) {
            uint16_t val       = vga_font_9x16[c][row];
            unsigned off       = c * 32 + row * 2;
            font_buf_[off]     = val;
            font_buf_[off + 1] = val >> 8;
        }
    }
}

//
// Render one text cell (9x16 pixels) into the framebuffer.
// Optionally draw a block cursor by inverting the cell.
//
void Video_Adapter::draw_cell(const uint8_t *text_buf, unsigned col, unsigned row,
                              bool is_cursor_cell)
{
    unsigned cell_off = (row * TEXT_COLS + col) * 2;
    uint8_t ch        = text_buf[cell_off];
    uint8_t attr      = text_buf[cell_off + 1];
    unsigned fg       = attr & 0x0f;
    unsigned bg       = (attr >> 4) & 0x0f;

    unsigned font_off = ch * 32;
    unsigned px       = col * GLYPH_WIDTH;
    unsigned py       = row * GLYPH_HEIGHT;

    if (is_cursor_cell && fg == bg) {
        fg = 15;
        bg = 0;
    }

    for (unsigned dy = 0; dy < GLYPH_HEIGHT; dy++) {
        uint16_t row_bits;
        row_bits = font_buf_[font_off + dy * 2] | (font_buf_[font_off + dy * 2 + 1] << 8);
        row_bits &= 0x1ff;

        for (unsigned dx = 0; dx < GLYPH_WIDTH; dx++) {
            bool set = (row_bits >> (8 - dx)) & 1;
            if (is_cursor_cell)
                set = !set;
            unsigned color_idx = set ? fg : bg;
            unsigned r         = PALETTE[color_idx][0];
            unsigned g         = PALETTE[color_idx][1];
            unsigned b         = PALETTE[color_idx][2];

            unsigned x = px + dx;
            unsigned y = py + dy;
            if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
                unsigned fb_off          = (y * SCREEN_WIDTH + x) * 4;
                framebuffer_[fb_off]     = b;
                framebuffer_[fb_off + 1] = g;
                framebuffer_[fb_off + 2] = r;
                framebuffer_[fb_off + 3] = 255;
            }
        }
    }
}

//
// Update the SDL texture from the framebuffer and present to the window.
//
void Video_Adapter::present()
{
    SDL_UpdateTexture(static_cast<SDL_Texture *>(texture_), nullptr, framebuffer_.data(),
                      SCREEN_WIDTH * 4);

    int w, h;
    SDL_GetWindowSize(static_cast<SDL_Window *>(window_), &w, &h);
    int want_w = w;
    int want_h = w * 400 / 720;
    if (want_h > h) {
        want_h = h;
        want_w = h * 720 / 400;
    }
    int dst_x    = (w - want_w) / 2;
    int dst_y    = (h - want_h) / 2;
    SDL_Rect dst = { dst_x, dst_y, want_w, want_h };
    SDL_RenderClear(static_cast<SDL_Renderer *>(renderer_));
    SDL_RenderCopy(static_cast<SDL_Renderer *>(renderer_), static_cast<SDL_Texture *>(texture_),
                   nullptr, &dst);
    SDL_RenderPresent(static_cast<SDL_Renderer *>(renderer_));
}

//
// Refresh reading from external buffer (e.g. memory at 0xb8000 + page_offset).
// cursor_type == 0 means hide cursor.
//
void Video_Adapter::refresh(const uint8_t *text_buf, unsigned cursor_col, unsigned cursor_row,
                            uint16_t cursor_type)
{
    if (cursor_visible_) {
        // Clear previous cursor.
        draw_cell(text_buf, cursor_col_, cursor_row_, false);
        cursor_visible_ = false;
    }

    for (unsigned row = 0; row < TEXT_ROWS; row++) {
        for (unsigned col = 0; col < TEXT_COLS; col++) {
            unsigned off = (row * TEXT_COLS + col) * 2;
            bool changed = (text_buf[off] != text_snapshot_[off]) ||
                           (text_buf[off + 1] != text_snapshot_[off + 1]);
            bool is_cursor = (cursor_type > 0) && (col == cursor_col) && (row == cursor_row);

            if (changed || is_cursor) {
                draw_cell(text_buf, col, row, is_cursor);
                if (is_cursor) {
                    cursor_visible_ = true;
                    cursor_row_     = row;
                    cursor_col_     = col;
                }
            }
        }
    }

    std::memcpy(text_snapshot_.data(), text_buf, TEXT_BUFFER_SIZE);
    present();
}

#include "machine.h"

//
// Pump SDL events: keyboard -> machine queue, modifiers -> BDA, set quit on SDL_QUIT.
// Refresh screen.
//
void Video_Adapter::pump_events(Machine &machine, bool &quit)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
            return;
        }
        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
                event.window.event == SDL_WINDOWEVENT_EXPOSED) {
                VideoRefreshParams p = machine.get_video_refresh_params();
                refresh(p.text_buf, p.cursor_col, p.cursor_row, p.cursor_type);
            }
            continue;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            uint32_t sdl_sc = event.key.keysym.scancode;
            bool down       = (event.type == SDL_KEYDOWN);
            uint16_t mod    = SDL_GetModState();
            uint16_t f0     = 0;

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

    //
    // Refresh screen every 10 msec.
    //
    uint64_t msec = SDL_GetTicks();
    static uint64_t last_refresh;
    if (msec > last_refresh + 10) {
        // Refresh SDL window from machine memory and BDA.
        VideoRefreshParams p = machine.get_video_refresh_params();
        if (p.need_refresh) {
            refresh(p.text_buf, p.cursor_col, p.cursor_row, p.cursor_type);
        }
    }
    last_refresh = msec;
}
