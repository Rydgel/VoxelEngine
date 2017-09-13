#ifndef VOXELSENGINE_WORLD_HPP
#define VOXELSENGINE_WORLD_HPP

#include <memory>
#include <Game.hpp>
#include <graphics/Camera.hpp>
#include <graphics/opengl/Frustum.hpp>
#include "Chunk.hpp"
#include "ChunkRenderer.hpp"

using ChunkPtr = std::shared_ptr<Chunk>;

struct World
{
    explicit World(Game & game);
    ~World();

    void update(float dt);
    void draw(float dt);

private:

    Game & game_;
    Camera camera_;
    Frustum frustum_;
    Renderer chunkRenderer_;
    std::vector<ChunkPtr> chunks_ = {};
};


#endif //VOXELSENGINE_WORLD_HPP
