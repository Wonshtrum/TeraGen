#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "../graphics/mesh.h"

#define CHUNK_SIZE 16
typedef unsigned char Block;

class Chunk {
	private:
		Block m_grid[CHUNK_SIZE*CHUNK_SIZE];
		Mesh m_mesh;

	public:
		Chunk() ;

		void draw() ;
};


#endif