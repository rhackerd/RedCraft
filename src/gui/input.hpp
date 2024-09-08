#ifndef INPUT_HPP
#define INPUT_HPP
#include <raylib.h>
#include <string>

class Input {
public:
    Input(int x, int y);
    ~Input();
    void update();
    void draw();

private:
    void drawText();
    void drawBackground();  // Corrected name
    void events();
    bool checkHovered();
    void checkEnabled();

    std::string actText;
    bool enabled;
    bool hovered;
    int posX, posY;  // Added member variables to hold position
};
#endif 