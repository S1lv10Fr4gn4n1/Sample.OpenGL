#ifndef APPEXAMPLE01_H_
#define APPEXAMPLE01_H_

#include "AbstractApp.h"

class AppExample01: public AbstractApp {
public:
	AppExample01();
	virtual ~AppExample01();

	const char * getTitle();

	bool init();
	void update(float timeStep);
	void render(float timeStep);
	void cleanUp();
	void reshape(int width, int height);
};

#endif /* APPEXAMPLE01_H_ */
