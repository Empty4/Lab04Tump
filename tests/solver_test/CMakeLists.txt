cmake_minimum_required(VERSION 3.10)
project(solver_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(solver_test test_solver.cpp)

target_include_directories(solver_test PRIVATE
    ${CMAKE_SOURCE_DIR}/solver_lib/include
)

target_link_libraries(solver_test
    GTest::gtest
    GTest::gtest_main
    solver_lib
)

include(GoogleTest)
gtest_discover_tests(solver_test)
