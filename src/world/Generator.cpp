#include "Generator.hpp"

Chunk::Chunk(const Vector2 &coordinates) : coordinates{coordinates}
{
    blocks = std::vector<std::vector<std::vector<bool>>>(
        size, std::vector<std::vector<bool>>(size, std::vector<bool>(height, false)));
}

void Chunk::draw(Vector3 playerPosition, Vector3 playerDirection)
{
    for (float x = 0.0f; x < size; ++x)
        for (float y = 0.0f; y < size; ++y)
            for (float z = 0.0f; z < height; ++z)
                if (blocks[x][y][z])
                    DrawCubeWiresV({x, y, z}, {1.0f, 1.0f, 1.0f}, WHITE);
}

Chunk FlatGenerator::generateChunk(Vector2 coordinates)
{
    Chunk chunk{coordinates};

    for (int x = 0; x < Chunk::size; ++x)
        for (int y = 0; y < Chunk::size; ++y)
            for (int z = 0; z < Chunk::height; ++z)
                if (z < seaLevel)
                    chunk.blocks[x][y][z] = true;

    return chunk;
}