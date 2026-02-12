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
#include <sys/time.h>

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
        if (Machine::trace_enabled()) {
            auto &out = Machine::get_trace_stream();
            auto save = out.flags();

            out << "\tAH=" << std::hex << std::setfill('0') << std::setw(2)
                << (unsigned)cpu.get_ah() << "h Unknown request" << std::endl;
            out.flags(save);
        }
    }
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
    struct timeval tv;
    gettimeofday(&tv, 0);

    // Get microseconds since midnight.
    const uint64_t sec_since_midnight  = tv.tv_sec % 86400;
    const uint64_t usec_since_midnight = (sec_since_midnight * 1000000) + tv.tv_usec;

    const uint64_t TICKS_PER_DAY = 1573040;
    uint32_t ticks = usec_since_midnight * TICKS_PER_DAY / 86400 / 1000000;

    cpu.set_cx(ticks >> 16);
    cpu.set_dx(ticks);
    cpu.set_al(0);
    cpu.set_cf(0);
}

void Machine::int1a_set_system_clock_count()
{
    throw std::runtime_error("Unimplemented: Set system clock count");
}

//
// AH=02h — Read CMOS time
//
// Read the current time from the RTC in BCD format.
// Outputs:
//      CH = hours
//      CL = minutes
//      DH = seconds (BCD)
//      DL bit 0 = daylight saving enable (DSE) from Status B
//      AL = CH (hours)
//      CF = 0
// If the RTC update-in-progress (UIP) bit is set, the handler returns with CF=1 (invalid).
//
void Machine::int1a_read_cmos_time()
{
    struct timeval tv;
    gettimeofday(&tv, 0);

    time_t now = tv.tv_sec;
    struct tm *info = localtime(&now);

    cpu.set_ch(info->tm_hour);
    cpu.set_cl(info->tm_min);
    cpu.set_dh(info->tm_sec);
    cpu.set_dl(info->tm_isdst);
    cpu.set_al(info->tm_hour);
    cpu.set_cf(0);
}

void Machine::int1a_set_cmos_time()
{
    throw std::runtime_error("Unimplemented: Set CMOS time");
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
    struct timeval tv;
    gettimeofday(&tv, 0);

    time_t now = tv.tv_sec;
    struct tm *info = localtime(&now);
    int century = 20;

    cpu.set_ch(century);
    cpu.set_cl(info->tm_year);
    cpu.set_dh(info->tm_mon);
    cpu.set_dl((info->tm_mday % 10) + (info->tm_mday / 10) * 16);
    cpu.set_al(century);
    cpu.set_cf(0);
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
