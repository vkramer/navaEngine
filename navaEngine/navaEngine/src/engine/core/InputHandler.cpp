#include "InputHandler.h"
#include <iostream>

//Initialize Vector Arrays
std::vector<int> InputHandler::keysPressed;
std::vector<int> InputHandler::keysReleased;
std::vector<int> InputHandler::keysHolding;

std::vector<int> InputHandler::buttonsPressed;
std::vector<int> InputHandler::buttonsReleased;
std::vector<int> InputHandler::buttonsHolding;

glm::vec2 InputHandler::cursorPosition = glm::vec2(0.0f, 0.0f);
glm::vec2 InputHandler::lockedCursorPosition;

bool InputHandler::isCursorLocked = false;

float InputHandler::scrollOffset = 0;

void InputHandler::initCallbacks(GLFWwindow* window)
{
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetScrollCallback(window, scroll_callback);
	std::cout << "Input Callbacks Initialized" << std::endl;
}

void InputHandler::update()
{
	glfwPollEvents();
}

void InputHandler::clear() {
	//setScrollOffset(0);
	keysPressed.clear();
	keysReleased.clear();
	buttonsPressed.clear();
	buttonsReleased.clear();
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS) {
		//std::cout << key << std::endl;
		if (std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end()) {
			//std::cout << "This key is already in the array: " << key << std::endl;
		}
		else {
			keysPressed.push_back(key);
			keysHolding.push_back(key);
		}

	}

	if (action == GLFW_RELEASE) {
		for (std::vector<int>::iterator iter = keysHolding.begin(); iter != keysHolding.end(); ++iter) {
			if (*iter == key) {
				keysHolding.erase(iter);
				break;
			}
		}
		keysReleased.push_back(key);
	}
}

void InputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == 1 && action == GLFW_PRESS) {
		//lockedCursorPosition = getCursorPosition();
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		isCursorLocked = true;
		setLockedCursorPosition(getCursorPosition());
		//std::cout << "Locked Cursor Position: " << lockedCursorPosition.x << std::endl;
	}

	if (button == 1 && action == GLFW_RELEASE) {
		// TODO:: Set Cursor Position to last lockedMousePosition;
		isCursorLocked = false;
		setCursorPosition(window, getLockedCursorPosition());
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (action == GLFW_PRESS) {
		if (std::find(buttonsPressed.begin(), buttonsPressed.end(), button) != buttonsPressed.end()) {
			//std::cout << "This key is already in the array: " << key << std::endl;
		}
		else {
			buttonsPressed.push_back(button);
			buttonsHolding.push_back(button);
		}
	}

	if (action == GLFW_RELEASE) {
		for (std::vector<int>::iterator iter = buttonsHolding.begin(); iter != buttonsHolding.end(); ++iter) {
			if (*iter == button) {
				buttonsHolding.erase(iter);
				break;
			}
		}
		buttonsReleased.push_back(button);
	}
}

void InputHandler::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	glm::vec2 position = glm::vec2((float)xpos, (float)ypos);
	cursorPosition = position;
	glfwSetCursorPos(window, xpos, ypos);
}
float varOffset = 0;
void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	scrollOffset += yoffset;
	//std::cout << "Scroll Offset: " << scrollOffset << std::endl;
}

glm::vec2 InputHandler::getCursorPosition() {
	return cursorPosition;
}

void InputHandler::setCursorPosition(GLFWwindow* window, glm::vec2 newPosition) {
	cursorPosition = newPosition;
	glfwSetCursorPos(window, newPosition.x, newPosition.y);
}

float InputHandler::getScrollOffset() {
	return scrollOffset;
}

void InputHandler::setScrollOffset(float offset) {
	scrollOffset = offset;
}

bool InputHandler::getLockStatus() {
	return isCursorLocked;
}

void InputHandler::setLockedCursorPosition(glm::vec2 lockedPosition) {
	lockedCursorPosition = lockedPosition;
}

glm::vec2 InputHandler::getLockedCursorPosition() {
	return lockedCursorPosition;
}

std::vector<int> InputHandler::getKeysPressed()
{
	return keysPressed;
}