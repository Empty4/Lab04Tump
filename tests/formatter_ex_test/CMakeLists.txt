cmake_minimum_required(VERSION 3.10)
project(formatter_ex_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(formatter_ex_test test_formatter_ex.cpp)

target_include_directories(formatter_ex_test PRIVATE
    ${CMAKE_SOURCE_DIR}/formatter_ex_lib/include
    ${CMAKE_SOURCE_DIR}/formatter_lib/include
)

target_link_libraries(formatter_ex_test
    GTest::gtest
    GTest::gtest_main
    formatter_ex
)

include(GoogleTest)
gtest_discover_tests(formatter_ex_test)
