#pragma once
#include "Cube.h"
#include "Cylinder.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Transform.h"
struct KingProps
{
    float cyTopHeight;
    float cyTopRadius;
    float cyMidHeight;
    float cyTopMidRadius;
    float cyBottomMidRadius;
    float cyBotHeight;
    float cyBotRadius;
    int sectorCount;
    int stackCount;
};
class King
{
public:

    King(const KingProps& properties, bool isWhite);
    
    Transform m_transform;

    void Render(Shader& shader, Camera& camera);

    void setPosition(const glm::vec3& newPosition);
    void setScale(const glm::vec3& newScale);
private:
    Cube horizontalCube = Cube(1.0f, 1.0f, 1.0f);
    Cube verticalCube = Cube(1.0f, 1.0f, 1.0f);
    Cylinder top_cylinder;
    Cylinder mid_cylinder;
    Cylinder bot_cylinder;
    Texture m_texture;
    
};
