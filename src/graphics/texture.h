#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GL/glew.h>
#include <iostream>
#include "utils/file.h"

class Texture {
	private:
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_channels;
		char* m_pixels;

	public:
		Texture(const char* name, char channels = 0);

		void print();
};


#endif