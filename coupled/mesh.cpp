#include <GL/glew.h>
#include <iostream>

class Mesh {
	private:
		unsigned int m_abo = 0;
		unsigned int m_ibo = 0;
		unsigned int m_nVertices;
		unsigned int m_nIndices;

	public:
		Mesh(float* vertices, unsigned int nVertices, unsigned int* indices, unsigned int nIndices): m_nVertices(nVertices), m_nIndices(nIndices) {
			glGenBuffers(1, &m_abo);
			glBindBuffer(GL_ARRAY_BUFFER, m_abo);
			glBufferData(GL_ARRAY_BUFFER, nVertices*sizeof(float), vertices, GL_STATIC_DRAW);

			glGenBuffers(1, &m_ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices*sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}

		void bind() {
			glBindBuffer(GL_ARRAY_BUFFER, m_abo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		}

		void draw() {
			glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, NULL);
		}
};
