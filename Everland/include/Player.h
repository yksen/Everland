#ifndef PLAYER_H
#define PLAYER_H

#include "Core.h"

#include "World.h"

namespace Everland
{
    namespace Player
    {
        extern glm::vec3 position;
        extern int renderDistance;
        extern int playerRange;

        void breakBlock();
        void placeBlock();
    }
}

#endif