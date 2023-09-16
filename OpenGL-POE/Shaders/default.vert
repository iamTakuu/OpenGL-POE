#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the texture coordinate has attribute position 2

// Outputs the color to the fragment shader
out vec3 color;
// Outputs the texture coordinate to the fragment shader
out vec2 textCoord;

uniform mat4 camMatrix;

void main()
{
   gl_Position = camMatrix * vec4(aPos, 1.0f);
   color = 1 - aColor;
   textCoord = aTexCoord;	
}