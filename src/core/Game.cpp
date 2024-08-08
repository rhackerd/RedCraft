#include "../core/Game.hpp"
#include "../gui/gui.hpp"
#include <raylib.h>

Game::Game()
    : gameState(0), width(800), height(600),
      menu(width, height), voxelium(), settings(), loading(), creator(), debugging(false), inventory(), discord() {
}

Game::~Game() {
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
    switch (gameState) {
        case 0:
            gameState += loading.next();
            break;

        case 1: {
            int nextStage = menu.nextStage();
            if (nextStage == 1) {
                gameState += 1;
            } else if (nextStage == -1) {
                info("closing game");
                CloseWindow();
                exit(0);
            }
            menu.handleEvents();
            break;
        }

        case 2:
            gameState += creator.next();
            break;

        case 3:
            voxelium.update();
            inventory.update();
            discord.update();
            break;

        default:
            break;
    }
}
