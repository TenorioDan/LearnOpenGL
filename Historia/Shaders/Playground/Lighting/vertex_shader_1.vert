#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 MVP;
uniform mat4 model;
uniform float angleSin;
uniform float angleCos;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

vec4 quaternionMultiplication(vec4 quat1, vec4 quat2);

void main(void)
{
	//vec3 unitY = vec3(0.0, 1.0, 0.0);
	vec4 posQuaternion = vec4(aPos, 0.0);
	vec4 rotQuaternion = vec4(0.0, angleSin, 0.0, angleCos);
	posQuaternion = quaternionMultiplication(vec4(-rotQuaternion.x, -rotQuaternion.y, -rotQuaternion.z, rotQuaternion.w), posQuaternion);
	posQuaternion = quaternionMultiplication(posQuaternion, rotQuaternion);
	gl_Position = MVP * vec4(posQuaternion.xyz, 1.0);
	

	FragPos = vec3(model * vec4(posQuaternion.xyz, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal; // create the normal matrix for non uniform scales 
	TexCoords = aTexCoords;
}

vec4 quaternionMultiplication(vec4 quat1, vec4 quat2)
{
	return vec4(
		(	quat1.w*quat2.x + quat1.x*quat2.w - quat1.y*quat2.z + quat1.z*quat2.y 	),
		(	quat1.w*quat2.y + quat1.x*quat2.z + quat1.y*quat2.w - quat1.z*quat2.x 	),
		(	quat1.w*quat2.z - quat1.x*quat2.y + quat1.y*quat2.x + quat1.z*quat2.w 	),
		(	quat1.w*quat2.w - quat1.x*quat2.x - quat1.y*quat2.y - quat1.z*quat2.z 	)
	);
}