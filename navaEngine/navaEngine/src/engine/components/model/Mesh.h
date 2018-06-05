#pragma once

#include <glad/glad.h>

#include "Vertex.h"

#include <iostream>
#include <vector>
#include <string>

class Mesh {

public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	~Mesh();

	void draw() const;

private:
	unsigned int m_vao;		// Vertex Array Object
	unsigned int m_vbo;		// Vertex Buffer Object
	unsigned int m_ibo;		// Index Buffer Object
	int m_size;				// Index Size

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	void generateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
};
