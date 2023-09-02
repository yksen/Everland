#include "MeshBuilder.hpp"

#include <algorithm>

namespace
{
void addFace(std::vector<float> &vertices, std::vector<float> &normals, Direction dir, int x, int y, int z)
{
    for (auto vertex : cubeFaces[dir])
        vertices.insert(vertices.end(), {vertex.x + x, vertex.y + y, vertex.z + z});
    for (int i = 0; i < 6; ++i)
    {
        auto normal = cubeNormals[dir];
        normals.insert(normals.end(), {normal.x, normal.y, normal.z});
    }
}
} // namespace

MeshBuilder::MeshBuilder()
{
}

Mesh MeshBuilder::buildMesh(const Chunk &chunk)
{
    std::vector<float> vertices, normals;

    for (int x = 0; x < Chunk::size; ++x)
        for (int z = 0; z < Chunk::size; ++z)
            for (int y = 0; y < Chunk::height; ++y)
                if (chunk.blocks[x][z][y])
                    me::enum_for_each<Direction>([&](Direction dir) {
                        int nx = std::clamp(x + cubeNormals[dir].x, 0.f, Chunk::size - 1.f);
                        int nz = std::clamp(z + cubeNormals[dir].z, 0.f, Chunk::size - 1.f);
                        int ny = std::clamp(y + cubeNormals[dir].y, 0.f, Chunk::height - 1.f);
                        if (!chunk.blocks[nx][nz][ny])
                            addFace(vertices, normals, dir, x, y, z);
                    });

    Mesh mesh{};
    mesh.vertexCount = vertices.size() / 3;
    mesh.triangleCount = mesh.vertexCount / 3;
    mesh.vertices = new float[vertices.size()];
    mesh.normals = new float[normals.size()];
    std::copy(vertices.begin(), vertices.end(), mesh.vertices);
    std::copy(normals.begin(), normals.end(), mesh.normals);

    UploadMesh(&mesh, false);

    return mesh;
}