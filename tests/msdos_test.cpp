#include "fixture.h"

//
// Start MS-DOS version 1.12
//
TEST_F(MachineTest, msdos_v1_12)
{
    machine.boot_disk(TEST_DIR "/../images/msdos1.25-320k.img");
    run("\r\r");
    EXPECT_EQ(cursor_row(), 13);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "Current date is Tue  1-01-1980");
    EXPECT_EQ(get_line(1), "Enter new date:");
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.00");
    EXPECT_EQ(get_line(3), "Enter new time:");

    EXPECT_EQ(get_line(5), "The COMPAQ Personal Computer DOS");
    EXPECT_EQ(get_line(6), "Version 1.12");

    EXPECT_EQ(get_line(9), "(C) Copyright COMPAQ Computer Corp. 1982, 83");
    EXPECT_EQ(get_line(10), "(C) Copyright Microsoft 1981, 82");

    EXPECT_EQ(get_line(13), "A>");
}

//
// Start MS-DOS version 2.12
//
TEST_F(MachineTest, msdos_v2_12)
{
    machine.boot_disk(TEST_DIR "/../images/msdos2.12-360k.img");
    run("\r\r");
    EXPECT_EQ(cursor_row(), 12);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "Current date is Tue  1-01-1980");
    EXPECT_EQ(get_line(1), "Enter new date:");
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.00");
    EXPECT_EQ(get_line(3), "Enter new time:");

    EXPECT_EQ(get_line(6), "The COMPAQ Personal Computer MS-DOS");
    EXPECT_EQ(get_line(7), "Version 2.12");

    EXPECT_EQ(get_line(9), "(C) Copyright COMPAQ Computer Corp. 1982, 83, 84");
    EXPECT_EQ(get_line(10), "(C) Copyright Microsoft 1981, 82, 83");

    EXPECT_EQ(get_line(12), "A>");
}

//
// Start MS-DOS version 3.31
//
TEST_F(MachineTest, msdos_v3_31)
{
    machine.boot_disk(TEST_DIR "/../images/msdos3.31-1.44m.img");
    run("\r\r");
    EXPECT_EQ(cursor_row(), 10);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "Current date is Tue  1-01-1980");
    EXPECT_EQ(get_line(1), "Enter new date (mm-dd-yy):");
    EXPECT_EQ(get_line(2), "Current time is  0:00:00.00");
    EXPECT_EQ(get_line(3), "Enter new time:");

    EXPECT_EQ(get_line(6), "Microsoft(R) MS-DOS(R)  Version 3.31");
    EXPECT_EQ(get_line(7), "             (C)Copyright Microsoft Corp 1981-1987");

    EXPECT_EQ(get_line(10), "A>");
}

//
// Start MS-DOS version 6.22
//
TEST_F(MachineTest, msdos_v6_22)
{
    machine.boot_disk(TEST_DIR "/../images/msdos6.22-1.44m.img");

    run("");
    show_screen();
    EXPECT_EQ(cursor_row(), 18);
    EXPECT_EQ(cursor_col(), 40);
    EXPECT_EQ(get_line(1), " Microsoft MS-DOS 6.22 Setup");
    EXPECT_EQ(get_line(17), "          │   \a To exit Setup, press F3.                              │");

    // Press F3 twice to exit Setup.
    run("@3@3");
    EXPECT_EQ(cursor_row(), 0);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(0), "A:\\>");

    run("ver\r");
    EXPECT_EQ(cursor_row(), 5);
    EXPECT_EQ(cursor_col(), 4);
    EXPECT_EQ(get_line(2), "MS-DOS Version 6.22");
    EXPECT_EQ(get_line(5), "A:\\>");
}
