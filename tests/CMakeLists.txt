# Указываем минимально необходимую версию CMake
cmake_minimum_required(VERSION 3.14)

# Включаем новую политику CMP0135
cmake_policy(SET CMP0135 NEW)

# Объявляем проект с именем RayTracing и указываем, что используем C++
project(RayTracing LANGUAGES CXX)

# Если используем компилятор MSVC (Visual Studio)
if(MSVC)
    # Настраиваем использование динамической версии стандартной библиотеки времени выполнения (MultiThreaded DLL)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)

# Требуем, чтобы стандарт был именно C++17, без понижения
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Отключаем расширения компилятора (например, Microsoft-specific extensions)
set(CMAKE_CXX_EXTENSIONS OFF)

# Создаем статическую или динамическую библиотеку raytracing_lib из перечисленных исходных файлов
add_library(raytracing_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracing_lib/safe_double/safe_double.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracing_lib/point/point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracing_lib/vector/vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/ray_tracing_lib/line/line.cpp
)

# Добавляем каталог с заголовочными файлами в пути поиска для raytracing_lib (публично)
target_include_directories(raytracing_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Принудительно заставляем GoogleTest использовать динамическую версию CRT (для MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Добавляем поддиректорию с исходниками GoogleTest
add_subdirectory(googletest)

# Создаем исполняемый файл tests из файла tests.cpp
add_executable(tests tests.cpp)

# Линкуем тесты с библиотекой raytracing_lib и GoogleTest
target_link_libraries(tests PRIVATE raytracing_lib gtest gtest_main)
