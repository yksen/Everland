#ifndef CHUNK_H
#define CHUNK_H

#include "Core.h"
#include "Block.h"

namespace Everland
{
    const int chunkSize = 16;

    struct Chunk
    {
        glm::vec3 position;
        std::vector<std::vector<std::vector<Block>>> blocks;

        Chunk()
        {
        }
    };
}

#endif