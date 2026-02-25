#include "fixture.h"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "disk.h"
#include "memory.h"
#include "pc86_arch.h"

//
// Lightweight fixture for Disk-only tests (no full Machine).
//
class DiskTest : public ::testing::Test {
protected:
    Memory memory;

    std::string temp_path(const char *suffix) const
    {
        return std::string(BUILD_DIR) + "/disk_test_" + suffix;
    }
};

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

// --- DiskTest fixture tests (from DiscUtils Vhd-tests) ---

//
// DiskBuilderTest.BuildDynamic: create dynamic VHD, write at sector boundaries, read back.
//
TEST_F(DiskTest, DiskVhdBuildDynamic)
{
    const std::string path = temp_path("build_dynamic.vhd");
    const unsigned size_sectors = 32768;  // 16 MB (for 15 MB offset)

    Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);

    const unsigned buf_addr = 0x1000;
    Byte *buf = memory.get_ptr(buf_addr);

    // Write pattern at sectors 0, 2048, 4096, 6144 (1MB boundaries) and sector 30720 (15MB).
    const unsigned sectors[] = { 0, 2048, 4096, 6144, 30720 };
    for (unsigned s : sectors) {
        memset(buf, (s / 2048) & 0xFF, SECTOR_NBYTES);
        disk.memory_to_disk(s, buf_addr, SECTOR_NBYTES);
    }

    // Read back and verify.
    for (unsigned s : sectors) {
        memset(buf, 0, SECTOR_NBYTES);
        disk.disk_to_memory(s, buf_addr, SECTOR_NBYTES);
        const uint8_t expect = (s / 2048) & 0xFF;
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
            EXPECT_EQ(buf[i], expect) << " sector " << s << " offset " << i;
        }
    }

    std::filesystem::remove(path);
}

//
// DynamicStreamTest.Attributes: verify size and writability.
//
TEST_F(DiskTest, DiskVhdAttributes)
{
    const std::string path = temp_path("attributes.vhd");
    const unsigned size_sectors = 81920;  // 40 MB

    Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);

    EXPECT_EQ(disk.get_size_sectors(), size_sectors);
    EXPECT_TRUE(disk.is_writable());
    EXPECT_GT(disk.get_size_sectors() * SECTOR_NBYTES, 15u * 1024 * 1024);

    std::filesystem::remove(path);
}

//
// DynamicStreamTest.ReadWriteSmall: write 1-2 sectors, read back, persist and reopen.
//
TEST_F(DiskTest, DiskVhdReadWriteSmall)
{
    const std::string path = temp_path("readwrite_small.vhd");
    const unsigned size_sectors = 100;
    const unsigned buf_addr = 0x1000;
    Byte *buf = memory.get_ptr(buf_addr);

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);

        memset(buf, 0x42, SECTOR_NBYTES);
        disk.memory_to_disk(0, buf_addr, SECTOR_NBYTES);

        memset(buf, 0x99, SECTOR_NBYTES);
        disk.memory_to_disk(1, buf_addr, SECTOR_NBYTES);
    }

    // Reopen and verify persistence.
    {
        Disk disk(path, memory, true);

        memset(buf, 0, SECTOR_NBYTES);
        disk.disk_to_memory(0, buf_addr, SECTOR_NBYTES);
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i)
            EXPECT_EQ(buf[i], 0x42) << " sector 0 offset " << i;

        memset(buf, 0, SECTOR_NBYTES);
        disk.disk_to_memory(1, buf_addr, SECTOR_NBYTES);
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i)
            EXPECT_EQ(buf[i], 0x99) << " sector 1 offset " << i;
    }

    std::filesystem::remove(path);
}

//
// DynamicStreamTest.ReadWriteLarge: write ~3 MB across block boundaries, read back.
//
TEST_F(DiskTest, DiskVhdReadWriteLarge)
{
    const std::string path = temp_path("readwrite_large.vhd");
    const unsigned size_sectors = 8192;   // 4 MB disk
    const unsigned write_sectors = 6144;  // 3 MB
    const unsigned buf_addr = 0x1000;

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
        Byte *buf = memory.get_ptr(buf_addr);

        for (unsigned s = 0; s < write_sectors; ++s) {
            memset(buf, s & 0xFF, SECTOR_NBYTES);
            disk.memory_to_disk(s, buf_addr, SECTOR_NBYTES);
        }
    }

    {
        Disk disk(path, memory, true);
        Byte *buf = memory.get_ptr(buf_addr);

        for (unsigned s = 0; s < write_sectors; ++s) {
            memset(buf, 0, SECTOR_NBYTES);
            disk.disk_to_memory(s, buf_addr, SECTOR_NBYTES);
            const uint8_t expect = s & 0xFF;
            for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
                EXPECT_EQ(buf[i], expect) << " sector " << s << " offset " << i;
            }
        }
    }

    std::filesystem::remove(path);
}

