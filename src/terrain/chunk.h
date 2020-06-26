#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <initializer_list>
#include "graphics/mesh.h"
#include "graphics/layout.h"
#include "utils/noise.h"
#include "macros.h"

typedef uint8_t Block;

class LightChunk {
	private:
		Mesh* m_mesh;

	public:
		LightChunk();

		~LightChunk();

		void seedMesh(double dx, double dy);

		void draw();
};

class DenseChunk {
	private:
		Mesh* m_mesh;
		Block* m_grid;

	public:
		DenseChunk();

		~DenseChunk();

		void updateMesh();

		void draw();
};

struct Squarre {
	unsigned int nVertices;
	unsigned int* vertices;
	Squarre(std::initializer_list<unsigned int> vertices_);
};

class MarchingSquarre {
	private:
		Mesh* m_mesh;
		Block* m_grid;
		static Squarre s_squarres[6];
		static unsigned int s_squarreId[16];
		static unsigned int s_squarreRot[16];
	public:
		MarchingSquarre();

		~MarchingSquarre();

		int configuration(unsigned int x, unsigned int y, Block limit);

		float smooth(Block a, Block b, Block limit);

		void coordinates(unsigned int x, unsigned int y, float* u, float* v, unsigned int index, unsigned int rotation, Block limit);

		void updateMesh(Block limit);

		void draw();
};


#endif