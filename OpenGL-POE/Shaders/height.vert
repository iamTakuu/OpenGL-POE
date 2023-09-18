#version 330 core
layout (location = 0) in vec3 aPos;

out float Height;
out vec3 Position;

uniform mat4 model;
// The camera matrix
uniform mat4 camMatrix;

void main()
{
    Height = aPos.y;
    Position = (model * vec4(aPos, 1.0)).xyz;
    gl_Position = model * camMatrix * vec4(aPos, 1.0);
}