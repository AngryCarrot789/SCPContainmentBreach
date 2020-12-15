#ifndef HF_MAINSCENE
#define HF_MAINSCENE

#include "../Scene.h"
#include "../../objects/presets/Ground.h"
#include "../../objects/presets/Cube.h"
#include "../../objects/presets/Sky.h"

class MainScene : public Scene
{
public:
	MainScene() { }

	~MainScene() {
		if (IsSceneSetUp) {
			DestroyScene();
		}
	}

	void CreateScene() override {
		sky = new Sky();
		Ground* ground = new Ground();
		Cube* cube = new Cube();
		cube->position = Point(-2.0f, 1.01f, 0.0f);
		cube->scale = Size(1, 1, 1);

		vObjects.push_back(ground);
		vObjects.push_back(cube);

		IsSceneSetUp = true;
	}

	void LoadPlayer(Player* player) override {
		player->Reset();
		player->SetPosition(Vector3(0.0f, 1.5f, 5.0f));
	}
};

#endif