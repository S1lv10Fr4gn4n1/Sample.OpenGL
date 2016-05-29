#include "AppExample01.h"
#include "Engine.h"

int main() {
	AppExample01 *app = new AppExample01();

	Engine *engine = new Engine();
	engine->setApp(app);
	int returnCode = engine->execute();

	delete app;
	delete engine;

	return returnCode;
}
