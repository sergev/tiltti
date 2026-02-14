# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(tiltti VERSION 0.1 DESCRIPTION "PC i86 Simulator")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Werror -Wshadow)
if(APPLE)
    add_compile_options(-fcolor-diagnostics)
endif()

include(FindPkgConfig)
pkg_check_modules(CAPSTONE REQUIRED capstone)

#
# TODO: Enable cppcheck by default
#
#find_program(Cppcheck NAMES cppcheck)
#if(NOT (Cppcheck MATCHES "NOTFOUND"))
#    message(STATUS "Found Cppcheck: ${Cppcheck}")
#    set(CMAKE_CXX_CPPCHECK "${Cppcheck}"
#        "--std=c++17"
#        "--enable=style"
#        "--check-level=exhaustive"
#        "--error-exitcode=1" # Fail on any issues
#        "--inline-suppr" # Enable inline control like // cppcheck-suppress "id"
#        "--quiet" # No progress report messages
#        "--suppress=badBitmaskCheck" # Allow redundant zero operands
#        "--suppress=*:*/_deps/*" # Ignore issues in Googletest
#        "--library=${CMAKE_SOURCE_DIR}/tests/googletest.xml" # Parse TEST() macro properly
#    )
#endif()

# Build library
add_library(simulator STATIC
    pc86_arch.cpp
    machine.cpp
    memory.cpp
    disk.cpp
    trace.cpp
    processor.cpp
    syscall.cpp
    encoding.cpp
    cp437.cpp
    int10_video.cpp
    int13_disk.cpp
    int14_serial.cpp
    int15_system.cpp
    int16_keyboard.cpp
    int17_printer.cpp
    int1a_rtc_timer.cpp
)

# Build executable file
add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CAPSTONE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} simulator ${CAPSTONE_LIBRARIES})

# Build image of Basic ROM.
add_dependencies(${PROJECT_NAME} generate_basic_rom_h)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/basic_rom.h
    COMMAND xxd -i -n basic_rom ${CMAKE_CURRENT_SOURCE_DIR}/images/ibm-basic-1.10.rom > ${CMAKE_CURRENT_SOURCE_DIR}/basic_rom.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/images/ibm-basic-1.10.rom
    COMMENT "Generating basic_rom.h"
    VERBATIM
)
add_custom_target(generate_basic_rom_h DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/basic_rom.h)

# Get git commit hash and revision count
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE GIT_HASH
)
execute_process(
    COMMAND git rev-list HEAD --count
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE GIT_REVCOUNT
)
set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS
    -DVERSION_STRING=\\"${CMAKE_PROJECT_VERSION}.${GIT_REVCOUNT}-${GIT_HASH}\\"
)

install(TARGETS
    ${PROJECT_NAME}
    DESTINATION bin
)

add_subdirectory(moo_booth)
add_subdirectory(tests)
