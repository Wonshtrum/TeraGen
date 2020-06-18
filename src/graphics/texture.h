#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <iostream>
#include "utils/file.h"

class Texture {
	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_channels;
		char* m_pixels;

		void applyPixels(const char* pixels);

	public:
		Texture(const char* name, unsigned int channels = 0);

		Texture(char* pixels, unsigned int width, unsigned int height, unsigned int channels = 4);

		~Texture();

		static Texture* createBlank(unsigned int channels = 4);

		void bind(unsigned int slot = 0);

		void print();
};


#endif