//
// DynamicStreamTest.ReadNotPresent: unallocated blocks read as zeros.
//
TEST_F(DiskTest, DiskVhdReadUnallocatedZeros)
{
    const std::string path = temp_path("unallocated_zeros.vhd");
    const unsigned size_sectors = 8192;

    Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);

    const unsigned buf_addr = 0x1000;
    Byte *buf = memory.get_ptr(buf_addr);

    // Read from middle of disk without ever writing there.
    memset(buf, 0xFF, SECTOR_NBYTES);
    disk.disk_to_memory(4096, buf_addr, SECTOR_NBYTES);

    for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
        EXPECT_EQ(buf[i], 0) << " unallocated sector 4096 offset " << i;
    }

    std::filesystem::remove(path);
}

//
// DiskImageFileTest.FooterMissing: truncated file (footer at end missing), fallback to footer at start.
//
TEST_F(DiskTest, DiskVhdFooterMissing)
{
    const std::string path = temp_path("footer_missing.vhd");
    const unsigned size_sectors = 100;

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
        Byte *buf = memory.get_ptr(0x1000);
        memset(buf, 0xAB, SECTOR_NBYTES);
        disk.memory_to_disk(0, 0x1000, SECTOR_NBYTES);
    }

    // Truncate last 512 bytes (footer at end).
    const auto len = std::filesystem::file_size(path);
    EXPECT_EQ(truncate(path.c_str(), len - 512), 0);

    {
        Disk disk(path, memory, true);
        EXPECT_EQ(disk.get_size_sectors(), size_sectors);

        Byte *buf = memory.get_ptr(0x1000);
        memset(buf, 0, SECTOR_NBYTES);
        disk.disk_to_memory(0, 0x1000, SECTOR_NBYTES);
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
            EXPECT_EQ(buf[i], 0xAB) << " offset " << i;
        }
    }

    std::filesystem::remove(path);
}

//
// DiskTest.ConstructorDynamic: create, close, reopen; verify geometry and content.
//
TEST_F(DiskTest, DiskVhdReopenPersists)
{
    const std::string path = temp_path("reopen_persists.vhd");
    const unsigned size_sectors = 1024;
    const unsigned expected_capacity = size_sectors * SECTOR_NBYTES;

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
        Byte *buf = memory.get_ptr(0x1000);
        memset(buf, 0x77, SECTOR_NBYTES);
        disk.memory_to_disk(0, 0x1000, SECTOR_NBYTES);
    }

    {
        Disk disk(path, memory, true);
        EXPECT_GT(disk.get_size_sectors() * SECTOR_NBYTES, expected_capacity * 99 / 100);
        EXPECT_LE(disk.get_size_sectors() * SECTOR_NBYTES, expected_capacity);

        Byte *buf = memory.get_ptr(0x1000);
        memset(buf, 0, SECTOR_NBYTES);
        disk.disk_to_memory(0, 0x1000, SECTOR_NBYTES);
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
            EXPECT_EQ(buf[i], 0x77) << " offset " << i;
        }
    }

    std::filesystem::remove(path);
}

//
// DiskTest.UndisposedChangedDynamic: footer at start and end must match after close.
//
TEST_F(DiskTest, DiskVhdFooterSyncOnClose)
{
    const std::string path = temp_path("footer_sync.vhd");
    const unsigned size_sectors = 100;

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
        Byte *buf = memory.get_ptr(0x1000);
        memset(buf, 0xCD, SECTOR_NBYTES);
        disk.memory_to_disk(0, 0x1000, SECTOR_NBYTES);
    }

    std::ifstream f(path, std::ios::binary);
    uint8_t first[512], last[512];
    f.read(reinterpret_cast<char *>(first), 512);
    f.seekg(-512, std::ios::end);
    f.read(reinterpret_cast<char *>(last), 512);
    f.close();

    EXPECT_EQ(memcmp(first, last, 512), 0) << " footer at start and end must match";

    std::filesystem::remove(path);
}

