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
		if (HasLoaded) {
			Unload();
		}
	}

	void Load(Player* player) override {
		Ground* ground = new Ground();

		Cube* cube = new Cube();
		cube->pos = Point(-5.0f, 0.5f, 0.0f);
		cube->scale = Size(1, 1, 1);

		vObjects.push_back(ground);
		vObjects.push_back(cube);
		sky = new Sky();
		player->SetPosition(Vector3(0.0f, 1.5f, 5.0f));
		vObjects.push_back(player);
		HasLoaded = true;
	}

	void Unload() override {
		for (GameObject* obj : vObjects) {
			delete(obj);
		}
		delete(sky);
		vObjects.clear();

		HasLoaded = false;
	}
};

#endif