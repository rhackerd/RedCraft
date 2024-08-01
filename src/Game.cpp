#include "Game.hpp"
#include "menu.hpp"
#include <raylib.h>

Game::Game() 
    : gameState(0), width(800), height(600), 
      menu(width, height), voxelium() {  // Initialize Voxelium instance
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
        char stateText[50];
        snprintf(stateText, sizeof(stateText), "State: %d", gameState);
        DrawText(stateText, 0, 0, 20, WHITE);
        
        if (gameState == 0) {
            if (menu.nextStage() == 1) {
                gameState = 1;
            } else if (menu.nextStage() == -1) {
                info("closing game");
                CloseWindow();
                break;
            }
            menu.draw();
            
            // Handle menu events
            menu.handleEvents();
        }else if(gameState == 1) {
            voxelium.draw();
        }

        EndDrawing();
    }
}

void Game::init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Allow window resizing
    SetConfigFlags(FLAG_MSAA_4X_HINT);     // Optionally set MSAA (anti-aliasing) flag
    InitWindow(width, height, "Game");
    SetTargetFPS(60);

    // Initialize Voxelium if needed
    voxelium.init();
}
