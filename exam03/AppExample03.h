#ifndef APPEXAMPLE03_H_
#define APPEXAMPLE03_H_

#include "AbstractApp.h"

class AppExample03: public AbstractApp {
public:
	AppExample03();
	virtual ~AppExample03();

	const char * getTitle();

	bool init();
	void update(float timeStep);
	void render(float timeStep);
	void cleanUp();
	void reshape(int width, int height);
	void keyboardHandle(SDL_Event event);
};

#endif /* APPEXAMPLE03_H_ */
