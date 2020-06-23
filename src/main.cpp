#include "graphics/view.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "terrain/chunk.h"
#include "utils/noise.h"

void cb(Event& event) {
	std::cout << event.getType() << std::endl;
}

int main(void) {
	{
		Camera camera(0.9, 640, 480, 0.1, 1000);
		Transform& t = camera.getTransform();
		t.setTranslation(-0.1,-0.5,1);
		t.setRotation(0.5,0.5,0.5);
		t.setScale(1,1,1);
		t.calculate();
		std::cout << t << std::endl;
		camera.calculate();

		View view(640, 480, "Simple example");
		//view.setCallback(BIND(cb));
		
		Texture* blank = Texture::createBlank(3);
		blank->print();

		Texture texture("src/assets/img/img.png");
		texture.print();
		texture.bind();

		float* vertices = new float[8*4] {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f
		};
		unsigned int* indices = new unsigned int[6] {
			0, 1, 2, 2, 3, 0
		};

		Mesh mesh(vertices, 4, indices, 6, {{Float3}, {Float2}, {Float3}});
		Chunk chunk = Chunk();
		float* chunkMesh = chunk.getMesh()->getVertices();

		Shader* shaderTexture = Shader::fromFile("src/assets/shaders/basicTex.vs", "src/assets/shaders/coloredTex.fs");
		Shader* shaderColoredTexture = Shader::fromFile("src/assets/shaders/coloredTex.vs", "src/assets/shaders/coloredTex.fs");

		double z;
		double f = 4.0;
		double Dx = 0;
		double Dy = 0;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (view.render()) {
			view.clear();
			shaderTexture->bind();
			shaderTexture->uploadUniform("u_transform", camera.getMatrix());
			chunk.draw();
			shaderColoredTexture->bind();
			mesh.draw();

			int i = 0;
			for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
				for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
					z = PerlinNoise::noise2D((f*x)/CHUNK_SIZE+Dx, (f*y)/CHUNK_SIZE+Dy);
					chunkMesh[5*i+2] = z*0.5;
					i++;
				}
			}
			Dx += 0.001;
			Dy += 0.001;
			chunk.getMesh()->update();
		}
	}
	exit(EXIT_SUCCESS);
}
