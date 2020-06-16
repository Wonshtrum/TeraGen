#include "graphics/view.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/layout.h"
#include "terrain/chunk.h"

int main(void) {
		View view(640, 480, "Simple example");
		float vertices[] = {
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f,  1.0f, 1.0f, 1.0f, 0.0f
		};
		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		LayoutElement elements[] = {{Float2}, {Float3}};
		Layout layout(elements, 2);

		Mesh mesh(vertices, 4, indices, 6, layout);
		Chunk chunk = Chunk();

		Shader* shaderDebug = Shader::fromFile("src/assets/shaders/debug.vs", "src/assets/shaders/basic.fs");
		Shader* shaderBasic = Shader::fromFile("src/assets/shaders/basic.vs", "src/assets/shaders/basic.fs");

		mesh.bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (view.render()) {
			view.clear();
			shaderBasic->bind();
			mesh.draw();
			shaderDebug->bind();
			chunk.draw();
		}
		exit(EXIT_SUCCESS);
}
