#include "graphics/view.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "terrain/chunk.h"
#include "utils/noise.h"
#include "math/transform.h"

void cb(Event& event) {
	std::cout << event.getType() << std::endl;
}

int main(void) {
	{
		Transform t;
		t.setTranslation(1,2,3);
		t.setRotation(1,2,3);
		t.setScale(0,1,1);
		t.calculateTransformMatrix();
		std::cout << t << std::endl;
		View view(640, 480, "Simple example");
		//view.setCallback(BIND(cb));
		
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
			 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};
		unsigned int* indices2 = new unsigned int[6] {
			0, 1, 2, 2, 3, 0
		};

		Mesh mesh1(vertices1, 4, indices1, 6, {{Float2}, {Float3}});
		view.bind();
		Mesh mesh2(vertices2, 4, indices2, 6, {{Float2}, {Float2}, {Float3}});
		Chunk chunk = Chunk();
		float* chunkMesh = chunk.getMesh()->getVertices();

		Shader* shaderBasic = Shader::fromFile("src/assets/shaders/basic.vs", "src/assets/shaders/basic.fs");
		Shader* shaderTexture = Shader::fromFile("src/assets/shaders/basicTex.vs", "src/assets/shaders/coloredTex.fs");

		double dx, dy;
		double f = 8.0;
		double Dx = 0;
		double Dy = 0;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (view.render()) {
			view.clear();
			shaderBasic->bind();
			mesh1.draw();
			shaderTexture->bind();
			chunk.draw();
			shaderTexture->bind();
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mesh2.draw();
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			int i = 0;
			for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
				for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
					dx = PerlinNoise::noise2D((f*x)/CHUNK_SIZE+Dx, (f*y)/CHUNK_SIZE+Dy);
					dy = PerlinNoise::noise2D((f*x)/CHUNK_SIZE+128+Dx, (f*y)/CHUNK_SIZE+Dy);
					chunkMesh[4*i+0] = 8*(x+dx*16.0/f)/CHUNK_SIZE;
					chunkMesh[4*i+1] = 8*(y+dy*16.0/f)/CHUNK_SIZE;
					chunkMesh[4*i+2] = x*1.0/CHUNK_SIZE;
					chunkMesh[4*i+3] = y*1.0/CHUNK_SIZE;
					i++;
				}
			}
			Dx += 0.02;
			Dy += 0.02;
			chunk.getMesh()->update();
		}
	}
	exit(EXIT_SUCCESS);
}
