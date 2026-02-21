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
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.00");
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
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.00");
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
    run("");
    EXPECT_EQ(cursor_row(), 0);
    EXPECT_EQ(cursor_col(), 0);

    run("@3y");
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
