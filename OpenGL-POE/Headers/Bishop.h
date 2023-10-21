#pragma once
#include "Cube.h"
#include "Cylinder.h"
#include "Mesh.h"
#include "Transform.h"

struct BishopProps
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
class Bishop
{
public:
    Transform m_transform;

    Bishop(const BishopProps& properties, bool isWhite);

    void Render(Shader& shader, Camera& camera);

    void setPosition(const glm::vec3& newPosition);
    void setScale(const glm::vec3& newScale);
private:
    Cylinder top_cylinder;
    Cylinder mid_cylinder;
    Cylinder bot_cylinder;
    //Cube cube_1;
    //Cube cube_2;
    //Cube cube_3;
    Texture m_texture;
    
};
