#include "game/render/debug/DebugDrawing.h"
#include "SCPContainmentBreach.h"
#include "resources.h"
#include "game/GameHeader.h"
#include "math/Maths.h"
#include "GL/glew.h"
#include "game/objects/presets/Sky.h"
#include "game/scene/scenes/MainScene.h"
#include "game/render/gui/TextDrawing.h"

Window* MAIN_WINDOW;
Input* MAIN_INPUT;
//TextDrawing* TEXT_DRAWER;

Presets PRESETS;
//TextDrawing GLTEXT;

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
        600, 100,
        1280, 720,
        false,
        true
    );

    main_window->InitialiseWindow();
    MAIN_WINDOW = main_window;
    MAIN_INPUT = main_window->Inputs;

    //TEXT_DRAWER = new TextDrawing();
    //TEXT_DRAWER->In

    main_player = new Player();

    SetupPresetObjectStuff();

    m_scene = new MainScene();
    m_scene->CreateScene();
    vScenes.push_back(m_scene);

    LoadScene(0);

    //GLTEXT.InitOpenGLText();

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

    Cube* cube = new Cube();
    cube->position = Vector3(2.0f, 2.0f, 5.0f);
    cube->scale = Vector3(0.5f, 0.5f, 0.5f);
    m_scene->vObjects.push_back(cube);

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

            cube->euler.y += 0.3f * GAME_DELTATIME;
            cube->MoveForward(2.0f);


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

// lol me trying to debug be like:

#define ToStr(__i) std::to_string(__i)
#define BToStr(__b) wstring_t(__b == true ? L"true" : L"false"))
#define VecToString(__p1) string_t("X: " + ToStr(__p1.x) + " | Y: " + ToStr(__p1.y) + " | Z: " + ToStr(__p1.z))
#define AABBXStr(__aabb) string_t("MinX: " + ToStr(__aabb.minX) + " | MaxX: " + ToStr(__aabb.maxX))
#define AABBYStr(__aabb) string_t("MinY: " + ToStr(__aabb.minY) + " | MaxY: " + ToStr(__aabb.maxY))
#define AABBZStr(__aabb) string_t("MinZ: " + ToStr(__aabb.minZ) + " | MaxZ: " + ToStr(__aabb.maxZ))
#define AABBString(__aabb) string_t(AABBXStr(__aabb) + "\n" + AABBYStr(__aabb) + "\n" + AABBZStr(__aabb)+ "\n")

#define ToWStr(__i) std::to_wstring(__i)
#define AABBXwStr(__aabb) wstring_t(L"MinX: " + ToWStr(__aabb.minX) + L" | MaxX: " + ToWStr(__aabb.maxX))
#define AABBYwStr(__aabb) wstring_t(L"MinY: " + ToWStr(__aabb.minY) + L" | MaxY: " + ToWStr(__aabb.maxY))
#define AABBZwStr(__aabb) wstring_t(L"MinZ: " + ToWStr(__aabb.minZ) + L" | MaxZ: " + ToWStr(__aabb.maxZ))
#define AABBwString(__aabb) wstring_t(AABBXwStr(__aabb) + L"\n" + AABBYwStr(__aabb) + L"\n" + AABBZwStr(__aabb) + L"\n")
#define ConcatAll(__ln1, __ln2) wstring_t(__ln1 + L"\n" + __ln2)

#define AABBvAABBX(__aabb1, __aabb2) (wstring_t(L"X Intersects: ") + BToStr(aabb1.IntersectsAABBX(aabb2))
#define AABBvAABBY(__aabb1, __aabb2) (wstring_t(L"Y Intersects: ") + BToStr(aabb1.IntersectsAABBY(aabb2))
#define AABBvAABBZ(__aabb1, __aabb2) (wstring_t(L"Z Intersects: ") + BToStr(aabb1.IntersectsAABBZ(aabb2))

#define AABB_OFFSETX(__aabb1, _aabb2) wstring_t(L"X: " + std::to_wstring(__aabb1.GetIntersectionAmountX(_aabb2, true)))
#define AABB_OFFSETY(__aabb1, _aabb2) wstring_t(L"Y: " + std::to_wstring(__aabb1.GetIntersectionAmountY(_aabb2, true)))
#define AABB_OFFSETZ(__aabb1, _aabb2) wstring_t(L"Z: " + std::to_wstring(__aabb1.GetIntersectionAmountZ(_aabb2, true)))

void SCPContainmentBreach::Update()
{
    if (IsSceneActive()) {
        main_player->Update();

        for (GameObject* object1 : m_scene->vObjects) {
            if (!object1) continue;
            object1->Update();
            PhysicalGameObject* phys1 = object1->AsPhysicalGameObject();
            if (!phys1) continue;

            PhysicalGameObject* playerPhys = main_player->AsPhysicalGameObject();
            if (!playerPhys) continue;


            // Player-GameObject collisions

            AxisAlignedBB& aabb1 = main_player->collider;
            AxisAlignedBB& aabb2 = phys1->collider;

            main_player->TryCollision(aabb2);
        }
    }
}

void SCPContainmentBreach::Render(Camera* cam)
{
    if (IsSceneActive()) {
        glClear(GL_DEPTH_BUFFER_BIT);
        m_scene->sky->Draw(cam);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //main_player->DebugDraw(cam);
        PhysicalGameObject* playerPhys = main_player->AsPhysicalGameObject();
        if (playerPhys) {
            DebugDrawing::DrawAABBOutline(cam, playerPhys->collider, 0, 0, 1);
        }

        for (GameObject* object : m_scene->vObjects) {
            object->Draw(cam);

            PhysicalGameObject* phys1 = object->AsPhysicalGameObject();
            if (!phys1) continue;
            DebugDrawing::DrawAABBOutline(cam, phys1->collider, 1, 0, 0);
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
