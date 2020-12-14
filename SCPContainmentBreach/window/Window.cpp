#include "Window.h"
#include "../logging/Logger.h"
#include "GL/glew.h"

LRESULT WINAPI StaticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if (window) {
        return window->WindowProc(hWnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
{
    Title = L"AtomiCraft Game";
    Class = L"AtomiCraft";
    PositionX = CW_USEDEFAULT;
    PositionY = CW_USEDEFAULT;
    Width = 1280;
    Height = 720;
    IsFullScreen = false;
    IsCursorVisible = true;
}

Window::Window(wstring_t title,
               wstring_t className,
               HINSTANCE instance,
               LONG xPos, LONG yPos,
               LONG width, LONG height,
               BOOL isFullscreen,
               BOOL cursorVisible)
{
    Title = title;
    Class = className;
    AppInstance = instance;
    PositionX = xPos;
    PositionY = yPos;
    Width = width;
    Height = height;
    IsFullScreen = isFullscreen;
    IsCursorVisible = cursorVisible;
}

void Window::InitialiseWindow()
{
    Logger::LogLineWindow(Title, L"Initialising window");
    SetProcessDPIAware();
    CreateGLWindow();
    InitialiseOpenGL();
    SetWindowLongPtr(Handle, GWLP_USERDATA, (LONG_PTR)this);
}

void Window::InitialiseOpenGL()
{
    //Initialize extensions
    glewInit();

    //Basic global variables
    glClearColor(0.6f, 0.9f, 1.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

void Window::CreateGLWindow()
{
    Logger::LogLineWindow(Title, L"Setting up Window stuff");
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)StaticWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = AppInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = Class.c_str();
    wc.hIconSm = NULL;

    if (!RegisterClassEx(&wc)) {
        Logger::LogLineWindow(Title, L"Failed to register class");
        MessageBoxEx(NULL, L"RegisterClass() failed: Cannot register window class.", L"Error", MB_OK, 0);
        return;
    }
    Logger::LogLineWindow(Title, L"Successfully registered application class/instance");

    //Create the window
    Handle = CreateWindowExW(
        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
        Class.c_str(),
        Title.c_str(),
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        PositionX,
        PositionY,
        Width,
        Height,
        NULL,
        NULL,
        AppInstance,
        NULL);

    if (Handle == NULL) {
        Logger::LogLineWindow(Title, L"Failed to create window");
        MessageBoxEx(NULL, L"CreateWindow() failed:  Cannot create a window.", L"Error", MB_OK, 0);
        return;
    }
    Logger::LogLineWindow(Title, L"Successfully created window");

    DeviceContext = GetDC(Handle);

    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    const int pf = ChoosePixelFormat(DeviceContext, &pfd);
    if (pf == 0) {
        Logger::LogLineWindow(Title, L"Failed to find a suitable pixel format");
        MessageBoxEx(NULL, L"ChoosePixelFormat() failed: Cannot find a suitable pixel format.", L"Error", MB_OK, 0);
        return;
    }
    Logger::LogLineWindow(Title, L"Successfully found a suitable pixel format");

    if (SetPixelFormat(DeviceContext, pf, &pfd) == FALSE) {
        Logger::LogLineWindow(Title, L"Failed to set format specified");
        MessageBoxEx(NULL, L"SetPixelFormat() failed: Cannot set format specified.", L"Error", MB_OK, 0);
        return;
    }
    Logger::LogLineWindow(Title, L"Successfully set up format HDC pixel format");

    DescribePixelFormat(DeviceContext, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    OpenGLContext = wglCreateContext(DeviceContext);
    if (wglMakeCurrent(DeviceContext, OpenGLContext) == FALSE) {
        Logger::LogLineWindow(Title, L"Failed to setup the current context as the OpenGL context");
    }
    Logger::LogLineWindow(Title, L"Successfully set up the current context as the OpenGL context");
}

void Window::SetupInputs()
{
    static const int HID_USAGE_PAGE_GENERIC = 0x01;
    static const int HID_USAGE_GENERIC_MOUSE = 0x02;
    static const int HID_USAGE_GENERIC_JOYSTICK = 0x04;
    static const int HID_USAGE_GENERIC_GAMEPAD = 0x05;

    RAWINPUTDEVICE Rid[3];

    Logger::LogLineWindow(Title, L"Setting up inputs; Mouse, Joystick and Gamepad");
    //Mouse
    Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    Rid[0].dwFlags = RIDEV_INPUTSINK;
    Rid[0].hwndTarget = Handle;

    //Joystick
    Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
    Rid[1].usUsage = HID_USAGE_GENERIC_JOYSTICK;
    Rid[1].dwFlags = 0;
    Rid[1].hwndTarget = 0;

    //Gamepad
    Rid[2].usUsagePage = HID_USAGE_PAGE_GENERIC;
    Rid[2].usUsage = HID_USAGE_GENERIC_GAMEPAD;
    Rid[2].dwFlags = 0;
    Rid[2].hwndTarget = 0;

    Logger::LogWindow(Title, L"Registering raw input devices...");
    if (RegisterRawInputDevices(Rid, 3, sizeof(Rid[0]))) {
        Logger::LogLineWindow(Title, L"Success!");
    }
    else {
        Logger::LogLineWindow(Title, L"Failed :(");
    }
}

void Window::ShowMWindow(bool showCursor, bool setFullscreen)
{
    wstring_t title = Title;
    Logger::LogLineWindow(Title, L"Showing window");
    SetCursorVisibility(showCursor);
    if (IsFullScreen && setFullscreen) {
        SetFullscreen(setFullscreen);
    }
    ShowWindow(Handle, SW_SHOW);
    SetForegroundWindow(Handle);
    SetFocus(Handle);
}

void Window::HideMWindow()
{
    Logger::LogLineWindow(Title, L"Hiding window");
    ShowWindow(Handle, SW_HIDE);
}

void Window::SetFullscreen(bool isFullscreen)
{
    wstring_t title = Title;
    if (isFullscreen) {
        Logger::LogLineWindow(Title, L"Setting window as Fullscreen");
        Width = GetSystemMetrics(SM_CXSCREEN);
        Height = GetSystemMetrics(SM_CYSCREEN);
        SetWindowLong(Handle, GWL_STYLE, WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
        SetWindowLong(Handle, GWL_EXSTYLE, WS_EX_APPWINDOW);
        SetWindowPos(Handle, HWND_TOPMOST, 0, 0, Width, Height, SWP_SHOWWINDOW);
    }
    else {
        Logger::LogLineWindow(Title, L"Reverting window back to normal from fullscreen");
        SetWindowLong(Handle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
        SetWindowLong(Handle, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
        SetWindowPos(Handle, HWND_TOP, PositionX, PositionY, Width, Height, SWP_SHOWWINDOW);
    }
    IsFullScreen = isFullscreen;
}

void Window::SetCursorVisibility(bool isVisible)
{
    ShowCursor(isVisible);
    IsCursorVisible = isVisible;
}

void Window::ConfineCursorToCenter()
{
    RECT rect = GetWindowRectangle();
    SetCursorPos((rect.right + rect.left) / 2, (rect.top + rect.bottom) / 2);
}

RECT Window::GetWindowRectangle()
{
    RECT r = { NULL };
    GetWindowRect(GetConsoleWindow(), &r);
    return r;
}

Position Window::GetWindowPosition()
{
    RECT rect = GetWindowRectangle();
    return Position(rect.left, rect.top);
}

Position Window::GetWindowSize()
{
    RECT rect = GetWindowRectangle();
    return Position(rect.right - rect.left, rect.bottom - rect.top);
}

Position Window::GetWindowCenter()
{
    RECT rect = GetWindowRectangle();
    return Position((rect.right + rect.left) / 2, (rect.top + rect.bottom) / 2);
}

LRESULT Window::WindowProc(HWND hCurWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static PAINTSTRUCT ps;
    static BYTE lpb[256];
    static UINT dwSize = sizeof(lpb);

    switch (uMsg) {
        case WM_SYSCOMMAND:
            if (wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER) {
                return 0;
            }
            break;

        case WM_PAINT:
            BeginPaint(hCurWnd, &ps);
            EndPaint(hCurWnd, &ps);
            return 0;

        case WM_SIZE:
            Width = LOWORD(lParam);
            Height = HIWORD(lParam);
            PostMessage(hCurWnd, WM_PAINT, 0, 0);
            return 0;

        case WM_KEYDOWN:
            //Ignore repeat keys
            if (lParam & 0x40000000) { return 0; }
            //if (GameInput) {
            //    Inputs.KeysDown[wParam & 0xFF] = true;
            //    Inputs.KeysPressed[wParam & 0xFF] = true;
            //}
            return 0;

        case WM_SYSKEYDOWN:
            if (wParam == VK_RETURN) {
                ToggleFullscreen();
                return 0;
            }
            break;

            //case WM_KEYUP:
            //    input.key[wParam & 0xFF] = false;
            //    return 0;

            //case WM_INPUT:
            //    dwSize = sizeof(lpb);
            //    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
            //    input.UpdateRaw((const RAWINPUT*)lpb);
            //    break;

        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hCurWnd, uMsg, wParam, lParam);
}

void Window::DisposeWindow()
{
    wglMakeCurrent(NULL, NULL);
    ReleaseDC(this->Handle, this->DeviceContext);
    wglDeleteContext(this->OpenGLContext);
    DestroyWindow(this->Handle);
}
