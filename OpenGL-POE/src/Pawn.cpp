#include "../Headers/Pawn.h"



Pawn::Pawn(GLfloat cylinderHeight, GLfloat cylinderTopRadius, GLfloat cylinderBottomRadius, GLfloat sphereRadius, GLint sectorCount, GLint stackCount)
{
    m_cylinder = Cylinder(cylinderHeight, cylinderTopRadius, cylinderBottomRadius, sectorCount, stackCount);
    m_sphere = Sphere(sphereRadius, sectorCount, stackCount);
            
    m_cylinder.transform.setLocalRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    m_cylinder.transform.setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    m_sphere.transform.setLocalPosition(glm::vec3(0.0f, 1.0f, 0.0f ));
    
    m_sphere.transform.computeModelMatrix(); // pass in the parents transform matrix
    m_cylinder.transform.computeModelMatrix(); // pass in the parents transform matrix


    // Set the parent transform
    m_cylinder.transform.m_parent = &m_transform;
    m_sphere.transform.m_parent = &m_transform;
    m_transform.setLocalPosition(glm::vec3(-3.0f, 4.0f, 8.0f));
    
    m_sphere.transform.computeModelMatrix(); // pass in the parents transform matrix
    m_cylinder.transform.computeModelMatrix(); // pass in the parents transform matrix
    
}

auto Pawn::Render(Shader& shader, Camera& camera) -> void
{
    m_cylinder.Render(shader, camera);
    m_sphere.Render(shader, camera);
}

void Pawn::setNewPosition(glm::vec3 newPosition)
{
    m_transform.setLocalPosition(newPosition);

    m_sphere.transform.computeModelMatrix(); // pass in the parents transform matrix
    m_cylinder.transform.computeModelMatrix(); // pass in the parents transform matrix
    
}
