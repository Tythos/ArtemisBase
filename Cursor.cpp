/**
 * Cursor.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Cursor::Cursor(ArtemisBase::Mouse * m)
: ArtemisBase::Panel(0.0f, 0.0f, 16.0f, 16.0f) {
	SDL_ShowCursor(SDL_DISABLE);
	mouse = m;
	x.unit = UNIT_PCT;
	y.unit = UNIT_PCT;
	w.align = ALIGN_NEGATIVE;
	h.align = ALIGN_POSITIVE;
	isTranslucent = true;
}

ArtemisBase::Cursor::~Cursor(void) {
	// Do not delete mouse; linked, not generated
}

void ArtemisBase::Cursor::render(ArtemisBase::Graphics * context) {
	x.value = mouse->getXCoord().toPct((float)(context->getWidth()));
	y.value = 1.0f - mouse->getYCoord().toPct((float)(context->getHeight()));
	Panel::render(context);
}