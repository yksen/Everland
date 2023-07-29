#include "Generator.hpp"

Chunk::Chunk(const rl::Vector2 &coordinates) : coordinates{coordinates}
{
    blocks = std::vector<std::vector<std::vector<bool>>>(
        size, std::vector<std::vector<bool>>(size, std::vector<bool>(height, false)));
}

void Chunk::draw(rl::Vector3 playerDirection)
{
    DrawCubeWiresV({coordinates.x * Chunk::size + Chunk::size / 2 - Chunk::blockSize.x / 2, Chunk::height / 2,
                    coordinates.y * Chunk::size + Chunk::size / 2 - Chunk::blockSize.z / 2},
                   {Chunk::size, Chunk::height, Chunk::size}, RED);

    Color color = (static_cast<int>(coordinates.x) + static_cast<int>(coordinates.y)) % 2 == 0 ? WHITE : GREEN;
    for (int x = 0; x < size; ++x)
        for (int z = 0; z < size; ++z)
            for (float y = 0.0f; y < height; ++y)
                if (blocks[x][z][y])
                    DrawCubeWiresV({coordinates.x * Chunk::size + x, y, coordinates.y * Chunk::size + z}, blockSize,
                                   color);
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