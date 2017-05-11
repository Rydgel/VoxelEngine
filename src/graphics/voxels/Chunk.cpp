#include <graphics/mesher/SimpleMesher.hpp>
#include "Chunk.hpp"

Chunk::Chunk(int id, glm::vec3 offset)
{
    chunkId_ = id;
    offset_ = offset;

    mesherPtr_ = std::make_unique<SimpleMesher>(*this, chunkMesh_);
    // todo replace by air
    voxels_.fill(std::make_shared<Voxel>(VoxelType::AIR));
    mapGen_ = std::make_unique<MapGeneratorHeightmap>(id);
    mapGen_->makeChunk(*this);
}

const glm::vec3 & Chunk::getOffset() const
{
    return offset_;
}

const MaybeVoxel Chunk::getVoxel(int x, int y, int z) const
{
    if (x < 0 || x >= Chunk::chunkWidth) {
        return boost::nullopt;
    }
    if (y < 0 || y >= Chunk::chunkHeight) {
        return boost::nullopt;
    }
    if (z < 0 || z >= Chunk::chunkDepth) {
        return boost::nullopt;
    }

    auto index = x + y * Chunk::chunkWidth + z * Chunk::chunkWidth * Chunk::chunkHeight;

    if (index < 0 || index >= Chunk::chunkSize) {
        return boost::nullopt;
    }

    return voxels_[index];
}

bool Chunk::isAir(int x, int y, int z) const
{
    MaybeVoxel voxel = getVoxel(x, y, z);
    if (voxel) {
        if (voxel->get()->getType() == VoxelType::AIR) {
            return true;
        }
    } else {
        // out of bound
        return true;
    }

    return false;
}

bool Chunk::voxelIsHidden(int x, int y, int z) const
{
    if (isAir(x, y, z)) return true;
    // Here we check is the block is surrounded by other blocks
    // If the block is touching an edge or air, then we should draw it
    if (x - 1 < 0 || x - 1 >= Chunk::chunkWidth) return false;
    if (y - 1 < 0 || y - 1 >= Chunk::chunkHeight) return false;
    if (z - 1 < 0 || z - 1 >= Chunk::chunkDepth) return false;
    if (x + 1 < 0 || x + 1 >= Chunk::chunkWidth) return false;
    if (y + 1 < 0 || y + 1 >= Chunk::chunkHeight) return false;
    if (z + 1 < 0 || z + 1 >= Chunk::chunkDepth) return false;

    if (isAir(x - 1, y, z)) return false;
    if (isAir(x + 1, y, z)) return false;
    if (isAir(x, y - 1, z)) return false;
    if (isAir(x, y + 1, z)) return false;
    if (isAir(x, y, z - 1)) return false;

    return !isAir(x, y, z + 1);
}

void Chunk::fill(Voxel voxel, int x, int y, int z)
{
    auto index = x + y * Chunk::chunkWidth + z * Chunk::chunkWidth * Chunk::chunkHeight;
    voxels_[index] = std::make_shared<Voxel>(voxel);
    needMeshing = true;
}

void Chunk::meshing()
{
    mesherPtr_->meshing();

    /**
    // back
    chunkMesh_.addPosition({1, 0, 0});
    chunkMesh_.addPosition({0, 0, 0});
    chunkMesh_.addPosition({0, 1, 0});
    chunkMesh_.addPosition({1, 1, 0});

    // right
    chunkMesh_.addPosition({1, 0, 1});
    chunkMesh_.addPosition({1, 0, 0});
    chunkMesh_.addPosition({1, 1, 0});
    chunkMesh_.addPosition({1, 1, 1});

    // front
    chunkMesh_.addPosition({0, 0, 1});
    chunkMesh_.addPosition({1, 0, 1});
    chunkMesh_.addPosition({1, 1, 1});
    chunkMesh_.addPosition({0, 1, 1});

    // left
    chunkMesh_.addPosition({0, 0, 0});
    chunkMesh_.addPosition({0, 0, 1});
    chunkMesh_.addPosition({0, 1, 1});
    chunkMesh_.addPosition({0, 1, 0});

    // top
    chunkMesh_.addPosition({0, 1, 1});
    chunkMesh_.addPosition({1, 1, 1});
    chunkMesh_.addPosition({1, 1, 0});
    chunkMesh_.addPosition({0, 1, 0});

    // bottom
    chunkMesh_.addPosition({0, 0, 0});
    chunkMesh_.addPosition({1, 0, 0});
    chunkMesh_.addPosition({1, 0, 1});
    chunkMesh_.addPosition({0, 0, 1}); */


    vertexArray_.bind();

    positionsBuffer_.setData(chunkMesh_.getPositions(), Usage::Static);
    normalsBuffer_.setData(chunkMesh_.getNormals(), Usage::Static);
    // colorsBuffer_.setData(chunkMesh_.getColors(), Usage::Static);
    indicesBuffer_.setData(chunkMesh_.getIndices(), Usage::Static);

    glEnableVertexAttribArray(0);
    positionsBuffer_.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    glEnableVertexAttribArray(1);
    normalsBuffer_.bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    unbind();

    needMeshing = false;
}

void Chunk::bind()
{
    vertexArray_.bind();
    indicesBuffer_.bind();
    normalsBuffer_.bind();
    positionsBuffer_.bind();
}

void Chunk::unbind()
{
    indicesBuffer_.unbind();
    normalsBuffer_.unbind();
    positionsBuffer_.unbind();
    vertexArray_.unbind();
}

void Chunk::draw()
{
    if (needMeshing) {
        meshing();
    }

    bind();
    auto indicesSize = static_cast<GLsizei>(chunkMesh_.getIndices().size());
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, chunkMesh_.getPositions().size());
    unbind();
}