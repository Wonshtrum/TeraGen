#ifndef __DECOMPRESS_H__
#define __DECOMPRESS_H__

#include <fstream>
#include <iostream>
#include <string.h>
#include <zlib.h>
#include <stdlib.h>
#define CHUNK 32768

void filter(uint8_t* buffer, unsigned int scanLine, unsigned int pad, unsigned int position, char type, bool priorH = true, bool priorV = true);

bool autoInflate(char** buffer_, unsigned int* size_);

struct PNGChunk {
	char m_type[5];
	uint32_t m_length;

	PNGChunk(std::ifstream& file);

	static uint32_t getLong(std::ifstream& file);

	static void move(std::ifstream& file, int delta = 4);

	bool is(const char* type);
};


#endif