#ifndef VOXELSENGINE_CHUNK_HPP
#define VOXELSENGINE_CHUNK_HPP

#include <array>
#include <optional>
#include <memory>
#include <glm/vec3.hpp>
#include "graphics/opengl/Mesh.hpp"
#include "graphics/opengl/VertexArray.hpp"
#include "graphics/opengl/ArrayBuffer.hpp"
#include "graphics/opengl/IndexBuffer.hpp"
#include "graphics/mesher/IMesher.hpp"
#include "graphics/models/map/MapGeneratorHeightmap.hpp"
#include "Voxel.hpp"

class MapGeneratorHeightmap;

using VoxelPtr = std::shared_ptr<Voxel>;
using MaybeVoxel = std::optional<VoxelPtr>;

struct Chunk
{
    auto static constexpr chunkWidth = 64;
    auto static constexpr chunkHeight = 32;
    auto static constexpr chunkDepth = 64;
    auto static constexpr chunkSize = chunkWidth * chunkHeight * chunkDepth;

    bool needMeshing = true;
    int indicesSize = 0;

    Chunk(int id, glm::vec3 offset);
    const glm::vec3 & getOffset() const;
    MaybeVoxel getVoxel(int x, int y, int z) const;
    bool isAir(int x, int y, int z) const;
    bool voxelIsHidden(int x, int y, int z) const;
    void fill(Voxel voxel, int x, int y, int z);
    void meshing();
    void bind();
    void unbind();
    void draw();

private:

    int chunkId_;
    glm::vec3 offset_;
    std::array<VoxelPtr, chunkSize> voxels_ {};

    Mesh chunkMesh_;
    std::unique_ptr<IMesher> mesherPtr_;
    VertexArray vertexArray_;
    ArrayBuffer verticesBuffer_;
    IndexBuffer indicesBuffer_;
};


#endif //VOXELSENGINE_CHUNK_HPP
