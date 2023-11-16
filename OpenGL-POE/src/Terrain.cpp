#include "../Headers/Terrain.h"

Terrain::Terrain(const char* heightMap)
{
   
    m_texture = Texture("Textures/rocks.png", "", 0);
    m_data = stbi_load(heightMap, &m_width, &m_height, &m_nrChannels, 0);
    if (m_data)
    {
        std::cout << "Loaded heightmap of size " << m_height << " x " << m_width << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    setVertices();
    setIndices();
    SetupMesh();
}

void Terrain::setVertices()
{
    const float yScale = 64.0f / 256.0f;
    const float yShift = 16.0f;
    //int rez = 1;
    const unsigned bytePerPixel = m_nrChannels;

    // Clear any existing vertices
    m_vertices.clear();
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            unsigned char* pixelOffset = m_data + (j + m_width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

            Vertex vertex{};
            auto xCord = -m_height / 2.0f + m_height * i / (float)m_height;    // vx
            auto yCord= (int)y * yScale - yShift;                       // vy
            auto zCord = -m_width / 2.0f + m_width * j / (float)m_width;       // vz

            vertex.Position = glm::vec3(xCord, yCord, zCord);
            vertex.Color = glm::vec3(1.0f, 1.0f, 1.0f);
            vertex.TexCoords.x = j / (float)(m_width - 1);
            vertex.TexCoords.y = i / (float)(m_height - 1);
            //calculateNormals();
            // Calculate normals
            // Calculate normals using Perlin noise gradient
            if (i > 0 && j > 0)
            {
                glm::vec3 v1 = m_vertices.back().Position;
                glm::vec3 v2 = m_vertices[m_vertices.size() - m_width].Position;
                glm::vec3 v3 = m_vertices[m_vertices.size() - 1].Position;

                glm::vec3 normal = glm::triangleNormal(v1, v2, v3);

                // Assign normals to the current vertex
                vertex.Normal = glm::normalize(normal);
            }


            m_vertices.push_back(vertex);
        }
    }
    std::cout << "Loaded " << m_vertices.size() / 3 << " vertices" << std::endl;
}

void Terrain::setIndices()
{
    for (unsigned i = 0; i < m_height - 1; i++)
    {
        for (unsigned j = 0; j < m_width - 1; j++)
        {
            m_indices.push_back(j + m_width * i);
            m_indices.push_back(j + m_width * (i + 1));
            m_indices.push_back(j + 1 + m_width * i);

            m_indices.push_back(j + 1 + m_width * i);
            m_indices.push_back(j + m_width * (i + 1));
            m_indices.push_back(j + 1 + m_width * (i + 1));
        }
    }
}
void Terrain::calculateNormals()
{
    for (unsigned i = 0; i < m_indices.size(); i += 3)
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

        // Assign normals to vertices
        m_vertices[index1].Normal += normal;
        m_vertices[index2].Normal += normal;
        m_vertices[index3].Normal += normal;
    }

    // Normalize normals
    for (unsigned i = 0; i < m_vertices.size(); ++i)
    {
        m_vertices[i].Normal = glm::normalize(m_vertices[i].Normal);
    }
}

void Terrain::Render(Shader& shader, Camera& camera)
{
    shader.Activate();
    shader.setMat4("model", transform.getModelMatrix());
    m_mesh.Draw(shader, camera);
}

void Terrain::SetupMesh()
{
    m_mesh.isTerrain(m_width, m_height, 1);
    m_mesh = Mesh(m_vertices, m_indices, m_texture);
}
