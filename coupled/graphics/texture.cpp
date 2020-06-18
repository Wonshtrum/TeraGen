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
		Texture(const char* name, char channels = 0): m_channels(channels) {
			m_pixels = readImage(name, &m_width, &m_height, &m_channels);
			std::cout << m_width << "/" << m_height << "/" << m_channels << std::endl;
		}

		void print() {
			for (unsigned int y = 0 ; y < m_height ; y+=2) {
				for (unsigned int x = 0 ; x < m_width ; x++) {
					std::cout << "\x1B[48;2";
					for (int doubleLine = 0 ; doubleLine < 2 ; doubleLine++) {
						for (unsigned int z = 0 ; z < 3 ; z++) {
							if (z < m_channels && y+doubleLine < m_height) {
								std::cout << ";" << (m_pixels[((y+doubleLine)*m_width+x)*m_channels+z]&255);
							} else {
								std::cout << ";" << 0;
							}
						}
						if (doubleLine == 0) {
							std::cout << ";38;2";
						}
					}
					std::cout << "m▄\x1B[0m";
				}
				std::cout << std::endl;
			}
		}
};
