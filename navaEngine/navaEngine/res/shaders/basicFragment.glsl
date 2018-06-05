#version 330 core

struct Light {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
};

in vec2 texCoordOut;
in vec3 normalOut;
in vec3 positionOut;

out vec4 fragColor;

uniform sampler2D sampler;
uniform Light light;

void main() {
	vec3 ambient = light.ambient * texture(sampler, texCoordOut).rgb;
	vec3 norm = normalize(normalOut);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);

	vec3 diffuse = light.diffuse * diff * texture(sampler, texCoordOut).rgb;

	//vec4 textureColor = ambient * texture(sampler, texCoordOut.xy);

	vec3 specular = vec3(0.2, 0.5, 0.2);

	vec3 result = ambient + diffuse;

	fragColor = vec4(result, 1.0);
}