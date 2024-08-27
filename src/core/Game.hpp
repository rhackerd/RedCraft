#ifndef GAME_HPP
#define GAME_HPP

#include "../utils/logging.hpp"
#include <string>
#include <raylib.h>
#include "../gui/menu.hpp"
#include "Voxelium.hpp"
#include "../utils/settings.hpp"
#include "../gui/loading.hpp"
#include "../core/gameCreator.hpp"
#include "../gui/inventory.hpp"
#include "../utils/discord.hpp"
#include "../utils/client.hpp"


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
    Discord discord;
    int sock;
};


#endif // GAME_HPP
