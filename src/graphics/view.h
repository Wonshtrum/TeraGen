#ifndef __VIEW_H__
#define __VIEW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void error_callback(int error, const char* description);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class View {
	private:
		int m_width;
		int m_height;
		GLFWwindow* m_window;

	public:
		View(int width, int height, const char* title);

		~View();

		void clear();

		bool render();
};


#endif