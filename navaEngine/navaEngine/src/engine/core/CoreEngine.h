#pragma once

#include "Window.h"
#include "Game.h"
#include "RenderingEngine.h"
#include <thread>

class CoreEngine {

public:
	CoreEngine(Window* window, double frameRate, RenderingEngine* renderingEngine, Game* game);
	virtual ~CoreEngine() {};

	static int fps;

	void init();
	void start();

private:
	Window* m_window;
	Game* m_game;
	RenderingEngine* m_renderingEngine;

	bool m_isRunning;
	double m_frameTime;

	void run();

	void input(float delta);
	void update(float delta);
	void render(RenderingEngine* renderingEngine);

	void stop();
	void cleanUp();

	

};