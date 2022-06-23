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
            int chunkX = position.x / chunkSize;
            int chunkZ = position.z / chunkSize;
            int localX = abs(position.x - chunkX * chunkSize);
            int localZ;
            int x = (position.x < 0) ? chunkSize - 1 - localX : localX;
            int y = position.y;
            int z = (position.z < 0) ? chunkSize - 1 - localZ : localZ;
            glm::ivec3 blockPosition{x, y, z};
            
            std::cout << position.x << "\t" << position.y << "\t" << position.z << "\n";
            std::cout << x << "\t" << y << "\t" << z << "\n";
            std::cout << chunkX << "\t" << chunkZ << "\n";

            chunks[{chunkX, chunkZ}].blocks[x][z][y] = Block{BlockType::Stone, blockPosition};
            chunks[{chunkX, chunkZ}].visibleBlocks.push_back(&chunks[{chunkX, chunkZ}].blocks[x][z][y]);
        }
    }
}