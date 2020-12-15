#ifndef HF_WINDOW
#define HF_WINDOW

#include <Windows.h>
#include "../standard.h"
#include "../inputs/Inputs.h"

typedef struct _WindowPosition {
	_WindowPosition(LONG x, LONG y) {
		X = x;
		Y = y;
	}

	LONG X, Y;

	RECT ToRect() {
		return { X, Y, 0, 0 };
	}
} WindowPosition, WindowSize;

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
	bool      IsFullScreen;
	bool      IsCursorVisible;
	bool      IsCursorConfined;
	Input*    Inputs;

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
	void SetCursorConfined(bool isConfined) { IsCursorConfined = isConfined;}
	void ConfineCursorToCenter();
	RECT GetWindowRectangle();
	RECT GetClientRectangle();

	/// <summary>
	/// Windows have invisible borders around them used as a gripping area for resizing. This is the size of that border
	/// </summary>
	/// <returns>The size of the 'invisible' border used as a resize area grip</returns>
	RECT GetDWMInvisibleBorder() { return { 7, 0, 7, 7 }; }
	/// <summary>
	/// Windows have invisible borders around them used as a gripping area for resizing. This will take that away
	/// </summary>
	/// <returns>The 'visible' position of the window</returns>
	WindowPosition GetDWMFrameWindowPosition();

	WindowPosition GetWindowPosition();
	WindowSize GetWindowSize();
	WindowPosition GetWindowCenter();

	void ToggleFullscreen() { SetFullscreen(!IsFullScreen); }
	void ToggleCursorVisibility() { SetCursorVisibility(!IsCursorVisible); }
	void ToggleCursorConfined() { SetCursorConfined(!IsCursorConfined); }

	int Update();
	LRESULT WindowProc(HWND hCurWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void DisposeWindow();

private:
	void InitialiseOpenGL();
	void CreateGLWindow();
	void SetupInputs();
};

#endif // !ABCD