#ifndef GAME_HPP
#define GAME_HPP

#include "logging.hpp"
#include <string>
#include <fstream>
#include <raylib.h>
#include "menu.hpp"
#include "Voxelium.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
    void init();

private:
    int gameState;
    int width;
    int height;
    Menu menu;
    Voxelium voxelium;  // Add Voxelium instance
};

#endif // GAME_HPP
