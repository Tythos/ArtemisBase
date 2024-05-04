/**
 * Color.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Color::Color() { 
	r = 1.0f; g = 1.0f; b = 1.0f; a = 1.0f; 
}

ArtemisBase::Color::Color(float fr, float fg, float fb, float fa) {
	r = fr; g = fg; b = fb; a = fa; 
}

void ArtemisBase::Color::set(float fr, float fg, float fb, float fa) { 
	r = fr; g = fg; b = fb; a = fa; 
}

void ArtemisBase::Color::setAll() {
	float values[] = { r, g, b, a };
	glColor4f(r, g, b, a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, values);
	glMaterialfv(GL_FRONT, GL_AMBIENT, values);
}

void ArtemisBase::Color::setColor() {
	glColor4f(r, g, b, a);
}

void ArtemisBase::Color::setDiffuseMat() {
	float values[] = { r, g, b, a };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, values);
}

void ArtemisBase::Color::setAmbientMat() {
	float values[] = { r, g, b, a };
	glMaterialfv(GL_FRONT, GL_AMBIENT, values);
}
