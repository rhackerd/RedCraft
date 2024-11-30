#include "gui.hpp"
#include <raylib.h>
#include <iostream>

Button::Button(const std::string& text, int x, int y, const std::function<void()>& callback, Color defaultColor, Color hoverColor, float transitionDuration)
    : text(text), x(x), y(y), width(100), height(50), callback(callback), clicked(false), hovered(false), disabled(false), 
      defaultColor(defaultColor), hoverColor(hoverColor), currentColor(defaultColor), transitionDuration(transitionDuration), hoverTime(0.0f) {
    this->position = glm::vec2(x, y);
    this->size = glm::vec2(width, height);
}



void Button::setX(int x) {
    this->x = x;
    this->position.x = x;
}

void Button::setY(int y) {
    this->y = y;
    this->position.y = y;
}


void Button::draw() {
    if (hovered) {
        hoverTime += GetFrameTime();
        if (hoverTime > transitionDuration) {
            hoverTime = transitionDuration;
        }
    } else {
        hoverTime -= GetFrameTime();
        if (hoverTime < 0.0f) {
            hoverTime = 0.0f;
        }
    }

    float t = hoverTime / transitionDuration;
    currentColor = { 
        static_cast<unsigned char>(defaultColor.r + t * (hoverColor.r - defaultColor.r)),
        static_cast<unsigned char>(defaultColor.g + t * (hoverColor.g - defaultColor.g)),
        static_cast<unsigned char>(defaultColor.b + t * (hoverColor.b - defaultColor.b)),
        static_cast<unsigned char>(defaultColor.a + t * (hoverColor.a - defaultColor.a))
    };

    DrawRectangleRounded(Rectangle{this->position.x, this->position.y, this->size.x, this->size.y}, 0.2f, 10, currentColor);
    
    const float borderThickness = 2.0f;
    DrawRectangleRounded(
        Rectangle{
            this->position.x,
            this->position.y,
            this->size.x - borderThickness,
            this->size.y - borderThickness
        },
        0.2f,
        10,
        BLACK
    );
    
    int textWidth = MeasureText(this->text.c_str(), 20);
    int textX = this->position.x + (this->size.x - textWidth) / 2;
    int textY = this->position.y + (this->size.y - 20) / 2;
    DrawText(this->text.c_str(), textX, textY, 20, BLACK);
}

bool Button::isClicked() {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && this->isHovered();
}

bool Button::isHovered() {
    return CheckCollisionPointRec(GetMousePosition(), Rectangle{this->position.x, this->position.y, this->size.x, this->size.y});
}

void Button::Events() {
    this->hovered = this->isHovered();
    if (this->isClicked()) {
        this->callback(); // Call the callback function if button is clicked
    }
}

Frame::Frame(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {
}

Frame::~Frame() {
}

void Frame::draw() {
    DrawRectangle(this->x, this->y, this->width, this->height, RED);
}
