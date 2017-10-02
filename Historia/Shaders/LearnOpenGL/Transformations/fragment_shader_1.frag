#version 450 core

out vec4 color;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(void)
{
	color = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}