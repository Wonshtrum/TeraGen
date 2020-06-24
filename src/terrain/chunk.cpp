#include "chunk.h"


LightChunk::LightChunk() {
	int stride = 5;
	float* vertices = new float[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*stride];
	unsigned int* indices = new unsigned int[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*6];
	unsigned int i = 0;
	unsigned int j = 0;
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

			vertices[stride*j+0] = x*1.0/CHUNK_SIZE;
			vertices[stride*j+1] = y*1.0/CHUNK_SIZE;
			vertices[stride*j+2] = 0;
			vertices[stride*j+3] = x*1.0/CHUNK_SIZE;
			vertices[stride*j+4] = y*1.0/CHUNK_SIZE;
			i++;
			j++;
		}
	}
	m_mesh = new Mesh(vertices, j, indices, 6*i, {{Float3}, {Float2}});
}

LightChunk::~LightChunk() {
	delete m_mesh;
}

void LightChunk::seedMesh(double dx, double dy) {
	int i = 0;
	double f = 4.0;
	int stride = 5;
	float* mesh = m_mesh->getVertices();
	for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
		for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
			mesh[stride*i+2] = 0.5*PerlinNoise::noise2D((f*x)/CHUNK_SIZE+dx, (f*y)/CHUNK_SIZE+dy);
			i++;
		}
	}
	m_mesh->update();
}

void LightChunk::draw() {
	m_mesh->draw();
}

DenseChunk::DenseChunk() {
	int stride = 5;
	m_grid = new Block[CHUNK_SIZE*CHUNK_SIZE];
	float* vertices = new float[CHUNK_SIZE*CHUNK_SIZE*4*stride];
	unsigned int* indices = new unsigned int[CHUNK_SIZE*CHUNK_SIZE*6];
	unsigned int i = 0;
	double f = 4.0;
	double z;
	for (int x = 0 ; x < CHUNK_SIZE ; x++) {
		for (int y = 0 ; y < CHUNK_SIZE ; y++) {
			z = PerlinNoise::noise2D((f*x)/CHUNK_SIZE, (f*y)/CHUNK_SIZE)*255;
			m_grid[y*CHUNK_SIZE+x] = z > 0 ? z : 0;
			indices[6*i+0] = 4*i+0;
			indices[6*i+1] = 4*i+2;
			indices[6*i+2] = 4*i+1;
			indices[6*i+3] = 4*i+2;
			indices[6*i+4] = 4*i+3;
			indices[6*i+5] = 4*i+1;
			i++;
		}
	}
	m_mesh = new Mesh(vertices, 4*i, indices, 6*i, {{Float3}, {Float2}});
	updateMesh();
}

DenseChunk::~DenseChunk() {
	delete m_mesh;
	delete m_grid;
}

void DenseChunk::updateMesh() {
	int stride = 5;
	unsigned int k = 0;
	float* mesh = m_mesh->getVertices();
	for (int x = 0 ; x < CHUNK_SIZE ; x++) {
		for (int y = 0 ; y < CHUNK_SIZE ; y++) {
			if (m_grid[y*CHUNK_SIZE+x] > 0) {
				for (int i = 0 ; i < 2 ; i++) {
					for (int j = 0 ; j < 2 ; j++) {
						mesh[stride*k+0] = (x+i)*1.0/CHUNK_SIZE;
						mesh[stride*k+1] = (y+j)*1.0/CHUNK_SIZE;
						mesh[stride*k+2] = -0.5*m_grid[(y+j)*CHUNK_SIZE+x+i]/255.0;
						mesh[stride*k+3] = i;
						mesh[stride*k+4] = j;
						k++;
					}
				}
			}
		}
	}
	m_mesh->setNVertices(k);
	m_mesh->update();
}

void DenseChunk::draw() {
	m_mesh->draw();
}
