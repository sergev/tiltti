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

#include <cmath>
#include <cstring>

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

// Snap (w,h) to nearest half-integer scale; return snapped (w,h).
static void snap_to_half_integer_scale(int w, int h, int *out_w, int *out_h)
{
    double scale_w = w / static_cast<double>(Video_Adapter::SCREEN_WIDTH);
    double scale_h = h / static_cast<double>(Video_Adapter::SCREEN_HEIGHT);
    double scale   = std::min(scale_w, scale_h); // maintain aspect
    scale          = std::max(1.0, scale);       // min 1x
    int half_steps = static_cast<int>(std::round(scale * 2));
    half_steps     = std::max(2, half_steps); // 2 half-steps = 1x
    double snapped = half_steps / 2.0;
    *out_w         = static_cast<int>(Video_Adapter::SCREEN_WIDTH * snapped);
    *out_h         = static_cast<int>(Video_Adapter::SCREEN_HEIGHT * snapped);
}

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
    init_keymap();
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
    active_   = true;
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

    if (fg == bg) {
        bg = 15 - fg;
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
            if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
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
            unsigned off   = (row * TEXT_COLS + col) * 2;
            bool changed   = (text_buf[off] != text_snapshot_[off]) ||
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
// Pump SDL events: keyboard -> machine queue, modifiers -> BDA, clear active on SDL_QUIT.
// Refresh screen.
//
void Video_Adapter::pump_events(Machine &machine, unsigned timeout)
{
    SDL_Event event;

    while (SDL_WaitEventTimeout(&event, timeout)) {
        if (event.type == SDL_QUIT) {
            active_ = false;
            return;
        }
        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                int w = event.window.data1;
                int h = event.window.data2;
                int snap_w, snap_h;
                snap_to_half_integer_scale(w, h, &snap_w, &snap_h);
                if (snap_w != w || snap_h != h) {
                    SDL_SetWindowSize(static_cast<SDL_Window *>(window_), snap_w, snap_h);
                }
            }
            if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
                event.window.event == SDL_WINDOWEVENT_EXPOSED) {
                VideoRefreshParams p = machine.get_video_refresh_params();
                refresh(p.text_buf, p.cursor_col, p.cursor_row, p.cursor_type);
            }
            continue;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            const uint16_t mod = SDL_GetModState();
            const Uint8 *state = SDL_GetKeyboardState(nullptr);

            uint16_t f0 = 0;
            if (mod & KMOD_RSHIFT)
                f0 |= KF0_RSHIFT;
            if (mod & KMOD_LSHIFT)
                f0 |= KF0_LSHIFT;
            if (mod & KMOD_CTRL)
                f0 |= KF0_CTRLACTIVE;
            if (mod & KMOD_ALT)
                f0 |= KF0_ALTACTIVE;
            if (state[SDL_SCANCODE_SCROLLLOCK])
                f0 |= KF0_SCROLLACTIVE;
            if (state[SDL_SCANCODE_NUMLOCKCLEAR])
                f0 |= KF0_NUMACTIVE;
            if (state[SDL_SCANCODE_CAPSLOCK])
                f0 |= KF0_CAPSACTIVE;
            uint8_t f1 = 0;
            if (mod & KMOD_RCTRL)
                f1 |= KF1_RCTRL;
            if (mod & KMOD_RALT)
                f1 |= KF1_RALT;
            machine.set_kbd_modifiers(f0, f1);

            if (event.type == SDL_KEYDOWN) {
                auto const &key    = keymap[event.key.keysym.scancode];
                uint16_t keystroke = 0;

                if (mod & KMOD_ALT) {
                    // Alt modifier is active
                    keystroke = key.alt;

                } else if (mod & KMOD_CTRL) {
                    // Ctrl modifier is active
                    keystroke = key.control;

                } else if ((mod & KMOD_SHIFT) ||
                           (state[SDL_SCANCODE_CAPSLOCK] &&
                            is_alphabetic(event.key.keysym.scancode)) ||
                           (state[SDL_SCANCODE_NUMLOCKCLEAR] &&
                            is_keypad(event.key.keysym.scancode))) {
                    // Shift modifier is active,
                    // or CapsLock for characters,
                    // or NumLock for keypad.
                    keystroke = key.shifted;
                } else {
                    keystroke = key.normal;
                }

                if (keystroke != 0) {
                    machine.push_keystroke(keystroke);
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

//
// Return true for keys A-Z.
//
bool Video_Adapter::is_alphabetic(unsigned scancode)
{
    switch (scancode) {
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_B:
    case SDL_SCANCODE_C:
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_E:
    case SDL_SCANCODE_F:
    case SDL_SCANCODE_G:
    case SDL_SCANCODE_H:
    case SDL_SCANCODE_I:
    case SDL_SCANCODE_J:
    case SDL_SCANCODE_K:
    case SDL_SCANCODE_L:
    case SDL_SCANCODE_M:
    case SDL_SCANCODE_N:
    case SDL_SCANCODE_O:
    case SDL_SCANCODE_P:
    case SDL_SCANCODE_Q:
    case SDL_SCANCODE_R:
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_T:
    case SDL_SCANCODE_U:
    case SDL_SCANCODE_V:
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_X:
    case SDL_SCANCODE_Y:
    case SDL_SCANCODE_Z:
        return true;
    default:
        return false;
    }
}

//
// Return true for keypad keys.
//
bool Video_Adapter::is_keypad(unsigned scancode)
{
    switch (scancode) {
    case SDL_SCANCODE_KP_0:
    case SDL_SCANCODE_KP_1:
    case SDL_SCANCODE_KP_2:
    case SDL_SCANCODE_KP_3:
    case SDL_SCANCODE_KP_4:
    case SDL_SCANCODE_KP_5:
    case SDL_SCANCODE_KP_6:
    case SDL_SCANCODE_KP_7:
    case SDL_SCANCODE_KP_8:
    case SDL_SCANCODE_KP_9:
    case SDL_SCANCODE_KP_DIVIDE:
    case SDL_SCANCODE_KP_ENTER:
    case SDL_SCANCODE_KP_MINUS:
    case SDL_SCANCODE_KP_MULTIPLY:
    case SDL_SCANCODE_KP_PERIOD:
    case SDL_SCANCODE_KP_PLUS:
        return true;
    default:
        return false;
    }
}

void Video_Adapter::init_keymap()
{
    // ---------------- Key --------------- Normal  Shifted Control Alt ----
    // clang-format off
    keymap[SDL_SCANCODE_ESCAPE]         = { 0x011B, 0x011B, 0x011B, 0      };
    keymap[SDL_SCANCODE_F1]             = { 0x3B00, 0x5400, 0x5E00, 0x6800 };
    keymap[SDL_SCANCODE_F2]             = { 0x3C00, 0x5500, 0x5F00, 0x6900 };
    keymap[SDL_SCANCODE_F3]             = { 0x3D00, 0x5600, 0x6000, 0x6A00 };
    keymap[SDL_SCANCODE_F4]             = { 0x3E00, 0x5700, 0x6100, 0x6B00 };
    keymap[SDL_SCANCODE_F5]             = { 0x3F00, 0x5800, 0x6200, 0x6C00 };
    keymap[SDL_SCANCODE_F6]             = { 0x4000, 0x5900, 0x6300, 0x6D00 };
    keymap[SDL_SCANCODE_F7]             = { 0x4100, 0x5A00, 0x6400, 0x6E00 };
    keymap[SDL_SCANCODE_F8]             = { 0x4200, 0x5B00, 0x6500, 0x6F00 };
    keymap[SDL_SCANCODE_F9]             = { 0x4300, 0x5C00, 0x6600, 0x7000 };
    keymap[SDL_SCANCODE_F10]            = { 0x4400, 0x5D00, 0x6700, 0x7100 };
    keymap[SDL_SCANCODE_F11]            = { 0x8500, 0x8700, 0x8900, 0x8B00 };
    keymap[SDL_SCANCODE_F12]            = { 0x8600, 0x8800, 0x8A00, 0x8C00 };

    keymap[SDL_SCANCODE_GRAVE]          = { 0x2960, 0x297E, 0,      0      };
    keymap[SDL_SCANCODE_1]              = { 0x0231, 0x0221, 0,      0x7800 };
    keymap[SDL_SCANCODE_2]              = { 0x0332, 0x0340, 0x0300, 0x7900 };
    keymap[SDL_SCANCODE_3]              = { 0x0433, 0x0423, 0,      0x7A00 };
    keymap[SDL_SCANCODE_4]              = { 0x0534, 0x0524, 0,      0x7B00 };
    keymap[SDL_SCANCODE_5]              = { 0x0635, 0x0625, 0,      0x7C00 };
    keymap[SDL_SCANCODE_6]              = { 0x0736, 0x075E, 0x071E, 0x7D00 };
    keymap[SDL_SCANCODE_7]              = { 0x0837, 0x0826, 0,      0x7E00 };
    keymap[SDL_SCANCODE_8]              = { 0x0938, 0x092A, 0,      0x7F00 };
    keymap[SDL_SCANCODE_9]              = { 0x0A39, 0x0A28, 0,      0x8000 };
    keymap[SDL_SCANCODE_0]              = { 0x0B30, 0x0B29, 0,      0x8100 };
    keymap[SDL_SCANCODE_MINUS]          = { 0x0C2D, 0x0C5F, 0x0C1F, 0x8200 };
    keymap[SDL_SCANCODE_EQUALS]         = { 0x0D3D, 0x0D2B, 0,      0x8300 };
    keymap[SDL_SCANCODE_BACKSPACE]      = { 0x0E08, 0x0E08, 0,      0      };

    keymap[SDL_SCANCODE_TAB]            = { 0x0F09, 0x0F00, 0,      0      };
    keymap[SDL_SCANCODE_Q]              = { 0x1071, 0x1051, 0x1011, 0x1000 };
    keymap[SDL_SCANCODE_W]              = { 0x1177, 0x1157, 0x1117, 0x1100 };
    keymap[SDL_SCANCODE_E]              = { 0x1265, 0x1245, 0x1205, 0x1200 };
    keymap[SDL_SCANCODE_R]              = { 0x1372, 0x1352, 0x1312, 0x1300 };
    keymap[SDL_SCANCODE_T]              = { 0x1474, 0x1454, 0x1414, 0x1400 };
    keymap[SDL_SCANCODE_Y]              = { 0x1579, 0x1559, 0x1519, 0x1500 };
    keymap[SDL_SCANCODE_U]              = { 0x1675, 0x1655, 0x1615, 0x1600 };
    keymap[SDL_SCANCODE_I]              = { 0x1769, 0x1749, 0x1709, 0x1700 };
    keymap[SDL_SCANCODE_O]              = { 0x186F, 0x184F, 0x180F, 0x1800 };
    keymap[SDL_SCANCODE_P]              = { 0x1970, 0x1950, 0x1910, 0x1900 };
    keymap[SDL_SCANCODE_LEFTBRACKET]    = { 0x1A5B, 0x1A7B, 0x1A1B, 0      };
    keymap[SDL_SCANCODE_RIGHTBRACKET]   = { 0x1B5D, 0x1B7D, 0x1B1D, 0      };
    keymap[SDL_SCANCODE_BACKSLASH]      = { 0x2B5C, 0x2B7C, 0x2B1C, 0      };

    keymap[SDL_SCANCODE_A]              = { 0x1E61, 0x1E41, 0x1E01, 0x1E00 };
    keymap[SDL_SCANCODE_S]              = { 0x1F73, 0x1F53, 0x1F13, 0x1F00 };
    keymap[SDL_SCANCODE_D]              = { 0x2064, 0x2044, 0x2004, 0x2000 };
    keymap[SDL_SCANCODE_F]              = { 0x2166, 0x2146, 0x2106, 0x2100 };
    keymap[SDL_SCANCODE_G]              = { 0x2267, 0x2247, 0x2207, 0x2200 };
    keymap[SDL_SCANCODE_H]              = { 0x2368, 0x2348, 0x2308, 0x2300 };
    keymap[SDL_SCANCODE_J]              = { 0x246A, 0x244A, 0x240A, 0x2400 };
    keymap[SDL_SCANCODE_K]              = { 0x256B, 0x254B, 0x250B, 0x2500 };
    keymap[SDL_SCANCODE_L]              = { 0x266C, 0x264C, 0x260C, 0x2600 };
    keymap[SDL_SCANCODE_SEMICOLON]      = { 0x273B, 0x273A, 0,      0      };
    keymap[SDL_SCANCODE_APOSTROPHE]     = { 0x2827, 0x2822, 0,      0      };
    keymap[SDL_SCANCODE_RETURN]         = { 0x1C0D, 0x1C0D, 0x1C0A, 0      };

    keymap[SDL_SCANCODE_NONUSBACKSLASH] = { 0x2B5C, 0x2B7C, 0x2B1C, 0      };
    keymap[SDL_SCANCODE_Z]              = { 0x2C7A, 0x2C5A, 0x2C1A, 0x2C00 };
    keymap[SDL_SCANCODE_X]              = { 0x2D78, 0x2D58, 0x2D18, 0x2D00 };
    keymap[SDL_SCANCODE_C]              = { 0x2E63, 0x2E43, 0x2E03, 0x2E00 };
    keymap[SDL_SCANCODE_V]              = { 0x2F76, 0x2F56, 0x2F16, 0x2F00 };
    keymap[SDL_SCANCODE_B]              = { 0x3062, 0x3042, 0x3002, 0x3000 };
    keymap[SDL_SCANCODE_N]              = { 0x316E, 0x314E, 0x310E, 0x3100 };
    keymap[SDL_SCANCODE_M]              = { 0x326D, 0x324D, 0x320D, 0x3200 };
    keymap[SDL_SCANCODE_COMMA]          = { 0x332C, 0x333C, 0,      0      };
    keymap[SDL_SCANCODE_PERIOD]         = { 0x342E, 0x343E, 0,      0      };
    keymap[SDL_SCANCODE_SLASH]          = { 0x352F, 0x353F, 0,      0      };

    keymap[SDL_SCANCODE_SPACE]          = { 0x3920, 0x3920, 0x3920, 0x3920 };

    keymap[SDL_SCANCODE_INSERT]         = { 0x5200, 0x5200, 0,      0      };
    keymap[SDL_SCANCODE_HOME]           = { 0x4700, 0x4700, 0x7700, 0      };
    keymap[SDL_SCANCODE_PAGEUP]         = { 0x4900, 0x4900, 0x8400, 0      };
    keymap[SDL_SCANCODE_DELETE]         = { 0x5300, 0x5300, 0,      0      };
    keymap[SDL_SCANCODE_END]            = { 0x4F00, 0x4F00, 0x7500, 0      };
    keymap[SDL_SCANCODE_PAGEDOWN]       = { 0x5100, 0x5100, 0x7600, 0      };

    keymap[SDL_SCANCODE_UP]             = { 0x4800, 0x4800, 0,      0      };
    keymap[SDL_SCANCODE_LEFT]           = { 0x4B00, 0x4B00, 0x7300, 0      };
    keymap[SDL_SCANCODE_DOWN]           = { 0x5000, 0x5000, 0,      0      };
    keymap[SDL_SCANCODE_RIGHT]          = { 0x4D00, 0x4D00, 0x7400, 0      };

    keymap[SDL_SCANCODE_KP_DIVIDE]      = { 0x352F, 0x352F, 0,      0      };
    keymap[SDL_SCANCODE_KP_MULTIPLY]    = { 0x372A, 0x372A, 0,      0      };
    keymap[SDL_SCANCODE_KP_MINUS]       = { 0x4A2D, 0x4A2D, 0,      0      };
    keymap[SDL_SCANCODE_KP_7]           = { 0x4700, 0x4737, 0x7700, 0      };
    keymap[SDL_SCANCODE_KP_8]           = { 0x4800, 0x4838, 0,      0      };
    keymap[SDL_SCANCODE_KP_9]           = { 0x4900, 0x4939, 0x8400, 0      };
    keymap[SDL_SCANCODE_KP_PLUS]        = { 0x4E2B, 0x4E2B, 0,      0      };
    keymap[SDL_SCANCODE_KP_4]           = { 0x4B00, 0x4B34, 0x7300, 0      };
    keymap[SDL_SCANCODE_KP_5]           = { 0,      0x4C35, 0,      0      };
    keymap[SDL_SCANCODE_KP_6]           = { 0x4D00, 0x4D36, 0x7400, 0      };
    keymap[SDL_SCANCODE_KP_1]           = { 0x4F00, 0x4F31, 0x7500, 0      };
    keymap[SDL_SCANCODE_KP_2]           = { 0x5000, 0x5032, 0,      0      };
    keymap[SDL_SCANCODE_KP_3]           = { 0x5100, 0x5133, 0x7600, 0      };
    keymap[SDL_SCANCODE_KP_ENTER]       = { 0x1C0D, 0x1C0D, 0x1C0A, 0      };
    keymap[SDL_SCANCODE_KP_0]           = { 0x5200, 0x5230, 0,      0      };
    keymap[SDL_SCANCODE_KP_PERIOD]      = { 0x5300, 0x532E, 0,      0      };
    // clang-format on
}
