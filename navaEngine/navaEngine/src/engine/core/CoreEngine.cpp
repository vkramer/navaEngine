#include "CoreEngine.h"
#include "InputHandler.h"

int CoreEngine::fps;

CoreEngine::CoreEngine(Window* window, double frameRate, RenderingEngine* renderingEngine, Game* game) :
	m_window(window),
	m_game(game),
	m_frameTime(1.0f / frameRate),
	m_isRunning(false),
	m_renderingEngine(renderingEngine)
{
	std::cout << "CoreEngine Constructed" << std::endl;
	init();
}

void CoreEngine::init() {
	std::cout << "CoreEngine Initialized" << std::endl;
	InputHandler::initCallbacks(m_window->getWindow());
	m_renderingEngine->init();
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
			//std::cout << fps << std::endl;
		}

		while (unprocessedTime > m_frameTime)
		{
			render = true;

			// If Close Window is requested - stop game loop and continue to dispose window and exit.
			if (m_window->isCloseRequested())
				this->stop();

			this->input((float)m_frameTime);
			this->update((float)m_frameTime);

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			this->render(m_renderingEngine);
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

void CoreEngine::input(float delta) {
	// GLFW Poll Events
	m_game->input(delta);
}

void CoreEngine::update(float delta) {
	// Update Game Content
	InputHandler::update();
	m_game->update(delta);
}

void CoreEngine::render(RenderingEngine* renderingEngine) {
	
	// Render Game Content
	m_game->render(m_renderingEngine);

	// Swap Buffers
	m_window->render();
}

void CoreEngine::cleanUp() {
	m_window->dispose();
}