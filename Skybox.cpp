/**
 * Skybox.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Skybox::Skybox()
: ArtemisBase::Object() {
	tex = new ArtemisBase::Texture();
	tex->loadFromFile("earth.PNG");
	radius = 1.0f;
	resolution = 32;
	mesh = new ArtemisBase::Mesh();
	mesh->loadSphere(radius, resolution);
	ambientMaterial->set(1.0f, 1.0f, 1.0f, 1.0f);
	diffuseMaterial->set(0.0f, 0.0f, 0.0f, 1.0f);
}

ArtemisBase::Skybox::Skybox(float r, int n) {
	tex = new ArtemisBase::Texture();
	tex->loadFromFile("earth.PNG");
	radius = r;
	resolution = n;
	mesh = new ArtemisBase::Mesh();
	mesh->loadSphere(radius, resolution);
	ambientMaterial->set(1.0f, 1.0f, 1.0f, 1.0f);
	diffuseMaterial->set(0.0f, 0.0f, 0.0f, 1.0f);
}

void ArtemisBase::Skybox::setRadius(float r) {
	radius = r;
	mesh->loadSphere(radius, resolution);
}

void ArtemisBase::Skybox::setResolution(int n) {
	resolution = n;
	mesh->loadSphere(radius, resolution);
}