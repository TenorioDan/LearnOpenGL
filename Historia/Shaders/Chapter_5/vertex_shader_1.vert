#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

//layout (location = 2) uniform vec4 offset;

out vec4 vert_color;

uniform TransformBlock
{
	float scale;		// Global scale to apply to everything
	vec3 translation;	// Translation in X, Y, and Z
	float rotation[3];	// Rotation around X, Y, and Z axes
	mat4 project_matrix; // A generalized project matrix to apply after scale and rotate
}  transform;

void main(void)
{
	gl_Position = position;
	vert_color = position;
}