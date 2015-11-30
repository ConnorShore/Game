#version 330 core

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

void main()
{
	float distance = length(fragmentUV);

	color = vec4(fragmentColor.rgb, fragmentColor.a * 1.0 - distance);
}