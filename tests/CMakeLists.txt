#
# Download GoogleTest
#
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
enable_testing()

#
# Common includes and libraries for all tests.
#
include_directories(BEFORE ..)
link_libraries(simulator gtest_main)
add_definitions(-DTEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DBUILD_DIR="${CMAKE_BINARY_DIR}")

set(TEST_SOURCES
    machine_test.cpp
    util.cpp
)

#
# Check CPU instructions.
#
add_executable(unit_tests EXCLUDE_FROM_ALL ${TEST_SOURCES})
add_dependencies(unit_tests ${PROJECT_NAME})
gtest_discover_tests(unit_tests EXTRA_ARGS --gtest_repeat=1 PROPERTIES TIMEOUT 120)
