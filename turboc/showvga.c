/*
 * showvga.c -- Standalone Turbo C CLI: show current VGA mode and BDA video fields.
 * Uses INT 10h AH=0Fh, INT 10h AX=1B00h, and direct BDA read at 40h.
 * Output goes to both stdout and vga.out.
 * INT 10h AH=1Bh returns the 64-byte Video Save Area (INT 10h AH=1Bh layout).
 */
#include <stdio.h>
#include <stdarg.h>
#include <dos.h>

#define BDA_SEG 0x40

static FILE *fout;

/* Print to both stdout and vga.out. */
static void out(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    if (fout != NULL)
        vfprintf(fout, fmt, ap);
    va_end(ap);
}

/* Read byte at BDA offset (segment 40h). */
static unsigned char bda_byte(unsigned int off)
{
    return *(unsigned char far *)MK_FP(BDA_SEG, off);
}

/* Read word at BDA offset (segment 40h, little-endian). */
static unsigned int bda_word(unsigned int off)
{
    return *(unsigned int far *)MK_FP(BDA_SEG, off);
}

/* Print a byte as hex and decoded bits (names for bits 0..n-1). */
static void out_bitfield(const char *name, unsigned char val, const char *bits[], int n)
{
    int i;
    out("  %s = 0x%02X\n", name, val);
    for (i = 0; i < n && bits[i] != NULL; i++) {
        if (val & (1 << i))
            out("    bit %d (0x%02X): %s\n", i, 1 << i, bits[i]);
    }
}

static void do_int10_0f(void)
{
    union REGS in, outregs;

    out("\n--- INT 10h AH=0Fh (Get current video mode) ---\n");
    in.h.ah = 0x0F;
    in.h.al = 0;
    int86(0x10, &in, &outregs);

    out("  AL (mode)     = 0x%02X (%u)", outregs.h.al, outregs.h.al);
    if (outregs.h.al & 0x80)
        out("  [bit 7 set: do not clear memory on mode set]");
    out("\n");
    out("  AH (columns) = %u\n", outregs.h.ah);
    out("  BH (page)    = %u\n", outregs.h.bh);
}

/* INT 10h AH=1Bh return buffer (64 bytes, Video Save Area layout). */
static void do_int10_1b00(void)
{
    static unsigned char buf[64];
    union REGS in, outregs;
    struct SREGS sregs;
    unsigned int i;
    unsigned long static_seg, static_off;
    static const char *rMiscFlags_bits[] = {
        "all modes on all displays active",
        "gray-scale summing is active",
        "monochrome display attached",
        "default palette loading disabled",
        "cursor emulation active",
        "blinking enabled (0=bold bkgnd)",
        NULL, NULL
    };
    static const char *rSaveStatus_bits[] = {
        "512-character set active",
        "dynamic save area active",
        "text font override active",
        "graphics font override active",
        "palette override active",
        "DCC extension active",
        NULL, NULL
    };

    out("\n--- INT 10h AX=1B00h (Video Save Area) ---\n");

    in.x.ax = 0x1B00;
    in.x.bx = 0;
    in.x.cx = 0;
    in.x.dx = 0;
    in.x.di = FP_OFF(buf);
    segread(&sregs);
    sregs.es = FP_SEG(buf);

    int86x(0x10, &in, &outregs, &sregs);

    if (outregs.h.al != 0x1B) {
        out("  Not supported (AL=0x%02X)\n", outregs.h.al);
        return;
    }

    out("  AL = 0x1B (supported)\n");

    out("  Raw Video Save Area (64 bytes):\n");
    for (i = 0; i < 64; i += 8) {
        out("  +%02Xh: %02X %02X %02X %02X %02X %02X %02X %02X\n",
            i, buf[i], buf[i + 1], buf[i + 2], buf[i + 3],
            buf[i + 4], buf[i + 5], buf[i + 6], buf[i + 7]);
    }

    static_off = (unsigned long)buf[0] | ((unsigned long)buf[1] << 8);
    static_seg = (unsigned long)buf[2] | ((unsigned long)buf[3] << 8);
    out("  pfrFnality    = %04lX:%04lX (static functionality table)\n", static_seg, static_off);

    out("  bCurDcc       = 0x%02X (active DCC)\n", buf[0x04]);
    out("  bCurMode      = 0x%02X\n", buf[0x05]);
    out("  bCrtClms      = %u\n", buf[0x06] | (buf[0x07] << 8));
    out("  wCrtBufLen    = %u bytes\n", buf[0x08] | (buf[0x09] << 8));
    out("  pCrtPgStart   = 0x%04X\n", buf[0x0A] | (buf[0x0B] << 8));

    out("  awCrsrPos     =");
    for (i = 0; i < 8; i++) {
        unsigned int pos = buf[0x0C + i * 2] | (buf[0x0D + i * 2] << 8);
        out(" page%u:(row=%u,col=%u)", i, pos >> 8, pos & 0xFF);
    }
    out("\n");

    out("  wCrsrType     = 0x%04X (start/end scan)\n", buf[0x1C] | (buf[0x1D] << 8));
    out("  bCurPg        = %u\n", buf[0x16]);
    out("  wCrtcPort     = 0x%02X (3B4=mono, 3D4=color)\n", buf[0x17]);
    out("  bModeSetReg   = 0x%02X (port 3?8)\n", buf[0x18]);
    out("  bClrSetReg    = 0x%02X (port 3?9)\n", buf[0x19]);
    out("  bCrtRows      = %u (character rows on screen)\n", buf[0x1A]);
    out("  bCrtPoints    = %u (scan lines per character cell)\n", buf[0x1B]);
    out("  bMaxPgs       = %u\n", buf[0x23]);
    out("  bScanLnsCode  = %u (0=200, 1=350, 2=400, 3=480)\n", buf[0x24]);
    out("  bFont1        = %u (primary font block)\n", buf[0x25]);
    out("  bFont2        = %u (secondary font block)\n", buf[0x26]);

    out_bitfield("rMiscFlags", buf[0x27], rMiscFlags_bits, 6);

    out("  bVidMemCode   = %u (0=64K, 1=128K, 2=192K, 3=256K)\n", buf[0x2C]);

    out_bitfield("rSaveStatus", buf[0x2D], rSaveStatus_bits, 6);

    out("  res           = +2eH and +2fH (reserved)\n");

    /* VgaStaticFnalityRec (16 bytes) per vga_static_functionality_table.html */
    if (static_seg != 0 || static_off != 0) {
        unsigned char far *st = (unsigned char far *)MK_FP((unsigned)static_seg, (unsigned)static_off);
        static const char *rMiscFlags1_bits[] = {
            "all modes on all displays",
            "gray-scale summing (INT 10h 101bh)",
            "char set loading (INT 10h 11h)",
            "default palette loading",
            "cursor emulation",
            "64-color palette (INT 10h 10h)",
            "video DAC palette loading",
            "palette loading via ATC",
            NULL
        };
        static const char *rMiscFlags2_bits[] = {
            "light pen (INT 10h 04h)",
            "save/restore state (INT 10h 1ch)",
            "blink/bold mapping (INT 10h 1003h)",
            "DCC control (INT 10h 1ah)",
            NULL, NULL, NULL, NULL
        };
        static const char *rSaveCaps_bits[] = {
            "multiple 512-character set",
            "dynamic save area",
            "text font override",
            "graphics font override",
            "palette override",
            "DCC extension",
            NULL, NULL
        };

        out("\n  --- VgaStaticFnalityRec (16 bytes) ---\n");
        out("  bModes1       = 0x%02X (bit0=mode00..bit7=mode07)\n", st[0]);
        out("  bModes2       = 0x%02X (bit0=mode08..bit7=mode0F)\n", st[1]);
        out("  bModes3       = 0x%02X (bit0=mode10..bit3=mode13)\n", st[2]);
        /* List supported modes from bModes1 */
        out("  modes supported (from bModes1):");
        for (i = 0; i < 8; i++)
            if (st[0] & (1 << i))
                out(" %u", i);
        out("\n");
        out("  res           = +3 4 bytes (reserved)\n");
        out("  bScanLnsFlgs  = 0x%02X (bit0=200, bit1=350, bit2=400)\n", st[7]);
        out("    scan lines available:");
        if (st[7] & 1) out(" 200");
        if (st[7] & 2) out(" 350");
        if (st[7] & 4) out(" 400");
        out("\n");
        out("  bFontBlks     = %u (font blocks available, 4=EGA 8=VGA)\n", st[8]);
        out("  bMaxFonts     = %u (max active font blocks in text mode)\n", st[9]);

        out_bitfield("rMiscFlags1", st[0x0A], rMiscFlags1_bits, 8);
        out_bitfield("rMiscFlags2", st[0x0B], rMiscFlags2_bits, 4);

        out("  res           = +0cH 2 bytes (reserved)\n");
        out_bitfield("rSaveCaps", st[0x0E], rSaveCaps_bits, 6);
        out("  res           = +0fH 1 byte (reserved)\n");
    }
}