//
// Read-only open: memory_to_disk on read-only file throws.
//
TEST_F(DiskTest, DiskVhdReadOnlyOpen)
{
    const std::string path = temp_path("readonly.vhd");
    const unsigned size_sectors = 100;

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
    }

    chmod(path.c_str(), 0444);

    {
        Disk disk(path, memory, true);
        Byte *buf = memory.get_ptr(0x1000);
        memset(buf, 0, SECTOR_NBYTES);
        EXPECT_THROW(disk.memory_to_disk(0, 0x1000, SECTOR_NBYTES), std::runtime_error);
    }

    chmod(path.c_str(), 0600);
    std::filesystem::remove(path);
}

//
// Sector range error: LBA beyond disk size throws.
//
TEST_F(DiskTest, DiskVhdSectorRangeError)
{
    const std::string path = temp_path("sector_range.vhd");
    const unsigned size_sectors = 100;

    Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
    Byte *buf = memory.get_ptr(0x1000);
    memset(buf, 0, SECTOR_NBYTES);

    EXPECT_THROW(disk.memory_to_disk(size_sectors, 0x1000, SECTOR_NBYTES), std::runtime_error);
    EXPECT_THROW(disk.disk_to_memory(size_sectors, 0x1000, SECTOR_NBYTES), std::runtime_error);

    std::filesystem::remove(path);
}

//
// Write sector fill: write_sector_fill for VHD, verify zeros.
//
TEST_F(DiskTest, DiskVhdWriteSectorFill)
{
    const std::string path = temp_path("sector_fill.vhd");
    const unsigned size_sectors = 100;
    const unsigned buf_addr = 0x1000;

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
        Byte *buf = memory.get_ptr(buf_addr);
        memset(buf, 0x11, SECTOR_NBYTES);
        disk.memory_to_disk(0, buf_addr, SECTOR_NBYTES);
    }

    {
        Disk disk(path, memory, true);
        disk.write_sector_fill(0, 1, 0x55);  // VHD always writes zeros
    }

    {
        Disk disk(path, memory, true);
        Byte *buf = memory.get_ptr(buf_addr);
        memset(buf, 0xFF, SECTOR_NBYTES);
        disk.disk_to_memory(0, buf_addr, SECTOR_NBYTES);
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i) {
            EXPECT_EQ(buf[i], 0) << " write_sector_fill for VHD writes zeros, offset " << i;
        }
    }

    std::filesystem::remove(path);
}

//
// Multi-block write: sectors in block 0 and block 1, read back.
//
TEST_F(DiskTest, DiskVhdMultiBlockWrite)
{
    const std::string path = temp_path("multi_block.vhd");
    // Block size 2MB = 4096 sectors; write in block 0 and block 1.
    const unsigned size_sectors = 8192;
    const unsigned buf_addr = 0x1000;

    {
        Disk disk(path, memory, ImageFormat::VhdDynamic, size_sectors);
        Byte *buf = memory.get_ptr(buf_addr);

        memset(buf, 0x01, SECTOR_NBYTES);
        disk.memory_to_disk(0, buf_addr, SECTOR_NBYTES);

        memset(buf, 0x02, SECTOR_NBYTES);
        disk.memory_to_disk(4096, buf_addr, SECTOR_NBYTES);
    }

    {
        Disk disk(path, memory, true);
        Byte *buf = memory.get_ptr(buf_addr);

        memset(buf, 0, SECTOR_NBYTES);
        disk.disk_to_memory(0, buf_addr, SECTOR_NBYTES);
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i)
            EXPECT_EQ(buf[i], 0x01) << " block 0 offset " << i;

        memset(buf, 0, SECTOR_NBYTES);
        disk.disk_to_memory(4096, buf_addr, SECTOR_NBYTES);
        for (unsigned i = 0; i < SECTOR_NBYTES; ++i)
            EXPECT_EQ(buf[i], 0x02) << " block 1 offset " << i;
    }

    std::filesystem::remove(path);
}
