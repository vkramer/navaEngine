#include "TestGame.h"
#include "../engine/geometry/Vertex.h"
#include "../engine/shader/BasicShader.h"

void TestGame::init() {
	
	// Manual Created Vertex Array( currently only passing in vertex position )
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(-0.5f,  -0.5f, 0.0f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f))
	};

	// Manually created Index Array
	std::vector<unsigned int> indices = {
		0,1,2
	};

	// New Mesh passing in vertex and index arrays
	mesh = new Mesh(vertices, indices);

	// New shader calling BasicShader singleton
	shader = BasicShader::getInstance();
}

void TestGame::render() {
	// Bind the Shader
	shader->bind();
	// Send Mesh to GPU to Render
	mesh->draw();
}