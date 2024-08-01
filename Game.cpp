#include "Game.hpp"

Game::Game() {
  gameState = 0;
  width = 0;
  height = 0;
}

Game::~Game() {
   
}

void Game::run() {

}

void Game::init() {
  InitWindow(800, 600, "Game");
  SetTargetFPS(60);
}
