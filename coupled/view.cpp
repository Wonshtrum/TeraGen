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
		int width, height;
		GLFWwindow* window;

	public:
		View(int width, int height, const char* title): width(width), height(height) {
			glfwSetErrorCallback(error_callback);
			if (!glfwInit())
				exit(EXIT_FAILURE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwSwapInterval(1);

			this->window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (!window) {
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			glfwMakeContextCurrent(this->window);
			glfwSetKeyCallback(this->window, key_callback);

			if (glewInit()!=GLEW_OK)
				exit(EXIT_FAILURE);
			std::cout << glGetString(GL_VERSION) << std::endl;
		}

		~View() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		bool render() {
			glfwGetFramebufferSize(window, &this->width, &this->height);
			//ratio = width / (float) height;
			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(this->window);
			glfwPollEvents();
			return !glfwWindowShouldClose(this->window);
		}
};
