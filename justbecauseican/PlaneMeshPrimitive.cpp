//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "PlaneMeshPrimitive.h"

void PlaneMeshPrimitive::createMesh() {
    // Four vertices
    float vertices[] = {
        -0.5f, 0.0f, -0.5f,
         0.5f, 0.0f, -0.5f,
         0.5f, 0.0f,  0.5f,
        -0.5f, 0.0f,  0.5f
    };

    // Two triangles
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    uploadMesh(
        vertices,
        sizeof(vertices),
        indices,
        sizeof(indices),
        6
    );
}