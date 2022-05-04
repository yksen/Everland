#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

namespace Everland
{
    namespace World
    {
        int worldSize = 200;
        float noiseMultiplier = 10.0f;
        std::vector<glm::vec3> world;

        void generate()
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
    }
}