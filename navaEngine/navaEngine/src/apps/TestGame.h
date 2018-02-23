#pragma once

#include "../engine/core/Game.h"
#include "../engine/geometry/Mesh.h"
#include "../engine/texture/Texture.h"
#include "../engine/shader/Shader.h"

class TestGame : public Game {

public:
	TestGame() {}

	virtual void init();
	virtual void render();

private:
	Shader* shader;
	Texture* texture;
	Mesh* mesh;
};


