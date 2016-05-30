#include "AppExample01.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
#include "utils/OpenGLUtils.h"
#include "utils/FileUtils.h"

GLuint VAO = 0;
GLuint programId = 0;
GLuint timeLocation;

AppExample01::AppExample01() {
}

AppExample01::~AppExample01() {
}

bool AppExample01::init() {
	std::string vertexShader = File::getFileContent("./exam01/shader03.vert");
	std::string fragmentShader = File::getFileContent("./exam01/shader03.frag");

	programId = OpenGLUtils::initGLStructure(vertexShader.c_str(), fragmentShader.c_str());

	// Vertex Buffer Object (VBO) Data
	const GLfloat vertexData[] = {
	     0.0f,    0.5f, 0.0f, 1.0f, // point 1
	     0.5f, -0.366f, 0.0f, 1.0f, // point 2
	    -0.5f, -0.366f, 0.0f, 1.0f, // point 3
	     1.0f,    0.0f, 0.0f, 1.0f, // color 1
	     0.0f,    1.0f, 0.0f, 1.0f, // color 2
	     0.0f,    0.0f, 1.0f, 1.0f, // color 3
	};

	GLuint VBO;

	// create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STREAM_DRAW);

	// create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0); // layout 1, position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1); // layout 2, color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) 48);

	// get the variable offset (uniform) from vertex shader
	timeLocation = glGetUniformLocation(programId, "time");

	// set loopDuration on vertex shader
	GLuint loopDurationLocation = glGetUniformLocation(programId, "loopDuration");
	glUseProgram(programId);
	glUniform1f(loopDurationLocation, 3.0f);
	glUseProgram(0);

	return true;
}

const char * AppExample01::getTitle() {
	return "Example 01";
}

void AppExample01::update(float timeStep) {
//Log::print("update %f", timeStep);

}

void AppExample01::render(float timeStep) {
//	Log::print("render %f", timeStep);

	// initialize clear color
	glClearColor(0.9f, 0.9f, 0.9f, 1.f);
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind program
	glUseProgram(programId);
	glUniform1f(timeLocation, SDL_GetTicks() / 1000.0f);
	glBindVertexArray(VAO);

	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	// unbind program
	glUseProgram(NULL);
}

void AppExample01::cleanUp() {
	Log::print("cleanUp");
}

void AppExample01::reshape(int width, int height) {
	Log::print("reshape w:%d h:%d", width, height);
}