static void do_bda_dump(void)
{
    unsigned int i;

    out("\n--- BDA video fields (40h:xx) ---\n");

    out("  40:49 video_mode     = 0x%02X\n", bda_byte(0x49));
    out("  40:4A video_cols     = %u (0x%04X)\n", bda_word(0x4A), bda_word(0x4A));
    out("  40:4C video_pagesize  = %u (0x%04X)\n", bda_word(0x4C), bda_word(0x4C));
    out("  40:4E video_pagestart = 0x%04X\n", bda_word(0x4E));

    for (i = 0; i < 8; i++) {
        unsigned int pos = bda_word(0x50 + i * 2);
        out("  40:50+%u cursor_pos[%u] = row=%u col=%u (0x%04X)\n",
            i * 2, i, pos >> 8, pos & 0xFF, pos);
    }

    out("  40:60 cursor_type    = 0x%04X\n", bda_word(0x60));
    out("  40:62 video_page     = %u\n", bda_byte(0x62));
    out("  40:63 crtc_address   = 0x%04X\n", bda_word(0x63));
    out("  40:65 video_msr      = 0x%02X\n", bda_byte(0x65));
    out("  40:66 video_pal      = 0x%02X\n", bda_byte(0x66));
    out("  40:84 video_rows     = %u (rows = %u)\n", bda_byte(0x84), bda_byte(0x84) + 1);
    out("  40:85 char_height    = %u\n", bda_word(0x85));
    out("  40:87 video_ctl      = 0x%02X (bit0=cursor en, bit7=no clear)\n", bda_byte(0x87));
    out("  40:88 video_switches = 0x%02X\n", bda_byte(0x88));
    out("  40:89 modeset_ctl    = 0x%02X\n", bda_byte(0x89));
    out("  40:8A dcc_index      = 0x%02X\n", bda_byte(0x8A));
}

int main(void)
{
    fout = fopen("vga.out", "w");
    if (fout == NULL) {
        printf("Warning: cannot open vga.out, writing to stdout only\n");
    }

    out("ShowVGA -- current VGA mode and BDA video fields\n");

    do_int10_0f();
    do_int10_1b00();
    do_bda_dump();

    out("\nDone.\n");

    if (fout != NULL) {
        fclose(fout);
        fout = NULL;
    }
    return 0;
}
