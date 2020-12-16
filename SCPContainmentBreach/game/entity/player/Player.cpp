#include "Player.h"
#include <Windows.h>
#include <iostream>
#include "../../GameHeader.h"
#include "../../../resources.h"

Player::Player() {
    Reset();
}

void Player::Reset() {
    PhysicalGameObject::Reset();
    //colliderScale = Vector3(0.4f, 0.9f, 0.4f);
    cam_rx = 0.0f;
    cam_ry = 0.0f;
    bob_mag = 0.0f;
    bob_phi = 0.0f;
    mass = 5.0f;
    friction = 0.04f;
    drag = 0.008f;
    onGround = true;
    useGravity = true;
    SetScale(1.0f, 1.0f, 1.0f);
    //SetScale(0.6f, 1.2f, 0.6f);
}

void Player::Update() {
    //Update bobbing motion
    float magT = (prev_pos - position).Mag() / (GAME_DELTATIME);
    if (!onGround) { magT = 0.0f; }
    bob_mag = bob_mag * (1.0f - GAME_BOB_DAMP) + magT * GAME_BOB_DAMP;
    if (bob_mag < GAME_BOB_MIN) {
        bob_phi = 0.0f;
    }
    else {
        bob_phi += GAME_BOB_FREQ * GAME_DELTATIME;
        if (bob_phi > 2 * Maths::PI) {
            bob_phi -= 2 * Maths::PI;
        }
    }

    //Physics
    PhysicalGameObject::Update();
    //collider.SetPositionFromCenter(pos, PreviewScale);

    //Looking
    Look(MAIN_INPUT->mouse_dx, MAIN_INPUT->mouse_dy);

    //Movement
    float moveB = 0, moveR = 0, moveU = 0;
    if (MAIN_INPUT->KeysDown['W']) {
        moveB -= 1.0f;
    }
    if (MAIN_INPUT->KeysDown['S']) {
        moveB += 1.0f;
    }
    if (MAIN_INPUT->KeysDown['A']) {
        moveR -= 1.0f;
    }
    if (MAIN_INPUT->KeysDown['D']) {
        moveR += 1.0f;
    }
    if (MAIN_INPUT->KeysDown[VK_SPACE]) {
        moveU += 1.0f;
    }
    if (MAIN_INPUT->KeysDown[VK_SHIFT]) {
        moveU -= 1.0f;
    }

    Move(moveB, moveR, moveU);

    //Reset ground state after update finishes
    onGround = false;
}

Matrix4 Player::WorldToCam()
{
    return Matrix4::CreateRotationX(-cam_rx) * Matrix4::CreateRotationY(-cam_ry) * Matrix4::CreateTranslation(-CamOffset()) * WorldToLocal();
}

Matrix4 Player::CamToWorld()
{
    return LocalToWorld() * Matrix4::CreateTranslation(CamOffset()) * Matrix4::CreateRotationY(cam_ry) * Matrix4::CreateRotationX(cam_rx);
}

Vector3 Player::CamOffset()
{
    //If bob is too small, don't even bother
    if (bob_mag < 0.1f) {
        return Vector3::Zero();
    }

    //Convert bob to translation
    const float theta = (Maths::PI / 2) * std::sin(bob_phi);
    const float y = bob_mag * 0.15f * (1.0f - std::cos(theta));
    return Vector3(0, y, 0);
}

void Player::Look(float mouseDx, float mouseDy) {
    //Adjust x-axis rotation
    cam_rx -= mouseDy * GAME_MOUSE_SENSITIVITY;
    if (cam_rx > Maths::PI / 2) {
        cam_rx = Maths::PI / 2;
    }
    else if (cam_rx < -Maths::PI / 2) {
        cam_rx = -Maths::PI / 2;
    }

    //Adjust y-axis rotation
    cam_ry -= mouseDx * GAME_MOUSE_SENSITIVITY;
    if (cam_ry > Maths::PI) {
        cam_ry -= Maths::PI * 2;
    }
    else if (cam_ry < -Maths::PI) {
        cam_ry += Maths::PI * 2;
    }
}

void Player::Move(float moveB, float moveR, float moveU) {
    move_back = Maths::Clamp(moveB, -1.0f, 1.0f);
    move_right = Maths::Clamp(moveR, -1.0f, 1.0f);
    move_up = Maths::Clamp(moveU, -1.0f, 1.0f);

    // Movement
    // Movement speed meets an equilibrium between movementSpeed and drag.
    // movementSpeed will keep accelerating an object, but the drag will slow it back down
    // i think
    float accelerator = (WalkAcceleration * GAME_DELTATIME);
    const Matrix4 camToWorld = LocalToWorld() * Matrix4::CreateRotationY(cam_ry);
    Euler lookDirection = camToWorld.MultiplyDirection(Vector3(move_right, 0, move_back));
    Vector3 movementSpeed = lookDirection * accelerator;
    movementSpeed += (Vector3(0, moveU, 0) * accelerator);
    movementSpeed.ClampMagnitude(WalkSpeed);

    velocity += movementSpeed;

    ////Don't allow non-falling speeds above the player's max speed
    //const float tempY = velocity.y;
    //velocity.y = 0.0f;
    //velocity.ClipMag(GAME_WALK_SPEED);
    //velocity.y = tempY;
}