#version 330 core

// Colors in RGBA format
out vec4 FragColor; 
// Imports the current color from the Vertex Shader
in vec3 color;
// Imports the current texture coordinate from the Vertex Shader
in vec2 texCoord;

uniform sampler2D tex0;


void main()
{
	FragColor = texture(tex0, texCoord) * vec4(color, 1.0);
	//FragColor = texture(tex0, texCoord);
}