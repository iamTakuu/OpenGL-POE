#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the texture coordinate has attribute position 2
layout (location = 3) in vec3 aNormal; // the normal variable has attribute position 3


// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the color to the fragment shader
out vec3 color;
// Outputs the texture coordinate to the fragment shader
out vec2 texCoord;
// Outputs the normal for the Fragment Shader
out vec3 Normal;


uniform vec3 camPos;
// The camera matrix
uniform mat4 camMatrix;
// The model matrix
uniform mat4 model;

void main()
{
   // calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = aNormal;
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTexCoord;
	
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * model * vec4(crntPos, 1.0);
}