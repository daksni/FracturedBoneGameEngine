//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "CylinderMeshPrimitive.h"

void CylinderMeshPrimitive::setRes(unsigned int radial)
{
    radialSegments = (radial < 3) ? 3 : radial;
}

void CylinderMeshPrimitive::createMesh()
{
    constexpr float PI = 3.14159265358979323846f;

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    float halfHeight = baseHeight / 2.0f;

    // Bottom and top centers
    unsigned int bottomCenter = 0;
    unsigned int topCenter = 1;

    vertices.insert(vertices.end(), {
        0.0f, -halfHeight, 0.0f,
        0.0f,  halfHeight, 0.0f
        });

    // Generate circular rings
    for (unsigned int i = 0; i <= radialSegments; i++)
    {
        float angle = 2.0f * PI * (float)i / (float)radialSegments;

        float x = baseRadius * cos(angle);
        float z = baseRadius * sin(angle);

        // Bottom vertex
        vertices.push_back(x);
        vertices.push_back(-halfHeight);
        vertices.push_back(z);

        // Top vertex
        vertices.push_back(x);
        vertices.push_back(halfHeight);
        vertices.push_back(z);
    }

    // Connect the rings and create caps
    for (unsigned int i = 0; i < radialSegments; i++)
    {
        unsigned int bottom = 2 + i * 2;
        unsigned int top = bottom + 1;

        unsigned int nextBottom = bottom + 2;
        unsigned int nextTop = top + 2;

        // Side surface
        indices.insert(indices.end(), {
            bottom, nextBottom, top,
            nextBottom, nextTop, top
            });

        // Bottom cap
        indices.insert(indices.end(), {
            bottomCenter, nextBottom, bottom
            });

        // Top cap
        indices.insert(indices.end(), {
            topCenter, top, nextTop
            });
    }

    uploadMesh(
        vertices.data(),
        vertices.size() * sizeof(float),
        indices.data(),
        indices.size() * sizeof(GLuint),
        static_cast<GLsizei>(indices.size())
    );
}