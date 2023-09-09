#include "../Headers/Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void Mesh::createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)
{

	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);



#pragma region creating VBO
	//create a buffer object
	// 1 buffer and assign the ID to VBO
	glGenBuffers(1, &VBO);

	//binding the VBO
	//Define which buffer to bind to (Multiple buffers availble)
	//using the array buffer, buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//connect the buffer data
	// takes 4 arguements
	//(Target, sizeOfData, data,Static/dynamic_draw)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	//(LocationOfAttribute,
	//XYZ which are 3 values,
	//TypeOfValues, 
	//NormaliseValues,
	//Stride(take a vertex value and skip n amount)
	// Offset(where the data starts))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
	//                     \\
 			//                      \\   
			 //enable Attribute 0     \/
	glEnableVertexAttribArray(0);

	//for textures
	//stride 3
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	//unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#pragma endregion
	glBindVertexArray(0);



}

void Mesh::renderMesh()
{

	glBindVertexArray(VAO); // binding the VAO (working with the VAO)

	//glDrawArrays(GL_TRIANGLES, 0, 3);//(mode, starting pos, number of points)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbind


}

void Mesh::clearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

Mesh::~Mesh()
{
	clearMesh();
}