#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 m_position;
	glm::vec2 m_textureCoord;
	//glm::vec3 m_normal;
	// TODO : add tangent
	// TODO : add bitTangent

	Vertex(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec2 textureCoord = glm::vec2(0, 0)) {
		this->m_position = position;
		this->m_textureCoord = textureCoord;
	}
};
