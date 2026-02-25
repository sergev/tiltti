#include "fixture.h"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <sys/wait.h>

#include "disk.h"
#include "pc86_arch.h"

//
// Create VHD with new constructor, write sector 0, read back, verify.
//
TEST_F(MachineTest, DiskCreateVhdWriteRead)
{
    const std::string path = std::string(BUILD_DIR) + "/disk_create_test.vhd";
    const unsigned size_sectors = 81920;  // 40 MB

    Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);

    EXPECT_EQ(disk.get_size_sectors(), size_sectors);
    EXPECT_TRUE(disk.is_writable());

    const unsigned buf_addr = 0x1000;
    Byte *buf = memory.get_ptr(buf_addr);

    // Fill sector with pattern and write.
    memset(buf, 0x55, SECTOR_NBYTES);
    disk.memory_to_disk(0, buf_addr, SECTOR_NBYTES);

    // Clear buffer and read back.
    memset(buf, 0, SECTOR_NBYTES);
    disk.disk_to_memory(0, buf_addr, SECTOR_NBYTES);

    for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
        EXPECT_EQ(buf[i], 0x55) << " at offset " << i;
    }

    // Verify created VHD opens in QEMU.
    const int r = std::system(("qemu-img info " + path + " > /dev/null 2>&1").c_str());
    EXPECT_EQ(WEXITSTATUS(r), 0) << "qemu-img info failed; VHD may be invalid";

    std::filesystem::remove(path);
}

//
// Create raw image, write sector 0, read back, verify.
//
TEST_F(MachineTest, DiskCreateRawWriteRead)
{
    const std::string path = std::string(BUILD_DIR) + "/disk_create_test_raw.img";
    const unsigned size_sectors = 2880;  // 1.44 MB floppy

    Disk disk(path, memory, ImageFormat::Raw, size_sectors);

    EXPECT_EQ(disk.get_size_sectors(), size_sectors);

    const unsigned buf_addr = 0x2000;
    Byte *buf = memory.get_ptr(buf_addr);

    memset(buf, 0xAA, SECTOR_NBYTES);
    disk.memory_to_disk(0, buf_addr, SECTOR_NBYTES);

    memset(buf, 0, SECTOR_NBYTES);
    disk.disk_to_memory(0, buf_addr, SECTOR_NBYTES);

    for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
        EXPECT_EQ(buf[i], 0xAA) << " at offset " << i;
    }

    std::filesystem::remove(path);
}
