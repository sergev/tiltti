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
include_directories(BEFORE . ..)
link_libraries(simulator gtest_main ${CAPSTONE_STATIC_LDFLAGS})
add_definitions(-DTEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DBUILD_DIR="${CMAKE_BINARY_DIR}")

set(TEST_SOURCES
    test8086.cpp
    bda_offsets_test.cpp
    8086/machine_test.cpp
    8086/video_test.cpp
    8086/add_adc.cpp
    8086/and_or_xor.cpp
    8086/call_ret_jmp_loop_int.cpp
    8086/cmp_test.cpp
    8086/flags_nop.cpp
    8086/in_out_esc.cpp
    8086/inc_dec.cpp
    8086/jump_cond.cpp
    8086/misc_arith.cpp
    8086/mov.cpp
    8086/mul_div_neg_not.cpp
    8086/pop.cpp
    8086/push.cpp
    8086/shift_rotate.cpp
    8086/string.cpp
    8086/sub_sbb.cpp
    8086/xchg_lea_lds_les.cpp
    8086/div_batch2.cpp
    8086/misc_batch2.cpp
    8086/mul_batch2.cpp
    8086/shift_batch2.cpp
    8086/batch3.cpp
    8086/batch4.cpp
    8086/ss_rep_movsw.cpp
    8086/batch5.cpp
    8086/batch6.cpp
    8086/batch7.cpp
    8086/daa_das.cpp
    8086/batch17.cpp
    8086/am88.cpp
    8086/msdos_test.cpp
    8086/drdos_test.cpp
    8086/pcdos_test.cpp
    8086/cpm_test.cpp
    8086/disk_test.cpp

    test386.cpp
    386/a_test.cpp
    386/b_test.cpp
    386/c_test.cpp
    386/d_test.cpp
    386/e_test.cpp
    386/f_test.cpp
    386/i_test.cpp
    386/j_test.cpp
    386/l_test.cpp
    386/m_test.cpp
    386/n_test.cpp
    386/o_test.cpp
    386/p_test.cpp
    386/r_test.cpp
    386/s_test.cpp
    386/t_test.cpp
    386/x_test.cpp
    386/batch2.cpp
    386/batch3.cpp
    386/batch4.cpp
    386/batch5.cpp
    386/string_test.cpp
    386/batch6.cpp
    386/batch7.cpp
)

#
# Check CPU instructions.
#
add_executable(unit_tests EXCLUDE_FROM_ALL ${TEST_SOURCES})
add_dependencies(unit_tests ${PROJECT_NAME})
gtest_discover_tests(unit_tests EXTRA_ARGS --gtest_repeat=1 PROPERTIES TIMEOUT 5)
