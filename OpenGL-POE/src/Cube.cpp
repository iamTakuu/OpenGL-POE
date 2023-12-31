﻿#include "../Headers/Cube.h"

Cube::Cube()
= default;

Cube::Cube(const Texture& texture)
{
    m_texture = texture;
    setVertices();
    setIndices();
    SetupMesh();
}

Cube::Cube(float width, float height, float length, const Texture& texture)
{
    m_texture = texture;
    setVertices(width, height, length);
    setIndices();
    SetupMesh();
}

void Cube::setIndices()
{
    const GLuint cubeIndices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };
    m_indices = std::vector<GLuint>(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
}
void Cube::setVertices(float width, float height, float length)
{
    const Vertex cubeVertex[] =
    {
        //              COORDINATES           /            COLORS          /      TEXTURE COORDINATES    /          NORMALS         //
        Vertex{glm::vec3(-width, -height, length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // Front bottom left
        Vertex{glm::vec3(-width, -height, -length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // Back bottom left
        Vertex{glm::vec3(width, -height, -length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  // Back bottom right
        Vertex{glm::vec3(width, -height, length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // Front bottom right

        Vertex{glm::vec3(-width, height, length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Front top left
        Vertex{glm::vec3(-width, height, -length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Back top left
        Vertex{glm::vec3(width, height, -length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // Back top right
        Vertex{glm::vec3(width, height, length), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}  // Front top right
    };


    m_vertices = std::vector<Vertex>(cubeVertex, cubeVertex + sizeof(cubeVertex) / sizeof(Vertex));
}
void Cube::setVertices()
{
    const Vertex cubeVertex[] =
    {
        //              COORDINATES           /            COLORS          /      TEXTURE COORDINATES    /          NORMALS         //
        Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // Front bottom left
        Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // Back bottom left
        Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)},  // Back bottom right
        Vertex{glm::vec3(1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)}, // Front bottom right

        Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Front top left
        Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Back top left
        Vertex{glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // Back top right
        Vertex{glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}  // Front top right
    };


    m_vertices = std::vector<Vertex>(cubeVertex, cubeVertex + sizeof(cubeVertex) / sizeof(Vertex));
}

void Cube::SetupMesh()
{
    m_mesh = Mesh(m_vertices,m_indices, m_texture);
}
void Cube::Render(Shader& shader, Camera& camera)
{
    shader.Activate();
    shader.setMat4("model", transform.getModelMatrix());
    m_mesh.Draw(shader, camera);
}




