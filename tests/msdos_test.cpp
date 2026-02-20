#include "fixture.h"

//
// Start MS-DOS version 1.25
//
TEST_F(MachineTest, msdos_v1_25)
{
    machine.boot_disk(TEST_DIR "/../images/msdos1.25-320k.img");
    run();
    EXPECT_EQ(cursor_row(), 1);
    EXPECT_EQ(cursor_col(), 16);
    EXPECT_EQ(get_line(0), "Current date is Tue  1-01-1980");
    EXPECT_EQ(get_line(1), "Enter new date:");
}
