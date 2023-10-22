#pragma once
#include "Cylinder.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Transform.h"
struct BishopProps
{
    float spRadius;
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
class Bishop
{
public:

    Bishop(const BishopProps& properties, bool isWhite);
    
    Transform m_transform;

    void Render(Shader& shader, Camera& camera);

    void setPosition(const glm::vec3& newPosition);
    void setScale(const glm::vec3& newScale);
private:
    Sphere sphere;
    Cylinder top_cylinder;
    Cylinder mid_cylinder;
    Cylinder bot_cylinder;
    Texture m_texture;
    
};
