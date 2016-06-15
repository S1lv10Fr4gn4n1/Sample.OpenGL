#ifndef APPEXAMPLE02_H_
#define APPEXAMPLE02_H_

#include "AbstractApp.h"

class AppExample02: public AbstractApp {
public:
	AppExample02();
	virtual ~AppExample02();

	const char * getTitle();

	bool init();
	void update(float timeStep);
	void render(float timeStep);
	void cleanUp();
	void reshape(int width, int height);
};

#endif /* APPEXAMPLE02_H_ */
