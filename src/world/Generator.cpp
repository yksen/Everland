#include "Generator.hpp"

Chunk::Chunk(const rl::Vector2 &coordinates) : coordinates{coordinates}
{
    blocks = std::vector<std::vector<std::vector<bool>>>(
        size, std::vector<std::vector<bool>>(size, std::vector<bool>(height, false)));
}

void Chunk::generateMesh()
{
    static const rl::Shader shader = [] {
        rl::Shader shader = rl::Shader::Load("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
        static constexpr float lightColor[3] = {1.0f, 1.0f, 1.0f};
        static constexpr float objectColor[3] = {0.0f, 1.0f, 0.0f};
        shader.SetValue(shader.GetLocation("lightColor"), &lightColor, SHADER_UNIFORM_VEC3);
        shader.SetValue(shader.GetLocation("objectColor"), &objectColor, SHADER_UNIFORM_VEC3);
        return shader;
    }();

    // model = std::make_unique<rl::Model>(rl::Mesh::Cube(Chunk::blockSize.x, Chunk::blockSize.y, Chunk::blockSize.z));
    // model->materials[0].shader = shader;
}

void Chunk::draw() const
{
    rl::Color color{rl::Color::Green()};

    // model->DrawWires({coordinates.x * Chunk::size, 0.0f, coordinates.y * Chunk::size}, 1.0f, color);
}

void Chunk::drawChunkBorders() const
{
    DrawCubeWiresV({coordinates.x * Chunk::size + Chunk::size / 2 - Chunk::blockSize.x / 2,
                    Chunk::height / 2 - Chunk::blockSize.y / 2,
                    coordinates.y * Chunk::size + Chunk::size / 2 - Chunk::blockSize.z / 2},
                   {Chunk::size, Chunk::height, Chunk::size}, RED);
}

Chunk Generator::generateChunk(const rl::Vector2 &coordinates)
{
    Chunk chunk{coordinates};

    generateTerrain(chunk);
    generateBiomes(chunk);
    generateFeatures(chunk);

    return chunk;
}

void FlatGenerator::generateTerrain(Chunk &chunk)
{
    for (int x = 0; x < Chunk::size; ++x)
        for (int z = 0; z < Chunk::size; ++z)
            for (int y = 0; y < Chunk::height; ++y)
                if (y < seaLevel)
                    chunk.blocks[x][z][y] = true;
}

void FlatGenerator::generateBiomes(Chunk &chunk)
{
}

void FlatGenerator::generateFeatures(Chunk &chunk)
{
}

void DefaultGenerator::generateTerrain(Chunk &chunk)
{
    for (int x = 0; x < Chunk::size; ++x)
        for (int z = 0; z < Chunk::size; ++z)
        {
            float height = perlinNoise.normalizedOctave2D_01((x + chunk.coordinates.x * Chunk::size) * scale,
                                                             (z + chunk.coordinates.y * Chunk::size) * scale, octaves,
                                                             persistance);
            height *= Chunk::height;

            for (int y = 0; y < Chunk::height; ++y)
                if (y < height)
                    chunk.blocks[x][z][y] = true;
        }
}

void DefaultGenerator::generateBiomes(Chunk &chunk)
{
}

void DefaultGenerator::generateFeatures(Chunk &chunk)
{
}