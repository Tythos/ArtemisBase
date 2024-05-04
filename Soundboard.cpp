/*
 * Soundboard.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Soundboard::Soundboard() {
	// Initialize SDL mixer
	audioRate = 22050;
	audioFormat = AUDIO_S16SYS;
	numChannels = 2;
	bufferSize = 4096;
	fadeLength = 1000;
	volume = 1.0f;
	repeatSongs = true;
	if (Mix_OpenAudio(audioRate, audioFormat, numChannels, bufferSize) != 0) {
		isInit = false;
	} else {
		isInit = true;
	}
}

ArtemisBase::Soundboard::~Soundboard() {
	if (isInit) Mix_CloseAudio();
}

Mix_Chunk* ArtemisBase::Soundboard::loadSound(ArtemisUtility::String filename) {
	Mix_Chunk * toReturn = Mix_LoadWAV(filename.raw());
	return toReturn;
}

void ArtemisBase::Soundboard::playSound(ArtemisUtility::String filename) {
	Mix_Chunk * snd = loadSound(filename);
	playSound(snd);
}

void ArtemisBase::Soundboard::playSound(Mix_Chunk* sound) {
	int channel = Mix_PlayChannel(-1, sound, 0);
}

Mix_Music* ArtemisBase::Soundboard::loadSong(ArtemisUtility::String filename) {
	Mix_Music* toReturn = Mix_LoadMUS(filename.raw());
	return toReturn;
}

void ArtemisBase::Soundboard::playSong(ArtemisUtility::String filename) {
	Mix_Music* mus = loadSong(filename);
	playSong(mus);
}

void ArtemisBase::Soundboard::playSong(Mix_Music* mus) {
	if (repeatSongs) {
		Mix_FadeInMusic(mus, -1, fadeLength);
	} else {
		Mix_FadeInMusic(mus, 0, fadeLength);
	}
}

void ArtemisBase::Soundboard::stopSong() {
	Mix_FadeOutMusic(fadeLength);
}

bool ArtemisBase::Soundboard::isPlaying() {
	return Mix_PlayingMusic() == 1;
}