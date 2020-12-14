#ifndef HF_WINDOW
#define HF_WINDOW

#include <Windows.h>
#include "../standard.h"

struct Position {
	Position(LONG x, LONG y) {
		X = x;
		Y = y;
	}

	LONG X, Y;
};

class Window
{
public:
	HINSTANCE AppInstance;
	HDC		  DeviceContext;
	HGLRC	  OpenGLContext;
	HWND	  Handle;
	wstring_t Title;
	wstring_t Class;
	LONG      PositionX;
	LONG      PositionY;
	LONG      Width;
	LONG      Height;
	BOOL      IsFullScreen;
	BOOL      IsCursorVisible;
	//Input     Inputs;

	Window();
	Window(wstring_t title,
		   wstring_t className,
		   HINSTANCE instance,
		   LONG xPos, LONG yPos,
		   LONG width, LONG height,
		   BOOL isFullscreen,
		   BOOL cursorVisible);

	void InitialiseWindow();
	void ShowMWindow(bool showCursor = false, bool setFullscreen = false);
	void HideMWindow();
	void SetFullscreen(bool isFullscreen);
	void SetCursorVisibility(bool isVisible);
	void ConfineCursorToCenter();
	RECT GetWindowRectangle();
	Position GetWindowPosition();
	Position GetWindowSize();
	Position GetWindowCenter();

	void ToggleFullscreen() { SetFullscreen(!IsFullScreen); }
	void ToggleCursorVisibility() { SetCursorVisibility(!IsCursorVisible); }

	LRESULT WindowProc(HWND hCurWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void DisposeWindow();

private:
	void InitialiseOpenGL();
	void CreateGLWindow();
	void SetupInputs();
};

#endif // !ABCD