#include "World.hpp"

World::World(Game & game)
: game_(game)
, camera_(game_.getInputManager())
{
    chunks_.push_back(std::make_unique<Chunk>(1, glm::vec3(0, 0, 0)));
    chunks_.push_back(std::make_unique<Chunk>(2, glm::vec3(0, 0, 32)));
    chunks_.push_back(std::make_unique<Chunk>(3, glm::vec3(0, 0, -32)));
    chunks_.push_back(std::make_unique<Chunk>(4, glm::vec3(32, 0, 0)));
    chunks_.push_back(std::make_unique<Chunk>(5, glm::vec3(-32, 0, 0)));
    chunks_.push_back(std::make_unique<Chunk>(6, glm::vec3(32, 0, 32)));
    chunks_.push_back(std::make_unique<Chunk>(7, glm::vec3(32, 0, -32)));
    chunks_.push_back(std::make_unique<Chunk>(8, glm::vec3(-32, 0, 32)));
    chunks_.push_back(std::make_unique<Chunk>(9, glm::vec3(-32, 0, -32)));

    chunks_.push_back(std::make_unique<Chunk>(10, glm::vec3(0, 0, -64)));
    chunks_.push_back(std::make_unique<Chunk>(11, glm::vec3(64, 0, 0)));
    chunks_.push_back(std::make_unique<Chunk>(12, glm::vec3(-64, 0, 0)));
    chunks_.push_back(std::make_unique<Chunk>(13, glm::vec3(64, 0, 64)));
    chunks_.push_back(std::make_unique<Chunk>(14, glm::vec3(64, 0, -64)));
    chunks_.push_back(std::make_unique<Chunk>(15, glm::vec3(-64, 0, 64)));
    chunks_.push_back(std::make_unique<Chunk>(16, glm::vec3(-64, 0, -64)));
    chunks_.push_back(std::make_unique<Chunk>(432, glm::vec3(0, 0, 64)));

    chunks_.push_back(std::make_unique<Chunk>(17, glm::vec3(32, 0, -64)));
    chunks_.push_back(std::make_unique<Chunk>(18, glm::vec3(64, 0, 32)));
    chunks_.push_back(std::make_unique<Chunk>(19, glm::vec3(-64, 0, 32)));
    chunks_.push_back(std::make_unique<Chunk>(20, glm::vec3(-32, 0, 64)));
    chunks_.push_back(std::make_unique<Chunk>(21, glm::vec3(64, 0, -32)));
    chunks_.push_back(std::make_unique<Chunk>(22, glm::vec3(32, 0, 64)));
    chunks_.push_back(std::make_unique<Chunk>(23, glm::vec3(-32, 0, -64)));
    chunks_.push_back(std::make_unique<Chunk>(24, glm::vec3(-64, 0, -32)));

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
    auto cameraPosition = camera_.getPosition();

    // draw each chunks
    for (auto & chunkPtr : chunks_) {
        auto pos = chunkPtr->getOffset();
        auto size = glm::vec3(Chunk::chunkWidth, Chunk::chunkHeight, Chunk::chunkDepth);
        if (frustum_.CubeInFrustum(pos, size)) {
            renderer_.draw(chunkPtr, view, projection, cameraPosition);
        }
    }
}
