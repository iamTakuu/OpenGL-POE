#pragma once

#include "Cube.h"
#include "Cylinder.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Transform.h"
struct KnightProps
{
    float cyMidHeight;
    float cyTopMidRadius;
    float cyBottomMidRadius;
    float cyBotHeight;
    float cyBotRadius;
    int sectorCount;
    int stackCount;
};
class Knight
{
public:

    Knight(const KnightProps& properties, bool isWhite);
    
    Transform m_transform;

    void Render(Shader& shader, Camera& camera);

    void setPosition(const glm::vec3& newPosition);
    void setScale(const glm::vec3& newScale);
    // Avoid using this, it's not working properly
    void setRotation(glm::vec3 vec);

private:
    Cylinder headCy;
    //Cylinder top_cylinder;
    Cylinder mid_cylinder;
    Cylinder bot_cylinder;
    Texture m_texture;
    
};
