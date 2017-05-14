#include <graphics/voxels/Chunk.hpp>
#include "SimpleMesher.hpp"

SimpleMesher::SimpleMesher(Chunk & chunk, Mesh & mesh)
: IMesher(chunk, mesh)
{

}

void SimpleMesher::meshing()
{
    for (int x = 0; x < Chunk::chunkWidth; x ++)
    for (int y = 0; y < Chunk::chunkHeight; y ++)
    for (int z = 0; z < Chunk::chunkDepth; z ++) {
        // block culling
        if (chunk_.voxelIsHidden(x, y, z)) {
            continue;
        }

        addCube(x, y, z);
    }
}

void SimpleMesher::addCube(int x, int y, int z)
{
    auto chunkOffset = chunk_.getOffset();
    auto ox = chunkOffset.x;
    auto oy = chunkOffset.y;
    auto oz = chunkOffset.z;

    // We need to add the 6 faces of cube
    // We add a face only if it touches a transparent element

    // back
    if (chunk_.isAir(x, y, z - 1)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.getPositions().size());
        mesh_.addPosition({ox + x + 1, oy + y, oz + z});
        mesh_.addPosition({ox + x, oy + y, oz + z});
        mesh_.addPosition({ox + x, oy + y + 1, oz + z});
        mesh_.addPosition({ox + x + 1, oy + y + 1, oz + z});

        mesh_.addNormal({0, 0, -1});
        mesh_.addNormal({0, 0, -1});
        mesh_.addNormal({0, 0, -1});
        mesh_.addNormal({0, 0, -1});

        int textureOffset = 0;
        mesh_.addUvs({1, 1, textureOffset + 0});
        mesh_.addUvs({0, 1, textureOffset + 0});
        mesh_.addUvs({0, 0, textureOffset + 0});
        mesh_.addUvs({1, 0, textureOffset + 0});

        mesh_.addIndices(indicesSize);
        mesh_.addIndices(indicesSize + 1);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 3);
        mesh_.addIndices(indicesSize);
    }

    // right
    if (chunk_.isAir(x + 1, y, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.getPositions().size());
        mesh_.addPosition({ox + x + 1, oy + y, oz + z + 1});
        mesh_.addPosition({ox + x + 1, oy + y, oz + z});
        mesh_.addPosition({ox + x + 1, oy + y + 1, oz + z});
        mesh_.addPosition({ox + x + 1, oy + y + 1, oz + z + 1});

        mesh_.addNormal({1, 0, 0});
        mesh_.addNormal({1, 0, 0});
        mesh_.addNormal({1, 0, 0});
        mesh_.addNormal({1, 0, 0});

        int textureOffset = 0;
        mesh_.addUvs({1, 1, textureOffset + 0});
        mesh_.addUvs({0, 1, textureOffset + 0});
        mesh_.addUvs({0, 0, textureOffset + 0});
        mesh_.addUvs({1, 0, textureOffset + 0});

        mesh_.addIndices(indicesSize);
        mesh_.addIndices(indicesSize + 1);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 3);
        mesh_.addIndices(indicesSize);
    }

    // front
    if (chunk_.isAir(x, y, z + 1)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.getPositions().size());
        mesh_.addPosition({ox + x, oy + y, oz + z + 1});
        mesh_.addPosition({ox + x + 1, oy + y, oz + z + 1});
        mesh_.addPosition({ox + x + 1, oy + y + 1, oz + z + 1});
        mesh_.addPosition({ox + x, oy + y + 1, oz + z + 1});

        mesh_.addNormal({0, 0, 1});
        mesh_.addNormal({0, 0, 1});
        mesh_.addNormal({0, 0, 1});
        mesh_.addNormal({0, 0, 1});

        int textureOffset = 0;
        mesh_.addUvs({1, 1, textureOffset + 0});
        mesh_.addUvs({0, 1, textureOffset + 0});
        mesh_.addUvs({0, 0, textureOffset + 0});
        mesh_.addUvs({1, 0, textureOffset + 0});

        mesh_.addIndices(indicesSize);
        mesh_.addIndices(indicesSize + 1);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 3);
        mesh_.addIndices(indicesSize);
    }

    // left
    if (chunk_.isAir(x - 1, y, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.getPositions().size());
        mesh_.addPosition({ox + x, oy + y, oz + z});
        mesh_.addPosition({ox + x, oy + y, oz + z + 1});
        mesh_.addPosition({ox + x, oy + y + 1, oz + z + 1});
        mesh_.addPosition({ox + x, oy + y + 1, oz + z});

        mesh_.addNormal({-1, 0, 0});
        mesh_.addNormal({-1, 0, 0});
        mesh_.addNormal({-1, 0, 0});
        mesh_.addNormal({-1, 0, 0});

        int textureOffset = 0;
        mesh_.addUvs({1, 1, textureOffset + 0});
        mesh_.addUvs({0, 1, textureOffset + 0});
        mesh_.addUvs({0, 0, textureOffset + 0});
        mesh_.addUvs({1, 0, textureOffset + 0});

        mesh_.addIndices(indicesSize);
        mesh_.addIndices(indicesSize + 1);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 3);
        mesh_.addIndices(indicesSize);
    }

    // top
    if (chunk_.isAir(x, y + 1, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.getPositions().size());
        mesh_.addPosition({ox + x, oy + y + 1, oz + z + 1});
        mesh_.addPosition({ox + x + 1, oy + y + 1, oz + z + 1});
        mesh_.addPosition({ox + x + 1, oy + y + 1, oz + z});
        mesh_.addPosition({ox + x, oy + y + 1, oz + z});

        mesh_.addNormal({0, 1, 0});
        mesh_.addNormal({0, 1, 0});
        mesh_.addNormal({0, 1, 0});
        mesh_.addNormal({0, 1, 0});

        int textureOffset = 0;
        mesh_.addUvs({1, 1, textureOffset + 2});
        mesh_.addUvs({0, 1, textureOffset + 2});
        mesh_.addUvs({0, 0, textureOffset + 2});
        mesh_.addUvs({1, 0, textureOffset + 2});

        mesh_.addIndices(indicesSize);
        mesh_.addIndices(indicesSize + 1);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 3);
        mesh_.addIndices(indicesSize);
    }

    // bottom
    if (chunk_.isAir(x, y - 1, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.getPositions().size());
        mesh_.addPosition({ox + x, oy + y, oz + z});
        mesh_.addPosition({ox + x + 1, oy + y, oz + z});
        mesh_.addPosition({ox + x + 1, oy + y, oz + z + 1});
        mesh_.addPosition({ox + x, oy + y, oz + z + 1});

        mesh_.addNormal({0, -1, 0});
        mesh_.addNormal({0, -1, 0});
        mesh_.addNormal({0, -1, 0});
        mesh_.addNormal({0, -1, 0});

        int textureOffset = 0;
        mesh_.addUvs({1, 1, textureOffset + 1});
        mesh_.addUvs({0, 1, textureOffset + 1});
        mesh_.addUvs({0, 0, textureOffset + 1});
        mesh_.addUvs({1, 0, textureOffset + 1});

        mesh_.addIndices(indicesSize);
        mesh_.addIndices(indicesSize + 1);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 2);
        mesh_.addIndices(indicesSize + 3);
        mesh_.addIndices(indicesSize);
    }
}

