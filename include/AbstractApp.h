#ifndef ABSTRACTAPP_H_
#define ABSTRACTAPP_H_

#include <SDL2/SDL_events.h>

class AbstractApp {
public:
	virtual ~AbstractApp() {};

	virtual bool init() = 0;
	virtual void update(float timeStep) = 0;
	virtual void render(float timeStep) = 0;
	virtual void cleanUp() = 0;
	virtual void reshape(int width, int height) = 0;
	virtual void keyboardHandle(SDL_Event event) = 0;

	virtual const char * getTitle() = 0;
};

#endif /* ABSTRACTAPP_H_ */
