#include "view.h"
#include "shader.h"
#include "mesh.h"

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

		Mesh mesh(vertices, 8, indices, 6);

		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		mesh.bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (const void*)0);

		Shader* shader = Shader::fromFile("src/assets/shaders/debug.vs", "src/assets/shaders/debug.fs");
		shader->bind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (view.render()) {
			view.clear();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		exit(EXIT_SUCCESS);
}
