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
#ifndef VIDEO_ADAPTER_H
#define VIDEO_ADAPTER_H

#include <array>
#include <cstddef>
#include <cstdint>

//
// VGA color text mode: 80x25, glyph 9x16, display 720x400.
// Text buffer: 4000 bytes (VGA 0xB8000 layout).
// Font buffer: 8192 bytes (0xA0000-style).
//
class Video_Adapter {
public:
    static constexpr unsigned TEXT_COLS        = 80;
    static constexpr unsigned TEXT_ROWS        = 25;
    static constexpr unsigned GLYPH_WIDTH      = 9;
    static constexpr unsigned GLYPH_HEIGHT     = 16;
    static constexpr unsigned SCREEN_WIDTH     = 720; // 80 * 9
    static constexpr unsigned SCREEN_HEIGHT    = 400; // 25 * 16
    static constexpr unsigned TEXT_BUFFER_SIZE = TEXT_COLS * TEXT_ROWS * 2;
    static constexpr unsigned FONT_BUFFER_SIZE = 256 * 16 * 2;

    // Create adapter. When text_buffer != nullptr, read from it (e.g. memory at 0xb8000).
    explicit Video_Adapter(const char *title, uint8_t *text_buffer = nullptr);
    ~Video_Adapter();

    Video_Adapter(const Video_Adapter &)            = delete;
    Video_Adapter &operator=(const Video_Adapter &) = delete;

    uint8_t *text_buffer() { return text_buf_ptr_; }
    const uint8_t *text_buffer() const { return text_buf_ptr_; }
    size_t text_buffer_size() const { return TEXT_BUFFER_SIZE; }

    uint8_t *font_buffer() { return font_buf_.data(); }
    const uint8_t *font_buffer() const { return font_buf_.data(); }
    size_t font_buffer_size() const { return font_buf_.size(); }

    // Refresh reading from given buffer and BDA-style cursor/page state.
    // text_buf points to the active page (e.g. 0xb8000 + page_offset).
    void refresh(const uint8_t *text_buf, unsigned cursor_col, unsigned cursor_row,
                 uint16_t cursor_type);

    void putchar(uint8_t ch, uint8_t attr);
    void puts(const char *s, uint8_t attr);

    void set_cursor(unsigned col, unsigned row);
    void get_cursor(unsigned &col, unsigned &row) const;

    bool has_window() const { return window_ != nullptr; }

private:
    std::array<uint8_t, TEXT_BUFFER_SIZE> text_buf_{};
    uint8_t *text_buf_ptr_; // points to text_buf_.data() or external buffer
    std::array<uint8_t, FONT_BUFFER_SIZE> font_buf_{};
    std::array<uint8_t, TEXT_BUFFER_SIZE> text_snapshot_{};

    void *window_   = nullptr;
    void *renderer_ = nullptr;
    void *texture_  = nullptr;
    std::array<uint8_t, SCREEN_WIDTH * SCREEN_HEIGHT * 4> framebuffer_{};

    // Cursor located at this position.
    unsigned cursor_col_ = 0;
    unsigned cursor_row_ = 0;
    bool cursor_visible_ = false;

    void init_font();
    void draw_cell(const uint8_t *text_buf, unsigned col, unsigned row, bool draw_cursor);
    void present();
};

#endif /* VIDEO_ADAPTER_H */
