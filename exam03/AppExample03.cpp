#include "AppExample03.h"

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
GLuint offsetUniform = 0;

bool depthClamping = false;
GLfloat offsetHorizontalObject = 0.0f;

AppExample03::AppExample03() {
}

AppExample03::~AppExample03() {
}


bool AppExample03::init() {
	std::string vertexShader = File::getFileContent("./exam03/shader.vert");
	std::string fragmentShader = File::getFileContent("./exam03/shader.frag");

	programId = OpenGLUtils::initGLStructure(vertexShader.c_str(), fragmentShader.c_str());

	// create buffers
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;

	// create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0); // layout 1, position
	glEnableVertexAttribArray(1); // layout 2, color
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBindVertexArray(NULL);

	// setup perspective matrix
	memset(perspectiveMatrix, 0, sizeof(float) * 16);
	perspectiveMatrix[0] = frustumScale;
	perspectiveMatrix[5] = frustumScale;
	perspectiveMatrix[10] = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[14] = (2 * zFar * zNear) / (zNear - zFar);
	perspectiveMatrix[11] = -1.0f;

	offsetUniform = glGetUniformLocation(programId, "offset");
	perspectiveMatrixUnif = glGetUniformLocation(programId, "perspectiveMatrix");

	glUseProgram(programId);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	return true;
}

const char * AppExample03::getTitle() {
	return "Example 03";
}

void AppExample03::update(float timeStep) {
//	Log::print("update %f", timeStep);
}

void AppExample03::render(float timeStep) {
//	Log::print("render %f", timeStep);

	// initialize clear color
	glClearColor(0.9f, 0.9f, 0.9f, 1.f);
	glClearDepth(1.0f);
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programId);

	glBindVertexArray(VAO);
	glUniform3f(offsetUniform, 0.0f, 0.0f, offsetHorizontalObject);
	glDrawElements(GL_TRIANGLES, sizeof(indexData), GL_UNSIGNED_SHORT, 0);

	glUniform3f(offsetUniform, 0.0f, 0.0f, -0.5f);
	glDrawElementsBaseVertex(GL_TRIANGLES, sizeof(indexData), GL_UNSIGNED_SHORT, 0, numberOfVertices/2);

	glBindVertexArray(NULL);
	glUseProgram(NULL);
}

void AppExample03::cleanUp() {
	Log::print("cleanUp");
}

void AppExample03::reshape(int width, int height) {
	Log::print("reshape w:%d h:%d", width, height);

	perspectiveMatrix[0] = frustumScale / (width /(float) height);
	perspectiveMatrix[5] = frustumScale;

	glUseProgram(programId);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(NULL);
}

void AppExample03::keyboardHandle(SDL_Event event) {
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			depthClamping = !depthClamping;
			// Depth Clamping
			if (depthClamping) {
				glEnable(GL_DEPTH_CLAMP);
			} else {
				glDisable(GL_DEPTH_CLAMP);
			}
		} else if (event.key.keysym.sym == SDLK_EQUALS) {
			offsetHorizontalObject += 0.05f;
		} else if (event.key.keysym.sym == SDLK_MINUS) {
			offsetHorizontalObject -= 0.05f;
		}
	}
}

