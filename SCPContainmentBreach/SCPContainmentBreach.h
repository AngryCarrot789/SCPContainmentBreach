#ifndef HP_SCPCONTAINMENTBREACH
#define HP_SCPCONTAINMENTBREACH

#include "logging/Logger.h"
#include "game/timer/Timer.h"
#include "game/objects/GameObject.h"
#include "game/entity/player/Player.h"
#include "game/render/Camera.h"
#include "window/Window.h"
#include "game/scene/Scene.h"

class Sky;

class SCPContainmentBreach
{
public: 
	SCPContainmentBreach();

	int Initialise();

	int Run();
	void Stop();
	bool CanRun;

	void LoadScene(int index);

	void Update();
	void Render(Camera* cam);

	int64_t TotalTicks;
	int64_t TicksSinceLastSecond;
private:
	Window* main_window;
	Timer timer;
	Camera* main_camera;
	Player* main_player;

	bool LockCamera;
	Matrix4 camera_matrix;

	std::vector<Scene*> vScenes;
	Scene* m_scene;
	bool IsSceneActive() { return m_scene != nullptr; }

	void SetupPresetObjectStuff();
};

#endif // !HP_SCPCONTAINMENTBREACH