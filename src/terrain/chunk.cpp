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
	int stride = 5;
	float* mesh = m_mesh->getVertices();
	LayeredNoise<PerlinNoise> noise(2, 0.5, 4.0/CHUNK_SIZE, 2, dx, dy);
	for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
		for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
			mesh[stride*i+2] = 0.5*noise.sample(x, y);
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
	double z;
	LayeredNoise<PerlinNoise> noise(3, 0.5, 4.0/CHUNK_SIZE);
	for (int x = 0 ; x < CHUNK_SIZE ; x++) {
		for (int y = 0 ; y < CHUNK_SIZE ; y++) {
			z = 255*noise.sample(x, y);
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
	m_mesh = new Mesh(vertices, 0, indices, 6*i, {{Float3}, {Float2}});
	updateMesh();
}

DenseChunk::~DenseChunk() {
	delete m_mesh;
	delete[] m_grid;
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

Squarre::Squarre(std::initializer_list<unsigned int> vertices_): nVertices(vertices_.size()) {
	vertices = new unsigned int[nVertices];
	for (unsigned int i = 0 ; i < nVertices ; i++) {
		vertices[i] = vertices_.begin()[i];
	}
}

Squarre MarchingSquarre::s_squarres[6] = {{}, {0,7,1}, {0,7,2,2,7,3}, {0,6,4,4,2,0}, {0,6,5,5,3,0,0,3,2}, {0,7,1,/*1,7,3,3,7,5,*/5,4,3}};
unsigned int MarchingSquarre::s_squarreId[16] =  {0, 1, 1, 2, 1, 2, 5, 4, 1, 5, 2, 4, 2, 4, 4, 3};
unsigned int MarchingSquarre::s_squarreRot[16] = {0, 0, 1, 0, 3, 3, 1, 0, 2, 0, 1, 1, 2, 3, 2, 0};
MarchingSquarre::MarchingSquarre() {
	int stride = 5;
	unsigned int maxTriangles = 3;
	m_grid = new Block[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)];
	float* vertices = new float[CHUNK_SIZE*CHUNK_SIZE*maxTriangles*3*stride];
	unsigned int* indices = new unsigned int[CHUNK_SIZE*CHUNK_SIZE*maxTriangles*3];
	unsigned int i = 0;
	LayeredNoise<PerlinNoise> noise(5, 0.5, 4.0/CHUNK_SIZE);
	for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
		for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
			m_grid[y*(CHUNK_SIZE+1)+x] = 127+127*noise.sample(x, y);
			if (x < CHUNK_SIZE && y < CHUNK_SIZE) {
				for (unsigned int j = 0 ; j < maxTriangles*3 ; j++) {
					indices[maxTriangles*3*i+j] = maxTriangles*3*i+j;
				}
				i++;
			}
		}
	}
	m_mesh = new Mesh(vertices, 0, indices, maxTriangles*3*i, {{Float3}, {Float2}});
	updateMesh(0);
}

MarchingSquarre::~MarchingSquarre() {
	delete m_mesh;
	delete[] m_grid;
}

int MarchingSquarre::configuration(unsigned int x, unsigned int y, Block limit) {
	int a = m_grid[(y+1)*(CHUNK_SIZE+1)+x] > limit ? 1 : 0;
	int b = m_grid[(y+1)*(CHUNK_SIZE+1)+x+1] > limit ? 2 : 0;
	int c = m_grid[y*(CHUNK_SIZE+1)+x] > limit ? 4 : 0;
	int d = m_grid[y*(CHUNK_SIZE+1)+x+1] > limit ? 8 : 0;
	return a+b+c+d;
}

float MarchingSquarre::smooth(Block a, Block b, Block limit) {
	return ((float)a-limit)/(a-b);
}

void MarchingSquarre::coordinates(unsigned int x, unsigned int y, float* u, float* v, unsigned int index, unsigned int rotation, Block limit) {
	int a = m_grid[(y+1)*(CHUNK_SIZE+1)+x];
	int b = m_grid[(y+1)*(CHUNK_SIZE+1)+x+1];
	int c = m_grid[y*(CHUNK_SIZE+1)+x];
	int d = m_grid[y*(CHUNK_SIZE+1)+x+1];

	index = (index+2*rotation)%8;
	switch (index) {
		case 0: *u = 0.0; *v = 1.0; return;
		case 1: *u = smooth(a, b, limit); *v = 1.0; return;
		case 2: *u = 1.0; *v = 1.0; return;
		case 3: *u = 1.0; *v = smooth(d, b, limit); return;
		case 4: *u = 1.0; *v = 0.0; return;
		case 5: *u = smooth(c, d, limit); *v = 0.0; return;
		case 6: *u = 0.0; *v = 0.0; return;
		case 7: *u = 0.0; *v = smooth(c, a, limit); return;
	}
}

void MarchingSquarre::updateMesh(Block limit) {
	int stride = 5;
	float* mesh = m_mesh->getVertices();
	int config;
	unsigned int* vertices;
	unsigned int nVertices;
	unsigned int i = 0;
	float u;
	float v;
	for (int x = 0 ; x < CHUNK_SIZE ; x++) {
		for (int y = 0 ; y < CHUNK_SIZE ; y++) {
			config = configuration(x, y, limit);
			vertices = s_squarres[s_squarreId[config]].vertices;
			nVertices = s_squarres[s_squarreId[config]].nVertices;
			for (unsigned int j = 0 ; j < nVertices ; j++) {
				coordinates(x, y, &u, &v, vertices[j], s_squarreRot[config], limit);
				mesh[i*stride+0] = (u+x)/CHUNK_SIZE;
				mesh[i*stride+1] = (v+y)/CHUNK_SIZE;
				mesh[i*stride+2] = 0;
				if ((x^y)&1) {
					mesh[i*stride+3] = (u+x)/CHUNK_SIZE;
					mesh[i*stride+4] = (v+y)/CHUNK_SIZE;
				} else {
					mesh[i*stride+3] = u;
					mesh[i*stride+4] = v;
				}
				i++;
			}
		}
	}
	m_mesh->setNVertices(i);
	m_mesh->update();
}

void MarchingSquarre::draw() {
	m_mesh->draw();
}
