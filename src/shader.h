#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <iostream>

class Shader {
	private:
		unsigned int id;
	public:
		Shader(const char* vertexShader, const char* fragmentShader) ;

		unsigned int getId() ;

		void bind() ;

		static unsigned int compile(unsigned int type, const char* source) ;
};


#endif