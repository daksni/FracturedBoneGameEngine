//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "GameObject.h"

void GameObject::setMesh(Mesh* newMesh)
{
    mesh = newMesh;
}

glm::mat4 GameObject::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));

    model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));

    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));

    model = glm::scale(model, scale);

    return model;
}

void GameObject::setColor(float red, float green, float blue, float alpha) {
    color = glm::vec4(red, green, blue, alpha);
}

void GameObject::addGameObject(GLuint shaderProgram, GLint modelLocation){
    if (!isActive || mesh == nullptr)
        return;

    //Set the color of objects.
    glUniform1f(glGetUniformLocation(shaderProgram, "red"), color.r);
    glUniform1f(glGetUniformLocation(shaderProgram, "green"), color.g);
    glUniform1f(glGetUniformLocation(shaderProgram, "blue"), color.b);
    glUniform1f(glGetUniformLocation(shaderProgram, "alpha"), color.a);

    glUseProgram(shaderProgram);

    glm::mat4 model = getModelMatrix();

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

    mesh->addMesh();
}

