#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>

#include <vector>

namespace Everland
{
    enum BlockType
    {
        Air,
        Grass,
        Stone
    };

    extern std::vector<glm::vec3> colors;

    struct Block
    {
        BlockType type;
        glm::vec3 color;

        Block() : type(BlockType::Air)
        {
        }

        void setType(BlockType _type)
        {
            type = _type;
            color = colors[type];
        }
    };
}

#endif