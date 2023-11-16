#include "../Headers/Sphere.h"

Sphere::Sphere(GLfloat radius, GLint sectorCount, GLint stackCount, const Texture& texture)
{
    this->radius = radius;
    this->sectorCount = sectorCount;
    this->stackCount = stackCount;
    this->m_texture = texture;


	setVertices();
	setIndices();
    //calculateNormals();
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
            vertex.Color = glm::vec3(1.0f, 1.0f, 1.0f);
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
void Sphere::calculateNormals()
{
    // Initialize normals to zero
    for (unsigned i = 0; i < m_vertices.size(); ++i)
    {
        m_vertices[i].Normal = glm::vec3(0.0f);
    }

    // Calculate normals
    for (int i = 0; i < m_indices.size(); i += 3)
    {
        unsigned int index1 = m_indices[i];
        unsigned int index2 = m_indices[i + 1];
        unsigned int index3 = m_indices[i + 2];

        glm::vec3 v1 = m_vertices[index1].Position;
        glm::vec3 v2 = m_vertices[index2].Position;
        glm::vec3 v3 = m_vertices[index3].Position;

        glm::vec3 edge1 = v2 - v1;
        glm::vec3 edge2 = v3 - v1;

        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

        // Accumulate normals for each vertex
        m_vertices[index1].Normal += normal;
        m_vertices[index2].Normal += normal;
        m_vertices[index3].Normal += normal;
    }

    // Normalize all normals
    for (unsigned i = 0; i < m_vertices.size(); ++i)
    {
        m_vertices[i].Normal = glm::normalize(m_vertices[i].Normal);
    }
}

void Sphere::SetupMesh()
{
    m_mesh = Mesh(m_vertices, m_indices, m_texture);
}

void Sphere::Render(Shader& shader, Camera& camera)
{
    shader.Activate();
    shader.setMat4("model", transform.getModelMatrix());
    m_mesh.Draw(shader, camera);
}