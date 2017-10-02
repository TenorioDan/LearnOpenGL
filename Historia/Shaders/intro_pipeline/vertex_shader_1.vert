#version 450 core


// offset and color ar input vertex attributes
layout (location = 0) in vec4 offset;
layout (location = 1) in vec4 color;

// Declare VS_OUT as an output interface block
//out VS_OUT
//{
//	vec4 color;
//} vs_out;


void main(void)
{
	// Declare a hard-code array of positons
	const vec4 vertices[3] = vec4[3](vec4(  0.25, -0.25, 0.5, 1.0),
									 vec4( -0.25, -0.25, 0.5, 1.0),
									 vec4(  0.25,  0.25, 0.5, 1.0));
	// Index into our array using gl_VertexID
	gl_Position = vertices[gl_VertexID] + offset;

	// output a fixed value for vs_color
	//vs_out.color = color;
}