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
