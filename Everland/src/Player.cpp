#include "Player.h"

namespace Everland
{
    namespace Player
    {
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        int renderDistance = 2;
        int playerRange = 5;

        void breakBlock()
        {
        }

        void placeBlock()
        {
            int chunkX = std::trunc(position.x / chunkSize);
            if (position.x < 0) --chunkX;
            int chunkZ = std::trunc(position.z / chunkSize);
            if (position.z < 0) --chunkZ;
            int x = globalToLocal(position.x);
            int y = position.y;
            int z = globalToLocal(position.z);
            glm::ivec3 blockPosition{x, y, z};
            
            std::cout << position.x << "\t" << position.y << "\t" << position.z << "\n";
            std::cout << x << "\t" << y << "\t" << z << "\n";
            std::cout << chunkX << "\t" << chunkZ << "\n";

            chunks[{chunkX, chunkZ}].blocks[x][z][y] = Block{BlockType::Stone, blockPosition};
            chunks[{chunkX, chunkZ}].visibleBlocks.push_back(&chunks[{chunkX, chunkZ}].blocks[x][z][y]);
        }

        int globalToLocal(int global)
        {
            std::cout << global << "\n";
            int result = global % chunkSize;
            if (result < 0)
                result += chunkSize;
            std::cout << result << "\n";
            return result;
        }
    }
}