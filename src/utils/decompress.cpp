#include "decompress.h"

void filter(uint8_t* buffer, unsigned int scanLine, unsigned int pad, unsigned int position, char type, bool priorH, bool priorV) {
	uint8_t null = 0;
	uint8_t* X = buffer+position;
	uint8_t* A = buffer+position-pad;
	uint8_t* B = buffer+position-pad*scanLine-1;
	uint8_t* C = buffer+position-pad*(scanLine+1)-1;
	if (!priorH) {
		A = &null;
		C = &null;
	}
	if (!priorV) {
		B = &null;
		C = &null;
	}
	int p, pa, pb, pc;
	switch (type) {
		case 0:
			return;
		case 1:
			*X += *A;
			return;
		case 2:
			*X += *B;
			return;
		case 3:
			*X += (*A+*B)/2;
			return;
		case 4:
			p = *A+*B-*C;
			pa = abs(p-*A);
			pb = abs(p-*B);
			pc = abs(p-*C);
			if (pa < pb) {
				*X += (pa < pc ? *A : *C);
			} else {
				*X += (pb < pc ? *B : *C);
			}
			return;
	}
	return;
}

bool autoInflate(char** buffer_, unsigned int* size_) {
	char* source = *buffer_;
	unsigned int size = *size_;

	int ret;
	unsigned int have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;

	unsigned int fill = 2*size;
	char* dest = new char[fill+1];
	unsigned int posIn = 0;
	unsigned int posOut = 0;

	ret = inflateInit(&strm);
	if (ret != Z_OK) {
		return false;
	}

	do {
		strm.avail_in = size > CHUNK ? CHUNK : size;
		memcpy(in, source+posIn, strm.avail_in);
		size -= strm.avail_in;
		posIn += strm.avail_in;
		if (strm.avail_in == 0) {
			break;
		}
		strm.next_in = in;
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			switch (ret) {
				case Z_STREAM_ERROR:
				case Z_NEED_DICT:
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					inflateEnd(&strm);
					return false;
			}

			have = CHUNK-strm.avail_out;
			if (posOut+have >= fill) {
				fill = posOut+have+size*2;
				char* tmp = new char[fill+1];
				memcpy(tmp, dest, posOut);
				delete[] dest;
				dest = tmp;
			}
			memcpy(dest+posOut, out, have);
			posOut += have;
		} while (strm.avail_out == 0);
	} while (ret != Z_STREAM_END);

	inflateEnd(&strm);
	if (ret != Z_STREAM_END) {
		return false;
	}

	delete[] source;
	*buffer_ = dest;
	*size_ = posOut;
	return true;
}

PNGChunk::PNGChunk(std::ifstream& file) {
	m_length = getLong(file);
	file.read(m_type, 4);
	m_type[4] = '\0';
}

uint32_t PNGChunk::getLong(std::ifstream& file) {
	char chunk[4];
	file.read(chunk, 4);
	return ((uint8_t)chunk[0] << 24)
		| ((uint8_t)chunk[1] << 16)
		| ((uint8_t)chunk[2] << 8)
		| ((uint8_t)chunk[3] << 0);
}

void PNGChunk::move(std::ifstream& file, int delta) {
	file.seekg(delta, std::ios::cur);
}

bool PNGChunk::is(const char* type) {
	return strcmp(m_type, type) == 0;
}
