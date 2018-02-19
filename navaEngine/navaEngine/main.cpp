#include <iostream>
#include "src\engine\core\Window.h"

const unsigned int WIN_WIDTH = 1600;
const unsigned int WIN_HEIGHT = 900;

int main() {

	// Initialize and create GLFW Window
	Window window;
	window.create(WIN_WIDTH, WIN_HEIGHT, "NavaEngine");

	// While close window call is not being requested - render window
	while (!glfwWindowShouldClose(window.getWindow())) {
		// Clear Screen
		window.clear();
		// Swap Buffers
		window.render();
		// GLFW Event Polling
		glfwPollEvents();
	}

	window.dispose();

	return 0;
}