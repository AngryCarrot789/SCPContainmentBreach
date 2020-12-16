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
    SetPosition(position + velocity * GAME_DELTATIME);
}

void PhysicalGameObject::TryCollision(const AxisAlignedBB& aabb)
{
    float intersectX = collider.GetIntersectionAmountX(aabb, true);
    float intersectY = collider.GetIntersectionAmountY(aabb, true);
    float intersectZ = collider.GetIntersectionAmountZ(aabb, true);
    Point difference = PosDifference();

    //if (intersectX > 0.0f) {
    //    SetPosition(position + (-(difference * Vector3::UnitX())));// + Point(0.00001f, 0.0f, 0.0f));
    //}                                                              //
    //if (intersectY > 0.0f) {                                       //
    //    SetPosition(position + (-(difference * Vector3::UnitY())));// + Point(0.0f, 0.00001f, 0.0f));
    //}                                                              //
    //if (intersectZ > 0.0f) {                                       //
    //    SetPosition(position + (-(difference * Vector3::UnitZ())));// + Point(0.0f, 0.0f, 0.00001f));
    //}
}
