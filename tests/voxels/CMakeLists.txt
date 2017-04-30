include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(VoxelsEngineTests
        voxels_tests.cpp)

target_link_libraries(VoxelsEngineTests gtest gtest_main)
target_link_libraries(VoxelsEngineTests VoxelsEngine)