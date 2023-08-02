#pragma once

#include "raylib-cpp.hpp"
#include <PerlinNoise.hpp>

#include <vector>

namespace rl = raylib;

struct Chunk
{
    static constexpr int size{16};
    static constexpr int height{128};
    static constexpr Vector3 blockSize{1.0f, 1.0f, 1.0f};

    Chunk(const rl::Vector2 &coordinates);

    void draw();
    void drawChunkBorders();

    rl::Vector2 coordinates;
    std::vector<std::vector<std::vector<bool>>> blocks;
};

class Generator
{
public:
    virtual Chunk generateChunk(const rl::Vector2 &coordinates);
    virtual void generateTerrain(Chunk &chunk) = 0;
    virtual void generateBiomes(Chunk &chunk) = 0;
    virtual void generateFeatures(Chunk &chunk) = 0;
};

class FlatGenerator : public Generator
{
public:
    void generateTerrain(Chunk &chunk) override;
    void generateBiomes(Chunk &chunk) override;
    void generateFeatures(Chunk &chunk) override;

private:
    static constexpr int seaLevel{1};
};

class DefaultGenerator : public Generator
{
public:
    void generateTerrain(Chunk &chunk) override;
    void generateBiomes(Chunk &chunk) override;
    void generateFeatures(Chunk &chunk) override;

private:
    static constexpr int seaLevel{64};
    static constexpr int octaves{4};
    static constexpr float scale{0.005f};
    static constexpr float persistance{1.3f};

    siv::PerlinNoise perlinNoise{std::random_device{}()};
};