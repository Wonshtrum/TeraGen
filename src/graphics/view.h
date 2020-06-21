#ifndef __VIEW_H__
#define __VIEW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include "events/events.h"

#define BIND(x) std::bind(&x, std::placeholders::_1)

void error_callback(int error, const char* description);

using EventCallback = std::function<void(Event&)>;
struct GLFWHook {
	EventCallback callback = [](Event& e) {};
};

class View {
	private:
		static bool s_GLFWInitialized;
		int width;
		int m_height;		
		GLFWwindow* m_window;
		GLFWHook m_hook;

		static void s_GLFWInit();

	public:
		View(int width, int height, const char* title);

		~View();

		void setCallback(EventCallback callback);

		void bind();

		void clear();

		bool render();
};


#endif