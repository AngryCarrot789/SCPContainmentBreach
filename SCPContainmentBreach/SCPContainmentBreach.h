#ifndef HP_SCPCONTAINMENTBREACH
#define HP_SCPCONTAINMENTBREACH

#include "logging/Logger.h"
#include "game/timer/Timer.h"
#include "game/objects/GameObject.h"
#include "game/entity/player/Player.h"
#include "game/render/Camera.h"
#include "window/Window.h"

class Sky;

class SCPContainmentBreach
{
public: 
	SCPContainmentBreach();

	int Initialise();

	int Run();
	void Stop();

	bool CanRun;

	void Update();
	void Render(Camera* cam);

	int64_t TotalTicks;
	int64_t TicksSinceLastSecond;
private:
	Window* wMainWindow;
	Timer timer;
	Camera* main_camera;
	Player* player;
	GameObject go;

	Sky* sky;
};

#endif // !HP_SCPCONTAINMENTBREACH