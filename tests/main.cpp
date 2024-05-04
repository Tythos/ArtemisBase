/**
 * tests/main.cpp
 */

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "ArtemisBase.hpp"

SDL_Event eve;
ArtemisBase::App* hApp;
ArtemisBase::Cube* hCube;
ArtemisBase::Planet* earth;
ArtemisBase::Texture * skyboxTex;
ArtemisBase::Mesh * skyboxMesh;

bool quitTrig() {
	return hApp->hKeyboard->checkKey('q');
}

void quitTarg() {
	hApp->isLooping = false;
}

bool fullscreenTrig() {
	return hApp->hKeyboard->checkKey(SDLK_SPACE);
}

void fullscreenTarg() {
	hApp->hGraphics->toggleFullscreen();
}

bool rotateRightTrig() {
	return hApp->hKeyboard->checkKey(SDLK_RIGHT);
}

bool rotateLeftTrig() {
	return hApp->hKeyboard->checkKey(SDLK_LEFT);
}

bool rotateUpTrig() {
	return hApp->hKeyboard->checkKey(SDLK_UP);
}

bool rotateDownTrig() {
	return hApp->hKeyboard->checkKey(SDLK_DOWN);
}

void rotateRightTarg() {
	float dTht = -0.5f * hApp->hStopwatch->getDt();
	hApp->camera->rotateFocus(dTht, 0.0f);
}

void rotateLeftTarg() {
	float dTht = 0.5f * hApp->hStopwatch->getDt();
	hApp->camera->rotateFocus(dTht, 0.0f);
}

void rotateUpTarg() {
	float dPhi = -0.5f * hApp->hStopwatch->getDt();
	hApp->camera->rotateFocus(0.0f, dPhi);
}

void rotateDownTarg() {
	float dPhi = 0.5f * hApp->hStopwatch->getDt();
	hApp->camera->rotateFocus(0.0f, dPhi);
}

bool testDraw() {
	hApp->debug("Test drawing...");
/*	float skyboxSide = 5.0f;
	glLoadIdentity();
	skyboxTex->use();
	skyboxMesh->render();
	/*glPushMatrix(); {
		glPushAttrib(GL_ENABLE_BIT); {
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			glDisable(GL_BLEND);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			skybox->use();
			glBegin(GL_QUADS); {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(skyboxSide, -skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyboxSide, -skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-skyboxSide, skyboxSide, -skyboxSide);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(skyboxSide, skyboxSide, -skyboxSide);
			} glEnd();
			glBegin(GL_QUADS); {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(skyboxSide, -skyboxSide, skyboxSide);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(skyboxSide, -skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(skyboxSide, skyboxSide, -skyboxSide);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(skyboxSide, skyboxSide, skyboxSide);
			} glEnd();
			glBegin(GL_QUADS); {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-skyboxSide, -skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyboxSide, -skyboxSide, skyboxSide);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-skyboxSide, skyboxSide, skyboxSide);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-skyboxSide, skyboxSide, -skyboxSide);
			} glEnd();
			glBegin(GL_QUADS); {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(skyboxSide, -skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyboxSide, -skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-skyboxSide, skyboxSide, -skyboxSide);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(skyboxSide, skyboxSide, -skyboxSide);
			} glEnd();
			glBegin(GL_QUADS); {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-skyboxSide, skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyboxSide, skyboxSide, skyboxSide);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(skyboxSide, skyboxSide, skyboxSide);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(skyboxSide, skyboxSide, -skyboxSide);
			} glEnd();
			glBegin(GL_QUADS); {
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-skyboxSide, -skyboxSide, -skyboxSide);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyboxSide, -skyboxSide, skyboxSide);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(skyboxSide, -skyboxSide, skyboxSide);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(skyboxSide, -skyboxSide, -skyboxSide);
			} glEnd();
		} glPopAttrib();
	} glPopMatrix();*/

	return true;
}

int main(int argc, char * argv[]) {
	// Set up app
	hApp = new ArtemisBase::App();
	hApp->hGraphics->setScreen(600, 900, 32);
	//hApp->debugging = true;
	hApp->externalRender = testDraw;
	hApp->hGraphics->hTypewriter->setFont("arial.ttf");

	// before textures are loaded, for newer sdl2_image implementations, we need to img_init with png
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 1;
	}

	// Set up cameraa
	hApp->camera->setRight(5.0f, 0.0f, -1.0f);
	hApp->camera->setNearClip(0.1f);
	hApp->camera->setFarClip(20.0f);
	hApp->camera->setSkyboxTexture("playabox.png");
	hApp->camera->setSkyboxResolution(1024);
	hApp->debug("Finished setting up camera");

	// Set up events
	hApp->gameEvents->createElement(ArtemisBase::AppState::ASTATE_GLOBAL, (*quitTrig), (*quitTarg));
	hApp->gameEvents->createElement(ArtemisBase::AppState::ASTATE_GLOBAL, (*fullscreenTrig), (*fullscreenTarg));
	hApp->gameEvents->createElement(ArtemisBase::AppState::ASTATE_GLOBAL, (*rotateRightTrig), (*rotateRightTarg));
	hApp->gameEvents->createElement(ArtemisBase::AppState::ASTATE_GLOBAL, (*rotateLeftTrig), (*rotateLeftTarg));
	hApp->gameEvents->createElement(ArtemisBase::AppState::ASTATE_GLOBAL, (*rotateUpTrig), (*rotateUpTarg));
	hApp->gameEvents->createElement(ArtemisBase::AppState::ASTATE_GLOBAL, (*rotateDownTrig), (*rotateDownTarg));

	// Test light
	ArtemisBase::Light* testLight = new ArtemisBase::Light();
	testLight->setAmbient(0.9f, 0.1f, 0.1f);
	testLight->setDiffuse(0.1f, 0.1f, 0.9f);
	testLight->setPosition(2.0f, 2.0f, 2.0f);
	testLight->setAttenuation(0.1f);
	testLight->setVisible(true);
	testLight->enable();
	hApp->addLight(testLight);
	hApp->setGlobalAmbient(0.5f, 0.5f, 0.5f);

	// Test cube
	hCube = new ArtemisBase::Cube();
	hCube->setSize(0.5f);
	hCube->setAngularVelocity(0.8f, 0.4f, 0.2f, 0.1f);
	hCube->setAmbient(0.5f, 0.5f, 0.5f);
	hCube->setDiffuse(0.7f, 0.7f, 0.7f);
	hApp->addObject(hCube);
	hApp->debug("First cube initialized");
	
	// Test planet
	earth = new ArtemisBase::Planet(1.0f, 2048);
	earth->setPosition(1.0f, 1.0f, -1.0f);
	earth->setRotation(0.1f, 0.1f, 0.9f, 0.0f);
	earth->setAngularVelocity(0.9f, 0.0f, 1.0f, 0.0f);
	earth->setAmbient(0.7f, 0.7f, 0.7f);
	earth->setDiffuse(0.9f, 0.9f, 0.9f);
	hApp->addObject(earth);
	hApp->debug("Earth initialized");

	// Load skybox
	skyboxTex = new ArtemisBase::Texture();
	skyboxTex->loadFromFile("background.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	skyboxMesh = new ArtemisBase::Mesh();
	skyboxMesh->loadSphere(1.5f, 32);
	//skyboxMesh->setColor(0.1f, 0.2f, 0.4f, 1.0f);

	// Run base
	hApp->debug("The app is being executed...");
	hApp->execute();
	hApp->debug("The app has being executed.");

	// Clean up and quit
	hApp->debug("Finished; shutting down...");
	hApp->terminate();
	return 0;
}