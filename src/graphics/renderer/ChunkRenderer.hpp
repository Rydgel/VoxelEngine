#ifndef VOXELSENGINE_RENDERER_HPP
#define VOXELSENGINE_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "graphics/opengl/TextureArray.hpp"
#include "graphics/opengl/Shader.hpp"
#include "graphics/models/Chunk.hpp"

struct ChunkRenderer
{
    explicit ChunkRenderer();
    ~ChunkRenderer();
    ChunkRenderer(const ChunkRenderer & renderer) = delete;
    ChunkRenderer & operator=(ChunkRenderer & other) = delete;
    ChunkRenderer(ChunkRenderer && other) noexcept = delete;
    ChunkRenderer & operator=(ChunkRenderer && other) noexcept = delete;

    void bind();
    void draw(std::shared_ptr<Chunk> chunk, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition);
    void unbind();

private:

    Shader shader_;
    TextureArray texture_;
};


#endif //VOXELSENGINE_RENDERER_HPP
