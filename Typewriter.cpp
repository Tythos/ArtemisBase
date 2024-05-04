/**
 * Typewriter.cpp
 */

#include "ArtemisBase.hpp"

ArtemisBase::Typewriter::Typewriter() {
	if (TTF_Init() == -1) {
		printf("aTypewriter::aTypewriter - Unable to initialize TTF\n");
	}
	currFont = NULL;
	color = new ArtemisBase::Color(1.0f, 1.0f, 1.0, 1.0f);
	cursorX.unit = UNIT_PCT; cursorX.align = ALIGN_NEGATIVE; cursorX.value = 0.0f;
	cursorY.unit = UNIT_PCT; cursorY.align = ALIGN_NEGATIVE; cursorY.value = 0.0f;
	fontSize.unit = UNIT_PCT; fontSize.value = 0.05f;
}

ArtemisBase::Typewriter::~Typewriter() {
	if (currFont != NULL) {
		TTF_CloseFont(this->currFont);
		TTF_Quit();
		currFont = NULL;
	}
	delete color;
}

int ArtemisBase::Typewriter::nextpoweroftwo(int x) {
	float arg = (float)x;
	float logbase2 = log(arg) / log(2.0f);
	float d = pow(2, ceil(logbase2));
	return (int)(d + 0.5);
}

bool ArtemisBase::Typewriter::setFont(ArtemisUtility::String fontName) {
	// Load a font
	if (currFont != NULL) {
		TTF_CloseFont(currFont);
	}
	currFont = TTF_OpenFont(fontName.raw(), 24);
	if (currFont == NULL) {
		printf("Unable to initialize font %s\n", fontName.raw());
		return false;
	}
	return true;
}

bool ArtemisBase::Typewriter::setColor(float r, float g, float b) {
	// Convert from RGB int to float color spec
	color->set(r, g, b, 1.0f);
	return true;
}

