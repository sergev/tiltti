#include "fixture.h"

//
// Start PC DOS version 1.10
//
TEST_F(MachineTest, pcdos_v1_10)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos1.10-160k.img");
    run("\r\r");
    EXPECT_EQ(cursor_row(), 9);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "Current date is Tue  1-01-1980");
    EXPECT_EQ(get_line(1), "Enter new date:");
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.00");
    EXPECT_EQ(get_line(3), "Enter new time:");

    EXPECT_EQ(get_line(6), "The IBM Personal Computer DOS");
    EXPECT_EQ(get_line(7), "Version 1.10 (C)Copyright IBM Corp 1981, 1982");

    EXPECT_EQ(get_line(9), "A>");
}

//
// Start PC DOS version 2.10
//
TEST_F(MachineTest, pcdos_v2_10)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos2.10-180k.img");
    run("\r\r");
    EXPECT_EQ(cursor_row(), 9);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "Current date is Tue  1-01-1980");
    EXPECT_EQ(get_line(1), "Enter new date:");
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.05");
    EXPECT_EQ(get_line(3), "Enter new time:");

    EXPECT_EQ(get_line(6), "The IBM Personal Computer DOS");
    EXPECT_EQ(get_line(7), "Version 2.10 (C)Copyright IBM Corp 1981, 1982, 1983");

    EXPECT_EQ(get_line(9), "A>");
}

//
// Start PC DOS version 3.30
//
TEST_F(MachineTest, pcdos_v3_30)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos3.30-720k.img");
    run("\r\r");
    EXPECT_EQ(cursor_row(), 10);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "Current date is Tue  1-01-1980");
    EXPECT_EQ(get_line(1), "Enter new date (mm-dd-yy):");
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.10");
    EXPECT_EQ(get_line(3), "Enter new time:");

    EXPECT_EQ(get_line(6), "The IBM Personal Computer DOS");
    EXPECT_EQ(get_line(7), "Version 3.30 (C)Copyright International Business Machines Corp 1981, 1987");
    EXPECT_EQ(get_line(8), "             (C)Copyright Microsoft Corp 1981, 1986");

    EXPECT_EQ(get_line(10), "A>");
}

//
// Start PC DOS version 4.00
//
TEST_F(MachineTest, pcdos_v4_00)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos4.01-720k.img");

    run("\r");
    show_screen();
    EXPECT_EQ(cursor_row(), 0);
    EXPECT_EQ(cursor_col(), 0);
    EXPECT_EQ(get_line(18), "                       (C) Copyright IBM Corp. 1988.");
    EXPECT_EQ(get_line(19), "                            All rights reserved.");

    run("@e@3");
    EXPECT_EQ(cursor_row(), 0);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "A>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 5);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "A>ver");

    EXPECT_EQ(get_line(2), "IBM DOS Version 4.00");

    EXPECT_EQ(get_line(5), "A>");
}

//
// Start PC DOS version 5.02
//
TEST_F(MachineTest, pcdos_v5_02)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos5.02-720k.img");
    run("\r");
    show_screen();
    run("@3");
    show_screen();
    EXPECT_EQ(cursor_row(), 15);
    EXPECT_EQ(cursor_col(), 40);

    run("y");
    EXPECT_EQ(cursor_row(), 0);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "A>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 6);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "A>ver");

    EXPECT_EQ(get_line(2), "IBM DOS Version 5.02");
    EXPECT_EQ(get_line(3), "Revision 0");

    EXPECT_EQ(get_line(6), "A>");
}

//
// Start PC DOS version 6.30
//
TEST_F(MachineTest, pcdos_v6_30)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos6.30-1.44m.img");

    run("@5");
    //show_screen();
    EXPECT_EQ(cursor_row(), 9);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(0), "Starting PC DOS...");
    EXPECT_EQ(get_line(2), "PC DOS is bypassing your CONFIG.SYS and AUTOEXEC.BAT files.");
    EXPECT_EQ(get_line(5), "PC DOS Version 6.30");
    EXPECT_EQ(get_line(6), "             (C)Copyright International Business Machines Corp 1981-1993.");
    EXPECT_EQ(get_line(7), "             (C)Copyright Microsoft Corp 1981-1993.");
    EXPECT_EQ(get_line(9), "A:\\>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 15);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(9), "A:\\>ver");

    EXPECT_EQ(get_line(11), "PC DOS Version 6.3");
    EXPECT_EQ(get_line(12), "Revision 0");

    EXPECT_EQ(get_line(15), "A:\\>");
}

//
// Start PC DOS version 7.0
//
TEST_F(MachineTest, pcdos_v7_0_rev1)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos7.0r1-1.44m.img");

    run("@5");
    //show_screen();
    EXPECT_EQ(cursor_row(), 8);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(0), "Starting PC DOS...");
    EXPECT_EQ(get_line(2), "PC DOS is bypassing your CONFIG.SYS and AUTOEXEC.BAT files.");
    EXPECT_EQ(get_line(5), "PC DOS Version 7.00");
    EXPECT_EQ(get_line(6), "             (C)Copyright International Business Machines Corp 1981-1995.");
    EXPECT_EQ(get_line(8), "A:\\>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 14);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(10), "PC DOS Version 7.0");
    EXPECT_EQ(get_line(11), "Revision 1");

    EXPECT_EQ(get_line(14), "A:\\>");
}

//
// Start PC DOS version 7.1
//
TEST_F(MachineTest, pcdos_v7_1)
{
    machine.boot_disk(TEST_DIR "/../images/pcdos7.1-1.44m.img");

    run("@5");
    //show_screen();
    EXPECT_EQ(cursor_row(), 8);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(0), "Starting PC DOS...");
    EXPECT_EQ(get_line(2), "PC DOS is bypassing your CONFIG.SYS and AUTOEXEC.BAT files.");
    EXPECT_EQ(get_line(5), "PC DOS Version 7.10");
    EXPECT_EQ(get_line(6), "             (C)Copyright International Business Machines Corp 1981-2002.");
    EXPECT_EQ(get_line(8), "A:\\>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 14);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(10), "PC DOS Version 7.1");
    EXPECT_EQ(get_line(11), "Revision 0");

    EXPECT_EQ(get_line(14), "A:\\>");
}
