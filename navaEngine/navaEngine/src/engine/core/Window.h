#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {

public:

	Window() {}
	~Window() {}

	void create(int width, int height, const char* title);
	bool isCloseRequested();
	void clear();
	void update();
	void render();
	void dispose();

	GLFWwindow* getWindow();
	int getWidth();
	int getHeight();


private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
	const char* m_title;
};