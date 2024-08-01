#ifndef GUI_HPP
#define GUI_HPP

#include "logging.hpp"
#include <string>
#include <functional>
#include <raylib.h>
#include <glm/glm.hpp>

class Button {
public:
    Button(const std::string& text, int x, int y, const std::function<void()>& callback, Color defaultColor, Color hoverColor, float transitionDuration);
    ~Button() = default;

    void draw();
    bool isHovered();
    bool isClicked();
    void Events();
    void setX(int x);
    void setY(int y);

private:
    std::string text;
    int x;
    int y;
    int width;
    int height;
    bool clicked;
    bool hovered;
    bool disabled;
    glm::vec2 position;
    glm::vec2 size;
    std::function<void()> callback;
    Color defaultColor;
    Color hoverColor;
    Color currentColor;
    float transitionDuration;
    float hoverTime;
    float elapsedTime;
};


class Frame {
public:
    Frame(int x, int y, int width, int height);
    ~Frame();

    void draw();

private:
    int x;
    int y;
    int width;
    int height;
};

#endif
