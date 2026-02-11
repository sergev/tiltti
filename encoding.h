//
// Encoding routines.
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
#ifndef TILTTI_ENCODING_H
#define TILTTI_ENCODING_H

#include <iostream>

//
// Write Unicode symbol to stdout in UTF-8 encoding.
//
void utf8_putc(unsigned ch);

//
// Write Unicode symbol to a stream in UTF-8 encoding.
//
void utf8_putc(unsigned ch, std::ostream &s);

//
// Convert Unicode character to Code Page 437 encoding.
//
unsigned char unicode_to_cp437(unsigned short val);

//
// Convert Code Page 437 encoding to Unicode.
//
extern const unsigned short cp437_to_unicode_table[256];

#endif // TILTTI_ENCODING_H
