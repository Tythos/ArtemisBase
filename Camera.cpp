/**
 * Camera.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Camera::Camera() {
	// Set up frame
	position = new KirkMath::Quat(0.0f, 0.0f, 0.0f, 1.0f);
	target = new KirkMath::Quat(0.0f, 0.0f, 0.0f, 0.0f);
	up = new KirkMath::Quat(0.0f, 0.0f, 1.0f, 0.0f);
	
	// Set up perspective
	int width = 900; int height = 600;
	fieldAngle = 45.0f;
	aspectRatio = (float)width / (float)height;
	nearClip = 0.1f;
	farClip = 1000.0f;

	// Set background skybox
	skybox = NULL;

	// Singularity tolerance specifies how close to vertical we can rotate to avoid gimbal lock
	singularityTolerance = 0.01f;
}

ArtemisBase::Camera::~Camera() {
	delete position;
	delete target;
	delete up;
	if (skybox != NULL) {
		delete skybox;
		skybox = NULL;
	}
}

void ArtemisBase::Camera::setFarClip(float v) {
	farClip = v;
	if (skybox == NULL) {
		skybox = new ArtemisBase::Skybox();
	}
	skybox->setRadius(0.5f * farClip);
}

void ArtemisBase::Camera::setPosition(float x, float y, float z) {
	position->set(0.0f, x, y, z);
}

void ArtemisBase::Camera::setTarget(float x, float y, float z) {
	target->set(0.0f, x, y, z);
}

void ArtemisBase::Camera::setUp(float x, float y, float z) {
	up->set(0.0f, x, y, z);
}

void ArtemisBase::Camera::setRight(float x, float y, float z) {
	// Calculates up vector from right vector orientation, assuming position and target are constant
	float atX = target->getVecI() - position->getVecI();
	float atY = target->getVecJ() - position->getVecJ();
	float atZ = target->getVecK() - position->getVecK();
	float upX = y * atZ - z * atY;
	float upY = z * atX - x * atZ;
	float upZ = x * atY - y * atX;
	float mag = sqrt(upX*upX + upY*upY + upZ*upZ);
	up->set(0.0f, upX / mag, upY / mag, upZ / mag);
}

void ArtemisBase::Camera::applyCamera() {
	// Applies camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double glpi = 3.1415926535897932384626433832795;
	double w, h;
	h = tan((fieldAngle / 2) / 180 * glpi) * nearClip;
	w = h * aspectRatio;
	glFrustum(-w, w, -h, h, nearClip, farClip);
	//gluPerspective(fieldAngle, aspectRatio, nearClip, farClip);
	gluLookAt(position->getVecI(), position->getVecJ(), position->getVecK(), target->getVecI(), target->getVecJ(), target->getVecK(), up->getVecI(), up->getVecJ(), up->getVecK());
	glMatrixMode(GL_MODELVIEW);
}

void ArtemisBase::Camera::print() {
	/*debugFile << "Position: {" <<  position->getVecI() << ", " << position->getVecJ() << ", " << position->getVecK() << "\n";
	debugFile << "Target: {" <<  target->getVecI() << ", " << target->getVecJ() << ", " << target->getVecK() << "\n";
	debugFile << "Up: {" <<  up->getVecI() << ", " << up->getVecJ() << ", " << up->getVecK() << "\n";*/
}

void ArtemisBase::Camera::setSkyboxTexture(KirkMath::String filename) {
	if (skybox == NULL) {
		skybox = new ArtemisBase::Skybox();
		skybox->setRadius(farClip);
	}
	skybox->setTexture(filename);
}

void ArtemisBase::Camera::setSkyboxTexture(SDL_Surface * surf) {
	if (skybox == NULL) {
		skybox = new ArtemisBase::Skybox();
		skybox->setRadius(farClip);
	}
	skybox->setTexture(surf);
}

