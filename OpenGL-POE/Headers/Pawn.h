#pragma once
#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>
#include "Cylinder.h"
#include "Mesh.h"
#include "Sphere.h"

class Pawn
{
public:
    glm::vec3 Position = { glm::vec3(0.0f) };
    glm::vec3 Rotation = { glm::vec3(0.0f) };
    glm::vec3 Scale = { glm::vec3(1.0f) };

    Pawn(GLfloat cylinderHeight = 1.0f, GLfloat cylinderTopRadius = 1.0f, GLfloat cylinderBottomRadius = 1.0f,  GLfloat sphereRadius = 1.0f,  GLint sectorCount = 36, GLint stackCount = 1);

    void Render(Shader& shader, Camera& camera);

    glm::mat4 GetModelMatrix() { return parent_model; }


private:
    glm::mat4 m_identity = { glm::mat4(1.0f) };
    glm::mat4 parent_model = { glm::mat4(1.0f) };
    glm::mat4* sphere_model;
    glm::mat4* cylinder_model;

    Cylinder m_cylinder;
    Sphere m_sphere;
};
