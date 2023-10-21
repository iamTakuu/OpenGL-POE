#include "../Headers/Sphere.h"

Sphere::Sphere(GLfloat radius, GLint sectorCount, GLint stackCount)
{
    this->radius = radius;
    this->sectorCount = sectorCount;
    this->stackCount = stackCount;


	setVertices();
	setIndices();
    SetupMesh();
}

void Sphere::setVertices() {
    for (int i = 0; i <= stackCount; ++i) {

        float V = i / (float)stackCount;
        float phi = V * glm::pi <float>();

        // Loop Through Slices
        for (int j = 0; j <= sectorCount; ++j) {

            float U = j / (float)sectorCount;
            float theta = U * (glm::pi <float>() * 2);

            // Calc The Vertex Positions
            float x = cosf(theta) * sinf(phi);
            float y = cosf(phi);
            float z = sinf(theta) * sinf(phi);

            Vertex vertex{};

            vertex.Position = glm::vec3(x, y, z) * radius;
            vertex.Color = glm::vec3(1.0f, .0f, .0f);

            vertex.TexCoords.x = U;
            vertex.TexCoords.y = V;

            m_vertices.push_back(vertex);
        }
    }
}

void Sphere::setIndices()
{
    for (int i = 0; i < sectorCount * stackCount + sectorCount; ++i) {

        m_indices.push_back(i);
        m_indices.push_back(i + sectorCount + 1);
        m_indices.push_back(i + sectorCount);

        m_indices.push_back(i + sectorCount + 1);
        m_indices.push_back(i);
        m_indices.push_back(i + 1);
    }
}

void Sphere::SetupMesh()
{
   
    Texture texture = Texture("Textures/black.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
    //std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

    m_mesh = Mesh(m_vertices, m_indices, texture);
}

void Sphere::Render(Shader& shader, Camera& camera)
{
    shader.Activate();
    shader.setMat4("model", transform.getModelMatrix());
    //glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(parent_model * m_model));
	m_mesh.Draw(shader, camera);
}