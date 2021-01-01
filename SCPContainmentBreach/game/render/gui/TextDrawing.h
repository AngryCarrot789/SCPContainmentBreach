#ifndef HF_TEXTDRAWING
#define HF_TEXTDRAWING
#include "../../../standard.h"
#include "OpenGLText.h"

typedef struct
{
	int x, y;
	string_t text;
} TextBlock_t;

class TextDrawing
{
public:
	TextDrawing();

	void InitOpenGLText();

	void AddText(TextBlock_t txt);
	void AddText(string_t text, int x, int y);
	void RenderAllText();

private:
	std::vector<TextBlock_t> blocks;
	void RenderText(TextBlock_t text);
};

//extern TextDrawing GLTEXT;

#endif