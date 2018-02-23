#include "TestGame.h"
#include "../engine/geometry/Vertex.h"
#include "../engine/shader/BasicShader.h"

void TestGame::init() {
	
	// Manual Created Vertex Array( currently only passing in vertex position )
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(-0.5f,  -0.5f, 0.0f), glm::vec2(0, 0)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1, 0)),
		Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1, 1)),
		Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0, 1))
	};

	// Manually created Index Array
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	// New Mesh passing in vertex and index arrays
	mesh = new Mesh(vertices, indices);

	// New shader calling BasicShader singleton
	shader = BasicShader::getInstance();

	// New texture
	// UV_Grid Texture courtesy of (http://www.pixelcg.com/blog/?p=146)
	texture = new Texture("res/textures/uv_grid.jpg");
}

void TestGame::render() {
	// Use to Enable Polygon Rendering instead of Fill
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Bind the Shader
	shader->bind();
	// Bind the Texture
	texture->bind();
	// Send Mesh to GPU to Render
	mesh->draw();
}