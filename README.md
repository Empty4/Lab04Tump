# Lab04Tump

Вы продолжаете проходить стажировку в "Formatter Inc." (см подробности).

В прошлый раз ваше задание заключалось в настройке автоматизированной системы CMake.

Сейчас вам требуется настроить систему непрерывной интеграции для библиотек и приложений, с которыми вы работали в прошлый раз. Настройте сборочные процедуры на различных платформах:

    используйте TravisCI для сборки на операционной системе Linux с использованием компиляторов gcc и clang;
    используйте AppVeyor для сборки на операционной системе Windows.
```bash
┌──(kali㉿empty4)-[~/empty4]
└─$ cd ~/empty4/lab04
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ cp -r ../lab03/formatter_lib ../lab03/formatter_ex_lib ../lab03/solver_lib ../lab03/hello_world ../lab03/solver .
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ find . -type f -name "*.hpp" -o -name "*.cpp" -o -name "*.h" | sort
./formatter_ex_lib/formatter_ex.cpp
./formatter_ex_lib/formatter_ex.h
./formatter_ex_lib/include/formatter_ex.hpp
./formatter_ex_lib/src/formatter_ex.cpp
./formatter_lib/formatter.cpp
./formatter_lib/formatter.h
./formatter_lib/include/formatter.hpp
./formatter_lib/src/formatter.cpp
./hello_world/src/hello_world.cpp
./solver_lib/include/solver.hpp
./solver_lib/solver.cpp
./solver_lib/solver.h
./solver_lib/src/solver.cpp
./solver/src/equation.cpp
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ sudo apt update && sudo apt install -y libgtest-dev libgmock-dev cmake g++ make
Сущ:1 http://http.kali.org/kali kali-rolling InRelease
Может быть обновлён 281 пакет. Запустите «apt list --upgradable» для показа.
Уже установлен пакет libgtest-dev самой новой версии (1.17.0-1).  
Уже установлен пакет libgmock-dev самой новой версии (1.17.0-1).
Уже установлен пакет cmake самой новой версии (4.1.1+really3.31.6-1).
Уже установлен пакет g++ самой новой версии (4:14.2.0-1).
Уже установлен пакет make самой новой версии (4.4.1-2).
Следующие пакеты устанавливались автоматически и больше не требуются:
  libqt5ct-common1.8  linux-image-6.12.25-amd64  python3-pyinstaller-hooks-contrib
  libsigsegv2         python3-packaging-whl      python3-wheel-whl
Для их удаления используйте «sudo apt autoremove».

Сводка:
  Обновление: 0, Установка: 0, Удаление: 0, Пропуск обновления: 281

┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ mkdir -p tests/formatter_test tests/formatter_ex_test tests/solver_test 
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ cd tests/formatter_test
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/formatter_test]
└─$ cat > test_formatter.cpp << 'EOF'
#include <gtest/gtest.h>
#include <formatter.hpp>

TEST(FormatterTest, BasicFormatting) {
    EXPECT_EQ(formatter::format("hello"), "hello");
}

TEST(FormatterTest, EmptyString) {
    EXPECT_EQ(formatter::format(""), "");
}

TEST(FormatterTest, StringWithSpaces) {
    EXPECT_EQ(formatter::format("hello world"), "hello world");
}
EOF
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/formatter_test]
└─$ cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.10)
project(formatter_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(formatter_test test_formatter.cpp)

target_include_directories(formatter_test PRIVATE
    ${CMAKE_SOURCE_DIR}/formatter_lib/include
)

target_link_libraries(formatter_test
    GTest::gtest
    GTest::gtest_main
    formatter
)

include(GoogleTest)
gtest_discover_tests(formatter_test)
EOF
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/formatter_test]
└─$ cd ../formatter_ex_test
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/formatter_ex_test]
└─$ cat > test_formatter_ex.cpp << 'EOF'
#include <gtest/gtest.h>
#include <formatter_ex.hpp>

TEST(FormatterExTest, BasicFormatting) {
    EXPECT_EQ(formatter_ex::format("hello"), "[hello]");
}

TEST(FormatterExTest, EmptyString) {
    EXPECT_EQ(formatter_ex::format(""), "[]");
}

TEST(FormatterExTest, StringWithSpaces) {
    EXPECT_EQ(formatter_ex::format("hello world"), "[hello world]");
}
EOF
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/formatter_ex_test]
└─$ cat > CMakeLists.txt << 'EOF'       
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
EOF
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/formatter_ex_test]
└─$ cd ../solver_test
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/solver_test]
└─$ cat > test_solver.cpp << 'EOF'
#include <gtest/gtest.h>
#include <solver.hpp>

TEST(SolverTest, BasicEquation) {
    EXPECT_DOUBLE_EQ(solve_equation(2.0, 4.0), -2.0);
}

TEST(SolverTest, ZeroACoefficient) {
    EXPECT_DOUBLE_EQ(solve_equation(0.0, 4.0), 0.0);
}

TEST(SolverTest, NegativeCoefficients) {
    EXPECT_DOUBLE_EQ(solve_equation(-2.0, -4.0), -2.0);
}

TEST(SolverTest, FractionalResult) {
    EXPECT_DOUBLE_EQ(solve_equation(4.0, 2.0), -0.5);
}
EOF
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/solver_test]
└─$ cat > CMakeLists.txt << 'EOF'
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
EOF
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/tests/solver_test]
└─$ cd ../..                     
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.10)
project(lab04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение поддержки тестирования
enable_testing()

# Основные библиотеки
add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)

# Приложения из lab03
add_subdirectory(hello_world)
add_subdirectory(solver)

# Тесты
add_subdirectory(tests/formatter_test)
add_subdirectory(tests/formatter_ex_test)
add_subdirectory(tests/solver_test)

# Установочные пути
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install CACHE PATH "Installation directory" FORCE)
endif()
EOF
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ mkdir build
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04]
└─$ cd build
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/build]
└─$ cmake .. -DBUILD_TESTING=ON
-- The CXX compiler identification is GNU 14.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- The C compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found GTest: /usr/lib/x86_64-linux-gnu/cmake/GTest/GTestConfig.cmake (found version "1.17.0")
-- Configuring done (1.0s)
-- Generating done (0.0s)
CMake Warning:
  Manually-specified variables were not used by the project:                                                       
                                                                                                                   
    BUILD_TESTING                                                                                                  
                                                                                                                   
                                                                                                                   
-- Build files have been written to: /home/kali/empty4/lab04/build
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/build]
└─$ make -j$(nproc)
[  6%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/src/solver.cpp.o
[ 12%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/src/formatter.cpp.o
[ 18%] Linking CXX static library ../lib/libsolver_lib.a
[ 25%] Linking CXX static library ../lib/libformatter.a
[ 25%] Built target formatter
[ 25%] Built target solver_lib
[ 31%] Building CXX object tests/formatter_test/CMakeFiles/formatter_test.dir/test_formatter.cpp.o
[ 37%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/src/formatter_ex.cpp.o
[ 43%] Linking CXX static library ../lib/libformatter_ex.a
[ 43%] Built target formatter_ex
[ 50%] Building CXX object tests/solver_test/CMakeFiles/solver_test.dir/test_solver.cpp.o
[ 56%] Linking CXX executable formatter_test
[ 62%] Linking CXX executable solver_test
[ 62%] Built target formatter_test
[ 68%] Building CXX object hello_world/CMakeFiles/hello_world.dir/src/hello_world.cpp.o
[ 68%] Built target solver_test
[ 75%] Building CXX object solver/CMakeFiles/solver.dir/src/equation.cpp.o
[ 81%] Linking CXX executable hello_world
[ 87%] Linking CXX executable solver
[ 87%] Built target hello_world
[ 93%] Building CXX object tests/formatter_ex_test/CMakeFiles/formatter_ex_test.dir/test_formatter_ex.cpp.o
[ 93%] Built target solver
[100%] Linking CXX executable formatter_ex_test
[100%] Built target formatter_ex_test
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/build]
└─$ ctest --output-on-failure
Test project /home/kali/empty4/lab04/build
      Start  1: FormatterTest.BasicFormatting
 1/10 Test  #1: FormatterTest.BasicFormatting ......   Passed    0.01 sec
      Start  2: FormatterTest.EmptyString
 2/10 Test  #2: FormatterTest.EmptyString ..........   Passed    0.00 sec
      Start  3: FormatterTest.StringWithSpaces
 3/10 Test  #3: FormatterTest.StringWithSpaces .....   Passed    0.00 sec
      Start  4: FormatterExTest.BasicFormatting
 4/10 Test  #4: FormatterExTest.BasicFormatting ....   Passed    0.00 sec
      Start  5: FormatterExTest.EmptyString
 5/10 Test  #5: FormatterExTest.EmptyString ........   Passed    0.00 sec
      Start  6: FormatterExTest.StringWithSpaces
 6/10 Test  #6: FormatterExTest.StringWithSpaces ...   Passed    0.00 sec
      Start  7: SolverTest.BasicEquation
 7/10 Test  #7: SolverTest.BasicEquation ...........   Passed    0.00 sec
      Start  8: SolverTest.ZeroACoefficient
 8/10 Test  #8: SolverTest.ZeroACoefficient ........   Passed    0.00 sec
      Start  9: SolverTest.NegativeCoefficients
 9/10 Test  #9: SolverTest.NegativeCoefficients ....   Passed    0.00 sec
      Start 10: SolverTest.FractionalResult
10/10 Test #10: SolverTest.FractionalResult ........   Passed    0.00 sec

100% tests passed, 0 tests failed out of 10

Total Test time (real) =   0.05 sec
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/build]
└─$ ./hello_world/hello_world
[hello, world!]
                                                                                                                   
┌──(kali㉿empty4)-[~/empty4/lab04/build]
└─$ ./solver/solver
[Solution: x = -2.000000]
                                                                                                                   
```
