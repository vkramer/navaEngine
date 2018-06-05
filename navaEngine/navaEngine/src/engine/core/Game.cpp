#include "Game.h"

void Game::input(float delta)
{
	m_rootNode.input(delta);
}

void Game::update(float delta)
{
	m_rootNode.update(delta);
}

void Game::render(RenderingEngine* renderingEngine)
{
	renderingEngine->render(&m_rootNode);
}

Node& Game::getRootNode() {
	return m_rootNode;
}

void Game::addToScene(Node* child)
{
	m_rootNode.addChild(child);
}