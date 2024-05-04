/**
 * Stopwatch.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Stopwatch::Stopwatch() {
	this->refresh();
	currTicks = 0;
	frame = 0;
	dt = 1.0f;
}

void ArtemisBase::Stopwatch::refresh() {
	// Only call ONCE PER CYCLE
	this->lastTime = this->currTime;
	lastTicks = currTicks;
	do {
		time(&currTime);
		localtime_s(&currTimeInfo, &currTime);
		currTicks = SDL_GetTicks();
		dt = (currTicks - lastTicks) / 1000.0f;
	} while (dt == 0.0f);
	frame++;
}

float ArtemisBase::Stopwatch::getFramerate() {
//	printf("frame: %li, framerate: %f fps\n", frame, 1.0f / dt);
	return 1.0f / dt;
}

ArtemisUtility::String ArtemisBase::Stopwatch::getDayText() {
	return "Monday";
}

ArtemisUtility::String ArtemisBase::Stopwatch::getMonthText() {
	return "February";
}

int ArtemisBase::Stopwatch::getDayOfWeek() {
	return this->currTimeInfo.tm_wday;
}

int ArtemisBase::Stopwatch::getDayOfMonth() {
	return this->currTimeInfo.tm_mday;
}

int ArtemisBase::Stopwatch::getDayOfYear() {
	return this->currTimeInfo.tm_yday;
}

int ArtemisBase::Stopwatch::getHour() {
	return this->currTimeInfo.tm_hour;
}

int ArtemisBase::Stopwatch::getMinute() {
	return this->currTimeInfo.tm_min;
}

int ArtemisBase::Stopwatch::getSecond() {
	return this->currTimeInfo.tm_sec;
}

int ArtemisBase::Stopwatch::getYear() {
	return this->currTimeInfo.tm_year;
}

ArtemisUtility::String ArtemisBase::Stopwatch::getFullTime() {
	ArtemisUtility::String toReturn("[fu:ll:tm]");
	return toReturn;
}

ArtemisUtility::String ArtemisBase::Stopwatch::getTimestamp() {
	ArtemisUtility::String toReturn = ArtemisUtility::String("[") + ArtemisUtility::String(currTimeInfo.tm_hour);
	toReturn = toReturn + ArtemisUtility::String(":");
	toReturn = toReturn + ArtemisUtility::String(currTimeInfo.tm_min);
	toReturn = toReturn + ArtemisUtility::String(":");
	toReturn = toReturn + ArtemisUtility::String(currTimeInfo.tm_sec);
	toReturn = toReturn + ArtemisUtility::String("]");
	return toReturn;
}