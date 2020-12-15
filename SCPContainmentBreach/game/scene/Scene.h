#ifndef HF_SCENE
#define HF_SCENE

#include <vector>
#include "../entity/player/Player.h"

class Scene {
public:
	virtual void Load(std::vector<int>& objs, Player& player){}
	virtual void Unload() {}
};

#endif