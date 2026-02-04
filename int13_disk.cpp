//
// Int 13h: BIOS disk services.
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
#include "machine.h"
#include "pc86_arch.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

//
// Read DAP at DS:SI from memory (raw load to avoid trace noise).
// DAP layout: size(u8), reserved(u8), count(u16), buffer_off(u16), buffer_seg(u16), lba(u64).
//
void Machine::read_dap(unsigned addr, unsigned &count, Word &buf_seg, Word &buf_off, uint64_t &lba) const
{
    count = memory.load16(addr + 2);
    buf_off = memory.load16(addr + 4);
    buf_seg = memory.load16(addr + 6);
    lba = memory.load32(addr + 8) | ((uint64_t)memory.load32(addr + 12) << 32);
}

//
// Process Int 13h requests: Disk I/O.
//
void Machine::handle_int13_disk()
{
#if 0
    switch (cpu.get_ah()) {
    case 0x00:
        Machine::print_exception("INT 13h AH=00h Reset disk system");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x01:
        Machine::print_exception("INT 13h AH=01h Read disk status");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x02:
        Machine::print_exception("INT 13h AH=02h Read sectors (CHS)");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " AL=0x" << std::setw(2)
            << (unsigned)al << " (count) CHS=" << cylinder << "/" << head << "/" << sector
            << " ES:BX=0x" << std::setw(4) << es << ":0x" << std::setw(4) << bx << std::endl;
        break;
    case 0x03:
        Machine::print_exception("INT 13h AH=03h Write sectors (CHS)");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " AL=0x" << std::setw(2)
            << (unsigned)al << " (count) CHS=" << cylinder << "/" << head << "/" << sector
            << " ES:BX=0x" << std::setw(4) << es << ":0x" << std::setw(4) << bx << std::endl;
        break;
    case 0x04:
        Machine::print_exception("INT 13h AH=04h Verify sectors (CHS)");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " AL=0x" << std::setw(2)
            << (unsigned)al << " CHS=" << cylinder << "/" << head << "/" << sector << std::endl;
        break;
    case 0x05:
        Machine::print_exception("INT 13h AH=05h Format track");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " AL=0x" << std::setw(2)
            << (unsigned)al << " (sectors/track) CH=0x" << std::setw(2) << (unsigned)ch
            << " DH=0x" << std::setw(2) << (unsigned)dh << " ES:BX=0x" << std::setw(4) << es
            << ":0x" << std::setw(4) << bx << std::endl;
        break;
    case 0x08:
        Machine::print_exception("INT 13h AH=08h Get drive parameters");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x09:
        Machine::print_exception("INT 13h AH=09h Initialize drive parameters");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x0C:
        Machine::print_exception("INT 13h AH=0Ch Seek to cylinder");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " cylinder=" << cylinder
            << std::endl;
        break;
    case 0x0D:
        Machine::print_exception("INT 13h AH=0Dh Alternate disk reset");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x10:
        Machine::print_exception("INT 13h AH=10h Check drive ready");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x11:
        Machine::print_exception("INT 13h AH=11h Recalibrate drive");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x14:
        Machine::print_exception("INT 13h AH=14h Controller diagnostic");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x15:
        Machine::print_exception("INT 13h AH=15h Read disk drive size");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x16:
        Machine::print_exception("INT 13h AH=16h Detect disk change");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x41:
        Machine::print_exception("INT 13h AH=41h EDD installation check");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x42: {
        Machine::print_exception("INT 13h AH=42h Extended read (LBA)");
        unsigned addr = pc86_linear_addr(ds, si);
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;
        read_dap(m->memory, addr, count, buf_seg, buf_off, lba);
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " DS:SI=0x" << std::setw(4) << ds
            << ":0x" << std::setw(4) << si << " count=" << count << " buffer=0x" << std::setw(4)
            << buf_seg << ":0x" << std::setw(4) << buf_off << " LBA=0x" << std::setw(16) << lba
            << std::endl;
        break;
    }
    case 0x43: {
        Machine::print_exception("INT 13h AH=43h Extended write (LBA)");
        unsigned addr = pc86_linear_addr(ds, si);
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;
        read_dap(m->memory, addr, count, buf_seg, buf_off, lba);
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " DS:SI=0x" << std::setw(4) << ds
            << ":0x" << std::setw(4) << si << " count=" << count << " buffer=0x" << std::setw(4)
            << buf_seg << ":0x" << std::setw(4) << buf_off << " LBA=0x" << std::setw(16) << lba
            << std::endl;
        break;
    }
    case 0x44: {
        Machine::print_exception("INT 13h AH=44h Extended verify (LBA)");
        unsigned addr = pc86_linear_addr(ds, si);
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;
        read_dap(m->memory, addr, count, buf_seg, buf_off, lba);
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " DS:SI=0x" << std::setw(4) << ds
            << ":0x" << std::setw(4) << si << " count=" << count << " LBA=0x" << std::setw(16)
            << lba << std::endl;
        break;
    }
    case 0x45:
        Machine::print_exception("INT 13h AH=45h Lock/unlock drive");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " AL=0x" << std::setw(2)
            << (unsigned)al << " (subfunction)" << std::endl;
        break;
    case 0x46:
        Machine::print_exception("INT 13h AH=46h Eject media");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x47: {
        Machine::print_exception("INT 13h AH=47h Extended seek (LBA)");
        unsigned addr = pc86_linear_addr(ds, si);
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;
        read_dap(m->memory, addr, count, buf_seg, buf_off, lba);
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " DS:SI=0x" << std::setw(4) << ds
            << ":0x" << std::setw(4) << si << " LBA=0x" << std::setw(16) << lba << std::endl;
        break;
    }
    case 0x48:
        Machine::print_exception("INT 13h AH=48h Get drive parameters (EDD)");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " DS:SI=0x" << std::setw(4) << ds
            << ":0x" << std::setw(4) << si << " (buffer)" << std::endl;
        break;
    case 0x49:
        Machine::print_exception("INT 13h AH=49h Extended media change");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " (drive)" << std::endl;
        break;
    case 0x4B:
        Machine::print_exception("INT 13h AH=4Bh El Torito CD emulation");
        out << "      AL=0x" << std::setw(2) << (unsigned)al << " DS:SI=0x" << std::setw(4) << ds
            << ":0x" << std::setw(4) << si << " (packet)" << std::endl;
        break;
    case 0x4E:
        Machine::print_exception("INT 13h AH=4Eh Set hardware configuration");
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " AL=0x" << std::setw(2)
            << (unsigned)al << " (subfunction)" << std::endl;
        break;
    default:
        Machine::print_exception(("INT 13h AH=0x" + to_hex(ah) + " (unknown)").c_str());
        out << "      DL=0x" << std::setw(2) << (unsigned)dl << " CX=0x" << std::setw(4) << cx
            << " DX=0x" << std::setw(4) << dx << " DS:SI=0x" << std::setw(4) << ds << ":0x"
            << std::setw(4) << si << " ES:BX=0x" << std::setw(4) << es << ":0x" << std::setw(4)
            << bx << std::endl;
        break;
    }

    Word ax = cpu.get_ax();
    Word cx = cpu.get_cx();
    Word dx = cpu.get_dx();
    Byte ah = (Byte)(ax >> 8);
    Byte al = (Byte)(ax & 0xff);
    Byte ch = (Byte)(cx >> 8);
    Byte cl = (Byte)(cx & 0xff);
    Byte dh = (Byte)(dx >> 8);
    Byte dl = (Byte)(dx & 0xff);
    Word es = cpu.get_es(), ds = cpu.get_ds(), bx = cpu.get_bx(), si = cpu.get_si();

    unsigned cylinder = ch | ((cl & 0xC0u) << 2);
    unsigned sector   = cl & 0x3F; // 1-based
    unsigned head     = dh;

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << std::hex << std::setfill('0');


        out.flags(save);
    }

    throw std::runtime_error("Unimplemented call INT 13h AH=0x" + to_hex(ah));
#endif
}
