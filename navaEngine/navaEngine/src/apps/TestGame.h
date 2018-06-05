#pragma once

#include "../engine/core/Game.h"
#include "../engine/components/model/Mesh.h"
#include "../engine/components/model/Model.h"
#include "../engine/components/model/Material.h"
#include "../engine/scenegraph/Node.h"
#include "../engine/texture/Texture.h"
#include "../engine/shader/Shader.h"

class TestGame : public Game {

public:
	TestGame() {}

	void init();
	void update(float delta);
	void render();

private:
	Node* cubeNodeTest;
	Node* cubeNodeTest2;
	Node* cubeNodeTest3;
};


