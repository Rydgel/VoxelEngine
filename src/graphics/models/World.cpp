#include "World.hpp"

World::World(Game & game)
: game_(game)
, camera_(game_.getInputManager())
{
    chunks_.push_back(std::make_shared<Chunk>(1, glm::vec3(0, 0, 0)));
    chunks_.push_back(std::make_shared<Chunk>(2, glm::vec3(0, 0, 64)));
    chunks_.push_back(std::make_shared<Chunk>(3, glm::vec3(0, 0, -64)));
    chunks_.push_back(std::make_shared<Chunk>(4, glm::vec3(64, 0, 0)));
    chunks_.push_back(std::make_shared<Chunk>(5, glm::vec3(-64, 0, 0)));
    chunks_.push_back(std::make_shared<Chunk>(6, glm::vec3(64, 0, 64)));
    chunks_.push_back(std::make_shared<Chunk>(7, glm::vec3(64, 0, -64)));
    chunks_.push_back(std::make_shared<Chunk>(8, glm::vec3(-64, 0, 64)));
    chunks_.push_back(std::make_shared<Chunk>(9, glm::vec3(-64, 0, -64)));

    chunks_.push_back(std::make_shared<Chunk>(10, glm::vec3(0, 0, -128)));
    chunks_.push_back(std::make_shared<Chunk>(11, glm::vec3(128, 0, 0)));
    chunks_.push_back(std::make_shared<Chunk>(12, glm::vec3(-128, 0, 0)));
    chunks_.push_back(std::make_shared<Chunk>(13, glm::vec3(128, 0, 128)));
    chunks_.push_back(std::make_shared<Chunk>(14, glm::vec3(128, 0, -128)));
    chunks_.push_back(std::make_shared<Chunk>(15, glm::vec3(-128, 0, 128)));
    chunks_.push_back(std::make_shared<Chunk>(16, glm::vec3(-128, 0, -128)));
    chunks_.push_back(std::make_shared<Chunk>(432, glm::vec3(0, 0, 128)));

    chunks_.push_back(std::make_shared<Chunk>(17, glm::vec3(64, 0, -128)));
    chunks_.push_back(std::make_shared<Chunk>(18, glm::vec3(128, 0, 64)));
    chunks_.push_back(std::make_shared<Chunk>(19, glm::vec3(-128, 0, 64)));
    chunks_.push_back(std::make_shared<Chunk>(20, glm::vec3(-64, 0, 128)));
    chunks_.push_back(std::make_shared<Chunk>(21, glm::vec3(128, 0, -64)));
    chunks_.push_back(std::make_shared<Chunk>(22, glm::vec3(64, 0, 128)));
    chunks_.push_back(std::make_shared<Chunk>(23, glm::vec3(-64, 0, -128)));
    chunks_.push_back(std::make_shared<Chunk>(24, glm::vec3(-128, 0, -64)));

    chunkRenderer_.bind();
}

World::~World()
{
    chunkRenderer_.unbind();
}

void World::update(const float dt)
{
    camera_.update(dt);
}

void World::draw(const float dt)
{
    auto view = camera_.getViewMatrix();
    auto projection = glm::perspective(camera_.getZoom(), 1920.0f / 1080.0f, 0.1f, 500.0f);
    frustum_.CalculateFrustum(projection, view);
    auto cameraPosition = camera_.getPosition();

    // draw each chunks
    for (auto & chunkPtr : chunks_) {
        auto pos = chunkPtr->getOffset();
        auto size = glm::vec3(Chunk::chunkWidth, Chunk::chunkHeight, Chunk::chunkDepth);
        if (frustum_.CubeInFrustum(pos, size)) {
            chunkRenderer_.draw(chunkPtr, view, projection, cameraPosition);
        }
    }
}
