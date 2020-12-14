#include "Inputs.h"
#include <Windows.h>
#include <memory>

Input::Input() {
    memset(this, 0, sizeof(Input));
}

void Input::EndFrame() {
    memset(KeysPressed, 0, sizeof(KeysPressed));
    memset(MouseButtonsPressed, 0, sizeof(MouseButtonsPressed));
    mouse_dx = mouse_dx * MouseSmoothing + mouse_ddx * (1.0f - MouseSmoothing);
    mouse_dy = mouse_dy * MouseSmoothing + mouse_ddy * (1.0f - MouseSmoothing);
    mouse_ddx = 0.0f;
    mouse_ddy = 0.0f;
}

void Input::UpdateRaw(const tagRAWINPUT* raw) {
    if (raw->header.dwType == RIM_TYPEMOUSE) {
        if (raw->data.mouse.usFlags == MOUSE_MOVE_RELATIVE) {
            mouse_ddx += raw->data.mouse.lLastX;
            mouse_ddy += raw->data.mouse.lLastY;
        }
        if (raw->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) {
            MouseButtonsDown[0] = true;
            MouseButtonsPressed[0] = true;
        }
        if (raw->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) {
            MouseButtonsDown[1] = true;
            MouseButtonsPressed[1] = true;
        }
        if (raw->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) {
            MouseButtonsDown[2] = true;
            MouseButtonsPressed[2] = true;
        }
        if (raw->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) MouseButtonsDown[0] = false;
        if (raw->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) MouseButtonsDown[1] = false;
        if (raw->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) MouseButtonsDown[2] = false;
    }
}