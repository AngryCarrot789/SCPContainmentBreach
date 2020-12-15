#include "game/render/debug/DebugDrawing.h"
#include "SCPContainmentBreach.h"
#include "resources.h"
#include "game/GameHeader.h"
#include "math/Maths.h"
#include "GL/glew.h"
#include "game/objects/presets/Sky.h"
#include "game/scene/scenes/MainScene.h"

Window* MAIN_WINDOW;
Input* MAIN_INPUT;

Presets PRESETS;

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
    MAIN_INPUT = main_window->Inputs;

    main_player = new Player();

    SetupPresetObjectStuff();

    m_scene = new MainScene();
    m_scene->CreateScene();
    vScenes.push_back(m_scene);

    LoadScene(0);

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

    MAIN_WINDOW->SetCursorConfined(true);
    MAIN_WINDOW->SetCursorVisibility(false);

    while (CanRun) {
        int code = main_window->Update();
        if (code == ErrorCodes::ECWINDOW_EXIT) {
            return code;
        }

        if (MAIN_INPUT->KeysPressed[VK_ESCAPE]) {
            Stop();
            return ErrorCodes::ECGLOOP_FORCEEXITED;
        }

        if (MAIN_INPUT->KeysPressed['E']) {
            main_window->ToggleCursorVisibility();
            main_window->ToggleCursorConfined();
        }
        if (MAIN_INPUT->KeysPressed['F']) {
            LockCamera = !LockCamera;
        }

        if (MAIN_INPUT->KeysPressed['1']) {
            LoadScene(0);
        }

        // Used for fixed updates
        const int64_t newTicks = timer.GetSystemTicks();
        for (int i = 0; currentTicks < newTicks && i < GAME_MAX_STEPS; ++i) {
            MAIN_INPUT->UpdateInputs();
            // Update Game
            Update();

            currentTicks += ticksPerStep;
            TotalTicks += 1;
            TicksSinceLastSecond += 1;
            if (TicksSinceLastSecond > GAME_UPDATES_PER_SECOND)
                TicksSinceLastSecond = 0;
        }
        currentTicks = (currentTicks < newTicks ? newTicks : currentTicks);

        if (TotalTicks % renderWait == 0) {
            //Setup camera for rendering
            if (!LockCamera) {
                camera_matrix = main_player->WorldToCam();
            }
            main_camera->worldView = camera_matrix;
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

void SCPContainmentBreach::LoadScene(int index)
{
    if (index >= vScenes.size()) {
        return;
    }

    //m_scene->UnloadPlayer();
    m_scene = vScenes[index];
    m_scene->LoadPlayer(main_player);
}

void SCPContainmentBreach::Update()
{
    if (IsSceneActive()) {
        main_player->Update();
        for (GameObject* object : m_scene->vObjects) {
            object->Update();
        }
    }
}

void SCPContainmentBreach::Render(Camera* cam)
{
    if (IsSceneActive()) {
        glClear(GL_DEPTH_BUFFER_BIT);
        m_scene->sky->Draw(cam);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        main_player->DebugDraw(cam);
        for (GameObject* object : m_scene->vObjects) {
            object->Draw(cam);
            object->DebugDraw(cam);
        }

        DebugDrawing::DrawXYZAxis(cam->projection, main_player->cam_ry, main_player->cam_rx);

        SwapBuffers(MAIN_WINDOW->DeviceContext);
    }
}

void SCPContainmentBreach::SetupPresetObjectStuff()
{
    // Initialise mesh/shader/texture presets
    PRESETS.Meshes.Quad = new Mesh("quad.obj");
    PRESETS.Meshes.Cube = new Mesh("cube.obj");
    PRESETS.Meshes.Tunnel = new Mesh("tunnel.obj");
    PRESETS.Meshes.Ground = new Mesh("ground.obj");
    PRESETS.Meshes.TeaPot = new Mesh("teapot.obj");
    PRESETS.Meshes.Bunny = new Mesh("bunny.obj");

    PRESETS.Shaders.Sky = new Shader("sky");
    PRESETS.Shaders.Pink = new Shader("pink");
    PRESETS.Shaders.Texture = new Shader("texture");

    PRESETS.Textures.Electromagnet = new Texture("electromagnet.bmp", 1, 1);
    PRESETS.Textures.CheckerboardGrey = new Texture("checker_grey.bmp", 1, 1);
    PRESETS.Textures.CheckerboardGreen = new Texture("checker_green.bmp", 1, 1);
    PRESETS.Textures.Gold = new Texture("gold.bmp", 1, 1);
    PRESETS.Textures.White = new Texture("white.bmp", 1, 1);
}
