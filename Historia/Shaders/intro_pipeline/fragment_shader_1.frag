#version 450 core

out vec4 color;

void main(void)
{
	color = vec4(0.0, 0.8, 1.0, 1.0);
}

//in VS_OUT
//{
//	vec4 color;
//} fs_in;

// Output to the frame buffer
//out vec4 color;

//void main(void)
//{
//	color = fs_in.color;
//}