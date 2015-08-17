#version 330 core

in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec3 fragmentNormal;

out vec4 color;

uniform sampler2D myTexture;

uniform vec3 lightPosition;
uniform vec3 lightColor;

void main(void)
{
	vec3 unitNormal = normalize(fragmentNormal);
	vec3 unitVector = normalize(lightPosition - fragmentPosition);
	
	float ambientLevel = 0.1;
	
	float lightDot = dot(unitNormal, unitVector);
	float brightness = max(lightDot, ambientLevel);
	
	vec3 diffuse = brightness * lightColor;

	vec4 colorTex = texture(myTexture, fragmentUV);
	color = vec4(diffuse, 1.0) * colorTex;
}