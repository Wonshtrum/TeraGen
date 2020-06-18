#include <fstream>
#include <iostream>
#include "decompress.h"

const char* readFile(const char* name) {
	int size;
	char* content;

	std::ifstream file(name);
	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size = file.tellg();
		content = new char[size+1];
		file.seekg(0, std::ios::beg);
		file.read(content, size);
		content[size] = '\0';
		file.close();
		return content;
	}

	std::cout << "Could not open file \"" << name << "\"" << std::endl;
	exit(EXIT_FAILURE);
}

char* readImage(const char* name, unsigned int* width_, unsigned int* height_, unsigned int* channels_) {
	int skipHeader = 8;
	unsigned int channels = *channels_;
	unsigned int width;
	unsigned int height;
	unsigned int pad;
	unsigned int position = 0;
	char type;
	char* content;
	char* image;

	std::ifstream file(name);
	if (file.is_open()) {
		file.seekg(skipHeader);
		PNGChunk ihdr(file);
		if (!ihdr.is("IHDR")) {
			std::cout << "Bad format \"" << name << "\"" << std::endl;
			exit(EXIT_FAILURE);
		}

		width = PNGChunk::getLong(file);
		height = PNGChunk::getLong(file);
		char flags[5];
		file.read(flags, 5);
		if ((flags[1] != 2 && flags[1] != 6) || flags[2] || flags[3] || flags[4]) {
			std::cout << "Unsupported format \"" << name << "\"" << std::endl;
		}
		pad = flags[1] == 2 ? 3 : 4;
		if (channels == 0) {
			channels = pad;
			*channels_ = pad;
		}
		image = new char[width*height*channels];
		memset(image, 0, width*height*channels);

		PNGChunk::move(file);
		while (!file.eof()) {
			PNGChunk c(file);
			if (c.is("IEND"))
				break;
			if (c.is("IDAT")) {
				content = new char[c.m_length];
				file.read(content, c.m_length);
				autoInflate(&content, &c.m_length);
				position = 0;
				for (unsigned int y = 0 ; y < height ; y++) {
					type = content[position++];
					for (unsigned int x = 0 ; x < width ; x++) {
						for (unsigned int z = 0 ; z < pad ; z++) {
							filter((uint8_t*)content, width, pad, position, type, x > 0, y > 0);
							if (z < channels) {
								image[(y*width+x)*channels+z] = content[position];
							}
							position++;
						}
					}
				}
				delete[] content;
				*width_ = width;
				*height_ = height;
				break;
			} else {
				PNGChunk::move(file, c.m_length);
			}
			PNGChunk::move(file);
		}
		return image;
	}
	std::cout << "Could not open file \"" << name << "\"" << std::endl;
	exit(EXIT_FAILURE);
}
