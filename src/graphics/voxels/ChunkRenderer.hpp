#ifndef VOXELSENGINE_RENDERER_HPP
#define VOXELSENGINE_RENDERER_HPP

#include <graphics/opengl/TextureArray.hpp>
#include <graphics/opengl/Shader.hpp>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Chunk.hpp"

struct Renderer
{
    explicit Renderer();
    ~Renderer();
    Renderer(const Renderer & renderer) = delete;
    Renderer & operator=(Renderer & other) = delete;
    Renderer(Renderer && other) noexcept = delete;
    Renderer & operator=(Renderer && other) noexcept = delete;


    void clear();
    void draw(std::shared_ptr<Chunk> chunk, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition);
    void bind();
    void unbind();

private:

    Shader shader_;
    TextureArray texture_;
};


#endif //VOXELSENGINE_RENDERER_HPP
