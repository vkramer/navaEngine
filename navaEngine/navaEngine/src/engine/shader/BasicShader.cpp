#include "BasicShader.h"

BasicShader::BasicShader()
{
	addVertexShaderFromFile("basicVertex.glsl");
	addFragmentShaderFromFile("basicFragment.glsl");

	setAttributeLocation("position", 0);
	setAttributeLocation("texCoord", 1);

	compileShader();

	addUniform("sampler");
	addUniform("model");
	addUniform("view");
	addUniform("projection");
	
	addUniform("light.ambient");
	addUniform("light.direction");
	addUniform("light.diffuse");
}

void BasicShader::updateUniforms(Transform& transform, Model& model, RenderingEngine* renderingEngine)
{
	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(60.0f), (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f);
	view = glm::translate(view, renderingEngine->getMainCamera().getTransform().getPos());
	model.getMaterial()->getDiffuse()->bind();

	setUniformi("sampler", model.getMaterial()->getDiffuse()->getTextureID());
	setUniform("model", transform.getWorldMatrix());
	setUniform("projection", renderingEngine->getMainCamera().getProjectionMatrix());
	setUniform("view", renderingEngine->getMainCamera().getViewMatrix());

	setUniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	setUniform("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	setUniform("light.direction", glm::vec3(0.0f, 0.0f, 1.0f));
}

