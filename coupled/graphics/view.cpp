#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>
#include "events/events.h"

void error_callback(int error, const char* description) {
	std::cerr << description << std::endl;
}

void setWindowEventsCallback(GLFWwindow* window);

using EventCallback = std::function<void(Event&)>;
struct GLFWHook {
	EventCallback callback = [](Event& e) {};
};

class View {
	private:
		static bool s_GLFWInitialized = false;
		int width;
		int m_height;		
		GLFWwindow* m_window;
		GLFWHook m_hook;

		static void s_GLFWInit() {
			if (s_GLFWInitialized) return;
			if (!glfwInit())
				exit(EXIT_FAILURE);
			glfwSetErrorCallback(error_callback);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			s_GLFWInitialized = true;
		}

	public:
		View(int width, int height, const char* title): width(width), m_height(height) {
			s_GLFWInit();

			m_window = glfwCreateWindow(width, m_height, title, NULL, NULL);
			if (!m_window) {
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			bind();
			glfwSwapInterval(1);

			if (glewInit()!=GLEW_OK)
				exit(EXIT_FAILURE);

			std::cout << glGetString(GL_VERSION) << std::endl;
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glClearColor(0.0, 1.0, 0.0, 1.0);
			glViewport(0, 0, width, m_height);

			glfwSetWindowUserPointer(m_window, &m_hook);
			setWindowEventsCallback(m_window);
		}

		~View() {
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}

		void setCallback(EventCallback callback) { m_hook.callback = callback; }

		void bind() {
			glfwMakeContextCurrent(m_window);
		}

		void clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool render() {
			glfwSwapBuffers(m_window);
			glfwPollEvents();
			return !glfwWindowShouldClose(m_window);
		}
};
