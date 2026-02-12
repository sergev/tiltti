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
#include <cstdint>
#include <iomanip>
#include <sstream>

#include "machine.h"
#include "pc86_arch.h"

//
// Read DAP at DS:SI from memory.
// DAP layout: size(u8), reserved(u8), count(u16), buffer_off(u16), buffer_seg(u16), lba(u64).
//
void Machine::read_dap(unsigned addr, unsigned &count, Word &buf_seg, Word &buf_off,
                       uint64_t &lba) const
{
    count   = memory.load16(addr + 2);
    buf_off = memory.load16(addr + 4);
    buf_seg = memory.load16(addr + 6);
    lba     = memory.load32(addr + 8) | ((uint64_t)memory.load32(addr + 12) << 32);
}

//
// Return from Int 13h request.
//
void Machine::disk_ret(unsigned drive, unsigned code)
{
    if (drive < EXTSTART_HD) {
        bda.floppy_last_status = code;
    } else {
        bda.disk_last_status = code;
    }
    cpu.set_ah(code);
    cpu.set_cf(code != DISK_RET_SUCCESS);
}

//
// Process Int 13h request: Disk I/O.
//
void Machine::handle_int13_disk()
{
    switch (cpu.get_ah()) {
    case 0x00:
        int13_reset_disk_system();
        break;
    case 0x01:
        int13_read_disk_status();
        break;
    case 0x02:
        int13_read_sectors();
        break;
    case 0x03:
        int13_write_sectors();
        break;
    case 0x04:
        int13_verify_sectors();
        break;
    case 0x05:
        int13_format_track();
        break;
    case 0x08:
        int13_get_drive_parameters();
        break;
    case 0x09:
        int13_initialize_drive_parameters();
        break;
    case 0x0C:
        int13_seek_to_cylinder();
        break;
    case 0x0D:
        int13_alternate_disk_reset();
        break;
    case 0x10:
        int13_check_drive_ready();
        break;
    case 0x11:
        int13_recalibrate_drive();
        break;
    case 0x14:
        int13_controller_diagnostic();
        break;
    case 0x15:
        int13_read_disk_drive_size();
        break;
    case 0x16:
        int13_detect_disk_change();
        break;
    case 0x41:
        int13_edd_installation_check();
        break;
    case 0x42:
        int13_extended_read();
        break;
    case 0x43:
        int13_extended_write();
        break;
    case 0x44:
        int13_extended_verify();
        break;
    case 0x45:
        int13_lock_unlock_drive();
        break;
    case 0x46:
        int13_eject_media();
        break;
    case 0x47:
        int13_extended_seek();
        break;
    case 0x48:
        int13_get_edd_parameters();
        break;
    case 0x49:
        int13_extended_media_change();
        break;
    case 0x4B:
        int13_el_torito_cd_emulation();
        break;
    case 0x4E:
        int13_set_hardware_configuration();
        break;
    default:
        if (Machine::trace_enabled()) {
            auto &out = Machine::get_trace_stream();
            auto save = out.flags();

            out << "\tAH=" << std::hex << std::setfill('0') << std::setw(2)
                << (unsigned)cpu.get_ah() << "h Unknown request" << std::endl;
            out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl()
                << " CX=0x" << std::setw(4) << cpu.get_cx()
                << " DX=0x" << std::setw(4) << cpu.get_dx()
                << " DS:SI=0x" << std::setw(4) << cpu.get_ds() << ":0x" << std::setw(4) << cpu.get_si()
                << " ES:BX=0x" << std::setw(4) << cpu.get_es() << ":0x" << std::setw(4) << cpu.get_bx()
                << std::endl;
            out.flags(save);
        }
        disk_ret(cpu.get_dl(), DISK_RET_EPARAM);
    }
}

//
// AH=00h — Reset disk system
//
// Reset the disk controller/drive.
// Often used before or after other INT 13h calls to recover from errors.
// Inputs:
//      DL = drive number
// Outputs:
//      CF = 0 on success.
//      AH = status 0 on success; otherwise CF=1.
//      BDA last-status updated.
//
void Machine::int13_reset_disk_system()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=00h Reset disk system" << std::endl;
        out << "\tDL=0x" << std::hex << std::setfill('0') << std::setw(2)
            << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }

    // Nothing to do.
    // Return Success.
    cpu.set_cf(0);
    cpu.set_ah(0);
}

