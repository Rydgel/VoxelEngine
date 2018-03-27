#include "graphics/mesher/SimpleMesher.hpp"
#include "Chunk.hpp"

Chunk::Chunk(int id, glm::vec3 offset)
{
    chunkId_ = id;
    offset_ = offset;

    mesherPtr_ = std::make_unique<SimpleMesher>(*this, chunkMesh_);
    voxels_.fill(std::make_shared<Voxel>(VoxelType::AIR));

    // generating terrain
    MapGeneratorHeightmap mapGen_(id);
    mapGen_.makeChunk(*this);
}

const glm::vec3 & Chunk::getOffset() const
{
    return offset_;
}

const MaybeVoxel Chunk::getVoxel(int x, int y, int z) const
{
    if (x < 0 || x >= Chunk::chunkWidth) {
        return std::nullopt;
    }
    if (y < 0 || y >= Chunk::chunkHeight) {
        return std::nullopt;
    }
    if (z < 0 || z >= Chunk::chunkDepth) {
        return std::nullopt;
    }

    auto index = x + y * Chunk::chunkWidth + z * Chunk::chunkWidth * Chunk::chunkHeight;

    if (index < 0 || index >= Chunk::chunkSize) {
        return std::nullopt;
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

    vertexArray_.bind();

    verticesBuffer_.setData(chunkMesh_.vertices, Usage::Static);
    // reduce memory usage
    chunkMesh_.vertices.clear();
    chunkMesh_.vertices.shrink_to_fit();

    indicesBuffer_.setData(chunkMesh_.indices, Usage::Static);
    indicesSize = static_cast<int>(chunkMesh_.indices.size());
    // reduce memory usage
    chunkMesh_.indices.clear();
    chunkMesh_.indices.shrink_to_fit();

    verticesBuffer_.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normals));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, uvs));

    verticesBuffer_.unbind();
    indicesBuffer_.unbind();
    vertexArray_.unbind();

    needMeshing = false;
}

void Chunk::bind()
{
    vertexArray_.bind();
    indicesBuffer_.bind();
}

void Chunk::unbind()
{
    indicesBuffer_.unbind();
    vertexArray_.unbind();
}

void Chunk::draw()
{
    if (needMeshing) {
        meshing();
    }

    bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
    unbind();
}