#ifndef __CHUNK_H__
#define __CHUNK_H__

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
		Chunk();

		~Chunk();

		void draw();
};


#endif