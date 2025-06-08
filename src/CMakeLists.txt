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

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ray_tracing_lib/safe_double/safe_double.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ray_tracing_lib/point/point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ray_tracing_lib/vector/vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ray_tracing_lib/line/line.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ray_tracing_lib/plane/plane.cpp
)

add_executable(main ${SOURCES})