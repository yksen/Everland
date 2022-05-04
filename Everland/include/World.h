#ifndef WORLD_H
#define WORLD_H

#include <vector>

namespace Everland
{
    namespace World
    {
        extern int worldSize;
        extern float noiseMultiplier;
        extern std::vector<glm::vec3> world;

        void generate();
        void saveToFile();
        void loadFromFile();
    }
}

#endif