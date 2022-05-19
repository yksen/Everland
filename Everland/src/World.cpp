#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

#include "Block.h"
#include "World.h"

namespace Everland
{
    namespace World
    {
        std::vector<std::vector<std::vector<Block>>> world;
        std::vector<std::vector<float>> noiseMap;

        int worldSize = 100;

        int minNoiseHeight;
        int maxNoiseHeight;

        float scale = 1.0f;
        int octaves = 4;
        float persistance = 0.5f;
        float lacunarity = 2.0f;

        void generate();
        void generateNoiseMap(int seed, float scale, int octaves, float persistance, float lacunarity, float _amplitude, float _frequency);
        void generateTerrain();
        void generateDecorations();

        void generate()
        {
            generateNoiseMap(rand(), scale, octaves, persistance, lacunarity, 5.0f, 0.1f);
            // generateNoiseMap(rand(), 25.0f, 4, 0.5f, 2.0f, 5.0f, 0.1f); // Plains
            // generateNoiseMap(rand(), 10.0f, 4, 0.5f, 2.0f, 5.0f, 0.1f); // Hills
            generateTerrain();
            // generateDecorations();
        }

        void generateNoiseMap(int seed, float scale, int octaves, float persistance, float lacunarity, float _amplitude, float _frequency)
        {
            noiseMap.resize(worldSize, std::vector<float>(worldSize));

            std::mt19937 rng(seed);
            std::uniform_int_distribution<int> dist(-1e5, 1e5);
            std::vector<glm::vec2> octaveOffsets;
            for (int i = 0; i < octaves; ++i)
            {
                float offsetX = dist(rng);
                float offsetY = dist(rng);
                octaveOffsets.push_back(glm::vec2(offsetX, offsetY));
            }

            minNoiseHeight = std::numeric_limits<int>::max();
            maxNoiseHeight = std::numeric_limits<int>::min();

            for (int x = 0; x < worldSize; ++x)
            {
                for (int z = 0; z < worldSize; ++z)
                {
                    float amplitude = _amplitude;
                    float frequency = _frequency;
                    float noiseHeight = 0;

                    for (int i = 0; i < octaves; ++i)
                    {
                        float sampleX = x / scale * frequency + octaveOffsets[i].x;
                        float sampleZ = z / scale * frequency + octaveOffsets[i].y;

                        float noise = glm::perlin(glm::vec2(sampleX, sampleZ)) * 2 - 1;
                        noiseHeight += noise * amplitude;

                        amplitude *= persistance;
                        frequency *= lacunarity;
                    }

                    if (noiseHeight < minNoiseHeight)
                        minNoiseHeight = glm::round(noiseHeight);
                    else if (noiseHeight > maxNoiseHeight)
                        maxNoiseHeight = glm::round(noiseHeight);

                    noiseMap[x][z] = glm::round(noiseHeight);
                }
            }
        }

        void generateTerrain()
        {
            world.clear();
            world.resize(worldSize, std::vector<std::vector<Block>>(worldSize, std::vector<Block>(maxWorldHeight + 1)));

            for (int x = 0; x < worldSize; ++x)
                for (int z = 0; z < worldSize; ++z)
                {
                    int y = noiseMap[x][z] + std::abs(minNoiseHeight);
                    if (y > maxWorldHeight) y = maxWorldHeight;

                    world[x][z][y].setType(BlockType::Grass);

                    for (int d = y - 1; d > minWorldHeight; --d)
                        world[x][z][d].setType(BlockType::Stone);
                }
        }

        void generateDecorations()
        {
            float treeSpawnChance = 0.001;
            int treeHeight = 10;
            int leavesRadius = 4;

            std::mt19937 mt(time(NULL));
            std::uniform_int_distribution<int> treeHeightDist(-2, 2);

            // for (int x = 0; x < worldSize; ++x)
            //     for (int z = 0; z < worldSize; ++z)
            //     {
            //         float rnd = rand() / float(RAND_MAX);
            //         if (rnd < treeSpawnChance)
            //         {
            //             int index = x * worldSize + z;
            //             int y = world[index].y;
            //             int newTreeHeight = treeHeight + treeHeightDist(mt);

            //             for (int i = 1; i < newTreeHeight; ++i)
            //                 world.push_back(glm::vec3(x, y + i, z));

            //             for (int i = x - leavesRadius; i < x + leavesRadius; ++i)
            //                 for (int j = y + newTreeHeight - leavesRadius; j < y + newTreeHeight + leavesRadius; ++j)
            //                     for (int k = z - leavesRadius; k < z + leavesRadius * 2; ++k)
            //                         if (glm::distance(glm::vec3(i, j, k), glm::vec3(x, y + newTreeHeight, z)) < leavesRadius)
            //                             world.push_back(glm::vec3(i, j, k));
            //         }
            //     }
        }
    }
}