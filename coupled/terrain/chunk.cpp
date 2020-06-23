#include "graphics/mesh.h"
#include "graphics/layout.h"
#include "utils/noise.h"

#define CHUNK_SIZE 64
typedef unsigned char Block;

class Chunk {
	private:
		Block* m_grid;
		Mesh* m_mesh;
	
	public:
		Chunk() {
			m_grid = new Block[CHUNK_SIZE*CHUNK_SIZE];
			int stride = 4;
			float* vertices = new float[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*stride];
			unsigned int* indices = new unsigned int[(CHUNK_SIZE+1)*(CHUNK_SIZE+1)*6];
			unsigned int i = 0;
			unsigned int j = 0;
			double dx, dy;
			double f = 16.0;
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
					dx = PerlinNoise::noise2D((f*x)/CHUNK_SIZE, (f*y)/CHUNK_SIZE);
					dy = PerlinNoise::noise2D((f*x)/CHUNK_SIZE+128, (f*y)/CHUNK_SIZE);
					vertices[stride*j+0] = (x+dx*16.0/f)/CHUNK_SIZE;
					vertices[stride*j+1] = (y+dy*16.0/f)/CHUNK_SIZE;
					vertices[stride*j+2] = x*1.0/CHUNK_SIZE;
					vertices[stride*j+3] = y*1.0/CHUNK_SIZE;
					i++;
					j++;
				}
			}
			m_mesh = new Mesh(vertices, j, indices, 6*i, {{Float2}, {Float2}});
		}

		~Chunk() {
			delete[] m_grid;
			delete m_mesh;
		}

		Mesh* getMesh() { return m_mesh; }

		void draw() {
			m_mesh->draw();
		}
};
