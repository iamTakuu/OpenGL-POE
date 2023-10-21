#pragma once
#include <GL/glew.h>
#include <glm/gtx/euler_angles.hpp>
#include "Cylinder.h"
#include "Mesh.h"
#include "Sphere.h"

struct PawnProperties
{
    float cyHeight;
    float cyTopRadius;
    float cyBottomRadius;
    float spRadius;
    int sectorCount;
    int stackCount;
};
class Pawn
{
public:
    Transform m_transform;

    Pawn(const PawnProperties& properties, bool isWhite);

    void Render(Shader& shader, Camera& camera);

    void setPosition(const glm::vec3& newPosition);
    void setScale(const glm::vec3& newScale);


private:
    Cylinder m_cylinder;
    Sphere m_sphere;
    Texture m_texture;
};
