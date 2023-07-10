#include "Player.hpp"

namespace Everland
{
    namespace Player
    {
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        int renderDistance = 1;
        int playerRange = 5;

        void breakBlock()
        {
        }

        void placeBlock()
        {
            int chunkX = std::trunc(position.x / chunkSize);
            if (position.x < 0)
                --chunkX;
            int chunkZ = std::trunc(position.z / chunkSize);
            if (position.z < 0)
                --chunkZ;
            int x = globalToLocal(position.x);
            int y = position.y;
            int z = globalToLocal(position.z);
            glm::ivec3 blockPosition{x, y, z};

            chunks[{chunkX, chunkZ}].blocks[x][z][y] = Block{{chunkX, chunkZ}, BlockType::Stone, blockPosition};
            chunks[{chunkX, chunkZ}].visibleBlocks.push_back(&chunks[{chunkX, chunkZ}].blocks[x][z][y]);
        }

        int globalToLocal(int global)
        {
            int result = global % chunkSize;
            if (result < 0)
                result += chunkSize;
            return result;
        }
    }
}