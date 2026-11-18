//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "CapsuleMeshPrimitive.h"

void CapsuleMeshPrimitive::setRes(
    unsigned int radial,
    unsigned int hemisphere)
{
    radialSegments = (radial < 3) ? 3 : radial;
    hemisphereSegments = (hemisphere < 2) ? 2 : hemisphere;
}

void CapsuleMeshPrimitive::createMesh()
{
    constexpr float PI = 3.14159265358979323846f;

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    float halfCylinder = baseCylinderHeight / 2.0f;

    unsigned int totalRings = hemisphereSegments * 2 + 1;

    // Generate vertices
    for (unsigned int i = 0; i <= totalRings; i++)
    {
        float y;
        float ringRadius;

        if (i <= hemisphereSegments)
        {
            // Bottom hemisphere
            float angle = -PI / 2.0f +
                (PI / 2.0f) * (float)i / (float)hemisphereSegments;

            ringRadius = baseRadius * cos(angle);
            y = -halfCylinder + baseRadius * sin(angle);
        }
        else if (i <= hemisphereSegments + 1)
        {
            // Top of cylindrical section
            ringRadius = baseRadius;
            y = halfCylinder;
        }
        else
        {
            // Top hemisphere
            float angle = (PI / 2.0f) *
                (float)(i - hemisphereSegments - 1) /
                (float)hemisphereSegments;

            ringRadius = baseRadius * cos(angle);
            y = halfCylinder + baseRadius * sin(angle);
        }

        for (unsigned int j = 0; j <= radialSegments; j++)
        {
            float phi = 2.0f * PI *
                (float)j / (float)radialSegments;

            float x = ringRadius * cos(phi);
            float z = ringRadius * sin(phi);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    // Generate indices
    unsigned int ringSize = radialSegments + 1;

    for (unsigned int i = 0; i < totalRings; i++)
    {
        for (unsigned int j = 0; j < radialSegments; j++)
        {
            unsigned int first = i * ringSize + j;
            unsigned int second = first + ringSize;

            // First triangle
            if (i != 0)
            {
                indices.push_back(first);
                indices.push_back(first + 1);
                indices.push_back(second);
            }

            // Second triangle
            if (i != totalRings - 1)
            {
                indices.push_back(first + 1);
                indices.push_back(second + 1);
                indices.push_back(second);
            }
        }
    }

    uploadMesh(
        vertices.data(),
        vertices.size() * sizeof(float),
        indices.data(),
        indices.size() * sizeof(GLuint),
        static_cast<GLsizei>(indices.size())
    );
}