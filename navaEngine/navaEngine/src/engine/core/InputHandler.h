#pragma once

#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class InputHandler
{
public:
	static void update();
	static void initCallbacks(GLFWwindow* window);

	// GET AND SET CURSOR POSITION
	static glm::vec2 getCursorPosition();
	static void setCursorPosition(GLFWwindow* window, glm::vec2 newPosition);

	// GET AND SET SCROLL OFFSET
	static float getScrollOffset();
	static void setScrollOffset(float offset);

	// GET ISCURSORLOCKED
	static bool getLockStatus();
	static void setLockedCursorPosition(glm::vec2 lockedPosition);
	static glm::vec2 getLockedCursorPosition();

	static std::vector<int> getKeysPressed();

private:
	static std::vector<int> keysPressed;
	static std::vector<int> keysReleased;
	static std::vector<int> keysHolding;
	static std::vector<int> buttonsPressed;
	static std::vector<int> buttonsReleased;
	static std::vector<int> buttonsHolding;

	static glm::vec2 cursorPosition;
	static glm::vec2 lockedCursorPosition;
	static float scrollOffset;
	static bool isCursorLocked;;

	void clear();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_pos_callback(GLFWwindow* window, double x, double y);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};