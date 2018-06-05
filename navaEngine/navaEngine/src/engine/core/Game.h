#pragma once

#include "RenderingEngine.h"
#include "../scenegraph/Node.h"

class Game {

public:
	Game() {}
	virtual ~Game() {}

	virtual void init() {}

	virtual void input(float delta);
	virtual void update(float delta);
	virtual void render(RenderingEngine* renderingEngine);

	Node& getRootNode();

protected:
	void addToScene(Node* child);

private:
	Node m_rootNode;

};