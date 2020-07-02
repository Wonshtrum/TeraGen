#include "eventPolling.h"

GLFWwindow* Inputs::s_window;

void Inputs::setWindow(GLFWwindow* window) { s_window = window; }

bool Inputs::isKeyPressed(int keyCode) {
	auto state = glfwGetKey(s_window, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Inputs::isButtonPressed(int button) {
	return glfwGetMouseButton(s_window, button) == GLFW_PRESS;
}

float Inputs::getMouseX() {
	double x, y;
	glfwGetCursorPos(s_window, &x, &y);
	return (float)x;
}

float Inputs::getMouseY() {
	double x, y;
	glfwGetCursorPos(s_window, &x, &y);
	return (float)y;
}
