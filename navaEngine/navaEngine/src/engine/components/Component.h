#pragma once

#include "../scenegraph/Transform.h"


class Node;
class RenderingEngine;

class Component
{
public:
	virtual ~Component() {}

	virtual void input(float delta);
	virtual void update(float delta);
	virtual void render(RenderingEngine* renderingEngine);

	void setParent(Node* parentNode);
	Transform& getTransform();
	virtual void addToRenderingEngine(RenderingEngine* renderingEngine) {}
	//inline const Transform& getTransform() const { return m_parent->getTransform(); }

private:
	Node* m_parent;

};