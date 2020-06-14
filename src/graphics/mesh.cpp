#include "mesh.h"


Mesh::Mesh(float* vertices, unsigned int nVertices, unsigned int* indices, unsigned int nIndices): m_nVertices(nVertices), m_nIndices(nIndices), m_vertices(vertices) {
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_abo);
	glBindBuffer(GL_ARRAY_BUFFER, m_abo);
	glBufferData(GL_ARRAY_BUFFER, nVertices*sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (const void*)0);

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices*sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

Mesh::Mesh(): m_vao(0), m_abo(0), m_ibo(0), m_nVertices(0), m_nIndices(0), m_vertices(NULL) {}

float* Mesh::getVertices() { return m_vertices; }

void Mesh::update() {
	glBindBuffer(GL_ARRAY_BUFFER, m_abo);
	glBufferData(GL_ARRAY_BUFFER, m_nVertices*sizeof(float), m_vertices, GL_STATIC_DRAW);
}

void Mesh::bind() {
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void Mesh::draw() {
	bind();
	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, NULL);
}
