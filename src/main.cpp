#include "graphics/view.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "terrain/chunk.h"

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
		Chunk chunk = Chunk();

		Shader* shader = Shader::fromFile("src/assets/shaders/debug.vs", "src/assets/shaders/debug.fs");
		shader->bind();

		mesh.bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (view.render()) {
			view.clear();
			chunk.draw();
			mesh.draw();
		}
		exit(EXIT_SUCCESS);
}
