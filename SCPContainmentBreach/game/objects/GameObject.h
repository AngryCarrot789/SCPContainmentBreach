#ifndef HF_GAMEOBJECT
#define HF_GAMEOBJECT

#include <memory>
#include "../render/Camera.h"
#include "../render/Presets.h"
#include "LayerMask.h"

// Forward declarations
class PhysicalGameObject;

class GameObject {
public:
	GameObject();
	virtual ~GameObject() { }

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

	/// <summary>
	/// The Position is the position of the object at the center
	/// </summary>
	Point position;
	/// <summary>
	/// The Euler is the rotation of the object from the center (i think)
	/// </summary>
	Euler euler;
	/// <summary>
	/// The Scale is the size of the object from the center, and the scale units are in all directions from the center.
	/// Meaning, a scale of 1 on the X axis, means it scales out by 1 in the negative axis and 1 in the
	/// positive axis, so effectively the final scale from left to right is 2. Same for Y and Z axis.
	/// A Scale of 2 totals to a scale of 4 from left to right (or bottom to top in the Y axis for example)
	/// </summary>
	Size scale;

	virtual void SetPosition(Point _pos) {
		position = _pos;
	}
	virtual void SetPosition(float x, float y, float z) {
		position = Vector3(x, y, z);
	}
	virtual void SetScale(Size size) {
		scale = size;
	}
	virtual void SetScale(float x, float y, float z) {
		scale = Vector3(x, y, z);
	}

	// Careful when deleting these because some are contained in PRESETS class

	Mesh* mesh;
	Texture* texture;
	Shader* shader;

	ColliderMask Mask;

	bool doesDebugDraw;
};

#endif // !HF_GAMEOBJECT