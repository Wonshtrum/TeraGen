#ifndef __VIEW_H__
#define __VIEW_H__

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description) ;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) ;

class View {
	private:
		int width, height;
		GLFWwindow* window;

	public:
		View(int width, int height, const char* title);

		~View() ;

		bool render() ;
};


#endif