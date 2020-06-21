#include "view.h"


void error_callback(int error, const char* description) {
	std::cerr << description << std::endl;
}

void setWindowEventsCallback(GLFWwindow* window);

bool View::s_GLFWInitialized = false;

void View::s_GLFWInit() {
	if (s_GLFWInitialized) return;
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	s_GLFWInitialized = true;
}

View::View(int width, int height, const char* title): width(width), m_height(height) {
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
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glViewport(0, 0, width, m_height);

	glfwSetWindowUserPointer(m_window, &m_hook);
	setWindowEventsCallback(m_window);
}

View::~View() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void View::setCallback(EventCallback callback) { m_hook.callback = callback; }

void View::bind() {
	glfwMakeContextCurrent(m_window);
}

void View::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

bool View::render() {
	glfwSwapBuffers(m_window);
	glfwPollEvents();
	return !glfwWindowShouldClose(m_window);
}
