#ifndef __REGION_H__
#define __REGION_H__

#include "utils/file.h"
#include "macros.h"

#define REGION_SIZE (CHUNK_SIZE+1)*(CHUNK_SIZE+1)

class Region {
	private:
		Block* m_data;
		unsigned int m_nChunks;
		ChunkId* m_chunkList;
	public:
		Region(const char* file);
};


#endif