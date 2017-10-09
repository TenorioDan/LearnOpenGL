#version 450 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main(void)
{
	FragColor = vec4(lightColor * objectColor, 1.0);
}