#version 450 core

layout (location = 0) in vec4 offset;

// vs_color is an output that will be sent to the next shader stage
out VS_OUT
{
	vec4 color;
} vs_out;


void main(void)
{
	const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),
									 vec4(-0.25, -0.25, 0.5, 1.0),
									 vec4( 0.25,  0.25, 0.5, 1.0));
	const vec4 colors[] = vec4[3](vec4( 1.0, 0.0, 0.0, 1.0),
								  vec4( 0.0, 1.0, 0.0, 1.0),
								  vec4( 0.0, 0.0, 1.0, 1.0));

	// Add 'offset' to ouir hard-coded vertex position
	gl_Position = vertices[gl_VertexID] + offset;

	// Output a fixed value for vs_color;
	vs_out.color = colors[gl_VertexID];
}