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
#include "../gui/chat.hpp"
#include <thread>
#include <mutex>



class Game {
public:
    Game();
    ~Game();
    void run();
    void init();
    void debug(bool debug);
    void recieveData();

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
    Loading loading;
    GameCreator creator;
    Inventory inventory;
    Discord discord;
    Chat chat;
    int sock;
    bool stopRecieveData;
    std::thread eventThread;
};


#endif // GAME_HPP
