#ifndef VOXELSENGINE_CHUNK_HPP
#define VOXELSENGINE_CHUNK_HPP

#include <array>
#include <glm/vec3.hpp>
#include <graphics/opengl/Mesh.hpp>
#include "Voxel.hpp"

using VoxelPtr = std::shared_ptr<Voxel>;

struct Chunk
{
    auto static constexpr chunkWidth = 64;
    auto static constexpr chunkHeight = 64;
    auto static constexpr chunkDepth = 64;
    auto static constexpr chunkSize = chunkWidth * chunkHeight * chunkDepth;

    Chunk(int id, glm::vec3 offset);
    const glm::vec3 getOffset() const;

private:

    int chunkId_;
    bool needMeshing = true;
    glm::vec3 offset_;
    std::array<VoxelPtr, chunkSize> voxels_ {};
    Mesh chunkMesh_;
};


#endif //VOXELSENGINE_CHUNK_HPP
