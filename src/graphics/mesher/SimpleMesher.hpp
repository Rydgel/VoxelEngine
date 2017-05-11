#ifndef VOXELSENGINE_SIMPLEMESHER_HPP
#define VOXELSENGINE_SIMPLEMESHER_HPP

#include "IMesher.hpp"

struct SimpleMesher : public IMesher
{
    SimpleMesher(Chunk & chunk, Mesh & mesh);
    virtual void meshing();

private:

    void addCube(int x, int y, int z);
};


#endif //VOXELSENGINE_SIMPLEMESHER_HPP
