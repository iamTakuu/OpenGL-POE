#include "../Headers/Knight.h"

Knight::Knight(const KnightProps& properties, bool isWhite)
{
    m_texture = Texture(isWhite ? "Textures/white-piece.png" : "Textures/black-piece.png", "", 0);

    
    // top_cylinder = Cylinder(properties.cyTopHeight, properties.cyTopRadius, properties.cyTopRadius,
    //                         properties.sectorCount, properties.stackCount, m_texture);
    headCube = Cube(1.0f, 1.2f, 3.0f, m_texture);
    mid_cylinder = Cylinder(properties.cyMidHeight, properties.cyTopMidRadius, properties.cyBottomMidRadius,
                           properties.sectorCount, properties.stackCount, m_texture);
    bot_cylinder = Cylinder(properties.cyBotHeight, properties.cyBotRadius, properties.cyBotRadius, 
                           properties.sectorCount, properties.stackCount, m_texture);

    headCube.transform.setLocalRotation(glm::vec3(isWhite ? -20.0f : 20.0f, 0.0f, 0.0f));
    headCube.transform.setLocalPosition( glm::vec3(.0f, 2.5f, isWhite? -0.2f : 0.2f));
    //headCube.transform.setLocalPosition( glm::vec3(.0f, isWhite? 0.0f : 6.0f, .0f));
    //headCube.transform.setLocalScale(glm::vec3(1.f, 0.9f, 1.4f));
    
    //headCube.transform.setLocalRotation(glm::vec3(isWhite ? -20.0f : 20.0f, 0.0f, 0.0f));
    mid_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 1.5f, 0.0f));
    bot_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 0.0f, 0.0f));
    m_transform.computeModelMatrix();
    
    bot_cylinder.transform.setParent(&m_transform);
    mid_cylinder.transform.setParent(&m_transform);
    headCube.transform.setParent(&m_transform);
    
    
    headCube.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
}

void Knight::Render(Shader& shader, Camera& camera)
{
    headCube.Render(shader, camera);
    mid_cylinder.Render(shader, camera);
    bot_cylinder.Render(shader, camera);
    
}

void Knight::setPosition(const glm::vec3& newPosition)
{
    m_transform.setLocalPosition(newPosition);

    headCube.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
}

void Knight::setScale(const glm::vec3& newScale)
{
    m_transform.setLocalScale(newScale);

    headCube.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
}

void Knight::setRotation(glm::vec3 vec)
{
    m_transform.setLocalRotation(vec);

    headCube.transform.computeModelMatrix();
    //top_cylinder.transform.computeModelMatrix(); 
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
}
