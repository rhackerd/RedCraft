#include "Game.hpp"
#include "gui.hpp"
#include "menu.hpp"
#include <raylib.h>

Game::Game() 
    : gameState(0), width(800), height(600), 
      menu(width, height), voxelium(), settings(), loading() {  // Initialize Voxelium instance
}

Game::~Game() {
}

void Game::run() {
    while (!WindowShouldClose()) {
        // Update button positions based on window size
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        menu.updateButtonPositions(screenWidth, screenHeight);

        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Draw menu
        if (this->debugging) {
            char stateText[50];
            snprintf(stateText, sizeof(stateText), "State: %d", gameState);
            DrawText(stateText, 0, 0, 20, WHITE);
        }
        if (gameState == 0) {
            gameState += loading.next();
            loading.draw();
        }
        else if (gameState == 1) {
            if (menu.nextStage() == 1) {
                gameState += 1;
            } else if (menu.nextStage() == -1) {
                info("closing game");
                CloseWindow();
                break;
            }
            menu.draw();
            
            // Handle menu events
            menu.handleEvents();
        }else if(gameState == 2) {
            voxelium.draw();
        }

        EndDrawing();
    }
}

void Game::debug(bool debug) {
    this->debugging = debug;
}

void Game::init() {
    this->debugging = false;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Allow window resizing
    SetConfigFlags(FLAG_MSAA_4X_HINT);     // Optionally set MSAA (anti-aliasing) flag
    std::string title = "Game " [ this->debugging] ? "RedCraft DEBUG" : "RedCraft";
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);

    // Initialize Voxelium if needed
    voxelium.init();
}
