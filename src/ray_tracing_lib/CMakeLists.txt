set(RAY_TRACING_LIB_SOURCES
    safe_double.cpp
    point.cpp
    vector.cpp
    line.cpp
    plane.cpp
    polygon.cpp
)

add_library(raytracing_lib STATIC ${RAY_TRACING_LIB_SOURCES})

target_include_directories(raytracing_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
