#include "../Headers/Pawn.h"

Pawn::Pawn(const PawnProps& properties, const bool isWhite)
{
    
    m_texture = Texture(isWhite ? "Textures/white-piece.png" : "Textures/black-piece.png", "", 0, GL_RGBA,
                        GL_UNSIGNED_BYTE);
    // Create the cylinder and sphere
    m_cylinder = Cylinder(properties.cyHeight, properties.cyTopRadius, properties.cyBottomRadius,
                          properties.sectorCount, properties.stackCount, m_texture);
    m_sphere = Sphere(properties.spRadius, properties.sectorCount, properties.stackCount, m_texture);

    // Set the local transform
    m_cylinder.transform.setLocalRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    m_cylinder.transform.setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    m_sphere.transform.setLocalPosition(glm::vec3(0.0f, 1.0f, 0.0f ));

    // Set the parent transform
    m_cylinder.transform.setParent(&m_transform);
    m_sphere.transform.setParent(&m_transform);

    //m_transform.setLocalRotation(glm::vec3(90.0f, 0.0f, 0.0f));
    // Compute the model matrix
    m_sphere.transform.computeModelMatrix(); 
    m_cylinder.transform.computeModelMatrix();
}

void Pawn::Render(Shader& shader, Camera& camera)
{
    m_cylinder.Render(shader, camera);
    m_sphere.Render(shader, camera);
}

void Pawn::setPosition(const glm::vec3& newPosition)
{
    m_transform.setLocalPosition(newPosition);

    m_sphere.transform.computeModelMatrix(); 
    m_cylinder.transform.computeModelMatrix();
    
}

void Pawn::setScale(const glm::vec3& newScale)
{
    m_transform.setLocalScale(newScale);

    m_sphere.transform.computeModelMatrix(); 
    m_cylinder.transform.computeModelMatrix();
}
