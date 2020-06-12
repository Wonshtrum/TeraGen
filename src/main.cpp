#include "view.h"
#include "shader.h"

int main(void) {
		View view(640, 480, "Simple example");
		float vertices[] = {
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
		};
		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		unsigned int vao = 0;
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		unsigned int positions;
		glGenBuffers(1, &positions);
		glBindBuffer(GL_ARRAY_BUFFER, positions);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (const void*)0);

		unsigned int ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		const char* vertexShader = R"(
		#version 330 core
		layout(location = 0) in vec2 a_position;
		out vec4 v_position;
		void main() {
			v_position = vec4(a_position/2, 0, 1);
			gl_Position = v_position;
		})";
		const char* fragmentShader = R"(
		#version 330 core
		in vec4 v_position;
		layout(location = 0) out vec4 color;
		void main() {
			color = 0.5*(v_position+1);
		})";

		Shader shader(vertexShader, fragmentShader);
		shader.bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (view.render()) {
			view.clear();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		exit(EXIT_SUCCESS);
}
