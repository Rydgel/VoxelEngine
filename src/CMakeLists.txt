project(VoxelsEngine)

set(HEADER_FILES
        VoxelsEngine.hpp
        graphics/Window.hpp
        graphics/opengl/OpenGLError.hpp
        graphics/Timer.hpp
        graphics/opengl/Shader.hpp
        graphics/opengl/VertexAttribute.hpp
        graphics/opengl/VertexArray.hpp
        graphics/opengl/Buffer.hpp
        graphics/opengl/ArrayBuffer.hpp
        graphics/opengl/IndexBuffer.hpp
        graphics/opengl/Mesh.hpp
        graphics/Camera.hpp
        graphics/InputManager.hpp
        )

set(SOURCE_FILES
        VoxelsEngine.cpp
        graphics/Window.cpp
        graphics/opengl/OpenGLError.cpp
        graphics/Timer.cpp
        graphics/opengl/Shader.cpp
        graphics/opengl/VertexArray.cpp
        graphics/opengl/Buffer.cpp
        graphics/opengl/Mesh.cpp
        graphics/Camera.cpp
        graphics/InputManager.cpp
        )

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
# add_subdirectory(lib/glm-0.9.8.4)
include_directories(lib/glm-0.9.8.4)

# loading stb_image
add_subdirectory(lib/stb_image-2.14)
include_directories(lib/stb_image-2.14)
target_link_libraries(VoxelsEngine stb_image)

# loading libnoise
set(BUILD_LIBNOISE_EXAMPLES OFF)
add_subdirectory(lib/libnoise)
include_directories(lib/libnoise)
target_link_libraries(VoxelsEngine noise-static)

# loading OpenAL
find_package(OpenAL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENAL_INCLUDE_DIR})
    target_link_libraries(VoxelsEngine ${OPENAL_LIBRARY})
endif()