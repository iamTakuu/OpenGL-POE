#pragma once
#include <GL/glew.h>
#include "Mesh.h"

class Cylinder
{
public:
    Cylinder(GLfloat height = 1.0f, GLfloat topRadius = 1.0f, GLfloat bottomRadius = 1.0f, GLint sectorCount = 36, GLint stackCount = 1);

    void Render(Shader& shader, Camera& camera, const glm::mat4& parent_model);
    glm::mat4 m_model = { glm::mat4(1.0f) };
    glm::vec3 Position = { glm::vec3(0.0f) };
    glm::vec3 Rotation = { glm::vec3(0.0f) };
    glm::vec3 Scale = { glm::vec3(1.0f) };
	
private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
	
    
    Mesh m_mesh;
    GLint sectorCount;
    GLint stackCount;
    GLfloat topRadius;
    GLfloat bottomRadius;
    GLfloat height;

    
    void setVertices();
    void setIndices();
    void SetupMesh();
    
};
