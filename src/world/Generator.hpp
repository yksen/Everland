#pragma once

#include "raylib.h"

#include <vector>

struct Chunk
{
    static constexpr int size{16};
    static constexpr int height{128};

    Chunk(const Vector2 &coordinates);

    void draw(Vector3 playerPosition, Vector3 playerDirection);

    Vector2 coordinates;
    std::vector<std::vector<std::vector<bool>>> blocks;
};

class Generator
{
public:
    Generator() = default;
    virtual ~Generator() = default;

    virtual Chunk generateChunk(Vector2 coordinates) = 0;
};

class FlatGenerator : public Generator
{
public:
    FlatGenerator() = default;

    Chunk generateChunk(Vector2 coordinates) override;

private:
    static constexpr int seaLevel{8};
    static constexpr float scale{3.7f};
    static constexpr int octaves{4};
    static constexpr float persistance{1.3f};
    static constexpr float lacunarity{1.0f};
    static constexpr float amplitude{5.0f};
    static constexpr float frequency{0.1f};
};