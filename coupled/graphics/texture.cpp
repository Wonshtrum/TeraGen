#include <GL/glew.h>
#include "utils/file.h"

class Texture {
	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_channels;
		char* m_pixels;

		void applyPixels(const char* pixels) {
			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, (m_channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, pixels);
		}

	public:
		Texture(const char* name, unsigned int channels = 0): m_channels(channels) {
			m_pixels = readImage(name, &m_width, &m_height, &m_channels);
			applyPixels(m_pixels);
		}

		Texture(char* pixels, unsigned int width, unsigned int height, unsigned int channels = 4): m_width(width), m_height(height), m_channels(channels), m_pixels(pixels) {
			applyPixels(m_pixels);
		}

		~Texture() {
			delete[] m_pixels;
			glDeleteTextures(1, &m_id);
		}

		static Texture* createBlank(unsigned int channels = 4) {
			char full = (char)255;
			char* pixel = new char[4] {full, full, full, full};
			return new Texture(pixel, 1, 1, channels);
		}

		void bind(unsigned int slot = 0) {
			glActiveTexture(GL_TEXTURE0+slot);
			glBindTexture(GL_TEXTURE_2D, m_id);
		}

		void print() {
			std::cout << m_width << "/" << m_height << "/" << m_channels << std::endl;
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
