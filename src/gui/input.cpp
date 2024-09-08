#include "../gui/input.hpp"
#include <raylib.h>
#include <string>

Input::Input(int x, int y) : posX(x), posY(y), actText(""), enabled(true), hovered(false) {
    // Initialize member variables using initializer list
}

Input::~Input() {
    // Destructor implementation (if needed)
}

void Input::update() {
    events();
}

void Input::draw() {
    drawBackground();
    drawText();
}

void Input::drawText() {
    DrawText(actText.c_str(), posX + 2, posY + 2, 20, WHITE);
}

void Input::drawBackground() {
    DrawRectangle(posX, posY, 150, 40, BLACK);  // Adjust dimensions if needed
}

void Input::events() {
    checkEnabled();
    if (enabled) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {  // Handle only printable characters
                actText += static_cast<char>(key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && actText.length() > 0) {
            actText.pop_back();  // Remove last character on backspace
        }
    }
}

bool Input::checkHovered() {
    return CheckCollisionPointRec(GetMousePosition(),
                                  {static_cast<float>(posX), static_cast<float>(posY), 150.0f, 40.0f});  // Adjust dimensions
}

void Input::checkEnabled() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (checkHovered()) {
            enabled = true;
        } else {
            enabled = false;
        }
    }
}