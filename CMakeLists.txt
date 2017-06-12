cmake_minimum_required(VERSION 3.8)
project(VoxelsEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic-errors -Werr -Wall -Wextra -O3 -ffast-math")

include(cotire)

include_directories(src)
include_directories(src/lib/glad)
include_directories(src/lib/optional)
add_subdirectory(src)
add_subdirectory(tests)

set(SOURCE_FILES app/main.cpp)
add_executable(VoxelsEngine_run ${SOURCE_FILES})
target_link_libraries(VoxelsEngine_run VoxelsEngine)
cotire(VoxelsEngine_run)

file(COPY src/graphics/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}.)
file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}.)