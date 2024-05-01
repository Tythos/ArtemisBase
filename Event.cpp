/**
 * aEvent.cpp
 */

#include "ArtemisBase.hpp"

bool blankTrigger() {
	return false;
}

void blankTarget() {
	return;
}

// --- aEvent class --- //
ArtemisBase::Event::Event() {
	this->trigger = (*blankTrigger);
	this->target = (*blankTarget);
}

ArtemisBase::Event::~Event() {
}
