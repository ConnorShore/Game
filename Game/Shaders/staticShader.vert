#version 330 core

in vec3 vertexPosition;
in vec2 vertexUV;

out vec2 fragmentUV;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

void main(void)
{
	gl_Position = (cameraMatrix * modelMatrix * vec4(vertexPosition, 1.0));
	fragmentUV = vertexUV;
}