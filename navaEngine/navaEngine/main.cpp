#include <iostream>
#include "src\engine\core\Window.h"
#include "src\engine\core\CoreEngine.h"
#include "src\engine\core\RenderingEngine.h"
#include "src\apps\TestGame.h"

const unsigned int NE_WIN_WIDTH = 1600;
const unsigned int NE_WIN_HEIGHT = 900;

const unsigned int NE_FRAMERATE = 60;

int main() {

	// Declare TestGame (located in src/apps)
	TestGame game;

	// Declare and create GLFW Window
	Window window;
	window.create(NE_WIN_WIDTH, NE_WIN_HEIGHT, "NavaEngine");

	// Declare Rendering Engine
	RenderingEngine renderingEngine;

	// Declare and start CoreEngine
	CoreEngine engine(&window, NE_FRAMERATE, &renderingEngine, &game);
	engine.start();

	return 0;
}