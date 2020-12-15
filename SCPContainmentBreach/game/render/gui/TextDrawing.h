#ifndef HF_TEXTDRAWING
#define HF_TEXTDRAWING
#include "../../../standard.h"
#include "OpenGLText.h"
class TextDrawing
{
public:
	TextDrawing();
	OpenGLText GLText;

	void InitOpenGLText();
	void DrawGLText(string_t text, int x, int y);
};

extern TextDrawing GLTEXT;

#endif