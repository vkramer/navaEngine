#include "Window.h"

// HANDLE WINDOW RESIZE
void window_resize(GLFWwindow *window, int width, int height);

// CREATE WINDOW
void Window::create(int width, int height, const char *title) {
	m_title = title;
	m_width = width;
	m_height = height;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
	}
	else {
		std::cout << "GLFW Initialized" << std::endl;
	}

	// Set Window Hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Get Monitor Properties
	GLFWmonitor* glfwMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* glfwVidMode = glfwGetVideoMode(glfwMonitor);

	// Create GLFW Window
	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, NULL);

	// Set Window Position
	glfwSetWindowPos(m_window, (glfwVidMode->width - m_width) / 2, (glfwVidMode->height - m_height) / 2);

	// Check to makes sure GLFW Window was created and fail if not
	if (!m_window) {
		std::cout << "Failed to create GLFW Window!" << std::endl;
	}
	else {
		std::cout << "GLFW Window has been created!" << std::endl;
	}

	// Set OpenGL Current Context to Window
	glfwMakeContextCurrent(m_window);

	// Set Callbacks
	glfwSetWindowSizeCallback(m_window, window_resize);
	glfwSetWindowUserPointer(m_window, this);

	// Load GLAD OpenGL Pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
	}
	else {
		std::cout << "GLAD OpenGL Initialized | OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	}
}

// CHECK TO SEE IF WINDOW CLOSE IS REAQUESTED
bool Window::isCloseRequested() {
	return glfwWindowShouldClose(m_window);
}

// UPDATE WINDOW
void Window::update() {
	glfwPollEvents();
}

// SWAP BUFFERS
void Window::render() {
	glfwSwapBuffers(m_window);
}

// CLEAR SCREEN
void Window::clear() {
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// DESTROY WINDOW & TERMINATE GLFW
void Window::dispose() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

// RETURN WINDOW WIDTH
int Window::getWidth() {
	return m_width;
}

// RETURN WINDOW HEIGHT
int Window::getHeight() {
	return m_height;
}

// RETURN GLFW WINDOW
GLFWwindow* Window::getWindow() {
	return m_window;
}

// HANDLE WINDOW RESIZE
void window_resize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}