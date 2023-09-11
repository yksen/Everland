#pragma once

#include "Generator.hpp"

#include <magic_enum_all.hpp>
#include <raylib-cpp.hpp>

#include <deque>

namespace me
{
using magic_enum::enum_for_each;
using magic_enum::containers::array;
} // namespace me
namespace rl = raylib;

class Chunk;

class MeshBuilder
{
public:
    enum class Direction
    {
        Top,
        Bottom,
        North,
        South,
        East,
        West,
    };

    static constexpr me::array<Direction, Vector3> cubeNormals{
        0.F,  1.F,  0.F,  // Top
        0.F,  -1.F, 0.F,  // Bottom
        0.F,  0.F,  1.F,  // North
        0.F,  0.F,  -1.F, // South
        -1.F, 0.F,  0.F,  // East
        1.F,  0.F,  0.F,  // West
    };

    static constexpr me::array<Direction, std::array<Vector3, 6>> cubeFaces{
        0.F, 1.F, 0.F, 1.F, 1.F, 1.F, 1.F, 1.F, 0.F, // Top
        0.F, 1.F, 0.F, 0.F, 1.F, 1.F, 1.F, 1.F, 1.F, //
        0.F, 0.F, 0.F, 1.F, 0.F, 0.F, 1.F, 0.F, 1.F, // Bottom
        0.F, 0.F, 0.F, 1.F, 0.F, 1.F, 0.F, 0.F, 1.F, //
        0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 1.F, 1.F, 1.F, // North
        0.F, 0.F, 1.F, 1.F, 1.F, 1.F, 0.F, 1.F, 1.F, //
        0.F, 0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 0.F, 0.F, // South
        0.F, 0.F, 0.F, 0.F, 1.F, 0.F, 1.F, 1.F, 0.F, //
        0.F, 0.F, 0.F, 0.F, 0.F, 1.F, 0.F, 1.F, 1.F, // East
        0.F, 0.F, 0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 0.F, //
        1.F, 0.F, 0.F, 1.F, 1.F, 1.F, 1.F, 0.F, 1.F, // West
        1.F, 0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 1.F, 1.F, //
    };

    MeshBuilder() = default;

    static Mesh buildMesh(const Chunk &chunk);
    static void addFace(std::deque<float> &vertices, std::deque<float> &normals, Direction dir, int x, int y, int z);
};