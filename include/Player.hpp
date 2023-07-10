#pragma once

#include "Core.hpp"
#include "World.hpp"

namespace Everland
{
    namespace Player
    {
        extern glm::vec3 position;
        extern int renderDistance;
        extern int playerRange;

        void breakBlock();
        void placeBlock();
        int globalToLocal(int global);
    }
}
