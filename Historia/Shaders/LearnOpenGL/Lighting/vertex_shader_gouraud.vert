#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec3 Normal;
out vec4 VertColor;

void main(void)
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vec3 position = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal; // create the normal matrix for non uniform scales 

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	float diffuseStrength = 1.0f;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseStrength * diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	VertColor = vec4(result, 1.0);
}