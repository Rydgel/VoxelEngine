project(VoxelsEngine)

set(HEADER_FILES
        Game.hpp
        graphics/gui/imgui_impl_glfw_gl3.h
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
        graphics/opengl/Frustum.hpp
        graphics/Camera.hpp
        graphics/InputManager.hpp
        graphics/models/Voxel.hpp
        graphics/models/Chunk.hpp
        graphics/models/World.hpp
        states/IGameState.hpp
        graphics/renderer/ChunkRenderer.hpp
        graphics/mesher/IMesher.hpp
        graphics/mesher/SimpleMesher.hpp
        utils/SimplexNoise.hpp
        graphics/models/map/MapGenerator.hpp
        graphics/models/map/MapGeneratorHeightmap.hpp
        graphics/opengl/TextureArray.hpp
        graphics/opengl/Vertex.hpp)

set(SOURCE_FILES
        Game.cpp
        graphics/gui/imgui_impl_glfw_gl3.cpp
        graphics/Window.cpp
        graphics/opengl/OpenGLError.cpp
        graphics/Timer.cpp
        graphics/opengl/Shader.cpp
        graphics/opengl/VertexArray.cpp
        graphics/opengl/Buffer.cpp
        graphics/opengl/Frustum.cpp
        graphics/Camera.cpp
        graphics/InputManager.cpp
        graphics/models/Voxel.cpp
        graphics/models/Chunk.cpp
        graphics/models/World.cpp
        states/PlayState.cpp
        graphics/renderer/ChunkRenderer.cpp
        graphics/mesher/SimpleMesher.cpp
        utils/SimplexNoise.cpp
        graphics/models/map/MapGeneratorHeightmap.cpp
        graphics/opengl/TextureArray.cpp)

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

# loading IMGUI
add_subdirectory(lib/imgui)
include_directories(lib/imgui)
target_link_libraries(VoxelsEngine ImGui)

# loading OpenAL
find_package(OpenAL REQUIRED)
if (OPENAL_FOUND)
    include_directories(${OPENAL_INCLUDE_DIR})
    target_link_libraries(VoxelsEngine ${OPENAL_LIBRARY})
endif()