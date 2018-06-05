#include "Model.h"

Model::Model()
{

}

Model::Model(Mesh* mesh, Material* material) :
	m_mesh(mesh),
	m_material(material)
{

}

Mesh* Model::getMesh()
{
	return m_mesh;
}

Material* Model::getMaterial()
{
	return m_material;
}

void Model::setMesh(Mesh* mesh)
{
	m_mesh = mesh;
}

void Model::setMaterial(Material* material)
{
	m_material = material;
}