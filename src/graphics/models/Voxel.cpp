#include "Voxel.hpp"

Voxel::Voxel()
{
    type_ = VoxelType::AIR;
}

Voxel::Voxel(const VoxelType type)
{
    type_ = type;
}

VoxelType & Voxel::getType()
{
    return type_;
}

void Voxel::setType(const VoxelType type)
{
    type_ = type;
}