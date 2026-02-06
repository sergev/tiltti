# MOO parser utility (C++17, zlib for gzip)
find_package(ZLIB REQUIRED)

add_executable(moo-booth
    main.cpp
    moo_parser.cpp
    test_case.cpp
    print.cpp
    emit_gtest.cpp
    run.cpp
)
target_link_libraries(moo-booth PRIVATE ZLIB::ZLIB)
