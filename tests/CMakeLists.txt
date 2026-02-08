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
    add_adc.cpp
    and_or_xor.cpp
    call_ret_jmp_loop_int.cpp
    cmp_test.cpp
    flags_nop.cpp
    in_out_esc.cpp
    inc_dec.cpp
    jump_cond.cpp
    misc_arith.cpp
    mov.cpp
    mul_div_neg_not.cpp
    pop.cpp
    push.cpp
    shift_rotate.cpp
    string.cpp
    sub_sbb.cpp
    xchg_lea_lds_les.cpp
    div_batch2.cpp
    misc_batch2.cpp
    mul_batch2.cpp
    shift_batch2.cpp
    batch3.cpp
    batch4.cpp
    ss_rep_movsw.cpp
)

#
# Check CPU instructions.
#
add_executable(unit_tests EXCLUDE_FROM_ALL ${TEST_SOURCES})
add_dependencies(unit_tests ${PROJECT_NAME})
gtest_discover_tests(unit_tests EXTRA_ARGS --gtest_repeat=1 PROPERTIES TIMEOUT 120)