//
// Read disk status
//
// Return the status of the last disk operation for the given drive.
// No BDA update.
// Inputs:
//      DL = drive number
// Outputs:
//      AH = last status (from BDA `floppy_last_status` or `disk_last_status`)
//      CF is set if AH ≠ 0.
// All other INT 13h functions set the BDA last-status and AH/CF.
// This request simply reports that value.
//
void Machine::int13_read_disk_status()
{
    unsigned drive = cpu.get_dl();

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=01h Read disk status" << std::endl;
        out << "\tdrive=0x" << std::setw(2) << drive << std::endl;
        out.flags(save);
    }

    unsigned last_status = drive < EXTSTART_HD ? bda.floppy_last_status
                                               : bda.disk_last_status;
    disk_ret(drive, last_status);
}

//
// Read disk sectors (CHS)
//
// Read one or more sectors from the disk using CHS addressing.
// Same CHS→LBA and buffer rules as AH=03h, 04h.
// For LBA and large disks use AH=42h.
// CHS is validated against logical geometry and converted to LBA.
// Sector count > 128 or 0, or sector 0, or CHS out of range yields EPARAM.
// Total transfer size is limited by 64 KiB boundary.
// Inputs:
//      DL = drive
//      DH = head
//      CH = cylinder low 8 bits
//      CL = bits 6–7 = cylinder high 2 bits, bits 0–5 = sector number (1-based)
//      AL = sector count
//      ES:BX = data buffer
// Outputs:
//      On success: CF=0, AH=0, AL = number of sectors read.
//      On error: CF=1, AH = status.
//      BDA last-status updated.
//      Buffer filled with sector data.
//
void Machine::int13_read_sectors()
{
    unsigned cylinder = cpu.get_ch() | ((cpu.get_cl() & 0xC0) << 2); // 10 bits, 0-based
    unsigned sector   = cpu.get_cl() & 0x3f;                         // 6 bits, 1-based
    unsigned head     = cpu.get_dh();                                // 8 bits, 0-based
    unsigned nsectors = cpu.get_al();
    unsigned drive    = cpu.get_dl();
    unsigned addr     = pc86_linear_addr(cpu.get_es(), cpu.get_bx());

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();

        out << "\tAH=02h Read sectors (CHS)" << std::endl;
        out << "\tdrive=0x" << std::hex << std::setw(2) << drive
            << " nsectors=" << std::dec << std::setw(2) << nsectors
            << " CHS=" << cylinder << "/" << head << "/" << sector
            << " addr=0x" << std::hex << std::setw(5) << addr
            << std::dec << std::endl;
    }

    if (nsectors > 128 || nsectors == 0 || sector == 0) {
        // Bad length or wrong sector.
        disk_ret(drive, DISK_RET_EPARAM);
        return;
    }

    auto status = disk_io_chs('r', drive, cylinder, head, sector, addr, nsectors * SECTOR_NBYTES);
    if (status == DISK_RET_SUCCESS) {
        cpu.set_al(nsectors);
    } else {
        cpu.set_al(0);
    }
    disk_ret(drive, status);
}

void Machine::int13_write_sectors()
{
    unsigned cylinder = cpu.get_ch() | ((cpu.get_cl() & 0xC0) << 2); // 10 bits, 0-based
    unsigned sector   = cpu.get_cl() & 0x3f;                         // 6 bits, 1-based
    unsigned head     = cpu.get_dh();                                // 8 bits, 0-based

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=03h Write sectors (CHS)" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " AL=0x" << std::setw(2)
            << (unsigned)cpu.get_al() << " (count) CHS=" << cylinder << "/" << head << "/" << sector
            << " ES:BX=0x" << std::setw(4) << cpu.get_es() << ":0x" << std::setw(4) << cpu.get_bx()
            << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Write sectors (CHS)");
}

void Machine::int13_verify_sectors()
{
    unsigned cylinder = cpu.get_ch() | ((cpu.get_cl() & 0xC0) << 2); // 10 bits, 0-based
    unsigned sector   = cpu.get_cl() & 0x3f;                         // 6 bits, 1-based
    unsigned head     = cpu.get_dh();                                // 8 bits, 0-based

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=04h Verify sectors (CHS)" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " AL=0x" << std::setw(2)
            << (unsigned)cpu.get_al() << " CHS=" << cylinder << "/" << head << "/" << sector
            << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Verify sectors (CHS)");
}

