cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)
project(RayTracing LANGUAGES CXX)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    add_compile_options(/Zc:__cplusplus)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(ray_tracing_lib)
add_subdirectory(tests)

add_executable(main main.cpp)

target_link_libraries(main raytracing_lib)
