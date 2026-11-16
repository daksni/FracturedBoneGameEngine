//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "SphereMeshPrimitive.h"

void SphereMeshPrimitive::setRes(unsigned int longitude, unsigned int latitude) {
    longitudeSegments = (longitude < 3) ? 3 : longitude;
    latitudeSegments = (latitude < 2) ? 2 : latitude;
}

void SphereMeshPrimitive::createMesh() {

    constexpr float PI = 3.14159265358979323846f;

    std::vector<float> vertices;
    std::vector<GLuint> indices;

    // Generate vertices
    for (unsigned int i = 0; i <= latitudeSegments; i++) {

        float theta = PI * (float)i / (float)latitudeSegments;

        for (unsigned int j = 0; j <= longitudeSegments; j++) {

            float phi = 2.0f * PI * (float)j / (float)longitudeSegments;

            float x = baseRadius * sin(theta) * cos(phi);
            float y = baseRadius * cos(theta);
            float z = baseRadius * sin(theta) * sin(phi);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    // Generate indices
    for (unsigned int i = 0; i < latitudeSegments; i++) {

        for (unsigned int j = 0; j < longitudeSegments; j++) {

            unsigned int first = i * (longitudeSegments + 1) + j;
            unsigned int second = first + longitudeSegments + 1;

            // First triangle
            if (i != 0) {
                indices.push_back(first);
                indices.push_back(first + 1);
                indices.push_back(second);
            }

            // Second triangle
            if (i != latitudeSegments - 1) {
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