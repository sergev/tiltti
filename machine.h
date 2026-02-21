//
// Implement PC i86 machine.
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
#ifndef TILTTI_MACHINE_H
#define TILTTI_MACHINE_H

#include <array>
#include <chrono>
#include <cstddef>
#include <functional>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

#include "disk.h"
#include "processor.h"

//
// Parameters for refreshing the display (used by main() with Video_Adapter).
//
struct VideoRefreshParams {
    const uint8_t *text_buf;
    unsigned cursor_col;
    unsigned cursor_row;
    uint16_t cursor_type;
    bool need_refresh;
};

class Machine {
private:
    // Protect the Upper Memory Area.
    bool mode_640k{};

    // A20 address line state (INT 15h AH=24h). When false, addresses above 1 MB would wrap
    // (not applied in current 1 MB memory model).
    bool a20_enabled{ true };

    // Disks and floppies.
    std::array<std::unique_ptr<Disk>, NDISKS> disks;

    // Dump disk data for debug.
    bool dump_io_flag{}; // set to true to dump all disk reads
    unsigned dump_serial_num{};

    // Trace output.
    static std::ofstream trace_stream;

    // Trace modes.
    static bool debug_all;      // trace CPU registers, instructions, memory and everything else
    static bool debug_syscalls; // trace syscalls
    static bool debug_ports;    // trace i/o ports

    // Keyboard queue (fed by main() from SDL).
    std::queue<uint16_t> keyboard_queue_;

    // Callback for input events (used by INT 16h).
    std::function<void(unsigned)> event_callback = [](unsigned) {};

    // Video memory has changed
    bool video_dirty{};

    // Optional font buffer for INT 10h AH=11h (display owns the storage).
    uint8_t *font_buf_    = nullptr;
    size_t font_buf_size_ = 0;

    // Current date and time.
    unsigned local_year{ 1980 };  // 1980...
    unsigned local_month{ 1 };    // 1...12
    unsigned local_mday{ 1 };     // 1...31
    unsigned local_hour{ 0 };     // 0...23
    unsigned local_min{ 0 };      // 0...59
    unsigned local_sec{ 0 };      // 0...59
    unsigned local_isdst{ 0 };    // 0...1

    // Static stuff.
    static uint64_t simulated_instructions; // Count of instructions

public:
    // 32K words of virtual memory.
    Memory &memory;

    // PC i86 processor.
    Processor cpu;

    Interrupt_Vector_Table &ivt;   // Interrupt vector table at 0x00000
    Bios_Data_Area &bda;           // Bios Data Area at 0x00400
    Extended_Bios_Data_Area &ebda; // Extended Bios Data Area at 0x9fc00
    Byte *bios;                    // Bios ROM at 0xf0000
    Floppy_Extended_Disk_Base_Table &diskette_param_table2;

    // Type and AH of the last syscall, for tests.
    unsigned last_syscall{};
    unsigned kbd_poll_count{};

    explicit Machine(Memory &memory);

    // Destructor.
    ~Machine();

    // Set event callback (used by INT 16h).
    void set_event_callback(std::function<void(unsigned)> func) { event_callback = func; }

    // Run a batch of CPU steps (main() owns the loop and calls this).
    void run_batch(unsigned n);
    void invoke_vector(unsigned vector);

    // Parameters for main() to refresh the display from memory at 0xb8000 and BDA.
    // Clear video_dirty flag.
    VideoRefreshParams get_video_refresh_params();

    // Update BDA kbd_flag0 from host modifier state (called by main() from SDL).
    void set_kbd_modifiers(uint16_t flags);

    // Set font buffer for INT 10h AH=11h; display (e.g. Video_Adapter) owns the storage.
    void set_font_buffer(uint8_t *ptr, size_t size);

    // Keyboard queue. AX = (scancode << 8) | ASCII.
    void push_keystroke(uint16_t ax);
    bool has_keystroke() const;
    uint16_t peek_keystroke() const;
    uint16_t pop_keystroke();

    // Get instruction count.
    static uint64_t get_instr_count() { return simulated_instructions; }
    static void incr_simulated_instructions() { simulated_instructions++; }

    // Enable trace output to the given file,
    // or to std::cout when filename not present.
    static void enable_trace(const char *mode);
    static void enable_trace(unsigned bitmask);
    static void redirect_trace(const char *file_name, const char *default_mode);
    static void close_trace();
    static bool trace_enabled() { return debug_all || debug_syscalls || debug_ports; }

    // Emit trace to this stream.
    static std::ostream &get_trace_stream();

    // Memory access, byte-addressed.
    // Word ops use little-endian (low at addr, high at addr+1).
    Byte mem_fetch_byte(unsigned addr);
    Byte mem_load_byte(unsigned addr);
    void mem_store_byte(unsigned addr, Byte val);
    Word mem_load_word(unsigned addr);
    void mem_store_word(unsigned addr, Word val);

    // Port I/O.
    static Byte port_in_byte(unsigned port);
    static void port_out_byte(unsigned port, Byte val);
    static Word port_in_word(unsigned port);
    static void port_out_word(unsigned port, Word val);

    // Disk i/o.
    unsigned disk_io_chs(char op, unsigned disk_unit, unsigned cylinder, unsigned head,
                         unsigned sector, unsigned addr, unsigned nbytes);
    void disk_mount(unsigned disk_unit, const std::string &path, bool write_permit);

