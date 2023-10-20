#include "../Headers/Pawn.h"

Pawn::Pawn(GLfloat cylinderHeight, GLfloat cylinderTopRadius, GLfloat cylinderBottomRadius, GLfloat sphereRadius, GLint sectorCount, GLint stackCount)
{
    m_cylinder = Cylinder(cylinderHeight, cylinderTopRadius, cylinderBottomRadius, sectorCount, stackCount);
    m_sphere = Sphere(sphereRadius, sectorCount, stackCount);

    //Rotate the cylinder 90 degrees on the X axis
    m_cylinder.m_model = glm::rotate(m_cylinder.m_model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    // Point the cylinder's model matrix to the pawn's model matrix
    //cylinder_model = &m_cylinder.m_model;
    //sphere_model = &m_sphere.m_model;
}

void Pawn::Render(Shader& shader, Camera& camera)
{
    // Adjust the Y position for the sphere
    glm::vec3 spherePosition = Position + glm::vec3(0.0f, Scale.x * 2.0f, 0.0f);

    // Set the model matrix for the cylinder
    glm::mat4 parent_model = glm::translate(m_identity, Position);
    parent_model = glm::eulerAngleXYZ(
        glm::radians(Rotation.x),
        glm::radians(Rotation.y),
        glm::radians(Rotation.z)) * parent_model;
    parent_model = glm::scale(parent_model, Scale);

    // Render the cylinder
    m_cylinder.Render(shader, camera, parent_model);

    // Set the model matrix for the sphere with the adjusted Y position
    glm::mat4 sphere_model = glm::translate(m_identity, spherePosition);
    sphere_model = glm::eulerAngleXYZ(
        glm::radians(Rotation.x),
        glm::radians(Rotation.y),
        glm::radians(Rotation.z)) * sphere_model;
    sphere_model = glm::scale(sphere_model, Scale);

    
    // Render the sphere
    m_sphere.Render(shader, camera, parent_model);
}