#include <Engine.h>
#include <GL/glew.h>
#include "utils/Log.h"

int countedFrames = 1;

Engine::Engine() {
	window = nullptr;
	glContext = nullptr;
	app = nullptr;
	fpsTimer = new Timer();
}

Engine::~Engine() {
	if (fpsTimer) {
		delete fpsTimer;
	}
}

void Engine::setApp(AbstractApp *app) {
	this->app = app;
}

int Engine::execute() {
	if (!init()) {
		halt("Engine init problem");
		return -1;
	}

//	TODO implement this timestep
//	http://gafferongames.com/game-physics/fix-your-timestep/
	float t = 0.0f;
	float dt = 0.1f;
	float currentTime = 0.0f;
	float accumulator = 0.0f;

	fpsTimer->start();
	bool running = true;
	while (running) {
		running = eventHandler();
//		calculatePrintFps();

		const float newTime = SDL_GetTicks();
		float deltaTime = newTime - currentTime;
		currentTime = newTime;

		if (deltaTime > 0.25f) {
			deltaTime = 0.25f;
		}

		accumulator += deltaTime / 2;

		while (accumulator >= dt) {
			accumulator -= dt;
			update(accumulator);
			t += dt;
		}

		calculatePrintFps();
//		update(timeStep);
		render(accumulator);
	}

	cleanUp();
	return 0;
}

bool Engine::init() {
	if (!app) {
		Log::print("App not informed");
		return false;
	}

	if (!initSDL()) {
		return false;
	}

	setupOpenGL();

	if (!initSDLWindow()) {
		return false;
	}

	if (!initSDLGLContext()) {
		return false;
	}

	if (!initGLEW()) {
		return false;
	}

	printVersions();

	if (!app->init()) {
		return false;
	}

	reshape();

	return true;
}

void Engine::update(float timeStep) {
	app->update(timeStep);
}

void Engine::render(float timeStep) {
	app->render(timeStep);

	// swap our back buffer to the front
	SDL_GL_SwapWindow(window);
}

void Engine::cleanUp() {
	app->cleanUp();

	// delete our opengl context, destroy our window, and shutdown SDL
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::halt(const char *_msg) {
	Log::print("Die: %s, %s", _msg, SDL_GetError());
	cleanUp();
}

bool Engine::eventHandler() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}

		if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
				case SDL_WINDOWEVENT_SHOWN:
					SDL_Log("Window %d shown", event.window.windowID);
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					SDL_Log("Window %d hidden", event.window.windowID);
					break;
				case SDL_WINDOWEVENT_RESTORED:
					SDL_Log("Window %d restored", event.window.windowID);
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
                    countedFrames = 1;
                    fpsTimer->start();
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
                    fpsTimer->stop();
					break;
				case SDL_WINDOWEVENT_RESIZED:
					reshape();
					break;
				default:
					break;
			}
		}
	}

	return true;
}

void Engine::reshape() {
	int screen_w, screen_h;
	SDL_GetWindowSize(window, &screen_w, &screen_h);
	app->reshape(screen_w, screen_h);
	glViewport(0, 0, screen_w, screen_h);
}

bool Engine::initSDL() {
	int sdlInit = SDL_INIT_VIDEO; //SDL_INIT_EVERYTHING
	if (SDL_Init(sdlInit) != 0) {
		Log::print("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Engine::setupOpenGL() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //SDL_GL_CONTEXT_PROFILE_COMPATIBILITY

	// turn on double buffering with a 24bit Z buffer.
	// you may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

bool Engine::initSDLWindow() {
	window = SDL_CreateWindow(app->getTitle(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			600,
			600,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == nullptr) {
		Log::print("SDL_CreateWindow error %s", SDL_GetError());
		return false;
	}

	return true;
}

bool Engine::initGLEW() {
	GLenum error;
	glewExperimental = GL_TRUE;
	error = glewInit();
	if (GLEW_OK != error) {
		Log::print("GLEWInit error: %s", glewGetErrorString(error));
		return false;
	}
	return true;
}

bool Engine::initSDLGLContext() {
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		Log::print("SDL_GL_CreateContext error %s", SDL_GetError());
		return false;
	}

	// SDL_GL_SetSwapInterval(0) set immediate swap (high FPS)
	// this makes our buffer swap syncronized with the monitor's vertical refresh
	// vsync
	if (SDL_GL_SetSwapInterval(1) != 0) {
		Log::print("Warning: unable to set VSync. Error %s", SDL_GetError());
	}

	return true;
}

void Engine::calculatePrintFps() {
    int ticks = fpsTimer->getTicks();
    if (countedFrames != 0 && ticks != 0) {
        // calculate and correct fps
        float avgFPS = countedFrames / (ticks / 1000.f);
        countedFrames++;

        int ticksModule = ticks % 1000;
        if (ticksModule >= 0 && ticksModule <= 12) {
            Log::print("FPS %f", avgFPS);
        }
    }
}

void Engine::printVersions() {
    Log::print("----------------------------------------------------------------");
    Log::print("Graphics Successfully Initialized");
    Log::print("OpenGL Info");
    Log::print("    Version: %s", glGetString(GL_VERSION));
    Log::print("     Vendor: %s", glGetString(GL_VENDOR));
    Log::print("   Renderer: %s", glGetString(GL_RENDERER));
    Log::print("    Shading: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    Log::print("       GLEW: %s", glewGetString(GLEW_VERSION));
    Log::print("----------------------------------------------------------------");
}


