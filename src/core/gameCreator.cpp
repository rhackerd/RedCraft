#include "gameCreator.hpp"
#include <string>
#include "../gui/gui.hpp"
#include <raylib.h>


GameCreator::GameCreator() : seed(324924929), confirm("Create", 10, GetScreenHeight() - 220, []() {  }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f), load("Quit", 10, GetScreenHeight() - 220, []() { debug("GameState Changed to -1"); }, {223, 208, 184, 255}, {148, 137, 121, 255}, 0.1f) {

}

GameCreator::~GameCreator() {

}


void GameCreator::Init() {
}


void GameCreator::Update() {
    confirm.Events();
    load.Events();
    confirm.setX(GetScreenWidth()-100);
    confirm.setY(GetScreenHeight() - 50);
    
}


void GameCreator::Draw() {
    this->Update();
    DrawText("Address to join: 127.0.0.1:25565", 0,0 , 20, WHITE);
    confirm.draw();
}


void GameCreator::Unload() {
}


int GameCreator::next() {
    if (confirm.isClicked()){
        return 1;
    }
    return 0;
}


int GameCreator::getSeed() {
    return seed;
}


std::string GameCreator::getSaveName() {
    return saveName;
}


int GameCreator::getDifficulty() {
    return difficulty;
}


int GameCreator::getCheats() {
    return cheats;
}