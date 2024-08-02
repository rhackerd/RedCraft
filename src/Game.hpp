#ifndef GAME_HPP
#define GAME_HPP

#include "logging.hpp"
#include <string>
#include <fstream>
#include <raylib.h>
#include "menu.hpp"
#include "Voxelium.hpp"
#include "settings.hpp"
#include "loading.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
    void init();
    void debug(bool debug);

private:
    int gameState;
    int width;
    bool debugging;
    int height;
    Menu menu;
    Voxelium voxelium;  // Add Voxelium instance
    Settings settings;
    Loading loading;
};

#endif // GAME_HPP
