#ifndef VOXELSENGINE_IMESHER_HPP
#define VOXELSENGINE_IMESHER_HPP

struct Mesh;
struct Chunk;

struct IMesher
{
    IMesher(Chunk & chunk, Mesh & mesh):
            chunk_(chunk), mesh_(mesh) { }

    virtual void meshing() = 0;

protected:

    Chunk & chunk_;
    Mesh & mesh_;
};

#endif //VOXELSENGINE_IMESHER_HPP
