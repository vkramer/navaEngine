#include "Node.h"


Node::Node() {

}

void Node::addChild(Node* child)
{
	child->setParent(this);
	m_children.push_back(child);
}

void Node::addComponent(Component* component)
{
	component->setParent(this);
	m_components.push_back(component);
}

void Node::input(float delta)
{
	m_transform.update();
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->input(delta);
	}

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->input(delta);
	}
}

void Node::update(float delta)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->update(delta);
	}

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->update(delta);
	}
}

void Node::render(RenderingEngine* renderingEngine)
{
	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->render(renderingEngine);
	}

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->render(renderingEngine);
	}
}

void Node::addToRenderingEngine(RenderingEngine* renderingEngine) {
	for (auto const& component : m_components)
		component->addToRenderingEngine(renderingEngine);

	for (auto const& child : m_children)
		child->addToRenderingEngine(renderingEngine);
}

Transform& Node::getTransform()
{
	return m_transform;
}

Node* Node::getParent()
{
	return m_parent;
}

std::vector<Node*> Node::getChildren()
{
	return m_children;
}

void Node::setParent(Node* parent)
{
	m_parent = parent;
}
