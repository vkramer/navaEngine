#pragma once

#include "Window.h"
#include "Game.h"
#include <thread>

class CoreEngine {

public:
	CoreEngine(Window* window, double frameRate, Game* game);
	~CoreEngine();

	void init();
	void start();

private:
	bool m_isRunning;
	Window* m_window;
	Game* m_game;
	double m_frameTime;
	static int fps;

	void run();

	void input();
	void update();
	void render();

	void stop();
	void cleanUp();

};