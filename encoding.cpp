//
// Text encoding.
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
#include "encoding.h"

#include <iostream>

//
// Write Unicode symbol to stdout.
//
void utf8_putc(unsigned ch)
{
    utf8_putc(ch, std::cout);
}

//
// Write Unicode symbol to a stream.
// Convert to UTF-8 encoding:
// 00000000.0xxxxxxx -> 0xxxxxxx
// 00000xxx.xxyyyyyy -> 110xxxxx, 10yyyyyy
// xxxxyyyy.yyzzzzzz -> 1110xxxx, 10yyyyyy, 10zzzzzz
//
void utf8_putc(unsigned ch, std::ostream &s)
{
    if (ch < 0x80) {
        s << (char)ch;
        return;
    }
    if (ch < 0x800) {
        s << (char)(ch >> 6 | 0xc0);
        s << (char)((ch & 0x3f) | 0x80);
        return;
    }
    s << (char)(ch >> 12 | 0xe0);
    s << (char)(((ch >> 6) & 0x3f) | 0x80);
    s << (char)((ch & 0x3f) | 0x80);
}
