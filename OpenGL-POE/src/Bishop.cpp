#include "../Headers/Bishop.h"

Bishop::Bishop(const BishopProps& properties, bool isWhite)
{
    if(isWhite)
    {
        m_texture = Texture("Textures/white-piece.png", "", 0, GL_RGBA, GL_UNSIGNED_BYTE);
    }
    else
    {
        m_texture = Texture("Textures/black-piece.png", "", 0, GL_RGBA, GL_UNSIGNED_BYTE);
    }

    top_cylinder = Cylinder(properties.cyTopHeight, properties.cyTopRadius, properties.cyTopRadius,
                            properties.sectorCount, properties.stackCount, m_texture);
    mid_cylinder = Cylinder(properties.cyMidHeight, properties.cyTopMidRadius, properties.cyBottomMidRadius,
                           properties.sectorCount, properties.stackCount, m_texture);
    bot_cylinder = Cylinder(properties.cyBotHeight, properties.cyBotRadius, properties.cyBotRadius, 
                           properties.sectorCount, properties.stackCount, m_texture);

    
    top_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 3.0f, 0.0f));
    mid_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 1.5f, 0.0f));
    bot_cylinder.transform.setLocalPosition( glm::vec3(0.0f, 0.0f, 0.0f));

    top_cylinder.transform.setParent(&m_transform);
    mid_cylinder.transform.setParent(&m_transform);
    bot_cylinder.transform.setParent(&m_transform);

    //cube_1.transform.setParent(&m_transform);
    //cube_2.transform.setParent(&m_transform);
    //cube_3.transform.setParent(&m_transform);

    top_cylinder.transform.computeModelMatrix();
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
    
}

void Bishop::Render(Shader& shader, Camera& camera)
{
    top_cylinder.Render(shader, camera);
    mid_cylinder.Render(shader, camera);
    bot_cylinder.Render(shader, camera);
    //cube_1.Render(shader, camera);
    //cube_2.Render(shader, camera);
    //cube_3.Render(shader, camera);
}

void Bishop::setPosition(const glm::vec3& newPosition)
{
    m_transform.setLocalPosition(newPosition);

    top_cylinder.transform.computeModelMatrix(); 
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
    //cube_1.transform.computeModelMatrix();
    //cube_2.transform.computeModelMatrix();
    //cube_3.transform.computeModelMatrix();
}

void Bishop::setScale(const glm::vec3& newScale)
{
    m_transform.setLocalScale(newScale);

    top_cylinder.transform.computeModelMatrix(); 
    mid_cylinder.transform.computeModelMatrix();
    bot_cylinder.transform.computeModelMatrix();
    //cube_1.transform.computeModelMatrix();
    //cube_2.transform.computeModelMatrix();
    //cube_3.transform.computeModelMatrix();
}
