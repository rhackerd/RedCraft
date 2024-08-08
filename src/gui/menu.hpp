#ifndef MENU_HPP
#define MENU_HPP

#include "../gui/gui.hpp"
#include <raylib.h>

class Menu {
public:
    Menu(int screenWidth, int screenHeight);
    ~Menu() = default;

    void draw();
    void updateButtonPositions(int screenWidth, int screenHeight);
    void handleEvents();

    int nextStage();

private:
    Button playButton;
    Button settingsButton;
    Button quitButton;
};

#endif // MENU_HPP
