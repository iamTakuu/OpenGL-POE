#pragma once
#include <GL/glew.h>
#include "Mesh.h"
#include "Transform.h"

class Cylinder
{
public:
    Cylinder(GLfloat height = 1.0f, GLfloat topRadius = 1.0f, GLfloat bottomRadius = 1.0f, GLint sectorCount = 36,
             GLint stackCount = 1, const Texture& texture = Texture());

    void Render(Shader& shader, Camera& camera);
    //Transform* m_parent = nullptr;
    Transform transform;
	
private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
	
    
    Mesh m_mesh;
    GLint sectorCount;
    GLint stackCount;
    GLfloat topRadius;
    GLfloat bottomRadius;
    GLfloat height;

    Texture m_texture;

    
    void setVertices();
    void setIndices();
    void SetupMesh();
    
};
