set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)

set(TEST_SOURCES
    edge.cpp 
    line.cpp
    plane.cpp
    point.cpp
    polygon.cpp
    safe_double.cpp
    vector.cpp
)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests PRIVATE raytracing_lib gtest gtest_main)

target_include_directories(tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../ray_tracing_lib
)
