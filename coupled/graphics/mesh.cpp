#include <GL/glew.h>
#include "layout.h"

class Mesh {
	private:
		unsigned int m_vao;
		unsigned int m_abo;
		unsigned int m_ibo;
		unsigned int m_nVertices;
		unsigned int m_nIndices;
		unsigned int* m_indices;
		float* m_vertices;
		Layout m_layout;

	public:
		Mesh(float* vertices, unsigned int nVertices, unsigned int* indices, unsigned int nIndices, Layout layout): m_nVertices(nVertices), m_nIndices(nIndices), m_indices(indices), m_vertices(vertices), m_layout(layout) {
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);

			glGenBuffers(1, &m_abo);
			glBindBuffer(GL_ARRAY_BUFFER, m_abo);
			glBufferData(GL_ARRAY_BUFFER, nVertices*layout.getStride(), vertices, GL_STATIC_DRAW);

			layout.bind();

			glGenBuffers(1, &m_ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices*sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}

		Mesh(): m_nVertices(0), m_nIndices(0), m_indices(NULL), m_vertices(NULL) {}

		~Mesh() {
			delete[] m_vertices;
			delete[] m_indices;
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_abo);
			glDeleteBuffers(1, &m_ibo);
		}

		unsigned int getNVertices() { return m_nVertices; }
		void setNVertices(unsigned int nVertices) { m_nVertices = nVertices; }
		float* getVertices() { return m_vertices; }

		void update() {
			glBindBuffer(GL_ARRAY_BUFFER, m_abo);
			glBufferData(GL_ARRAY_BUFFER, m_nVertices*m_layout.getStride(), m_vertices, GL_STATIC_DRAW);
		}

		void bind() {
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		}

		void draw() {
			bind();
			glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, NULL);
		}
};
