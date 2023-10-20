#include "../Headers/Cylinder.h"

Cylinder::Cylinder(GLfloat height, GLfloat topRadius, GLfloat bottomRadius, GLint sectorCount, GLint stackCount)
{
    this->topRadius = topRadius;
    this->bottomRadius = bottomRadius;
    this->height = height;
    this->sectorCount = sectorCount;
    this->stackCount = stackCount;

    setVertices();
    setIndices();
    SetupMesh();
}

void Cylinder::setVertices() {
    for (int i = 0; i <= stackCount; ++i) {

        float V = i / (float)stackCount;
        float phi = V * glm::pi<float>();

        // Calculate the vertical position
        float y = -height / 2.0f + (height * i / (float)stackCount);

        // Interpolate between top and bottom radii
        float radius = bottomRadius + (topRadius - bottomRadius) * (i / (float)stackCount);

        // Loop Through Slices
        for (int j = 0; j <= sectorCount; ++j) {

            float U = j / (float)sectorCount;
            float theta = U * (glm::pi<float>() * 2);

            // Calculate the vertex positions
            float x = cosf(theta) * radius;
            float z = sinf(theta) * radius;

            Vertex vertex{};

            vertex.Position = glm::vec3(x, y, z);
            vertex.Color = glm::vec3(0.2f, 0.0f, 0.4f);

            // Calculate UV coordinates
            vertex.TexCoords.x = U;
            vertex.TexCoords.y = V;

            m_vertices.push_back(vertex);
        }
    }
}

void Cylinder::setIndices()
{
    for (int i = 0; i < stackCount; ++i) {
        for (int j = 0; j < sectorCount; ++j) {
            int index = i * (sectorCount + 1) + j;

            m_indices.push_back(index);
            m_indices.push_back(index + 1);
            m_indices.push_back(index + sectorCount + 1);

            m_indices.push_back(index + 1);
            m_indices.push_back(index + sectorCount + 1);
            m_indices.push_back(index + sectorCount + 2);
        }
    }
}

void Cylinder::SetupMesh()
{
    Texture textures[] =
    {
        // Leave textType blank for now, later we will use it to determine the type of texture.
        // Like diffuse, specular, etc.
        //Texture("Textures/pop_cat.png", "", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("Textures/white.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE), // Text Index: 0
        Texture("Textures/black.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE) // Text Index: 1
    };

    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

    m_mesh = Mesh(m_vertices, m_indices, tex, 1);
}

void Cylinder::Render(Shader& shader, Camera& camera, const glm::mat4& parent_model)
{
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(parent_model * m_model));
    m_mesh.Draw(shader, camera);
}
