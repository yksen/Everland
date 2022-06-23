#include "World.h"

namespace Everland
{
    std::mt19937 rng(time((NULL)));

    std::uniform_real_distribution<float> waterColorDist(0.5f, 0.6f);

    std::map<std::pair<int, int>, Chunk> chunks;
    std::vector<std::vector<float>> noiseMap;

    float scale = 3.7f;
    size_t octaves = 4;
    std::vector<glm::vec2> octaveOffsets;
    float persistance = 1.3f;
    float lacunarity = 1.0f;

    void generateNewWorld();
    void generateChunk(Chunk *chunk);
    void generateNoiseMap(glm::vec2 position, int seed, float scale, int octaves, float persistance, float lacunarity, float _amplitude, float _frequency);
    void generateTerrain(Chunk *chunk);
    void generateTrees();

    bool isVisible(int x, int z, int y);

    void generateNewWorld()
    {
        chunks.clear();
        noiseMap.clear();
        octaveOffsets.clear();

        std::uniform_int_distribution<int> dist(-1e5, 1e5);
        for (size_t i = 0; i < octaves; ++i)
        {
            float offsetX = dist(rng);
            float offsetY = dist(rng);
            octaveOffsets.push_back(glm::vec2(offsetX, offsetY));
        }

        generateArea(Player::position, Player::renderDistance);
    }

    void generateArea(glm::vec3 position, int renderDistance)
    {
        for (int x = std::trunc(position.x / chunkSize) - renderDistance; x <= std::trunc(position.x / chunkSize) + renderDistance; ++x)
            for (int z = std::trunc(position.z / chunkSize) - renderDistance; z <= std::trunc(position.z / chunkSize) + renderDistance; ++z)
                if (chunks.count({x, z}) == 0)
                {
                    chunks[{x, z}] = Chunk({x, z});
                    Chunk *chunk = &chunks[{x, z}];
                    generateChunk(chunk);
                }
    }

    void generateChunk(Chunk *chunk)
    {
        generateNoiseMap(chunk->position, scale, octaves, persistance, lacunarity, 5.0f, 0.1f);
        generateTerrain(chunk);
        chunk->checkVisibility();
    }

    void generateNoiseMap(glm::vec2 position, float scale, size_t octaves, float persistance, float lacunarity, float _amplitude, float _frequency)
    {
        noiseMap.resize(chunkSize, std::vector<float>(chunkSize));

        for (size_t x = 0; x < chunkSize; ++x)
        {
            for (size_t z = 0; z < chunkSize; ++z)
            {
                float amplitude = _amplitude;
                float frequency = _frequency;
                float noiseHeight = 0;

                for (size_t i = 0; i < octaves; ++i)
                {
                    float sampleX = (x + position.x * chunkSize) / scale * frequency + octaveOffsets[i].x;
                    float sampleZ = (z + position.y * chunkSize) / scale * frequency + octaveOffsets[i].y;

                    float noise = glm::perlin(glm::vec2(sampleX, sampleZ));
                    noiseHeight += noise * amplitude;

                    amplitude *= persistance;
                    frequency *= lacunarity;
                }

                if (noiseHeight > 64)
                    noiseHeight = 64;
                else if (noiseHeight < -64)
                    noiseHeight = -64;

                noiseHeight = (noiseHeight + (maxWorldHeight / 2)) / maxWorldHeight;

                noiseMap[x][z] = noiseHeight;
            }
        }
    }

    void generateTerrain(Chunk *chunk)
    {
        chunk->blocks.resize(chunkSize, std::vector<std::vector<Block>>(chunkSize));

        for (int x = 0; x < chunkSize; ++x)
        {
            for (int z = 0; z < chunkSize; ++z)
            {
                int y = noiseMap[x][z] * maxWorldHeight;

                if (y < seaLevel + 2)
                {
                    chunk->blocks[x][z][y].setType(Sand);
                    if (y < seaLevel)
                    {
                        chunk->blocks[x][z][seaLevel].setType(Water);
                        chunk->blocks[x][z][seaLevel].setPosition(glm::vec3(x, seaLevel, z));
                        chunk->blocks[x][z][seaLevel].color.g = waterColorDist(rng);
                    }
                }
                else
                    chunk->blocks[x][z][y].setType(Grass);

                chunk->blocks[x][z][y].setPosition(glm::vec3(x, y, z));

                for (int d = y - 1; d > minWorldHeight; --d)
                {
                    chunk->blocks[x][z][d].setType(Stone);
                    chunk->blocks[x][z][d].setPosition(glm::vec3(x, d, z));
                }

                chunk->blocks[x][z][minWorldHeight].setType(Sand);
                chunk->blocks[x][z][minWorldHeight].setPosition(glm::vec3(x, minWorldHeight, z));
            }
        }
    }

    void generateTrees()
    {
        // float treeSpawnChance = 0.001;
        // int treeHeight = 10;
        // int leavesRadius = 4;

        // std::mt19937 mt(time(NULL));
        // std::uniform_int_distribution<int> treeHeightDist(-2, 2);

        // for (int x = 0; x < worldSize; ++x)
        //     for (int z = 0; z < worldSize; ++z)
        //     {
        //         float rnd = rand() / float(RAND_MAX);
        //         if (rnd < treeSpawnChance)
        //         {
        //             int y = maxWorldHeight;
        //             while (y > 0 && world[x][z][y].type == Air)
        //                 --y;

        //             int newTreeHeight = treeHeight + treeHeightDist(mt);

        //             for (int i = 1; i < newTreeHeight; ++i)
        //             {
        //                 world[x][z][y + i].setType(Wood);
        //                 world[x][z][y + i].setPosition(glm::vec3(x, y + i, z));
        //             }

        //             for (int i = x - leavesRadius; i < x + leavesRadius; ++i)
        //                 for (int j = y + newTreeHeight - leavesRadius; j < y + newTreeHeight + leavesRadius; ++j)
        //                     for (int k = z - leavesRadius; k < z + leavesRadius * 2; ++k)
        //                         if (glm::distance(glm::vec3(i, j, k), glm::vec3(x, y + newTreeHeight, z)) < leavesRadius)
        //                         {
        //                             if (i < 0 || j < 0 || k < 0)
        //                                 continue;
        //                             if (i > worldSize - 1 || j > maxWorldHeight + 1 || k > worldSize - 1)
        //                                 continue;
        //                             world[i][k][j].setType(Leaves);
        //                             world[i][k][j].setPosition(glm::vec3(i, j, k));
        //                         }
        //         }
        //     }
    }

    bool isVisible(int x, int z, int y)
    {
        // if (world[x][z][y].type == Air)
        //     return false;

        // std::vector<glm::vec3> adjacentCoordinates{
        //     {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};

        // // if (x == 0 || z == 0)
        // //     return true;
        // // if (x == worldSize - 1 || z == worldSize - 1)
        // //     return true;

        // for (glm::vec3 relPos : adjacentCoordinates)
        // {
        //     if (x + relPos.x < 0 || z + relPos.z < 0 || y + relPos.y < 0)
        //         continue;
        //     if (x + relPos.x > worldSize - 1 || z + relPos.z > worldSize - 1 || y + relPos.y > worldSize - 1)
        //         continue;
        //     if (world[x + relPos.x][z + relPos.z][y + relPos.y].type == Air)
        //         return true;
        // }
        return true;
        // return false;
    }
}