#include "TestGame.h"
#include "../engine/components/model/Vertex.h"
#include "../engine/shader/BasicShader.h"
#include "../engine/components/renderer/Renderer.h"
#include "../engine/components/camera/Camera.h"

#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void TestGame::init()
{
	// Manual Created Vertex Array( currently only passing in vertex position )
	std::vector<Vertex> vertices = {
		// Back
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)),

		// Front
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),

		// Top
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),

		// Bottom
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),

		// Right
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f,  -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),

		// Left
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, 0.5f,  -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f))
	};

	// Manually created Index Array
	std::vector<unsigned int> indices = {
		0,  1,  2,      0,  2,  3,    // front
		4,  5,  6,      4,  6,  7,    // back
		8,  9,  10,     8,  10, 11,   // top
		12, 13, 14,     12, 14, 15,   // bottom
		16, 17, 18,     16, 18, 19,   // right
		20, 21, 22,     20, 22, 23,   // left
	};

	Camera* mainCamera = new Camera(glm::radians(45.0f), (float)Window::getWidth() / (float)Window::getHeight(), 0.1f, 1000.0f);

	Model* testModel1 = new Model(new Mesh(vertices, indices), new Material(new Texture("res/textures/wood2.jpg")));
	Model* testModel2 = new Model(new Mesh(vertices, indices), new Material(new Texture("res/textures/stone2.jpg")));
	Model* testModel3 = new Model(new Mesh(vertices, indices), new Material(new Texture("res/textures/uv_grid.jpg")));

	Shader* shader = BasicShader::getInstance();

	Node* cameraNode = new Node();
	cameraNode->addComponent(mainCamera);
	cameraNode->getTransform().setPos(glm::vec3(0.0f, 0.0f, -3.0f));

	cubeNodeTest = new Node();
	cubeNodeTest->addComponent(new Renderer(testModel1, shader));
	cubeNodeTest->getTransform().setPos(glm::vec3(-1.0f, 0.0f, 0.0f));

	cubeNodeTest2 = new Node();
	cubeNodeTest2->addComponent(new Renderer(testModel2, shader));
	cubeNodeTest2->getTransform().setPos(glm::vec3(1.0f, 0.0f, 0.0f));
	cubeNodeTest2->getTransform().setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	cubeNodeTest3 = new Node();
	cubeNodeTest3->addComponent(new Renderer(testModel3, shader));
	cubeNodeTest3->getTransform().setPos(glm::vec3(0, 0, 3));

	addToScene(cameraNode);
	addToScene(cubeNodeTest);
	addToScene(cubeNodeTest2);
	addToScene(cubeNodeTest3);
}

void TestGame::update(float delta)
{
	cubeNodeTest->getTransform().rotate(glm::vec3(0, 1, 0), delta);
	cubeNodeTest2->getTransform().rotate(glm::vec3(1, 0, 0), delta);
	cubeNodeTest3->getTransform().rotate(glm::vec3(1, 0, 1), delta);
}
