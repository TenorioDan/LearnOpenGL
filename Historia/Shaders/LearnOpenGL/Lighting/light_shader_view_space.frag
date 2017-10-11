#version 450 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in mat4 viewMatrix;

out vec4 FragColor;

void main(void)
{	

	vec3 lightPosView = vec3(viewMatrix * vec4(lightPos, 1.0));

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	float diffuseStrength = 1.0f;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosView - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseStrength * diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}