#pragma once
#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>
#include "Cylinder.h"
#include "Mesh.h"
#include "Sphere.h"

class Pawn
{
public:
    Transform m_transform;

    Pawn(GLfloat cylinderHeight = 1.0f, GLfloat cylinderTopRadius = 1.0f, GLfloat cylinderBottomRadius = 1.0f,  GLfloat sphereRadius = 1.0f,  GLint sectorCount = 36, GLint stackCount = 1);

    void Render(Shader& shader, Camera& camera);

    void setNewPosition(glm::vec3 newPosition);


private:
    Cylinder m_cylinder;
    Sphere m_sphere;
};
