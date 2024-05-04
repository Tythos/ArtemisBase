/**
 * Keyboard.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Keyboard::Keyboard() {
	for (int i = 0; i < 312; i++) {
		this->map[i] = false;
	}
}

void ArtemisBase::Keyboard::update() {
	// Set keyboard for new loop (move curr to prev)
	for (int i = 0; i < 312; i++) {
		this->prevMap[i] = this->map[i];
	}
}

void ArtemisBase::Keyboard::update(SDL_Event eve) {
	// Register key event
	if (eve.type == SDL_KEYDOWN) {
		int val = int(eve.key.keysym.sym);
		if (val < 312) {
			this->map[val] = true;
		}
	} else if (eve.type == SDL_KEYUP) {
		int val = int(eve.key.keysym.sym);
		if (val < 312) {
			this->map[int(eve.key.keysym.sym)] = false;
		}
	}
}

bool ArtemisBase::Keyboard::checkPressDown(char key) {
	return (!this->checkPrevKey(key)) && this->checkKey(key);
}

bool ArtemisBase::Keyboard::checkLiftUp(char key) {
	return this->checkPrevKey(key) && (!this->checkKey(key));
}

bool ArtemisBase::Keyboard::checkPrevKey(char key) {
	// Return key status for the given ascii char
	switch(key) {
		case '\b': return this->prevMap[int(SDLK_BACKSPACE)];
		case '\t': return this->prevMap[int(SDLK_TAB)];
		case '\r': return this->prevMap[int(SDLK_RETURN)];
			//case '^[': return this->prevMap[int(SDLK_ESCAPE)];
		case ' ': return this->prevMap[int(SDLK_SPACE)];
		case '!': return this->prevMap[int(SDLK_EXCLAIM)];
		case '"': return this->prevMap[int(SDLK_QUOTEDBL)];
		case '#': return this->prevMap[int(SDLK_HASH)];
		case '$': return this->prevMap[int(SDLK_DOLLAR)];
		case '\'': return this->prevMap[int(SDLK_QUOTE)];
		case '(': return this->prevMap[int(SDLK_LEFTPAREN)];
		case ')': return this->prevMap[int(SDLK_RIGHTPAREN)];
		case '*': return this->prevMap[int(SDLK_ASTERISK)];
		case '+': return this->prevMap[int(SDLK_PLUS)];
		case ',': return this->prevMap[int(SDLK_COMMA)];
		case '-': return this->prevMap[int(SDLK_MINUS)];
		case '.': return this->prevMap[int(SDLK_PERIOD)];
		case '/': return this->prevMap[int(SDLK_SLASH)];
		case '0': return this->prevMap[int(SDLK_0)];
		case '1': return this->prevMap[int(SDLK_1)];
		case '2': return this->prevMap[int(SDLK_2)];
		case '3': return this->prevMap[int(SDLK_3)];
		case '4': return this->prevMap[int(SDLK_4)];
		case '5': return this->prevMap[int(SDLK_5)];
		case '6': return this->prevMap[int(SDLK_6)];
		case '7': return this->prevMap[int(SDLK_7)];
		case '8': return this->prevMap[int(SDLK_8)];
		case '9': return this->prevMap[int(SDLK_9)];
		case ':': return this->prevMap[int(SDLK_COLON)];
		case ';': return this->prevMap[int(SDLK_SEMICOLON)];
		case '<': return this->prevMap[int(SDLK_LESS)];
		case '=': return this->prevMap[int(SDLK_EQUALS)];
		case '>': return this->prevMap[int(SDLK_GREATER)];
		case '?': return this->prevMap[int(SDLK_QUESTION)];
		case '@': return this->prevMap[int(SDLK_AT)];
		case '[': return this->prevMap[int(SDLK_LEFTBRACKET)];
		case '\\': return this->prevMap[int(SDLK_BACKSLASH)];
		case ']': return this->prevMap[int(SDLK_RIGHTBRACKET)];
		case '^': return this->prevMap[int(SDLK_CARET)];
		case '_': return this->prevMap[int(SDLK_UNDERSCORE)];
		case '`': return this->prevMap[int(SDLK_BACKQUOTE)];
		case 'a': return this->prevMap[int(SDLK_a)];
		case 'b': return this->prevMap[int(SDLK_b)];
		case 'c': return this->prevMap[int(SDLK_c)];
		case 'd': return this->prevMap[int(SDLK_d)];
		case 'e': return this->prevMap[int(SDLK_e)];
		case 'f': return this->prevMap[int(SDLK_f)];
		case 'g': return this->prevMap[int(SDLK_g)];
		case 'h': return this->prevMap[int(SDLK_h)];
		case 'i': return this->prevMap[int(SDLK_i)];
		case 'j': return this->prevMap[int(SDLK_j)];
		case 'k': return this->prevMap[int(SDLK_k)];
		case 'l': return this->prevMap[int(SDLK_l)];
		case 'm': return this->prevMap[int(SDLK_m)];
		case 'n': return this->prevMap[int(SDLK_n)];
		case 'o': return this->prevMap[int(SDLK_o)];
		case 'p': return this->prevMap[int(SDLK_p)];
		case 'q': return this->prevMap[int(SDLK_q)];
		case 'r': return this->prevMap[int(SDLK_r)];
		case 's': return this->prevMap[int(SDLK_s)];
		case 't': return this->prevMap[int(SDLK_t)];
		case 'u': return this->prevMap[int(SDLK_y)];
		case 'v': return this->prevMap[int(SDLK_v)];
		case 'w': return this->prevMap[int(SDLK_w)];
		case 'x': return this->prevMap[int(SDLK_x)];
		case 'y': return this->prevMap[int(SDLK_y)];
		case 'z': return this->prevMap[int(SDLK_z)];
		case '~': return this->prevMap[int(SDLK_BACKQUOTE)] && this->checkState() == AKEY_SHIFT;
			//case '^?': return this->prevMap[int(SDLK_DELETE)];
	}
	return false;
}

bool ArtemisBase::Keyboard::checkKey(char key) {
	// Return key status for the given ascii char
	switch(key) {
		case '\b': return this->map[int(SDLK_BACKSPACE)];
		case '\t': return this->map[int(SDLK_TAB)];
		case '\r': return this->map[int(SDLK_RETURN)];
		//case '^[': return this->map[int(SDLK_ESCAPE)];
		case ' ': return this->map[int(SDLK_SPACE)];
		case '!': return this->map[int(SDLK_EXCLAIM)];
		case '"': return this->map[int(SDLK_QUOTEDBL)];
		case '#': return this->map[int(SDLK_HASH)];
		case '$': return this->map[int(SDLK_DOLLAR)];
		case '\'': return this->map[int(SDLK_QUOTE)];
		case '(': return this->map[int(SDLK_LEFTPAREN)];
		case ')': return this->map[int(SDLK_RIGHTPAREN)];
		case '*': return this->map[int(SDLK_ASTERISK)];
		case '+': return this->map[int(SDLK_PLUS)];
		case ',': return this->map[int(SDLK_COMMA)];
		case '-': return this->map[int(SDLK_MINUS)];
		case '.': return this->map[int(SDLK_PERIOD)];
		case '/': return this->map[int(SDLK_SLASH)];
		case '0': return this->map[int(SDLK_0)];
		case '1': return this->map[int(SDLK_1)];
		case '2': return this->map[int(SDLK_2)];
		case '3': return this->map[int(SDLK_3)];
		case '4': return this->map[int(SDLK_4)];
		case '5': return this->map[int(SDLK_5)];
		case '6': return this->map[int(SDLK_6)];
		case '7': return this->map[int(SDLK_7)];
		case '8': return this->map[int(SDLK_8)];
		case '9': return this->map[int(SDLK_9)];
		case ':': return this->map[int(SDLK_COLON)];
		case ';': return this->map[int(SDLK_SEMICOLON)];
		case '<': return this->map[int(SDLK_LESS)];
		case '=': return this->map[int(SDLK_EQUALS)];
		case '>': return this->map[int(SDLK_GREATER)];
		case '?': return this->map[int(SDLK_QUESTION)];
		case '@': return this->map[int(SDLK_AT)];
		case '[': return this->map[int(SDLK_LEFTBRACKET)];
		case '\\': return this->map[int(SDLK_BACKSLASH)];
		case ']': return this->map[int(SDLK_RIGHTBRACKET)];
		case '^': return this->map[int(SDLK_CARET)];
		case '_': return this->map[int(SDLK_UNDERSCORE)];
		case '`': return this->map[int(SDLK_BACKQUOTE)];
		case 'a': return this->map[int(SDLK_a)];
		case 'b': return this->map[int(SDLK_b)];
		case 'c': return this->map[int(SDLK_c)];
		case 'd': return this->map[int(SDLK_d)];
		case 'e': return this->map[int(SDLK_e)];
		case 'f': return this->map[int(SDLK_f)];
		case 'g': return this->map[int(SDLK_g)];
		case 'h': return this->map[int(SDLK_h)];
		case 'i': return this->map[int(SDLK_i)];
		case 'j': return this->map[int(SDLK_j)];
		case 'k': return this->map[int(SDLK_k)];
		case 'l': return this->map[int(SDLK_l)];
		case 'm': return this->map[int(SDLK_m)];
		case 'n': return this->map[int(SDLK_n)];
		case 'o': return this->map[int(SDLK_o)];
		case 'p': return this->map[int(SDLK_p)];
		case 'q': return this->map[int(SDLK_q)];
		case 'r': return this->map[int(SDLK_r)];
		case 's': return this->map[int(SDLK_s)];
		case 't': return this->map[int(SDLK_t)];
		case 'u': return this->map[int(SDLK_y)];
		case 'v': return this->map[int(SDLK_v)];
		case 'w': return this->map[int(SDLK_w)];
		case 'x': return this->map[int(SDLK_x)];
		case 'y': return this->map[int(SDLK_y)];
		case 'z': return this->map[int(SDLK_z)];
		case '~': return this->map[int(SDLK_BACKQUOTE)] && this->checkState() == AKEY_SHIFT;
		//case '^?': return this->map[int(SDLK_DELETE)];
	}
	return false;
}

bool ArtemisBase::Keyboard::checkKey(SDL_Keycode aKey) {
	int val = int(aKey);
	if (val < 312) {
		return this->map[val];
	}
	return false;
}

ArtemisBase::KeyState ArtemisBase::Keyboard::checkState() {
	// Return current keyboard state, checked in given order.
	if (this->checkKey(SDLK_CAPSLOCK)) {
		return AKEY_CAPS;
/* } else if (this->checkKey(SDLK_RMETA) || this->checkKey(SDLK_LMETA)) {
		return AKEY_COMMAND;*/
/* } else if (this->checkKey(SDLK_LSUPER) || this->checkKey(SDLK_RSUPER)) {
		return AKEY_WINDOWS;*/
	} else if (this->checkKey(SDLK_RSHIFT) || this->checkKey(SDLK_LSHIFT)) {
		return AKEY_SHIFT;
	} else if (this->checkKey(SDLK_RCTRL) || this->checkKey(SDLK_LCTRL)) {
		return AKEY_CTRL;
	} else if (this->checkKey(SDLK_RALT) || this->checkKey(SDLK_LALT)) {
		return AKEY_ALT;
/* } else if (this->checkKey(SDLK_NUMLOCK)) {
		return AKEY_NUM;*/
	} else {
		return AKEY_NONE;
	}
}