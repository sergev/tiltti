#include "fixture.h"

//
// Output one character via Int 10h syscall, and check result in video memory.
//
TEST_F(MachineTest, TeletypeOutput)
{
    Byte const ch = 'Q';
    Byte *base    = memory.get_ptr(0xb8000);

    EXPECT_NE(base[0], ch);

    // Output a character.
    cpu.set_al(ch);
    machine.int10_teletype_output();

    // Check result in video memory.
    EXPECT_EQ(base[0], ch);
}
