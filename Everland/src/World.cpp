#include <iostream>
#include <random>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

namespace Everland
{
    namespace World
    {
        int worldSize = 300;
        float noiseMultiplier = 10.0f;
        std::vector<glm::vec3> world;

        void generate();
        void generateTerrain();
        void generateDecorations();

        void generate()
        {
            generateTerrain();
            generateDecorations();
        }

        void generateTerrain()
        {
            world.clear();
            int seed = rand();

            for (int x = 0; x < worldSize; ++x)
                for (int z = 0; z < worldSize; ++z)
                {
                    float noise = glm::perlin(glm::vec2(x + seed, z + seed) * 0.01f);
                    float y = glm::round(noise * noiseMultiplier);
                    world.push_back(glm::vec3(x, y, z));
                }
        }

        void generateDecorations()
        {
            float treeSpawnChance = 0.001;
            int treeHeight = 10;
            int leavesRadius = 4;

            std::mt19937 mt(time(NULL));
            std::uniform_int_distribution<int> treeHeightDist(-2, 2);

            for (int x = 0; x < worldSize; ++x)
                for (int z = 0; z < worldSize; ++z)
                {
                    float rnd = rand() / float(RAND_MAX);
                    if (rnd < treeSpawnChance)
                    {
                        int index = x * worldSize + z;
                        int y = world[index].y;
                        int newTreeHeight = treeHeight + treeHeightDist(mt);

                        for (int i = 1; i < newTreeHeight; ++i)
                            world.push_back(glm::vec3(x, y + i, z));

                        for (int i = x - leavesRadius; i < x + leavesRadius; ++i)
                            for (int j = y + newTreeHeight - leavesRadius; j < y + newTreeHeight + leavesRadius; ++j)
                                for (int k = z - leavesRadius; k < z + leavesRadius * 2; ++k)
                                    if (glm::distance(glm::vec3(i, j, k), glm::vec3(x, y + newTreeHeight, z)) < leavesRadius)
                                        world.push_back(glm::vec3(i, j, k));
                    }
                }
        }
    }
}