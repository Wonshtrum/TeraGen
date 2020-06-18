#ifndef __MESH_H__
#define __MESH_H__

#include <GL/glew.h>
#include <iostream>
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
		Mesh(float* vertices, unsigned int nVertices, unsigned int* indices, unsigned int nIndices, Layout layout);

		Mesh();

		~Mesh();

		float* getVertices();

		void update();

		void bind();

		void draw();
};


#endif