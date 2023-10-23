#pragma once
#include "Cube.h"
#include "Cylinder.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Transform.h"
struct QueenProps
{
    float cyTopHeight;
    float cyTopTRadius;
    float cyTopBRadius;
    float cyMidHeight;
    float cyTopMidRadius;
    float cyBottomMidRadius;
    float cyBotHeight;
    float cyBotRadius;
    int sectorCount;
    int stackCount;
};
class Queen
{
public:

    Queen(const QueenProps& properties, bool isWhite);
    
    Transform m_transform;

    void Render(Shader& shader, Camera& camera);

    void setPosition(const glm::vec3& newPosition);
    void setScale(const glm::vec3& newScale);
private:
    
    Cylinder top_cylinder;
    Cylinder mid_cylinder;
    Cylinder bot_cylinder;
    Texture m_texture;
    
};
