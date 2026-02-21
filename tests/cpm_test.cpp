#include "fixture.h"

//
// Start CP/M version 1.1
//
TEST_F(MachineTest, cpm_v1_1)
{
    machine.boot_disk(TEST_DIR "/../images/cpm1.1-320k.img");
    run("");
    EXPECT_EQ(cursor_row(), 13);
    EXPECT_EQ(cursor_col(), 2);
    EXPECT_EQ(get_line(0), "Loading CPM.SYS.");

    EXPECT_EQ(get_line(2), "CP/M-86 for the IBM PC and IBM PC XT  Version 1.1");
    EXPECT_EQ(get_line(3), "Copyright (C) 1983, Digital Research");

    EXPECT_EQ(get_line(6), "Hardware Supported :");

    EXPECT_EQ(get_line(8), "          Diskette Drive(s) : 1");
    EXPECT_EQ(get_line(9), "                Memory (Kb) : 640");
    EXPECT_EQ(get_line(10), "                M:Disk (Kb) : 128");

    EXPECT_EQ(get_line(13), "A>");
}
