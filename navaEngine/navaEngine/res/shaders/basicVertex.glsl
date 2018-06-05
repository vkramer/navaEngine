#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 positionOut;
out vec2 texCoordOut;
out vec3 normalOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	
	positionOut = vec3(model * vec4(position, 1.0));
	normalOut = mat3(transpose(inverse(model))) * normal;  
	texCoordOut = texCoord;

	gl_Position = projection * view * model * vec4(position, 1.0);

}