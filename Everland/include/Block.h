#ifndef BLOCK_H
#define BLOCK_H

#include "Core.h"

namespace Everland
{
    enum BlockType
    {
        Air,
        Grass,
        Stone,
        Sand,
        Wood,
        Leaves
    };

    const std::vector<glm::vec3> colors{
        {0.0, 0.0, 0.0},
        {0.188, 0.796, 0.082},
        {0.529, 0.529, 0.529},
        {1, 0.729, 0.160},
        {0.650, 0.215, 0.027},
        {0.384, 0.980, 0.239}};

    struct Block
    {
        BlockType type;
        glm::vec3 position;
        glm::vec3 color;

        Block() : type(BlockType::Air)
        {
        }

        void setType(BlockType _type)
        {
            type = _type;
            color = colors[type];
        }

        void setPosition(glm::vec3 _position)
        {
            position = _position;
        }
    };
}

#endif