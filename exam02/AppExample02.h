#ifndef APPEXAMPLE02_H_
#define APPEXAMPLE02_H_

#include "AbstractApp.h"

class AppExample02: public AbstractApp {
public:
	AppExample02();
	virtual ~AppExample02();

	void update();
	void render();
	void build();
};

#endif /* APPEXAMPLE02_H_ */