void Machine::int13_format_track()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=05h Format track" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " AL=0x" << std::setw(2)
            << (unsigned)cpu.get_al() << " (sectors/track) CH=0x" << std::setw(2)
            << (unsigned)cpu.get_ch() << " DH=0x" << std::setw(2) << (unsigned)cpu.get_dh()
            << " ES:BX=0x" << std::setw(4) << cpu.get_es() << ":0x" << std::setw(4) << cpu.get_bx()
            << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Format track");
}

//
// AH=08h — Get drive parameters.
//
// Return logical CHS geometry and number of drives of this type.
// Inputs:
//      DL = drive number
// Outputs, on success:
//      CF = 0
//      AH = 0
//      AL = 0
//      CH = max cylinder (low 8 bits)
//      CL = (max cylinder >> 2) in bits 6–7,
//           sectors per track in bits 0–5
//      DH = max head
//      DL = count of drives (floppy or HD)
// For floppy:
//      ES:DI = diskette parameter table (segment 0xF000, `diskette_param_table2`);
//      BX = floppy type.
// For HD: last logical cylinder is reduced by one (reserved).
// On CD: returns EPARAM (not supported).
//
void Machine::int13_get_drive_parameters()
{
    unsigned drive = cpu.get_dl();

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=08h Get drive parameters" << std::endl;
        out << "\tdrive=0x" << std::setw(2) << drive << std::endl;
        out.flags(save);
    }

    // No hard disk for now.
    disk_ret(drive, DISK_RET_EPARAM);
}

void Machine::int13_initialize_drive_parameters()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=09h Initialize drive parameters" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Initialize drive parameters");
}

void Machine::int13_seek_to_cylinder()
{
    unsigned cylinder = cpu.get_ch() | ((cpu.get_cl() & 0xC0) << 2); // 10 bits, 0-based

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=0Ch Seek to cylinder" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " cylinder=" << cylinder
            << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Seek to cylinder");
}

void Machine::int13_alternate_disk_reset()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=0Dh Alternate disk reset" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Alternate disk reset");
}

void Machine::int13_check_drive_ready()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=10h Check drive ready" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Check drive ready");
}

void Machine::int13_recalibrate_drive()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=11h Recalibrate drive" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Recalibrate drive");
}

void Machine::int13_controller_diagnostic()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=14h Controller diagnostic" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Controller diagnostic");
}

//
// AH=15h — Read disk drive size.
//
// Return drive type and (for hard disks) total sector count in INT 13h geometry.
// Inputs:
//      DL = drive number
// Outputs:
//      CF = 0
//      For floppy or CD:
//          AH on return = 1 (drive present, type 1)
//      For hard disk:
//          AH = 3 (drive present, type 3)
//          CX:DX = 32-bit sector count (CX = high word, DX = low word)
//                  for the logical CHS space (max cylinder minus one for HD,
//                  then cylinders ×heads ×sectors).
//  BDA last-status set to success.
//  For HD computes sectors as `(nlc-1)*nlh*nls`.
//  For floppy/CD returns AH=1 only.
//
void Machine::int13_read_disk_drive_size()
{
    unsigned drive = cpu.get_dl();

    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=15h Read disk drive size" << std::endl;
        out << "\tdrive=0x" << std::setw(2) << drive << std::endl;
        out.flags(save);
    }
    if (drive < EXTSTART_HD) {
        // Floppy.
        cpu.set_ah(1);
        disk_ret(drive, DISK_RET_SUCCESS);
        return;
    }
    throw std::runtime_error("Unimplemented: Read disk drive size");
}

void Machine::int13_detect_disk_change()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=16h Detect disk change" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Detect disk change");
}

void Machine::int13_edd_installation_check()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=41h EDD installation check" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: EDD installation check");
}

