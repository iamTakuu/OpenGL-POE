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
            vertex.Color = glm::vec3(.2f, .0f, .4f);

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
    Texture textures[] =
    {
        // Leave textType blank for now, later we will use it to determine the type of texture.
        // Like diffuse, specular, etc.
        //Texture("Textures/pop_cat.png", "", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("Textures/white.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE), // Text Index: 0
        Texture("Textures/black.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE) // Text Index: 1
    };

    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

    m_mesh = Mesh(m_vertices, m_indices, tex, 0);
}

void Sphere::Render(Shader& shader, Camera& camera)
{
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
	m_mesh.Draw(shader, camera);
}