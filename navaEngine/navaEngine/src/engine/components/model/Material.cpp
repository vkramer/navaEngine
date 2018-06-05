#include "Material.h"

Material::Material()
{

}

Material::Material(Texture* diffuse) :
	m_diffuse(diffuse)
{

}

Material::Material(glm::vec3 color) :
	m_color(color)
{

}

char Material::getName()
{
	return m_name;
}

Texture* Material::getDiffuse()
{
	return m_diffuse;
}

Texture* Material::getNormal()
{
	return m_normal;
}

glm::vec3 Material::getColor()
{
	return m_color;
}

void Material::setDiffuse(Texture* diffuse)
{
	m_diffuse = diffuse;
}

void Material::setNormal(Texture* normal)
{
	m_normal = normal;
}

void Material::setColor(glm::vec3 color)
{
	m_color = color;
}