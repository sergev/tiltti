#include "fixture.h"

//
// Start DR-DOS version 3.41
//
TEST_F(MachineTest, drdos_v3_41)
{
    machine.boot_disk(TEST_DIR "/../images/drdos3.41-720k.img");

    // To exit from installer, type F10 - Up arrow - Enter.
    run("@A@u\rver\r");

    EXPECT_EQ(cursor_row(), 24);
    EXPECT_EQ(cursor_col(), 2);

    EXPECT_EQ(get_line(22), "A>ver");
    EXPECT_EQ(get_line(23), "DR DOS Release 3.41");
    EXPECT_EQ(get_line(24), "A>");
}

//
// Start DR-DOS version 5.0
//
TEST_F(MachineTest, drdos_v5_0)
{
    machine.boot_disk(TEST_DIR "/../images/drdos5.0-720k.img");

    // To exit from installer, type F10 - Up arrow - Enter.
    run("@A@u\rver\r");

    EXPECT_EQ(cursor_row(), 24);
    EXPECT_EQ(cursor_col(), 2);

    EXPECT_EQ(get_line(20), "A>ver");

    EXPECT_EQ(get_line(22), "DR DOS Release 5.0");

    EXPECT_EQ(get_line(24), "A>");
}

//
// Start DR-DOS version 6.0
//
TEST_F(MachineTest, drdos_v6_0)
{
    machine.boot_disk(TEST_DIR "/../images/drdos6.0-720k.img");

    // Start installer
    run(" ");
    EXPECT_EQ(cursor_row(), 24);
    EXPECT_EQ(cursor_col(), 80);
    EXPECT_EQ(get_line(24), " <Enter>=continue  <F10>=abort");

    // To exit from installer, type F10 - Up arrow - Enter.
    run("@A@u\r");
    EXPECT_EQ(cursor_row(), 24);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(24), "A>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 24);
    EXPECT_EQ(cursor_col(), 0);
    EXPECT_EQ(get_line(24), "A>ver");

    run("");
    EXPECT_EQ(cursor_row(), 24);
    EXPECT_EQ(cursor_col(), 2);

    EXPECT_EQ(get_line(18), "A>ver");

    EXPECT_EQ(get_line(20), "DR DOS Release 6.0");
    EXPECT_EQ(get_line(21), "Copyright (c) 1976,1982,1988,1990,1991 Digital Research Inc.");
    EXPECT_EQ(get_line(22), "All rights reserved.");

    EXPECT_EQ(get_line(24), "A>");
}

//
// Start DR-DOS version 7.03
//
TEST_F(MachineTest, drdos_v7_03)
{
    machine.boot_disk(TEST_DIR "/../images/drdos7.03-1.44m.img");

    // To exit from installer, type F8.
    run("@8nnnnyynnnnn");
    EXPECT_EQ(cursor_row(), 18);
    EXPECT_EQ(cursor_col(), 4);

    EXPECT_EQ(get_line(0), "S t a r t i n g   C a l d e r a   D R - D O S . . .");

    EXPECT_EQ(get_line(2), "Single stepping configuration files...");
    EXPECT_EQ(get_line(3), "DEVICE=SETVER.EXE [Y,N,R]? N");
    EXPECT_EQ(get_line(4), "COUNTRY=001,,A:\\COUNTRY.SYS [Y,N,R]? N");
    EXPECT_EQ(get_line(5), "DEVICE=HIMEM.SYS [Y,N,R]? N");
    EXPECT_EQ(get_line(6), "INSTALL=KEYB.COM US [Y,N,R]? N");
    EXPECT_EQ(get_line(7), "Executing AUTOEXEC.BAT [<Y>,N,R]? Y");

    EXPECT_EQ(get_line(9), "Caldera DR-DOS 7.03");
    EXPECT_EQ(get_line(10), "Copyright (c) 1976, 1998 Caldera, Inc.  All rights reserved.");

    EXPECT_EQ(get_line(12), "@ECHO OFF (Y/N) ? y");
    EXPECT_EQ(get_line(13), "if exist INSTALL.EXE goto install (Y/N) ? n");
    EXPECT_EQ(get_line(14), "ECHO Insert the UTILITIES 1 disk in drive A: (Y/N) ? n");
    EXPECT_EQ(get_line(15), "pause (Y/N) ? n");
    EXPECT_EQ(get_line(16), "if not exist INSTALL.EXE goto no_install (Y/N) ? n");
    EXPECT_EQ(get_line(17), "INSTALL.EXE (Y/N) ? n");
    EXPECT_EQ(get_line(18), "A:\\>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 18);
    EXPECT_EQ(cursor_col(), 0);

    run("");
    EXPECT_EQ(cursor_row(), 23);
    EXPECT_EQ(cursor_col(), 4);

    EXPECT_EQ(get_line(18), "A:\\>ver");

    EXPECT_EQ(get_line(20), "Caldera DR-DOS 7.03");
    EXPECT_EQ(get_line(21), "Copyright (c) 1976, 1998 Caldera, Inc.  All rights reserved.");

    EXPECT_EQ(get_line(23), "A:\\>");
}

//
// Start DR-DOS version 8.0
//
TEST_F(MachineTest, drdos_v8_0)
{
    machine.boot_disk(TEST_DIR "/../images/drdos8.0-1.44m.img");

    // To exit from installer, type F5.
    run("@5");
    EXPECT_EQ(cursor_row(), 2);
    EXPECT_EQ(cursor_col(), 0);

    run("");
    EXPECT_EQ(cursor_row(), 8);
    EXPECT_EQ(cursor_col(), 4);

    EXPECT_EQ(get_line(1), "Starting DeviceLogics DR-DOS...");

    EXPECT_EQ(get_line(4), "DeviceLogics DR-DOS 8.0");
    EXPECT_EQ(get_line(5), "Copyright (c) 1976, 2004 DeviceLogics, LLC.  All rights reserved.");

    EXPECT_EQ(get_line(8), "A:\\>");
}
