#include "../core/Game.hpp"
#include "../gui/gui.hpp"
#include "gameCreator.hpp"
#include <cstdint>
#include <cstdlib>
#include <netinet/in.h>
#include <raylib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include "../utils/client.hpp"

Game::Game()
    : gameState(0), width(800), height(600),
      menu(width, height), voxelium(), settings(), loading(), creator(), debugging(false), inventory(), discord(), chat(){
}

Game::~Game() {
    // Properly close the game
    voxelium.~Voxelium();
    settings.~Settings();
    loading.~Loading();
    creator.~GameCreator();
    inventory.~Inventory();
    discord.~Discord();
    menu.~Menu();
    chat.~Chat();
    // Properly close the client
    std::string player_name = "rhacker_8853";
    unload_server(sock,player_name);
    close(sock);
    CloseWindow(); // Properly close the raylib window
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        render();
    }
}

void Game::debug(bool debug) {
    debugging = debug;
}

void Game::init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

    std::string title = debugging ? "RedCraft DEBUG" : "RedCraft";
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    discord.init("1026924641962430464"); // Pass application ID as a string
    voxelium.init();
}

void Game::update() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    menu.updateButtonPositions(screenWidth, screenHeight);
    handleGameState();
}

void Game::render() {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    switch (gameState) {
        case 0:
            loading.draw();
            break;
        case 1:
            menu.draw();
            break;
        case 2:
            creator.Draw();
            break;
        case 3:
            voxelium.draw();
            inventory.draw();
            chat.Draw();
            break;
    }

    if (debugging) {
        char stateText[50];
        snprintf(stateText, sizeof(stateText), "State: %d", gameState);
        DrawText(stateText, 0, 0, 20, WHITE);
        snprintf(stateText, sizeof(stateText), "Win focused: %s", IsWindowFocused() ? "true" : "false");
        DrawText(stateText, 0, 20, 20, WHITE);
        snprintf(stateText, sizeof(stateText), "Win ready: %s", IsWindowReady() ? "true" : "false");
        DrawText(stateText, 0, 40, 20, WHITE);
        snprintf(stateText, sizeof(stateText), "FPS: %d", GetFPS());
        DrawText(stateText, 0, 60, 20, WHITE);
    }

    EndDrawing();
}

void Game::handleGameState() {
    discord.update();
    switch (gameState) {
        case 0:
            gameState += loading.next();
            discord.changeState("Loading...");
            break;
        
        case 1: {
            int nextStage = menu.nextStage();
            if (nextStage == 1) {
                gameState += 1;
                creator.Unload();
            } else if (nextStage == -1) {
                info("closing game");
                CloseWindow();
                exit(0);
            }
            menu.handleEvents();
            discord.changeState("In menu");
            break;
        }

        case 2: {
            gameState += creator.next();
            if (creator.next() == 1) {
                sock = connectToServer(creator.getServerPort());
                chat.sock = sock;
                std::string player_name = "rhacker_8853";
                std::string response = load_server(sock, player_name);
                info(response);

                int x = 0;
                int y = 0;
                std::pair<int, std::vector<int>> cell = get_cell(sock, x, y);
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 16; j++) {
                        // Ensure that cell.second is a std::vector<int>
                        int blockId = cell.second[i * 16 + j]; // Get the block ID from the vector
                        voxelium.setBlock(i, j, blockId-1); // Call setBlock with the block ID
                    }
                }


            }
            discord.changeState("Connecting to server");
            break;
        }

        case 3:
            voxelium.update();
            discord.changeState("In game");
            inventory.update();
            chat.Update();
            break;

        default:
            break;
    }
}