bool ArtemisBase::Typewriter::stamp(ArtemisUtility::String text) {
    // this method may be OBE but in the meantime we hard-code width/height until either we drop it or the appropriate dimensions can be forwarded
    const int _width = 100;
    const int _height = 100;

	// Stamps text based on default bitmap font
	float x_f = 2.0f * cursorX.value / _width - 1;
	float y_f = 2.0f * cursorY.value / _height - 1;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glLoadIdentity();
	color->setAll();
	glRasterPos2f(x_f, y_f);
	
	float chrSpc = 8.0f;
	int line = 0;
	for (int i = 0; text[i] != NULL; i++) {
		switch(text[i]) {
			case '\n': {
				line++;
				break;
			}
			case 'a': {
				unsigned char curChr[8] = {0x00, 0x3a, 0x46, 0x46, 0x3a, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'b': {
				unsigned char curChr[8] = {0x00, 0x5c, 0x62, 0x42, 0x7c, 0x40, 0x40, 0x40};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'c': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x40, 0x40, 0x3c, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'd': {
				unsigned char curChr[8] = {0x00, 0x3a, 0x46, 0x42, 0x3e, 0x02, 0x02, 0x02};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'e': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x40, 0x7e, 0x42, 0x3c, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'f': {
				unsigned char curChr[8] = {0x00, 0x20, 0x20, 0x20, 0x70, 0x20, 0x28, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'g': {
				unsigned char curChr[8] = {0x38, 0x04, 0x3c, 0x44, 0x44, 0x38, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'h': {
				unsigned char curChr[8] = {0x00, 0x44, 0x44, 0x44, 0x78, 0x40, 0x40, 0x40};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'i': {
				unsigned char curChr[8] = {0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'j': {
				unsigned char curChr[8] = {0x20, 0x50, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'k': {
				unsigned char curChr[8] = {0x00, 0x48, 0x50, 0x60, 0x50, 0x48, 0x40, 0x40};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'l': {
				unsigned char curChr[8] = {0x00, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'm': {
				unsigned char curChr[8] = {0x00, 0x54, 0x54, 0x54, 0x68, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'n': {
				unsigned char curChr[8] = {0x00, 0x48, 0x48, 0x68, 0x50, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'o': {
				unsigned char curChr[8] = {0x00, 0x30, 0x48, 0x48, 0x30, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'p': {
				unsigned char curChr[8] = {0x40, 0x40, 0x78, 0x44, 0x44, 0x78, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'q': {
				unsigned char curChr[8] = {0x06, 0x04, 0x1c, 0x24, 0x24, 0x1c, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'r': {
				unsigned char curChr[8] = {0x00, 0x40, 0x40, 0x40, 0x62, 0x5c, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 's': {
				unsigned char curChr[8] = {0x00, 0x70, 0x08, 0x30, 0x40, 0x38, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 't': {
				unsigned char curChr[8] = {0x00, 0x18, 0x20, 0x20, 0x70, 0x20, 0x20, 0x20};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'u': {
				unsigned char curChr[8] = {0x00, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'v': {
				unsigned char curChr[8] = {0x00, 0x10, 0x28, 0x28, 0x44, 0x44, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'w': {
				unsigned char curChr[8] = {0x00, 0x28, 0x54, 0x54, 0x54, 0x54, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'x': {
				unsigned char curChr[8] = {0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'y': {
				unsigned char curChr[8] = {0x38, 0x04, 0x3c, 0x44, 0x44, 0x44, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'z': {
				unsigned char curChr[8] = {0x00, 0x7e, 0x10, 0x08, 0x04, 0x7e, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'A': {
				unsigned char curChr[8] = {0x00, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'B': {
				unsigned char curChr[8] = {0x00, 0x78, 0x44, 0x44, 0x78, 0x44, 0x44, 0x78};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'C': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x40, 0x40, 0x40, 0x40, 0x40, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'D': {
				unsigned char curChr[8] = {0x00, 0x78, 0x44, 0x42, 0x42, 0x42, 0x44, 0x78};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'E': {
				unsigned char curChr[8] = {0x00, 0x7e, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x7e};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'F': {
				unsigned char curChr[8] = {0x00, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x7e};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'G': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x42, 0x42, 0x46, 0x40, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'H': {
				unsigned char curChr[8] = {0x00, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'I': {
				unsigned char curChr[8] = {0x00, 0x1c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'J': {
				unsigned char curChr[8] = {0x00, 0x38, 0x44, 0x04, 0x04, 0x04, 0x04, 0x1e};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'K': {
				unsigned char curChr[8] = {0x00, 0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'L': {
				unsigned char curChr[8] = {0x00, 0x7e, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'M': {
				unsigned char curChr[8] = {0x00, 0x44, 0x44, 0x44, 0x54, 0x54, 0x6c, 0x44};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'N': {
				unsigned char curChr[8] = {0x00, 0x42, 0x42, 0x46, 0x4a, 0x52, 0x62, 0x42};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'O': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'P': {
				unsigned char curChr[8] = {0x00, 0x40, 0x40, 0x40, 0x7c, 0x42, 0x42, 0x7c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'Q': {
				unsigned char curChr[8] = {0x00, 0x3f, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'R': {
				unsigned char curChr[8] = {0x00, 0x42, 0x44, 0x48, 0x7c, 0x42, 0x42, 0x7c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'S': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x02, 0x02, 0x3c, 0x40, 0x40, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'T': {
				unsigned char curChr[8] = {0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xfe};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'U': {
				unsigned char curChr[8] = {0x00, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'V': {
				unsigned char curChr[8] = {0x00, 0x10, 0x10, 0x28, 0x28, 0x44, 0x44, 0x82};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'W': {
				unsigned char curChr[8] = {0x00, 0x28, 0x28, 0x54, 0x54, 0x54, 0x54, 0x54};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'X': {
				unsigned char curChr[8] = {0x00, 0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'Y': {
				unsigned char curChr[8] = {0x00, 0x10, 0x10, 0x10, 0x10, 0x28, 0x44, 0x82};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case 'Z': {
				unsigned char curChr[8] = {0x00, 0x7e, 0x20, 0x10, 0x08, 0x04, 0x02, 0x7e};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '0': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x62, 0x52, 0x4a, 0x46, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '1': {
				unsigned char curChr[8] = {0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x30, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '2': {
				unsigned char curChr[8] = {0x00, 0x7e, 0x20, 0x10, 0x08, 0x04, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '3': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x42, 0x02, 0x3c, 0x02, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '4': {
				unsigned char curChr[8] = {0x00, 0x04, 0x04, 0xfe, 0x44, 0x24, 0x14, 0x0c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '5': {
				unsigned char curChr[8] = {0x00, 0x78, 0x04, 0x04, 0x78, 0x40, 0x40, 0x7e};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '6': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x3e};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '7': {
				unsigned char curChr[8] = {0x00, 0x10, 0x10, 0x10, 0x3c, 0x08, 0x04, 0x7e};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '8': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '9': {
				unsigned char curChr[8] = {0x00, 0x1c, 0x02, 0x02, 0x3e, 0x42, 0x42, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '.': {
				unsigned char curChr[8] = {0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case ',': {
				unsigned char curChr[8] = {0x20, 0x10, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case ':': {
				unsigned char curChr[8] = {0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case ';': {
				unsigned char curChr[8] = {0x20, 0x10, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '\'': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '"': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x14};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '!': {
				unsigned char curChr[8] = {0x00, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '@': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x40, 0x5c, 0x5a, 0x42, 0x3c, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '#': {
				unsigned char curChr[8] = {0x00, 0x48, 0x48, 0xfc, 0x24, 0x7e, 0x12, 0x12};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '$': {
				unsigned char curChr[8] = {0x00, 0x38, 0x54, 0x14, 0x38, 0x50, 0x54, 0x38};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '%': {
				unsigned char curChr[8] = {0x44, 0x4a, 0x24, 0x10, 0x08, 0x24, 0x52, 0x22};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '^': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x28, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '&': {
				unsigned char curChr[8] = {0x00, 0x3a, 0x44, 0x2a, 0x10, 0x28, 0x44, 0x38};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '*': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x54, 0x38, 0x38, 0x54};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '(': {
				unsigned char curChr[8] = {0x00, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case ')': {
				unsigned char curChr[8] = {0x00, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '-': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '=': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '_': {
				unsigned char curChr[8] = {0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '+': {
				unsigned char curChr[8] = {0x00, 0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '\\': {
				unsigned char curChr[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '|': {
				unsigned char curChr[8] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '{': {
				unsigned char curChr[8] = {0x00, 0x10, 0x20, 0x20, 0x40, 0x20, 0x20, 0x10};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '}': {
				unsigned char curChr[8] = {0x00, 0x20, 0x10, 0x10, 0x08, 0x10, 0x10, 0x20};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '[': {
				unsigned char curChr[8] = {0x00, 0x3c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case ']': {
				unsigned char curChr[8] = {0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x78};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '/': {
				unsigned char curChr[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '?': {
				unsigned char curChr[8] = {0x00, 0x08, 0x00, 0x08, 0x04, 0x02, 0x22, 0x1c};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '>': {
				unsigned char curChr[8] = {0x00, 0x00, 0x10, 0x08, 0x04, 0x08, 0x10, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '<': {
				unsigned char curChr[8] = {0x00, 0x00, 0x04, 0x08, 0x10, 0x08, 0x04, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '~': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			case '`': {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
			default: {
				unsigned char curChr[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
				glBitmap(8, 8, 0.0, 0.0, chrSpc, chrSpc * line, curChr);
				break;
			}
		}
	}
	return true;
}

bool ArtemisBase::Typewriter::type(ArtemisUtility::String text, int contextWidth, int contextHeight) {
	// Print the given text (with the currently-loaded font and color) at the
	// given location. Note that the coordinates will render according to the
	// current GL view matrix, so they may or may not be aligned with the world.
	if (currFont == NULL) {
		//printf("aTypewriter::type - Cannot type string '%s' without a loaded font\n", text);
		return false;
	}
	
	SDL_Surface * initial;
	SDL_Surface * intermediary;
	ScreenDimension w; w.unit = UNIT_PIX;
	ScreenDimension h; h.unit = UNIT_PIX;
	GLuint texture;

	// Render string to surface
	SDL_Color shade;
	shade.r = (int)(color->r * 255);
	shade.g = (int)(color->g * 255);
	shade.b = (int)(color->b * 255);
	initial = TTF_RenderText_Blended(currFont, text.raw(), shade);
	
	// Must blit to power-of-two surface for OpenGL texture
	w.value = (float)(nextpoweroftwo(initial->w));
	h.value = (float)(nextpoweroftwo(initial->h));
	intermediary = SDL_CreateRGBSurface(0, (int)(w.value), (int)(h.value), 32, initial->format->Rmask, initial->format->Gmask, initial->format->Bmask, initial->format->Amask);
	//SDL_SetAlpha(initial, 0, 0);
	SDL_BlitSurface(initial, 0, intermediary, 0);
	
	// Register text surface as texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, (int)(w.value), (int)(h.value), 0, GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	
	// Stand by to render!
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	// Calculate location and dimensions
	float aspectRatio = (float)(contextHeight) / ((float)(contextWidth));
	float left = cursorX.toPct(contextWidth);
	float bottom = cursorY.toPct(contextHeight);
	float right = left + w.toPct(contextWidth) * aspectRatio * fontSize.toPct(contextWidth) / h.toPct(contextWidth);
	float top = bottom + fontSize.toPct(contextWidth);

	// Render on top of scene
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS); {
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(left, bottom);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(left, top);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(right, top);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(right, bottom);
	} glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	// Clean up and set new location
	SDL_FreeSurface(initial);
	SDL_FreeSurface(intermediary);
	glDeleteTextures(1, &texture); // Is this a good idea?
	return true;
}

void ArtemisBase::Typewriter::setFontSize(float fs) {
	fontSize.unit = UNIT_PCT;
	fontSize.value = fs;
}

void ArtemisBase::Typewriter::moveCursor(ArtemisBase::ScreenDimension x, ArtemisBase::ScreenDimension y) {
	cursorX = x;
	cursorY = y;
}
