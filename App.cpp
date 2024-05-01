/**
 * App.cpp
 */

#include "ArtemisBase.hpp"

// Initializes application components, including graphics context and empty object & panel lists
ArtemisBase::App::App() {
	// Start with null pointers for safety check
	hConsole = NULL;
	hGraphics = NULL;
	hStopwatch = new ArtemisBase::Stopwatch();
	hKeyboard = NULL;
	gameEvents = NULL;
	camera = NULL;
	hMouse = NULL;
	hCursor = NULL;
	origin = NULL;
	externalRender = NULL;
	panels = NULL;
	lights = NULL;

	// Initialize debugging (file, console)
	isDebugToFile = true;
	isDebugToConsole = true;
	debugFile.open("debug.txt");
	ArtemisUtility::String msg0 = "Debug file initialized";
	debug(msg0);
	hConsole = new ArtemisBase::Console();

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
//		kString msg1 = "Couldn't initialize SDL";
//		debug(msg1);
//		debug(SDL_GetError());
		exit(1);
	}
	
    // Setup graphics context
	hGraphics = new ArtemisBase::Graphics();
    hGraphics->setScreen(480, 640, 32);
//	kString msg2 = "Screen initialized";
//	debug(msg2);

	// Initialize other components
	hKeyboard = new ArtemisBase::Keyboard();
	gameEvents = new ArtemisBase::EventList();
	camera = new ArtemisBase::Camera();
//	kString msg3 = "Components initialized";
//	debug(msg3);

	// Initialize mouse and cursor
	hMouse = new ArtemisBase::Mouse();
	hCursor = new ArtemisBase::Cursor(hMouse);
		
	// Initialize frame tree with origin
	origin = new ArtemisBase::Object(0.0, 0.0, 0.0);
//	kString msg4 = "Origin initialized";
//	debug(msg4);
	
	// Misc setup
	isLooping = true;
	currState = ASTATE_GLOBAL;
//	kString msg5 = "Misc intialized";
//	debug(msg5);
	
	// Initialize lights (list is empty; ambient only)
	globalAmbient = new KirkMath::Quat(1.0f, 1.0f, 1.0f, 1.0f);

	// Start your sound!
	hSoundboard = new ArtemisBase::Soundboard();
}

// Destroy application components, and call SDL_Quit
ArtemisBase::App::~App() {
	if (hGraphics != NULL) {
		delete hGraphics;
		hGraphics = NULL;
	}
	if (hStopwatch != NULL) {
		delete hStopwatch;
		hStopwatch = NULL;
	}
	if (hKeyboard != NULL) {
		delete hStopwatch;
		hKeyboard = NULL;
	}
	if (gameEvents != NULL) {
		delete gameEvents;
		gameEvents = NULL;
	}
	if (camera != NULL) {
		delete camera;
		camera = NULL;
	}
	if (origin != NULL) {
		delete origin;
		origin = NULL;
	}
	if (panels != NULL) {
		delete panels;
		panels = NULL;
	}
	if (lights != NULL) {
		delete lights;
		lights = NULL;
	}
	if (globalAmbient != NULL) {
		delete globalAmbient;
		globalAmbient = NULL;
	}

	// SDL_Quit must be called last, after EVERYTHING, else surfaces and function pointers will be freed twice
	SDL_Quit();
}

// Executing an application involves running the main loop (or managing different loops on different threads)
void ArtemisBase::App::execute() {
	// Reference main loop
	mainLoop();
}

// When an application is closed but not destroyed, these resources must be freed
void ArtemisBase::App::terminate() {
	// Cleanup
	origin->freeChildren();
	debugFile.close();
}

// Primary loop for single-thread applications
void ArtemisBase::App::mainLoop() {
	SDL_Event eve;
	while(isLooping) {
		// Update keyboard, mouse, and stopwatch
		hKeyboard->update();
		hMouse->update();
		while (SDL_PollEvent(&eve)) {
			// Update input devices with events
			hKeyboard->update(eve);
			hMouse->update(eve);

			// Handle built-in system events
			switch (eve.type) {
				case SDL_QUIT:
					isLooping = false;
					break;
				default:
					break;
			}
		}
		hStopwatch->refresh();

		// Check for system and program events
		gameEvents->checkEvents();
		
		// Update objects and panels (on separate thread?)
		update();
		
		// Render objects and panels (on separate thread?)
		render();
	}
}

