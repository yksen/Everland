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
        Stone,
        Sand,
        Wood,
        Leaves
    };

    extern std::vector<glm::vec3> colors;

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