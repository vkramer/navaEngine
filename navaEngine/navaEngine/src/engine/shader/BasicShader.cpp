#include "BasicShader.h"

BasicShader::BasicShader() {
	addVertexShaderFromFile("basicVertex.glsl");
	addFragmentShaderFromFile("basicFragment.glsl");

	setAttributeLocation("position", 0);
	setAttributeLocation("texCoord", 1);

	compileShader();
}
