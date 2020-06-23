#include "chunk.h"


Chunk::Chunk() {
	m_grid = new Block[CHUNK_SIZE*CHUNK_SIZE];
	int stride = 5;
	float* vertices = new float[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*stride];
	unsigned int* indices = new unsigned int[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*6];
	unsigned int i = 0;
	unsigned int j = 0;
	double z;
	double f = 8.0;
	for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
		for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
			if (x < CHUNK_SIZE && y < CHUNK_SIZE) {
				indices[6*i+0] = i+0;
				indices[6*i+1] = i+CHUNK_SIZE+1;
				indices[6*i+2] = i+CHUNK_SIZE+2;
				indices[6*i+3] = i+0;
				indices[6*i+4] = i+CHUNK_SIZE+2;
				indices[6*i+5] = i+1;
			}
			z = PerlinNoise::noise2D((f*x)/CHUNK_SIZE, (f*y)/CHUNK_SIZE);

			vertices[stride*j+0] = x*1.0/CHUNK_SIZE;
			vertices[stride*j+1] = y*1.0/CHUNK_SIZE;
			vertices[stride*j+2] = z*0.2;
			vertices[stride*j+3] = x*1.0/CHUNK_SIZE;
			vertices[stride*j+4] = y*1.0/CHUNK_SIZE;
			i++;
			j++;
		}
	}
	m_mesh = new Mesh(vertices, j, indices, 6*i, {{Float3}, {Float2}});
}

Chunk::~Chunk() {
	delete[] m_grid;
	delete m_mesh;
}

Mesh* Chunk::getMesh() { return m_mesh; }

void Chunk::draw() {
	m_mesh->draw();
}
