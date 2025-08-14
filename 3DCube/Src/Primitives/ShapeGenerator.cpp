#include "ShapeGenerator.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include "ShapeData.h"
#include "Debuger.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a)


using namespace glm;


ShapeData ShapeGenerator::MakeCube()
{
    ShapeData Cube;
    Vertex stackVerts[] =
    {
        vec3(-1.0f, +1.0f, +1.0f), // 0
        vec3(+1.0f, +0.0f, +0.0f),

        vec3(+1.0f, +1.0f, +1.0f), // 1
        vec3(+0.0f, +1.0f, +0.0f),

        vec3(+1.0f, +1.0f, -1.0f), // 2
        vec3(+0.0f, +0.0f, +1.0f),

        vec3(-1.0f, +1.0f, -1.0f), // 3
        vec3(+1.0f, +1.0f, +1.0f),

        vec3(-1.0f, +1.0f, -1.0f), // 4
        vec3(+1.0f, +0.0f, +1.0f),

        vec3(+1.0f, +1.0f, -1.0f), // 5
        vec3(+0.0f, +0.5f, +0.2f),

        vec3(+1.0f, -1.0f, -1.0f), // 6
        vec3(+0.8f, +0.6f, +0.4f),

        vec3(-1.0f, -1.0f, -1.0f), // 7
        vec3(+0.3f, +1.0f, +0.5f),

        vec3(+1.0f, +1.0f, -1.0f), // 8
        vec3(+0.2f, +0.5f, +0.2f),

        vec3(+1.0f, +1.0f, +1.0f), // 9
        vec3(+0.9f, +0.3f, +0.7f),

        vec3(+1.0f, -1.0f, +1.0f), // 10
        vec3(+0.3f, +0.7f, +1.0f),

        vec3(+1.0f, -1.0f, -1.0f), // 11
        vec3(+0.5f, +0.7f, +0.5f),

        vec3(-1.0f, +1.0f, +1.0f), // 12
        vec3(+0.7f, +0.8f, +0.2f),

        vec3(-1.0f, +1.0f, -1.0f), // 13
        vec3(+0.5f, +0.7f, +0.3f),

        vec3(-1.0f, -1.0f, -1.0f), // 14
        vec3(+0.4f, +0.7f, +0.7f),

        vec3(-1.0f, -1.0f, +1.0f), // 15
        vec3(+0.2f, +0.5f, +1.0f),

        vec3(+1.0f, +1.0f, +1.0f), // 16
        vec3(+0.6f, +1.0f, +0.7f),

        vec3(-1.0f, +1.0f, +1.0f), // 17
        vec3(+0.6f, +0.4f, +0.8f),

        vec3(-1.0f, -1.0f, +1.0f), // 18
        vec3(+0.2f, +0.8f, +0.7f),

        vec3(+1.0f, -1.0f, +1.0f), // 19
        vec3(+0.2f, +0.7f, +1.0f),

        vec3(+1.0f, -1.0f, -1.0f), // 20
        vec3(+0.8f, +0.3f, +0.7f),

        vec3(-1.0f, -1.0f, -1.0f), // 21
        vec3(+0.8f, +0.9f, +0.5f),

        vec3(-1.0f, -1.0f, +1.0f), // 22
        vec3(+0.5f, +0.8f, +0.5f),

        vec3(+1.0f, -1.0f, +1.0f), // 23
        vec3(+0.9f, +1.0f, +0.2f),
    };

    Cube.NumVertices = NUM_ARRAY_ELEMENTS(stackVerts);
    Cube.Vertices = new Vertex[Cube.NumVertices];
    memcpy(Cube.Vertices, stackVerts, sizeof(stackVerts));

    GLushort stackIndices[] = {
        0,   1,  2,  0,  2,  3, // Top
        4,   5,  6,  4,  6,  7, // Front
        8,   9, 10,  8, 10, 11, // Right
        12, 13, 14, 12, 14, 15, // Left
        16, 17, 18, 16, 18, 19, // Back
        20, 22, 21, 20, 23, 22, // Bottom
    };

    Cube.NumIndices = NUM_ARRAY_ELEMENTS(stackIndices);
    Cube.Indices = new GLushort[Cube.NumIndices];
    memcpy(Cube.Indices, stackIndices, sizeof(stackIndices));

    return Cube;
}

ShapeData ShapeGenerator::MakePlane(const int Dimension)
{
    
    ShapeData Plane;
    Plane.NumVertices = Dimension * Dimension;
    int Half = Dimension / 2;
    Plane.Vertices = new Vertex[Plane.NumVertices];

    for (int i = 0; i < Dimension; i++)
    {
        for (int j = 0; j < Dimension; j++)
        {
            Vertex& thisVert = Plane.Vertices[i * Dimension + j];
            thisVert.Position.x = j - Half;
            thisVert.Position.y = i - Half;
            thisVert.Position.z = 0;
            thisVert.Color = vec3(1.0f, 0.0f, 0.0f);
            thisVert.Normal = vec3(0.0f, 1.0f, 0.0f);
        }
    }

    Plane.NumIndices = (Dimension - 1) * (Dimension - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
    Plane.Indices = new unsigned short[Plane.NumIndices];
    int runner = 0;
    for (int row = 0; row < Dimension - 1; row++)
    {
        for (int col = 0; col < Dimension - 1; col++)
        {
            Plane.Indices[runner++] = Dimension * row + col;
            Plane.Indices[runner++] = Dimension * row + col + Dimension;
            Plane.Indices[runner++] = Dimension * row + col + Dimension + 1;
             
            Plane.Indices[runner++] = Dimension * row + col;
            Plane.Indices[runner++] = Dimension * row + col + Dimension + 1;
            Plane.Indices[runner++] = Dimension * row + col + 1;
        }
    }
    assert(runner == Plane.NumIndices);

    return Plane;
}
