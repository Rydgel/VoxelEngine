#include "World.hpp"

World::World(Game & game)
: game_(game)
, camera_(game_.getInputManager())
{
    chunks_.push_back(std::make_unique<Chunk>(1, glm::vec3(0, 0, 0)));
    renderer_.bind();
}

World::~World()
{
    renderer_.unbind();
}

void World::update(const float dt)
{
    camera_.update(dt);
}

void World::draw(const float dt)
{
    glm::mat4 view = camera_.getViewMatrix();
    glm::mat4 projection = glm::perspective(camera_.getZoom(), 1200.0f / 800.0f, 0.1f, 500.0f);
    frustum_.CalculateFrustum(projection, view);

    // draw each chunks
    for (auto & chunkPtr : chunks_) {
        // todo if chunk is in frustum then draw it
        renderer_.draw(chunkPtr, view, projection);
    }
}
