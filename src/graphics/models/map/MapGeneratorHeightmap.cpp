#include "MapGeneratorHeightmap.hpp"
#include "utils/SimplexNoise.hpp"


MapGeneratorHeightmap::MapGeneratorHeightmap(int seed)
: MapGenerator(seed)
{
    m_seed = seed;
}

void MapGeneratorHeightmap::makeChunk(Chunk & chunk)
{
    // Landscape generation
    float m_landscapeOctaves = 4.0f;
    float m_landscapePersistence = 0.3f;
    float m_landscapeScale = 0.02f;
    float m_mountainOctaves = 4.0f;
    float m_mountainPersistence = 0.3f;
    float m_mountainScale = 0.0275f;
    float m_mountainMultiplier = 0.8f;

    auto offset = chunk.getOffset();
    for (int x = 0; x < Chunk::chunkWidth; x++) {
        for (int z = 0; z < Chunk::chunkDepth; z++) {
            float xPosition = offset.x + x;
            float zPosition = offset.z + z;

            // Get the noise height
            float noise = octave_noise_2d(m_landscapeOctaves, m_landscapePersistence, m_landscapeScale, xPosition, zPosition);
            float noiseNormalized = ((noise + 1.0f) * 0.5f);
            float noiseHeight = noiseNormalized * Chunk::chunkHeight;

            // Multiple by mountain ratio
            float mountainNoise = octave_noise_2d(m_mountainOctaves, m_mountainPersistence, m_mountainScale, xPosition, zPosition);
            float mountainNoiseNormalise = (mountainNoise + 1.0f) * 0.5f;
            float mountainMultiplier = m_mountainMultiplier * mountainNoiseNormalise;
            noiseHeight *= mountainMultiplier;

            for (int y = 0; y < Chunk::chunkHeight; y++) {
                // float yPosition = offset.y + y;

                if (y < noiseHeight) {
                    chunk.fill(Voxel { VoxelType::GRASS }, x, y, z);
                }
            }
        }
    }
}
