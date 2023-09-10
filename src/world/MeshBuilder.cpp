#include "MeshBuilder.hpp"

#include <algorithm>
#include <deque>

namespace
{
void addFace(std::deque<float> &vertices, std::deque<float> &normals, Direction dir, int x, int y, int z)
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

Mesh MeshBuilder::buildMesh(const Chunk &chunk) const
{
    std::deque<float> vertices, normals;

    for (int x = 0; x < Chunk::size; ++x)
        for (int z = 0; z < Chunk::size; ++z)
            for (int y = 0; y < Chunk::height; ++y)
                if (chunk.getBlock(x, y, z))
                    me::enum_for_each<Direction>([&](Direction dir) {
                        int nx = x + cubeNormals[dir].x;
                        int nz = z + cubeNormals[dir].z;
                        int ny = y + cubeNormals[dir].y;
                        if (!chunk.getBlock(nx, ny, nz))
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