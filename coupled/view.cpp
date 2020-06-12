#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

class View {
	private:
		int m_width, m_height;
		GLFWwindow* m_window;

	public:
		View(int width, int height, const char* title): m_width(width), m_height(height) {
			glfwSetErrorCallback(error_callback);
			if (!glfwInit())
				exit(EXIT_FAILURE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);
			if (!m_window) {
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			glfwMakeContextCurrent(m_window);
			glfwSetKeyCallback(m_window, key_callback);

			if (glewInit()!=GLEW_OK)
				exit(EXIT_FAILURE);

			glfwSwapInterval(1);
			std::cout << glGetString(GL_VERSION) << std::endl;
			glDisable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glClearColor(0.0, 1.0, 0.0, 1.0);
		}

		~View() {
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}

		void clear() {
			glfwGetFramebufferSize(m_window, &m_width, &m_height);
			glViewport(0, 0, m_width, m_height);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		bool render() {
			glfwSwapBuffers(m_window);
			glfwPollEvents();
			return !glfwWindowShouldClose(m_window);
		}
};
