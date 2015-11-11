#version 330 core

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D myTexture;

void main()
{
	vec4 spriteTexture = texture(myTexture, fragmentUV);
	
	color = fragmentColor * spriteTexture;
}