// Timestamps & outputs debugging message to file and optional debugFnc function
void ArtemisBase::App::debug(ArtemisUtility::String msg) {
	// Timestamp it (if we have a stopwatch)
	if (hStopwatch != NULL) {
		ArtemisUtility::String spacer = hStopwatch->getTimestamp() + ArtemisUtility::String(" ");
		msg = spacer + msg;
	}
	
	// Output to file, if specified & open
	if (isDebugToFile && debugFile.is_open()) {
		debugFile << msg.raw() << "\n";
	}

	// Output to console, if specified & valid
	if (isDebugToConsole && hConsole != NULL) {
		hConsole->addLine(msg);
	}
}

void ArtemisBase::App::fail(ArtemisUtility::String msg) {
	// Debugs, aborts, exits
	debug(msg);
	isLooping = false;
	exit(EXIT_FAILURE);
}

// Updates dynamics of objects and panels based on time passed
void ArtemisBase::App::update() {
	// Get time differential
	hStopwatch->refresh();
	float dt = hStopwatch->getDt();

	// Update objects
	origin->update(dt, true);
	
	// Update panels
	if (panels != NULL) {
		int numPanels = panels->listLength();
		for (int i = 0; i < numPanels; i++) {
			panels->get(i)->update(dt);
		}
	}

	// Update console
	if (hConsole != NULL) {
		hConsole->update(dt);
	}
}

// Draw the scene, including lights, background, screen buffering and swapping
void ArtemisBase::App::render() {
	// Set up render properties
	hGraphics->clearScreen();

	// Refresh light positions
	hGraphics->go3d(camera);
	float ambient[] = { globalAmbient->getVecI(), globalAmbient->getVecJ(), globalAmbient->getVecK(), 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	for (int i = 0; i < lights->listLength(); i++) {
		ArtemisBase::Light* l = lights->get(i);
		if (l->getStatus()) {
			l->refreshPosition();
	 	}
	}
	
	// Render background and all objects
	if (camera->skybox != NULL) {
		camera->renderSkybox();
	}
	origin->render(true);

	// Switch to 2d projection and turn lights off for panels
	hGraphics->go2d();
	glDisable(GL_LIGHTING);

	// Render panels
	ArtemisBase::Panel* tmp = NULL;
	if (panels != NULL) {
		for (int i = 0; i < panels->listLength(); i++) {
			tmp = panels->get(i);
			if (tmp->isTranslucent) {
				glEnable(GL_BLEND);
				glDisable(GL_DEPTH_TEST);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			tmp->render(hGraphics);
			if (tmp->isTranslucent) {
				glDisable(GL_BLEND);
				glEnable(GL_DEPTH_TEST);
			}
		}
	}

	// External rendering
	if (externalRender != NULL) {
		externalRender();
	}

	// Render console
	hConsole->render(hGraphics);

	// Render mouse cursor
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	hCursor->render(hGraphics);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	// Turn lights back on
	glEnable(GL_LIGHTING);

	// Swap buffers
	hGraphics->swapBuffers();
}

void ArtemisBase::App::addPanel(ArtemisBase::Panel* p) {
	if (panels == NULL) {
		panels = p;
	} else {
		panels->set(p);
	}
}

void ArtemisBase::App::addObject(ArtemisBase::Object * o) {
	origin->addChild(o);
}

void ArtemisBase::App::addLight(ArtemisBase::Light * l) {
	if (lights == NULL) {
		lights = l;
	} else {
		lights->set(l, -1);
	}
}

void ArtemisBase::App::setGlobalAmbient(float r, float g, float b) {
	globalAmbient->set(1.0f, r, g, b);
}

void ArtemisBase::App::setOriginVisibility(bool isVisible) {
	origin->isVisible = isVisible;
}
