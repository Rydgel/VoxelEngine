#include "graphics/opengl/OpenGLError.hpp"
#include "ChunkRenderer.hpp"

ChunkRenderer::ChunkRenderer()
: shader_("shaders/default.vert", "shaders/default.frag")
{
    // todo refactor that in a texture table to remove duplicates
    std::vector<std::string> paths = {
            "resources/blocks/grass_side.png",
            "resources/blocks/dirt.png",
            "resources/blocks/wool_colored_green.png",
            "resources/blocks/dirt.png",
            "resources/blocks/dirt.png",
            "resources/blocks/dirt.png",
            "resources/blocks/stone.png",
            "resources/blocks/stone.png",
            "resources/blocks/stone.png",
    };

    texture_.add(paths);
}

ChunkRenderer::~ChunkRenderer()
{
    unbind();
}

void ChunkRenderer::draw(std::shared_ptr<Chunk> chunk, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition)
{
    auto pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 model;
    model = glm::translate(model, pos);
    shader_.setUniform("model", model);
    shader_.setUniform("view", view);
    shader_.setUniform("projection", projection);
    // glm::vec3 lightPosLoc(30.0f, 10.0f, 0.0f);
    // glm::vec3 lightColorLoc(1.0f, 1.0f, 1.0f);
    // shader_.setUniform("lightColor", lightColorLoc);
    // shader_.setUniform("lightPos", lightPosLoc);
    // shader_.setUniform("viewPos", cameraPosition);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    chunk->draw();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // shader_.setUniform("colorDraw", glm::vec4(0, 0, 0, 1));
    // chunk->draw();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // OpenGLError errorGL;
    // errorGL.isOpenGLError();
}

void ChunkRenderer::bind()
{
    shader_.bind();
    texture_.bind();
}

void ChunkRenderer::unbind()
{
    shader_.unbind();
    texture_.unbind();
}
