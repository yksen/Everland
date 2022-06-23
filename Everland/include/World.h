#ifndef WORLD_H
#define WORLD_H

#include "Core.h"

#include "Player.h"

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

    bool isVisible(int x, int z, int y);

    struct Block
    {
        BlockType type;
        glm::vec3 position;
        glm::vec3 color;

        Block() : type(BlockType::Air), position(glm::vec3{0, 0, 0}), color(glm::vec3{0, 0, 0})
        {
        }

        Block(BlockType type, glm::vec3 position) : type(type), position(position)
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
            blocks.resize(chunkSize, std::vector<std::vector<Block>>(chunkSize, std::vector<Block>(maxWorldHeight + 1)));
            generateChunk(this);
        }

        void checkVisibility()
        {
            visibleBlocks.clear();
            for (size_t x = 0; x < chunkSize; ++x)
                for (size_t z = 0; z < chunkSize; ++z)
                    for (size_t y = seaLevel; y < maxWorldHeight; ++y)
                        if (blocks[x][z][y].type != Air && blocks[x][z][y + 1].type == Air)
                            visibleBlocks.push_back(&blocks[x][z][y]);
        }
    };
}

#endif