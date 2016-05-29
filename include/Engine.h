#ifndef ENGINE_H_
#define ENGINE_H_

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include "AbstractApp.h"
#include "Timer.h"

class Engine {
private:
	SDL_Window *window;
	SDL_GLContext glContext;
	AbstractApp *app;
	Timer *fpsTimer;

	bool init();
	bool initSDL();
	void setupOpenGL();
	bool initSDLWindow();
	bool initSDLGLContext();
	bool initGLEW();

	void update(float timeStep);
	void render(float timeStep);
	bool eventHandler();

	void calculatePrintFps();
	void printVersions();

	void cleanUp();
	void halt(const char * _msg);
	void reshape();
public:
	Engine();
	~Engine();

	void setApp(AbstractApp *app);
	int execute();
};

#endif /* ENGINE_H_ */
