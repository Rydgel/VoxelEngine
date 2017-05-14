#ifndef VOXELSENGINE_CHUNK_HPP
#define VOXELSENGINE_CHUNK_HPP

#include <array>
#include <glm/vec3.hpp>
#include <graphics/opengl/Mesh.hpp>
#include <graphics/opengl/VertexArray.hpp>
#include <graphics/opengl/ArrayBuffer.hpp>
#include <graphics/opengl/IndexBuffer.hpp>
#include <optional.hpp>
#include <graphics/mesher/IMesher.hpp>
#include <graphics/voxels/map/MapGeneratorHeightmap.hpp>
#include "Voxel.hpp"

class MapGeneratorHeightmap;

namespace boost = std::experimental;
using MaybeVoxel = boost::optional<std::shared_ptr<Voxel>>;
using VoxelPtr = std::shared_ptr<Voxel>;

struct Chunk
{
    auto static constexpr chunkWidth = 32;
    auto static constexpr chunkHeight = 32;
    auto static constexpr chunkDepth = 32;
    auto static constexpr chunkSize = chunkWidth * chunkHeight * chunkDepth;

    bool needMeshing = true;

    Chunk(int id, glm::vec3 offset);
    const glm::vec3 & getOffset() const;
    const MaybeVoxel getVoxel(int x, int y, int z) const;
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
    std::unique_ptr<MapGeneratorHeightmap> mapGen_;

    Mesh chunkMesh_;
    std::unique_ptr<IMesher> mesherPtr_;
    VertexArray vertexArray_;
    ArrayBuffer positionsBuffer_;
    ArrayBuffer normalsBuffer_;
    ArrayBuffer uvsBuffer_;
    IndexBuffer indicesBuffer_;
};


#endif //VOXELSENGINE_CHUNK_HPP
