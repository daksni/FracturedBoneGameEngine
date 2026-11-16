//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include "Mesh.h"
class GameObject
{
public:
	Mesh* mesh = nullptr;

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec4 color = glm::vec4(1.0f);

    bool isActive = true;

    void setMesh(Mesh* newMesh);
    void setColor(float red, float green, float blue, float alpha);

    glm::mat4 getModelMatrix();

    void addGameObject(GLuint shaderProgram, GLint modelLocation);
};

