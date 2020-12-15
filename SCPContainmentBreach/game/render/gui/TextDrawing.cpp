#include "TextDrawing.h"

TextDrawing::TextDrawing()
{

}

void TextDrawing::InitOpenGLText()
{
	// broken
	GLText.init("consola", 1280, 720);
}

void TextDrawing::DrawGLText(string_t text, int x, int y)
{
	GLText.beginString();
	float bbStr[2];
	const char* tmpStr = text.c_str();
	GLText.stringSize(tmpStr, bbStr);
	GLText.drawString(x - bbStr[0] * 0.5, y - bbStr[1], tmpStr, 0, 0xF0F0F0F0);
	GLText.endString(); // will render the whole at once
}
