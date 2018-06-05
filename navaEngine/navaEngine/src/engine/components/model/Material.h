#pragma once

#include <glm/glm.hpp>

#include "../../texture/Texture.h"

class Material
{
public:
	Material();
	Material(Texture* diffuse);
	Material(glm::vec3 color);
	~Material() {};

	char getName();
	Texture* getDiffuse();
	Texture* getNormal();
	glm::vec3 getColor();

	void setDiffuse(Texture* diffuse);
	void setNormal(Texture* normal);
	void setColor(glm::vec3 color);

private:
	char m_name;
	Texture* m_diffuse;
	Texture* m_normal;
	glm::vec3 m_color;
};