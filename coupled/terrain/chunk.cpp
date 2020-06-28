#include <initializer_list>
#include "graphics/mesh.h"
#include "graphics/layout.h"
#include "utils/noise.h"
#include "utils/file.h"
#include "macros.h"

class Chunk {
	protected:
		Mesh* m_mesh;
		Block* m_grid;
		unsigned int m_x;
		unsigned int m_y;
		LayeredNoise<PerlinNoise> m_noise;

	public:
		Chunk(unsigned int x, unsigned int y): m_x(x), m_y(y) {
			m_noise = LayeredNoise<PerlinNoise>(1, 0.5, 4.0/CHUNK_SIZE, 2, x, y);
		}

		virtual ~Chunk() {
			delete m_mesh;
			delete[] m_grid;
		}

		virtual void updateMesh() = 0;

		virtual void draw() {
			m_mesh->draw();
		}
};

class LightChunk: public Chunk {
	public:
		LightChunk(unsigned int x, unsigned int y): Chunk(x, y) {
			int stride = 5;
			m_grid = new Block[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)];
			float* vertices = new float[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*stride];
			unsigned int* indices = new unsigned int[CHUNK_SIZE*CHUNK_SIZE*6];
			unsigned int i = 0;
			unsigned int j = 0;
			for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
				for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
					if (x < CHUNK_SIZE && y < CHUNK_SIZE) {
						indices[6*i+0] = j+0;
						indices[6*i+1] = j+CHUNK_SIZE+1;
						indices[6*i+2] = j+CHUNK_SIZE+2;
						indices[6*i+3] = j+0;
						indices[6*i+4] = j+CHUNK_SIZE+2;
						indices[6*i+5] = j+1;
						i++;
					}

					m_grid[j] = 255*m_noise.sample(x, y);
					vertices[stride*j+0] = x*1.0/CHUNK_SIZE;
					vertices[stride*j+1] = y*1.0/CHUNK_SIZE;
					vertices[stride*j+2] = 0;
					vertices[stride*j+3] = x*1.0/CHUNK_SIZE;
					vertices[stride*j+4] = y*1.0/CHUNK_SIZE;
					j++;
				}
			}
			m_mesh = new Mesh(vertices, j, indices, 6*i, {{Float3}, {Float2}});
			updateMesh();
		}

		virtual void updateMesh() override {
			int i = 0;
			int stride = 5;
			float* mesh = m_mesh->getVertices();
			for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
				for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
					mesh[stride*i+2] = m_grid[i]/511.0;
					i++;
				}
			}
			m_mesh->update();
		}
};

