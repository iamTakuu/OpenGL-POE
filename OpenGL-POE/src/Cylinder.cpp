#include "../Headers/Cylinder.h"

Cylinder::Cylinder(GLfloat height, GLfloat topRadius, GLfloat bottomRadius, GLint sectorCount, GLint stackCount, const Texture& texture)
{
    this->topRadius = topRadius;
    this->bottomRadius = bottomRadius;
    this->height = height;
    this->sectorCount = sectorCount;
    this->stackCount = stackCount;
    this->m_texture = texture;

    setVertices();
    setIndices();
    SetupMesh();
}

void Cylinder::setVertices() {
    for (int i = 0; i <= stackCount; ++i) {
        float V = i / (float)stackCount;
        float phi = V * glm::pi<float>();
        float y = -height / 2.0f + (height * i / (float)stackCount);
        float radius = bottomRadius + (topRadius - bottomRadius) * (i / (float)stackCount);

        for (int j = 0; j <= sectorCount; ++j) {
            float U = j / (float)sectorCount;
            float theta = U * (glm::pi<float>() * 2);
            float x = cosf(theta) * radius;
            float z = sinf(theta) * radius;

            Vertex vertex{};
            vertex.Position = glm::vec3(x, y, z);
            vertex.Color = glm::vec3(1.0f, 1.0f, 1.0f);
            vertex.TexCoords.x = U;
            vertex.TexCoords.y = V;

            m_vertices.push_back(vertex);

            // Check if this is the top or bottom stack to create caps
            if (i == 0 || i == stackCount) {
                Vertex capVertex{};
                capVertex.Position = glm::vec3(x, y, z);
                capVertex.Color = glm::vec3(1.0f, 1.0f, 1.0f);
                capVertex.TexCoords.x = 0.5f + x / (2 * topRadius);
                capVertex.TexCoords.y = 0.5f + z / (2 * topRadius);
                m_vertices.push_back(capVertex);
            }
        }
    }
}


void Cylinder::setIndices() {
    for (int i = 0; i < stackCount; ++i) {
        for (int j = 0; j < sectorCount; ++j) {
            int index = i * (sectorCount + 1) + j;

            m_indices.push_back(index);
            m_indices.push_back(index + 1);
            m_indices.push_back(index + sectorCount + 1);

            m_indices.push_back(index + 1);
            m_indices.push_back(index + sectorCount + 1);
            m_indices.push_back(index + sectorCount + 2);

            // Check if this is the top or bottom stack to create caps
            if (i == 0) {
                // Bottom cap triangle fan
                m_indices.push_back(0);
                m_indices.push_back(index + 1);
                m_indices.push_back(index + 2);
            } else if (i == stackCount - 1) {
                // Top cap triangle fan
                int topCenterIndex = (stackCount + 1) * (sectorCount + 1);
                m_indices.push_back(topCenterIndex);
                m_indices.push_back(index + sectorCount + 2);
                m_indices.push_back(index + sectorCount + 1);
            }
        }
    }
}
void Cylinder::SetupMesh()
{
    m_mesh = Mesh(m_vertices, m_indices, m_texture);
}

void Cylinder::Render(Shader& shader, Camera& camera)
{
    shader.Activate();
    shader.setMat4("model", transform.getModelMatrix());
    m_mesh.Draw(shader, camera);
}
