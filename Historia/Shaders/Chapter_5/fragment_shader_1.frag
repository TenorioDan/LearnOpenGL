#version 450 core

in vec4 vert_color;
out vec4 color;

layout (location = 2) uniform vec4 offset;

void main(void)
{
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	color = vert_color + offset;
}