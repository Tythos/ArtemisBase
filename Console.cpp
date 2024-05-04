/*
 * Console.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Console::Console() {
	lines = new ConsoleLine("Console initialized");
	state = CS_DOWN;
	speed.unit = UNIT_PCT; speed.value = 20.0f;	// Default speed is 20% of screen height per second
	limit.unit = UNIT_PCT; limit.value = 0.5f;	// Limit console to covering top half of screen
	x.unit = UNIT_PCT; x.value = 0.0f; x.align = ALIGN_NEGATIVE;
	y.unit = UNIT_PCT; y.value = limit.value; y.align = ALIGN_NEGATIVE;
	w.unit = UNIT_PCT; w.value = 1.0f; w.align = ALIGN_NEGATIVE;
	h.unit = UNIT_PCT; h.value = limit.value; h.align = ALIGN_NEGATIVE;
}

ArtemisBase::Console::~Console() {
	if (lines != NULL) {
		delete lines;
		lines = NULL;
	}
}

void ArtemisBase::Console::addLine(ArtemisUtility::String contents) {
	// Add new line to beginning of stack
	if (lines == NULL) {
		lines = new ConsoleLine(contents);
	} else {
		ConsoleLine* oldLines = lines;
		lines = new ConsoleLine(contents);
		lines->next = oldLines;
	}
}

ArtemisUtility::String ArtemisBase::Console::getLine(int n) {
	// Returns the nth line, or "" if index is invalid
	if (lines == NULL) { return ""; }
	else { return lines->get(n)->contents; }
}

void ArtemisBase::Console::render(ArtemisBase::Graphics* context) {
	// Draw background using panel render
	switch(state) {
		case CS_UP:
			// Don't draw anything
			break;
		case CS_DOWN:
		case CS_MOVING_UP:
		case CS_MOVING_DOWN:
		default:
			// Update font, color, size
			if (font != "") {
				context->hTypewriter->setFont(font);
				font = "";
			}
			context->hTypewriter->setColor(fontColor.r, fontColor.g, fontColor.b);
			context->hTypewriter->setFontSize(fontSize);

			// Draw console background (panel)
			Panel::render(context);

			// Draw text from bottom up
			int n = lines->numLines();
			ScreenDimension cx = x;
			ScreenDimension cy = y;
			ArtemisUtility::String line;
			for (int i = 0; i < n && y.value < 1.0f && cy.value < 1.0f; i++) {
				context->hTypewriter->moveCursor(cx, cy);
				line = lines->get(i)->contents;
				context->hTypewriter->type(line, context->getWidth(), context->getHeight());
				cy.value += context->hTypewriter->getFontSize();
			}
			break;
	}
}

void ArtemisBase::Console::update(float dt) {
	// Update panel position based on state and time passed
	switch(state) {
		case CS_MOVING_DOWN:
			// Move panel down by increment
			y.value -= speed.value * dt;
			if (y.value <= limit.value) {
				state = CS_DOWN;
				y.value = limit.value;
			}
			break;
		case CS_MOVING_UP:
			// Move panel up by increment
			y.value += speed.value * dt;
			if (y.value >= 1.0f) {
				state = CS_UP;
				y.value = 1.0f;
			}
			break;
		case CS_UP:
		case CS_DOWN:
		default:
			// Panel remains visible / hidden
			break;
	}
}

void ArtemisBase::Console::setFont(ArtemisUtility::String f) {
	font = f;
}

void ArtemisBase::Console::setFontColor(float r, float g, float b) {
	fontColor.r = r;
	fontColor.g = g;
	fontColor.b = b;
}

void ArtemisBase::Console::setFontSize(float pct) {
	fontSize = pct;
}
