#ifndef WORLD_H
#define WORLD_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

#include "Block.h"
#include "Chunk.h"
#include "World.h"

namespace Everland
{
    namespace World
    {
        extern std::vector<Chunk> chunks;
        extern std::vector<std::vector<float>> noiseMap;

        const int minWorldHeight = 0;
        const int maxWorldHeight = 128;
        extern int worldSize;

        extern int minNoiseHeight;
        extern int maxNoiseHeight;

        extern float scale;
        extern int octaves;
        extern std::vector<glm::vec2> octaveOffsets;
        extern float persistance;
        extern float lacunarity;

        extern int worldSize;

        void generateNewWorld();
        void generateChunk(Chunk *chunk);
        void generateNoiseMap(float scale, int octaves, float persistance, float lacunarity, float _amplitude, float _frequency);
        void generateTerrain(Chunk *chunk);
        void generateTrees();

        bool isVisible(int x, int z, int y);
    }
}

#endif