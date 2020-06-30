#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "core.h"
#include "graphics/mesh.h"
#include "graphics/layout.h"
#include "utils/noise.h"
#include "utils/file.h"

class Chunk {
	protected:
		Mesh* m_mesh;
		Block* m_grid;
		unsigned int m_x;
		unsigned int m_y;
		LayeredNoise<PerlinNoise> m_noise;

	public:
		Chunk(unsigned int x, unsigned int y);

		virtual ~Chunk();

		virtual void updateMesh() = 0;

		virtual void draw();
};

class LightChunk: public Chunk {
	public:
		LightChunk(unsigned int x, unsigned int y);

		static constexpr unsigned int getSize() { return CHUNK_SIZE+1; }

		virtual void updateMesh();
};

class DenseChunk: public Chunk {	
	public:
		DenseChunk(unsigned int x, unsigned int y);

		static constexpr unsigned int getSize() { return CHUNK_SIZE; }

		virtual void updateMesh();
};

struct Squarre {
	unsigned int nVertices;
	unsigned int* vertices;
	Squarre(std::initializer_list<unsigned int> vertices_);
};

class MarchingSquarre: public Chunk {
	private:
		static Squarre s_squarres[6];
		static unsigned int s_squarreId[16];
		static unsigned int s_squarreRot[16];
		Block m_limit;

	public:
		MarchingSquarre(unsigned int x, unsigned int y);

		static constexpr unsigned int getSize() { return CHUNK_SIZE+1; }

		Block getLimit();

		void setLimit(Block limit);

		int configuration(unsigned int x, unsigned int y);

		float smooth(Block a, Block b);

		void coordinates(unsigned int x, unsigned int y, float* u, float* v, unsigned int index, unsigned int rotation);

		virtual void updateMesh();
};


#endif