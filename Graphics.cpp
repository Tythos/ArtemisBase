/**
 * Graphics.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Graphics::Graphics() {
	// Set up initial graphics dimensions
	windowOk = false;
	window = NULL;
	hTypewriter = new Typewriter();
}

ArtemisBase::Graphics::~Graphics() {
	if (window != NULL) {
		/*bool t = false;
		SDL_FreeSurface(screen);
		screen = NULL;
		t = false;*/
	}
}

bool ArtemisBase::Graphics::setScreen(int newHeight, int newWidth, int newBpp) {
	// start with window NOT okay; will only be true if we succeed
	windowOk = false;

	// Assign new screen attributes if valid
	width = newWidth;
	height = newHeight;
	bpp = newBpp;
	
	int colorBits = int(float(bpp) / 4.0f);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, colorBits);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, colorBits);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, colorBits);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bpp - 3 * colorBits);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// create and verify window handle
	window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, newHeight, newWidth, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		return false;
	}

	// create and verify context
	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		return false;
	}

	// initialize glew
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		return false;
	}

	// assert vsync
	if (SDL_GL_SetSwapInterval(1) < 0) {
		return false;
	}

	// initialize OpenGL settings
	if (!declareSettings()) {
		return false;
	}

	windowOk = true;
	return windowOk;
}

bool ArtemisBase::Graphics::declareSettings() {
	// Gl settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL);
	return true;
}

void ArtemisBase::Graphics::printAttributes() {
	int value;

	// print red size
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
	printf("Red size: %d bits\n", value);

	// print blue size
	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
	printf("Blue size: %d bits\n", value);

	// print green size
	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
	printf("Green size: %d bits\n", value);

	// print alpha size
	SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &value);
	printf("Alphasize: %d bits\n", value);

	// print color buffer size
	SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &value);
	printf("Color buffer size: %d bits\n", value);

	// print depth buffer size
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
	printf("Depth buffer size: %d bits\n", value);
}

void ArtemisBase::Graphics::resize(int w, int h) {
	// Release and refresh properties
	/*if (screen == NULL) { SDL_FreeSurface(screen); }
	screen = SDL_SetVideoMode(w, h, bpp, SDL_OPENGL | SDL_SWSURFACE | SDL_RESIZABLE);
	if (screen == NULL) {
		windowOk = false;
		return;
	}
	height = h;
	width = w;
	declareSettings();*/
}

bool ArtemisBase::Graphics::toggleFullscreen() {
	/*if (isWindowed) {
		// Reset screen surface
		screen = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL | SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN);
		if (screen == NULL) {
			windowOk = false;
		} else {
			windowOk = true;
			isWindowed = false;
			declareSettings();
		}
	} else {
		// Reset screen surface
		screen = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL | SDL_SWSURFACE | SDL_RESIZABLE);
		if (screen == NULL) {
			windowOk = false;
		} else {
			windowOk = true;
			isWindowed = true;
			declareSettings();
		}
	}*/
	return true;
}

void ArtemisBase::Graphics::go2d() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
}

void ArtemisBase::Graphics::go3d() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 12.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ArtemisBase::Graphics::go3d(ArtemisBase::Camera * cam) {
	KirkMath::Quat* pos = cam->getPosition();
	KirkMath::Quat* trg = cam->getTarget();
	KirkMath::Quat* upq = cam->getUp();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cam->getFieldAngle(), cam->getAspectRatio(), cam->getNearClip(), cam->getFarClip());
	gluLookAt(pos->getVecI(), pos->getVecJ(), pos->getVecK(), trg->getVecI(), trg->getVecJ(), trg->getVecK(), upq->getVecI(), upq->getVecJ(), upq->getVecK());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ArtemisBase::Graphics::swapBuffers() {
	// Show current buffer on screen
	SDL_GL_SwapWindow(window);
}

void ArtemisBase::Graphics::clearScreen() {
	// Fills screen surface with background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, bgColor.r, bgColor.g, bgColor.b));
}

void ArtemisBase::Graphics::testLoop() {
	// Executes a test drawing loop that renders various colors and primitives
	glClear(GL_COLOR_BUFFER_BIT);
	static float x = 0.0f, y = 0.0f;
	static float angle = 0.0f;
	angle += 0.01f;
	if (angle >= 360.0f)
		angle = 0.0f;
	glLoadIdentity();
	glTranslatef(-x, -y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glEnable(GL_POINT_SMOOTH);
	
	glBegin(GL_TRIANGLES); {
		glColor3f(0.1f, 0.3f, 0.5f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glColor3f(0.3f, 0.5f, 0.1f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.5f, 0.1f, 0.3f);
		glVertex3f(0.0f, 0.0f, 1.0f);
	} glEnd();
	
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0f);
	glBegin(GL_LINES); {
		glColor3f(0.2f, 0.4f, 0.2f);
		glVertex3f(-1.0f, -0.5f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 0.3f, 0.0f);
	} glEnd();
	
	glFlush();
}

void ArtemisBase::Graphics::drawCube(float xPos, float yPos, float zPos) {
	glPushMatrix(); {
		glTranslatef(xPos, yPos, zPos);
		glBegin(GL_QUADS); { // Top
			glNormal3f(0.0f, 1.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
			glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
			glColor3f(0.0f, 1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
		} glEnd();
		glBegin(GL_QUADS); { // Front
			glNormal3f(0.0f, 0.0f, 1.0f);
			glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
			glColor3f(0.0f, 1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
			glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
		} glEnd();
		glBegin(GL_QUADS); { // Right
			glNormal3f(1.0f, 0.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
			glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
			glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
		} glEnd();
		glBegin(GL_QUADS); { // Left
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
			glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		} glEnd();
		glBegin(GL_QUADS); { // Bottom
			glNormal3f(0.0f, -1.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
			glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
		} glEnd();
		glBegin(GL_QUADS); { // Back
			glNormal3f(0.0f, 0.0f, -1.0f);
			glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
			glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		} glEnd();
	} glPopMatrix();
}

void ArtemisBase::Graphics::drawTexturedCube(float xPos, float yPos, float zPos) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix(); {
		glTranslatef(xPos, yPos, zPos);
		
		glBegin(GL_QUADS); { // Top face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		} glEnd();
		
		glBegin(GL_QUADS); { // Front face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
		} glEnd();
		
		glBegin(GL_QUADS); { // Right face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
		} glEnd();
		
		glBegin(GL_QUADS); { // Left face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
		} glEnd();
		
		glBegin(GL_QUADS); { // Bottom face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
		} glEnd();
		
		glBegin(GL_QUADS); { // Back face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
		} glEnd();
	} glPopMatrix();	
}
