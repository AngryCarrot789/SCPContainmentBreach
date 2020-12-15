#include "PhysicalGameObject.h"
#include "../GameHeader.h"

PhysicalGameObject::PhysicalGameObject() {
    Reset();
}

void PhysicalGameObject::Reset() {
    GameObject::Reset();
    SetVelocity(Axis::Zero());
    SetScale(1, 1, 1);
    gravity.Set(0.0f, -9.8f, 0.0f);
    mass = 1;
    bounce = 0.0f;
    friction = 0.02f;
    hiGAME_friction = 0.0f;
    drag = 0.008f;
    useGravity = true;
    useCollisions = true;
    SetPosition(0, 0, 0);
}

void PhysicalGameObject::Update() {
    if (useGravity)
        SetVelocity(velocity + gravity * GAME_DELTATIME);
    SetVelocity(velocity * (1.0f - drag));
    SetPosition(pos + velocity * GAME_DELTATIME);
}