#pragma once
#include "Cube.h"
#include "Cylinder.h"
#include "Mesh.h"
#include "Transform.h"

struct RookProps
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
class Rook
{
public:
    Transform m_transform;

    Rook(const RookProps& properties, bool isWhite);

    void Render(Shader& shader, Camera& camera);

    void setPosition(const glm::vec3& newPosition);
    void setScale(const glm::vec3& newScale);
private:
    Cylinder top_cylinder;
    Cylinder mid_cylinder;
    Cylinder bot_cylinder;
    Texture m_texture;
    
};
