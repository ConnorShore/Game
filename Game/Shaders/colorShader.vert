#version 330 core

in vec3 vertexPosition;
//in vec4 vertexColor;
in vec2 vertexUV;

//out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P;

void main(void)
{
	gl_Position = (P * vec4(vertexPosition, 1.0));
	//fragmentColor = vertexColor;
	fragmentUV = vertexUV;
}