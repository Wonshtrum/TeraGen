#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "event/event.h"
#include "event/eventPolling.h"

void error_callback(int code, const char* description) {
	CORE_ERROR("code: ", code, "\n", description);
}

void setWindowEventsCallback(GLFWwindow* window);

using EventCallback = std::function<void(Event&)>;
struct GLFWHook {
	EventCallback callback = [](Event& e) {};
};

class View {
	private:
		static bool s_GLFWInitialized = false;
		int m_width;
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
		View(int width, int height, const char* title): m_width(width), m_height(height) {
			s_GLFWInit();

			m_window = glfwCreateWindow(width, m_height, title, NULL, NULL);
			if (!m_window) {
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			Inputs::setWindow(m_window);

			bind();
			glfwSwapInterval(1);

			if (glewInit()!=GLEW_OK)
				exit(EXIT_FAILURE);

			CORE_TRACE(glGetString(GL_VERSION));
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glClearColor(0.0, 1.0, 0.0, 1.0);
			glViewport(0, 0, m_width, m_height);

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
