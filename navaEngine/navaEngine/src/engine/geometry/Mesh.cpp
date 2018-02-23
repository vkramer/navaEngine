#include "Mesh.h"

// BASE MESH CONSTRUCTOR
Mesh::Mesh() :
	m_vbo(0),
	m_vao(0),
	m_ibo(0),
	m_size(0)
{

}

// MESH OVERLOAD PASSING IN VERTEX AND INDEX ARRAYS
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	generateMesh(vertices, indices);
}

// DESTRUCTOR
Mesh::~Mesh() {
	if (m_vbo) glDeleteBuffers(1, &m_vbo);
	if (m_ibo) glDeleteBuffers(1, &m_ibo);
	if (m_vao) glDeleteVertexArrays(1, &m_vao);
}

// GENERATE A MESH BASED ON PASSED IN VERTEX AND INDEX ARRAYS
void Mesh::generateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	if (!m_vao) glGenVertexArrays(1, &m_vao);
	if (!m_vbo) glGenBuffers(1, &m_vbo);
	if (!m_ibo) glGenBuffers(1, &m_ibo);
	m_size = indices.size();

	glBindVertexArray(m_vao);

	// VERTEX BUFFER OBJECT
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// INDEX BUFFER OBJECT
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// VERTEX ATTRIBUTE POINTERS (POSITION, TEXTURE COORDINATES, NORMALS)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_textureCoord));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));
}

// SEND MESH TO GPU TO RENDER
void Mesh::draw() const {
	// BIND VERTEX ARRAY
	glBindVertexArray(m_vao);

	// ENABLE VERTEX ATTRIBUTE ARRAYS
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// DRAW THE DAMN TRIANGLES
	glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);

	// DISABLE VERTEX ATTRIBUTE ARRAYS
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// UNBIND VERTEX ARRAY
	glBindVertexArray(0);
}