#ifndef HF_PHYSICALOBJECT
#define HF_PHYSICALOBJECT

#include "GameObject.h"
#include "../collision/AxisAlignedBB.h"

class PhysicalGameObject : public GameObject {
public:
    PhysicalGameObject();
    virtual ~PhysicalGameObject() override {}

    virtual void Reset() override;
    virtual void Update() override;

    void SetPositionFromCenter(const Vector3& _pos) {
        prev_pos = position;
        SetPosition(_pos);
    }

    void SetVelocity(Axis vel) {
        velocity = vel;
        UpdateAABB();
    }

    void SetPosition(Point _pos) override {
        prev_pos = position;
        position = _pos;
        UpdateAABB();
    }
    void SetPosition(float x, float y, float z) override {
        prev_pos = position;
        position = Vector3(x, y, z);
        UpdateAABB();
    }
    void SetScale(Size size) override {
        scale = size;
        UpdateAABB();
    }
    virtual void SetScale(float x, float y, float z) {
        scale = Vector3(x, y, z);
        UpdateAABB();
    }
    void UpdateAABB() {
        collider.SetPositionFromCenter(position, scale);
    }

    virtual PhysicalGameObject* AsPhysicalGameObject() override { return this; }

    AxisAlignedBB collider;

    Axis gravity;
    Axis velocity;
    float mass;
    float bounce;
    float friction;
    float hiGAME_friction;
    float drag;
    bool useGravity;
    bool useCollisions;

    Point prev_pos;

    Point PosDifference() {
        return position - prev_pos;
    }

    void TryCollision(const AxisAlignedBB& aabb);
};


#endif