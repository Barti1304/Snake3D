#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

struct SpotLight
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};
uniform SpotLight spotLight;

uniform vec3 ViewPos;

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(ViewPos - FragPos);

	vec3 result = CalcSpotLight(spotLight, normal, FragPos, viewDir);

	FragColor = vec4(result, 1);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float diff = max(dot(lightDir, normal), 0);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	float distance = length(light.position - fragPos);
	float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0, 1);

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	vec3 result = ambient + diffuse + specular;
	return result;
}