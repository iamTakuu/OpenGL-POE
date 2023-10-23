#include "../Headers/King.h"

King::King(const KingProps& properties, bool isWhite)
{
  
    //verticalCube = Cube(m_texture);
    m_texture = Texture(isWhite ? "Textures/white-piece.png" : "Textures/black-piece.png", "", 0, GL_RGBA,
                        GL_UNSIGNED_BYTE);

    horizontalCube = Cube(2.0f, 1.0f, 1.0f, m_texture);
    verticalCube = Cube(1.0f, 2.0f, 1.0f, m_texture);
    top_cylinder = Cylinder(properties.cyTopHeight, properties.cyTopRadius, properties.cyTopRadius,
                            properties.sectorCount, properties.stackCount, m_texture);
    mid_cylinder = Cylinder(properties.cyMidHeight, properties.cyTopMidRadius, properties.cyBottomMidRadius,
                           properties.sectorCount, properties.stackCount, m_texture);
    bot_cylinder = Cylinder(properties.cyBotHeight, properties.cyBotRadius, properties.cyBotRadius, 
                           properties.sectorCount, properties.stackCount, m_texture);

   
    horizontalCube.transform.setLocalPosition( glm::vec3(0.0f, 5.0f, 0.0f));
    horizontalCube.transform.setLocalScale(glm::vec3(1.f, 1.0f, 1.0f));

    verticalCube.transform.setLocalPosition( glm::vec3(0.0f, 5.0f, 0.0f));
    verticalCube.transform.setLocalScale(glm::vec3(1.0f, 1.f, 1.0f));

    top_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 4.0f, 0.0f));
    mid_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 2.5f, 0.0f));
    bot_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 0.0f, 0.0f));

    
    top_cylinder.transform.setParent(&m_transform);
    mid_cylinder.transform.setParent(&m_transform);
    bot_cylinder.transform.setParent(&m_transform);
    horizontalCube.transform.setParent(&m_transform);
    verticalCube.transform.setParent(&m_transform);
    
}

void King::Render(Shader& shader, Camera& camera)
{
    horizontalCube.Render(shader, camera);
    verticalCube.Render(shader, camera);
    top_cylinder.Render(shader, camera);
    mid_cylinder.Render(shader, camera);
    bot_cylinder.Render(shader, camera);
    
}

void King::setPosition(const glm::vec3& newPosition)
{
    m_transform.setLocalPosition(newPosition);

    horizontalCube.transform.computeModelMatrix();
    verticalCube.transform.computeModelMatrix();
    top_cylinder.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
    
}

void King::setScale(const glm::vec3& newScale)
{
    m_transform.setLocalScale(newScale);

    top_cylinder.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
    horizontalCube.transform.computeModelMatrix();
    verticalCube.transform.computeModelMatrix();
}