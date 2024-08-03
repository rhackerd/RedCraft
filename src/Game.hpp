#ifndef GAME_HPP
#define GAME_HPP

#include "logging.hpp"
#include <string>
#include <raylib.h>
#include "menu.hpp"
#include "Voxelium.hpp"
#include "settings.hpp"
#include "loading.hpp"
#include "gameCreator.hpp"
#include "inventory.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
    void init();
    void debug(bool debug);

private:
    void update();
    void render();
    void handleGameState();

    int gameState;
    int width;
    int height;
    bool debugging;

    Menu menu;
    Voxelium voxelium;
    Settings settings;
    Loading loading;
    GameCreator creator;
    Inventory inventory;
};

#endif // GAME_HPP
