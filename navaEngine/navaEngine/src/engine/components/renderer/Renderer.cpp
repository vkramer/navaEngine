#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Renderer::Renderer(Model* model, Shader* shader) :
	m_model(model),
	m_shader(shader)
{

}

void Renderer::render(RenderingEngine* renderingEngine)
{
	glm::mat4 model;
	model = glm::translate(model, getTransform().getPos());
	model = glm::rotate(model, (float)glfwGetTime() * getTransform().getPos().x, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, getTransform().getScale());

	m_shader->bind();

	//m_shader->setUniform("model", model);
	//m_shader->setUniform("view", view);
	
	m_shader->updateUniforms(getTransform(), *m_model, renderingEngine);

	m_model->getMesh()->draw();
}