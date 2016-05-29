#include "AppExample02.h"
#include "Engine.h"

int main() {
	AppExample02 *app = new AppExample02();
	app->build();

	Engine *engine = new Engine();
	engine->setApp(app);
	int returnCode = engine->execute();

	delete app;
	delete engine;

	return returnCode;
}
