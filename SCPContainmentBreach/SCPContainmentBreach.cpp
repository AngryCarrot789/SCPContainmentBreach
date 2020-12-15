#include "SCPContainmentBreach.h"
#include "resources.h"
#include "game/GameHeader.h"
#include "math/Maths.h"
#include "GL/glew.h"
#include "game/objects/presets/Sky.h"
#include "game/render/presets/Presets.h"

Window* MAIN_WINDOW;
Input* MAIN_INPUT;

SCPContainmentBreach::SCPContainmentBreach()
{
	CanRun = false;
}

int SCPContainmentBreach::Initialise()
{
    wMainWindow = new Window(
        L"SCP Containment Breach",
        L"SCPContainmentBreach",
        MAIN_INSTANCE,
        100, 100,
        1280, 720,
        false,
        true
    );

    wMainWindow->InitialiseWindow();
    MAIN_WINDOW = wMainWindow;
    MAIN_INPUT = new Input();

    Logger::LogLineFormat(L"SCP Containment Breach", L"Successfully initialised");

	return ErrorCodes::EC_NOERROR;
}

int SCPContainmentBreach::Run()
{
	CanRun = true;
    MAIN_WINDOW->ShowMWindow(true, false);

    // Setup Timer
    float renderDeltaTime = 1.0f / GAME_RENDERS_PER_SECOND;
    const int64_t ticksPerStep = timer.SecondsToTicks(GAME_DELTATIME); // 20,000
    int64_t currentTicks = timer.GetSystemTicks(); // 100000 million idk xd
    int64_t renderWait = GAME_UPDATES_PER_SECOND / GAME_RENDERS_PER_SECOND;
    TotalTicks = 0;

    Logger::LogLineFormat(L"SCP Containment Breach", L"Running Game Loop");

    go.mesh = CUBE;
    go.texture = ELECTROMAGNET;
    go.shader = TEXTURE;
    go.pos = Point(0, 0, 0);

    player = new Player();
    player->pos = Point(0, 0, -4);

    main_camera = new Camera();
    
    sky = new Sky();

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

        if (MAIN_INPUT->KeysPressed[VK_ESCAPE]) {
            Stop();
            return ErrorCodes::ECGLOOP_FORCEEXITED;
        }

        // Used for fixed updates
        const int64_t newTicks = timer.GetSystemTicks();
        for (int i = 0; currentTicks < newTicks && i < GAME_MAX_STEPS; ++i) {
            // Update Game
            Update();

            currentTicks += ticksPerStep;
            TotalTicks += 1;
            TicksSinceLastSecond += 1;
            if (TicksSinceLastSecond > GAME_UPDATES_PER_SECOND)
                TicksSinceLastSecond = 0;
            MAIN_INPUT->EndFrame();
        }
        currentTicks = Maths::Max(newTicks, currentTicks);// (currentTicks < newTicks ? newTicks : currentTicks);

        if (TotalTicks % renderWait == 0) {
            //Setup camera for rendering
            //if (!lockCameraPos) {
            //    cam_matrix = player->WorldToCam();
            //}
            main_camera->worldView = player->WorldToLocal();
            main_camera->SetSize(MAIN_WINDOW->Width, MAIN_WINDOW->Height, CAMERA_DEFAULT_NEAR, CAMERA_DEFAULT_FAR, CAMERA_DEFAULT_FOV);
            main_camera->UseViewport();
        
            //Render scene
            Render(main_camera);
            //frame_count++;
        }
    }

	return ErrorCodes::ECGLOOP_EXITED_UNEXPECTED;
}

void SCPContainmentBreach::Stop()
{
    CanRun = false;
    ClipCursor(NULL);
    MAIN_WINDOW->DisposeWindow();
}

void SCPContainmentBreach::Update()
{
    go.Update();
    player->Update();
}

void SCPContainmentBreach::Render(Camera* cam)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    sky->Draw(cam);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, MAIN_WINDOW->Width, MAIN_WINDOW->Height);

    go.Draw(cam);

    SwapBuffers(MAIN_WINDOW->DeviceContext);
}