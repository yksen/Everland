#pragma once

#include "raylib-cpp.hpp"

#include <vector>

namespace rl = raylib;

struct Chunk
{
    static constexpr int size{16};
    static constexpr int height{128};

    Chunk(const rl::Vector2 &coordinates);

    void draw(rl::Vector3 playerPosition, rl::Vector3 playerDirection);

    rl::Vector2 coordinates;
    std::vector<std::vector<std::vector<bool>>> blocks;
};

class Generator
{
public:
    virtual ~Generator() = default;

    virtual Chunk generateChunk(const rl::Vector2 &coordinates);
    virtual void generateTerrain(Chunk &chunk) = 0;
    virtual void generateBiomes(Chunk &chunk) = 0;
    virtual void generateFeatures(Chunk &chunk) = 0;
};

class FlatGenerator : public Generator
{
public:
    FlatGenerator() = default;

    void generateTerrain(Chunk &chunk) override;
    void generateBiomes(Chunk &chunk) override;
    void generateFeatures(Chunk &chunk) override;

private:
    static constexpr int seaLevel{1};
    static constexpr float scale{3.7f};
    static constexpr int octaves{4};
    static constexpr float persistance{1.3f};
    static constexpr float lacunarity{1.0f};
    static constexpr float amplitude{5.0f};
    static constexpr float frequency{0.1f};
};