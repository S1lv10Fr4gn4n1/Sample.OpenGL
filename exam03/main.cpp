#include "Engine.h"
#include "AppExample03.h"

int main() {
	AppExample03 *app = new AppExample03();

	Engine *engine = new Engine();
	engine->setApp(app);
	int returnCode = engine->execute();

	delete app;
	delete engine;

	return returnCode;
}
