#ifndef VOXELSENGINE_SIMPLEMESHER_HPP
#define VOXELSENGINE_SIMPLEMESHER_HPP

#include <tuple>
#include <graphics/models/Chunk.hpp>
#include "IMesher.hpp"

struct Point3D { float x, y, z; };

using VertexProperty = std::pair<Point3D, Point3D>;
using MeshProperty = std::pair<Point3D, std::array<VertexProperty, 4>>;

struct SimpleMesher : public IMesher
{
    SimpleMesher(Chunk & chunk, Mesh & mesh);
    void meshing() override;

private:

    Point3D chunkOffset_;
    float ox_, oy_, oz_;
    void addCube(int x, int y, int z);
};


#endif //VOXELSENGINE_SIMPLEMESHER_HPP
