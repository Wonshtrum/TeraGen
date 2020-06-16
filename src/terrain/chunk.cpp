#include "chunk.h"


Chunk::Chunk() {
	float* vertices = new float[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*2];
	unsigned int* indices = new unsigned int[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*6];
	LayoutElement elements[] = {{Float2}};
	Layout layout(elements, 1);
	unsigned int i = 0;
	unsigned int j = 0;
	for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
		for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
			if (x < CHUNK_SIZE && y < CHUNK_SIZE) {
				indices[6*i+0] = i+0;
				indices[6*i+1] = i+1;
				indices[6*i+2] = i+CHUNK_SIZE+1;
				indices[6*i+3] = i+1;
				indices[6*i+4] = i+CHUNK_SIZE+2;
				indices[6*i+5] = i+CHUNK_SIZE+1;
			}
			vertices[2*j+0] = x;
			vertices[2*j+1] = y;
			i++;
			j++;
		}
	}
	m_mesh = Mesh(vertices, j, indices, 6*i, layout);
}

void Chunk::draw() {
	m_mesh.draw();
}
