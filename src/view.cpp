#include "view.h"


void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

View::View(int width, int height, const char* title): width(width), height(height) {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);
	glfwSetKeyCallback(this->window, key_callback);
}

View::~View() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool View::render() {
	glfwGetFramebufferSize(window, &this->width, &this->height);
	//ratio = width / (float) height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(this->window);
	glfwPollEvents();
	return !glfwWindowShouldClose(this->window);
}
