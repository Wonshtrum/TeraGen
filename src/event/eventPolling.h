#ifndef __EVENTPOLLING_H__
#define __EVENTPOLLING_H__

#include "core.h"
#include <GLFW/glfw3.h>
#include "event.h"

class Inputs {
	private:
		static GLFWwindow* s_window;

	public:
		static void setWindow(GLFWwindow* window);

		static bool isKeyPressed(int keyCode);

		static bool isButtonPressed(int button);

		static float getMouseX();

		static float getMouseY();
};


#endif