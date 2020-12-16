#include "PhysicalGameObject.h"
#include "../GameHeader.h"
#include "../../logging/Logger.h"

PhysicalGameObject::PhysicalGameObject() {
    Reset();
}

void PhysicalGameObject::Reset() {
    GameObject::Reset();
    colliderScale = Size(1, 1, 1);
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
    Vector3 normal = Vector3(0, 0, 0);
    float intersectX = collider.GetIntersectionAmountX(aabb, true);
    float intersectY = collider.GetIntersectionAmountY(aabb, true);
    float intersectZ = collider.GetIntersectionAmountZ(aabb, true);
    Point difference = PosDifference();
    float mins = Maths::Min3(intersectX, intersectY, intersectZ);

    bool invertX = collider.IsBehindAABBX(aabb);
    bool invertY = collider.IsBehindAABBY(aabb);
    bool invertZ = collider.IsBehindAABBZ(aabb);

    if (intersectX == mins) normal.x = 1.0f;
    if (intersectY == mins) normal.y = 1.0f;
    if (intersectZ == mins) normal.z = 1.0f;

    //Logger::LogLine(L"X: " + std::to_wstring(intersectX));
    //Logger::LogLine(L"Y: " + std::to_wstring(intersectY));
    //Logger::LogLine(L"Z: " + std::to_wstring(intersectZ));

    //position += difference * normal.UnitInvert();
    //if (mins > 0.0f) {
    //    position += (-difference) + 0.001f;
    //    //velocity *= normal.UnitInvert();
    //}


    if (mins > 0.0f) {
        position += (-(difference * normal));
    }

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
