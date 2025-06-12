set(RAY_TRACING_LIB_SOURCES
    angle.cpp
    camera.cpp
    line.cpp
    plane.cpp
    point.cpp
    polygon.cpp
    polyhedron.cpp
    safe_double.cpp
    vector.cpp
)

add_library(raytracing_lib STATIC ${RAY_TRACING_LIB_SOURCES})

target_include_directories(raytracing_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
