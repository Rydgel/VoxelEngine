#ifndef VOXELSENGINE_VOXEL_HPP
#define VOXELSENGINE_VOXEL_HPP

#include <cstdint>

enum VoxelType
{
    AIR = 0,
    GRASS = 1,
};

struct Voxel
{
    explicit Voxel();
    explicit Voxel(VoxelType type);
    VoxelType & getType();
    void setType(VoxelType type);

private:

    VoxelType type_;
};

#endif //VOXELSENGINE_VOXEL_HPP
