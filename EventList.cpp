/**
 * EventList.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::EventList::EventList() {
	this->thisEvent = NULL;
	this->nextNode = NULL;
}

ArtemisBase::EventList::~EventList() {
	if (this->nextNode != NULL)
		delete this->nextNode;
	if (this->thisEvent != NULL)
		delete this->thisEvent;
}

int ArtemisBase::EventList::listLength() {
	// Returns the length of this list.
	ArtemisBase::EventList* currentNode = this;
	int lengthCounter = 0;
	while(currentNode->thisEvent != NULL && currentNode->nextNode != NULL) {
		lengthCounter++;
		currentNode = currentNode->nextNode;
	}
	return lengthCounter;
}

ArtemisBase::Event* ArtemisBase::EventList::getElement(int n) {
	// Returns the pointer to the nth object (NOT the list node).
	int maxLength = this->listLength();
	ArtemisBase::EventList* currentNode = this;
	if (n >= maxLength) {
		n = maxLength - 1;
	}
	
	for (int i = 0; i < n; i++) {
		currentNode = currentNode->nextNode;
	}
	return currentNode->thisEvent;
}

ArtemisBase::Event* ArtemisBase::EventList::createElement() {
	// Creates a new object of the base type (aObject); returns it's location
	ArtemisBase::EventList* currentNode = this;
	while(currentNode->nextNode != NULL && currentNode->thisEvent != NULL) {
		currentNode = currentNode->nextNode;
	}
	currentNode->nextNode = new ArtemisBase::EventList();
	currentNode->thisEvent = new ArtemisBase::Event();
	return currentNode->thisEvent;
}

int ArtemisBase::EventList::createElement(ArtemisBase::Event* newEvent) {
	// Creates a new element in the array whose event is in the passed location
	// The index of the new element is returned.
	if (this->thisEvent == NULL) {
		this->thisEvent = newEvent;
		return 0;
	}
	int maxLength = this->listLength();
	ArtemisBase::EventList* currentNode = this;
	while(currentNode->nextNode != NULL && this->thisEvent != NULL) {
		currentNode = currentNode->nextNode;
	}
	currentNode->nextNode = new ArtemisBase::EventList();
	currentNode = currentNode->nextNode;
	currentNode->nextNode = NULL;
	currentNode->thisEvent = newEvent;
	return maxLength;
}

void ArtemisBase::EventList::createElement(ArtemisBase::AppState myState, bool (*myTrigger)(void), void (*myTarget)(void)) {
	static int nodesCreated = 0;
	ArtemisBase::EventList* currentNode = this;
	while(currentNode->nextNode != NULL && currentNode->thisEvent != NULL) {
		currentNode = currentNode->nextNode;
	}
	nodesCreated++;
	currentNode->nextNode = new ArtemisBase::EventList();
	currentNode->thisEvent = new ArtemisBase::Event();
	currentNode->thisEvent->eventState = myState;
	currentNode->thisEvent->trigger = myTrigger;
	currentNode->thisEvent->target = myTarget;
}

void ArtemisBase::EventList::checkEvents() {
	// Check all events for the current state
	ArtemisBase::Event* eventPointer;
	for (int i = 0; i < this->listLength(); i++) {
		eventPointer = this->getElement(i);
		if (eventPointer->trigger()) {
			eventPointer->target();
		}
	}
}

void ArtemisBase::EventList::map() {
	ArtemisBase::EventList* currentNode = this;
	char * te = (char*)"";
	char * nn = (char*)"";
	for (int i = 0; i < 10; i++) {
		if (currentNode->thisEvent == NULL)
			te = (char*)"NULL";
		else
			te = (char*)"EVENT";
		if (currentNode->nextNode == NULL)
			nn = (char*)"NULL";
		else
			nn = (char*)"NODE";
		printf("NODE %i: thisEvent, %s; nextNode, %s\n", i, te, nn);
		if (currentNode->thisEvent == NULL && currentNode->nextNode == NULL)
			break;
		else
			currentNode = currentNode->nextNode;
	}
}
