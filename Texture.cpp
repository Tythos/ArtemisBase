/**
 * Texture.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Texture::Texture() {
	_textureId = 0;
	_texture = NULL;
	_isLoaded = false;
	glEnable(GL_TEXTURE_2D);
}

ArtemisBase::Texture::~Texture() {
	if (_texture != NULL) { SDL_FreeSurface(_texture); }
}

bool ArtemisBase::Texture::loadFromFile(ArtemisUtility::String filename) {
	// Loads texture image from file
	SDL_Surface* surface = IMG_Load(filename.raw());
	if (surface == NULL) {
		_isLoaded = false;
		return false;
	}

	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (surface->format->BytesPerPixel % 4 == 0) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	} else if (surface->format->BytesPerPixel % 3 == 0) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	} else {
		// Format not accounted for
		_isLoaded = false;
		return false;
	}
	_isLoaded = true;
	return true;
}

bool ArtemisBase::Texture::loadFromSurface(SDL_Surface * surf) {
	// Loads texture from SDL surface
	_isLoaded = true;
	_texture = surf;
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (_texture->format->BitsPerPixel % 4 == 0) {
		glTexImage2D(GL_TEXTURE_2D, 0, 4, _texture->w, _texture->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, _texture->pixels);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _texture->w, _texture->h, GL_BGRA, GL_UNSIGNED_BYTE, _texture->pixels);
	} else if (_texture->format->BitsPerPixel % 3 == 0) {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, _texture->w, _texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texture->pixels);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _texture->w, _texture->h, GL_RGB, GL_UNSIGNED_BYTE, _texture->pixels);
	} else {
		_isLoaded = false;
	}
	return _isLoaded;
}

bool ArtemisBase::Texture::unload() {
	if (!_isLoaded) return _isLoaded;
	glDeleteTextures(1, &_textureId);
	SDL_FreeSurface(_texture);
	_texture = NULL;
	_isLoaded = false;
	return true;
}

bool ArtemisBase::Texture::bind() {
	// Binds as current texture
	if (!_isLoaded) { return _isLoaded; }
	glBindTexture(GL_TEXTURE_2D, _textureId);
	return _isLoaded;
}

bool ArtemisBase::Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, NULL);
	return true;
}