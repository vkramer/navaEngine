#include "Component.h"
#include "../scenegraph/Node.h"

void Component::input(float delta)
{

}

void Component::update(float delta)
{

}

void Component::render(RenderingEngine* renderingEngine)
{
	//std::cout << "Rendering" << std::endl;
}

void Component::setParent(Node* parentNode)
{
	m_parent = parentNode;
}

Transform& Component::getTransform()
{
	return m_parent->getTransform();
}