#include "menu.hpp"
#include <iostream>
#include <raylib.h>
#include "../utils/logging.hpp"
#include "../resources/textures.hpp"

Menu::Menu(int screenWidth, int screenHeight)
    : playButton("Play", 10, screenHeight - 80, []() { info("GameState Changed to 1"); }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f),
      settingsButton("Settings", 10, screenHeight - 150, []() { info("trying to open settings"); }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f),
      quitButton("Quit", 10, screenHeight - 220, []() { debug("GameState Changed to -1"); }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f) {
}

void Menu::updateButtonPositions(int screenWidth, int screenHeight) {
    playButton.setX(20);
    playButton.setY(screenHeight - 220);
    settingsButton.setX(20);
    settingsButton.setY(screenHeight - 150);

    quitButton.setX(20);
    quitButton.setY(screenHeight - 80);
}

void Menu::draw() {
    DrawBG();
    DrawText("RedCraft", 10, 10, 100, WHITE);
    playButton.draw();
    settingsButton.draw();
    quitButton.draw();
}

void Menu::handleEvents() {
    playButton.Events();
    settingsButton.Events();
    quitButton.Events();
}

void Menu::DrawBG() {
    // Get the dimensions of the screen
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Get the dimensions of the texture
    int textureWidth = grassTexture.width;
    int textureHeight = grassTexture.height;

    // Loop through the screen in steps of the texture size
    for (int y = 0; y < screenHeight; y += textureHeight) {
        for (int x = 0; x < screenWidth; x += textureWidth) {
            DrawTexture(grassTexture, x, y, WHITE);
        }
    }
}


int Menu::nextStage() {
    if (playButton.isClicked()) {
        return 1;
    }
    if (settingsButton.isClicked()) {
        return 0;
    }
    if (quitButton.isClicked()) {
        return -1;
    }
    return 0;
}