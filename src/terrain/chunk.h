#ifndef __CHUNK_H__
#define __CHUNK_H__

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


#endif