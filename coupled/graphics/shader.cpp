#include <GL/glew.h>
#include "utils/file.h"
#include "math/matrix.h"
#include "math/vector.h"

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
				CORE_ERROR("Failed to compile ", type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", " shader\n", message);
				glDeleteShader(shader);
				return 0;
			}
			return shader;
		}

		unsigned int getId() { return m_id; }

		void bind() { glUseProgram(m_id); }

		void uploadUniform(const char* name, Matrix4& mat4) {
			unsigned int location = glGetUniformLocation(m_id, name);
			glUniformMatrix4fv(location, 1, GL_FALSE, mat4.m);
		}
};
