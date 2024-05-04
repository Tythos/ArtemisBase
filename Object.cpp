/*
 * Object.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Object::Object(ArtemisBase::Object * p) {
	frame = new KirkMath::Trans();
	linearVelocity = new KirkMath::Quat(1.0f, 0.0f, 0.0f, 0.0f);
	angularVelocity = new KirkMath::Quat(0.0f, 1.0f, 0.0f, 0.0f);
	parent = p;
	children = NULL;
	next = NULL;
	ambientMaterial = new ArtemisBase::Color(0.7f, 0.7f, 0.7f, 1.0f);
	diffuseMaterial = new ArtemisBase::Color(0.9f, 0.9f, 0.7f, 1.0f);
	tex = NULL;
	mesh = NULL;
	isVisible = true;
}

ArtemisBase::Object::Object(float x, float y, float z, ArtemisBase::Object* p) {
	frame = new KirkMath::Trans(); frame->setPos(x, y, z);
	linearVelocity = new KirkMath::Quat(1.0f, 0.0f, 0.0f, 0.0f);
	angularVelocity = new KirkMath::Quat(0.0f, 1.0f, 0.0f, 0.0f);
	parent = p;
	children = NULL;
	next = NULL;
	ambientMaterial = new ArtemisBase::Color(0.7f, 0.7f, 0.7f, 1.0f);
	diffuseMaterial = new ArtemisBase::Color(0.9f, 0.9f, 0.7f, 1.0f);
	mesh = NULL;
	tex = NULL;
	isVisible = true;
}

ArtemisBase::Object::Object(KirkMath::Quat orientation, ArtemisBase::Object* p) {
	// Note: orientation is a valued rotation quaternion
	frame = new KirkMath::Trans();
	frame->setRot(orientation.getScl(), orientation.getVecI(), orientation.getVecJ(), orientation.getVecK());
	linearVelocity = new KirkMath::Quat(1.0f, 0.0f, 0.0f, 0.0f);
	angularVelocity = new KirkMath::Quat(0.0f, 1.0f, 0.0f, 0.0f);
	parent = p;
	children = NULL;
	next = NULL;
	ambientMaterial = new ArtemisBase::Color(0.7f, 0.7f, 0.7f, 1.0f);
	diffuseMaterial = new ArtemisBase::Color(0.9f, 0.9f, 0.7f, 1.0f);
	mesh = NULL;
	tex = NULL;
	isVisible = true;
}

ArtemisBase::Object::Object(float x, float y, float z, KirkMath::Quat orientation, ArtemisBase::Object* p) {
	// Note: orietnation is a valued rotation quaternion
	frame = new KirkMath::Trans();
	frame->setPos(x, y, z);
	frame->setRot(orientation.getScl(), orientation.getVecI(), orientation.getVecJ(), orientation.getVecK());
	linearVelocity = new KirkMath::Quat(1.0f, 0.0f, 0.0f, 0.0f);
	angularVelocity = new KirkMath::Quat(0.0f, 1.0f, 0.0f, 0.0f);
	parent = p;
	children = NULL;
	next = NULL;
	ambientMaterial = new ArtemisBase::Color(0.7f, 0.7f, 0.7f, 1.0f);
	diffuseMaterial = new ArtemisBase::Color(0.9f, 0.9f, 0.7f, 1.0f);
	mesh = NULL;
	tex = NULL;
	isVisible = true;
}

ArtemisBase::Object::~Object() {
	delete frame;
	delete linearVelocity;
	delete angularVelocity;
	delete ambientMaterial;
	delete diffuseMaterial;
	if (mesh != NULL) { delete mesh; }
	if (tex != NULL) { delete tex; }
}

void ArtemisBase::Object::freeChildren() {
	// Before an aObject is destroyed, it may need to free its children
	int childCount = children->listLength();
	ArtemisBase::Object* tmp = NULL;
	for (int i = childCount; i > 0; i--) {
		tmp = children->get(i-1);
		tmp->freeChildren();
		delete tmp;
	}
	children = NULL;
}

KirkMath::Trans ArtemisBase::Object::getFrame() {
	KirkMath::Trans toReturn = (*frame);
	return toReturn;
}

KirkMath::Quat ArtemisBase::Object::getLocation() {
	KirkMath::Quat toReturn = frame->getPos();
	return toReturn;
}

KirkMath::Quat ArtemisBase::Object::getRotation() {
	KirkMath::Quat toReturn = frame->getRot();
	return toReturn;
}

KirkMath::Quat ArtemisBase::Object::getScaling() {
	KirkMath::Quat toReturn = frame->getScl();
	return toReturn;
}

void ArtemisBase::Object::setAmbient(float r, float g, float b) {
	ambientMaterial->set(r, g, b, 1.0f);
}

void ArtemisBase::Object::setDiffuse(float r, float g, float b) {
	diffuseMaterial->set(r, g, b, 1.0f);
}

void ArtemisBase::Object::setTexture(ArtemisUtility::String filename) {
	if (tex->isLoaded()) { tex->unload(); }
	tex->loadFromFile(filename);
}

void ArtemisBase::Object::setTexture(SDL_Surface* surf) {
	if (tex->isLoaded()) { tex->unload(); }
	tex->loadFromSurface(surf);
}

void ArtemisBase::Object::setScaling(float x, float y, float z) {
	frame->setScl(x, y, z);
}

KirkMath::Quat ArtemisBase::Object::getLinearVelocity() {
	KirkMath::Quat toReturn = (*linearVelocity);
	return toReturn;
}

KirkMath::Quat ArtemisBase::Object::getAngularVelocity() {
	KirkMath::Quat toReturn = (*angularVelocity);
	return toReturn;
}

void ArtemisBase::Object::update(float dt, bool updateChildren) {
	// Update object position based on current velocity and given timestep
	// Follow up by updating child positions, unless indicated otherwise
	frame->update(linearVelocity, angularVelocity, dt);
	if (updateChildren && children != NULL) {
		for (int i = 0; i < children->listLength(); i++) {
			children->get(i)->update(dt, updateChildren);
		}
	}
}

void ArtemisBase::Object::render(bool renderChildren) {
	// For base object, draw orthonormal coordinates
	frame->glApply(); {
		if (isVisible) {
			if (mesh == NULL) {
				float red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
				float green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
				float blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
				float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
				glBegin(GL_LINES); {
					glMaterialfv(GL_FRONT, GL_AMBIENT, red);
					glColor3f(1.0f, 0.0f, 0.0f);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(1.0f, 0.0f, 0.0f);
					glMaterialfv(GL_FRONT, GL_AMBIENT, green);
					glColor3f(0.0f, 1.0f, 0.0f);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(0.0f, 1.0f, 0.0f);
					glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
					glColor3f(0.0f, 0.0f, 1.0f);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(0.0f, 0.0f, 1.0f);
				} glEnd();
			} else {
				// Set material, texture
				diffuseMaterial->setDiffuseMat();
				ambientMaterial->setAmbientMat();
				if (tex != NULL) { tex->bind(); }
				mesh->render();
				if (tex != NULL) { tex->unbind(); }
			}
		}
		
		// Render children as well?
		if (renderChildren && children != NULL) {
			for (int i = 0; i < children->listLength(); i++) {
				children->get(i)->render(renderChildren);
			}
		}
	} frame->glUnapply();
}

void ArtemisBase::Object::setPosition(float x, float y, float z) {
	frame->setPos(x, y, z);
}

void ArtemisBase::Object::setRotation(float w, float x, float y, float z) {
	frame->setRot(w, x, y, z);
}

void ArtemisBase::Object::setLinearVelocity(float x, float y, float z) {
	linearVelocity->set(0.0f, x, y, z);
}

void ArtemisBase::Object::setAngularVelocity(float w, float x, float y, float z) {
	angularVelocity->set(w, x, y, z);
}

void ArtemisBase::Object::addChild(ArtemisBase::Object* newChild) {
	if (children == NULL) {
		children = newChild;
	} else {
		children->set(newChild, -1);
	}
}

ArtemisBase::Object* ArtemisBase::Object::get(int n) {
	if (n <= 0 || next == NULL) {
		return this;
	} else {
		return next->get(n-1);
	}
}

void ArtemisBase::Object::set(ArtemisBase::Object* value, int n) {
	if (n == 0 || next == NULL) {
		next = value;
	} else if (n < 0 && next == NULL) {
		next = value;
	} else {
		next->set(value, n-1);
	}		
}

int ArtemisBase::Object::listLength() {
	if (this == NULL) {
		return 0;
	} else if (next == NULL) {
		return 1;
	} else {
		return next->listLength() + 1;
	}
}
