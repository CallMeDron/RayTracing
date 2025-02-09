cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)

project(RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

############################################### main block
set(SOURCES
    main.cpp
    geometry3D/safeDouble/safeDouble.cpp
    geometry3D/point/point.cpp
    geometry3D/vector/vector.cpp
    geometry3D/line/line.cpp
)
add_executable(main ${SOURCES})
###############################################