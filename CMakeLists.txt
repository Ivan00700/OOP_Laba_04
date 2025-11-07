cmake_minimum_required(VERSION 3.10)
project(Lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исходники программы
add_executable(lab4
    src/main.cpp
)

# Указываем папку с заголовками
include_directories(${PROJECT_SOURCE_DIR}/src)

# Подключение GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Исполняемый файл для тестов
add_executable(test_figure
    test/test_figure.cpp
)

target_link_libraries(test_figure ${GTEST_LIBRARIES} pthread)
add_test(NAME test_figure COMMAND test_figure)
