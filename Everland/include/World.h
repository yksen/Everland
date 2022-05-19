#ifndef WORLD_H
#define WORLD_H

#include <vector>

namespace Everland
{
    namespace World
    {
        extern std::vector<std::vector<std::vector<Block>>> world;
        extern std::vector<std::vector<float>> noiseMap;

        const int minWorldHeight = 0;
        const int maxWorldHeight = 100;
        extern int worldSize;

        extern int minNoiseHeight;
        extern int maxNoiseHeight;

        extern float scale;
        extern int octaves;
        extern float persistance;
        extern float lacunarity;

        extern int worldSize;

        void generate();
        void generateNoiseMap();
        void generateTerrain();
        void generateDecorations();

        bool isVisible(int x, int z, int y);
    }
}

#endif