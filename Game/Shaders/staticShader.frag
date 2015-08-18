#version 330 core

in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec3 fragmentNormal;

in vec3 toCameraVec;

out vec4 color;

uniform sampler2D myTexture;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform float shineLevel;
uniform float shineDamp;

void main(void)
{
	vec3 unitNormal = normalize(fragmentNormal);
	vec3 unitLightVector = normalize(lightPosition - fragmentPosition);
	vec3 unitCamera = normalize(toCameraVec);
	
	vec3 lightDirection = -unitLightVector;
	vec3 reflectDirection = reflect(lightDirection, unitNormal);
	
	float ambientLevel = 0.1;
	
	float lightDot = clamp(dot(unitNormal, unitLightVector), 0, 1);
	float brightness = max(lightDot, ambientLevel);
	
	float specularFactor = dot(reflectDirection, unitCamera);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, shineDamp);
	vec3 finalSpecular = dampedFactor * lightColor;
	
	vec3 diffuse = brightness * lightColor;

	vec4 colorTex = texture(myTexture, fragmentUV);
	color = (vec4(diffuse, 1.0) + vec4(finalSpecular, 1.0)) * colorTex;
}