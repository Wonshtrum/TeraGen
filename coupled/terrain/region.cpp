#include "utils/file.h"

template <class chunk>
class Region {
	private:
		Block* m_data;
		unsigned int m_nChunks;
		ChunkId* m_chunkList;
		static const unsigned int s_regionSize = chunk::getSize()*chunk::getSize();

	public:
		Region(const char* file) {
			int size;
			m_data = (Block*)readFile(file, &size);
			CORE_TRACE(size);
			int nodeSize = s_regionSize+2;
			m_nChunks = size/nodeSize;
			m_chunkList = new ChunkId[m_nChunks];
			for (unsigned int i = 0 ; i < m_nChunks ; i++) {
				m_chunkList[i] = (m_data[i*nodeSize]<<8)+m_data[i*nodeSize+1];
				std::cout << m_chunkList[i];
			}
		}
};
