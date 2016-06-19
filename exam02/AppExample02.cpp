#include "AppExample02.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
#include "utils/OpenGLUtils.h"
#include "utils/FileUtils.h"
#include "data.h"

GLuint VAO = 0;
GLfloat perspectiveMatrix[16];
GLuint programId = 0;
GLuint perspectiveMatrixUnif = 0;

AppExample02::AppExample02() {
}

AppExample02::~AppExample02() {
}


bool AppExample02::init() {
	std::string vertexShader = File::getFileContent("./exam02/shader01.vert");
	std::string fragmentShader = File::getFileContent("./exam02/shader01.frag");

	programId = OpenGLUtils::initGLStructure(vertexShader.c_str(), fragmentShader.c_str());

	// create VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0); // layout 1, position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1); // layout 2, color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(vertexData) / 2));

	// setup perspective matrix
	memset(perspectiveMatrix, 0, sizeof(float) * 16);
	perspectiveMatrix[0] = frustumScale;
	perspectiveMatrix[5] = frustumScale;
	perspectiveMatrix[10] = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[14] = (2 * zFar * zNear) / (zNear - zFar);
	perspectiveMatrix[11] = -1.0f;

	GLuint offsetUniform = glGetUniformLocation(programId, "offset");
	perspectiveMatrixUnif = glGetUniformLocation(programId, "perspectiveMatrix");

	glUseProgram(programId);
	glUniform2f(offsetUniform, 0.5f, 0.5f);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	return true;
}

const char * AppExample02::getTitle() {
	return "Example 02";
}

void AppExample02::update(float timeStep) {
//	Log::print("update %f", timeStep);
}

void AppExample02::render(float timeStep) {
//	Log::print("render %f", timeStep);

	// initialize clear color
	glClearColor(0.9f, 0.9f, 0.9f, 1.f);
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind program
	glUseProgram(programId);
	glBindVertexArray(VAO);

	// draw points 0-36 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// unbind program
	glUseProgram(NULL);
}

void AppExample02::cleanUp() {
	Log::print("cleanUp");
}

void AppExample02::reshape(int width, int height) {
	Log::print("reshape w:%d h:%d", width, height);

	perspectiveMatrix[0] = frustumScale / (width /(float) height);
	perspectiveMatrix[5] = frustumScale;

	glUseProgram(programId);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(NULL);
}

