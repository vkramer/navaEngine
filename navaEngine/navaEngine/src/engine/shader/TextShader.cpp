#include "TextShader.h"

TextShader::TextShader() {
	addVertexShaderFromFile("textVertex.glsl");
	addFragmentShaderFromFile("textFragment.glsl");

	setAttributeLocation("vertex", 0);

	compileShader();

	addUniform("projection");
	addUniform("textColor");
}

void TextShader::updateX() {

	glm::mat4 projection = glm::ortho(0.0f, (float)1600, 0.0f, (float)900);
	glm::vec3 textColor = glm::vec3(1.0f, 1.0f, 1.0f);

	setUniform("projection", projection);
	setUniform("textColor", textColor);
}
