#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the texture coordinate has attribute position 2

// Outputs the color to the fragment shader
out vec3 color;
// Outputs the texture coordinate to the fragment shader
out vec2 textCoord;

uniform float scale; // uniform variable for the scale of the triangle
void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   // Upside down triangle
   //gl_Position = vec4(-aPos.x + aPos.x * -scale, -aPos.y + aPos.y * -scale, -aPos.z + aPos.z * -scale, 1.0);
   color = 1 - aColor;
   textCoord = aTexCoord;	
}