    // Boot from disk or floppy image. Second path optional (drive B:).
    void boot_disk(const std::string &filename, const std::string &filename_b = "");
    void start_basic();

    // Syscalls.
    bool is_syscall(int type);
    void process_syscall(int type);
    void handle_int10_video();
    void handle_int13_disk();
    void handle_int14_serial();
    void handle_int15_system_services();
    void handle_int16_keyboard();
    void handle_int17_printer();
    void handle_int1a_rtc_timer();

    //
    // Trace methods.
    //
    static void trace_exception(const char *message)
    {
        if (trace_enabled())
            print_exception(message);
    }

    void trace_instruction()
    {
        if (debug_all)
            cpu.print_instruction();
    }

    void trace_registers()
    {
        if (debug_all)
            cpu.print_registers();
    }

    void print_exception_ah(const char *message);
    static void print_exception(const char *message);
    static void print_byte_access(unsigned addr, Byte val, const char *opname);
    static void print_word_access(unsigned addr, Word val, const char *opname);
    void print_handler(unsigned addr);

    void unsupported(uint8_t op, const std::string &required_cpu);

    void setup_bios_config_table();
    void setup_floppy();
    void set_video_mode(unsigned mode);
    void clear_video_memory();
    void read_dap(unsigned addr, unsigned &count, Word &buf_seg, Word &buf_off,
                  uint64_t &lba) const;
    void disk_ret(unsigned drive, unsigned code);

    // Int 10: video
    void int10_set_video_mode();
    void int10_set_cursor_shape();
    void int10_set_cursor_position();
    void int10_get_cursor_position();
    void int10_read_light_pen_position();
    void int10_select_display_page();
    void int10_scroll_window_up();
    void int10_scroll_window_down();
    void int10_read_char();
    void int10_write_char();
    void int10_write_char_only();
    void int10_set_cga_palette();
    static void int10_write_pixel();
    static void int10_read_pixel();
    void int10_teletype_output();
    void int10_get_current_video_mode();
    void int10_palette_control();
    void int10_char_generator();
    void int10_alternate_select();
    void int10_write_string();
    void int10_display_combination_code();
    void int10_video_bios_functionality();
    void int10_save_restore_video_state();
    void int10_vbe();
    void scroll_window(int dir);
    void write_cells_at_cursor(unsigned page, unsigned count, uint8_t ch, bool use_fixed_attr,
                               uint8_t fixed_attr);

    // Int 13: disk
    void int13_reset_disk_system();
    void int13_read_disk_status();
    void int13_read_sectors();
    void int13_write_sectors();
    void int13_verify_sectors();
    void int13_format_track();
    void int13_get_drive_parameters();
    void int13_initialize_drive_parameters();
    void int13_seek_to_cylinder();
    void int13_alternate_disk_reset();
    void int13_check_drive_ready();
    void int13_recalibrate_drive();
    void int13_controller_diagnostic();
    void int13_read_disk_drive_size();
    void int13_detect_disk_change();
    void int13_edd_installation_check();
    void int13_extended_read();
    void int13_extended_write();
    void int13_extended_verify();
    void int13_lock_unlock_drive();
    void int13_eject_media();
    void int13_extended_seek();
    void int13_get_edd_parameters();
    void int13_extended_media_change();
    void int13_el_torito_cd_emulation();
    void int13_set_hardware_configuration();

    // Int 14: serial
    void int14_initialize_serial_port();
    static void int14_write_char();
    static void int14_read_char();
    static void int14_get_port_status();

    // Int 15: system services
    void int15_a20_gate_control();
    static void int15_keyboard_intercept();
    static void int15_removable_media_eject();
    static void int15_apm_bios();
    static void int15_vga_option_rom_intel();
    static void int15_vga_option_rom_smi();
    static void int15_user_wait_interval();
    static void int15_wait_for_time();
    static void int15_copy_memory_block();
    void int15_get_extended_memory_size();
    static void int15_switch_to_protected_mode();
    static void int15_device_busy();
    static void int15_interrupt_complete();
    void int15_get_system_configuration();
    void int15_get_ebda_segment();
    static void int15_mouse_interface();
    static void int15_extended_memory();

    // Int 16: keyboard
    void int16_read_keyboard_input();
    void int16_check_keyboard_status();
    void int16_get_shift_flag_status();
    static void int16_store_keystroke_in_buffer();
    void int16_get_keyboard_functionality();
    static void int16_get_keyboard_id();
    static void int16_read_mf2_keyboard_input();
    static void int16_check_mf2_keyboard_status();
    static void int16_get_extended_keyboard_status();
    static void int16_keyboard_capability_check();
    void int16_keyboard_capability_dos_keyb();
    static void int16_122key_capability_check();

    // Int 17: printer
    static void int17_write_char();
    void int17_initialize_port();
    static void int17_get_status();

    // Int 1a: RTC and timer
    void int1a_read_system_clock_count();
    void int1a_set_system_clock_count();
    void int1a_read_cmos_time();
    void int1a_set_cmos_time();
    void int1a_read_cmos_date();
    void int1a_set_cmos_date();
    static void int1a_set_alarm_time();
    static void int1a_turn_off_alarm();
    void update_timer_counter();
};

#endif // TILTTI_MACHINE_H
