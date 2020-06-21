#include "eventsCallback.h"


void setWindowEventsCallback(GLFWwindow* window) {
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		GET_HOOK;
		WindowCloseEvent event;
		hook.callback(event);
	});
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		GET_HOOK;
		WindowResizeEvent event(width, height);
		hook.callback(event);
	});
	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
		GET_HOOK;
		if (focused) {
			WindowFocusEvent event;
			hook.callback(event);
		} else {
			WindowLoseFocusEvent event;
			hook.callback(event);
		}
	});
	glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y) {
		GET_HOOK;
		WindowMoveEvent event(x, y);
		hook.callback(event);
	});
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
		GET_HOOK;
		switch (action) {
			case GLFW_PRESS: {
				KeyPressEvent event(key, 0);
				hook.callback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressEvent event(key, 1);
				hook.callback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleaseEvent event(key);
				hook.callback(event);
				break;
			}
		}
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		GET_HOOK;
		switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressEvent event(button);
				hook.callback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleaseEvent event(button);
				hook.callback(event);
				break;
			}
		}
	});
	glfwSetScrollCallback(window, [](GLFWwindow* window, double dx, double dy) {
		GET_HOOK;
		MouseScrollEvent event((float)dx, (float)dy);
		hook.callback(event);
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		GET_HOOK;
		MouseMoveEvent event((int)x, (int)y);
		hook.callback(event);
	});
}
