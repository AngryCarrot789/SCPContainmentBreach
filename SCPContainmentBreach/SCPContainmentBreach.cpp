#include "SCPContainmentBreach.h"
#include "resources.h"
#include "game/GameHeader.h"
#include "math/Maths.h"
#include "GL/glew.h"
#include "game/objects/presets/Sky.h"
#include "game/render/presets/Presets.h"
#include "game/scene/scenes/MainScene.h"

Window* MAIN_WINDOW;
Input* MAIN_INPUT;

SCPContainmentBreach::SCPContainmentBreach()
{
	CanRun = false;
}

int SCPContainmentBreach::Initialise()
{
    main_window = new Window(
        L"SCP Containment Breach",
        L"SCPContainmentBreach",
        MAIN_INSTANCE,
        100, 100,
        1280, 720,
        false,
        true
    );

    main_window->InitialiseWindow();
    MAIN_WINDOW = main_window;
    MAIN_INPUT = main_window->input;

    main_player = new Player();

    m_scene = new MainScene();
    vScenes.push_back(m_scene);
    m_scene->Load(main_player);

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

    main_camera = new Camera();

    while (CanRun) {
        int code = main_window->Update();
        if (code == ErrorCodes::ECWINDOW_EXIT) {
            return code;
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
        currentTicks = (currentTicks < newTicks ? newTicks : currentTicks);

        if (TotalTicks % renderWait == 0) {
            //Setup camera for rendering
            //if (!lockCameraPos) {
            //    cam_matrix = player->WorldToCam();
            //}
            main_camera->worldView = main_player->WorldToLocal();
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
    if (SceneActive()) {
        for (GameObject* object : m_scene->vObjects) {
            object->Update();
        }
    }
}

void SCPContainmentBreach::Render(Camera* cam)
{
    if (SceneActive()) {
        glClear(GL_DEPTH_BUFFER_BIT);
        m_scene->sky->Draw(cam);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (GameObject* object : m_scene->vObjects) {
            object->Draw(cam);
        }

        SwapBuffers(MAIN_WINDOW->DeviceContext);
    }
}