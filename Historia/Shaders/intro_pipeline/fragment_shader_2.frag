#version 450 core

in VS_OUT
{
	vec4 color;
} fs_in;

// Output to the frame buffer
out vec4 color;

void main(void)
{
	color = fs_in.color;
}