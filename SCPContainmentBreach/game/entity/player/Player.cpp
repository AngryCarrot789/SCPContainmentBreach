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
    cam_rx = 0.0f;
    cam_ry = 0.0f;
    bob_mag = 0.0f;
    bob_phi = 0.0f;
    mass = 5.0f;
    friction = 0.04f;
    drag = 0.008f;
    onGround = true;
    SetScale(0.6f, 1.2f, 0.6f);
}

void Player::Update() {
    //Update bobbing motion
    float magT = (prev_pos - pos).Mag() / (GAME_DELTATIME);
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
    float
        moveF = 0,
        moveL = 0,
        moveU = 0;

    if (MAIN_INPUT->KeysDown['W']) {
        moveF += 1.0f;
    }
    if (MAIN_INPUT->KeysDown['S']) {
        moveF -= 1.0f;
    }
    if (MAIN_INPUT->KeysDown['A']) {
        moveL += 1.0f;
    }
    if (MAIN_INPUT->KeysDown['D']) {
        moveL -= 1.0f;
    }
    if (MAIN_INPUT->KeysDown[VK_SPACE]) {
        moveU += 1.0f;
    }
    if (MAIN_INPUT->KeysDown[VK_SHIFT]) {
        moveU -= 1.0f;
    }

    Move(moveF, moveL, moveU);

    //Reset ground state after update finishes
    onGround = false;
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

void Player::Move(float moveF, float moveL, float moveUp) {
    move_f = Maths::Clamp(moveF, -1.0f, 1.0f);
    move_l = Maths::Clamp(moveL, -1.0f, 1.0f);
    move_up = Maths::Clamp(moveUp, -1.0f, 1.0f);

    // Movement
    // Movement speed meets an equilibrium between movementSpeed and drag.
    // movementSpeed will keep accelerating an object, but the drag will slow it back down
    float accelerator = (WalkAcceleration * GAME_DELTATIME);
    const Matrix4 camToWorld = LocalToWorld() * Matrix4::CreateRotationY(cam_ry);
    Euler lookDirection = camToWorld.MultiplyDirection(Vector3(-move_l, 0, -move_f));
    Vector3 movementSpeed = lookDirection * accelerator;
    movementSpeed += (Vector3(0, moveUp, 0) * accelerator);
    movementSpeed.ClampMagnitude(WalkSpeed);

    velocity += movementSpeed;

    ////Don't allow non-falling speeds above the player's max speed
    //const float tempY = velocity.y;
    //velocity.y = 0.0f;
    //velocity.ClipMag(GAME_WALK_SPEED);
    //velocity.y = tempY;
}