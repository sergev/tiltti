# MOO parser utility (C++17, zlib for gzip)
find_package(ZLIB REQUIRED)

add_executable(moo8086
    main.cpp
    moo_parser.cpp
    test_case.cpp
    print.cpp
    emit_gtest.cpp
    run.cpp
)
include_directories(BEFORE ..)
target_link_libraries(moo8086 PRIVATE simulator ${CAPSTONE_STATIC_LDFLAGS} ZLIB::ZLIB)
