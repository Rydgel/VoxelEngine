#ifndef VOXELS_MAPGENERATORHEIGHTMAP_HPP
#define VOXELS_MAPGENERATORHEIGHTMAP_HPP

#include <iostream>
#include <vector>
#include "MapGenerator.hpp"
#include "graphics/models/Chunk.hpp"

class MapGenerator;
class MapGeneratorHeightmap : public MapGenerator
{
public :
    explicit MapGeneratorHeightmap(int seed = 131183);
    void makeChunk(Chunk & chunk) override;
};


#endif //VOXELS_MAPGENERATORHEIGHTMAP_HPP
