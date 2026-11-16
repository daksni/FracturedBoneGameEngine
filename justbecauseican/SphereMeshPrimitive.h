//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include "Mesh.h"

class SphereMeshPrimitive : public Mesh
{
private:
    const float baseRadius = 0.5f;

    unsigned int longitudeSegments = 32;
    unsigned int latitudeSegments = 16;

public:
    void setRes(unsigned int longitude, unsigned int latitude);

    void createMesh() override;
};