void ArtemisBase::Camera::setSkyboxResolution(int n) {
	if (skybox == NULL) {
		skybox = new ArtemisBase::Skybox();
		skybox->setRadius(farClip);
	}
	skybox->setResolution(n);
}

void ArtemisBase::Camera::renderSkybox() {
	// Renders skybox; resets modelview matrix to camera location with world coordinate orientation
	if (skybox != NULL) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix(); {
			glTranslatef(position->getVecI(), position->getVecJ(), position->getVecK());
			skybox->render();
		} glPopMatrix();
	}
}

void ArtemisBase::Camera::rotateFocus(float dTht, float dPhi) {
	// Rotates camera about focus point by given increments in spherical coordinates
	float relX = position->getVecI() - target->getVecI();
	float relY = position->getVecJ() - target->getVecJ();
	float relZ = position->getVecK() - target->getVecK();
	float mag = sqrt(relX*relX + relY*relY + relZ*relZ);

	// Calculate and increment spherical coordinates
	float tht = atan(relZ / relX);
	if (relX < 0.0f) {
		if (relZ < 0.0f) {
			tht += float(M_PI);
		} else {
			tht -= float(M_PI);
		}
	}
	tht += dTht;
	float phi = acos(relY / mag) + dPhi;

	// Safecheck bounds - theta is periodic, phi is singular
	float twoPi = 2.0f * float(M_PI);
	while (tht < 0.0) {
		tht += twoPi;
	}
	while (tht > twoPi) {
		tht -= twoPi;
	}
	if (phi < singularityTolerance) phi = singularityTolerance;
	if (phi > float(M_PI) - singularityTolerance) phi = float(M_PI) - singularityTolerance;

	// Translate back into cartesian and set new position
	relX = mag * cos(tht) * sin(phi);
	relY = mag * cos(phi);
	relZ = mag * sin(tht) * sin(phi);
	position->set(0.0f, target->getVecI() + relX, target->getVecJ() + relY, target->getVecK() + relZ);

	// Recalculate up vector from right
	float rightX = relZ;
	float rightY = 0.0f;
	float rightZ = -1.0f * relX;
	float upX = relY * rightZ - relZ * rightY;
	float upY = relZ * rightX - relX * rightZ;
	float upZ = relX * rightY - relY * rightX;
	mag = sqrt(upX*upX + upY*upY + upZ*upZ);
	up->set(0.0f, upX / mag, upY / mag, upZ / mag);
}

void ArtemisBase::Camera::rotateCenter(float dTht, float dPhi) {
	// Rotates camera about the current position by given increments in spherical coordinates
}

void ArtemisBase::Camera::pan(float dx, float dy, float dz) {
	// Pans camera in world coordinate system by given increments
	KirkMath::Quat* increment = new KirkMath::Quat(0.0f, dx, dy, dz);
	(*target) = (*target) + (*increment);
	(*position) = (*position) + (*increment);
}

void ArtemisBase::Camera::focus(float x, float y, float z) {
	// Keeping position and orientation relative to target, moves to focus on new target
	KirkMath::Quat* dif = new KirkMath::Quat(position->getVecI() - target->getVecI(), position->getVecJ() - target->getVecJ(), position->getVecK() - target->getVecK());
	target->set(0.0f, x, y, z);
	(*position) = (*dif) + (*target);
}

void ArtemisBase::Camera::zoomFocus(float dz) {
	// Given focus point, zooms in by factor dz (r in spherical coordinates)
	float relX = position->getVecI() - target->getVecI();
	float relY = position->getVecJ() - target->getVecJ();
	float relZ = position->getVecK() - target->getVecK();

	// Zoom by factor dz (dz < 1 zooms in, dz > 1 zooms out)
	relX *= dz;
	relY *= dz;
	relZ *= dz;

	// Set position with new relative x, y, z
	position->set(0.0f, target->getVecI() + relX, target->getVecJ() + relY, target->getVecK() + relZ);
}