void Machine::int13_extended_read()
{
    if (Machine::trace_enabled()) {
        auto &out     = Machine::get_trace_stream();
        auto save     = out.flags();
        unsigned addr = pc86_linear_addr(cpu.get_ds(), cpu.get_si());
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;

        read_dap(addr, count, buf_seg, buf_off, lba);
        out << "\tAH=42h Extended read (LBA)" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " DS:SI=0x"
            << std::setw(4) << cpu.get_ds() << ":0x" << std::setw(4) << cpu.get_si()
            << " count=" << count << " buffer=0x" << std::setw(4) << buf_seg << ":0x"
            << std::setw(4) << buf_off << " LBA=0x" << std::setw(16) << lba << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Extended read (LBA)");
}

void Machine::int13_extended_write()
{
    if (Machine::trace_enabled()) {
        auto &out     = Machine::get_trace_stream();
        auto save     = out.flags();
        unsigned addr = pc86_linear_addr(cpu.get_ds(), cpu.get_si());
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;

        read_dap(addr, count, buf_seg, buf_off, lba);
        out << "\tAH=43h Extended write (LBA)" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " DS:SI=0x"
            << std::setw(4) << cpu.get_ds() << ":0x" << std::setw(4) << cpu.get_si()
            << " count=" << count << " buffer=0x" << std::setw(4) << buf_seg << ":0x"
            << std::setw(4) << buf_off << " LBA=0x" << std::setw(16) << lba << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Extended write (LBA)");
}

void Machine::int13_extended_verify()
{
    if (Machine::trace_enabled()) {
        auto &out     = Machine::get_trace_stream();
        auto save     = out.flags();
        unsigned addr = pc86_linear_addr(cpu.get_ds(), cpu.get_si());
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;

        read_dap(addr, count, buf_seg, buf_off, lba);
        out << "\tAH=44h Extended verify (LBA)" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " DS:SI=0x"
            << std::setw(4) << cpu.get_ds() << ":0x" << std::setw(4) << cpu.get_si()
            << " count=" << count << " LBA=0x" << std::setw(16) << lba << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Extended verify (LBA)");
}

void Machine::int13_lock_unlock_drive()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=45h Lock/unlock drive" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " AL=0x" << std::setw(2)
            << (unsigned)cpu.get_al() << " (subfunction)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Lock/unlock drive");
}

void Machine::int13_eject_media()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=46h Eject media" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Eject media");
}

void Machine::int13_extended_seek()
{
    if (Machine::trace_enabled()) {
        auto &out     = Machine::get_trace_stream();
        auto save     = out.flags();
        unsigned addr = pc86_linear_addr(cpu.get_ds(), cpu.get_si());
        unsigned count;
        Word buf_seg, buf_off;
        uint64_t lba;

        read_dap(addr, count, buf_seg, buf_off, lba);
        out << "\tAH=47h Extended seek (LBA)" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " DS:SI=0x"
            << std::setw(4) << cpu.get_ds() << ":0x" << std::setw(4) << cpu.get_si() << " LBA=0x"
            << std::setw(16) << lba << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Extended seek (LBA)");
}

void Machine::int13_get_edd_parameters()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=48h Get drive parameters (EDD)" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " DS:SI=0x"
            << std::setw(4) << cpu.get_ds() << ":0x" << std::setw(4) << cpu.get_si() << " (buffer)"
            << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Get drive parameters (EDD)");
}

void Machine::int13_extended_media_change()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=49h Extended media change" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " (drive)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Extended media change");
}

void Machine::int13_el_torito_cd_emulation()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=4Bh El Torito CD emulation" << std::endl;
        out << "\tAL=0x" << std::setw(2) << (unsigned)cpu.get_al() << " DS:SI=0x"
            << std::setw(4) << cpu.get_ds() << ":0x" << std::setw(4) << cpu.get_si() << " (packet)"
            << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: El Torito CD emulation");
}

void Machine::int13_set_hardware_configuration()
{
    if (Machine::trace_enabled()) {
        auto &out = Machine::get_trace_stream();
        auto save = out.flags();

        out << "\tAH=4Eh Set hardware configuration" << std::endl;
        out << "\tDL=0x" << std::setw(2) << (unsigned)cpu.get_dl() << " AL=0x" << std::setw(2)
            << (unsigned)cpu.get_al() << " (subfunction)" << std::endl;
        out.flags(save);
    }
    throw std::runtime_error("Unimplemented: Set hardware configuration");
}
