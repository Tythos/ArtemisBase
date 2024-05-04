/**
 * Vertex.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Vertex::Vertex() {
	x = 0.0f; y = 0.0f; z = 0.0f;
}

ArtemisBase::Vertex::Vertex(float px, float py, float pz) {
	x = px; y = py, z = pz; 
}

void ArtemisBase::Vertex::set(float px, float py, float pz) { 
	x = px; y = py; z = pz; 
}

float ArtemisBase::Vertex::mag() { 
	return sqrt(x*x + y*y + z*z); 
}

ArtemisBase::Vertex ArtemisBase::Vertex::operator- (ArtemisBase::Vertex operand) {
	ArtemisBase::Vertex toReturn;
	toReturn.set(x - operand.x, y - operand.y, z - operand.z);
	return toReturn;
}

bool ArtemisBase::Vertex::operator== (ArtemisBase::Vertex operand) {
	return (x == operand.x && y == operand.y && z == operand.z);
}

ArtemisBase::Vertex ArtemisBase::Vertex::cross(ArtemisBase::Vertex operand) {
	ArtemisBase::Vertex toReturn;
	toReturn.set(y * operand.z - z * operand.y, z * operand.x - x * operand.z, x * operand.y - y * operand.x);
	return toReturn;
}

ArtemisBase::Vertex ArtemisBase::Vertex::norm() {
	ArtemisBase::Vertex toReturn;
	float mag = this->mag();
	toReturn.set(x / mag, y / mag, z / mag);
	return toReturn;
}

void ArtemisBase::Vertex::print() {
	printf("{%f, %f, %f}\n", x, y, z);
}
