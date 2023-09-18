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

	const int numStrips = (heightImg - 1) / rez;
	const int numTrisPerStrip = (widthImg / rez) * 2 - 2;
	std::cout << "Created lattice of " << numStrips << " strips with " << numTrisPerStrip << " triangles each" << std::endl;
	std::cout << "Created " << numStrips * numTrisPerStrip << " triangles total" << std::endl;


}	