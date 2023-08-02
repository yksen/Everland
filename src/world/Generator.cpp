#include "Generator.hpp"

Chunk::Chunk(const rl::Vector2 &coordinates) : coordinates{coordinates}
{
    blocks = std::vector<std::vector<std::vector<bool>>>(
        size, std::vector<std::vector<bool>>(size, std::vector<bool>(height, false)));
}

void Chunk::draw()
{
    Color color = (static_cast<int>(coordinates.x) + static_cast<int>(coordinates.y)) % 2 == 0 ? WHITE : GREEN;
    for (int x = 0; x < size; ++x)
        for (int z = 0; z < size; ++z)
            for (float y = 0.0f; y < height; ++y)
                if (blocks[x][z][y])
                    DrawCubeV({coordinates.x * Chunk::size + x, y, coordinates.y * Chunk::size + z}, blockSize, color);
}

void Chunk::drawChunkBorders()
{
    DrawCubeWiresV({coordinates.x * Chunk::size + Chunk::size / 2 - Chunk::blockSize.x / 2,
                    Chunk::height / 2 - Chunk::blockSize.y / 2,
                    coordinates.y * Chunk::size + Chunk::size / 2 - Chunk::blockSize.z / 2},
                   {Chunk::size, Chunk::height, Chunk::size}, RED);
}

Chunk Generator::generateChunk(const rl::Vector2 &coordinates)
{
    Chunk chunk{coordinates};

    generateTerrain(chunk);
    generateBiomes(chunk);
    generateFeatures(chunk);

    return chunk;
}

void FlatGenerator::generateTerrain(Chunk &chunk)
{
    for (int x = 0; x < Chunk::size; ++x)
        for (int z = 0; z < Chunk::size; ++z)
            for (int y = 0; y < Chunk::height; ++y)
                if (y < seaLevel)
                    chunk.blocks[x][z][y] = true;
}

void FlatGenerator::generateBiomes(Chunk &chunk)
{
}

void FlatGenerator::generateFeatures(Chunk &chunk)
{
}

void DefaultGenerator::generateTerrain(Chunk &chunk)
{
    for (int x = 0; x < Chunk::size; ++x)
        for (int z = 0; z < Chunk::size; ++z)
        {
            float height = perlinNoise.normalizedOctave2D_01((x + chunk.coordinates.x * Chunk::size) * scale,
                                                             (z + chunk.coordinates.y * Chunk::size) * scale, octaves,
                                                             persistance);
            height *= Chunk::height;
            chunk.blocks[x][z][height] = true;
        }
}

void DefaultGenerator::generateBiomes(Chunk &chunk)
{
}

void DefaultGenerator::generateFeatures(Chunk &chunk)
{
}