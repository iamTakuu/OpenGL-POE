#include "../Headers/Queen.h"

Queen::Queen(const QueenProps& properties, bool isWhite)
{

    m_texture = Texture(isWhite ? "Textures/white-piece.png" : "Textures/black-piece.png", "", 0);

    top_cylinder = Cylinder(properties.cyTopHeight, properties.cyTopTRadius, properties.cyTopBRadius,
                            properties.sectorCount, properties.stackCount, m_texture);
    mid_cylinder = Cylinder(properties.cyMidHeight, properties.cyTopMidRadius, properties.cyBottomMidRadius,
                           properties.sectorCount, properties.stackCount, m_texture);
    bot_cylinder = Cylinder(properties.cyBotHeight, properties.cyBotRadius, properties.cyBotRadius, 
                           properties.sectorCount, properties.stackCount, m_texture);

 
    top_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 4.0f, 0.0f));
    mid_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 2.1f, 0.0f));
    bot_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 0.0f, 0.0f));

    
    top_cylinder.transform.setParent(&m_transform);
    mid_cylinder.transform.setParent(&m_transform);
    bot_cylinder.transform.setParent(&m_transform);
    
    
}

void Queen::Render(Shader& shader, Camera& camera)
{
    top_cylinder.Render(shader, camera);
    mid_cylinder.Render(shader, camera);
    bot_cylinder.Render(shader, camera);
    
}

void Queen::setPosition(const glm::vec3& newPosition)
{
    m_transform.setLocalPosition(newPosition);

    
    top_cylinder.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
    
}

void Queen::setScale(const glm::vec3& newScale)
{
    m_transform.setLocalScale(newScale);

    top_cylinder.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
    
}