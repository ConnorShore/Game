#version 330 core

in vec2 fragmentUV;

out vec4 color;

uniform sampler2D testTex;

void main(void)
{
	vec4 colorTex = texture(testTex, fragmentUV);
	color = colorTex;
}