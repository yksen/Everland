#include "Generator.hpp"

Chunk::Chunk(const rl::Vector2 &coordinates) : coordinates{coordinates}
{
    blocks = std::vector<std::vector<std::vector<bool>>>(
        size, std::vector<std::vector<bool>>(size, std::vector<bool>(height, false)));
}

void Chunk::draw()
{
    if (model)
        model->Draw({coordinates.x * Chunk::size, 0.0f, coordinates.y * Chunk::size}, 1.0f, rl::Color::White());
}

void Chunk::drawChunkBorders() const
{
    DrawCubeWiresV({coordinates.x * Chunk::size + Chunk::size / 2, Chunk::height / 2,
                    coordinates.y * Chunk::size + Chunk::size / 2},
                   {Chunk::size, Chunk::height, Chunk::size}, RED);
}

void Chunk::buildMesh()
{
    static const rl::Shader shader = [] {
        rl::Shader shader = rl::Shader::Load("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
        static constexpr std::array<float, 3> lightColor{1.0F, 1.0F, 1.0F};
        shader.SetValue(shader.GetLocation("lightColor"), &lightColor, SHADER_UNIFORM_VEC3);
        return shader;
    }();

    auto mesh = MeshBuilder::buildMesh(*this);
    model = std::make_unique<rl::Model>(mesh);
    model->materials[0].shader = shader;
}

bool Chunk::getBlock(int x, int y, int z) const
{
    rl::Vector2 chunkPosition{std::floor(static_cast<float>(x) / Chunk::size),
                              std::floor(static_cast<float>(z) / Chunk::size)};
    const bool inChunk = static_cast<bool>(chunkPosition.Equals({0, 0}));

    if (inChunk)
        return blocks[x][z][y];

    const int nx = (x + Chunk::size) % Chunk::size;
    const int nz = (z + Chunk::size) % Chunk::size;

    auto *neighbor = neighbors[chunkPosition.x + 1][chunkPosition.y + 1];
    if (neighbor != nullptr)
        return neighbor->getBlock(nx, y, nz);

    return true;
}

Chunk Generator::generateChunk(const rl::Vector2 &coordinates)
{
    Chunk chunk{coordinates};

    generateTerrain(chunk);
    generateBiomes(chunk);
    generateFeatures(chunk);
    chunk.buildMesh();

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