#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "../utils.h"

class Shader {
	private:
		unsigned int m_id;
	public:
		Shader(const char* vertexShader, const char* fragmentShader) ;

		static Shader* fromFile(const char* vertexFile, const char* fragmentFile) ;

		unsigned int getId() ;

		void bind() ;

		static unsigned int compile(unsigned int type, const char* source) ;
};


#endif