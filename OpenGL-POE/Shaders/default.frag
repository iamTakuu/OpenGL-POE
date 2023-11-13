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


vec4 pointLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);

	// outputs final color
	return texture(tex0, texCoord) * (diffuse + ambient + specular) * lightColor;
}
vec4 spotLight()
{
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// No specular texture, so remove the specular texture sampling and calculations
	float specular = 0.0;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * (diffuse * inten + ambient)) * lightColor;
}

vec4 directionalLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(-lightPos); // Negate the light direction for a directional light
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);

	// outputs final color
	return texture(tex0, texCoord) * (diffuse + ambient + specular) * lightColor;
}

void main()
{
	// outputs final color
	//FragColor = directionalLight();
	FragColor = spotLight();
	//FragColor = pointLight();
}
