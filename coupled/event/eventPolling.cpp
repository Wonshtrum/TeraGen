#include <GLFW/glfw3.h>
#include "event.h"

class Inputs {
	private:
		static GLFWwindow* s_window;

	public:
		static void setWindow(GLFWwindow* window) { s_window = window; }

		static bool isKeyPressed(int keyCode) {
			auto state = glfwGetKey(s_window, keyCode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		static bool isButtonPressed(int button) {
			return glfwGetMouseButton(s_window, button) == GLFW_PRESS;
		}

		static float getMouseX() {
			double x, y;
			glfwGetCursorPos(s_window, &x, &y);
			return (float)x;
		}

		static float getMouseY() {
			double x, y;
			glfwGetCursorPos(s_window, &x, &y);
			return (float)y;
		}
};