class DenseChunk: public Chunk {	
	public:
		DenseChunk(unsigned int x, unsigned int y): Chunk(x, y) {
			int stride = 5;
			m_grid = new Block[CHUNK_SIZE*CHUNK_SIZE];
			float* vertices = new float[CHUNK_SIZE*CHUNK_SIZE*4*stride];
			unsigned int* indices = new unsigned int[CHUNK_SIZE*CHUNK_SIZE*6];
			unsigned int i = 0;
			double z;
			for (int x = 0 ; x < CHUNK_SIZE ; x++) {
				for (int y = 0 ; y < CHUNK_SIZE ; y++) {
					z = m_noise.sample(x, y)-0.5;
					m_grid[y*CHUNK_SIZE+x] = z > 0 ? z*255 : 0;
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
	
		virtual void updateMesh() override {
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
};


struct Squarre {
	unsigned int nVertices;
	unsigned int* vertices;
	Squarre(std::initializer_list<unsigned int> vertices_): nVertices(vertices_.size()) {
		vertices = new unsigned int[nVertices];
		for (unsigned int i = 0 ; i < nVertices ; i++) {
			vertices[i] = vertices_.begin()[i];
		}
	}
};

class MarchingSquarre: public Chunk {
	private:
		static Squarre s_squarres[6] = {{}, {0,7,1}, {0,7,2,2,7,3}, {0,6,4,4,2,0}, {0,6,5,5,3,0,0,3,2}, {0,7,1,/*1,7,3,3,7,5,*/5,4,3}};
		static unsigned int s_squarreId[16] =  {0, 1, 1, 2, 1, 2, 5, 4, 1, 5, 2, 4, 2, 4, 4, 3};
		static unsigned int s_squarreRot[16] = {0, 0, 1, 0, 3, 3, 1, 0, 2, 0, 1, 1, 2, 3, 2, 0};
		Block m_limit;

	public:
		MarchingSquarre(unsigned int x, unsigned int y): Chunk(x, y), m_limit(130) {
			int stride = 5;
			unsigned int maxTriangles = 3;
			m_grid = new Block[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)];
			float* vertices = new float[CHUNK_SIZE*CHUNK_SIZE*maxTriangles*3*stride];
			unsigned int* indices = new unsigned int[CHUNK_SIZE*CHUNK_SIZE*maxTriangles*3];
			unsigned int i = 0;
			for (int x = 0 ; x <= CHUNK_SIZE ; x++) {
				for (int y = 0 ; y <= CHUNK_SIZE ; y++) {
					m_grid[y*(CHUNK_SIZE+1)+x] = 255*m_noise.sample(x, y);
					if (x < CHUNK_SIZE && y < CHUNK_SIZE) {
						for (unsigned int j = 0 ; j < maxTriangles*3 ; j++) {
							indices[maxTriangles*3*i+j] = maxTriangles*3*i+j;
						}
						i++;
					}
				}
			}
			m_mesh = new Mesh(vertices, 0, indices, maxTriangles*3*i, {{Float3}, {Float2}});
			updateMesh();
		}

		Block getLimit() { return m_limit; }

		void setLimit(Block limit) {
			m_limit = limit;
			updateMesh();
		}

		int configuration(unsigned int x, unsigned int y) {
			int a = m_grid[(y+1)*(CHUNK_SIZE+1)+x] > m_limit ? 1 : 0;
			int b = m_grid[(y+1)*(CHUNK_SIZE+1)+x+1] > m_limit ? 2 : 0;
			int c = m_grid[y*(CHUNK_SIZE+1)+x] > m_limit ? 4 : 0;
			int d = m_grid[y*(CHUNK_SIZE+1)+x+1] > m_limit ? 8 : 0;
			return a+b+c+d;
		}

		float smooth(Block a, Block b) {
			return ((float)a-m_limit)/(a-b);
		}

		void coordinates(unsigned int x, unsigned int y, float* u, float* v, unsigned int index, unsigned int rotation) {
			int a = m_grid[(y+1)*(CHUNK_SIZE+1)+x];
			int b = m_grid[(y+1)*(CHUNK_SIZE+1)+x+1];
			int c = m_grid[y*(CHUNK_SIZE+1)+x];
			int d = m_grid[y*(CHUNK_SIZE+1)+x+1];

			index = (index+2*rotation)%8;
			switch (index) {
				case 0: *u = 0.0; *v = 1.0; return;
				case 1: *u = smooth(a, b); *v = 1.0; return;
				case 2: *u = 1.0; *v = 1.0; return;
				case 3: *u = 1.0; *v = smooth(d, b); return;
				case 4: *u = 1.0; *v = 0.0; return;
				case 5: *u = smooth(c, d); *v = 0.0; return;
				case 6: *u = 0.0; *v = 0.0; return;
				case 7: *u = 0.0; *v = smooth(c, a); return;
			}
		}
		
		virtual void updateMesh() override {
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
					config = configuration(x, y);
					vertices = s_squarres[s_squarreId[config]].vertices;
					nVertices = s_squarres[s_squarreId[config]].nVertices;
					for (unsigned int j = 0 ; j < nVertices ; j++) {
						coordinates(x, y, &u, &v, vertices[j], s_squarreRot[config]);
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
};
