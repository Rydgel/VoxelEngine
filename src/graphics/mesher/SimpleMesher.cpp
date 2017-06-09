#include <graphics/voxels/Chunk.hpp>
#include "SimpleMesher.hpp"

SimpleMesher::SimpleMesher(Chunk & chunk, Mesh & mesh)
: IMesher(chunk, mesh)
{

}

void SimpleMesher::meshing()
{
    for (int x = 0; x < Chunk::chunkWidth; x ++) {
        for (int y = 0; y < Chunk::chunkHeight; y ++) {
            for (int z = 0; z < Chunk::chunkDepth; z ++) {
                // block culling
                if (chunk_.voxelIsHidden(x, y, z)) {
                    continue;
                }

                addCube(x, y, z);
            }
        }
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
        auto const indicesSize = static_cast<GLuint>(mesh_.vertices.size());

        int textureOffset = 0;
        mesh_.vertices.push_back({{ox + x + 1, oy + y, oz + z}, {0, 0, -1}, {1, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x, oy + y, oz + z}, {0, 0, -1}, {0, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x, oy + y + 1, oz + z}, {0, 0, -1}, {0, 0, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y + 1, oz + z}, {0, 0, -1}, {1, 0, textureOffset + 0}});

        mesh_.indices.push_back(indicesSize);
        mesh_.indices.push_back(indicesSize + 1);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 3);
        mesh_.indices.push_back(indicesSize);
    }

    // right
    if (chunk_.isAir(x + 1, y, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.vertices.size());

        int textureOffset = 0;

        mesh_.vertices.push_back({{ox + x + 1, oy + y, oz + z + 1}, {1, 0, 0}, {1, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y, oz + z}, {1, 0, 0}, {0, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y + 1, oz + z}, {1, 0, 0}, {0, 0, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y + 1, oz + z + 1}, {1, 0, 0}, {1, 0, textureOffset + 0}});

        mesh_.indices.push_back(indicesSize);
        mesh_.indices.push_back(indicesSize + 1);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 3);
        mesh_.indices.push_back(indicesSize);
    }

    // front
    if (chunk_.isAir(x, y, z + 1)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.vertices.size());

        int textureOffset = 0;

        mesh_.vertices.push_back({{ox + x, oy + y, oz + z + 1}, {0, 0, 1}, {1, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y, oz + z + 1}, {0, 0, 1}, {0, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y + 1, oz + z + 1}, {0, 0, 1}, {0, 0, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x, oy + y + 1, oz + z + 1}, {0, 0, 1}, {1, 0, textureOffset + 0}});

        mesh_.indices.push_back(indicesSize);
        mesh_.indices.push_back(indicesSize + 1);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 3);
        mesh_.indices.push_back(indicesSize);
    }

    // left
    if (chunk_.isAir(x - 1, y, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.vertices.size());

        int textureOffset = 0;

        mesh_.vertices.push_back({{ox + x, oy + y, oz + z}, {-1, 0, 0}, {1, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x, oy + y, oz + z + 1}, {-1, 0, 0}, {0, 1, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x, oy + y + 1, oz + z + 1}, {-1, 0, 0}, {0, 0, textureOffset + 0}});
        mesh_.vertices.push_back({{ox + x, oy + y + 1, oz + z}, {-1, 0, 0}, {1, 0, textureOffset + 0}});

        mesh_.indices.push_back(indicesSize);
        mesh_.indices.push_back(indicesSize + 1);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 3);
        mesh_.indices.push_back(indicesSize);
    }

    // top
    if (chunk_.isAir(x, y + 1, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.vertices.size());

        int textureOffset = 0;

        mesh_.vertices.push_back({{ox + x, oy + y + 1, oz + z + 1}, {0, 1, 0}, {1, 1, textureOffset + 2}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y + 1, oz + z + 1}, {0, 1, 0}, {0, 1, textureOffset + 2}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y + 1, oz + z}, {0, 1, 0}, {0, 0, textureOffset + 2}});
        mesh_.vertices.push_back({{ox + x, oy + y + 1, oz + z}, {0, 1, 0}, {1, 0, textureOffset + 2}});

        mesh_.indices.push_back(indicesSize);
        mesh_.indices.push_back(indicesSize + 1);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 3);
        mesh_.indices.push_back(indicesSize);
    }

    // bottom
    if (chunk_.isAir(x, y - 1, z)) {
        auto const indicesSize = static_cast<GLuint>(mesh_.vertices.size());

        int textureOffset = 0;

        mesh_.vertices.push_back({{ox + x, oy + y, oz + z}, {0, -1, 0}, {1, 1, textureOffset + 1}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y, oz + z}, {0, -1, 0}, {0, 1, textureOffset + 1}});
        mesh_.vertices.push_back({{ox + x + 1, oy + y, oz + z + 1}, {0, -1, 0}, {0, 0, textureOffset + 1}});
        mesh_.vertices.push_back({{ox + x, oy + y, oz + z + 1}, {0, -1, 0}, {1, 0, textureOffset + 1}});

        mesh_.indices.push_back(indicesSize);
        mesh_.indices.push_back(indicesSize + 1);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 2);
        mesh_.indices.push_back(indicesSize + 3);
        mesh_.indices.push_back(indicesSize);
    }
}

