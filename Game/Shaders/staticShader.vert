#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragmentPosition;
out vec2 fragmentUV;
out vec3 fragmentNormal;

out vec3 toLightVector[4];

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition[4];

void main(void)
{
	vec4 worldPos = modelMatrix * vec4(vertexPosition, 1.0);
	mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	
	gl_Position = (MVP * vec4(vertexPosition, 1.0));
	
	for(int i = 0; i < 4; i++) {
		toLightVector[i] = lightPosition[i] - worldPos.xyz;
	}
	
	fragmentPosition = worldPos.xyz;
	fragmentUV = vertexUV;
	fragmentNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
}