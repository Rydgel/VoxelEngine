project(VoxelsEngine)

set(HEADER_FILES
        VoxelsEngine.hpp
        )

set(SOURCE_FILES
        VoxelsEngine.cpp)

add_library(VoxelsEngine STATIC ${SOURCE_FILES} ${HEADER_FILES})

# loading fmt library
add_subdirectory(lib/fmt-3.0.1)
target_link_libraries(VoxelsEngine fmt)

# loading glad
add_subdirectory(lib/glad)
target_link_libraries(VoxelsEngine glad)
include_directories(lib/glad)

# loading glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw-3.2.1)
target_link_libraries(VoxelsEngine glfw)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(VoxelsEngine ${OPENGL_gl_LIBRARY})
endif()

# loading glm
include_directories(lib/glm-0.9.8.4)

# loading OpenAL
find_package(OpenAL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENAL_INCLUDE_DIR})
    target_link_libraries(VoxelsEngine ${OPENAL_LIBRARY})
endif()