#include "SCPContainmentBreach.h"
#include "GL/glew.h"
#include "resources.h"

Window* wMainWindow;

SCPContainmentBreach::SCPContainmentBreach()
{
	CanRun = false;
}

int SCPContainmentBreach::Initialise()
{
    Window* mainWindow = new Window(
        L"SCP Containment Breach",
        L"SCPContainmentBreach",
        hMainInstance,
        100, 100,
        1280, 720,
        false,
        true
    );

    mainWindow->InitialiseWindow();

    wMainWindow = mainWindow;

	return ErrorCodes::EC_NOERROR;
}

int SCPContainmentBreach::Run()
{
	CanRun = true;

    wMainWindow->ShowMWindow(true, false);

	while (CanRun) {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            //Handle windows messages
            if (msg.message == WM_QUIT) {
                break;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        Update();

        Render();
	}

	return ErrorCodes::ECGLOOP_EXITED_UNEXPECTED;
}

void SCPContainmentBreach::Stop()
{
    CanRun = false;
    ClipCursor(NULL);
    wMainWindow->DisposeWindow();
}

void SCPContainmentBreach::Update()
{

}

void SCPContainmentBreach::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Window* mWin = wMainWindow;

    glViewport(0, 0, mWin->Width, mWin->Height);



    SwapBuffers(wMainWindow->DeviceContext);

    Sleep(1);
}