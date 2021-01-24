#include "graphics/models/Chunk.hpp"
#include "SimpleMesher.hpp"

inline static Point3D convertGLMToPoint(glm::vec3 vec)
{
    return { vec.x, vec.y, vec.z };
}

SimpleMesher::SimpleMesher(Chunk & chunk, Mesh & mesh)
: IMesher(chunk, mesh)
{
    chunkOffset_ = convertGLMToPoint(chunk_.getOffset());
    ox_ = chunkOffset_.x;
    oy_ = chunkOffset_.y;
    oz_ = chunkOffset_.z;
}

constexpr std::array<MeshProperty, 6> meshingProperties = { // NOLINT
        // Back
        MeshProperty {
            { 0, 0, -1 },
            {
                VertexProperty { { 1, 0, 0 }, { 1, 1, 0 } },
                VertexProperty { { 0, 0, 0 }, { 0, 1, 0 } },
                VertexProperty { { 0, 1, 0 }, { 0, 0, 0 } },
                VertexProperty { { 1, 1, 0 }, { 1, 0, 0 } }
            }
        },
        // Right
        MeshProperty {
            { 1, 0, 0 },
            {
                VertexProperty { { 1, 0, 1 }, { 1, 1, 0 } },
                VertexProperty { { 1, 0, 0 }, { 0, 1, 0 } },
                VertexProperty { { 1, 1, 0 }, { 0, 0, 0 } },
                VertexProperty { { 1, 1, 1 }, { 1, 0, 0 } }
            }
        },
        // Front
        MeshProperty {
            { 0, 0, 1 },
            {
                VertexProperty { { 0, 0, 1 }, { 1, 1, 0 } },
                VertexProperty { { 1, 0, 1 }, { 0, 1, 0 } },
                VertexProperty { { 1, 1, 1 }, { 0, 0, 0 } },
                VertexProperty { { 0, 1, 1 }, { 1, 0, 0 } }
            }
        },
        // Left
        MeshProperty {
            { -1, 0, 0 },
            {
                VertexProperty { { 0, 0, 0 }, { 1, 1, 0 } },
                VertexProperty { { 0, 0, 1 }, { 0, 1, 0 } },
                VertexProperty { { 0, 1, 1 }, { 0, 0, 0 } },
                VertexProperty { { 0, 1, 0 }, { 1, 0, 0 } }
            }
        },
        // Top
        MeshProperty {
            { 0, 1, 0 },
            {
                VertexProperty { { 0, 1, 1 }, { 1, 1, 2 } },
                VertexProperty { { 1, 1, 1 }, { 0, 1, 2 } },
                VertexProperty { { 1, 1, 0 }, { 0, 0, 2 } },
                VertexProperty { { 0, 1, 0 }, { 1, 0, 2 } }
            }
        },
        // Bottom
        MeshProperty {
            { 0, -1, 0 },
            {
                VertexProperty { { 0, 0, 0 }, { 1, 1, 1 } },
                VertexProperty { { 1, 0, 0 }, { 0, 1, 1 } },
                VertexProperty { { 1, 0, 1 }, { 0, 0, 1 } },
                VertexProperty { { 0, 0, 1 }, { 1, 0, 1 } }
            }
        },
};

void SimpleMesher::meshing()
{
    for (int x = 0; x < Chunk::chunkWidth; x ++) {
        for (int y = 0; y < Chunk::chunkHeight; y ++) {
            for (int z = 0; z < Chunk::chunkDepth; z ++) {
                // block culling
                if (!chunk_.voxelIsHidden(x, y, z)) {
                    addCube(x, y, z);
                }
            }
        }
    }
}

void SimpleMesher::addCube(int x, int y, int z)
{
    // todo this must change based on Voxel type
    float textureOffset = 0.f;

    // We need to add the 6 faces of cube
    for (auto [normal, verticesProps] : meshingProperties) {
        auto [xn, yn, zn] = normal;
        // We add a face only if it touches a transparent element
        auto indicesOff = mesh_.verticesSize();
        if (chunk_.isAir(x + static_cast<int>(xn), y + static_cast<int>(yn), z + static_cast<int>(zn))) {
            for (auto [off1, off2] : verticesProps) {
                auto [off1x, off1y, off1z] = off1;
                auto [off2x, off2y, off2z] = off2;
                auto xf = static_cast<float>(x);
                auto yf = static_cast<float>(y);
                auto zf = static_cast<float>(z);

                mesh_.vertices.push_back(
                    {
                        { ox_ + xf + off1x, oy_ + yf + off1y, oz_ + zf + off1z       },
                        { x,               y,               z                     },
                        { off2x,           off2y,           textureOffset + off2z }
                    }
                );
            }

            for (auto dSize : { 0, 1, 2, 2, 3, 0 })
                mesh_.indices.push_back(indicesOff + dSize);
        }
    }
}

