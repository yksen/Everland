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

    virtual Chunk generateChunk(rl::Vector2 coordinates) = 0;
};

class FlatGenerator : public Generator
{
public:
    FlatGenerator() = default;

    Chunk generateChunk(rl::Vector2 coordinates) override;

private:
    static constexpr int seaLevel{1};
    static constexpr float scale{3.7f};
    static constexpr int octaves{4};
    static constexpr float persistance{1.3f};
    static constexpr float lacunarity{1.0f};
    static constexpr float amplitude{5.0f};
    static constexpr float frequency{0.1f};
};