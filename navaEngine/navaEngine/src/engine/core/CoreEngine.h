#pragma once

#include "Window.h"
#include <thread>

class CoreEngine {

public:
	CoreEngine(Window* window, double frameRate);
	~CoreEngine();

	void init();
	void start();

private:
	bool m_isRunning;
	Window* m_window;
	double m_frameTime;
	static int fps;

	void run();

	void input();
	void update();
	void render();

	void stop();
	void cleanUp();

};