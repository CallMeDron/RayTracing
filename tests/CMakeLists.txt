cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)

project(RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

############################################### googletest block
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)
###############################################

############################################### tests block
set(SOURCES
  test.cpp
  ../src/geometry3D/safeDouble/safeDouble.cpp
  ../src/geometry3D/point/point.cpp
  ../src/geometry3D/vector/vector.cpp
  ../src/geometry3D/line/line.cpp
)
add_executable(test ${SOURCES})
target_link_libraries(test gtest gtest_main)
###############################################