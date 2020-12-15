#ifndef HF_GAMEOBJECT
#define HF_GAMEOBJECT

#include <memory>
#include "../render/Camera.h"
#include "../render/Mesh.h"
#include "../render/Shader.h"
#include "../render/Texture.h"
//Forward declarations

class PhysicalGameObject;

class GameObject {
public:
	GameObject();
	virtual ~GameObject() {}

	virtual void Reset();
	virtual void Draw(Camera* cam);
	virtual void Update() {};
	virtual void OnHit(GameObject& other, Vector3& push) {};

	//Casts
	virtual PhysicalGameObject* AsPhysicalGameObject() { return nullptr; }
	const PhysicalGameObject* AsPhysicalGameObject() const { return const_cast<GameObject*>(this)->AsPhysicalGameObject(); }

	void DebugDraw(Camera* cam);

	// Returns a matrix that can be used to determind the location 
	// of the vertices of a specific object in world space
	virtual Matrix4 LocalToWorld();
	virtual Matrix4 WorldToLocal();

	Vector3 Forward() const;

	Point pos;
	Euler euler;
	Size scale;

	virtual void SetPosition(Point _pos) {
		pos = _pos;
	}
	virtual void SetPosition(float x, float y, float z) {
		pos = Vector3(x, y, z);
	}
	virtual void SetScale(Size size) {
		scale = size;
	}
	virtual void SetScale(float x, float y, float z) {
		scale = Vector3(x, y, z);
	}

	Mesh* mesh;
	Texture* texture;
	Shader* shader;

	bool doesDebugDraw;
};

#endif // !HF_GAMEOBJECT