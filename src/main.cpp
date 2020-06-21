#include "graphics/view.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "terrain/chunk.h"
#include "utils/noise.h"

void cb(Event& event) {
	std::cout << event.getType() << std::endl;
}

int main(void) {
	{
		View view(640, 480, "Simple example");
		view.setCallback(BIND(cb));
		
		Texture* blank = Texture::createBlank(3);
		blank->print();

		Texture texture("src/assets/img/img.png");
		texture.print();
		texture.bind();

		float* vertices1 = new float[5*4] {
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f,  1.0f, 1.0f, 1.0f, 0.0f
		};
		unsigned int* indices1 = new unsigned int[6] {
			0, 1, 2, 2, 3, 0
		};
		float* vertices2 = new float[7*4] {
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		unsigned int* indices2 = new unsigned int[6] {
			0, 1, 2, 2, 3, 0
		};

		Mesh mesh1(vertices1, 4, indices1, 6, {{Float2}, {Float3}});
		view.bind();
		Mesh mesh2(vertices2, 4, indices2, 6, {{Float2}, {Float2}, {Float3}});
		Chunk chunk = Chunk();

		Shader* shaderDebug = Shader::fromFile("src/assets/shaders/debug.vs", "src/assets/shaders/basic.fs");
		Shader* shaderBasic = Shader::fromFile("src/assets/shaders/basic.vs", "src/assets/shaders/basic.fs");
		Shader* shaderTexture = Shader::fromFile("src/assets/shaders/basicTex.vs", "src/assets/shaders/basicTex.fs");

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (view.render()) {
			view.clear();
			shaderBasic->bind();
			mesh1.draw();
			shaderDebug->bind();
			chunk.draw();
			shaderTexture->bind();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mesh2.draw();
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}
	exit(EXIT_SUCCESS);
}
