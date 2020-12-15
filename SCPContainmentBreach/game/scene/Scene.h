#ifndef HF_SCENE
#define HF_SCENE

#include <vector>
#include "../entity/player/Player.h"
//class Sky;
#include "../objects/presets/Sky.h"


class Scene {
public:
	Scene() { }
	/// <summary>
	/// Creates all the objects (on the heap) and positions them.
	/// You should only really call this once. Call RecreateScene to "reload" the scene.
	/// </summary>
	virtual void CreateScene(){}
	/// <summary>
	/// Deletes all the objects (on the heap) and removes them from vObjects.
	/// Only call this when you want to "Dispose" of the scene, aka never use again.
	/// </summary>
	virtual void DestroyScene() {
		for (GameObject* obj : vObjects) {
			delete(obj);
		}
		delete(sky);
		vObjects.clear();
		IsSceneSetUp = false;
	}
	/// <summary>
	/// Deletes all the objects, and then recreates and repositions them
	/// </summary>
	virtual void RecreateScene() {
		DestroyScene();
		CreateScene();
	}

	/// <summary>
	/// Sets up a player's start position within the scene
	/// </summary>
	/// <param name="player"></param>
	virtual void LoadPlayer(Player* player) { }

	bool IsSceneSetUp;

	std::vector<GameObject*> vObjects;
	Sky* sky;
};

#endif