#version 330 core

in vec2 texCoord0;

out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main() {
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoord0).r);
	color = vec4(textColor, 0.5) * sampled;
}
