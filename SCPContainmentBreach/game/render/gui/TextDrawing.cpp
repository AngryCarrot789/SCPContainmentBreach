#include "TextDrawing.h"
#include <Windows.h>
#include "../../../resources.h"

TextDrawing::TextDrawing()
{

}

void TextDrawing::InitOpenGLText()
{

}

void TextDrawing::AddText(TextBlock_t txt)
{
	blocks.push_back(txt);
}

void TextDrawing::AddText(string_t text, int x, int y)
{
	blocks.push_back({x, y, text});
}

void TextDrawing::RenderAllText()
{
	for (TextBlock_t text : blocks) {
		RenderText(text);
	}
	blocks.clear();
}

void TextDrawing::RenderText(TextBlock_t text)
{
	RECT r = { 0, 0, MAIN_WINDOW->Width, MAIN_WINDOW->Height };
	r.top += text.x;
	r.left += text.y;
	DrawTextA(MAIN_WINDOW->DeviceContext, text.text.c_str(), text.text.length(), &r, DT_TOP | DT_LEFT | DT_NOCLIP);
}
