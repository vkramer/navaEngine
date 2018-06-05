#include "RenderingEngine.h"
#include "CoreEngine.h"
#include "../../modules/font/Font.h"
#include "../shader/TextShader.h"
#include <string>
#include "InputHandler.h"

RenderingEngine::RenderingEngine()
{

}

//RenderingEngine::RenderingEngine(Window& window) : m_window(&window) 
//{
//	std::cout << "RenderingEngine constructed" << std::endl;
//}

void RenderingEngine::init()
{
	std::cout << "RenderingEngine Initialized" << std::endl;

	//m_mainCamera = new Camera(60.0f, (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f);


	// TEST FONT
	font = new Font("res/fonts/Roboto-LightItalic.ttf");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	//glEnable(GL_CULL_FACE);
}

void RenderingEngine::render(Node* rootNode)
{
	// Add Camera To Root Scenegraph Node
	rootNode->addToRenderingEngine(this);

	if (!m_mainCamera)
	{
		std::cout << "Main Camera Does Not Exist" << std::endl;
		exit(-1);
	}

	// Clear Screen
	Window::clear();

	// Render Scenegraph
	rootNode->render(this);

	// Render Debugging Text
	font->drawText(*TextShader::getInstance(), "OpenGL:  4.5.0 - BUILD 22.20.16.4749", 10.0f, Window::getHeight() - 30.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	font->drawText(*TextShader::getInstance(), "FPS:  " + std::to_string(CoreEngine::fps), 10.0f, Window::getHeight() - 60.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	font->drawText(*TextShader::getInstance(), "MS:  " + std::to_string((float)1000 / CoreEngine::fps) + " ms", 10.0f, Window::getHeight() - 90.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
	font->drawText(*TextShader::getInstance(), "TIME:  " + std::to_string(glfwGetTime()), 10.0f, Window::getHeight() - 120.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));

	font->drawText(
		*TextShader::getInstance(),
		"Camera Position: [ x: " +
		std::to_string(m_mainCamera->getTransform().getPos().x) +
		"f y: " +
		std::to_string(m_mainCamera->getTransform().getPos().y) +
		"f z: " +
		std::to_string(m_mainCamera->getTransform().getPos().z) +
		"f ]",

		10.0f, 15.0f, 0.4f,
		glm::vec3(1.0f, 1.0f, 1.0f)
	);

}

