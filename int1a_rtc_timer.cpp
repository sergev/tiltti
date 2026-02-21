//
// Int 1Ah: BIOS RTC and timer.
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

#include "encoding.h"
#include "machine.h"
#include "pc86_arch.h"

//
// Process Int 1Ah request: RTC and Timer.
//
void Machine::handle_int1a_rtc_timer()
{
    switch (cpu.get_ah()) {
    case 0x00:
        int1a_read_system_clock_count();
        break;
    case 0x01:
        int1a_set_system_clock_count();
        break;
    case 0x02:
        int1a_read_cmos_time();
        break;
    case 0x03:
        int1a_set_cmos_time();
        break;
    case 0x04:
        int1a_read_cmos_date();
        break;
    case 0x05:
        int1a_set_cmos_date();
        break;
    case 0x06:
        int1a_set_alarm_time();
        break;
    case 0x07:
        int1a_turn_off_alarm();
        break;
    default:
        if (debug_all || debug_syscalls) {
            auto &out = Machine::get_trace_stream();
            auto save = out.flags();

            out << "\tAH=" << std::hex << std::setfill('0') << std::setw(2)
                << (unsigned)cpu.get_ah() << "h Unknown request" << std::endl;
            out.flags(save);
        }
    }
}

static unsigned bcd2bin(unsigned val)
{
    return (val & 0x0f) + ((val >> 4) * 10);
}

static unsigned bin2bcd(unsigned val)
{
    return (val % 10) | ((val / 10) << 4);
}

//
// AH=00h — Read system clock count.
//
// Return the current BIOS tick count and the midnight rollover flag.
// The tick count runs at approximately 18.2 Hz and rolls over at TICKS_PER_DAY (1573040).
// Outputs:
//      CX:DX = 32-bit tick count (high word in CX, low in DX)
//      AL = value of `timer_rollover` (then cleared)
//      CF = 0
// Reads BDA `timer_counter` and `timer_rollover`, clears `timer_rollover`, sets success.
//
void Machine::int1a_read_system_clock_count()
{
    cpu.set_cx(bda.timer_counter >> 16);
    cpu.set_dx(bda.timer_counter);
    cpu.set_al(bda.timer_rollover);
    bda.timer_rollover = 0;
    cpu.set_cf(0);
}

//
// AH=01h — Set system clock count.
//
// Set the BIOS tick counter and clear the midnight rollover flag.
// Inputs:
//      CX:DX = new 32-bit tick count (CX = high word, DX = low word).
// Outputs:
//      AH = 0, CF = 0.
// Writes BDA `timer_counter` and clears `timer_rollover`.
//
void Machine::int1a_set_system_clock_count()
{
    uint32_t ticks     = (cpu.get_cx() << 16) | cpu.get_dx();
    bda.timer_counter  = ticks;
    bda.timer_rollover = 0;
    cpu.set_ah(0);
    cpu.set_cf(0);
}

//
// AH=02h — Read CMOS time
//
// Read the current time from the RTC in BCD format.
// Outputs:
//      CH = hours (BCD)
//      CL = minutes (BCD)
//      DH = seconds (BCD)
//      DL bit 0 = daylight saving enable (DSE) from Status B
//      AH = 0
//      AL = CH (hours)
//      CF = 0
// If the RTC update-in-progress (UIP) bit is set, the handler returns with CF=1 (invalid).
//
void Machine::int1a_read_cmos_time()
{
    cpu.set_ch(bin2bcd(local_hour));
    cpu.set_cl(bin2bcd(local_min));
    cpu.set_dh(bin2bcd(local_sec));
    cpu.set_dl(local_isdst);
    cpu.set_ah(0);
    cpu.set_al(cpu.get_ch());
    cpu.set_cf(0);
}

//
// AH=03h — Set CMOS time
//
// Set the RTC time in BCD. Also updates Status B for 24-hour mode and daylight saving.
// Inputs:
//      CH = hours (BCD)
//      CL = minutes (BCD)
//      DH = seconds (BCD)
//      DL bit 0 = DSE (daylight saving enable)
// Outputs:
//      AH = 0
//      AL = value last written to CMOS Status B (24h + DSE)
//      CF = 0
//
void Machine::int1a_set_cmos_time()
{
    unsigned ch = cpu.get_ch();
    unsigned cl = cpu.get_cl();
    unsigned dh = cpu.get_dh();
    unsigned dl = cpu.get_dl();

    unsigned hour = bcd2bin(ch);
    unsigned min  = bcd2bin(cl);
    unsigned sec  = bcd2bin(dh);

    if (hour > 23)
        hour = 23;
    if (min > 59)
        min = 59;
    if (sec > 59)
        sec = 59;

    local_hour  = hour;
    local_min   = min;
    local_sec   = sec;
    local_isdst = dl & 1;

    // Sync BIOS tick counter so AH=00h (read tick count) stays consistent.
    unsigned sec_since_midnight = ((local_hour * 60) + local_min) * 60 + local_sec;
    bda.timer_counter = (sec_since_midnight * 1000u) / 55;

    cpu.set_ah(0);
    cpu.set_al(0x02 | (dl & 1)); // Status B: 24-hour mode + DSE
    cpu.set_cf(0);
}

//
// AH=04h — Read CMOS date
//
// Read the current date from the RTC in BCD format.
// Outputs:
//      CH = century
//      CL = year
//      DH = month
//      DL = day of month (BCD)
//      AL = CH
//      CF = 0
// If RTC is updating, CF=1 (invalid).
//
void Machine::int1a_read_cmos_date()
{
    cpu.set_ch(bin2bcd(local_year / 100));
    cpu.set_cl(bin2bcd(local_year % 100));
    cpu.set_dh(bin2bcd(local_month));
    cpu.set_dl(bin2bcd(local_mday));
    cpu.set_ah(0);
    cpu.set_al(cpu.get_ch());
    cpu.set_cf(0);

    // Debug.
    //auto &out = Machine::get_trace_stream();
    //out << "--- Year: CH=" << std::hex << (unsigned)cpu.get_ch() << ", CL=" << (unsigned)cpu.get_cl() << std::dec << std::endl;
    //out << "--- Month: DH=" << std::hex << (unsigned)cpu.get_dh() << std::dec << std::endl;
    //out << "--- Day: DL=" << std::hex << (unsigned)cpu.get_dl() << std::dec << std::endl;
}

void Machine::int1a_set_cmos_date()
{
    throw std::runtime_error("Unimplemented: Set CMOS date");
}

void Machine::int1a_set_alarm_time()
{
    throw std::runtime_error("Unimplemented: Set alarm time");
}

void Machine::int1a_turn_off_alarm()
{
    throw std::runtime_error("Unimplemented: Turn off alarm");
}
