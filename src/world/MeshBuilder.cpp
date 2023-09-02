#include "MeshBuilder.hpp"

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
                        for (auto vertex : cubeFaces[dir])
                            vertices.insert(vertices.end(), {vertex.x + x, vertex.y + y, vertex.z + z});
                        for (int i = 0; i < 6; ++i)
                        {
                            auto normal = cubeNormals[dir];
                            normals.insert(normals.end(), {normal.x, normal.y, normal.z});
                        }
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