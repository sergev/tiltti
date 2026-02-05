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
link_libraries(simulator gtest_main ${CAPSTONE_LIBRARIES})
add_definitions(-DTEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DBUILD_DIR="${CMAKE_BINARY_DIR}")

set(TEST_SOURCES
    fixture.cpp
    machine_test.cpp
    add_adc_test.cpp
    and_or_xor_test.cpp
    call_ret_test.cpp
    cmp_test_test.cpp
    esc_test.cpp
    in_out_test.cpp
    inc_dec_test.cpp
    int_test.cpp
    jump_cond_test.cpp
    jump_loop_test.cpp
    misc_test.cpp
    mov_test.cpp
    mul_div_neg_not_test.cpp
    pop_test.cpp
    push_test.cpp
    shift_rotate_test.cpp
    string_test.cpp
    sub_sbb_test.cpp
    xchg_test.cpp
)

#
# Check CPU instructions.
#
add_executable(unit_tests EXCLUDE_FROM_ALL ${TEST_SOURCES})
add_dependencies(unit_tests ${PROJECT_NAME})
gtest_discover_tests(unit_tests EXTRA_ARGS --gtest_repeat=1 PROPERTIES TIMEOUT 120)
