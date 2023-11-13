#version 330 core

// Colors in RGBA format
out vec4 FragColor; 
// Imports the current color from the Vertex Shader
in vec3 color;
// Imports the current texture coordinate from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Your standard texture sampler, use this for diffuse maps
uniform sampler2D tex0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;




void main()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// No specular lighting, so remove the specular calculations
	float specular = 0.0;

	// outputs final color
	FragColor = texture(tex0, texCoord) * (diffuse + ambient) * lightColor;
}
