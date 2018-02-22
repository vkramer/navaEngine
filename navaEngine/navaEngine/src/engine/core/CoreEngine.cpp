#include "CoreEngine.h"

int CoreEngine::fps;

CoreEngine::CoreEngine(Window* window, double frameRate, Game* game) :
	m_window(window),
	m_game(game),
	m_frameTime(1.0 / frameRate),
	m_isRunning(false)
{
	init();
}

CoreEngine::~CoreEngine() {

}

void CoreEngine::init() {
	std::cout << "CoreEngine Initialized" << std::endl;
}

void CoreEngine::start() {
	if (m_isRunning)
		return;
	run();
}

void CoreEngine::run() {
	m_isRunning = true;

	// Initialize Game Content
	m_game->init();

	double previousTime = glfwGetTime();
	double unprocessedTime = 0;
	double frameCounter = 0;
	int frames = 0;

	// Main Game Loop
	while (m_isRunning) {
		bool render = false;

		double startTime = glfwGetTime();
		double elapsedTime = startTime - previousTime;
		previousTime = startTime;

		unprocessedTime += elapsedTime;
		frameCounter += elapsedTime;

		if (frameCounter >= 1.0)
		{
			// Set FPS to frame count
			fps = frames;
			// Clear frame count
			frames = 0;
			// Clear frameCounter
			frameCounter = 0;

			// Print FPS to Terminal
			std::cout << fps << std::endl;
		}

		while (unprocessedTime > m_frameTime)
		{
			render = true;

			// If Close Window is requested - stop game loop and continue to dispose window and exit.
			if (m_window->isCloseRequested())
				this->stop();

			this->input();
			this->update();

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			this->render();
			frames++;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	// Dispose of Window
	cleanUp();
}

void CoreEngine::stop() {
	if (!m_isRunning)
		return;

	m_isRunning = false;
}

void CoreEngine::input() {
	// GLFW Poll Events
	m_window->update();
}

void CoreEngine::update() {
	// Update Game Content
	m_game->update();
}

void CoreEngine::render() {
	// Clear Screen
	m_window->clear();
	// Render Game Content
	m_game->render();
	// Swap Buffers
	m_window->render();
}

void CoreEngine::cleanUp() {
	m_window->dispose();
}