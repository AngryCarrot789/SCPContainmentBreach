#ifndef HF_SCENE
#define HF_SCENE

#include <vector>
#include "../entity/player/Player.h"
//class Sky;
#include "../objects/presets/Sky.h"


class Scene {
public:
	Scene() { }
	virtual void Load(Player* player){}
	virtual void Unload() {}

	bool HasLoaded;

	std::vector<GameObject*> vObjects;
	Sky* sky;
};

#endif