#ifndef OPENGL_UTILS_H_
#define OPENGL_UTILS_H_

#include <vector>

#include <GL/glew.h>
#include "Log.h"

namespace OpenGLUtils {
	const char* getShaderType(GLenum eShaderType) {
		const char *strShaderType = NULL;
		switch (eShaderType) {
			case GL_VERTEX_SHADER:
				strShaderType = "vertex";
				break;
			case GL_GEOMETRY_SHADER:
				strShaderType = "geometry";
				break;
			case GL_FRAGMENT_SHADER:
				strShaderType = "fragment";
				break;
		}
		return strShaderType;
	}

	GLuint createShader(GLenum eShaderType, const char* strShaderFile) {
		// create shader
		GLuint shaderId = glCreateShader(eShaderType);

		// set shader source
		glShaderSource(shaderId, 1, &strShaderFile, NULL);

		// compile shader
		glCompileShader(shaderId);

		// check shader error
		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE) {
			GLint infoLogLength;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shaderId, infoLogLength, NULL, strInfoLog);

			const char *strShaderType = getShaderType(eShaderType);
			Log::print("Unable to compile %s shader\n%s", strShaderType, strInfoLog);
			return false;
		}

		return shaderId;
	}

	GLuint createProgram(std::vector<GLuint> &shaderList) {
		GLuint program = glCreateProgram();

		for (size_t i = 0; i < shaderList.size(); i++) {
			glAttachShader(program, shaderList[i]);
		}

		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			Log::print("Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		for (size_t i = 0; i < shaderList.size(); i++) {
			glDetachShader(program, shaderList[i]);
		}

		return program;
	}

	GLuint initGLStructure(const char * vertexShaderSource, const char * fragmentShaderSource) {
		std::vector<GLuint> shaderList;

		shaderList.push_back(createShader(GL_VERTEX_SHADER, vertexShaderSource));
		shaderList.push_back(createShader(GL_FRAGMENT_SHADER, fragmentShaderSource));

		GLuint programId = createProgram(shaderList);

		std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

		return programId;
	}
}
#endif /* OPENGL_UTILS_H_ */
