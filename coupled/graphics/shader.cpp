#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "utils/file.h"

class Shader {
	private:
		unsigned int m_id;
	public:
		Shader(const char* vertexShader, const char* fragmentShader) {
			unsigned int program = glCreateProgram();
			unsigned int vs = Shader::compile(GL_VERTEX_SHADER, vertexShader);
			unsigned int fs = Shader::compile(GL_FRAGMENT_SHADER, fragmentShader);
			glAttachShader(program, vs);
			glAttachShader(program, fs);
			glLinkProgram(program);
			glValidateProgram(program);
			glDeleteShader(vs);
			glDeleteShader(fs);
			m_id = program;
		}

		~Shader() { glDeleteProgram(m_id); }

		static Shader* fromFile(const char* vertexFile, const char* fragmentFile) {
			const char* vertexShader = readFile(vertexFile);
			const char* fragmentShader = readFile(fragmentFile);
			Shader* shader = new Shader(vertexShader, fragmentShader);
			delete[] vertexShader;
			delete[] fragmentShader;
			return shader;
		}

		unsigned int getId() { return m_id; }

		void bind() { glUseProgram(m_id); }

		static unsigned int compile(unsigned int type, const char* source) {
			unsigned int shader = glCreateShader(type);
			glShaderSource(shader, 1, &source, nullptr);
			glCompileShader(shader);
			int result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				int length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length*sizeof(char));
				glGetShaderInfoLog(shader, length, &length, message);
				std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " shader" << std::endl;
				std::cout << message << std::endl;
				glDeleteShader(shader);
				return 0;
			}
			return shader;
		}
};
