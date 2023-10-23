#pragma once
#include <GL/glew.h>
#include "Mesh.h"
#include "Transform.h"
class Cube
{
public:
    Cube();
    Cube(const Texture& texture);
    // Creates a cube with the given texture. Is default 1x1x1 in size.
    Cube(float width = 1.0f, float height = 1.0f, float length = 1.0f, const Texture& texture = Texture());
    void Render(Shader& shader, Camera& camera);
    // Use this to adjust the position, rotation, and scale of the cube.
    Transform transform;

private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    Texture m_texture;
    Mesh m_mesh;
    
    void setVertices(float width, float height, float length);
    void setVertices();
    void setIndices();
    void SetupMesh();
};
