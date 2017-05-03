#include "Chunk.hpp"

Chunk::Chunk(int id, glm::vec3 offset)
{
    chunkId_ = id;
    offset_ = offset;

    // todo replace by air
    voxels_.fill(std::make_shared<Voxel>(VoxelType::GRASS));
}

const glm::vec3 Chunk::getOffset() const
{
    return offset_;
}
