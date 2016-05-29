#include "AppExample01.h"
#include "utils/OpenGLUtils.h"
#include <GL/glew.h>

GLuint gVAO1 = 0;
GLuint gVAO2 = 0;
GLuint programId = 0;

AppExample01::AppExample01() {
}

AppExample01::~AppExample01() {
}

bool AppExample01::init() {
	// vertex shader source
	const GLchar *vertexShaderSource = { "#version 400\nin vec3 vp; "
			"void main() { "
			"		gl_Position = vec4(vp, 1.0); "
			"}" };

	// fragment shader source
	const GLchar *fragmentShaderSource { "#version 400\nout "
			"vec4 frag_colour; "
			"void main() { "
			"	frag_colour = vec4(1.0, 1.0, 1.0, 1.0); "
			"}" };

	programId = OpenGLUtils::initGLStructure(vertexShaderSource, fragmentShaderSource);

	// Vertex Buffer Object (VBO) Data
	GLfloat vertexData1[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };
	GLfloat vertexData2[] = { 0.5f, 0.9f, 0.0f, 0.9f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f };

	GLuint gVBO1;
	GLuint gVBO2;

	// create VBO1
	glGenBuffers(1, &gVBO1);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO1);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertexData1, GL_STATIC_DRAW);

	// create VAO1
	glGenVertexArrays(1, &gVAO1);
	glBindVertexArray(gVAO1);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// create VBO2
	glGenBuffers(1, &gVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO2);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertexData2, GL_STATIC_DRAW);

	// create VAO2
	glGenVertexArrays(1, &gVAO2);
	glBindVertexArray(gVAO2);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	return true;
}

const char * AppExample01::getTitle() {
	return "Example 01";
}

void AppExample01::update(float timeStep) {
	//Log::print("update %f", timeStep);
}

void AppExample01::render(float timeStep) {
	//Log::print("render %f", timeStep);

	// initialize clear color
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind program
	glUseProgram(programId);
	glBindVertexArray(gVAO1);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	glBindVertexArray(gVAO2);
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
