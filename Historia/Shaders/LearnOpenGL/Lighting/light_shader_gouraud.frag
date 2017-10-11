#version 450 core

in vec4 VertColor;

out vec4 FragColor;

void main(void)
{
	FragColor = VertColor;
}