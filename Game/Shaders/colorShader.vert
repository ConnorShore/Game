#version 330 core

in vec3 vertexPosition;
in vec2 vertexUV;

out vec2 fragmentUV;

uniform mat4 P;

void main(void)
{
	gl_Position = (P * vec4(vertexPosition, 1.0));
	fragmentUV = vertexUV;
}