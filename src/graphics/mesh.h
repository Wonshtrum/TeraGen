#ifndef __MESH_H__
#define __MESH_H__

#include <GL/glew.h>
#include <iostream>

class Mesh {
	private:
		unsigned int m_vao;
		unsigned int m_abo;
		unsigned int m_ibo;
		unsigned int m_nVertices;
		unsigned int m_nIndices;
		float* m_vertices;

	public:
		Mesh(float* vertices, unsigned int nVertices, unsigned int* indices, unsigned int nIndices);

		Mesh();

		float* getVertices() ;

		void update() ;

		void bind() ;

		void draw() ;
};


#endif