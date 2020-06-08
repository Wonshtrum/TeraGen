#include "shader.h"

Shader::Shader(const char* vertexShader, const char* fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = Shader::compile(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = Shader::compile(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	this->id = program;
}

unsigned int Shader::getId() { return this->id; }

void Shader::bind() {
	glUseProgram(this->id);
}

unsigned int Shader::compile(unsigned int type, const char* source) {
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
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}
