#pragma once

#include "Core.hpp"
#include "Player.hpp"

namespace Everland
{
    struct Block;
    struct Chunk;

    enum BlockType
    {
        Air,
        Grass,
        Stone,
        Sand,
        Wood,
        Leaves,
        Water
    };

    const std::vector<glm::vec3> blockColors{
        {0.0, 0.0, 0.0},
        {0.188, 0.796, 0.082},
        {0.529, 0.529, 0.529},
        {1, 0.729, 0.160},
        {0.650, 0.215, 0.027},
        {0.384, 0.980, 0.239},
        {0.101, 0.670, 0.917}};

    const std::vector<glm::vec3> adjacentCoordinates{
        {-1, 0, 0},
        {1, 0, 0},
        {0, 0, -1},
        {0, 0, 1},
        {0, -1, 0},
        {0, 1, 0}};

    extern std::map<std::pair<int, int>, Chunk> chunks;
    extern std::vector<std::vector<float>> noiseMap;

    const int minWorldHeight = 0;
    const int maxWorldHeight = 128;
    const int seaLevel = 64;

    extern float scale;
    extern size_t octaves;
    extern std::vector<glm::vec2> octaveOffsets;
    extern float persistance;
    extern float lacunarity;

    const int chunkSize = 16;

    void generateNewWorld();
    void generateArea(glm::vec3 position, int renderDistance);
    void generateChunk(Chunk *chunk);
    void generateNoiseMap(glm::vec2 position, float scale, size_t octaves, float persistance, float lacunarity, float _amplitude, float _frequency);
    void generateTerrain(Chunk *chunk);
    void generateTrees();

    struct Block
    {
        std::pair<int, int> chunkPosition;
        BlockType type;
        glm::vec3 position;
        glm::vec3 color;

        Block(std::pair<int, int> chunkPosition) : chunkPosition(chunkPosition), type(BlockType::Air), position(glm::vec3{0, 0, 0}), color(glm::vec3{0, 0, 0})
        {
        }

        Block(std::pair<int, int> chunkPosition, BlockType type, glm::vec3 position) : chunkPosition(chunkPosition), type(type), position(position)
        {
            color = blockColors[type];
        }

        void setType(BlockType _type)
        {
            type = _type;
            color = blockColors[type];
        }

        void setPosition(glm::vec3 _position)
        {
            position = _position;
        }

        bool isVisible()
        {
            if (type == Air)
                return false;

            // for (auto rel : adjacentCoordinates)
            // {
            //     glm::vec3 relPos{position.x + rel.x, position.y + rel.y, position.z + rel.z};
            //     if (std::max({relPos.x, relPos.y, relPos.z}) > 15 || std::min({relPos.x, relPos.y, relPos.z}) < 0)
            //         return true;
            //     if (chunks.count(chunkPosition) > 0)
            //         if (chunks[chunkPosition].blocks[relPos.x][relPos.y][relPos.z].type == Air)
            //             return true;
            // }

            return true;
            // return false;
        }
    };

    struct Chunk
    {
        glm::vec2 position;
        std::vector<std::vector<std::vector<Block>>> blocks;
        std::vector<Block *> visibleBlocks;

        Chunk()
        {
        }

        Chunk(glm::vec2 pos) : position(pos)
        {
            blocks.resize(chunkSize, std::vector<std::vector<Block>>(chunkSize, std::vector<Block>(maxWorldHeight + 1, Block{{position.x, position.y}})));
            generateChunk(this);
        }

        void checkVisibility()
        {
            visibleBlocks.clear();
            for (size_t x = 0; x < chunkSize; ++x)
                for (size_t z = 0; z < chunkSize; ++z)
                    for (size_t y = seaLevel; y < maxWorldHeight; ++y)
                        if (blocks[x][z][y].isVisible())
                            visibleBlocks.push_back(&blocks[x][z][y]);
        }
    };
}
