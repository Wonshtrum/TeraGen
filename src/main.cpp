#include "core.h"
#include "graphics/view.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "terrain/chunk.h"
#include "terrain/region.h"
#include "utils/noise.h"

int main(void) {
	LOG::init();
	CORE_LOGGER->setPrompt("%L[%f(%l)]%N: ");
	{
		Camera camera(0.9, 640, 480, 0.01, 1000);
		Transform& t = camera.getTransform();
		t.setTranslation(-0.5,-0.5,1);
		t.calculate();
		camera.calculate();

		View view(640, 480, "Simple example");
		view.setCallback(BIND(Camera::onEvent, camera));
		
		Texture* blank = Texture::createBlank(3);
		blank->print();

		Texture texture("src/assets/img/img.png");
		texture.print();
		texture.bind();
		
		//LightChunk chunk(0,0);
		//DenseChunk chunk(0,0);
		MarchingSquarre chunk(0,0);
		//Region<MarchingSquarre> region("test");

		Shader* shaderTexture = Shader::fromFile("src/assets/shaders/basicTex.vs", "src/assets/shaders/coloredTex.fs");

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Block limit = 0;
		while (view.render()) {
			view.clear();
			shaderTexture->bind();
			shaderTexture->uploadUniform("u_transform", camera.getMatrix());
			chunk.draw();
			chunk.setLimit(limit++);
		}
	}
	LOG::terminate();
	exit(EXIT_SUCCESS);
}
