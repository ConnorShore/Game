#version 330 core

in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec3 fragmentNormal;
in vec3 toLightVector[4];

out vec4 color;

uniform sampler2D myTexture;

uniform vec3 lightColor[4];

void main(void)
{
	float ambientLevel = 0.2;
	
	vec3 totalDiffuse = vec3(0.0);
	
	for(int i = 0; i < 4; i++) {
		vec3 unitNormal = normalize(fragmentNormal);
		vec3 unitLightVector = normalize(toLightVector[i]);
		
		float lightDot = clamp(dot(unitNormal, unitLightVector), 0, 1);
		float brightness = max(lightDot, 0.0);
		
		totalDiffuse = totalDiffuse + brightness * lightColor[i];
	}
	
	totalDiffuse = max(totalDiffuse, ambientLevel);
	
	vec4 colorTex = texture(myTexture, fragmentUV);
	color = (vec4(totalDiffuse, 1.0)) * colorTex;
}