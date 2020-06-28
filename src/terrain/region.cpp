#include "region.h"


Region::Region(const char* file) {
	int size;
	m_data = (Block*)readFile(file, &size);
	std::cout << size << std::endl;
	int nodeSize = REGION_SIZE+2;
	m_nChunks = size/nodeSize;
	m_chunkList = new ChunkId[m_nChunks];
	for (unsigned int i = 0 ; i < m_nChunks ; i++) {
		m_chunkList[i] = (m_data[i*nodeSize]<<8)+m_data[i*nodeSize+1];
		std::cout << m_chunkList[i];
	}
}
