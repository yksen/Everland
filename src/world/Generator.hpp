#pragma once

#include "MeshBuilder.hpp"

#include <PerlinNoise.hpp>
#include <raylib-cpp.hpp>

#include <memory>
#include <vector>

namespace rl = raylib;

class MeshBuilder;

struct Chunk
{
    static constexpr int size{16};
    static constexpr int height{128};
    static constexpr Vector3 blockSize{1.f, 1.f, 1.f};

    static MeshBuilder meshBuilder;

    Chunk(const rl::Vector2 &coordinates);

    void draw();
    void drawChunkBorders() const;

    rl::Vector2 coordinates;
    std::vector<std::vector<std::vector<bool>>> blocks;
    std::unique_ptr<rl::Model> model;
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
    static constexpr float scale{1 / 200.f};
    static constexpr float persistance{1.3f};

    siv::PerlinNoise perlinNoise{std::random_device{}()};
};