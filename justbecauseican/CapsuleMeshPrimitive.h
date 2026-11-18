//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include "Mesh.h"

class CapsuleMeshPrimitive : public Mesh
{
private:
    const float baseRadius = 0.5f;
    const float baseCylinderHeight = 1.0f;

    unsigned int radialSegments = 32;
    unsigned int hemisphereSegments = 8;

public:
    void setRes(unsigned int radial, unsigned int hemisphere);

    void createMesh() override;
};
