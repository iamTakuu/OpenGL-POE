#pragma once
#include <GL/glew.h>
#include "Mesh.h"
#include "Transform.h"
class Cube
{
public:
    // Creates a cube with the given texture. Is always 1x1x1 in size.
    Cube(const Texture& texture);
    void Render(Shader& shader, Camera& camera);
    // Use this to adjust the position, rotation, and scale of the cube.
    Transform transform;

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    Texture m_texture;
    Mesh m_mesh;
    
    void setVertices();
    void setIndices();
    void SetupMesh();
};
