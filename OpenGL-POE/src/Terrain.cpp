#include "../Headers/Terrain.h"

Terrain::Terrain(const char* img)
{
	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(img, &widthImg, &heightImg, &numColCh, 0);

	if (bytes)
	{
		std::cout << "Loaded heightmap of size " << heightImg << " x " << widthImg << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	float yScale = 64.0f / 256.0f, yShift = 16.0f;
	int rez = 1;
	unsigned bytePerPixel = numColCh;

	for (int i = 0; i < heightImg; i++)
	{
		for (int j = 0; j < widthImg; j++)
		{
			unsigned char* pixelOffset = bytes + (j + widthImg * i) * bytePerPixel;
			unsigned char y = pixelOffset[0];

			// vertex
			terrain_vertices.push_back(-heightImg / 2.0f + heightImg * i / (float)heightImg);   // vx
			terrain_vertices.push_back((int)y * yScale - yShift);   // vy
			terrain_vertices.push_back(-widthImg / 2.0f + widthImg * j / (float)widthImg);   // vz
		}
	}
	std::cout << "Loaded " << terrain_vertices.size() / 3 << " vertices" << std::endl;
	stbi_image_free(bytes);

	for (unsigned i = 0; i < heightImg - 1; i += rez)
	{
		for (unsigned j = 0; j < widthImg; j += rez)
		{
			for (unsigned k = 0; k < 2; k++)
			{
				terrain_indices.push_back(j + widthImg * (i + k * rez));
			}
		}
	}
	std::cout << "Loaded " << terrain_indices.size() << " indices" << std::endl;

	numStrips = (heightImg - 1) / rez;
	numTrisPerStrip = (widthImg / rez) * 2 - 2;
	std::cout << "Created lattice of " << numStrips << " strips with " << numTrisPerStrip << " triangles each" << std::endl;
	std::cout << "Created " << numStrips * numTrisPerStrip << " triangles total" << std::endl;


	// first, configure the cube's VAO (and terrainVBO + terrainIBO)
	glGenBuffers(1, &terrainVBO);
	glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBufferData(GL_ARRAY_BUFFER, terrain_vertices.size() * sizeof(float), &terrain_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// position attribute

	//Draw(shader, camera);
	glGenVertexArrays(1, &terrainVAO);
	glBindVertexArray(terrainVAO);

	//Camera
	//glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

	glGenBuffers(1, &terrainIBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrain_indices.size() * sizeof(unsigned), &terrain_indices[0], GL_STATIC_DRAW);


}	

void Terrain::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();
	
	// Bind the model matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	camera.Matrix(shader, "camMatrix");

	glBindVertexArray(terrainVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);
	for (unsigned strip = 0; strip < numStrips; strip++)
	{
		glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
			numTrisPerStrip + 2,   // number of indices to render
			GL_UNSIGNED_INT,     // index data type
			(void*)(sizeof(unsigned) * (numTrisPerStrip + 2) * strip)); // offset to starting index
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);

	glBindVertexArray(0);

	//glDrawElements(GL_TRIANGLE_STRIP, terrain_indices.size(), GL_UNSIGNED_INT, 0);
}