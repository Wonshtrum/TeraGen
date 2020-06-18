#include "texture.h"


void Texture::applyPixels(const char* pixels) {
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, (m_channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, pixels);
}

Texture::Texture(const char* name, unsigned int channels): m_channels(channels) {
	m_pixels = readImage(name, &m_width, &m_height, &m_channels);
	applyPixels(m_pixels);
}

Texture::Texture(char* pixels, unsigned int width, unsigned int height, unsigned int channels): m_width(width), m_height(height), m_channels(channels), m_pixels(pixels) {
	applyPixels(m_pixels);
}

Texture::~Texture() { delete[] m_pixels; }

Texture* Texture::createBlank(unsigned int channels) {
	char full = (char)255;
	char* pixel = new char[4] {full, full, full, full};
	return new Texture(pixel, 1, 1, channels);
}

void Texture::bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::print() {
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
